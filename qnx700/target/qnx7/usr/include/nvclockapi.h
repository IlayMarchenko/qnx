/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __CLOCKAPI_H__
#define __CLOCKAPI_H__

#include "nvcommon.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define NVCLOCK_BUF_SIZE 100
#define NVCLOCK_CLK_DEFAULT 0xFFFFU /* NOTE: Keeping 0xFFFF as DEFAULT value */
#define NVCLOCK_RESET_DEFAULT 0xFFFFU /* NOTE: Keeping 0xFFFF as DEFAULT value */
#define MAX_CLK_DVFS_FREQS 50

typedef NvU32 NvClockClock;
typedef NvU32 NvClockReset;

enum {
    NVCLK_ROOT = 0,
    NVCLK_CLOCK_TREE,
    NVCLK_GET_SOURCE_CLK_FREQ,
    NVCLK_GET_CLK_FREQ,
    NVCLK_GET_DEVICE_CLK_FREQ,
    NVCLK_GET_MAX_DEVICE_CLK_FREQ,
    NVCLK_GET_DEVICE_CLK_STATUS,
    NVCLK_GET_DEVICE_RST_STATUS,
    NVCLK_DEVICE_CLK_CONTROL,
    NVCLK_DEVICE_RST_CONTROL,
    NVCLK_RESET_DEVICE,
    NVCLK_RESET_AND_DISABLE_DEVICE,
    NVCLK_RESET_AND_ENABLE_DEVICE,
    NVCLK_GET_DEVICE_CLK_SRC,
    NVCLK_CHANGE_DEVICE_CLK_SRC,
    NVCLK_GET_COUNT_OF_DEVICES_USING_CLK_SRC,
    NVCLK_SET_DEVICE_FREQ,
    NVCLK_SET_CLOCK_FREQ,
    NVCLK_SET_MAX_DEVICE_FREQ,
    NVCLK_CLEAR_REFERENCE_COUNT,
    NVCLK_GET_VERB_LEVEL,
    NVCLK_SET_VERB_LEVEL,
    NVCLK_CLK_NUM_TO_NAME,
    NVCLK_CLK_NAME_TO_NUM,
    NVCLK_RST_NUM_TO_NAME,
    NVCLK_RST_NAME_TO_NUM,
    NVCLK_GET_CLK_FREQ_LIST,
    NVCLK_IMPL_LIB_API_WRAPPER,
    NVCLK_MAX_FILE_IDS
};

typedef enum {
    NvClockBpmpCommFailed   = -3,  /* Communication with Bpmp failed */
    NvClockDaemonCommFailed = -2,  /* Communication with clock daemon failed */
    NvClockError            = -1,  /* Any other Error */
    NvClockSuccess          = 0,   /* Success */
} NvClockErrCode;

typedef enum {
    NVCLK_CONFIG_BOOTLOADER,
    NVCLK_CONFIG_LINUX_STARTUP,
    NVCLK_CONFIG_QNX_STARTUP,
} NvClockConfigStage;

typedef enum {
    NVCLK_RESET_ONLY,
    NVCLK_ENABLE_ONLY,
    NVCLK_DISABLE_ONLY,
    NVCLK_RESET_AND_ENABLE,
} NvClockAction;

typedef enum {
    NVCLK_CLKSTATE_OFF = 0,
    NVCLK_CLKSTATE_ON
} NvClockState;

typedef enum {
    NVCLK_RSTSTATE_REMOVE = 0,
    NVCLK_RSTSTATE_APPLY
} NvResetState;

typedef struct ClockMsgData {
    union {
        char Buf[NVCLOCK_BUF_SIZE];
        NvU32 U32Data;
        NvS32 S32Data;
    } SendData;

    union {
        char BufVal[NVCLOCK_BUF_SIZE];
        struct FTable {
            NvU32 FTblSize;
            NvU32 FTbl[MAX_CLK_DVFS_FREQS];
        } FreqTable;
    } RecvData;

    NvClockErrCode Ret;
} NvClockMsgData;

/**
 * Set Verobse Level
 * @VerbLevel - Verbose level to be set
 */
NvClockErrCode NvClockSetVerboseLevel(NvS32 VerbLevel);

/**
 * Get Verobse Level
 * @VerbLevel - Holds the result
 */
NvClockErrCode NvClockGetVerboseLevel(NvS32 *VerbLevel);

/**
 * Get Source Clock frequency.
 * @ClockId     - Source Clock ID
 * @Frequency   - Holds the result
 */
NvClockErrCode NvClockGetSourceClockFreq(NvClockClock ClockId, NvS32 *Frequency);

/**
 * Get Clock frequency in Hz.
 * @ClockId     - Source Clock ID
 * @Frequency   - Holds the result
 */
NvClockErrCode NvClockGetClockFreqHz(NvClockClock ClockId, NvS64 *Frequency);

/**
 * Get the device clock frequency.
 * @ClockId     - Device Clock ID
 * @Frequency   - Holds the result
 */
NvClockErrCode NvClockGetDeviceClockFreq(NvClockClock ClockId, NvS32 *Frequency);

/**
 * Enable/Disable clock to a module/device.
 * @ClockId  - Device Clock ID
 * @ClkState - Clock State [boolean: 1/0 or on/off or enable/disable]
 */
NvClockErrCode NvClockDeviceClockControl(NvClockClock ClockId,
    const char *ClkState);

/**
 * Set/Clear Reset to a module/device.
 * @ResetId  - Device Reset ID
 * @RstState - Reset State [boolean: 1/0 or set/clear]
 */
NvClockErrCode NvClockDeviceResetControl(NvClockReset ResetId,
    const char *RstState);

/**
 * Get device clock status.
 * @ClockId     - Device Clock ID
 * @ClockStatus - Holds the result
 */
NvClockErrCode NvClockGetDeviceClockStatus(NvClockClock ClockId, NvU32 *ClockStatus);

/**
 * Get device reset status.
 * @ResetId     - Device Reset ID
 * @ResetStatus - Holds the result
 */
NvClockErrCode NvClockGetDeviceResetStatus(NvClockReset ResetId, NvU32 *ResetStatus);

/**
 * Reset a device.
 * After calling this function the device will be reset and it's original
 * reset state will be restored.
 * @ResetId - Device Reset ID
 */
NvClockErrCode NvClockResetDevice(NvClockReset ResetId);

/**
 * Reset and disable device.
 * After calling this function the device will be in reset and the clock
 * will be disabled.
 * @ResetId - Device Reset ID
 * @ClockId - Device Clock ID
 */
NvClockErrCode NvClockResetAndDisableDevice(NvClockReset ResetId, NvClockClock ClockId);

/**
 * Reset and enable device.
 * After calling this function the device will be out of reset and the clock
 * will be enabled.
 * @ResetId - Device Reset ID
 * @ClockId - Device Clock ID
 */
NvClockErrCode NvClockResetAndEnableDevice(NvClockReset ResetId, NvClockClock ClockId);

/**
 * Get Device Clock source info.
 * @ClockId     - Device Clock ID
 * @ClkSrcId    - Holds the result
 */
NvClockErrCode NvClockGetDeviceClockSource(NvClockClock ClockId, NvClockClock *ClkSrcId);

/**
 * Change Device Parent clock.
 * @ClockId     - Device Clock ID
 * @SrcId       - Source Clock ID
 */
NvClockErrCode NvClockChangeDeviceClockSource(NvClockClock ClockId, NvClockClock SrcId);

/**
 * Get Count of devices using ClockId as their Parent Clock.
 * @ClockId  - Source Clock ID
 * @Count    - Holds the result
 */
NvClockErrCode NvClockGetCountOfDevicesUsingClockSource(NvClockClock ClockId, NvU32 *Count);

/**
 * Set Device's frequency to a desired Frequency.
 * @ClockId    - Device Clock ID
 * @Frequency  - New target frequency [in KHz]
 * @DevSpecialFlags - Device special flags
 */
NvClockErrCode NvClockSetDeviceClockFreq(NvClockClock ClockId, NvS32 Frequency, NvU32 DevSpecialFlags);

/**
 * Set clock frequency in Hz.
 * @ClockId    - Device Clock ID
 * @Frequency  - New target frequency [in Hz]
 */
NvClockErrCode NvClockSetClockFreqHz(NvClockClock ClockId, NvS64 Frequency);

/**
 * Get the maximum frequency at which a device can run at.
 * @ClockId         - Device Clock ID
 * @MaxFrequency    - Holds the result
 */
NvClockErrCode NvClockGetMaxDeviceClockFreq(NvClockClock ClockId, NvS32 *MaxFrequency);

/**
 * Set Device's frequency to it's Maximum Frequency.
 * @ClockId    - Device Clock ID
 * @DevSpecialFlags - Device special flags
 */
NvClockErrCode NvClockSetMaxDeviceClockFreq(NvClockClock ClockId, NvU32 DevSpecialFlags);

/**
 * Clear OS local reference counts for all Clocks and Resets.
 */
NvClockErrCode NvClockClearRefCount(void);

/**
 * Get clock frequency list for clock id - ClockId
 * @ClockId         - Source Clock ID
 * @FreqTableSize   - Holds the size of the frequency table
 * @FreqTable       - Holds the frequency table
 */
NvClockErrCode NvClockGetClockFreqList(NvClockClock ClockId, NvU32 *FreqTableSize, NvU32 FreqTable[]);

/**
 * Convert Clock Name to Clock Number
 * @ClkName     - Clock Name
 * @ClockId     - Holds the result
 */
NvClockErrCode NvClockClkNameToNum(const char *ClkName, NvClockClock *ClockId);

/**
 * Convert Clock Number to Clock Name
 * @ClockId   - Clock ID
 * @ClkName   - Holds the result
 */
NvClockErrCode NvClockClkNumToName(NvClockClock ClockId, char *ClkName);

/**
 * Convert Reset Name to Reset Number
 * @RstName     - Reset Name
 * @ResetId     - Holds the result
 */
NvClockErrCode NvClockRstNameToNum(const char *RstName, NvClockReset *ClockId);

/**
 * Convert Reset Number to Reset Name
 * @ResetId   - Reset ID
 * @RstName   - Holds the result
 */
NvClockErrCode NvClockRstNumToName(NvClockReset ResetId, char *RstName);

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif  // __CLOCKAPI_H__
