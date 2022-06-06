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
 * @file Det.h
 * @b Description: Contains development error reporting mechanisms.
 */

#ifndef _DET_H
#define _DET_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include <Std_Types.h>

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

void Det_ReportError(uint16 module_id, uint8 instance_id,
                     uint8 service_id, uint8 error_id);

void Det_ReportRuntimeError(uint16 module_id, uint8 instance_id,
                     uint8 service_id, uint8 error_id);
#endif /* _DET_H */
