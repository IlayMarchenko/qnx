/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#if (!defined PLATFORM_TYPES_H)
#define PLATFORM_TYPES_H
/**
 * @file Platform_Types.h
 * @brief <b>Data type definitions</b>
 * @b Description: This file contains platform specific data type definitions.
 */

/** @brief Type definition of AUTOSAR standard type boolean */
typedef unsigned char boolean;

/** @brief Type definition of AUTOSAR standard type sint8 */
typedef signed char sint8;

/** @brief Type definition of AUTOSAR standard type sint16 */
typedef short sint16;

/** @brief Type definition of AUTOSAR standard type sint32 */
typedef int sint32;

/** @brief Type definition of AUTOSAR standard type uint8 */
typedef unsigned char uint8;

/** @brief Type definition of AUTOSAR standard type uint16 */
typedef unsigned short uint16;

/** @brief Type definition of AUTOSAR standard type uint32 */
typedef unsigned int uint32;

/** @brief Type definition of AUTOSAR standard type uint64 */
typedef unsigned long long int uint64;

/** @brief Type definition of AUTOSAR standard type sint8_least */
typedef signed int sint8_least;

/** @brief Type definition of AUTOSAR standard type sint16_least */
typedef signed int sint16_least;

/** @brief Type definition of AUTOSAR standard type sint32_least */
typedef signed int sint32_least;

/** @brief Type definition of AUTOSAR standard type uint8_least */
typedef unsigned int uint8_least;

/** @brief Type definition of AUTOSAR standard type uint16_least */
typedef unsigned int uint16_least;

/** @brief Type definition of AUTOSAR standard type uint32_least */
typedef unsigned int uint32_least;

/** @brief Type definition of AUTOSAR standard type float32 */
typedef float float32;

/** @brief Type definition of AUTOSAR standard type float64 */
typedef double float64;

#endif /* if (!defined PLATFORM_TYPES_H) */
