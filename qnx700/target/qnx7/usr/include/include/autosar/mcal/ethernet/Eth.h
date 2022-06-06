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
 * @file Eth.h
 * @brief <b>Interface to MCAL ETHERNET CONTOLLER</b>
 * @b Description: Contains type definitions and API declarations
 *                 for MCAL Eth (Eth driver).
 */

#ifndef _ETH_H
#define _ETH_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* General Eth type declarations */
#include <Eth_GeneralTypes.h>

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define ETH_INSTANCE_ID     ((uint8)0U)
#define ETH_VENDOR_ID       ((uint16)65535U) /* Placeholder */
#define ETH_MODULE_ID       ((uint16)88U)

/* Specification: SWS_Eth_00016 Error IDs */
/* Invalid controller index */
#define ETH_E_INV_CTRL_IDX      ((uint8)0x01)

/* Eth module or controller was not initialized */
#define ETH_E_NOT_INITIALIZED   ((uint8)0x02)

/* Invalid pointer in parameter list*/
#define ETH_E_PARAM_POINTER     ((uint8)0x03)

/* Invalid parameter */
#define ETH_E_INV_PARAM         ((uint8)0x04)

/* Invalid mode */
#define ETH_E_INV_MODE          ((uint8)0x05)


/* API Service IDs */
/* API Service ID for Eth_Init */
#define ETH_SID_INIT                        ((uint8)0x01U)

/* API Service ID for Eth_SetControllerMode */
#define ETH_SID_SET_CONTROLLER_MODE         ((uint8)0x03U)

/* API Service ID for Eth_GetControllerMode */
#define ETH_SID_GET_CONTROLLER_MODE         ((uint8)0x04U)

/* API Service ID for Eth_GetPhysAddr */
#define ETH_SID_GET_PHYS_ADDR               ((uint8)0x08U)

/* API Service ID for Eth_SetPhysAddr */
#define ETH_SID_SET_PHYS_ADDR               ((uint8)0x13U)

/* API Service ID for Eth_UpdatePhysAddrFilter */
#define ETH_SID_UPDATE_PHYS_ADDR_FILTER     ((uint8)0x12U)

/* API Service ID for Eth_WriteMii */
#define ETH_SID_WRITE_MII                   ((uint8)0x05U)

/* API Service ID for Eth_ReadMii */
#define ETH_SID_READ_MII                    ((uint8)0x06U)

/* API Service ID for Eth_GetDropCount */
#define ETH_SID_GET_DROP_COUNT              ((uint8)0x14U)

/*  Service ID for Eth_GetEtherStats */
#define ETH_SID_GET_ETHER_STATS             ((uint8)0x15U)

/* API Service ID for Eth_GetCurrentTime */
#define ETH_SID_GET_CURRENT_TIME            ((uint8)0x16U)

/* API Service ID for Eth_EnableEgressTimeStamp */
#define ETH_SID_ENABLE_EGRESS_TIME_STAMP    ((uint8)0x17U)

/* API Service ID for Eth_GetEgressTimeStamp */
#define ETH_SID_GET_EGRESS_TIME_STAMP       ((uint8)0x18U)

/* API Service ID for Eth_GetIngressTimeStamp */
#define ETH_SID_GET_INGRESS_TIME_STAMP      ((uint8)0x19U)

/* API Service ID for Eth_SetCorrectionTime */
#define ETH_SID_SET_CORRECTION_TIME         ((uint8)0x1aU)

/* API Service ID for Eth_SetGlobalTime */
#define ETH_SID_SET_GLOBAL_TIME             ((uint8)0x1bU)

/* API Service ID for Eth_ProvideTxBuffer */
#define ETH_SID_PROVIDE_TX_BUFFER           ((uint8)0x09U)

/* API Service ID for Eth_Transmit */
#define ETH_SID_TRANSMIT                    ((uint8)0xaU)

/* API Service ID for Eth_Receive */
#define ETH_SID_RECEIVE                     ((uint8)0xbU)

/* API Service ID for Eth_TxConfirmation */
#define ETH_SID_TX_CONFIRMATION             ((uint8)0xcU)

/* API Service ID for Eth_GetVersionInfo */
#define ETH_SID_GET_VERSION_INFO            ((uint8)0xdU)

/* API Service ID for Eth_MainFunction */
#define ETH_SID_MAIN_FUNCTION               ((uint8)0x0aU)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/* Specification: SWS_Eth_00157 */
/* Description: Ethernet Driver specific return type. */
typedef enum Eth_ReturnType
{
    ETH_OK = 0,     /* success */
    ETH_E_NOT_OK,   /* general failure */
    ETH_E_NO_ACCESS /* Ethernet hardware access failure */
} Eth_ReturnType;

/* Specification: SWS_Eth_00159 */
/* Description: Status supervision used for Development
 * Error Detection. The state shall be
 * available for debugging.
 */
typedef enum Eth_StateType
{
    ETH_STATE_UNINIT = 0,   /* Driver is not yet configured */
    ETH_STATE_INIT          /* Driver is configured */
} Eth_StateType;

/*
Type: Eth_Status_t
This type defines the range of specific Status values for Ethernet Driver.
*/
typedef uint8 Eth_State_t;
typedef uint8 Eth_Mode_t;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

#define ETH_START_GLOBAL_VAR_8BIT
/* MISRA RULE 20.1 violation. Status file inclusion after pre-processor
directive is allowed only for Eth_MemMap.h. */
#include <Eth_MemMap.h>


#define ETH_STOP_GLOBAL_VAR_8BIT
/* MISRA RULE 20.1 violation. Status file inclusion after pre-processor
directive is allowed only for Eth_MemMap.h. */
#include <Eth_MemMap.h>

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
#define ETH_START_SEC_CODE
/* MISRA RULE 20.1 violation. Status file inclusion after pre-processor
directive is allowed only for Eth_MemMap.h. */
#include <Eth_MemMap.h>

/* Specification: SWS_Eth_00027 */
void Eth_Init(
    const Eth_ConfigType *CfgPtr
);

/* Specification: SWS_Eth_00041 */
Std_ReturnType Eth_SetControllerMode(
    uint8 CtrlIdx,
    Eth_ModeType CtrlMode
);

/* Specification: SWS_Eth_00046 */
Std_ReturnType Eth_GetControllerMode(
    uint8 CtrlIdx,
    Eth_ModeType* CtrlModePtr
);

/* Specification: SWS_Eth_00052 */
void Eth_GetPhysAddr(
    uint8 CtrlIdx,
    uint8* PhysAddrPtr
);

/* Specification: SWS_Eth_00151 */
void Eth_SetPhysAddr(
    uint8 CtrlIdx,
    const uint8* PhysAddrPtr
);

/* Specification: SWS_Eth_00152 */
Std_ReturnType Eth_UpdatePhysAddrFilter(
    uint8 CtrlIdx,
    const uint8* PhysAddrPtr,
    Eth_FilterActionType Action
);

/* Specification: SWS_Eth_00058 */
Std_ReturnType Eth_WriteMii(
    uint8 CtrlIdx,
    uint8 TrcvIdx,
    uint8 RegIdx,
    uint16 RegVal
);

/* Specification: SWS_Eth_00064 */
Std_ReturnType Eth_ReadMii(
    uint8 CtrlIdx,
    uint8 TrcvIdx,
    uint8 RegIdx,
    uint16* RegValPtr
);

/* Specification: SWS_Eth_00226 */
Std_ReturnType Eth_GetDropCount(
    uint8 CtrlIdx,
    uint8 CountValues,
    uint32* DropCount
);

/* Specification: SWS_Eth_00233 */
Std_ReturnType Eth_GetEtherStats(
    uint8 CtrlIdx,
    uint32* etherStats
);

/* Specification: SWS_Eth_00181 */
Std_ReturnType Eth_GetCurrentTime(
    uint8 CtrlIdx,
    Eth_TimeStampQualType* timeQualPtr,
    Eth_TimeStampType* timeStampPtr
);

/* Specification: SWS_Eth_00186 */
void Eth_EnableEgressTimeStamp(
    uint8 CtrlIdx,
    uint8 BufIdx
);

/* Specification: SWS_Eth_00190 */
void Eth_GetEgressTimeStamp(
    uint8 CtrlIdx,
    uint8 BufIdx,
    Eth_TimeStampQualType* timeQualPtr,
    Eth_TimeStampType* timeStampPtr);

/* Specification: SWS_Eth_00195 */
void Eth_GetIngressTimeStamp(
    uint8 CtrlIdx,
    Eth_DataType* DataPtr,
    Eth_TimeStampQualType* timeQualPtr,
    Eth_TimeStampType* timeStampPtr);

/* Specification: SWS_Eth_00200 */
void Eth_SetCorrectionTime(
    uint8 CtrlIdx,
    const Eth_TimeIntDiffType* timeOffsetPtr,
    const Eth_RateRatioType* rateRatioPtr
);

/* Specification: SWS_Eth_00205 */
Std_ReturnType Eth_SetGlobalTime(
    uint8 CtrlIdx,
    const Eth_TimeStampType* timeStampPtr
);

/* Specification: SWS_Eth_00077 */
BufReq_ReturnType Eth_ProvideTxBuffer(
    uint8 CtrlIdx,
    Eth_BufIdxType* BufIdxPtr,
    uint8** BufPtr,
    uint16* LenBytePtr
);

/* Specification: SWS_Eth_00087 */
Std_ReturnType Eth_Transmit(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    Eth_FrameType FrameType,
    boolean TxConfirmation,
    uint16 LenByte,
    const uint8* PhysAddrPtr
);

/* Specification: SWS_Eth_00095 */
void Eth_Receive(
    uint8 CtrlIdx,
    Eth_RxStatusType* RxStatusPtr
);

/* Specification: SWS_Eth_00100 */
void Eth_TxConfirmation(
    uint8 CtrlIdx
);

/* Specification: SWS_Eth_00106 */
void Eth_GetVersionInfo(
    Std_VersionInfoType *VersionInfoPtr
);

/* Customer requested for this */
void Eth_DeInit(void);

/*******************************************************************************
**                      Scheduled Function Declarations                       **
*******************************************************************************/
/* Eth Main Function */
void Eth_MainFunction(void);

#define ETH_STOP_SEC_CODE
/* MISRA RULE 20.1 violation. Status file inclusion after pre-processor
directive is allowed only for Eth_MemMap.h. */
#include <Eth_MemMap.h>

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

#endif /* _ETH_H */
