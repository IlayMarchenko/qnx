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
 *  x86_64/context.h
 *

 */

#ifndef __X86_64_CONTEXT_H_INCLUDED
#define __X86_64_CONTEXT_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

typedef struct x86_64_cpu_registers {
/*-
    This layout (almost) mimics the kernel call argument order.
    Normally, rcx should be in the place of r10; however the syscall
    Instruction insists on stuffing %rip into %rcx (what were they thinking?),
    So the kernel call does a "mov %rcx, %r10" in the preamble.
*/
	_Uint64t	rdi,
				rsi,
				rdx,
				r10,
				r8,
				r9,
				rax,
				rbx,
				rbp,
				rcx,
				r11,
				r12,
				r13,
				r14,
				r15;
	_Uint64t	rip;
	_Uint32t	cs;
	_Uint32t	rsvd1;
	_Uint64t	rflags;
	_Uint64t	rsp;
	_Uint32t	ss;
	_Uint32t	rsvd2;
} X86_64_CPU_REGISTERS;

typedef struct fsave_area_64 {
	_Uint32t	fpu_control_word;
	_Uint32t	fpu_status_word;
	_Uint32t	fpu_tag_word;
	_Uint32t	fpu_ip;
	_Uint32t	fpu_cs;
	_Uint32t	fpu_op;
	_Uint32t	fpu_ds;
	_Uint8t		st_regs[80]; /* each register is 10 bytes! */
} X86_64_NDP_REGISTERS;

typedef struct fxsave_area_64 {
	_Uint16t	fpu_control_word;
	_Uint16t	fpu_status_word;
	_Uint16t	fpu_tag_word;
	_Uint16t	fpu_operand;
	_Uint64t	fpu_rip;
	_Uint64t	fpu_rdp;
	_Uint32t	mxcsr;
	_Uint32t	mxcsr_mask;
	_Uint8t		st_regs[128];
	_Uint8t		xmm_regs[128];
	_Uint8t		reserved2[224];
} X86_64_FXSAVE_REGISTERS;

typedef struct fpu_extention_savearea_64 {
	_Uint8t     other[512]; /* NDP+SSE */
	_Uint64t    xstate_bv;  /* bitvec of supported saves */
	_Uint64t    xstate_undef[64/8-1];
	_Uint8t     xstate_info[800-(512+64)];
} X86_64_XSAVE_REGISTERS;

/*-
  one note: 1024 wastes about 224 bytes extra; however it ensures these are
  page aligned; a mid-save or mid-restore fault may not be restartable, and
  I saw at least one INT#9 [ coprocessor overrun ] which the techref states
  never happens.  It is an abort.
*/

typedef union x86_64_fpu_registers {
	X86_64_NDP_REGISTERS	fsave_area;
	X86_64_FXSAVE_REGISTERS	fxsave_area;
	X86_64_XSAVE_REGISTERS	xsave_area;
	_Uint8t					data[1024];
} X86_64_FPU_REGISTERS;

typedef struct x86_64_alt_registers {
	/*
	 * There are no architecturally defined alt regs
	 */
	unsigned	__dummy;
} X86_64_ALT_REGISTERS;

#define X86_64_GET_REGIP(regs)			((regs)->rip)
#define X86_64_GET_REGSP(regs)			((regs)->rsp)
#define X86_64_SET_REGIP(regs,v)		(((regs)->rip) = (v))
#define X86_64_SET_REGSP(regs,v)		(((regs)->rsp) = (v))

/* Performance Counters */

/* Pentium 6 Class */
typedef struct x86_64_base_perfregs {
	_Uint32t	id; /* unique part id */
	_Uint32t	spare0;	/* make sure things are aligned */

	_Uint64t	perfevtsel0;
	_Uint64t	perfevtsel1;
	_Uint64t	perfevtsel2;
	_Uint64t	perfevtsel3;
	_Uint64t	perfctr0; /* 40 bit */
	_Uint64t	perfctr1; /* 40 bit */
	_Uint64t	perfctr2; /* 40 bit */
	_Uint64t	perfctr3; /* 40 bit */
} X86_64_BASE_PERFREGS;

#if 0
/* Xeon Class */
#define X86_64_P4XEON_BPU		4
#define X86_64_P4XEON_MS		4
#define X86_64_P4XEON_FLAME	4
#define X86_64_P4XEON_IQ		6

typedef struct x86_64_pentium4xeon_perfregs {
	_Uint32t	id; 	/* unique part id */
	_Uint32t	spare0; /* Align */

	_Uint64t	bsu_escr[2];
	_Uint64t	fsb_escr[2];
	_Uint64t	mob_escr[2];
	_Uint64t	pmh_escr[2];
	_Uint64t	bpu_escr[2];
	_Uint64t	is_escr[2];
	_Uint64t	itlb_escr[2];
	_Uint64t	ix_escr[2];
	_Uint64t	ms_escr[2];
	_Uint64t	tbpu_escr[2];
	_Uint64t	tc_escr[2];
	_Uint64t	firm_escr[2];
	_Uint64t	flame_escr[2];
	_Uint64t	dac_escr[2];
	_Uint64t	saat_escr[2];
	_Uint64t	u2l_escr[2];
	_Uint64t	cru_escr[6];
	_Uint64t	iq_escr[2];
	_Uint64t	rat_escr[2];
	_Uint64t	ssu_escr0;
	_Uint64t	alf_escr[2];


	_Uint64t	bpu_cccr[X86_64_P4XEON_BPU];
	_Uint64t	ms_cccr[X86_64_P4XEON_MS];
	_Uint64t	flame_cccr[X86_64_P4XEON_FLAME];
	_Uint64t	iq_cccr[X86_64_P4XEON_IQ];


	_Uint64t	bpu_counter[X86_64_P4XEON_BPU];
	_Uint64t	ms_counter[X86_64_P4XEON_MS];
	_Uint64t	flame_counter[X86_64_P4XEON_FLAME];
	_Uint64t	iq_counter[X86_64_P4XEON_IQ];


	/* Extra space for expansion. */
	_Uint64t	spare1[10];

} X86_64_PENTIUM4XEON_PERFREGS;
#endif

typedef union {
	_Uint32t	id;
	X86_64_BASE_PERFREGS base;
} X86_64_PERFREGS;

struct x86_64_segdesc {
	_Uint64t	base;
	_Uint32t	acc;
	_Uint32t	limit;
	_Uint16t	selector;
};

typedef struct {
	_Uint64t	gdt_base;
	_Uint64t	gdt_limit;
	_Uint64t	idt_base;
	_Uint64t	idt_limit;
	struct x86_64_segdesc	ldt;
	struct x86_64_segdesc	tr;
	struct x86_64_segdesc	cs;
	struct x86_64_segdesc	ds;
	struct x86_64_segdesc	es;
	struct x86_64_segdesc	fs;
	struct x86_64_segdesc	gs;
	struct x86_64_segdesc	ss;
} X86_64_SEGREGS;

typedef struct {
	_Uint64t		cr0;
	_Uint64t		cr2;
	_Uint64t		cr3;
	_Uint64t		cr4;
	_Uint64t		cr8;
} X86_64_CTRLREGS;

typedef struct {
	_Uint64t		dr[8];
} X86_64_DBGREGS;


#define __APIC_REG(name)	\
	_Uint32t	name; 		\
	_Uint8t		__space##name[0xc] /* <STAN_MACRO1,STAN_MACRO5/> */

typedef struct {
	__APIC_REG(reserved1);
	__APIC_REG(reserved2);
	__APIC_REG(id);
	__APIC_REG(version);
	__APIC_REG(reserved3);
	__APIC_REG(reserved4);
	__APIC_REG(reserved5);
	__APIC_REG(reserved6);
	__APIC_REG(task_priority);
	__APIC_REG(arbitration_priority);
	__APIC_REG(processor_priority);
	__APIC_REG(eoi);
	__APIC_REG(remote_read);
	__APIC_REG(logical_destination);
	__APIC_REG(destination_format);
	__APIC_REG(spurious_interrupt_vector);
	__APIC_REG(inservice0);
	__APIC_REG(inservice1);
	__APIC_REG(inservice2);
	__APIC_REG(inservice3);
	__APIC_REG(inservice4);
	__APIC_REG(inservice5);
	__APIC_REG(inservice6);
	__APIC_REG(inservice7);
	__APIC_REG(trigger_mode0);
	__APIC_REG(trigger_mode1);
	__APIC_REG(trigger_mode2);
	__APIC_REG(trigger_mode3);
	__APIC_REG(trigger_mode4);
	__APIC_REG(trigger_mode5);
	__APIC_REG(trigger_mode6);
	__APIC_REG(trigger_mode7);
	__APIC_REG(interrupt_request0);
	__APIC_REG(interrupt_request1);
	__APIC_REG(interrupt_request2);
	__APIC_REG(interrupt_request3);
	__APIC_REG(interrupt_request4);
	__APIC_REG(interrupt_request5);
	__APIC_REG(interrupt_request6);
	__APIC_REG(interrupt_request7);
	__APIC_REG(error_status);
	__APIC_REG(reserved7);
	__APIC_REG(reserved7a);
	__APIC_REG(reserved7b);
	__APIC_REG(reserved7c);
	__APIC_REG(reserved7d);
	__APIC_REG(reserved7e);
	__APIC_REG(lvt_cmci);
	__APIC_REG(icrl);
	__APIC_REG(icrh);
	__APIC_REG(lvt_timer);
	__APIC_REG(lvt_thermal_sensor);
	__APIC_REG(lvt_performance_monitoring_counters);
	__APIC_REG(lvt_lint0);
	__APIC_REG(lvt_lint1);
	__APIC_REG(lvt_error);
	__APIC_REG(initial_count);
	__APIC_REG(current_count);
	__APIC_REG(reserved8);
	__APIC_REG(reserved9);
	__APIC_REG(reserved10);
	__APIC_REG(reserved11);
	__APIC_REG(divide_configuration);
	__APIC_REG(reserved12);
} X86_64_LAPICREGS;

// TODO: move to its own header?
/// Data structure used for posted interrupts.
/// See table 29-1 in Intel's x86_64 manual and paragraph 9.12 in VT-d manual
struct posted_interrupt_descriptor {
	_Uint32t	pir[8];			///<	256 bits, one per vector
	_Uint32t	on;				///<	and extra VT-d fields
	_Uint32t	ndst;			///<	destination, for use by VT-d
	_Uint64t	reserved[3];	///<	empty all the way to 64 bytes
};

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/x86_64/context.h $ $Rev: 818402 $")
#endif
