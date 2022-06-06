/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: NvMedia Video Decode Processing API </b>
 *
 * This file contains the \ref video_decoder_api "Video Decode Processing API".
 */

#ifndef _NVMEDIA_VIDDEC_H
#define _NVMEDIA_VIDDEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"
#include "nvmedia_video.h"

/**
 * \defgroup video_decoder_api Video Decoder
 * Defines and manages objects that decode video.
 *
 * The NvMediaVideoDecoder object decodes compressed video data, writing
 * the results to a \ref NvMediaVideoSurface "NvMediaVideoSurface".
 *
 * A specific NvMedia implementation may support decoding multiple
 * types of compressed video data. However, NvMediaVideoDecoder objects
 * are able to decode a specific type of compressed video data.
 * This type must be specified during creation.
 *
 * \ingroup nvmedia_video_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VIDEODEC_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_VIDEODEC_VERSION_MINOR   6

/**
 * \brief To Get the decoding status from HW decoder
 */
typedef struct{
    /** \brief pass hw decode clock value to calculate decode time */
    uint32_t hwClockValue;
    /** \brief non-zero value indicates error occured during decoding (codec-specific) */
    uint16_t decode_error;
    /** \brief number of macroblocks decoded */
    uint32_t decoded_mbs;
    /** \brief number of macroblocks error-concealed */
    uint32_t concealed_mbs;        // number of macroblocks concealed
    /** \brief 32 bits fields, each bit indicate the decoding progress */
    uint32_t decoding_status;
    /** \brief HW decoding time */
    uint32_t hwDecodeTime;
} NvMediaVideoDecodeFrameStatus;

/**
 * \brief Macroblock types
 */
typedef enum {
    /** \brief macroblock type B */
    NVMEDIA_MBTYPE_B,
    /** \brief macroblock type P forward */
    NVMEDIA_MBTYPE_P_FORWARD,
    /** \brief macroblock type P backward */
    NVMEDIA_MBTYPE_P_BACKWARD,
    /** \brief macroblock type I */
    NVMEDIA_MBTYPE_I
} NvMediaMacroBlockType;

/**
 * \brief MB types
 */
typedef enum {
    /** \brief MB type SKIP */
    NVMEDIA_SKIP,
    /** \brief MB type P */
    NVMEDIA_P,
    /** \brief MB type B */
    NVMEDIA_B,
    /** \brief MB type I */
    NVMEDIA_I,
    /** \brief invalid option */
    NVMEDIA_UNKNOWN_TYPE
} NvMedia_MB_Type_enum;

/**
 * \brief MB part
 */
typedef enum {
    /** \brief MB part 16x16 */
    NVMEDIA_PART_16x16,
    /** \brief MB part 16x8 */
    NVMEDIA_PART_16x8,
    /** \brief MB part 8x16 */
    NVMEDIA_PART_8x16,
    /** \brief MB part 8x8 */
    NVMEDIA_PART_8x8,
    /** \brief invalid option */
    NVMEDIA_UNKNOWN_PART
} NvMedia_MB_Part_enum;

/**
 * \brief Per Macroblock header information
 */
typedef struct {
    /** \brief macroblock number */
    uint16_t mbNum;
    /** \brief macroblock type */
    NvMediaMacroBlockType MBType;
    /** \brief forward motion vector in x direction */
    int16_t mv_for_x;
    /** \brief forward motion vector in y direction */
    int16_t mv_for_y;
    /** \brief backward motion vector in x direction */
    int16_t mv_bac_x;
    /** \brief forward motion vector in y direction */
    int16_t mv_bac_y;
    /** \brief qp value */
    uint8_t qp;
    /** \brief mb type */
    NvMedia_MB_Type_enum mb_type;
    /** \brief mb part */
    NvMedia_MB_Part_enum mb_part;
} NvMediaMotionVectorMB_Metadata;

/**
 * \brief Motion vector array to get the required current frame stats.
 */
typedef struct{
    /** \brief FrameNumber in decoder order */
    uint32_t frameNumDecodeOrder;
    /** \brief total number of macroblocks in current frame */
    uint32_t mbCount;
    /** \brief flag to indicate whether motion vector dump is present or not. */
    NvMediaBool  bMVDumpPresent;
    /** \brief pointer to motion vector array */
    NvMediaMotionVectorMB_Metadata *mv;
} NvMediaMotionVectorFrameMetaData;

/**
 * \brief Frame stats structure to get get ring entry idx and motion vector dump.
 *
 * When motion vector dump is enabled then decoder wait for current frame decode to complete
 * and read the motion vector in NvMediaVideoDecoderRenderEx().
 *
 * RingEntryIdx parameter is returned from NvMediaVideoDecoderRenderEx() to get current frame
 * decoding status as specified in \ref NvMediaVideoDecodeFrameStatus
 */
typedef struct{
    /** \brief this index is used to get the required decoded stats of current frame */
    uint32_t uRingEntryIdx;
    /** \brief Will be used in case of H264/HEVC to convey the nearest POC out of RPS/DPB */
    uint32_t uErrorRefPOC;
    /** \brief motion vector dump for current frame */
    NvMediaMotionVectorFrameMetaData mvfData;
} NvMediaVideoDecodeStats;

/**
 * \brief A handle representing a video decoder object.
 */
typedef struct {
    /** \brief Codec type */
    NvMediaVideoCodec codec;
    /** \brief Decoder width */
    uint16_t width;
    /** \brief Decoder height */
    uint16_t height;
    /** \brief Maximum number of reference pictures */
    uint16_t maxReferences;
    /** \brief Instance ID of the decoder */
    NvMediaDecoderInstanceId instanceId;
} NvMediaVideoDecoder;


/**
 * \defgroup decoder_create_flag Decoder Creation Flag
 * Defines decoder flag bit masks for constructing the decoder.
 * @{
 */

/**
 * \hideinitializer
 * \brief Defines 10-bit decode.
 */

#define NVMEDIA_VIDEO_DECODER_10BIT_DECODE (1<<0)

/**
 * \hideinitializer
 * \brief Rec_2020 color format for the decoded surface
 */

#define NVMEDIA_VIDEO_DECODER_PIXEL_REC_2020 (1<<1)

/**
 * \hideinitializer
 * \brief Use 16 bit surfaces if contents is higher than 8 bit.
 */

#define NVMEDIA_VIDEO_DECODER_OUTPUT_16BIT_SURFACES (1<<2)

/**
 * \hideinitializer
 * \brief Create decoder for encrypted content decoding
 */

#define NVMEDIA_VIDEO_DECODER_ENABLE_AES  (1<<3)

/**
 * \hideinitializer
 * \brief Create decoder to output in NV24 format.
 */

#define NVMEDIA_VIDEO_DECODER_NV24_OUTPUT (1<<4)

/**
 * \hideinitializer
 * \brief Enable decoder profiling support
 */

#define NVMEDIA_VIDEO_DECODER_PROFILING   (1<<5)

/**
 * \hideinitializer
 * \brief Enable decoder motion vector dump
 */

#define NVMEDIA_VIDEO_DECODER_DUMP_MV     (1<<6)

/*@} <!-- Ends decoder_create_flag sub-group --> */

/** \brief Gets the version information for the NvMedia Video Decoder library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure to be filled
 * by the function.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */

NvMediaStatus
NvMediaVideoDecoderGetVersion(
    NvMediaVersion *version
);

/** \brief Creates a video decoder object.
 *
 * Creates a \ref NvMediaVideoDecoder object for the specified codec. Each
 * decoder object may be accessed by a separate thread. The object
 * must be destroyed with \ref NvMediaVideoDecoderDestroy(). All surfaces
 * used with the \c NvMediaVideoDecoder must be must obtained by
 * /ref NvMediaSurfaceFormatGetType with:
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR, UINT, 8/10/12, BL)
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, SEMI_PLANAR, UINT, 8/10/12, BL)
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 444, SEMI_PLANAR, UINT, 8/10/12, BL)
 *
 * \param[in] device The \ref NvMediaDevice "device" this video decoder will use.
 * \param[in] codec Codec type. The following types are supported:
 * - \ref NVMEDIA_VIDEO_CODEC_HEVC
 * - \ref NVMEDIA_VIDEO_CODEC_H264
 * - \ref NVMEDIA_VIDEO_CODEC_VC1
 * - \ref NVMEDIA_VIDEO_CODEC_VC1_ADVANCED
 * - \ref NVMEDIA_VIDEO_CODEC_MPEG1
 * - \ref NVMEDIA_VIDEO_CODEC_MPEG2
 * - \ref NVMEDIA_VIDEO_CODEC_MPEG4
 * - \ref NVMEDIA_VIDEO_CODEC_MJPEG
 * - \ref NVMEDIA_VIDEO_CODEC_VP8
 * - \ref NVMEDIA_VIDEO_CODEC_VP9
 * \param[in] width Decoder width in luminance pixels.
 * \param[in] height Decoder height in luminance pixels.
 * \param[in] maxReferences The maximum number of reference frames used.
 * This limits internal allocations.
 * \param[in] maxBitstreamSize The maximum size for bitstream.
 * This limits internal allocations.
 * \param[in] inputBuffering How many frames can be in flight at any given
 * time. If this value is 1, NvMediaVideoDecoderRenderEx() blocks until the
 * previous frame has finished decoding. If this is 2, \c NvMediaVideoDecoderRenderEx
 * blocks if two frames are pending but does not block if one is pending.
 * This value is clamped internally to between 1 and 8.
 * \param[in] flags Set the flags of the decoder.
 * The following flags are supported:
 * \n \ref NVMEDIA_VIDEO_DECODER_10BIT_DECODE
 * \param[in] instanceId The ID of the engine instance.
 * The following instances are supported:
 * \n \ref NVMEDIA_DECODER_INSTANCE_0
 * \n \ref NVMEDIA_DECODER_INSTANCE_1
 * \n \ref NVMEDIA_DECODER_INSTANCE_AUTO
 * \return NvMediaVideoDecoder The new video decoder's handle or NULL if unsuccessful.
 */

NvMediaVideoDecoder *
NvMediaVideoDecoderCreateEx(
    NvMediaDevice *device,
    NvMediaVideoCodec codec,
    uint16_t width,
    uint16_t height,
    uint16_t maxReferences,
    uint64_t maxBitstreamSize,
    uint8_t inputBuffering,
    uint32_t flags,
    NvMediaDecoderInstanceId instanceId
);

/** \brief Destroys a video decoder object.
 * \param[in] decoder The decoder to be destroyed.
 */
void
NvMediaVideoDecoderDestroy(
   NvMediaVideoDecoder *decoder
);

/**
 * \brief Decodes a compressed field/frame and render the result
 *        into a \ref NvMediaVideoSurface "NvMediaVideoSurface".
 * \param[in] decoder The decoder object that will perform the
 *       decode operation.
 * \param[in] target The video surface to render to.
 * \param[in] pictureInfo A (pointer to a) structure containing
 *       information about the picture to be decoded. Note that
 *       the appropriate type of NvMediaPictureInfo* structure must
 *       be provided to match to profile that the decoder was
 *       created for.
 * \param[in] encryptParams A (pointer to a) structure containing
 *       information about encryption parameter used to decrypt the
 *       video content on the fly.
 * \param[in] numBitstreamBuffers The number of bitstream
 *       buffers containing compressed data for this picture.
 * \param[in] bitstreams An array of bitstream buffers.
 * \param[out] FrameStatsDump A (pointer to a) structure containing
 *       frame coding specific informations. This includes frame
 *       type, motion vector dumps,macroblock types and other details.
 * \return \ref NvMediaStatus The completion status of the operation.
 * \param[in] instanceId The ID of the engine instance.
 * The following instances are supported if NVMEDIA_DECODER_INSTANCE_AUTO
 * was used in \ref NvMediaVideoDecoderCreateEx API, else this parameter is ignored:
 * \n \ref NVMEDIA_DECODER_INSTANCE_0
 * \n \ref NVMEDIA_DECODER_INSTANCE_1
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoDecoderRenderEx(
    NvMediaVideoDecoder *decoder,
    NvMediaVideoSurface *target,
    NvMediaPictureInfo *pictureInfo,
    void *encryptParams,
    uint32_t numBitstreamBuffers,
    const NvMediaBitstreamBuffer *bitstreams,
    NvMediaVideoDecodeStats *FrameStatsDump,
    NvMediaDecoderInstanceId instanceId
);

/**
 * \brief This function is intended for use in low-latency decode mode.
 *  It is implemented only for H264 decoder. Error will be returned if it is
 *  called for any other codec.
 *
 *  Each set of buffers should contain exactly 1 slice data.
 *  For first slice of every frame, \ref NvMediaVideoDecoderRenderEx() function should be called.
 *  \ref NvMediaVideoDecoderSliceDecode() function should be called for all subsequent
 *  slices of the frame.
 *
 *  Note that the ucode expects next slice data to be available within certain
 *  time (= 100msec). If data is not available within this time, it is assumed that
 *  the data is lost and error-concealment may be performed on the remaining portion
 *  of the frame.
 *
 * \param[in] decoder The decoder object that will perform the
 *       decode operation.
 * \param[in] target The video surface to render to.
 * \param[in] sliceDecData SliceDecode data info.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */

NvMediaStatus
NvMediaVideoDecoderSliceDecode (
    NvMediaVideoDecoder *decoder,
    NvMediaVideoSurface *target,
    NvMediaSliceDecodeData *sliceDecData
);


/**
 * \brief Retrieves the HW decode status available. This is to be used to get
 *  the decoding status. If application does not need decoding status then no need
 *  to call this function. This function should be called in decode order once
 *  decode is complete for target surface. This can be called from separate thread
 *  in decode order before the same index getting used. Syncronization can be
 *  acheived for \ref NvMediaVideoDecoderRenderEx and \ref
 *  NvMediaVideoDecoderGetFrameDecodeStatus using Semaphore.
 *  Semaphore can be signalled at the begining with inputBuffering times.
 *  Then client can wait on Semaphore before every \ref NvMediaVideoDecoderRenderEx
 *  This Semaphore will be signalled from thread after calling
 *  \ref NvMediaVideoDecoderGetFrameDecodeStatus for frame in decode order.
 *  For example: if inputBuffering is 3 when creating decoder using
 *  \ref NvMediaVideoDecoderCreateEx then following sequence should be followed.
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:0) : ringEntryIdx=0
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:1) : ringEntryIdx=1
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:2) : ringEntryIdx=2
 *  NvMediaVideoDecoderGetFrameDecodeStatus(0)
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=0
 *  NvMediaVideoDecoderGetFrameDecodeStatus(1)
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=1
 *  NvMediaVideoDecoderGetFrameDecodeStatus(2)
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=2
 *  NvMediaVideoDecoderGetFrameDecodeStatus(0)
 *  Another example could be like this for above case
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:0) : ringEntryIdx=0
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:1) : ringEntryIdx=1
 *  NvMediaVideoDecoderGetFrameDecodeStatus(0)
 *  NvMediaVideoDecoderRenderEx(DecodeOrder:2) : ringEntryIdx=2
 *  NvMediaVideoDecoderGetFrameDecodeStatus(1)
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=0
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=1
 *  NvMediaVideoDecoderGetFrameDecodeStatus(2)
 *  NvMediaVideoDecoderRenderEx() : ringEntryIdx=2
 *  NvMediaVideoDecoderGetFrameDecodeStatus(0)
 *
 * \param[in] decoder The decoder object that will perform the
 *       decode operation.
 * \param[in] ringEntryIdx This is decoder order index.
 *       decode operation.
 * \param[out]  FrameStatus A pointer to \ref NvMediaVideoDecodeFrameStatus structure
 *       which will store current decoded frame status.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */

NvMediaStatus
NvMediaVideoDecoderGetFrameDecodeStatus(
    NvMediaVideoDecoder *decoder,
    uint32_t ringEntryIdx,
    NvMediaVideoDecodeFrameStatus *FrameStatus
);

/** \brief NvMediaVideoDecoder get backward updates counters for VP9
 *       adaptive entropy contexts.
 *
 * \param[in] decoder A pointer to the decoder object that performs the
 *       decoding operation.
 * \param[in] backupdates A pointer to a structure that holds the
 *       backward update counters.
 */
NvMediaStatus
NvMediaVideoDecoderGetBackwardUpdates(
    NvMediaVideoDecoder *decoder,
    void *backupdates
);

/*
 * \defgroup history_nvmedia_viddec History
 * Provides change history for the NvMedia Video Decode API.
 *
 * \section history_nvmedia_viddec Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b> April 07, 2017
 * - Added hwClockValue in \ref NvMediaVideoDecodeFrameStatus
 * - Rename NvMediaVideoBackwardUpdates to \ref NvMediaVideoDecoderGetBackwardUpdates
 *
 * <b> Version 1.2 </b> April 18, 2017
 * - Deprecated NvMediaVideoDecoderCreate() and NvMediaVideoDecoderRender()
 * - Added \ref NvMediaVideoDecoderGetVersion()
 * - Added device and instance ID parameters to \ref NvMediaVideoDecoderCreateEx()
 * - Added instanceId parameter to \ref NvMediaVideoDecoderRenderEx()
 * - Added instanceId to \ref NvMediaVideoDecoder object
 * - Changed to use standard data types
 *
 * <b> Version 1.3 </b> May 17, 2017
 * - Added deprecated warning message for \ref NvMediaVideoDecoderSetAttributes
 *
 * <b> Version 1.4 </b> June 05, 2017
 * - Removed \ref -NvMediaVideoDecoderCopySliceData interface
 * - Added \ref NvMediaVideoDecoderSliceDecode interface
 * - Added \ref NvMediaSliceDecodeData structure required for
 *   \ref NvMediaVideoDecoderSliceDecode argument.
 *
 * <b> Version 1.5 </b> June 15, 2017
 * - Deprecated \ref NvMediaVideoDecoderSetAttributes()
 *
 * <b> Version 1.6 </b> July 04, 2017
 * - Added \ref NvMedia_MB_Type_enum enumerator
 * - Added \ref NvMedia_MB_Part_enum enumerator
 * - Added qp, mb_type and mb_part to \ref NvMediaMotionVectorMB_Metadata structure
 */

/** @} <!-- Ends decoder_api Video Decoder --> */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VIDDEC_H */
