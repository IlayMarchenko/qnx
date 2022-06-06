/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _STDDEF_H_INCLUDED
#define _STDDEF_H_INCLUDED
#define _STDDEF_H_DECLARED

#ifndef _YVALS
 #include <yvals.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

#if defined(__RSIZE_T)
typedef __RSIZE_T	rsize_t;
#undef __RSIZE_T
#endif

#if defined(__PTRDIFF_T)
typedef __PTRDIFF_T	ptrdiff_t;
#undef __PTRDIFF_T
#endif

#if defined(__WCHAR_T)
typedef __WCHAR_T	wchar_t;
#undef __WCHAR_T
#endif

#ifndef NULL
# define NULL _NULL
#endif

#if (__GNUC__ >= 4) && !defined(__INTEL_COMPILER)
# define offsetof(__typ,__id) __builtin_offsetof(__typ,__id)
#elif defined(__cplusplus) && (__GNUC__ == 3 && __GNUC_MINOR__ == 4) && !defined(__INTEL_COMPILER)
# define offsetof(__typ,__id)									\
    (__offsetof__(reinterpret_cast <size_t>						\
				  (&reinterpret_cast <const volatile char &>	\
				   (static_cast<__typ *>(0)->__id))))
#else
# define offsetof(__typ,__id) ((size_t)&(((__typ*)0)->__id))
#endif

#if defined(__cplusplus) || (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#if defined(__MAX_ALIGN_T)
typedef __MAX_ALIGN_T	max_align_t;
#undef __MAX_ALIGN_T
#endif
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/stddef.h $ $Rev: 806926 $")
#endif
