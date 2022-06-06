/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVTIME_H__
#define __NVTIME_H__
#include <inttypes.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * \file
 * \brief <b> NVIDIA NvTime API</b>
 */

/** @defgroup nvtime_group NvTime API
 * Accesses high resolution time on QNX.
 * Based on the platform, this time may be synced with some time master.
 * @ingroup qnx_lib_group
 * @{
 */

/** Gets monotonic time with a resolution of 32 MHz */
int32_t nvtime_gettime_mono(struct timespec *time);

/** Gets real system time with a resolution of 32 MHz */
int32_t nvtime_gettime_real(struct timespec *time);

/**
 * Sets the system time and also the high resolution time returned
 * by nvtime_gettime().
 */
int32_t nvtime_settime(struct timespec *time);

/** Tells NvTime to look for a remote PTP instance */
int32_t nvtime_enable_virtual_ptp(void);

/** Nvtime PPS interface APIs */

/* evt_mode */
#define NVPPS_MODE_GPIO     0x01
#define NVPPS_MODE_TIMER    0x02

/* tsc_mode */
#define NVPPS_TSC_NSEC      0
#define NVPPS_TSC_COUNTER   1

typedef enum
{
    NVTIME_CALLBACK_EVENT_EVENT_AVAIL,
} nvtime_ppsCbEvent;

typedef void (*nvtime_ppsCbFuncPtr) (nvtime_ppsCbEvent eEvent);

typedef void *nvtime_ppsHandle;

struct nvtime_params
{
    uint32_t evt_mode;
    uint32_t tsc_mode;
};

struct nvtime_timeevent
{
    uint32_t evt_nb;
    uint64_t tsc;
    struct timespec ptp_time;
    uint32_t evt_mode;
    uint32_t tsc_mode;
    uint64_t tsc_res_ns;
};

int32_t nvtime_get_params(struct nvtime_params *params);

int32_t nvtime_set_params(struct nvtime_params *params);

int32_t nvtime_get_event(struct nvtime_timeevent *pps_event);

int32_t nvtime_subscribeEvents(nvtime_ppsHandle *phandle, nvtime_ppsCbFuncPtr
        pCallback, uint32_t numEvents);

int32_t nvtime_unsubscribeEvents(nvtime_ppsHandle phandle);

#if defined(__cplusplus)
}
#endif

/** @} */
#endif // __NVTIME_H__
