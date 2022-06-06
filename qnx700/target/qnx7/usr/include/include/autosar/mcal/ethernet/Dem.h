/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/**
 * @file Dem.h
 * @b Description: Contains diagnostic error management mechanisms.
 */

#ifndef _DEM_H
#define _DEM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include <Std_Types.h>

/*******************************************************************************
**                      Variable Definitions                                 **
*******************************************************************************/
typedef uint16 Dem_EventIdType;

/*******************************************************************************
**                      Macros                                               **
*******************************************************************************/
#ifndef DEM_EVENT_STATUS_PASSED
/** \brief Monitor reports qualified test result passed */
#define DEM_EVENT_STATUS_PASSED      0x00U
#endif

#ifndef DEM_EVENT_STATUS_FAILED
/** \brief Monitor reports qualified test result failed */
#define DEM_EVENT_STATUS_FAILED      0x01U
#endif

#ifndef DEM_EVENT_STATUS_PREPASSED
/** \brief Monitor reports non-qualified test result pre-passed
 ** (debounced Dem-internally) */
#define DEM_EVENT_STATUS_PREPASSED   0x02U
#endif

#ifndef DEM_EVENT_STATUS_PREFAILED
/** \brief Monitor reports non-qualified test result pre-failed
 ** (debounced Dem-internally) */
#define DEM_EVENT_STATUS_PREFAILED   0x03U
#endif


/** \brief Extended Production Errors */

#ifndef ETH_E_RX_FRAMES_LOST
/** \brief Ethernet Frames Lost. SWS_Eth_00174 */
#define ETH_E_RX_FRAMES_LOST 0xAEU
#endif

#ifndef ETH_E_CRC
/** \brief CRC Failure. SWS_Eth_00219 */
#define ETH_E_CRC 0xDBU
#endif


/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/** \brief Reports production error for a configured Dem event Id
 *
 *  \param[in] Dem Event Id
 *  \param[in] Dem Event Status
 */
void Dem_ReportErrorStatus(uint16 EventId, uint8 EventStatus);

#endif /* _DEM_H */
