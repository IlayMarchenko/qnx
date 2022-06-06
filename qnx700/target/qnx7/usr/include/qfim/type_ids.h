/*
 * $QNXLicenseC:
 * Copyright (c) 2016-2017, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


#ifndef _QFIM_TYPE_IDS_H_INCLUDED
#define _QFIM_TYPE_IDS_H_INCLUDED


/* --- libqfim headers --- */
#include <qfim/common.h>

/* --- Library headers --- */

/* --- System/standard library headers --- */


__QFIM_BEGIN_DECLS


/* Identifiers for Integrity Measurement types */
enum qfim_type_id_e {

    /** Special invalid value indicator */
    QFIM_TYPE_ID_INVALID = -1,

    /** Binary blob (array of bytes) */
    QFIM_TYPE_ID_BLOB = 0,

    /** Comment (null-terminated string) */
    QFIM_TYPE_ID_COMMENT,

    QFIM_NUM_TYPE_IDS,
};


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_TYPE_IDS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/type_ids.h $ $Rev: 823191 $")
#endif
