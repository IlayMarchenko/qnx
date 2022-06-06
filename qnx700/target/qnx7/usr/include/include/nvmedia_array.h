/*
 * Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */


/**
 * \file
 * \brief <b> NVIDIA Media Interface: Arrays </b>
 *
 * @b Description: This file contains the API to access 1 dimensional arrays managed by
 *                 NvMedia used in multimedia applications.
 */

#ifndef _NVMEDIA_ARRAY_H
#define _NVMEDIA_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"

/**
 * \defgroup array_api NvMedia Array
 *
 * The NvMedia Array API encompasses all NvMedia
 * functions that create, destroy, access and update arrays
 * used in media processing and computer vision applications.
 *
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_ARRAY_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_ARRAY_VERSION_MINOR   1

/**
 * \hideinitializer
 * \brief Infinite time-out for \ref NvMediaArrayGetStatus.
 */
#define NVMEDIA_ARRAY_TIMEOUT_INFINITE  0xFFFFFFFF

/** \brief Defines the different types of Arrays.
 */
typedef enum {
    /*! Undefined array type. */
    NVMEDIA_ARRAY_TYPE_UNDEFINED = 0,
    /*! Signed 8 bit.*/
    NVMEDIA_ARRAY_TYPE_INT8 = 1,
    /*! Unsigned 8 bit.*/
    NVMEDIA_ARRAY_TYPE_UINT8 = 2,
    /*! Signed 16 bit.*/
    NVMEDIA_ARRAY_TYPE_INT16 = 3,
    /*! Unsigned 16 bit.*/
    NVMEDIA_ARRAY_TYPE_UINT16 = 4,
    /*! Float 16 bit.*/
    NVMEDIA_ARRAY_TYPE_FLOAT16 = 5,
    /*! Unsigned 32 bit.*/
    NVMEDIA_ARRAY_TYPE_UINT32 = 6,
    /*! Signed 32 bit.*/
    NVMEDIA_ARRAY_TYPE_INT32 = 7,
    /*! Float 32 bit.*/
    NVMEDIA_ARRAY_TYPE_FLOAT32 = 8,
    /*! Number of types - If more types are needed, add above this and update this.*/
    NVMEDIA_ARRAY_NUM_TYPES = 8,
} NvMediaArrayType;

/**
 * \brief Holds a descriptor for the array.
 * Note: The array needs to be created and destroyed using the corresponding
 *       NvMediaArrayCreate() and NvMediaArrayDestroy() functions.
 */
typedef struct NvMediaArray NvMediaArray;

/**
 * \brief Defines NvMedia array allocation attribute types.
 */
typedef enum {
    /**! CPU access to surface flags (default: uncached) */
    NVM_ARRAY_ATTR_CPU_ACCESS,
} NvMediaArrayAllocAttrType;

/** \brief \ref NVM_SURF_ATTR_CPU_ACCESS flags
  */
/** Uncached (mapped) access type flag */
#define NVM_ARRAY_ATTR_CPU_ACCESS_UNCACHED 0x00000000
/** NVM_SURF_ATTR_CPU_ACCESS flag: Cached (mapped) access type flag */
#define NVM_ARRAY_ATTR_CPU_ACCESS_CACHED 0x00000001

/**
 * \brief Holds array allocation attributes.
 */
typedef struct {
    /** \brief Array Allocation Attribute Type */
    NvMediaArrayAllocAttrType type;
    /** \brief Array Allocation Attribute Value */
    uint32_t value;
} NvMediaArrayAllocAttr;

/**
 * \brief Defines array-lock access types.
 * \ingroup lock_unlock
 */
typedef enum {
    /** Read access */
    NVMEDIA_ARRAY_ACCESS_READ       = (1 << 0),
    /** Write access */
    NVMEDIA_ARRAY_ACCESS_WRITE      = (1 << 1),
    /** Read/Write access */
    NVMEDIA_ARRAY_ACCESS_READ_WRITE = (NVMEDIA_ARRAY_ACCESS_READ | NVMEDIA_ARRAY_ACCESS_WRITE),
} NvMediaArrayLockAccess;

/**
 * \brief Returns the version information for the NvMediaArray library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    filled by the NvMediaArray library.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaArrayGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an NvMedia Array.
 * \param[in] device Handle to the NvMedia device obtained by calling \ref NvMediaDeviceCreate.
 * \param[in] type \ref NvMediaArrayType Type of Array to be created.
 * \param[in] stride Stride in bytes of each element.
 * \param[in] numElements number of Elements in the array.
 * \param[in] attrs An array of \ref NvMediaArrayAllocAttr Allocation attributes.
 * \param[in] numAttrs Number of allocation objects @a attrs.
 * \return \ref NvMediaArray Handle to array. Null if unsuccessful.
 */
NvMediaArray *
NvMediaArrayCreate(
    NvMediaDevice *device,
    NvMediaArrayType type,
    uint32_t stride,
    uint32_t numElements,
    const NvMediaArrayAllocAttr *attrs,
    uint32_t numAttrs
);

/**
 * \brief Destroys an array created by NvMediaArrayCreate().
 * \param[in] handle The handle to the array to be destroyed.
 * \return \ref NvMediaStatus The status of the API.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument is NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaArrayDestroy(
    NvMediaArray* handle
);

/**
 * \brief Gets the size of an element, for a particular type of array element.
 * \param[in] type \ref NvMediaArrayType Type of element.
 * \param[out] elementSize Pointer to size of element in bytes.
 * \return \ref NvMediaStatus The status of the API.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER for invalid type, or NULL pointer.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaArrayGetElemSizeForType(
    NvMediaArrayType type,
    uint32_t *elementSize
);

/**
 * \brief Gets the size of the array.
 *        An array's size is the number of populated elements in the array.
 *        If the array has not been written to,
 *        the function sets \a *numElementsPtr to 0.
 * \param[in] handle The handle to the array.
 * \param[out] numElementsPtr Pointer to the number of valid elements.
 * \return \ref NvMediaStatus The status of the API.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument is NULL.
 * - \ref NVMEDIA_STATUS_ERROR if array is not locked.
 */
NvMediaStatus
NvMediaArrayGetSize(
    NvMediaArray* handle,
    uint32_t *numElementsPtr
);

/**
 * \brief Sets the size of the array.
 *        Call this function before writing to the array.
 *        The number of elements must be less than the number with which the
 *        array was created.
 *        An array's size is the number of populated elements in the array.
  * \sa NvMediaArrayCreate().
 * \param[in] handle The handle to the array.
 * \param[in] numElements Number of elements to set the size to.
 * \return \ref NvMediaStatus The status of the API.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if input argument is NULL.
 * - \ref NVMEDIA_STATUS_INVALID_SIZE if numElements is greater than initial size.
 * - \ref NVMEDIA_STATUS_ERROR if array is not locked.
 */
NvMediaStatus
NvMediaArraySetSize(
    NvMediaArray* handle,
    uint32_t numElements
);

/**
 * \brief Helper function to get array properties with which array was created.
 * \param[in] handle The handle to the array.
 * \param[out] elementType Type of elements \ref NvMediaArrayType.
 * \param[out] capacity Pointer to the capacity (Number of elements).
 * \param[out] stride Pointer to the stride (Stride in bytes to move to next element).
 * \return \ref NvMediaStatus The status of the API.
 * Possible return values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if any argument is NULL.
 * - \ref NVMEDIA_STATUS_ERROR for any other error.
 */
NvMediaStatus
NvMediaArrayGetProperties(
    NvMediaArray* handle,
    NvMediaArrayType* elementType,
    uint32_t* capacity,
    uint32_t* stride
);

/**
 * \brief Gets the status of the current/last operation for the Array
          and optionally waits for the operation to complete/timeout.
 * \param[in] handle The handle to the array.
 * \param[in] millisecondWait Time  in milliseconds to wait for operation to
              complete before getting status.
              \ref NVMEDIA_ARRAY_TIMEOUT_INFINITE means wait till operation is completed
              and then get status.
 * \param[out] status Status of the operation.
 * \return \ref NvMediaStatus The status of the function call.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_TIMED_OUT
 * - \ref NVMEDIA_STATUS_ERROR
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER
 */
NvMediaStatus
NvMediaArrayGetStatus(
    NvMediaArray *handle,
    uint32_t millisecondWait,
    NvMediaTaskStatus *status
);

/**
 * Locks an Array to which data can be written/read
 * without interference from another thread/process.
 * If the array is being used by an internal engine, this function waits until
 * the completion of this operation.
 *
 * \param[in] handle Handle to the array to be locked.
 * \param[in] lockAccessType Determines the access type.
 * \param[out] ptr CPU mapped pointer to which data can be read/written.
 * The following access types are supported and may be OR'd together:
 * - \ref NVMEDIA_ARRAY_ACCESS_READ Read access
 * - \ref NVMEDIA_ARRAY_ACCESS_WRITE Write access
 * - \ref NVMEDIA_ARRAY_ACCESS_READ_WRITE Read/Write access
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * - \ref NVMEDIA_STATUS_OK
 * - \ref NVMEDIA_STATUS_ERROR
 * \ingroup lock_unlock
 */
NvMediaStatus
NvMediaArrayLock(
    NvMediaArray *handle,
    NvMediaArrayLockAccess lockAccessType,
    void **ptr
);

/**
 * Unlocks an Array.
 * To be called after data has been written to it/read from it by client.
 * \param[in] handle Handle to the array to be unlocked.
 * \return void
 * \ingroup lock_unlock
 */
void
NvMediaArrayUnlock(
    NvMediaArray *handle
);

/*
 * \defgroup history_nvmedia_array History
 * Provides change history for the NvMedia Array API.
 *
 * \section history_nvmedia_arrays Version History
 *
 * <b> Version 1.0 </b> December 4, 2017
 * - Initial Release.
 *
 * <b> Version 2.0 </b> June 1, 2018
 * - Remove keypoint type. VPI-specific types are in VPI headers.
 *
 * <b> Version 2.1 </b> July 9, 2018
 * - Add version query API.
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif // _NVMEDIA_ARRAY_H
