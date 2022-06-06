/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */


/**
 * \file
 * \brief <b> NVIDIA Media VPI Interface </b>
 *
 * @b Description: This file contains the NvMedia VPI API.
 */

#ifndef _NvMediaVPI_H
#define _NvMediaVPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_common.h"
#include "nvmedia_image.h"
#include "nvmedia_array.h"
#include "nvmedia_image_pyramid.h"
#include "nvmedia_cvscratchpad.h"

/**
 * \defgroup NvMediaVPI Vision Programming Interface
 *
 * The NvMedia Vision Programming Interface (VPI) API contains NvMedia functions
 * for accessing the Computer Vision (CV) hardware accelerated algorithms.
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major version number. */
#define NVMEDIA_VPI_VERSION_MAJOR   2
/** \brief Minor version number. */
#define NVMEDIA_VPI_VERSION_MINOR   3

/** \brief Maximum number of tasks that can be queued. Used by
    NvMediaVPICreate(). */
#define NVMEDIA_VPI_MAX_QUEUED_TASKS 64

/**
 * \brief Holds an opaque object representing NvMediaVPI.
 */
typedef struct NvMediaVPI NvMediaVPI;

/** \brief Defines the different types of VPI-specific arrays.
 */
typedef enum {
    /*! Keypoint type. */
    NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT = 0,
    /*! Bounding Box with Transform type. */
    NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM = 1,
    /*! Transform type. */
    NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM = 2,
    /*! Number of types. */
        /* If more types are needed, add above this and update this. */
    NVMEDIA_VPI_ARRAY_NUM_TYPES = 2,
} NvMediaVPIArrayType;

/**
 * \brief  Holds 2D floating point definition.
 */
typedef struct {
    /*! x co-ordinate. */
    float x;
    /*! y co-ordinate. */
    float y;
} NvMediaVPIPoint2Df;

/**
 * \brief Axis Aligned Bounding Box.
 *  Holds coordinates, scale factor delta portion and status.
 */
typedef struct {
    /*! x coordinate. */
    float x;
    /*! y coordinate. */
    float y;
    /*! width of bounding box. */
    float width;
    /*! height of bounding box. */
    float height;
    /*! 1 indicates tracking is invalid, 0 indicates valid. */
    uint8_t trackingStatus;
    /*! 1 indicatestemplate needs updating, 0 indicates template is valid. */
    uint8_t updateTemplate;
    /*! Reserved for future use. Do not read/write this field. */
    uint8_t reserved1;
    /*! Reserved for future use. Do not read/write this field. */
    uint8_t reserved2;
} NvMediaVPIAABB;

/**
 * \brief  3x3 transform matrix.
 */
typedef struct {
    float mat3[3][3];
} NvMediaVPI2DTransform;

/**
 * \brief Translation with Scale parameters.
 */
typedef struct {
    /*! Scale. */
    float deltaScale;
    /*! Need description. */
    float deltaX;
    /*! Need description. */
    float deltaY;
} NvMediaVPITranslationWithScale;

/**
 * \brief  Holds bounding box definition.
 */
typedef struct {
    /*! Transform array. */
    NvMediaVPI2DTransform transform;
    /*! width of bounding box. */
    float width;
    /*! height of bounding box. */
    float height;
    /*! 1 indicates tracking is invalid, 0 indicates valid. */
    uint8_t trackingStatus;
    /*! 1 indicates template needs updating, 0 indicates template is valid. */
    uint8_t templateStatus;
    /*! Reserved for future. Do not read/write this field. */
    uint8_t reserved1;
    /*! Reserved for future. Do not read/write this field. */
    uint8_t reserved2;
} NvMediaVPIBoundingBoxWithTransform;

/**
 * \brief  Returns the number of HW engines accessible.
 * \param[in] numEngines        A pointer to the number of engines.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIGetNumEngines(
    uint32_t *numEngines
);

/**
 * \brief  Returns version information for the NvMediaVPI library.
 * \param[in] version   A pointer to a \ref NvMediaVersion structure
 *                      filled by the NvMediaVPI library.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer wass invalid.
 */
NvMediaStatus
NvMediaVPIGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an NvMediaVPI object.
 * \param[in] Id    Engine ID. Must be less than the value returned by
 *                  NvMediaVPIGetNumEngines().
 * \param[in] maxQueuedTasks
 *                  Number of simultaneous tasks that can be submitted to an
 *                  instance at a time, before \ref NvMediaVPIFlush must be
 *                  called. maxQueuedTasks is clamped between 1 and
 *                  \ref NVMEDIA_VPI_MAX_QUEUED_TASKS.
 * \return  A pointer to an \ref NvMediaVPI if successful, or NULL otherwise.
 */
NvMediaVPI *
NvMediaVPICreate(
    const uint32_t Id,
    const uint32_t maxQueuedTasks
);

/**
 * \brief Destroys an \ref NvMediaVPI object created by NvMediaVPICreate().
 * \param[in] vpi       A pointer to the object to be destroyed.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIDestroy(
     NvMediaVPI *vpi
);

/**
 * \brief  Flushes all queued operations.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIFlush(
     NvMediaVPI *vpi
);

/**
 * \brief  Registers an image for use with an NvMediaVPI function.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] image     A pointer to image to be registered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIImageRegister(
    NvMediaVPI *vpi,
    NvMediaImage *image
);

/**
 * \brief  Unregisters an image after use.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] image     A pointer to the image to be unregistered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIImageUnregister(
    NvMediaVPI *vpi,
    NvMediaImage *image
);

/**
 * \brief  Registers an array for use with an NvMediaVPI function.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] array     A pointer to array to be registered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayRegister(
    NvMediaVPI *vpi,
    NvMediaArray *array
);

/**
 * \brief  Unregisters an array after use.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] array     A pointer to array to be unregistered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUnregister(
    NvMediaVPI *vpi,
    NvMediaArray *array
);

/**
 * \brief  Registers scratchpad memory for use with an NvMediaVPI function.
 * \param[in] vpi           A pointer to the \ref NvMediaVPI returned by
 *                          NvMediaVPICreate().
 * \param[in] scratchpad    A pointer to the \ref NvMediaCVScratchpad handle
 *                          to be registered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIScratchpadRegister(
    NvMediaVPI *vpi,
    NvMediaCVScratchpad *scratchpad
);

/**
 * \brief  Unregisters scratchpad memory after use.
 * \param[in] vpi           A pointer to the \ref NvMediaVPI returned by
 *                          NvMediaVPICreate().
 * \param[in] scratchpad    A pointer to the \ref NvMediaCVScratchpad handle
 *                          to be unregistered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIScratchpadUnregister(
    NvMediaVPI *vpi,
    NvMediaCVScratchpad *scratchpad
);

/**
 * \brief  Creates an \ref NvMediaArray for a VPI-specific element type.
 * \param[in] device        Handle to the NvMedia device obtained by calling
 *                          NvMediaDeviceCreate().
 * \param[in] type          Type of array to be created.
 * \param[in] numElements   Number of elements in the array.
 * \param[in] attrs         A pointer to an array of allocation attributes.
 * \param[in] numAttrs      Number of allocation elelments in @a attrs.
 * \return  Handle to the array, or NULL if unsuccessful.
 */
NvMediaArray *
NvMediaVPIArrayCreate(
    NvMediaDevice *device,
    NvMediaVPIArrayType type,
    uint32_t numElements,
    const NvMediaArrayAllocAttr *attrs,
    uint32_t numAttrs
);

/**
 * \brief  Registers a pyramid for use with an NvMediaVPI function.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] pyramid   A pointer to the pyramid to be registered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIPyramidRegister(
    NvMediaVPI *vpi,
    NvMediaImagePyramid *pyramid
);

/**
 * \brief  Unregisters a pyramid after use.
 * \param[in] vpi       A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in] pyramid   A pointer to the pyramid to be unregistered.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIPyramidUnregister(
    NvMediaVPI *vpi,
    NvMediaImagePyramid *pyramid
);

/**
 * \brief NvMediaVPIProcessStereo descriptor.
 */
typedef struct NvMediaVPIProcessStereoDescriptor NvMediaVPIProcessStereoDescriptor;

/**
 * \brief Specifies the types of output for Optical Flow/Stereo Disparity
 * processing.
 */
typedef enum {
    /*! Disparity relative to reference. */
    NVMEDIA_VPI_STEREO_DISPARITY = 0,
    /*! Absolute motion vector output. */
    NVMEDIA_VPI_MV,
    /*! Motion vector hints for the NVENC hardware engine, which performs
     *  video encoding. When this type is used with \c processStereoPair(), the
     *  output holds data of type \ref NvMediaEncodeExternalMEHint. */
    NVMEDIA_VPI_MV_HINTS,
} NvMediaVPIOFSTOutputType;

/**
 * \brief  Creates \ref NvMediaVPIProcessStereoDescriptor.
 *
 * \param[in]  vpi          A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in]  width        Width of the input images.
 * \param[in]  height       Height of the input images.
 * \param[in]  outputType   \ref NvMediaVPIOFSTOutputType for type of output.
 * \return  A pointer to the \ref NvMediaVPIProcessStereoDescriptor.
 */
NvMediaVPIProcessStereoDescriptor *
NvMediaVPICreateProcessStereoPairDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaVPIOFSTOutputType outputType
);

/**
 * \brief  Queues an operation to process a stereo image pair.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 *  to the engine.
 *
 * \param[in]     vpi           A pointer to the \ref NvMediaVPI returned by
 *                              NvMediaVPICreate().
 * \param[in,out] descriptor    Pointer returned by
 *                              NvMediaVPICreateProcessStereoPairDescriptor().
 * \param[in]     left          A pointer to the left \ref NvMediaImage image.
 * \param[in]     right         A pointer to the right \ref NvMediaImage image.
 * \param[out]    output        A pointer to the output \ref NvMediaImage image.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the queuing operation is successful.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation is unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments are incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue is full.
 *    (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIProcessStereoPairDesc(
    NvMediaVPI *vpi,
    NvMediaVPIProcessStereoDescriptor *descriptor,
    NvMediaImage *left,
    NvMediaImage *right,
    NvMediaImage *output
);

/**
 * \brief NvMediaVPIConvertMV descriptor.
 */
typedef struct NvMediaVPIConvertMVDescriptor NvMediaVPIConvertMVDescriptor;

/**
 * \brief Creates an \ref NvMediaVPIConvertMVDescriptor.
 *
 * \param[in]  vpi      A pointer to the \ref NvMediaVPI object returned by
 *                      NvMediaVPICreate().
 * \param[in]  width    Width of the input depth image.
 * \param[in]  height   Height of the input depth image.
 * \param[in]  type     \ref NvMediaSurfaceType of the input depth image.
 * \param[in]  strength Smoothing strength: a value in the range (0.0,1.0).
 * \param[in]  scale    Scale factor.
 * \return  A pointer to the \ref NvMediaVPIConvertMVDescriptor.
 */
NvMediaVPIConvertMVDescriptor *
NvMediaVPICreateConvertMVDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaSurfaceType type,
    const float strength,
    const float scale
);

/**
 * \brief Converts or refines a motion vector image.
 * The processing done  on the image depends on the \a outputType parameter:
 * - If set to \c NVMEDIA_VPI_STEREO_DISPARITY, this function converts the
 *   image to a stereo disparity.
 * - If set to \c NVMEDIA_VPI_MV this function refines it.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue to
 * the engine.
 *
 * \param[in]     vpi       A pointer to the \ref NvMediaVPI returned by
 *                          NvMediaVPICreate().
 * \param[in,out] descriptor
 *                          A pointer returned by
 *                          NvMediaVPICreateConvertMVDescriptor().
 * \param[in]     inputMVImage
 *                          A pointer to an Input Motion Vectors image which
 *                          must be converted or refined.
 * \param[in]     inputColor
 *                          A pointer to an input color \ref NvMediaImage image.
 * \param[out]    output    A pointer to the \ref NvMediaImage image which has
 *                          been refined.
 * \param[in]     outputType
 *                          Type of @a output.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation is queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation is unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments are incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue is full.
 *    (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIConvertMVDesc(
    NvMediaVPI *vpi,
    NvMediaVPIConvertMVDescriptor *descriptor,
    NvMediaImage *inputMVImage,
    NvMediaImage *inputColor,
    NvMediaImage *output,
    const NvMediaVPIOFSTOutputType outputType
);


/**
 * \brief  NvMediaVPISteroPostprocess descriptor.
 */
typedef struct NvMediaVPIStereoPostprocessDescriptor NvMediaVPIStereoPostprocessDescriptor;

/**
 * \brief Creates an \ref NvMediaVPIStereoPostprocessDescriptor.
 *
 * \param[in]  vpi      A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in]  width    Width of the input disparity image.
 * \param[in]  height   Height of the input disparity image.
 * \param[in]  scale    Upsample scale factor. Must be 1.0 or 4.0.
 * \return  A pointer to the \ref NvMediaVPIStereoPostprocessDescriptor.
 */
NvMediaVPIStereoPostprocessDescriptor *
NvMediaVPICreateStereoPostprocessDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const float scale
);

/**
 * \brief  Holds stereo postprocess parameters.
 */
typedef struct {
    /*! Holds the confidence threshold.*/
    uint16_t confidenceThresh;
    /*! Holds the disparity refinement window dimensions. Must be 1, 3, 5,
     or 7.*/
    uint32_t windowDimension;
} NvMediaVPIStereoPostprocessParams;

/**
 * \brief  Performs stereo postprocessing to refine a disparity image.
 * \note NvMediaVPIFlush() must be called to actually flush the queue to
 * the engine.
 *
 * \param[in]     vpi               A pointer to the \ref NvMediaVPI returned by
 *                                  NvMediaVPICreate().
 * \param[in,out] descriptor        A pointer returned by
 *                                  NvMediaVPICreateStereoPostprocessDescriptor().
 * \param[in]     params            A pointer to an
 *                                  \ref NvMediaVPIStereoPostprocessParams.
 * \param[in]     disparityInput    A pointer to an input disparity image
 *                                  that needs refinement.
 * \param[in]     confidenceInput   A pointer to an input confidence map.
 * \param[out]    disparityOutput   A pointer to the refined and upscaled
 *                                  (for scale&gt;1.0) disparity image.
 * \param[out]    confidenceOutput  A pointer to the refined and upscaled
 *                                  (for scale&gt;1.0) confidence map.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successfully queued.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *       (Call NvMediaVPIFlush() to flush the queue to the engine.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIStereoPostprocessDesc(
    NvMediaVPI *vpi,
    NvMediaVPIStereoPostprocessDescriptor *descriptor,
    NvMediaVPIStereoPostprocessParams *params,
    NvMediaImage *disparityInput,
    NvMediaImage *confidenceInput,
    NvMediaImage *disparityOutput,
    NvMediaImage *confidenceOutput
);

/**
 * \brief  NvMediaVPISteroPreprocess descriptor.
 */
typedef struct NvMediaVPIStereoPreprocessDescriptor NvMediaVPIStereoPreprocessDescriptor;

/**
 * \brief  Creates an \ref NvMediaVPIStereoPreprocessDescriptor.
 *
 * \param[in]  vpi          A pointer to the \ref NvMediaVPI returned by
 *                          NvMediaVPICreate().
 * \param[in]  width        Width of the input disparity image.
 * \param[in]  height       Height of the input disparity image.
 * \param[in]  outputType   An \ref NvMediaVPIOFSTOutputType specifying the
 *                          type of output.
 * \return  A pointer to the \ref NvMediaVPIStereoPreprocessDescriptor.
 */
NvMediaVPIStereoPreprocessDescriptor *
NvMediaVPICreateStereoPreprocessDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaVPIOFSTOutputType outputType
);

/**
 * \brief  Holds stereo preprocessing parameters.
 * \note  NvMediaVPISetVersionId() must be called after initiation to set
 *  the value of versionId.
 */
typedef struct {
    /*! Holds the number of hints per macro-block. Must be in the range [1,8].*/
    uint8_t numberOfHintsPerMB;
    /*! Holds the number of fractional bits. Must be in the range [0,13]. */
    uint8_t fractionalBits;
    /*! Holds the confidence threshold.*/
    uint8_t confidenceThresh;
    /*! Holds the shift of disparity difference before confidence table
        indexing.*/
    uint8_t disparityDiffToConfidenceShift;
} NvMediaVPIStereoPreprocessParams;

/**
 * \brief  Performs stereo preprocessing to produce a disparity image or
 *  motion vector hints.
 * \note  NvMediaVPIFlush() must be called to actually flush the queue to
 *  the engine.
 *
 * \param[in]     vpi           A pointer to the \ref NvMediaVPI returned by
 *                              NvMediaVPICreate().
 * \param[in,out] descriptor    A pointer returned by
 *                              NvMediaVPICreateStereoPreprocessDescriptor().
 * \param[in]     params        A pointer to an
                                \ref NvMediaVPIStereoPreprocessParams.
 * \param[in]     confidenceTable
 *                              A pointer to an \ref NvMediaArray containing
 *                              mapped confidence. The array must be of
 *                              unsigned @c int16 type with a capacity at least
 *                              @c NVPVA_STEREO_CONF_GEN_MAX_CONF_TABLE_LEN.
 * \param[in]     leftImage     A pointer to the input left image.
 * \param[in]     rightImage    A pointer to the input right image.
 * \param[out]    output0       A pointer to the first output image. It contains
 *                              hints if \ref NvMediaVPIOFSTOutputType is
 *                              \ref NVMEDIA_VPI_MV_HINTS. It contains the left
 *                              disparity if \ref NvMediaVPIOFSTOutputType
 *                              is \ref NVMEDIA_VPI_STEREO_DISPARITY.
 * \param[out]    output1       A pointer to the second output image. It must
 *                              be NULL if
 *                              \ref NvMediaVPIOFSTOutputType is
 *                              \ref NVMEDIA_VPI_MV_HINTS. It contains
 *                              the right disparity if
 *                              \ref NvMediaVPIOFSTOutputType is
 *                              \ref NVMEDIA_VPI_STEREO_DISPARITY.
 *
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *        (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIStereoPreprocessDesc(
    NvMediaVPI *vpi,
    NvMediaVPIStereoPreprocessDescriptor *descriptor,
    NvMediaVPIStereoPreprocessParams *params,
    NvMediaArray *confidenceTable,
    NvMediaImage *leftImage,
    NvMediaImage *rightImage,
    NvMediaImage *output0,
    NvMediaImage *output1
);


/**
 * \brief  Specifies types of post-process non-maximum suppression.
 */
typedef enum {
    /* Use a 2D grid of 8x8 cells with no minimal distance. */
    NVMEDIA_VPI_2D_GRID_8x8_CELL_NO_MIN_DISTANCE = 0
} NvMediaVPINonMaxSuppressionType;

/**
 * \brief  Specifies types of filters used in the Harris corner detector.
 */
typedef enum {
    /*! Built-in normalized separable Sobel filter. */
    NVMEDIA_VPI_HARRIS_FILTER_TYPE_DEFAULT = 0,
    /*! User-supplied separable gradient filter. The filter is automatically
     normalized. */
    NVMEDIA_VPI_HARRIS_FILTER_TYPE_USER
} NvMediaVPIHarrisGradientFilterType;

/*
 * \brief NvMediaVPIGetKeyPointsHarrisDescriptor.
 */
typedef struct NvMediaVPIGetKeyPointsHarrisDescriptor NvMediaVPIGetKeyPointsHarrisDescriptor;

/**
 * \brief Creates a pointer to a \ref NvMediaVPIGetKeyPointsHarrisDescriptor.
 *
 * \param[in]  vpi      A pointer to the \ref NvMediaVPI returned by
 *                      NvMediaVPICreate().
 * \param[in]  width    Input image width.
 * \param[in]  height   Input image height.
 * \param[in]  nonMaxSuppressionType
 *                      Post-process non-maximum suppression type.
 * \return  A pointer to the \ref NvMediaVPIGetKeyPointsHarrisDescriptor.
 */
NvMediaVPIGetKeyPointsHarrisDescriptor *
NvMediaVPICreateGetKeyPointsHarrisDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaVPINonMaxSuppressionType nonMaxSuppressionType);

/**
 * \brief Holds Harris keypoint parameters.
 */
typedef struct {
    /*! Holds gradient window size. Must be 3, 5 or 7. */
    const uint32_t gradientSize;
    /*! Holds filter type. */
    const NvMediaVPIHarrisGradientFilterType gradientFilterType;
    /*! Holds horizontal filter of @a gradientSize coefficients. */
    const int16_t *horizontalFilterCoefficients;
    /*! Holds vertical filter of @a gradientSize coefficients. */
    const uint16_t *verticalFilterCoefficients;
    /*! Holds block window size used to compute the Harris Corner score.
        Must be 3, 5 or 7. */
    const uint32_t blockSize;
    /*! Holds the minimum threshold with which to eliminate Harris Corner
     scores. */
    const float strengthThresh;
    /*! Holds the sensitivity threshold from the Harris-Stephens equation. */
    const float sensitivity;
    /*! Holds the post-process non-maximum suppression type. */
    const NvMediaVPINonMaxSuppressionType nonMaxSuppressionType;
    /*! Holds the radial Euclidean distance for non-maximum suppression. */
    const float minDistance;
} NvMediaVPIGetKeyPointsHarrisParams;

/**
 * \brief  Queues an operation to get Harris keypoints throughout an image.
 *
 * If the tracked keypoints array is not empty, then those keypoints are
 * inserted at the beginning of the output \a keypoints array. An optional
 * \a mask can be supplied to suppress detected and tracked keypoints.
 * Suppressed tracked keypoints are removed from the output array.
 * Non-maximum suppression is applied only to newly detected keypoints.
 *
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue to
 *  the engine.
 *
 * \param[in]     vpi       A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in,out] descriptor
 *                          A pointer returned by
 *                          NvMediaVPICreateGetKeyPointsHarrisDescriptor().
 * \param[in]     params    A pointer to
 *                          \ref NvMediaVPIGetKeyPointsHarrisParams.
 * \param[in]     input     A pointer to an \ref NvMediaImage image.
 * \param[in]     mask      \ref NvMediaImage mask image. Optional. Value may
 *                          be 0 (suppressed) or 0xFF (not suppressed).
 * \param[in]     trackedKeypoints
 *                          A pointer to an \ref NvMediaArray containing
 *                          keypoints to track. Optional. If NULL,
 *                          @a trackedScores must be NULL.
 *                          The array must be of type
 *                          \ref NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT,
 *                          created by a call to \ref NvMediaVPIArrayCreate.
 * \param[in]     trackedScores
 *                          A pointer to an \ref NvMediaArray containing
 *                          scores of keypoints to track. Optional. If NULL,
 *                          @a trackedKeypoints must be NULL.
 * \param[out]    keypoints A pointer to an \ref NvMediaArray containing
 *                          keypoints. \a array must be of
 *                          \ref NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT type
 *                          created by a call to NvMediaVPIArrayCreate().
 * \param[out]    scores    A pointer to an \ref NvMediaArray containing scores.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or morearguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *        (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIGetKeyPointsHarrisDesc(
    NvMediaVPI *vpi,
    NvMediaVPIGetKeyPointsHarrisDescriptor *descriptor,
    const NvMediaVPIGetKeyPointsHarrisParams *params,
    NvMediaImage *input,
    NvMediaImage *mask,
    NvMediaArray *trackedKeypoints,
    NvMediaArray *trackedScores,
    NvMediaArray *keypoints,
    NvMediaArray *scores
);

/*
 * \brief NvMediaVPIGetKeyPointsFastDescriptor.
 */
typedef struct NvMediaVPIGetKeyPointsFastDescriptor NvMediaVPIGetKeyPointsFastDescriptor;

/**
 * \brief  Creates a pointer to an \ref NvMediaVPIGetKeyPointsFastDescriptor.
 *
 * \param[in]  vpi      A pointer to the \ref NvMediaVPI object returned by
 *                      NvMediaVPICreate().
 * \param[in]  width    Width of the input image.
 * \param[in]  height   Height of the input image.
 * \param[in]  type     \ref NvMediaSurfaceType of the input image.
 * \return  A pointer to the \ref NvMediaVPIGetKeyPointsFastDescriptor.
 */
NvMediaVPIGetKeyPointsFastDescriptor *
NvMediaVPICreateGetKeyPointsFastDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaSurfaceType type
);

/**
 * \brief  Queues an operation to get FAST keypoints throughout an image.
 *        If the keypoints array is not empty, then the operation tracks the
 *        keypoints as well.
 * \note  NvMediaVPIFlush() must be called to actually flush the queue to
 *  the engine.
 *
 * \param[in]     vpi       A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in,out] descriptor
 *                          A pointer returned by
 *                          NvMediaVPICreateGetKeyPointsFastDescriptor().
 * \param[in]     input     \ref NvMediaImage image.
 * \param[in]     strengthThresh
 *                          Threshold of difference between intensity of
 *                          the central pixel and pixels on Bresenham's circle
 *                          of radius 3.
 * \param[in]     nonmaxSupression
 *                          Indicates whether to apply non-maximum suppression.
 * \param[in,out] keypoints A pointer to an \ref NvMediaArray containing
 *                          keypoints.
 * \param[out]    scores    A pointer to an \ref NvMediaArray containing scores.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIGetKeyPointsFastDesc(
    NvMediaVPI *vpi,
    NvMediaVPIGetKeyPointsFastDescriptor *descriptor,
    NvMediaImage *input,
    const uint32_t strengthThresh,
    const NvMediaBool nonmaxSupression,
    NvMediaArray *keypoints,
    NvMediaArray *scores
);

/** \brief  Specifies the conditions that cause the Lucas-Kanade Feature Tracker
 *  to be terminated.
 */
typedef enum {
    /** Specifies termination by the number of iterations. */
    NVMEDIA_VPI_TERMINATION_CRITERION_ITERATIONS = 0,
    /** Specifies termination by matching the value against epsilon. */
    NVMEDIA_VPI_TERMINATION_CRITERION_EPSILON,
    /** Specifies termination by iterations or epsilon, whichever happens
     first. */
    NVMEDIA_VPI_TERMINATION_CRITERION_BOTH
} NvMediaVPITerminationCriterion;

/**
 * \brief  NvMediaVPIGetSparseFlowPyrLKParams.
 */
typedef struct {
    /*! Holds the termination criteria. */
    const NvMediaVPITerminationCriterion termination;
    /*! Holds the error for terminating the algorithm. */
    float epsilon;
    /*! Holds the number of points. */
    uint32_t numPoints;
    /*! Holds the number of iterations. */
    uint32_t numIterations;
    /*! Holds the size of the window on which to perform the algorithm.
     *  Must be in the range [3,32]. */
    uint32_t windowDimension;
    /*! Holds a Boolean flag that indicates whether to calculate tracking
     error. */
    int32_t calcError;
    /*! Holds the number of levels in the pyramid. */
    uint32_t numLevels;
} NvMediaVPIGetSparseFlowPyrLKParams;

/**
 * \brief  NvMediaVPISparseFlowPyr descriptor.
 */
typedef struct NvMediaVPIGetSparseFlowPyrLKDescriptor NvMediaVPIGetSparseFlowPyrLKDescriptor;

/**
 * \brief  Creates a pointer to an \ref NvMediaVPIGetSparseFlowPyrLKDescriptor.
 *
 * \param[in]  vpi      A pointer to an \ref NvMediaVPI object returned by
 *                      NvMediaVPICreate().
 * \param[in]  params   A pointer to an \ref NvMediaVPIGetSparseFlowPyrLKParams.
 * \return  A pointer to an \ref NvMediaVPIGetSparseFlowPyrLKDescriptor.
 */
NvMediaVPIGetSparseFlowPyrLKDescriptor *
NvMediaVPICreateGetSparseFlowPyrLKDescriptor(
    NvMediaVPI *vpi,
    const NvMediaVPIGetSparseFlowPyrLKParams *params
);

/**
 * \brief  Queues an operation to track features in a pyramid.
 * \note  \ref NvMediaVPIFlush() must be called to actually flush the queue to
 *  the engine.
 *
 * \param[in]     vpi       A pointer to an \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in,out] descriptor
 *                          A pointer returned by
 *                          NvMediaVPICreateGetSparseFlowPyrLKDescriptor().
 * \param[in]     params    A pointer to an
 *                          \ref NvMediaVPIGetSparseFlowPyrLKParams.
 * \param[in]     oldImages A pointer to the input \ref NvMediaImagePyramid of
 *                          first (old) images.
 * \param[in]     newImages A pointer to the input \ref NvMediaImagePyramid of
 *                          destination (new) images.
 * \param[in]     oldPoints A pointer to an array of keypoints in the
 *                          \a oldImages high resolution pyramid.
 * \param[in,out] newPoints A pointer to an array of keypoints in the
 *                          \a newImages high resolution pyramid. It is used
 *                          for starting a search in \a newImages.
 * \param[out]    newStatus A pointer to an array for tracking status for each
 *                          input in \a oldPoints.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus NvMediaVPIGetSparseFlowPyrLKDesc(
    NvMediaVPI *vpi,
    NvMediaVPIGetSparseFlowPyrLKDescriptor *descriptor,
    const NvMediaVPIGetSparseFlowPyrLKParams *params,
    NvMediaImagePyramid *oldImages,
    NvMediaImagePyramid *newImages,
    NvMediaArray *oldPoints,
    NvMediaArray *newPoints,
    NvMediaArray *newStatus
);

/**
 * \brief NvMediaVPIKLTDescriptor descriptor.
 */
typedef struct NvMediaVPIKLTDescriptor NvMediaVPIKLTDescriptor;

/**
 * \brief Creates a pointer to the \ref NvMediaVPIKLTDescriptor.
 *
 * \param[in]  vpi      A pointer to a \ref NvMediaVPI object returned by
 *                      NvMediaVPICreate().
 * \param[in]  width    Width of the input image.
 * \param[in]  height   Height of the input image.
 * \param[in]  type     \ref NvMediaSurfaceType of the input image.
 * \return  A pointer to the \ref NvMediaVPIKLTDescriptor.
 */
NvMediaVPIKLTDescriptor *
NvMediaVPICreateKLTDescriptor(
    NvMediaVPI *vpi,
    const uint32_t width,
    const uint32_t height,
    const NvMediaSurfaceType type
);

/** Specifies the types of KLT Tracking. */
typedef enum NvMediaVPIKltTrackType
{
    /** Specifies Inverse Compositional tracking type. */
    NVMEDIA_VPI_KLT_INVERSE_COMPOSITIONAL = 0,
} NvMediaVPIKltTrackType;

/**
 * \brief Holds the KLT parameters.
 */
typedef struct {
    /*! Num Iterations Scaling. */
    uint32_t numIterationsScaling;
    /*! Num Iterations Translation. */
    uint32_t numIterationsTranslation;
    /*! Num Iterations Coarse. */
    uint32_t numIterationsCoarse;
    /*! Num Iterations Fine. */
    uint32_t numIterationsFine;
    /*! Maximum Pixel Tolerance. */
    float maxPixelTolerance;
    /*! Threshold Update. */
    float thresholdUpdate;
    /*! Threshold Kill. */
    float thresholdKill;
    /*! Threshold Stop. */
    float thresholdStop;
    /*! Maximum Scale Change. */
    float maxScaleChange;
    /*! Tracking Type. */
    NvMediaVPIKltTrackType trackingType;
} NvMediaVPIKLTParams;

/**
 * \brief  Queues an operation to run the Kanade Lucas Tomasi (KLT) tracking
 *  algorithm.
 * \note  \ref NvMediaVPIFlush() must be called to actually flush the queue
 *  to the engine.
 *
 * \param[in]     vpi           A pointer to an \ref NvMediaVPI object returned
 *                              by NvMediaVPICreate().
 * \param[in,out] descriptor    A pointer returned by
 *                              NvMediaVPICreateKLTDescriptor().
 * \param[in]     params        A pointer to an \ref NvMediaVPIKLTParams object.
 * \param[in]     referenceImage
 *                              A pointer to an \ref NvMediaImage reference
 *                              image.
 * \param[in]     templateImage A pointer to an \ref NvMediaImage template
 *                              image.
 * \param[in]     inputBoxList  A pointer to an \ref NvMediaArray input
 *                              bounding box list. The array must be of type
 *                              \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM,
 *                              created by a call to NvMediaVPIArrayCreate().
 * \param[in]     predictedBoxList
 *                              A pointer to an \ref NvMediaArray predicted
 *                              bounding box list. The array must be of type
 *                              \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM,
 *                              created by a call to NvMediaVPIArrayCreate().
 * \param[out]    outputBoxList A pointer to an \ref NvMediaArray output
 *                              bounding box list. The array must be of type
 *                              \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM,
 *                              created by a call to NvMediaVPIArrayCreate().
 * \param[out]    estimationList
 *                              A pointer to an \ref NvMediaArray output
 *                              estimated motion. The array must be of type
 *                              \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM,
 *                              created by a call to NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIKLTDesc(
    NvMediaVPI *vpi,
    NvMediaVPIKLTDescriptor *descriptor,
    const NvMediaVPIKLTParams *params,
    NvMediaImage *referenceImage,
    NvMediaImage *templateImage,
    NvMediaArray *inputBoxList,
    NvMediaArray *predictedBoxList,
    NvMediaArray *outputBoxList,
    NvMediaArray *estimationList
);

/**
 * \brief Returns the size of scratchpad memory required for operations that
 *  support an NvMediaCVScratchpad based scratchpad.
 *
 * \param[in]     descriptor            A pointer returned by
 *                                      NvMediaVPICreateXYZDescriptor().
 * \param[out]    scratchpadSizeBytes   A pointer to the amount of scratchpad
 *                                      memory required for the operation,
 *                                      in bytes.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was succcessful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIGetScratchpadSize(
    void *descriptor,
    uint32_t *scratchpadSizeBytes
);

/**
 * \brief  Queues an operation to run the Kanade Lucas Tomasi (KLT) tracking
 *  algorithm.
 *
 * This version uses CVScratchpad for optimized operation.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 * to the engine.
 *
 * \param[in]     vpi          A pointer to the \ref NvMediaVPI object returned
 *                             by NvMediaVPICreate().
 * \param[in,out] descriptor   A pointer returned by
 *                             NvMediaVPICreateKLTDescriptor().
 * \param[in]     scratchpad   A pointer to an NvMediaCVScratchpad created by
 *                             \ref NvMediaCVScratchpadCreate().
 * \param[in]     params       A pointer to an \ref NvMediaVPIKLTParams object.
 * \param[in]     referenceImage
 *                             A pointer to an \ref NvMediaImage reference
 *                             image.
 * \param[in]     templateImage
 (                             A pointer to an \ref NvMediaImage template image.
 * \param[in]     inputBoxList A pointer to an \ref NvMediaArray input
 *                             bounding box list. The array must be of type
 *                             \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM,
 *                             created by a call to NvMediaVPIArrayCreate().
 * \param[in]     predictedBoxList
 *                             A pointer to an \ref NvMediaArray predicted
 *                             bounding box list. The array must be of type
 *                             \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM type,
 *                             created by a call to NvMediaVPIArrayCreate().
 * \param[out]    outputBoxList
 *                             A pointer to an \ref NvMediaArray output
 *                             bounding box list. The array must be of type
 *                             \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM,
 *                             created by a call to NvMediaVPIArrayCreate().
 * \param[out]    estimationList
 *                             A pointer to an \ref NvMediaArray output
 *                             estimated motion. The array must be of type
 *                             \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM type,
 *                             created by a call to NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIKLTFastDesc(
    NvMediaVPI *vpi,
    NvMediaVPIKLTDescriptor *descriptor,
    NvMediaCVScratchpad *scratchpad,
    const NvMediaVPIKLTParams *params,
    NvMediaImage *referenceImage,
    NvMediaImage *templateImage,
    NvMediaArray *inputBoxList,
    NvMediaArray *predictedBoxList,
    NvMediaArray *outputBoxList,
    NvMediaArray *estimationList
);

/**
 * \brief  Queues an operation to generate a Gaussian pyramid from an input
 *  image.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 * to the engine.
 *
 * \param[in]  vpi      A pointer to the \ref NvMediaVPI object returned by
 *                      NvMediaVPICreate().
 * \param[in]  input    A pointer to an \ref NvMediaImage image. The image may
 *                      be the same NvMediaImage as is returned by
 *                      @c NvMediaImagePyramidGetImageForLevel(output, 0),
 *                      thereby saving a copy operation of the input to the
 *                      output.
 * \param[out] output   A pointer to an \ref NvMediaImagePyramid.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIGetImagePyramid(
    NvMediaVPI *vpi,
    NvMediaImage *input,
    NvMediaImagePyramid *output
);

/**
 * \brief  Queues an operation to convolve an input image with a client-supplied
 * convolution matrix.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 * to the engine.
 *
 * \param[in]  vpi          A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in]  input        A pointer to an \ref NvMediaImage image.
 * \param[in]  kernelData   A pointer to the convolution kernel coefficients.
 * \param[in]  kernelWidth  Convolution kernel width.
 * \param[in]  kernelHeight Convolution kernel height.
 * \param[out] output       A pointer to an \ref NvMediaImage image.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *  (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIConvolveImage(
    NvMediaVPI *vpi,
    NvMediaImage *input,
    const float *kernelData,
    const uint32_t kernelWidth,
    const uint32_t kernelHeight,
    NvMediaImage *output
);

/**
 * \brief NvMediaVPIConvolveImageSeparableDescriptor.
 */
typedef struct NvMediaVPIConvolveImageSeparableDescriptor \
               NvMediaVPIConvolveImageSeparableDescriptor;

/**
 * \brief  Creates a pointer to the
 *  \ref NvMediaVPIConvolveImageSeparableDescriptor.
 *
 * \param[in]  vpi          A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in]  type         \ref NvMediaSurfaceType of the input image.
 * \param[in]  kernelX      A pointer to the x convolution kernel coefficients.
 * \param[in]  kernelXSize  Size of the x convolution kernel.
 * \param[in]  kernelY      A pointer to the y convolution kernel coefficients.
 * \param[in]  kernelYSize  Size of the y convolution kernel.
 * \return  A pointer to the \ref NvMediaVPIConvolveImageSeparableDescriptor.
 */
NvMediaVPIConvolveImageSeparableDescriptor *
NvMediaVPICreateConvolveImageSeparableDescriptor(
    NvMediaVPI *vpi,
    NvMediaSurfaceType type,
    const float *kernelX,
    const uint32_t kernelXSize,
    const float *kernelY,
    const uint32_t kernelYSize
);

/**
 * \brief  Queues an operation to convolve an image with a 2D kernel,
 *  using separable convolution.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 *  to the engine.
 *
 * \param[in]  vpi          A pointer to the \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in]  input        A pointer to an \ref NvMediaImage image.
 * \param[in]  kernelX      A pointer to the x convolution kernel coefficients.
 * \param[in]  kernelXSize  Size of the x convolution kernel.
 * \param[in]  kernelY      A pointer to the y convolution kernel coefficients.
 * \param[in]  kernelYSize  Size of the y convolution kernel.
 * \param[in]  output       A pointer to an \ref NvMediaImage image.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIConvolveImageSeparable(
    NvMediaVPI *vpi,
    NvMediaImage *input,
    const float *kernelX,
    const uint32_t kernelXSize,
    const float *kernelY,
    const uint32_t kernelYSize,
    NvMediaImage *output
);

/**
 * \brief  Queues an operation to compute a generic box filter window of the
 *  input image.
 * \note \ref NvMediaVPIFlush() must be called to actually flush the queue
 *  to the engine.
 *
 * \param[in]     vpi           A pointer to the \ref NvMediaVPI object
 *                              returned by NvMediaVPICreate().
 * \param[in]     input         A pointer to an \ref NvMediaImage image.
 * \param[in]     windowWidth   Window width.
 * \param[in]     windowHeight  Window height.
 * \param[in]     output        A pointer to an \ref NvMediaImage image.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the operation was unsupported.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING if the queue was full.
 *   (Call NvMediaVPIFlush() to flush the queue.)
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIFilterImageBox(
    NvMediaVPI *vpi,
    NvMediaImage *input,
    const uint32_t windowWidth,
    const uint32_t windowHeight,
    NvMediaImage *output
);

/**
 * \brief  Helper function; converts an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT type to an array of type
 *  \ref NvMediaVPIPoint2Df.
 *
 * \param[in]  array        A pointer to the input \ref NvMediaArray. The array
 *                          must be created with NvMediaVPIArrayCreate().
 * \param[in]  startIndex   Index offset (number of elements) into the array.
 *                          Currently 0 (zero) is the only value supported.
 * \param[in]  numElements  Number of elements to write to the destination.
 * \param[out] destPtr      A pointer to the location where the output array is
 *                          to be written.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayGetPoint2Df(
    NvMediaArray *array,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaVPIPoint2Df *destPtr
);

/**
 * \brief  Helper function; converts an array of type \ref NvMediaVPIPoint2Df
 *  to an \ref NvMediaArray of type \ref NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT.
 *
 * \param[in]  inputPtr     A pointer to the input array.
 * \param[in]  startIndex   Index offset (number of elements) into the
 *                          destination array.
 * \param[in]  numElements  Number of elements to write to the destination.
 * \param[out] destArray    A pointer to the output \ref NvMediaArray.
 *                          \a destArray must be created by a call to
 *                          NvMediaVPIArrayCreate() with @a type set to
 *                          \ref NVMEDIA_VPI_ARRAY_TYPE_KEYPOINT.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUpdatePoint2Df(
    NvMediaVPIPoint2Df *inputPtr,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaArray *destArray
);

/**
 * \brief  Helper function; converts an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM type to an array of type
 *  \ref NvMediaVPIAABB.
 *
 * \param[in]  array        A pointer to an input \ref NvMediaArray. The array
 *                          must be created with NvMediaVPIArrayCreate().
 * \param[in]  startIndex   Index offset (number of elements) into array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destPtr      A pointer to the location at which to write
 *                          the output array.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayGetAABB(
    NvMediaArray *array,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaVPIAABB *destPtr
);

/**
 * \brief  Helper function; converts an array of type \ref NvMediaVPIAABB to an
 *  \ref NvMediaArray of type \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM.
 *
 * \param[in]  inputPtr     A pointer to the input array.
 * \param[in]  startIndex   Index offset (number of elements) into the
 *                          destination array.
 * \param[in]  numElements  Number of elements to write to the destination.
 * \param[out] destArray    A pointer to the output \ref NvMediaArray.
 *                          \a destArray must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUpdateAABB(
    NvMediaVPIAABB *inputPtr,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaArray *destArray
);

/**
 * \brief  Helper function; converts an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM type to an array of type
 *  \ref NvMediaVPIBoundingBoxWithTransform.
 *
 * \param[in]  array        A pointer to the input \ref NvMediaArray. The array
 *                          must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \param[in]  startIndex   Index offset (number of elements) into array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destPtr      A pointer to a location in which to write the
 *                          output array.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayGetBoundingBoxWithTransform(
    NvMediaArray *array,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaVPIBoundingBoxWithTransform *destPtr
);

/**
 * \brief  Helper function; converts an array of type
 *  \ref NvMediaVPIBoundingBoxWithTransform to an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_BBOX_XFORM.
 *
 * \param[in]  inputPtr     A pointer to the input array.
 * \param[in]  startIndex   Index offset (number of elements) into destination
 *                          array.
 * \param[in]  numElements  Number of elements to write to the destination.
 * \param[out] destArray    A pointer to an output \ref NvMediaArray.
 *                          \a destArray must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUpdateBoundingBoxWithTransform(
    NvMediaVPIBoundingBoxWithTransform *inputPtr,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaArray *destArray
);

/**
 * \brief  Helper function; converts an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM to an array of type
 *  \ref NvMediaVPITranslationWithScale.
 *
 * \param[in]  array        A pointer to the input \ref NvMediaArray. The array
 *                          must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \param[in]  startIndex   Index offset (number of elements) into array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destPtr      A pointer to a location at which to write the
 *                          output array.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */

NvMediaStatus
NvMediaVPIArrayGetTranslationWithScale(
    NvMediaArray *array,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaVPITranslationWithScale *destPtr
);

/**
 * \brief  Helper function; converts an array of type
 *  \ref NvMediaVPITranslationWithScale to an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM.
 *
 * \param[in]  inputPtr     A pointer to the input array.
 * \param[in]  startIndex   Index offset (number of elements) into
 *                          destination array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destArray    A pointer to the output \ref NvMediaArray.
 *                          \a destArray must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUpdateTranslationWithScale(
    NvMediaVPITranslationWithScale *inputPtr,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaArray *destArray
);

/**
 * \brief  Helper function; converts an \ref NvMediaArray of type
 *  \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM type to an array of type
 *  \ref NvMediaVPI2DTransform.
 *
 * \param[in]  array        A pointer to the input \ref NvMediaArray. The array
 *                          must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \param[in]  startIndex   Index offset (number of elements) into array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destPtr      A pointer to a location in which to write the
 *                          output array.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayGet2DTransform(
    NvMediaArray *array,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaVPI2DTransform *destPtr
);

/**
 * \brief  Helper function; converts an array of \ref NvMediaVPI2DTransform to
 * \ref NvMediaArray of \ref NVMEDIA_VPI_ARRAY_TYPE_TRANSFORM type.
 *
 * \param[in]  inputPtr     A pointer to the input array.
 * \param[in]  startIndex   Index offset (number of elements) into array.
 * \param[in]  numElements  Number of elements to write to destination.
 * \param[out] destArray    A pointer to output \ref NvMediaArray.
 *                          \a destArray must be created by a call to
 *                          NvMediaVPIArrayCreate().
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIArrayUpdate2DTransform(
    NvMediaVPI2DTransform *inputPtr,
    const uint32_t startIndex,
    const uint32_t numElements,
    NvMediaArray *destArray
);

/**
 * \brief  Destroys an NvMediaVPI function descriptor.
 *
 * \param[in] vpi           A pointer to an \ref NvMediaVPI object returned by
 *                          NvMediaVPICreate().
 * \param[in] descriptor    A pointer to an NvMediaVPI function descriptor.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was queued successfully.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more arguments were incorrect.
 * - \ref NVMEDIA_STATUS_NOT_INITIALIZED if the function descriptor was
 *   uninitialized.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaVPIDestroyDescriptor(
    NvMediaVPI *vpi,
    void *descriptor
);

/*
 * \defgroup history_NvMediaVPI History
 * Provides change history for the NVIDIA VPI API.
 *
 * \section history_NvMediaVPI Version History
 *
 * <b> Version 1.0 </b> March 2, 2018
 * - Initial API definitions.
 *
 * <b> Version 2.0 </b> June 5, 2018
 * - Update Harris tracking API.
 *
 * <b> Version 2.1 </b> July 12, 2018
 * - Add KLT API, and array accessor API's.
 *
 * <b> Version 2.2 </b> July 12, 2018
 * - Add API to query number of available engines.
 *
 * <b> Version 2.3 </b> Sept 27, 2018
 * - Add KLT Fast API
 *
 */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _NVMEDIA_VPI_H */
