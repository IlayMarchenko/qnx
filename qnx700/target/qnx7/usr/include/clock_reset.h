/*
 * Copyright (c) 2015-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef _CLOCK_RESET_H
#define _CLOCK_RESET_H

#include "bpmp_abi.h"

typedef enum _NvBpmpClockResetError
{
    NVBPMP_CLOCK_RESET_SUCCESS = 0,

    /* Errors returned by BPMP FW */
    NVBPMP_CLOCK_RESET_BPMP_ENOENT, /* No such file or directory */
    NVBPMP_CLOCK_RESET_BPMP_ENOHANDLER, /* No MRQ handler */
    NVBPMP_CLOCK_RESET_BPMP_EIO, /* I/O error */
    NVBPMP_CLOCK_RESET_BPMP_EBADCMD, /* Bad sub-MRQ command */
    NVBPMP_CLOCK_RESET_BPMP_ENOMEM, /* Not enough memory */
    NVBPMP_CLOCK_RESET_BPMP_EACCES, /* Permission denied */
    NVBPMP_CLOCK_RESET_BPMP_EFAULT, /* Bad address */
    NVBPMP_CLOCK_RESET_BPMP_ENODEV, /* No such device */
    NVBPMP_CLOCK_RESET_BPMP_EISDIR,
    NVBPMP_CLOCK_RESET_BPMP_EINVAL, /* Invalid argument */
    NVBPMP_CLOCK_RESET_BPMP_ETIMEDOUT,
    NVBPMP_CLOCK_RESET_BPMP_ERANGE,
    NVBPMP_CLOCK_RESET_BPMP_EUNRECOGNIZED,

    /* Other errors returned by library only */
    NVBPMP_CLOCK_RESET_EIVC, /* IVC send receive error */
    NVBPMP_CLOCK_RESET_EINVAL_PARAM, /* Invalid argument by caller */
    NVBPMP_CLOCK_RESET_EUNKNOWN, /* Unknown error */
} NvBpmpClockResetError;

typedef struct _NvBpmpClockAllInfo
{
    uint32_t can_set_parent;
    uint32_t can_set_rate;
    uint32_t is_root;
    uint32_t parent;
    uint32_t parents[MRQ_CLK_MAX_PARENTS];
    uint8_t num_parents;
    uint8_t name[MRQ_CLK_NAME_MAXLEN];
} NvBpmpClockAllInfo;

/*
 * Keep this struct in sync with mrq_cpu_ndiv_limits_response
 * in bpmp_abi.h
 */
typedef struct {
    /** @brief Reference frequency in Hz */
    uint32_t ref_clk_hz;
    /** @brief Post divider value */
    uint16_t pdiv;
    /** @brief Input divider value */
    uint16_t mdiv;
    /** @brief FMAX expressed with max NDIV value */
    uint16_t ndiv_max;
    /** @brief Minimum allowed NDIV value */
    uint16_t ndiv_min;
} NvBpmpCpuNDivLimits;

NvBpmpClockResetError NvBpmpEnableClock(uint32_t clock_id);

NvBpmpClockResetError NvBpmpDisableClock(uint32_t clock_id);

NvBpmpClockResetError NvBpmpGetMaxClockId(uint32_t *max_id);

NvBpmpClockResetError NvBpmpGetClockRate(uint32_t clock_id, int64_t *rate);

NvBpmpClockResetError NvBpmpRoundClockRate(uint32_t clock_id,
    int64_t expected_rate, int64_t *actual_rate);

NvBpmpClockResetError NvBpmpAssertReset(uint32_t reset_id);

NvBpmpClockResetError NvBpmpDeassertReset(uint32_t reset_id);

NvBpmpClockResetError NvBpmpIsClockEnabled(uint32_t clock_id,
    uint32_t *is_enabled);

NvBpmpClockResetError NvBpmpResetDevice(uint32_t reset_id);

NvBpmpClockResetError NvBpmpGetParent(uint32_t clock_id, uint32_t *parent_id);

NvBpmpClockResetError NvBpmpSetParent(uint32_t clock_id,
    uint32_t parent_clock_id);

NvBpmpClockResetError NvBpmpSetRate(uint32_t clock_id, int64_t frequency);

NvBpmpClockResetError NvBpmpClockGetAllInfo(uint32_t clock_id,
    NvBpmpClockAllInfo *all_info);

NvBpmpClockResetError NvBpmpGetCpuVHint(uint32_t phys_addr, size_t size,
    uint32_t cluster_id);

NvBpmpClockResetError NvBpmpGetCpuNDivLimits(uint32_t cluster_id,
    NvBpmpCpuNDivLimits *cpu_ndiv_limits);

const char *NvBpmpErrToStr(NvBpmpClockResetError err);

#ifdef GCOV_ENABLED
/**
 * Dump the GCOV Data. It expects the GCOV env variables to set as needed.
 */
void NvBpmpClkRstDumpGcov(void);
#endif

#endif // _CLOCK_RESET_H
