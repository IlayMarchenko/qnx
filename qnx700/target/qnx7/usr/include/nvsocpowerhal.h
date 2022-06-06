/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#pragma once

#include "nvcommon.h"

#if defined(__cplusplus)
extern "C"
{
#endif

typedef enum  {
    NvSocPowerHalSC7 = 1,
    NvSocPowerHalSC8,
} NvSocPowerHalSuspendLevel_t;

typedef enum nvsoc_cpu_state_enum {
    /*
     * Stay consistent with the PSCI implementation definition
     *
     * CPU_READY -> CPU_DOWN_REQ -> CPU_DOWN_IN_PROGRESS -> CPU_DOWN
     *      ^                          |                        |
     *      |      CPU_DOWN_FAILED <---+                        |
     *      +---------------------------------------------------+
     */
    CPU_READY               = 0x000,
    CPU_DOWN_REQ            = 0x011,
    CPU_DOWN_IN_PROGRESS    = 0x010,
    CPU_DOWN_FAILED         = 0x111,
    CPU_DOWN                = 0x001,
    CPU_UNKNOWN             = 0xFFF,
} NVSOC_CPU_STATE;

/*
 * All functions return 0 on success. Any other value indicates a fail
 *
 * NvSocPowerhalInit must be called before any operation.
 * The result is undefined otherwise
 */
int32_t NvSocPowerHalDeinit(void);
int32_t NvSocPowerHalInit(void);
int32_t NvSocPowerHalCpuOff(uint32_t cpu);
int32_t NvSocPowerHalCpuOn(uint32_t cpu);
int32_t NvSocPowerHalGetNumCpu(uint32_t *numcpu);
int32_t NvSocPowerHalGetCpuState(uint32_t numcpu, NVSOC_CPU_STATE *arr);
int32_t NvSocPowerHalEnterSuspend(NvSocPowerHalSuspendLevel_t suspend_level);

#if defined(__cplusplus)
}
#endif
