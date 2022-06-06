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
 *  x86/syspage.h
 *

 */

#ifndef __SYSPAGE_H_INCLUDED
#error x86/syspage.h should not be included directly.
#endif

/*
 *	CPU capability/state flags
 */
#define X86_CPU_CPUID		(1U <<  0)	/* CPU supports cpuid instruction */
#define X86_CPU_RDTSC		(1U <<  1)	/* CPU supports rdtsc instruction */
#define X86_CPU_INVLPG		(1U <<  2)  /* CPU has INVLPG instruction */
#define X86_CPU_WP			(1U <<  3)  /* CPU has WP bit in CR0 */
#define X86_CPU_BSWAP		(1U <<  4)  /* CPU has BSWAP instruction */
#define X86_CPU_MMX			(1U <<  5)  /* CPU has MMX instructions */
#define X86_CPU_CMOV		(1U <<  6)  /* CPU has CMOVxx instructions */
#define X86_CPU_PSE			(1U <<  7)  /* CPU has page size extensions */
#define X86_CPU_PGE			(1U <<  8)  /* CPU has TLB global mappings */
#define X86_CPU_MTRR		(1U <<  9)  /* CPU has MTRR registers */
#define X86_CPU_SEP			(1U <<  10)  /* CPU supports SYSENTER  */
#define X86_CPU_SIMD		(1U <<  11)  /* CPU supports SIMD (SSE1)  */
#define X86_CPU_FXSR		(1U <<  12)  /* CPU supports FXSAVE/FXRSTOR  */
#define X86_CPU_PAE			(1U <<  13)  /* CPU has phys addr extension  */
#define X86_CPU_NX			(1U <<  14)  /* CPU supports NX PTE bit */
#define X86_CPU_SSE2		(1U <<  15)  /* CPU supports SSE2 */
#define X86_CPU_AVX			(1U <<  16)  /* CPU supports AVX */
#define X86_CPU_XSAVE		(1U <<  17)  /* CPU supports XSAVE/XRSTOR */
#define X86_CPU_PAT			(1U <<  18)  /* CPU supports Page Attribute Tables */
#define X86_CPU_PTESPLIT_TLBFLUSH (1U <<  19)  /* Needs TLB flush when splitting a large page */
#define X86_CPU_PCID		(1U <<  20)  /* CPU supports PCID's */
#define X86_CPU_INVARIANT_TSC		(1U <<  21)  /* CPU supports invariant(constant) TSC */

#if defined(ENABLE_DEPRECATED_SYSPAGE_SECTIONS)
/*
 *	Support hardware flags
 */
#define X86_HW_A20_MASK			(7U <<  0)	/* Mask A20 gating type */
#define X86_HW_A20_NONE			(0U <<  0)	/* No A20 gate */
#define X86_HW_A20_FAST			(1U <<  0)	/* PS/2 fast A20 gate */
#define X86_HW_A20_AT			(2U <<  0)	/* Standard AT kbd ctrl A20 gate */
#define X86_HW_A20_7552			(3U <<  0)	/* IBM 7552 A20 gate */
#define X86_HW_WATCHDOG_MASK	(7U <<  3)  /* Watchdog timer type */
#define X86_HW_WATCHDOG_NONE	(0U <<  3)	/* No watchdog */
#define X86_HW_WATCHDOG_PS2		(1U <<  3)  /* PS/2 watchdog */
#define X86_HW_WATCHDOG_386EX	(2U <<  3)  /* 386ex watchdog */
#define X86_HW_BUS_ISA			(1U <<  6)	/* Machine has ISA bus */
#define X86_HW_BUS_EISA			(1U <<  7)	/* Machine has EISA bus */
#define X86_HW_BUS_PCI			(1U <<  8)  /* Machine has PCI bus */
#define X86_HW_BUS_MCA			(1U <<  9)	/* Machine has micro channel bus */
#define X86_HW_NO_DMA_MEM		(1U << 10)	/* Machine has memory you can't DMA to/from */

struct	x86_boxinfo_entry {
	_Uint32t		hw_flags;			/* HW_* */
	_Uint32t		spare[9];
};

struct x86_diskinfo_entry {
	_Uint16t    valid;
	_Uint16t    heads;
	_Uint16t    cyls;
	_Uint16t    sectors;
	_Uint32t    nblocks;
	_Uint32t	spare;
};

struct x86_smpinfo_entry {
	_SCPPONLY32(void,ap_start_addr,);
	_SCPPONLY32(unsigned,lapic_addr,);
	_Uint32t			spare;
	_Uint8t 			lapicid_to_index[16];
};
#endif

struct x86_syspage_entry {
	syspage_entry_info						DEPRECATED_SECTION_NAME(boxinfo);
	syspage_entry_info						DEPRECATED_SECTION_NAME(smpinfo);
	syspage_entry_info				 		DEPRECATED_SECTION_NAME(diskinfo);
	_Uint32t								spare[4];
	_SCPPONLY32(struct x86_seg_descriptor_entry, gdt,);
	_SCPPONLY32(struct x86_gate_descriptor_entry, idt,);
	_SCPPONLY32(_Paddr32t, pgdir,);
	_SCPPONLY32(void, real_addr,);
};

struct x86_kernel_entry {
	 _Uint8t	code[4]; 
};


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86/syspage.h $ $Rev: 803179 $")
#endif
