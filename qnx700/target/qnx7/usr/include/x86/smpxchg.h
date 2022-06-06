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

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
#ifndef __atomic_fool_gcc
struct __gcc_fool { int __fool[100]; };
#define __atomic_fool_gcc(__x) (*(volatile struct __gcc_fool *)__x)
#endif

static __inline unsigned __attribute__((__unused__)) 
_smp_cmpxchg(volatile unsigned *const __dst, unsigned const __cmd, 
		unsigned const __new) {
	unsigned 	__res;

	__asm__ __volatile__(
		"lock; cmpxchgl %3, %0"
		:"=m" (__atomic_fool_gcc(__dst)), "=a" (__res)
		:"m" (*__dst), "r" (__new), "1" (__cmd)
		:"memory");
	return __res;
}

static __inline unsigned __attribute__((__unused__)) 
_smp_xchg(volatile unsigned *const __dst, unsigned const __src) {
	unsigned 	__res;

	__asm__ __volatile__(
		"xchgl %0,%1"
		:"=r" (__res)
		:"m" (__atomic_fool_gcc(__dst)), "0" (__src)
		:"memory");
	return __res;
}

#elif defined(__MWERKS__)

#define __MWINL inline __declspec(naked)

static __MWINL unsigned
_smp_cmpxchg(volatile unsigned *__dst, unsigned __cmd, unsigned __new) {
	asm {
		push ecx
		push edx
		mov  edx, __dst
		mov  ecx, __new
		mov  eax, __cmd
		lock: cmpxchg  [edx],ecx
		pop edx
		pop ecx
	}
}

static __MWINL unsigned
_smp_xchg(volatile unsigned *__dst, unsigned __src) {
    asm {
    	push edx
    	mov  edx, __dst
    	mov  eax, __src
	xchg [edx],eax
    }
}

#else
#error Compiler not defined
#endif

static __inline__ unsigned long
_smp_cmpxchg_ul(volatile unsigned long *const __dst, unsigned long const __cmd, 
		unsigned long const __new) {
	return _smp_cmpxchg((volatile unsigned *)__dst, __cmd, __new);
}

static __inline__ unsigned long
_smp_xchg_ul(volatile unsigned long *const __dst, unsigned long const __src) {
	return _smp_xchg((volatile unsigned *)__dst, (unsigned)__src);
}


__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/x86/smpxchg.h $ $Rev: 781722 $")
#endif
