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
 *  x86_64/syspage.h
 *

 */

#ifndef __X86_64_SYSPAGE_H_INCLUDED
#define __X86_64_SYSPAGE_H_INCLUDED

#ifndef __SYSPAGE_H_INCLUDED
#error x86_64/syspage.h should not be included directly.
#endif

/*
 *	CPU capability/state flags
 */
/* RUSH64: Nobody should be referencing this */
#define X86_CPU_PAE			(1U <<  13)  /* CPU has phys addr extension  */

/*
 *	CPU capability/state flags
 */
#define X86_64_CPU_CPUID		(1U <<  0)	/* CPU supports cpuid instruction */
#define X86_64_CPU_RDTSC		(1U <<  1)	/* CPU supports rdtsc instruction */
#define X86_64_CPU_INVLPG		(1U <<  2)  /* CPU has INVLPG instruction */
#define X86_64_CPU_WP			(1U <<  3)  /* CPU has WP bit in CR0 */
#define X86_64_CPU_BSWAP		(1U <<  4)  /* CPU has BSWAP instruction */
#define X86_64_CPU_MMX			(1U <<  5)  /* CPU has MMX instructions */
#define X86_64_CPU_CMOV			(1U <<  6)  /* CPU has CMOVxx instructions */
#define X86_64_CPU_PSE			(1U <<  7)  /* CPU has page size extensions */
#define X86_64_CPU_PGE			(1U <<  8)  /* CPU has TLB global mappings */
#define X86_64_CPU_MTRR			(1U <<  9)  /* CPU has MTRR registers */
#define X86_64_CPU_SEP			(1U <<  10)  /* CPU supports SYSENTER  */
#define X86_64_CPU_SIMD			(1U <<  11)  /* CPU supports SIMD (SSE1)  */
#define X86_64_CPU_FXSR			(1U <<  12)  /* CPU supports FXSAVE/FXRSTOR  */
#define X86_64_CPU_PAE			(1U <<  13)  /* CPU has phys addr extension  */
#define X86_64_CPU_NX			(1U <<  14)  /* CPU supports NX PTE bit */
#define X86_64_CPU_SSE2			(1U <<  15)  /* CPU supports SSE2 */
#define X86_64_CPU_AVX			(1U <<  16)  /* CPU supports AVX */
#define X86_64_CPU_XSAVE		(1U <<  17)  /* CPU supports XSAVE/XRSTOR */
#define X86_64_CPU_PAT			(1U <<  18)  /* CPU supports Page Attribute Tables */
#define X86_64_CPU_PTESPLIT_TLBFLUSH (1U <<  19)  /* Needs TLB flush when splitting a large page */
#define X86_64_CPU_PCID			(1U <<  20)  /* CPU supports PCID's */
#define X86_64_CPU_INVARIANT_TSC		(1U <<  21)  /* CPU supports invariant(constant) TSC */


struct x86_64_syspage_entry {
	_Uint64t								gdt;
	_Uint64t								idt;
	_Uint64t								pgdir;
	_Uint64t								spare[5];
};
 
struct x86_64_kernel_entry {
	_Uint8t		code[4];
};


#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86_64/syspage.h $ $Rev: 803179 $")
#endif
