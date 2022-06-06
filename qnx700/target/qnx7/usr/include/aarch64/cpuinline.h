/*
 * $QNXLicenseC:
 * Copyright 2014 QNX Software Systems. All Rights Reserved.
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

#ifndef _AARCH64_CPUINLINE_INCLUDED
#define _AARCH64_CPUINLINE_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

extern unsigned __cpu_flags;

#if defined(__GNUC__)

# define __cpu_membarrier()	\
		(__extension__ ({ __asm__ __volatile__ ("dmb sy" : : : "memory"); }))

#define __cpu_bus_backoff() (__cpu_membarrier())

#else
# error compiler not supported
#endif

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/aarch64/cpuinline.h $ $Rev: 780423 $")
#endif
