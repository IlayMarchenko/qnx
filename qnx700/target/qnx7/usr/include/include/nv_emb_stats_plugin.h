/*
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _NV_EMB_STATS_PLUGIN_H_
#define _NV_EMB_STATS_PLUGIN_H_

#include "nvmedia_ipp.h"

#ifdef __cplusplus
extern "C" {
#endif

NvMediaStatus
NvEmbStatsPluginCreate(
    NvMediaIPPComponent *parentControlAlgorithmHandle,
    NvMediaIPPPluginSupportFuncs *pSupportFunctions,
    NvMediaIPPPropertyStatic *pStaticProperties,
    void *clientContext,
    NvMediaIPPPlugin **pluginHandle,
    NvMediaIPPISPVersion ispVersion);

void
NvEmbStatsPluginDestroy(
    NvMediaIPPPlugin *pluginHandle);

NvMediaStatus
NvEmbStatsPluginProcessEx(
    NvMediaIPPPlugin *pluginHandle,
    NvMediaIPPPluginInput *pluginInput,
    NvMediaIPPPluginOutputEx *pluginOutput);

#ifdef __cplusplus
}
#endif

#endif // _NV_EMB_STATS_PLUGIN_H_
