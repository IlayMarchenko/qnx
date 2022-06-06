/*
 * Copyright (c) 2015-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

#ifndef _BBMP_POWERGATE_H
#define _BBMP_POWERGATE_H

#include "nvcommon.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/* NOTE:
 * The clock driver in BPMP maintains a separate reference count for the clocks
 * that are turned on/off via the powergating API. The clock states seen by the
 * powergating API are based on this separate counter. So, if a clock is turned
 * on/off per the powergating API, it's actual state can be different based on
 * calls made directly via the clock driver APIs.
 */

#define PARTITION_NAME_MAXLEN 40U

typedef enum _NvBpmpPowergateError
{
    NVBPMP_POWERGATE_SUCCESS = 0,
    NVBPMP_POWERGATE_ERROR = 1,
    NVBPMP_POWERGATE_INVALID = 2,
} NvBpmpPowergateError;

typedef enum _NvBpmpPowergateState
{
    NVBPMP_POWERGATE_GATED = 0, /* Powergated, with clock OFF */
    NVBPMP_POWERGATE_UNGATED_CLK_OFF = 1, /* UnPowergated, with the clock OFF */
    NVBPMP_POWERGATE_UNGATED_CLK_ON = 2, /* UnPowergated, with the clock ON */
} NvBpmpPowergateState;

/**
 * @brief Gets the state of the given partition.
 * @input
 *   PartID: Partition ID.
 * @output
 *   State: One of the states from enum NvBpmpPowergateState.
 *
 * @returns
 *   NVBPMP_POWERGATE_SUCCESS: On success.
 *   NVBPMP_POWERGATE_ERROR  : On error.
 */
NvBpmpPowergateError NvBpmpIsPartitionEnabled(NvU32 PartID, NvBpmpPowergateState *State);

/**
 * @brief Powergates the given partition and also turns off its clock from the
 *        powergate driver perspective.
 * @input
 *   PartID: Partition ID.
 *
 * @returns
 *   NVBPMP_POWERGATE_SUCCESS: On success.
 *   NVBPMP_POWERGATE_ERROR  : On error.
 */
NvBpmpPowergateError NvBpmpPowergatePartition(NvU32 PartID);

/**
 * @brief Unpowergates the given partition and clock is not turned on
 *        explicitly in the powergate driver.
 * @input
 *   PartID: Partition ID.
 *
 * @returns
 *   NVBPMP_POWERGATE_SUCCESS: On success.
 *   NVBPMP_POWERGATE_ERROR  : On error.
 */
NvBpmpPowergateError NvBpmpUnpowergatePartition(NvU32 PartID);

/**
 * @brief Get the max powergate partition ID.
 * @output
 *   MaxPartID: Max partition ID.
 *
 * @returns
 *   NVBPMP_POWERGATE_SUCCESS: On success.
 *   NVBPMP_POWERGATE_ERROR  : On error.
 */
NvBpmpPowergateError NvBpmpGetMaxPowergateID(NvU32 *MaxPartID);

/**
 * @brief Get name of the given partition.
 * @input
 *   PartID: Partition ID.
 * @output
 *   PartName: Buffer to store the partition name. Max name length can be
 *             PARTITION_NAME_MAXLEN bytes.
 *
 * @returns
 *   NVBPMP_POWERGATE_SUCCESS: On success.
 *   NVBPMP_POWERGATE_ERROR  : On error.
 */
NvBpmpPowergateError NvBpmpGetPowergatePartitionName(NvU32 PartID, char *PartName);

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif // _BBMP_POWERGATE_H
