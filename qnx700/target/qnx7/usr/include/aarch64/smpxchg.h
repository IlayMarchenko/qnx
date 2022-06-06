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



/*
 *  smpxchg.h
 *
 */

#ifndef __SMPXCHG_H_INCLUDED
#define __SMPXCHG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/*
 *  code sequences for SMP atomic exchanging of mutex stuff.
 */

static __inline__ unsigned __attribute__((__unused__))
_smp_cmpxchg(volatile unsigned *const __dst, unsigned const __cmp, 
		unsigned const __src) {
	unsigned	__res;
	unsigned	__tmp;

	__asm__ __volatile__(
		"1:	ldaxr	%w0, [%2]\n"
		"	cmp		%w0, %w3\n"
		"	b.ne	2f\n"
		"	stlxr	%w1, %w4, [%2]\n"
		"	cbnz	%w1, 1b\n"
		"2:\n"
		: "=&r" (__res), "=&r" (__tmp)
		: "r" (__dst), "r" (__cmp), "r" (__src)
		: "cc", "memory"
	);
	return(__res);
}

static __inline__ unsigned __attribute__((__unused__))
_smp_xchg(volatile unsigned *const __dst, unsigned const __new) {
	unsigned	__res;
	unsigned	__tmp;

	__asm__ __volatile__(
		"1:	ldaxr	%w0, [%2]\n"
		"	stlxr	%w1, %w3, [%2]\n"
		"	cbnz	%w1, 1b\n"
		: "=&r" (__res), "=&r" (__tmp)
		: "r" (__dst), "r" (__new)
		: "cc", "memory"
	);
	return(__res);
}

static __inline__ unsigned long __attribute__((__unused__))
_smp_cmpxchg_ul(volatile unsigned long *const __dst, unsigned long const __cmp, 
		unsigned long const __src) {
	unsigned long	__res;
	unsigned __tmp;

	__asm__ __volatile__(
		"1:	ldaxr	%0, [%2]\n"
		"	cmp		%0, %3\n"
		"	b.ne	2f\n"
		"	stlxr	%w1, %4, [%2]\n"
		"	cbnz	%w1, 1b\n"
		"2:\n"
		: "=&r" (__res), "=&r" (__tmp)
		: "r" (__dst), "r" (__cmp), "r" (__src)
		: "cc", "memory"
	);
	return(__res);
}

static __inline__ unsigned long __attribute__((__unused__))
_smp_xchg_ul(volatile unsigned long *const __dst, unsigned long const __new) {
	unsigned long	__res;
	unsigned __tmp;

	__asm__ __volatile__(
		"1:	ldaxr	%0, [%2]\n"
		"	stlxr	%w1, %3, [%2]\n"
		"	cbnz	%w1, 1b\n"
		: "=&r" (__res), "=&r" (__tmp)
		: "r" (__dst), "r" (__new)
		: "cc", "memory"
	);
	return(__res);
}

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/aarch64/smpxchg.h $ $Rev: 780578 $")
#endif
