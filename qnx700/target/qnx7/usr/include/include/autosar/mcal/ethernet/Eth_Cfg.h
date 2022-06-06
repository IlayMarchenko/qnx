/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/**
 * @file Eth_Cfg.h
 * @brief <b>Interface to Eth</b>
 * @b Description: Contains compile time configuration details and global
 *                 macros.
 */

#ifndef _ETH_CFG_H
#define _ETH_CFG_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/* PUBLISHED INFORMATION */

/* AUTOSAR specification version numbers */
#define ETH_AR_RELEASE_MAJOR_VERSION       (4U)
#define ETH_AR_RELEASE_MINOR_VERSION       (2U)
#define ETH_AR_RELEASE_REVISION_VERSION    (2U)

/* Vendor specific implementation version information */
#define ETH_SW_MAJOR_VERSION           (2U)
#define ETH_SW_MINOR_VERSION           (0U)
#define ETH_SW_REVISION_VERSION        (0U)
#define ETH_SW_PATCH_VERSION           (0U)

/* ETH GENERAL PARAMETERS */
/*
Configuration: ETH_DEV_ERROR_DETECT:
- if ON, DET is Enabled
- if OFF,DET is Disabled
Compile switch to enable/disable development error detection
for this module.
*/
#define ETH_DEV_ERROR_DETECT           (STD_ON)
/*
Configuration: ETH_ENABLE_RX_INT:
- if ON, DET is Enabled
- if OFF,DET is Disabled
Compile switch to enable/disable development error detection
for this module.
*/
#define ETH_ENABLE_RX_INT              (STD_ON)
/*
Configuration: ETH_ENABLE_TX_INT:
- if ON, DET is Enabled
- if OFF,DET is Disabled
Compile switch to enable/disable development error detection
for this module.
*/
#define ETH_ENABLE_TX_INT              (STD_ON)

/* Index to specify thw ETH driver */
#define ETH_INDEX                      (0U)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* _ETH_CFG_H */
