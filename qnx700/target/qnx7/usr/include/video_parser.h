/*
 * Copyright (c) 2011-2018 NVIDIA Corporation.  All Rights Reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

#ifndef _VIDEO_PARSER_H
#define _VIDEO_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvcommon.h"

// RVCT compiler doesn't allow anonymous structures or unions by default.
#if defined(__CC_ARM)
#pragma anon_unions
#endif

#define MAX_FMO_MBCNT           8192
#define MAX_NALS                32

#define DEFAULT_WIDTH_IN_MBS_FOR_AES      120 // This is for 1080p resolution
#define DEFAULT_HEIGHT_IN_MBS_FOR_AES      68 // This is for 1080p resolution
#define MAX_USER_SEI_PAYLOAD              128 // maximum user defined sei payload size

// Compression Standard
typedef enum _NvVideoCompressionStd
{
    NVCS_Unknown    =-1,
    NVCS_MPEG1      =0,
    NVCS_MPEG2      =1,     // 13818
    NVCS_MPEG4      =2,     // 14496-2
    NVCS_VC1        =3,     // VC1
    NVCS_H264       =4,     // 14496-10
    NVCS_H264_MVC   =5,     // H264 MVC
    //NVCS_H264_SVC =6,     // H264 SVC
    NVCS_MJPEG      =7,     // MJPEG
    NVCS_JPEG       =8,     // JPEG
    NVCS_VP8        =9,     // VP8
    NVCS_H265       =10,    // H265
    NVCS_VP9        =11,    // VP9
#if defined(NV_BUILD_CONFIGURATION_EXPOSING_T19X) && (NV_BUILD_CONFIGURATION_EXPOSING_T19X)
    NVCS_H265_MV    =12,    // H265 MV
#endif
} NvVideoCompressionStd;

// Definitions for video_format
enum {
    NVEVideoFormat_Component=0,
    NVEVideoFormat_PAL,
    NVEVideoFormat_NTSC,
    NVEVideoFormat_SECAM,
    NVEVideoFormat_MAC,
    NVEVideoFormat_Unspecified,
    NVEVideoFormat_Reserved6,
    NVEVideoFormat_Reserved7
};

// Definitions for Color Range
enum {
    NVEColorRange_Reduced=0,
    NVEColorRange_Full
};

// Definitions for color_primaries
enum {
    NVEColorPrimaries_Forbidden=0,
    NVEColorPrimaries_BT709,
    NVEColorPrimaries_Unspecified,
    NVEColorPrimaries_Reserved,
    NVEColorPrimaries_BT470M,
    NVEColorPrimaries_BT470BG,
    NVEColorPrimaries_SMPTE170M,
    NVEColorPrimaries_SMPTE240M,
    NVEColorPrimaries_GenericFilm,
    NVEColorPrimaries_BT2020
};

// Definitions for matrix_coefficients
enum {
    NVEMatrixCoefficients_Forbidden=0,
    NVEMatrixCoefficients_BT709,
    NVEMatrixCoefficients_Unspecified,
    NVEMatrixCoefficients_Reserved,
    NVEMatrixCoefficients_FCC,
    NVEMatrixCoefficients_BT470BG,
    NVEMatrixCoefficients_SMPTE170M,
    NVEMatrixCoefficients_SMPTE240M,
    NVEMatrixCoefficients_YCgCo,
    NVEMatrixCoefficients_BT2020_nc,       // non-constant luminance system
    NVEMatrixCoefficients_BT2020_c,        // constant luminance system
};

// Definitions for transfer_characteristics
enum {
    NVETransferCharacteristics_Forbidden=0,
    NVETransferCharacteristics_BT709,
    NVETransferCharacteristics_Unspecified,
    NVETransferCharacteristics_Reserved,
    NVETransferCharacteristics_BT470M,
    NVETransferCharacteristics_BT470BG,
    NVETransferCharacteristics_SMPTE170M,
    NVETransferCharacteristics_SMPTE240M,
    NVETransferCharacteristics_Linear,
    NVETransferCharacteristics_Log100,
    NVETransferCharacteristics_Log316,
    NVETransferCharacteristics_IEC61966_2_4,
    NVETransferCharacteristics_BT1361,
    NVETransferCharacteristics_IEC61966_2_1,
    NVETransferCharacteristics_BT2020_1,    // same 1, 6, 14, 15
    NVETransferCharacteristics_BT2020_2,    // same 1, 6, 14, 15
    NVETransferCharacteristics_SMPTE2084,   // applicable for 10, 12, 14, 16 bit
    NVETransferCharacteristics_ST418_1,
    NVETransferCharacteristics_HLG
};

// Supporting DRM modes
enum {
    NVDrmNetflix = 0,
    NVDrmWidevine = 1,
    NVDrmUltraviolet,
    NVDrmPiff,
    NVDrmMarlin,
    NVDrmPiffCbc,
    NVDrmPiffCtr,
    NVDrmMarlinCbc,
    NVDrmMarlinCtr,
    NVDrmWidevineCtr,
    NVDrmClear = 0xf,
    NVDrmClearAsEncrypted,
    NVDrmNone       // This should be the last element
};

// NAL types found in a bitstream packet
enum
{
    NV_SLH_PRESENT = 0x1,
    NV_SPS_PRESENT = 0x2,
    NV_PPS_PRESENT = 0x4
};

enum
{
    NormalDecode = 0,
    SyncToKeyFrame // Decoder Skips all NonIDR Frames Till Next IDR
};

/** Attribute helps to set/get decoder prpoerties to parse
    * as per client/app requirement */
typedef enum
{
    NVDVideoParserAttribute_SkipFrames=1,
    NVDVideoParserAttribute_AribConstraints,
    NVDVideoParserAttribute_FilterTimestamps,
    NVDVideoParserAttribute_h264DisableDpb,          // Disable DPB logic for low latency H264 playback
    NVDVideoParserAttribute_DecodeIDRFrameOnly,
    NVDVideoParserAttribute_DecodeMode,
    NVDVideoParserAttribute_UseFrameTimingInfo,      // Use frame timing info for PTS calculation
    NVDVideoParserAttribute_SetFramerate,            // Set frame rate for PTS calculation (float type)
    NVDVideoParserAttribute_SetDefaultFramerate,     // Set default frame rate for PTS calculation (float type)
    NVDVideoParserAttribute_DropMPEG2BFrames,        // Drop MPEG2 B-Frames
    NVDVideoParserAttribute_EnableVC1APInterlaced,   // Enable VC-1 advanced profile interlaced
    NVDVideoParserAttribute_MaxDecFrameBuffering,    // Set default H.264 max_dec_frame_buffering
    NVDVideoParserAttribute_AbortDecodeOnParserError, // Abort decoding when unsupported features or erroneous bitstream
    NVDVideoParserAttribute_h265DisableDpb,         // Disable DPB logic for low latency H265 playback
    NVDVideoParserAttribute_SetMaxRes,            // For setting max resolution for creating decoder
    NVDVideoParserAttribute_GenerateSliceOffsets,    // generate slice offsets with CompletePicture mode.
    NVDVideoParserAttribute_DpbSize_SetTo_MaxRefFrames,    // DPB size is set to max number of reference frames
    NVDVideoParserAttribute_ErrorStatusReporting,    // Enable error status reporting
    NVDVideoParserAttribute_SecureDecode,        // Enable m_pSlhData allocation for encrypted streams in parser
    NVDVideoParserAttribute_GetBitstreamError,      // Get bitstream error for current input buffer
    NVDVideoParserAttribute_PrevFrameLostFlag,      // To get the status whether previous frame was lost
    NVDVideoParserAttribute_SliceLevelDecode     //Enable Slice level decode feature using HW decoder. Applicable only for hevc
} NVDVideoParserAttribute;

typedef void NVDPicBuff;

typedef struct _NVMasteringDisplayData
{
    // idx 0 : G, 1 : B, 2 : R
    NvU16 display_primaries_x[3];       // normalized x chromaticity cordinate. It shall be in the range of 0 to 50000
    NvU16 display_primaries_y[3];       // normalized y chromaticity cordinate. It shall be in the range of 0 to 50000
    NvU16 white_point_x;    // normalized x chromaticity cordinate of white point of mastering display
    NvU16 white_point_y;    // normalized y chromaticity cordinate of white point of mastering display
    NvU32 max_display_parameter_luminance;      // nominal maximum display luminance in units of 0.0001 candelas per square metre
    NvU32 min_display_parameter_luminance;      // nominal minimum display luminance in units of 0.0001 candelas per square metre
} NVMasteringDisplayData;

#define MAX_SEQ_HDR_LEN   512        // 512 bytes

// Sequence information
typedef struct _NVDSequenceInfo
{
    NvVideoCompressionStd eCodec;     // Compression Standard
    double fFrameRate;                // Frame Rate stored in the bitstream
    NvS32 nDecodeBuffers;             // Number of decode buffers required
    NvS32 bProgSeq;                   // Progressive Sequence
    NvS32 nDisplayLeftOffset;         // Left offset for display
    NvS32 nDisplayTopOffset;          // Top offset for display
    NvS32 nDisplayWidth;              // Displayed Horizontal Size
    NvS32 nDisplayHeight;             // Displayed Vertical Size
    NvS32 nCodedWidth;                // Coded Picture Width
    NvS32 nCodedHeight;               // Coded Picture Height
    NvS32 nActualWidth;               // Actual Width
    NvS32 nActualHeight;              // Actual Height
    NvU8 nChromaFormat;               // Chroma Format (0=4:0:0, 1=4:2:0, 2=4:2:2, 3=4:4:4)
    NvU8 uBitDepthLumaMinus8;         // Luma bit depth (0=8bit)
    NvU8 uBitDepthChromaMinus8;       // Chroma bit depth (0=8bit)
    NvU8 uReserved1;                  // For alignment
    NvS32 lBitrate;                   // Video bitrate (bps)
    NvS32 lDARWidth, lDARHeight;      // Display Aspect Ratio = lDARWidth : lDARHeight
    NvU32 SARWidth, SARHeight;        // Sample Aspect Ratio
    NvS32 lVideoFormat;               // Video Format (NVEVideoFormat_XXX)
    NvS32 lVideoFullRangeFlag;        // Video Range (0-255) vs (16-235)
    NvS32 lColorPrimaries;            // Colour Primaries (NVEColorPrimaries_XXX)
    NvS32 lTransferCharacteristics;   // Transfer Characteristics
    NvS32 lMatrixCoefficients;        // Matrix Coefficients
    NvS32 cbSequenceHeader;           // Number of bytes in SequenceHeaderData
    NvU32 MaxBitstreamSize;           // maximum size of bitstream buffer
    NvU8 bMasteringDispDataPresent;              // flag to indicated mastering display data is present
    NVMasteringDisplayData MasteringDispData;
    NvU8 SequenceHeaderData[MAX_SEQ_HDR_LEN]; // Raw sequence header data (codec-specific)
    NvU8 ChromaLocTopField;           //chroma_sample_loc_type_top_field
    NvU8 ChomaLocBottomField;         //chroma_sample_loc_type_bottom_field
} NVDSequenceInfo;

typedef struct _NVDEncryptParams
{
    // Encryption params
    NvBool enableEncryption;
    NvU32 drmMode;
    NvU32 InitVector[MAX_NALS][4];
    NvU32 IvValid[MAX_NALS];
    NvU32 BytesOfEncryptedData;
    NvU32 EncryptBlkCnt;    // used for pattern mode encryption
    NvU32 SkipBlkCnt;       // used for pattern mode encryption
    NvU32 numNals;
    NvU32 BOED[MAX_NALS];
    NvU32 BOCD[MAX_NALS];
    NvU32 *AesPass1OutputBuffer;
    NvU32 non_slice_data;
}NVDEncryptParams;

typedef struct _NVMPEG2PictureData
{
    NVDPicBuff *pForwardRef;           // Forward reference (P/B-frames)
    NVDPicBuff *pBackwardRef;          // Backward reference (B-frames)
    NvS32 picture_coding_type;         // TYPE_?FRAME
    NvS32 picture_structure;
    NvS32 full_pel_forward_vector;
    NvS32 full_pel_backward_vector;
    NvS32 f_code[2][2];
    NvS32 intra_dc_precision;
    NvS32 frame_pred_frame_dct;
    NvS32 concealment_motion_vectors;
    NvS32 q_scale_type;
    NvS32 intra_vlc_format;
    NvS32 alternate_scan;

    // Encryption params
    NVDEncryptParams encryptParams;
    // Quantization matrices (raster order)
    NvU8 QuantMatrixIntra[64];
    NvU8 QuantMatrixInter[64];
    NvU8 flag_slices_across_multiple_rows;
} NVMPEG2PictureData;

typedef struct _NVH264DPBEntry
{
    NVDPicBuff *pPicBuf;      // ptr to reference frame
    NvS32 FrameIdx;           // frame_num(short-term) or LongTermFrameIdx(long-term)
    NvS32 is_long_term;       // 0=short term reference, 1=long term reference
    NvS32 is_field;           // 0=frame picture, 1 = field picture
    NvS32 not_existing;       // non-existing reference frame (corresponding PicIdx should be set to -1)
    NvS32 used_for_reference; // 0=unused, 1=top_field, 2=bottom_field, 3=both_fields
    NvS32 FieldOrderCnt[2];   // field order count of top and bottom fields
} NVH264DPBEntry;

typedef struct _NVH264PictureData
{
    // SPS
    NvS32 log2_max_frame_num_minus4;
    NvS32 pic_order_cnt_type;
    NvS32 log2_max_pic_order_cnt_lsb_minus4;
    NvS32 delta_pic_order_always_zero_flag;
    NvS32 frame_mbs_only_flag;
    NvS32 direct_8x8_inference_flag;
    NvS32 num_ref_frames;
    NvS32 residual_colour_transform_flag;
    NvS32 qpprime_y_zero_transform_bypass_flag;
    NvU32 pic_width_in_mbs_minus1;
    NvU32 pic_height_in_map_units_minus1;
    // PPS
    NvS32 num_ref_idx_l0_active_minus1;
    NvS32 num_ref_idx_l1_active_minus1;
    NvS32 weighted_pred_flag;
    NvS32 weighted_bipred_idc;
    NvS32 pic_init_qp_minus26;
    NvS32 redundant_pic_cnt_present_flag;
    NvU8 deblocking_filter_control_present_flag;
    NvU8 transform_8x8_mode_flag;
    NvU8 MbaffFrameFlag;
    NvU8 constrained_intra_pred_flag;
    NvU8 entropy_coding_mode_flag;
    NvU8 pic_order_present_flag;
    NvS8 chroma_qp_index_offset;
    NvS8 second_chroma_qp_index_offset;
    NvS32 frame_num;
    NvS32 CurrFieldOrderCnt[2];
    NvU8 fmo_aso_enable;
    NvU8 scaling_matrix_present;
    NvU8 num_slice_groups_minus1;
    NvU8 slice_group_map_type;
    NvS8 pic_init_qs_minus26;
    NvU32 slice_group_change_rate_minus1;
    NvU8 *pMb2SliceGroupMap;

    // Stereo frame packing SEI
    NvU8 frame_packing_arrangement_type;
    NvU8 content_interpretation_flag;
    NvU8 quincunx_sampling_flag;
    NvU8 spatial_flipping_flag;
    NvU8 frame0_flipped_flag;
    NvU8 field_views_flag;
    NvU8 current_frame_is_frame0_flag;
    NvBool StereoEnabled;

    // SEI user data unregistered SEI message
    NvU32 UserSeiPayloadLength;
    NvU8 UserDefinedSeiPayload[MAX_USER_SEI_PAYLOAD];

    // DPB
    NVH264DPBEntry dpb[16+1];          // List of reference frames within the DPB

    NvS32 last_sps_id;
    NvS32 last_pps_id;

    // Encryption params
    NVDEncryptParams encryptParams;
    NvU32 nal_ref_idc;

    // Quantization Matrices (raster-order)
    NvU8 WeightScale4x4[6][16];
    NvU8 WeightScale8x8[2][64];
    union
    {
        // MVC extension
        struct
        {
            NvU16 num_views_minus1;
            NvU16 view_id;
            NvU8 inter_view_flag;
            NvU8 num_inter_view_refs_l0;
            NvU8 num_inter_view_refs_l1;
            NvU8 MVCReserved8Bits;
            NvU16 InterViewRefsL0[16];
            NvU16 InterViewRefsL1[16];
        } mvcext;
        // SVC extension
        struct
        {
            NvU8 profile_idc;
            NvU8 level_idc;
            NvU8 DQId;
            NvU8 DQIdMax;
            NvU8 disable_inter_layer_deblocking_filter_idc;
            NvU8 ref_layer_chroma_phase_y_plus1;
            NvS8  inter_layer_slice_alpha_c0_offset_div2;
            NvS8  inter_layer_slice_beta_offset_div2;
            NvU16 DPBEntryValidFlag;

            union
            {
                struct
                {
                    NvU8 inter_layer_deblocking_filter_control_present_flag     : 1;
                    NvU8 extended_spatial_scalability_idc                       : 2;
                    NvU8 adaptive_tcoeff_level_prediction_flag                  : 1;
                    NvU8 slice_header_restriction_flag                          : 1;
                    NvU8 chroma_phase_x_plus1_flag                              : 1;
                    NvU8 chroma_phase_y_plus1                                   : 2;
                    NvU8 tcoeff_level_prediction_flag                           : 1;
                    NvU8 constrained_intra_resampling_flag                      : 1;
                    NvU8 ref_layer_chroma_phase_x_plus1_flag                    : 1;
                    NvU8 store_ref_base_pic_flag                                : 1;
                    NvU8 Reserved                                               : 4;
                } f;
                NvU8 ucBitFields[2];
            } spsext;

            union {
                NvS16 seq_scaled_ref_layer_left_offset;
                NvS16 scaled_ref_layer_left_offset;
            } scaledleftoffset;
            union {
                NvS16 seq_scaled_ref_layer_top_offset;
                NvS16 scaled_ref_layer_top_offset;
            } scaledtopoffset;
            union {
                NvS16 seq_scaled_ref_layer_right_offset;
                NvS16 scaled_ref_layer_right_offset;
            } scaledrightoffset;
            union {
                NvS16 seq_scaled_ref_layer_bottom_offset;
                NvS16 scaled_ref_layer_bottom_offset;
            } scaledbottomoffset;
        } svcext;
    } ext;
    void *slcgrp;
    // Video stats specific for H264
    NvS32 slice_type;
} NVH264PictureData;

typedef struct _NVVC1PictureData
{
    NVDPicBuff *pForwardRef;   // Forward reference (P/B-frames)
    NVDPicBuff *pBackwardRef;  // Backward reference (B-frames)
    NVDPicBuff *pRangeMapped;  // Ranged mapped output
    NvS32 FrameWidth;          // Actual frame width
    NvS32 FrameHeight;         // Actual frame height
    NvS32 ptype;               // Picture type
    NvS32 fcm;                 // Frame coding mode
    // SEQUENCE
    NvS32 profile;
    NvS32 postprocflag;
    NvS32 pulldown;
    NvS32 interlace;
    NvS32 tfcntrflag;
    NvS32 finterpflag;
    NvS32 psf;
    NvS32 multires;
    NvS32 syncmarker;
    NvS32 rangered;
    NvS32 maxbframes;
    // ENTRYPOINT
    NvS32 panscan_flag;
    NvS32 refdist_flag;
    NvS32 extended_mv;
    NvS32 dquant;
    NvS32 vstransform;
    NvS32 loopfilter;
    NvS32 fastuvmc;
    NvS32 overlap;
    NvS32 quantizer;
    NvS32 extended_dmv;
    NvS32 range_mapy_flag;
    NvS32 range_mapy;
    NvS32 range_mapuv_flag;
    NvS32 range_mapuv;
    NvS32 rangeredfrm;    // range reduction state

    // Encryption params
    NVDEncryptParams encryptParams;
} NVVC1PictureData;

typedef struct _NVMPEG4PictureData
{
    NVDPicBuff *pForwardRef;           // Forward reference (P/B-frames)
    NVDPicBuff *pBackwardRef;          // Backward reference (B-frames)
    // VOL
    NvS32 video_object_layer_width;
    NvS32 video_object_layer_height;
    NvS32 vop_time_increment_bitcount;
    NvS32 vop_time_increment_resolution;
    NvS32 resync_marker_disable;
    NvS32 quant_type;
    NvS32 quarter_sample;
    NvS32 short_video_header;
    NvS32 divx_flags;
    // VOP
    NvS32 vop_coding_type;
    NvS32 vop_coded;
    NvS32 vop_rounding_type;
    NvS32 alternate_vertical_scan_flag;
    NvS32 interlaced;
    NvS32 vop_fcode_forward;
    NvS32 vop_fcode_backward;
    NvS32 trd[2];
    NvS32 trb[2];
    // shdeshpande : DivX GMC Concealment
    // Flag to prevent decoding of non I-VOPs during a GMC sequence
    // and indicate beginning / end of a GMC sequence.
    NvBool bGMCConceal;
    // Quantization matrices (raster order)
    NvU8 QuantMatrixIntra[64];
    NvU8 QuantMatrixInter[64];
    NvU32 data_partitioned;
    NvU32 reversible_vlc;
} NVMPEG4PictureData;

typedef struct
{
    NvU8 scaling_matrix_present_flag;
    NvU8 scaling_list_type[8]; // scaling_list_type_e
    NvU8 ScalingList4x4[6][16];
    NvU8 ScalingList8x8[2][64];
}NVH264scaling_s;

typedef struct
{
    NvU8 cpb_cnt_minus1;
    NvU32 bit_rate;
    NvU32 cbp_size;
}NVH264hrdparam_s;

typedef struct
{
    NvU16 sar_width;
    NvU16 sar_height;
    NvU8 video_signal_type_present_flag;
    NvU8 video_format;
    NvU8 video_full_range_flag;
    NvU8 colour_description_present_flag;
    NvU8 colour_primaries;
    NvU8 transfer_characteristics;
    NvU8 matrix_coefficients;
    NvU8 timing_info_present_flag;
    NvU32 num_units_in_tick;
    NvU32 time_scale;
    NvU8 fixed_frame_rate_flag;
    NvU8 nal_hrd_parameters_present_flag;
    NvU8 vcl_hrd_parameters_present_flag;
    NvU8 pic_struct_present_flag;
    NvU8 initial_cpb_removal_delay_length;
    NvU8 cpb_removal_delay_length_minus1;
    NvU8 dpb_output_delay_length_minus1;
    NvU8 num_reorder_frames;
    NvU8 max_dec_frame_buffering;
    NVH264hrdparam_s nal_hrd;
    NVH264hrdparam_s vcl_hrd;
}NVH264vuiparam_s;

typedef struct
{
    NvU8 seq_parameter_set_id;
    NvU8 profile_idc;
    NvU8 constraint_set_flags;
    NvU8 level_idc;
    NvU8 chroma_format_idc;
    NvU8 residual_colour_transform_flag;
    NvU8 bit_depth_luma_minus8;
    NvU8 bit_depth_chroma_minus8;
    NvU8 qpprime_y_zero_transform_bypass_flag;
    NvU8 log2_max_frame_num_minus4;
    NvU8 pic_order_cnt_type;
    NvU8 log2_max_pic_order_cnt_lsb_minus4;
    NvU8 delta_pic_order_always_zero_flag;
    NvS32 offset_for_non_ref_pic;
    NvS32 offset_for_top_to_bottom_field;
    NvU8 num_ref_frames_in_pic_order_cnt_cycle;
    NvU8 num_ref_frames;
    NvU8 gaps_in_frame_num_value_allowed_flag;
    NvU32 pic_width_in_mbs_minus1;
    NvU32 pic_height_in_map_units_minus1;
    NvU8 frame_mbs_only_flag;
    NvU8 mb_adaptive_frame_field_flag;
    NvU8 direct_8x8_inference_flag;
    NvU8 frame_cropping_flag;
    NvU32 frame_crop_left_offset;
    NvU32 frame_crop_right_offset;
    NvU32 frame_crop_top_offset;
    NvU32 frame_crop_bottom_offset;
    NvU8 vui_parameters_present_flag;
    NvS32 offset_for_ref_frame[255];
    NVH264scaling_s seq;
    NVH264vuiparam_s vui;
}NVH264SPSData;

typedef struct
{
    NvU8 pic_parameter_set_id;
    NvU8 seq_parameter_set_id;
    NvU8 entropy_coding_mode_flag;
    NvU8 pic_order_present_flag;
    NvU8 num_slice_groups_minus1;
    NvU8 num_ref_idx_l0_active_minus1;
    NvU8 num_ref_idx_l1_active_minus1;
    NvU8 weighted_pred_flag;
    NvU8 weighted_bipred_idc;
    NvS8 pic_init_qp_minus26;
    NvS8 pic_init_qs_minus26;
    NvS8 chroma_qp_index_offset;
    NvS8 second_chroma_qp_index_offset;
    NvU8 deblocking_filter_control_present_flag;
    NvU8 constrained_intra_pred_flag;
    NvU8 redundant_pic_cnt_present_flag;
    NvU8 transform_8x8_mode_flag;
    NvU8 slice_group_map_type;
    NvU32 slice_group_change_rate_minus1;
    NVH264scaling_s pic;
}NVH264PPSData;

typedef struct
{
    NvS32 memory_management_control_operation;
    NvS32 difference_of_pic_nums_minus1;
    NvS32 long_term_frame_idx;
}NVH264SLH_MMCO;

typedef struct _NVH264SLHData
{
    NvS32 first_mb_in_slice;
    NvS32 slice_type_raw;
    NvS32 slice_type;
    NvS32 pic_parameter_set_id;
    NvS32 frame_num;
    NvS32 field_pic_flag;
    NvS32 bottom_field_flag;
    NvS32 idr_pic_id;
    NvS32 pic_order_cnt_lsb;
    NvS32 delta_pic_order_cnt_bottom;
    NvS32 delta_pic_order_cnt[2];
    NvS32 redundant_pic_cnt;
    NvS32 direct_spatial_mv_pred_flag;
    NvS32 num_ref_idx_l0_active_minus1;
    NvS32 num_ref_idx_l1_active_minus1;
    // dec_ref_pic_marking
    NvU8 no_output_of_prior_pics_flag;
    NvU8 long_term_reference_flag;
    NvU8 adaptive_ref_pic_marking_mode_flag;
    NvU8 mmco5; // derived value that indicates presence of an mmco equal to 5
    NVH264SLH_MMCO mmco[72];  // MAX_MMCOS=72

    NvU8 nal_ref_idc;        // extracted from NAL start code
    NvU8 nal_unit_type;      // extracted from NAL start code

    // access_unit_delimiter
    NvS32 primary_pic_type;
    // pic_timing
    NvS32 sei_pic_struct;
    NvS32 IdrPicFlag;
    NvS32 view_id;
    // FMO
    NvU32 slice_group_change_cycle;
} NVH264SLHData;

typedef struct _NVH264HeaderData
{
    NVH264SLHData h264_slh;
    NVH264SPSData h264_sps;
    NVH264PPSData h264_pps;
} NVH264HeaderData;

typedef struct _NVVP8PictureData
{
    NVDPicBuff *pLastRef;            // Last reference frame
    NVDPicBuff *pGoldenRef;          // Golden reference frame
    NVDPicBuff *pAltRef;             // Alternate reference frame
    NvU8 key_frame;
    NvU8 version;
    NvU8 show_frame;
    NvU8 clamp_type;           // 0 means clamp needed in decoder. 1: no clamp needed
    //16
    NvU8 segmentation_enabled;
    NvU8 update_mb_seg_map;
    NvU8 update_mb_seg_data;
    NvU8 update_mb_seg_abs;    // 0 means delta, 1 means absolute value
    NvU8 filter_type;
    NvU8 loop_filter_level;
    NvU8 sharpness_level;
    NvU8 mode_ref_lf_delta_enabled;
    NvU8 mode_ref_lf_delta_update;
    NvU8 num_of_partitions;
    NvU8 dequant_index;
    NvS8 deltaq[5];
    //32
    NvU8 golden_ref_frame_sign_bias;
    NvU8 alt_ref_frame_sign_bias;
    NvU8 refresh_entropy_probs;
    NvU8 CbrHdrBedValue;
    NvU8 CbrHdrBedRange;
    NvU8 mb_seg_tree_probs [3];
    //40
    NvS8 seg_feature[2][4];
    NvS8 ref_lf_deltas[4];
    NvS8 mode_lf_deltas[4];
    //56
    NvU8 BitsConsumed;              //Bit cosumed for current bitstream byte.
    NvU8 AlignByte[3];
    //60
    NvU32 hdr_partition_size;       // Remaining header parition size
    NvU32 hdr_start_offset;         // Start of hdr partition;
    NvU32 hdr_processed_offset;     // Offset to byte which is parsed in cpu
    NvU32 coeff_partition_size[8];
    NvU32 coeff_partition_start_offset[8];
    //136
    NvU32 RetRefreshGoldenFrame;
    NvU32 RetRefreshAltFrame;
    NvU32 RetRefreshLastFrame;
    // Encryption params
    NVDEncryptParams encryptParams;
} NVVP8PictureData;

typedef struct {
    /* last bytes of address 41 */
    NvU8 joints[3];
    NvU8 sign[2];
    /* address 42 */
    NvU8 class0[2][1];
    NvU8 fp[2][3];
    NvU8 class0_hp[2];
    NvU8 hp[2];
    NvU8 classes[2][10];
    /* address 43 */
    NvU8 class0_fp[2][2][3];
    NvU8 bits[2][10];

} nvparser_nmv_context;

/* Adaptive entropy contexts, padding elements are added to have
 * 256 bit aligned tables for HW access.
 * Compile with TRACE_PROB_TABLES to print bases for each table. */
typedef struct nvparser_vp9AdaptiveEntropyProbs_s
{
    /* address 32 */
    NvU8 inter_mode_prob[7][4];
    NvU8 intra_inter_prob[4];

    /* address 33 */
    NvU8 uv_mode_prob[10][8];
    NvU8 tx8x8_prob[2][1];
    NvU8 tx16x16_prob[2][2];
    NvU8 tx32x32_prob[2][3];
    NvU8 sb_ymode_probB[4][1];
    NvU8 sb_ymode_prob[4][8];

    /* address 37 */
    NvU8 partition_prob[2][16][4];

    /* address 41 */
    NvU8 uv_mode_probB[10][1];
    NvU8 switchable_interp_prob[4][2];
    NvU8 comp_inter_prob[5];
    NvU8 mbskip_probs[3];
    NvU8 pad1[1];

    nvparser_nmv_context nmvc;

    /* address 44 */
    NvU8 single_ref_prob[5][2];
    NvU8 comp_ref_prob[5];
    NvU8 pad2[17];

    /* address 45 */
    NvU8 probCoeffs[2][2][6][6][4];
    NvU8 probCoeffs8x8[2][2][6][6][4];
    NvU8 probCoeffs16x16[2][2][6][6][4];
    NvU8 probCoeffs32x32[2][2][6][6][4];

} nvparser_vp9AdaptiveEntropyProbs_t;

/* Entropy contexts */
typedef struct nvparser_vp9EntropyProbs_s
{
    /* Default keyframe probs */
    /* Table formatted for 256b memory, probs 0to7 for all tables followed by
     * probs 8toN for all tables.
     * Compile with TRACE_PROB_TABLES to print bases for each table. */

    NvU8 kf_bmode_prob[10][10][8];

    /* Address 25 */
    NvU8 kf_bmode_probB[10][10][1];
    NvU8 ref_pred_probs[3];
    NvU8 mb_segment_tree_probs[7];
    NvU8 segment_pred_probs[3];
    NvU8 ref_scores[4];
    NvU8 prob_comppred[2];
    NvU8 pad1[9];

    /* Address 29 */
    NvU8 kf_uv_mode_prob[10][8];
    NvU8 kf_uv_mode_probB[10][1];
    NvU8 pad2[6];

    nvparser_vp9AdaptiveEntropyProbs_t a;    /* Probs with backward adaptation */

} nvparser_vp9EntropyProbs_t;

typedef struct {
    NvU32 joints[4];
    NvU32 sign[2][2];
    NvU32 classes[2][11];
    NvU32 class0[2][2];
    NvU32 bits[2][10][2];
    NvU32 class0_fp[2][2][4];
    NvU32 fp[2][4];
    NvU32 class0_hp[2][2];
    NvU32 hp[2][2];

} nvvp9_nmv_context_counts;

/* Counters for adaptive entropy contexts */
typedef struct nvparser_vp9EntropyCounts_s
{
    NvU32 inter_mode_counts[7][3][2];
    NvU32 sb_ymode_counts[4][10];
    NvU32 uv_mode_counts[10][10];
    NvU32 partition_counts[16][4];
    NvU32 switchable_interp_counts[4][3];
    NvU32 intra_inter_count[4][2];
    NvU32 comp_inter_count[5][2];
    NvU32 single_ref_count[5][2][2];
    NvU32 comp_ref_count[5][2];
    NvU32 tx32x32_count[2][4];
    NvU32 tx16x16_count[2][3];
    NvU32 tx8x8_count[2][2];
    NvU32 mbskip_count[3][2];

    nvvp9_nmv_context_counts nmvcount;

    NvU32 countCoeffs[2][2][6][6][4];
    NvU32 countCoeffs8x8[2][2][6][6][4];
    NvU32 countCoeffs16x16[2][2][6][6][4];
    NvU32 countCoeffs32x32[2][2][6][6][4];

    NvU32 countEobs[4][2][2][6][6];

} NVVP9BackwardUpdateCounts;

typedef struct _NVVP9PictureData
{
    NVDPicBuff *pLastRef;            // Last reference frame
    NVDPicBuff *pGoldenRef;          // Golden reference frame
    NVDPicBuff *pAltRef;             // Alternate reference frame
    NvU32    width;
    NvU32    height;
    NvU32    keyFrame;
    NvU32    bit_depth;
    NvU32    prevIsKeyFrame;
    NvU32    PrevShowFrame;
    NvU32    resolutionChange;
    NvU32    errorResilient;
    NvU32    intraOnly;
    NvU8     frameContextIdx;
    NvU8     refFrameSignBias[4];
    NvU32            loopFilterLevel;
    NvU32            loopFilterSharpness;
    /* Quantization parameters */
    NvS32             qpYAc;
    NvS32             qpYDc;
    NvS32             qpChAc;
    NvS32             qpChDc;
    /* From here down, frame-to-frame persisting stuff */
    NvU32             lossless;
    NvU32             transform_mode;
    NvU32             allow_high_precision_mv;
    NvU32             allow_comp_inter_inter;
    NvU32             mcomp_filter_type;
    NvU32             comp_pred_mode;
    NvU32             comp_fixed_ref;
    NvU32             comp_var_ref[2];
    NvU32             log2_tile_columns;
    NvU32             log2_tile_rows;
    NvU32             segmentEnabled;
    NvU32             segmentMapUpdate;
    NvS32             segmentMapTemporalUpdate;
    NvU32             segmentFeatureMode; /* ABS data or delta data */
    NvU8   segmentFeatureEnable[8][4];
    NvS16             segmentFeatureData[8][4];
    NvU32             modeRefLfEnabled;
    NvU32             mbRefLfDelta[4];
    NvU32             mbModeLfDelta[2];
    NvU32             offsetToDctParts;
    NvU32             frameTagSize;

    nvparser_vp9EntropyProbs_t entropy;
    NVVP9BackwardUpdateCounts buCounts;
    // Encryption params
    NVDEncryptParams encryptParams;
} NVVP9PictureData;


typedef struct _NVHEVCPictureData
{
    // sps
    NvU32 pic_width_in_luma_samples;
    NvU32 pic_height_in_luma_samples;
    NvU8 log2_min_luma_coding_block_size_minus3;
    NvU8 log2_diff_max_min_luma_coding_block_size;
    NvU8 log2_min_transform_block_size_minus2;
    NvU8 log2_diff_max_min_transform_block_size;
    NvU8 pcm_enabled_flag;
    NvU8 log2_min_pcm_luma_coding_block_size_minus3;
    NvU8 log2_diff_max_min_pcm_luma_coding_block_size;
    NvU8 bit_depth_luma;
    NvU8 bit_depth_chroma;
    NvU8 pcm_sample_bit_depth_luma_minus1;

    NvU8 pcm_sample_bit_depth_chroma_minus1;
    NvU8 pcm_loop_filter_disabled_flag;
    NvU8 strong_intra_smoothing_enabled_flag;
    NvU8 max_transform_hierarchy_depth_intra;
    NvU8 max_transform_hierarchy_depth_inter;
    NvU8 amp_enabled_flag;
    NvU8 separate_colour_plane_flag;
    NvU8 log2_max_pic_order_cnt_lsb_minus4;

    NvU8 num_short_term_ref_pic_sets;
    NvU8 long_term_ref_pics_present_flag;
    NvU8 num_long_term_ref_pics_sps;
    NvU8 sps_temporal_mvp_enabled_flag;
    NvU8 sample_adaptive_offset_enabled_flag;
    NvU8 scaling_list_enable_flag;
    NvU8 chroma_format_idc;
    NvU8 reserved1[3];

    // pps
    NvU8 dependent_slice_segments_enabled_flag;
    NvU8 slice_segment_header_extension_present_flag;
    NvU8 sign_data_hiding_enabled_flag;
    NvU8 cu_qp_delta_enabled_flag;
    NvU8 diff_cu_qp_delta_depth;
    NvS8 init_qp_minus26;
    NvS8 pps_cb_qp_offset;
    NvS8 pps_cr_qp_offset;

    NvU8 constrained_intra_pred_flag;
    NvU8 weighted_pred_flag;
    NvU8 weighted_bipred_flag;
    NvU8 transform_skip_enabled_flag;
    NvU8 transquant_bypass_enabled_flag;
    NvU8 entropy_coding_sync_enabled_flag;
    NvU8 log2_parallel_merge_level_minus2;
    NvU8 num_extra_slice_header_bits;

    NvU8 loop_filter_across_tiles_enabled_flag;
    NvU8 loop_filter_across_slices_enabled_flag;
    NvU8 output_flag_present_flag;
    NvU8 num_ref_idx_l0_default_active_minus1;
    NvU8 num_ref_idx_l1_default_active_minus1;
    NvU8 lists_modification_present_flag;
    NvU8 cabac_init_present_flag;
    NvU8 pps_slice_chroma_qp_offsets_present_flag;

    NvU8 deblocking_filter_control_present_flag;
    NvU8 deblocking_filter_override_enabled_flag;
    NvU8 pps_deblocking_filter_disabled_flag;
    NvS8 pps_beta_offset_div2;
    NvS8 pps_tc_offset_div2;
    NvU8 tiles_enabled_flag;
    NvU8 uniform_spacing_flag;
    NvU8 num_tile_columns_minus1;
    NvU8 num_tile_rows_minus1;

    NvU16 column_width_minus1[22];
    NvU16 row_height_minus1[20];

    // RefPicSets
    NvU32 iCur;
    NvU32 IDRPicFlag;
    NvU32 RAPPicFlag;
    NvU32 SliceType;
    NvU32 NumDeltaPocsOfRefRpsIdx;
    NvU32 NumPocTotalCurr;
    NvU32 NumPocStCurrBefore;
    NvU32 NumPocStCurrAfter;
    NvU32 NumPocLtCurr;
    NvU32 NumBitsToSkip;
    NvS32 CurrPicOrderCntVal;
    NVDPicBuff *RefPics[16];
    NvS32 PicOrderCntVal[16];
    NvU8 IsLongTerm[16];           // 1=long-term reference
    NvS8 RefPicSetStCurrBefore[8];
    NvS8 RefPicSetStCurrAfter[8];
    NvS8 RefPicSetLtCurr[8];

    // scaling lists (diag order)
    NvU8 ScalingList4x4[6][16];       // [matrixId][i]
    NvU8 ScalingList8x8[6][64];       // [matrixId][i]
    NvU8 ScalingList16x16[6][64];     // [matrixId][i]
    NvU8 ScalingList32x32[2][64];     // [matrixId][i]
    NvU8 ScalingListDCCoeff16x16[6];  // [matrixId]
    NvU8 ScalingListDCCoeff32x32[2];  // [matrixId]

    NvU32 NumDeltaPocs[64];
    NvU8 sps_range_extension_present_flag;
    // sps extension HEVC-main 444
    NvU8 transformSkipRotationEnableFlag ;    //sps extension for transform_skip_rotation_enabled_flag
    NvU8 transformSkipContextEnableFlag ;     //sps extension for transform_skip_context_enabled_flag
    NvU8 implicitRdpcmEnableFlag ;            //sps implicit_rdpcm_enabled_flag
    NvU8 explicitRdpcmEnableFlag ;            //sps explicit_rdpcm_enabled_flag
    NvU8 extendedPrecisionProcessingFlag ;    //sps extended_precision_processing_flag,always 0 in current profile
    NvU8 intraSmoothingDisabledFlag ;         //sps intra_smoothing_disabled_flag
    NvU8 highPrecisionOffsetsEnableFlag ;      //sps high_precision_offsets_enabled_flag
    NvU8 fastRiceAdaptationEnableFlag ;        //sps fast_rice_adaptation_enabled_flag
    NvU8 cabacBypassAlignmentEnableFlag ;      //sps cabac_bypass_alignment_enabled_flag, always 0 in current profile
    NvU8 intraBlockCopyEnableFlag ;            //sps intraBlockCopyEnableFlag, always 0 not used by the spec as of now

    NvU8 pps_range_extension_present_flag;
    // pps extension HEVC-main 444
    NvU8 log2MaxTransformSkipSize ;               //pps extension log2_max_transform_skip_block_size_minus2, 0...5
    NvU8 crossComponentPredictionEnableFlag;   //pps cross_component_prediction_enabled_flag
    NvU8 chromaQpAdjustmentEnableFlag;         //pps chroma_qp_adjustment_enabled_flag
    NvU8 diffCuChromaQpAdjustmentDepth;        //pps diff_cu_chroma_qp_adjustment_depth, 0...3
    NvU8 chromaQpAdjustmentTableSize;          //pps chroma_qp_adjustment_table_size_minus1+1, 1...6
    NvU8 log2SaoOffsetScaleLuma;               //pps log2_sao_offset_scale_luma, max(0,bitdepth-10),maxBitdepth 16 for future.
    NvU8 log2SaoOffsetScaleChroma;             //pps log2_sao_offset_scale_chroma
    NvS8 cb_qp_adjustment[6];                    //-[12,+12]
    NvS8 cr_qp_adjustment[6];                    //-[12,+12]
    NvU8 bMasteringDispDataPresent;              // flag to indicated mastering display data is present
    NVMasteringDisplayData MasteringDispData;
    // Encryption params
    NVDEncryptParams encryptParams;
#if defined(NV_BUILD_CONFIGURATION_EXPOSING_T19X) && (NV_BUILD_CONFIGURATION_EXPOSING_T19X)
    // hevc-mv extension
    struct
    {
        NvU32 mv_hevc_enable;
        NvU32 nuh_layer_id;
        NvU32 default_ref_layers_active_flag;
        NvU32 NumDirectRefLayers;
        NvU32 max_one_active_ref_layer_flag;
        NvU32 NumActiveRefLayerPics;
        NvU32 poc_lsb_not_present_flag;
        NvU32 NumActiveRefLayerPics0;
        NvU32 NumActiveRefLayerPics1;
        NvS32 RefPicSetInterLayer0[32];
        NvS32 RefPicSetInterLayer1[32];
    } mvext;
#endif
} NVHEVCPictureData;

typedef struct _NVDAesMetaData
{
    NvU32 clearHeaderSize;
    NvU8 *clearHeaderPtr;
    NvU32 *AesPass1OutputBuffer;
} NVDAesMetaData;

typedef struct _DecRefFrame
{
    NvBool bPresent;          // present in DPB
    NvBool bIdrFrame;         // Is an IDR
    NvBool bLTRefFrame;       // Long Term Ref Flag
    NvBool bPredicted;        // This frame is motion predicted for current frame as specified in slice header
    NvU32 nPictureOrderCnt;   // POC
    NvU32 nFrameNum;          // FrameNum
    NvU32 nLTRFrameIdx;       // LongTermFrameIdx of a picture
} DecRefFrame;

typedef struct _DecCurrentFrame
{
    NvBool bRefFrame;            // current frame referenced or non-referenced
    NvBool bIdrFrame;            // Is an IDR
    NvBool bLTRefFrame;          // Long Term Ref Flag
    NvU32 nPictureOrderCnt;      // POC
    NvU32 nFrameNum;             // FrameNum
    NvU32 nLTRFrameIdx;          // LongTermFrameIdx of a picture
} DecCurrentFrame;

typedef struct _NVDDpbInfo
{
    NvU32 poc_fn_bits;
    DecCurrentFrame currentFrame;           // property of current decoded frame
    NvU32 nActiveRefFrames;                     // # of valid entries in RPS
    DecRefFrame RPSList[16];  // RPS List as signaled in slice header excluding current frame, only first nActiveRefFrames are valid. This can be different from list of frames in current DPB due to frame loss.
} NVDDpbInfo;

#if NV_BUILD_CONFIGURATION_EXPOSING_T19X
typedef struct
{
    /** Bitstream data*/
    /** Number of bytes in bitstream data buffer */
    NvU32 uBitstreamDataLen;
    /** Ptr to bitstream data for this picture (slice-layer) */
    NvU8 *pBitstreamData;
    /** Number of slices in this SliceData */
    NvU32 uNumSlices;
    /** If not NULL, nNumSlices entries, contains offset of each slice within the bitstream data buffer */
    NvU32 *pSliceDataOffsets;
    /** Number of CTB present in this slice */
    NvU32 uCTBCount;
    /** CTB number of first CTB in the slice data */
    NvU32 uFirstCtbAddr;
    /** First slice flag: whether this SliceData contains first slice of frame */
    NvBool bFirstSlice;
    /** Last slice flag: whether this SliceData contains last slice of frame */
    NvBool bLastSlice;
    /** Single slice flag: whether this is complete frame with only 1 slice */
    NvBool bSingleSliceCase;
} NvVideoParserSliceData;
#endif

typedef struct _NVDPictureData
{
    NvS32 PicWidthInMbs;      // Coded Frame Size
    NvS32 FrameHeightInMbs;   // Coded Frame Height

    NVDPicBuff *pCurrPic; // Current picture (output)

    NvS32 field_pic_flag;     // 0=frame picture, 1=field picture
    NvS32 bottom_field_flag;  // 0=top field, 1=bottom field (ignored if field_pic_flag=0)
    NvS32 second_field;       // Second field of a complementary field pair
    NvS32 progressive_frame;  // Frame is progressive
    NvS32 top_field_first;    // Frame pictures only
    NvS32 repeat_first_field; // For 3:2 pulldown (number of additional fields, 2=frame doubling, 4=frame tripling)
    NvS32 ref_pic_flag;       // Frame is a reference frame
    NvS32 intra_pic_flag;     // Frame is entirely intra coded (no temporal dependencies)
    NvS32 chroma_format;      // Chroma Format (should match sequence info)
    NvS32 picture_order_count; // picture order count (if known)
    // Bitstream data
    NvU32 nBitstreamDataLen;  // Number of bytes in bitstream data buffer
    NvU8 *pBitstreamData;     // Ptr to bitstream data for this picture (slice-layer)
    NvU32 nVp8CoeffPartitionDataLen; // Number of bytes in VP8 Coeff partition (for OTF case)
    NvU32 Vp8CoeffPartitionBuffer;   // Handle to VP8 Coeff partition (for OTF case)
    NvU32 nNumSlices;                // Number of slices in this picture
    NvU32 *pSliceDataOffsets; // nNumSlices entries, contains offset of each slice within the bitstream data buffer
    NvS32 lDARWidth, lDARHeight;      // Display Aspect Ratio = lDARWidth : lDARHeight
    NvS32 displayLeftOffset;         // Left offset for display
    NvS32 displayTopOffset;          // Top offset for display
    NvU32 displayWidth, displayHeight; // Display Width and Height
    NvU32 nal_ref_idc;        // Required only for encrypted bitstreams
    NvS64 frame_time;         // Frame time in time_base units if NVDVideoParserAttribute_UseFrameTimingInfo is enabled
    NvS64 time_base;          // Base time units per second if NVDVideoParserAttribute_UseFrameTimingInfo is enabled
    NvU32 clearHeaderSize;    // Number of bytes in clear header
    NvU8 *pClearHeader;       // Ptr to clear bitstream data for this header
    // Codec-specific data
    union {
        NVMPEG2PictureData mpeg2;   // Also used for MPEG-1
        NVMPEG4PictureData mpeg4;
        NVH264PictureData h264;
        NVVC1PictureData vc1;
        NVVP8PictureData vp8;
        NVHEVCPictureData hevc;
        NVVP9PictureData vp9;
    } CodecSpecific;
    union {
        NVH264HeaderData h264_hdr;
    } CodecSpecificHeaders;

    // Contains the re-encrypted bitstream along with 256 bytes of clearbitstream of slice NAL
    NVDAesMetaData AesMetaData;
#if NV_BUILD_CONFIGURATION_EXPOSING_T19X
    //T194 onwards: slice level decode params for HEVC
    NvVideoParserSliceData SliceInfo;
#endif
    NvBool bSliceDecode; //set to true when slice level decoding is enabled.
} NVDPictureData;

struct _NVDParserContext;
// Abstraction of OS-specific client callbacks
typedef NvS32  (*pfnCbBeginSequence)(void *, const NVDSequenceInfo *);
typedef NvBool (*pfnCbDecodePicture)(void *, NVDPictureData *);
typedef NvBool (*pfnCbDisplayPicture)(void *, NVDPicBuff *, NvS64);
typedef void   (*pfnCbUnhandledNALU)(void *, const NvU8 *, NvS32);
typedef NvBool (*pfnCbAllocPictureBuffer)(void *, NVDPicBuff **);
typedef void   (*pfnCbRelease)(void *, NVDPicBuff *);
typedef void   (*pfnCbAddRef)(void *, NVDPicBuff *);
typedef NvBool (*pfnCbCreateDecrypter)(void *, NvU16 width, NvU16 height);
typedef NvBool (*pfnCbDecryptHdr)(void *, NVDPictureData *);
typedef NvBool (*pfnCbGetHdr)(void *, NVDPictureData *, NvU8 *);
typedef NvBool (*pfnCbUpdateHdr)(void *, NVDPictureData *, NvU8);
typedef NvBool (*pfnCbSliceDecode)(void *, NVDPictureData *);
typedef NvBool (*pfnCbGetClearHdr)(void *, NVDPictureData *);
typedef NvBool (*pfnCbGetBackwardUpdates)(void *, NVDPictureData *);
typedef void   (*pfnCbGetDpbInfoForMetadata)(void *, NVDPicBuff *, NVDDpbInfo *);

typedef struct _NVDClientCb
{
    pfnCbBeginSequence          BeginSequence;
    pfnCbDecodePicture          DecodePicture;
    pfnCbDisplayPicture         DisplayPicture;
    pfnCbUnhandledNALU          UnhandledNALU;
    pfnCbAllocPictureBuffer     AllocPictureBuffer;
    pfnCbRelease                Release;
    pfnCbAddRef                 AddRef;
    pfnCbCreateDecrypter        CreateDecrypter;
    pfnCbDecryptHdr             DecryptHdr;
    pfnCbGetHdr                 GetHdr;
    pfnCbUpdateHdr              UpdateHdr;
    pfnCbSliceDecode            SliceDecode;
    pfnCbGetClearHdr            GetClearHdr;
    pfnCbGetBackwardUpdates     GetBackwardUpdates;
    pfnCbGetDpbInfoForMetadata  GetDpbInfoForMetadata;
} NVDClientCb;

// Initialization parameters for decoder class
typedef struct _NVDParserParams
{
    NVDClientCb *pClient;                   // should always be present if using parsing functionality
    void *pClientCtx;                       // client context
    NvS32 lReferenceClockRate;              // ticks per second of PTS clock (0=default=10000000=10Mhz)
    NvS32 lErrorThreshold;                  // threshold for deciding to bypass of picture (0=do not decode, 100=always decode)
    NvVideoCompressionStd eCodec;           // codec type
    NVDSequenceInfo* pExternalSeqInfo;      // optional external sequence header data
} NVDParserParams;

// Encryption related parameters
typedef struct _NVDAesIv
{
    NvU8    IV[16];
    NvBool  IvValid;
} NVDAesIv;


typedef struct _NVDAesParams
{
    NvU32 drmMode;
    NvU8 *IV;
    NvU32 EncryptBlkCnt;    // used for pattern mode encryption
    NvU32 SkipBlkCnt;       // used for pattern mode encryption
    NvU32 *BOED; // Bytes Of Encrypted Data
    NvU32 *BOCD; // Bytes Of Clear Data
    NvU32 metadataCount;
    NvU32 nonAlignedOffset;
    NVDAesIv IvSet[MAX_NALS];
} NVDAesParams;

// Packet input for parsing
typedef struct _bitstream_packet_s
{
    const NvU8 *pByteStream;  // Ptr to byte stream data
    NvS32 nDataLength;        // Data length for this packet
    NvS32 bEOS;               // TRUE if this is an End-Of-Stream packet (flush everything)
    NvS32 bPTSValid;          // TRUE if llPTS is valid (also used to detect frame boundaries for VC1 SP/MP)
    NvS32 bDiscontinuity;     // TRUE if DecMFT is signalling a discontinuity
    NvS32 bCompletePicture;   // TRUE if this packet contains complete picture
    NvS32 bCompleteSlice;     // TRUE if this packet contains complete Slice
    NvS32 bDecodeNextSlice;   // TRUE if this packet belongs to the same frame currently being decoded
    NvU32 RTP_NALUSizeFieldWidthInBytes; //if it is 0 then it is non-RTP
    NvS64 llPTS;              // Presentation Time Stamp for this packet (clock rate specified at initialization)
} bitstream_packet_s;

typedef void video_parser_context_s;

// Export functions
video_parser_context_s* video_parser_create(NVDParserParams *pnvdp);
void video_parser_destroy(video_parser_context_s *ctx);
NvBool video_parser_parse(video_parser_context_s *ctx, bitstream_packet_s *pkt);
NvBool video_parser_scan(video_parser_context_s *ctx, bitstream_packet_s *pkt);
NvBool video_parser_set_encryption(video_parser_context_s *ctx, NVDAesParams *pAesParams);
void video_parser_flush(video_parser_context_s *ctx);
NvBool video_parser_set_attribute(video_parser_context_s *ctx, NvU32 AttributeType, NvU32 AttributeSize,void *pAttribute);
NvBool video_parser_get_attribute(video_parser_context_s *ctx, NvU32 AttributeType, NvU32 AttributeSize,void *pAttribute);

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif //_VIDEO_PARSER_H
