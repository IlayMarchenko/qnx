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
 *  x86/cpu.h
 *

 */

#ifndef __X86_CPU_H_INCLUDED
#define __X86_CPU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __X86_CONTEXT_H_INCLUDED
#include _NTO_HDR_(x86/context.h)
#endif

#define X86_STRINGNAME	"x86"

/*
 * Processor Status Word Register
 */
#define X86_PSW_CF				_ONEBIT32L( 0 )
#define X86_PSW_PF				_ONEBIT32L( 2 )
#define X86_PSW_AF				_ONEBIT32L( 4 )
#define	X86_PSW_ZF				_ONEBIT32L( 6 )
#define X86_PSW_SF				_ONEBIT32L( 7 )
#define X86_PSW_TF				_ONEBIT32L( 8 )
#define X86_PSW_IF				_ONEBIT32L( 9 )
#define X86_PSW_DF				_ONEBIT32L( 10 )
#define X86_PSW_OF				_ONEBIT32L( 11 )
#define X86_PSW_IOPL_MASK		_BITFIELD32L( 12, 0x3 )
#define X86_PSW_IOPL_SHIFT		(12)
#define X86_PSW_NT				_ONEBIT32L( 14 )
#define X86_PSW_RF				_ONEBIT32L( 16 )
#define X86_PSW_VM				_ONEBIT32L( 17 )
#define X86_PSW_AC				_ONEBIT32L( 18 )
#define X86_PSW_VIF				_ONEBIT32L( 19 )
#define X86_PSW_VIP				_ONEBIT32L( 20 )
#define X86_PSW_ID				_ONEBIT32L( 21 )

/*
 * Machine status word/CR0 flags
 */

#define X86_MSW_PE_BIT			0x00000001u		/* Was MSW_PROTECT_BIT */
#define X86_CR0_PE_BIT			0x00000001u		/* Was MSW_PROTECT_BIT */
#define X86_MSW_MP_BIT			0x00000002u
#define X86_CR0_MP_BIT			0x00000002u
#define X86_MSW_EM_BIT			0x00000004u
#define X86_CR0_EM_BIT			0x00000004u
#define X86_MSW_TS_BIT			0x00000008u
#define X86_CR0_TS_BIT			0x00000008u
#define X86_MSW_ET_BIT			0x00000010u
#define X86_MSW_NE_BIT			0x00000020u
#define X86_CR0_ET_BIT			0x00000010u
#define X86_MSW_WP_BIT			0x00010000u
#define X86_CR0_NE_BIT			0x00000020u
#define X86_MSW_AM_BIT			0x00040000u
#define X86_CR0_AM_BIT			0x00040000u
#define X86_CR0_WP_BIT			0x00010000u
#define X86_MSW_NW_BIT			0x20000000u
#define X86_CR0_NW_BIT			0x20000000u
#define X86_MSW_CD_BIT			0x40000000u
#define X86_CR0_CD_BIT			0x40000000u
#define X86_MSW_PG_BIT			0x80000000u
#define X86_CR0_PG_BIT			0x80000000u

/*
 * CR4 flags
 */
#define X86_CR4_VME			0x00000001u
#define X86_CR4_PVI			0x00000002u
#define X86_CR4_TSD			0x00000004u
#define X86_CR4_DE			0x00000008u
#define X86_CR4_PSE			0x00000010u
#define X86_CR4_PAE			0x00000020u
#define X86_CR4_MCE			0x00000040u
#define X86_CR4_PGE			0x00000080u
#define X86_CR4_PCE			0x00000100u
#define X86_CR4_OSFXSR		0x00000200u
#define X86_CR4_OSXMMEXCPT	0x00000400u
#define X86_CR4_VMXE		0x00002000u
#define X86_CR4_SMX			0x00004000u
#define X86_CR4_PCIDE		0x00020000u
#define X86_CR4_OSXSAVE		0x00040000u
#define X86_CR4_SMEP		0x00100000u
#define X86_CR4_SMAP		0x00200000u

/*
 * Sement descriptor flags field.
 *
 *  ------------------------
 * | P | DPL | C | TYPE | A |
 *  ------------------------
 *   7   6 5   4   3 2 1  0
 *
 * C = 1
 * Type consists of three access permission types.
 */

#define X86_ACCESSED				0x01

#define X86_READABLE_CODE			0x02
#define X86_WRITEABLE_DATA			0x02

#define X86_CONFORMING_CODE			0x04
#define X86_EXPANDABLE_DOWN_DATA	0x04

#define X86_EXECUTABLE				0x08	/* Determines meaning of prev 2 bits */

#define X86_SEG_DESCRIPTOR			0x10

#define X86_DPL0					0x00
#define X86_DPL1					0x20
#define X86_DPL2					0x40
#define X86_DPL3					0x60

#define X86_PRESENT					0x80

#define X86_TYPE_CODE_SEG	(X86_PRESENT | X86_DPL0 | X86_SEG_DESCRIPTOR | X86_EXECUTABLE | X86_READABLE_CODE | X86_ACCESSED)
#define X86_TYPE_DATA_SEG	(X86_PRESENT | X86_DPL0 | X86_SEG_DESCRIPTOR | X86_WRITEABLE_DATA | X86_ACCESSED)

/*
 * Sement descriptor limflags field.
 *
 *  -------------------------
 * | G | D | 0 | A |   lim   |
 *  -------------------------
 *   7   6   5   4   3 2 1 0
 *
 * D for code is the same bit as B for data
 */

#define X86_A_BIT	0x10
#define X86_B_BIT	0x40
#define X86_D_BIT	0x40
#define X86_G_BIT	0x80

struct x86_seg_descriptor_entry {
	_Uint16t	limit;
	_Uint16t	base_lo;
	_Uint8t		base_hi;			/* bits 16 to 23 */
	_Uint8t		flags;
	_Uint8t		limflags;			/* limit 16 to 19 and extra flags */
	_Uint8t		base_xhi;			/* bits 24 to 31 */
};


/*
 * System descriptor flags field.
 *
 *  ----------------------
 * | P | DPL | C |  TYPE  |
 *  ----------------------
 *   7   6 5   4   3 2 1 0
 *
 *  C = 0
 *  Type indicates one of 8 descriptor types.
 *	We list only LDT & TSS below (this was wrong in 286 intel manual).
 */

#define X86_TSS16_DESCRIPTOR		1
#define X86_LDT_DESCRIPTOR			2
#define X86_TSS32_DESCRIPTOR		9
#define X86_TYPE_TSS16_SEG	(X86_PRESENT | X86_DPL0 | X86_TSS16_DESCRIPTOR)
#define X86_TYPE_TSS32_SEG	(X86_PRESENT | X86_DPL0 | X86_TSS32_DESCRIPTOR)


/*
 * Gate descriptor flags field
 *
 *  ------------------------
 * | P | DPL | C | TYPE | x |
 *  ------------------------
 *   7   6 5   4   3 2 1  0
 *
 *  C = 0
 *  Type indicates one of 8 descriptor types
 */

#define X86_CALL_GATE16				(4 << 1)
#define X86_INT_GATE16				(6 << 1)
#define X86_TRAP_GATE16				(7 << 1)
#define X86_CALL_GATE32				(12<< 1)
#define X86_INT_GATE32				(14<< 1)
#define X86_TRAP_GATE32				(15<< 1)


struct x86_gate_descriptor_entry {
	_Uint16t	offset_lo;
	_Uint16t	selector;
	_Uint8t		intel_reserved;			/* always zero */
	_Uint8t		flags;
	_Uint16t	offset_hi;
};


/*
 * Selector definition
 *
 *  ------------------------
 * |     index    | T | RPL |
 *  ------------------------
 *  15           3  2   1 0
 */

#define X86_RPL0		0x00
#define X86_RPL1		0x01
#define X86_RPL2		0x02
#define X86_RPL3		0x03

#define X86_USE_LDT		0x04


typedef struct x86_tss_entry {
	_Uint32t	back_link,
				esp0,
				ss0,
				esp1,
				ss1,
				esp2,
				ss2,
				pdbr,
				eip,
				eflags,
				eax,
				ecx,
				edx,
				ebx,
				*esp,
				ebp,
				esi,
				edi,
				es,
				cs,
				ss,
				ds,
				fs,
				gs,
				ldt; 
	_Uint16t	debug_flag; /* T flag in bottom bit */
	_Uint16t	iomap_base;						   
	_Uint32t	iomap_data[1];
} X86_TSS;
	
/*
 * Page directory entry bits
 */

#define X86_PDE_PRESENT			0x00000001
#define X86_PDE_WRITE			0x00000002
#define X86_PDE_USER			0x00000004
#define X86_PDE_WT				0x00000008
#define X86_PDE_CD				0x00000010
#define X86_PDE_ACCESSED		0x00000020
#define X86_PDE_PS				0x00000080
#define X86_PDE_GLOBAL			0x00000100
#define X86_PDE_USER1			0x00000200
#define X86_PDE_USER2			0x00000400
#define X86_PDE_USER3			0x00000800
#define X86_PDE_NX				((uint64_t)0x80000000 << 32)
#define X86_4M_PAGESIZE			0x00400000

/*
 * Page table entry bits
 */

#define X86_PTE_PRESENT			0x00000001
#define X86_PTE_WRITE			0x00000002
#define X86_PTE_USER			0x00000004
#define X86_PTE_WT				0x00000008
#define X86_PTE_CD				0x00000010
#define X86_PTE_ACCESSED		0x00000020
#define X86_PTE_DIRTY			0x00000040
#define X86_PTE_PAT				0x00000080
#define X86_PTE_GLOBAL			0x00000100
#define X86_PTE_USER1			0x00000200
#define X86_PTE_USER2			0x00000400
#define X86_PTE_USER3			0x00000800
#define X86_PTE_NX				((uint64_t)0x80000000 << 32)

/*
 * Error code bits
 */
#define X86_ERRC_PGNP	(1u<<0)
#define X86_ERRC_WRITE	(1u<<1)
#define X86_ERRC_USER	(1u<<2)
#define X86_ERRC_RSV	(1u<<3)
#define X86_ERRC_INSTR	(1u<<4)

/*
 * CPUID feature bits
 */
/* EDX register */
#define X86_FEATURE_FPU			(1U << 0)
#define X86_FEATURE_VME			(1U << 1)
#define X86_FEATURE_DE			(1U << 2)
#define X86_FEATURE_PSE			(1U << 3)
#define X86_FEATURE_TSC			(1U << 4)
#define X86_FEATURE_MSR			(1U << 5)
#define X86_FEATURE_PAE			(1U << 6)
#define X86_FEATURE_MCE			(1U << 7)
#define X86_FEATURE_CXS			(1U << 8)
#define X86_FEATURE_APIC		(1U << 9)
#define X86_FEATURE_SEP			(1U << 11)
#define X86_FEATURE_MTRR		(1U << 12)
#define X86_FEATURE_PGE			(1U << 13)
#define X86_FEATURE_MCA			(1U << 14)
#define X86_FEATURE_CMOV		(1U << 15)
#define X86_FEATURE_PAT			(1U << 16)
#define X86_FEATURE_PSE36		(1U << 17)
#define X86_FEATURE_SN			(1U << 18)
#define X86_FEATURE_CFLUSH		(1U << 19)
#define X86_FEATURE_DS			(1U << 21)
#define X86_FEATURE_ACPI		(1U << 22)
#define X86_FEATURE_MMX			(1U << 23)
#define X86_FEATURE_FXSR		(1U << 24)
#define X86_FEATURE_SIMD		(1U << 25)
#define X86_FEATURE_SSE2		(1U << 26)
#define X86_FEATURE_SS			(1U << 27)
#define X86_FEATURE_HTT			(1U << 28)
#define X86_FEATURE_TM			(1U << 29)
#define X86_FEATURE_PBE			(1U << 31)
/*ECX register */
#define X86_FEATURE2_SSE3		(1U << 0)
#define X86_FEATURE2_PCLMULQDQ	(1U << 1)
#define X86_FEATURE2_DTES64		(1U << 2)
#define X86_FEATURE2_MONITOR	(1U << 3)
#define X86_FEATURE2_DS_CPL		(1U << 4)
#define X86_FEATURE2_VMX		(1U << 5)
#define X86_FEATURE2_SMX		(1U << 6)
#define X86_FEATURE2_EIST		(1U << 7)
#define X86_FEATURE2_TM2		(1U << 8)
#define X86_FEATURE2_SSSE3		(1U << 9)
#define X86_FEATURE2_CNXT_ID	(1U << 10)
#define X86_FEATURE2_FMA		(1U << 12)
#define X86_FEATURE2_CMPXCHG16B	(1U << 13)
#define X86_FEATURE2_xTPR_UPDATE_CONTROL	(1U << 14)
#define X86_FEATURE2_PDCM		(1U << 15)
#define X86_FEATURE2_PCID		(1U << 17)
#define X86_FEATURE2_DCA		(1U << 18)
#define X86_FEATURE2_SSE4_1		(1U << 19)
#define X86_FEATURE2_SSE4_2		(1U << 20)
#define X86_FEATURE2_x2APIC		(1U << 21)
#define X86_FEATURE2_MOVBEA		(1U << 22)
#define X86_FEATURE2_POPCNT		(1U << 23)
#define X86_FEATURE2_TSC_DEADLINE	(1U << 24)
#define X86_FEATURE2_AESNI		(1U << 25)
#define X86_FEATURE2_XSAVE		(1U << 26)
#define X86_FEATURE2_OSXSAVE	(1U << 27)
#define X86_FEATURE2_AVX		(1U << 28)
#define X86_FEATURE2_F16C		(1U << 29)
#define X86_FEATURE2_RDRAND		(1U << 30)

/*
 * CPU invariant TSC
 * input(eax): 80000007H
 * return: invariant TSC:edx[8]
 */
#define X86_TSC_INVARIANT		(1U << 8)

#define X86_FAULT_PAGELP	0x01
#define X86_FAULT_WRITE		0x02
#define X86_FAULT_USER		0x04
#define X86_FAULT_RSV		0x08
#define X86_FAULT_INSTR		0x10

/*
 * MTRR register encodings
 */

#define X86_MSR_MTRRCAP					0xfe
#define X86_MSR_MTRR_PHYSBASE0			0x200
#define X86_MSR_MTRR_PHYSMASK0			0x201
#define X86_MSR_MTRR_DEFTYPE			0x2ff

#define X86_MTRR_CAP_WC					(1UL << 10)
#define X86_MTRR_CAP_FIX				(1UL << 8)
#define X86_MTRR_CAP_NVAR_MASK			0x000000ff

#define X86_MTRR_DEFTYPE_MASK			0x000000ff
#define X86_MTRR_DEFTYPE_FE				(1UL << 10)
#define X86_MTRR_DEFTYPE_E				(1UL << 11)

#define X86_MTRR_PHYSBASE_TYPE_MASK		0x000000ff
#define X86_MTRR_PHYSBASE_BASE_MASK		(((uint64_t)0x0000000f << 32) | (uint64_t)0xfffff000)
#define X86_MTRR_PHYSMASK_RANGE_MASK	(((uint64_t)0x0000000f << 32) | (uint64_t)0xfffff000)
#define X86_MTRR_PHYSMASK_VALID			(1UL << 11)

#define X86_MTRR_TYPE_UNCACHEABLE		0
#define X86_MTRR_TYPE_WRITECOMBINING	1
#define X86_MTRR_TYPE_WRITETHROUGH		4
#define X86_MTRR_TYPE_WRITEPROTECTED	5
#define X86_MTRR_TYPE_WRITEBACK			6


/*
 * PAT register encodings
 */

#define X86_PAT_UC    0x00u
#define X86_PAT_WC    0x01u
#define X86_PAT_WT    0x04u
#define X86_PAT_WP    0x05u
#define X86_PAT_WB    0x06u
#define X86_PAT_UCM   0x07u
#define X86_PAT_MASK  0x07u
	
#define X86_MSR_PAT                     0x277u



/*
 * Extended Feature Enable Register
 */
#define X86_MSR_EFER		0xc0000080
#define X86_EFER_SCE		(1 << 0)
#define X86_EFER_LME		(1 << 8)
#define X86_EFER_LMA		(1 << 10)
#define X86_EFER_NXE		(1 << 11)


/*
 * XSAVE/XRSTOR header
 *
 */
struct x86_xsave_header {
	_Uint64t		xstate_bv;
	_Uint8t			reserved[56];
};


#endif /* __X86_CPU_H_INCLUDED */


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86/cpu.h $ $Rev: 803179 $")
#endif
