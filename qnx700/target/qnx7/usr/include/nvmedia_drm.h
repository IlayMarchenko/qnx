/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */


#ifndef _NVMEDIA_DRM_H
#define _NVMEDIA_DRM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Video Decryptor (DRM) API </b>
 *
 * @b Description: This file provides the Video Decryptor (DRM) API.
 */

/**
 * \defgroup nvmedia_drm_group Video Decryptor (DRM) API
 * \ingroup nvmedia_video_top
 *
 * \brief Decrypts and re-encrypts video data with supported formats for the hardware
 * in a video stream.
 * @{
 */

/**
 * \hideinitializer
 * \brief max number of subsample support
 */
#define NVMEDIA_MAX_NALS 32

/** \brief Defines the supported DRM formats. */
typedef enum {
    /** drm format: Netflix */
    NvMDRM_Netflix = 0,
    /** drm format: Widevine */
    NvMDRM_Widevine = 1,
    /** drm format: Ultravoilet */
    NvMDRM_Ultraviolet,
    /** drm format: Piff */
    NvMDRM_Piff,
    /** drm format: Marlin */
    NvMDRM_Marlin,
    /** drm format: Piff CBC */
    NvMDRM_PiffCbc,
    /** drm format: Piff CTC */
    NvMDRM_PiffCtr,
    /** drm format: Marlin CBC */
    NvMDRM_MarlinCbc,
    /** drm format: Marlin CTR */
    NvMDRM_MarlinCtr,
    /** drm format: Widevine CTR */
    NvMDRM_WidevineCtr,
    /** drm format: Clear data */
    NvMDRM_Clear = 0xf,
    /** drm format: To tell clear data processing in secure buffer */
    NvMDRM_ClearAsEncrypted,
    /** drm format: None: This should be the last element */
    NvMDRM_None
} NvMediaDRMType;

/**
 * \brief Holds encrypted metadata information that
 * the parser passes to the video decoder component. */
typedef struct
{
    /** Flag that specifies whether the buffer is encrypted. */
    NvMediaBool   enableEncryption;
    /** drm mode of encrypted content. */
    uint32_t      uDrmMode;
    /** Intialization vector of all subsamples */
    uint32_t      InitVector[NVMEDIA_MAX_NALS][4];
    /** intialization vectors are present or not for subsamples */
    uint32_t      IvValid[NVMEDIA_MAX_NALS];
    /** total bytes of encrypted data in input buffer */
    uint32_t      uBytesOfEncryptedData;
    /** encrypt blk count when pattern mode encryption is used */
    uint32_t      uEncryptBlkCnt;
    /** skip blk count when pattern mode encryption is used */
    uint32_t      uSkipBlkCnt;
    /** total number of subsamples for given buffer */
    uint32_t      uNumNals;
    /** keyslot number used where content key is written */
    uint32_t      KeySlotNumber;
    /** bytes of encrypted data for subsamples */
    uint32_t      BOED[NVMEDIA_MAX_NALS];
    /** bytes of clear data for subsamples */
    uint32_t      BOCD[NVMEDIA_MAX_NALS];
    /** encrypted metadata buffer of pass1 */
    uint32_t      *AesPass1OutputBuffer;
    /** bytes of non slice data in input buffer */
    uint32_t      non_slice_data;
}NvMediaEncryptParams;

/**
 * \brief Holds re-encrypted data information that the video decoder returns
 * to the parser.
 * \sa \ref pfnCbNvMediaDecodePicture
 */
typedef struct {
    /** clear hdr side after pass1 */
    uint32_t  uClearHeaderSize;
    /** clear hdr pointer to buffer after pass1 */
    uint8_t  *pClearHeaderPtr;
    /** encrypted metadata struture pointer after pass1 */
    uint32_t *pAesPass1OutputBuffer;
} NvMediaAESMetaData;

/** \brief Holds encryption intialization vector information. */
typedef struct {
    /** intialization vector */
    uint8_t         IV[16];
    /** intialization vector present or not */
    NvMediaBool     bIvValid;
} NvMediaAESIv;

/** \brief Holds encrypted metadata information that the client sends
 *  to the parser.
 *  \sa NvMediaParserSetEncryption()
 */
typedef struct _NvMediaAESParams
{
    /** drm mode of encrypted content */
    uint32_t uDrmMode;
    /** pointer to intialization vector array */
    uint8_t  *pIV;
    /** encrypt blk count when pattern mode encryption is used */
    uint32_t uEncryptBlkCnt;
    /** skip blk count when pattern mode encryption is used */
    uint32_t uSkipBlkCnt;
    /** keyslot number used where content key is written */
    uint32_t KeySlotNumber;
    /** pointer to bytes of encrypted data for subsamples */
    uint32_t *pBOED;
    /** pointer to bytes of clear data for subsamples */
    uint32_t *pBOCD;
    /** total number of subsamples for given buffer */
    uint32_t uMetadataCount;
    /** non aligned offset for encrypted buffer */
    uint32_t uNonAlignedOffset;
    /** initialization vector array */
    NvMediaAESIv IvSet[NVMEDIA_MAX_NALS];
} NvMediaAESParams;

/**
 * \hideinitializer
 * \brief Defines flags used for decryptor creation.
 */
#define NVMEDIA_VIDEO_DECRYPT_PROFILING             (1<<0)

/** \brief Holds the video decrypter object. */
typedef struct {
    /** \brief Codec type */
    NvMediaVideoCodec eCodec;
    /** \brief pass hw decode clock value for otf case */
    uint32_t  hwClockValue;
} NvMediaVideoDecrypter;

/** \brief Creates a video decrypter object.
 *
 * Creates a \ref NvMediaVideoDecrypter object for the specified codec \ref NvMediaVideoCodec.
 * Use NvMediaVideoDecrypterDestroy() to destroy this video decrypter object.

 * \param[in] codec Codec type. The following types are supported:
 * - \ref NVMEDIA_VIDEO_CODEC_HEVC
 * - \ref NVMEDIA_VIDEO_CODEC_H264
 * - \ref NVMEDIA_VIDEO_CODEC_MPEG1
 * - \ref NVMEDIA_VIDEO_CODEC_MPEG2
 * - \ref NVMEDIA_VIDEO_CODEC_VP8
 * - \ref NVMEDIA_VIDEO_CODEC_VP9
 * \param[in] maxBitstreamSize The maximum size for bitstream.
 * This limits internal allocations.
 * \param[in] flags Set the flags of the decoder.
 * \param[in] instanceId The ID of the engine instance.
 * The following instances are supported:
 * \n \ref NVMEDIA_DECODER_INSTANCE_0
 * \n \ref NVMEDIA_DECODER_INSTANCE_1
 * \n \ref NVMEDIA_DECODER_INSTANCE_AUTO
 * \return NvMediaVideoDecrypter The new video decoder decrypter handle or NULL if unsuccessful.
 */

NvMediaVideoDecrypter *
NvMediaVideoDecrypterCreate (
    NvMediaVideoCodec codec,
    uint32_t maxBitstreamSize,
    uint32_t flags,
    NvMediaDecoderInstanceId instanceId
);

/** \brief Destroys a video decoder decrypter object.
 * \param[in] pDecrypter The video decoder decrypter to be destroyed.
 */
void
NvMediaVideoDecrypterDestroy(
    NvMediaVideoDecrypter *pDecrypter
);


/**
 * \brief Decrypts the HDR of the encrypted content.
 *
 * The \ref NvMediaParserClientCb::DecryptHdr callback function calls this function.
 * \param[in] pDecrypter A pointer to the decrypter object.
 * \param[in] pictureData A pointer to NvMediaParserPictureData.
 * \param[in] pBitstream A pointer to bitstream data.
 * \param[in] instanceId The ID of the engine instance.
 * The following instances are supported if NVMEDIA_DECODER_INSTANCE_AUTO
 * was used in \ref NvMediaVideoDecoderCreateEx API, else this parameter is ignored:
 * \n \ref NVMEDIA_DECODER_INSTANCE_0
 * \n \ref NVMEDIA_DECODER_INSTANCE_1
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 */

NvMediaStatus
NvMediaVideoDecryptHeader(
    NvMediaVideoDecrypter *pDecrypter,
    void *pictureData,
    const NvMediaBitstreamBuffer *pBitstream,
    NvMediaDecoderInstanceId instanceId
);


/**
 * \brief Gets clear header data after pass1.
 *
 * The \ref NvMediaParserClientCb::GetClearHdr callback function calls this function.
 * This is a blocking call, which means the output data is guaranteed to contain
 * clear header data along with re-entrypted data for pass2.
 * \param[in] pDecrypter The decrypter object.
 * \param[out] pictureData A pointer to \ref NvMediaParserPictureData.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 */

NvMediaStatus
NvMediaVideoGetClearHeader(
    NvMediaVideoDecrypter *pDecrypter,
    void *pictureData
);

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_DRM_H */
