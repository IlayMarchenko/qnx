/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file nvmedia_vop.h
 * \brief <b> NVIDIA Media Interface: Video Output Processing (VOP)</b>
 *
 * This file contains the \ref image_display_api "Video Output Processing API".
 */

#ifndef _NVMEDIA_VOP_H
#define _NVMEDIA_VOP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_common.h"
#include "nvmedia_video.h"

/**
 * \defgroup videooutput_api Video Output
 * \ingroup nvmedia_video_top
 *
 * Declares and manages objects for defining the locations of the composed surfaces.
 *
 * The NvMediaVideoOutput object determines where the composed surfaces
 * are going to be displayed.
 *
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VOP_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_VOP_VERSION_MINOR   0

/**
 * \brief Video output object created by \ref NvMediaVideoOutputCreate.
 */
typedef struct {
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaVideoOutput;

/**
 * \brief Sets the preferences for the video output creation.
 *  @note Depending on the video output type, these preferences might not be met
 *  and the created video output parameters might be different.
 */
typedef struct {
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaVideoOutputPreferences;

/**
 * \brief Device parameters returned by \ref NvMediaVideoOutputDevicesQuery function.
 */
typedef struct {
    /*! Display identification */
    uint32_t displayId;
    /*! Set to NVMEDIA_TRUE if the device is already enabled (initialized) by the system */
    NvMediaBool enabled;
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaVideoOutputDeviceParams;

/**
 * \brief Sets video output position and size.
 * \param[in] output Video output
 * \param[in] position The rectangle where the video is going to be rendered
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoOutputSetPosition(
   NvMediaVideoOutput *output,
   NvMediaRect *position
);

/**
 * \brief Sets video output depth. This function must be called after
 * NvMediaVideoMixerCreate().
 * \param[in] output Video output
 * \param[in] depth  A positive value (up to 255) to where the video display
 *                   relative to the top-most layer (depth == 0).
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoOutputSetDepth(
   NvMediaVideoOutput *output,
   uint32_t depth
);

/**
 * \brief Queries the display system and returns the parameters of all display devices.
 *        If the \a outputParams parameter is NULL,
 *        the function returns only an \a outputDevices parameter. With this scheme, the
 *        client can query the number of devices, allocate memory for the descriptors,
 *        and call this function again, with the properly allocated \a outputParams buffer.
 * \param[out] outputDevices The number of display devices.
 * \param[in,out] outputParams A pointer to an array that the function
 *        fills with an entry for each display device, where:
 *        <ul>
 *         <li>\a outputDevices specifies the number of entries, and</li>
 *         <li>each entry specifies the parameters for a display device.</li>
 *        </ul>
 *        It is the client's
 *        responsibility to allocate sufficient memory.
 *        If the client sets the value to NULL, no data is returned.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoOutputDevicesQuery(
   int32_t *outputDevices,
   NvMediaVideoOutputDeviceParams *outputParams
);

/**
 * \brief Returns the version information for the Video Output Processing library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    filled by the Video Output Processing library.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaVideoOutputGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates a video output object.
 * \param[in] displayId If the \a alreadyCreated parameter is set to
 *            \ref NVMEDIA_TRUE and for an overlay,
 *            then this parameter provides the previously created video output ID.
 * \param[in] windowId The hardware overlay window to access.
 *            For example: @code (windowId = 0) == (Overlay Window A) @endcode
 *            Valid values are 0 (A), 1 (B), 2 (C).
 * \param[in] outputPreference A pointer to the desired video output parameters.
 * \param[in] alreadyCreated Set to \ref NVMEDIA_TRUE if the video output is already created
 *            by another application. In this case NvMedia is not going to create a new one
 *            just reuse it.
 * \return \ref NvMediaVideoOutput The new video output's handle or NULL if
 *            unsuccessful. The NvMediaVideoOutput::width, NvMediaVideoOutput::height,
 *            and NvMediaVideoOutput::refreshRate members reflect the
 *            actual video output values.
 */
NvMediaVideoOutput *
NvMediaVideoOutputCreate(
   uint32_t displayId,
   uint32_t windowId,
   NvMediaVideoOutputPreferences *outputPreference,
   NvMediaBool alreadyCreated
);

/**
 * \brief Destroys a video output created by \ref NvMediaVideoOutputCreate.
 * \param[in] output The video output to be destroyed.
 */
void
NvMediaVideoOutputDestroy(
    NvMediaVideoOutput *output
);

/** \brief Sets NvMediaVideoOutput attributes.
 *
 * \param[in] output The output object that performs the
 *       flipping operation.
 * \param[in] attributeMask Determines which attributes are set. The value
 *       can be any combination of the binary OR of the following attributes:
 * - \ref NVMEDIA_DISP_ATTR_LIMITED_RGB
 * - \ref NVMEDIA_DISP_ATTR_BRIGHTNESS
 * - \ref NVMEDIA_DISP_ATTR_CONTRAST
 * - \ref NVMEDIA_DISP_ATTR_SATURATION
 * - \ref NVMEDIA_DISP_ATTR_HUE
 * - \ref NVMEDIA_DISP_ATTR_COLOR_STANDARD
 * \param[in] attributes A pointer to a structure that holds all the
 *        attributes, but only those which are indicated in the
 *        \a attributeMask are used.
 */
void
NvMediaVideoOutputSetAttributes(
   NvMediaVideoOutput *output,
   uint32_t attributeMask,
   NvMediaDispAttributes *attributes
);

/**
 * \brief Displays a video surface using video output that
 * NvMediaVideoOutputCreate() created.
 * \param[in] output The video output handle.
 * \param[in] videoSurface The video surface to be displayed.
 * \param[in] srcRect
 *       A structure containing co-ordinates of the rectangle in the source surface
 *       from which the client surface is to be copied. Setting \a srcRect to NULL
 *       implies a rectangle of full surface size.
 * \param[in] dstRect
 *       A structure containing co-ordinates of the rectangle in the destination surface
 *       to which the client surface is to be copied. Setting \a dstRect to NULL implies a
 *       rectangle of full surface size.
 * \param[in] releaseList A pointer to an array of \ref NvMediaVideoSurface pointers filled by this
 *       function and terminated with NULL.
 *       When \ref NvMediaVideoOutputFlip function is called it might need to use some of the
 *       input video buffers for a longer time depending on the pipelining model.
 *       When the buffers are no longer needed they are released using this list.
 *       It is the responsibility of the application to allocate the memory for the list.
 *       The maximum size of the list is the number of possible surfaces passed to
 *       this function plus one for the NULL terminator.
 * \param[in] timeStamp Determines when the input video surface is going to be displayed.
 *       This is a pointer to the time structure. NULL means the input video surface
 *       displays as soon as possible.
 * \return \ref NvMediaStatus Status of the operation. Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaVideoOutputFlip(
     NvMediaVideoOutput *output,
     NvMediaVideoSurface *videoSurface,
     NvMediaRect *srcRect,
     NvMediaRect *dstRect,
     NvMediaVideoSurface **releaseList,
     NvMediaTime *timeStamp
);
/** @} <!-- Ends videooutput_api Video Output --> */

/*
 * \defgroup history_nvmedia_vop History
 * Provides change history for the NvMedia Video Output API.
 *
 * \section history_nvmedia_vop Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 2.0 </b> May 16, 2017
 * - Removed NvMediaVideoOutputType and NvMediaVideoOutputDevice types
 * - Removed NvMediaVideoOutputCreateEx function
 * - Removed NvMediaVideoOutputCheckFormatSupport function
 * - Changed parameters of NvMediaVideoOutputCreate function
 * - Added NvMediaVideoOutputGetVersion function
 * - All NvMedia data types are moved to standard data types
 */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VOP_H */
