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
 *  x86_64/cpu.h
 *
 */

/* FIXME: a lot of these definitions are duplicated from x86.  We need to
 * go through them, get rid of any that aren't applicable to x86_64, and
 * maybe get rid of the duplication by keeping them in one place.
 */

#ifndef __X86_64_CPU_H_INCLUDED
#define __X86_64_CPU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __X86_64_CONTEXT_H_INCLUDED
#include _NTO_HDR_(x86_64/context.h)
#endif


#define X86_64_STRINGNAME	"x86_64"

/*
 * SEGMENT DWORD #1
 *  ------------------------
 * |Base 31-24|G|D|L|?|SEGLIM|P|DPL|C|TYPE|A|Base 23-16|
 *  ------------------------
 *
 * C = 1
 * Type consists of three access permission types.
 */
#define X86_64_GRAN                 (1u<<23)
#define X86_64_32BIT                (1u<<22)
#define X86_64_64BIT                (1u<<21)
#define X86_64_AVAIL	            (1u<<20)
#define X86_64_PRESENT				(1u<<15)
#define X86_64_DPL(n)				((n)<<13)
#define X86_64_SEGMENT              (1u<<12)
#define  X86_64_EXECUTABLE          (1u<<11)
#define    X86_64_CONFORMING        (1u<<10)
#define    X86_64_READABLE          (1u<<9)
#define  X86_64_DATA                (0u<<11)
#define    X86_64_EXPANDDOWN        (1u<<10)
#define    X86_64_WRITABLE          (1u<<9)
#define  X86_64_ACCESSED            (1u<<8)
#define X86_64_SYSTEM               (0u<<12)
#define X86_64_SYSTYPE(x)           ((x)<<8)
#define  X86_64_LDT		    2u
#define  X86_64_TSS64		9u
#define  X86_64_CALL_GATE   12u
#define  X86_64_INTR_GATE   14u
#define  X86_64_TRAP_GATE   15u

#define X86_64_READABLE_CODE		(X86_64_READABLE)
#define X86_64_WRITEABLE_DATA		(X86_64_WRITABLE)
#define X86_64_CONFORMING_CODE		(X86_64_CONFORMING)
#define X86_64_SEG_DESCRIPTOR		(X86_64_SEGMENT)

#define X86_64_LONG_CSEG(n) \
	(X86_64_PRESENT |\
     X86_64_DPL(n) |\
     X86_64_SEGMENT |\
     X86_64_EXECUTABLE | \
	 X86_64_64BIT)\

#define X86_64_LONG_DSEG(n) \
	(X86_64_PRESENT | X86_64_SEG_DESCRIPTOR)


#define X86_64_COMPAT_CSEG(n) \
	(X86_64_PRESENT | \
	X86_64_DPL(n) | \
	X86_64_SEGMENT | \
	X86_64_EXECUTABLE | \
	X86_64_READABLE | \
	X86_64_ACCESSED | \
	X86_64_32BIT | \
	X86_64_GRAN)

#define X86_64_COMPAT_DSEG(n)	\
	(X86_64_PRESENT |\
	 X86_64_DPL(n) |\
	 X86_64_SEG_DESCRIPTOR |\
	 X86_64_WRITEABLE_DATA |\
	 X86_64_ACCESSED |\
	 X86_64_32BIT | \
	 X86_64_GRAN)


#define X86_64_SYSSEG(dpl, type) \
	(X864_64_PRESENT | ((dpl)<<5) | ((type)<<1))

/*-
 note: segment descriptor indexing is the same as with x86, that is,
       segment index * 8 is the byte offset in the [lg]dt of the
       descriptor to be loaded.
       segment indexes must be divisible by 2:
		ie. 0, 2, 4, 6.
       although the hardware doesn't enforce this.   The 'zero' location
       in the long mode descriptor, however, would cause an invalid type
       segment load [thus #gpf ].
*/

/*
 * CPUID feature bits
 */
/* EDX register */
#define X86_64_FEATURE_FPU			(1U << 0)
#define X86_64_FEATURE_VME			(1U << 1)
#define X86_64_FEATURE_DE			(1U << 2)
#define X86_64_FEATURE_PSE			(1U << 3)
#define X86_64_FEATURE_TSC			(1U << 4)
#define X86_64_FEATURE_MSR			(1U << 5)
#define X86_64_FEATURE_PAE			(1U << 6)
#define X86_64_FEATURE_MCE			(1U << 7)
#define X86_64_FEATURE_CXS			(1U << 8)
#define X86_64_FEATURE_APIC			(1U << 9)
#define X86_64_FEATURE_SEP			(1U << 11)
#define X86_64_FEATURE_MTRR			(1U << 12)
#define X86_64_FEATURE_PGE			(1U << 13)
#define X86_64_FEATURE_MCA			(1U << 14)
#define X86_64_FEATURE_CMOV			(1U << 15)
#define X86_64_FEATURE_PAT			(1U << 16)
#define X86_64_FEATURE_PSE36		(1U << 17)
#define X86_64_FEATURE_SN			(1U << 18)
#define X86_64_FEATURE_CFLUSH		(1U << 19)
#define X86_64_FEATURE_DS			(1U << 21)
#define X86_64_FEATURE_ACPI			(1U << 22)
#define X86_64_FEATURE_MMX			(1U << 23)
#define X86_64_FEATURE_FXSR			(1U << 24)
#define X86_64_FEATURE_SIMD			(1U << 25)
#define X86_64_FEATURE_SSE2			(1U << 26)
#define X86_64_FEATURE_SS			(1U << 27)
#define X86_64_FEATURE_HTT			(1U << 28)
#define X86_64_FEATURE_TM			(1U << 29)
#define X86_64_FEATURE_PBE			(1U << 31)
/*ECX register */
#define X86_64_FEATURE2_SSE3		(1U << 0)
#define X86_64_FEATURE2_PCLMULQDQ	(1U << 1)
#define X86_64_FEATURE2_DTES64		(1U << 2)
#define X86_64_FEATURE2_MONITOR		(1U << 3)
#define X86_64_FEATURE2_DS_CPL		(1U << 4)
#define X86_64_FEATURE2_VMX			(1U << 5)
#define X86_64_FEATURE2_SMX			(1U << 6)
#define X86_64_FEATURE2_EIST		(1U << 7)
#define X86_64_FEATURE2_TM2			(1U << 8)
#define X86_64_FEATURE2_SSSE3		(1U << 9)
#define X86_64_FEATURE2_CNXT_ID		(1U << 10)
#define X86_64_FEATURE2_FMA			(1U << 12)
#define X86_64_FEATURE2_CMPXCHG16B	(1U << 13)
#define X86_64_FEATURE2_xTPR_UPDATE_CONTROL	(1U << 14)
#define X86_64_FEATURE2_PDCM		(1U << 15)
#define X86_64_FEATURE2_PCID		(1U << 17)
#define X86_64_FEATURE2_DCA			(1U << 18)
#define X86_64_FEATURE2_SSE4_1		(1U << 19)
#define X86_64_FEATURE2_SSE4_2		(1U << 20)
#define X86_64_FEATURE2_x2APIC		(1U << 21)
#define X86_64_FEATURE2_MOVBEA		(1U << 22)
#define X86_64_FEATURE2_POPCNT		(1U << 23)
#define X86_64_FEATURE2_TSC_DEADLINE (1U << 24)
#define X86_64_FEATURE2_AESNI		(1U << 25)
#define X86_64_FEATURE2_XSAVE		(1U << 26)
#define X86_64_FEATURE2_OSXSAVE		(1U << 27)
#define X86_64_FEATURE2_AVX			(1U << 28)
#define X86_64_FEATURE2_F16C		(1U << 29)
#define X86_64_FEATURE2_RDRAND		(1U << 30)
#define X86_64_FEATURE2_HYPERVISOR	(1U << 31)
/*CPUID 06H (Thermal and Power Management Leaf) */
#define X86_64_TPML_EAX_DTS			(1U << 0)
#define X86_64_TPML_EAX_PTM			(1U << 6)
#define X86_64_TPML_ECX_HCFC		(1U << 0)
#define X86_64_TPML_ECX_EPB			(1U << 3)
/*CPUID 07H (Structured Extended Feature Flags Enumeration Leaf) sub-leaf 0 */
#define X86_64_SEFFEL0_EBX_TSC_ADJ	(1U << 1)
#define X86_64_SEFFEL0_EBX_SMEP		(1U << 7)

/*
 * CPU invariant TSC
 * input(eax): 80000007H
 * return: invariant TSC:edx[8]
 */
#define X86_64_TSC_INVARIANT		(1U << 8)

typedef struct x86_64_segment {
	_Uint32t    desc[2];
} X86_64_SEG;


typedef struct x86_64_gate {
	_Uint16t    offset_0_15;
	_Uint16t    selector;
	_Uint8t     stack; /*must be zero*/
	_Uint8t     gate_type;
	_Uint16t    offset_16_31;
	_Uint32t    offset_32_63;
	_Uint32t    reserved;  /* must be zero */
/*-
 * note the last field, by being zero, ensures 'odd' selectors
 * are invalid.
 */
} X86_64_GATE;

#include _NTO_HDR_(_pack1.h)

typedef struct x86_64_tss  {
    _Uint32t    rsvd1;
    _Uint64t    rsp0;
    _Uint64t    rsp1;
    _Uint64t    rsp2;
    _Uint64t    rsvd2;
    _Uint64t    ist1;
    _Uint64t    ist2;
    _Uint64t    ist3;
    _Uint64t    ist4;
    _Uint64t    ist5;
    _Uint64t    ist6;
    _Uint64t    ist7;
    _Uint64t    rsvd3;
    _Uint16t    rsvd4;
    _Uint16t    iobmap;
} X86_64_TSS;

#include _NTO_HDR_(_packpop.h)

/*
 * Selector definition
 *
 *  ------------------------
 * |     index    | T | RPL |
 *  ------------------------
 *  15           3  2   1 0
 */

#define X86_64_RPL0		0x00u
#define X86_64_RPL1		0x01u
#define X86_64_RPL2		0x02u
#define X86_64_RPL3		0x03u

#define X86_64_USE_LDT	0x04u

/*-
 * Traps are mashalled to the correct stack based on priority;
 * for example, an NMI can occur just after an interrupt, but before
 * the kernel stack has been cleaned up; therefore it needs its own
 * stack.
 */

#define X86_64_TRAP_STACK   1u
#define X86_64_ERR_STACK    2u
#define X86_64_INTR_STACK   3u
#define X86_64_DEBUG_STACK  4u /* kdebug */
#define X86_64_NMI_STACK    5u
#define X86_64_SMP_STACK    6u /* may not be necessary, but very fast */
#define X86_64_USER_STACK   7u /* not sure. */

#define X86_64_ITOSEL(x)  (((x)<<3))

#define X86_64_LDT_SEL    ((2u<<3)|0u)

/*-
 * The layout is required by syscall, specifically that the
 * syscall SS = syscall CS + 8.
 */

#define X86_64_KER_CS     ((4u<<3)|0u)
#define X86_64_KER_SS     ((5u<<3)|0u)

#define X86_64_SYS_CS     ((6u<<3)|1u)
#define X86_64_SYS_SS     ((7u<<3)|1u)

#define X86_64_USR32_CS   (( 9u<<3)|3u)
#define X86_64_USR_SS     ((10u<<3)|3u)
#define X86_64_USR_CS     ((11u<<3)|3u)


#define X86_64_TSS_SEL0   ((32u<<3)|0u)
#define X86_64_FS0   	  ((34u<<3)|3u)



/*
 * PAT register encodings
 */

#define X86_64_PAT_UC		0x00u
#define X86_64_PAT_WC		0x01u
#define X86_64_PAT_WT		0x04u
#define X86_64_PAT_WP		0x05u
#define X86_64_PAT_WB		0x06u
#define X86_64_PAT_UCM		0x07u		/* UC- */
#define X86_64_PAT_MASK		0x07u

#define X86_64_MSR_PAT		0x277u


/*
 * Processor Status Word Register
 */
#define X86_64_PSW_CF				(1ULL<< 0 )
#define X86_64_PSW_PF				(1ULL<< 2 )
#define X86_64_PSW_AF				(1ULL<< 4 )
#define	X86_64_PSW_ZF				(1ULL<< 6 )
#define X86_64_PSW_SF				(1ULL<< 7 )
#define X86_64_PSW_TF				(1ULL<< 8 )
#define X86_64_PSW_IF				(1ULL<< 9 )
#define X86_64_PSW_DF				(1ULL<< 10)
#define X86_64_PSW_OF				(1ULL<< 11)
#define X86_64_PSW_IOPL_MASK		(3ULL<<12)
#define X86_64_PSW_IOPL_SHIFT		(12)
#define X86_64_PSW_NT				(1ULL<< 14)
#define X86_64_PSW_RF				(1ULL<< 16)
#define X86_64_PSW_VM				(1ULL<< 17)
#define X86_64_PSW_AC				(1ULL<< 18)
#define X86_64_PSW_VIF				(1ULL<< 19)
#define X86_64_PSW_VIP				(1ULL<< 20)
#define X86_64_PSW_ID				(1ULL<< 21)

/*
 * CRO flags
 */

#define X86_64_CR0_PE_BIT			0x00000001ull		/* Was MSW_PROTECT_BIT */
#define X86_64_CR0_MP_BIT			0x00000002ull
#define X86_64_CR0_EM_BIT			0x00000004ull
#define X86_64_CR0_TS_BIT			0x00000008ull
#define X86_64_CR0_ET_BIT			0x00000010ull
#define X86_64_CR0_NE_BIT			0x00000020ull
#define X86_64_CR0_WP_BIT			0x00010000ull
#define X86_64_CR0_AM_BIT			0x00040000ull
#define X86_64_CR0_NW_BIT			0x20000000ull
#define X86_64_CR0_CD_BIT			0x40000000ull
#define X86_64_CR0_PG_BIT			0x80000000ull

/*
 * CR3 flags
 */

#define X86_64_CR3_PWT				0x00000004ull
#define X86_64_CR3_PCD				0x00000010ull
#define X86_64_CR3_PAMASK			0x000ffffffffff000ull
/*
 * CR4 flags
 */
#define X86_64_CR4_VME				0x00000001ull
#define X86_64_CR4_PVI				0x00000002ull
#define X86_64_CR4_TSD				0x00000004ull
#define X86_64_CR4_DE				0x00000008ull
#define X86_64_CR4_PSE				0x00000010ull
#define X86_64_CR4_PAE				0x00000020ull
#define X86_64_CR4_MCE				0x00000040ull
#define X86_64_CR4_PGE				0x00000080ull
#define X86_64_CR4_PCE				0x00000100ull
#define X86_64_CR4_OSFXSR			0x00000200ull
#define X86_64_CR4_OSXMMEXCPT		0x00000400ull
#define X86_64_CR4_VMXE				0x00002000ull
#define X86_64_CR4_SMX				0x00004000ull
#define X86_64_CR4_PCIDE			0x00020000ull
#define X86_64_CR4_OSXSAVE			0x00040000ull
#define X86_64_CR4_SMEP				0x00100000ull
#define X86_64_CR4_SMAP				0x00200000ull


/*
 * Page table entry bits
 */

#define X86_64_PTE_PRESENT			(1u<<0)
#define X86_64_PTE_WRITE			(1u<<1)
#define X86_64_PTE_USER				(1u<<2)
#define X86_64_PTE_WT				(1u<<3)
#define X86_64_PTE_CD				(1u<<4)
#define X86_64_PTE_ACCESSED			(1u<<5)
#define X86_64_PTE_DIRTY			(1u<<6)
/* Pagesize for an interior entry [level 0..3]; PAT for level 4 ] */
#define X86_64_PTE_PS               (1u<<7)
#define X86_64_PTE_PAT				(1u<<7)
#define X86_64_PTE_GLOBAL			(1u<<8)
#define X86_64_PTE_USER1			(1u<<9)
#define X86_64_PTE_USER2			(1u<<10)
#define X86_64_PTE_USER3			(1u<<11)
#define X86_64_PTE_NX				(1ull<<63)

/*
 * Error code bits
 */
#define X86_64_ERRC_PGNP	(1u<<0)
#define X86_64_ERRC_WRITE	(1u<<1)
#define X86_64_ERRC_USER	(1u<<2)
#define X86_64_ERRC_RSV		(1u<<3)
#define X86_64_ERRC_INSTR	(1u<<4)

/*
 * MTRR register encodings
 */
#define X86_64_MSR_APICBASE         0x1bu
#define X86_64_MSR_PERFCTR0         0xc1u
#define X86_64_MSR_PERFCTR1         0xc2u

#define X86_64_MSR_MTRRCAP			0xfeu
#define X86_64_MSR_MTRR_PHYSBASE0		0x200u
#define X86_64_MSR_MTRR_PHYSMASK0		0x201u
#define X86_64_MSR_MTRR_DEFTYPE			0x2ffu

#define X86_64_MTRR_CAP_WC			(1u << 10)
#define X86_64_MTRR_CAP_FIX			(1u << 8)
#define X86_64_MTRR_CAP_NVAR_MASK		0x000000ffu

#define X86_64_MTRR_DEFTYPE_MASK		0x000000ffu
#define X86_64_MTRR_DEFTYPE_FE			(1u << 10)
#define X86_64_MTRR_DEFTYPE_E			(1u << 11)

#define X86_64_MTRR_PHYSBASE_TYPE_MASK		0x000000ffu
#define X86_64_MTRR_PHYSBASE_BASE_MASK		0xffffff000ull
#define X86_64_MTRR_PHYSMASK_RANGE_MASK	        0xffffff000ull
#define X86_64_MTRR_PHYSMASK_VALID		(1u << 11)

#define X86_64_MTRR_TYPE_UNCACHEABLE		0u
#define X86_64_MTRR_TYPE_WRITECOMBINING		1u
#define X86_64_MTRR_TYPE_WRITETHROUGH		4u
#define X86_64_MTRR_TYPE_WRITEPROTECTED		5u
#define X86_64_MTRR_TYPE_WRITEBACK			6u

/*
 * Extended Feature Enable Register
 */
#define __MSREXT(x)         (0xc0000000u|(x))

#define X86_64_MSR_EFER		(__MSREXT(0x80u))
#define X86_64_EFER_SCE		(1u << 0)
#define X86_64_EFER_LME		(1u << 8)
#define X86_64_EFER_LMA		(1u << 10)
#define X86_64_EFER_NXE		(1u << 11)

#define X86_64_MSR_STAR     (__MSREXT(0x81u))
#define X86_64_MSR_LSTAR    (__MSREXT(0x82u))
#define X86_64_MSR_CSTAR    (__MSREXT(0x83u))
#define X86_64_MSR_SFMASK   (__MSREXT(0x84u))

#define X86_64_MSR_USRFS   (__MSREXT(0x100u))
#define X86_64_MSR_USRGS   (__MSREXT(0x101u))
#define X86_64_MSR_KERGS   (__MSREXT(0x102u))
#define X86_64_MSR_TSCAUX  (__MSREXT(0x103u))

#define X86_64_MSR_SYSENTER_CS		0x174u
#define X86_64_MSR_SYSENTER_ESP		0x175u
#define X86_64_MSR_SYSENTER_EIP		0x176u
/*
 * This keeps the bootstrap addresses low so the existing startup continues
 * to work.
 */

/* these are in 0.5Tbyte slots */
#define X86_64_MREGSHFT    39

#define X86_64_AS_USER     0UL

/*
 * The following slots are used for msg xfer (and maybe other circumstances
 * where we want to map one address space's slot 0 into another address space?)
 * The range for these slots is [X86_64_AS_ASIDLO .. X86_64_AS_ASIDHI] -- that is,
 * inclusive of the given values at both ends of the range.
 */
#define X86_64_AS_ASIDLO   4UL
#define X86_64_AS_ASIDHI   132UL

/*-
 * this little oddity should maybe be encapsulated in a function;
 * but that kills static initialization, etc...
 *
 * The range of virtual address from
 * 2^48.. 2^64-2^48 are invalid, and cause GP-FAULTs if referenced.
 * Someday, the amd64 architecture may grow by another page table level,
 * and this will change to
 * 2^57..2^64-2^57.
 */

#define _X86_64_AS_SLOT2VA(_s) (\
	(((_s) >= 256U) ? \
		(0xffff800000000000ULL + (((_s)-256U) << X86_64_MREGSHFT)) :\
		((_s) << X86_64_MREGSHFT)\
	))

#define X86_64_AS_SLOT2VA(_s) (_X86_64_AS_SLOT2VA((_Uint64t)(_s)))


/*
 * This is a bit more expansive.   Everything system lives on a higher plane,
 * everything user is closer to ground.
 */

#define X86_64_AS_SYS      256UL
#define X86_64_AS_STARTUP  257UL

#define X86_64_AS_COMMON_LO  256UL
#define X86_64_AS_COMMON_HI  511UL

/* VMX related MSR's */
#define X86_VMX_MSR_BASIC					0x480u
#define X86_VMX_MSR_PINBASED_CTLS			0x481u
#define X86_VMX_MSR_PROCBASED_CTLS			0x482u
#define X86_VMX_MSR_EXIT_CTLS				0x483u
#define X86_VMX_MSR_ENTRY_CTLS				0x484u
#define X86_VMX_MSR_MISC					0x485u
#define X86_VMX_MSR_CR0_FIXED0				0x486u
#define X86_VMX_MSR_CR0_FIXED1				0x487u
#define X86_VMX_MSR_CR4_FIXED0				0x488u
#define X86_VMX_MSR_CR4_FIXED1				0x489u
#define X86_VMX_MSR_VMCS_ENUM				0x48au
#define X86_VMX_MSR_PROCBASED_CTLS2			0x48bu
#define X86_VMX_MSR_EPT_VPID_CAP			0x48cu
#define X86_VMX_MSR_TRUE_PINBASED_CTLS		0x48du
#define X86_VMX_MSR_TRUE_PROCBASED_CTLS		0x48eu
#define X86_VMX_MSR_TRUE_EXIT_CTLS			0x48fu
#define X86_VMX_MSR_TRUE_ENTRY_CTLS			0x490u
#define X86_VMX_MSR_VMFUNC					0x491u

#define X86_64_MSR_IA32_FEATURE_CONTROL	0x0000003au
#define X86_64_MSR_PERF_GLOBAL_CTRL		0x0000038fu
#define X86_64_MSR_MISC_ENABLE			0x000001a0u
#define X86_64_MSR_XSS					0x00000da0u

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86_64/cpu.h $ $Rev: 821048 $")
#endif
