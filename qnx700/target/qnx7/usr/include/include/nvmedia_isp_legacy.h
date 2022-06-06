/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Signal Processing</b>
 *
 * @b Description: This file contains the \ref image_isp_api_legacy "Image Signal Processing API (Legacy)".
 */

#ifndef _NVMEDIA_ISP_LEGACY_H
#define _NVMEDIA_ISP_LEGACY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_image.h"

/**
 * \defgroup image_isp_api_legacy Image Signal Processing (Legacy)
 *
 * The Image Signal Processing API encompasses all NvMedia image processing
 * functions that are necessary to produce a processed image from image data
 * captured from an image sensor.
 *
 * @ingroup nvmedia_image_top
 * @{
 */


/** \brief  Major version number. */
#define NVMEDIA_ISP_VERSION_MAJOR   1
/** \brief  Minor version number. */
#define NVMEDIA_ISP_VERSION_MINOR   7

/**
 * \defgroup image_isp_types_legacy Basic ISP Types (Legacy)
 * The Image Signal Processing API provides common ISP processing functions.
 * @ingroup basic_api_top
 *
 * @{
 */

/**
 * \brief  Specifies which ISP to use.
 */
typedef enum {
    /** \brief  Selects ISP A. */
    NVMEDIA_ISP_SELECT_ISP_A,
    /** \brief  Selects ISP B. */
    NVMEDIA_ISP_SELECT_ISP_B
} NvMediaISPSelect;

enum {
    /** Specifies the number of color components. */
    NVMEDIA_ISP_COLOR_COMPONENT_NUM = 4
};

enum {
    NVMEDIA_ISP_COLOR_COMPONENT_0 = 0
};
enum {
    NVMEDIA_ISP_COLOR_COMPONENT_1 = 1
};
enum {
    NVMEDIA_ISP_COLOR_COMPONENT_2 = 2
};
enum {
    NVMEDIA_ISP_COLOR_COMPONENT_3 = 3
};
enum {
    NVMEDIA_ISP_COLOR_COMPONENT_MAX = 4
};

/**
 * Specifies color component positions.
 */
enum {
    /** Specifies the top left pixel position. */
    NVMEDIA_ISP_COLOR_COMPONENT_TL = NVMEDIA_ISP_COLOR_COMPONENT_0,
    /** Specifies the top right pixel position. */
    NVMEDIA_ISP_COLOR_COMPONENT_TR = NVMEDIA_ISP_COLOR_COMPONENT_1,
    /** Specifies the bottom left pixel position. */
    NVMEDIA_ISP_COLOR_COMPONENT_BL = NVMEDIA_ISP_COLOR_COMPONENT_2,
    /** Specifies the bottom right pixel position. */
    NVMEDIA_ISP_COLOR_COMPONENT_BR = NVMEDIA_ISP_COLOR_COMPONENT_3
};

enum {
    /** Specifies the number of color components in a triplet. */
    NVMEDIA_ISP_COLOR_COMPONENT_TRIPLET_NUM = 3
};


enum {
    NVMEDIA_ISP_HDR_SAMPLE_MAP_NUM = 16
};

enum {
    NVMEDIA_ISP_HIST_RANGE_CFG_NUM = 8
};
enum {
    NVMEDIA_ISP_LAC_ROI_NUM = 4
};
enum {
    NVMEDIA_ISP_AFM_ROI_NUM = 8
};
enum {
    NVMEDIA_ISP_AFM_FILTER_COEFF_NUM = 6
};

/**
 * Defines the ISP color channels.
 */
typedef enum
{
    NVMEDIA_ISP_COLORCHANNEL_TL_R_V = NVMEDIA_ISP_COLOR_COMPONENT_0,
    NVMEDIA_ISP_COLORCHANNEL_TR_G_Y,
    NVMEDIA_ISP_COLORCHANNEL_BL_B_U,
    NVMEDIA_ISP_COLORCHANNEL_BR,
    NVMEDIA_ISP_COLORCHANNEL_LUMINANCE,

    NVMEDIA_ISP_COLORCHANNEL_FORCE32 = 0x7FFFFFFF
} NvMediaISPColorChannel;

/**
 * Defines the ISP pixel format types.
 */
typedef enum {
    /** Specifies RGB pixel format. */
    NVMEDIA_ISP_PIXELFORMAT_RGB = 0x1,
    /** Specifies YUV pixel format. */
    NVMEDIA_ISP_PIXELFORMAT_YUV,
    /** Specifies quad pixel format. */
    NVMEDIA_ISP_PIXELFORMAT_QUAD
} NvMediaISPPixelFormat;

/**
 * Defines the HDR mode types.
 */
typedef enum
{
    /** Specifies that samples are not distinguished and all are used as
     short exposure pixels. */
    NVMEDIA_ISP_HDR_MODE_NORMAL = 0x1,
    /** Specifies short exposure pixels. */
    NVMEDIA_ISP_HDR_MODE_SHORT,
    /** Specifies long exposure pixels. */
    NVMEDIA_ISP_HDR_MODE_LONG,
    /** Specifies that the HDR contains both short and long exposure pixels. */
    NVMEDIA_ISP_HDR_MODE_BOTH,
    /** @b Applies @b to: code-name Parker; specifies to handle long and
     short exposure pixels separately. */
    NVMEDIA_ISP_HDR_MODE_SEPARATE,

    NVMEDIA_ISP_HDR_MODE_FORCE32 = 0x7FFFFFFF
} NvMediaISPHdrMode;

/**
 * Holds an integer range.
 */
typedef struct
{
    /**  Holds the lower limit of the range. */
    int low;
    /**  Holds the upper limit of the range. */
    int high;
} NvMediaISPRange;

/**
 * Holds a float range.
 */
typedef struct
{
    /** Holds the lower limit of the range. */
    float low;
    /** Holds the upper limit of the range. */
    float high;
} NvMediaISPRangeFloat;

/**
 * Holds a two-dimensional surface which is
 * determined by the surface height and width in pixels.
 */
typedef struct
{
    /** Holds the width of the surface in pixels. */
    int width;
    /** Holds the height of the surface in pixels. */
    int height;
} NvMediaISPSize;

/**
 * Holds the coordinates of a point on a two-dimensional object,
 * where the coordinate (0,0) is at the top left of the object. The
 * values of x and y are in pixels.
 */
typedef struct
{
    /** Holds the horizontal coordinate of the point. */
    int x;
    /** Holds the vertical coordinate of the point. */
    int y;
} NvMediaISPPoint;

/**
 * Holds the coordinates of a point on a two-dimensional object,
 * where the coordinate (0,0) is at the top left of the object.  The
 * values of x and y are in pixels.
 */
typedef struct
{
    /** Holds the horizontal coordinate of the point. */
    float x;
    /** Holds the vertical coordinate of the point. */
    float y;
} NvMediaISPFloatPoint;

/** @} <!-- Ends image_isp_types_legacy Basic ISP Types --> */

/**
 * \defgroup isp_frame_stats_legacy ISP Statistics (Legacy)
 * Defines ISP statistics types, settngs, and functions.
 * @{
 */

/**
 * Defines the ISP statistics selector types.
 */
typedef enum
{
    /** Specifies histogram statistics. */
    NVMEDIA_ISP_STATS_HISTOGRAM = 1,
    /** Specifies local average and clipped statistics. */
    NVMEDIA_ISP_STATS_LAC,
    /** Specifies flicker band statistics. */
    NVMEDIA_ISP_STATS_FLICKER_BAND,
    /** Specifies focus metric statistics. */
    NVMEDIA_ISP_STATS_FOCUS_METRIC,
    /** Specifies histogram statistics for ISP version 4. */
    NVMEDIA_ISP_STATS_HISTOGRAM_V4,
    /** Specifies local average and clipped statistics for ISP version 4. */
    NVMEDIA_ISP_STATS_LAC_V4,
    /** Specifies flicker band statistics for ISP version 4. */
    NVMEDIA_ISP_STATS_FLICKER_BAND_V4,
    /** Specifies focus metric statistics_V4 for ISP version 4. */
    NVMEDIA_ISP_STATS_FOCUS_METRIC_V4,
    /** Specifies histogram statistics for ISP version 5. */
    NVMEDIA_ISP_STATS_HISTOGRAM_V5,
    /** Specifies local average and clipped statistics for ISP version 5. */
    NVMEDIA_ISP_STATS_LAC_V5,
    /** Specifies flicker band statistics for ISP version 5. */
    NVMEDIA_ISP_STATS_FLICKER_BAND_V5,
    /** Specifies local tone map statistics for ISP version 5. */
    NVMEDIA_ISP_STATS_LTM_V5,
    /** Specifies outlier rejection statistics for ISP version 5. */
    NVMEDIA_ISP_STATS_OR_V5
} NvMediaISPStats;

/**
 * Holds the settings for the histogram statistics of ISP version 4.
 */
typedef struct
{
    /** Holds a Boolean that enables histogram statistics. */
    NvMediaBool enable;

    /** Holds the pixel format on which a client wants this instance to operate. */
    NvMediaISPPixelFormat pixelFormat;

    /**
     * Holds range of pixel values to be considered for each zone. The pixel
     * range is divided in to 8 zones.
     *
     * Values 0-2 and 13-15 may not be used. The valid values and the
     * correponding log 2 ranges are:
     * @code
     * 3 : Range = 8
     * 4 : Range = 16
     * 5 : Range = 32
     * 6 : Range = 64
     * 7 : Range = 128
     * 8 : Range = 256
     * 9 : Range = 512
     * 10 : Range = 1024
     * 11 : Range = 2048
     * 12 : Range = 4096
     * @endcode
     */
    unsigned char range[NVMEDIA_ISP_HIST_RANGE_CFG_NUM];

    /**
     * Holds the coeffcients for the curve that defines the mapping of input
     * pixel range to bins. The curve between two knee points is linearly
     * interpolated. Knee[-1] = 0 and Knee[7] = 255 (the total number of
     * bins&nbsp;-&nbsp;1).
     */
    unsigned char knee[NVMEDIA_ISP_HIST_RANGE_CFG_NUM];

    /**
     * Holds an offset to be applied to the input data prior to performing
     * the bin mapping operation.
     */
    float offset;

    /** Holds the definition of a window to construct the histogram. */
    NvMediaRect window;

    /**
     * Holds an HDR interleave pattern.
     *
     * Example:
     * @code
     * 1 1 1 1      1 1 0 0     1 1 0 0
     * 1 1 1 1  OR  1 1 0 0 OR  1 1 0 0
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * @endcode
     */
    unsigned char  hdrSampleMap[NVMEDIA_ISP_HDR_SAMPLE_MAP_NUM];

    /** Holds the HDR mode. */
    NvMediaISPHdrMode   hdrMode;
} NvMediaISPStatsHistogramSettingsV4;

/**
 * Holds a histogram statistics measurement.
 */
typedef struct
{
    /**
     * Holds the number of bins in the histogram of each color component.
     * All color components must have the same number of bins.
     */
    unsigned int numBins;

    /**
     * Holds an array of pointers to the histogram data for different color
     * components. Use the indices based on the color space on which the
     * histogram is gathered.
     * - For Bayer, use `NVMEDIA_ISP_COLOR_COMPONENT_[TL|TR|BL|BR]`.
     * - For YUV, use `NVMEDIA_ISP_COLOR_COMPONENT_[Y|U|V]`.
     * - For RGB, use `NVMEDIA_ISP_COLOR_COMPONENT_[R|G|B]`.
     */
    unsigned int *data[NVMEDIA_ISP_COLOR_COMPONENT_NUM];
} NvMediaISPStatsHistogramMeasurement;

/**
 * Holds definitions of the windows used in ISP statistics calculations.
 *
 * \code
 *      -------------------------------------------------------------------
 *      |                                                                 |
 *      |      StartOffset                                                |
 *      |     /                                                           |
 *      |     ********        ********        ********  -                 |
 *      |     *      *        *      *        *      *  |                 |
 *      |     *      *        *      *        *      *  |                 |
 *      |     *      *        *      *        *      *  |                 |
 *      |     ********        ********        ********  |                 |
 *      |     |---------------|                         |   \             |
 *      |      HorizontalInterval   VerticalInterval--->|     VerticalNum |
 *      |                                               |   /             |
 *      |     ******** -      ********        ********  -                 |
 *      |     *      * |      *      *        *      *                    |
 *      |     *      * |      *      *        *      *                    |
 *      |     *      * |      *      *        *      *                    |
 *      |     ******** -      ********        ********                    |
 *      |     |------| \                                                  |
 *      |               Size                                              |
 *      |                                                                 |
 *      |                   \     |     /                                 |
 *      |                   HorizontalNum                                 |
 *      |                                                                 |
 *      -------------------------------------------------------------------
 * \endcode
 */
typedef struct
{
    /** Holds the size of each window. */
    NvMediaISPSize size;

    /** Holds the horizontal number of windows. */
    unsigned int horizontalNum;
    /** Holds the vertical number of windows. */
    unsigned int verticalNum;

    /** Holds the distance between the left edges of one window and a
     horizontally adjacent window. */
    unsigned int horizontalInterval;

    /** Holds the distance between the top edges of one window and a vertically
     adjacent window. */
    unsigned int verticalInterval;

    /** Holds the position of the top left pixel in the top left window. */
    NvMediaISPPoint startOffset;
} NvMediaISPStatsWindows;

/**
 * Holds the settings to use for LAC statistics for ISP version 4.
 */
typedef struct
{
    /** Holds a Boolean that enables LAC statistics. */
    NvMediaBool enable;

    /** Holds a Boolean that enables each ROI region. */
    NvMediaBool ROIEnable[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Indicates whether pixels are in Bayer format or triplets (YUV/RGB+Y). */
    NvMediaISPPixelFormat pixelFormat;

    /**
     * Holds an array that is used to convert RGB to Y when LAC is gathered on
     * RGB. Use NVMEDIA_ISP_COLOR_COMPONENT_[R|G|B] for the indices.
     *
     * Y = sum of (X + rgbToYOffset[X]) * rgbToYGain[X]) over X = {R, G, B}
     * \n rgbToYOffset range [-1.0, 1.0)
     */
    float rgbToYOffset[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds rgbToYGain range [0, 1.0). */
    float rgbToYGain[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /**
     * Holds the range of each color component to be used in the calculation
     * of the average. Range is [-0.5, 1.5) for RGBY, and [-1.0, 1.0) for UV.
     */
    NvMediaISPRangeFloat range[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds definitions of windows for LAC calculation for each ROI. */
    NvMediaISPStatsWindows windows[NVMEDIA_ISP_LAC_ROI_NUM];

    /**
     * Holds the HDR interleave pattern.
     *
     * Example:
     * @code
     * 1 1 1 1      1 1 0 0     1 1 0 0
     * 1 1 1 1  OR  1 1 0 0 OR  1 1 0 0
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * @endcode
     */
    unsigned char  hdrSampleMap[NVMEDIA_ISP_HDR_SAMPLE_MAP_NUM];

    /**
     * Holds HDR mode for each ROI. If an ROI is not enabled, just
     * use the first value in the array and ignore the others.
     */
    NvMediaISPHdrMode   hdrMode[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds a value that is used to determine long exposure pixels. */
    float   hdrShort;

    /** Holds a value that is used to determine the long exposure pixels. */
    float   hdrLong;
} NvMediaISPStatsLacSettingsV4;

/**
 * Holds the LAC statistics measurement for ISP version 4.
 */
typedef struct
{
    /**
     * Holds a Boolean that specifies to ignore the stats value
     * if an ROI is not enabled.
     * @warning  Using the values for disabled ROI causes undefined behavior.
     */
    NvMediaBool ROIEnable[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds the coordinates of the top left pixel in the top left window. */
    NvMediaISPPoint startOffset[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds the size of each window. */
    NvMediaISPSize windowSize[NVMEDIA_ISP_LAC_ROI_NUM];

    /**
     * Holds the number of windows in LAC stats.
     *
     * When the client calls NvIspGetStats(), @a numWindows is the size of each
     * array that the pAverage[ROI_ID][COLOR_COMPONENT] and
     * pNumPixels[ROI_ID][COLOR_COMPONENT]
     * pointers point to. It must be
     * &ge; (<em>numWindowsH</em> &lowast; <em>numWindowsV</em>) in
     * @c NvIspStatsLacSettings
     * used to set up LAC. If a particular ROI is disabled, ignore the
     * corresponding measurement values.
     * Reading values for a disabled ROI gives undefined stats values.
     *
     * The LAC data is stored in row-major order.
     */
    unsigned int numWindows[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds the number of windows in the horizontal direction. */
    unsigned int numWindowsH[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds the number of windows in the vertical direction. */
    unsigned int numWindowsV[NVMEDIA_ISP_LAC_ROI_NUM];

    /**
     * For Bayer, use NVMEDIA_ISP_COLOR_COMPONENT_[TL|TR|BL|BR] for the indices.
     * For YUV, use NVMEDIA_ISP_COLOR_COMPONENT_[Y|U|V].
     * For RGB, use NVMEDIA_ISP_COLOR_COMPONENT_[R|G|B].
     * Data may be negative.
     */
    float *average[NVMEDIA_ISP_LAC_ROI_NUM][NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds the number of pixels per ROI per component. */
    unsigned int *numPixels[NVMEDIA_ISP_LAC_ROI_NUM][NVMEDIA_ISP_COLOR_COMPONENT_NUM];
} NvMediaISPStatsLacMeasurementV4;

/**
 * Holds the flicker band settings for ISP version 4.
 *
 * The flicker band module computes the average brightness of a number of
 * samples of the image.
 */
typedef struct
{
    /** Holds a Boolean that enables flicker band statistics. */
    NvMediaBool enable;

    /**
     * Holds definitions of the windows for flicker band calculation.
     * The horizontal number of windows must be 1. The height of each window
     * may be rounded due to hardware limitation.
     */
    NvMediaISPStatsWindows windows;

    /**
     * Holds the color channel used for flicker band calculation.
     * For the YUV color format, selecting Channel Y or Luminance does the
     * same thing in the hardware.
     */
    NvMediaISPColorChannel colorChannel;

    /**
     * Holds the HDR interleave pattern.
     *
     * For example:
     * @code
     * 1 1 1 1      1 1 0 0     1 1 0 0
     * 1 1 1 1  OR  1 1 0 0 OR  1 1 0 0
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * 0 0 0 0      1 1 0 0     0 0 1 1
     * @endcode
     */
    unsigned char hdrSampleMap[NVMEDIA_ISP_HDR_SAMPLE_MAP_NUM];

    /**
     * Holds the HDR mode.
     */
    NvMediaISPHdrMode   hdrMode;
} NvMediaISPStatsFlickerBandSettingsV4;

/**
 * Holds the flicker band statistics measurement.
 */
typedef struct
{
    /**
     * Holds the number of flicker band windows.
     *
     * @a numWindows is the size of the array that luminance points to.
     */
    unsigned int numWindows;

    /** Holds a pointer to the array of the average luminance value of the samples.
     *  Data may be negative.
     */
    int *luminance;
} NvMediaISPStatsFlickerBandMeasurement;

/**
 * Holds the focus metric statistics settings.
 *
 * ISP calculates the focus metric in each focus window. The statistics can
 * only be generated on Bayer data.
 */
typedef struct
{
    /** Holds a Boolean that enables focus metric statistics. */
    NvMediaBool enable;

    /** Holds a Boolean that enables noise compensation when calculating
     focus metrics. */
    NvMediaBool noiseCompensation;

    /**
     * Holds the gain applied to noise compensation when noise compensation
     * is enabled. This value is rounded to the nearest value that
     * the hardware supports.
     */
    float noiseCompensationGain;

    /**
     * Holds the gain applied to the accumulated focus metric. This value is
     * rounded to the nearest value that the hardware supports.
     *
     * Examples of valid values are 1, 0.5, and 0.25.
     */
    float metricGain;

    /** Holds the number of coefficients for each color component. */
    unsigned int numCoefficients;

    /**
     * Holds coefficients of the filter used to compute the focus metric
     * for each color component.
     *
     * An example of 9-tap filter is: (-1, -2, -1, 2, 4, 2, -1, -2, -1).
     */
    float *coefficient[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds a minimum focus metric value. Focus metric values lower than
     this are clamped to zero. */
    float metricLowerLimit;

    /** Holds the maximum value of the input pixels to be used for calculation
     of the focus metric. */
    float inputThreshold;

    /** Holds definitions of windows for focus metric calculation. */
    NvMediaISPStatsWindows windows;
} NvMediaISPStatsFocusMetricSettings;

/**
 * Holds the focus metric statistics measurement.
 */
typedef struct
{
    /** Holds the position of the top left pixel in the top left window. */
    NvMediaISPPoint startOffset;

    /** Holds the size of each window. */
    NvMediaISPSize windowSize;

    /** Holds the size of the array to which @a pMetric points. */
    unsigned int numWindows;

    /** Holds a pointer to the array of the focus metrics of the windows. */
    unsigned int *metric[NVMEDIA_ISP_COLOR_COMPONENT_NUM];
} NvMediaISPStatsFocusMetricMeasurement;

/*
 * Start of statistics defines for ISP version 5.
 */

/** Number of radial transfer function control points. */
#define NVMEDIA_ISP5_RADTF_CP_COUNT             6
/** Number of flicker band windows. */
#define NVMEDIA_ISP5_FB_WINDOWS                 256
/** Number of histogram transfer function knee points. */
#define NVMEDIA_ISP5_HIST_TF_KNEE_POINT_COUNT   8
/** Number of histogram bins. */
#define NVMEDIA_ISP5_HIST_BIN_COUNT             256
/** Number of local average and clip windows in a region of interest. */
#define NVMEDIA_ISP_LAC_ROI_WIN_NUM             (32 * 32)
/** Number of local tone map histogram bins. */
#define NVMEDIA_ISP5_LTM_HIST_BIN_COUNT         128
/** Number of local tone map averaging windows. */
#define NVMEDIA_ISP5_LTM_AVG_WIN_COUNT          8

/**
 * Defines multi-exposure lane selections.
 */
typedef enum
{
    NVMEDIA_ISP_MULTI_EXP_LANE_RV = 0,
    NVMEDIA_ISP_MULTI_EXP_LANE_GY = 1,
    NVMEDIA_ISP_MULTI_EXP_LANE_BU = 2,
} NvMediaIsp5MultiExpLane;

/**
 * Holds a radial mask (defined by an ellipse).
 */
typedef struct
{
    /** Holds the X coordinate of the center of the ellipse, in pixels. */
    double_t x;
    /** Holds the Y coordinate of the center of the ellipse, in pixels. */
    double_t y;
    /** Holds the ellipse matrix transformation's kxx coefficient. */
    double_t kxx;
    /** Holds the ellipse matrix transformation's kxy coefficient. */
    double_t kxy;
    /** Holds the ellipse matrix transformation's kyx coefficient. */
    double_t kyx;
    /** Holds the ellipse matrix transformation's kyy coefficient. */
    double_t kyy;
} NvMediaIsp5RadialMask;

/**
 * Holds a rectangular mask for local tone mapping.
 */
typedef struct
{
    /** Holds the Y coordinate of the rectangle's top. */
    uint16_t top;
    /** Holds the Y coordinate of the rectangle's bottom. */
    uint16_t bottom;
    /** Holds the X coordinate of the rectangle's left side. */
    uint16_t left;
    /** Holds the X coordinate of the rectangle's right side. */
    uint16_t right;
} NvMediaIsp5RectMask;

/**
 * Holds a control point for a Cubic Hermite spline. Many ISP blocks use the
 * cubic spline to interpolate functions.
 *
 * A spline is defined by an array of control points; number of points
 * varies between units.
 */
typedef struct
{
    /** Holds the X coordinate of the control point. */
    float_t x;
    /** Holds the Y coordinate of the control point. */
    float_t y;
    /** Holds the slope (tangent) of the interpolated curve at the
     control point */
    double_t slope;
} NvMediaISP5CubicSplineCtrlPoint;

/**
 * Holds the definition of a radial transfer function.
 */
typedef struct
{
    /** Holds a radial mask. */
    NvMediaIsp5RadialMask ellipse;
    /** Holds an array of control points. */
    NvMediaISP5CubicSplineCtrlPoint tf[NVMEDIA_ISP5_RADTF_CP_COUNT];
} NvMediaIsp5RadialTf;

/**
 * Defines channel selections for a histogram for ISP version 5.
 */
typedef enum
{
    NVMEDIA_ISP_HIST_CH_R_V = 0,
    NVMEDIA_ISP_HIST_CH_G_Y = 1,
    NVMEDIA_ISP_HIST_CH_B_U = 2,
    NVMEDIA_ISP_HIST_CH_Y   = 3,
} NvMediaIsp5HistChannel;

/**
 * Defines channel selections for a 4th channel histogram for ISP version 5.
 */
typedef enum {
    NVMEDIA_ISP_HIST_CH_MAXORY_MAX = 0,
    NVMEDIA_ISP_HIST_CH_MAXORY_Y   = 3,
} NvMediaIsp5HistChannelMaxOrY;

/**
 * Holds flicker band settings for ISP version 5.
 *
 * The flicker band module computes the average brightness of a number of
 * samples of the image.
 */
typedef struct
{
    /** Holds a Boolean that enables the flicker band stats unit. */
    NvMediaBool enable;

    /**
     * Holds a value that select the channel used for calculating statistics.
     *
     * The Luminance channel is calculated as follows:
     * - For CFA input data it is set to average of pixels in
     *   a single CFA block, so the value is 0.25*R + 0.5*G + 0.25*B.
     * - For RGB data it is set to 0.25*R + 0.625*G + 0.125*B.
     * - For YUV data the Y channel is used directly.
     */

    NvMediaISPColorChannel chSelect;

    /** Holds a Boolean that enables the elliptical mask for disabling pixels
     outside area of interest. */
    NvMediaBool radialMaskEnable;

    /** Holds the count of flicker band samples to collect per frame. */
    uint8_t bandCount;

    /** Holds the offset of the first band top line (and first pixel in a line
     for all bands). */
    NvMediaISPPoint offset;

    /**
     * Holds the size of a single band. This must be chosen so that:
     * - Both width and height are even and &ge;2.
     * - Total number of accumulated pixels is &le;2^18.
     */
    NvMediaISPSize bandSize;

    /**
     * Holds a value that selects the range of pixel values to include when
     * calculating the FB statistics.
     *
     * In a merged multi-exposure HDR image, each exposure might have different
     * characteristics (exposure time and timing) that affect FB statistics.
     * By setting these limits so that only pixels for a single exposure are
     * included, the accuracy of FB statistics can be significantly improved.
     */
    NvMediaISPRangeFloat range;
    NvMediaISPRangeFloat chromaRange;

    /** Holds an elliptical mask for selecting pixels included if
     * @ref radialMaskEnable is set to true. */
    NvMediaIsp5RadialMask radialMask;

} NvMediaISPStatsFlickerBandSettingsV5;

/**
 * Holds the flicker band statistics measurement for ISP version 5.
 */
typedef struct
{
    /** Holds the number of flicker band windows. This is the size of the array
     that luminance points to. */
    uint32_t numWindows;

    /** Holds a pointer to the array of the average luminance values of the
     samples. Data may be negative.  */
    float_t luminance[NVMEDIA_ISP5_FB_WINDOWS];
} NvMediaISPStatsFlickerBandMeasurementV5;

/**
 * Holds the settings for the histogram statistics for ISP version 5.
 */
typedef struct
{
    /** Holds a Boolean that enables the histogram unit. */
    NvMediaBool enable;

    /** Holds a Boolean that enables a mask for excluding pixels outside
     a specified elliptical area. */
    NvMediaBool radialMaskEnable;

    /**
     * Holds a Boolean that enables radial weighting of pixels based on their
     * spatial location. This can be used, for example, to compensate for
     * lens shading if @a Hist is measured before LS correction, or a different
     * area covered by pixels.
     */
    NvMediaBool radialWeigthEnable;

    /**
     * Holds an enum that selects the exposure used for the histogram if input
     * is a multi-exposure image.
     *
     * Valid values are in the range [0, 2].
     */
    NvMediaIsp5MultiExpLane laneSelect;

    /** Holds the rectangle used for the histogram. */
    NvMediaRect window;

    /**
     * Holds data used for the first histogram channel.
     *
     * There are four channels named (0) channel10, (1) \ref channel1,
     * (2) \ref channel2, and (3) \ref channel3.
     * For channels 0-2, valid values are any of the color channels
     * (R/V, G/Y, B/U) or Y calculated from RGB pixel values.
     * For channel 3 the valid values are either maximum of R,G,B (or U,V in
     * case of YUV input) or calculated Y.
     */
    NvMediaIsp5HistChannel channel0;
    /** Data used for the second histogram channel. See the description of
     \ref channel0. */
    NvMediaIsp5HistChannel channel1;
    /** Data used for the third histogram channel. See the description of
     \ref channel0. */
    NvMediaIsp5HistChannel channel2;
    /** Data used for the fourth histogram channel. See the description of
     \ref channel0. */
    NvMediaIsp5HistChannelMaxOrY channel3;

    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t R2YGain;
    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t G2YGain;
    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t B2YGain;
    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t R2YOffset;
    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t G2YOffset;
    /** Holds data used for calculating the Y channel in RGB-to-Y conversion. */
    float_t B2YOffset;

    /** Holds an offset to be applied to the input data prior to performing
     the bin mapping operation. */
    float_t offset;

    /** Holds an offset to be applied to chroma channels of the input data
     prior to performing the bin mapping operation. */
    float_t chromaOffset;

    /** Holds log2 width of the histogram mapping zones. */
    uint8_t kneePoints[NVMEDIA_ISP5_HIST_TF_KNEE_POINT_COUNT];

    /** Holds log2 ranges of the histogram mapping zones. */
    uint8_t ranges[NVMEDIA_ISP5_HIST_TF_KNEE_POINT_COUNT];

    /** Holds log2 width of the histogram mapping zones. */
    uint8_t chromaKneePoints[NVMEDIA_ISP5_HIST_TF_KNEE_POINT_COUNT];

    /** Holds log2 ranges of the histogram mapping zones. */
    uint8_t chromaRanges[NVMEDIA_ISP5_HIST_TF_KNEE_POINT_COUNT];

    /** Holds an elliptical mask for selecting pixels included if
     \ref radialMaskEnable is set to true. */
    NvMediaIsp5RadialMask radialMask;

    /** Holds a radial transfer function if \ref radialWeigthEnable is set to
     true. */
    NvMediaIsp5RadialTf radialWeightTf;

} NvMediaISPStatsHistogramSettingsV5;

/**
 * Holds the histogram statistics measurement for ISP version 5.
 */
typedef struct
{
    /**
     * Holds an array of histogram data for different color components.
     * Use the indices based on the color space on which the histogram is
     * gathered.
     * - For Bayer, use `NV_ISP_COLOR_COMPONENT_[TL|TR|BL|BR]`.
     * - For YUV, use `NV_ISP_COLOR_COMPONENT_[Y|U|V]`.
     * - For RGB, use `NV_ISP_COLOR_COMPONENT_[R|G|B]`.
     */
    uint32_t histData[NVMEDIA_ISP5_HIST_BIN_COUNT][NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds the pixel count for excluded pixels for each color component. */
    uint32_t excludedCount[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

} NvMediaISPStatsHistogramMeasurementV5;

/**
 * Holds settings to use for LAC statistics for ISP version 5.
 */
typedef struct
{
    /** Holds a Boolean which enables the LAC statistics unit. */
    NvMediaBool enable;

    /** Holds an array of Booleans which enable the individual ROIs. */
    NvMediaBool ROIEnable[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds an array of Booleans which enable a mask for excluding pixels
     outside the specified elliptical area in each ROI. */
    NvMediaBool radialMaskEnable[NVMEDIA_ISP_LAC_ROI_NUM];

    /**
     * Holds a value which selects the exposure used for LAC statistics
     * if input is a multi-exposure image.
     *
     * Valid values are in the range [0, 2].
     */
    NvMediaIsp5MultiExpLane laneSelect;

    /** Holds red to Y gain used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t R2YGain;
    /** Holds green to Y gain used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t G2YGain;
    /** Holds blue to Y gain used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t B2YGain;
    /** Holds red to Y offset used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t R2YOffset;
    /** Holds green to Y offset used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t G2YOffset;
    /** Holds blue to Y offset used for calculating the Y channel in RGB to Y
     conversion if input is an RGB/YUV image. */
    float_t B2YOffset;

    /** Holds minimum and maximum values of pixels for TL/R/V, TR/G/Y, BL/B/U,
     and BR/Y channels respectively. */
    NvMediaISPRangeFloat range[NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds definition of the LAC windows for each ROI. */
    NvMediaISPStatsWindows windows[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds an elliptical mask for selecting pixels included if
     \ref radialMaskEnable is set to true */
    NvMediaIsp5RadialMask radialMask;

} NvMediaISPStatsLacSettingsV5;

/**
 * Holds the LAC statistics measurement for ISP version 5.
 */
typedef struct
{
    /** Holds the number of windows in one set of LAC ROI statistics. */
    uint32_t numWindows;

    /** Holds the number of windows in the horizontal direction. */
    uint32_t numWindowsH;

    /** Holds the number of windows in the vertical direction. */
    uint32_t numWindowsV;

    /**
     * - For Bayer, use `NVMEDIA_ISP_COLOR_COMPONENT_[TL|TR|BL|BR]` for the
     *   indices.
     * - For YUV, use `NVMEDIA_ISP_COLOR_COMPONENT_[Y|U|V]`.
     * - For RGB, use `NVMEDIA_ISP_COLOR_COMPONENT_[R|G|B]`.
     *
     * Data may be negative.
     */
    float_t average[NVMEDIA_ISP_LAC_ROI_WIN_NUM][NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds the number of pixels removed by the elliptical mask per window
     per component. */
    uint32_t maskedOffCnt[NVMEDIA_ISP_LAC_ROI_WIN_NUM][NVMEDIA_ISP_COLOR_COMPONENT_NUM];

    /** Holds the number of clipped pixel count per window per component. */
    uint32_t clippedCnt[NVMEDIA_ISP_LAC_ROI_WIN_NUM][NVMEDIA_ISP_COLOR_COMPONENT_NUM];

} NvMediaISPStatsLacROIDataV5;

typedef struct
{
    /**
     * Holds a Boolean that specifies whether to ignore the stats value
     * if an ROI is not enabled.
     * @warning  Using the value for a disabled ROI causes undefined behavior.
     */
    NvMediaBool ROIEnable[NVMEDIA_ISP_LAC_ROI_NUM];

    /** Holds the size of each window. */
    NvMediaISPSize windowSize[NVMEDIA_ISP_LAC_ROI_NUM];

    /**
     * Holds the data for each ROI in LAC stats.
     *
     * The LAC data is stored in row-major order.
     */
    NvMediaISPStatsLacROIDataV5 ROIData[NVMEDIA_ISP_LAC_ROI_NUM];

} NvMediaISPStatsLacMeasurementV5;

/**
 * Defines settings to use for local tone mapping statistics for ISP version 5.
 *
 * Local tone mapping parameters depend on statistics gathered from previous
 * frames by the LTM sub-block. LTM provides a global tone histogram with
 * 128 bins and local average statistics for configurable 8x8 windows.
 * Both of these support rectangular and elliptical masks to block certain
 * image areas from statistics gathering.
 */
typedef struct
{
    /** Holds a Boolean that enables local tonemapping statistics. */
    NvMediaBool enable;

    /** Holds a Boolean that enables a rectangular mask to restrict the
     image area used for statistics. */
    NvMediaBool rectMaskEnable;

    /** Holds a rectangular mask used to restrict statistics calculation. */
    NvMediaIsp5RectMask rectMask;

    /** Holds a Boolean that enables a radial mask to restrict the image area
     used for statistics. */
    NvMediaBool radialMaskEnable;

    /** Holds a radial mask used to restrict statistics calculation. */
    NvMediaIsp5RadialMask radialMask;

    /**
     * Holds width of the local average statistics window in pixels.
     * The value must be even. The value must be selected so that the
     * 8x8 grid of windows covers whole active image area, i.e., so that
     * 8 &lowast; StatsLocalAvgWndWidth &ge; image width. The window must
     * also be roughly rectangular.
     */
    uint16_t localAvgWndWidth;

    /**
     * Holds the height of the local average statistics window in pixels.
     * The value must be even.
     *
     * See localAvgWidth for recommendations on selecting the value.
     */
    uint16_t localAvgWndHeight;

} NvMediaISPStatsLTMSettingsV5;

/**
 * Holds the LTM statistics measurement for ISP version 5.
 */
typedef struct
{
    /**
     * Holds count of pixels with tone falling into each histogram bin.
     */
    uint32_t histogram[NVMEDIA_ISP5_LTM_HIST_BIN_COUNT];

    /**
     * Holds average tone in local average window. The tone values are computed
     * by converting YUV input to tone, taking the logarithm of the value, and
     * normalizing it so that dynamic range is mapped to the range [0.0, 1.0].
     * See NvMediaISPStatsLocalToneMapV5 for parameters that control
     * this process.
     *
     * If no pixels contributed to a window (because the window either was
     * out of image boundaries, or was completely excluded by rectangular
     * or elliptical masks), this value is set to zero.
     */
    float_t localAverageTone[NVMEDIA_ISP5_LTM_AVG_WIN_COUNT][NVMEDIA_ISP5_LTM_AVG_WIN_COUNT];

    /** Holds the number of pixels in each local average window that
     contributed to statistics. */
    uint32_t nonMaskedPixelCount[NVMEDIA_ISP5_LTM_AVG_WIN_COUNT][NVMEDIA_ISP5_LTM_AVG_WIN_COUNT];

} NvMediaISPStatsLTMMeasurementV5;

/**
 * Holds the OR statistics measurement for ISP version 5.
 */
typedef struct
{
    /** Holds the bad pixel count for pixels corrected upwards within
     the window. */
    uint32_t highInWin;
    /** Holds the bad pixel count for pixels corrected downwards within
     the window. */
    uint32_t lowInWin;
    /** Holds the accumulatd pixel adjustment for pixels corrected upwards
     within the window. */
    uint32_t highMagInWin;
    /** Holds the accumulatd pixel adjustment for pixels corrected downwards
     within the window. */
    uint32_t lowMagInWin;
    /** Holds the bad pixel count for pixels corrected upwards
     outside the window. */
    uint32_t highOutWin;
    /** Holds the bad pixel count for pixels corrected downwards
     outside the window. */
    uint32_t lowOutWin;
    /** Holds the accumulatd pixel adjustment for pixels corrected upwards
     outside the window. */
    uint32_t highMagOutWin;
    /** Holds the accumulatd pixel adjustment for pixels corrected downwards
     outside the window. */
    uint32_t lowMagOutWin;
} NvMediaISPStatsORMeasurementV5;

/** @} <!-- ends isp_frame_stats_legacy --> */

/*
 * \defgroup history_isp_legacy History
 * Provides change history for the NvMedia ISP API.
 *
 * \section history_isp_legacy Version History
 *
 * <b> Version 1.0 </b> July 8, 2014
 * - Initial release
 *
 * <b> Version 1.1 </b> March 13, 2015
 * - Added ISP version 3 support
 *
 * <b> Version 1.2 </b> November 17, 2015
 * - Added ISP version 4 support
 *
 * <b> Version 1.3 </b> March 31, 2017
 * - Removed ISP version 3 support
 *
 * <b> Version 1.4 </b> August 15, 2017
 * - Added ISP version 5 support
 *
 * <b> Version 1.5 </b> December 1, 2017
 * - Added windowSize to NvMediaISPStatsLacMeasurementV5 for ISP version 5
 *
 * <b> Version 1.6 </b> Febuary 22, 2018
 * - Renamed unClippedCnt to maskedOffCnt
 *
 * <b> Version 1.7 </b> April 10, 2018
 * - Change slope to double point in NvMediaISP5CubicSplineCtrlPoint
 */
/** @} */
#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_ISP_LEGACY_H */
