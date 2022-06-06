/*
 * Copyright (c) 2015-2017, NVIDIA CORPORATION.  All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */
/**
 * \file
 * \brief <b> NVIDIA Media Interface: Auto Control Plugin API </b>
 *
 * @b Description: This file contains the Camera AutoControl Plugin API.
 */

#ifndef __NVMEDIA_ACP_H__
#define __NVMEDIA_ACP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_ipp.h"
/**
 * \defgroup image_acp_api Camera AutoControl Plugin
 * The Camera AutoControl Plugin API provides ACP configuration functions.
 * @ingroup nvmedia_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_ACP_VERSION_MAJOR   1u
/** \brief Minor Version number */
#define NVMEDIA_ACP_VERSION_MINOR   3u

/**
 * \brief Version information for the NvMedia ACP library.
 */
typedef struct {
    /*! Library version information */
    NvMediaVersion libVersion;
} NvMediaACPVersionInfo;

NvMediaStatus
NvMediaACPCreate(
    NvMediaIPPComponent *parentControlAlgorithmHandle,
    NvMediaIPPPluginSupportFuncs *pSupportFunctions,
    NvMediaIPPPropertyStatic *pStaticProperties,
    void *clientContext,
    NvMediaIPPPlugin **pluginHandle,
    NvMediaIPPISPVersion ispVersion);

NvMediaStatus
NvMediaACPProcess(
    NvMediaIPPPlugin *pluginHandle,
    NvMediaIPPPluginInput *pluginInput,
    NvMediaIPPPluginOutputEx *pluginOutput);

void NvMediaACPDestroy(
    NvMediaIPPPlugin *pluginHandle);

NvMediaStatus
NvMediaACPGetVersionInfo(
    NvMediaACPVersionInfo *versionInfo);

NvMediaStatus
NvMediaBEPCreate(
    NvMediaIPPComponent *parentControlAlgorithmHandle,
    NvMediaIPPPluginSupportFuncs *pSupportFunctions,
    NvMediaIPPPropertyStatic *pStaticProperties,
    void *clientContext,
    NvMediaIPPPlugin **pluginHandle,
    NvMediaIPPISPVersion ispVersion);

void
NvMediaBEPDestroy(
    NvMediaIPPPlugin *pluginHandle);

NvMediaStatus
NvMediaBEPProcessEx(
    NvMediaIPPPlugin *pluginHandle,
    NvMediaIPPPluginInput *pluginInput,
    NvMediaIPPPluginOutputEx *pluginOutput);
/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif //__NVMEDIA_ACP_H__
