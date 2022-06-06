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
 *  x86_64/inline.h     some handy pragma's for low-level work:
 *

 */

#ifndef _X86_64_INLINE_H_INCLUDED
#define _X86_64_INLINE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _X86_64_INOUT_INCLUDE
#include <x86_64/inout.h>
#endif

__BEGIN_DECLS


#if defined(__GNUC__) || defined(__INTEL_COMPILER)

#define breakpoint()	({ __asm__ __volatile__ ("int $0x03": :); })
#define trppoint()		({ __asm__ __volatile__ ("int $0x20": :); })

#define _cs() ({register _Uint16t __seg; __asm__ ( "movw %%cs,%0": "=qm" (__seg):); __seg; })
#define _ds() ({register _Uint16t __seg; __asm__ ( "movw %%ds,%0": "=qm" (__seg):); __seg; })
#define _es() ({register _Uint16t __seg; __asm__ ( "movw %%es,%0": "=qm" (__seg):); __seg; })
#define _fs() ({register _Uint16t __seg; __asm__ ( "movw %%fs,%0": "=qm" (__seg):); __seg; })
#define _gs() ({register _Uint16t __seg; __asm__ ( "movw %%gs,%0": "=qm" (__seg):); __seg; })
#define _ss() ({register _Uint16t __seg; __asm__ ( "movw %%ss,%0": "=qm" (__seg):); __seg; })

static inline void _ldfs(const _Uint32t __val) {
	__asm__ ( "mov %0,%%fs" :: "r" (__val));
}

/* ldsp() - set the current stack pointer */
static __inline__ void ldsp(_Uintptrt __sp) {
	__asm__ ("mov	%0, %%rsp" :: "g" (__sp));
}

/* rdsp() - obtain the current stack pointer */
static __inline__ _Uintptrt rdsp(void) {
	_Uintptrt sp;
	__asm__ ("mov	%%rsp, %0" : "=g" (sp));
	return sp;
}

#define io_safe()		({ __asm__ __volatile__("jmp 1f\n1:\tjmp 1f\n1:"); })

#define swapw(__val)	({ _Uint16t __tmp = (__val); __asm__("xchgb %b0, %h0": "=q" (__tmp): "0" (__tmp)); (__tmp); })
#define swapl(__val)	({ _Uint32t __tmp = (__val); __asm__("xchgb %b0, %h0\n\trorl $16,%0\n\txchgb %b0,%h0": "=q" (__tmp): "0" (__tmp)); (__tmp); })

#define fninit()		({ __asm__ __volatile__ ("fninit": :); })
#define fnclex()		({ __asm__ __volatile__ ("fnclex": :); })

#define delay_8X(__num)	({register _Uint32t __tmp; __asm__ __volatile__("0: loop 0b": "=c" (__tmp) : "0" (__num)); })

#define pswget()		({register _Uint64t __flags; __asm__ __volatile__ ( \
						"pushf\n\tpop %0" \
						: "=r" (__flags) :); __flags; })

#define restore(__fl)	({register _Uint64t __flags = (__fl); \
						 __asm__ __volatile__ \
						("push %0\n\tpopf": : "r" (__flags): "cc"); \
						})

#define disable()		({register _Uint64t __flags; __asm__ __volatile__ ( \
						"pushfq\n\t" \
						"popq %0\n\t" \
						"cli\n\t" \
						: "=r" (__flags) : : "memory"); __flags; })

#define enable()		({register _Uint64t __flags; __asm__ __volatile__ ( \
						"pushfq\n\t" \
						"sti\n\t" \
						"pop %0\n\t" \
						: "=r" (__flags) : : "memory"); __flags; })

#define str_forward()	({register _Uint64t __flags; __asm__ __volatile__ ( \
						"pushfq\n\t" \
						"cld\n\t" \
						"pop %0\n\t" \
						: "=r" (__flags) : : "memory"); __flags; })

#define str_reverse()	({register _Uint64t __flags; __asm__ __volatile__ ( \
						"pushfq\n\t" \
						"std\n\t" \
						"pop %0\n\t" \
						: "=r" (__flags) : : "memory"); __flags; })

static __inline__ void __attribute__((__unused__)) rdtsc(_Uint64t *const __ptr) {
	struct __hilo { unsigned __lo, __hi; } *__num = (struct __hilo *)__ptr;
	__asm__ __volatile__ (
		"rdtsc\n\t"
		"movl %%eax,%0\n\t"
		"movl %%edx,%1\n\t"
		: "=m" (__num->__lo), "=m" (__num->__hi): :"eax", "edx");
}

/**
 * Starting with the Intel Pentium, Intel CPUs spuport out-of-order execution of the code
 * to optimize the different instruction latencies.
 * Unfortunately, this feature does not guarantee that the temporal sequence of
 * the single compiled C instructions will respect the sequence of the instruction
 * Intel recommends to use cpuid/lfence instructions to serialize the instruction
 *
 * Documented in Intel benmark-code-execution-paper-1
 */
static __inline__ void __attribute__((__unused__)) rdtsc_ordered(_Uint64t *const __ptr) {
	struct __hilo { unsigned __lo, __hi; } *__num = (struct __hilo *)__ptr;
	__asm__ __volatile__ (
		"cpuid\n\t"
		"rdtsc\n\t"
		"movl %%eax,%0\n\t"
		"movl %%edx,%1\n\t"
		: "=m" (__num->__lo), "=m" (__num->__hi): :"eax", "ebx", "ecx", "edx");
}

#define bsr(__num)		({ _Uint32t __tmp = (__num); __asm__("bsr %0,%0": "=r" (__tmp): "0" (__tmp)); (__tmp); })
#define bsr0(__num)		({ _Uint32t __tmp = (__num); __asm__("bsr %0,%0\n\tjnz 0f\n\txor %0,%0\n0:": "=r" (__tmp): "0" (__tmp)); (__tmp); })

/*
 * Make sure gcc doesn't try to be clever and move things around
 * on us. We need to use _exactly_ the address the user gave us,
 * not some alias that contains the same information.
 */
#ifndef __atomic_fool_gcc
struct __gcc_fool { int __fool[100]; };
#define __atomic_fool_gcc(__x) (*(volatile struct __gcc_fool *)(__x))
#endif

static __inline void __attribute__((__unused__)) smp_locked_or(volatile unsigned *__dst, unsigned __value) {
	__asm__ __volatile__(
		"lock; orl %2,%0"
		:"=m" (__atomic_fool_gcc(__dst))
		:"m" (__atomic_fool_gcc(__dst)), "ir" (__value)
		:"memory");
}

static __inline void __attribute__((__unused__)) smp_locked_and(volatile unsigned *__dst, unsigned __value) {
	__asm__ __volatile__(
		"lock; andl %2,%0"
		:"=m" (__atomic_fool_gcc(__dst))
		:"m" (__atomic_fool_gcc(__dst)), "ir" (__value)
		:"memory");
}


/**
 * Invoke the CPUID instruction.
 * It can only be used for leaves that ignore the value of ECX.
 * @param		__func	leaf index
 * @param[out]	__eaxp	area to store returned value of EAX
 * @param[out]	__ebxp	area to store returned value of EBX
 * @param[out]	__ecxp	area to store returned value of ECX
 * @param[out]	__edxp	area to store returned value of EDX
 */
static __inline void
x86_cpuid1(unsigned const __func, unsigned *const __eaxp, unsigned *const __ebxp,
			unsigned *const __ecxp, unsigned *const __edxp) {
	unsigned __eax, __ebx, __ecx, __edx;

	__asm __volatile( "cpuid" : "=a" (__eax), "=b" (__ebx), "=c" (__ecx), "=d" (__edx) : "a" (__func));
	if(__eaxp != (void *)0) {
		*__eaxp = __eax;
	}
	if(__ebxp != (void *)0) {
		*__ebxp = __ebx;
	}
	if(__ecxp != (void *)0) {
		*__ecxp = __ecx;
	}
	if(__edxp != (void *)0) {
		*__edxp = __edx;
	}
}

/**
 * Invoke the CPUID instruction.
 * It can be used for any leaf.
 * @param		__func	leaf index
 * @param		__subfunc	sub-leaf index
 * @param[out]	__eaxp	area to store returned value of EAX
 * @param[out]	__ebxp	area to store returned value of EBX
 * @param[out]	__ecxp	area to store returned value of ECX
 * @param[out]	__edxp	area to store returned value of EDX
 */
static __inline void
x86_cpuid2(unsigned const __func, unsigned const __subfunc, unsigned *const __eaxp,
		unsigned *const __ebxp, unsigned *const __ecxp, unsigned *const __edxp) {
	unsigned __eax, __ebx, __ecx, __edx;

	__asm __volatile( "cpuid" : "=a" (__eax), "=b" (__ebx), "=c" (__ecx), "=d" (__edx) : "a" (__func), "c" (__subfunc));
	if(__eaxp != (void *)0) {
		*__eaxp = __eax;
	}
	if(__ebxp != (void *)0) {
		*__ebxp = __ebx;
	}
	if(__ecxp != (void *)0) {
		*__ecxp = __ecx;
	}
	if(__edxp != (void *)0) {
		*__edxp = __edx;
	}
}


/**
 * Invoke the XSETBV instruction.
 * @param	__reg	extended control reg number
 * @param	__high	high 32 bits to load
 * @param	__low	low  32 bits to load
 */
static __inline void
x86_xsetbv(unsigned const __reg, unsigned const __high, unsigned const __low) {
	__asm __volatile( "xsetbv" :: "c" (__reg), "a" (__low), "d" (__high));
}


/**
 * Invoke the FNOP instruction.
 */
static __inline void
x86_fnop(void) {
	__asm __volatile( "fnop");
}


#else
#error Compiler not defined.
#endif


__END_DECLS



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/x86_64/inline.h $ $Rev: 815801 $")
#endif
