/********************************************************************************/
/*										*/
/*			     TSS Library Dependent Crypto Support		*/
/*			     Written by Ken Goldman				*/
/*		       IBM Thomas J. Watson Research Center			*/
/*	      $Id: tsscrypto.h 878 2016-12-19 19:52:56Z kgoldman $		*/
/*										*/
/* (c) Copyright IBM Corporation 2015.						*/
/*										*/
/* All rights reserved.								*/
/* 										*/
/* Redistribution and use in source and binary forms, with or without		*/
/* modification, are permitted provided that the following conditions are	*/
/* met:										*/
/* 										*/
/* Redistributions of source code must retain the above copyright notice,	*/
/* this list of conditions and the following disclaimer.			*/
/* 										*/
/* Redistributions in binary form must reproduce the above copyright		*/
/* notice, this list of conditions and the following disclaimer in the		*/
/* documentation and/or other materials provided with the distribution.		*/
/* 										*/
/* Neither the names of the IBM Corporation nor the names of its		*/
/* contributors may be used to endorse or promote products derived from		*/
/* this software without specific prior written permission.			*/
/* 										*/
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS		*/
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT		*/
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	*/
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT		*/
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,	*/
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT		*/
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,	*/
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY	*/
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT		*/
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE	*/
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.		*/
/********************************************************************************/

/* This is a semi-public header. The API should be stable, but is less guaranteed.

   It is useful for applications that need some basic crypto functions.
*/

#ifndef TSSCRYPTO_H
#define TSSCRYPTO_H

#include <stdint.h>
#include <stdio.h>

#include <openssl/rsa.h>

#ifndef TPM_TSS
#define TPM_TSS
#endif

#include <tss2/tss.h>

#ifdef __cplusplus
extern "C" {
#endif

    LIB_EXPORT
    TPM_RC TSS_Crypto_Init(void);

    LIB_EXPORT
    TPM_RC TSS_Hash_Generate_valist(TPMT_HA *digest,
				    va_list ap);
    LIB_EXPORT
    TPM_RC TSS_HMAC_Generate_valist(TPMT_HA *digest,
				    const TPM2B_KEY *hmacKey,
				    va_list ap);
    LIB_EXPORT void TSS_XOR(unsigned char *out,
			    const unsigned char *in1,
			    const unsigned char *in2,
			    size_t length);
    LIB_EXPORT
    TPM_RC TSS_RandBytes(unsigned char *buffer, uint32_t size);

    LIB_EXPORT
    TPM_RC TSS_RSA_padding_add_PKCS1_OAEP(unsigned char *em, uint32_t emLen,
					  const unsigned char *from, uint32_t fLen,
					  const unsigned char *p,
					  int plen,
					  TPMI_ALG_HASH halg);	
    LIB_EXPORT
    TPM_RC TSS_RSAPublicEncrypt(unsigned char* encrypt_data,
				size_t encrypt_data_size,
				const unsigned char *decrypt_data,
				size_t decrypt_data_size,
				unsigned char *narr,
				uint32_t nbytes,
				unsigned char *earr,
				uint32_t ebytes,
				unsigned char *p,
				int pl,
				TPMI_ALG_HASH halg);
    LIB_EXPORT
    TPM_RC TSS_RSAGeneratePublicToken(RSA **rsa_pub_key,		/* freed by caller */
				      const unsigned char *narr,   	/* public modulus */
				      uint32_t nbytes,
				      const unsigned char *earr,   	/* public exponent */
				      uint32_t ebytes);

    TPM_RC TSS_AES_GetEncKeySize(size_t *tssSessionEncKeySize);
    TPM_RC TSS_AES_GetDecKeySize(size_t *tssSessionDecKeySize);
    TPM_RC TSS_AES_KeyGenerate(void *tssSessionEncKey,
			       void *tssSessionDecKey);
    TPM_RC TSS_AES_Encrypt(void *tssSessionEncKey,
			   unsigned char **encrypt_data,
			   uint32_t *encrypt_length,
			   const unsigned char *decrypt_data,
			   uint32_t decrypt_length);
    TPM_RC TSS_AES_Decrypt(void *tssSessionDecKey,
			   unsigned char **decrypt_data,
			   uint32_t *decrypt_length,
			   const unsigned char *encrypt_data,
			   uint32_t encrypt_length);
    TPM_RC TSS_AES_EncryptCFB(uint8_t	*dOut,
			      uint32_t	keySizeInBits,
			      uint8_t 	*key,
			      uint8_t 	*iv,
			      uint32_t	dInSize,
			      uint8_t 	*dIn);
    TPM_RC TSS_AES_DecryptCFB(uint8_t *dOut,
			      uint32_t keySizeInBits,
			      uint8_t *key,
			      uint8_t *iv,
			      uint32_t dInSize,
			      uint8_t *dIn);

#ifdef __cplusplus
}
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/tss/ibmtss/public/tss2/tsscrypto.h $ $Rev: 820787 $")
#endif
