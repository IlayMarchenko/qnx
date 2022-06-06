/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Pyramid Processing </b>
 *
 * @b Description: This file contains the
 *                 \ref nvmedia_image_pyramid_top "Image Pyramid Processing API".
 */

#ifndef _NVMEDIA_IMAGE_PYRAMID_H
#define _NVMEDIA_IMAGE_PYRAMID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_image.h"

/**
 * \defgroup nvmedia_image_pyramid_top Image Pyramid Handling API
 *
 * The Image Pyramid Processing API encompasses all NvMedia related functionality
 * for handling pyramids of \ref NvMediaImage
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_IMAGE_PYRAMID_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_IMAGE_PYRAMID_VERSION_MINOR   0

/** \brief Max allowed levels in a pyramid */
#define MAX_PYRAMID_LEVELS (10)

/**
 * \brief A handle representing image pyramid objects.
 */
typedef struct NvMediaImagePyramid NvMediaImagePyramid;

/**
 * \brief Allocates an image pyramid.
 * \param[in] device The \ref NvMediaDevice.
 * \param[in] type Surface format type obtained from \ref NvMediaSurfaceFormatGetType API.
 * \param[in] attrs An array of surface alloc attributes for surface creation.
 *                  Resolution is for the base level of the pyramid.
 * \param[in] numLevels Number of levels in the pyramid.
 * \param[in] scale Scale factor for the pyramid.
 * \param[in] numAttrs Number of attributes in the array.
 * \param[in] flags Flags for module hint (used in future).
 * \return \ref NvMediaImagePyramid The new image pyramid's handle or NULL if unsuccessful.
 */
NvMediaImagePyramid *
NvMediaImagePyramidCreate(
    NvMediaDevice *device,
    NvMediaSurfaceType type,
    NvMediaSurfAllocAttr *attrs,
    uint32_t numLevels,
    float scale,
    uint32_t numAttrs,
    uint32_t flags
);

/**
 * \brief Destroys an image pyramid that NvMediaImagePyramidCreate() created.
 * \param[in] pyramid The image pyramid to destroy.
 * \return void
 */
void
NvMediaImagePyramidDestroy(
    NvMediaImagePyramid *pyramid
);

/**
 * Locks an image pyramid and returns the associated mapped pointers
 * pointing to the image pyramid surface data. Only images created without the
 * \ref NVM_SURF_ATTR_CPU_ACCESS_UNMAPPED attribute can be accessed by CPU.
 * If an image is being used by an internal engine this function waits until
 * the completion of this operation.
 * \param[in] pyramid Image pyramid object
 * \param[in] lockAccessType Determines the access type.
 * The following access types are supported and may be OR'd together:
 * \n \ref NVMEDIA_IMAGE_ACCESS_READ Read access
 * \n \ref NVMEDIA_IMAGE_ACCESS_WRITE Write access
 * \n \ref NVMEDIA_IMAGE_ACCESS_READ_WRITE Read/Write access
 * \param[out] surfaceMap Array of Surface descriptors per level.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup lock_unlock
 */
NvMediaStatus
NvMediaImagePyramidLock(
    NvMediaImagePyramid *pyramid,
    uint32_t lockAccessType,
    NvMediaImageSurfaceMap *surfaceMap
);

/**
 * Unlocks an image pyramid. Internal engines cannot use a surface
 * until it is locked.
 * \param[in] pyramid Pyramid object to unlock
 * \return void
 * \ingroup lock_unlock
 */
void
NvMediaImagePyramidUnlock(
    NvMediaImagePyramid *pyramid
);

/**
 * \brief Gets status of the current/last operation for the image pyramid,
          and optionally waits for operation to complete/timeout.
 * \param[in] pyramid A pointer to the image.
 * \param[in] millisecondWait Time  in milliseconds to wait for operation to
              complete before getting status.
              \ref NVMEDIA_IMAGE_TIMEOUT_INFINITE means wait till operation is completed
              and then get status.
 * \param[out] status Status of the operation.
 * \return \ref NvMediaStatus The status of the function call.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaImagePyramidGetStatus(
    NvMediaImagePyramid *pyramid,
    uint32_t millisecondWait,
    NvMediaTaskStatus *status
);

/**
 * \brief Returns \ref NvMediaImage pointer of image for a level.
 * \param[in] pyramid The image pyramid handle.
 * \param[in] level The level for which to obtain image pointer.
 * \return \ref NvMediaImage pointer. NULL in case of error.
 */
NvMediaImage *
NvMediaImagePyramidGetImageForLevel(
    NvMediaImagePyramid * pyramid,
    uint32_t level
);

/**
 * \brief Returns number of levels in the pyramid.
 * \param[in] pyramid The image pyramid handle.
 * \return Number of levels. 0 in case of error.
 */
uint32_t
NvMediaImagePyramidGetNumLevels(
    NvMediaImagePyramid * pyramid
);

/**
 * \brief Returns scale factor of the pyramid.
 * \param[in] pyramid The image pyramid handle.
 * \return Scale factor. 0 in case of error.
 */
float
NvMediaImagePyramidGetScale(
    NvMediaImagePyramid * pyramid
);

/*
 * \defgroup history_nvmedia_image_pyramid History
 * Provides change history for the NvMedia ImagePyramid API.
 *
 * \section history_nvmedia_image_pyramid Version History
 *
 * <b> Version 1.0 </b> December 4, 2017
 * - Initial Release.
 *
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IMAGE_PYRAMID_H */