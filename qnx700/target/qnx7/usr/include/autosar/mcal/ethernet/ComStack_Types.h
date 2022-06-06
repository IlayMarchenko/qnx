/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/**
 * @file ComStack_Types.h
 * @brief <b>Header for AUTOSAR COM module Software Stack Types </b>
 * @b Description: Contains types definition
 *                 for COM module Software Stack.
 */

#ifndef _COMSTACK_TYPES_H_
#define _COMSTACK_TYPES_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include <Std_Types.h>

/*******************************************************************************
**                     COM Stack Section Types                                **
*******************************************************************************/
typedef enum BufReq_ReturnType
{
    BUFREQ_OK = 0,      /* success */
    BUFREQ_E_NOT_OK,    /* development error detected */
    BUFREQ_E_BUSY,      /* all buffers in use */
    BUFREQ_E_OVFL       /* requested buffer too large*/
} BufReq_ReturnType;

#endif /* _COMSTACK_TYPES_H_ */
