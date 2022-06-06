/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */
/*
 * This file lists down the message exchange datatypes and formats for achieving
 * bulk transfers (few Kbs, running into MBs) via NvC2C - Nvidia's Chip-To-Chip
 * stack over PCIe. For the bulk transfers, we the EmdeddedDMA controller inside
 * T19x PCIe controller.
 *
 * As this data is transferred via DMA, applications must ensure that C2C
 * messages contain offset of reserve physical memory that NvC2C stack is also
 * aware of. Using reserved carveouts is recommended way as demonstrated by
 * sample application - test_nvc2c_bulk.
 *
 * This should be really Read-Only file(external use).
 */

#ifndef __NVC2C_H__
#define __NVC2C_H__

#include <stdint.h>
#include <stdbool.h>


/* C2C Message is a list of tuples, each tuple: offset in physical memory
 * accessible/sharable with NvC2C and size of that offset.
 * Maximum such tuples supported within a single C2C message.
 */
#define C2CMSG_MAX_TUPLES    (8)


/*
 * Message/Command/Response/Error of the c2c message from NvC2C app to NvC2C
 * Sw stack and vice-versa.
 *
 * CMD_ go from NvC2C app(e.g test_nvc2c_bulk) to NvC2C Sw Stack.
 * RESP_ come back from NvC2C Sw Stack to app for each CMD_ c2c message.
 *
 * The RESP_ are reponse to the CMD_ that was sent to NvC2C Sw stack. It
 * doesn't signify that the data was consumed by remote SoC.
 */
typedef enum {
    /* Invalid. */
    MSG_INVALID = 0,

    /* Empty this Buffer - NvC2C app to NvC2C Sw Stack.*/
    CMD_ETB,

    /* Fill This Buffer. - */
    CMD_FTB,

    /* Response Empty buffer Done.*/
    RESP_EBD,

    /* Response Fill buffer Done.*/
    RESP_FBD,

    /* Message Error:
     * May result in case there are more than supported tuples.
     * Tuples have fields that have invalid size(=0).
     * Tuples who have offset+size exceed shared memory size.
     * Size is not aligned to (4).
     * Basically any error in the format of message error.
     */
    RESP_MSG_ERR,

    /* Transfer via DMA / Copy Error.*/
    RESP_XFER_ERR,

    /* Ack Generic Error. */
    RESP_ERR,

    /* Maximum. */
    MSG_MAXIMUM,
} C2CMessageType;


/*
 * pair of offset, size tuple.
 *
 * when application is producing data for similar application on remote SoC.
 * - the producer application must cotain the list of offsets of shared
 *   memory with NvC2C Sw stack where it has written data for NvC2C stack to
 *   empty it. (DMA).
 * when application is consuming data from similar application on remote SoC.
 * - the consumer application must cotain the list of offsets of shared
 *   memory with NvC2C Sw stack where it wants NvC2C stack to fill it.
 *
 * Offsets must be relative to start of the physical shared memory base
 * with NvC2C Sw.
 */
typedef struct {
    /* offset relative to ivm mempool/co.
     * These are kept 64-bit just in case we make them absolute addresses.
     */
    uint64_t offset;

    /* size of fragment.*/
    uint32_t size;
} C2CMessageTuple;


/*
 * Message passing to/from NvC2C app to NvC2C Sw.
 *
 * This is the C2C message that nvc2c app populates and passes
 * onto NvC2C Sw stack to either empty the contents of memory it
 * has offsets and size of to remote SoC OR fill the contents of
 * memory it has offsets and size of by data sent over PCIe by
 * remote SoC.
 *
 * All fields in this message are read-only for NvC2C Sw except
 * msg_type for sharing RESP_ to CMD_
 */
 typedef struct {
    /* sequencce number of the packet.*/
    uint64_t seq_num;

    /* reserved (for timestamp, future use). */
    uint64_t reserved;

    /* Message type / Command / Resp. / Error Code. */
    C2CMessageType msg_type;

    /* list of message tuples. */
    C2CMessageTuple tuple[C2CMSG_MAX_TUPLES];

    /* number of tuples of offset+size pair in this message.
     * the upper limit is - C2CMSG_MAX_TUPLES. */
    uint8_t tuples_nr;
} C2CMessage;

#endif //__NVC2C_H__
