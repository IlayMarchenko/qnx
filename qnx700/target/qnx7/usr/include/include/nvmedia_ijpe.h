/*
 * Copyright (c) 2014-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file nvmedia_ijpe.h
 * \brief <b>NVIDIA Media Interface: Image JPEG Encode Processing API</b>
 *
 * @b Description: This file contains the \ref image_jpeg_encode_api "Image JPEG Encode Processing API".
 */

#ifndef _NVMEDIA_IJPE_H
#define _NVMEDIA_IJPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"

/**
 * \defgroup image_jpeg_encode_api Image JPEG Encoder
 *
 * The NvMediaIJPE object takes uncompressed image data and turns it
 * into a jpeg bitstream.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_IJPE_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_IJPE_VERSION_MINOR   3

/**
 * \hideinitializer
 * \brief JPEG encoder flag empty
 */
#define NVMEDIA_JPEG_ENC_FLAG_NONE                      (0 << 0)
/**
 * \hideinitializer
 * \brief JPEG encoder flag to skip SOI marker. Normally, app inserts EXIF data in
 * jpeg image which occurs after SOI marker. This flag be used to skip SOI marker
 * insertion.
 */
#define NVMEDIA_JPEG_ENC_FLAG_SKIP_SOI                  (1 << 0)

/**
 * \hideinitializer
 * \brief Quality
 */
#define NVMEDIA_IMAGE_JPEG_ATTRIBUTE_QUALITY            (1 << 0)
/**
 * \hideinitializer
 * \brief Restart interval
 */
#define NVMEDIA_IMAGE_JPEG_ATTRIBUTE_RESTARTINTERVAL    (1 << 1)
/**
 * \hideinitializer
 * \brief encode frame target size
 */
#define NVMEDIA_IMAGE_JPEG_ATTRIBUTE_TARGETSIZE         (1 << 2)
/**
 * \hideinitializer
 * \brief Luma/Chroma quant table
 */
#define NVMEDIA_IMAGE_JPEG_ATTRIBUTE_QUANTTABLE         (1 << 3)
/**
 * \hideinitializer
 * \brief Huffmann table
 */
#define NVMEDIA_IMAGE_JPEG_ATTRIBUTE_HUFFTABLE          (1 << 4)

/**
 * \brief image JPEG encoder HuffmanTable.
 */
typedef struct {
   uint8_t length[16];
   uint8_t *values;
} NvMediaJPHuffmanTableSpecfication;

/**
 * \brief image JPEG encoder attributes.
 */
typedef struct {
/** \brief A value clamped to between 1 and 100, set to generate luma/chroma Quant tables.
 *  It is initialized to 0 at NvMediaIJPE creation, so encoder will use default standard
 *  Luma/Chroma quant tables. The corresponding attribute mask is \ref
 *  NVMEDIA_IMAGE_JPEG_ATTRIBUTE_QUALITY
 */
   uint8_t quality;
/** \brief A value to specify restart interval, initialized to 0 at NvMediaIJPE creation.
 *  The corresponding attribute mask is \ref NVMEDIA_IMAGE_JPEG_ATTRIBUTE_RESTARTINTERVAL
 */
   uint32_t restartInterval;
/** \brief A value to specify target encode size, initialized to 0xffffffff at NvMediaIJPE
 *  creation. The corresponding attribute mask is \ref NVMEDIA_IMAGE_JPEG_ATTRIBUTE_TARGETSIZE
 */
   uint32_t targetImageSize;
/** \brief A table for Luma quantization, initialized to default standard table at NvMediaIJPE
 *  creation. The corresponding attribute mask is \ref NVMEDIA_IMAGE_JPEG_ATTRIBUTE_QUANTTABLE
 */
   uint8_t lumaQuant[64];
/** \brief A table for Chroma quantization, initialized to default standard table at NvMediaIJPE
 *  creation. The corresponding attribute mask is \ref NVMEDIA_IMAGE_JPEG_ATTRIBUTE_QUANTTABLE
 */
   uint8_t chromaQuant[64];
/** \brief A Huffmann table for Luma DC sample, initialized to NULL for using default table
 *  in JPEG specification. The corresponding attribute mask is \ref
 *  NVMEDIA_IMAGE_JPEG_ATTRIBUTE_HUFFTABLE
 *  Only support in T210 or greater
 */
   NvMediaJPHuffmanTableSpecfication *lumaDC;
/** \brief A Huffmann table for Luma AC sample, initialized to NULL for using default table
 *  in JPEG specification. The corresponding attribute mask is \ref
 *  NVMEDIA_IMAGE_JPEG_ATTRIBUTE_HUFFTABLE
 *  Only support in T210 or greater
 */
   NvMediaJPHuffmanTableSpecfication *lumaAC;
/** \brief A Huffmann table for Chroma DC sample, initialized to NULL for using default table
 *  in JPEG specification. The corresponding attribute mask is \ref
 *  NVMEDIA_IMAGE_JPEG_ATTRIBUTE_HUFFTABLE
 *  Only support in T210 or greater
 */
   NvMediaJPHuffmanTableSpecfication *chromaDC;
/** \brief A Huffmann table for Chroma AC sample, initialized to NULL for using default table
 *  in JPEG specification. The corresponding attribute mask is \ref
 *  NVMEDIA_IMAGE_JPEG_ATTRIBUTE_HUFFTABLE
 *  Only support in T210 or greater
 */
   NvMediaJPHuffmanTableSpecfication *chromaAC;
} NvMediaJPEncAttributes;

/**
 * \brief image JPEG encoder object created by \ref NvMediaIJPECreate.
 */
typedef struct {
    /** Input Image surface type. */
    NvMediaSurfaceType inputFormat;
} NvMediaIJPE;

/**
 * \brief Gets the version compatibility for the NvMedia IJPE library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaIJPEGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates a JPEG encoder object capable of turning a stream of surfaces
 * of the \a inputFormat into a JPEG stream.
 * Surfaces are fed to the encoder with NvMediaIJPEFeedFrame()
 * and bitstream buffers are retrieved with NvMediaIJPEGetBits().
 * \param[in] device The \ref NvMediaDevice "device" this image JPEG encoder will use.
 * \param[in] inputFormat Specifies the stream of surfaces to convert to JPEG.
 * \param[in] maxOutputBuffering
 *      This determines how many frames of encoded bitstream can be held
 *      by the \ref NvMediaIJPE object before it must be retrieved using
 *      NvMediaIJPEGetBits().  This number must be greater than
 *      or equal to \a maxInputBuffering and is clamped to between
 *      \a maxInputBuffering and 16.  If \a maxOutputBuffering frames worth
 *      of encoded bitstream are yet unretrieved by @c %NvMediaIJPEGetBits(),
 *      then NvMediaIJPEFeedFrame() returns
 *      \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING.  One or more frames must
 *      be retrieved with \c %NvMediaIJPEGetBits() before frame feeding
 *      can continue.
 * \param[in] maxBitstreamBytes Determines the maximum bytes that JPEG encoder can produce
 *      for each feed frame.
 * \retval NvMediaIJPE The new image JPEG encoder device's handle
 * or \c NULL if unsuccessful.
 */
NvMediaIJPE *
NvMediaIJPECreate(
    NvMediaDevice *device,
    NvMediaSurfaceType inputFormat,
    uint8_t maxOutputBuffering,
    uint32_t  maxBitstreamBytes
);

/**
 * \brief Destroys an NvMedia image JPEG encoder
 * \param[in] encoder The JPEG encoder to destroy.
 */
void NvMediaIJPEDestroy(NvMediaIJPE *encoder);

/**
 * \brief Encodes the specified \a frame with input quality.
 * \param[in] encoder The encoder to use.
 * \param[in] frame
 *      This must be of the same sourceType as in the the \ref NvMediaIJPE object.
 *      There is no limit on the size of this surface.
 * \param[in] quality
 *      This specifies the encode quality. JPEG encode will generate quant tables
 *      for luma and chroma according to the quality value
 * \n Supported quality value: 1..100
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if successful.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL or invalid.
 * \n \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if NvMediaIJPEGetBits()
 *  has not been called frequently enough and the maximum internal
 *  bitstream buffering (determined by \a maxOutputBuffering passed to
 *  NvMediaIJPECreate()) has been exhausted.
 */
NvMediaStatus
NvMediaIJPEFeedFrame(
    NvMediaIJPE *encoder,
    NvMediaImage *frame,
    uint8_t quality
);

/**
 * \brief Encodes the specified \a frame with input Luma and Chroma quant tables.
 * \param[in] encoder The encoder to use.
 * \param[in] frame
 *      This must be of the same sourceType as in the \ref NvMediaIJPE object.
 *      There is no limit on the size of this surface.
 * \param[in] lumaQuant
 *      This specifies Luma quant table used for encode
 * \param[in] chromaQuant
 *      This specifies Chroma quant table used for encode
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if successful.
 * \n \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING
 *    if NvMediaIJPEGetBits() has not been called frequently enough and the
 *    maximum internal bitstream buffering (determined by \a maxOutputBuffering
 *    passed to \ref NvMediaIJPECreate()) has been exhausted.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL or invalid.
 */
NvMediaStatus
NvMediaIJPEFeedFrameQuant(
    NvMediaIJPE *encoder,
    NvMediaImage *frame,
    uint8_t *lumaQuant,
    uint8_t *chromaQuant
);

/**
 * \brief Encodes the specified \a frame with input Luma and Chroma quant tables
 *  and targetImageSize.
 * \param[in] encoder The encoder to use.
 * \param[in] frame
 *      This must be of the same sourceType as in the \ref NvMediaIJPE object.
 *      There is no limit on the size of this surface.
 * \param[in] lumaQuant
 *      This specifies Luma quant table used for encode
 * \param[in] chromaQuant
 *      This specifies Chroma quant table used for encode
 * \param[in] targetImageSize
 *      This specifies target image size in bytes
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if successful.
 * \n \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if NvMediaIJPEGetBits()
 *  has not been called frequently enough and the maximum internal
 *  bitstream buffering (determined by \a maxOutputBuffering passed to
 *  \ref NvMediaIJPECreate()) has been exhausted.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL or invalid.
 */
NvMediaStatus
NvMediaIJPEFeedFrameRateControl(
    NvMediaIJPE *encoder,
    NvMediaImage *frame,
    uint8_t *lumaQuant,
    uint8_t *chromaQuant,
    uint32_t targetImageSize
);

/**
 * \brief Sets the JPEG encoder attributes. These go into effect at
 * the next encode frame.
 * \param[in] encoder The encoder to use.
 * \param[in] attributeMask Attribute mask.
 * \param[in] attributes Attributes data.
 * \n Supported attribute structures:
 * \n \ref NvMediaJPEncAttributes
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if successful.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 */
NvMediaStatus
NvMediaIJPESetAttributes(
    NvMediaIJPE *encoder,
    uint32_t attributeMask,
    void *attributes
);

/**
 * \brief Returns a frame's worth of bitstream
 *  into the provided \a buffer. \n numBytes returns the size of this
 *  bitstream.  It is safe to call this function from a separate thread.
 *  The return value and behavior is the same as that of
 *  NvMediaIJPEBitsAvailable() when called with \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER
 *  except that when \ref NVMEDIA_STATUS_OK is returned, the \a buffer will be
 *  filled in addition to the \a numBytes.
 *
 * Before calling this function:
 * 1. Call NvMediaIJPEBitsAvailable() to determine the number of bytes
 *    required for the next frame.
 * 2. Allocate a buffer that can hold the next frame.
 *
 * \param[in] encoder The encoder to use.
 * \param[out] numBytes
 *       Returns the size of the filled bitstream.
 * \param[in,out] buffer
 *      The buffer to be filled with the encoded data. If buffer is NULL, this function
 *      returns without copying the encoded bitstream.
 * \param[in] flags
 *      The flags for special handlings
 *      Current support flag \ref NVMEDIA_JPEG_ENC_FLAG_NONE or
 *                           \ref NVMEDIA_JPEG_ENC_FLAG_SKIP_SOI
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_PENDING if an encode is in progress but not yet completed.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 */
NvMediaStatus
NvMediaIJPEGetBits(
    NvMediaIJPE *encoder,
    uint32_t *numBytes,
    void *buffer,
    uint32_t flags
);

/**
 * Performs the same operation as NvMediaIJPEGetBits() except
 * NvMediaIJPEGetBitsEx() consumes an array of buffers. Please see NvMediaIJPEGetBits()
 * for usage.
 * \param[in] encoder The encoder to use.
 * \param[out] numBytes
 *       Returns the size of the filled bitstream.
 * \param[in] numBitstreamBuffers
 *       Number of buffers provided to encoder
 * \param[in,out] bitstreams
 *      Pointer pointing to the array of buffers of type NvMediaBitstreamBuffer.
 *      These buffer to be filled with the encoded data. If it is NULL, this function
 *      returns without copying the encoded bitstreams.
 * \param[in] flags
 *      The flags for special handlings
 *      Current support flag \ref NVMEDIA_JPEG_ENC_FLAG_NONE or
 *                           \ref NVMEDIA_JPEG_ENC_FLAG_SKIP_SOI
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_PENDING if an encode is in progress but not yet completed.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 */
NvMediaStatus
NvMediaIJPEGetBitsEx(
    NvMediaIJPE *encoder,
    uint32_t *numBytes,
    uint32_t numBitstreamBuffers,
    const NvMediaBitstreamBuffer *bitstreams,
    uint32_t flags
);

/**
 * \brief Returns the encode status
 *  and number of bytes available for the next frame (if any).
 *  The specific behavior depends on the specified \a blockingType.
 *  It is safe to call this function from a separate thread.
 * \param[in] encoder The encoder to use.
 * \param[in] numBytesAvailable
 *      The number of bytes available in the next encoded frame. This
 *      is valid only when the return value is \ref NVMEDIA_STATUS_OK.
 * \param[in] blockingType
 *      The following are the supported blocking types:
 * \li \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER
 *    \n  This type never blocks. As a result, \a millisecondTimeout is ignored.
 *        With this \a blockingType value, the following return values are possible:
 *        \n \c NVMEDIA_STATUS_OK
 *        \n \ref NVMEDIA_STATUS_PENDING
 *        \n \ref NVMEDIA_STATUS_NONE_PENDING
 * \li \ref NVMEDIA_ENCODE_BLOCKING_TYPE_IF_PENDING
 *     \n Same as \c NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER except that
 *        the function never returns with \c NVMEDIA_STATUS_PENDING.
 *        If an encode is pending, then
 *        this function blocks until the status changes to
 *        \c NVMEDIA_STATUS_OK or until the timeout occurs.
 *        With this \a blockingType value, the following return values are possible:
 *        \n \c NVMEDIA_STATUS_OK
 *        \n \c NVMEDIA_STATUS_NONE_PENDING
 *        \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \li \ref NVMEDIA_ENCODE_BLOCKING_TYPE_ALWAYS
 *        With this \a blockingType value, the function blocks until the conditions
 *        represented by those return values are satisfied.
 *        Only the following return values are possible:
 *        \n \c NVMEDIA_STATUS_OK
 *        \n \c NVMEDIA_STATUS_TIMED_OUT
 * \param[in] millisecondTimeout
 *       Timeout in milliseconds or \ref NVMEDIA_VIDEO_ENCODER_TIMEOUT_INFINITE
 *       if a timeout is not desired.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \c NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \c NVMEDIA_STATUS_PENDING if an encode is in progress but not yet completed.
 * \n \c NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 * \n \c NVMEDIA_STATUS_TIMED_OUT if the operation timed out.
 */
NvMediaStatus
NvMediaIJPEBitsAvailable(
    NvMediaIJPE *encoder,
    uint32_t *numBytesAvailable,
    NvMediaBlockingType blockingType,
    uint32_t millisecondTimeout
);

/*
 * \defgroup history_nvmedia_ijpe History
 * Provides change history for the NvMedia Image Jpeg Encode API.
 *
 * \section history_nvmedia_ijpe Version History
 *
 * <b> Version 1.0 </b> November 9, 2015
 * - Initial release
 *
 * <b> Version 1.1 </b> May 11, 2016
 * - Added \ref NvMediaIJPECheckVersion API
 *
 * <b> Version 1.2 </b> Sep 19, 2016
 * - Added \ref NvMediaIJPEGetBitsEx API
 *
 * <b> Version 1.3 </b> May 15, 2017
 * - Added \ref NvMediaIJPEGetVersion API to get the version of NvMedia IJPE library
 * - NvMediaIJPECheckVersion is deprecated. Use NvMediaIJPEGetVersion() instead
 * - All NvMedia data types are moved to standard data types
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IJPE_H */
