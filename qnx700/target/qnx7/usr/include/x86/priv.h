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

#define HALT() __asm__ __volatile__ ( "hlt": : :"memory")

#define sldt() ({ register _uint16 __ldt; __asm__ ( "sldt %w0": "=q" (__ldt) : : "memory"); __ldt; })

#define setts() ((void)({ register _uint16 __reg; __asm__ __volatile__( "smsw %w0\n\torb $8,%b0\n\tlmsw %w0": "=q" (__reg):); }))

#define lgdt(__gdt) ((void)({__asm__ ( "lgdt (%0)": : "r" (__gdt) : "memory"); }))
#define sgdt(__gdt) __asm__ ( "sgdt (%0)": : "r" (__gdt): "memory" )

#define invlpg(__p) ((void)({__asm__ ("invlpg %0": : "m" (*(char *)__p): "memory"); }))

#define lidt(__idt) ((void)({__asm__ ( "lidt (%0)": : "r" (__idt)); }))
#define sidt(__idt) ((void)({void *__ptr = (__idt); __asm__ ( "sidt (%0)":: "r" (__ptr): "memory"); }))

#define ldpgdir(__dir) ((void)({__asm__ ( "movl %0,%%cr3": :"r" (__dir)); }))
#define rdpgdir() ({register _uint32 __dir; __asm__ ( "movl %%cr3,%0": "=q" (__dir):); __dir; })

#define ldcr0(__flags) ((void)({__asm__ ( "movl %0,%%cr0": :"r" (__flags)); }))
#define rdcr0() ({register _uint32 __flags; __asm__ ( "movl %%cr0,%0": "=q" (__flags):); __flags; })

#define rdcr2() ({register _uint32 __flags; __asm__ ( "movl %%cr2,%0": "=q" (__flags):); __flags; })

#define ldcr4(__flags) ((void)({__asm__ ( "movl %0,%%cr4": :"r" (__flags)); }))
#define rdcr4() ({register _uint32 __flags; __asm__ ( "movl %%cr4,%0": "=q" (__flags):); __flags; })

#define flushtlb()	({InterruptDisable();ldpgdir(rdpgdir());InterruptEnable();})

#define flushcache() ((void)({__asm__ __volatile__ ( "wbinvd": : : "memory"); }))

#define wrdr0(__flags) ((void)({__asm__ ( "movl %0,%%db0": :"r" (__flags)); }))
#define wrdr1(__flags) ((void)({__asm__ ( "movl %0,%%db1": :"r" (__flags)); }))
#define wrdr2(__flags) ((void)({__asm__ ( "movl %0,%%db2": :"r" (__flags)); }))
#define wrdr3(__flags) ((void)({__asm__ ( "movl %0,%%db3": :"r" (__flags)); }))
#define wrdr6(__flags) ((void)({__asm__ ( "movl %0,%%db6": :"r" (__flags)); }))
#define wrdr7(__flags) ((void)({__asm__ ( "movl %0,%%db7": :"r" (__flags)); }))

#define rddr0() ({register _uint32 __flags; __asm__ ( "movl %%db0,%0": "=q" (__flags):); __flags; })
#define rddr1() ({register _uint32 __flags; __asm__ ( "movl %%db1,%0": "=q" (__flags):); __flags; })
#define rddr2() ({register _uint32 __flags; __asm__ ( "movl %%db2,%0": "=q" (__flags):); __flags; })
#define rddr3() ({register _uint32 __flags; __asm__ ( "movl %%db3,%0": "=q" (__flags):); __flags; })
#define rddr6() ({register _uint32 __flags; __asm__ ( "movl %%db6,%0": "=q" (__flags):); __flags; })
#define rddr7() ({register _uint32 __flags; __asm__ ( "movl %%db7,%0": "=q" (__flags):); __flags; })

#define wrtr(__tr) ((void)({register _uint16 __tmp = (__tr); __asm__ ( "ltr %w0": : "r" (__tmp)); }))
#define rdtr() ({register _uint16 __tr; __asm__ ( "str %w0": "=q" (__tr):); __tr; })

#define clts() ((void)({__asm__ __volatile__ ( "clts": :); }))

#define rdmsr(__idx)	({ register _uint64 __value; register int __i = (__idx); __asm__( \
						"rdmsr" \
						: "=A" (__value): "c" (__i)); __value; })

#define wrmsr(__idx, __value)	((void)({ register _uint64 __v = (__value); register int __i = (__idx); __asm__( \
						"wrmsr" \
						: : "c" (__i), "A" (__v)); }))

#else
#error Compiler not defined.
#endif

__END_DECLS

#endif

/* __SRCVERSION("priv.h $Rev: 781291 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/startup/lib/public/x86/priv.h $ $Rev: 781291 $")
#endif
