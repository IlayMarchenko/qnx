/*
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/**
 * Description: This file declares interfaces for libnvtegrahv.
 *
 * Return Values:
 * 	NvHvCheckOsNative:
 * 		 1 -> Native
 *		 0 -> Non Native
 *		-1 -> cannot determine
 *	NvHvGetOsVmId:
 *		!0 -> Fail
 *		 0 -> Success, non native
 *	NvHvGetDisplayVmId:
 *		!0 -> Fail
 *		 0 -> Success, non-native
 *      NvHvGetSysinfoAddr:
 *              !0 -> Fail
 *               0 -> Success. Argument will contain sysinfo phy addr
 */

#ifndef __NV_TEGRA_HV_H__
#define __NV_TEGRA_HV_H__

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdint.h>

#define BUF_SIZE 	20 /* Max digits for vmid */
#define DISPLAY_VM 	"DISPLAY_VM" /* environ var that stores display vmid */

typedef int (*PfnNvHvGetOsVmId)(unsigned int *);
int NvHvGetOsVmId(unsigned int *);

typedef int (*PfnNvHvCheckOsNative)(void);
int NvHvCheckOsNative(void);

typedef int (*PfnNvHvGetDisplayVmId)(unsigned int *);
int NvHvGetDisplayVmId(unsigned int *);

typedef int (*PfnNvHvGetSysinfoAddr)(uint64_t *);
int NvHvGetSysinfoAddr(uint64_t *);

typedef enum
{
    Os_Non_Native = 0,
    Os_Native,
    Os_Detection_Failed = -1
} NvOsType;
#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif
