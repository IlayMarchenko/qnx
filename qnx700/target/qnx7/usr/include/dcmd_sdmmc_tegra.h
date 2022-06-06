/*
 * Copyright (c) 2011-2016 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

/*
 *  dcmd_sdmmc_tegra.h   Devctl definitions for mNAND
 */

#ifndef _DCMD_SDMMC_TEGRA_H_INCLUDED
#define _DCMD_SDMMC_TEGRA_H_INCLUDED

#include <devctl.h>

#include <_pack64.h>

typedef struct _mmcsd_rw_log {
	uint64_t bytes_read;  //no. of bytes read since last check
	uint64_t bytes_written; //no. of bytes written since last check
} MMCSD_RW_LOG;

typedef MMCSD_RW_LOG SDMMC_RW_LOG;

#define DCMD_MMCSD_MAX_NUM_SECTORS_PER_TRANS	256
#define DCMD_SDMMC_MAX_NUM_SECTORS_PER_TRANS	DCMD_MMCSD_MAX_NUM_SECTORS_PER_TRANS

typedef struct _mmcsd_rw_trans_log {
	// Count number of read transactions for each transaction size.
	// Transactions with more sectors than DCMD_MMCSD_MAX_NUM_SECTORS_PER_TRANS
	// accummulate into that slot.
	uint64_t reads[DCMD_SDMMC_MAX_NUM_SECTORS_PER_TRANS];

	// Ditto for writes.
	uint64_t writes[DCMD_SDMMC_MAX_NUM_SECTORS_PER_TRANS];
} MMCSD_RW_TRANS_LOG;

typedef MMCSD_RW_TRANS_LOG SDMMC_RW_TRANS_LOG;

/* Included defines from dcmd_mmcsd_tegra.h for backward compatibility in mnand_log_control tool */
#define DCMD_MMCSD_LOG_FILE_NAME_LEN	100

#define DCMD_MMCSD_GET_RW_STAT               __DIOF(_DCMD_CAM, _SIM_MMCSD + 10, MMCSD_RW_LOG)
#define DCMD_MMCSD_SET_TIMEO_IN_MSEC         __DIOT(_DCMD_CAM, _SIM_MMCSD + 11, uint32_t)
#define DCMD_MMCSD_SET_CMDLOG                __DIOT(_DCMD_CAM, _SIM_MMCSD + 12, uint32_t)
#define DCMD_MMCSD_SET_LOG_LEVEL             __DIOT(_DCMD_CAM, _SIM_MMCSD + 13, uint32_t)
#define DCMD_MMCSD_SET_LOG_FILE              __DIOT(_DCMD_CAM, _SIM_MMCSD + 14, uint32_t)
#define DCMD_MMCSD_SET_RFSH_INTERVAL         __DIOT(_DCMD_CAM, _SIM_MMCSD + 15, uint32_t)
#define DCMD_MMCSD_GET_CMDLOG                __DIOF(_DCMD_CAM, _SIM_MMCSD + 16, uint32_t)
#define DCMD_MMCSD_GET_RW_TRANS_STAT         __DIOF(_DCMD_CAM, _SIM_MMCSD + 17, MMCSD_RW_TRANS_LOG)

#define DCMD_SDMMC_GET_RW_STAT               __DIOF(_DCMD_CAM, _SIM_SDMMC + 20, SDMMC_RW_LOG)
#define DCMD_SDMMC_SET_TIMEO_IN_MSEC         __DIOT(_DCMD_CAM, _SIM_SDMMC + 21, uint32_t)
#define DCMD_SDMMC_SET_CMDLOG                __DIOT(_DCMD_CAM, _SIM_SDMMC + 22, uint32_t)
#define DCMD_SDMMC_SET_LOG_LEVEL             __DIOT(_DCMD_CAM, _SIM_SDMMC + 23, uint32_t)
#define DCMD_SDMMC_SET_LOG_FILE              __DIOT(_DCMD_CAM, _SIM_SDMMC + 24, uint32_t)
#define DCMD_SDMMC_SET_RFSH_INTERVAL         __DIOT(_DCMD_CAM, _SIM_SDMMC + 25, uint32_t)
#define DCMD_SDMMC_GET_CMDLOG                __DIOF(_DCMD_CAM, _SIM_SDMMC + 26, uint32_t)
#define DCMD_SDMMC_GET_RW_TRANS_STAT         __DIOF(_DCMD_CAM, _SIM_MMCSD + 27, SDMMC_RW_TRANS_LOG)

#include <_packpop.h>

#endif
