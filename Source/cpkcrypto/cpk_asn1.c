/* Copyright (c) 2007  "Guan Zhi" <guanzhi1980@gmail.com> */

#include <openssl/asn1t.h>
#include "cpk.h"


ASN1_SEQUENCE(CPK_SECRET_MATRIX) = {
	ASN1_SIMPLE(CPK_SECRET_MATRIX, version, LONG),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, matrix_uri, ASN1_UTF8STRING),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, curve_obj, ASN1_OBJECT),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, map_algor, X509_ALGOR),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, column_size, LONG),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, row_size, LONG),
	ASN1_SIMPLE(CPK_SECRET_MATRIX, bignums, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(CPK_SECRET_MATRIX)
IMPLEMENT_ASN1_FUNCTIONS(CPK_SECRET_MATRIX)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_SECRET_MATRIX)


ASN1_SEQUENCE(CPK_PUBLIC_MATRIX) = {
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, version, LONG),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, matrix_uri, ASN1_UTF8STRING),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, curve_obj, ASN1_OBJECT),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, map_algor, X509_ALGOR),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, column_size, LONG),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, row_size, LONG),
	ASN1_SIMPLE(CPK_PUBLIC_MATRIX, points, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(CPK_PUBLIC_MATRIX)
IMPLEMENT_ASN1_FUNCTIONS(CPK_PUBLIC_MATRIX)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_PUBLIC_MATRIX)


ASN1_SEQUENCE(CPK_IDENTITY_INFO) = {
	ASN1_SIMPLE(CPK_IDENTITY_INFO, matrix_uri, ASN1_UTF8STRING),
	ASN1_SIMPLE(CPK_IDENTITY_INFO, id_schema, ASN1_OBJECT),
	ASN1_SIMPLE(CPK_IDENTITY_INFO, id_data, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(CPK_IDENTITY_INFO)
IMPLEMENT_ASN1_FUNCTIONS(CPK_IDENTITY_INFO)


ASN1_SEQUENCE(CPK_KEY_INFO) = {
	ASN1_SIMPLE(CPK_KEY_INFO, version, LONG),
	ASN1_SIMPLE(CPK_KEY_INFO, identity, CPK_IDENTITY_INFO),
	ASN1_SIMPLE(CPK_KEY_INFO, key_data, ASN1_OCTET_STRING),
	ASN1_SIMPLE(CPK_KEY_INFO, curve_obj, ASN1_OBJECT)
} ASN1_SEQUENCE_END(CPK_KEY_INFO)
IMPLEMENT_ASN1_FUNCTIONS(CPK_KEY_INFO)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_KEY_INFO)


/* This is the ANY DEFINED BY table for the top level PKCS#7 structure */
ASN1_ADB_TEMPLATE(cpkp7default) = ASN1_EXP_OPT(CPK_PKCS7, d.other, ASN1_ANY, 0);

ASN1_ADB(CPK_PKCS7) = {
	ADB_ENTRY(NID_pkcs7_data, ASN1_NDEF_EXP_OPT(CPK_PKCS7, d.data, ASN1_OCTET_STRING_NDEF, 0)),
	ADB_ENTRY(NID_pkcs7_signed, ASN1_NDEF_EXP_OPT(CPK_PKCS7, d.sign, CPK_SIGNED, 0)),
	ADB_ENTRY(NID_pkcs7_enveloped, ASN1_NDEF_EXP_OPT(CPK_PKCS7, d.enveloped, CPK_ENVELOPE, 0)),
	ADB_ENTRY(NID_pkcs7_signedAndEnveloped, 
		ASN1_NDEF_EXP_OPT(CPK_PKCS7, d.signed_and_enveloped, CPK_SIGN_ENVELOPE, 0)),
} ASN1_ADB_END(CPK_PKCS7, 0, type, 0, &cpkp7default_tt, NULL);


ASN1_NDEF_SEQUENCE(CPK_PKCS7) = {
	ASN1_SIMPLE(CPK_PKCS7, type, ASN1_OBJECT),
	ASN1_ADB_OBJECT(CPK_PKCS7)
}ASN1_NDEF_SEQUENCE_END(CPK_PKCS7)
IMPLEMENT_ASN1_FUNCTIONS(CPK_PKCS7)
IMPLEMENT_ASN1_NDEF_FUNCTION(CPK_PKCS7)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_PKCS7)


ASN1_NDEF_SEQUENCE(CPK_SIGNED) = {
	ASN1_SIMPLE(CPK_SIGNED, version, LONG),
	ASN1_SET_OF(CPK_SIGNED, digest_algors, X509_ALGOR),
	ASN1_SIMPLE(CPK_SIGNED, contents, CPK_PKCS7),
	ASN1_IMP_SEQUENCE_OF_OPT(CPK_SIGNED, cert, X509, 0),
	ASN1_IMP_SET_OF_OPT(CPK_SIGNED, crl, X509_CRL, 1),
	ASN1_SET_OF(CPK_SIGNED, signer_infos, CPK_SIGNER_INFO)
} ASN1_NDEF_SEQUENCE_END(CPK_SIGNED)
IMPLEMENT_ASN1_FUNCTIONS(CPK_SIGNED)


ASN1_SEQUENCE(CPK_SIGNER_INFO) = {
	ASN1_SIMPLE(CPK_SIGNER_INFO, version, LONG),
	ASN1_SIMPLE(CPK_SIGNER_INFO, signer, CPK_IDENTITY_INFO),
	ASN1_SIMPLE(CPK_SIGNER_INFO, digest_algor, X509_ALGOR),
	ASN1_IMP_SEQUENCE_OF_OPT(CPK_SIGNER_INFO, auth_attr, X509_ATTRIBUTE, 0),
	ASN1_SIMPLE(CPK_SIGNER_INFO, sign_algor, X509_ALGOR),
	ASN1_SIMPLE(CPK_SIGNER_INFO, signature, ASN1_OCTET_STRING),
	ASN1_IMP_SET_OF_OPT(CPK_SIGNER_INFO, unauth_attr, X509_ATTRIBUTE, 1)
} ASN1_SEQUENCE_END(CPK_SIGNER_INFO)
IMPLEMENT_ASN1_FUNCTIONS(CPK_SIGNER_INFO)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_SIGNER_INFO)


ASN1_NDEF_SEQUENCE(CPK_ENVELOPE) = {
	ASN1_SIMPLE(CPK_ENVELOPE, version, LONG),
	ASN1_SET_OF(CPK_ENVELOPE, recip_infos, CPK_RECIP_INFO),
	ASN1_SIMPLE(CPK_ENVELOPE, enc_data, CPK_ENC_CONTENT)
} ASN1_NDEF_SEQUENCE_END(CPK_ENVELOPE)
IMPLEMENT_ASN1_FUNCTIONS(CPK_ENVELOPE)


ASN1_SEQUENCE(CPK_RECIP_INFO) = {
	ASN1_SIMPLE(CPK_RECIP_INFO, version, LONG),
	ASN1_SIMPLE(CPK_RECIP_INFO, recipient, CPK_IDENTITY_INFO),
	ASN1_SIMPLE(CPK_RECIP_INFO, enc_algor, X509_ALGOR),
	ASN1_SIMPLE(CPK_RECIP_INFO, enc_data, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(CPK_RECIP_INFO)
IMPLEMENT_ASN1_FUNCTIONS(CPK_RECIP_INFO)
IMPLEMENT_ASN1_DUP_FUNCTION(CPK_RECIP_INFO)


ASN1_NDEF_SEQUENCE(CPK_ENC_CONTENT) = {
	ASN1_SIMPLE(CPK_ENC_CONTENT, content_type, ASN1_OBJECT),
	ASN1_SIMPLE(CPK_ENC_CONTENT, enc_algor, X509_ALGOR),
	ASN1_IMP_OPT(CPK_ENC_CONTENT, enc_data, ASN1_OCTET_STRING, 0)
} ASN1_NDEF_SEQUENCE_END(CPK_ENC_CONTENT)
IMPLEMENT_ASN1_FUNCTIONS(CPK_ENC_CONTENT)


ASN1_NDEF_SEQUENCE(CPK_SIGN_ENVELOPE) = {
	ASN1_SIMPLE(CPK_SIGN_ENVELOPE, version, LONG),
	ASN1_SET_OF(CPK_SIGN_ENVELOPE, recip_infos, CPK_RECIP_INFO),
	ASN1_SET_OF(CPK_SIGN_ENVELOPE, digest_algors, X509_ALGOR),
	ASN1_SIMPLE(CPK_SIGN_ENVELOPE, enc_data, CPK_ENC_CONTENT),
	ASN1_IMP_SET_OF_OPT(CPK_SIGN_ENVELOPE, cert, X509, 0),
	ASN1_IMP_SET_OF_OPT(CPK_SIGN_ENVELOPE, crl, X509_CRL, 1),
	ASN1_SET_OF(CPK_SIGN_ENVELOPE, signer_infos, CPK_SIGNER_INFO)
} ASN1_NDEF_SEQUENCE_END(CPK_SIGN_ENVELOPE)
IMPLEMENT_ASN1_FUNCTIONS(CPK_SIGN_ENVELOPE)



/* Specials for authenticated attributes */

/* When signing attributes we want to reorder them to match the sorted
 * encoding.
 */
ASN1_ITEM_TEMPLATE(CPK_PKCS7_ATTR_SIGN) = 
	ASN1_EX_TEMPLATE_TYPE(ASN1_TFLG_SET_ORDER, 0, PKCS7_ATTRIBUTES, X509_ATTRIBUTE)
ASN1_ITEM_TEMPLATE_END(CPK_PKCS7_ATTR_SIGN)

/* When verifying attributes we need to use the received order. So 
 * we use SEQUENCE OF and tag it to SET OF
 */
ASN1_ITEM_TEMPLATE(CPK_PKCS7_ATTR_VERIFY) = 
	ASN1_EX_TEMPLATE_TYPE(ASN1_TFLG_SEQUENCE_OF | ASN1_TFLG_IMPTAG | ASN1_TFLG_UNIVERSAL,
				V_ASN1_SET, PKCS7_ATTRIBUTES, X509_ATTRIBUTE)
ASN1_ITEM_TEMPLATE_END(CPK_PKCS7_ATTR_VERIFY)


#define IMPLEMENT_ASN1_IO_FUNCTIONS(TYPE) \
	IMPLEMENT_ASN1_FP_FUNCTIONS(TYPE) \
	IMPLEMENT_ASN1_BIO_FUNCTIONS(TYPE)\
	IMPLEMENT_ASN1_FILE_FUNCTIONS(TYPE)

#define IMPLEMENT_ASN1_FP_FUNCTIONS(TYPE)			\
	TYPE *d2i_##TYPE##_fp(FILE *fp, TYPE **pp)		\
	{ return ASN1_item_d2i_fp(ASN1_ITEM_rptr(TYPE),fp,pp);}	\
	int i2d_##TYPE##_fp(FILE *fp, TYPE *p)			\
	{ return ASN1_item_i2d_fp(ASN1_ITEM_rptr(TYPE),fp,p); }
								
#define IMPLEMENT_ASN1_BIO_FUNCTIONS(TYPE)			\
	TYPE *d2i_##TYPE##_bio(BIO *bp, TYPE **pp) 		\
	{ return ASN1_item_d2i_bio(ASN1_ITEM_rptr(TYPE),bp,pp);}\
	int i2d_##TYPE##_bio(BIO *bp, TYPE *p)			\
	{ return ASN1_item_i2d_bio(ASN1_ITEM_rptr(TYPE),bp,p); }

#define IMPLEMENT_ASN1_FILE_FUNCTIONS(TYPE)			\
	TYPE *d2i_##TYPE##_file(const char *file, TYPE **pp) {	\
	TYPE *r;FILE *fp= fopen(file,"rb"); if(!fp) return NULL;\
	r=d2i_##TYPE##_fp(fp, pp); fclose(fp); return r; }	\
	int i2d_##TYPE##_file(const char *file, TYPE *p) {	\
	FILE *fp = fopen(file,"wb"); if (!fp) return 0;		\
	if (!i2d_##TYPE##_fp(fp, p)) { fclose(fp); return 0; }	\
	fclose(fp); return 1; }



IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_SECRET_MATRIX)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_PUBLIC_MATRIX)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_IDENTITY_INFO)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_KEY_INFO)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_SIGNER_INFO)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_RECIP_INFO)
IMPLEMENT_ASN1_IO_FUNCTIONS(CPK_PKCS7)
