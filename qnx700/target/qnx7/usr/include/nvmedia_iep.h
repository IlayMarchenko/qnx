/*
 * Copyright (c) 2014-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: NvMedia Image Encode Processing API </b>
 *
 * This file contains the \ref image_encode_api "Image Encode Processing API".
 */

#ifndef _NVMEDIA_IEP_H
#define _NVMEDIA_IEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"
#include "nvmedia_image.h"

/**
 * \defgroup image_encode_api Image Encoder
 *
 * The NvMediaIEP object takes uncompressed image data and turns it
 * into a codec specific bitstream. Only H.264, H.265 and VP9 encoding is supported.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_IEP_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_IEP_VERSION_MINOR   2

/**
 * \brief Image encode type
 */
typedef enum {
    /** \brief H.264 encode */
    NVMEDIA_IMAGE_ENCODE_H264,
    NVMEDIA_IMAGE_ENCODE_HEVC,
    NVMEDIA_IMAGE_ENCODE_VP9,
    NVMEDIA_IMAGE_ENCODE_VP8
} NvMediaIEPType;


/**
 * \brief Holds the image encoder object created by \ref NvMediaIEPCreate.
 */
typedef struct {
    /** Codec type */
    NvMediaIEPType encodeType;
    /** Input Image surface type. */
    NvMediaSurfaceType inputFormat;
    /** Instance ID */
    NvMediaEncoderInstanceId instanceId;
} NvMediaIEP;

/**
 * \brief Checks the version compatibility for the NvMedia IEP library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaIEPGetVersion(
    NvMediaVersion *version
);

/**
 * Creates an encoder object capable of turning a stream of surfaces
 * of the "inputFormat" into a bitstream of the specified "codec".
 * Surfaces are feed to the encoder with \ref NvMediaIEPFeedFrame
 * and bitstream buffers are retrieved with \ref NvMediaIEPGetBitsEx.
 * \param[in] device The \ref NvMediaDevice "device" this image encoder will use.
 * \param[in] encodeType The encode type, which can be:
 *      \n \ref NVMEDIA_IMAGE_ENCODE_H264
 *      \n \ref NVMEDIA_IMAGE_ENCODE_HEVC
 *      \n \ref NVMEDIA_IMAGE_ENCODE_VP9
 * \param[in] initParams The encode parameters, which can be:
 * \n Supported encode parameter structures:
 * \n \ref NvMediaEncodeInitializeParamsH264
 * \n \ref NvMediaEncodeInitializeParamsH265
 * \n \ref NvMediaEncodeInitializeParamsVP9
 * \param[in] inputFormat Must be obtained by /ref NvMediaSurfaceFormatGetType with:
 *      \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR, UINT, [8/10], BL)
 *      \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 444, SEMI_PLANAR, UINT, [8/10], BL)
 * \param[in] maxInputBuffering
 *      Maximum number of frames in the encode pipeline
 *      at any time.  For example, if `maxInputBuffering==1`,
 *      \ref NvMediaIEPFeedFrame is blocked until the previous
 *      encode completes.  If `maxInputBuffering==2`,
 *      \ref NvMediaIEPFeedFrame accepts one frame while another
 *      is still being encoded by the hardware, but will block if two
 *      are still being encoded.  \a maxInputBuffering is clamped between
 *      1 and 16.  This field is ignored for YUV inputs which do not require
 *      a pre-processing pipeline before the encode hardware.
 * \param[in] maxOutputBuffering
 *      Maximum number of frames of encoded bitstream that can be held
 *      by the NvMediaIEP before it must be retrieved using
 *      NvMediaIEPGetBitsEx().  This number must be greater than
 *      or equal to \a maxInputBuffering and is clamped to between
 *      \a maxInputBuffering and 16.  If \a maxOutputBuffering frames worth
 *      of encoded bitstream are yet unretrived by \ref NvMediaIEPGetBitsEx
 *      \ref NvMediaIEPFeedFrame returns
 *      \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING. One or more frames must
 *      be retrived with NvMediaIEPGetBitsEx() before frame feeding
 *      can continue.
 * \param[in] instanceId The ID of the encoder engine instance. The following
 *      instances are supported:
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_0
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_1
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_AUTO
 * \return \ref NvMediaIEP The new image encoder's handle or NULL if unsuccessful.
 */
NvMediaIEP *
NvMediaIEPCreate(
    NvMediaDevice *device,
    NvMediaIEPType encodeType,
    void *initParams,
    NvMediaSurfaceType inputFormat,
    uint8_t maxInputBuffering,
    uint8_t maxOutputBuffering,
    NvMediaEncoderInstanceId instanceId
);

/**
 * \brief Destroys an NvMedia image encoder.
 * \param[in] encoder The encoder to destroy.
 */
void NvMediaIEPDestroy(NvMediaIEP *encoder);

/**
 * \brief Encodes the specified frame.  This function
 *  returns \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if \ref NvMediaIEPGetBitsEx
 *  has not been called frequently enough and the maximum internal
 *  bitstream buffering has been exhausted. The \a MaxOutputBuffering argument
 *  passed to NvMediaIEPCreate() specifies the maximum buffering.
 * \param[in] encoder The encoder to use.
 * \param[in] frame The frame, which
 *      must be of the same sourceType as in the NvMediaIEP.
 *      There is no limit on the size of this surface.  The
 *      source rectangle specified by \a sourceRect is scaled
 *      to the stream dimensions.
 * \param[in] sourceRect
 *       The rectangle on the source, which is scaled to the stream
 *       dimensions.  A value of NULL specifies a rectangle the full size of
 *       the source surface.  The source can be flipped horizontally
 *       or vertically, by swapping the left and right or top and bottom
 *       coordinates. This parameter is valid only for RGB type input
 *       surfaces.
 * \param[in] picParams Picture parameters used for the frame.
 * \n Supported picture parameter structures:
 * \n \ref NvMediaEncodePicParamsH264
 * \n \ref NvMediaEncodePicParamsH265
 * \n \ref NvMediaEncodePicParamsVP9
 * \param[in] instanceId The ID of the encoder engine instance.
 * The following instances are supported if NVMEDIA_ENCODER_INSTANCE_AUTO
 * was used in \ref NvMediaIEPCreate API, else this parameter is ignored:
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_0
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_1
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 */
NvMediaStatus
NvMediaIEPFeedFrame(
    NvMediaIEP *encoder,
    NvMediaImage *frame,
    NvMediaRect *sourceRect,
    void *picParams,
    NvMediaEncoderInstanceId instanceId
);

/**
 * \brief Sets the encoder configuration. The values in the configuration
 * take effect only at the start of the next GOP.
 * \param[in] encoder A pointer to the encoder to use.
 * \param[in] configuration Configuration data.
 * \n Supported configuration structures:
 * \n \ref NvMediaEncodeConfigH264
 * \n \ref NvMediaEncodeConfigH265
 * \n \ref NvMediaEncodeConfigVP9
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 */
NvMediaStatus
NvMediaIEPSetConfiguration(
    NvMediaIEP *encoder,
    void *configuration
);

/**
 * \brief Returns the bitstream for a slice or frame.
 *
 *  It is safe to call this function from a separate thread.
 *
 *  When slice Level output is enabled, this function must be called repeatedly.
 *  until the output \a extradata field \c bEndOfFrame is not set to \c NVMEDIA_TRUE.
 *  With every call to \ref NvMediaIEPGetBitsEx, the function returns the bitstream
 *  for a slice or frame.
 *
 *  When slice level output is not enabled, the return value and behavior is the
 *  same as that of NvMediaIEPBitsAvailable() when called with
 *  \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER, except that when
 *  \ref NVMEDIA_STATUS_OK is returned, the \a buffer is filled in addition
 *  to the \a numBytes.
 * \param[in] encoder A pointer to the encoder to use.
 * \param[out] numBytes Size of the filled bitstream.
 * \param[in] numBitstreamBuffers The number of bitstreams.
 * \param[in,out] bitstreams A pointer to the buffer to be filled with the encoded data.
 * \param[out] extradata Output extradata required by application.
 *      The output extra data buffer to be filled by the encoder.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 */
NvMediaStatus
NvMediaIEPGetBitsEx(
    NvMediaIEP *encoder,
    uint32_t *numBytes,
    uint32_t numBitstreamBuffers,
    NvMediaBitstreamBuffer *bitstreams,
    void *extradata
);

/**
 * \brief Returns the encode status
 *  and number of bytes available for the next frame (if any).
 *  The specific behavior depends on the specified \ref NvMediaBlockingType.
 *  It is safe to call this function from a separate thread.
 * \param[in] encoder The encoder to use.
 * \param[in] numBytesAvailable
 *      The number of bytes available in the next encoded frame.  This
 *      is valid only when the return value is \ref NVMEDIA_STATUS_OK.
 * \param[in] blockingType Blocking type.
 *      The following are supported blocking types:
 * \n \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER
 *        This type never blocks so \a millisecondTimeout is ignored.
 *        The following are possible return values:  \ref NVMEDIA_STATUS_OK
 *        \ref NVMEDIA_STATUS_PENDING or \ref NVMEDIA_STATUS_NONE_PENDING.
 * \n
 * \n \ref NVMEDIA_ENCODE_BLOCKING_TYPE_IF_PENDING
 *        Same as \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER except that \ref NVMEDIA_STATUS_PENDING
 *        will never be returned.  If an encode is pending this function
 *        will block until the status changes to \ref NVMEDIA_STATUS_OK or until the
 *        timeout has occurred.  Possible return values: \ref NVMEDIA_STATUS_OK,
 *        \ref NVMEDIA_STATUS_NONE_PENDING, \ref NVMEDIA_STATUS_TIMED_OUT.
 * \n
 * \n \ref NVMEDIA_ENCODE_BLOCKING_TYPE_ALWAYS
 *         This function returns only when \ref NVMEDIA_STATUS_OK or
 *         \ref NVMEDIA_STATUS_TIMED_OUT.  It blocks until those conditions
 *         are satisfied.
 * \param[in] millisecondTimeout
 *       Timeout in milliseconds or \ref NVMEDIA_VIDEO_ENCODER_TIMEOUT_INFINITE
 *       if a timeout is not desired.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_PENDING if an encode is in progress but not yet completed.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 * \n \ref NVMEDIA_STATUS_TIMED_OUT if the operation timed out.
 */
NvMediaStatus
NvMediaIEPBitsAvailable(
    NvMediaIEP *encoder,
    uint32_t *numBytesAvailable,
    NvMediaBlockingType blockingType,
    uint32_t millisecondTimeout
);


/**
 * \brief Gets the encoder attribute for the current encoding session.
 * This function can be called after passing the first frame for encoding.
 * It can be used to get header information (SPS/PPS/VPS) for the
 * current encoding session. Additionally, it can be extended for further
 * requirements, by implementing proper data structures.
 *
 * Before calling this function, you must pass the first frame for encoding.
 *
 * \param[in] encoder A pointer to the encoder to use.
 * \param[in] attrType Attribute type as defined in \ref NvMediaEncAttrType.
 * \param[in] attrSize Size of the data structure associated with attribute.
 * \param[out] AttributeData A pointer to data structure associated with the attribute.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameters are NULL.
 */
NvMediaStatus
NvMediaIEPGetAttribute(
    NvMediaIEP *encoder,
    NvMediaEncAttrType attrType,
    uint32_t attrSize,
    void *AttributeData
);

/*
 * \defgroup history_nvmedia_iep History
 * Provides change history for the NvMedia IEP API.
 *
 * \section history_nvmedia_iep Version History
 *
 * <b> Version 1.0 </b> March 14, 2016
 * - Initial release
 *
 * <b> Version 1.1 </b> May 11, 2016
 * - Added \ref NvMediaICPCheckVersion API
 *
 * <b> Version 1.2 </b> May 5, 2017
 * - Added \ref NvMediaIEPGetBitsEx and \ref NvMediaIEPSetInputExtraData API
 * - Added \ref NvMediaIEPGetAttribute
 *
 * <b> Version 2.0 </b> May 9, 2017
 * - Added instance ID parameter to NvMediaIEPCreate() and NvMediaIEPFeedFrame()
 * - optionalDevice parameter is removed from NvMediaIEPCreate()
 * - NvMediaIEPGetVersion() is added to get the version of NvMedia Image Encoder library
 * - NvMediaIEPGetBits() is deprecated. Use NvMediaIEPGetBitsEx() instead.
 * - All NvMedia data types are moved to standard data types
 *
 * <b> Version 2.1 </b> June 30, 2017
 * - Removed \ref NvMediaIEPSetInputExtraData API
 *
 * <b> Version 2.2 </b> Sept 1, 2017
 * - Added NVMEDIA_IMAGE_ENCODE_VP8 in \ref NvMediaIEPType enum
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IEP_H */
