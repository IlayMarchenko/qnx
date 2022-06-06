/*
 * Copyright (c) 2007-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

#ifndef __INIT_COMMON_H__
#define __INIT_COMMON_H__

#include "nvclockapi.h"

#define SET_BIT_MASKED(virt_addr, pos)                              \
    do {                                                            \
         NvU32 dummy;                                               \
         *((volatile NvU32 *)(virt_addr)) = (0x1 << (pos));         \
         dummy = *((volatile NvU32 *)(virt_addr)); /* fence read */ \
    } while(0)

#define SET_BIT(virt_addr, pos)      *((volatile NvU32 *)(virt_addr)) |= (0x1 << (pos))
#define CLR_BIT(virt_addr, pos)      *((volatile NvU32 *)(virt_addr)) &= (~(0x1 << (pos) ))
#define WRITE_REG32(virt_addr, val)  *((volatile NvU32 *)(virt_addr)) = (val)
#define READ_REG32(virt_addr)        *((volatile NvU32 *)(virt_addr))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/**
 * Configure power state of a device.
 *
 * @param dev_name Device node name
 * @param state Power state of the device
 */
int configure_dev_pwr_state(const char *dev_name, int state);

#define NVTOOLS_COMMON_PRINTF(args...) \
    do {                               \
        printf("%s: ", __FUNCTION__);  \
        printf(args);                  \
    } while (0)

#define CHECK_ERROR(a)    \
    do {                  \
        int error;        \
        error = (a);      \
        if (error != 0) { \
            return error; \
        }                 \
    } while (0)

#endif // __INIT_COMMON_H__
