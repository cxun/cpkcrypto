#include <pthread.h>
#include <security/cryptoki.h>
#include "cpkGlobal.h"
#include "cpkObject.h"
#include "cpkOps.h"
#include "cpkSession.h"


CK_RV
C_SignInit(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism,
    CK_OBJECT_HANDLE hKey)
{

	CK_RV		rv;
	cpk_session_t	*session_p;
	cpk_object_t	*key_p;
	int	lock_held = B_FALSE;

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	/* Obtain the session pointer. */
	rv = handle2session(hSession, &session_p);
	if (rv != CKR_OK)
		return (rv);

	if (pMechanism == NULL) {
		rv = CKR_ARGUMENTS_BAD;
		goto clean_exit;
	}

	/* Obtain the object pointer. */
	HANDLE2OBJECT(hKey, key_p, rv);
	if (rv != CKR_OK) {
		goto clean_exit;
	}

	(void) pthread_mutex_lock(&session_p->session_mutex);
	lock_held = B_TRUE;

	/* Check to see if sign operation is already active. */
	if (session_p->sign.flags & CRYPTO_OPERATION_ACTIVE) {
		/* free the memory to avoid memory leak */
		cpk_sign_verify_cleanup(session_p, B_TRUE, B_TRUE);
	}

	/*
	 * This active flag will remain ON until application calls either
	 * C_Sign or C_SignFinal to actually obtain the signature.
	 */
	session_p->sign.flags = CRYPTO_OPERATION_ACTIVE;

	(void) pthread_mutex_unlock(&session_p->session_mutex);
	lock_held = B_FALSE;

	rv = cpk_sign_init(session_p, pMechanism, key_p);

	if (rv != CKR_OK) {
		(void) pthread_mutex_lock(&session_p->session_mutex);
		session_p->sign.flags &= ~CRYPTO_OPERATION_ACTIVE;
		lock_held = B_TRUE;
	}


	OBJ_REFRELE(key_p);
clean_exit:
	SES_REFRELE(session_p, lock_held);
	return (rv);
}


CK_RV
C_Sign(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen,
    CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen)
{

	CK_RV		rv;
	cpk_session_t	*session_p;
	int	lock_held = B_FALSE;

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	/* Obatin the session pointer */
	rv = handle2session(hSession, &session_p);
	if (rv != CKR_OK)
		return (rv);

	if ((pData == NULL) || (pulSignatureLen == NULL)) {
		rv = CKR_ARGUMENTS_BAD;
		goto clean_exit;
	}

	(void) pthread_mutex_lock(&session_p->session_mutex);
	lock_held = B_TRUE;

	/* Application must call C_SignInit before calling C_Sign. */
	if (!(session_p->sign.flags & CRYPTO_OPERATION_ACTIVE)) {
		SES_REFRELE(session_p, lock_held);
		return (CKR_OPERATION_NOT_INITIALIZED);
	}

	/*
	 * C_Sign must be called without intervening C_SignUpdate
	 * calls.
	 */
	if (session_p->sign.flags & CRYPTO_OPERATION_UPDATE) {
		/*
		 * C_Sign can not be used to terminate a multi-part
		 * operation, so we'll leave the active sign operation
		 * flag on and let the application continue with the
		 * sign update operation.
		 */
		SES_REFRELE(session_p, lock_held);
		return (CKR_FUNCTION_FAILED);
	}

	(void) pthread_mutex_unlock(&session_p->session_mutex);
	lock_held = B_FALSE;

	rv = cpk_sign(session_p, pData, ulDataLen, pSignature,
	    pulSignatureLen);

	if ((rv == CKR_BUFFER_TOO_SMALL) ||
	    (pSignature == NULL && rv == CKR_OK)) {
		/*
		 * We will not terminate the active sign operation flag,
		 * when the application-supplied buffer is too small, or
		 * the application asks for the length of buffer to hold
		 * the signature.
		 */
		SES_REFRELE(session_p, lock_held);
		return (rv);
	}

clean_exit:
	/* Clear contexts, free key, and release session counter */
	cpk_sign_verify_cleanup(session_p, B_TRUE, B_FALSE);
	return (rv);
}


CK_RV
C_SignUpdate(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pPart,
    CK_ULONG ulPartLen)
{

	CK_RV		rv;
	cpk_session_t	*session_p;
	int	lock_held = B_FALSE;

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	/* Obtain the session pointer */
	rv = handle2session(hSession, &session_p);
	if (rv != CKR_OK)
		return (rv);

	if (ulPartLen == 0) {
		SES_REFRELE(session_p, lock_held);
		return (CKR_OK);
	}

	if (pPart == NULL) {
		rv = CKR_ARGUMENTS_BAD;
		goto clean_exit;
	}

	(void) pthread_mutex_lock(&session_p->session_mutex);
	lock_held = B_TRUE;

	/*
	 * Application must call C_SignInit before calling
	 * C_SignUpdate.
	 */
	if (!(session_p->sign.flags & CRYPTO_OPERATION_ACTIVE)) {
		SES_REFRELE(session_p, lock_held);
		return (CKR_OPERATION_NOT_INITIALIZED);
	}

	session_p->sign.flags |= CRYPTO_OPERATION_UPDATE;

	(void) pthread_mutex_unlock(&session_p->session_mutex);
	lock_held = B_FALSE;

	rv = cpk_sign_update(session_p, pPart, ulPartLen);

	if (rv == CKR_OK) {
		SES_REFRELE(session_p, lock_held);
		return (rv);
	}

clean_exit:
	/* After error, clear context, free key, & release session counter */
	cpk_sign_verify_cleanup(session_p, B_TRUE, B_FALSE);

	return (rv);

}


CK_RV
C_SignFinal(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pSignature,
    CK_ULONG_PTR pulSignatureLen)
{

	CK_RV		rv;
	cpk_session_t	*session_p;
	int	lock_held = B_FALSE;

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	/* Obtain the session pointer */
	rv = handle2session(hSession, &session_p);
	if (rv != CKR_OK)
		return (rv);

	if (pulSignatureLen == NULL) {
		rv = CKR_ARGUMENTS_BAD;
		goto clean_exit;
	}

	(void) pthread_mutex_lock(&session_p->session_mutex);
	lock_held = B_TRUE;

	/*
	 * Application must call C_SignInit before calling
	 * C_SignFinal.
	 */
	if (!(session_p->sign.flags & CRYPTO_OPERATION_ACTIVE)) {
		SES_REFRELE(session_p, lock_held);
		return (CKR_OPERATION_NOT_INITIALIZED);
	}

	(void) pthread_mutex_unlock(&session_p->session_mutex);
	lock_held = B_FALSE;

	rv = cpk_sign_final(session_p, pSignature, pulSignatureLen);

	if ((rv == CKR_BUFFER_TOO_SMALL) ||
	    (pSignature == NULL && rv == CKR_OK)) {
		/*
		 * We will not terminate the active sign operation flag,
		 * when the application-supplied buffer is too small, or
		 * the application asks for the length of buffer to hold
		 * the signature.
		 */
		SES_REFRELE(session_p, lock_held);
		return (rv);
	}

clean_exit:
	/* Clear contexts, free key, and release session counter */
	cpk_sign_verify_cleanup(session_p, B_TRUE, B_FALSE);

	return (rv);
}


CK_RV
C_SignRecoverInit(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism,
    CK_OBJECT_HANDLE hKey)
{

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	return (CKR_FUNCTION_NOT_SUPPORTED);

}


CK_RV
C_SignRecover(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData,
    CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen)
{

	if (!cpktoken_initialized)
		return (CKR_CRYPTOKI_NOT_INITIALIZED);

	return (CKR_FUNCTION_NOT_SUPPORTED);

}
