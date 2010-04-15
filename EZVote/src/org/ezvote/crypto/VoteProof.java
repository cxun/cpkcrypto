package org.ezvote.crypto;

import java.io.IOException;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

import org.apache.log4j.Logger;
import org.bouncycastle.asn1.ASN1EncodableVector;
import org.bouncycastle.asn1.ASN1InputStream;
import org.bouncycastle.asn1.ASN1OctetString;
import org.bouncycastle.asn1.DEROctetString;
import org.bouncycastle.asn1.DERSequence;
import org.bouncycastle.asn1.x9.X9ECPoint;
import org.bouncycastle.jce.spec.ECParameterSpec;
import org.bouncycastle.math.ec.ECCurve;
import org.bouncycastle.math.ec.ECPoint;
import org.ezvote.util.Utility;

/**
 * represent a proof of voter casting a ballot either have value of G or -G;
 * provide functionalities of:
 * 1. make proof
 * 2. verify proof
 * 3. serial/deserial proof
 * @author Red
 */
public class VoteProof {
	
	private static Logger _log = Logger.getLogger(VoteProof.class);
	
	/**
	 * given clear text and cipher text, make a proof that the cleartext is either G or -G
	 * @param ecParam the ec curve's parameter
	 * @param P the public key of ciphertext
	 * @param omsg the clear text
	 * @param ct the cipher text
	 * @param k the random used in creating CipherText
	 * @return an non-interactive proof
	 * @throws ProofException 
	 */
	public static VoteProof createProof(
			ECParameterSpec ecParam,
			ECPoint P,
			ECPoint omsg,
			CipherText ct,
			BigInteger k
		) throws ProofException{
		
		try{
			ECPoint G = ecParam.getG();
			int bitlen = ecParam.getN().bitLength();
			SecureRandom random = new SecureRandom();
					
			ECPoint x = ct.getX();
			ECPoint y = ct.getY();
			BigInteger order = ecParam.getN(); //the order of eccurve
			BigInteger w = new BigInteger(bitlen, random).mod(order);

			VoteProof vp = new VoteProof();

			if(omsg.equals(G)){ //vote is `1'
				vp._r1 = new BigInteger(bitlen, random).mod(order);
				vp._d1 = new BigInteger(bitlen, random).mod(order); 

				vp._a1 = G.multiply(vp._r1).add(x.multiply(vp._d1)); //a1 = r1*G + d1*x
				vp._b1 = P.multiply(vp._r1).add(y.add(G).multiply(vp._d1));//b1 = r1*P + (y+G)*d1
				vp._a2 = G.multiply(w); //a2 = w*G
				vp._b2 = P.multiply(w); //b2 = w*P

				BigInteger c = makeChallenge(vp).mod(order); //c is generated by digest				
				
				vp._d2 = c.subtract(vp._d1).mod(order); //d2 = c - d1				
				vp._r2 = w.subtract(k.multiply(vp._d2)).mod(order); //r2 = w-k*d2
				
				_log.debug("created c="+c.toString());
				_log.debug("created d1="+vp._d1.toString());
				_log.debug("created d2="+vp._d2.toString());
				_log.debug("created w ="+w.toString());
				_log.debug("created r2="+vp._r2.toString());
				_log.debug("created k ="+k.toString());
				
				assert(x.equals(G.multiply(k))); //x == G*k
				assert(x.multiply(vp._d2).equals(G.multiply(k).multiply(vp._d2))); // x*d2 == G*k*d2
				
				assert(G.multiply(k).multiply(vp._d2).equals(x.multiply(vp._d2))); // ((G*k)*d2) == x*d2
				assert(G.multiply(k).multiply(vp._d2).equals(G.multiply(k.multiply(vp._d2))));  //(G*k)*d2 == G*(k*d2)
				
				assert(G.multiply(vp._d2.multiply(k)).equals(x.multiply(vp._d2))); // (G*(d2*k)) == x*d2
				assert(w.equals(vp._r2.add(vp._d2.multiply(k)).mod(order))); //w == r2 + d2*k
				assert(vp._r2.equals(w.subtract(k.multiply(vp._d2)).mod(order))); //r2 == w - k*d2
				assert(vp._a2.equals(G.multiply(w))); //a2 == w*G
				
				assert(c.equals(vp._d1.add(vp._d2).mod(order)));  // c==d1+d2
				assert(vp._a1.equals(G.multiply(vp._r1).add(x.multiply(vp._d1))));
				assert(vp._b1.equals(P.multiply(vp._r1).add(y.add(G).multiply(vp._d1))));				
				assert(vp._a2.equals(G.multiply(vp._r2).add(x.multiply(vp._d2))));		
				assert(vp._b2.equals(P.multiply(vp._r2).add(y.subtract(G).multiply(vp._d2))));

			}else if(omsg.equals(G.negate())){ //vote is `-1'
				vp._r2 = new BigInteger(bitlen, random).mod(order);
				vp._d2 = new BigInteger(bitlen, random).mod(order);
				
				vp._a1 = G.multiply(w); //a1 = w*G
				vp._b1 = P.multiply(w); //b1 = w*P
				vp._a2 = G.multiply(vp._r2).add(x.multiply(vp._d2)); //a2 = r2*G + d2*x
				vp._b2 = P.multiply(vp._r2).add(y.subtract(G).multiply(vp._d2)); //b2 = r2*P + (y-G)*d2
				
				BigInteger c = makeChallenge(vp).mod(order);
				
				vp._d1 = c.subtract(vp._d2).mod(order);
				vp._r1 = w.subtract(k.multiply(vp._d1)).mod(order);
				
				assert(c.equals(vp._d1.add(vp._d2).mod(order))); 
				assert(vp._a1.equals(G.multiply(vp._r1).add(x.multiply(vp._d1))));
				assert(vp._b1.equals(P.multiply(vp._r1).add(y.add(G).multiply(vp._d1))));
				assert(vp._a2.equals(G.multiply(vp._r2).add(x.multiply(vp._d2))));
				assert(vp._b2.equals(P.multiply(vp._r2).add(y.subtract(G).multiply(vp._d2))));
				
			}else{
				throw new ProofException("the original message is neither G nor -G");
			}
			
			return vp;
		}catch(NoSuchAlgorithmException e){
			throw new ProofException(e);
		}		
	}
	/**
	 * deserialize the byte[] representation of proof to VoteProof instance
	 * @param ecParam the EC curve's parameter
	 * @param bytesProof the byte[] repr.
	 * @return the VoteProof inst
	 * @throws IOException 
	 */
	public static VoteProof deserialize(ECParameterSpec ecParam, byte[] bytesProof) throws IOException{
		ASN1InputStream is = new ASN1InputStream(bytesProof);
		DERSequence seq = (DERSequence)is.readObject();
		VoteProof vp = new VoteProof();
		
		ECCurve curve = ecParam.getCurve();
		ECPoint a1 = new X9ECPoint(curve, (ASN1OctetString) seq.getObjectAt(0)).getPoint();
		ECPoint a2 = new X9ECPoint(curve, (ASN1OctetString) seq.getObjectAt(1)).getPoint();
		ECPoint b1 = new X9ECPoint(curve, (ASN1OctetString) seq.getObjectAt(2)).getPoint();
		ECPoint b2 = new X9ECPoint(curve, (ASN1OctetString) seq.getObjectAt(3)).getPoint();
		BigInteger d1 = new BigInteger(((ASN1OctetString)seq.getObjectAt(4)).getOctets());
		BigInteger d2 = new BigInteger(((ASN1OctetString)seq.getObjectAt(5)).getOctets());
		BigInteger r1 = new BigInteger(((ASN1OctetString)seq.getObjectAt(6)).getOctets());
		BigInteger r2 = new BigInteger(((ASN1OctetString)seq.getObjectAt(7)).getOctets());
		
		vp._a1 = a1;
		vp._a2 = a2;
		vp._b1 = b1;
		vp._b2 = b2;
		vp._d1 = d1;
		vp._d2 = d2;
		vp._r1 = r1;
		vp._r2 = r2;
		
		return vp;
	}
	
	private static BigInteger makeChallenge(VoteProof vp)
			throws NoSuchAlgorithmException {
		MessageDigest dgst = MessageDigest.getInstance(Utility.DGSTALG);
		dgst.update(vp._a1.getEncoded());
		dgst.update(vp._a2.getEncoded());
		dgst.update(vp._b1.getEncoded());
		dgst.update(vp._b2.getEncoded());
		byte[] bytesC = dgst.digest();
		
		return new BigInteger(bytesC);
	}
	
	private ECPoint _a1, _a2, _b1, _b2;

	private BigInteger _d1, _d2, _r1, _r2;	
	
	private VoteProof(){}
	
	/**
	 * serialize this proof instance to byte[]
	 * @return byte[] representation of proof
	 */
	public byte[] serialize(){		
		return serialToSeq().getDEREncoded();
	}
	
	public DERSequence serialToSeq(){
		ASN1EncodableVector vec = new ASN1EncodableVector();
		vec.add(new X9ECPoint(_a1));
		vec.add(new X9ECPoint(_a2));
		vec.add(new X9ECPoint(_b1));
		vec.add(new X9ECPoint(_b2));
		vec.add(new DEROctetString(_d1.toByteArray()));
		vec.add(new DEROctetString(_d2.toByteArray()));
		vec.add(new DEROctetString(_r1.toByteArray()));
		vec.add(new DEROctetString(_r2.toByteArray()));
		return new DERSequence(vec);
	}
	
	/**
	 * verify this proof against given cipher text 
	 * @param ct the cipher text
	 * @param ecParam the EC curve's parameter
	 * @param P the public key of CipherText
	 * @return whether the proof is valid
	 * @throws NoSuchAlgorithmException 
	 */
	public boolean verifyProof(CipherText ct, ECParameterSpec ecParam, ECPoint P) throws NoSuchAlgorithmException{
		boolean result = false;
		do{
			ECPoint G = ecParam.getG();
			ECPoint x = ct.getX();
			ECPoint y = ct.getY();
			BigInteger order = ecParam.getN();
			BigInteger c = makeChallenge(this).mod(order);

			if( ! c.equals(_d1.add(_d2).mod(order)) ) { _log.error("c!=d1+d2"); break; } //c == d1 + d2
			if( ! _a1.equals(G.multiply(_r1).add(x.multiply(_d1))) ) {_log.error("2nd");break;} //a1 == r1*G + d1*x
			if( ! _b1.equals(P.multiply(_r1).add(y.add(G).multiply(_d1)))) {_log.error("3rd");break;} //b1 == r1*P + d1*(y+G)
			if( ! _a2.equals(G.multiply(_r2).add(x.multiply(_d2)))) {_log.error("4th"); break; }//a2 == r2*G + d2*x
			if( ! _b2.equals(P.multiply(_r2).add(y.subtract(G).multiply(_d2)))) {_log.error("5th"); break;} //b2 == r2*P + (y-G)*d2
			
			result = true;
		}while(false);	
		
		return result;
	}
}
