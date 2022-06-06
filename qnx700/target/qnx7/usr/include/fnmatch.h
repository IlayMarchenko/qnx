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
 *  fnmatch.h
 *

 */

#ifndef _FNMATCH_H_INCLUDED
#define _FNMATCH_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif


#define FNM_PATHNAME 	0x1
#define FNM_PERIOD   	0x2
#define FNM_NOESCAPE 	0x4
#if defined(__EXT_QNX)
#define FNM_QUOTE    	FNM_NOESCAPE
#endif
#if defined(__EXT_UNIX_MISC)
#define FNM_LEADING_DIR 0x8
#define	FNM_CASEFOLD	0x10	/* Case insensitive search. */
#endif

#define FNM_NOMATCH  1


__BEGIN_DECLS
extern int fnmatch(const char *__pat, const char *__str, int __flags);

#if defined(__EXT_QNX)
struct iovec;
extern int _fnmatchv(const char *__pat, const struct iovec *__iov,
					 unsigned __iovnum, int __flags);
#endif

__END_DECLS
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/fnmatch.h $ $Rev: 794957 $")
#endif
