/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 *
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Lens Distortion Correction (LDC) </b>
 *
 * @b Description: This file contains the NvMedia LDC API.
 */

#ifndef _NVMEDIA_LDC_H
#define _NVMEDIA_LDC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"
#include "nvmedia_image.h"

/**
 * \defgroup ldc_api Lens Distortion Correction
 *
 * The NvMedia Lens Distortion Correction (LDC) API contains NvMedia
 * functions for accessing the LDC hardware engine
 * for geometric transform and temporal noise reduction (TNR3).
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Defines the major version number. */
#define NVMEDIA_LDC_VERSION_MAJOR   1
/** \brief Defines the minor version number. */
#define NVMEDIA_LDC_VERSION_MINOR   2

/**
 * \brief Defines the NvMedia LDC handle as an opaque struct.
 */
typedef struct NvMediaLDC NvMediaLDC;

/** \brief Defines the maximum number of horizontal regions. */
#define NVMEDIA_LDC_MAX_HOR_REGION    4

/** \brief Defines the aximum number of vertical regions. */
#define NVMEDIA_LDC_MAX_VER_REGION    4

/** \brief Defines the minimum width of horizontal and vertical regions. */
#define NVMEDIA_LDC_MIN_REGION_WIDTH  64

/** \brief Defines the minimum height of horizontal and vertical regions. */
#define NVMEDIA_LDC_MIN_REGION_HEIGHT 16

/**
 * \brief Defines the NvMedia LDC operating modes.
 */
typedef enum {
    /*! Specifies to do geometric transform.*/
    NVMEDIA_LDC_MODE_GEOTRANS,

    /*! Specifies to do temporal noise reduction version 3. */
    NVMEDIA_LDC_MODE_TNR3,

    /*! Specifies to do both geometric transform and temporal noise reduction version 3. */
    NVMEDIA_LDC_MODE_GEOTRANS_TNR3,

    /*! Specifies to do temporal noise reduction version 2. */
    NVMEDIA_LDC_MODE_TNR2
} NvMediaLDCMode;

/**
 * \brief Defines geometric transform operate modes.
 */
typedef enum {
    /*! Specifies to generate sparse warp map for geometric transform. */
    NVMEDIA_GEOTRANS_MODE_GEN_MAPPING = 0,

    /*! Specifies to take sparse warp map from client via
     * \ref NvMediaLDCFeedSparseWarpMap(). */
    NVMEDIA_GEOTRANS_MODE_FEED_MAPPING,

    /*! Specifies to do affine transform. */
    NVMEDIA_GEOTRANS_MODE_AFFINE_TRANSFORM,

    /*! Specifies to do perspective transform. */
    NVMEDIA_GEOTRANS_MODE_PERSPECTIVE_TRANSFORM
} NvMediaGeoTransMode;

/**
 * \brief Defines supported lens models.
 */
typedef enum {
    /*! Polynomial distortion model */
    NVMEDIA_LDC_MODEL_POLYNOMIAL_DISTORTION,

    /*! Fisheye model: r = 2ftan(theta/2), where theta is the angle from the optical axis,
        f is the focal length and r is the distance of a pixel from the image center */
    NVMEDIA_LDC_MODEL_FISHEYE_EQUIDISTANT,

    /*! Fisheye model: r = f*theta, where theta is the angle from the optical axis,
        f is the focal length and r is the distance of a pixel from the image center */
    NVMEDIA_LDC_MODEL_FISHEYE_EQUISOLID,

    /*! Fisheye model: r = 2fsin(theta/2), where theta is the angle from the optical axis,
        f is the focal length and r is the distance of a pixel from the image center */
    NVMEDIA_LDC_MODEL_FISHEYE_ORTHOGRAPHIC,

    /*! Fisheye model: r = fsin(theta), where theta is the angle from the optical axis,
        f is the focal length and r is the distance of a pixel from the image center */
    NVMEDIA_LDC_MODEL_FISHEYE_STEREOGRAPHIC
} NvMediaLensModel;

/**
 * \brief Holds NvMedia camera intrinsic parameters.
 */
typedef struct {
    /*! Specifies the camera focal length in X axis, measured in pixel unit. */
    float_t fx;

    /*! Specifies the camera focal length in Y axis, measured in pixel unit. */
    float_t fy;

    /*! Specifies the optical center in X axis, measured in pixel unit. */
    float_t cx;

    /*! Specifies the optical center in Y axis, measured in pixel unit. */
    float_t cy;
} NvMediaCamIntriParams;

/**
 * \brief Holds distortion coefficients for the lens model.
 *  Distortion coefficients is defined in the following way:
 *  k1, k2, k3, k4, k5, k6 are radial distortion coeffcients. p1 and p2 are tangential
 *  distortion coeffcients.
 *  Setting any of the coefficients to 0 implies that it is not used in computation.
 *
 *  If we denote a point without distortion as [x, y, 1] and the corresponding point with distortion
 *  as [xd, yd, 1], then the distortion model is defined as follows:
 *
 *  When NvMediaLensModel is
 *  \ref NVMEDIA_LDC_MODEL_POLYNOMIAL_DISTORTION
 *  The control parameters are k1, k2, k3, k4, k5, k6, p1, p2.
 *
 *      r = sqrt (x ^ 2 + y ^ 2)
 *      kr = (1 + k1 * r^2 + k2 * r^4 + k3 * r^6) / (1 + k4 * r^2 + k5 * r^4 + k6 * r^6)
 *      xd = x * kr + p1 * (2 * x * y) + p2 * (r^2 + 2 * x^2)
 *      yd = y * kr + p1 * (r^2 + 2 * y^2) + p2 * (2 * x * y)
 *
 *
 *  When NvMediaLensModel is
 *  \ref NVMEDIA_LDC_MODEL_FISHEYE_EQUIDISTANT or
 *  \ref NVMEDIA_LDC_MODEL_FISHEYE_EQUISOLID  or
 *  \ref NVMEDIA_LDC_MODEL_FISHEYE_ORTHOGRAPHIC or
 *  \ref NVMEDIA_LDC_MODEL_FISHEYE_STEREOGRAPHIC
 *  The control parameters are k1, k2, k3, k4.
 *
 *      r = sqrt (x ^ 2 + y ^ 2)
 *      theta = atan(r)
 *      theta_d = theta * (1 + k1 * theta^2 + k2 * theta^4 + k3 * theta^6 + k4 * theta^8)
 */
typedef struct {
    /*! Specifies radial distortion coefficient. */
    float_t k1;

    /*! Specifies radial distortion coefficient. */
    float_t k2;

    /*! Specifies radial distortion coefficient. */
    float_t k3;

    /*! Specifies radial distortion coefficient. */
    float_t k4;

    /*! Specifies radial distortion coefficient. */
    float_t k5;

    /*! Specifies radial distortion coefficient. */
    float_t k6;

    /*! Specifies tangential distortion coefficient. */
    float_t p1;

    /*! Specifies tangential distortion coefficient. */
    float_t p2;
} NvMediaLensDistortion;

/**
 * \brief Holds NvMedia LDC camera parameter info.
 */
typedef struct {
    /*! Specifies the camera model. */
    NvMediaLensModel model;

    /*! Specifies the distortion coefficients. */
    NvMediaLensDistortion distCoeffs;

    /*! Specifies the camera intrinsic matrix. */
    NvMediaCamIntriParams K;

    /*! Specifies the rotation matrix. Defined in the following way:
    \n           |r11  r12  r13|
    \n           |r21  r22  r23|
    \n           |r31  r32  r33|
    */
    float_t R[3][3];

    /*! Specifies the translation vector. Defined in the following way:
     *\n         |t1 t2 t3|
    */
    float_t T[3];

    /*! Specifies the target camera intrinsic matrix. */
    NvMediaCamIntriParams targetK;
} NvMediaCameraModel;

/**
 * \brief Holds the NvMedia LDC region configuration.
 * The \ref NvMediaLDCRegionConfig defines the layout of the control points in the
 * destination image.
 *
 * The control points will be used as the basis for geometric transformation from source image to
 * the destination image. The remaining points will be transformed based on the interpolation.
 * So the density of the control points will control the quality of the geometric transformation.
 *
 * Example of defining regions in the image
 * \code
 *
 *
 *
 *            (dstRect->x1 - dstRect->x0)
 *         /                              \
 *        /                                \
 *       /                                  \
 *
 *   horRegionWidth[0]         horRegionWidth[numHorRegion -1]
 *       /     \                     /      \
 *      |-------|                   |--------|
 *      --------------------------------------                                      \
 *      |******** ******** ...      ******** |--                                     \
 *      |* +  + * *      * ...      *      * |   \                                    \
 *      |* +  + * *      *          *      * | verRegionHeight[0]                      \
 *      |* +  + * *      *          *      * |   /                                      \
 *      |******** ********          ******** |--                                         \
 *      |..                         ..       |                                            \
 *      |..                         ..       |
 *      |..                         ..       |                           (dstRect->y1 - dstRect->y0)
 *      |                                    |
 *      |                                    |                                            /
 *      |******** ********...       ******** |--                                         /
 *      |*      * *      *...       *      * |  \                                       /
 *      |*      * *      *          *      * | verRegionHeight[numVerRegion -1]        /
 *      |*      * *      *          *      * |  /                                     /
 *      |******** ********          ******** |--                                     /
 *      --------------------------------------
 *
 * \endcode
 *
 * Example of defining control points in one region
 * \code
 *      *********
 *      *  +  + *-- \
 *      *       *     (1 << log2verSpace)
 *      *  +  + *-- /
 *      *       *
 *      *********
 *         |--|
 *       (1 << log2horSpace)
 *
 * \endcode
 *
 * ### Restrictions
 *
 * * numHorRegion cannot exceed NVMEDIA_LDC_MAX_HOR_REGION
 * * numVerRegion cannot exceed NVMEDIA_LDC_MAX_VER_REGION
 * * Alignment restrictions:
 *   - horRegionWidth[0] to horRegionWidth[numHorRegion-2] must be greater than and aligned to
 *     NVMEDIA_LDC_MIN_REGION_WIDTH.
 *     horRegionWidth[numHorRegion-1] must be greater than NVMEDIA_LDC_MIN_REGION_WIDTH.
 *   - verRegionHeight[0] to verRegionHeight[numVerRegion-2] must be greater than and aligned to
 *     NVMEDIA_LDC_MIN_REGION_HEIGHT.
 *     verRegionHeight[numVerRegion-1] must be greater than NVMEDIA_LDC_MIN_REGION_HEIGHT.
 * * Region width/height restrictions:
 *  - The sum of horRegionWidth[] must be equal to the width of the \a dstRect
 *    argument passed to NvMediaLDCCreate().
 *  - The sum of verRegionHeight[] must be equal to the height of \a dstRect
 *    argument passed to NvMediaLDCCreate().
 */

typedef struct {
    /*! Specifies the number of horizontal regions.
        Allowed values are [1, 4], inclusive. */
    uint8_t numHorRegion;

    /*! Specifies the number of vertical regions.
        Allowed values are [1, 4], inclusive. */
    uint8_t numVerRegion;

    /*! Specifies the width of regions */
    uint16_t horRegionWidth[NVMEDIA_LDC_MAX_HOR_REGION];

    /*! Specifies the height of regions */
    uint16_t verRegionHeight[NVMEDIA_LDC_MAX_VER_REGION];

    /*! Specifies the horizontal interval between the control points in each region
        in log2 space. */
    uint16_t log2horSpace[NVMEDIA_LDC_MAX_HOR_REGION];

    /*! Specifies the vertical interval between the control points in each region
        in log2 space. */
    uint16_t log2verSpace[NVMEDIA_LDC_MAX_VER_REGION];
} NvMediaLDCRegionConfig;

/**
 * \brief Holds the NvMedia mask map surface.
 * With destination rectangle, this mask map surface defines the region of interest
 * in the destination image.
 * The \a dstRect argument passed to NvMediaLDCCreate() defines the destination rectangle.
 */
typedef struct {
    /*! Holds the width in bytes of the mask map surface, which must be equal to
        the width of destination rectangle. */
    uint16_t width;

    /*! Holds the height in bytes of the mask map surface, which must be equal
     * to the height of the destination rectangle. */
    uint16_t height;

    /*! Holds the value for mask map surface. The mask map surface is stored
     * row by row. Each byte is used to indicate whether this pixel has been
     * masked or not. Non-zero value pixel means will not be masked.
     * The size of this buffer in bytes must be: width * height.
     */
    void *mapPtr;

    /*! Holds a flag indicating whether to fill the masked pixel with the specified color. */
    NvMediaBool maskedPixelFillColor;
} NvMediaLDCBitMaskMap;

/**
 * \brief Holds geometric transform initialization paramters.
 */
typedef struct {
    /*! Specifies the geometric transform mode.
    */
    NvMediaGeoTransMode geoTransMode;

    /*! Specifies the filter quality. */
    NvMediaFilterQuality filter;

    /*! Specifies the camera model parameters.
     *  Must be set when geoTransMode is \ref NVMEDIA_GEOTRANS_MODE_GEN_MAPPING.
     */
    NvMediaCameraModel cameraModel;

    /*! Specifies the perspective matrix.
     *  Must be set when geoTransMode is
     *  \ref NVMEDIA_GEOTRANS_MODE_AFFINE_TRANSFORM or
     *  \ref NVMEDIA_GEOTRANS_MODE_PERSPECTIVE_TRANSFORM.
     *  Defined in the following way:
     *  \n        |p[0][0]  p[0][1]  p[0][2]|
     *  \n        |p[1][0]  p[1][1]  p[1][2]|
     *  \n        |p[2][0]  p[2][1]  p[2][2]|
     */
    float_t ptMatrix[3][3];

    /*! Specifies the region configure paramters.
     */
    NvMediaLDCRegionConfig regionConfig;

    /*! Holds the Y channel value of the default color. This value is clamped between 0.0 and 1.0. */
    float_t maskY;

    /*! Holds the U channel value of the default color. This value is clamped between 0.0 and 1.0. */
    float_t maskU;

    /*! Holds the V channel value of the default color. This value is clamped between 0.0 and 1.0. */
    float_t maskV;

    /*! Indicates whether bit mask map is enabled. */
    NvMediaBool bitMaskEnable;

    /*! Holds the bit mask map information when bitMaskEnable is NV_TRUE.
     * The width and height of this bit mask map must match with the destination
     * rectangle.
     */
    NvMediaLDCBitMaskMap bitMaskMap;
} NvMediaGeoTransParams;

/**
 * \brief Holds the TNR3 initialization paramters.
 */
typedef struct {
    /*! Specifies the sigma of the luma for spatial filter */
    uint16_t spatialSigmaLuma;

    /*! Specifies the sigma of the chroma for spatial filter */
    uint16_t spatialSigmaChroma;

    /*! Specifies the sigma of the luma for range filter */
    uint16_t rangeSigmaLuma;

    /*! Specifies the sigma of the chroma for range filter */
    uint16_t rangeSigmaChroma;

    /*! Specifies the SAD multiplier parameter.
     * This value is clamped between 0.0 and 1.0
     */
    float_t sadMultiplier;

    /*! Specifies the weight of luma when calculating SAD.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t sadWeightLuma;

    /*! flag whether to enable the spatial alpha smooth */
    NvMediaBool alphaSmoothEnable;

    /*! Specifies the temporal alpha restrict increase capablility.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaIncreaseCap;

    /*! Specifies the alpha scale IIR for strength.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaScaleIIR;

    /*! Specifies the max luma value in Alpha Clip Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaMaxLuma;

    /*! Specifies the min luma value in Alpha Clip Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaMinLuma;

    /*! Specifies the max chroma value in Alpha Clip Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaMaxChroma;

    /*! Specifies the min chroma value in Alpha Clip Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t alphaMinChroma;

    /*! Specifies parameter BetaX1 in Beta Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t betaX1;

    /*! Specifies parameter BetaX2 in Beta Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t betaX2;

    /*! Specifies parameter MinBeta threshold in Beta Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t minBeta;

    /*! Specifies parameter MaxBeta threshold in Beta Calculation.
     *  This value is clamped between 0.0 and 1.0
     */
    float_t maxBeta;
} NvMediaTNR3Params;

/**
 * \brief Holds the TNR2 initialization paramters.
 */
typedef struct {
    /*! Specifies the noise reduction strength. This value is clamped between 0.0 and 1.0 */
    float_t noiseReduction;
    /*! Specifies the noise reduction algorithm. See \ref NvMediaNoiseReductionAlgorithm. */
    NvMediaNoiseReductionAlgorithm noiseReductionAlgorithm;
} NvMediaTNR2Params;

/**
 * \brief Holds the NvMedia LDC initialization paramters.
 */
typedef struct {
    /*! Specifies the LDC mode. */
    NvMediaLDCMode ldcMode;

    /*! Specifies geometric transform initialization paramters.
     *  Must be set when ldcMode is
     *  \ref NVMEDIA_LDC_MODE_GEOTRANS or \ref NVMEDIA_LDC_MODE_GEOTRANS_TNR3.
     */
    NvMediaGeoTransParams geoTransParams;

    /*! Specifies TNR3 initialization paramters.
     *  Must be set when ldcMode is
     *  \ref NVMEDIA_LDC_MODE_TNR3 or \ref NVMEDIA_LDC_MODE_GEOTRANS_TNR3.
     */
    NvMediaTNR3Params tnr3Params;

    /*! Specifies TNR2 initialization paramters.
     *  Must be set when ldcMode is
     *  \ref NVMEDIA_LDC_MODE_TNR2.
     */
    NvMediaTNR2Params tnr2Params;

    /*! Specifies source format type for LDC or TNR operation.
     *  srcSurfaceType must be set.
     */
    NvMediaSurfaceType srcSurfaceType;
} NvMediaLDCInitParams;

/**
 * \brief Defines the NvMedia LDC Data Format.
 */
typedef enum {
    /*! standard float_t format */
    NVMEDIA_LDC_DATAFORMAT_FLOAT_T,

    /*! S15.5 is the fixed floating format where the data is stored only
        in the most significant 20 bits of 32bits (4 bytes). */
    NVMEDIA_LDC_DATAFORMAT_FIXEDFLOAT_S15_5
} NvMediaLDCDataFormat;

/**
 * \brief Holds the NvMedia LDC defintion of Sparse warp map.
 *
 * Sparse warp map stores the mappings of each control point from destination
 * image to input image. The coordinates of control points in destination image is defined by
 * \ref NvMediaLDCRegionConfig.
 */
typedef struct {
    /*! Specifies the number of control points in each row. */
    uint16_t numHorPoints;

    /*! Specifies the number of control points in each column. */
    uint16_t numVerPoints;

    /*! Specifies the number of control points in one stride. */
    uint16_t mapStride;

    /*! Holds the mapping value for each of the control points. While the control points
     *  are stored in the row order themselves, for each control point, the coordinates are
     *  stored in the order of (x,y) where x is horizontal coordinate and y is vertical coordinate.
     *  The size of this buffer in bytes must be:
     *  mapStride * numVerPoints * sizeof(float_t) * 2.
     */
    void *mapPtr;

    /*! Specifies the data format used in the buffer pointed by mapPtr.
     *  Supported formats are as specified by \ref NvMediaLDCDataFormat.
     */
    NvMediaLDCDataFormat dataFormat;
} NvMediaLDCSparseWarpMap;

/**
 * \brief Defines the xSobel working modes.
 */
typedef enum {
    /*! Specifies to disable both sobel and downsample output. */
    NVMEDIA_GEOTRANS_DISABLE_XSOBEL_DISABLE_DS = 0,

    /*! Specifies to produce luma sobel and luma downsample output. */
    NVMEDIA_GEOTRANS_DISABLE_XSOBEL_ENABLE_DS,

    /*! Specifies to produce gradient sobel and disable downsample output. */
    NVMEDIA_GEOTRANS_ENABLE_XSOBEL_DISABLE_DS,

    /*! Specifies to produce gradient sobel and gradient downsample output. */
    NVMEDIA_GEOTRANS_ENABLE_XSOBEL_ENABLE_DS
} NvMediaLDCSobelMode;

/**
 * \brief Holds runtime control parameters for NvMediaLDCProcess().
 */
typedef struct {
    /*! Specifies the xSobel working mode.
     *  Supported modes are specified by \ref NvMediaLDCSobelMode.
     * \n Used when ldcMode is \ref NVMEDIA_LDC_MODE_GEOTRANS.
	 * Otherwise, set this field to NULL.
     */
    NvMediaLDCSobelMode xSobelMode;
} NvMediaLDCCtrlParams;

/**
 * \brief Returns the version information of NvMedia LDC.
 *
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *            filled by the NvMedia LDC.
 * \return \ref NvMediaStatus. Return status.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK - Success.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument.
 */
NvMediaStatus
NvMediaLDCGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an NvMedia LDC handle.
 * The function creates and initializes the appropriate internal infrastructure for LDC/TNR3
 * depending on the input arguments. A valid NvMedia LDC handle is returned if successful.
 *
 * \param[out] pldc An indirect pointer to the NvMediaLDC handle.
 * \param[in] srcWidth Width of the source image.
 * \param[in] srcHeight Height of the source image.
 * \param[in] srcRect Structure containing co-ordinates of the rectangle in the source image.
 *            Setting srcRect to NULL implies rectangle of full source image size.
 * \param[in] dstWidth Width of the destination image.
 * \param[in] dstHeight Height of the destination image.
 * \param[in] dstRect Structure containing co-ordinates of the rectangle in the destination image.
 *            Setting dstRect to NULL implies rectangle of full destination image size.
 * \param[in] initParams Initialization parameters of LDC creation. See \ref NvMediaLDCInitParams.
 * \return \ref NvMediaStatus Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK - Success. pldc will point to a valid LDC handle.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED - Not supported in current config.
 * - \ref NVMEDIA_STATUS_OUT_OF_MEMORY - Insufficient memory
 */
NvMediaStatus
NvMediaLDCCreate(
    NvMediaLDC **pldc,
    const uint16_t srcWidth,
    const uint16_t srcHeight,
    const NvMediaRect *srcRect,
    const uint16_t dstWidth,
    const uint16_t dstHeight,
    const NvMediaRect *dstRect,
    const NvMediaLDCInitParams *initParams);

/**
 * \brief Destroys the NvMedia LDC handle that was created by NvMediaLDCCreate().
 * Frees up the internal resources and handles allocated during NvMediaLDCCreate().
 *
 * \param[in] ldc Handle to the current context, previously returned by NvMediaLDCCreate().
 * \return \ref NvMediaStatus Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK - Success. ldc is not a valid \ref NvMediaLDC handle anymore.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 */
NvMediaStatus
NvMediaLDCDestroy(
    NvMediaLDC *ldc
);

/**
 * \brief Feeds sparse warp map to NvMedia LDC.
 * Must be called when \ref NvMediaGeoTransMode is \ref NVMEDIA_GEOTRANS_MODE_FEED_MAPPING.
 * The sparse warp map must match the \ref NvMediaLDCRegionConfig.
 *
 * \param[in] ldc Handle to the current context, previously returned by NvMediaLDCCreate().
 * \param[in] map Client-specified sparse warp map, \ref NvMediaLDCSparseWarpMap.
 * \return \ref NvMediaStatus Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK - Success.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED - Not supported in current config.
 * - \ref NVMEDIA_STATUS_OUT_OF_MEMORY - Insufficient memory
 */
NvMediaStatus
NvMediaLDCFeedSparseWarpMap(
    NvMediaLDC *ldc,
    const NvMediaLDCSparseWarpMap *map);

/**
 * \brief Generates sparse warp mapping based on \ref NvMediaCameraModel.
 * Must be called when \ref NvMediaGeoTransMode is \ref NVMEDIA_GEOTRANS_MODE_GEN_MAPPING.
 * This is a CPU-based operation.
 * \param[in] ldc Handle to the current context, previously returned by NvMediaLDCCreate().
 * \return \ref NvMediaStatus Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK - Success.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED - Not supported in current config.
 */
NvMediaStatus
NvMediaLDCMappingGen(
    NvMediaLDC *ldc);

/**
 * \brief Updates TNR3 parameters after NvMediaLDCCreate().
 *
 * \ref NvMediaLDCCreate() initializes \ref NvMediaLDC with TNR3 parameters specified as part of \ref
 * NvMediaLDCInitParams.
 * If necessary, this function can be used to update the TNR3 parameters.
 *
 * \param[in] ldc Handle to the current context, previously returned by \ref NvMediaLDCCreate().
 * \param[in] tnr3Params Pointer to object of type \ref NvMediaTNR3Params.
 * \return \ref NvMediaStatus. Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK - Success.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument(s).
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED - Not supported in current config.
 */
NvMediaStatus
NvMediaLDCUpdateTNR3Params(
    NvMediaLDC *ldc,
    const NvMediaTNR3Params *tnr3Params);

/**
 * \brief Performs the specified LDC operation.
 *
 * LDC performs transformations depending onthe GEO mode:
 *
 * 1. LDC performs geometric transformation if NvMediaLDCInitParams::ldcMode is
 *    \ref NVMEDIA_LDC_MODE_GEOTRANS or \ref NVMEDIA_LDC_MODE_GEOTRANS_TNR3.
 *    It uses NvMediaLDCInitParams::geoTransParams to fetch the pixel defined
 *    by srcRect in the source image and renders onto the destination
 *    rectangle of the destination image.
 *    The source image and the destination image must have the same format.
 *    LDC bypasses the transform stage if geometric transform is disabled.
 *    The region of interest in the destination image is defined by:
 * <br>
 *    - Destination rectangle and
 *    - NvMediaLDCBitMaskMap surface
 *      (if \ref NvMediaGeoTransParams::bitMaskEnable is set).
 * <br>
 * 2. LDC outputs \a xSobel if:
 * <br>
 *    - NvMediaLDCInitParams::ldcMode is \ref NVMEDIA_LDC_MODE_GEOTRANS and
 *    - \ref NvMediaLDCCtrlParams::xSobelMode is
 *      \ref NVMEDIA_GEOTRANS_ENABLE_XSOBEL_ENABLE_DS or
 *      \ref NVMEDIA_GEOTRANS_ENABLE_XSOBEL_DISABLE_DS.
 * <br>
 *    The xSobel image must have the same bit-depth as the source image.
 *    NvMediaLDCCtrlParams::xSobelMode must be NULL if
 *    NvMediaLDCInitParams::ldcMode is not
 *    \ref NVMEDIA_LDC_MODE_GEOTRANS.
 * <br>
 * 3. LDC outputs 4x4 downsampled \a xSobel output if:
 * <br>
 *    - NvMediaLDCInitParams::ldcMode is \ref NVMEDIA_LDC_MODE_GEOTRANS and
 *    - \ref NvMediaLDCCtrlParams::xSobelMode is
 *      \ref NVMEDIA_GEOTRANS_ENABLE_XSOBEL_ENABLE_DS or
 *      \ref NVMEDIA_GEOTRANS_DISABLE_XSOBEL_ENABLE_DS.
 * <br>
 *    The downSample image must have the same bit-depth as the source image.
 *    \a downSample must be NULL if no downsample output is expected.
 *
 * If NvMediaLDCInitParams::ldcMode is \ref NVMEDIA_LDC_MODE_TNR3 or
 * \ref NVMEDIA_LDC_MODE_GEOTRANS_TNR3, LDC performs temporal noise reduction.
 *
 * NvMediaLDCProcess() is a non-blocking call.
 *
 * NvMediaImageGetStatus() can be used to check the status of input/output
 * images.
 *
 * \param[in] ldc           NvMediaLDC Handle obtained by call to
 *                          \ref NvMediaLDCCreate().
 * \param[in] prevSurface   A pointer to the previous image output. Used only
 *                          when NvMediaLDCInitParams::ldcMode is
 *                          \ref NVMEDIA_LDC_MODE_GEOTRANS_TNR3 or
 *                          \ref NVMEDIA_LDC_MODE_TNR3.
 * \param[in] curSurface    A pointer to the source image.
 * \param[in,out] outputSurface
 *                          A pointer to the output image. Caller must create
 *                          this surface.
 * \param[inout] xSobel     A pointer to the xSobel image output. Caller must
 *                          create this surface.
 * \param[in,out] downSample
 *                          A pointer to the downsampled image output. Caller
 *                          must create this surface.
 * \param[in] ldcCtrlParams A pointer to run-time control parameters.
 * \return  A status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK - Success.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED - Invalid state.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER - Invalid input argument(s).
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED - Not supported in current config.
 * - \ref NVMEDIA_STATUS_OUT_OF_MEMORY - Insufficient memory.
 * - \ref NVMEDIA_STATUS_ERROR - A catch-all error, used when no other error
 *   code applies.
 */
NvMediaStatus
NvMediaLDCProcess(
    NvMediaLDC *ldc,
    NvMediaImage *prevSurface,
    NvMediaImage *curSurface,
    NvMediaImage *outputSurface,
    NvMediaImage *xSobel,
    NvMediaImage *downSample,
    const NvMediaLDCCtrlParams *ldcCtrlParams
);

/** @} <!-- Ends ldc_api Lens Distortion Correction sub-group -> */

/*
 * \defgroup history_nvmedia_ldc History
 * Provides change history for the NvMedia LDC API.
 *
 * \section history_nvmedia_ldc Version History
 *
 * <b> Version 1.0 </b> May 1, 2017
 * - Initial release.
 *
 * <b> Version 1.1 </b> March 16, 2018
 * - Add support of TNR2
 *
 * <b> version 1.2 </b> September 4, 2018
 * - New member variable srcSurfaceType is added to NvMediaLDCInitParams.
 */

#ifdef __cplusplus
}
#endif

#endif // _NvMedia_LDC_H
