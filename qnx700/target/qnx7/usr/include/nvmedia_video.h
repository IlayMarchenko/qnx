/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Video Surface Processing </b>
 *
 * @b Description: This file contains the
 *                 \ref nvmedia_video_top "Video Surface Processing API".
 */

#ifndef _NVMEDIA_VIDEO_H
#define _NVMEDIA_VIDEO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_surface.h"

/**
 * \defgroup nvmedia_video_top Video Surface Handling API
 *
 * The Video Processing API encompasses all NvMedia video surface related functionality
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VIDEO_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_VIDEO_VERSION_MINOR   5

/**
 * \defgroup surface_api Video Surface
 * @ingroup nvmedia_video_top
 *
 * Defines and manages objects for defining video RAM surfaces.
 *
 * \ref NvMediaVideoSurface "NvMediaVideoSurface"s are video RAM surfaces
 * storing YUV or RGBA data. They may be used as sources for the video mixer and
 * they may be used as rendering targets/references by the video decoder.
 * \ref NvMediaVideoSurface "NvMediaVideoSurface"s are created with
 * \ref NvMediaVideoSurfaceCreateNew() and destroyed with
 * \ref NvMediaVideoSurfaceDestroy().
 * @{
 */

/**
 * \brief A handle representing a video surface object.
 */
typedef struct {
    /*! Surface type. */
    NvMediaSurfaceType type;
    /*! Surface width */
    uint32_t width;
    /*! Surface height */
    uint32_t height;
    /*! Surface tag that can be used by the application. NvMedia
        does not change the value of this member. */
    void *tag;
    /*! Surface color standard type */
    uint32_t colorStd;
} NvMediaVideoSurface;

/**
 * \brief A handle representing a video surface map.
 * Corresponding members of this structure are filled by \ref NvMediaVideoSurfaceLock.
 * For different surface types different members are filled as described here:
 *  <table border>
 *  <tr>
 *     <td><b> Surface type </b></td>
 *     <td><b> Filled members </b></td>
 *  </tr>
 *  <tr>
 *     <td><b> \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420/422/444, PACKED/SEMI-PLANAR/PLANAR, 8, PL/BL) </b></td>
 *     <td> lumaWidth, lumaHeight, pY, pitchY, pU, pitchU, pV, pitchV </td>
 *  </tr>
 *  <tr>
 *     <td><b> \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUYV, 422, PACKED, 8, PL) </b></td>
 *     <td> lumaWidth, lumaHeight, pY, pitchY
 *          \n Y refer to YUYV. </td> *  </tr>
 *  <tr>
 *     <td><b> \ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, RGBA, UINT, 8, PL/BL) </b></td>
 *     <td> lumaWidth, lumaHeight, pRGBA, pitchRGBA </td>
 *  </tr>
 *  </table>
 */
typedef struct {
    /*! Surface width in luma pixels*/
    uint32_t lumaWidth;
    /*! Surface height in luma pixels */
    uint32_t lumaHeight;
    /*! Y surface pointer */
    unsigned char *pY;
    /*! Y surface pitch */
    uint32_t pitchY;
    /*! U surface pointer */
    unsigned char *pU;
    /*! U surface pitch */
    uint32_t pitchU;
    /*! V surface pointer */
    unsigned char *pV;
    /*! V surface pitch */
    uint32_t pitchV;
    /*! Y2 surface pointer */
    unsigned char *pY2;
    /*! Y2 surface pitch */
    uint32_t pitchY2;
    /*! U2 surface pointer */
    unsigned char *pU2;
    /*! U2 surface pitch */
    uint32_t pitchU2;
    /*! V2 surface pointer */
    unsigned char *pV2;
    /*! V2 surface pitch */
    uint32_t pitchV2;
    /*! RGBA surface pointer */
    unsigned char *pRGBA;
    /*! RGBA surface pitch */
    uint32_t pitchRGBA;
} NvMediaVideoSurfaceMap;

/**
 * \brief Allocates a video surface object. Upon creation, the contents are in an
 * undefined state.
 * \param[in] device A pointer to the device's resource manager connection, which is used for the allocation.
 * \param[in] type Surface format type obtained from \ref NvMediaSurfaceFormatGetType API.
 * \param[in] attrs An array of surface allocation attributes for surface creation.
 * \param[in] numAllocAttrs Number of attributes in the array.
 * \param[in] flags Flags for module hint (used in future).
 * \return \ref NvMediaVideoSurface The new surfaces's handle or NULL if unsuccessful.
 */
NvMediaVideoSurface *
NvMediaVideoSurfaceCreateNew(
    NvMediaDevice *device,
    NvMediaSurfaceType type,
    NvMediaSurfAllocAttr *attrs,
    uint32_t numAllocAttrs,
    uint32_t flags
);

/**
 * \brief Destroys a video surface object.
 * \param[in] surface The video surface to destroy.
 */
void
NvMediaVideoSurfaceDestroy(
    NvMediaVideoSurface *surface
);

/**
 * Locks a video surface and returns the associated mapped pointers
 * pointing to the Y, U and V surfaces that a software video decoder
 * can fill up.
 * \param[in] surface Video surface object
 * \param[out] surfaceMap Surface pointers and pitches
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaVideoSurfaceLock(
    NvMediaVideoSurface *surface,
    NvMediaVideoSurfaceMap *surfaceMap
);

/**
 * Unlocks a video surface. Internal engines cannot use a surface
 * until it is locked.
 * \param[in] surface Video surface object
 */
void
NvMediaVideoSurfaceUnlock(
    NvMediaVideoSurface *surface
);

/**
 * \brief NvMediaVideoSurfacePutBits reads a client memory buffer and
 *       writes the content into an NvMedia video surface.
 * \param[out] videoSurface
 *       Destination NvMediaVideoSurface type surface. The surface must be locked using
 *       \ref NvMediaVideoSurfaceLock prior to calling this function.
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
 * \n \ref NVMEDIA_STATUS_ERROR if videoSurface is not locked.
 */
NvMediaStatus
NvMediaVideoSurfacePutBits(
    NvMediaVideoSurface *videoSurface,
    NvMediaRect *dstRect,
    void **srcPntrs,
    uint32_t *srcPitches
);

/**
 * \brief Reads an NvMedia video surface and
 *        writes the content into a client memory buffer.
 * \param[in] videoSurface
 *       Source NvMediaVideoSurface type surface. The surface must be locked using
 *       \ref NvMediaVideoSurfaceLock prior to calling this function.
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
 * \n \ref NVMEDIA_STATUS_ERROR if videoSurface is not locked.
 */
NvMediaStatus
NvMediaVideoSurfaceGetBits(
    NvMediaVideoSurface *videoSurface,
    NvMediaRect *srcRect,
    void **dstPntrs,
    uint32_t *dstPitches
);

/*@} <!-- Ends surface_api -> */

/*
 * \defgroup history_nvmedia_video History
 * Provides change history for the NvMedia Video Surface handling
 *
 * \section history_nvmedia_video Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b> May 15, 2017
 * - Added deprecated warning message for \ref NvMediaVideoSurfaceCreateEx,
 *   \ref NvMediaVideoSurfaceSetAttributes
 *
 * <b> Version 1.2 </b> May 18, 2017
 * - Added deprecated warning message for \ref NvMediaVideoSurfaceCreate
 * - NvMediaVideoSurfaceWaitForCompletion() is deprecated
 * - All NvMedia data types are moved to standard data types
 *
 * <b> Version 1.3 </b> May 18, 2017
 * - Added colorStd member in \ref NvMediaVideoSurface
 *
 * <b> Version 1.4 </b> September 12, 2017
 * - Removed NVMEDIA_SURFACE_CREATE_ATTRIBUTE_CAPTURE, NVMEDIA_SURFACE_CREATE_ATTRIBUTE_DISPLAY,
 *   NVMEDIA_SURFACE_ATTRIBUTE_INTERLACED
 * - Deprecated \ref NvMediaVideoSurfaceCreate, \ref NvMediaVideoSurfaceCreateEx,
 *   \ref NvMediaVideoSurfaceSetAttributes
 *
 * <b> Version 1.5 </b> October 5, 2018
 * - Updated the comments in the header to use new NvMediaSurfaceType values
 *
 */

/** @} <!-- Ends nvmedia_video_top --> */


#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VIDEO_H */
