/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: NvMedia Video Encode Processing API </b>
 *
 * This file contains the \ref encoder_api "Video Encode Processing API".
 */

#ifndef _NVMEDIA_VEP_H
#define _NVMEDIA_VEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"
#include "nvmedia_video.h"

/**
 * \defgroup encoder_api Video Encoder
 * \ingroup nvmedia_video_top
 * The NvMediaVideoEncoder object takes uncompressed video data and tuns it
 * into a codec specific bitstream. Currently only H.264 encoding is supported.
 *
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VEP_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_VEP_VERSION_MINOR   1

/**
 * \brief Video encoder codec type
 * @ingroup encoder_api
 */
typedef enum {
    /** \brief H.264 codec */
    NVMEDIA_VIDEO_ENCODE_CODEC_H264,
    NVMEDIA_VIDEO_ENCODE_CODEC_HEVC,
    NVMEDIA_VIDEO_ENCODE_CODEC_VP9,
    NVMEDIA_VIDEO_ENCODE_CODEC_VP8
} NvMediaVideoEncodeType;

/**
 * \brief Video encoder object created by \ref NvMediaVideoEncoderCreate.
 * @ingroup encoder_api
 */
typedef struct {
    /** Codec type */
    NvMediaVideoEncodeType codec;
    /** Input surface format */
    NvMediaSurfaceType inputFormat;
    /** Instance ID */
    NvMediaEncoderInstanceId instanceId;
} NvMediaVideoEncoder;


/** \brief Gets the version information for the NvMedia Video Encoder library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure to be filled
 * by the function.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaVideoEncoderGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an encoder object capable of turning a stream of surfaces
 * of the "inputFormat" into a bitstream of the specified "codec".
 * Surfaces are feed to the encoder with \ref NvMediaVideoEncoderFeedFrame
 * and bitstream buffers are retrieved with \ref NvMediaVideoEncoderGetBits.
 * \param[in] device The \ref NvMediaDevice "device" this video encoder will use.
 * \param[in] codec Currently only \ref NVMEDIA_VIDEO_ENCODE_CODEC_H264 is supported.
 * \param[in] initParams Encode parameters.
 * \param[in] inputFormat Must be obtained by /ref NvMediaSurfaceFormatGetType with:
 *      \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR, UINT, 8/10, BL)
 *      \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 444, SEMI_PLANAR, UINT, 8/10, BL)
 * \param[in] maxInputBuffering
 *      This determines how many frames may be in the encode pipeline
 *      at any time.  For example, if maxInputBuffering==1,
 *      \ref NvMediaVideoEncoderFeedFrame will block until the previous
 *      encode has completed.  If maxInputBuffering==2,
 *      \ref NvMediaVideoEncoderFeedFrame will accept one frame while another
 *      is still being encoded by the hardware, but will block if two
 *      are still being encoded.  maxInputBuffering will be clamped between
 *      1 and 16.  This field is ignored for YUV inputs which don't require
 *      a pre-processing pipeline before the encode hardware.
 * \param[in] maxOutputBuffering
 *      This determines how many frames of encoded bitstream can be held
 *      by the NvMediaVideoEncoder before it must be retrieved using
 *      NvMediaVideoEncoderGetBits().  This number must be greater than
 *      or equal to maxInputBuffering and is clamped to between
 *      maxInputBuffering and 16.  If maxOutputBuffering frames worth
 *      of encoded bitstream are yet unretrieved by \ref NvMediaVideoEncoderGetBits
 *      \ref NvMediaVideoEncoderFeedFrame will return
 *      \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING.  One or more frames need to
 *      be retrieved with NvMediaVideoEncoderGetBits() before frame feeding
 *      can continue.
 * \param[in] instanceId The ID of the encoder engine instance. The following
 *      instances are supported:
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_0
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_1
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_AUTO
 * \return \ref NvMediaVideoEncoder The new video encoder's handle or NULL if unsuccessful.
 */
NvMediaVideoEncoder *
NvMediaVideoEncoderCreate(
    NvMediaDevice *device,
    NvMediaVideoEncodeType codec,
    void *initParams,
    NvMediaSurfaceType inputFormat,
    uint8_t maxInputBuffering,
    uint8_t maxOutputBuffering,
    NvMediaEncoderInstanceId instanceId
);

/**
 * \brief Destroys an NvMediaEncoder object.
 * \param[in] encoder A pointer to the encoder to destroy.
 */
void NvMediaVideoEncoderDestroy(NvMediaVideoEncoder *encoder);

/**
 * \brief Encodes the specified "frame".  NvMediaVideoEncoderFeedFrame
 *  returns \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if \ref NvMediaVideoEncoderGetBits
 *  has not been called frequently enough and the maximum internal
 *  bitstream buffering (determined by "maxOutputBuffering" passed to
 *  \ref NvMediaVideoEncoderCreate) has been exhausted.
 * \param[in] encoder A pointer to the encoder to use.
 * \param[in] frame
 *      This must be of the same sourceType as the NvMediaEncoder.
 *      There is no limit on the size of this surface.  The
 *      source rectangle specified by "sourceRect" will be scaled
 *      to the stream dimensions.
 * \param[in] sourceRect
 *       This rectangle on the source will be scaled to the stream
 *       dimensions.  If NULL, a rectangle the full size of the source
 *       surface is implied.  The source may be flipped horizontally
 *       or vertically by swapping the left and right or top and bottom
 *       coordinates. This parameter is valid only for RGB type input
 *       surfaces.
 * \param[in] picParams Picture parameters used for the frame.
 * \param[in] instanceId The ID of the encoder engine instance.
 * The following instances are supported if NVMEDIA_ENCODER_INSTANCE_AUTO
 * was used in \ref NvMediaVideoEncoderCreate API, else this parameter is ignored:
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_0
 *      \n \ref NVMEDIA_ENCODER_INSTANCE_1
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 */
NvMediaStatus
NvMediaVideoEncoderFeedFrame(
    NvMediaVideoEncoder *encoder,
    NvMediaVideoSurface *frame,
    NvMediaRect *sourceRect,
    void *picParams,
    NvMediaEncoderInstanceId instanceId
);

/**
 * \brief Sets the encoder configuration.
 * This configuration goes into effect only at
 * the start of the next GOP.
 * \param[in] encoder A pointer to the encoder to use.
 * \param[in] configuration Configuration data.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 */
NvMediaStatus
NvMediaVideoEncoderSetConfiguration(
    NvMediaVideoEncoder *encoder,
    void *configuration
);

/**
 * \brief NvMediaVideoEncoderGetBits returns a frame's worth of bitstream
 *  into the provided "buffer".  "numBytes" returns the size of this
 *  bitstream.  It is safe to call this function from a separate thread.
 *  The return value and behavior is the same as that of
 *  \ref NvMediaVideoEncoderBitsAvailable when called with \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER
 *  except that when \ref NVMEDIA_STATUS_OK is returned, the "buffer" will be
 *  filled in addition to the "numBytes".
 * \param[in] encoder A pointer to the encoder to use.
 * \param[in] numBytes
 *       Returns the size of the filled bitstream.
 * \param[in] buffer
 *      The buffer to be filled with the encoded data.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_PENDING if an encode is in progress but not yet completed.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING if no encode is in progress.
 */
NvMediaStatus
NvMediaVideoEncoderGetBits(
    NvMediaVideoEncoder *encoder,
    uint32_t *numBytes,
    void *buffer
);

/**
 * \brief Returns the encode status
 *  and number of bytes available for the next frame (if any).
 *  The specific behavior depends on the specified \ref NvMediaBlockingType.
 *  It is safe to call this function from a separate thread.
 * \param[in] encoder A pointer to the encoder to use.
 * \param[out] numBytesAvailable A pointer to
 *      the number of bytes available in the next encoded frame.  This
 *      is valid only when the return value is \ref NVMEDIA_STATUS_OK.
 * \param[in] blockingType The blocking types.
 *      The following are supported blocking types:
 * \n \ref NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER
 *        This type never blocks so "millisecondTimeout" is ignored.
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
 *         This function will return only \ref NVMEDIA_STATUS_OK or
 *         \ref NVMEDIA_STATUS_TIMED_OUT.  It will block until those conditions.
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
NvMediaVideoEncoderBitsAvailable(
    NvMediaVideoEncoder *encoder,
    uint32_t *numBytesAvailable,
    NvMediaBlockingType blockingType,
    uint32_t millisecondTimeout
);

/** @} <!-- ends continuation of encoder_api group --> */

/*
 * \defgroup history_nvmedia_vep History
 * Provides change history for the NvMedia Video Encode API.
 *
 * \section history_nvmedia_vcp Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b/> April 18, 2017
 * - Added \ref NvMediaVideoEncodeType
 * - Added \ref NvMediaVideoEncoderGetVersion
 * - Added instance ID parameter to \ref NvMediaVideoEncoderCreate()
 * - Added instance ID parameter to \ref NvMediaVideoEncoderFeedFrame()
 * - Added instanceId to \ref NvMediaVideoEncoder object
 * - Changed \ref NvMediaVideoEncoderCreate codec parameter to
 *   \ref NvMediaVideoEncodeType
 * - Changed to use standard data type
 *
 * <b> Version 2.0 </b> May 9, 2017
 * - Removed optionalDevice param from NvMediaVideoEncoderCreate()
 *
 * <b> Version 2.1 </b> Sept 1, 2017
 * - Added NVMEDIA_VIDEO_ENCODE_CODEC_VP8 in \ref NvMediaVideoEncodeType enum
 */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VEP_H */
