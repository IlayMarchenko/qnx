/*
 * Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVDT_TYPES_H
#define __NVDT_TYPES_H

#include <inttypes.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#define NVDT_MAGIC       0xd00dfeed      /* 4: version, 4: total size */
#define NVDT_TAGSIZE     sizeof(uint32_t)

#define NVDT_ERR_NOTFOUND 1
#define NVDT_BEGIN_NODE  0x1             /* Start node: full name */
#define NVDT_END_NODE    0x2             /* End node */
#define NVDT_PROP        0x3             /* Property: name off,
                                           size, content */
#define NVDT_NOP         0x4             /* nop */
#define NVDT_END         0x9

typedef enum {
    NVDT_SUCCESS = 0,
    NVDT_NO_DTB,
    NVDT_NO_NODE,
    NVDT_NO_NEXT_NODE,
    NVDT_NO_PROP,
    NVDT_MMAP_ERROR,
    NVDT_NULL_PTR,
    NVDT_DISABLED,
    NVDT_INVALID,
    NVDT_ERROR,
    NVDT_REPORT_GVS_ERROR, /*Report FATAL error due to DT parsing*/
} nvdt_error;

struct nvdt_base {
    uint32_t *pbase; /* List of Physical base addresses */
    uint32_t *size; /* Size to map */
    uintptr_t *vbase; /* List of Virtual base addresses */
    uint32_t num_base; /* Number of regs */
};

/* This struct represents a single tuple */
struct nv_prod_tuple {
    uint32_t index; /* Address base index */
    uint32_t addr;  /* offset address*/
    uint32_t mask;  /* mask */
    uint32_t val;   /* value */
};

/* This struct is for each named prod */
struct nv_tegra_prod {
    const char *name;
    struct nv_prod_tuple *prod_tuple;
    uint32_t count; /* number of prod_tuple*/
    bool boot_init; /* set for prods with "nvidia,prod-boot-init" property */
};

/*
 * This struct is for the complete prod list. Settings apply to all the
 * named prods.
 */
struct nv_tegra_prod_list {
    struct nv_tegra_prod *tegra_prod;
    uint32_t num; /* number of tegra_prod*/
    uint32_t n_prod_cells; /* number of cells in each tuple */
};

#endif // __NVDT_TYPES_H
