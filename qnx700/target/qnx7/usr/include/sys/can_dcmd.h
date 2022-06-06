/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */


#ifndef __CAN_DCMD_H_INCLUDED
#define __CAN_DCMD_H_INCLUDED

#include <stdint.h>

#ifndef _DEVCTL_H_INCLUDED
    #include <devctl.h>
#endif

#define CAN_MSG_DATA_MAX        0x8        /* Max number of data bytes in a CAN message as defined by CAN spec */
#define CAN_MSG_MID_UNKNOWN     UINT32_MAX /* Set by libcan when write() is used instead of a devctl */

/* CAN mailbox type */
typedef enum
{
    CANDEV_MODE_IO,        /* All mailboxes are set up to tx/rx specific message IDs */
    CANDEV_MODE_RAW_FRAME  /* One rx and one tx mailbox for any frame, use devctl to
                              tx/rx fully defined CAN frames */
} CANDEV_MODE;

/* Extended CAN Message */
typedef struct can_msg_ext {
    uint32_t        timestamp;         /* CAN message timestamp */
    uint32_t        is_extended_mid;   /* 1=29-bit MID, 0=11-bit MID */
    uint32_t        is_remote_frame;   /* 1=remote frame request, 0=data frame */
} CAN_MSG_EXT;

/* CAN Message */
typedef struct can_msg {
    /* Pre-allocate CAN messages to the max data size */
    uint8_t         dat[CAN_MSG_DATA_MAX];  /* CAN message data */
    uint8_t         len;                    /* Actual CAN message data length */
    uint32_t        mid;                    /* CAN message identifier */
    CAN_MSG_EXT     ext;                    /* Extended CAN message info */
} CAN_MSG;

/* Generic CAN Devctl Error Structure - meaning is device specific */
typedef struct can_devctl_error {
    uint32_t        drvr1;
    uint32_t        drvr2;
    uint32_t        drvr3;
    uint32_t        drvr4;
} CAN_DEVCTL_ERROR;

typedef struct can_devctl_stats {
    uint32_t        transmitted_frames;
    uint32_t        received_frames;
    uint32_t        missing_ack;
    uint32_t        total_frame_errors;
    uint32_t        stuff_errors;
    uint32_t        form_errors;
    uint32_t        dom_bit_recess_errors;
    uint32_t        recess_bit_dom_errors;
    uint32_t        parity_errors;
    uint32_t        crc_errors;
    uint32_t        hw_receive_overflows;
    uint32_t        sw_receive_q_full;
    uint32_t        error_warning_state_count;
    uint32_t        error_passive_state_count;
    uint32_t        bus_off_state_count;
    uint32_t        bus_idle_count;
    uint32_t        power_down_count;
    uint32_t        wake_up_count;
    uint32_t        rx_interrupts;
    uint32_t        tx_interrupts;
    uint32_t        total_interrupts;
} CAN_DEVCTL_STATS;


typedef struct can_devctl_info {
    char            description[64];    /* CAN device description */
    uint32_t        msgq_size;          /* Number of message queue objects */
    uint32_t        waitq_size;         /* Number of client wait queue objects */
    CANDEV_MODE     mode;               /* CAN driver mode - I/O or raw frames */
    uint32_t        bit_rate;           /* Bit rate */
    uint16_t        bit_rate_prescaler; /* Bit rate prescaler */
    uint8_t         sync_jump_width;    /* Time quantum Sync Jump Width */
    uint8_t         time_segment_1;     /* Time quantum Time Segment 1 */
    uint8_t         time_segment_2;     /* Time quantum Time Segment 2 */
    uint32_t        num_tx_mboxes;      /* Number of TX Mailboxes */
    uint32_t        num_rx_mboxes;      /* Number of RX Mailboxes */
    uint32_t        loopback_external;  /* External loopback is enabled */
    uint32_t        loopback_internal;  /* Internal loopback is enabled */
    uint32_t        autobus_on;         /* Auto timed bus on after bus off */
    uint32_t        silent;             /* Receiver only, no ack generation */
} CAN_DEVCTL_INFO;

/* CAN Devctl Data */
typedef union
{
    uint32_t            mid;              /* CAN message identifier */
    uint32_t            mfilter;          /* Device driver defined CAN message filter */
    uint32_t            prio;             /* Device driver defined CAN priority */
    uint32_t            timestamp;        /* Device CAN message timestamp */
    uint32_t            print_debug_all;  /* when printing debug info, print all or specific device */
    CAN_DEVCTL_ERROR    error;            /* Device driver specific error info */
    CAN_MSG             canmsg;           /* CAN message */
    CAN_DEVCTL_STATS    stats;            /* CAN general stats counters */
    CAN_DEVCTL_INFO     info;             /* CAN general info counters */
} DCMD_DATA;

#define CAN_CMD_CODE                      1
#define CAN_DEVCTL_GET_MID              __DIOF(_DCMD_MISC, CAN_CMD_CODE + 0,   uint32_t)
#define CAN_DEVCTL_SET_MID              __DIOT(_DCMD_MISC, CAN_CMD_CODE + 1,   uint32_t)
#define CAN_DEVCTL_GET_MFILTER          __DIOF(_DCMD_MISC, CAN_CMD_CODE + 2,   uint32_t)
#define CAN_DEVCTL_SET_MFILTER          __DIOT(_DCMD_MISC, CAN_CMD_CODE + 3,   uint32_t)
#define CAN_DEVCTL_GET_PRIO             __DIOF(_DCMD_MISC, CAN_CMD_CODE + 4,   uint32_t)
#define CAN_DEVCTL_SET_PRIO             __DIOT(_DCMD_MISC, CAN_CMD_CODE + 5,   uint32_t)
#define CAN_DEVCTL_GET_TIMESTAMP        __DIOF(_DCMD_MISC, CAN_CMD_CODE + 6,   uint32_t)
#define CAN_DEVCTL_SET_TIMESTAMP        __DIOT(_DCMD_MISC, CAN_CMD_CODE + 7,   uint32_t)
#define CAN_DEVCTL_READ_CANMSG_EXT      __DIOF(_DCMD_MISC, CAN_CMD_CODE + 8,   struct can_msg)
#define CAN_DEVCTL_WRITE_CANMSG_EXT     __DIOT(_DCMD_MISC, CAN_CMD_CODE + 9,   struct can_msg)
#define CAN_DEVCTL_ERROR                __DIOF(_DCMD_MISC, CAN_CMD_CODE + 100, struct can_devctl_error)
#define CAN_DEVCTL_DEBUG_INFO           __DION(_DCMD_MISC, CAN_CMD_CODE + 101)
#define CAN_DEVCTL_DEBUG_INFO2          __DIOT(_DCMD_MISC, CAN_CMD_CODE + 102, uint32_t)
#define CAN_DEVCTL_RX_FRAME_RAW_NOBLOCK __DIOF(_DCMD_MISC, CAN_CMD_CODE + 103, struct can_msg)
#define CAN_DEVCTL_RX_FRAME_RAW_BLOCK   __DIOF(_DCMD_MISC, CAN_CMD_CODE + 104, struct can_msg)
#define CAN_DEVCTL_TX_FRAME_RAW         __DIOT(_DCMD_MISC, CAN_CMD_CODE + 105, struct can_msg)
#define CAN_DEVCTL_GET_STATS            __DIOF(_DCMD_MISC, CAN_CMD_CODE + 106, struct can_devctl_stats)
#define CAN_DEVCTL_GET_INFO             __DIOF(_DCMD_MISC, CAN_CMD_CODE + 107, struct can_devctl_info)

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-can/public/sys/can_dcmd.h $ $Rev: 803036 $")
#endif
