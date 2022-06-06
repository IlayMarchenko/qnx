/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef __SYS_SWAP_H__
#define __SYS_SWAP_H__

#include <sys/sysmsg.h>

/**
 * Messages sent to an external swap device.
 */
enum {
	/**
	 * Write the contents of a page to the external swap device.
	 * The ID passed in will be used with the read/free messages and should be
	 * able to correctly identify the page on the device.
	 */
	_SWAPDEV_WRITE_PAGE,
	/**
	 * Read a page stored on the device with the given ID.
	 */
	_SWAPDEV_READ_PAGE,
	/**
	 * Discard a page with the given ID.
	 */
	_SWAPDEV_FREE_PAGE,
};

/*
 * Flags used in the registration message (_MEM_SWAP_REGISTER).
 */

/**
 * Send the _SWAPDEV_FREE_PAGE message when a swap page is released.
 */
#define	_SWAP_REGISTER_WANT_FREE	0x1

typedef struct
{
	_Uint16t	type;
	_Uint16t	pad;
	_Uint32t	id;
	_Uint64t	paddr;
} swapdev_msg_t;

/*
 * The following type definitions are only used to describe the format of the
 * various messages. There is no need to use them in code.
 */

/**
 * _SWAPDEV_WRITE_PAGE message.
 * Input is a header followed by the page contents.
 */
typedef struct
{
	union {
		struct {
			swapdev_msg_t	hdr;
			_Uint8t			data[__PAGESIZE];
		}				i;
	} u;
} swapdev_write_msg_t;

/**
 * _SWAPDEV_READ_PAGE message.
 * Input is a message containing the page ID.
 * Output is the page contents.
 */
typedef struct
{
	union {
		swapdev_msg_t	i;
		struct {
			_Uint8t			data[__PAGESIZE];
		}				o;
	} u;
} swapdev_read_msg_t;

/**
 * _SWAPDEV_FREE_PAGE message.
 * Input is a message containing the page ID.
 */
typedef struct
{
	union {
		swapdev_msg_t	i;
	} u;
} swapdev_free_msg_t;


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/swap.h $ $Rev: 772036 $")
#endif
