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
 *  smpxchg.h     code sequences for SMP atomic exchanging of mutex stuff.
 *

 */

#ifndef __SMPXCHG_H_INCLUDED
#define __SMPXCHG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

static __inline unsigned __attribute__((__unused__))
_smp_cmpxchg(volatile unsigned *const __dest, unsigned const __oldval, 
		unsigned const __newval) {
	unsigned __ret;
	__asm__ __volatile__(
	    "lock; cmpxchgl %2,%1"
	    : "=a" (__ret), "+m" (*__dest)
	    : "r" (__newval), "0"(__oldval)
	    : "memory");
	return __ret;
}

static __inline unsigned long  __attribute__((__unused__))
_smp_cmpxchg_ul(volatile unsigned long *const __target, unsigned long const __oldval,
	       unsigned long const __newval) {
	unsigned long __ret;
	__asm__ __volatile__ (
	    "lock; cmpxchgq %2,%1"
	    : "=a" (__ret), "+m" (*__target)
	    : "q" (__newval), "0"(__oldval)
	    : "memory");
	    return __ret;
}


static __inline unsigned __attribute__((__unused__))
_smp_xchg(volatile unsigned *const __dst, unsigned const __val) {
	unsigned __ret;
	__asm__ __volatile__(
		"xchgl %0,%1"
		:"=r" (__ret), "+m" (*__dst)
		: "0" (__val)
		:"memory");
	return __ret;
}

static __inline unsigned long __attribute__((__unused__))
_smp_xchg_ul(volatile unsigned long *const __dest, unsigned long const __val) {
	unsigned long  __ret;
	__asm__ __volatile__ (
		"xchgq %0,%1"
		: "=r" (__ret), "+m" (*__dest)
		: "0"(__val)
		: "memory");
	return __ret;
}

#else
#error Compiler not defined
#endif


__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/x86_64/smpxchg.h $ $Rev: 780674 $")
#endif
