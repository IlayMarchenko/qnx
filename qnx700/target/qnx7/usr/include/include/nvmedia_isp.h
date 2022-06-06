/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Signal Processing (ISP)</b>
 *
 * This file contains the Image Signal Processing API.
 */

#ifndef NVMEDIA_ISP_H
#define NVMEDIA_ISP_H

#include <stdint.h>

#include "nvmedia_core.h"
#include "nvmedia_image.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup nvmedia_isp_api Image Signal Processing (ISP)
 *
 * The Image Signal Processing API encompasses all NvMedia image processing
 * functions that are necessary to produce a processed image from image data
 * captured from an image sensor.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number. */
#define NVM_ISP_VERSION_MAJOR   1

/** \brief Minor Version number. */
#define NVM_ISP_VERSION_MINOR   0

/**
 * \brief Maximum supported simultaneous outputs.
 */
#define NVM_ISP_MAX_OUTPUTS                 (3u)

/**
 * \brief Maximum number of input planes.
 */
#define NVM_ISP_MAX_INPUT_PLANES            (3u)

/**
 * \brief Maximum number of queued requests.
 */
#define NVM_ISP_MAX_QUEUED_REQUESTS         (32u)

/**
 * \brief Maximum number of color components.
 */
#define NVM_ISP_MAX_COLOR_COMPONENT         (4u)

/**
 * \brief Number of radial transfer function control points.
 */
#define NVM_ISP_RADTF_POINTS                (6u)

/**
 * \brief Maximum number of linearization knee points.
 */
#define NVM_ISP_MAX_LIN_KNEE_POINTS         (10u)

/**
 * \brief Number of transfer function control points for level adjusted
 * saturation block.
 */
#define NVM_ISP_LAS_TF_POINTS               (9u)

/**
 * \brief Number of transfer function control points for global tone map.
 */
#define NVM_ISP_GTM_TF_POINTS               (18u)

/**
 * \brief Local tone map soft key width.
 */
#define NVM_ISP_LTM_SOFT_KEY_WIDTH          (8u)

/**
 * \brief Local tone map soft key height.
 */
#define NVM_ISP_LTM_SOFT_KEY_HEIGHT         (8u)

/**
 * \brief Local tone map gain points.
 */
#define NVM_ISP_LTM_GAIN_POINTS             (9u)

/**
 * \brief Number of histogram knee points.
 */
#define NVM_ISP_HIST_KNEE_POINTS            (8u)

/**
 * \brief Maximum number of local average & clip stats block regions of interest.
 */
#define NVM_ISP_MAX_LAC_ROI                 (4u)

/**
 * \brief Maximum number of windows for local average & clip in a region of
 * interest.
 */
#define NVM_ISP_MAX_LAC_ROI_WINDOWS         (32u * 32u)

/**
 * \brief Number of bins for histogram.
 */
#define NVM_ISP_HIST_BINS                   (256u)

/**
 * \brief Number of histogram bins for local tone map stats block.
 */
#define NVM_ISP_LTM_HIST_BINS               (128u)

/**
 * \brief Number of averaging windows for local tone map stats block.
 */
#define NVM_ISP_LTM_AVG_WINDOWS             (8u)

/**
 * \brief A handle representing ISP object.
 */
typedef struct _NvMediaISP NvMediaISP;

/**
 * \brief A handle representing ISP stats surface object.
 */
typedef struct _NvMediaISPStatsSurface NvMediaISPStatsSurface;

/**
 * \brief A handle representing ISP settings object.
 */
typedef struct _NvMediaISPSettings NvMediaISPSettings;

/**
 * \brief Defines supported ISP pipelines.
 */
typedef enum {
    /**
     * \brief Xavier ISP pipeline.
     */
    NVM_ISP_PIPELINE_X1 = (('X' << 24) | 0x01),
} NvMediaISPPipelineEnum;

/**
 * \brief Gives the version information for the NvMedia ISP library.
 * \param[in,out] version \ref NvMediaVersion structure which will be populated.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if the operation was successful.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer was invalid.
 */
NvMediaStatus
NvMediaISPGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Allocates an Image Signal Processing object.
 * \param[in] instanceId ISP instance ID. Valid values: 0
 * \param[in] pipelineEnum ISP pipeline configuration.
 * \param[in] maxQueuedRequests
        Determines number of processing requests can be pending for an ISP
        instance at a time.
        Supported values: [1, NVM_ISP_MAX_QUEUED_REQUESTS]
 * \return \ref NvMediaISP handle to specified isp engine instance or NULL
 * if unsuccessful.
 */
NvMediaISP *
NvMediaISPCreate(
    uint32_t instanceId,
    NvMediaISPPipelineEnum pipelineEnum,
    uint32_t maxQueuedRequests
);

/**
 * \brief Stops the image processing.
 * \param[in] isp ISP object to destroy.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPStop(
    NvMediaISP *isp
);

/**
 * \brief Destroys an Image Signal Processing object.
 * \param[in] isp ISP object.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer is NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPDestroy(
    NvMediaISP *isp
);

/**
 * \brief Allocates an ISP statistics surface object.
 * \param[in] isp ISP object.
 * \return \ref NvMediaISPStatsSurface handle to ISP statistics surface or NULL
 * if unsuccessful.
 */
NvMediaISPStatsSurface *
NvMediaISPStatsSurfaceCreate(
    NvMediaISP *isp
);

/**
 * \brief Destroys an ISP statistics surface object.
 * \param[in] statsSurface ISP statistics surface object to destroy.
 * \return \ref NvMediaStatus The status of the operation.
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPStatsSurfaceDestroy(
    NvMediaISPStatsSurface *statsSurface
);

/**
 * \brief Allocates an ISP settings object.
 * \param[in] isp ISP object.
 * \param[in] pipelineEnum
 *      ISP pipeline configuration, reserved for future extension.
        For now this must be same as value given in \ref NvMediaISPCreate
 * \return \ref NvMediaISPSettings handle to ISP settings object or NULL
 * if unsuccessful.
 */
NvMediaISPSettings *
NvMediaISPSettingsCreate(
    NvMediaISP *isp,
    NvMediaISPPipelineEnum pipelineEnum
);

/**
 * \brief Destroys an ISP settings object.
 * \param[in] settings ISP settings object to destroy.
 * \return \ref NvMediaStatus The status of the operation.
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPSettingsDestroy(
    NvMediaISPSettings *settings
);

/**
 * \brief Holds controls for ISP linearization (LIN) block.
 */
typedef struct {
    /**
     * Holds boolean to enable linearization block.
     */
    NvMediaBool enable;
    /**
     * Holds count of piecewise linear transfer function.
     * @li Supported values: [1, NVM_ISP_MAX_INPUT_PLANES]
     */
    uint32_t numPlanes;
    /**
     * Holds count of knee points for each plane.
     * @li Supported values: [2, NVM_ISP_MAX_LIN_KNEE_POINTS]
     */
    uint32_t numKneePoints[NVM_ISP_MAX_INPUT_PLANES];
    /**
     * Holds knee points for piecewise linear transfer function for each plane.
     * @li Supported values for X coordinate of knee point: [0.0, 1.0]
     * @li Supported values for Y coordinate of knee point: [0.0, 1.0]
     * @li Y coordinate of the 1st knee point must be 0.0.
     */
    NvMediaPointDouble kneePoints[NVM_ISP_MAX_INPUT_PLANES][NVM_ISP_MAX_LIN_KNEE_POINTS];
} NvMediaISPLinearization;

/**
 * \brief Programs linearizartion block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a linearization
 *                      block.
 * \param[in] size      Size of the linearization block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLinearization(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLinearization *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP black level correction (BLC) block.
 */
typedef struct {
    /**
     * Holds boolean to enable black level correction block.
     */
    NvMediaBool enable;
    /**
     * Holds black level correction values in RGGB/RCCB/RCCC component order
     * for each plane & each color component.
     * @li Supported values: [0.0, 1.0]
     */
    double_t pedestal[NVM_ISP_MAX_INPUT_PLANES][NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPBlackLevelCorrection;

/**
 * \brief Programs black level correction block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a black level
 *                      correction block.
 * \param[in] size      Size of the black level correction block control
 *                      structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetBlackLevelCorrection(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPBlackLevelCorrection *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP white balance correction (WBC) block.
 */
typedef struct {
    /**
     * Holds boolean to enable white balance correction block.
     */
    NvMediaBool enable;
    /**
     * Holds white balance gains in RGGB/RCCB/RCCC component order for each
     * plane & each color component.
     * @li Supported values: [0.0, 8.0]
     */
    float_t wbGain[NVM_ISP_MAX_INPUT_PLANES][NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPWhiteBalanceCorrection;

/**
 * \brief Programs white balance correction block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a white balance
 *                      correction block.
 * \param[in] size      Size of the white balance correction block control
 *                      structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetWhiteBalanceCorrection(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPWhiteBalanceCorrection *controls,
    size_t size
);

/**
 * \brief Defines supported exposure fusion modes.
 */
typedef enum {
    /**
     * Specifies use plane 0.
     */
    NVM_ISP_EXP_FUSION_USE_0 = 0,
    /**
     * Specifies use plane 1.
     */
    NVM_ISP_EXP_FUSION_USE_1 = 1,
    /**
     * Specifies use plane 2.
     */
    NVM_ISP_EXP_FUSION_USE_2 = 2,
    /**
     * Specifies blend plane 0 & 1.
     */
    NVM_ISP_EXP_FUSION_BLEND_01 = 3,
    /**
     * Specifies blend all planes.
     */
    NVM_ISP_EXP_FUSION_BLEND_ALL = 4,
} NvMediaISPExposureFusionMode;

/**
 * \brief Holds controls for ISP exposure fusion (Fusion) block.
 */
typedef struct {
    /**
     * Holds boolean to enable exposure fusion block.
     */
    NvMediaBool enable;
    /**
     * Holds ratio of shortest exposure gain vs exposure gain for each plane.
     * Index 0 & 2 are for longest & shortest exposure respectively.
     * @li Supported values: [0.0, 1.0]
     */
    float_t scaleFactors[NVM_ISP_MAX_INPUT_PLANES];
    /**
     * Holds exposure fusion mode.
     */
    NvMediaISPExposureFusionMode fusionMode;
} NvMediaISPExposureFusion;

/**
 * \brief Programs exposure fusion block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for an exposure
 *                      fusion block.
 * \param[in] size      Size of the exposure fusion block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetExposureFusion(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPExposureFusion *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP bad pixel correction (BPC) block.
 */
typedef struct {
    /**
     * Holds boolean to enable bad pixel correction block.
     */
    NvMediaBool enable;
    /**
     * Holds strength of bad pixel correction.
     * @li Supported values: [0.0, 1.0],
     * 0.0 & 1.0 means minimum & maximum strength respectively
     */
    float_t strength;
    /**
     * Holds boolean to enable noise estimation.
     */
    NvMediaBool noiseProfileEnable;
    /**
     * Holds noise profile nunber.
     * @li Supported values: [0, 1024]
     */
    uint32_t profileNum;
    /**
     * Holds gain applied in sensor effecting whole noise profile.
     * @li Supported values: [0.0, 10000.0]
     */
    float_t sensorGain;
    /**
     * Holds white balance gain applied in sensor effecting whole noise profile.
     * @li Supported values: [0.0, 128.0]
     */
    float_t wbGain[NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPBadPixelCorrection;

/**
 * \brief Programs bad pixel correction block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      control structure for a bad pixel correction block.
 * \param[in] size      Size of the bad pixel correction block control
 *                      structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetBadPixelCorrection(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPBadPixelCorrection *controls,
    size_t size
);

/**
 * \brief Defines spline control point.
 */
typedef struct {
    /**
     * Defines X coordinate of control point.
     */
    float_t x;
    /**
     * Defines Y coordinate of control point.
     */
    float_t y;
    /**
     * Defines slope of spline curve at control point.
     */
    double_t slope;
} NvMediaISPSplineControlPoint;

/**
 * \brief Defines an ellipse.
 */
typedef struct {
    /**
     * Defines center of the ellipse.
     */
    NvMediaPoint center;
    /**
     * Defines horizontal axis of the ellipse.
     */
    uint32_t horizontalAxis;
    /**
     * Defines vertical axis of the ellipse.
     */
    uint32_t verticalAxis;
    /**
     * Defines angle of the ellipse horizontal axis from x-axis in degrees in
     * clockwise direction.
     */
    float_t angle;
} NvMediaISPEllipse;

/**
 * \brief Defines a radial transform.
 */
typedef struct {
    /**
     * Defines ellipse for radial transform.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively.
     *
     * @li Supported values for X coordinate of the center: [0, input width]
     * @li Supported values for Y coordinate of the center: [0, input height]
     * @li Supported values for hortizontal axis: [16, 2 x input width]
     * @li Supported values for vertical axis: [16, 2 x input height]
     * @li Supported values for angle: [0.0, 360.0]
     */
    NvMediaISPEllipse radialTransform;
    /**
     * Defines spline control point for radial transfer function.
     * @li Supported values for X coordinate of spline control point : [0.0, 2.0]
     * @li Supported values for Y coordinate of spline control point : [0.0, 16.0]
     * @li Supported values for slope of spline control point : \f$[-2^{16}, 2^{16}]\f$
     */
    NvMediaISPSplineControlPoint controlPoints[NVM_ISP_RADTF_POINTS];
} NvMediaISPRadialTF;

/**
 * \brief Holds controls for ISP lens shading correction (LSC) block.
 */
typedef struct {
    /**
     * Holds boolean to enable CCT based lens shading correction.
     */
    NvMediaBool cctBasedLSCEnable;
    /**
     * Holds color correlated temperature.
     * @li Supported values: [1000.0, 20000.0]
     */
    float_t cct;
    /**
     * Holds ratio between corner & center lens shading correction.
     * @li Supported values: [0.0, 1.0]
     */
    float_t fallOff;
} NvMediaISPLensShadingCorrection;

/**
 * \brief Programs lens shading correction block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a lens shading
 *                      correction block.
 * \param[in] size      Size of the lens shading correction block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLensShadingCorrection(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLensShadingCorrection *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP demosaic (DM) block.
 */
typedef struct {
    /**
     * Holds strength of demosaicing.
     * @li Supported values: [0.0, 1.0],
     * 0.0 & 1.0 means minimum & maximum strength respectively
     */
    float_t strength;
} NvMediaISPDemosaic;

/**
 * \brief Programs demosaic block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a demosaic block.
 * \param[in] size      Size of the demosaic block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetDemosaic(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPDemosaic *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP level adjusted saturation (LAS) block.
 */
typedef struct {
    /**
     * Holds boolean to enable level adjusted saturation block.
     */
    NvMediaBool enable;
    /**
     * Holds spline control points for transfer function.
     * @li Supported values for X coordinate of spline control point : [0.0, 4.0]
     * @li Supported values for Y coordinate of spline control point : [0.0, 4.0]
     * @li Supported values for slope of spline control point : \f$[-2^{16}, 2^{16}]\f$
     */
    NvMediaISPSplineControlPoint controlPoints[NVM_ISP_LAS_TF_POINTS];
} NvMediaISPLevelAdjSat;

/**
 * \brief Programs level adjusted saturation block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a level
 *                      adjusted saturation block.
 * \param[in] size      Size of the level adjusted saturation block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLevelAdjSat(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLevelAdjSat *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP noise reduction (NR) block.
 */
typedef struct {
    /**
     * Holds boolean to enable noise reduction block.
     */
    NvMediaBool enable;
    /**
     * Holds strength of noise reduction.
     * @li Supported values: [0.0, 1.0],
     * 0.0 & 1.0 means minimum & maximum strength respectively
     */
    float_t strength;
    /**
     * Holds boolean to enable noise estimation.
     */
    NvMediaBool noiseProfileEnable;
    /**
     * Holds noise profile number.
     * @li Supported values: [0, 1024]
     */
    uint32_t profileNum;
    /**
     * Holds gain applied in sensor effecting whole noise profile.
     * @li Supported values: [0.0, 10000.0]
     */
    float_t sensorGain;
    /**
     * Holds white balance gain applied in sensor effecting whole noise profile.
     * @li Supported values: [0.0, 128.0]
     */
    float_t wbGain[NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds boolean to enable radial transform.
     */
    NvMediaBool radialTFEnable;
    /**
     * Holds a radial transfer function.
     * @li Supported values: Check the declaration of \ref NvMediaISPRadialTF
     */
    NvMediaISPRadialTF radialTF;
} NvMediaISPNoiseReduction;

/**
 * \brief Programs noise reduction block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      noise reduction block.
 * \param[in] size      Size of the noise reduction block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetNoiseReduction(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPNoiseReduction *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP color correction matrix (CCM) block.
 */
typedef struct {
    /**
     * Holds boolean to enable color correction matrix block.
     */
    NvMediaBool enable;
    /**
     * Holds color correction matrix.
     * @li Supported values: [-8.0, 8.0]
     */
    float_t matrix[3][3];
} NvMediaISPColorCorrectionMatrix;

/**
 * \brief Programs color correction matrix block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      color correction matrix block.
 * \param[in] size      Size of the color correction matrix block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetColorCorrectionMatrix(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPColorCorrectionMatrix *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP global tone map (GTM) block.
 */
typedef struct {
    /**
     * Holds boolean to enable global tone map block.
     */
    NvMediaBool enable;
    /**
     * Holds spline control points for global tone map transfer function.
     * @li Supported values for X coordinate of spline control point: [0.0, 1.0]
     * @li Supported values for Y coordinate of spline control point: [0.0, 1.0]
     * @li Supported values for slope of spline control point: \f$[0.0, 2^{17}]\f$
     */
    NvMediaISPSplineControlPoint controlPoints[NVM_ISP_GTM_TF_POINTS];
} NvMediaISPGlobalToneMap;

/**
 * \brief Programs global tone map block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      global tone map block.
 * \param[in] size      Size of the global tone map block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetGlobalToneMap(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPGlobalToneMap *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP local tone map (LTM) block.
 */
typedef struct {
    /**
     * Holds boolean to enable local tone map block.
     */
    NvMediaBool enable;
    /**
     * Holds softkey signal. Softkey signal is a low resolution estimate of the
     * image used to determine the local average tone.
     * @li Supported values: [0.0, 1.0]
     */
    float_t softKey[NVM_ISP_LTM_SOFT_KEY_HEIGHT][NVM_ISP_LTM_SOFT_KEY_WIDTH];
    /**
     * Holds piecewise linear transfer function for large scale contrast gain.
     * @li Supported values: [0.0, 16.0]
     */
    float_t largeScaleContrastGain[NVM_ISP_LTM_GAIN_POINTS];
    /**
     * Holds piecewise linear transfer function for small scale contrast gain.
     * @li Supported values: [0.0, 16.0]
     */
    float_t smallScaleContrastGain[NVM_ISP_LTM_GAIN_POINTS];
    /**
     * Holds piecewise linear transfer function to adjust saturation based on
     * tone value.
     * @li Supported values: [-1.0, 1.0]
     */
    float_t saturation[NVM_ISP_LTM_GAIN_POINTS];
} NvMediaISPLocalToneMap;

/**
 * \brief Programs local tone map block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      local tone map block.
 * \param[in] size      Size of the local tone map block control structure.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLocalToneMap(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLocalToneMap *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP color space conversion (CSC) block.
 */
typedef struct {
    /**
     * Holds boolean to enable color space conversion block.
     */
    NvMediaBool enable;
    /**
     * Holds color space conversion matrix.
     * @li Supported values: [-8.0, 8.0]
     */
    float_t matrix[3][3];
} NvMediaISPColorSpaceConversion;

/**
 * \brief Programs color space conversion block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      color space conversion block.
 * \param[in] size      Size of the color space conversion block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetColorSpaceConversion(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPColorSpaceConversion *controls,
    size_t size
);

/**
 * \brief Programs inverse color space conversion block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for an
 *                      inverse color space conversion block.
 * \param[in] size      Size of the inverse color space conversion block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetInvColorSpaceConversion(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPColorSpaceConversion *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP saturation (SAT) block.
 */
typedef struct {
    /**
     * Holds boolean to enable saturation block.
     */
    NvMediaBool enable;
    /**
     * Holds saturation value.
     * @li Supported values: [-1.0, 1.0],
     * -1.0, 0.0 & 1.0 means 0%, 100% & 200% saturation respectively
     */
    float_t saturation;
} NvMediaISPSaturation;

/**
 * \brief Programs saturation block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a saturation block.
 * \param[in] size      Size of the saturation block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetSaturation(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPSaturation *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP sharpness (Sharp) block.
 */
typedef struct {
    /**
     * Holds boolean to enable sharpness block.
     */
    NvMediaBool enable;
    /**
     * Holds strength of sharpness.
     * @li Supported values: [0.0, 1.0],
     * 0.0 & 1.0 means minimum & maximum strength respectively
     */
    float_t strength;
} NvMediaISPSharpness;

/**
 * \brief Programs sharpness block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a sharpness block.
 * \param[in] size      Size of the sharpness block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetSharpness(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPSharpness *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP downscale (DS) block.
 */
typedef struct {
    /**
     * Holds boolean to enable downscale block.
     */
    NvMediaBool enable;
    /**
     * Holds image width after downscaling.
     * @li Supported values: [input width / 32, input width]
     */
    uint32_t downscaledWidth;
    /**
     * Holds image height after downscaling.
     * @li Supported values: [input height / 32, input height]
     */
    uint32_t downscaledHeight;
} NvMediaISPDownscale;

/**
 * \brief Programs downscale block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a downscale block.
 * \param[in] size      Size of the downscale block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetDownscale(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPDownscale *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP clip (Clip) block.
 */
typedef struct {
    /**
     * Holds boolean to enable clip block.
     */
    NvMediaBool enable;
    /**
     * Holds minimum clip value for each color component in RGGB/RCCB/RCCC
     * component order for bayer data & RGB/YUV component order for
     * RGB/YUV data.
     * @li Supported values: [-0.125, 2.0]
     */
    float_t min[NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds maximum clip value for each color component in RGGB/RCCB/RCCC
     * component order for bayer data & RGB/YUV component order for RGB/YUV
     * data.
     * @li Supported values: [-0.125, 2.0], max >= min
     */
    float_t max[NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPClip;

/**
 * \brief Programs clip block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a clip block.
 * \param[in] size      Size of the clip block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetClip(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPClip *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP offset (Offset) block.
 */
typedef struct {
    /**
     * Holds boolean to enable offset block.
     */
    NvMediaBool enable;
    /**
     * Holds offset value for each color component.
     * @li Supported values: [-2.0, 2.0]
     */
    float_t offset[NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPOffset;

/**
 * \brief Programs offset block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for an offset block.
 * \param[in] size      Size of the offset block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetOffset(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPOffset *controls,
    size_t size
);

/**
 * \brief Holds controls for ISP digital gain (DG) block.
 */
typedef struct {
    /**
     * Holds boolean to enable digital gain block.
     */
    NvMediaBool enable;
    /**
     * Holds digital gain value.
     * @li Supported values: [0.0, 8.0]
     */
    float_t digitalGain;
} NvMediaISPDigitalGain;

/**
 * \brief Programs digital gain block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      digital gain block.
 * \param[in] size      Size of the digital gain block control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetDigitalGain(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPDigitalGain *controls,
    size_t size
);

/**
 * \brief Holds controls for histogram statistics (HIST Stats).
 */
typedef struct {
    /**
     * Holds boolean to enable histogram statistics block.
     */
    NvMediaBool enable;
    /**
     * Holds offset to be applied to input data prior to bin mapping.
     * @li Supported values: [-2.0, 2.0]
     */
    float_t offset;
    /**
     * Holds bin index specifying different zones in the histogram. Each zone
     * can have different number of bins.
     * @li Supported values: [1, 255]
     */
    uint8_t knees[NVM_ISP_HIST_KNEE_POINTS];
    /**
     * Holds \f$log_2\f$ range of the pixel values to be considered for each
     * zone. Whole pixel range is divided into NVM_ISP_HIST_KNEE_POINTS
     * zones.
     * @li Supported values: [0, 21]
     */
    uint8_t ranges[NVM_ISP_HIST_KNEE_POINTS];
    /**
     * Holds rectangluar mask for selecting pixels.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively. Either memset the rectangluar to 0 or set
     * it rectangle to include full image to have no rectangular mask.
     *
     * @li Supported values: Rectangle must be within input image & must be a
     * valid rectangle ((right > left) && (bottom > top))
     */
    NvMediaRect rectangularMask;
    /**
     * Holds boolean to enable mask for excluding pixels outside specified
     * elliptical area.
     */
    NvMediaBool ellipticalMaskEnable;
    /**
     * Holds elliptical mask for excluding pixels outside specified
     * elliptical area.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively.
     *
     * @li Supported values for X coordinate of the center: [0, input width]
     * @li Supported values for Y coordinate of the center: [0, input height]
     * @li Supported values for hortizontal axis: [16, 2 x input width]
     * @li Supported values for vertical axis: [16, 2 x input height]
     * @li Supported values for angle: [0.0, 360.0]
     */
    NvMediaISPEllipse ellipticalMask;
    /**
     * Holds boolean to enable elliptical weighting of pixels based on spatial
     * location. This can be used to compensate for lens shading when
     * histogram is measured before lens shading correction.
     */
    NvMediaBool ellipticalWeightEnable;
    /**
     * Holds a radial transfer function for elliptical weight.
     * @li Supported values: Check the declaration of \ref NvMediaISPRadialTF
     */
    NvMediaISPRadialTF radialTF;
} NvMediaISPHistogramStats;

/**
 * \brief Programs histogram statistics block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      histogram statistics block.
 * \param[in] size      Size of the histogram statistics block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetHistogramStats(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPHistogramStats *controls,
    size_t size
);

/**
 * \brief Defines the windows used in ISP stats calculations.
 *
 * \code
 * ------------------------------------------------------------------------------
 * |         startOffset    horizontalInterval                                  |
 * |                    \  |--------------|                                     |
 * |                     - *******        *******        *******                |
 * |                     | *     *        *     *        *     *                |
 * |                     | *     *        *     *        *     *                |
 * |                     | *     *        *     *        *     *                |
 * |                     | *******        *******        *******                |
 * |  verticalInterval-->|                                        \             |
 * |                     |                                          numWindowsV |
 * |                     |                                        /             |
 * |                     - *******        *******        *******                |
 * |                     | *     *        *     *        *     *                |
 * |            height-->| *     *        *     *        *     *                |
 * |                     | *     *        *     *        *     *                |
 * |                     - *******        *******        *******                |
 * |                       |-----|                                              |
 * |                        width     \      |     /                            |
 * |                                    numWindowsH                             |
 * ------------------------------------------------------------------------------
 * \endcode
 */
typedef struct {
    /**
     * Defines width of the window in pixels.
     */
    uint32_t width;
    /**
     * Defines height of the window in pixels.
     */
    uint32_t height;
    /**
     * Defiens number of windows horizontally.
     */
    uint32_t numWindowsH;
    /**
     * Defines number of windows vertically.
     */
    uint32_t numWindowsV;
    /**
     * Defines distance between the left edges of one window and a horizontally
     * adjacent window.
     */
    uint32_t horizontalInterval;
    /**
     * Defines distance between the top edges of one window and a vertically
     * adjacent window.
     */
    uint32_t verticalInterval;
    /**
     * Defines position of the top-left pixel in the top-left window.
     */
    NvMediaPoint startOffset;
} NvMediaISPStatisticsWindows;

/**
 * \brief Holds controls for local average & clip statistics (LAC Stats)
 */
typedef struct {
    /**
     * Holds boolean to enable local average & clip statistics block.
     */
    NvMediaBool enable;
    /**
     * Holds minimum value of pixels in RGGB/RCCB/RCCC order.
     * @li Supported values: [0.0, 1.0]
     */
    float_t min[NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds maximum value of pixels in RGGB/RCCB/RCCC order.
     * @li Supported values: [0.0, 1.0], max >= min
     */
    float_t max[NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds boolean to enable indiviual region of interest.
     */
    NvMediaBool roiEnable[NVM_ISP_MAX_LAC_ROI];
    /**
     * Holds local average & clip windows for each region of interest.
     * @li Supported values for width of the window: [2, 256], must be an even number
     * @li Supported values for height of the window: [2, 256]
     * @li Supported values for number of the windows horizontally: [1, 32]
     * @li Supported values for number of the windows vertically: [1, 32]
     * @li Supported values for horizontal interval between windows: \f$[4, 2^{16})\f$, must be an even number
     * @li Supported values for vertical interval between windows: \f$[2, 2^{16})\f$
     * @li Supported values for X coordinate of start offset: \f$[0, 2^{16})\f$, must be an even number
     * @li Supported values for Y coordinate of start offset: \f$[0, 2^{16})\f$
     */
    NvMediaISPStatisticsWindows windows[NVM_ISP_MAX_LAC_ROI];
    /**
     * Holds boolean to enable mask for excluding pixels outside specified
     * elliptical area for each region of interest.
     */
    NvMediaBool ellipticalMaskEnable[NVM_ISP_MAX_LAC_ROI];
    /**
     * Holds elliptical mask for excluding pixels outside specified elliptical area.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively.
     *
     * @li Supported values for X coordinate of the center: [0, input width]
     * @li Supported values for Y coordinate of the center: [0, input height]
     * @li Supported values for hortizontal axis: [16, 2 x input width]
     * @li Supported values for vertical axis: [16, 2 x input height]
     * @li Supported values for angle: [0.0, 360.0]
     */
    NvMediaISPEllipse ellipticalMask;
} NvMediaISPLocalAvgClipStats;

/**
 * \brief Programs local average and clip statistics block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      local average and clip statistics block.
 * \param[in] size      Size of the local average and clip statistics block
 *                      control structure.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLocalAvgClipStats(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLocalAvgClipStats *controls,
    size_t size
);

/**
 * \brief Holds controls for bad pixel statistics (BP Stats).
 */
typedef struct {
    /**
     * Holds boolean to enable bad pixel statistics block.
     */
    NvMediaBool enable;
    /**
     * Holds rectangluar mask for selecting pixels.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively. Either memset the rectangle to 0 or set it
     * to include full image to have no rectangular mask.
     *
     * @li Supported values: Rectangle must be within input image & must be a
     * valid rectangle ((right > left) && (bottom > top))
     */
    NvMediaRect rectangularMask;
} NvMediaISPBadPixelStats;

/**
 * \brief Programs bad pixel statistics block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      control structure for a bad pixel statistics block.
 * \param[in] size      Size of the bad pixel statistics block control
 *                      structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetBadPixelStats(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPBadPixelStats *controls,
    size_t size
);

/**
 * \brief Holds controls for local tone map statistics (LTM Stats).
 */
typedef struct {
    /**
     * Holds boolean to enable local tonemap statistics block.
     */
    NvMediaBool enable;
    /**
     * Holds rectangluar mask for selecting pixels.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively. Either memset the rectangle to 0 or set it
     * to include full image to have no rectangular mask.
     *
     * @li Supported values: Rectangle must be within input image & must be a
     * valid rectangle ((right > left) && (bottom > top))
     */
    NvMediaRect rectangularMask;
    /**
     * Holds boolean to enable elliptical mask to exclude pixels outside
     * elliptical area.
     */
    NvMediaBool ellipticalMaskEnable;
    /**
     * Holds elliptical mask for excluding pixels outside specified
     * elliptical area.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively.
     *
     * @li Supported values for X coordinate of the center: [0, input width]
     * @li Supported values for Y coordinate of the center: [0, input height]
     * @li Supported values for hortizontal axis: [16, 2 x input width]
     * @li Supported values for vertical axis: [16, 2 x input height]
     * @li Supported values for angle: [0.0, 360.0]
     */
    NvMediaISPEllipse ellipticalMask;
} NvMediaISPLocalToneMapStats;

/**
 * \brief Programs local tone map statistics block controls.
 * \param[in] settings  Handle representing the ISP settings object.
 * \param[in] instance  Instance of the block to be programmed.
 * \param[in] controls  A pointer to a control structure for a
 *                      local tone map statistics block.
 * \param[in] size      Size of the local tone map statistics block
 *                      control structure.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input pointer was NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaISPSetLocalToneMapStats(
    NvMediaISPSettings *settings,
    uint32_t instance,
    const NvMediaISPLocalToneMapStats *controls,
    size_t size
);

/**
 * \brief Holds ISP processing parameters.
 */
typedef struct {
    /**
     * Holds input image(s).
     */
    NvMediaImageGroup input;
    /**
     * Holds cropping rectangle for input image.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively. Either memset the rectangle to 0 or set it
     * to include full image for no cropping.
     *
     * Input crop only supports cropping in vertical direction, meaning
     * left & bottom cordinated must be 0 & input width respectively.
     */
    NvMediaRect inputCropRect;
    /**
     * Holds output image for each ISP output.
     * An output would be enabled if the corresponding image is not NULL.
     */
    NvMediaImage *output[NVM_ISP_MAX_OUTPUTS];
    /**
     * Holds cropping rectangle for each output image.
     *
     * Coordinates of image top-left & bottom-right points are (0, 0) &
     * (width, height) respectively. Either memset the rectangle to 0 or set it
     * to include full image for no cropping.
     *
     * Rectangle must be within input image or downscaled image if downscaling
     * is enabled. Cropped width & height must be same as output width & height
     * respectively and cropped width must be even.
     *
     */
    NvMediaRect outputCropRect[NVM_ISP_MAX_OUTPUTS];
    /**
     * Holds output statistics surface.
     * Must not be NULL, if any of the statistics blocks are enabled.
     */
    NvMediaISPStatsSurface *statsSurface;
    /**
     * Holds ISP settings.
     */
    const NvMediaISPSettings *settings;
} NvMediaISPProcessParams;

/**
 * \brief ISP processing function.
 * \param[in] isp ISP object.
 * \param[in] params  ISP processing parameters.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPProcess(
    NvMediaISP *isp,
    const NvMediaISPProcessParams *params
);

/**
 * \brief Holds histogram statistics (HIST Stats) data.
 */
typedef struct {
    /**
     * Holds histogram data for each color component in RGGB/RCCB/RCCC order.
     */
    uint32_t data[NVM_ISP_HIST_BINS][NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds number of pixels excluded by the elliptical mask for each
     * color component.
     */
    uint32_t excludedCount[NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPHistogramStatsData;

/**
 * \brief Gets the histogram statistics data.
 * \param[in] statsSurface  Statistics surface.
 * \param[in] instance      Instance of the block to get statistics.
 * \param[in,out] statsData A pointer to histogram statistics data.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPGetHistogramStatsData(
    NvMediaISPStatsSurface *statsSurface,
    uint32_t instance,
    NvMediaISPHistogramStatsData *statsData
);

/**
 * \brief Holds local average & clip statistics data for a region of interest.
 */
typedef struct {
    /**
     * Holds number of windows in one region of interest.
     */
    uint32_t numWindows;
    /**
     * Holds average pixel value for each window & each color component in
     * RGGB/RCCB/RCCC order.
     */
    float_t average[NVM_ISP_MAX_LAC_ROI_WINDOWS][NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds number of pixels excluded by the elliptical mask for each window &
     * each color component in RGGB/RCCB/RCCC order.
     */
    uint32_t maskedOffCount[NVM_ISP_MAX_LAC_ROI_WINDOWS][NVM_ISP_MAX_COLOR_COMPONENT];
    /**
     * Holds number of clipped pixels for each window & each color component in
     * RGGB/RCCB/RCCC order.
     */
    uint32_t clippedCount[NVM_ISP_MAX_LAC_ROI_WINDOWS][NVM_ISP_MAX_COLOR_COMPONENT];
} NvMediaISPLocalAvgClipStatsROIData;

/**
 * \brief Holds local average & clip statistics block (LAC Stats) data.
 */
typedef struct {
    /**
     * Holds statistics data for each region of interest.
     */
    NvMediaISPLocalAvgClipStatsROIData data[NVM_ISP_MAX_LAC_ROI];
} NvMediaISPLocalAvgClipStatsData;

/**
 * \brief Gets the local average & clip statistics data.
 * \param[in] statsSurface  A pointer to a statistics surface.
 * \param[in] instance      Instance of the block to get statistics.
 * \param[in,out] statsData A pointer to local average & clip statistics data.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPGetLocalAvgClipStatsData(
    NvMediaISPStatsSurface *statsSurface,
    uint32_t instance,
    NvMediaISPLocalAvgClipStatsData *statsData
);

/**
 * \brief Holds local tone map statistics block (LTM Stats) data.
 */
typedef struct {
    /**
     * Holds count of pixels for each histogram bin.
     */
    uint32_t histogram[NVM_ISP_LTM_HIST_BINS];
    /**
     * Holds average tone in local average window. The tone values are computed
     * by converting YUV input to tone, taking logarithm from the value and
     * normalizing it so that dynamic range is mapped to range [0.0, 1.0].
     * If no pixels contributed to a windows (either because the windows was
     * out of image boundaries, or it was completely excluded by rectangular
     * or elliptical masks) this value is set to zero.
     */
    float_t localAverageTone[NVM_ISP_LTM_AVG_WINDOWS][NVM_ISP_LTM_AVG_WINDOWS];
    /**
     * Holds number of pixels for each local average window that contributed to
     * statistics.
     */
    uint32_t nonMaskedCount[NVM_ISP_LTM_AVG_WINDOWS][NVM_ISP_LTM_AVG_WINDOWS];
} NvMediaISPLocalToneMapStatsData;

/**
 * \brief Gets the local tone map statistics data.
 * \param[in] statsSurface  A pointer to a statistics surface.
 * \param[in] instance      Instance of the block to get statistics.
 * \param[in,out] statsData A pointer to local tone map statistics data.
 * \return  The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPGetLocalToneMapStatsData(
    NvMediaISPStatsSurface *statsSurface,
    uint32_t instance,
    NvMediaISPLocalToneMapStatsData *statsData
);

/**
 * \brief Holds bad pixel statistics (BP Stats) data.
 */
typedef struct {
    /**
     * Holds bad pixel count for pixels corrected upwards within the window.
     */
    uint32_t highInWin;
    /**
     * Holds bad pixel count for pixels corrected downwards within the window.
     */
    uint32_t lowInWin;
    /**
     * Holds accumulatd pixel adjustment for pixels corrected upwards within the
     * window.
     */
    uint32_t highMagInWin;
    /**
     * Hols accumulatd pixel adjustment for pixels corrected downwards within
     * the window.
     */
    uint32_t lowMagInWin;
    /**
     * Holds bad pixel count for pixels corrected upwards outside the window.
     */
    uint32_t highOutWin;
    /**
     * Holds bad pixel count for pixels corrected downwards outside the window.
     */
    uint32_t lowOutWin;
    /**
     * Holds accumulatd pixel adjustment for pixels corrected upwards outside
     * the window. */
    uint32_t highMagOutWin;
    /**
     * Holds accumulatd pixel adjustment for pixels corrected downwards outside
     * the window.
     */
    uint32_t lowMagOutWin;
} NvMediaISPBadPixelStatsData;

/**
 * \brief Gets the bad pixel statistics data.
 * \param[in] statsSurface  A pointer to a statistics surface.
 * \param[in] instance      Instance of the block to get statistics.
 * \param[in,out] statsData A pointer to bad pixel statistics data.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input arguments were
 *        invalid.
 * - \ref NVMEDIA_STATUS_ERROR if there is any error.
 */
NvMediaStatus
NvMediaISPGetBadPixelStatsData(
    NvMediaISPStatsSurface *statsSurface,
    uint32_t instance,
    NvMediaISPBadPixelStatsData *statsData
);

/*@} <!-- Ends nvmedia_isp_api Image Signal Processing --> */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* NVMEDIA_ISP_H */
