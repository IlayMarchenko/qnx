/*
 * Copyright (c) 2016-2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifndef _NVCAN_H
#define _NVCAN_H

#if defined(__cplusplus)
extern "C" {
#endif
#include <stdint.h>
#include <time.h>

/**
 * \file
 * \brief <b> NVIDIA CAN Resource Manager API</b>
 *
 * @b Description: This file contains the CAN resource manager API.
 */

/**
 * @defgroup nvcan_group CAN Resource Manager API
 *
 * The Control Area Network (CAN) resource manager provides an interface for
 * managing interactions with the CAN controllers (nvcan).
 * @ingroup qnx_lib_group
 * @{
 */


/**
* \brief Defines the maximum length of the device name passed in NvCANOpen().
*/
#define MAX_DEVICE_NAME_LENGTH 5
#define MAX_RESMGR_NAME_LENGTH 40

#define CAN_FRAME_MAX_DATA_LEN 64

#define NVCAN_RESMGR_NAME "devc-nvcan"
#define NVCAN_RESMGR_PATH "/dev/nvcan"

#define NVCAN_TIMEOUT_INFINITE (0xFFFFFFFFFFFFFFFFU)

/**
* \brief Holds an nvcan handle.
*/
typedef void* NvCANHandle;

/**
* \brief Defines the error codes.
*/
typedef enum {
    NVCAN_STATUS_OK = 0U,
    NVCAN_STATUS_FAIL = 0x80000000U,
    NVCAN_STATUS_OUT_OF_MEMORY,
    NVCAN_STATUS_WRITE_QUEUE_FULL,
    NVCAN_STATUS_NOT_SUPPORTED,
    NVCAN_STATUS_INVALID_STATE,
    NVCAN_STATUS_INVALID_PARAMETER,
    NVCAN_STATUS_READ_TIMED_OUT,
    NVCAN_STATUS_RECOVER_TIMED_OUT,
    NVCAN_STATUS_BUS_OFF,
    NVCAN_STATUS_ERROR_PASSIVE
} NvCANStatus;

typedef enum {
    NVCAN_MODE_READ,
    NVCAN_MODE_WRITE
} NvCANMode;
/**
* \brief Defines the callback event codes
*/
typedef enum {
    /* Indicates that the CAN node is in "BUS OFF" State*/
    NVCAN_CALLBACK_EVENT_BUS_OFF_STATE = 1,
    /* Indicates that the CAN node is in "ERROR PASSIVE" State -
       atleast one of error counter (Tx and Rx) has reached the limit 128 */
    NVCAN_CALLBACK_EVENT_ERROR_PASSIVE_STATE,
    /* Indicates that atleast one of error counter (Tx and Rx)
       has reached the Error_Warning limit of 96 */
    NVCAN_CALLBACK_EVENT_ERROR_WARNING_STATE,
    /* Indicates Stuff Error */
    NVCAN_CALLBACK_EVENT_STUFF_ERROR,
    /* Indicates Form Error  */
    NVCAN_CALLBACK_EVENT_FORM_ERROR,
    /* Indicates Acknowledgement Error */
    NVCAN_CALLBACK_EVENT_ACK_ERROR,
    /* Indicates bit0 error */
    NVCAN_CALLBACK_EVENT_BIT0_ERROR,
    /* Indicates bit1 error */
    NVCAN_CALLBACK_EVENT_BIT1_ERROR,
    /* Indicates CRC error */
    NVCAN_CALLBACK_EVENT_CRC_ERROR,
    /* Indicates that some received CAN messages are lost due to lack of space */
    NVCAN_CALLBACK_EVENT_SOME_RX_MESSAGES_LOST,
    /* Indicates that no CAN bus event was detected since the last
       CPU read access to the protocol status register */
    NVCAN_CALLBACK_NO_CHANGE
} NvCANCallbackEvent;

/**
* \brief Defines the callback function pointer
*/
typedef void (*NvCANCallbackFuncPtr)(NvCANCallbackEvent eEvent);

/**
* Holds the CAN standard filter element.
*/
typedef struct {
    /** Holds the standard filter. The following values are supported:
       - 0= Range filter from \ref uStdFilterID1 to \ref uStdFilterID2.
       - 1= Dual ID filter for \a uStdFilterID1 or \a StdFilterID2.
       - 2= Classic filter: \a uStdFilterID1 = filter,
            \a uStdFilterID2 = mask.
       - 3= Filter element disabled.
     */
    uint8_t  uStdFilterType;
    /** Holds the standard filter configuration.
        The following values are supported:
       - 0= Disables the filter element.
       - 1= Stores in the Rx FIFO 0, if the filter matches.
       - 2= Stores in the Rx FIFO 1, if the filter matches.
       - 3= Rejects ID, if the filter matches.
     */
    uint8_t  uStdFilterConfig;
    /** Holds bit 0 - 10 : ID. */
    uint16_t uStdFilterID1;
    /** Holds bit 0 - 10 : ID. */
    uint16_t uStdFilterID2;
    uint16_t uStdFilterIndex;
} NvCANStdFilterElement;

/**
* Holds the CAN extended filter element.
*/
typedef struct {
    /** Holds the extended filter type. The following values are supported:
       - 0= Range filter from \ref uExtFilterID1 to \ref uExtFilterID2.
       - 1= Dual ID filter for \a uExtFilterID1 or \a uExtFilterID2.
       - 2= Classic filter: \a uExtFilterID1 = filter,
            \a uExtFilterID2 = mask.
     */
    uint8_t  uExtFilterType;
    /** Holds the extended filter configuration.
        The following values are supported:
       - 0= Disables filter element.
       - 1= Stores in the Rx FIFO 0, if the filter matches.
       - 2= Stores in the Rx FIFO 1, if the filter matches.
       - 3= Rejects ID, if the filter matches.
     */
    uint8_t  uExtFilterConfig;
    /* Bit 0 - 28 : ID */
    uint32_t uExtFilterID1;
    /* Bit 0 - 28 : ID */
    uint32_t uExtFilterID2;
    uint16_t uExtFilterIndex;
} NvCANExtFilterElement;

/**
* Holds the CAN configuration.
*/
typedef struct {
   /** Holds a Boolean that specifies whether to configure the standard
       CAN filter. */
   uint8_t bSetStdFilter;
   /** Holds the pointer to a standard filter element.
       Valid only when \ref bSetStdFilter is true. */
   NvCANStdFilterElement *pStdFilter;
   /* Holds a Boolean that specifies whether to configure the extended
      CAN filter. */
   uint8_t bSetExtFilter;
   /* Holds the pointer to an extended filter element.
      Valid only when \ref bSetExtFilter is true. */
   NvCANExtFilterElement *pExtFilter;
} NvCANConfig;

/**
* Holds CAN frame data.
*/
typedef struct {
    /** Holds the CAN ID, where:
     - Bit 0 - 28 : CAN identifier.
     - Bit 29     : type of frame (0 = data, 1 = error).
     - Bit 30     : RTR.
     - Bit 31     : frame format type (0 = std, 1 = ext).
     */
    uint32_t uCANId;
    /** Holds the data length. */
    uint8_t  uDataLen;
    /** Holds the CAN FD flags, where:
     - Bit 0 : 1 = BRS; 0 = Normal.
     - Bit 1 : 1 = Error Passive; 0 = Error Active.
     - Bit 2 : 1 = CAN FD; 0 = Normal.
     - Bit 4 : 1 = RX; 0 = Tx Direction.
     */
    uint8_t  uFlags;
    uint8_t  uReserved0;
    uint8_t  uReserved1;
    /** Holds the CAN data. */
    uint8_t  arrData[CAN_FRAME_MAX_DATA_LEN];
    /* Indicates if \ref RXTimestamp is synced within threshold (with system
     * time) or not */
    uint8_t bTimeStampSyncWithinThreshold;
    /** Holds Tegra's system clock time when CAN frame is received by
        the controller
     */
    struct timespec RxTimestamp;
} NvCANFrame;

/**
* \brief Defines union for devctl types that can be received
*/
typedef union {
    NvCANStdFilterElement pStdFilter;
    NvCANExtFilterElement pExtFilter;
    uint64_t pTimeoutNsec;
    uint64_t pRecoverTimeoutMsec;
    NvCANStatus pCANStatus;
} NvCANDevctl;

/**
  * Opens the specified nvcan device and gets a handle for communicating
  * with the nvcan module.
  *
  * This API must be called before interacting with nvcan module.
  *
  * @param[in] pHandle   A pointer to NvCANHandle created by nvcan module.
  * @param[in] pszDevice A pointer to a null terminated string containing
                         the device name.
  *                      Valid device names are \a can0 and \a can1.
  * @param[in] pCallback A pointer to the callback function.
  *                      If Client require notfications from nvcan, then callback function
  *                      is to be implemented and its pointer should be updated in pCallback.
  *                      Set pCallback to NULL if notifications are not required.
  * @param[in] eMode     enum of type \ref NvCANMode containing the CAN Open mode
  *                      should be NVCAN_MODE_READ for reading CAN messages and for
  *                      configuring CAN filters
  *                      should be NVCAN_MODE_WRITE for writing CAN messages
  *                      Recovering from bus off is supported in both modes
  * @return    NVCAN_STATUS_OK if successful, or the appropriate error code.
  */
NvCANStatus NvCANOpen(NvCANHandle *pHandle, const char *pszDevice,
                      NvCANCallbackFuncPtr pCallback, NvCANMode eMode);

/**
  * Configures the nvcan module.
  *
  * @param[in]  hNvCAN The handle that NvCANOpen() returned.
  * @param[in]  pCANConfig A pointer to \ref NvCANConfig.
  * @return     NVCAN_STATUS_OK if successful, or the appropriate error code.
  */
NvCANStatus NvCANConfigure(NvCANHandle hNvCAN, NvCANConfig *pCANConfig);

/**
  * Writes a CAN frame to the CAN controller.
  * The CAN controller sends this frame over the CAN bus.
  *
  * @param[in]  hNvCAN The handle that NvCANOpen() returned.
  * @param[in]  pCANFrame A pointer to NvCANFrame
  * @retval     NVCAN_STATUS_OK If successful.
  * @retval     NVCAN_STATUS_WRITE_QUEUE_FULL if the write queue in CAN
  *             controller is full.
  *             Otherwise, returns the appropriate error code.
  */
NvCANStatus NvCANWrite(NvCANHandle hNvCAN, NvCANFrame *pCANFrame);

/**
  * Reads the specified number of CAN frames from the CAN controller.
  *
  * @param[in]  hNvCAN The handle that NvCANOpen() returned.
  * @param[in]  pCANFrame A pointer to an array of \ref NvCANFrame structures.
  * @param[in]  uFramesToRead The number of frames to read.
  * @param[in]  pFramesRead A pointer to the number of frames actually read by
  *             the nvcan module.
  * @param[in]  uTimeoutNsec unsigned 64 bit integer containing time-interval in ns
  *             for which NvCANRead waits to receive a frame.
  * @retval     NVCAN_STATUS_OK If successful.
  * @retval     NVCAN_STATUS_READ_TIMED_OUT If there are no CAN frames in the read queue
  *             after waiting for timeout period.
  *             Otherwise, returns the appropriate error code.
  */
NvCANStatus NvCANRead(NvCANHandle hNvCAN, NvCANFrame *pCANFrame, uint32_t uFramesToRead,
                      uint32_t *pFramesRead, uint64_t uTimeoutNsec);

/**
  * Recovers from Bus off state
  *
  * @param[in]  hNvCAN The handle that NvCANOpen() returned.
  * @param[in]  uTimeoutMsec unsigned 64 bit integer containing time-interval in milliseconds
  *             The driver waits for \a uTimeoutMsec for CAN controller to recover
  *             from bus off. If the \a uTimeoutMsec is set to \ref NVCAN_TIMEOUT_INFINITE,
  *             then the API will return only after recovery is succesful
  * @retval     NVCAN_STATUS_OK if successful
  * @retval     NVCAN_STATUS_RECOVER_TIMED_OUT If recovery is not successful within the
  *             time interval \a uTimeoutMsec
  *             Otherwise, returns the appropriate error code.
  */
NvCANStatus NvCANRecoverFromBusOff(NvCANHandle hNvCAN, uint64_t uTimeoutMsec);

/**
  * Gets the CAN controller's status (error passive / bus off)
  *
  * @param[in] hNvCAN The handle that NvCANOpen() returned.
  * @return    NVCAN_STATUS_BUS_OFF if CAN controller is in bus off state.
  *            NVCAN_STATUS_ERROR_PASSIVE if CAN controller is in error passive state.
  *            NVCAN_STATUS_OK if it is in any other state, or the appropriate error code.
  */
NvCANStatus NvCANGetStatus(NvCANHandle hNvCAN);

/**
  * Closes the nvcan device.
  *
  * @param[in]  hNvCAN The handle that NvCANOpen() returned.
  * @return     NVCAN_STATUS_OK if successful, or the appropriate error code.
  */
NvCANStatus NvCANClose(NvCANHandle hNvCAN);

/** @} */

#if defined(__cplusplus)
}
#endif
#endif//#define _NVCAN_H
