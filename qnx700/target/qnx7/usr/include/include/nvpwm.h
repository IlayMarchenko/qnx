/*
 * Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVPWM_H__
#define __NVPWM_H__

#include "nvcommon.h"
#include "nvclockapi.h"

typedef enum {
    NvPwmError_Success = 0,
    NvPwmError_Error,
    NvPwmError_Invalid,
} NvPwmError;

typedef enum {
    NVPWM_STATE_DISABLE = 0,
    NVPWM_STATE_ENABLE,
} NvPwmState;

typedef struct _NvPwmHandle *NvPwmHandle;

/**
 * Initializes and maps the controller instance.
 *   @phys_addr: Physical address of the PWM controller to init.
 *   @handle: Pointer to store NvPwm handle.
 *   @init_clk: Set to 1 to reset and enable clock to PWM ctrl.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmInit(NvU32 phys_addr, NvPwmHandle *handle, NvU8 init_clk);

/**
 * Deinit PWM controller and unmap the instance.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   @deinit_clk: Set to 1 to disable clock to PWM ctrl.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmDeInit(NvPwmHandle handle, NvU8 deinit_clk);

/**
 * Sets PWM state.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle or state is invalid
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmSetState(NvPwmHandle handle, NvPwmState);

/**
 * Gets pulse width for PWM.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   @width: Pointer to store the pulse width in percentage.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid or pointer to store pulse width is NULL
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmGetDutyCycle(NvPwmHandle handle, uint32_t *width);

/**
 * Gets frequency for PWM.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   @frequency: Pointer to store the frequency in KHz.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid or pointer to store frequency is NULL
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmGetFrequency(NvPwmHandle handle, uint32_t *frequency);

/**
 * Sets pulse width of PWM.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   @width: Value of pulse width to set in percentage.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid or width is out of range
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmSetDutyCycle(NvPwmHandle handle, uint32_t width);

/**
 * Sets frequency of PWM.
 *   @handle: NvPwm handle returned by NvPwmInit.
 *   @frequency: Value of the frequency in KHz.
 *   Return:
 *       NvPwmError_Success, on success
 *       NvPwmError_Invalid, if handle is invalid or frequency is 0
 *       NvPwmError_Error, otherwise
 */
NvPwmError NvPwmSetFrequency(NvPwmHandle handle, uint32_t frequency);

#endif // __NVPWM_H__
