/*
 * Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: CVScratchpad </b>
 *
 * @b Description: This file contains the API to access CVScratchpad managed by
 *                 NvMedia, which is used in media processing and computer
 *                 vision pipelines.
 */

#ifndef _NVMEDIA_CVSCRATCHPAD_H
#define _NVMEDIA_CVSCRATCHPAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"

/**
 * \defgroup cvscratchpad_api NvMedia CVScratchpad
 *
 * The NvMedia CVScratchpad API creates and destroys CVScratchpad objects for
 * use as scratch memory for internal operation in media processing and
 * computer vision pipelines.
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major version number */
#define NVMEDIA_CVSCRATCHPAD_VERSION_MAJOR 1
/** \brief Minor version number */
#define NVMEDIA_CVSCRATCHPAD_VERSION_MINOR 0

/** \brief Specifies the type of memory that is allocated
*/
typedef enum {
    /*! Specifies scratch memory allocated in CVSRAM. */
    NVMEDIA_SCRATCH_MEMORY_TYPE_CVSRAM = 0,
    /*! Specifies scratch memory allocated in DRAM. */
    NVMEDIA_SCRATCH_MEMORY_TYPE_DRAM = 1,
    /*! Specifies the number of memory types. */
        /* If more types are needed, add above this and update this. */
    NVMEDIA_SCRATCH_NUM_MEMORY_TYPES = 2,

} NvMediaCVScratchMemoryAllocationType;

/**
 * \brief Holds a descriptor for the CVScratchpad.
 * \note  The handle must be created and destroyed using
 *  NvMediaCVScratchpadCreate() and NvMediaCVScratchpadDestroy().
 */
typedef struct NvMediaCVScratchpad NvMediaCVScratchpad;

/**
 * \brief  Returns version information for the CVScratchpad component.
 * \param[in] version   A pointer to a structure to be filled with version
 *                      information.
 * \return  Status indicator.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if @a version was invalid.
 */
NvMediaStatus
NvMediaCVScratchpadGetVersion(
    NvMediaVersion *version
);

/**
 * \brief  Creates an NvMedia CVScratchpad handle.
 * \param[in] device        Handle to the NvMedia device returned by
 *                          NvMediaDeviceCreate().
 * \param[in] size          Size for the CVScratchpad allocation in bytes.
 *                          Value must be in the range [1,4096].
 * \param[in] memoryType    Type of memory to be allocated.
 * \return  A handle to the allocated CVScratchpad, or NULL if the operation
 *          was unsuccessful.
 */
NvMediaCVScratchpad *
NvMediaCVScratchpadCreate(
    NvMediaDevice *device,
    uint32_t size,
    NvMediaCVScratchMemoryAllocationType memoryType
);

/**
 * \brief  Destroys a CVScratchpad handle created by
 *  NvMediaCVScratchpadCreate().
 * \param[in] handle        The handle to the CVScratchpad to be destroyed.
 * \return   Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid or NULL.
 */
NvMediaStatus
NvMediaCVScratchpadDestroy(
    NvMediaCVScratchpad *handle
);

/**
 * \brief  Gets the size in bytes and memory location type of a CVScratchpad.
 *
 * \param[in] handle        Handle to a CVScratchpad.
 * \param[out] size         A pointer to a location in which to store the size
 *                          of the CVScratchpad.
 * \param[out] memoryType   A pointer to a location in which to store the type
 *                          of memory used.
 * \return  Status indicator.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK if the operation was successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument was invalid or NULL.
 */
NvMediaStatus
NvMediaCVScratchpadGetProperties(
    NvMediaCVScratchpad *handle,
    uint32_t *size,
    NvMediaCVScratchMemoryAllocationType *memoryType
);

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif // _NVMEDIA_CVSCRATCHPAD_H
