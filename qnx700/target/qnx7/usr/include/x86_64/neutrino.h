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

#ifndef __X86_64_NEUTRINO_H_INCLUDED
#define __X86_64_NEUTRINO_H_INCLUDED

#ifndef __NEUTRINO_H_INCLUDED
#error x86_64/neutrino.h should not be included directly.
#endif

#define CLOCKCYCLES_INCR_BIT	0

#if defined(__SLIB_DATA_INDIRECT) && !defined(__SLIB)
extern unsigned __get_cpu_flags(void);
#define __cpu_flags (__get_cpu_flags())
#else
extern unsigned __cpu_flags;
#endif

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

static __inline _Uint64t
ClockCycles(void)
{
	register _Uint32t __lo, __hi;
	__asm __volatile ("rdtsc" : "=a" (__lo), "=d" (__hi));
	return (_Uint64t)__lo | ((_Uint64t)__hi << 32);
}


static __inline void
__inline_InterruptUnlock(struct intrspin *__spin)
{
	__asm __volatile("mfence; movl $0, (%0); sti"
		: : "r" (__spin) : "memory");
}

static __inline void
__inline_InterruptLock(struct intrspin *__spin)
{
	register int __tmp;
	__asm __volatile (
		"cli;"
		"0:movl $1,%0;"
		"xchgl (%1),%0;"
		"testl %0,%0;"
		"jz 1f;"
		"pause;"
		"jmp 0b;"
		"1:"
		: "=&r" (__tmp)
		: "r" (__spin)
		: "memory");
}
static __inline void
__inline_InterruptDisable(void)
{
	__asm __volatile("cli; nop" : : : "memory");
}

static __inline void
__inline_InterruptEnable(void)
{
/*-
 nop here seems anal: interrupts aren't actually accepted until
 after the nop, but no code should be able to tell the difference...
*/
	__asm __volatile("sti; nop" : : : "memory");
}

/* note: copied from x86_64/cpu.h */
#define __X86_64_PSW_IF				(1ULL<< 9 )

static __inline unsigned
__inline_InterruptStatus(void)
{
	_Uint64t __flags;
	__asm __volatile("pushfq; popq %0;" : "=r" (__flags) : : "memory");
	return (__flags & __X86_64_PSW_IF);
}

static __inline void
__inline_DebugBreak(void)
{
	__asm __volatile("int $0x03":::"memory");
}

static __inline void
__inline_DebugKDBreak(void)
{
	__asm __volatile("int $0x20":::"memory");
}

/*-
 * This is broken: it should just use the std calling convention.
 */
static __inline void
__inline_DebugKDOutput(const char *__text, size_t __len)
{
	__asm __volatile("int $0x21" :: "a"(__text) , "d"(__len));
}

#else
# error Compiler not defined.
#endif


#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86_64/neutrino.h $ $Rev: 780680 $")
#endif
