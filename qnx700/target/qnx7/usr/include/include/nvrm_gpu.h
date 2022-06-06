/*
 * Copyright (c) 2014-2018 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef INCLUDED_nvrm_gpu_H
#define INCLUDED_nvrm_gpu_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "nvcommon.h"
#include "nverror.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * \file
 * \brief <b> NVIDIA Resource Manager: Discrete GPU</b>
 *
 * @b Description: This file contains a resource manager API
 *    for GPU clock controls.
 */

 /**
 * @defgroup nvrm_gpu_group GPU Resource Manager API
 *
 * Manages GPU resources.
 * For related information, see
 * <a href="../Clock Freq and Thermal/discrete_GPU.html" target="_blank">
 * Discrete GPU</a> in the _Development Guide_.
 *
 * General usage notes:
 *
 * - This library uses object-oriented design. In general, objects are referred by
 *   handles.
 *
 * - When destroying an object, the child objects are not destroyed by default.
 *   Additionally, it is an error to destroy a parent before its child.
 *
 * - In object creation, the attribute pointer (where applicable) can always be
 *   NULL, which indicates defaults.
 *
 * - In object creation, the first parameter specifies the parent. Some objects
 *   may be created for parents of different types.
 *
 * - Whenever a function that returns a new handle is invoked, the handle is
 *   guaranteed to be unique as well as the object it points to. There will be
 *   1-to-1 mapping between handles and objects.
 *
 * - It is a fatal error to provide unexpected handle type. That will produce
 *   either an assert (debug builds) or undefined behavior (release builds)
 *
 * - In general, the const pointers returned by functions are valid as long as
 *   the related object is valid, unless otherwise stated. And in particular,
 *   they shall not be free'd by the caller. For example, the device list
 *   returned by NvRmGpuLibListDevices() is valid until the lib handle is
 *   closed, and the device info struct returned by NvRmGpuDeviceGetInfo() is
 *   valid until the device is closed.
 *
 * - This library is thread-safe with the following rule: an object can be
 *   closed only if there are no concurrent operations on-going on
 *   it. Attempting to close an object during an on-going operation is a fatal
 *   error.
 * @{
 */


/** Handle type. */
typedef struct NvRmGpuLibRec NvRmGpuLib;
/** Handle type. */
typedef struct NvRmGpuDeviceRec NvRmGpuDevice;

/**** Generic functions ****/

typedef struct NvRmGpuLibOpenAttrRec
{
    // placeholder for extensions
    uint32_t reserved;

} NvRmGpuLibOpenAttr;

#define NVRM_GPU_DEFINE_LIB_OPEN_ATTR(x) \
    NvRmGpuLibOpenAttr x = { 0 }

/**
 * Opens a new instance of the library. There can be multiple concurrent
 * instances.
 */
NvRmGpuLib *NvRmGpuLibOpen(const NvRmGpuLibOpenAttr *attr);

/**
 * Closes the library and releases all resources.
 */
void NvRmGpuLibClose(NvRmGpuLib *hlib);

typedef enum
{
    NvRmGpuLibDeviceState_Detached,
    NvRmGpuLibDeviceState_Attached,
} NvRmGpuDeviceState;

typedef struct NvRmGpuLibDeviceListEntryRec
{
    int deviceIndex;
    NvRmGpuDeviceState deviceState;
    const char *name; // temporary name, e.g., Nouveau GPU 0 or some such
} NvRmGpuLibDeviceListEntry;

/**
 * Returns a pointer to the device array. The size of the array is returned in
 * pnumDevices. pnumDevices must be non-NULL.
 *
 * The returned pointer is valid until the library is closed. The caller must
 * not attempt to free the pointer.
 *
 * Remarks:
 * - The first device listed will always be considered the primary GPU.
 * - The device index numbers returned will be non-negative, unique and in
 *   ascending order. Numbering may be discontiguous, and specifically, the
 *   index numbers will likely not start at 0.
 * - Negative index numbers are reserved for pseudo indexes used by
 *   NvRmGpuDeviceOpen().
 */
const NvRmGpuLibDeviceListEntry *NvRmGpuLibListDevices(NvRmGpuLib *hlib, size_t *pnumDevices);

/**
 * Power up and attach a GPU.
 * hlib: handle to nvrm gpu lib.
 * deviceIndex: GPU device index.
 *
 * Returns NvSuccess on a succesful GPU attach. Returns NvError otherwise.
 */
NvError NvRmGpuLibAttachDevice(NvRmGpuLib *const hlib, const int deviceIndex);

/**
 * Detach and power down a GPU.
 * hlib: handle to nvrm gpu lib.
 * deviceIndex: GPU device index.
 *
 * Returns NvSuccess on a succesful GPU power-off. Returns NvError otherwise.
 */
NvError NvRmGpuLibDetachDevice(NvRmGpuLib *const hlib, const int deviceIndex);

/**** Device functions ****/

#define NVRM_GPU_DEVICE_INDEX_DEFAULT (-1)

typedef enum
{
    NvRmGpuSyncType_Default,       // platform-specific default
    NvRmGpuSyncType_SyncFd,
    NvRmGpuSyncType_Syncpoint,
} NvRmGpuSyncType;

typedef struct NvRmGpuDeviceOpenAttrRec
{
    /**
     * The default sync type for all input/output sync objects. Note: It is a
     * fatal error (i.e., assert or undefined operation) for the client to set
     * an unsupported sync type. In the long run, default should be okay for
     * anyone, but in the meanwhile, the caller - unfortunately - must do some
     * build-time magic in case the default is not supported everywhere in the
     * stack. */
    NvRmGpuSyncType syncType;

    /**
     * If true, channels are created in sandbox-friendly manner. Effectively,
     * this means that necessary steps are taken so that opening a channel does
     * not require access to device files. However, this may mean that extra
     * resources are consumed per device. Note that opening a device or an
     * address space may still require filesystem access. */
    bool sandboxFriendlyChannels;
} NvRmGpuDeviceOpenAttr;

#define NVRM_GPU_DEFINE_DEVICE_OPEN_ATTR(x) \
    NvRmGpuDeviceOpenAttr x = { NvRmGpuSyncType_Default, false }


/**
 * Opens the GPU device.
 *
 * @note Do not assume that the device indexes are sequential and start from
 * zero. Use the NVRM_GPU_DEVICE_INDEX_DEFAULT for the primary GPU when the
 * system has more than one GPU.
 * @note Only attached GPUs can be opened. A detached GPU can be attached
 * with help of NvRmGpuLibAttachDevice(deviceIndex).
 */
NvError NvRmGpuDeviceOpen(NvRmGpuLib *hLib, int deviceIndex, const NvRmGpuDeviceOpenAttr *attr,
                          NvRmGpuDevice **phDevice);

/**
 * Closes the GPU device.
 */
void NvRmGpuDeviceClose(NvRmGpuDevice *hDevice);

/**
 * NvRmGpuDevice subinterface for application-driven GPU clock frequency management.
 *
 *  - The lifespan of GPU clock requests is tied to the @ref NvRmGpuDevice instance.
 *    All requests are canceled when the NvRmGpuDevice handle is closed.
 *
 *  - The clock requests of all NvRmGpuDevice instances are coalesced.
 *    Generally, given that thermal and power limits are not exceeded, the
 *    actual clock frequency will be at least the greatest requested. The exact
 *    selection algorithm depends on the global clock management driver policy.
 *    The selection algorithm is run by the "clock arbiter".
 *
 *  - Each clock domain has VF points, defined as frequencies for which voltage is
 *    optimal. The clock arbiter will try to program frequencies which correspond to
 *    VF points.
 *
 *  - A single clock request can set target frequencies for multiple clock domains
 *
 *  - Clock requests can be either synchronous or asynchronous. In asynchronous mode
 *    a request handle is allocated and can be used to wait for request completion.
 *    This request handle must be freed by application.
 *
 *  - It is possible to wait for any clock change event, in order to detect clock
 *    changes that originated from other applications or thermal conditions.
 *
 */

#if NVOS_IS_LINUX || NVOS_IS_QNX
#define NVRM_GPU_CLOCK_ASYNC_REQ_HANDLE_PRIFMT "d"
typedef int NvRmGpuClockAsyncReqHandle;
#else
#define NVRM_GPU_CLOCK_ASYNC_REQ_HANDLE_PRIFMT "p"
typedef struct NvRmGpuClockAsyncNotImplemented *NvRmGpuClockAsyncReqHandle;
#endif

/**
 * Clock domains
 */
typedef enum NvRmGpuClockDomain
{
    NvRmGpuClockDomain_MCLK = 0,    ///< Memory clock
    NvRmGpuClockDomain_GPCCLK,      ///< Main graphics core clock
    NvRmGpuClockDomain_Count
} NvRmGpuClockDomain;

typedef enum NvRmGpuClockType
{
    NvRmGpuClockType_Target = 1,    ///< Target clock frequency requested by application
    NvRmGpuClockType_Actual,        ///< Actual clock frequency programmed (including PLL constraints).
    NvRmGpuClockType_Effective      ///< Effective clock, measured from hardware
} NvRmGpuClockType;

typedef struct NvRmGpuClockGetEntryRec
{
    NvRmGpuClockDomain domain;      ///< in: Clock domain to query
    NvRmGpuClockType type;          ///< in: Frequency type (target, actual or effective)
    uint64_t freqHz;                ///< out: Frequency in Hz
} NvRmGpuClockGetEntry;

typedef struct NvRmGpuClockSetEntryRec
{
    NvRmGpuClockDomain domain;
    uint64_t freqHz;
} NvRmGpuClockSetEntry;

typedef struct NvRmGpuClockRangeRec
{
    uint64_t minHz;
    uint64_t maxHz;
} NvRmGpuClockRange;

typedef struct NvRmGpuClockPointRec
{
    uint64_t freqHz;
} NvRmGpuClockPoint;

typedef struct NvRmGpuClockDomainInfoRec
{
    NvRmGpuClockDomain domain;
    NvRmGpuClockRange range;
    size_t maxVfPoints;
} NvRmGpuClockDomainInfo;

/**
 * Gets configurable clock domains.
 *
 * @param[in] hDevice GPU device handle.
 * @param[out] infos Array of configurable clock domains. This list is valid
 *                   only during the life-time of the @a hDevice handle.
 * @param[out] pNumDomains Number of domains in array.
 *
 * @return NvSuccess indicates that request was successful.
 */
NvError NvRmGpuClockGetDomains(NvRmGpuDevice *hDevice,
                               const NvRmGpuClockDomainInfo **infos,
                               size_t *pNumDomains);

/**
 * Gets VF points for a given clock domain.
 * For information about VF points, see @ref NvRmGpuClockAsyncReqHandle.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] domain Clock domain to query.
 * @param[in,out] pClkPoints Array of optimal Voltage/Frequency points.
 *        The allocated array must contain space for at least
 *        NvRmGpuClockDomainInfo::maxVfPoints (as retrieved by
 *        NvRmGpuClockGetDomains())
 * @param[out] pNumPoints Number of VF points. May vary depending on thermal
 *        conditions, and be lower than maxPoints.
 *
 * @return NvSuccess indicates that request was successful.
 */
NvError NvRmGpuClockGetPoints(NvRmGpuDevice *hDevice,
                              NvRmGpuClockDomain domain,
                              NvRmGpuClockPoint *pClkPoints,
                              size_t *pNumPoints);

/**
 * Sets a clock request.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] pClkSetEntries Array of entries. Each entry specifies target
 *        frequency for one clock domain. If a clock domain appears multiple
 *        times, then only last entry will be taken into account.
 * @param[in] numEntries Number of entries in the @a pClkSetEntries array.
 * @param[in,out] phReq A pointer to request handle.
 *       - (in) If NULL, the request is synchronous and function waits
 *        until all clocks are programmed.
 *        Otherwise, the request is asynchronous and is assigned a
 *        request handle. The application may wait for asynchronous request
 *        completion using NvRmGpuClockWaitAsync(). The request handle MUST
 *        be freed by the application using NvRmGpuClockCloseAsyncReq().
 *        - (out) The request handle that was assigned to this asynchronous request.
 *
 * @return NvSuccess indicates that the request has completed in the
 *         synchronous case, and that the request was successfully submitted
 *         in the asynchronous case.
 *         NvError_Busy indicates that an asynchronous request could
 *         not be submitted, and application should try again.
 *
 * @note
 *  - A subsequent clock request to a domain supersedes the previous request
 *
 *  - Actual frequency might differ depending on global policies, requests
 *    from other NvRmGpuDevice instances, or thermal conditions.
 *
 *  - If specified target frequency is not a VF point, clock arbiter will
 *    try to program the clocks with first VF point that is greater than or
 *    equal to specified target frequency (assuming a single application)
 *
 *  - All clock requests will be cancelled when hDevice is closed.
 */
NvError NvRmGpuClockSet(NvRmGpuDevice *hDevice,
                        const NvRmGpuClockSetEntry *pClkSetEntries,
                        size_t numEntries,
                        NvRmGpuClockAsyncReqHandle *phReq);

/**
 * Waits for completion of one or more asynchronous requests.
 *
 * @param hDevice GPU device handle.
 * @param phReqs Array of request handles.
 * @param numEntries Number of entries in array.
 * @param timeoutMs Timeout value in milliseconds. Set this value as follows:
 *        - `timeoutMs = <positive integer>` for time-limited polling, where the function returns
 *           when the request completes or when the timeout expires, whichever comes first.
 *        - `timeoutMs = 0` specifies open-ended polling, where the function returns
 *           only when the request has completed.
 *
 * @return NvSuccess indicates that requests have completed.
 *         NvError_Timeout indicates that timeout was reached.
 */
NvError NvRmGpuClockWaitAsyncReq(NvRmGpuDevice *hDevice,
                                 const NvRmGpuClockAsyncReqHandle *phReqs,
                                 size_t numEntries,
                                 uint32_t timeoutMs);

/**
 * Closes an asynchronous request handle.
 *
 * Frees all resources related to an asynchronous request. It is not mandatory
 * to wait for request completion, before closing the handle.
 *
 * @param hDevice GPU device handle.
 * @param hReq Request handle obtained from NvRmGpuClockSet.
 *
 * @return NvSuccess indicates that handle was closed.
 */
NvError NvRmGpuClockCloseAsyncReq(NvRmGpuDevice *hDevice,
                                  NvRmGpuClockAsyncReqHandle hReq);

/**
 * Waits on any clock update event.
 *
 * @param hDevice GPU device handle
 * @param timeoutMs Timeout value in milliseconds.
 *        @c NV_WAIT_INFINITE for no timeout.
 *
 * @return NvSuccess indicates that we received a clock change event.
 *         NvError_Timeout indicates that timeout was reached.
 *
 * @note If several clock changes occurred between two calls to this
 *       function, then a single event will be reported.
 */
NvError NvRmGpuClockWaitAnyEvent(NvRmGpuDevice *hDevice,
                                 uint32_t timeoutMs);

/**
 * Gets clock state(s).
 *
 * @param[in] hDevice GPU device handle
 * @param[out] pClkGetEntries Array of clock entries. For each entry, the clock
 *        domain and clock types MUST be set, and the associated frequency
 *        will be returned on a successful call. It is allowed to mix several
 *        clocks domains and clock types in the same request.
 * @param[out] numEntries Number of entries to query
 *
 * @return NvSuccess indicates that request was successful.
 */
NvError NvRmGpuClockGet(NvRmGpuDevice *hDevice,
                        NvRmGpuClockGetEntry *pClkGetEntries,
                        size_t numEntries);

/**
 * Gets gpu load.
 *
 * @param[in] hDevice GPU device handle
 * @param[out] pLoad GPU load in permille
 *
 * @return NvSuccess indicates that request was successful.
 */
NvError NvRmGpuDeviceGetLoad(NvRmGpuDevice *hDevice,
                              uint32_t *pLoadPerMille);

typedef enum
{
    NvRmGpuDeviceVoltage_Core = 1,
    NvRmGpuDeviceVoltage_SRAM,
    NvRmGpuDeviceVoltage_Bus
} NvRmGpuDeviceVoltage;

/**
 * Gets a list of the available voltage sensors.
 *
 * @param[in] hDevice GPU device handle
 * @param[out] pSensors List of available sensors (may be NULL if no
 *                   sensor is available)
 * @param[out] numSensors Number of sensors available
 *
 * @return: NvSuccess on successful operation.
 */
NvError NvRmGpuDeviceListVoltageSensors(NvRmGpuDevice *hDevice,
                                        const NvRmGpuDeviceVoltage **pSensors,
                                        size_t *numSensors);
/**
 * Gets the current voltage.
 *
 * @param[in] hDevice GPU device handle
 * @param[in] which The voltage to query
 * @param[out] pVoltageMicroVolt Voltage in microvolts.
 *
 * @return: NvSuccess or NvError_NotSupported
 */
NvError NvRmGpuDeviceGetVoltage(NvRmGpuDevice *hDevice,
                                NvRmGpuDeviceVoltage which,
                                uint64_t *pVoltageMicroVolt);

typedef enum
{
    NvRmGpuDeviceCurrent_Bus = 1,
} NvRmGpuDeviceCurrent;

/**
 * Gets a list of the available current sensors.
 *
 * @param[in] hDevice GPU device handle.
 * @param[out] pSensors List of available sensors (may be NULL if no
 *                   sensor is available).
 * @param[out] numSensors Number of sensors available.
 *
 * @return: NvSuccess on successful operation.
 */
NvError NvRmGpuDeviceListCurrentSensors(NvRmGpuDevice *hDevice,
                                        const NvRmGpuDeviceCurrent **pSensors,
                                        size_t *numSensors);

/**
 * Gets the current drawn by the GPU.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] which The current to query.
 * @param[out] pCurrentMicroAmpere Current in microamperes.
 *
 * @return: NvSuccess or NvError_NotSupported
 */
NvError NvRmGpuDeviceGetCurrent(NvRmGpuDevice *hDevice,
                                NvRmGpuDeviceCurrent which,
                                uint64_t *pCurrentMicroAmpere);

typedef enum
{
    NvRmGpuDevicePower_Bus = 1  // power consumed at regulator
} NvRmGpuDevicePower;

/**
 * Gets a list of the available power sensors.
 *
 * @param[in] hDevice GPU device handle.
 * @param[out] pSensors List of available sensors (may be NULL if no
 *                   sensor is available).
 * @param[out] numSensors Number of sensors available.
 *
 * @return: NvSuccess on successful operation.
 */
NvError NvRmGpuDeviceListPowerSensors(NvRmGpuDevice *hDevice,
                                      const NvRmGpuDevicePower **pSensors,
                                      size_t *numSensors);

/**
 * Gets the power consumed by the GPU.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] which The Power to query.
 * @param[out] pPowerMicroWatt Power in microwatts.
 *
 * @return: NvSuccess or NvError_NotSupported.
 */
NvError NvRmGpuDeviceGetPower(NvRmGpuDevice *hDevice,
                              NvRmGpuDevicePower which,
                              uint64_t *pPowerMicroWatt);


typedef enum
{
    NvRmGpuDeviceTemperature_InternalSensor = 1
} NvRmGpuDeviceTemperature;

/**
 * Gets the list of available temperature sensors.
 *
 * @param[in] hDevice GPU device handle
 * @param[out] pSensors List of available sensors (may be NULL if no
 *                   sensor is available).
 * @param[out] numSensors Number of sensors available.
 *
 * @return: NvSuccess on successful operation.
 */
NvError NvRmGpuDeviceListTemperatureSensors(NvRmGpuDevice *hDevice,
                                            const NvRmGpuDeviceTemperature **pSensors,
                                            size_t *numSensors);

/**
 * Gets the temperature.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] which Temperature sensor to query.
 * @param[out] pTemperatureMilliCelsius Temperature in millidegrees Celsius.
 *
 * @return: NvSuccess or NvError_NotSupported
 */
NvError NvRmGpuDeviceGetTemperature(NvRmGpuDevice *hDevice,
                                    NvRmGpuDeviceTemperature which,
                                    int32_t *pTemperatureMilliCelsius);

/**
 * Sets the thermal alert limit.
 *
 * @param hDevice GPU device handle.
 * @param temperature_mC Thermal temperature alert limit value in millidegrees Celsius.
 *
 * @return NvSuccess indicates that request was successful.
 */
NvError NvRmGpuDeviceThermalAlertSetLimit(NvRmGpuDevice *hDevice,
                                          int32_t temperature_mC);

/** Holds information about the GPU device event. */
typedef enum
{
    /// VF update occurred for a clock domain, either because one session changed
    /// target frequency or because of thermal or power conditions.
    NvRmGpuDeviceEventId_VfUpdate = 0,
    /// One clock domain frequency is below target.
    NvRmGpuDeviceEventId_AlarmTargetVfNotPossible,
    /// One clock domain frequency is below local target frequency requested by one session.
    NvRmGpuDeviceEventId_AlarmLocalTargetVfNotPossible,
    /// Clock Arbiter failed.
    NvRmGpuDeviceEventId_AlarmClockArbiterFailed,
    /// Vf table update failed.
    NvRmGpuDeviceEventId_AlarmVfTableUpdateFailed,
    /// Temperature above threshold.
    NvRmGpuDeviceEventId_AlarmThermalAboveThreshold,
    /// Power above threshold.
    NvRmGpuDeviceEventId_AlarmPowerAboveThreshold,
    /// GPU lost (non-recoverable).
    NvRmGpuDeviceEventId_AlarmGpuLost,
    /// Number of events.
    NvRmGpuDeviceEventId_Count
} NvRmGpuDeviceEventId;

typedef struct NvRmGpuDeviceEventSessionRec NvRmGpuDeviceEventSession;

/// Holds the events for which to listen.
typedef struct NvRmGpuDeviceEventSessionOpenAttrRec
{
    /// Holds the events for which to listen.
    const NvRmGpuDeviceEventId *filterList;
    /// Holds the size of the filter list.
    size_t filterListSize;
} NvRmGpuDeviceEventSessionOpenAttr;

#define NVRM_GPU_DEFINE_DEVICE_EVENT_SESSION_ATTR(x)            \
    NvRmGpuDeviceEventSessionOpenAttr x = { NULL, 0 }

static inline void NvRmGpuDeviceEventSessionOpenAttrSetAllEvents(NvRmGpuDeviceEventSessionOpenAttr *attr)
{
    static const NvRmGpuDeviceEventId allEvents[] =
    {
        NvRmGpuDeviceEventId_VfUpdate,
        NvRmGpuDeviceEventId_AlarmTargetVfNotPossible,
        NvRmGpuDeviceEventId_AlarmLocalTargetVfNotPossible,
        NvRmGpuDeviceEventId_AlarmClockArbiterFailed,
        NvRmGpuDeviceEventId_AlarmVfTableUpdateFailed,
        NvRmGpuDeviceEventId_AlarmThermalAboveThreshold,
        NvRmGpuDeviceEventId_AlarmPowerAboveThreshold,
        NvRmGpuDeviceEventId_AlarmGpuLost
    };
    attr->filterList = allEvents;
    attr->filterListSize = NV_ARRAY_SIZE(allEvents);
}

/**
 * Opens the session to monitor device events.
 *
 * @param[in] hDevice GPU device handle.
 * @param[in] attr Event session attributes, including event filter.
 * @param[out] phSession A pointer to the event session handle.
 *
 * @return NvSuccess if event session could be created.
 */
NvError NvRmGpuDeviceEventSessionOpen(NvRmGpuDevice *hDevice,
                                      const NvRmGpuDeviceEventSessionOpenAttr *attr,
                                      NvRmGpuDeviceEventSession **phSession);

typedef struct NvRmGpuDeviceEventInfoRec
{
    NvRmGpuDeviceEventId eventId;
    uint64_t timeNs;    // GPU timestamp in ns
} NvRmGpuDeviceEventInfo;

/**
 * Reads detailed event information from the event session.
 *
 * @param[in] hSession Event session handle
 * @param[out] pEventInfo Detailed event information
 * @param[in] timeoutMs Timeout value in milliseconds.
 *     NVRM_GPU_CLK_WAIT_INFINITE to wait infinitely.
 *
 * @return NvSuccess indicates that one event occurred, and detailed
 *         information has been updated in @a pEventInfo.
 *         NvError_Timeout indicates that timeout was reached.
 *
 * @note If several identical events occur between two calls to this function,
 *       then a single event will be reported. After this call, related event
 *       information is cleared.
 */
NvError NvRmGpuDeviceEventSessionRead(NvRmGpuDeviceEventSession *hSession,
                                      NvRmGpuDeviceEventInfo *pEventInfo,
                                      uint32_t timeoutMs);

/**
 * Closes the event session.
 *
 * @param hSession Event session handle
 *
 * @return NvSuccess on successful operation.

 */
void NvRmGpuDeviceEventSessionClose(NvRmGpuDeviceEventSession *hSession);

/** @} */

#if defined(__cplusplus)
}
#endif

#if !defined(NV_SDK_BUILD)
#include "nvrm_gpu_priv.h"
#endif

#endif
