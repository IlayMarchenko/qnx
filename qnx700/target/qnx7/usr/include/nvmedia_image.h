/*
 * Copyright (c) 2013-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Processing </b>
 *
 * @b Description: This file contains the
 *                 \ref nvmedia_image_top "Image Processing API".
 */

#ifndef _NVMEDIA_IMAGE_H
#define _NVMEDIA_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_video.h"

/**
 * \defgroup nvmedia_image_top Image Handling API
 *
 * The Image Processing API encompasses all NvMedia image related functionality
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_IMAGE_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_IMAGE_VERSION_MINOR   11

/**
 * \defgroup image_creation_api Image Creation
 *
 * Defines and manages image objects.
 *
 * \ref NvMediaImage "NvMediaImage"s are video RAM surfaces
 * storing YUV, RGBA or RAW data. They can store one or more images depending
 * on the class.
 * \ref NvMediaImage "NvMediaImage"s are created with
 * \ref NvMediaImageCreateNew() and destroyed with
 * \ref NvMediaImageDestroy().
 * @{
 */

/**
 * \hideinitializer
 * \brief Maximum number of images in an aggregate image
 */
#define NVMEDIA_MAX_AGGREGATE_IMAGES   6

/**
 * \hideinitializer
 * \brief Maximum number of images in an image group
 */
#define NVMEDIA_MAX_IMAGE_GROUP_SIZE   3

/**
 * \hideinitializer
 * \brief Infinite time-out for \ref NvMediaImageGetStatus
 */
#define NVMEDIA_IMAGE_TIMEOUT_INFINITE  0xFFFFFFFF

/**
 * \brief A handle representing image objects.
 */
typedef struct {
    /*! Image surface type. */
    NvMediaSurfaceType type;
    /*! Image width. */
    uint32_t width;
    /*! Image height. */
    uint32_t height;
    /*! Number of images stored in this image container. */
    uint32_t imageCount;
    /*! Size of top embedded data. */
    uint32_t embeddedDataTopSize;
    /*! Size of bottom embedded data */
    uint32_t embeddedDataBottomSize;
    /*! Image attributes */
    uint32_t attributes;
    /*! Tag that can be used by the application. NvMedia
        does not change the value of this member. */
    void *tag;
    /*! Image capture time-stamp. */
    NvMediaTime captureTimeStamp;
    /*! Image capture global timestamp in microseconds. */
    NvMediaGlobalTime captureGlobalTimeStamp;
    /*! Image color standard type */
    uint32_t colorStd;
} NvMediaImage;

/**
 * \brief A handle representing an image group.
 */
typedef struct {
    /*! List of NvMedia Images in the group. */
    NvMediaImage *imageList[NVMEDIA_MAX_IMAGE_GROUP_SIZE];
    /*! Number of NvMedia Images in the group. */
    uint32_t numImages;
    /*! Tag that can be used by the application. NvMedia
        does not change the value of this member. */
    void *tag;
} NvMediaImageGroup;

/**
 * \brief Bits per pixel.
 */
typedef enum {
    /*! 8 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_8 = 0,
    /*! 10 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_10,
    /*! 12 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_12,
    /*! 14 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_14,
    /*! 16 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_16,
    /*! 20 bits per pixel. */
    NVMEDIA_BITS_PER_PIXEL_20
} NvMediaBitsPerPixel;

/**
 * \brief Pixel order in a raw image.
 */
typedef enum {
    /*! RGGB order. */
    NVMEDIA_RAW_PIXEL_ORDER_RGGB = 0,
    /*! BGGR order. */
    NVMEDIA_RAW_PIXEL_ORDER_BGGR,
    /*! GRBG order. */
    NVMEDIA_RAW_PIXEL_ORDER_GRBG,
    /*! GBRG order. */
    NVMEDIA_RAW_PIXEL_ORDER_GBRG
} NvMediaRawPixelOrder;

/**
 * \brief Gets the version for the NvMedia Image library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaImageGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Allocates an image object. Upon creation, the contents are in an
 * undefined state.
 * \param[in] device The \ref NvMediaDevice.
 * \param[in] type Surface format type obtained from \ref NvMediaSurfaceFormatGetType API.
 * \param[in] attrs An array of surface alloc attributes for surface creation.
 * \param[in] numAttrs Number of attributes in the array.
 * \param[in] flags Flags for module hint (used in future).
 * \return \ref NvMediaImage The new image's handle or NULL if unsuccessful.
 */

NvMediaImage *
NvMediaImageCreateNew(
    NvMediaDevice *device,
    NvMediaSurfaceType type,
    NvMediaSurfAllocAttr *attrs,
    uint32_t numAttrs,
    uint32_t flags
);

/**
 * \brief Destroys an image object that was created by \ref NvMediaImageCreateNew
 * \param[in] image The image to destroy.
 * \return void
 */
void
NvMediaImageDestroy(
    NvMediaImage *image
);

/*@} <!-- Ends image_creation_api Image Creation API --> */

/** \defgroup lock_unlock Image Locking and Unlocking
 *
 * Locking and unlocking provides acces to the image surfaces.
 */

/**
 * \brief Image lock access types.
 * \ingroup lock_unlock
 */
typedef enum {
    /** Read access */
    NVMEDIA_IMAGE_ACCESS_READ       = (1 << 0),
    /** Write access */
    NVMEDIA_IMAGE_ACCESS_WRITE      = (1 << 1),
    /** Read/Write access */
    NVMEDIA_IMAGE_ACCESS_READ_WRITE = (NVMEDIA_IMAGE_ACCESS_READ | NVMEDIA_IMAGE_ACCESS_WRITE),
} NvMediaImageLockAccess;

/**
 * \brief Image surface descriptor used by
 * \ref NvMediaImageLock.
 * \ingroup lock_unlock
 */
typedef struct {
    /*! Pitch of the surface. */
    uint32_t pitch;
    /*! CPU accessible memory pointer of the surface. */
    void *mapping;
} NvMediaImageSurface;

/**
 * \brief Image surface map descriptor used by
 * \ref NvMediaImageLock. This contains up to 6 surface descriptors
 * depending on the image type.
 * \ingroup lock_unlock
 */
typedef struct {
    /*! Image surface type. */
    NvMediaSurfaceType type;
    /*! Image width. */
    uint32_t width;
    /*! Image height. */
    uint32_t height;
    /*! Number of surfaces in the image. */
    uint32_t surfaces;
    /*! Surface descriptors. Only surfaces count of elements are valid. */
    NvMediaImageSurface surface[6];
    /*! Pointer to access metadata */
    void *metaData;
} NvMediaImageSurfaceMap;

/**
 * Locks an image and returns the associated mapped pointers
 * pointing to the image surface data. Only images created without the
 * \ref NVM_SURF_ATTR_CPU_ACCESS_UNMAPPED attribute can be accessed by CPU.
 * If an image is being used by an internal engine this function waits until
 * the completion of this operation.
 * \param[in] image Image object
 * \param[in] lockAccessType Determines the access type.
 * The following access types are supported and may be OR'd together:
 * \n \ref NVMEDIA_IMAGE_ACCESS_READ Read access
 * \n \ref NVMEDIA_IMAGE_ACCESS_WRITE Write access
 * \n \ref NVMEDIA_IMAGE_ACCESS_READ_WRITE Read/Write access
 * \param[out] surfaceMap Surface descriptors
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup lock_unlock
 */
NvMediaStatus
NvMediaImageLock(
    NvMediaImage *image,
    uint32_t lockAccessType,
    NvMediaImageSurfaceMap *surfaceMap
);

/**
 * Unlocks an image. Internal engines cannot use a surface
 * until it is locked.
 * \param[in] image Image object to unlock
 * \return void
 * \ingroup lock_unlock
 */
void
NvMediaImageUnlock(
    NvMediaImage *image
);

/** \defgroup image_get_put_bits Image Read and Write by Client
 *
 * Provides image surface read and write by the client application
 * for diagnostic purposes.
 *
 * \warning These functions are for diagnostics purposes only
 * and should not be used in production code.
 */

/**
 * \brief Reads a client memory buffer and
 *       writes the content into an NvMedia image surface.
 * \param[in] image
 *       The destination NvMediaImage type surface. The image must be locked using
 *       \ref NvMediaImageLock prior to calling this function.
 * \param[in] dstRect
 *       Structure containing co-ordinates of the rectangle in the destination surface
 *       to which the client surface is to be copied. Setting dstRect to NULL implies
 *       rectangle of full surface size.
 * \param[in] srcPntrs
 *       Array of pointers to the client surface planes
 * \param[in] srcPitches
 *       Array of pitch values for the client surface planes
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameters is invalid.
 * \n \ref NVMEDIA_STATUS_ERROR if the image is not locked.
 * \ingroup image_get_put_bits
 */
NvMediaStatus
NvMediaImagePutBits(
    NvMediaImage *image,
    NvMediaRect *dstRect,
    void **srcPntrs,
    uint32_t *srcPitches
);

/**
 * \brief NvMediaImageGetBits reads an NvMedia image and
 *        writes the content into a client memory buffer.
 * \param[in] image
 *       Source NvMediaImage type surface. The surface must be locked using
 *       \ref NvMediaImageLock prior to calling this function.
 * \param[in] srcRect
 *       Structure containing co-ordinates of the rectangle in the source surface
 *       from which the client surface is to be copied. Setting srcRect to NULL
 *       implies rectangle of full surface size.
 * \param[out] dstPntrs
 *       Array of pointers to the destination surface planes
 * \param[in] dstPitches
 *       Array of pitch values for the destination surface planes
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameters is invalid.
 * \n \ref NVMEDIA_STATUS_ERROR if the image is not locked.
 * \ingroup image_get_put_bits
 */
NvMediaStatus
NvMediaImageGetBits(
    NvMediaImage *image,
    NvMediaRect *srcRect,
    void **dstPntrs,
    uint32_t *dstPitches
);

/**
 * \brief Return embedded data stored in a captured image.
 * Embedded data can be added to the following image types.
 * This type must obtained by /ref NvMediaSurfaceFormatGetType with:
 * NVM_SURF_FMT_SET_ATTR_YUV(attr, YUYV, 422, PACKED, UINT, 8, PL)
 * NVM_SURF_FMT_SET_ATTR_RGBA (attr, RGBA, UINT, 8, [PL|BL])
 * NVM_SURF_FMT_SET_ATTR_RAW (attr, [RGGB/BGGR/GRBG/GBRG], INT, [8/10/12/16/20], PL)
 * NVM_SURF_FMT_SET_ATTR_RAW (attr, [RCCB/BCCR/CRBC/CBRC], INT, 12, PL)
 * NVM_SURF_FMT_SET_ATTR_RAW (attr, [RCCC/CCCR/CRCC/CCRC], INT, 12, PL)
 * \param[in] image Image to get the embedded data from.
 * \param[in] imageIndex Index of the sub-image in case of multi-image handle. For single image
 * this parameter is ignored. Index count starts from 0.
 * \param[in] embeddedBufTop The buffer where the top embedded data is stored.
 * \param[in] embeddedBufTopSize Pointer to top buffer size. The actual size of copied
 * data will be returned in this parameter.
 * \param[in] embeddedBufBottom The buffer where the bottom embedded data is stored.
 * \param[in] embeddedBufBottomSize Pointer to bottom buffer size. The actual size of copied
 * data will be returned in this parameter.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER If any of the input parameter is NULL
 * \n \ref NVMEDIA_STATUS_ERROR If the surface type is not supported
 */
NvMediaStatus
NvMediaImageGetEmbeddedData(
    NvMediaImage *image,
    uint32_t imageIndex,
    void *embeddedBufTop,
    uint32_t *embeddedBufTopSize,
    void *embeddedBufBottom,
    uint32_t *embeddedBufBottomSize
);

/**
 * \brief Gets the capture timestamp of the image.
 * \param[in] image A pointer to the image for which to get the timestamp.
 * \param[in] timeStamp A pointer the capture timestamp of the image.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK Success
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER If image or timeStamp is NULL
 * \n \ref NVMEDIA_STATUS_ERROR If any error occurred
 */
NvMediaStatus
NvMediaImageGetTimeStamp(
    NvMediaImage *image,
    NvMediaTime *timeStamp
);

/**
 * \brief Gets the global capture time-stamp of the image.
 * The global time-stamp is set by the NvMedia IPP Capture component.
 * \param[in] image A pointer to the image for which to get the time-stamp.
 * \param[in] globalTimeStamp A pointer to the global capture timestamp of the image.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK Success
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER If image or timeStamp is NULL
 * \n \ref NVMEDIA_STATUS_ERROR If any error occurred
 */
NvMediaStatus
NvMediaImageGetGlobalTimeStamp(
    NvMediaImage *image,
    NvMediaGlobalTime *globalTimeStamp
);

/**
 * \brief Gets status of the current/last operation for the image,
          and optionally waits for operation to complete/timeout.
 * \param[in] image A pointer to the image.
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
NvMediaImageGetStatus(
    NvMediaImage *image,
    uint32_t millisecondWait,
    NvMediaTaskStatus *status
);

/*@} <!-- Ends image_api Image Handling API --> */

/*
 * \defgroup history_nvmedia_image History
 * Provides change history for the NvMedia Image API.
 *
 * \section history_nvmedia_image Version History
 *
 * <b> Version 1.1 </b> March 3, 2016
 * - Initial release
 *
 * <b> Version 1.2 </b> May 11, 2016
 * - Added \ref NvMediaImageCheckVersion API
 *
 * <b> Version 1.3 </b> Jan 17, 2017
 * - Added atrribute NVMEDIA_IMAGE_ATTRIBUTE_CAPTURE in \ref NvMediaImageAttributes
 *
 * <b> Version 1.4 </b> Feb 9, 2017
 * - Added new APIs
 *       NvMediaImageCreateNew()
 *
 * <b> Version 1.5 </b> March 16, 2017
 * - Added \ref NVMEDIA_BITS_PER_PIXEL_16 in \ref NvMediaBitsPerPixel
 *
 * <b> Version 1.6 </b> May 9, 2017
 * - Deprecated the following APIs
 *     - NvMediaImageAcquire
 *     - NvMediaImageRelease
 *     - NvMediaImageWaitForIdle
 *     - NvMediaImageWaitForCompletion
 *     - NvMediaImageCheckVersion
 * - NvMediaImageGetVersion() is added to get the version of NvMedia Image library
 * - All NvMedia data types are moved to standard data types
 *
 * <b> Version 1.7 </b> May 14, 2017
 * - Added API to get status of operation on an image. \ref NvMediaImageGetStatus
 *
 * <b> Version 1.8 </b> May 15, 2017
 * - Added deprecated warning message for \ref NvMediaImageCreate,
 *   \ref NvMediaImageSiblingCreate, \ref NvMediaImageSiblingDestroy,
 *   \ref NvMediaVideoCreateImageSibling, \ref NvMediaImageCreateVideoSibling
 *
 * <b> Version 1.9 </b> May 18, 2017
 * - Added colorStd member in \ref NvMediaImage
 *
 * <b> Version 1.10 </b> June 12, 2017
 * - Added \ref NvMediaImageGroup to hold a list of NvMediaImages.
 *
 * <b> Version 1.11 </b> September 12, 2017
 * - Deprecated \ref NvMediaImageClass, \ref NvMediaImageAttributes, \ref NvMediaImageAdvancedConfig
 * - Deprecated \ref NvMediaImageCreate, \ref NvMediaImageSiblingCreate,
 *   \ref NvMediaVideoCreateImageSibling, \ref NvMediaImageSiblingDestroy,
 *   \ref NvMediaImageCreateVideoSibling, \ref NvMediaVideoSurfaceSiblingDestroy
 *
 */
/*@}*/

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IMAGE_H */
