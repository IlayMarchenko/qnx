/*
 * Copyright (c) 2014-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVPMUAPI_H__
#define __NVPMUAPI_H__

#include "nvcommon.h"

#if defined(__cplusplus)
extern "C"
{
#endif

typedef enum {
    NvPmuError    = -1,       /* Error */
    NvPmuSuccess  = 0,        /* Success */
} NvPmuErrCode;

/* interfaces */
typedef enum {
    NVPMU_ROOT = 0,
    NVPMU_POWER_TREE,
    NVPMU_GET_VERBOSE_LEVEL,
    NVPMU_SET_VERBOSE_LEVEL,
    NVPMU_GET_VOLTAGE,
    NVPMU_SET_VOLTAGE,
    NVPMU_GET_VOLTAGE_LIMITS,
    NVPMU_DISABLE,
    NVPMU_ENABLE,
    NVPMU_GET_VOLTAGE_PHANDLE,
    NVPMU_SET_VOLTAGE_PHANDLE,
    NVPMU_GET_VOLTAGE_LIMITS_PHANDLE,
    NVPMU_DISABLE_PHANDLE,
    NVPMU_ENABLE_PHANDLE,
    NVPMU_GET_STATUS,
    NVPMU_GET_NUM_OF_RAILS,
    NVPMU_GET_NAME_AND_ID_OF_RAIL,
    NVPMU_IMPL_LIB_API_WRAPPER,
    NVPMU_MAX_FILE_IDS
} NvPmuNodeId;

#define NVPMU_BUF_SIZE 100
#define NVPMU_RAIL_NAME_SIZE 40

typedef struct PmuMsgData {
    union {
        char Buf[NVPMU_BUF_SIZE];
        NvS32 S32Data;
        NvU32 U32Data;
    } SendData;

    union {
        char BufVal[NVPMU_BUF_SIZE];
        NvPmuErrCode Ret;
    } RecvData;
} NvPmuMsgData;

/**
 * Get Verobse Level
 */
NvPmuErrCode NvPmuGetVerboseLevel(NvS32 *VerbLevel);

/**
 * Set Verobse Level
 */
NvPmuErrCode NvPmuSetVerboseLevel(NvS32 VerbLevel);

/**
 * Get voltage
 */
NvPmuErrCode NvPmuGetVoltage(NvU32 RailId, NvS32 *Volt);

/**
 * Set voltage
 */
NvPmuErrCode NvPmuSetVoltage(NvU32 RailId, NvS32 Volt);

/**
 * Get voltage Limits
 */
NvPmuErrCode NvPmuGetVoltageLimits(NvU32 RailId, NvS32 *MinVolt, NvS32 *MaxVolt);

/**
 * Disable Rail
 */
NvPmuErrCode NvPmuDisable(NvU32 RailId);

/**
 * Enable Rail
 */
NvPmuErrCode NvPmuEnable(NvU32 RailId);

/**
 * Get Rail Status
 */
NvPmuErrCode NvPmuGetStatus(NvU32 RailId, NvU32 *IsEnabled);

/**
 * Get voltage based on DT PHandle
 */
NvPmuErrCode NvPmuGetVoltagePHandle(NvU32 PHandle, NvS32 *Volt);

/**
 * Set voltage based on DT PHandle
 */
NvPmuErrCode NvPmuSetVoltagePHandle(NvU32 PHandle, NvS32 Volt);

/**
 * Get voltage Limits based on DT PHandle
 */
NvPmuErrCode NvPmuGetVoltageLimitsPHandle(NvU32 PHandle, NvS32 *MinVolt, NvS32 *MaxVolt);

/**
 * Disable Rail based on DT PHandle
 */
NvPmuErrCode NvPmuDisablePHandle(NvU32 PHandle);

/**
 * Enable Rail based on DT PHandle
 */
NvPmuErrCode NvPmuEnablePHandle(NvU32 PHandle);

/**
 * Get number of Rails
 */
NvPmuErrCode NvPmuGetNumOfRails(NvU32 *RailCount);

/**
 * Get name and id of rail at given Index
 */
NvPmuErrCode NvPmuGetNameAndIdOfRail(char *RailName, NvU32 *RailId, NvU32 Index);

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif  // __NVPMUAPI_H__
