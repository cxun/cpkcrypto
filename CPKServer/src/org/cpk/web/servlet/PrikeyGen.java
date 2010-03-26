package org.cpk.web.servlet;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.net.URI;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.Security;
import java.security.SignatureException;
import java.security.cert.Certificate;
import java.security.cert.CertificateEncodingException;
import java.security.spec.InvalidKeySpecException;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.TimeZone;

import javax.jdo.PersistenceManager;
import javax.jdo.Query;
import javax.security.auth.x500.X500Principal;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.bouncycastle.x509.X509V3CertificateGenerator;
import org.cpk.crypto.MapAlgMgr;
import org.cpk.crypto.MappingAlgorithmException;
import org.cpk.crypto.pubmatrix.DERPubmatrixSerializer;
import org.cpk.crypto.pubmatrix.PubMatrix;
import org.cpk.crypto.secmatrix.DERSecmatrixSerializer;
import org.cpk.crypto.secmatrix.SecMatrix;
import org.cpk.web.jdo.JdoSecMatrix;
import org.cpk.web.jdo.PMF;

import com.dyuproject.openid.OpenIdUser;
import com.dyuproject.openid.RelyingParty;
import com.dyuproject.openid.ext.AxSchemaExtension;
/**
 * start authentication with OpenID
 * @author Administrator
 */
public class PrikeyGen extends HttpServlet {
	private static final long serialVersionUID = 4906098085632188831L;
	private static Logger logger = Logger.getLogger(PrikeyGen.class);
	
	/// strings indicating uri
	private static final String GENKEY = "/keygen/GenKey";
	private static final String GENKEY_CERT = "/keygen/GenKeyAndCert";
	private static final String GENCERT = "/keygen/GenCert";
	private static final String GET_PUBMATRIX = "/GetPubMatrix";
	private static final Object GET_ROOTCERT = "/GetRootCert";
	
	/// string indicating init parameters of Servlet
	private static final String EC_CURVE_NAME = "EcCurveName";
	private static final String ROW_CNT = "RowCnt";
	private static final String COL_CNT = "ColCnt";
	private static final String MAP_ALG = "MappingAlg";
	
	
	///secmatrix & pubmatrix
	private SecMatrix m_secMatrix = null;
	private PubMatrix m_pubMatrix = null;
	private byte[] m_bytesPubMatrix = null;
	
	//variables
	private String m_appURI = null;
	private String m_timeZone = null;
	private Date m_notBefore = null;
	private Date m_notAfter = null;
	private JdoSecMatrix m_storeData = null;
	
	private PrivateKey m_serverPrivateKey = null;
	private PublicKey m_serverPublicKey = null;
	private Certificate m_serverCertificate = null;
	
	static
	{		
		RelyingParty.getInstance()
		.addListener(new AxSchemaExtension()
		.addExchange("email")
//		.addExchange("country")
//		.addExchange("language")
		);
	}
	
	
	@Override	
	public void init(ServletConfig config) throws ServletException{
		
		logger.info("Initialization start");
		
		try{
			MapAlgMgr.Configure("MapAlg.properties", "OIDMapAlg.properties");
		}catch(Exception ex){
			logger.error("Not all the configuration files are ready...exit", ex);
			logger.error("Maybe 'MapAlg.properties' or 'OIDMapAlg.properties' not present?", ex);
			throw new ServletException("PrikeyGen Init failed", ex);		
		}	
		
		if( -1 == Security.addProvider(new BouncyCastleProvider())){ //add this provider
			logger.error("Failed to add BouncyCastleProvider");
			throw new ServletException("PrikeyGen init failed");			
		}
		
		PersistenceManager pm = PMF.get().getPersistenceManager();
		SecMatrix secMatrix = null;
		try{
			logger.info("ready to init secmatrix");
			//if can find in JDO store, then deserialize it;
			//or create a new instance of SecMatrix and serialize to store
			
			m_timeZone = config.getServletContext().getInitParameter("TimeZone");
			logger.debug("timezone="+m_timeZone);
			Calendar c = Calendar.getInstance(TimeZone.getTimeZone(m_timeZone));
			int year = c.get(Calendar.YEAR);
			c.clear();
			c.set(year, 0, 1, 0, 0, 0);
			m_notBefore = c.getTime();
			c.set(year+1, 0, 1, 0, 0, 0);
			m_notAfter = c.getTime();

			logger.info("query store for stored secmatrix");
			//construct query
			Query query = pm.newQuery(JdoSecMatrix.class, "this.start == date");
			query.declareParameters("java.util.Date date");
			List<JdoSecMatrix> result = (List<JdoSecMatrix>)query.execute(m_notBefore);

			if(result.isEmpty()){
				//not found, create new instance
				logger.info("not found, create new one");
				String ecCurveName = config.getInitParameter(EC_CURVE_NAME);
				int rowCnt = Integer.parseInt(config.getInitParameter(ROW_CNT));
				int colCnt = Integer.parseInt(config.getInitParameter(COL_CNT));
				String mapAlg = config.getInitParameter(MAP_ALG);

				logger.info("generating secmatrix...");
				m_appURI = config.getServletContext().getInitParameter("AppURI");			
				secMatrix = SecMatrix.GenerateNewMatrix(rowCnt, colCnt, ecCurveName, mapAlg, new URI(m_appURI));
				ByteArrayOutputStream baos = new ByteArrayOutputStream();
				DERSecmatrixSerializer serial = new DERSecmatrixSerializer(null, baos);
				serial.ExportSecMatrix(secMatrix);
				
				logger.info("generating secmatrix...done");
				
				logger.info("serializing secmatrix...");
				m_storeData = new JdoSecMatrix(baos.toByteArray(), m_notBefore, m_notAfter);
				pm.makePersistent(m_storeData);				
				logger.info("serialize secmatrix... done");
			}else{
				//found, deserialize the bytes
				logger.info("found in storage, deserialize it...");
				assert(result.size() == 1);
				
				JdoSecMatrix jdoSecMatrix = result.get(0);
				ByteArrayInputStream bais = new ByteArrayInputStream(jdoSecMatrix.getBytesSecmatrix().getBytes());
				DERSecmatrixSerializer serial = new DERSecmatrixSerializer(bais, null);
				secMatrix = serial.GetSecMatrix();
				
				logger.info("deserialize secmatrix... done");
			}
			
			/// generate pubmatrix from secmatrix
			logger.info("generate pubmatrix, this may take some time...");
			m_secMatrix = secMatrix;			
			m_pubMatrix = secMatrix.DerivePubMatrix();
			logger.info("generate pubmatrix, done");
			
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			DERPubmatrixSerializer pubSerial = new DERPubmatrixSerializer(null, baos);
			pubSerial.ExportPubMatrix(m_pubMatrix);
			m_bytesPubMatrix = baos.toByteArray();
			logger.info("generated serialized pubmatrix for retrieval");
			
			m_serverPrivateKey = m_secMatrix.GeneratePrivateKey(m_appURI);
			logger.info("generated the server's private key");
			
			m_serverPublicKey = m_pubMatrix.GeneratePublicKey(m_appURI);
			logger.info("generated the server's public key");
			
			m_serverCertificate = CreateCertificate(
					m_serverPrivateKey, 
					m_serverPublicKey,
					m_appURI);
			logger.info("generated the server's self-signed certificate");
			
		}catch (Exception e) {
			logger.error("Init secmatrix and pubmatrix failed", e);
			throw new ServletException("Init secmatrix and pubmatrix failed", e);
		}finally{
			pm.close();
		}
		
		logger.info("Initialization end");
	}
		
	@Override
	public void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException{
		try{
			String requestUri = req.getRequestURI();
			logger.debug("requestURL: " + req.getRequestURL());
			if(requestUri.equals(GENKEY)){
				ReturnPrivateKey(req, resp);
			}else if(requestUri.equals(GENCERT)){
				ReturnUserCert(req, resp);
			}else if(requestUri.equals(GET_PUBMATRIX)){
				ReturnPubMatrix(resp);
			}else if(requestUri.equals(GET_ROOTCERT)){
				ReturnRootCert(resp);
			}else{
				resp.setStatus(HttpServletResponse.SC_FORBIDDEN);
			}
		}catch(Exception ex){
			logger.error("Error when processing request: " + req.getRequestURL(), ex);
		}
	}
	
	private void ReturnUserCert(HttpServletRequest req, HttpServletResponse resp)
	throws InvalidKeySpecException, MappingAlgorithmException, CertificateEncodingException, InvalidKeyException, NoSuchAlgorithmException, SignatureException, IOException{
		logger.debug("returning user cert");
		OpenIdUser user = (OpenIdUser)req.getAttribute(OpenIdUser.ATTR_NAME);
		Map<String,String> axschema = AxSchemaExtension.get(user);
		String email = axschema.get("email");
		logger.debug("generate public key, id = " + email);
		PublicKey pubKey = m_pubMatrix.GeneratePublicKey(email);
		logger.debug("generate user certificate");
		Certificate cert = CreateCertificate(m_serverPrivateKey, pubKey, email);
		TransferToClient(cert.getEncoded(), resp);
		logger.debug("returning user cert...done");		
	}

	private void ReturnRootCert(HttpServletResponse resp)
			throws CertificateEncodingException, IOException {
		logger.debug("return root cert");
		byte[] bytes = m_serverCertificate.getEncoded();
		TransferToClient(bytes, resp);
		logger.debug("return root cert...done");
	}
	
	private void TransferToClient(byte[] data, HttpServletResponse resp) throws IOException{
		BufferedOutputStream bos = new BufferedOutputStream(resp.getOutputStream());
		bos.write(data);
	}
	
	/**
	 * create the certificate for subject 
	 * @param prikey the issuer's private key
	 * @param pubkey the subject's public key
	 * @param subject the subject's CN
	 * @return created certificate
	 */
	private Certificate CreateCertificate(PrivateKey prikey, PublicKey pubkey, String subject)
		throws IOException, CertificateEncodingException,
		NoSuchAlgorithmException, SignatureException, InvalidKeyException {
		X509V3CertificateGenerator certGen = new X509V3CertificateGenerator();
		certGen.setIssuerDN(new X500Principal("CN="+m_appURI+", OU=CPK, O=CPK, C=CN"));
		
		certGen.setNotAfter(m_notAfter);
		certGen.setNotBefore(m_notBefore);

		certGen.setPublicKey(pubkey);		
		certGen.setSerialNumber(new BigInteger(IncCertSerial().toString()));
		certGen.setSignatureAlgorithm("SHA1withEC");		
		certGen.setSubjectDN(new X500Principal("CN="+subject+", OU=Unknown, O=Unknown, C=CN"));

		Certificate cert = certGen.generate(prikey);
		return cert;
	}
	
	/**
	 * increment the certificate serial, and return the value before increment
	 * @return the value before increment
	 */
	private synchronized Integer IncCertSerial(){
		Integer ret = m_storeData.getCertSerial();
		m_storeData.setCertSerial(ret + 1);
		return ret;
	}

	private void ReturnPrivateKey(HttpServletRequest req,
			HttpServletResponse resp) throws InvalidKeySpecException,
			IOException {
		logger.debug("returning private key");
		OpenIdUser user = (OpenIdUser)req.getAttribute(OpenIdUser.ATTR_NAME);
		Map<String,String> axschema = AxSchemaExtension.get(user);
		String email = axschema.get("email");
		logger.debug("generate privateKey, id = " + email);
		PrivateKey priKey = m_secMatrix.GeneratePrivateKey(email);
		TransferToClient(priKey.getEncoded(), resp);
		logger.debug("returning private key...done");
	}

	private void ReturnPubMatrix(HttpServletResponse resp) throws IOException {
		logger.debug("returning pubmatrix");
		TransferToClient(m_bytesPubMatrix, resp);
		logger.debug("returning pubmatrix...done");
	}
	
	@Override
	public void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException{
		doGet(req, resp);
	}
}
