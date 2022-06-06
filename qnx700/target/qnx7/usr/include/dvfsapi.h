/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef _DVFSAPI_H
#define _DVFSAPI_H

#include <pthread.h>
#include "nvcommon.h"
#include "nvqnx_common.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * @file dvfsapi.h
 * @brief <b> API for getting and setting CPU frequency </b>
 *
 * @b Description: This files declares the interface for getting and
 * setting the CPU frequency.
 *
 */

/**
 * @defgroup nvdvfs_group DVFS API
 *
 * @ingroup qnx_lib_group
 * @{
 */

/**
* \brief Defines the maximum number of frequencies in frequency table.
*/
#define MAX_DVFS_FREQS  40

/**
* \brief Defines the error codes.
*/
typedef enum {
    NvDvfsError    = -1,       /* Error */
    NvDvfsSuccess  = 0,        /* Success */
} NvDvfsErrCode;

/*
 * For T19x, valid rail names are -
 *   - VDD_CARMEL0
 *   - VDD_CARMEL1
 *   - VDD_CARMEL2
 *   - VDD_CARMEL3
 */

/**
 * @brief Get frequency of cluster associated with the rail
 *
 * @param RailName Name of rail
 * @param Frequency Pointer to 32-bit integer where freq can be stored
 *
 * @return NvDvfsSuccess on success, NvDvfsError on error.
 */
NvDvfsErrCode NvDvfsGetDvfsFreq(const char *RailName, NvU32 *Frequency);

/**
 * @brief Set frequency of cluster associated with the rail
 *
 * @param RailName Name of rail
 * @param Frequency Desired frequency in KHz
 *
 * @return NvDvfsSuccess on success, NvDvfsError on error.
 */
NvDvfsErrCode NvDvfsSetDvfsFreq(const char *RailName, NvU32 Frequency);

/**
 * @brief Set max frequency for cluster associated with the rail
 *
 * @param RailName Name of rail
 *
 * @return NvDvfsSuccess on success, NvDvfsError on error.
 */
NvDvfsErrCode NvDvfsSetMaxDvfsFreq(const char *RailName);

/**
 * @brief Get the frequency table for cluster associated with the rail
 *
 * @param RailName Name of rail
 * @param FreqTable[] Array to store the frequency table in KHz
 * @param FreqTableSize Size of the frequency table array
 *
 * @return NvDvfsSuccess on success, NvDvfsError on error.
 */
NvDvfsErrCode NvDvfsGetDvfsFreqTable(const char *RailName, NvU32 FreqTable[],
    NvU32 FreqTableSize);

/**
 * @brief Print the frequency of clusters associated with all rails
 *
 * @return NvDvfsSuccess on success, NvDvfsError on error.
 */
NvDvfsErrCode NvDvfsPrintDvfsTree(void);

/** @} */

#if defined(__cplusplus)
}
#endif

#endif  // _DVFSAPI_H
