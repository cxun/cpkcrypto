/*
 * This file is used to extend pkcs11t.h
 * CPK mechanisms, key types are appended to pkcs11t.h
 */

#ifndef _PKCS11CPK_H_
#define _PKCS11CPK_H_ 1

#ifdef __cplusplus
extern "C" {
#endif


#define CKK_CPK							0x90000000
#define CKK_CPK_MATRIX						0x90000001


#define CKA_CPK_DER						0x80000001
#define CKA_CPK_ID						0x80000002
#define CKA_CPK_MATRIX_URI					0x80000003
#define CKA_CPK_MATRIX_COLUMN					0x80000004
#define CKA_CPK_MATRIX_ROW					0x80000005
#define CKA_CPK_EC_NAME						0x80000006
#define CKA_CPK_POINT_COMPRESSED				0x80000007
#define CKA_CPK_DIGEST_MECHANISM				0x80000008
#define CKA_CPK_SIGN_MECHANISM					0x80000009
#define CKA_CPK_SIGNED_TIME					0x8000000a
#define CKA_CPK_SIGNER_ID					0x8000000b
#define CKA_CPK_ENCRYPT_MECHANISM				0x8000000c
#define CKA_CPK_ECIES_PARAMETERS				0x8000000d
#define CKA_DATA_TYPE						0x8000000e



#define CKM_CPK							0x80000002
#define CKM_CPK_ECDSA						0x80000003
#define CKM_CPK_ECDSA_SHA1					0x80000004
#define CKM_CPK_ECIES						0x80000005
#define CKM_CPK_ECIES_STDDH_SHA1KDF_DES3CBC_PAD_MD5HMAC		0x80000016
#define CKM_CPK_ECIES_STDDH_SHA1KDF_DES3CBC_PAD_SHA1HMAC	0x80000006
#define CKM_CPK_ECIES_STDDH_SHA1KDF_AES128CBC_PAD_SHA1HMAC	0x80000007
#define CKM_CPK_ECIES_STDDH_SHA1KDF_AES128CFB_SHA1HMAC		0x80000017
#define CKM_CPK_PKCS7_SIGNED					0x80000008
#define CKM_CPK_PKCS7_ENVELOPE_DES3CBC_PAD			0x80000009
#define CKM_CPK_PKCS7_ENVELOPE_AES128CBC_PAD			0x8000000a
#define CKM_CPK_PKCS7_SIGNED_ENVELOPED_DES3CBC_PAD		0x8000000b
#define CKM_CPK_PKCS7_SIGNED_ENVELOPED_AES128CBC_PAD		0x8000000c
#define CKM_CPK_PKCS7						0x8000000d


typedef CK_ULONG	CK_DATA_TYPE;

#define CKD_CPK_SIGNER_INFO					0x80000001
#define CKD_CPK_RECIP_INFO					0x80000002
#define CKD_CPK_PKCS7						0x80000003

#define CKR_DATA_TYPE_INCONSISTENT				0x80000001

#define CKO_CPK_MESSAGE						


#define CPK_OK 1


#ifdef __cplusplus
}
#endif

#endif