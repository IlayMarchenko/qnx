/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: VMP Processing Control </b>
 *
 * @b Description: This file contains the Image Video Media Processing (VMP) API.
 */

#ifndef _NVMEDIA_VMP_H
#define _NVMEDIA_VMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_common.h"
#include "nvmedia_video.h"
#include "nvmedia_vop.h"

/**
 * \defgroup mixer_api Video Mixer
 * \ingroup nvmedia_video_top
 *
 * Video mixer provides a surface to surface based rendering with
 * deinterlacing, inverse telecine, scaling, alpha blending,
 * noise reduction, filtering, and background color support.
 *
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VMP_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_VMP_VERSION_MINOR   2

/**
 * \defgroup mixer_features Mixer Features
 * Declares and manages objects for specifying mixer features.
 * @{
 */

/**
 * \hideinitializer
 * \brief Specifies that background is used in the video mixer.
 */
#define NVMEDIA_VMP_FEATURE_BACKGROUND_PRESENT              (1<<0)

/**
 * \hideinitializer
 * \brief Video is interlaced.
 */
#define NVMEDIA_VMP_FEATURE_INTERLACED                      (1<<1)

/**
 * \hideinitializer
 * \brief Specifies that video is interlaced and it needs deiterlacing.
 */
#define NVMEDIA_VMP_FEATURE_DEINTERLACING                   (1<<2)

/**
 * \hideinitializer
 * \brief Enables support for advanced1 de-interlacing
 */
#define NVMEDIA_VMP_FEATURE_ADVANCED1_DEINTERLACING         (1<<3)

/**
 * \hideinitializer
 * \brief Enable support for advanced2 de-interlacing
 */
#define NVMEDIA_VMP_FEATURE_ADVANCED2_DEINTERLACING         (1<<4)

/**
 * \hideinitializer
 * \brief Input uses limited (16-235) RGB range.
 */
#define NVMEDIA_VMP_FEATURE_LIMITED_RGB_INPUT               (1<<5)

/**
 * \hideinitializer
 * \brief Enable support for inverse telecine processing. This features
 * works only if advanced1 or advanced2 de-interlacing is enabled.
 */
#define NVMEDIA_VMP_FEATURE_INVERSE_TELECINE                (1<<6)

/**
 * \hideinitializer
 * \brief Enable support for noise reduction video processing.
 */
#define NVMEDIA_VMP_FEATURE_NOISE_REDUCTION                 (1<<7)

/**
 * \hideinitializer
 * \brief Enable support for sharpening video processing.
 */
#define NVMEDIA_VMP_FEATURE_SHARPENING                      (1<<8)

/**
 * \hideinitializer
 * \brief Enables the Alpha surface blending mode. In this mode there can be one extra alpha layer.
 * This alpha surface scales to the output size and replaces the alpha channel.
 */
#define NVMEDIA_VMP_FEATURE_ALPHA_SURFACE_MODE              (1<<9)

/**
 * \hideinitializer
 * \brief Enable support for processing into VPR surfaces
 */
#define NVMEDIA_VMP_FEATURE_PROTECTED                       (1<<10)

/**
 * \hideinitializer
 * \brief Enable dynamic frequency setting for mixer hardware block
 */
#define NVMEDIA_VMP_FEATURE_ENABLE_DFS                      (1<<11)

/** @} <!-- Ends mixer_features sub-group --> */

/**
 * \defgroup mixer_attributes Mixer Attributes
 * Defines mixer attribute bit masks for constructing attribute masks.
 * @{
 */

/**
 * \hideinitializer
 * \brief Brightness
 */
#define NVMEDIA_VMP_ATTR_BRIGHTNESS                    (1<<0)
/**
 * \hideinitializer
 * \brief Contrast
 */
#define NVMEDIA_VMP_ATTR_CONTRAST                      (1<<1)
/**
 * \hideinitializer
 * \brief Sturation
 */
#define NVMEDIA_VMP_ATTR_SATURATION                    (1<<2)
/**
 * \hideinitializer
 * \brief Hue
 */
#define NVMEDIA_VMP_ATTR_HUE                           (1<<3)
/**
 * \hideinitializer
 * \brief Color Standard for video input
 */
#define NVMEDIA_VMP_ATTR_COLOR_STANDARD                (1<<4)
/**
 * \hideinitializer
 * \brief Deintelacing type
 */
#define NVMEDIA_VMP_ATTR_DEINTERLACE_TYPE              (1<<6)
/**
 * \hideinitializer
 * \brief Noise reduction level
 */
#define NVMEDIA_VMP_ATTR_NOISE_REDUCTION               (1<<7)
/**
 * \hideinitializer
 * \brief Noise reduction algorithm
 */
#define NVMEDIA_VMP_ATTR_NOISE_REDUCTION_ALGORITHM     (1<<8)
/**
 * \hideinitializer
 * \brief Sharpening level
 */
#define NVMEDIA_VMP_ATTR_SHARPENING                    (1<<9)
/**
 * \hideinitializer
 * \brief Inverse telecine control
 */
#define NVMEDIA_VMP_ATTR_INVERSE_TELECINE              (1<<10)
/**
 * \hideinitializer
 * \brief Filter quality mode
 */
#define NVMEDIA_VMP_ATTR_FILTER_QUALITY                (1<<11)
/**
 * \hideinitializer
 * \brief Enables the alpha value for an RGBA surface.
 */
#define NVMEDIA_VMP_ATTR_DESTINATION_ALPHA             (1<<12)
/**
 * \hideinitializer
 * \brief Premultiply the output with the provided alpha surface.
 */
#define NVMEDIA_VMP_ATTR_DESTINATION_PREMULTIPLY_ALPHA (1<<13)
/**
 * \hideinitializer
 * \brief Apply transformation on the destination surface.
 */
#define NVMEDIA_VMP_ATTR_TRANSFORM                     (1<<14)
/*@} <!-- Ends mixer_attributes sub-group --> */

/**
 * \brief A handle representing a video mixer object.
 */
typedef void NvMediaVideoMixer;

/** \brief Defines deinterlace types.
 */
typedef enum {
/** \hideinitializer \brief BOB deinterlacing. */
    NVMEDIA_DEINTERLACE_TYPE_BOB = 0,
/** \hideinitializer \brief Advanced1 deinterlacing. */
    NVMEDIA_DEINTERLACE_TYPE_ADVANCED1 = 1,
/** \hideinitializer \brief Advanced2 deinterlacing. */
    NVMEDIA_DEINTERLACE_TYPE_ADVANCED2 = 2
} NvMediaDeinterlaceType;

/** \brief Defines picture structure types.
 */
typedef enum {
/** \hideinitializer \brief The picture is a field, and is the top field of the surface. */
    NVMEDIA_PICTURE_STRUCTURE_TOP_FIELD = 0x1,
/** \hideinitializer \brief The picture is a field, and is the bottom field of the surface. */
    NVMEDIA_PICTURE_STRUCTURE_BOTTOM_FIELD = 0x2,
/** \hideinitializer \brief The picture is a frame, and hence is the entire surface. */
    NVMEDIA_PICTURE_STRUCTURE_FRAME = 0x3
} NvMediaPictureStructure;

/**
 * \brief Returns the version information for the Video Mixer library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    filled by the Video Mixer library.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaVideoMixerGetVersion(
    NvMediaVersion *version
);

/**
 * \brief The principle job of the video mixer is to convert YUV data to
 * RGB, and perform other post-processing at the same time, such as
 * deinterlacing.
 *
 * \param[in] device The \ref NvMediaDevice "device" this video mixer will use.
 * \param[in] surfaceType Surface type of the input surface.
 * \param[in] mixerWidth Video mixer width.
 * \param[in] mixerHeight Video mixer height.
 * \param[in]  sourceAspectRatio Aspect ratio of the source video.
 * This determines how the video is going to be presented on the output surface.
 * \param[in] videoWidth Video width.
 * \param[in] videoHeight Video height.
 * \param[in] features  This selects which features this \ref NvMediaVideoMixer will
 * support. This determines the internal scratch surfaces
 * this function initially creates. At present,
 * the following features are supported and may be OR'd together:
 *  - \ref NVMEDIA_VMP_FEATURE_BACKGROUND_PRESENT
 *  - \ref NVMEDIA_VMP_FEATURE_INTERLACED
 *  - \ref NVMEDIA_VMP_FEATURE_DEINTERLACING
 *  - \ref NVMEDIA_VMP_FEATURE_ADVANCED1_DEINTERLACING
 *  - \ref NVMEDIA_VMP_FEATURE_ADVANCED2_DEINTERLACING
 *  - \ref NVMEDIA_VMP_FEATURE_LIMITED_RGB_INPUT
 *  - \ref NVMEDIA_VMP_FEATURE_INVERSE_TELECINE
 *  - \ref NVMEDIA_VMP_FEATURE_NOISE_REDUCTION
 *  - \ref NVMEDIA_VMP_FEATURE_SHARPENING
 *  - \ref NVMEDIA_VMP_FEATURE_ALPHA_SURFACE_MODE
 * \return \ref NvMediaVideoMixer The new video mixer's handle or NULL if unsuccessful.
 */
NvMediaVideoMixer *
NvMediaVideoMixerCreate(
    NvMediaDevice *device,
    NvMediaSurfaceType surfaceType,
    uint16_t mixerWidth,
    uint16_t mixerHeight,
    float_t  sourceAspectRatio,
    uint16_t videoWidth,
    uint16_t videoHeight,
    uint32_t features
);

/**
 * \brief Destroys a mixer created by \ref NvMediaVideoMixerCreate.
 * \param[in] mixer The mixer to be destroyed.
 */
void
NvMediaVideoMixerDestroy(
    NvMediaVideoMixer *mixer
);

/**
 * \brief Holds video mixer attributes.
 */
typedef struct {
/** \brief A value clamped to between -1.0 and 1.0, initialized to
 * 0.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_BRIGHTNESS.
 */
    float_t brightness;
/** \brief A value clamped to between 0.0 and 10.0, initialized to
 * 1.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_CONTRAST.
 */
    float_t contrast;
/** \brief A value clamped to between 0.0 and 10.0, initialized to
 * 1.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_SATURATION.
 */
    float_t saturation;
/** \brief A value clamped to between -PI and PI, initialized to
 * 0.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_HUE.
 */
    float_t hue;
/** \brief Color standard for input video. One of the following:
 * - \ref NVMEDIA_COLOR_STANDARD_ITUR_BT_601 (default)
 * - \ref NVMEDIA_COLOR_STANDARD_ITUR_BT_709
 * - \ref NVMEDIA_COLOR_STANDARD_SMPTE_240M
 * \n The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_COLOR_STANDARD.
 */
    NvMediaColorStandard colorStandard;
/** \brief Deintelacing type for input video. One of the following:
 * - \ref NVMEDIA_DEINTERLACE_TYPE_BOB (default)
 * - \ref NVMEDIA_DEINTERLACE_TYPE_ADVANCED1
 * \n The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_DEINTERLACE_TYPE.
 */
    NvMediaDeinterlaceType deinterlaceType;
/**
 * \brief Holds a value confined to the range 0.0 to 1.0, initialized
 * 0.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_NOISE_REDUCTION.
 */
    float_t noiseReduction;
/** \brief Holds a Noise Reduction Algorithm, which must be one of the following:
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_ORIGINAL
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_LOW_LIGHT,
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_MEDIUM_LIGHT,
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_OUTDOOR_HIGH_LIGHT,
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_LOW_LIGHT,
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_MEDIUM_LIGHT,
 * - \ref NVMEDIA_NOISE_REDUCTION_ALGORITHM_INDOOR_HIGH_LIGHT
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_NOISE_REDUCTION_ALGORITHM.
 */
    NvMediaNoiseReductionAlgorithm noiseReductionAlgorithm;
/**
 * \brief A value confined to the range 0.0 and 1.0, initialized
 * 0.0 at NvMediaVideoMixer creation.  The corresponding
 * attribute mask is \ref NVMEDIA_VMP_ATTR_SHARPENING.
 */
    float_t sharpening;
/**
 * A boolean initialized to NVMEDIA_FALSE at NvMediaVideoMixer
 * creation.  This option is ignored unless using
 * ADVANCED1/2 deinterlacing at field-rate output.
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_INVERSE_TELECINE.
 */
    NvMediaBool inverseTelecine;
/** \brief Filter quality. One of the following:
 * - \ref NVMEDIA_FILTER_QUALITY_LOW
 * - \ref NVMEDIA_FILTER_QUALITY_MEDIUM
 * - \ref NVMEDIA_FILTER_QUALITY_HIGH
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_FILTER_QUALITY.
 */
    NvMediaFilterQuality filterQuality;
/**
 * \brief Holds a value confined to the range 0.0 and 1.0.
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_DESTINATION_ALPHA.
 */
    float_t destinationAlpha;
/**
 * Holds a flag that specifies to pre-multiply the output
 * surface by the alpha channel.
 * The flag is initialized to NVMEDIA_FALSE at \ref NvMediaVideoMixer
 * creation.  This option is applies only when using API
 * NvMediaVideoMixerRenderSurfaceWithAlpha().
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_DESTINATION_PREMULTIPLY_ALPHA.
 * With this option enabled, the output surface is pre-multiplied by
 * the alpha channel.
 */
    NvMediaBool premultiplyAlpha;
/** \brief Specifies one of the destination transformation:
 * - \ref NVMEDIA_TRANSFORM_NONE
 * - \ref NVMEDIA_TRANSFORM_ROTATE_90
 * - \ref NVMEDIA_TRANSFORM_ROTATE_180,
 * - \ref NVMEDIA_TRANSFORM_ROTATE_270,
 * - \ref NVMEDIA_TRANSFORM_FLIP_HORIZONTAL,
 * - \ref NVMEDIA_TRANSFORM_INV_TRANSPOSE,
 * - \ref NVMEDIA_TRANSFORM_FLIP_VERTICAL,
 * - \ref NVMEDIA_TRANSFORM_TRANSPOSE
 *
 * The corresponding attribute mask is
 * \ref NVMEDIA_VMP_ATTR_TRANSFORM.
 */
    NvMediaTransform dstTransform;
} NvMediaVideoMixerAttributes;

/** \brief Sets NvMediaVideoMixer attributes.
 *
 * \param[in] mixer The mixer object that will perform the
 *       mixing/rendering operation.
 * \param[in] attributeMask Determines which attributes are set. The value
 *       can be any combination of the binary OR of the following attributes:
 * - \ref NVMEDIA_VMP_ATTR_BRIGHTNESS
 * - \ref NVMEDIA_VMP_ATTR_CONTRAST
 * - \ref NVMEDIA_VMP_ATTR_SATURATION
 * - \ref NVMEDIA_VMP_ATTR_HUE
 * - \ref NVMEDIA_VMP_ATTR_COLOR_STANDARD
 * - \ref NVMEDIA_VMP_ATTR_DEINTERLACE_TYPE
 * - \ref NVMEDIA_VMP_ATTR_NOISE_REDUCTION
 * - \ref NVMEDIA_VMP_ATTR_NOISE_REDUCTION_ALGORITHM
 * - \ref NVMEDIA_VMP_ATTR_SHARPENING
 * - \ref NVMEDIA_VMP_ATTR_INVERSE_TELECINE
 * - \ref NVMEDIA_VMP_ATTR_FILTER_QUALITY
 * - \ref NVMEDIA_VMP_ATTR_DESTINATION_ALPHA
 * - \ref NVMEDIA_VMP_ATTR_DESTINATION_PREMULTIPLY_ALPHA
 * - \ref NVMEDIA_VMP_ATTR_TRANSFORM
 * \param[in] attributes A pointer to a structure that holds all the
 *        attributes but only those are used which are indicated in the
 *        attributeMask.
 */
void
NvMediaVideoMixerSetAttributes(
   NvMediaVideoMixer *mixer,
   uint32_t attributeMask,
   NvMediaVideoMixerAttributes *attributes
);

/**
 * \brief Background descriptor for video mixing.
 */
typedef struct {
    /** \brief Background color */
    NvMediaColor backgroundColor;
} NvMediaBackground;

/**
 * \brief Video descriptor for video mixing.
 */
typedef struct {
    /** \brief Picture structure */
    NvMediaPictureStructure pictureStructure;
    /** \brief Frame/field that follow the current frame/field, NULL if unavailable. */
    NvMediaVideoSurface *next;
    /** \brief Current frame/field. */
    NvMediaVideoSurface *current;
    /** \brief Frame/field prior to the current frame/field, NULL if unavailable */
    NvMediaVideoSurface *previous;
    /** \brief Frame/field prior to previous frame/field, NULL if unavailable. */
    NvMediaVideoSurface *previous2;
    /** \brief Source rectangle, If NULL, a rectangle the full size of the \ref NvMediaVideoSurface is implied. */
    NvMediaRect *srcRect;
    /** \brief Destination rectangle, If NULL, a rectangle the full size of the \ref NvMediaVideoMixer is implied.  */
    NvMediaRect *dstRect;
} NvMediaVideoDesc;

/**
 * \brief Holds an Alpha Surface descriptor for video mixing.
 */
typedef struct {
    /** Holds a pointer to the surface. This surface type must be obtained by
        /ref NvMediaSurfaceFormatGetType with:
        /ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, ALPHA, UINT, 8, BL)
        /ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR, UINT, 8, BL)
        If it is YUV 420 semi planar surface, the Y channel is used as the alpha surface.
    */
    NvMediaVideoSurface *alphaSurface;

    /** Holds the source rectangle. This rectangle is scaled to the mixer size.
        A value of NULL implies a rectangle that is the full size of the alpha surface.
    */
    NvMediaRect *srcRect;
} NvMediaAlphaSurface;

/**
 * \brief Performs a video post-processing and compositing
 *        operation to a surface.
 * \param[in] mixer The mixer object that will perform the
 *       mixing/rendering operation.
 * \param[in] outputSurface Destination surface.
 * \param[in] background A background color or image. If set to any value other
 *       than NULL, the specific color or surface will be used as the first layer
 *       in the mixer's compositing process.
 * \param[in] video Video input descriptor structure.
 * \return \ref NvMediaStatus Status of the mixing operation. Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoMixerRenderSurface(
    NvMediaVideoMixer *mixer,
    NvMediaVideoSurface *outputSurface,
    NvMediaBackground *background,
    NvMediaVideoDesc *video
);

/**
 * Performs post-processing and compositing with alpha channel replacement.
 * More specifically, this function does the following:
 *  1. Performs video post-processing and composites to a surface.
 *     For more information, see NvMediaVideoMixerRenderSurface().
 *  2. Uses the alpha surface to replace the alpha channel in the
 *     output of step 1.
 *     If \ref NVMEDIA_VMP_ATTR_DESTINATION_PREMULTIPLY_ALPHA
 *     is enabled, the output is pre-multiplied by the alpha surface.
 *
 * \param[in] mixer A pointer to the mixer object that performs the
 *       mixing/rendering operation.
 * \param[in] outputSurface A pointer to the destination surface.
 *       This surface type must obtained by /ref NvMediaSurfaceFormatGetType with
 *       \ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, RGBA, UINT, 8, PL/BL).
 * \param[in] background A pointer to a background color or image. If set to any value other
 *       than NULL, the specific color will be used as the background layer.
 * \param[in] video A pointer to the video descriptor structure.
 *       This function only supports progressive video.
 * \param[in] alpha A pointer to the alpha surface used to replace the
 *       alpha channel.
 * \return \ref NvMediaStatus Status of the mixing operation. Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoMixerRenderSurfaceWithAlpha(
    NvMediaVideoMixer *mixer,
    NvMediaVideoSurface *outputSurface,
    NvMediaBackground *background,
    NvMediaVideoDesc *video,
    NvMediaAlphaSurface *alpha
);

/** @} <!-- Ends Video Mixer API --> */

/*
 * \defgroup history_nvmedia_vmp History
 * Provides change history for the NvMedia Video Mixer API.
 *
 * \section history_nvmedia_vmp Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 2.0 </b> May 17, 2017
 * - Removed NvMediaVideoMixerRender and NvMediaVideoMixerRenderWithAlpha functions
 * - Removed multi-layer rendering
 * - Removed secondary video and graphics layer support
 * - Added NvMediaVideoMixerGetVersion function
 * - Added destination surface transformation
 * - Changed NvMediaVideoMixer function definition
 * - All NvMedia data types are moved to standard data types
 *
 * <b> Version 2.1 </b> September 7, 2017
 * - Added feature \ref NVMEDIA_VMP_FEATURE_ENABLE_DFS to enable DFS for mixer
 *   hardware block
 *
 * <b> Version 2.2 </b> March 16, 2018
 * - Move \ref NvMediaNoiseReductionAlgorithm structure definition to nvmedia_common.h header file
 */


#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VMP_H */
