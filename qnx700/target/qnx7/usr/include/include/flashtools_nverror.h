/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

/**
 * @file
 * @brief <b>NVIDIA Flashtools Interface: Error Handling </b>
 *
 * @b Description: This file declares APIs for errors.
 */

#ifndef INCLUDED_FLASHTOOLS_NVERROR_H
#define INCLUDED_FLASHTOOLS_NVERROR_H

/**
 * @defgroup flashtools_nverror Flashtools Error Handling
 *
 * Contains error code enumeration and helper macros.
 * @{
 */

/**
 * The NvError enumeration contains ALL return / error codes.  Error codes
 * are specifically explicit to make it easy to identify where an error
 * came from.
 *
 * @ingroup nv_errors
 */
typedef enum
{

    NvError_Success                     = 0x00000000,
    NvError_NotImplemented              = 0x00000001,
    NvError_NotSupported                = 0x00000002,
    NvError_NotInitialized              = 0x00000003,
    NvError_BadParameter                = 0x00000004,
    NvError_Timeout                     = 0x00000005,
    NvError_InsufficientMemory          = 0x00000006,
    NvError_ReadOnlyAttribute           = 0x00000007,
    NvError_InvalidState                = 0x00000008,
    NvError_InvalidAddress              = 0x00000009,
    NvError_InvalidSize                 = 0x0000000A,
    NvError_BadValue                    = 0x0000000B,
    NvError_AlreadyAllocated            = 0x0000000C,
    NvError_Busy                        = 0x0000000D,
    NvError_ModuleNotPresent            = 0x0000000E,
    NvError_ResourceError               = 0x0000000F,
    NvError_CountMismatch               = 0x00000010,
    NvError_OverFlow                    = 0x00000011,
    NvError_ImageCorrupted              = 0x00000012,
    NvError_BadImage                    = 0x00000013,
    NvError_FuseBurningTempReadFailure  = 0x00000014,
    NvError_Mb1PartialUpdate            = 0x00000015,
    NvError_Sc7PartialUpdate            = 0x00000016,
    NvError_MtsPartialUpdate            = 0x00000017,
    NvError_Mb1OemSwRatchetSanityCheckFailed = 0x00000018,
    NvError_MtsOemSwRatchetSanityCheckFailed = 0x00000019,
    NvError_MtsRatchetScratchNotInitialized = 0x0000001a,
    NvError_Sc7OemSwRatchetSanityCheckFailed = 0x0000001b,
    NvError_Mb1Sc7OemSwRatchetMismatch = 0x0000001c,
    NvError_HashMismatch               = 0x0000001d,
    NvError_ImageMismatch               = 0x0000001e,
    Nverror_InvalidPtLayout             = 0x0000001f,
    NvError_BCHNotCached                = 0x00000020,
    NvError_FuseBurningTempLow          = 0x00000021,
    NvError_FuseBurningTempHigh         = 0x00000022,
    NvError_ECIDMisMatch                = 0x00000023,
    NvError_InActiveBinInvalid          = 0x00000024,

    NvError_FileWriteFailed             = 0x00030000,
    NvError_FileReadFailed              = 0x00030001,
    NvError_EndOfFile                   = 0x00030002,
    NvError_FileOperationFailed         = 0x00030003,
    NvError_DirOperationFailed          = 0x00030004,
    NvError_EndOfDirList                = 0x00030005,
    NvError_ConfigVarNotFound           = 0x00030006,
    NvError_InvalidConfigVar            = 0x00030007,
    NvError_MemoryMapFailed             = 0x0003000a,
    NvError_IoctlFailed                 = 0x0003000f,
    NvError_AccessDenied                = 0x00030010,
    NvError_DeviceNotFound              = 0x00030011,
    NvError_KernelDriverNotFound        = 0x00030012,
    NvError_FileNotFound                = 0x00030013,
    NvError_InvalidArgument             = 0x00030014,
    NvError_ProcessNotFound             = 0x00030015,
    NvError_Deadlock                    = 0x00030016,
    NvError_FileNameNotExist            = 0x00030017,
    NvError_PartitionNotExist           = 0x00030018,
    NvError_DeviceFailToRegister        = 0x00030019,
    NvError_SystemCommandFailed         = 0x0003001A,
    NvError_CorruptedBuffer             = 0x0003000B,

    NvError_SdioCardNotPresent          = 0x00042000,
    NvError_SdioInstanceTaken           = 0x00042001,
    NvError_SdioControllerBusy          = 0x00042002,
    NvError_SdioReadFailed              = 0x00042003,
    NvError_SdioWriteFailed             = 0x00042004,
    NvError_SdioBadBlockSize            = 0x00042005,
    NvError_SdioClockNotConfigured      = 0x00042006,
    NvError_SdioSdhcPatternIntegrityFailed = 0x00042007,
    NvError_SdioCommandFailed           = 0x00042008,
    NvError_SdioCardAlwaysPresent       = 0x00042009,
    NvError_SdioAutoDetectCard          = 0x0004200a,

    NvError_SdMmcRecoveryFailed         = 0x00043001,
    NvError_SdMmcTransferStateTimeout   = 0x00043002,
    NvError_SdMmcStandByStateTimeout    = 0x00043003,
    NvError_SdMmcIdleStateTimeout       = 0x00043004,

    NvError_I2cReadFailed               = 0x00045000,
    NvError_I2cWriteFailed              = 0x00045001,
    NvError_I2cDeviceNotFound           = 0x00045003,
    NvError_I2cInternalError            = 0x00045004,
    NvError_I2cArbitrationFailed        = 0x00045005,
    NvError_I2CCommunicationError       = 0x00045006,

    NvError_IdeHwError                  = 0x00046000,
    NvError_IdeReadError                = 0x00046001,
    NvError_IdeWriteError               = 0x00046002,
    NvError_VsWriteError                = 0x00046003,
    NvError_VsReadError                 = 0x00046004,

    NvError_ChipSkuClockLimitViolation  = 0x00180000,
    NvError_ChipSkuNumCoreViolation     = 0x00180001,
    NvError_ChipSkuDmaFuseReadFail      = 0x00180002,
    NvError_ChipSkuNoTableEntry         = 0x00180003,
    NvError_ChipSkuInvalidDividerValue  = 0x00180004,
    NvError_MCMRevFuseReadFail          = 0x00180005,

    // An alias for success
    NvSuccess = NvError_Success,

    NvError_Force32 = 0x7FFFFFFF
} NvError;

#endif // INCLUDED_FLASHTOOLS_NVERROR_H
