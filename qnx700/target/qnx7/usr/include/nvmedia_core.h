/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */


/**
 * \file
 * \brief <b> NVIDIA Media Interface: Core </b>
 *
 * @b Description: This file contains the Core data types and API.
 */

#ifndef _NVMEDIA_CORE_H
#define _NVMEDIA_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdint.h>
#include <time.h>

#if !defined(__NVM_DEPRECATED__)
    #if defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 6)
        /*
         * deprecated as build time warnings to prompt developers to migrate
         * from older API to new one gradually. Should be removed once API
         * transition is done(ie: no warnings).
         */

        #pragma GCC diagnostic warning "-Wdeprecated-declarations"
        #define __NVM_DEPRECATED_MSG__(fmt) __attribute__((deprecated(fmt)))
    #else
        #define __NVM_DEPRECATED__
        #define __NVM_DEPRECATED_MSG__(fmt) __NVM_DEPRECATED__
    #endif
#else
    #define __NVM_DEPRECATED_MSG__(fmt) __NVM_DEPRECATED__
#endif

/**
 * \defgroup nvmedia_common_top Common Declarations
 * \ingroup nvmedia_top
 *
 * \brief Defines basic types used for video and images throughout the NvMedia API.
 */

/**
 * \defgroup basic_api_top Basic NvMedia Types and Structures
 * \ingroup nvmedia_common_top
 *
 * \brief Defines basic types used throughout the NvMedia API.
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_RELEASE_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_RELEASE_VERSION_MINOR   0

/** \brief Major Version number */
#define NVMEDIA_CORE_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_CORE_VERSION_MINOR   6

/** \hideinitializer \brief A true \ref NvMediaBool value */
#define NVMEDIA_TRUE  (0 == 0)
/** \hideinitializer \brief A false \ref NvMediaBool value */
#define NVMEDIA_FALSE (0 == 1)

/**
 * \brief A boolean value, holding \ref NVMEDIA_TRUE or \ref
 * NVMEDIA_FALSE.
 */
typedef uint32_t NvMediaBool;

/**
 * \brief Holds the media time (timespec as defined by the POSIX specification).
 */
typedef struct timespec NvMediaTime;

/**
 * \brief Media global time, measured in microseconds.
 */
typedef uint64_t NvMediaGlobalTime;

/** \brief Defines clock base for NvMediaTime.
 */
typedef enum {
/** \hideinitializer \brief PTP clock is used for base time calculation. */
    NVMEDIA_TIME_BASE_CLOCK_PTP = 0,
/** \hideinitializer \brief Kernel monotonic clock is used for base time calculation. */
    NVMEDIA_TIME_BASE_CLOCK_MONOTONIC,
/** \hideinitializer \brief User defined clock is used for base time calculation. */
    NVMEDIA_TIME_BASE_CLOCK_USER_DEFINED,
} NvMediaTimeBase;

/**
 * \brief Holds a constant RGBA color.
 *
 * @note the components are stored as float_t values in the
 * range 0.0...1.0 rather than format-specific integer values.
 * This allows NvMediaColor values to be independent from the exact
 * surface format(s) in use.
 */
typedef struct {
    /*! Red color component */
    float_t red;
    /*! Green color component */
    float_t green;
    /*! Blue color component */
    float_t blue;
    /*! Alpha color component */
    float_t alpha;
} NvMediaColor;

/** \brief Defines color standards.
 */
typedef enum {
/** \hideinitializer \brief ITU BT.601 color standard. */
    NVMEDIA_COLOR_STANDARD_ITUR_BT_601,
/** \hideinitializer \brief ITU BT.709 color standard. */
    NVMEDIA_COLOR_STANDARD_ITUR_BT_709,
/** \hideinitializer \brief SMTE 240M color standard. */
    NVMEDIA_COLOR_STANDARD_SMPTE_240M,
/** \hideinitializer \brief ITU BT.601 color standard extended range. */
    NVMEDIA_COLOR_STANDARD_ITUR_BT_601_ER,
/** \hideinitializer \brief ITU BT.709 color standard extended range. */
    NVMEDIA_COLOR_STANDARD_ITUR_BT_709_ER
} NvMediaColorStandard;

/**
 * \brief Holds a rectangular region of a surface.
 *
 * The co-ordinates are top-left inclusive, bottom-right
 * exclusive.
 *
 * The NvMedia co-ordinate system has its origin at the top-left
 * of a surface, with x and y components increasing right and
 * down.
 */
typedef struct {
    /*! Left X co-ordinate. Inclusive. */
    uint16_t x0;
    /*! Top Y co-ordinate. Inclusive. */
    uint16_t y0;
    /*! Right X co-ordinate. Exclusive. */
    uint16_t x1;
    /*! Bottom Y co-ordinate. Exclusive. */
    uint16_t y1;
} NvMediaRect;

/**
 * \brief Holds a location on a 2-dimensional object.
 */
typedef struct {
    /*! Horizontal location of the point */
    int32_t x;
    /*! Vertical location of the point */
    int32_t y;
} NvMediaPoint;

/**
 * \brief Holds a double precision location of a 2-dimensional object.
 */
typedef struct {
    /*! Horizontal location of the point */
    double_t x;
    /*! Vertical location of the point */
    double_t y;
} NvMediaPointDouble;

/**
 * \brief Holda a Region of Interest
 *
 * The co-ordinates are top-left inclusive, bottom-right
 * exclusive.
 *
 */
typedef struct {
    /** left column of a rectangle */
    int32_t left;
    /** top row of a rectangle */
    int32_t top;
    /** right column of a rectangle */
    int32_t right;
    /** bottom row of a rectangle */
    int32_t bottom;
} NvMediaROI;

/**
 * \hideinitializer
 * \brief The set of all possible error codes.
 */
typedef enum {
    /** \hideinitializer The operation completed successfully; no error. */
    NVMEDIA_STATUS_OK = 0,
    /** Bad parameter was passed. */
    NVMEDIA_STATUS_BAD_PARAMETER,
    /** Operation has not finished yet. */
    NVMEDIA_STATUS_PENDING,
    /** Operation timed out. */
    NVMEDIA_STATUS_TIMED_OUT,
    /** Out of memory. */
    NVMEDIA_STATUS_OUT_OF_MEMORY,
    /** Not initialized. */
    NVMEDIA_STATUS_NOT_INITIALIZED,
    /** Not supported. */
    NVMEDIA_STATUS_NOT_SUPPORTED,
    /** A catch-all error, used when no other error code applies. */
    NVMEDIA_STATUS_ERROR,
    /** No operation is pending. */
    NVMEDIA_STATUS_NONE_PENDING,
    /** Insufficient buffering. */
    NVMEDIA_STATUS_INSUFFICIENT_BUFFERING,
    /** Invalid size. */
    NVMEDIA_STATUS_INVALID_SIZE,
    /** Incompatible version. */
    NVMEDIA_STATUS_INCOMPATIBLE_VERSION,
    /** Operation is cancelled when the hardware is timed out. */
    NVMEDIA_STATUS_CANCELLED,
    /** Undefined state. */
    NVMEDIA_STATUS_UNDEFINED_STATE,
} NvMediaStatus;

/**
 * \brief Holds status of latest operation for NvMedia managed data structure.
 *
 * Data structures include images and arrays.
 */
typedef struct {
    /*! Holds actual status - \ref NvMediaStatus. */
    NvMediaStatus status;
    /*! Timestamp of end of operation. */
    uint64_t endTimestamp;
} NvMediaTaskStatus;

/**
 * \defgroup version_info_api Version Information
 *
 * Provides version information for the NvMedia library.
 * @{
 */

/**
 * Holds NvMedia Version information.
 */
typedef struct {
    /*! Major version */
    uint8_t major;
    /*! Minor version */
    uint8_t minor;
} NvMediaVersion;

/**
 * \brief Gets the release version information for the NvMedia library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                      to be filled by the function.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaReleaseGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Gets the core version information for the NvMedia library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                      to be filled by the function.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaCoreGetVersion(
    NvMediaVersion *version
);

/** @} <!-- Ends version_info_api Version Information sub-group -> */

/**
 * \defgroup device_api Device
 *
 * Manages NvMediaDevice objects, which are the root of the Nvmedia object
 * system.
 *
 * The NvMediaDevice is the root of the NvMedia object system. Using a
 * NvMediaDevice object, all other object types may be created. See
 * the sections describing those other object types for details
 * on object creation.
 * @{
 */

/**
 * \brief  An opaque handle representing a NvMediaDevice object.
 */
typedef void NvMediaDevice;

/**
 * \brief Creates an NvMediaDevice.
 * \return The new handle for the device, or NULL if unsuccessful.
 */
NvMediaDevice *
NvMediaDeviceCreate(
    void
);

/**
 * \brief Destroys an NvMediaDevice.
 * \param[in] device A pointer to the device to destroy.
 */
void
NvMediaDeviceDestroy(
    NvMediaDevice *device
);

/** @} <!-- Ends device_api Device sub-group -> */

/** @} <!-- Ends basic_api_top group Basic NvMedia Types and Structures --> */

/*
 * \defgroup history_nvmedia_core History
 * Provides change history for the NvMedia Common Types.
 *
 * \section history_nvmedia_core Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b> April 18, 2017
 * - NVMEDIA_VERSION_MAJOR is renamed to NVMEDIA_CORE_VERSION_MAJOR.
 * - NVMEDIA_VERSION_MINOR is renamed to NVMEDIA_CORE_VERSION_MINOR.
 * - NvMediaBool is now changed from "int" to "uint32_t" type.
 * - NvMediaRect is now changed from "unsigned short" to "uint16_t".
 * - All NvMedia data types are moved to standard data types from <stdint.h>
 * - NvMediaVersionInfo is now deprecated. Use module specific GetVersion()
     API to query the module versions.
 * - NvMediaGetVersionInfo is now deprecated. Use NvMediaCoreGetVersion()
     or NvMediaReleaseGetVersion()
 * - NvMediaCheckVersion is now deprecated. Applications are expected
     to check their version using above GetVersion() APIs.
 * - NVMEDIA_SET_VERSION macro is now deprecated.
 *
 * <b> Version 1.2 </b> May 4, 2017
 * - Added \ref NvMediaROI and \ref NvMediaTaskStatus.
 *
 * <b> Version 1.3 </b> May 17, 2017
 * - Added macros to generate build warnings for deprecated APIs
 * - Changed the size of \ref NvMediaPoint members
 *
 * <b> Version 1.4 </b> September 14, 2017
 * - Added \ref NvMediaTimeBase
 *
 * <b> Version 1.5 </b> December 12, 2017
 * - Deprecated the following palette related APIs:
 *   NvMediaPaletteCreate
 *   NvMediaPaletteDestroy
 *   NvMediaPaletteLoad
 *
 * <b> Version 1.6 </b> Sep 12, 2018
 * - Add \ref NvMediaPointDouble
 */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_CORE_H */
