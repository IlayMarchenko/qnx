/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __LIBNVGIC_H_INCLUDED
#define __LIBNVGIC_H_INCLUDED

typedef enum _NvGicType {
    CCPLEX_GIC = 0,
    APE_GIC = 1,
} NvGicType;

typedef enum _NvGicError {
    NVGIC_SUCCESS,
    NVGIC_MMAP_FAILED,
    NVGIC_WRONG_GIC_TYPE,
    NVGIC_WRONG_IRQ,
    NVGIC_WRONG_CPU,
} NvGicError;

typedef enum _NvGicCpuIntf {
    GIC_CPUINTF_MIN = 0,
    GIC_CPUINTF_0 = 0,
    GIC_CPUINTF_1,
    GIC_CPUINTF_2,
    GIC_CPUINTF_3,
    GIC_CPUINTF_4,
    GIC_CPUINTF_5,
    GIC_CPUINTF_6,
    GIC_CPUINTF_7,
    GIC_CPUINTF_MAX = 7,
} NvGicCpuIntf;

#if defined(CONFIG_ARCH_TEGRA_t18x_SOC)
#define GIC_CPUINTF_ADSP        GIC_CPUINTF_4
#endif

NvGicError NvGicInterruptRoute(NvGicType type, uint32_t irq_num,
    NvGicCpuIntf cpu_id);

const char * const NvGicErrorToString(NvGicError err);

NvGicError NvGicAgicInit(void);

#endif //__LIBNVGIC_H_INCLUDED
