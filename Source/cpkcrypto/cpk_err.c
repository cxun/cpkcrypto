/* Copyright (c) 2007  "Guan Zhi" <guanzhi1980@gmail.com> */

#include <openssl/err.h>
#include "cpk.h"

/* BEGIN ERROR CODES */
#ifndef OPENSSL_NO_ERR

#define ERR_FUNC(func) ERR_PACK(ERR_LIB_CPK,func,0)
#define ERR_REASON(reason) ERR_PACK(ERR_LIB_CPK,0,reason)

static ERR_STRING_DATA CPK_str_functs[] = 
{
	{ERR_FUNC(CPK_F_CPK_SECRET_MATRIX_CREATE),	"CPK_SECRET_MATRIX_create"},
	{ERR_FUNC(CPK_F_CPK_PUBLIC_MATRIX_CREATE),	"CPK_PUBLIC_MATRIX_create"},
	{ERR_FUNC(CPK_F_CPK_IDENTITY_INFO_SET),		"CPK_IDENTITY_INFO_set"},
	{ERR_FUNC(CPK_F_CPK_IDENTITY_INFO_GET_KEY),	"CPK_IDENTITY_INFO_get_key"},
	{ERR_FUNC(CPK_F_CPK_KEY_INFO_CREATE),		"CPK_KEY_INFO_create"},
	{ERR_FUNC(CPK_F_CPK_KEY_INFO_GET_KEY),		"CPK_KEY_INFO_get_key"},
	{ERR_FUNC(CPK_F_CPK_PUBLIC_MATRIX_GET_KEY),	"CPK_PUBLIC_MATRIX_get_key"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_SET),		"CPK_SIGNER_INFO_set"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_ADD_ATTR),	"CPK_SIGNER_INFO_add_attr"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_ADD_SIGNED_ATTR),"CPK_SIGNER_INFO_add_signed_attr"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_ADD_SIGNED_TIME),"CPK_SIGNER_INFO_add_signed_time"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_ADD_SIGNED_DIGEST),"CPK_SIGNER_INFO_add_signed_digest"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_DO_SIGN),	"CPK_SIGNER_INFO_do_sign"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_GET_ATTR),	"CPK_SIGNER_INFO_get_attR"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_GET_SIGNED_ATTR),"CPK_SIGNER_INFO_get_signed_attr"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_GET_SIGNED_TIME),"CPK_SIGNER_INFO_get_signed_time"},
	{ERR_FUNC(CPK_F_CPK_SIGNER_INFO_DO_VERIFY),	"PK_SIGNER_INFO_do_verify"},
	{ERR_FUNC(CPK_F_CPK_RECIP_INFO_SET),		"CPK_RECIP_INFO_set"},
	{ERR_FUNC(CPK_F_CPK_RECIP_INFO_DO_ENCRYPT),	"CPK_RECIP_INFO_do_encrypt"},
	{ERR_FUNC(CPK_F_CPK_RECIP_INFO_DO_DECRYPT),	"CPK_RECIP_INFO_do_decrypt"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_SET_TYPE),		"CPK_PKCS7_set_type"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_SET_CONTENT),		"CPK_PKCS7_set_content"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_CONTENT_NEW),		"CPK_PKCS7_content_new"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_ADD_SIGNER),		"CPK_PKCS7_add_signer"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_ADD_RECIPIENT),	"CPK_PKCS7_add_recipient"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_SET_CIPHER),		"CPK_PKCS7_set_cipher"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_DATAINIT),		"CPK_PKCS7_dataInit"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_DATADECODE),		"CPK_PKCS7_dataDecode"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_DATAUPDATE),		"CPK_PKCS7_dataUpdate"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_DATAFINAL),		"CPK_PKCS7_dataFinal"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_DATAVERIFY),		"CPK_PKCS7_dataVerify"},
	{ERR_FUNC(CPK_F_CPK_PKCS7_FIND_DIGEST),		"CPK_PKCS7_find_digest"},
	{ERR_FUNC(CPK_F_BIO_ADD_DIGEST),		"bio_add_digest"},
	{ERR_FUNC(CPK_F_BIO_ADD_CIPHER),		"bio_add_cipher"},
	{0, NULL}
};

static ERR_STRING_DATA CPK_str_reasons[] = 
{
	{ERR_REASON(CPK_R_BAD_ARGUMENT),		"CPK_R_BAD_ARGUMENT"},
	{ERR_REASON(CPK_R_UNKNOWN_DIGEST_TYPE),		"CPK_R_UNKNOWN_DIGEST_TYPE"},
	{ERR_REASON(CPK_R_UNKNOWN_CIPHER_TYPE),		"CPK_R_UNKNOWN_CIPHER_TYPE"},
	{ERR_REASON(CPK_R_UNKNOWN_MAP_TYPE),		"CPK_R_UNKNOWN_MAP_TYPE"},
	{ERR_REASON(CPK_R_UNKNOWN_CURVE),		"CPK_R_UNKNOWN_CURVE"},
	{ERR_REASON(CPK_R_STACK_ERROR),			"CPK_R_STACK_ERROR"},
	{ERR_REASON(CPK_R_DERIVE_KEY_FAILED),		"CPK_R_DERIVE_KEY_FAILED"},
	{ERR_REASON(CPK_R_ECIES_ENCRYPT_FAILED),	"CPK_R_ECIES_ENCRYPT_FAILED"},
	{ERR_REASON(CPK_R_ECIES_DECRYPT_FAILED),	"CPK_R_ECIES_DECRYPT_FAILED"},
	{ERR_REASON(CPK_R_DER_DECODE_FAILED),		"CPK_R_DER_DECODE_FAILED"},
	{ERR_REASON(CPK_R_UNSUPPORTED_PKCS7_CONTENT_TYPE),"CPK_R_UNSUPPORTED_PKCS7_CONTENT_TYPE"},
	{ERR_REASON(CPK_R_SET_SIGNER),			"CPK_R_SET_SIGNER"},
	{ERR_REASON(CPK_R_SET_RECIP_INFO),		"CPK_R_SET_RECIP_INFO"},
	{ERR_REASON(CPK_R_UNABLE_TO_FIND_MESSAGE_DIGEST),"CPK_R_UNABLE_TO_FIND_MESSAGE_DIGEST"},
	{ERR_REASON(CPK_R_BAD_DATA),			"CPK_R_BAD_DATA"},
	{ERR_REASON(CPK_R_MAP_FAILED),			"CPK_R_MAP_FAILED"},
	{ERR_REASON(CPK_R_ADD_SIGNING_TIME),		"CPK_R_ADD_SIGNING_TIME"},
	{ERR_REASON(CPK_R_VERIFY_FAILED),		"CPK_R_VERIFY_FAILED"},
	{ERR_REASON(CPK_R_UNKNOWN_ECDH_TYPE),		"CPK_R_UNKNOWN_ECDH_TYPE"},
	{ERR_REASON(CPK_R_DIGEST_FAILED),		"CPK_R_DIGEST_FAILED"},
	{ERR_REASON(CPK_R_WITHOUT_DECRYPT_KEY),		"CPK_R_WITHOUT_DECRYPT_KEY"},
	{ERR_REASON(CPK_R_UNKNOWN_PKCS7_TYPE),		"CPK_R_UNKNOWN_PKCS7_TYPE"},
	{0, NULL}
};

#endif

void ERR_load_CPK_strings(void)
{
#ifndef OPENSSL_NO_ERR

	if (ERR_func_error_string(CPK_str_functs[0].error) == NULL) {
		ERR_load_strings(0, CPK_str_functs);
		ERR_load_strings(0, CPK_str_reasons);
	}

#endif
}
