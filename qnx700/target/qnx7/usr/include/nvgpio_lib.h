/*
 * Copyright (c) 2015-2018 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVGPIO_LIB_H__
#define __NVGPIO_LIB_H__

#define GPIO_NAME_LENGTH 50

#include <sys/siginfo.h>
#include <inttypes.h>

/**
 * \file
 * \brief <b>NVIDIA General Purpose Input/Output (GPIO) library API</b>
 */

/** @defgroup gpio_group GPIO APIs
 * Manages interactions with General Purpose Input/Output (GPIO) pins.
 * @ingroup qnx_lib_group
 * @{
 */

/*
 * NvGpio_Success:          success
 * NvGpio_InvalidName:      gpio_name doesn't match any of the pins initialized
 * NvGpio_InvalidParam:     invalid parameter(s) passed by client
 * NvGpio_Busy:             gpio is already opened by some other client
 * NvGpio_InvalidDirection: gpio is configured as input and thus output level cannot be set
 * NvGpio_NotSupported:     interrupts are not supported by gpio on I/O expander
 * NvGpio_NoAccess:         NvGpio_Open failed and hence no access to gpio
 * NvGpio_Timeout:          timeout waiting on event.
 * NvGpio_StdErr:           underlying resmgr function failed
 * NvGpio_SigErr:           interrupted by a signal.
 */
typedef enum {
    NvGpio_Success = 256,
    NvGpio_InvalidName,
    NvGpio_InvalidParam,
    NvGpio_Busy,
    NvGpio_InvalidDirection,
    NvGpio_NotSupported,
    NvGpio_NoAccess,
    NvGpio_Timeout,
    NvGpio_StdErr,
    NvGpio_SigErr,
    NvGpio_StdErrno,
} NvGpio_ErrNo;

typedef enum {
    E_ARM_NO_INT = 0,
    E_ARM_LEVEL_LOW,
    E_ARM_LEVEL_HIGH,
    E_ARM_EDGE_ANY,
    E_ARM_EDGE_RISING,
    E_ARM_EDGE_FALLING,
} NvGpio_ArmMode;

typedef struct {
    uint32_t gpio_pin_num;
    char gpio_name[GPIO_NAME_LENGTH];
    uint32_t gpio_ctrl_phandle;
} NvGpioInfo;

/**
 *  Defines Gpio directions.
 */
typedef enum
{
    NvGpioDir_Input = 0,
    NvGpioDir_Output,
    NvGpioDir_Force32 = 0x7FFFFFFF,
} NvGpioDir;

/**
 *  Defines Gpio pin levels.
 */
typedef enum
{
    NvGpioLevel_Low = 0,
    NvGpioLevel_High,
    NvGpioLevel_Force32 = 0x7FFFFFFF,
} NvGpioLevel;

typedef struct NvGpio_HandlerRec {
    int32_t gpio_devnode;
    /* StopExecution should not be changed by the client code */
    int32_t StopExecution;
    char gpio_name[GPIO_NAME_LENGTH];
    uint32_t ts_enable;
    uint64_t ts;
} NvGpio_Handler;

static inline const char *arm_mode_name(NvGpio_ArmMode arm_mode)
{
    const char *ret_val;

    switch (arm_mode) {
        case E_ARM_NO_INT:
            ret_val = "no interrupt";
            break;
        case E_ARM_LEVEL_LOW:
            ret_val = "low level";
            break;
        case E_ARM_LEVEL_HIGH:
            ret_val = "high level";
            break;
        case E_ARM_EDGE_ANY:
            ret_val = "any edge";
            break;
        case E_ARM_EDGE_RISING:
            ret_val = "rising edge";
            break;
        case E_ARM_EDGE_FALLING:
            ret_val =  "falling edge";
            break;
        default:
            ret_val =  "";
            break;
    }
    return ret_val;
}

/*
 * Initializes variable gpio_handler to perform operations on the gpio_name passed and provides
 * exclusive access to the gpio
 * Possible error number(s):
 * NvGpio_InvalidName
 * NvGpio_InvalidParam
 * NvGpio_Busy
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioOpen(NvGpio_Handler *gpio_handler, const char *gpio_name);

/*
 * Handler obtained from NvGpio_Open is used to null access to
 * gpio so that other clients can use it
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioClose(const NvGpio_Handler *gpio_handler);

/*
 * Handler obtained from NvGpioOpen is used to get the gpio level
 * It will be stored in gpio_level
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioGetLevel(const NvGpio_Handler *gpio_handler, NvGpioLevel *gpio_level);

/*
 * Handler obtained from NvGpioOpen is used to get the gpio direction
 * It will be stored in gpio_dir
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioGetDir(const NvGpio_Handler *gpio_handler, NvGpioDir *gpio_dir);

/*
 * Handler obtained from NvGpioOpen is used to get the gpio irq config mode
 * It will be stored in arm_mode
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioGetIrqMode(const NvGpio_Handler *gpio_handler, NvGpio_ArmMode *arm_mode);

/*
 * Handler obtained from NvGpioOpen is used to enable the gpio irq timestamp
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioEnableIrqTs(const NvGpio_Handler *gpio_handler);

/*
 * Handler obtained from NvGpioOpen is used to enable the gpio irq timestamp
 * ts = 0 : TS not stored/updated for this irq event
 * ts = X : TS value for this irq event
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioGetIrqTs(const NvGpio_Handler *gpio_handler);

/*
 * Handler obtained from NvGpioOpen is used to acess the gpio
 * gpio_level = NvGpioLevel_High: Configured as High
 * gpio_level = NvGpioLevel_Low: Configured as Low
 * Returns NvGpio_Success on success
 * Returns an error number on failure NvGpio_ErrNo
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioSetasOutput(const NvGpio_Handler *gpio_handler, NvGpioLevel gpio_level);

/*
 * Handler obtained from NvGpioOpen is used to acess the gpio
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioSetasInput(const NvGpio_Handler *gpio_handler);

/*
 * Handler obtained from NvGpioOpen is used to acess the gpio
 * Possible error number(s):
 * NvGpio_InvalidDirection
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioSetLevel(const NvGpio_Handler *gpio_handler, NvGpioLevel gpio_level);

/*
 * Handler obtained from NvGpioOpen is used to acess the gpio
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_NotSupported
 * NvGpio_InvalidParam
 * NvGpio_StdErr
 */
NvGpio_ErrNo NvGpioSetIrqMode(const NvGpio_Handler *gpio_handler, NvGpio_ArmMode arm_mode);

/*
 * Tests whether a gpio responds to a particular interrupt mode
 * gpio_handler    GPIO handler
 * timeout         Timeout (time to wait for an event) in seconds
 *                 Timeout = -1 : infinite
 * arm_mode        Interrupt mode to use
 * event_count     Number of count of events\n"
 *                 Give 0 for infinite number of events. Default value is 0
 * sleep_time      Time to sleep after event (in seconds)
 *                 Useful to check CPU usage and for level modes
 * Possible error number(s):
 * NvGpio_InvalidName
 * NvGpio_Busy
 * NvGpio_NoAccess
 * NvGpio_NotSupported
 * NvGpio_InvalidParam
 * NvGpio_Timeout
 * NvGpio_StdErr
 * NvGpio_SigErr
 */
NvGpio_ErrNo NvGpioWaitforInterruptEvent(NvGpio_Handler *gpio_handler, int32_t timeout,
    NvGpio_ArmMode arm_mode, int32_t event_count, uint32_t sleep_time);

/*
 * Gives the total number of gpios initialized
 * Return -1 for error
 */
int32_t NvGpioGetCount(void);

/*
 * Retrieves the gpio name for pin number provided in gpio_info.gpio_pin_num.
 * The function also expects the gpio_info.gpio_ctrl_phandle to be set to the
 * phandle of the appropriate gpio controller.
 * In following example, value at index 0 is gpio_ctrl_phandle and index 1 is
 * gpio_num. Convert to little endian before setting the struct fields -
 *     gpio = <&tegra_main_gpio TEGRA_MAIN_GPIO(L, 5) 0>
 *
 * Possible error number(s):
 * NvGpio_NoAccess
 * NvGpio_InvalidParam
 */
NvGpio_ErrNo NvGpioGetGpioName(NvGpioInfo *gpio_info);

/*
 * Stop the execution of NvGpioWaitforInterruptEvent
 * after receiving current interrupt event.
 */
void NvGpioAbortInterruptWait(NvGpio_Handler *gpio_handler);

/** @} */

#endif /* end __NVGPIO_LIB_H__ */
