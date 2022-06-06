/*
 * Copyright (c) 2015-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

/**
 * @file nvdma32.h
 * @brief <b> NVIDIA DMA32 headr </b>
 *
 * @b Description: This files declares the interface for allocating/freeing
 * DMA32 memory (i.e. within 32bit address space).
 *
 */

#ifndef __NV_DMA32_H__
#define __NV_DMA32_H__

#include <stdio.h>
#include <unistd.h>
#include <sys/neutrino.h>


/**
 * @defgroup qnx_dma32_group DMA32 Interface
 *
 * Allocates and frees
 * DMA32 memory (i.e. within 32bit address space).
 * @ingroup qnx_lib_group
 * @{
 */


/**
 * Allocates non-cached memory in 32-bit address space.
 *
 * @param size - size of memory to be allocated
 * @param paddr - returning physical address of the allocated memory
 *
 * @return  Pointer to the allocated memory,
 *          or -1 if there is an allocation failure.
 */
void *dma32_alloc_uncached(size_t size, off64_t *paddr);

/**
 * Allocates cached memory in 32-bit address space.
 *
 * @param size - size of memory to be allocated.
 * @param paddr - returning physical address of the allocated memory.
 *
 * @return  A non-NULL pointer to the allocated memory,
 *          or NULL if there is an allocation failure.
 */
void *dma32_alloc_cached(size_t size, off64_t *paddr);

/**
 * Frees the previously allocated memory.
 * @param size Size of the memory to free.
 * @param ptr  A pointer to the memory to be freed.
 *
 * @return  Return values are:
 *          - 0 indicates success.
 *          - Non-zero value indicates failure (errno is set).
 */
int dma32_free(size_t size, void *ptr);

/** @} */

#endif /* __NV_DMA32_H__ */
