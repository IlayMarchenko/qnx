/*
 * Copyright (c) 2013-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: 2D Processing Control </b>
 *
 * @b Description: This file contains the \ref image_2d_api "Image 2D
 *  Processing API."
 */

#ifndef _NVMEDIA_2D_H
#define _NVMEDIA_2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_common.h"
#include "nvmedia_image.h"
/**
 * \defgroup image_2d_api Image 2D Processing
 *
 * The Image 2D Processing API encompasses all NvMedia 2D image processing
 * related functionality.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number. */
#define NVMEDIA_2D_VERSION_MAJOR   2
/** \brief Minor Version number. */
#define NVMEDIA_2D_VERSION_MINOR   2


/** \defgroup filter Surface Filtering */
/**
 * \brief Specifies filtering mode used for stretched blits.
 * \ingroup filter
 */
typedef enum
{
    /** Specifies disable the horizontal and vertical filtering. */
    NVMEDIA_2D_STRETCH_FILTER_OFF = 0x1,
    /** Specifies enable low quality filtering. */
    NVMEDIA_2D_STRETCH_FILTER_LOW,
    /** Specifies enable media quality filtering. */
    NVMEDIA_2D_STRETCH_FILTER_MEDIUM,
    /** Specifies enable the best quality filtering. */
    NVMEDIA_2D_STRETCH_FILTER_HIGH
} NvMedia2DStretchFilter;

/** \brief Specifies operation flags that affect blit behavior.
 * \ingroup blit
 **/
typedef enum
{
    /** Specifies compute and return CRC value. */
    NVMEDIA_2D_BLIT_FLAG_RETURN_CRC             = (1u << 0)
} NvMedia2DBlitFlags;

/*---------------------------------------------------------*/
/** \defgroup blit Blits
 *
 * Blit functions define valid parameters for a blit.
 */

/**
 * \brief Specifies bit-mask for \ref NvMedia2DBlitParameters::validFields.
 * \ingroup blit
 */
typedef enum
{
    /** Specifies enable use of stretch filter. */
    NVMEDIA_2D_BLIT_PARAMS_FILTER               = (1u << 0),
    /** Specifies enable use of blit flags. */
    NVMEDIA_2D_BLIT_PARAMS_FLAGS                = (1u << 1),
    /** Specifies enable use of destination transform. */
    NVMEDIA_2D_BLIT_PARAMS_DST_TRANSFORM        = (1u << 2),
    /** Specifies enable use of color space conversion standard. */
    NVMEDIA_2D_BLIT_PARAMS_COLOR_STD            = (1u << 3)
} NvMedia2DBlitParamField;

/**
 * Holds the additional parameters for a blit.
 * The \a validFields field is a mask which indicates which fields of the struct
 * to read.
 *
 * \ingroup blit
 */
typedef struct
{
    /*! Indicates valid fields in this structure. This determines which structure
        members are used. The following bit-masks can be ORed:
        \n \ref NVMEDIA_2D_BLIT_PARAMS_FILTER
        \n \ref NVMEDIA_2D_BLIT_PARAMS_FLAGS
        \n \ref NVMEDIA_2D_BLIT_PARAMS_DST_TRANSFORM
    */
    uint32_t                        validFields;
    /*! Indicates filter mode. */
    NvMedia2DStretchFilter          filter;
    /*! Holds flags to use when setting \ref NVMEDIA_2D_BLIT_PARAMS_FLAGS. */
    uint32_t                        flags;
    /*! Holds destination transformation when
     \ref NVMEDIA_2D_BLIT_PARAMS_DST_TRANSFORM is set. */
    NvMediaTransform                dstTransform;
    /*! Holds color space conversion standard when
     \ref NVMEDIA_2D_BLIT_PARAMS_COLOR_STD is set. */
    NvMediaColorStandard            colorStandard;
} NvMedia2DBlitParameters;

/**
 * Holds additional values returned from a blit.
 *
 * \ingroup blit
 */
typedef struct
{
    /** Holds returned CRC value. */
    uint32_t crc;
} NvMedia2DBlitParametersOut;

/**
 * \brief Returns the version information for the NvMedia 2D library.
 * \param[out] version A pointer to a \ref NvMediaVersion structure
 *                    filled by the 2D library.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMedia2DGetVersion(
    NvMediaVersion *version
);

/**
 * \brief  An opaque handle representing an NvMedia2D object.
 */
typedef void NvMedia2D;

/**
 * \brief Creates a 2D object.
 * \param[in] device A pointer to the \ref NvMediaDevice device this 2D object
 *  will use.
 * \return \ref NvMedia2D, the new 2D object's handle if successful, or NULL
 *  otherwise.
 * \ingroup blit
 */
NvMedia2D *
NvMedia2DCreate(
    NvMediaDevice *device
);

/**
 * \brief Destroys a 2D object.
 * \param[in] i2d A pointer to the 2D object to destroy.
 * \return void
 * \ingroup blit
 */
void
NvMedia2DDestroy(
    NvMedia2D *i2d
);

/**
 * Performs a 2D blit operation with supplementary return values.
 *
 * A blit transfers pixels from a source surface to a destination surface,
 * applying a variety of transformations to the pixel values on the way.
 * Note that for a YUV surface type with 16-bit depth, only scale and crop are
 * supported. Format conversion is not supported.
 *
 * The interface aims at making the typical uses of normal pixel copy easy,
 * by not mandating the setting of advanced blit parameters unless they are
 * actually required.
 *
 * Passing in NULL as \a params invokes a standard pixel copy blit without
 * additional transformations. If the dimensions of the source rectangle do
 * not match the dimensions of the destination rectangle, pixels are scaled
 * to fit the destination rectangle. The filtering mode for the scale defaults
 * to NVMEDIA_2D_STRETCH_FILTER_LOW. Additional filtering modes are available
 * by setting the corresponding parameter in \ref NvMedia2DBlitParameters.
 *
 * Passing in NULL as \a srcRect defaults to a source rectangle the size of the
 * full source surface, likewise for \a dstRect and the destination surface.
 *
 * If \a paramsOut is not NULL, the blit operation stores supplementary return
 * values for the blit to the structure pointed to by \a paramsOut, if
 * applicable.
 * If \a paramsOut is NULL, no supplementry information is returned.
 *
 * Supplementary values are returned when using the blit flag:
 *
 * \ref NVMEDIA_2D_BLIT_FLAG_RETURN_CRC returns a CRC value of blitted pixels.
 *
 * A straight pixel copy between surfaces of the same dimensions (but not
 * necessarily the same bit depth or even color format) is performed by:
 *
 * @code
 *      NvMedia2DBlitEx(i2d, dst, NULL, src, NULL, NULL, NULL);
 * @endcode
 *
 * \param[in] i2d        A pointer to a i2d Image 2D object.
 * \param[in] dstSurface A pointer to a destination surface.
 * \param[in] dstRect A pointer to a destination rectangle. For a YUV surface
 *                   type with 16-bit depth, the x0 and y0 of \a dstRect must
 *                   be 0.
 * \param[in] srcSurface A pointer to a source surface.
 * \param[in] srcRect A pointer to a source rectangle.
 * \param[in] params A pointer to parameters.
 * \param[out] paramsOut A pointer to returned parameters.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if succcessful, or
 *  \ref NVMEDIA_STATUS_BAD_PARAMETER if any mandatory pointer is invalid.
 * \ingroup blit
 */
NvMediaStatus
NvMedia2DBlitEx(
    NvMedia2D                       *i2d,
    NvMediaImage                    *dstSurface,
    const NvMediaRect               *dstRect,
    NvMediaImage                    *srcSurface,
    const NvMediaRect               *srcRect,
    const NvMedia2DBlitParameters   *params,
    NvMedia2DBlitParametersOut      *paramsOut
);

/**
 * Copies a plane of a YUV image to another YUV image.
 *
 * The source and the destination must have the same format.
 *
 * \param[in] dstSurface A pointer to a destination surface.
 * \param[in] dstPlane Destination plane.
 * \param[in] srcSurface A pointer to the source surface.
 * \param[in] srcPlane Source plane.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more parameter values are bad.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the requested operation is not
 *    supported.
 * - \ref NVMEDIA_STATUS_ERROR otherwise.
 * \ingroup blit
 */
NvMediaStatus
NvMedia2DCopyPlane(
    NvMediaImage    *dstSurface,
    uint32_t        dstPlane,
    NvMediaImage    *srcSurface,
    uint32_t        srcPlane
)__NVM_DEPRECATED_MSG__("Use NvMedia2DCopyPlaneNew API");

/**
 * Copies a plane of a YUV image to another YUV image.
 *
 * The source and the destination must have the same format.
 *
 * \param[in] i2d NvMedia 2D device handle.
 * \param[in] dstSurface A pointer to a destination surface.
 * \param[in] dstPlane Destination plane.
 * \param[in] srcSurface A pointer to the source surface.
 * \param[in] srcPlane Source plane.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more parameter values are bad.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the requested operation is not
 *    supported.
 * - \ref NVMEDIA_STATUS_ERROR otherwise.
 * \ingroup blit
 */
NvMediaStatus
NvMedia2DCopyPlaneNew(
    NvMedia2D       *i2d,
    NvMediaImage    *dstSurface,
    uint32_t        dstPlane,
    NvMediaImage    *srcSurface,
    uint32_t        srcPlane
);

/**
 * Performs an NvMedia2D weave operation on NvMedia images.
 *
 * 2D weave interface takes frames containing odd and even lines
 * as input. The destination frame is formed by interleaving odd and
 * even lines.
 *
 * The input frames must have the same format, which must be RAW8 or RGBA.
 * The output frame format is always RGBA; the output frame has the same
 * width as each input frame, and twice the height.
 *
 * \param[in] device: NvMedia device handle.
 * \param[in] imageOdd: A pointer to an NvMedia image representing odd lines.
 * \param[in] imageEven: A pointer to an NvMedia image representing even lines.
 * \param[out] outImage: A pointer to an NvMedia image containing weave output.
 * \return \ref NvMediaStatus, the completion status of operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more parameter values are bad.
 * - \ref NVMEDIA_STATUS_OUT_OF_MEMORY if the operation ran out of memory.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if input surface types don't match.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any mandatory pointer is invalid.
 *
 **/
NvMediaStatus
NvMedia2DWeave(
    NvMediaDevice    *device,
    NvMediaImage     *imageOdd,
    NvMediaImage     *imageEven,
    NvMediaImage     *outImage
)__NVM_DEPRECATED_MSG__("Use NvMedia2DWeaveNew() API");

/**
 * Performs an NvMedia2D weave operation on NvMedia images.
 *
 * 2D weave interface takes frames containing odd and even lines
 * as input. The destination frame is formed by interleaving odd and
 * even lines.
 *
 * The input frames must have the same format, which must be RAW8 or RGBA.
 * The output frame format is always RGBA; the output frame has the same
 * width as each input frame, and twice the height.
 *
 * \param[in] i2d     : NvMedia 2D device handle.
 * \param[in] imageOdd: A pointer to an NvMedia image representing odd lines.
 * \param[in] imageEven: A pointer to an NvMedia image representing even lines.
 * \param[out] outImage: A pointer to an NvMedia image containing weave output.
 * \return \ref NvMediaStatus, the completion status of operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if one or more parameter values are bad.
 * - \ref NVMEDIA_STATUS_OUT_OF_MEMORY if the operation ran out of memory.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if input surface types don't match.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any mandatory pointer is invalid.
 *
 **/
NvMediaStatus
NvMedia2DWeaveNew(
    NvMedia2D        *i2d,
    NvMediaImage     *imageOdd,
    NvMediaImage     *imageEven,
    NvMediaImage     *outImage
);

/*
 * \defgroup history_nvmedia_2d History
 * Provides change history for the NvMedia 2D API.
 *
 * \section history_nvmedia_2d Version History
 *
 * <b> Version 1.1 </b> February 1, 2016
 * - Initial release
 *
 * <b> Version 1.2 </b> May 11, 2016
 * - Added \ref NvMedia2DCheckVersion API
 *
 * <b> Version 1.3 </b> May 5, 2017
 * - Removed compositing, blending and alpha related defines and structures
 *
 * <b> Version 2.0 </b> May 11, 2017
 * - Deprecated NvMedia2DBlit API
 * - Deprecated NvMedia2DCheckVersion API
 * - Deprecated NvMedia2DColorStandard, NvMedia2DColorRange and
 *   NvMedia2DColorMatrix types
 * - Added \ref NvMedia2DGetVersion API
 *
 * <b> Version 2.1 </b> May 17, 2017
 * - Moved transformation to nvmedia_common.h
 * - Renamed NvMedia2DTransform to \ref NvMediaTransform
 *
 * <b> Version 2.2 </b> September 4, 2018
 * - Added deprecated warning message for \refNvMedia2DCopyPlane,
     NvMedia2DWeave
 * - Added APIs \ref NvMedia2DCopyPlaneNew, \ref NvMedia2DWeaveNew
 */
/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_2D_H */
