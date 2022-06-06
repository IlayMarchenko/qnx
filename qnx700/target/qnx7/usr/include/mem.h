/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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



/*
 *  mem.h       Memory manipulation functions
 *
 */

#ifndef _LIBC_MEM_H_
#define _LIBC_MEM_H_

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__PTRDIFF_T)
typedef __PTRDIFF_T	ptrdiff_t;
#undef __PTRDIFF_T
#endif

#include <string.h>

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/mem.h $ $Rev: 780356 $")
#endif
