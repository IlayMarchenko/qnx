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
 * @file Eth_MemMap.h
 * @brief <b>Header for ETH Memory Section Management</b>
 * @b Description: Contains memory section macros.
 */

/*******************************************************************************
**                      Includes - MemMap extensions                          **
*******************************************************************************/

/*******************************************************************************
**                     Memory Section Macros                                  **
*******************************************************************************/

#if (defined ETH_START_SEC_CODE)
    #undef ETH_START_SEC_CODE

#elif (defined ETH_STOP_SEC_CODE)
    #undef ETH_STOP_SEC_CODE

#elif (defined ETH_START_GLOBAL_VAR_8BIT)
    #undef ETH_START_GLOBAL_VAR_8BIT

#elif (defined ETH_STOP_GLOBAL_VAR_8BIT)
    #undef ETH_STOP_GLOBAL_VAR_8BIT

#elif (defined ETH_START_GLOBAL_VAR_32BIT)
    #undef ETH_START_GLOBAL_VAR_32BIT

#elif (defined ETH_STOP_GLOBAL_VAR_32BIT)
    #undef ETH_STOP_GLOBAL_VAR_32BIT
#endif

