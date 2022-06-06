/*
 * $QNXLicenseC: 
 * Copyright 2014, QNX Software Systems.  
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
 *  aarch64/cpu.h
 */

#ifndef __AARCH64_CPU_H_INCLUDED
#define __AARCH64_CPU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __AARCH64_CONTEXT_H_INCLUDED
#include _NTO_HDR_(aarch64/context.h)
#endif

#define AARCH64_STRINGNAME	"aarch64"

/*
 * AArch64 PSTATE register bits
 */
#define	AARCH64_PSTATE_MODE_MASK	0x1fu
#define	AARCH64_PSTATE_nRW			0x10u

#define	AARCH64_PSTATE_MODE(x)		(((unsigned)(x) & AARCH64_PSTATE_MODE_MASK))
#define	AARCH64_PSTATE_AARCH32(x)	((unsigned)(x) & AARCH64_PSTATE_nRW)
#define	AARCH64_PSTATE_EL0t	0x0u
#define	AARCH64_PSTATE_EL1t	0x4u
#define	AARCH64_PSTATE_EL1h	0x5u
#define	AARCH64_PSTATE_EL2t	0x8u
#define	AARCH64_PSTATE_EL2h	0x9u
#define	AARCH64_PSTATE_EL3t	0xcu
#define	AARCH64_PSTATE_EL3h	0xdu

#define	AARCH64_PSTATE_F	(1u << 6)
#define	AARCH64_PSTATE_I	(1u << 7)
#define	AARCH64_PSTATE_A	(1u << 8)
#define	AARCH64_PSTATE_D	(1u << 9)

#define	AARCH64_PSTATE_IL	(1u << 20)
#define	AARCH64_PSTATE_SS	(1u << 21)

#define	AARCH64_PSTATE_V	(1u << 28)
#define	AARCH64_PSTATE_C	(1u << 29)
#define	AARCH64_PSTATE_Z	(1u << 30)
#define	AARCH64_PSTATE_N	(1u << 31)

/*
 * AArch32 PSTATE register bits
 */
#define AARCH32_CPSR_MODE		0x1fu
#define AARCH32_CPSR_USR		0x10u
#define AARCH32_CPSR_FIQ		0x11u
#define AARCH32_CPSR_IRQ		0x12u
#define AARCH32_CPSR_SVC		0x13u
#define AARCH32_CPSR_ABT		0x17u
#define AARCH32_CPSR_UND		0x1bu
#define AARCH32_CPSR_SYS		0x1fu
#define AARCH32_CPSR_T			(1u << 5)
#define AARCH32_CPSR_F			(1u << 6)
#define AARCH32_CPSR_I			(1u << 7)
#define	AARCH32_CPSR_A			(1u << 8)
#define	AARCH32_CPSR_E			(1u << 9)
#define	AARCH32_CPSR_GE_MASK	0x000f0000u
#define	AARCH32_CPSR_GE0		(1u << 16)
#define	AARCH32_CPSR_GE1		(1u << 17)
#define	AARCH32_CPSR_GE2		(1u << 18)
#define	AARCH32_CPSR_GE3		(1u << 19)
#define	AARCH32_CPSR_J			(1u << 24)
#define	AARCH32_CPSR_Q			(1u << 27)
#define AARCH32_CPSR_COND_MASK	0xf0000000u
#define AARCH32_CPSR_V			(1u << 28)
#define AARCH32_CPSR_C			(1u << 29)
#define AARCH32_CPSR_Z			(1u << 30)
#define AARCH32_CPSR_N			(1u << 31)
#define AARCH32_CPSR_IT_1_0		0x06000000u
#define AARCH32_CPSR_IT_7_2		0x0000fc00u
#define AARCH32_CPSR_ITSTATE	(AARCH32_CPSR_IT_1_0|AARCH32_CPSR_IT_7_2)

/*
 * AArch64 SCTLR_EL1 bits
 */
#define	AARCH64_SCTLR_EL1_UCI	(1u << 26)
#define	AARCH64_SCTLR_EL1_EE	(1u << 25)
#define	AARCH64_SCTLR_EL1_E0E	(1u << 24)
#define	AARCH64_SCTLR_EL1_WXN	(1u << 19)
#define	AARCH64_SCTLR_EL1_nTWE	(1u << 18)
#define	AARCH64_SCTLR_EL1_nTWI	(1u << 16)
#define	AARCH64_SCTLR_EL1_UCT	(1u << 15)
#define	AARCH64_SCTLR_EL1_DZE	(1u << 14)
#define	AARCH64_SCTLR_EL1_I		(1u << 12)
#define	AARCH64_SCTLR_EL1_UMA	(1u << 9)
#define	AARCH64_SCTLR_EL1_SED	(1u << 8)
#define	AARCH64_SCTLR_EL1_ITD	(1u << 7)
#define	AARCH64_SCTLR_EL1_BEN	(1u << 5)
#define	AARCH64_SCTLR_EL1_SA0	(1u << 4)
#define	AARCH64_SCTLR_EL1_SA	(1u << 3)
#define	AARCH64_SCTLR_EL1_C		(1u << 2)
#define	AARCH64_SCTLR_EL1_A		(1u << 1)
#define	AARCH64_SCTLR_EL1_M		(1u << 0)
#define	AARCH64_SCTLR_EL1_RES1		\
	(								\
		(1u << 29) |				\
		(1u << 28) |				\
		(1u << 23) |				\
		(1u << 22) |				\
		(1u << 20) |				\
		(1u << 11) \
	)

/*
 * ESR Exception Codes
 */
#define	AARCH64_ESR_EC_SHIFT		26u
#define	AARCH64_ESR_EC(x)			((x) >> AARCH64_ESR_EC_SHIFT)
#define	AARCH64_ESR_EC_UNKNOWN		0x00u
#define	AARCH64_ESR_EC_WFI			0x01u
#define	AARCH64_ESR_EC_CP15_MCR		0x03u
#define	AARCH64_ESR_EC_CP15_MCRR	0x04u
#define	AARCH64_ESR_EC_CP14_MCR		0x05u
#define	AARCH64_ESR_EC_CP14_LS		0x06u
#define	AARCH64_ESR_EC_FPSIMD		0x07u
#define	AARCH64_ESR_EC_CP10_MCR		0x08u
#define	AARCH64_ESR_EC_CP14_MCRR	0x0cu
#define	AARCH64_ESR_EC_ILL			0x0eu
#define	AARCH64_ESR_EC_SVC_32		0x11u
#define	AARCH64_ESR_EC_HVC_32		0x12u
#define	AARCH64_ESR_EC_SMC_32		0x13u
#define	AARCH64_ESR_EC_SVC_64		0x15u
#define	AARCH64_ESR_EC_HVC_64		0x16u
#define	AARCH64_ESR_EC_SMC_64		0x17u
#define	AARCH64_ESR_EC_SYS_64		0x18u
#define	AARCH64_ESR_EC_IABT_EL0		0x20u
#define	AARCH64_ESR_EC_IABT_EL1		0x21u
#define	AARCH64_ESR_EC_PC_ALIGN		0x22u
#define	AARCH64_ESR_EC_DABT_EL0		0x24u
#define	AARCH64_ESR_EC_DABT_EL1		0x25u
#define	AARCH64_ESR_EC_SP_ALIGN		0x26u
#define	AARCH64_ESR_EC_FPEXC_32		0x28u
#define	AARCH64_ESR_EC_FPEXC_64		0x2cu
#define	AARCH64_ESR_EC_SERR			0x2fu
#define	AARCH64_ESR_EC_BREAK_EL0	0x30u
#define	AARCH64_ESR_EC_BREAK_EL1	0x31u
#define	AARCH64_ESR_EC_SSTEP_EL0	0x32u
#define	AARCH64_ESR_EC_SSTEP_EL1	0x33u
#define	AARCH64_ESR_EC_WATCH_EL0	0x34u
#define	AARCH64_ESR_EC_WATCH_EL1	0x35u
#define	AARCH64_ESR_EC_BKPT_32		0x38u
#define	AARCH64_ESR_EC_VCATCH_32	0x3au
#define	AARCH64_ESR_EC_BRK_64		0x3cu

/*
 * ESR Instruction Length
 */
#define	AARCH64_ESR_IL				(1u << 25)

/*
 * ESR Instruction Specific Syndrome
 */
#define	AARCH64_ESR_ISS(x)			((x) & 0xffffffu)

/*
 * ESR IABT/DABT ISS bits
 */
#define	AARCH64_ESR_IABT(x)			(((unsigned)(x) & (4u << AARCH64_ESR_EC_SHIFT)) == 0)
#define	AARCH64_ESR_ABT_ISV(x)		((unsigned)(x) & (1u << 24))
#define	AARCH64_ESR_ABT_SAS(x)		((unsigned)((x) >> 22) & 0x3)
#define	AARCH64_ESR_ABT_SSE(x)		((unsigned)(x) & (1u << 21))
#define	AARCH64_ESR_ABT_SRT(x)		((unsigned)((x) >> 16) & 0x1f)
#define	AARCH64_ESR_ABT_SF(x)		((unsigned)(x) & (1u << 15))
#define	AARCH64_ESR_ABT_AR(x)		((unsigned)(x) & (1u << 14))
#define	AARCH64_ESR_ABT_EA(x)		((unsigned)(x) & (1u << 9))
#define	AARCH64_ESR_ABT_CM(x)		((unsigned)(x) & (1u << 8))
#define	AARCH64_ESR_ABT_S1PTW(x)	((unsigned)(x) & (1u << 7))
#define	AARCH64_ESR_ABT_WnR(x)		((unsigned)(x) & (1u << 6))
#define	AARCH64_ESR_ABT_DFSC(x)		((unsigned)(x) & 0x3fu)

/*
 * ESR fault status codes
 */
#define	AARCH64_ESR_FSC_TRANS_L0	0x04u
#define	AARCH64_ESR_FSC_TRANS_L1	0x05u
#define	AARCH64_ESR_FSC_TRANS_L2	0x06u
#define	AARCH64_ESR_FSC_TRANS_L3	0x07u

#define	AARCH64_ESR_FSC_PERM_L1		0x0du
#define	AARCH64_ESR_FSC_PERM_L2		0x0eu
#define	AARCH64_ESR_FSC_PERM_L3		0x0fu

#define	AARCH64_ESR_FSC_ALIGN		0x21u

/*
 * ESR BKPT/BRK_64 ISS bits
 */
#define	AARCH64_ESR_BRK_COMMENT(x)	((x) & 0xffffu)

/*
 * Well-known brk comments
 */
#define AARCH64_ESR_BRK_COMMENT_CRASH	0xffffu
#define AARCH64_ESR_BRK_COMMENT_KDBREAK	0xfffeu

/*
 * CPACR bits
 */
#define	AARCH64_CPACR_TTA		(1u << 28)
#define	AARCH64_CPACR_ENABLE	(3u << 20)

/*
 * FPCR bits
 */
#define	AARCH64_FPCR_AHP		(1u << 26)
#define	AARCH64_FPCR_DN			(1u << 25)
#define	AARCH64_FPCR_FZ			(1u << 24)
#define	AARCH64_FPCR_RN			(0u << 22)
#define	AARCH64_FPCR_RP			(1u << 22)
#define	AARCH64_FPCR_RM			(2u << 22)
#define	AARCH64_FPCR_RZ			(3u << 22)
#define	AARCH64_FPCR_IDE		(1u << 15)
#define	AARCH64_FPCR_IXE		(1u << 12)
#define	AARCH64_FPCR_UFE		(1u << 11)
#define	AARCH64_FPCR_OFE		(1u << 10)
#define	AARCH64_FPCR_DZE		(1u << 9)
#define	AARCH64_FPCR_IOE		(1u << 8)

#define	AARCH64_FPCR_RMASK		(3u << 22)
#define	AARCH64_FPCR_RMODE(x)	((x) & AARCH64_FPCR_RMASK)

/*
 * FPSR bits
 */
#define	AARCH64_FPSR_N			(1u << 31)
#define	AARCH64_FPSR_Z			(1u << 30)
#define	AARCH64_FPSR_C			(1u << 29)
#define	AARCH64_FPSR_V			(1u << 28)
#define	AARCH64_FPSR_QC			(1u << 27)
#define	AARCH64_FPSR_IDC		(1u << 7)
#define	AARCH64_FPSR_IXC		(1u << 4)
#define	AARCH64_FPSR_UFC		(1u << 3)
#define	AARCH64_FPSR_OFC		(1u << 2)
#define	AARCH64_FPSR_DZC		(1u << 1)
#define	AARCH64_FPSR_IOC		(1u << 0)

#endif /* __AARCH64_CPU_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/aarch64/cpu.h $ $Rev: 780432 $") 
#endif

