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
 *  aarch64/context.h
 */

#ifndef __AARCH64_CONTEXT_H_INCLUDED
#define __AARCH64_CONTEXT_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

typedef struct aarch64_cpu_registers {
	_Uint64t	gpr[32];
	_Uint64t	elr;
	_Uint64t	pstate;
} AARCH64_CPU_REGISTERS __attribute__((__aligned__(16)));

/*
 * Register names
 */
#define	AARCH64_REG_X0		0
#define	AARCH64_REG_X1		1
#define	AARCH64_REG_X2		2
#define	AARCH64_REG_X3		3
#define	AARCH64_REG_X4		4
#define	AARCH64_REG_X5		5
#define	AARCH64_REG_X6		6
#define	AARCH64_REG_X7		7
#define	AARCH64_REG_X8		8
#define	AARCH64_REG_X9		9
#define	AARCH64_REG_X10		10
#define	AARCH64_REG_X11		11
#define	AARCH64_REG_X12		12
#define	AARCH64_REG_X13		13
#define	AARCH64_REG_X14		14
#define	AARCH64_REG_X15		15
#define	AARCH64_REG_X16		16
#define	AARCH64_REG_X17		17
#define	AARCH64_REG_X18		18
#define	AARCH64_REG_X19		19
#define	AARCH64_REG_X20		20
#define	AARCH64_REG_X21		21
#define	AARCH64_REG_X22		22
#define	AARCH64_REG_X23		23
#define	AARCH64_REG_X24		24
#define	AARCH64_REG_X25		25
#define	AARCH64_REG_X26		26
#define	AARCH64_REG_X27		27
#define	AARCH64_REG_X28		28
#define	AARCH64_REG_X29		29
#define	AARCH64_REG_X30		30
#define	AARCH64_REG_X31		31

/*
 * Register name aliases
 */
#define	AARCH64_REG_LR		30
#define	AARCH64_REG_SP		31

/*
 * Register manipulation
 */
#define AARCH64_GET_REGIP(regs)			((regs)->elr)
#define AARCH64_GET_REGSP(regs)			((regs)->gpr[AARCH64_REG_SP])
#define AARCH64_SET_REGIP(regs,v)		((regs)->elr = (v))
#define AARCH64_SET_REGSP(regs,v)		((regs)->gpr[AARCH64_REG_SP] = (v))

/*
 * Register mappings for AARCH32 state
 */
#define	AARCH32_REG_R0		0
#define	AARCH32_REG_R1		1
#define	AARCH32_REG_R2		2
#define	AARCH32_REG_R3		3
#define	AARCH32_REG_R4		4
#define	AARCH32_REG_R5		5
#define	AARCH32_REG_R6		6
#define	AARCH32_REG_R7		7
#define	AARCH32_REG_R8		8
#define	AARCH32_REG_R9		9
#define	AARCH32_REG_R10		10
#define	AARCH32_REG_R11		11
#define	AARCH32_REG_R12		12
#define	AARCH32_REG_R13		13
#define	AARCH32_REG_R14		14

#define	AARCH32_REG_SP		(AARCH32_REG_R13)
#define	AARCH32_REG_LR		(AARCH32_REG_R14)

#define AARCH32_GET_REGIP(regs)			((regs)->elr)
#define AARCH32_GET_REGSP(regs)			((regs)->gpr[AARCH32_REG_SP])
#define AARCH32_SET_REGIP(regs,v)		((regs)->elr = (v))
#define AARCH32_SET_REGSP(regs,v)		((regs)->gpr[AARCH32_REG_SP] = (v))

/*
 * FIXME_AARCH64: we really want a _Uint128t type for Q0-Q31
 */
typedef struct {
	_Uint64t	qlo;
	_Uint64t	qhi;
} aarch64_qreg_t;

typedef struct aarch64_fpu_registers {
	aarch64_qreg_t	reg[32];
	_Uint32t		fpsr;
	_Uint32t		fpcr;
} AARCH64_FPU_REGISTERS;

typedef struct aarch64_alt_registers {
	/*
	 * There are no architecturally defined alt registers
	 */
	_Uint64t	dummy;
} AARCH64_ALT_REGISTERS;

typedef union {
	/*
	 * FIXME_AARCH64
	 */
	_Uint64t	id;
} AARCH64_PERFREGS;


/*
 * Temporary hack - the #if/#define will go away once we've migrated this
 * file to the main branch and switched startup to use this definition.
 */
#if !defined(HAVE_ORIGINAL_EL2_REGS)
#define HAVE_ORIGINAL_EL2_REGS
struct aarch64_original_el2_regs {
	_Uint64t	vbar;
	_Uint64t	sctlr;
	_Uint64t	hcr;
	_Uint64t	vttbr;
	_Uint64t	vtcr;
	_Uint64t	tcr;
	_Uint64t	ttbr0;
	_Uint64t	tpidr;
	_Uint64t	sp;
};
#endif

#endif /* __AARCH64_CONTEXT_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/aarch64/context.h $ $Rev: 818402 $" )
#endif

