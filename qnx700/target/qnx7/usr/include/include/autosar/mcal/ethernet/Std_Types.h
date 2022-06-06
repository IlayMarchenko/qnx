/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#if (!defined STD_TYPES_H)
#define STD_TYPES_H
/**
 * @file Std_Types.h
 * @brief <b>AUTOSAR datatypes</b>
 * @b Description: This file contains AUTOSAR datatype definitions.
 */

#include <Platform_Types.h>

/** @brief Autosar definition for 'ON' */
#define STD_ON (1U)

/** @brief Autosar definition for 'OFF' */
#define STD_OFF (0U)

#if (!defined E_OK)
#define E_OK      (0U)
#endif

#if (!defined E_NOT_OK)
#define E_NOT_OK  (1U)
#endif

/*==================[type definitions]=======================================*/

/** @brief Autosar standard API return type */
typedef uint8 Std_ReturnType;

/** \brief return type for <Module_name>_GetVersionInfo() calls
 **
 ** This type is used to request the version of BSW module using the
 ** <Module_name>_GetVersionInfo() function. */
typedef struct
{
  uint16 vendorID;
  uint16 moduleID;
  uint8  sw_major_version;
  uint8  sw_minor_version;
  uint8  sw_patch_version;
}Std_VersionInfoType;

#endif /* if !defined( STD_TYPES_H ) */
