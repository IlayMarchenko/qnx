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
 * @file Eth_GeneralTypes.h
 * @brief <b>Header for General Types used in Eth Driver </b>
 * @b Description: Contains General type definitions and macros
 *                 for Ethernet Driver.
 */

#ifndef _ETH_GENERALTYPES_H_
#define _ETH_GENERALTYPES_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include <ComStack_Types.h>
#include <Eth_Cfg.h>

/*******************************************************************************
**                     Ethernet General Types                                 **
*******************************************************************************/

/* Specification: SWS_Eth_00175 */
/* Description: Ethernet buffer identifier type. */
typedef uint32 Eth_BufIdxType;

/* Specification: SWS_Eth_00156 */
/* Description: Implementation specific structure
 * of the post build configuration
 * Structure for Controller configuration(for initialization)
 */
typedef struct Eth_ConfigType
{
    /* Controller Index */
    uint8 CtrlIdx;
    /* Limits the maximum receive buffer length (frame length) in bytes */
    uint32  EthCtrlRxBufLenByte;
    /* Limits the maximum transmit buffer length (frame length) in bytes*/
    uint32  EthCtrlTxBufLenByte;
    /* Configures the number of receive buffers. */
    uint32 EthRxBufTotal;
    /* Configures the number of transmit buffers */
    uint32 EthTxBufTotal;
    /* Flag for Checking RxPolling behavior  */
    boolean EthRxPollEnable;
    /* Enable TimeStamp  */
    boolean EthEnableTimeStamp;
    /* Enable 1588v2  */
    boolean EthTimeStamp1588v2;
    /* Enable TimeStamp for all packets  */
    boolean EthTimeStampAllPkts;
    /* Enable 802.1as Mode  */
    boolean EthEnableMode8021AS;
    /* TCP/IP Checksum Offload */
    boolean EthChecksumOffload;
    /* Rx Interrupt Thread Priority*/
    uint32 EthRxThreadPri;
    /* Tx Interrupt Thread Priority*/
    uint32 EthTxThreadPri;
    /* Common Interrupt Thread Priority*/
    uint32 EthCommThreadPri;

} Eth_ConfigType;

/* Specification: SWS_Eth_00161 */
/* Description: This type defines the Ethernet data type used
 * for data transmission. Its definition depends
 * on the used CPU.
 */
typedef uint32 Eth_DataType;

/* Specification: SWS_Eth_00163 */
/* Description: The typedef enumeration Type Eth_Filter
 * ActionType describes the action to be taklen for the
 * MAC address given in *PhysAddrPtr.
 */
typedef enum Eth_FilterActionType
{
    ETH_ADD_TO_FILTER = 0, /* add the MAC address to the filter */
    ETH_REMOVE_FROM_FILTER /* remove the MAC address from the filter */
} Eth_FilterActionType;


/* Specification: SWS_Eth_00158 */
/* Description: This type defines the controller modes */
typedef enum Eth_ModeType
{
    ETH_MODE_DOWN = 0,  /* Controller disabled */
    ETH_MODE_ACTIVE,    /* Controller enabled */
} Eth_ModeType;

/* Specification: SWS_Eth_00160 */
/* Description: This type defines the Ethernet frame type
 * used in the Ethernet frame header.
 */
typedef uint16 Eth_FrameType;

/* Specification: SWS_Eth_00162 */
/* Description: Used as out parameter in Eth_Receive() indicates
 * whether a frame has been received and if so,
 * whether more frames are available or frames got lost.
 */
typedef enum Eth_RxStatusType
{
    /* Ethernet frame has been received, no further frames available */
    ETH_RECEIVED = 0,
    /* Ethernet frame has not been received, no further frames available */
    ETH_NOT_RECEIVED,
    /* Ethernet frame has been received, more frames are available */
    ETH_RECEIVED_MORE_DATA_AVAILABLE
} Eth_RxStatusType;

/* Specification: SWS_Eth_00177 */
/* Description: Depending on the HW, quality information regarding the
 * evaluated time stamp might be supported. If not
 * supported, the value shall be always Valid. For
 * Uncertain and Invalid values, the upper layer shall
 * discard the time stamp.
 */
typedef enum Eth_TimeStampQualType
{
    ETH_VALID = 0,
    ETH_INVALID,
    ETH_UNCERTAIN
} Eth_TimeStampQualType;

/* Specification: SWS_Eth_00178 */
/* Description: Variables of this type are used for expressing
 * time stamps including relative time
 * and absolute calendar time.
 */
typedef struct Eth_TimeStampType
{
    uint32 nanoseconds; /* Nanoseconds part of the time */
    uint32 seconds;     /* 32 bit LSB of the 48 bits Seconds part of the time */
    uint32 secondsHi;   /* 16 bit MSB of the 48 bits Seconds part of the time */
} Eth_TimeStampType;

/* Specification: SWS_Eth_00179 */
/* Description: Variables of this type are
 * used to express time differences.
 */
typedef struct Eth_TimeIntDiffType
{
    Eth_TimeStampType diff; /* time difference*/
    boolean sign;               /* Positive (True) / negative (False) time */
} Eth_TimeIntDiffType;

/* Specification: SWS_Eth_00180 */
/* Description: Variables of this type are used to
 * express frequency ratios.
 */
typedef struct Eth_RateRatioType
{
    /* IngressTimeStampSync2 - IngressTimeStampSync1 */
    Eth_TimeIntDiffType IngressTimeStampDelta;
    /* OriginTimeStampSync2[FUP2] - OriginTimeStampSync1[FUP1] */
    Eth_TimeIntDiffType OriginTimeStampDelta;
}Eth_RateRatioType;

#endif /* _ETH_GENERALTYPES_H_ */

