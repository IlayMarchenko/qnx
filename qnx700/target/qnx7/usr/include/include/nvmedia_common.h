/*
 * Copyright (c) 2017-2018 NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */


/**
 * \file
 * \brief <b> NVIDIA Media Interface: Common Types for Video/Image Encode/Decode</b>
 *
 * @b Description: This file contains common types and definitions for image and video
 * decode and encode operations.
 */

#ifndef _NVMEDIA_COMMON_H
#define _NVMEDIA_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"

/**
 * \defgroup common_types_top Video and Image Encode/Decode: Common Types
 * \ingroup nvmedia_common_top
 *
 * \brief Defines common types and declarations for image and video
 * decode and encode operations.
 * @{
 */

/**
 * \defgroup decoder_api Video Decoder: Common Types
 * \ingroup nvmedia_video_top
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
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_COMMON_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_COMMON_VERSION_MINOR   21

/**
 * \hideinitializer
 * \brief Specifies the minimum number of capture buffers.
 */
#define NVMEDIA_MIN_CAPTURE_FRAME_BUFFERS   2
/**
 * \hideinitializer
 * \brief Maximum number of capture buffers
 */
#define NVMEDIA_MAX_CAPTURE_FRAME_BUFFERS   32

/**
 * \brief Specifies the decoder instance ID
 */
typedef enum  {
    /** \brief Specifies the decoder instance ID 0 */
    NVMEDIA_DECODER_INSTANCE_0 = 0,
    /** \brief Specifies the decoder instance ID 1 */
    NVMEDIA_DECODER_INSTANCE_1,
   /** \brief Specifies that the decoder instance ID
    * can be set dynamically during decode
    */
    NVMEDIA_DECODER_INSTANCE_AUTO,
} NvMediaDecoderInstanceId;

/**
 * \brief Specifies the encoder instance ID
 */
typedef enum {
    /** \brief Specifies the encoder instance ID 0 */
    NVMEDIA_ENCODER_INSTANCE_0 = 0,
    /** \brief Specifies the encoder instance ID 1 */
    NVMEDIA_ENCODER_INSTANCE_1,
   /** \brief Specifies that the encoder instance ID
    * can be set dynamically during encode
    */
    NVMEDIA_ENCODER_INSTANCE_AUTO,
} NvMediaEncoderInstanceId;

/**
 * \brief Video codec type
 */
typedef enum {
    /** \brief H.264 codec */
    NVMEDIA_VIDEO_CODEC_H264,
    /** \brief VC-1 simple and main profile codec */
    NVMEDIA_VIDEO_CODEC_VC1,
    /** \brief VC-1 advanced profile codec */
    NVMEDIA_VIDEO_CODEC_VC1_ADVANCED,
    /** \brief MPEG1 codec */
    NVMEDIA_VIDEO_CODEC_MPEG1,
    /** \brief MPEG2 codec */
    NVMEDIA_VIDEO_CODEC_MPEG2,
    /** \brief MPEG4 Part 2 codec */
    NVMEDIA_VIDEO_CODEC_MPEG4,
    /** \brief MJPEG codec */
    NVMEDIA_VIDEO_CODEC_MJPEG,
    /** \brief VP8 codec */
    NVMEDIA_VIDEO_CODEC_VP8,
    /** \brief H265 codec */
    NVMEDIA_VIDEO_CODEC_HEVC,
    /** \brief VP9 codec */
    NVMEDIA_VIDEO_CODEC_VP9,
    /** \brief H.264 Multiview Video Coding codec */
    NVMEDIA_VIDEO_CODEC_H264_MVC,
    /** \brief H265 Multiview Video Coding codec */
    NVMEDIA_VIDEO_CODEC_HEVC_MV,
} NvMediaVideoCodec;

/**
 * \brief Holds an application data buffer containing compressed video
 *        data.
 */
typedef struct {
    /** A pointer to the bitstream data bytes. */
    uint8_t *bitstream;
    /** The number of data bytes */
    uint32_t bitstreamBytes;
    /** Size of bitstream array */
    uint32_t bitstreamSize;
} NvMediaBitstreamBuffer;

/**
 * \brief NAL types found in a bitstream packet. This is used for TK1 H264 OTF cases.
 */
enum
{
    /** \brief slice header data present or not */
    NVMEDIA_SLH_PRESENT = 0x1,
    /** \brief sequence header data present or not */
    NVMEDIA_SPS_PRESENT = 0x2,
    /** \brief picture header data present or not */
    NVMEDIA_PPS_PRESENT = 0x4
};

/**
 * \brief A generic "picture information" pointer type.
 *
 * This type serves solely to document the expected usage of a
 * generic (void *) function parameter. In actual usage, the
 * application is expected to physically provide a pointer to an
 * instance of one of the "real" NvMediaPictureInfo* structures,
 * picking the type appropriate for the decoder object in
 * question.
 */
typedef void NvMediaPictureInfo;

/**
 * \brief A generic "reference surface" pointer type.
 *
 * This type serves solely to document the expected usage of a
 * generic (void *) function parameter. In actual usage, the
 * application is expected to physically provide a pointer to an
 * instance of NvMediaVideoSurface or NvMediaImage, depending on
 * the type of decoder API used.
 */

typedef void NvMediaRefSurface;

/*@} <!-- Ends decoder_api Video Decoder --> */

/**
 * \defgroup h264decoder_api H.264 Structures
 * \ingroup basic_api_top
 * Provides structures for defining the H.264 reference frame.
 * @{
 */

/**
 * \brief Information about an H.264 reference frame
 *
 * @note References to "copy of bitstream field" in the field descriptions may:
 * - Refer to data literally parsed from the bitstream or
 * - Be derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * The surface that contains the reference image.
     * Set to NULL for unused entries.
     */
    NvMediaRefSurface   *surface;
    /** Is this a long term reference (else short term). */
    NvMediaBool         is_long_term;
    /**
     * Is the top field used as a reference.
     * Set to NVMEDIA_FALSE for unused entries.
     */
    NvMediaBool         top_is_reference;
    /**
     * Is the bottom field used as a reference.
     * Set to NVMEDIA_FALSE for unused entries.
     */
    NvMediaBool         bottom_is_reference;
    /** [0]: top, [1]: bottom */
    int32_t                 field_order_cnt[2];
    /**
     * Copy of the H.264 bitstream field:
     * frame_num from slice_header for short-term references,
     * LongTermPicNum from decoding algorithm for long-term references.
     */
    uint16_t     FrameIdx;

    /** Parser only: Non-existing reference frame flag
     * (corresponding PicIdx should be set to -1)
     */
    uint16_t     not_existing;
} NvMediaReferenceFrameH264;

/**  \brief Maximum user defined sei payload size */
#define MAX_USER_SEI_PAYLOAD    128

/**
 * \brief H.264 SEI payload information
 *  Used by the parser only.
 *
 */
typedef struct {
    /** Indicate the type of packing arrangement of the frames,
        as described in Annex D */
    uint8_t frame_packing_arrangement_type;
    /** Indicate whether each colour component plane of each consituent
        frame is quincunx sampled or not, as described in Annex D */
    uint8_t quincunx_sampling_flag;
    /** Indicates the intended interpretation of the constituent frames,
        as described in Annex D */
    uint8_t content_interpretation_flag;
    /** Indicates that whether one of the two constituent frames is
        spatially flipped relative to its intended orientation for
        display, as described in Annex D */
    uint8_t spatial_flipping_flag;
    /** Indicates which one of the two constituent frames is flipped,
        as described in Annex D */
    uint8_t frame0_flipped_flag;
    /** Indicates whether all pictures in the current coded video sequence
        are coded as complementary field pairs, as described in Annex D */
    uint8_t field_views_flag;
    /** Indicate whether current frame is frame 0, as described in Annex D */
    uint8_t current_frame_is_frame0_flag;
    /** Flag whether stereo is enabled or not */
    NvMediaBool bStereoEnabled;
    /** Specify the length of user data unregistered SEI message,
        as described in Annex D */
    uint32_t uUserSeiPayloadLength;
    /** Holds user data unregistered SEI message, as described in Annex D */
    uint8_t UserDefinedSeiPayload[MAX_USER_SEI_PAYLOAD];
} NvMediaSEIPayloadH264;

/**
 * \brief Picture parameter information for an H.264 picture.
 *
 * @note The \ref referenceFrames array must contain the "DPB" as
 * defined by the H.264 specification. In particular, once a
 * reference frame has been decoded to a surface, that surface must
 * continue to appear in the DPB until no longer required to predict
 * any future frame. Once a surface is removed from the DPB, it can
 * no longer be used as a reference, unless decoded again.
 *
 * Also note that only surfaces previously generated using \ref
 * NvMediaVideoDecoderRenderEx may be used as reference frames.
 *
 * @note References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /** [0]: top, [1]: bottom */
    int32_t            field_order_cnt[2];
    /** Will the decoded frame be used as a reference later. */
    NvMediaBool    is_reference;

    /** Copy of the H.264 bitstream field. */
    uint16_t chroma_format_idc;
    /** Copy of the H.264 bitstream field. */
    uint16_t frame_num;
    /** Copy of the H.264 bitstream field. */
    uint8_t  field_pic_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  bottom_field_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_frames;
    /** Copy of the H.264 bitstream field. */
    uint8_t  mb_adaptive_frame_field_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  constrained_intra_pred_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  weighted_pred_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  weighted_bipred_idc;
    /** Copy of the H.264 bitstream field. */
    uint8_t  frame_mbs_only_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  transform_8x8_mode_flag;
    /** Copy of the H.264 bitstream field. */
    int8_t           chroma_qp_index_offset;
    /** Copy of the H.264 bitstream field. */
    int8_t           second_chroma_qp_index_offset;
    /** Copy of the H.264 bitstream field. */
    int8_t           pic_init_qp_minus26;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_idx_l0_active_minus1;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_ref_idx_l1_active_minus1;
    /** Copy of the H.264 bitstream field. */
    uint8_t  log2_max_frame_num_minus4;
    /** Copy of the H.264 bitstream field. */
    uint8_t  pic_order_cnt_type;
    /** Copy of the H.264 bitstream field. */
    uint8_t  log2_max_pic_order_cnt_lsb_minus4;
    /** Copy of the H.264 bitstream field. */
    uint8_t  delta_pic_order_always_zero_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  direct_8x8_inference_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  entropy_coding_mode_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  pic_order_present_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  deblocking_filter_control_present_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  redundant_pic_cnt_present_flag;
    /** Copy of the H.264 bitstream field. */
    uint8_t  num_slice_groups_minus1;
    /** Copy of the H.264 bitstream field. */
    uint8_t  slice_group_map_type;
    /** Copy of the H.264 bitstream field. */
    uint32_t   slice_group_change_rate_minus1;
    /** Slice group map */
    uint8_t *slice_group_map;
    /** Copy of the H.264 bitstream field. */
    uint8_t fmo_aso_enable;
    /** Copy of the H.264 bitstream field. */
    uint8_t scaling_matrix_present;

    /** Copy of the H.264 bitstream field, converted to raster order. */
    uint8_t  scaling_lists_4x4[6][16];
    /** Copy of the H.264 bitstream field, converted to raster order. */
    uint8_t  scaling_lists_8x8[2][64];

    /** See \ref NvMediaPictureInfoH264 for instructions regarding this field. */
    NvMediaReferenceFrameH264 referenceFrames[16];
    /** Number of slices in this picture. \a nNumSlices entries contain the offset
     of each slice within the bitstream data buffer. Required for nvdec. */
    uint32_t nNumSlices;
    /** Passing NULL for \a pSliceDataOffsets disables error-concealment. */
    uint32_t *pSliceDataOffsets;
    /** 0:FrameType_B  1:FrameType_P  2:FrameType_I */
    uint8_t frameType;

    /** MVC extension */
    struct {
        /** Copy of the H.264 mvc bitstream field. */
        uint16_t num_views_minus1;
        /** Copy of the H.264 mvc bitstream field. */
        uint16_t view_id;
        /** Copy of the H.264 mvc bitstream field. */
        uint8_t inter_view_flag;
        /** Copy of the H.264 mvc bitstream field. */
        uint8_t num_inter_view_refs_l0;
        /** Copy of the H.264 mvc bitstream field. */
        uint8_t num_inter_view_refs_l1;
        /** Copy of the H.264 mvc bitstream field. */
        uint8_t MVCReserved8Bits;
        /** Copy of the H.264 mvc bitstream field. */
        uint16_t InterViewRefsL0[16];
        /** Copy of the H.264 mvc bitstream field. */
        uint16_t InterViewRefsL1[16];
    } mvcext;

    /** Parser only: SEI payload info */
    NvMediaSEIPayloadH264 seiPayloadInfo;
    /** Copy of the H.264 bitstream field. Required for OTF */
    uint32_t pic_width_in_mbs_minus1;
    /** Copy of the H.264 bitstream field. Required for OTF */
    uint32_t pic_height_in_map_units_minus1;
    /** Copy of the H.264 bitstream field. Required for OTF */
    int32_t last_sps_id;
    /** Copy of the H.264 bitstream field. Required for OTF */
    int32_t last_pps_id;
    /** Copy of the H.264 bitstream field, qpprime_y_zero_transform_bypass_flag */
    int32_t qpprime_y_zero_transform_bypass_flag;
} NvMediaPictureInfoH264;

/** @} <!-- Ends h264decoder_api Basic Types sub-group --> */

/**
 * \defgroup h265decoder_api H.265 Structures
 * \ingroup basic_api_top
 * Provides structures for defining the H.265 reference frame.
 * @{
 */

/**
 * \brief Mastering display data for an H.265 picture.
 *  Used by the parser only.
 *
 *  Array indexing 0 : G, 1 : B, 2 : R
 */
typedef struct
{
    /** Normalized x chromaticity cordinate. It shall be in the range of 0 to 50000 */
    uint16_t display_primaries_x[3];
    /** Normalized y chromaticity cordinate. It shall be in the range of 0 to 50000 */
    uint16_t display_primaries_y[3];
    /** Normalized x chromaticity cordinate of white point of mastering display */
    uint16_t white_point_x;
    /** Normalized y chromaticity cordinate of white point of mastering display */
    uint16_t white_point_y;
    /** Nominal maximum display luminance in units of 0.0001 candelas per square metre */
    uint32_t max_display_parameter_luminance;
    /** Nominal minimum display luminance in units of 0.0001 candelas per square metre */
    uint32_t min_display_parameter_luminance;
} NvMediaMasteringDisplayData;


/** \brief slice level data used with slice level decoding
 *
 * @note This slice level information is passed with \ref NvMediaParserClientCb::SliceDecode
 * callback. Client will call NvMediaVideoDecoderSliceDecode() to
 * program hardware for decoding current slice. This feature is available
 * only for specific hardware/codecs.
 */
typedef struct
{
    /** Bitstream data*/
    /** Number of bytes in bitstream data buffer */
    uint32_t uBitstreamDataLen;
    /** Ptr to bitstream data for this picture (slice-layer) */
    uint8_t *pBitstreamData;
    /** Number of slices in this SliceData */
    uint32_t uNumSlices;
    /** If not NULL, nNumSlices entries, contains offset of each slice within the bitstream data buffer */
    uint32_t *pSliceDataOffsets;
    /** Number of CTB present in this CTB */
    uint32_t uCTBCount;
    /** CTB number of first CTB in the slice data */
    uint32_t uFirstCtbAddr;
    /** First slice flag: whether this SliceData contains first slice of frame */
    NvMediaBool bFirstSlice;
    /** Last slice flag: whether this SliceData contains last slice of frame */
    NvMediaBool bLastSlice;
    /** Error flag if some parsing error detected */
    NvMediaBool bErrorFlag;
} NvMediaSliceDecodeData;

/**
 * \brief Holds picture parameter information for an H.265 picture.
 *
 * \note The NvMediaPictureInfoH264.referenceFrames array must contain the "DPB" as
 * defined by the H.265 specification. Once a
 * reference frame has been decoded to a surface, that surface must
 * continue to appear in the DPB until it is no longer required to predict
 * any future frame. Once a surface is removed from the DPB, it is
 * no longer used as a reference unless decoded again.
 * Only surfaces previously generated using \ref
 * NvMediaVideoDecoderRenderEx may be used as reference frames.
 * References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    // sps
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t pic_width_in_luma_samples;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t pic_height_in_luma_samples;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_min_luma_coding_block_size_minus3;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_diff_max_min_luma_coding_block_size;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_min_transform_block_size_minus2;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_diff_max_min_transform_block_size;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pcm_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_min_pcm_luma_coding_block_size_minus3;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_diff_max_min_pcm_luma_coding_block_size;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t bit_depth_luma;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t bit_depth_chroma;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pcm_sample_bit_depth_luma_minus1;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pcm_sample_bit_depth_chroma_minus1;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pcm_loop_filter_disabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t strong_intra_smoothing_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t max_transform_hierarchy_depth_intra;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t max_transform_hierarchy_depth_inter;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t amp_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t separate_colour_plane_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_max_pic_order_cnt_lsb_minus4;
    /** Holds a copy of the H.265 bitstream field. */

    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_short_term_ref_pic_sets;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t long_term_ref_pics_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_long_term_ref_pics_sps;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t sps_temporal_mvp_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t sample_adaptive_offset_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t scaling_list_enable_flag;
    /** Holds a copy of the chroma_format_idc. */
    uint8_t chroma_format_idc;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t reserved1[3];

    // pps
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t dependent_slice_segments_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t slice_segment_header_extension_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t sign_data_hiding_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t cu_qp_delta_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t diff_cu_qp_delta_depth;
    /** Holds a copy of the H.265 bitstream field. */
    int8_t init_qp_minus26;
    /** Holds a copy of the H.265 bitstream field. */
    int8_t pps_cb_qp_offset;
    /** Holds a copy of the H.265 bitstream field. */
    int8_t pps_cr_qp_offset;

    /** Holds a copy of the H.265 bitstream field. */
    uint8_t constrained_intra_pred_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t weighted_pred_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t weighted_bipred_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t transform_skip_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t transquant_bypass_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t entropy_coding_sync_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t log2_parallel_merge_level_minus2;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_extra_slice_header_bits;

    /** Holds a copy of the H.265 bitstream field. */
    uint8_t loop_filter_across_tiles_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t loop_filter_across_slices_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t output_flag_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_ref_idx_l0_default_active_minus1;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_ref_idx_l1_default_active_minus1;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t lists_modification_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t cabac_init_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pps_slice_chroma_qp_offsets_present_flag;

    /** Holds a copy of the H.265 bitstream field. */
    uint8_t deblocking_filter_control_present_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t deblocking_filter_override_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t pps_deblocking_filter_disabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    int8_t pps_beta_offset_div2;
    /** Holds a copy of the H.265 bitstream field. */
    int8_t pps_tc_offset_div2;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t tiles_enabled_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t uniform_spacing_flag;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_tile_columns_minus1;
    /** Holds a copy of the H.265 bitstream field. */
    uint8_t num_tile_rows_minus1;

    /** Holds a copy of the H.265 bitstream field. */
    uint16_t column_width_minus1[22];
    /** Holds a copy of the H.265 bitstream field. */
    uint16_t row_height_minus1[20];

    // RefPicSets
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t iCur;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t IDRPicFlag;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t RAPPicFlag;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumDeltaPocsOfRefRpsIdx;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumPocTotalCurr;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumPocStCurrBefore;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumPocStCurrAfter;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumPocLtCurr;
    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumBitsToSkip;
    /** Holds a copy of the H.265 bitstream field. */
    int32_t CurrPicOrderCntVal;
    /**
     * Holds the surface that contains the reference image.
     * Set to NULL for unused entries.
     */
    NvMediaRefSurface *RefPics[16];
    int32_t PicOrderCntVal[16];
    /** 1 = long-term reference. */
    uint8_t IsLongTerm[16];
    int8_t RefPicSetStCurrBefore[8];
    int8_t RefPicSetStCurrAfter[8];
    int8_t RefPicSetLtCurr[8];

    // scaling lists (diag order)
    /** Holds a copy of the H.265 bitstream field. [matrixId][i]*/
    uint8_t ScalingList4x4[6][16];
    /** Holds a copy of the H.265 bitstream field. [matrixId][i]*/
    uint8_t ScalingList8x8[6][64];
    /** Holds a copy of the H.265 bitstream field. [matrixId][i]*/
    uint8_t ScalingList16x16[6][64];
    /** Holds a copy of the H.265 bitstream field. [matrixId][i]*/
    uint8_t ScalingList32x32[2][64];
    /** Holds a copy of the H.265 bitstream field. [matrixId]*/
    uint8_t ScalingListDCCoeff16x16[6];
    /** Holds a copy of the H.265 bitstream field. [matrixId]*/
    uint8_t ScalingListDCCoeff32x32[2];

    /** Holds a copy of the H.265 bitstream field. */
    uint32_t NumDeltaPocs[64];

    uint8_t sps_range_extension_present_flag;
    // sps extension HEVC-main 444
    /** Holds the SPS extension for \a transform_skip_rotation_enabled_flag. */
    uint8_t transformSkipRotationEnableFlag;
    /** Holds the SPS extension for \a transform_skip_context_enabled_flag. */
    uint8_t transformSkipContextEnableFlag;
    /** Holds the SPS \a implicit_rdpcm_enabled_flag. */
    uint8_t implicitRdpcmEnableFlag;
    /** Holds the SPS \a explicit_rdpcm_enabled_flag. */
    uint8_t explicitRdpcmEnableFlag;
    /** Holds the SPS \a extended_precision_processing_flag; always 0 in current profile. */
    uint8_t extendedPrecisionProcessingFlag;
    /** Holds the SPS \a intra_smoothing_disabled_flag. */
    uint8_t intraSmoothingDisabledFlag;
    /** Holds the SPS \a high_precision_offsets_enabled_flag. */
    uint8_t highPrecisionOffsetsEnableFlag;
    /** Holds the SPS \a fast_rice_adaptation_enabled_flag. */
    uint8_t fastRiceAdaptationEnableFlag;
    /** Holds the SPS \a cabac_bypass_alignment_enabled_flag; always 0 in current profile. */
    uint8_t cabacBypassAlignmentEnableFlag;
    /** Holds the SPS \a intraBlockCopyEnableFlag; always 0 not currently used by the spec. */
    uint8_t intraBlockCopyEnableFlag;

    uint8_t pps_range_extension_present_flag;
    // pps extension HEVC-main 444
    /** Holds the PPS extension \a log2_max_transform_skip_block_size_minus2, 0...5 */
    uint8_t log2MaxTransformSkipSize;
    /** Holds the PPS \a cross_component_prediction_enabled_flag. */
    uint8_t crossComponentPredictionEnableFlag;
    /** Holds the PPS \a chroma_qp_adjustment_enabled_flag .*/
    uint8_t chromaQpAdjustmentEnableFlag;
    /** Holds the PPS \a diff_cu_chroma_qp_adjustment_depth, 0...3 */
    uint8_t diffCuChromaQpAdjustmentDepth;
    /** Holds the PPS \a chroma_qp_adjustment_table_size_minus1+1, 1...6 */
    uint8_t chromaQpAdjustmentTableSize;
    /** Holds the PPS \a log2_sao_offset_scale_luma, max(0,bitdepth-10), maxBitdepth 16 for future. */
    uint8_t log2SaoOffsetScaleLuma;
    /** Holds the PPS \a log2_sao_offset_scale_chroma. */
    uint8_t log2SaoOffsetScaleChroma;
    /** Holds -[12,+12]. */
    int8_t cb_qp_adjustment[6];
    /** Holds -[12,+12]. */
    int8_t cr_qp_adjustment[6];
    /** Ensures alignment to 4 bytes. */
    uint8_t reserved2;
    /** 0:FrameType_B  1:FrameType_P  2:FrameType_I */
    uint8_t frameType;

    /** Parser Only: Flag to indicated mastering display data is present */
    uint8_t masterin_display_data_present;
    /** Parser Only: Mastering display data if present */
    NvMediaMasteringDisplayData MasteringDispData;
    /** Flag to indicate slice decode is enabled */
    NvMediaBool  bSliceDecEnable;
    /** Slice decode data when Slice decode is enabled */
    NvMediaSliceDecodeData sliceDecData;

    /** Holds multiview video extensions. */
    struct {
        /** Indicates hecv-mv is present in the stream. */
        uint32_t mv_hevc_enable;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t nuh_layer_id;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t default_ref_layers_active_flag;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t NumDirectRefLayers;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t max_one_active_ref_layer_flag;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t NumActiveRefLayerPics;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t poc_lsb_not_present_flag;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t  NumActiveRefLayerPics0;
        /** Holds a copy of the H.265-MV bitstream field. */
        uint32_t  NumActiveRefLayerPics1;
        /** Holds a copy of the H.265-MV bitstream field. */
        int32_t  RefPicSetInterLayer0[32];
        /** Holds a copy of the H.265-MV bitstream field. */
        int32_t  RefPicSetInterLayer1[32];
    } mvext;
} NvMediaPictureInfoH265;
/** @} <!-- Ends h265decoder_api Basic Types sub-group --> */

/**
 * \defgroup mpeg1and2decoder_api MPEG-1 and MPEG-2 Structures
 * \ingroup basic_api_top
 * Provides a structure for defining the MPEG-1 and MPEG-2 picture parameter
 * information.
 * @{
 */

/**
 * \brief Holds picture parameter information for an MPEG 1 or MPEG 2
 *        picture.
 *
 * @note References to "copy of bitstream field" in the field descriptions
 * may refer to data literally parsed from the bitstream, or derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *forward_reference;
    /**
     * Reference used by B frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *backward_reference;

    /** Holds a copy of the MPEG bitstream field. */
    uint8_t picture_structure;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t picture_coding_type;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t intra_dc_precision;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t frame_pred_frame_dct;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t concealment_motion_vectors;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t intra_vlc_format;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t alternate_scan;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t q_scale_type;
    /** Holds a copy of the MPEG bitstream field. */
    uint8_t top_field_first;
    /** Holds a copy of the MPEG-1 bitstream field. For MPEG-2, set to 0. */
    uint8_t full_pel_forward_vector;
    /** Holds a copy of the MPEG-1 bitstream field. For MPEG-2, set to 0. */
    uint8_t full_pel_backward_vector;
    /**
     * Holds a copy of the MPEG bitstream field.
     * For MPEG-1, fill both horizontal and vertical entries.
     */
    uint8_t f_code[2][2];
    /** Holds a copy of the MPEG bitstream field, converted to raster order. */
    uint8_t intra_quantizer_matrix[64];
    /** Holds a copy of the MPEG bitstream field, converted to raster order. */
    uint8_t non_intra_quantizer_matrix[64];
    /** Holds the number of slices in this picture.
      * \a nNumSlices entries contain the offset
      * of each slice within the bitstream data buffer. Required for nvdec. */
    uint32_t nNumSlices;
    /** Passing NULL for \a pSliceDataOffsets disables error-concealment. */
    uint32_t *pSliceDataOffsets;
    /** Indicates whether the MPEG slices span across multiple rows. */
    uint8_t flag_slices_across_multiple_rows;
} NvMediaPictureInfoMPEG1Or2;

/** @} <!-- Ends mpeg1and2decoder_api MPEG4 and MPEG Structures --> */

/**
 * \defgroup mpeg4part2decoder_api MPEG4 Part 2 Structures
 * \ingroup basic_api_top
 * Provides a structure for defining picture parameters for the
 * MPEG-4 Part 2 picture.
 * @{
 */

/**
 * \brief Holds picture parameter information for an MPEG-4 Part 2 picture.
 *
 * @note References to "copy of bitstream field" in the field descriptions may:
 * - Refer to data literally parsed from the bitstream or
 * - Be derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *forward_reference;
    /**
     * Reference used by B frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *backward_reference;

    /** Holds a copy of the bitstream field. */
    int32_t            trd[2];
    /** Holds a copy of the bitstream field. */
    int32_t            trb[2];
    /** Holds a copy of the bitstream field. */
    uint16_t vop_time_increment_resolution;
    /** Holds a copy of the bitstream field. */
    uint32_t   vop_time_increment_bitcount;
    /** Holds a copy of the bitstream field. */
    uint8_t  vop_coding_type;
    /** Holds a copy of the bitstream field. */
    uint8_t  vop_fcode_forward;
    /** Holds a copy of the bitstream field. */
    uint8_t  vop_fcode_backward;
    /** Holds a copy of the bitstream field. */
    uint8_t  resync_marker_disable;
    /** Holds a copy of the bitstream field. */
    uint8_t  interlaced;
    /** Holds a copy of the bitstream field. */
    uint8_t  quant_type;
    /** Holds a copy of the bitstream field. */
    uint8_t  quarter_sample;
    /** Holds a copy of the bitstream field. */
    uint8_t  short_video_header;
    /** Derived from vop_rounding_type bitstream field. */
    uint8_t  rounding_control;
    /** Holds a copy of the bitstream field. */
    uint8_t  alternate_vertical_scan_flag;
    /** Holds a copy of the bitstream field. */
    uint8_t  top_field_first;
    /** Holds a copy of the bitstream field. */
    uint8_t  intra_quantizer_matrix[64];
    /** Holds a copy of the bitstream field. */
    uint8_t  non_intra_quantizer_matrix[64];
    /** Holds a copy of the bitstream field. */
    uint8_t  data_partitioned;
    /** Holds a copy of the bitstream field. */
    uint8_t  reversible_vlc;
    /** Number of slices in this picture. \a nNumSlices entries contain the offset
     of each slice within the bitstream data buffer. Required for nvdec. */
    uint32_t nNumSlices;
    /** Passing NULL for \a pSliceDataOffsets disables error-concealment. */
    uint32_t *pSliceDataOffsets;

    /** Parser Only: Video object layer width */
    uint16_t video_object_layer_width;
    /** Parser Only: Video object layer height */
    uint16_t video_object_layer_height;
    /** Parser Only: DivX flags */
    uint32_t divx_flags;
    /** Parser only: DivX GMC Concealment
     *  Flag to prevent decoding of non I-VOPs during a GMC sequence
     * and indicate beginning / end of a GMC sequence. */
    NvMediaBool bGMCConceal;
} NvMediaPictureInfoMPEG4Part2;

/** @} <!-- Ends mpeg4part2decoder_api MPEG4 Part 2 structures -> */

/**
 * \defgroup vc1decoder_api VC1 Structures
 * \ingroup nvmedia_video_top
 * Defines a structure for defining picture information for a VC1 picture.
 * @{
 */

/**
 * \brief Holds picture parameter information for a VC1 picture.
 *
 * @note References to "copy of bitstream field" in the field descriptions may:
 * - Refer to data literally parsed from the bitstream or
 * - Be derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /**
     * Reference used by B and P frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *forward_reference;
    /**
     * Reference used by B frames.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *backward_reference;
    /**
     * Reference used for range mapping.
     * Set to NULL when not used.
     */
    NvMediaRefSurface *range_mapped;

    /** I=0, P=1, B=3, BI=4  from 7.1.1.4. */
    uint8_t  picture_type;
    /** Progressive=0, Frame-interlace=2, Field-interlace=3; see VC-1 7.1.1.15. */
    uint8_t  frame_coding_mode;
    /** Bottom field flag TopField=0 BottomField=1 */
    uint8_t  bottom_field_flag;


    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.5. */
    uint8_t postprocflag;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.8. */
    uint8_t pulldown;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.9. */
    uint8_t interlace;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.10. */
    uint8_t tfcntrflag;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.11. */
    uint8_t finterpflag;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.1.3. */
    uint8_t psf;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.8. */
    uint8_t dquant;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.3. */
    uint8_t panscan_flag;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.4. */
    uint8_t refdist_flag;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.11. */
    uint8_t quantizer;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.7. */
    uint8_t extended_mv;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.14. */
    uint8_t extended_dmv;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.10. */
    uint8_t overlap;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.9. */
    uint8_t vstransform;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.5. */
    uint8_t loopfilter;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.6. */
    uint8_t fastuvmc;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.12.15. */
    uint8_t range_mapy_flag;
    /** Holds a copy of the VC-1 bitstream field. */
    uint8_t range_mapy;
    /** Holds a copy of the VC-1 bitstream field. See VC-1 6.2.16. */
    uint8_t range_mapuv_flag;
    /** Holds a copy of the VC-1 bitstream field. */
    uint8_t range_mapuv;

    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.10.
     * Only used by simple and main profiles.
     */
    uint8_t multires;
    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.16.
     * Only used by simple and main profiles.
     */
    uint8_t syncmarker;
    /**
     * VC-1 SP/MP range reduction control. See VC-1 J.1.17.
     * Only used by simple and main profiles.
     */
    uint8_t rangered;
    /**
     * Copy of the VC-1 bitstream field. See VC-1 7.1.13
     * Only used by simple and main profiles.
     */
    uint8_t rangeredfrm;
    /**
     * Copy of the VC-1 bitstream field. See VC-1 J.1.17.
     * Only used by simple and main profiles.
     */
    uint8_t maxbframes;
    /** Number of slices in this picture. \a nNumSlices entries contain the offset
     of each slice within the bitstream data buffer. Required for nvdec. */
    uint32_t nNumSlices;
    /** Passing NULL for \a pSliceDataOffsets disables error-concealment. */
    uint32_t *pSliceDataOffsets;

    /** Parser only: Profile */
    uint8_t profile;
    /** Parser only: Actual frame width */
    uint16_t frameWidth;
    /** Parser only: Actual frame height */
    uint16_t frameHeight;
} NvMediaPictureInfoVC1;
/** @} <!-- Ends vc1decoder_api VC1 structures -> */

/**
 * \defgroup vp8decoder_api VP8 Structures
 * \ingroup nvmedia_video_top
 * Defines a structure for defining picture information for a VP8 picture.
 * @{
 */

/**
 * \brief Picture parameter information for a VP8 picture.
 *
 * @note References to "copy of bitstream field" in the field descriptions may:
 * - Refer to data literally parsed from the bitstream or
 * - Be derived from
 * the bitstream using a mechanism described in the specification.
 */
typedef struct {
    /** Last reference frame. */
    NvMediaRefSurface *LastReference;
    /** Golden reference frame. */
    NvMediaRefSurface *GoldenReference;
    /** Alternate reference frame. */
    NvMediaRefSurface *AltReference;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t key_frame;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t version;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t show_frame;
    /**
     * Copy of the VP8 bitstream field.
     * 0 = clamp needed in decoder, 1 = no clamp needed
     */
    uint8_t clamp_type;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t segmentation_enabled;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t update_mb_seg_map;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t update_mb_seg_data;
    /**
     * Copy of the VP8 bitstream field.
     * 0 means delta, 1 means absolute value
     */
    uint8_t update_mb_seg_abs;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t filter_type;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t loop_filter_level;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t sharpness_level;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t mode_ref_lf_delta_enabled;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t mode_ref_lf_delta_update;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t num_of_partitions;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t dequant_index;
    /** Holds a copy of the VP8 bitstream field. */
    int8_t deltaq[5];

    /** Holds a copy of the VP8 bitstream field. */
    uint8_t golden_ref_frame_sign_bias;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t alt_ref_frame_sign_bias;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t refresh_entropy_probs;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t CbrHdrBedValue;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t CbrHdrBedRange;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t mb_seg_tree_probs [3];

    /** Holds a copy of the VP8 bitstream field. */
    int8_t seg_feature[2][4];
    /** Holds a copy of the VP8 bitstream field. */
    int8_t ref_lf_deltas[4];
    /** Holds a copy of the VP8 bitstream field. */
    int8_t mode_lf_deltas[4];

    /** Bits consumed for the current bitstream byte. */
    uint8_t BitsConsumed;
    /** Holds a copy of the VP8 bitstream field. */
    uint8_t AlignByte[3];
    /** Remaining header parition size */
    uint32_t hdr_partition_size;
    /** Start of header partition */
    uint32_t hdr_start_offset;
    /** Offset to byte which is parsed in cpu */
    uint32_t hdr_processed_offset;
    /** Holds a copy of the VP8 bitstream field. */
    uint32_t coeff_partition_size[8];
    /** Holds a copy of the VP8 bitstream field. */
    uint32_t coeff_partition_start_offset[8];
    /** Number of slices in this picture. \a nNumSlices entries contain the offset
     of each slice within the bitstream data buffer. Required for nvdec. */
    uint32_t nNumSlices;
    /** Passing NULL for \a pSliceDataOffsets disables error-concealment. */
    uint32_t *pSliceDataOffsets;
    /** Number of bytes in VP8 Coeff partition (for OTF case) */
    uint32_t uCoeffPartitionDataLen;
    /** Handle to VP8 Coeff partition (for OTF case). */
    uint32_t uCoeffPartitionBufferHandle;

    /** Parser only: RetRefreshGoldenFrame */
    uint32_t RetRefreshGoldenFrame;
    /** Parser only: RetRefreshAltFrame */
    uint32_t RetRefreshAltFrame;
    /** Parser only: RetRefreshLastFrame */
    uint32_t RetRefreshLastFrame;
} NvMediaPictureInfoVP8;
/** @} <!-- Ends vp8decoder_api VP8 Structures -> */

/**
 * \defgroup vp9decoder_api VP9 Structures
 * \ingroup nvmedia_video_top
 * Provides structures for defining the VP9 reference frame.
 * @{
 */

/**
 * \brief Holds VP9 counters for adaptive entropy contexts.
 */
typedef struct {
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t inter_mode_counts[7][3][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t sb_ymode_counts[4][10];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t uv_mode_counts[10][10];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t partition_counts[16][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t switchable_interp_counts[4][3];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t intra_inter_count[4][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t comp_inter_count[5][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t single_ref_count[5][2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t comp_ref_count[5][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t tx32x32_count[2][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t tx16x16_count[2][3];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t tx8x8_count[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t mbskip_count[3][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t joints[4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t sign[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t classes[2][11];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t class0[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t bits[2][10][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t class0_fp[2][2][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t fp[2][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t class0_hp[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t hp[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t countCoeffs[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t countCoeffs8x8[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t countCoeffs16x16[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t countCoeffs32x32[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t countEobs[4][2][2][6][6];
} NvMediaVP9BackwardUpdates;

/**
 * \brief Holds VP9 entropy contexts.
 * Table formatted for 256 bits memory; probs 0 to 7 for all tables followed by
 * probs 8 to N for all tables.
 * Compile with TRACE_PROB_TABLES to print bases for each table.
 */
typedef struct {

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t kf_bmode_prob[10][10][8];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t kf_bmode_probB[10][10][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t ref_pred_probs[3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t mb_segment_tree_probs[7];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t segment_pred_probs[3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t ref_scores[4];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t prob_comppred[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t pad1[9];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t kf_uv_mode_prob[10][8];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t kf_uv_mode_probB[10][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t pad2[6];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t inter_mode_prob[7][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t intra_inter_prob[4];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t uv_mode_prob[10][8];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t tx8x8_prob[2][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t tx16x16_prob[2][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t tx32x32_prob[2][3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t sb_ymode_probB[4][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t sb_ymode_prob[4][8];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t partition_prob[2][16][4];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t uv_mode_probB[10][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t switchable_interp_prob[4][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t comp_inter_prob[5];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t mbskip_probs[3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t pad3[1];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t joints[3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t sign[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t class0[2][1];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t fp[2][3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t class0_hp[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t hp[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t classes[2][10];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t class0_fp[2][2][3];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t bits[2][10];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t single_ref_prob[5][2];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t comp_ref_prob[5];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t pad4[17];

    /** Holds a copy of the VP9 bitstream field. */
    uint8_t probCoeffs[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t probCoeffs8x8[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t probCoeffs16x16[2][2][6][6][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t probCoeffs32x32[2][2][6][6][4];
} NvmediaVP9EntropyProbs;

/**
 * \brief Holds picture parameter information for a VP9 picture.
 *
 * \note References to "copy of bitstream field" in the field descriptions
 * either refer to data literally parsed from the bitstream or data derived from
 * the bitstream using a mechanism described in the specification.
 */

typedef struct {
    /** Holds a pointer to the last reference frame. */
    NvMediaRefSurface *LastReference;
    /** Holds a pointer to the golden reference frame. */
    NvMediaRefSurface *GoldenReference;
    /** Holds a pointer to the alternate reference frame. */
    NvMediaRefSurface *AltReference;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    width;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    height;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref0_width;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref0_height;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref1_width;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref1_height;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref2_width;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t    ref2_height;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t keyFrame;
    /** Holds the depth per pixel. */
    uint32_t bit_depth;
    /** If previous frame is key frame. */
    uint32_t prevIsKeyFrame;
    /** Previous frame is show frame.*/
    uint32_t PrevShowFrame;
    /** Resolution change. */
    uint32_t resolutionChange;
    /** Error Resilient. */
    uint32_t errorResilient;
    /** Intra only. */
    uint32_t intraOnly;
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t frameContextIdx;
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t refFrameSignBias[4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t loopFilterLevel;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t loopFilterSharpness;
    /** Holds a copy of the VP9 bitstream field. */
    int32_t qpYAc;
    /** Holds a copy of the VP9 bitstream field. */
    int32_t qpYDc;
    /** Holds a copy of the VP9 bitstream field. */
    int32_t qpChAc;
    /** Holds a copy of the VP9 bitstream field. */
    int32_t qpChDc;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t lossless;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t transform_mode;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t allow_high_precision_mv;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t allow_comp_inter_inter;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t mcomp_filter_type;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t comp_pred_mode;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t comp_fixed_ref;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t comp_var_ref[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t log2_tile_columns;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t log2_tile_rows;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t segmentEnabled;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t segmentMapUpdate;
    /** Holds a copy of the VP9 bitstream field. */
    int32_t segmentMapTemporalUpdate;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t segmentFeatureMode;
    /** Holds a copy of the VP9 bitstream field. */
    uint8_t segmentFeatureEnable[8][4];
    /** Holds a copy of the VP9 bitstream field. */
    short segmentFeatureData[8][4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t modeRefLfEnabled;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t mbRefLfDelta[4];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t mbModeLfDelta[2];
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t offsetToDctParts;
    /** Holds a copy of the VP9 bitstream field. */
    uint32_t frameTagSize;
    /** Holds a copy of the VP9 bitstream field. */
    NvmediaVP9EntropyProbs entropy;

    /** Parser only: Backward update counts */
    NvMediaVP9BackwardUpdates backwardUpdateCounts;
} NvMediaPictureInfoVP9;
/** @} <!-- Ends vp9decoder_api VP9 Structures --> */

/**
 * \hideinitializer
 * \brief Infinite time-out for \ref NvMediaVideoEncoderBitsAvailable
 */
#define NVMEDIA_VIDEO_ENCODER_TIMEOUT_INFINITE  0xFFFFFFFF

/**
 * \hideinitializer
 * \brief Infinite GOP length so that keyframes are not inserted automatically
 */
#define NVMEDIA_ENCODE_INFINITE_GOPLENGTH       0xFFFFFFFF

/**
 * Holds quantization parameters(QP) value for frames.
 * @ingroup basic_api_top
 */
typedef struct {
    /** QP value for P frames */
    uint32_t qpInterP;
    /** QP value for B frames */
    uint32_t qpInterB;
    /** QP value for Intra frames */
    uint32_t qpIntra;
} NvMediaEncodeQP;

/**
 * Rate Control Modes
 * \hideinitializer
 * @ingroup encoder_api
 */
typedef enum
{
    /** Constant bitrate mode. */
    NVMEDIA_ENCODE_PARAMS_RC_CBR          = 0,
    /** Constant QP mode. */
    NVMEDIA_ENCODE_PARAMS_RC_CONSTQP      = 1,
    /** Variable bitrate mode. */
    NVMEDIA_ENCODE_PARAMS_RC_VBR          = 2,
    /** Variable bitrate mode with MinQP. */
    NVMEDIA_ENCODE_PARAMS_RC_VBR_MINQP    = 3,
    /** Constant bitrate mode with MinQP. */
    NVMEDIA_ENCODE_PARAMS_RC_CBR_MINQP    = 4
} NvMediaEncodeParamsRCMode;

/**
 * Holds rate control configuration parameters.
 * @ingroup basic_api_top
 */
typedef struct {
    /** Holds the rate control mode. */
    NvMediaEncodeParamsRCMode rateControlMode;
    /** Specified number of B frames between two reference frames */
    uint32_t numBFrames;
    union {
        struct {
            /** Holds the average bitrate (in bits/sec) used for encoding. */
            uint32_t averageBitRate;
            /** Holds the VBV(HRD) buffer size. in bits.
               Set 0 to use the default VBV buffer size. */
            uint32_t vbvBufferSize;
            /** Holds the VBV(HRD) initial delay in bits.
               Set 0 to use the default VBV initial delay.*/
            uint32_t vbvInitialDelay;
        } cbr; /**< Parameters for NVMEDIA_ENCODE_PARAMS_RC_CBR mode */
        struct {
            /** Holds the initial QP to be used for encoding, these values would be used for
                all frames in Constant QP mode. */
            NvMediaEncodeQP constQP;
        } const_qp; /**< Parameters for NVMEDIA_ENCODE_PARAMS_RC_CONSTQP mode */
        struct {
            /** Holds the average bitrate (in bits/sec) used for encoding. */
            uint32_t averageBitRate;
            /** Holds the maximum bitrate for the encoded output. */
            uint32_t maxBitRate;
            /** Holds the VBV(HRD) buffer size. in bits.
               Set 0 to use the default VBV buffer size. */
            uint32_t vbvBufferSize;
            /** Holds the VBV(HRD) initial delay in bits.
               Set 0 to use the default VBV initial delay.*/
            uint32_t vbvInitialDelay;
        } vbr; /**< Parameters for NVMEDIA_ENCODE_PARAMS_RC_VBR mode */
        struct {
            /** Holds the average bitrate (in bits/sec) used for encoding. */
            uint32_t averageBitRate;
            /** Holds the maximum bitrate for the encoded output. */
            uint32_t maxBitRate;
            /** Holds the VBV(HRD) buffer size. in bits.
               Set 0 to use the default VBV buffer size. */
            uint32_t vbvBufferSize;
            /** Holds the VBV(HRD) initial delay in bits.
               Set 0 to use the default VBV initial delay.*/
            uint32_t vbvInitialDelay;
            /** Holds the minimum QP used for rate control. */
            NvMediaEncodeQP minQP;
        } vbr_minqp; /**< Parameters for NVMEDIA_ENCODE_PARAMS_RC_VBR_MINQP mode */
        struct {
            /** Holds the average bitrate (in bits/sec) used for encoding. */
            uint32_t averageBitRate;
            /** Holds the VBV(HRD) buffer size. in bits.
               Set 0 to use the default VBV buffer size. */
            uint32_t vbvBufferSize;
            /** Holds the VBV(HRD) initial delay in bits.
               Set 0 to use the default VBV initial delay.*/
            uint32_t vbvInitialDelay;
            /** Holds the minimum QP used for rate control. */
            NvMediaEncodeQP minQP;
        } cbr_minqp; /**< Parameters for NVMEDIA_ENCODE_PARAMS_RC_CBR_MINQP mode */
    } params; /**< Rate Control parameters */
    /** using constant frame QP throughout the current encode frame.
        This is used when when constQP mode rate control is not used */
    NvMediaBool bConstFrameQP;
    /** Holds the max QP for encoding session when external picture RC hint
        is used */
    uint32_t maxSessionQP;
 } NvMediaEncodeRCParams;

/**
 * Blocking type
 * @ingroup encoder_api
 */
typedef enum {
    /** Never blocks */
    NVMEDIA_ENCODE_BLOCKING_TYPE_NEVER,
    /** Block only when operation is pending */
    NVMEDIA_ENCODE_BLOCKING_TYPE_IF_PENDING,
    /** Always blocks */
    NVMEDIA_ENCODE_BLOCKING_TYPE_ALWAYS
} NvMediaBlockingType;

/**
 * @defgroup h264_encoder_api H.264 Encoder
 * The H.264 Encoder API provides basic encode picture types.
 * @ingroup basic_api_top
 * @{
 */

/**
 * Input picture type
 * \hideinitializer
 */
typedef enum {
    /** Auto selected picture type */
    NVMEDIA_ENCODE_PIC_TYPE_AUTOSELECT      = 0,
    /** Forward predicted */
    NVMEDIA_ENCODE_PIC_TYPE_P               = 1,
    /** Bi-directionally predicted picture */
    NVMEDIA_ENCODE_PIC_TYPE_B               = 2,
    /** Intra predicted picture */
    NVMEDIA_ENCODE_PIC_TYPE_I               = 3,
    /** IDR picture */
    NVMEDIA_ENCODE_PIC_TYPE_IDR             = 4,
    /** Starts a new intra refresh cycle if intra
        refresh support is enabled otherwise it
        indicates a P frame */
    NVMEDIA_ENCODE_PIC_TYPE_P_INTRA_REFRESH = 5
} NvMediaEncodePicType;

/**
 * Defines encoding profiles.
 */
typedef enum {
    /** Automatic profile selection */
    NVMEDIA_ENCODE_PROFILE_AUTOSELECT  = 0,

    /** Baseline profile */
    NVMEDIA_ENCODE_PROFILE_BASELINE    = 66,
    /** Main profile */
    NVMEDIA_ENCODE_PROFILE_MAIN        = 77,
    /** Extended profile */
    NVMEDIA_ENCODE_PROFILE_EXTENDED    = 88,
    /** High profile */
    NVMEDIA_ENCODE_PROFILE_HIGH        = 100,
    /** High 444 profile */
    /** H.264 High444 profile support lossless encode (trans-quant bypass) for YUV444
        and YUV420 input. Lossy encode is not supported with High444 profile. */
    NVMEDIA_ENCODE_PROFILE_HIGH444     = 244
} NvMediaEncodeProfile;

/**
 * Defines encoding levels.
 * \hideinitializer
*/
typedef enum {
    /** Automatic level selection */
    NVMEDIA_ENCODE_LEVEL_AUTOSELECT         = 0,

    /** H.264 Level 1 */
    NVMEDIA_ENCODE_LEVEL_H264_1             = 10,
    /** H.264 Level 1b */
    NVMEDIA_ENCODE_LEVEL_H264_1b            = 9,
    /** H.264 Level 1.1 */
    NVMEDIA_ENCODE_LEVEL_H264_11            = 11,
    /** H.264 Level 1.2 */
    NVMEDIA_ENCODE_LEVEL_H264_12            = 12,
    /** H.264 Level 1.3 */
    NVMEDIA_ENCODE_LEVEL_H264_13            = 13,
    /** H.264 Level 2 */
    NVMEDIA_ENCODE_LEVEL_H264_2             = 20,
    /** H.264 Level 2.1 */
    NVMEDIA_ENCODE_LEVEL_H264_21            = 21,
    /** H.264 Level 2.2 */
    NVMEDIA_ENCODE_LEVEL_H264_22            = 22,
    /** H.264 Level 3 */
    NVMEDIA_ENCODE_LEVEL_H264_3             = 30,
    /** H.264 Level 3.1 */
    NVMEDIA_ENCODE_LEVEL_H264_31            = 31,
    /** H.264 Level 3.2 */
    NVMEDIA_ENCODE_LEVEL_H264_32            = 32,
    /** H.264 Level 4 */
    NVMEDIA_ENCODE_LEVEL_H264_4             = 40,
    /** H.264 Level 4.1 */
    NVMEDIA_ENCODE_LEVEL_H264_41            = 41,
    /** H.264 Level 4.2 */
    NVMEDIA_ENCODE_LEVEL_H264_42            = 42,
} NvMediaEncodeLevel;

/**
 * Defines encoding Picture encode flags.
 * \hideinitializer
*/
typedef enum {
    /** Writes the sequence and picture header in encoded bitstream of the
      * current picture. */
    NVMEDIA_ENCODE_PIC_FLAG_OUTPUT_SPSPPS      = (1 << 0),
    /** Indicates change in rate control parameters from the current picture onwards */
    NVMEDIA_ENCODE_PIC_FLAG_RATECONTROL_CHANGE = (1 << 1),
    /** Indicates that this frame is encoded with each slice completely independent of
        other slices in the frame. NVMEDIA_ENCODE_CONFIG_H264_ENABLE_CONSTRANED_ENCODING
        must be set to support this encode mode */
    NVMEDIA_ENCODE_PIC_FLAG_CONSTRAINED_FRAME  = (1 << 2)
} NvMediaEncodePicFlags;

/**
 * Defines encode quality level pre-settings.
 */
typedef enum {
    /** Quality Level 0 Pre-settings */
    NVMEDIA_ENCODE_QUALITY_L0                  = 0,
    /** Quality Level 1 Pre-settings */
    NVMEDIA_ENCODE_QUALITY_L1                  = 1,
    /** Quality Level 2 Pre-settings */
    NVMEDIA_ENCODE_QUALITY_L2                  = 2
} NvMediaEncodeQuality;

/**
 * Defines H.264 entropy coding modes.
 * \hideinitializer
*/
typedef enum {
    /** Entropy coding mode is CAVLC */
    NVMEDIA_ENCODE_H264_ENTROPY_CODING_MODE_CAVLC = 0,
    /** Entropy coding mode is CABAC */
    NVMEDIA_ENCODE_H264_ENTROPY_CODING_MODE_CABAC = 1
} NvMediaEncodeH264EntropyCodingMode;

/**
 * Defines H.264 specific Bdirect modes.
 * \hideinitializer
 */
typedef enum {
    /** Spatial BDirect mode */
    NVMEDIA_ENCODE_H264_BDIRECT_MODE_SPATIAL  = 0,
    /** Disable BDirect mode */
    NVMEDIA_ENCODE_H264_BDIRECT_MODE_DISABLE  = 1,
    /** Temporal BDirect mode */
    NVMEDIA_ENCODE_H264_BDIRECT_MODE_TEMPORAL = 2
} NvMediaEncodeH264BDirectMode;

/**
 * Defines H.264 specific Adaptive Transform modes.
 * \hideinitializer
 */
typedef enum {
    /** Specifies that Adaptive Transform 8x8 mode is auto selected by the encoder driver. */
    NVMEDIA_ENCODE_H264_ADAPTIVE_TRANSFORM_AUTOSELECT = 0,
    /** Specifies that Adaptive Transform 8x8 mode is disabled. */
    NVMEDIA_ENCODE_H264_ADAPTIVE_TRANSFORM_DISABLE    = 1,
    /** Specifies that Adaptive Transform 8x8 mode must be used. */
    NVMEDIA_ENCODE_H264_ADAPTIVE_TRANSFORM_ENABLE     = 2
} NvMediaEncodeH264AdaptiveTransformMode;

/**
 * \hideinitializer
 * Defines motion prediction exclusion flags for H.264.
 */
typedef enum {
    /** Disable Intra 4x4 vertical prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_VERTICAL_PREDICTION               = (1 << 0),
    /** Disable Intra 4x4 horizontal prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_HORIZONTAL_PREDICTION             = (1 << 1),
    /** Disable Intra 4x4 DC prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_DC_PREDICTION                     = (1 << 2),
    /** Disable Intra 4x4 diagonal down left prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_DIAGONAL_DOWN_LEFT_PREDICTION     = (1 << 3),
    /** Disable Intra 4x4 diagonal down right prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_DIAGONAL_DOWN_RIGHT_PREDICTION    = (1 << 4),
    /** Disable Intra 4x4 vertical right prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_VERTICAL_RIGHT_PREDICTION         = (1 << 5),
    /** Disable Intra 4x4 horizontal down prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_HORIZONTAL_DOWN_PREDICTION        = (1 << 6),
    /** Disable Intra 4x4 vertical left prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_VERTICAL_LEFT_PREDICTION          = (1 << 7),
    /** Disable Intra 4x4 horizontal up prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_4x4_HORIZONTAL_UP_PREDICTION          = (1 << 8),

    /** Disable Intra 8x8 vertical prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_VERTICAL_PREDICTION               = (1 << 9),
    /** Disable Intra 8x8 horizontal prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_HORIZONTAL_PREDICTION             = (1 << 10),
    /** Disable Intra 8x8 DC prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_DC_PREDICTION                     = (1 << 11),
    /** Disable Intra 8x8 diagonal down left prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_DIAGONAL_DOWN_LEFT_PREDICTION     = (1 << 12),
    /** Disable Intra 8x8 diagonal down right prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_DIAGONAL_DOWN_RIGHT_PREDICTION    = (1 << 13),
    /** Disable Intra 8x8 vertical right prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_VERTICAL_RIGHT_PREDICTION         = (1 << 14),
    /** Disable Intra 8x8 horizontal down prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_HORIZONTAL_DOWN_PREDICTION        = (1 << 15),
    /** Disable Intra 8x8 vertical left prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_VERTICAL_LEFT_PREDICTION          = (1 << 16),
    /** Disable Intra 8x8 horizontal up prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_8x8_HORIZONTAL_UP_PREDICTION          = (1 << 17),

    /** Disable Intra 16x16 vertical prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_16x16_VERTICAL_PREDICTION             = (1 << 18),
    /** Disable Intra 16x16 horizontal prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_16x16_HORIZONTAL_PREDICTION           = (1 << 19),
    /** Disable Intra 16x16 DC prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_16x16_DC_PREDICTION                   = (1 << 20),
    /** Disable Intra 16x16 plane prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_16x16_PLANE_PREDICTION                = (1 << 21),

    /** Disable Intra chroma vertical prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_CHROMA_VERTICAL_PREDICTION            = (1 << 22),
    /** Disable Intra chroma horizontal prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_CHROMA_HORIZONTAL_PREDICTION          = (1 << 23),
    /** Disable Intra chroma DC prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_CHROMA_DC_PREDICTION                  = (1 << 24),
    /** Disable Intra chroma plane prediction */
    NVMEDIA_ENCODE_DISABLE_INTRA_CHROMA_PLANE_PREDICTION               = (1 << 25),

    /** Disable Inter L0 partition 16x16 prediction */
    NVMEDIA_ENCODE_DISABLE_INTER_L0_16x16_PREDICTION                   = (1 << 26),
    /** Disable Inter L0 partition 16x8 prediction */
    NVMEDIA_ENCODE_DISABLE_INTER_L0_16x8_PREDICTION                    = (1 << 27),
    /** Disable Inter L0 partition 8x16 prediction */
    NVMEDIA_ENCODE_DISABLE_INTER_L0_8x16_PREDICTION                    = (1 << 28),
    /** Disable Inter L0 partition 8x8 prediction */
    NVMEDIA_ENCODE_DISABLE_INTER_L0_8x8_PREDICTION                     = (1 << 29)
} NvMediaEncodeH264MotionPredictionExclusionFlags;

/**
 * \hideinitializer
 * Defines motion search mode control flags for H.264.
 */
typedef enum {
    /** IP Search mode bit Intra 4x4 */
    NVMEDIA_ENCODE_ENABLE_IP_SEARCH_INTRA_4x4                 = (1 << 0),
    /** IP Search mode bit Intra 8x8 */
    NVMEDIA_ENCODE_ENABLE_IP_SEARCH_INTRA_8x8                 = (1 << 1),
    /** IP Search mode bit Intra 16x16 */
    NVMEDIA_ENCODE_ENABLE_IP_SEARCH_INTRA_16x16               = (1 << 2),
    /** Enable self_temporal_refine */
    NVMEDIA_ENCODE_ENABLE_SELF_TEMPORAL_REFINE               = (1 << 3),
    /** Enable self_spatial_refine */
    NVMEDIA_ENCODE_ENABLE_SELF_SPATIAL_REFINE                = (1 << 4),
    /** Enable coloc_refine */
    NVMEDIA_ENCODE_ENABLE_COLOC_REFINE                       = (1 << 5),
    /** Enable external_refine */
    NVMEDIA_ENCODE_ENABLE_EXTERNAL_REFINE                    = (1 << 6),
    /** Enable const_mv_refine */
    NVMEDIA_ENCODE_ENABLE_CONST_MV_REFINE                    = (1 << 7),
    /** Enable the flag set */
    NVMEDIA_ENCODE_MOTION_SEARCH_CONTROL_FLAG_VALID          = (1 << 31)
} NvMediaEncodeH264MotionSearchControlFlags;

/**
 * Specifies the frequency of the writing of Sequence and Picture parameters
 * for H.264.
 * \hideinitializer
 */
typedef enum {
    /** Repeating of SPS/PPS is disabled */
    NVMEDIA_ENCODE_SPSPPS_REPEAT_DISABLED          = 0,
    /** SPS/PPS is repeated for every intra frame */
    NVMEDIA_ENCODE_SPSPPS_REPEAT_INTRA_FRAMES      = 1,
    /** SPS/PPS is repeated for every IDR frame */
    NVMEDIA_ENCODE_SPSPPS_REPEAT_IDR_FRAMES        = 2
} NvMediaEncodeH264SPSPPSRepeatMode;

/**
 * Specifies the Video encoder get attribute type.
 * This can be extended to get other encoding parameter information.
 * \hideinitializer
 */
typedef enum {
    /** This attribute is used to get SPS data for current encoding session */
    NvMediaEncAttr_GetSPS = 1,
    /** This attribute is used to get PPS data for current encoding session */
    NvMediaEncAttr_GetPPS,
    /** This attribute is used to get VPS data for current h265 encoding session */
    NvMediaEncAttr_GetVPS
} NvMediaEncAttrType;

/**
 * Define H.264 pic_order_cnt_type
 * \hideinitializer
 */
typedef enum {
    /** Automatic level selection */
    NVMEDIA_ENCODE_H264_POC_TYPE_AUTOSELECT     = 0,
    /** Pic_order_cnt_type 0 */
    NVMEDIA_ENCODE_H264_POC_TYPE_0              = 1,
    /** Pic_order_cnt_type 2 */
    NVMEDIA_ENCODE_H264_POC_TYPE_2              = 2
} NvMediaEncodeH264POCType;

/**
 * \hideinitializer
 * \brief Maximum encoded header info size
 */
#define MAX_NON_SLICE_DATA_SIZE 2048

/**
 * This is used to get header info (SPS/PPS/VPS) using GetAttribute call.
 * HeaderInfo type is defined in \ref NvMediaEncAttrType
 */
typedef struct {
    /** Nal size for header */
    uint32_t ulNalSize;
    /** header data passed on this buffer */
    uint8_t data[MAX_NON_SLICE_DATA_SIZE];
} NvMediaNalData;

/**
 * Holds H264 video usability information parameters.
 */
typedef struct {
    /** If set to NVMEDIA_TRUE, it specifies that the \a aspectRatioIdc is present. */
    NvMediaBool aspectRatioInfoPresentFlag;
    /** Holds the acpect ratio IDC
        (as defined in Annex E of the ITU-T Specification).*/
    uint8_t aspectRatioIdc;
    /** If \a aspectRatioIdc is Extended SAR then it indicates horizontal size
        of the sample aspect ratio (in arbitrary units). */
    uint16_t aspectSARWidth;
    /** If aspectRatioIdc is Extended SAR then it indicates vertical size
        of the sample aspect ratio (in the same arbitrary units as aspectSARWidth) */
    uint16_t aspectSARHeight;
    /** If set to NVMEDIA_TRUE, it specifies that the overscanInfo is present */
    NvMediaBool overscanInfoPresentFlag;
    /** Holds the overscan info (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool overscanAppropriateFlag;
    /** If set to NVMEDIA_TRUE, it specifies  that the videoFormat, videoFullRangeFlag and
        colourDescriptionPresentFlag are present. */
    NvMediaBool videoSignalTypePresentFlag;
    /** Holds the source video format
        (as defined in Annex E of the ITU-T Specification).*/
    uint8_t videoFormat;
    /** Holds the output range of the luma and chroma samples
        (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool videoFullRangeFlag;
    /** If set to NVMEDIA_TRUE, it specifies that the colourPrimaries, transferCharacteristics
        and colourMatrix are present. */
    NvMediaBool colourDescriptionPresentFlag;
    /** Holds color primaries for converting to RGB (as defined in Annex E of
        the ITU-T Specification). */
    uint8_t colourPrimaries;
    /** Holds the opto-electronic transfer characteristics to use
        (as defined in Annex E of the ITU-T Specification). */
    uint8_t transferCharacteristics;
    /** Holds the matrix coefficients used in deriving the luma and chroma from
        the RGB primaries (as defined in Annex E of the ITU-T Specification). */
    uint8_t colourMatrix;
    /** Holds that num_units_in_tick, time_scale and fixed_frame_rate_flag are present
       in the bitstream (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool timingInfoPresentFlag;
    /** Holds the bitstream restriction info (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool bitstreamRestrictionFlag;
} NvMediaEncodeConfigH264VUIParams;

/**
 * Holds an external motion vector hint with counts per block type.
 */
typedef struct {
    /** Holds the number of candidates per 16x16 block. */
    uint32_t   numCandsPerBlk16x16;
    /** Holds the number of candidates per 16x8 block. */
    uint32_t   numCandsPerBlk16x8;
    /** Holds the number of candidates per 8x16 block. */
    uint32_t   numCandsPerBlk8x16;
    /** Holds the number of candidates per 8x8 block. */
    uint32_t   numCandsPerBlk8x8;
} NvMediaEncodeExternalMeHintCountsPerBlocktype;

/**
 * Holds an External Motion Vector hint.
 */
typedef struct {
    /** Holds the x component of integer pixel MV (relative to current MB) S12.0. */
    int32_t mvx        : 12;
    /** Holds the y component of integer pixel MV (relative to current MB) S10.0 .*/
    int32_t mvy        : 10;
    /** Holds the reference index (31=invalid). Current we support only 1 reference frame per direction for external hints, so refidx must be 0. */
    uint32_t refidx     : 5;
    /** Holds the direction of motion estimation . 0=L0 1=L1.*/
    uint32_t dir        : 1;
    /** Holds the block partition type. 0=16x16 1=16x8 2=8x16 3=8x8 (blocks in partition must be consecutive).*/
    uint32_t partType   : 2;
    /** Set to NVMEDIA_TRUE for the last MV of (sub) partition  */
    uint32_t lastofPart : 1;
    /** Set to NVMEDIA_TRUE for the last MV of macroblock. */
    uint32_t lastOfMB   : 1;
} NvMediaEncodeExternalMEHint;

/**
 * Defines H264 encoder configuration features.
 * \hideinitializer
 */
typedef enum {
    /** Enable to write access unit delimiter syntax in bitstream */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_OUTPUT_AUD               = (1 << 0),
    /** Enable gradual decoder refresh or intra refresh.
       If the GOP structure uses B frames this will be ignored */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_INTRA_REFRESH            = (1 << 1),
    /** Enable dynamic slice mode. Client must specify max slice
       size using the maxSliceSizeInBytes field. */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_DYNAMIC_SLICE_MODE       = (1 << 2),
    /** Enable constrainedFrame encoding where each slice in the
       constrained picture is independent of other slices. */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_CONSTRANED_ENCODING      = (1 << 3),
    /** Enable lossless compression. */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_LOSSLESS_COMPRESSION     = (1 << 4),
    /** Enable slice level output encoding. This enables delivery
      endoded data slice by slice to client to reduce encode latency */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_SLICE_LEVEL_OUTPUT       = (1 << 5),
    /** Enable RTP mode output. Nal unit start code will be replaced
       with NAL size for the NAL units. */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_RTP_MODE_OUTPUT          = (1 << 6),
    /** Enable support for external picture RC hint */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_EXT_PIC_RC_HINT          = (1 << 7),
    /** Enable support for dynamic reference picture set RPS/DPB
       control support. After receiving an input buffer and result
       of previous frame encoding, based on real time information,
       Some client software determines properties for the new input
       buffer (long term/short term/non-referenced,
       frame number/poc/LT index), */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_DYNAMIC_RPS              = (1 << 8),
    /** Enable support for motion vector buffer dump. This will enable
       motion vector dump. Motion vector buffer will be appended at the
       end of encoded bitstream data */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_MV_BUFFER_DUMP           = (1 << 9),
    /** Enable encoder profiling. Profiling information would be added
       as part of output extradata */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_PROFILING                = (1 << 10),
    /** Enable support to use client provided Initial QP for all frame types */
    NVMEDIA_ENCODE_CONFIG_H264_INIT_QP                         = (1 << 11),
    /** Enable support to use client provided QP max for all frame types */
    NVMEDIA_ENCODE_CONFIG_H264_QP_MAX                          = (1 << 12),
    /** Enable support to use 4 byte start code in all the slices in a picture */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_FOUR_BYTE_START_CODE     = (1 << 13),
    /** Enable ultra fast encoding. It overrides some of the quality settings
        to acheive ultra fast encoding. This is specific to H264 encode. */
    NVMEDIA_ENCODE_CONFIG_H264_ENABLE_ULTRA_FAST_ENCODE        = (1 << 14)
} NvMediaEncodeH264Features;

/**
 * Holds an H264 encoder configuration.
 */
typedef struct {
    /** Holds bit-wise OR`ed configuration feature flags. See NvMediaEncodeH264Features enum */
    uint32_t features;
    /** Holds the number of pictures in one GOP. Low latency application client can
       set goplength to NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that keyframes are not
       inserted automatically. */
    uint32_t gopLength;
    /** Holds the rate control parameters for the current encoding session. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the frequency of the writing of Sequence and Picture parameters */
    NvMediaEncodeH264SPSPPSRepeatMode repeatSPSPPS;
    /** Holds the IDR interval. If not set, this is made equal to gopLength in
       NvMediaEncodeConfigH264. Low latency application client can set IDR interval to
       NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that IDR frames are not inserted automatically. */
    uint32_t idrPeriod;
    /** Holds a number that is 1 less than the number of slices desired per frame. */
    uint16_t numSliceCountMinus1;
    /** Holds the deblocking filter mode. Permissible value range: [0,2]. */
    uint8_t disableDeblockingFilterIDC;
    /** Holds the AdaptiveTransform Mode. */
    NvMediaEncodeH264AdaptiveTransformMode adaptiveTransformMode;
    /** Holds the BDirect mode. */
    NvMediaEncodeH264BDirectMode bdirectMode;
    /** Holds the entropy coding mode. */
    NvMediaEncodeH264EntropyCodingMode entropyCodingMode;
    /** Holds the interval between frames that trigger a new intra refresh cycle
       and this cycle lasts for intraRefreshCnt frames.
       This value is used only if the NVMEDIA_ENCODE_CONFIG_H264_ENABLE_INTRA_REFRESH is
       set in features.
       NVMEDIA_ENCODE_PIC_TYPE_P_INTRA_REFRESH picture type also triggers a new intra
       refresh cycle and resets the current intra refresh period.
       Setting it to zero results in that no automatic refresh cycles are triggered.
       In this case only NVMEDIA_ENCODE_PIC_TYPE_P_INTRA_REFRESH picture type can trigger
       a new refresh cycle. */
    uint32_t intraRefreshPeriod;
    /** Holds the number of frames over which intra refresh will happen.
       This value must be less than or equal to intraRefreshPeriod. Setting it to zero
       turns off the intra refresh functionality. Setting it to one essentially means
       that after every intraRefreshPeriod frames the encoded P frame contains only
       intra predicted macroblocks.
       This value is used only if the NVMEDIA_ENCODE_CONFIG_H264_ENABLE_INTRA_REFRESH
       is set in features. */
    uint32_t intraRefreshCnt;
    /** Holds the max slice size in bytes for dynamic slice mode.
       Client must set NVMEDIA_ENCODE_CONFIG_H264_ENABLE_DYNAMIC_SLICE_MODE in features to use
       max slice size in bytes. */
    uint32_t maxSliceSizeInBytes;
    /** Number of macroblocks per slice. Set to 0 if fix number of macroblocks not required or
        maxSliceSizeInBytes or numSliceCountMinus1 is set to non-zero value. */
    uint32_t numMacroblocksPerSlice;
    /** Holds the H264 video usability info pamameters. Set to NULL if VUI is not needed */
    NvMediaEncodeConfigH264VUIParams *h264VUIParameters;
    /** Holds bit-wise OR`ed exclusion flags. See NvMediaEncodeH264MotionPredictionExclusionFlags enum. */
    uint32_t motionPredictionExclusionFlags;
    /** Holds encode quality pre-set. See NvMediaEncodeQuality enum.
        Recommended pre-setting is NVMEDIA_ENCODE_QUALITY_L1. */
    NvMediaEncodeQuality quality;
    /** Holds pic_ordec_cnt_type */
    NvMediaEncodeH264POCType pocType;
    /** Holds Initial QP parameters. Client must set NVMEDIA_ENCODE_CONFIG_H264_INIT_QP in features to
        use this. QP values should be within the range of 1 to 51 */
    NvMediaEncodeQP initQP;
    /** Holds maximum QP parameters. Client must set
     *  NVMEDIA_ENCODE_CONFIG_H264_QP_MAX in features to use this. The maximum QP values
     *  must be within the range of 1 to 51 and must be greater than
     * \ref NvMediaEncodeRCParams::minQP. */
    NvMediaEncodeQP maxQP;
    /** Holds enable weighted predition */
    uint8_t enableWeightedPrediction;
} NvMediaEncodeConfigH264;

/**
 *  H.264 specific User SEI message
 */
typedef struct {
    /** SEI payload size in bytes. SEI payload must be byte aligned, as described in Annex D */
    uint32_t payloadSize;
    /** SEI payload types and syntax can be found in Annex D of the H.264 Specification. */
    uint32_t payloadType;
    /** Pointer to user data. */
    uint8_t *payload;
} NvMediaEncodeH264SEIPayload;

/**
 * Holds H264-specific encode initialization parameters.
 */
typedef struct {
    /** Holds the encode width.*/
    uint32_t encodeWidth;
    /** Holds the encode height.*/
    uint32_t encodeHeight;
    /** Set this to NVMEDIA_TRUE for limited-RGB (16-235) input */
    NvMediaBool enableLimitedRGB;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the denominator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the encoding profile. Client is recommended to set this to
        NVMEDIA_ENCODE_PROFILE_AUTOSELECT in order to enable the Encode interface
        to select the correct profile. */
    uint8_t profile;
    /** Holds the encoding level. Client is recommended to set this to
        NVMEDIA_ENCODE_LEVEL_AUTOSELECT in order to enable the Encode interface
        to select the correct level. */
    uint8_t level;
    /** Holds the max reference numbers used for encoding. Allowed range is [0, 2].
        Values:
           - 0 allows only I frame encode
           - 1 allows I and IP encode
           - 2 allows I, IP and IBP encode */
    uint8_t maxNumRefFrames;
    /** Set to NVMEDIA_TRUE to enable external ME hints.
        Currently this feature is not supported if B frames are used */
    NvMediaBool enableExternalMEHints;
    /** If Client wants to pass external motion vectors in \ref NvMediaEncodePicParamsH264
        meExternalHints buffer it must specify the maximum number of hint candidates
        per block per direction for the encode session. The \ref NvMediaEncodeInitializeParamsH264
        maxMEHintCountsPerBlock[0] is for L0 predictors and \ref NvMediaEncodeInitializeParamsH264
        maxMEHintCountsPerBlock[1] is for L1 predictors. This client must also set
        \ref NvMediaEncodeInitializeParamsH264 enableExternalMEHints to NVMEDIA_TRUE. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype maxMEHintCountsPerBlock[2];
    /** Enable support for recon CRC generation. NVMEDIA will
       allocate extra surface for recon CRC calculation. This can
       be enabled at run time for any frame by enabling recon CRC and
       passing recon CRC rectangle. */
    NvMediaBool enableReconCRC;
    /** If client want to do MVC encoding then this flag need to be set. */
    NvMediaBool enableMVC;
    /** Enable region of interest encoding. Region of interest encoding parameters are
        passed with Input extra data parameters */
    NvMediaBool enableROIEncode;
    /** use slice encode to reduce latency in getting encoded buffers. */
    NvMediaBool enableSliceEncode;
    /** Enables B frames to be used as refernces frames */
    uint32_t useBFramesAsRef;
    /** Enable 2 pass RC support. First pass RC can be run on full or quarter resolution. */
    NvMediaBool enableTwoPassRC;
    /** Enable 2 pass RC with quarter resolution first pass. */
    NvMediaBool enableSourceHalfScaled;
    /** Number of views used for MVC */
    uint32_t mvcNumViews;
} NvMediaEncodeInitializeParamsH264;

/**
 * H264 specific encoder picture params. Sent on a per frame basis.
 */
typedef struct {
    /** Holds input picture type. */
    NvMediaEncodePicType pictureType;
    /** Holds bit-wise OR`ed encode pic flags. See NvMediaEncodePicFlags enum. */
    uint32_t encodePicFlags;
    /** Secifies the number of B-frames that follow the current frame.
        This number can be set only for reference frames and the frames
        that follow the current frame must be nextBFrames count of B-frames.
        B-frames are supported only if the profile is greater than
        NVMEDIA_ENCODE_PROFILE_BASELINE and the maxNumRefFrames is set to 2.
        Set to zero if no B-frames are needed. */
    uint32_t nextBFrames;
    /** Holds the rate control parameters from the current frame onward
        if the NVMEDIA_ENCODE_PIC_FLAG_RATECONTROL_CHANGE is set in the encodePicFlags.
        Please note that the rateControlMode cannot be changed on a per frame basis only
        the associated rate control parameters. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the number of elements allocated in seiPayloadArray array.
        Set to 0 if no SEI messages are needed */
    uint32_t seiPayloadArrayCnt;
    /** Array of SEI payloads which will be inserted for this frame. */
    NvMediaEncodeH264SEIPayload *seiPayloadArray;
    /** Holds the number of hint candidates per block per direction for the current frame.
        meHintCountsPerBlock[0] is for L0 predictors and meHintCountsPerBlock[1] is for
        L1 predictors. The candidate count in \ref NvMediaEncodePicParamsH264 meHintCountsPerBlock[lx]
        must never exceed \ref NvMediaEncodeInitializeParamsH264 maxMEHintCountsPerBlock[lx] provided
        during encoder intialization. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype meHintCountsPerBlock[2];
    /** Holds the pointer to ME external hints for the current frame.
        The size of ME hint buffer must be equal to number of macroblocks multiplied
        by the total number of candidates per macroblock.
        The total number of candidates per MB per direction =
        <pre>
        1*meHintCountsPerBlock[Lx].numCandsPerBlk16x16 +
        2*meHintCountsPerBlock[Lx].numCandsPerBlk16x8 +
        2*meHintCountsPerBlock[Lx].numCandsPerBlk8x16 +
        4*meHintCountsPerBlock[Lx].numCandsPerBlk8x8
        </pre>
        For frames using bidirectional ME, the total number of candidates for a
        single macroblock is the sum of the total number of candidates per MB
        for each direction (L0 and L1).

        If no external ME hints are needed, set this field to NULL. */
    NvMediaEncodeExternalMEHint *meExternalHints;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the viewId of current picture */
    uint32_t viewId;
} NvMediaEncodePicParamsH264;
/** @} <!-- Ends h264_encoder_api H.264 Encoder -> */

/**
 * @defgroup h265_encoder_api H.265 Encoder: Common Types
 * The H.265 Encoder API provides basic encode parameters.
 * @ingroup basic_api_top
 * @{
 */
/**
 * Holds the H.265 video usability information parameters.
 */
typedef struct {
    /** If set to NVMEDIA_TRUE, specifies the \a aspectRatioIdc is present. */
    NvMediaBool aspectRatioInfoPresentFlag;
    /** Holds the aspect ratio IDC
        (as defined in Annex E of the ITU-T specification).*/
    uint8_t aspectRatioIdc;
    /** If \a aspectRatioIdc is Extended SAR it indicates horizontal size
        of the sample aspect ratio (in arbitrary units). */
    uint16_t aspectSARWidth;
    /** If \a aspectRatioIdc is Extended SAR it indicates vertical size
        of the sample aspect ratio (in the same arbitrary units as \a aspectSARWidth). */
    uint16_t aspectSARHeight;
    /** If set to NVMEDIA_TRUE, it specifies that the \a overscanInfo is present. */
    NvMediaBool overscanInfoPresentFlag;
    /** Holds the overscan info (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool overscanAppropriateFlag;
    /** If set to NVMEDIA_TRUE, it specifies that the \a videoFormat, \a videoFullRangeFlag, and
        \a colourDescriptionPresentFlag are present. */
    NvMediaBool videoSignalTypePresentFlag;
    /** Holds the source video format
        (as defined in Annex E of the ITU-T Specification).*/
    uint8_t videoFormat;
    /** Holds the output range of the luma and chroma samples
        (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool videoFullRangeFlag;
    /** If set to NVMEDIA_TRUE, it specifies that the \a colourPrimaries, \a transferCharacteristics,
        and \a colourMatrix are present. */
    NvMediaBool colourDescriptionPresentFlag;
    /** Holds color primaries for converting to RGB (as defined in Annex E of
        the ITU-T Specification). */
    uint8_t colourPrimaries;
    /** Holds the opto-electronic transfer characteristics to use
        (as defined in Annex E of the ITU-T Specification). */
    uint8_t transferCharacteristics;
    /** Holds the matrix coefficients used in deriving the luma and chroma from
        the RGB primaries (as defined in Annex E of the ITU-T Specification). */
    uint8_t matrixCoeffs;
    /* Holds that num_units_in_tick, time_scale and fixed_frame_rate_flag are present
       in the bitstream (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool vuiTimingInfoPresentFlag;
    /* Specified the bitstream restriction info (as defined in Annex E of the ITU-T Specification). */
    NvMediaBool bitstreamRestrictionFlag;
} NvMediaEncodeConfigH265VUIParams;

/**
 * Defines H265 encoder configuration features.
 * \hideinitializer
 */
typedef enum {
    /** Enable to write access unit delimiter syntax in bitstream */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_OUTPUT_AUD               = (1 << 0),
    /** Enable gradual decoder refresh or intra refresh.
       If the GOP structure uses B frames this will be ignored */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_INTRA_REFRESH            = (1 << 1),
    /** Enable dynamic slice mode. Client must specify max slice
       size using the maxSliceSizeInBytes field. */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_DYNAMIC_SLICE_MODE       = (1 << 2),
    /** Enable constrainedFrame encoding where each slice in the
       constrained picture is independent of other slices. */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_CONSTRANED_ENCODING      = (1 << 3),
    /** Enable lossless compression. */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_LOSSLESS_COMPRESSION     = (1 << 4),
    /** Enable slice level output encoding. This enables delivery
      endoded data slice by slice to client to reduce encode latency */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_SLICE_LEVEL_OUTPUT       = (1 << 5),
    /** Enable RTP mode output. Nal unit start code will be replaced
       with NAL size for the NAL units. */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_RTP_MODE_OUTPUT          = (1 << 6),
    /** Enable support for external picture RC hint */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_EXT_PIC_RC_HINT          = (1 << 7),
    /** Enable support for dynamic reference picture set RPS/DPB
       control support. After receiving an input buffer and result
       of previous frame encoding, based on real time information,
       Some client software determines properties for the new input
       buffer (long term/short term/non-referenced,
       frame number/poc/LT index), */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_DYNAMIC_RPS              = (1 << 8),
    /** Enable support for motion vector buffer dump. This will enable
       motion vector dump. Motion vector buffer will be appended at the
       end of encoded bitstream data */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_MV_BUFFER_DUMP           = (1 << 9),
    /** Enable encoder profiling. Profiling information would be added
       as part of output extradata */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_PROFILING                = (1 << 10),
    /** Enable ultra fast encoding. It overrides some of the quality settings
        to acheive ultra fast encoding. This is specific to H265 encode. */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_ULTRA_FAST_ENCODE        = (1 << 11),
    /** Enable support to use client provided Initial QP for all frame types */
    NVMEDIA_ENCODE_CONFIG_H265_INIT_QP                         = (1 << 12),
    /** Enable support to use client provided QP max for all frame types. */
    NVMEDIA_ENCODE_CONFIG_H265_QP_MAX                        = (1 << 13),
    /** Enable support to use 4 byte start code in all the slices in a picture */
    NVMEDIA_ENCODE_CONFIG_H265_ENABLE_FOUR_BYTE_START_CODE     = (1 << 14)
} NvMediaEncodeH265Features;

/**
 * Holds the H265 encoder configuration parameters.
 */
typedef struct {
    /** Holds bit-wise OR`ed configuration feature flags.
      *  See the \ref NvMediaEncodeH265Features enum. */
    uint32_t features;
    /** Holds the number of pictures in one GOP. Low latency application client can
       set the \a goplength field to \ref NVMEDIA_ENCODE_INFINITE_GOPLENGTH
       so that keyframes are not inserted automatically. */
    uint32_t gopLength;
    /** Holds the rate control parameters for the current encoding session. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the frequency of the writing of Sequence and Picture parameters. */
    NvMediaEncodeH264SPSPPSRepeatMode repeatSPSPPS;
    /** Holds the IDR interval. If not set, this is made equal to
        NvMediaEncodeConfigH265::gopLength. Low latency application client can set IDR interval to
       NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that IDR frames are not inserted automatically. */
    uint32_t idrPeriod;
    /** Set to 1 less than the number of slices desired per frame */
    uint16_t numSliceCountMinus1;
    /** Holds disable the deblocking filter */
    uint8_t disableDeblockingFilter;
    /** Holds enable weighted predition */
    uint8_t enableWeightedPrediction;
    /** Holds the interval between frames that trigger a new intra refresh cycle
       and this cycle lasts for intraRefreshCnt frames.
       This value is used only if the \ref NVMEDIA_ENCODE_CONFIG_H265_ENABLE_INTRA_REFRESH is
       set in features.
       The \ref NVMEDIA_ENCODE_PIC_TYPE_P_INTRA_REFRESH picture type also triggers a new intra-
       refresh cycle and resets the current intra-refresh period.
       Setting it to zero results in that no automatic refresh cycles are triggered.
       In this case only NVMEDIA_ENCODE_PIC_TYPE_P_INTRA_REFRESH picture type can trigger
       a new refresh cycle. */
    uint32_t intraRefreshPeriod;
    /** Holds the number of frames over which intra refresh will happen.
       This value must be less than or equal to intraRefreshPeriod. Setting it to zero
       turns off the intra refresh functionality. Setting it to one essentially means
       that after every intraRefreshPeriod frames the encoded P frame contains only
       intra predicted macroblocks.
       This value is used only if the NVMEDIA_ENCODE_CONFIG_H265_ENABLE_INTRA_REFRESH
       is set in features. */
    uint32_t intraRefreshCnt;
    /** Holds the maximum slice size in bytes for dynamic slice mode. The
       Client must set NVMEDIA_ENCODE_CONFIG_H265_ENABLE_DYNAMIC_SLICE_MODE in features to use
       max slice size in bytes. */
    uint32_t maxSliceSizeInBytes;
    /** Number of CTU per slice. Set to 0 if fix number of macroblocks not required or
        maxSliceSizeInBytes or numSliceCountMinus1 is set to non-zero value. */
    uint32_t numCTUsPerSlice;
    /** Holds the H265 video usability info pamameters. Set to NULL if VUI is not needed */
    NvMediaEncodeConfigH265VUIParams *h265VUIParameters;
    /** Holds encode quality pre-set. See NvMediaEncodeQuality enum.
        Recommended pre-setting is NVMEDIA_ENCODE_QUALITY_L0. */
    NvMediaEncodeQuality quality;
    /** Holds Initial QP parameters. Client must set NVMEDIA_ENCODE_CONFIG_H265_INIT_QP in features to
        use this. QP values should be within the range of 1 to 51 */
    NvMediaEncodeQP initQP;
    /** Holds maximum QP parameters. Client must set
     *  NVMEDIA_ENCODE_CONFIG_H265_QP_MAX in features to use this. The maximum QP values
     *  must be within the range of 1 to 51 and must be set to a value greater than
     * \ref NvMediaEncodeRCParams::minQP. */
    NvMediaEncodeQP maxQP;
} NvMediaEncodeConfigH265;

/**
 * Holds H265-specific encode initialization parameters.
 */
typedef struct {
    /** Holds the encode width.*/
    uint32_t encodeWidth;
    /** Holds the encode height.*/
    uint32_t encodeHeight;
    /** Set this to NVMEDIA_TRUE for limited-RGB (16-235) input. */
    NvMediaBool enableLimitedRGB;
    /** Set this to NVMEDIA_TRUE for slice level encode. */
    NvMediaBool enableSliceLevelEncode;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the denominator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the encoding profile. Client is recommended to set this to
        NVMEDIA_ENCODE_PROFILE_AUTOSELECT in order to enable the Encode interface
        to select the correct profile. */
    uint8_t profile;
    /** Holds the encoding level. Client is recommended to set this to
        NVMEDIA_ENCODE_LEVEL_AUTOSELECT in order to enable the Encode interface
        to select the correct level. */
    uint8_t level;
    /** Holds the level tier information. This is set to 0 for main tier
        and 1 for high tier. This is valid only when level is not selected
        as NVMEDIA_ENCODE_LEVEL_AUTOSELECT. */
    uint8_t levelTier;
    /** Holds the max reference numbers used for encoding. Allowed range is [0, 2].
        Values:
           - 0 allows only I frame encode
           - 1 allows I and IP encode
           - 2 allows I, IP and IBP encode */
    uint8_t maxNumRefFrames;
    /** Set to NVMEDIA_TRUE to enable external ME hints.
        Currently this feature is not supported if B frames are used */
    NvMediaBool enableExternalMEHints;
    /** If Client wants to pass external motion vectors in \ref NvMediaEncodePicParamsH265
        meExternalHints buffer it must specify the maximum number of hint candidates
        per block per direction for the encode session. The \ref NvMediaEncodeInitializeParamsH265
        maxMEHintCountsPerBlock[0] is for L0 predictors and \ref NvMediaEncodeInitializeParamsH265
        maxMEHintCountsPerBlock[1] is for L1 predictors. This client must also set
        \ref NvMediaEncodeInitializeParamsH265 enableExternalMEHints to NVMEDIA_TRUE. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype maxMEHintCountsPerBlock[2];
    /** Enable support for recon CRC generation. NVMEDIA will
       allocate extra surface for recon CRC calculation. This can
       be enabled at run time for any frame by enabling recon CRC and
       passing recon CRC rectangle. */
    NvMediaBool enableReconCRC;
    /** If client want to do MVC encoding then this flag need to be set. */
    NvMediaBool enableMVC;
    /** Enable region of interest encoding. Region of interest encoding parameters are
        passed with Input extra data parameters */
    NvMediaBool enableROIEncode;
    /** use slice encode to reduce latency in getting encoded buffers. */
    NvMediaBool enableSliceEncode;
    /** Enables B frames to be used as refernces frames */
    uint32_t useBFramesAsRef;
    /** Enable 2 pass RC support. First pass RC can be run on full or quarter resolution. */
    NvMediaBool enableTwoPassRC;
    /** Enable 2 pass RC with quarter resolution first pass. */
    NvMediaBool enableSourceHalfScaled;
    /** Number of views used for MV-Hevc */
    uint32_t mvNumViews;
} NvMediaEncodeInitializeParamsH265;

/**
 *  Holds an H265-specific User SEI message.
 */
typedef struct {
    /** SEI payload size in bytes. SEI payload must be byte aligned, as described in Annex D */
    uint32_t payloadSize;
    /** SEI payload types and syntax can be found in Annex D of the H265 Specification. */
    uint32_t payloadType;
    /** SEI nal_unit_type */
    uint32_t nalUnitType;
    /** pointer to user data */
    uint8_t *payload;
} NvMediaEncodeH265SEIPayload;

/**
 * Holds H265-specific encoder picture parameters. Sent on a per frame basis.
 */
typedef struct {
    /** Holds input picture type. */
    NvMediaEncodePicType pictureType;
    /** Holds bit-wise OR`ed encode pic flags. See NvMediaEncodePicFlags enum. */
    uint32_t encodePicFlags;
    /** Secifies the number of B-frames that follow the current frame.
        This number can be set only for reference frames and the frames
        that follow the current frame must be nextBFrames count of B-frames.
        B-frames are supported only if the profile is greater than
        NVMEDIA_ENCODE_PROFILE_BASELINE and the maxNumRefFrames is set to 2.
        Set to zero if no B-frames are needed. */
    uint32_t nextBFrames;
    /** Holds the rate control parameters from the current frame onward
        if the NVMEDIA_ENCODE_PIC_FLAG_RATECONTROL_CHANGE is set in the encodePicFlags.
        Please note that the rateControlMode cannot be changed on a per frame basis only
        the associated rate control parameters. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the number of elements allocated in seiPayloadArray array.
        Set to 0 if no SEI messages are needed */
    uint32_t seiPayloadArrayCnt;
    /** Array of SEI payloads which will be inserted for this frame. */
    NvMediaEncodeH265SEIPayload *seiPayloadArray;
    /** Holds the number of hint candidates per block per direction for the current frame.
        meHintCountsPerBlock[0] is for L0 predictors and meHintCountsPerBlock[1] is for
        L1 predictors. The candidate count in \ref NvMediaEncodePicParamsH265 meHintCountsPerBlock[lx]
        must never exceed \ref NvMediaEncodeInitializeParamsH265 maxMEHintCountsPerBlock[lx] provided
        during encoder intialization. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype meHintCountsPerBlock[2];
    /** Holds the pointer to ME external hints for the current frame.
        The size of ME hint buffer must be equal to number of macroblocks multiplied
        by the total number of candidates per macroblock.
        The total number of candidates per MB per direction =
        <pre>
          1*meHintCountsPerBlock[Lx].numCandsPerBlk16x16 +
          2*meHintCountsPerBlock[Lx].numCandsPerBlk16x8 +
          2*meHintCountsPerBlock[Lx].numCandsPerBlk8x16 +
          4*meHintCountsPerBlock[Lx].numCandsPerBlk8x8
        </pre>
        For frames using bidirectional ME, the total number of candidates for
        a single macroblock is the sum of the total number of candidates per MB
        for each direction (L0 and L1).

        If no external ME hints are needed, set this field to NULL. */
    NvMediaEncodeExternalMEHint *meExternalHints;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the viewId of current picture */
    uint32_t viewId;
} NvMediaEncodePicParamsH265;

/*@} <!-- Ends h265_encoder_api sub-group --> */

/**
 * \defgroup vp9_encoder_api VP9 Encoder: Common Types
 * The VP9 Encoder API provides VP9 related functions.
 * @ingroup nvmedia_video_top
 * @{
 */

/**
 * Defines VP9 encoder configuration features.
 */
typedef enum {
    /** Enable to set loop filter parameters */
    NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_LOOP_FILTER_PARAMS               = (1 << 0),
    /** Enable to set quantization parameters */
    NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS              = (1 << 1),
    /** Enable transform mode */
    NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_TRANSFORM_MODE                   = (1 << 2),
    /** Enable high precision mv */
    NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_HIGH_PRECISION_MV                = (1 << 3),
    /** Disable error resiliency. Error resiliency is enabled by default */
    NVMEDIA_ENCODE_CONFIG_VP9_DISABLE_ERROR_RESILIENT                 = (1 << 4),
    /** Enable encoder profiling. Profiling information would be added
       as part of output extradata */
    NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_PROFILING                        = (1 << 5),
    /** Enable support to use client provided Initial QP for all frame types */
    NVMEDIA_ENCODE_CONFIG_VP9_INIT_QP                                 = (1 << 6),
    /** Enable support to use client provided QP max for all frame types */
    NVMEDIA_ENCODE_CONFIG_VP9_QP_MAX                                = (1 << 7)
} NvMediaEncodeVP9Features;

/**
 * Holds VP9 encoder configuration parameters.
 */
typedef struct {
    /** Holds bit-wise OR`ed configuration feature flags. TBD */
    uint32_t features;
    /** Holds the number of pictures in one GOP. Low-latency application client can
       set \a goplength to NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that keyframes are not
       inserted automatically. */
    uint32_t gopLength;
    /** Holds the rate control parameters for the current encoding session. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the IDR interval. If not set, this is made equal to \a gopLength in
       NvMediaEncodeConfigVP9. Low-latency application client can set IDR interval to
       NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that IDR frames are not inserted automatically. */
    uint32_t idrPeriod;

    /** Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_LOOP_FILTER_PARAMS
       to change the following parameters */
    /** Specifies the type of the filter used. :0 eight-tap smooth, 1: eight-tap,
       2: eight-tap sharp, 3: bilinear, 4: switchable */
    uint32_t filter_type;
    /** Specifies the loop filter strength for each segment */
    uint32_t filter_level;
    /** Specifies Sharpness level */
    uint32_t sharpness_level;
    /** Specifies the Loop filter strength adjustments based on frame type (intra,
       inter) */
    int8_t ref_lf_deltas[4];
    /** Specifies the Loop filter strength adjustments based on mode (zero, new mv) */
    int8_t mode_lf_deltas[2];
    /** Set it to true if MB-level loop filter adjustment is on */
    NvMediaBool bmode_ref_lf_delta_enabled;
    /** Set it to true if MB-level loop filter adjustment delta values are updated */
    NvMediaBool bmode_ref_lf_delta_update;

    /* Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS
       to set the following parameters */
    /** Specifies quant base index (used only when rc_mode = 0) for each segment 0...255.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS. */
    uint32_t base_qindex;
    /** Specifies explicit qindex adjustment for y dccoefficient, -15...15.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS. */
    int32_t delta_y_dc_q;
    /** Specifies qindex adjustment for uv accoefficient, -15...15.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS. */
    int32_t delta_uv_dc;
    /** Specifies qindex adjustment for uv dccoefficient, -15...15.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_QUANTIZATION_PARAMS. */
    int32_t delta_uv_ac;

    /* Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_TRANSFORM_MODE to
       set the following parameter */
    /** Specifies transform_mode: 0: only4x4, 1: allow_8x8, 2: allow_16x16, 3: allow_32x32,
       4:transform_mode_select. This is for setting the feature flag
       \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_TRANSFORM_MODE. */
    uint32_t transform_mode;

    /* Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_HIGH_PRECISION_MV
       to set the following parameter */
    /** Specifies to enable high precision MV.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_ENABLE_HIGH_PRECISION_MV. */
    uint32_t high_prec_mv;

    /* Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_DISABLE_ERROR_RESILIENT to
       set the following parameter */
    /** Enable Error resiliency.
        This is for setting the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP9_DISABLE_ERROR_RESILIENT. */
    NvMediaBool error_resilient;

    /** Holds Initial QP parameters. Client must set NVMEDIA_ENCODE_CONFIG_VP9_INIT_QP in features to
        use this. QP values should be within the range of 1 to 255 */
    NvMediaEncodeQP initQP;
    /** Holds maximum QP parameters. Client must set
     *  NVMEDIA_ENCODE_CONFIG_VP9_QP_MAX in features to use this. The maximum QP values
     *  must be within the range of 1 to 255 and must be set to a value greater than
     * \ref NvMediaEncodeRCParams::minQP. */
    NvMediaEncodeQP maxQP;
} NvMediaEncodeConfigVP9;

/**
 * Holds VP9-specific encode initialization parameters.
 */
typedef struct {
    /** Holds the encode width.*/
    uint32_t encodeWidth;
    /** Holds the encode height.*/
    uint32_t encodeHeight;
    /** Holds a flag indicating whether input is limted-RGB (16-235).
        Set this to NVMEDIA_TRUE for limited-RGB (16-235) input. */
    NvMediaBool enableLimitedRGB;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the denominator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the max reference numbers used for encoding. Allowed range is [0, 2].
        Values:
        - 0 allows only I frame encode
        - 1 allows I and IP encode
        - 2 allows I, IP and IBP encode */
    uint8_t maxNumRefFrames;
    /** Holds a flag indicating whether to enable or disable the external ME hints.
        Set to NVMEDIA_TRUE to enable external ME hints.
        Currently this feature is not supported if B frames are used. */
    NvMediaBool enableExternalMEHints;
    /** If Client wants to pass external motion vectors in \ref NvMediaEncodePicParamsVP9
        \a meExternalHints buffer it must specify the maximum number of hint candidates,
        per block and per direction, for the encode session. The \ref NvMediaEncodeInitializeParamsVP9
        \a maxMEHintCountsPerBlock[0] is for L0 predictors and \ref NvMediaEncodeInitializeParamsVP9
        \a maxMEHintCountsPerBlock[1] is for L1 predictors. This client must also set
        \ref NvMediaEncodeInitializeParamsVP9 \a enableExternalMEHints to NVMEDIA_TRUE. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype maxMEHintCountsPerBlock[2];
} NvMediaEncodeInitializeParamsVP9;

/**
 * Holds VP9-specific encoder picture parameters, which are sent on a per frame basis.
 */
typedef struct {
    /** Holds input picture type. */
    NvMediaEncodePicType pictureType;
    /** Holds bit-wise OR`ed encode pic flags. See NvMediaEncodePicFlags enum. */
    uint32_t encodePicFlags;
    /** Holds the number of B-frames that follow the current frame.
        This number can be set only for reference frames and the frames
        that follow the current frame must be nextBFrames count of B-frames.
        B-frames are supported only if the profile is greater than
        NVMEDIA_ENCODE_PROFILE_BASELINE and the maxNumRefFrames is set to 2.
        Set to zero if no B-frames are needed. */
    uint32_t nextBFrames;
    /** Holds the rate control parameters from the current frame onward
        if the NVMEDIA_ENCODE_PIC_FLAG_RATECONTROL_CHANGE is set in the encodePicFlags.
        Please note that the rateControlMode cannot be changed on a per frame basis only
        the associated rate control parameters. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the number of hint candidates per block per direction for the current frame.
        \a meHintCountsPerBlock[0] is for L0 predictors and \a meHintCountsPerBlock[1] is for
        L1 predictors. The candidate count in \ref NvMediaEncodePicParamsVP9 \a meHintCountsPerBlock[lx]
        must never exceed \ref NvMediaEncodeInitializeParamsVP9 \a maxMEHintCountsPerBlock[lx] provided
        during encoder initialization. */
    NvMediaEncodeExternalMeHintCountsPerBlocktype meHintCountsPerBlock[2];
    /** Holds the pointer to ME external hints for the current frame.
        The size of ME hint buffer must be equal to number of macroblocks multiplied
        by the total number of candidates per macroblock.
        The total number of candidates per MB per direction =
        <pre>
         1*meHintCountsPerBlock[Lx].numCandsPerBlk16x16 +
         2*meHintCountsPerBlock[Lx].numCandsPerBlk16x8 +
         2*meHintCountsPerBlock[Lx].numCandsPerBlk8x16 +
         4*meHintCountsPerBlock[Lx].numCandsPerBlk8x8
        </pre>
        For frames using bidirectional ME , the total number of candidates for
        a single macroblock is the sum of the total number of candidates per MB
        for each direction (L0 and L1).

        If no external ME hints are needed, set this field to NULL. */
    NvMediaEncodeExternalMEHint *meExternalHints;
} NvMediaEncodePicParamsVP9;

/*@} <!-- Ends vp9_encoder_api sub-group --> */

/**
 * \defgroup vp8_encoder_api VP8 Encoder: Common Types
 * The VP8 Encoder API provides VP8 related functions.
 * @ingroup nvmedia_video_top
 * @{
 */

/**
 * Defines VP8 encoder configuration features.
 */
typedef enum {
    /** Enable to set loop filter parameters */
    NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_LOOP_FILTER_PARAMS               = (1 << 0),
    /** Enable to set quantization parameters */
    NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_QUANTIZATION_PARAMS              = (1 << 1),
    /** Enable segmentation */
    NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_SEGMENTATION                     = (1 << 2),
    /** Enable encoder profiling. Profiling information would be added
        as part of output extradata */
    NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_PROFILING                        = (1 << 3),
    /** Enable support to use client provided Initial QP for all frame types */
    NVMEDIA_ENCODE_CONFIG_VP8_INIT_QP                                 = (1 << 4),
    /** Enable support to use client provided QP max for all frame types */
    NVMEDIA_ENCODE_CONFIG_VP8_QP_MAX                                  = (1 << 5)
} NvMediaEncodeVP8Features;

/**
 * Holds VP8 encoder configuration parameters.
 */
typedef struct {
    /** Holds bit-wise OR`ed configuration feature flags */
    uint32_t features;
    /** Holds the number of pictures in one GOP. Low-latency application client can
        set \a goplength to NVMEDIA_ENCODE_INFINITE_GOPLENGTH so that keyframes are not
        inserted automatically. */
    uint32_t gopLength;
    /** Number of reference frame. */
    uint32_t numReferenceFrames;
    /** VP8 version type. */
    uint32_t version;
    /** Holds the rate control parameters for the current encoding session. */
    NvMediaEncodeRCParams rcParams;
    /** Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_LOOP_FILTER_PARAMS
        to change the following parameters */
    /** Specifies the type of the filter used. :0 eight-tap smooth, 1: eight-tap,
        2: eight-tap sharp, 3: bilinear, 4: switchable */
    uint32_t filter_type;
    /** Specifies the loop filter strength for each segment */
    uint32_t filter_level;
    /** Specifies Sharpness level */
    uint32_t sharpness_level;
    /** Specifies the Loop filter strength adjustments based on frame type (intra,
        inter) */
    int8_t ref_lf_deltas[4];
    /** Specifies the Loop filter strength adjustments based on mode (zero, new mv) */
    int8_t mode_lf_deltas[4];
    /** Set it to true if MB-level loop filter adjustment is on */
    NvMediaBool bmode_ref_lf_delta_enabled;
    /** Set it to true if MB-level loop filter adjustment delta values are updated */
    NvMediaBool bmode_ref_lf_delta_update;
    /** Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_QUANTIZATION_PARAMS
        to set the following parameters */
    /** Specifies quant base index (used only when rc_mode = 0) for each segment 0...255 */
    uint32_t base_qindex;
    /** VP8 delta (subtracted from baseline quant index) */
    /** VP8 Y1 dc delta */
    uint32_t y1dc_delta_q;
    /** VP8 Y2 dc delta */
    uint32_t y2dc_delta_q;
    /** VP8 Y2 ac delta */
    uint32_t y2ac_delta_q;
    /** VP8 UV dc delta */
    uint32_t uvdc_delta_q;
    /** VP8 UV ac delta */
    uint32_t uvac_delta_q;
    /** VP8 refresh entropy probs */
    uint32_t refresh_entropy_probs;
    /** Set the feature flag \ref NVMEDIA_ENCODE_CONFIG_VP8_ENABLE_SEGMENTATION
        to set the following parameters */
    /** VP8 update mb segmentation map */
    uint32_t update_mb_segmentation_map;
    /** VP8 update mb segmentation data */
    uint32_t update_mb_segmentation_data;
    /** VP8 mb segment abs delta */
    uint32_t mb_segment_abs_delta;
    /** VP8 segment filter level */
    int8_t seg_filter_level[4];
    /** VP8 segment qp index */
    int8_t seg_qindex[4];
    /** Set to enable skipping of macroblocks with no non-zero coefficients at the frame level */
    NvMediaBool mb_no_coeff_skip_flag;
    /** Set to disable temporal mv hints */
    NvMediaBool no_temporal_mv_hints;
    /** Set to turn off all probability updates to save hw testing time */
    NvMediaBool stop_prob_update;
    /** Holds Initial QP parameters. Client must set NVMEDIA_ENCODE_CONFIG_VP8_INIT_QP in features to
        use this. QP values should be within the range of 1 to 255 */
    NvMediaEncodeQP initQP;
    /** Holds max QP parameters. Client must set NVMEDIA_ENCODE_CONFIG_VP8_QP_MAX in features to
        use this. max QP values must be within the range of 1 to 255 and must be greater than
        \ref NvMediaEncodeRCParams::minQP */
    NvMediaEncodeQP maxQP;
    /** Holds encode quality pre-set. See NvMediaEncodeQuality enum. */
    NvMediaEncodeQuality quality;
} NvMediaEncodeConfigVP8;

/**
 * Holds VP8-specific encode initialization parameters.
 */
typedef struct {
    /** Holds the encode width. */
    uint32_t encodeWidth;
    /** Holds the encode height. */
    uint32_t encodeHeight;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the denominator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
    /** Holds the max reference numbers used for encoding. Allowed range is [0, 2].
        Values:
        - 0 allows only I frame encode
        - 1 allows I and IP encode */
    uint8_t maxNumRefFrames;
} NvMediaEncodeInitializeParamsVP8;

/**
 * Holds VP8-specific encoder picture parameters, which are sent on a per frame basis.
 */
typedef struct {
    /** Holds input picture type. */
    NvMediaEncodePicType pictureType;
    /** Holds bit-wise OR`ed encode pic flags. See NvMediaEncodePicFlags enum. */
    uint32_t encodePicFlags;
    /** Holds the rate control parameters from the current frame onward
        if the NVMEDIA_ENCODE_PIC_FLAG_RATECONTROL_CHANGE is set in the encodePicFlags.
        Please note that the rateControlMode cannot be changed on a per frame basis only
        the associated rate control parameters. */
    NvMediaEncodeRCParams rcParams;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateNum;
    /** Holds the numerator for frame rate used for encoding in frames per second
        ( Frame rate = frameRateNum / frameRateDen ). */
    uint32_t frameRateDen;
} NvMediaEncodePicParamsVP8;

/*@} <!-- Ends vp8_encoder_api sub-group --> */

/** \brief Defines filter quality levels.
 */
typedef enum {
    /** \hideinitializer \brief Low (default) filter quality. */
    NVMEDIA_FILTER_QUALITY_LOW = 0,
    /** \hideinitializer \brief Medium filter quality. */
    NVMEDIA_FILTER_QUALITY_MEDIUM,
    /** \hideinitializer \brief High filter quality. */
    NVMEDIA_FILTER_QUALITY_HIGH
} NvMediaFilterQuality;

/**
 * \defgroup display_attributes Display Attributes
 * Defines display attribute bit masks for constructing attribute masks.
 * @{
 */

/**
 * \hideinitializer
 * \brief Brightness
 */
#define NVMEDIA_DISP_ATTR_BRIGHTNESS      (1<<0)
/**
 * \hideinitializer
 * \brief Contrast
 */
#define NVMEDIA_DISP_ATTR_CONTRAST        (1<<1)
/**
 * \hideinitializer
 * \brief Sturation
 */
#define NVMEDIA_DISP_ATTR_SATURATION      (1<<2)
/**
 * \hideinitializer
 * \brief Hue
 */
#define NVMEDIA_DISP_ATTR_HUE             (1<<3)
/**
 * \hideinitializer
 * \brief Color Standard for display
 */
#define NVMEDIA_DISP_ATTR_COLOR_STANDARD  (1<<4)
/**
 * \hideinitializer
 * \brief Limited RGB range input
 */
#define NVMEDIA_DISP_ATTR_LIMITED_RGB     (1<<5)
/**
 * \hideinitializer
 * \brief Sets the layer composition mode.
 */
#define NVMEDIA_DISP_ATTR_COMPOSITION     (1<<6)
/**
 * \hideinitializer
 * \brief Sets video output depth
 */
#define NVMEDIA_DISP_ATTR_SET_DEPTH       (1<<7)
/**
 * \hideinitializer
 * \brief Sets video output position
 */
#define NVMEDIA_DISP_ATTR_SET_POSITION    (1<<8)

/*@} <!-- Ends display_attributes sub-group --> */

/**
 * \brief Specifies composition modes for layers.
 */
typedef enum {
    /*! A lower depth overlay is fully covering any higher depth overlay.*/
    NVMEDIA_DISP_COMP_MODE_OPAQUE,
    /*! A lower depth overlay is per-pixel alpha blended over any higher depth overlay.
        The blending mode is Source Alpha. */
    NVMEDIA_DISP_COMP_MODE_SRC_ALPHA,
    /*! A lower depth overlay is per-pixel alpha blended over any higher depth overlay.
        The blending mode is Pre-multiplied Source Alpha. */
    NVMEDIA_DISP_COMP_MODE_PREMULTI_SRC_ALPHA
} NvMediaDispCompMode;

/**
 * \brief Holds NvMedia display attributes.
 */
typedef struct {
    /** \brief A value clamped to between -0.5 and 0.5, initialized to
     * 0.0 at NvMediaVideoOutput creation. The corresponding
     * attribute mask is \ref NVMEDIA_DISP_ATTR_BRIGHTNESS.
     */
    float_t brightness;
    /** \brief A value clamped to between 0.1 and 2.0, initialized to
     * 1.0 at NvMediaVideoMixer creation. The corresponding
     * attribute mask is \ref NVMEDIA_DISP_ATTR_CONTRAST.
     */
    float_t contrast;
    /** \brief A value clamped to between 0.1 and 2.0, initialized to
     * 1.0 at NvMediaVideoMixer creation. The corresponding
     * attribute mask is \ref NVMEDIA_DISP_ATTR_SATURATION.
     */
    float_t saturation;
    /** \brief A value clamped to between -PI and PI, initialized to
     * 0.0 at NvMediaVideoMixer creation. The corresponding
     * attribute mask is \ref NVMEDIA_DISP_ATTR_HUE.
     */
    float_t hue;
    /** \brief Color standard for video display. One of the following:
     * \n \ref NVMEDIA_COLOR_STANDARD_ITUR_BT_601 (default)
     * \n \ref NVMEDIA_COLOR_STANDARD_ITUR_BT_709
     * \n \ref NVMEDIA_COLOR_STANDARD_SMPTE_240M
     * \n The corresponding attribute mask is
     * \ref NVMEDIA_DISP_ATTR_COLOR_STANDARD.
     */
    NvMediaColorStandard colorStandard;
    /** \brief Limited RGB
     * \ref NVMEDIA_DISP_ATTR_LIMITED_RGB.
     */
    NvMediaBool limitedRGB;
    /** \brief Defines the composition mode for the layer.
     * \n \ref NVMEDIA_DISP_COMP_MODE_OPAQUE
     * \n \ref NVMEDIA_DISP_COMP_MODE_SRC_ALPHA
     * \n \ref NVMEDIA_DISP_COMP_MODE_PREMULTI_SRC_ALPHA
     * \ref NVMEDIA_DISP_ATTR_COMPOSITION.
     */
    NvMediaDispCompMode compositionMode;
    /** \brief Holds a positive value (up to 255) that specifies the video displays
     *  relative to the top-most layer @code(depth == 0)@endcode.
     * \ref NVMEDIA_DISP_ATTR_SET_DEPTH.
     */
    uint32_t depth;
    /** \brief The rectangle where the video renders.
     * \ref NVMEDIA_DISP_ATTR_SET_POSITION.
     */
    NvMediaRect position;
} NvMediaDispAttributes;

/** \defgroup transform Transformations
 *
 * Transformations are used to rotate and mirror the source surface of
 * a blit operation.  The destination rectangle is not affected by any
 * transformation settings.
 *
 * @ref NvMediaTransform identifies the transformations that can be applied
 * as a combination of rotation and mirroring
 *
 * Specifically, given a hypothetical 2x2 image, applying these operations
 * would yield the following results
 * @code
 *
 *       INPUT                      OUTPUT
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |     IDENTITY     | 0 | 1 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 2 | 3 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |    ROTATE_90     | 1 | 3 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 0 | 2 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |    ROTATE_180    | 3 | 2 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 1 | 0 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |    ROTATE_270    | 2 | 0 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 3 | 1 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |  FLIP_HORIZONTAL | 1 | 0 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 3 | 2 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |  INVTRANSPOSE    | 3 | 1 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 2 | 0 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |  FLIP_VERTICAL   | 2 | 3 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 0 | 1 |
 *      +---+---+                  +---+---+
 *
 *      +---+---+                  +---+---+
 *      | 0 | 1 |    TRANSPOSE     | 0 | 2 |
 *      +---+---+ ---------------> +---+---+
 *      | 2 | 3 |                  | 1 | 3 |
 *      +---+---+                  +---+---+
 * @endcode
 */

/**
 * \brief Transformations
 * \ingroup transform
 **/
typedef enum
{
    /** No transformation */
    NVMEDIA_TRANSFORM_NONE = 0x0,
    /** Rotation by 90 degrees */
    NVMEDIA_TRANSFORM_ROTATE_90,
    /** Rotation by 180 degrees */
    NVMEDIA_TRANSFORM_ROTATE_180,
    /** Rotation by 270 degrees */
    NVMEDIA_TRANSFORM_ROTATE_270,
    /** Mirroring in the horizontal */
    NVMEDIA_TRANSFORM_FLIP_HORIZONTAL,
    /**
     * Mirroring along a diagonal axis from the top right to the bottom
     * left of the rectangular region
     */
    NVMEDIA_TRANSFORM_INV_TRANSPOSE,
    /** Mirroring in the vertical direction */
    NVMEDIA_TRANSFORM_FLIP_VERTICAL,
    /**
     * Mirroring along a diagonal axis from the top left to the bottom
     * right of the rectangular region
     */
    NVMEDIA_TRANSFORM_TRANSPOSE
} NvMediaTransform;

/** \brief Noise Reduction Algorithm
 */
typedef enum {
/** \hideinitializer \brief Original (default) noise reduction algorithm. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_ORIGINAL = 0,
/** \hideinitializer \brief Noise reduction algorithm for outdoor low light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_LOW_LIGHT,
/** \hideinitializer \brief Noise reduction algorithm for outdoor medium light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_MEDIUM_LIGHT,
/** \hideinitializer \brief Noise reduction algorithm for outdoor high light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_HIGH_LIGHT,
/** \hideinitializer \brief Noise reduction algorithm for indoor low light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_LOW_LIGHT,
/** \hideinitializer \brief Noise reduction algorithm for indoor medium light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_MEDIUM_LIGHT,
/** \hideinitializer \brief Noise reduction algorithm for indoor high light condition. */
    NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_HIGH_LIGHT
} NvMediaNoiseReductionAlgorithm;

/** @} <!-- Ends common_types_top group NvMedia Types and Structures common to Video & Image --> */

/*
 * \defgroup history_nvmedia_common History
 * Provides change history for the NvMedia Common Types.
 *
 * \section history_nvmedia_common Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b> April 18, 2017
 * - Added \ref NvMediaDecoderInstanceId enum and
 *   \ref NvMediaEncoderInstanceId enum
 * - Changed to use standard data types
 * - Removed input surface rotation and mirroring enumerations and members from
 *   \ref NvMediaEncodeInitializeParamsH264 and \ref NvMediaEncodeInitializeParamsH265
 *
 * <b> Version 1.2 </b> May 4, 2017
 * - Added SLICE_LEVEL_OUTPUT, RTP_MODE_OUTPUT, EXT_PIC_RC_HINT, DYNAMIC_RPS,
 *   MV_BUFFER_DUMP and RECON_CRC features for \ref NvMediaEncodeH264Features
 *   and \ref NvMediaEncodeH265Features
 * - Add bConstFrameQP parameter in \ref NvMediaEncodeRCParams.
 * - Add NvMediaEncAttrType enum and NvMediaNalData data structure.
 *
 * <b> Version 1.3 </b> May 8, 2017
 * - Added \ref numMacroblocksPerSlice in \ref NvMediaEncodeConfigH264
 *   and \ref numCTUsPerSlice in \ref NvMediaEncodeConfigH265.
 *
 * <b> Version 1.4 </b> May 10, 2017
 * - Added LOOP_FILTER_PARAMS, QUANTIZATION_PARAMS, TRANSFORM_MODE, HIGH_PRECISION_MV
 *   and ERROR_RESILIENT features in \ref NvMediaEncodeVP9Features.
 * - Added filter_type, filter_level, sharpness_level, ref_lf_deltas, mode_lf_deltas,
 *   bmode_ref_lf_delta_enabled, bmode_ref_lf_delta_update, base_qindex, delta_y_dc_q,
 *   delta_uv_dc, delta_uv_ac, transform_mode, high_prec_mv and error_resilient
 *   parameters in \ref NvMediaEncodeConfigVP9.
 *
 * <b> Version 1.5 </b> May 17, 2017
 * - Added display_attributes enum defines
 * - Added \ref NvMediaDispCompMode and \ref NvMediaDispAttributes
 *
 * <b> Version 1.6 </b> May 18, 2017
 * - Added NvMediaTransform enum defines
 *
 * <b> Version 1.7 </b> June 05, 2017
 * - Add \ref bSliceDecEnable and \ref NvMediaSliceDecodeData structure member in
 *   \ref NvMediaPictureInfoH265 structure.
 *
 * <b> Version 1.8 </b> June 07, 2017
 * - Added \ref NvMediaEncodeH264POCType enum for H.264 pic_order_cnt_type.
 *   The support is added for pic_order_cnt_type 0 and 2. pic_order_cnt_type 1 is not
 *   not supported.
 * - Added variable pocType of type \ref NvMediaEncodeH264POCType in \ref NvMediaEncodeConfigH264.
 *
 * <b> Version 1.9 </b> June 09, 2017
 * -Added PROFILING feature in \ref NvMediaEncodeH264Features,
 *  \ref NvMediaEncodeH265Features and \ref NvMediaEncodeVP9Features.
 *
 * <b> Version 1.10 </b> June 09, 2017
 * - Removed RECON_CRC features from \ref NvMediaEncodeH264Features
 *   and \ref NvMediaEncodeH265Features and added it as enableReconCRC
 *   for \ref NvMediaEncodeInitializeParamsH264 and \ref
 *   NvMediaEncodeInitializeParamsH265.
 * - Added enableMVC, enableROIEncode and enableSliceEncode
 *   in \ref NvMediaEncodeInitializeParamsH264 and \ref
 *   NvMediaEncodeInitializeParamsH265.
 *
 * <b> Version 1.11 </b> June 22, 2017
 * -Added levelTier parameter in \ref NvMediaEncodeInitializeParamsH265
 *  Added initQP, maxQP parameters in \ref NvMediaEncodeConfigH264,
 *  \ref NvMediaEncodeConfigH265 and \ref NvMediaEncodeConfigVP9.
 *
 * <b> Version 1.12 </b> June 29, 2017
 * -Added feature in \ref NvMediaEncodeH264Features and \ref NvMediaEncodeH265Features,
 *  to enable 4 byte start code.
 *
 * <b> Version 1.13</b> June 30, 2017
 * -Added HEVC MV interface members in \ref NvMediaPictureInfoH265 structure
 *
 * <b> Version 1.14</b> July 26, 2017
 * -Added enableWeightedPrediction in \ref NvMediaEncodeConfigH264 structure *
 *
 * <b> Version 1.15</b> Sept 1, 2017
 * -Added NvMediaEncodeVP8Features, NvMediaEncodeConfigVP8, NvMediaEncodeInitializeParamsVP8
 *  and NvMediaEncodePicParamsVP8 structures *
 *
 * <b> Version 1.16 </b> Sept 13, 2017
 * -Added frameRateNum and frameRateDen parameters in \ref NvMediaEncodePicParamsVP8
 *
 * <b> Version 1.17 </b> Oct 26, 2017
 * -Added useBFramesAsRef parameter in \ref NvMediaEncodeInitializeParamsH264
 *  and \ref NvMediaEncodeInitializeParamsH265
 *
 * <b> Version 1.18 </b> Nov 6, 2017
 * - Added enableTwoPassRC and enableSourceHalfScaled for \ref NvMediaEncodeInitializeParamsH264 and
 *   \ref NvMediaEncodeInitializeParamsH265.
 *
 * <b> Version 1.19 </b> Nov 24, 2017
 * - Added mvNumViews for \ref NvMediaEncodeInitializeParamsH265 and viewId for
 *   \ref NvMediaEncodePicParamsH265. Added mvcNumViews for \ref NvMediaEncodeInitializeParamsH264
 *   and viewId for \ref NvMediaEncodePicParamsH264.
 *
 * <b> Version 1.20 </b> March 16, 2018
 * - Added \ref NvMediaNoiseReductionAlgorithm structure
 *
 * <b> Version 1.21 </b> October 4, 2018
 * - Added Ultrafast encoding support for H.264 for platforms >=T194 in
 *   \ref NvMediaEncodeH264Features
 */


#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_COMMON_H */
