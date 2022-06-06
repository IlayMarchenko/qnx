/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * privledged instructions for kernel
 *

 *
 */
#ifndef __PRIV_H_INCLUDED
#define __PRIV_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#if defined(__GNUC__) || defined(__INTEL_COMPILER)


static __inline void
HALT(void)
{
	__asm __volatile( "hlt": : :"memory");
}
static __inline uint16_t
sldt(void)
{
	uint16_t __ldt;
	__asm volatile("sldt %w0" : "=r" (__ldt) : : "memory");
	return __ldt;
}

static __inline void
setts(void)
{
	uint16_t  __reg;
	__asm __volatile("smsw %w0; orb $8,%b0; lmsw %w0" : "=r" (__reg):);
}
static __inline void
lgdt(void *__gdt)
{
	__asm volatile( "lgdt (%0)": : "r" (__gdt));
}

static __inline void
sgdt(void *__gdtp)
{
	__asm volatile( "sgdt (%0)": : "r" (__gdtp): "memory" );
}

static __inline void
invlpg(uintptr_t pg)
{
	__asm __volatile("invlpg %0" : : "m" (*(char *)pg): "memory");
}

static __inline void
invpcid(unsigned type, unsigned pcid, _Uintptrt vaddr)
{
	_Uintptrt volatile desc[2] = {pcid, vaddr};
	__asm __volatile("invpcid %1,%0" :: "r" ((_Uint64t)type), "m" (desc[0]));
}

static __inline void
lidt(void * __idt)
{
	__asm __volatile("lidt (%0)": : "r"(__idt));
}

static __inline void
sidt(void *__idt)
{
	__asm __volatile("sidt (%0)" :: "r"(__idt): "memory");
}


static __inline uint64_t
rdcr0(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%cr0, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
ldcr0(uint64_t __rval)
{
	__asm __volatile("movq %0, %%cr0" : : "r" (__rval));
}

static __inline uint64_t
rdcr2(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%cr2, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
ldcr2(uint64_t __rval)
{
	__asm __volatile("movq %0, %%cr2" : : "r" (__rval));
}

static __inline uint64_t
rdcr3(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%cr3, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
ldcr3(uint64_t __rval)
{
	__asm __volatile("movq %0, %%cr3" : : "r" (__rval));
}

static __inline uint64_t
rdcr4(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%cr4, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
ldcr4(uint64_t __rval)
{
	__asm __volatile("movq %0, %%cr4" : : "r" (__rval));
}


static __inline void
flushcache(void)
{
	__asm __volatile("wbinvd" : : : "memory");
}

static __inline uint64_t
rddr0(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db0, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr0(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db0" : : "r" (__rval));
}



static __inline uint64_t
rddr1(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db1, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr1(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db1" : : "r" (__rval));
}

static __inline uint64_t
rddr2(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db2, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr2(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db2" : : "r" (__rval));
}
static __inline uint64_t
rddr3(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db3, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr3(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db3" : : "r" (__rval));
}
static __inline uint64_t
rddr4(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db4, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr4(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db4" : : "r" (__rval));
}
static __inline uint64_t
rddr5(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db5, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr5(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db5" : : "r" (__rval));
}
static __inline uint64_t
rddr6(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db6, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr6(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db6" : : "r" (__rval));
}
static __inline uint64_t
rddr7(void)
{
	uint64_t __rval;
	__asm __volatile("movq %%db7, %0" : "=r" (__rval));
	return __rval;
}

static __inline void
wrdr7(uint64_t __rval)
{
	__asm __volatile("movq %0, %%db7" : : "r" (__rval));
}

static __inline void
wrtr(uint16_t __tr)
{
	__asm __volatile("ltr %w0": : "r" (__tr): "memory");
}

static __inline uint16_t
rdtr(void)
{
	uint16_t __tr;
	__asm __volatile("str %w0": "=r" (__tr));
	return __tr;
}

static __inline void
clts(void)
{
	__asm __volatile("clts"::);
}

static __inline uint64_t
rdmsr(unsigned __idx)
{
	uint32_t  __lo, __hi;
	__asm __volatile("rdmsr " : "=a" (__lo), "=d" (__hi): "c" (__idx));
	return (uint64_t)__lo|((uint64_t)__hi<<32);
}

static __inline void
wrmsr(unsigned __idx, uint64_t __val)
{
	uint32_t  __lo, __hi;
	__lo = (uint32_t)__val;
	__hi = (uint32_t)(__val >> 32);
	__asm __volatile("wrmsr " : : "a" (__lo), "d" (__hi), "c" (__idx));
}

#define ldpgdir ldcr3
#define rdpgdir rdcr3
#define flushtlb()	({InterruptDisable();ldpgdir(rdpgdir());InterruptEnable();})

#else
#error Compiler not defined.
#endif

__END_DECLS

#endif

/* __SRCVERSION("priv.h $Rev: 778261 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/startup/lib/public/x86_64/priv.h $ $Rev: 778261 $")
#endif
