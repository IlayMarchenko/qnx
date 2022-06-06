/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Surface Handling </b>
 *
 * @b Description: This file contains the
 *                 \ref surface_handling_api "NvMedia Surface Handling API".
 */

#ifndef _NVMEDIA_SURFACE_H
#define _NVMEDIA_SURFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"

/**
 * \defgroup surface_handling_api Surface Handling API
 *
 * Defines and manages image and video surface objects.
 *
 * \ref NvMediaVideoSurface "NvMedia Surfaces" are video RAM surfaces
 * storing YUV, RGBA or RAW data. They can store one or more surfaces depending
 * on the surface types.
 *
 * - For guidance on creating and destroying image surfaces,
 *   see NvMediaImageCreateNew() and NvMediaImageDestroy()
 *   in \ref nvmedia_image_top.
 * - For guidance on creating and destroying video surfaces,
 *   see NvMediaVideoSurfaceCreateNew() and NvMediaVideoSurfaceDestroy() in
 *   in \ref nvmedia_video_top.
 *
 * @ingroup nvmedia_common_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_SURFACE_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_SURFACE_VERSION_MINOR   9


/**
 * \brief Defines NvMedia Surface format attribute types. */
typedef enum {
    /**! Surface type flags. */
    NVM_SURF_ATTR_SURF_TYPE = 0,
    /**! Surface layout type flags. */
    NVM_SURF_ATTR_LAYOUT,
    /**! Surface data type flags. */
    NVM_SURF_ATTR_DATA_TYPE,
    /**! Surface memory type flags. */
    NVM_SURF_ATTR_MEMORY,
    /**! Surface sub sampling type flags. */
    NVM_SURF_ATTR_SUB_SAMPLING_TYPE,
    /**! Bits per component flags. */
    NVM_SURF_ATTR_BITS_PER_COMPONENT,
    /**! Pixel order flags. */
    NVM_SURF_ATTR_COMPONENT_ORDER,
    /**! Maximum number of surface format attributes. */
    NVM_SURF_FMT_ATTR_MAX,
} NvMediaSurfFormatAttrType;

/** \brief NVM_SURF_ATTR_SURF_TYPE flags */
/** YUV surface type flag */
#define NVM_SURF_ATTR_SURF_TYPE_YUV                       0x00000001
/** RGBA surface type flag */
#define NVM_SURF_ATTR_SURF_TYPE_RGBA                      0x00000002
/** RAW surface type flag */
#define NVM_SURF_ATTR_SURF_TYPE_RAW                       0x00000003

/** \brief NVM_SURF_ATTR_LAYOUT flags */
/** Block Linear (BL) surface layout flag */
#define NVM_SURF_ATTR_LAYOUT_BL                           0x00000001
/** Pitch Linear (PL) surface layout flag */
#define NVM_SURF_ATTR_LAYOUT_PL                           0x00000002

/** \brief NVM_SURF_ATTR_DATA_TYPE flags */
/** Unsigned Integer surface data type flag */
#define NVM_SURF_ATTR_DATA_TYPE_UINT                      0x00000001
/** Integer surface data type flag */
#define NVM_SURF_ATTR_DATA_TYPE_INT                       0x00000002
/** Float surface data type flag */
#define NVM_SURF_ATTR_DATA_TYPE_FLOAT                     0x00000003
/** FloatISP surface data type flag */
#define NVM_SURF_ATTR_DATA_TYPE_FLOATISP                  0x00000004

/** \brief NVM_SURF_ATTR_MEMORY flags */
/** Planar surface memory type flag */
#define NVM_SURF_ATTR_MEMORY_PLANAR                       0x00000001
/** Semi-Planar surface memory type flag */
#define NVM_SURF_ATTR_MEMORY_SEMI_PLANAR                  0x00000002
/** Packed surface memory type flag */
#define NVM_SURF_ATTR_MEMORY_PACKED                       0x00000003

/** \brief NVM_SURF_ATTR_SUB_SAMPLING_TYPE flags for YUV surface types
  * "R" indicates a transpose
  */
/** 4:2:0 sub-sampling type flag */
#define NVM_SURF_ATTR_SUB_SAMPLING_TYPE_420               0x00000001
/** 4:2:2 sub-sampling type flag */
#define NVM_SURF_ATTR_SUB_SAMPLING_TYPE_422               0x00000002
/** 4:4:4 sub-sampling type flag */
#define NVM_SURF_ATTR_SUB_SAMPLING_TYPE_444               0x00000003
/** 4:2:2 transposed sub-sampling type flag */
#define NVM_SURF_ATTR_SUB_SAMPLING_TYPE_422R              0x00000004
/** sub-sampling type not applicable flag*/
#define NVM_SURF_ATTR_SUB_SAMPLING_TYPE_NONE              0x00000000

/** \brief NVM_SURF_ATTR_BITS_PER_COMPONENT flags
  * If a layout is not specified, it is a uniform layout across components
  */
/** 8-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_8                 0x00000001
/** 10-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_10                0x00000002
/** 12-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_12                0x00000003
/** 14-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_14                0x00000004
/** 16-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_16                0x00000005
/** 32-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_32                0x00000006

/** 16:8:8 bits per component layout flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_LAYOUT_16_8_8     0x00000007
/** 10:8:8 bits per component layout flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_LAYOUT_10_8_8     0x00000008
/** 2:10:10:10 bits per component layout flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_LAYOUT_2_10_10_10 0x00000009
/** 20-bit per component flag*/
#define NVM_SURF_ATTR_BITS_PER_COMPONENT_20                0x0000000A

/** \brief NVM_SURF_ATTR_COMPONENT_ORDER flags for YUV surface type */
/** Luma component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_LUMA                0x00000001
/** YUV component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_YUV                 0x00000002
/** YVU component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_YVU                 0x00000003
/** YUYV component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_YUYV                0x00000004
/** YVYU component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_YVYU                0x00000005
/** VYUY component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_VYUY                0x00000006
/** UYVY component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_UYVY                0x00000007
/** XUYV component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_XUYV                0x00000008
/** XYUV component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_XYUV                0x00000009
/** VUYX component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_VUYX                0x0000000A

/** \brief NVM_SURF_ATTR_PIXEL_ORDER flags for RGBA surface type */
/** Alpha component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_ALPHA               0x00000011
/** RGBA component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_RGBA                0x00000012
/** ARGB component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_ARGB                0x00000013
/** BGRA component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_BGRA                0x00000014
/** RG component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_RG                  0x00000015

/** \brief NVM_SURF_ATTR_PIXEL_ORDER flags for RAW surface type */
/** RGGB component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_RGGB                0x00000021
/** BGGR component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_BGGR                0x00000022
/** GRBG component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_GRBG                0x00000023
/** GBRG component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_GBRG                0x00000024

/** RCCB component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_RCCB                0x00000025
/** BCCR component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_BCCR                0x00000026
/** CRBC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CRBC                0x00000027
/** CBRC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CBRC                0x00000028

/** RCCC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_RCCC                0x00000029
/** CCCR component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CCCR                0x0000002A
/** CRCC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CRCC                0x0000002B
/** CCRC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CCRC                0x0000002C

/** CCCC component order flag*/
#define NVM_SURF_ATTR_COMPONENT_ORDER_CCCC                0x0000002D

/**
 * \brief Holds NvMedia Surface format attributes.
 */
typedef struct {
    /** \brief Surface Format Attribute Type */
    NvMediaSurfFormatAttrType type;
    /** \brief Surface Format Attribute Value */
    unsigned int value;
} NvMediaSurfFormatAttr;

/**
 * \brief A helper macro to define surface format attributes.
 */
#define NVM_SURF_FMT_DEFINE_ATTR(x)                                                   \
    NvMediaSurfFormatAttr x[] = {                                                     \
        {                                                                             \
            .type = NVM_SURF_ATTR_SURF_TYPE,                                          \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_LAYOUT,                                             \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_DATA_TYPE,                                          \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_MEMORY,                                             \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_SUB_SAMPLING_TYPE,                                  \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_BITS_PER_COMPONENT,                                 \
            .value = 0,                                                               \
        },                                                                            \
        {                                                                             \
            .type = NVM_SURF_ATTR_COMPONENT_ORDER,                                    \
            .value = 0,                                                               \
        },                                                                            \
    };                                                                                \

/**
 * \brief A helper macro to set YUV surface format attributes.
 * attr paramater must be defined before setting the values using \ref NVM_SURF_FMT_SET_ATTR_YUV
 * For NVM_SURF_ATTR_COMPONENT_ORDER_XUYV and NVM_SURF_ATTR_COMPONENT_ORDER_LUMA,
 * set sampling type to be NVM_SURF_ATTR_SUB_SAMPLING_TYPE_NONE
 */
#define NVM_SURF_FMT_SET_ATTR_YUV(attr, order, samplingtype, memory, datatype, bpc, layout)       \
{                                                                                                 \
    attr[0].type = NVM_SURF_ATTR_SURF_TYPE;                                                       \
    attr[0].value = NVM_SURF_ATTR_SURF_TYPE_YUV;                                                  \
                                                                                                  \
    attr[1].type = NVM_SURF_ATTR_LAYOUT;                                                          \
    attr[1].value = NVM_SURF_ATTR_LAYOUT_##layout;                                                \
                                                                                                  \
    attr[2].type = NVM_SURF_ATTR_DATA_TYPE;                                                       \
    attr[2].value = NVM_SURF_ATTR_DATA_TYPE_##datatype;                                           \
                                                                                                  \
    attr[3].type = NVM_SURF_ATTR_MEMORY;                                                          \
    attr[3].value = NVM_SURF_ATTR_MEMORY_##memory;                                                \
                                                                                                  \
    attr[4].type = NVM_SURF_ATTR_SUB_SAMPLING_TYPE;                                               \
    attr[4].value = NVM_SURF_ATTR_SUB_SAMPLING_TYPE_##samplingtype;                               \
                                                                                                  \
    attr[5].type = NVM_SURF_ATTR_BITS_PER_COMPONENT;                                              \
    attr[5].value = NVM_SURF_ATTR_BITS_PER_COMPONENT_##bpc;                                       \
                                                                                                  \
    attr[6].type = NVM_SURF_ATTR_COMPONENT_ORDER;                                                 \
    attr[6].value = NVM_SURF_ATTR_COMPONENT_ORDER_##order;                                        \
}

/**
 * \brief A helper macro to set RGBA surface format attributes.
 * attr paramater must be defined before setting the values using \ref NVM_SURF_FMT_SET_ATTR_RGBA
 */
#define NVM_SURF_FMT_SET_ATTR_RGBA(attr, order, datatype, bpc, layout)                            \
{                                                                                                 \
    attr[0].type = NVM_SURF_ATTR_SURF_TYPE;                                                       \
    attr[0].value = NVM_SURF_ATTR_SURF_TYPE_RGBA;                                                 \
                                                                                                  \
    attr[1].type = NVM_SURF_ATTR_LAYOUT;                                                          \
    attr[1].value = NVM_SURF_ATTR_LAYOUT_##layout;                                                \
                                                                                                  \
    attr[2].type = NVM_SURF_ATTR_DATA_TYPE;                                                       \
    attr[2].value = NVM_SURF_ATTR_DATA_TYPE_##datatype;                                           \
                                                                                                  \
    attr[3].type = NVM_SURF_ATTR_MEMORY;                                                          \
    attr[3].value = NVM_SURF_ATTR_MEMORY_PACKED;                                                  \
                                                                                                  \
    attr[4].type = NVM_SURF_ATTR_SUB_SAMPLING_TYPE;                                               \
    attr[4].value = 0;                                                                            \
                                                                                                  \
    attr[5].type = NVM_SURF_ATTR_BITS_PER_COMPONENT;                                              \
    attr[5].value = NVM_SURF_ATTR_BITS_PER_COMPONENT_##bpc;                                       \
                                                                                                  \
    attr[6].type = NVM_SURF_ATTR_COMPONENT_ORDER;                                                 \
    attr[6].value = NVM_SURF_ATTR_COMPONENT_ORDER_##order;                                        \
}

/**
 * \brief A helper macro to set RAW surface format attributes.
 * Before setting the values, use \ref NVM_SURF_FMT_SET_ATTR_RAW to define \a attr.
 */
#define NVM_SURF_FMT_SET_ATTR_RAW(attr, order, datatype, bpc, layout)                             \
{                                                                                                 \
    attr[0].type = NVM_SURF_ATTR_SURF_TYPE;                                                       \
    attr[0].value = NVM_SURF_ATTR_SURF_TYPE_RAW;                                                  \
                                                                                                  \
    attr[1].type = NVM_SURF_ATTR_LAYOUT;                                                          \
    attr[1].value = NVM_SURF_ATTR_LAYOUT_##layout;                                                \
                                                                                                  \
    attr[2].type = NVM_SURF_ATTR_DATA_TYPE;                                                       \
    attr[2].value = NVM_SURF_ATTR_DATA_TYPE_##datatype;                                           \
                                                                                                  \
    attr[3].type = NVM_SURF_ATTR_MEMORY;                                                          \
    attr[3].value = NVM_SURF_ATTR_MEMORY_PACKED;                                                  \
                                                                                                  \
    attr[4].type = NVM_SURF_ATTR_SUB_SAMPLING_TYPE;                                               \
    attr[4].value = 0;                                                                            \
                                                                                                  \
    attr[5].type = NVM_SURF_ATTR_BITS_PER_COMPONENT;                                              \
    attr[5].value = NVM_SURF_ATTR_BITS_PER_COMPONENT_##bpc;                                       \
                                                                                                  \
    attr[6].type = NVM_SURF_ATTR_COMPONENT_ORDER;                                                 \
    attr[6].value = NVM_SURF_ATTR_COMPONENT_ORDER_##order;                                        \
}

/**
 * \brief Defines NvMedia Surface Allocation attribute types.
 */
typedef enum {
    /**! Surface width */
    NVM_SURF_ATTR_WIDTH,
    /**! Surface height (excluding embedded data lines) */
    NVM_SURF_ATTR_HEIGHT,
    /**! Embedded lines top */
    NVM_SURF_ATTR_EMB_LINES_TOP,
    /**! Embedded lines bottom */
    NVM_SURF_ATTR_EMB_LINES_BOTTOM,
    /**! CPU access to surface flags (default: uncached) */
    NVM_SURF_ATTR_CPU_ACCESS,
    /**! Allocation type, isochronous or secured (default: none) */
    NVM_SURF_ATTR_ALLOC_TYPE,
    /**! Peer VM ID in case of shared buffers */
    NVM_SURF_ATTR_PEER_VM_ID,
    /**! Surface scan type (default: Progressive) */
    NVM_SURF_ATTR_SCAN_TYPE,
    /**! Color Standard type (default:
     *   YCbCr Rec.601 (Extended Range) for YUV surface types,
     *   sRGB for RGB surface types)
     */
    NVM_SURF_ATTR_COLOR_STD_TYPE,
    /**! Maximum number of surface allocation attributes */
    NVM_SURF_ALLOC_ATTR_MAX,
} NvMediaSurfAllocAttrType;

/** \brief NVM_SURF_ATTR_CPU_ACCESS flags
  */
/** Uncached (mapped) access type flag */
#define NVM_SURF_ATTR_CPU_ACCESS_UNCACHED                 0x00000001
/** Cached (mapped) access type flag */
#define NVM_SURF_ATTR_CPU_ACCESS_CACHED                   0x00000002
/** Unmapped access type flag */
#define NVM_SURF_ATTR_CPU_ACCESS_UNMAPPED                 0x00000003

/** \brief NVM_SURF_ATTR_ALLOC_TYPE flags
  */
/** Isochronous buffer allocation flag */
#define NVM_SURF_ATTR_ALLOC_ISOCHRONOUS                   0x00000001
/** Secured buffer allocation flag */
#define NVM_SURF_ATTR_ALLOC_SECURED                       0x00000002

/** \brief NVM_SURF_ATTR_SCAN_TYPE flags
  */
/** Progressive surface scan type flag */
#define NVM_SURF_ATTR_SCAN_PROGRESSIVE                    0x00000001
/** Interlaced surface scan type flag */
#define NVM_SURF_ATTR_SCAN_INTERLACED                     0x00000002

/** \brief NVM_SURF_ATTR_COLOR_STD_TYPE flags
  */
/** sRGB Color Std flag
  * Range [RGB:0-255]
  */
#define NVM_SURF_ATTR_COLOR_STD_SRGB                      0x00000001
/** YCbCr Rec.601 (Studio Range) Color Std flag
  * Range [Y:16-235 CbCr:16-240]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC601_SR                 0x00000002
/** YCbCr Rec.601 (Extended Range) Color Std flag
  * Range [YCbCr:0-255]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC601_ER                 0x00000003
/** YCbCr Rec.709 (Studio Range) Color Std flag
  * Range [Y:16-235 CbCr:16-240]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC709_SR                 0x00000004
/** YCbCr Rec.709 (Extended Range) Color Std flag
  * Range [YCbCr:0-255]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC709_ER                 0x00000005
/** RGB Rec.2020 Color Std flag
  * Range [RGB:0-1023 (10-bit),
  *            0-4095 (12-bit),
  *            0-65535(16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC2020_RGB               0x00000006
/** YCbCr Rec.2020 (Studio Range) Color Std flag
  * Range [Y:64-940     CbCr:64-960    (10-bit),
  *        Y:256-3760   CbCr:256-3840  (12-bit),
  *        Y:1024-60160 CbCr:1024-61440(16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC2020_SR                0x00000007
/** YCbCr Rec.2020 (Extended Range) Color Std flag
  * Range [YCbCr:0-1023 (10-bit),
  *              0-4095 (12-bit),
  *              0-65535(16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC2020_ER                0x00000008
/** YcCbcCrc Rec.2020 (Studio Range) Color Std flag
  * Range [Y:64-940     CbCr:64-960    (10-bit),
  *        Y:256-3760   CbCr:256-3840  (12-bit),
  *        Y:1024-60160 CbCr:1024-61440(16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_YcCbcCrc_SR               0x00000009
/** YcCbcCrc Rec.2020 (Extended Range) Color Std flag
  * Range [YCbCr:0-1023 (10-bit),
  *              0-4095 (12-bit),
  *              0-65535(16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_YcCbcCrc_ER               0x0000000A

/** Sensor RGBA Color Std flag
  * This color std flag is used to represent
  * demosaiced and white-balanced sensor bayer
  * data in linear space.
  * Range [RGBA: 0.0 -1.0 (16-bit float)]
  */
#define NVM_SURF_ATTR_COLOR_STD_SENSOR_RGBA               0x0000000B

/** YCbCr Rec.2020PQ (Extended Range) Color Std flag
  * Range [YCbCr:0-65535 (16-bit)]
  */
#define NVM_SURF_ATTR_COLOR_STD_REC2020PQ_ER              0x0000000C

/**
 * \brief Holds NvMedia Surface allocation attributes.
 */
typedef struct {
    /** \brief Surface Allocation Attribute Type */
    NvMediaSurfAllocAttrType type;
    /** \brief Surface Allocation Attribute Value */
    unsigned int value;
} NvMediaSurfAllocAttr;

/**
 * \brief Defines the set of NvMedia surface types.
 */
#define NvMediaSurfaceType    unsigned int

/** Video surface for 4:2:0 format video decoders.
  The actual physical surface format is selected based
  on the chip architecture. */
#define NvMediaSurfaceType_Video_420                                  1000
#define NvMediaSurfaceType_Video_420_10bit                            1001
#define NvMediaSurfaceType_Video_420_12bit                            1002
/** Video surface for 4:2:2 format video decoders.
  The actual physical surface format is selected based
  on the chip architecture. */
#define NvMediaSurfaceType_Video_422                                  1003
#define NvMediaSurfaceType_Video_422_10bit                            1004
#define NvMediaSurfaceType_Video_422_12bit                            1005
/** Video surface for 4:4:4 format video decoders.
  The actual physical surface format is selected based
  on the chip architecture. */
#define NvMediaSurfaceType_Video_444                                  1006
#define NvMediaSurfaceType_Video_444_10bit                            1007
#define NvMediaSurfaceType_Video_444_12bit                            1008
/** Video capture surface for 4:2:2 format. */
#define NvMediaSurfaceType_VideoCapture_422                           1009
/** Video capture surface for YUYV format. */
#define NvMediaSurfaceType_VideoCapture_YUYV_422                      1010
/** R8G8B8A8 surface type. */
#define NvMediaSurfaceType_R8G8B8A8                                   1011
/** R8G8B8A8 surface type used for video rendering.
    Surfaces that are interacting with EGL Stream
    functions must be in this format. */
#define NvMediaSurfaceType_R8G8B8A8_BottomOrigin                      1012
/** Monochrome image. */
#define NvMediaSurfaceType_Image_Monochrome                           1013
/** 4:2:0 format image. */
#define NvMediaSurfaceType_Image_YUV_420                              1014
/** 4:2:2 format image. */
#define NvMediaSurfaceType_Image_YUV_422                              1015
/** 4:4:4 format image. */
#define NvMediaSurfaceType_Image_YUV_444                              1016
/** 4:2:2 format packed image with YUYV component order. */
#define NvMediaSurfaceType_Image_YUYV_422                             1017
/** RGBA image type */
#define NvMediaSurfaceType_Image_RGBA                                 1018
/** RAW image type */
#define NvMediaSurfaceType_Image_RAW                                  1019
/** 4:4:4:4 format packed image with VYUX component order. */
#define NvMediaSurfaceType_Image_V16Y16U16X16                         1020
/** 16-bit Y data image. */
#define NvMediaSurfaceType_Image_Y16                                  1021
/** 4:4:4:4 format packed image with XUYV component order. */
#define NvMediaSurfaceType_Image_X2U10Y10V10                          1022
/** 4:2:0 semi-planar YUV */
#define NvMediaSurfaceType_Image_Y10U8V8_420                          1023
/** 10-bit Y data image. */
#define NvMediaSurfaceType_Image_Y10                                  1024
/** A8 alpha surface */
#define NvMediaSurfaceType_A8                                         1025
/** Unsupported types */
#define NvMediaSurfaceType_Unsupported                                99999

/** Obsolete 4:2:0 video surface type */
#define NvMediaSurfaceType_YV12 NvMediaSurfaceType_Video_420
/** Obsolete 4:2:2 video surface type */
#define NvMediaSurfaceType_YV16 NvMediaSurfaceType_Video_422
/** Obsolete 4:4:4 video surface type */
#define NvMediaSurfaceType_YV24 NvMediaSurfaceType_Video_444
/** Obsolete 4:2:2 video capture surface type */
#define NvMediaSurfaceType_YV16x2 NvMediaSurfaceType_VideoCapture_422

/**
 * \brief Gets the NvMedia surface format type for the input surface format attributes.
 * \param[in] attrs An array of surface format attributes.
 * \param[in] numAttrs Number of attributes in the array.
 * \return \ref NvMediaSurfaceType for the input attributes (or) NvMediaSurfaceType_Unsupported if unsuccessful.
 */
NvMediaSurfaceType
NvMediaSurfaceFormatGetType(
    NvMediaSurfFormatAttr *attrs,
    unsigned int numAttrs
);

/**
 * \brief Gets NvMedia surface format attributes for the input surface type.
 * \param[in] type NvMediaSurfacetype of the surface.
 * \param[in] attrs A pointer to array of \ref NvMediaSurfFormatAttr.
 *                  The attribute value is returned for the input attribute
 *                  type \ref NvMediaSurfFormatAttrType for each array element.
 * \param[in] numAttrs Number of attributes in the array.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \n \ref NVMEDIA_STATUS_NOT_SUPPORTED
 */

NvMediaStatus
NvMediaSurfaceFormatGetAttrs(
    NvMediaSurfaceType type,
    NvMediaSurfFormatAttr *attrs,
    unsigned int numAttrs
);

/**
 * \brief Returns the version information for the NvMediaSurface component
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    to be filled by the NvMediaSurface component.
 * \retval NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaSurfaceGetVersion(
    NvMediaVersion *version
);

/*
 * \defgroup history_nvmedia_surface History
 * Provides change history for the NvMedia Surface API.
 *
 * \section history_nvmedia_surface Version History
 *
 * <b> Version 1.0 </b> March 1, 2017
 * - Initial release
 *
 *
 * <b> Version 1.1 </b> April 24, 2017
 * - Added NVM_SURF_ATTR_COMPONENT_ORDER_XYUV and
 *   NVM_SURF_ATTR_COMPONENT_ORDER_RG component order flags
 *
 * <b> Version 1.2 </b> May 18, 2017
 * - Added NVM_SURF_ATTR_COLOR_STD_TYPE and
 *   NVM_SURF_ATTR_COLOR_STD flags
 *
 * <b> Version 1.3 </b> June 08, 2017
 * - Removed NvMediaSurfaceType_Image_NonColor_S16_XY and
 *   NvMediaSurfaceType_Image_NonColor_S16_X surface types
 *
 * <b> Version 1.4 </b> June 12, 2017
 * - Added NVM_SURF_ATTR_COMPONENT_ORDER_VUYX flag
 *
 * <b> Version 1.5 </b> October 09, 2017
 * - Added NVM_SURF_ATTR_COLOR_STD_SENSOR_RGBA and
 *   NVM_SURF_ATTR_COLOR_STD_REC2020PQ_ER flags
 *
 * <b> Version 1.6 </b> October 31, 2017
 * - Added NVM_SURF_ATTR_DATA_TYPE_FLOATISP type
 *
 * <b> Version 1.7 </b> November 07, 2017
 * - Added NVM_SURF_ATTR_BITS_PER_COMPONENT_20
 *
 * <b> Version 1.8 </b> June 04, 2018
 * - Added NVM_SURF_ATTR_COMPONENT_ORDER_CCCC component order
 *
 * <b> Version 1.9 </b> July 10, 2018
 * - Added NvMediaSurfaceGetVersion API
 *
 */
/*@}*/

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_SURFACE_H */
