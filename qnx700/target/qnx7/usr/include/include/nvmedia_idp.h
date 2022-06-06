/*
 * Copyright (c) 2014-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file nvmedia_idp.h
 * \brief <b> NVIDIA Media Interface: Image Display Processing (IDP)</b>
 *
 * This file contains the \ref image_display_api "Image Display Processing API".
 */

#ifndef _NVMEDIA_IDP_H
#define _NVMEDIA_IDP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_common.h"
#include "nvmedia_image.h"

/**
 * \defgroup image_display_api Image Display Processing (IDP)
 *
 * Displays \ref NvMediaImage type surfaces.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_IDP_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_IDP_VERSION_MINOR   0

/**
 * \brief Image display object created by \ref NvMediaIDPCreate.
 */
typedef struct {
    /*! Display device (head) Id */
    uint32_t displayId;
    /*! Display window Id */
    uint32_t windowId;
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaIDP;

/**
 * \brief Sets the preferences for the image display creation.
 *  Note: Depending on the display device type these preferences might not be met
 *  and the created display parameters might be different.
 */
typedef struct {
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaIDPPreferences;

/**
 * \brief Device parameters returned by \ref NvMediaIDPQuery function.
 */
typedef struct {
    /*! Display device Id */
    uint32_t displayId;
    /*! Set to NVMEDIA_TRUE if the device is already enabled (initialized) by the system */
    NvMediaBool enabled;
    /*! Display width */
    uint32_t width;
    /*! Display height */
    uint32_t height;
    /*! Display refresh rate in Hertz */
    float_t refreshRate;
} NvMediaIDPDeviceParams;

/**
 * \brief Gets the version compatibility for the NvMedia IDP library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaIDPGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an image display object
 * \param[in] displayId Display id (head) of the device.
 * \param[in] windowId Specifies the h/w overlay window to access.
 *            ex:  (windowId = 0) == (Overlay Window A). Valid values are 0 (A), 1 (B), 2 (C).
 * \param[in] displayPreference Desired display parameters. To use defaults set it to NULL.
 * \param[in] alreadyCreated Set to \ref NVMEDIA_TRUE if the dislpay is already created (initialized)
 *            by another application. In this case NvMedia is not going to create a new one
 *            just reuse it.
 * \return \ref NvMediaIDP The new image display's handle or NULL if unsuccessful.
 *            The width, hight and refreshRate members reflect the actual display parameter values.
 */
NvMediaIDP *
NvMediaIDPCreate(
    uint32_t displayId,
    uint32_t windowId,
    NvMediaIDPPreferences *displayPreference,
    NvMediaBool alreadyCreated
);

/**
 * \brief Destroy an image display object created by \ref NvMediaIDPCreate.
 * \param[in] idp The display to be destroyed.
 * \return void
 */
void
NvMediaIDPDestroy(
    NvMediaIDP *idp
);

/** \brief Set \ref NvMediaIDP attributes.
 *
 * \param[in] idp Image display object
 * \param[in] attributeMask Determines which attributes are set. The value
 *       can be any combination of the binary OR of the following attributes:
 * \n \ref NVMEDIA_DISP_ATTR_BRIGHTNESS
 * \n \ref NVMEDIA_DISP_ATTR_CONTRAST
 * \n \ref NVMEDIA_DISP_ATTR_SATURATION
 * \n \ref NVMEDIA_DISP_ATTR_HUE
 * \n \ref NVMEDIA_DISP_ATTR_COLOR_STANDARD
 * \n \ref NVMEDIA_DISP_ATTR_LIMITED_RGB
 * \n \ref NVMEDIA_DISP_ATTR_COMPOSITION
 * \n \ref NVMEDIA_DISP_ATTR_SET_DEPTH
 * \param[in] attributes A pointer to a structure that holds all the
 *        attributes but only those are used which are indicated in the
 *        attributeMask.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameters is invalid.
 */

NvMediaStatus
NvMediaIDPSetAttributes(
    NvMediaIDP *idp,
    uint32_t attributeMask,
    NvMediaDispAttributes *attributes
);

/**
 * \brief Queries the display system and returns the parameters of all display devices.
 *        If displayParams is NULL then only displayDevices is returned and this way the
 *        client can query the number of devices, allocate memory for the descriptors
 *        and call this function again with the properly allocated displayParams buffer.
 * \param[out] displayDevices Set by the function to the number of display devices.
 * \param[out] displayParams This parameters is used as an array and the function
 *             fills it up with displayDevices number of entries. It is the client's
 *             responsibility to allocate sufficient memory. If NULL no data is returned.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaIDPQuery(
    int32_t *displayDevices,
    NvMediaIDPDeviceParams *displayParams
);

/**
 * \brief Displays an image on the display device.
 * \param[in] idp The display device object.
 * \param[in] image The image to be displayed.
 * \param[in] srcRect Source rectangle. If NULL, a rectangle of the full size of the \ref NvMediaImage
 *        is implied.
 * \param[in] dstRect Destination rectangle on the display. If NULL, a rectangle of the full size of
 *        the display device is implied.
 *       <b> Note: </b> Scaling is not supported for RGB type images and dstRect acts as a crop rectangle.
 * \param[in] releaseList Points to an array of \ref NvMediaImage pointers filled by this
 *       function and terminated with NULL.
 *       When \ref NvMediaIDPFlip function is called it might need to use some of the
 *       input images for a longer time depending on the pipelining model.
 *       When the images are no longer needed they are released using this list.
 *       It is the application responsibility to allocate the memory for the list.
 *       The maximum size of the list is 2 including the one for the NULL terminator.
 * \param[in] timeStamp Determines when the image is going to be displayed.
 *       This is a pointer to the time structure. NULL means the image
 *       is displayed as soon as possible.
 * \return \ref NvMediaStatus Status of the display flip operation. Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaIDPFlip(
    NvMediaIDP *idp,
    NvMediaImage *image,
    NvMediaRect *srcRect,
    NvMediaRect *dstRect,
    NvMediaImage **releaseList,
    NvMediaTime *timeStamp
);

/*
 * \defgroup history_nvmedia_idp History
 * Provides change history for the NvMedia IDP API.
 *
 * \section history_nvmedia_idp Version History
 *
 * <b> Version 1.1 </b> September 24, 2015
 * - Initial release
 *
 * <b> Version 1.2 </b> May 11, 2016
 * - Added \ref NvMediaIDPCheckVersion API
 *
 * <b> Version 2.0 </b> May 12, 2017
 * - Added \ref NvMediaIDPGetVersion API to get the version of NvMedia image display library
 * - NvMediaIDPCheckVersion is deprecated. Use NvMediaIDPGetVersion() instead
 * - Remove NvMediaIDPDeviceType
 * - Remove imageType as input parameter of \ref NvMediaIDPCreate
 * - Replace NvMediaIDPCompositionModes with \ref NvMediaDispCompMode
 * - Replace NvMediaIDPAttributes with \ref NvMediaDispAttributes
 * - Deprecated NvMediaIDPSetDepth, use NvMediaIDPSetAttributes with
 *   NVMEDIA_DISP_ATTR_SET_DEPTH instead
 * - All NvMedia data types are moved to standard data types
 */
/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IDP_H */
