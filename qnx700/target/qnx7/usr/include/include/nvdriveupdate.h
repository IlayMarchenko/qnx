/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/*!
 * @file   nvdriveupdate.h
 * @brief <b>NVIDIA DRIVE Update</b>
 *
 * @b Description: This file declares APIs for the DRIVE update library
 * 'libnvdriveupdate'. Clients calling these APIs must run in the working
 * directory where the package is located.
 *
 */

#ifndef __NV_DRIVE_UPDATE_H_
#define __NV_DRIVE_UPDATE_H_

#include "nvcommon.h"
#include "flashtools_nverror.h"

/**
 * @defgroup group_drive_update_group DRIVE Update
 *
 * Performs updates with \c libnvdriveupdate.
 * Clients calling these APIs must run in the working
 * directory where the package is located.
 * @{
 */

/*!
 * Defines the types of package input source.
 * Use this enum with the package install APIs,
 * such as NvStartDeployPackage() and NvStopDeployPackage().
 */
typedef enum {
    NV_OTA_PKG_JSON,
    NV_OTA_PKG_ZIP
} NvPkgType;

/*!
 * Defines the types which contains the images that
 * the system can boot from.
 */
typedef enum
{
    NvBootChain_ChainA = 0,
    NvBootChain_ChainB,
    NvBootChain_Invalid = 0x7fffffff
} NvBootChain;

/*!
 * @brief Starts installing a package on a DriveUpdate instance.
 *
 * @param[in] pFileName The file name of the package, either absolute path or
 *            relative path where the package is located
 *
 * @param[in] PkgType   The type of the package input source.
 *                      Currently, only @ref NV_OTA_PKG_JSON is supported.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvStartDeployPackage(NvU8 *pFileName, NvPkgType PkgType);

/*!
 * @brief Cancels a package deploying process.
 * @warning Currently, this function is not fully implemented.
 *
 * @param[in] pFileName The file name of the package, either absolute path or
 *            relative path where the package is located
 *
 * @param[in] PkgType   The type of the package input source.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvCancelDeployPackage(NvU8 *pFileName, NvPkgType PkgType);

/*!
 * @brief Gets the progress of the package deploying process.
 * @warning Currently, this function is not fully implemented.
 *
 * @param[in]  pFileName The file name of the package, either absolute path or
 *             relative path where the package is located
 *
 * @param[out] pPercent  Percentage of the deploy progress of 0 to 100
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvGetDeployPackageProgress(NvU8 *pFileName, NvU32 *pPercent);

/*!
 * @brief Switches the bootchain of the host SoC on which DriveUpdate is running.
 *        This function reboots the host SoC to complete bootchain switch.
 *
 * @param[in] pABrBctPath Image path of partition brbct in A chain.
 *
 * @param[in] pBBrBctPath Image path of partition brbct in B chain.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvSwitchBootChain(NvS8 *pABrBctPath, NvS8 *pBBrBctPath);

/*!
 * @brief Gets the current boot chain type that the system has booted.
 *
 * @param[out] pBootChain The bootchain type that the system has booted.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvQueryBootChain(NvBootChain *pBootChain);

/*!
 * @brief Reboot the host tegra where DriveUpdate instance is running on.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 *
 */
NvError NvReboot(void);

/*!
 * @brief Reads the content of a partition.
 *
 * @param[in]     DeviceId Device ID of the device on which the BR BCT resides.
 *                Reserved for future usage, always pass zero for now.
 *
 * @param[in]     pPartName name of the partition to be read
 *
 * @param[out]    pBuffer Client-allocated buffer where the content of the
 *                partition will be filled in
 *
 * @param[in]     BufferSize The size of the buffer in bytes.
 *
 * @param[in]     Offset The offset of the partition to start reading from
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 */
NvError NvReadPartitionContent(
        NvU8  DeviceId,
        NvS8 *pPartName,
        NvU8 *pBuffer,
        NvU64 BufferSize,
        NvU64 Offset);

/*!
 * @brief Queries whether a partition exists in the partition table.
 *
 * @param[in]     DeviceId Device ID of the device where the BR BCT resides.
 *                Reserved for future usage, always pass zero for now.
 *
 * @param[in]     pPartName name of the partition.
 *
 * @param[out]    pIsPartPresent Set to NV_TRUE if partition is present.
 *                Set to NV_FALSE is partition is not found.
 *
 * @return @ref NvSuccess if successful, or the appropriate error code.
 */
NvError NvQueryIsPartitionPresent(
        NvU8     DeviceId,
        NvS8    *pPartName,
        NvBool  *pIsPartPresent);

/*!
 * @brief Erases a specified partition.
 *
 * @param[in]     DeviceId Device ID of the device where the BR BCT resides.
 *                Reserved for future usage, always pass zero for now.
 *
 * @param[in]     pPartName partition to be erased
 *
 * @return @ref NvSuccess if successful, or the appropriate error code
 *         otherwise.
 */
NvError NvErasePartitionContent(NvU8 DeviceId, NvS8 *pPartName);

/*!
 * @brief Determines whether the partition is erased.
 *
 * @param[in]     DeviceId Device ID of the device where the BR BCT resides.
 *                Reserved for future usage, always pass zero for now.
 *
 * @param[in]     pPartName name of the partition
 *
 * @param[out]    pIsPartErased The boolean that indicates if the partition is
 *                erased.
 * @return @ref NvSuccess if successful, or the appropriate error code.
 */
NvError NvQueryIsPartitionErased(
        NvU8    DeviceId,
        NvS8   *pPartName,
        NvBool *pIsPartErased);

/** @} */
#endif /* __NV_DRIVE_UPDATE_H_ */
