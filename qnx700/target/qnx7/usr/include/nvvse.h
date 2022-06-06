/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _NVVSE_H
#define _NVVSE_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>

#define NVVSE_RESMGR_NAME "devc-nvvse"
#define NVVSE_RESMGR_PATH "/dev/nvvse"
#define NVVSE_SHA_DEVICE_NAME  "/dev/nvvse/sha"
#define NVVSE_PKA1_DEVICE_NAME "/dev/nvvse/pka1"
#define NVVSE_AES0_DEVICE_NAME "/dev/nvvse/aes0"
#define NVVSE_AES1_DEVICE_NAME "/dev/nvvse/aes1"
#define NVVSE_RNG1_DEVICE_NAME "/dev/nvvse/rng1"

#define NVVSE_MAX_RANDOM_NUMBER_LEN_SUPPORTED 512

#define NVVSE_MAX_DATA_KEY_LEN_SUPPORTED    512

#define NVVSE_AES_LINEAR_CTR_LEN 16

/**
* \file
* \brief <b>NVIDIA Security Engine Access</b>
*/

/**
 * @defgroup nvvse_group Secure Engine Driver (nvvse) APIs
 * Accesses the Security Engine.
 * @ingroup qnx_lib_group
 * @{
 */
typedef void* NvVseHandle;

/**
* \brief Defines SE engines.
*/
typedef enum {
    /** Specifies support for AES Encryption/Decryption and AES CMAC. */
    NVVSE_AES0 = 0,
    /** Specifies support for AES Encryption/Decryption and AES CMAC. */
    NVVSE_AES1,
    /** Specifies support for RSA operation up to key size 2048 bits. */
    NVVSE_RSA,
    /** Specifies support for SHA256, SHA384 and SHA512 modes. */
    NVVSE_SHA,
    /** Specifies support for random number generation using DRNG fed by
     *  TRNG Seed. */
    NVVSE_RNG1,
    /** Specifies support for RSASSAPSS signature scheme up to key size 4096 bits. */
    NVVSE_PKA1,
    NVVSE_MAX_ENGINE_NUM,
} NvVseEngineType;

/**
* \brief Defines the error codes.
*/
typedef enum {
    NVVSE_STATUS_OK = 0u,
    NVVSE_STATUS_FAIL = 0x80000000u,
    NVVSE_STATUS_NOT_SUPPORTED,
    NVVSE_STATUS_OUT_OF_MEMORY,
    NVVSE_STATUS_INVALID_STATE,
    NVVSE_STATUS_INVALID_PARAMETER
} NvVseStatus;

/**
* \brief Defines SHA Types.
*/
typedef enum {
    NVVSE_SHA_TYPE_SHA256 = 0u,
    NVVSE_SHA_TYPE_SHA384,
    NVVSE_SHA_TYPE_SHA512
} NvVseSHAType;

/**
* \brief Defines RSA signature algorithms.
*
* The recommended RSA signature algorithm is \c RSASSAPSS with
* a modulus length greater than 3000 bits.
*
* BSI discourages use of the \c RSASSAPKCS1_V1_5 algorithm.
*
*/
typedef enum {
    NVVSE_RSASSA_PSS_SHA256 = 0u,
    NVVSE_RSASSA_PSS_SHA384,
    NVVSE_RSASSA_PSS_SHA512,
    NVVSE_RSASSA_PKCS1_V1_5_SHA256,
    NVVSE_RSASSA_PKCS1_V1_5_SHA384,
    NVVSE_RSASSA_PKCS1_V1_5_SHA512
} NvVseRSASigAlgo;

/**
* \brief Defines RSA encryption algorithms.
*/
typedef enum {
    NVVSE_RSAES_OAEP_SHA256 = 0u,
    NVVSE_RSAES_OAEP_SHA384,
    NVVSE_RSAES_OAEP_SHA512
} NvVseRSAEncryptAlgo;

/**
* \brief Defines AES modes.
*/
typedef enum {
    NVVSE_AES_MODE_CBC = 0u,
    NVVSE_AES_MODE_ECB,
    NVVSE_AES_MODE_CTR,
} NvVseAESMode;

/**
* \brief Defines IV selection types.
*/
typedef enum {
    NVVSE_IVSEL_ORIGINAL_IV = 0u,
    NVVSE_IVSEL_UPDATED_IV,
    NVVSE_IVSEL_REG
} NvVseIVSel;

/**
* Holds RSA authentication parameters.
*/
typedef struct {
    /** Holds a pointer to digest of message buffer. */
    uint8_t    *pMsgDigest;
    /** Holds the length of the message digest. */
    uint32_t   uMsgDigestLength;
    /** Holds a pointer to the signature of the message buffer. */
    uint8_t    *pMsgSignature;
    /** Holds Length of the message signature. */
    uint32_t   uMsgSigLength;
    /** Holds Length of the key modulus. */
    uint32_t   uModulusKeyLength;
    /** Holds KeySlot where the key is stored. */
    uint8_t    uKeySlot;
    /** Holds RSA Signature algorithm to be used for authentication. */
    NvVseRSASigAlgo eRSASigAlgo;
    /** Holds authentication results, which the driver updates.
      * Result values are:
      * - '0' indicates authentication success.
      * - Non-zero value indicates authentication failure. */
    uint8_t    bResult;
} NvVseRSASSAVerifyParams;

/**
* Holds PKA1 RSA encrypt/Decrypt Parameters.
*/
typedef struct {
    /** Holds a boolean that specifies whether to encrypt buffer */
    uint8_t bEncrypt;
    /** Holds a pointer to the input buffer to be encrypted/decrypted. */
    uint8_t *pSrcBuffer;
    /** Holds the length of the source buffer */
    uint32_t uSrcBufferLen;
    /** Holds a pointer to the encrypted/decrypted buffer */
    uint8_t *pDestBuffer;
    /** Holds the length of encrypted/decrypted buffer */
    uint32_t uDestBufferLen;
    /** Holds a pointer to modulus key data */
    uint8_t *pModKey;
    /** Holds the length of modulus key data */
    uint32_t uModKeyLen;
    /** Holds a pointer to exponent key data */
    uint8_t *pExpKey;
    /** Holds the length of exponent key data */
    uint32_t uExpKeyLen;
    /** Holds keyslot where the key is stored */
    uint8_t uKeySlot;
    /** Holds RSA encryption algorithm */
    NvVseRSAEncryptAlgo eRSAEncryptAlgo;
    /* Set Key(0: key present in keyslot,
     *         1: write key data to keyslot during encryption)
     */
    uint8_t bSetKey;
} NvVsePKA1RSAEncDecParams;

/**
* Holds AES encrypt/decrypt parameters.
*/
typedef struct {
   /** Holds a Boolean that specifies whether to encrypt the buffer. */
    uint8_t   bEncrypt;
    uint8_t   uKeySlot;
    uint8_t   uKeyLength;
    NvVseAESMode eAESMode;
    NvVseIVSel   eIVSel;
    uint8_t   oLinearCTR[NVVSE_AES_LINEAR_CTR_LEN];
    uint8_t   uLinearCTRCNTN;
    /** Length of the input buffer. */
    uint32_t uDataLength;
    /** Holds a pointer to input buffer to be encrypted/decrypted. */
    uint8_t *pSrcBuffer;
    /** Holds a pointer to the encrypted/decrypted buffer. */
    uint8_t *pDstBuffer;
} NvVseAESEncDecParams;

/**
* Holds AES CMAC parameters.
*/
typedef struct {
    uint8_t uKeySlot;
    uint8_t uKeyLength;
    NvVseIVSel eIVSel;
    /* Length of the input buffer. */
    uint32_t uDataLength;
    /** Holds a pointer to the input buffer for which
        AES CMAC is to be calculated. */
    uint8_t *pSrcBuffer;
    /* Holds a pointer the AES CMAC signature. */
    uint8_t *pDstBuffer;
} NvVseAESCMACParams;

/**
  * Opens the nvvse device and gets a handle for further communication.
  *
  * This API must be called before interacting with nvvse.
  *
  * @param[out] pHandle   A pointer to NvVseHandle created by the nvvse module.
  * @param[in]  eEngineType The type of nvvse engine to be opened.
  * @return     NVVSE_STATUS_OK if successful, or the appropriate error code.
  */
NvVseStatus NvVseOpen(NvVseHandle *pHandle, NvVseEngineType eEngineType);

/**
  * Initializes the driver for SHA calculation.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  eSHAType SHA algorithm to be used.
  * @param[in]  uTotalMsgsize Size of the message.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseSHAInit(NvVseHandle hNvVse, NvVseSHAType eSHAType, uint64_t uTotalMsgsize);

/**
  * Updates the intermediate/final input buffer.
  *
  * The driver calculates the hash of this buffer along with
  * intermediate hash of the previous buffers (if any) and stores
  * the resulting hash in driver's memory.
  * The application must call NvVseSHAUpdate() to read the final hash.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pInputBuffer A pointer to the input buffer.
  * @param[in]  uInputBuffersize Indicates the size of the input buffer.
  * @param[in]  bLast Indicates the last chunk of the input message.
  *                  Set to '1' to indicate the last chunk of the input message.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseSHAUpdate(NvVseHandle hNvVse, uint8_t *pInputBuffer,
               uint32_t uInputBuffersize, uint8_t bLast);

/**
  * Returns the final hash of all buffers that the client previously injected
  * by calling NvVseSHAUpdate().
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pDigestBuffer A pointer to the buffer where the driver
  *             stores the digest.
  * @param[in]  uDigestSize Indicates the size of the digest buffer.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseSHAFinal(NvVseHandle hNvVse, uint8_t *pDigestBuffer,
                   uint32_t uDigestSize);

/**
  * Allocates a RSA KeySlot from the PKA1 engine.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[out]  pKeySlot A pointer to the KeySlot that NVVSE allocates.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVsePKA1RSAAllocKey(NvVseHandle hNvVse, uint8_t *pKeySlot);

/**
  * Releases kesyslot already allocated from PKA1 engine.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[in]   uKeySlot KeySlot to be released.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVsePKA1RSAReleaseKey(NvVseHandle hNvVse, uint8_t uKeySlot);

/**
  * Sets the key for the RSA keyslot from the PKA1 engine.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[in]   uKeySlot KeySlot to be set.
  * @param[in]   uExpKeyLength Length of the key exponent.
  * @param[in]   pExpKeyData A pointer to key exponent.
  * @param[in]   uModKeyLength Length of key modulus.
  * @param[in]   pModKeyData A pointer to key modulus.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVsePKA1RSASetKey(NvVseHandle hNvVse, uint8_t uKeySlot,
                   uint32_t uExpKeyLength, uint8_t *pExpKeyData,
                   uint32_t uModKeyLength, uint8_t *pModKeyData);

/**
  * Authenticates the RSA signature using PKA1 Engine.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pRSASSAVerifyParams A pointer to NvVseRSASSAVerifyParams.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVsePKA1RSASSAVerify(NvVseHandle hNvVse,
                         NvVseRSASSAVerifyParams *pRSASSAVerifyParams);
/**
  * Encrypts/Decrypts the buffer using specified RSA Key and PKA1 Engine.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pPKA1RSAEncDecParams A pointer to NvVsePKA1RSAEncDecParams.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVsePKA1RSAEncryptDecrypt(NvVseHandle hNvVse,
                        NvVsePKA1RSAEncDecParams *pPKA1RSAEncDecParams);
/**
  * Allocates an AES KeySlot.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[out]  pKeySlot A pointer to KeySlot Allocated by nvvse.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESAllocKey(NvVseHandle hNvVse, uint8_t *pKeySlot);

/**
  * Releases already allocated AES KeySlot.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[in]   uKeySlot KeySlot to be released.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESReleaseKey(NvVseHandle hNvVse, uint8_t uKeySlot);

/**
  * Sets the AES Key.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[in]   uKeySlot KeySlot to be set.
  * @param[in]   uKeyLength Length of the key.
  * @param[in]   pKeyData A pointer to Key Data.
  * @param[in]   bCMAC indicates that the key is set for AES CMAC.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESSetKey(NvVseHandle hNvVse, uint8_t uKeySlot,
               uint32_t uKeyLength, uint8_t *pKeyData, uint8_t bCMAC);

/**
  * Sets the AES IV.
  *
  * @param[in]   hNvVse The handle that NvVseOpen() returned.
  * @param[in]   bOriginalIV Indicates if original IV is Set.
  * @param[in]   pIV A pointer to IV.
  * @param[in]   uKeySlot KeySlot to be set.
  * @retval      NVVSE_STATUS_OK If successful.
  *              Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESSetIV(NvVseHandle hNvVse, uint8_t bOriginalIV, uint8_t *pIV, uint8_t uKeySlot);

/**
  * Encrypts/Decrypts the buffer using specified AES Key.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pAESParams A pointer to NvVseAESEncDecParams.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESEncryptDecrypt(NvVseHandle hNvVse, NvVseAESEncDecParams *pAESParams);

/**
  * AES CMAC of the buffer using specified key.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  pAESCMACParams A pointer to \ref NvVseAESCMACParams.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseAESCMAC(NvVseHandle hNvVse, NvVseAESCMACParams *pAESCMACParams);

/**
  * Generates a random number using DRNG with the input seed from TRNG.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @param[in]  uDataLength Length of random number to be generated.
  *             Max allowed length is 512 bytes.
  * @param[in]  pDst A pointer to the random number generated.
  * @retval     NVVSE_STATUS_OK If successful.
  *             Otherwise, returns the appropriate error code.
  */
NvVseStatus
NvVseRNG1GetDRNGWithTRNGSeed(NvVseHandle hNvVse, uint32_t uDataLength, uint8_t *pDst);

/**
  * Closes the nvvse device.
  *
  * @param[in]  hNvVse The handle that NvVseOpen() returned.
  * @return     NVVSE_STATUS_OK if successful, or the appropriate error code.
  */
NvVseStatus NvVseClose(NvVseHandle hNvVse);

/** @} */
#if defined(__cplusplus)
}
#endif
#endif//#define _NVVSE_H
