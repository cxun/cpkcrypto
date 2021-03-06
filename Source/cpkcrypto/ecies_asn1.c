/* Copyright (c) 2007  "Guan Zhi" <guanzhi1980@gmail.com> */

#include <openssl/err.h>
#include <openssl/asn1t.h>
#include "ecies.h"


ASN1_SEQUENCE(ECIES_CIPHERTEXT) = {
	ASN1_SIMPLE(ECIES_CIPHERTEXT, algor, X509_ALGOR),
	ASN1_SIMPLE(ECIES_CIPHERTEXT, encdata, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(ECIES_CIPHERTEXT)
IMPLEMENT_ASN1_FUNCTIONS(ECIES_CIPHERTEXT)
IMPLEMENT_ASN1_DUP_FUNCTION(ECIES_CIPHERTEXT)

ASN1_SEQUENCE(ECIES_MACTAG) = {
	ASN1_SIMPLE(ECIES_MACTAG, algor, X509_ALGOR),
	ASN1_SIMPLE(ECIES_MACTAG, macdata, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(ECIES_MACTAG)
IMPLEMENT_ASN1_FUNCTIONS(ECIES_MACTAG)
IMPLEMENT_ASN1_DUP_FUNCTION(ECIES_MACTAG)

ASN1_SEQUENCE(ECIES_CIPHERTEXT_VALUE) = {
	ASN1_SIMPLE(ECIES_CIPHERTEXT_VALUE, ephem_point, ASN1_OCTET_STRING),
	ASN1_SIMPLE(ECIES_CIPHERTEXT_VALUE, ciphertext, ASN1_OCTET_STRING),
	ASN1_SIMPLE(ECIES_CIPHERTEXT_VALUE, mactag, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(ECIES_CIPHERTEXT_VALUE)
IMPLEMENT_ASN1_FUNCTIONS(ECIES_CIPHERTEXT_VALUE)
IMPLEMENT_ASN1_DUP_FUNCTION(ECIES_CIPHERTEXT_VALUE)
