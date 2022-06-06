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
 *  ucontext.h    Machine context structures/functions
 *

 */
#ifndef _UCONTEXT_H_INCLUDED
#define _UCONTEXT_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__X86__) || defined(__WANT_X86_MCONTEXT)
	#ifndef __X86_CONTEXT_H_INCLUDED
		#include <x86/context.h>
	#endif
	struct __x86_mcontext {
		X86_CPU_REGISTERS	cpu;
		X86_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__MIPS__) || defined(__WANT_MIPS_MCONTEXT)
	#ifndef __MIPS_CONTEXT_H_INCLUDED
		#include <mips/context.h>
	#endif
	struct __mips_mcontext {
		MIPS_CPU_REGISTERS	cpu;
		MIPS_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__PPC__) || defined(__WANT_PPC_MCONTEXT)
	#ifndef __PPC_CONTEXT_H_INCLUDED
		#include <ppc/context.h>
	#endif
	struct __ppc_mcontext {
		PPC_CPU_REGISTERS	cpu;
		PPC_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__SH__) || defined(__WANT_SH_CONTEXT)
	#ifndef __SH_CONTEXT_H_INCLUDED
		#include <sh/context.h>
	#endif
	struct __sh_mcontext {
		SH_CPU_REGISTERS	cpu;
		SH_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__ARM__) || defined(__WANT_ARM_MCONTEXT)
	#ifndef __ARM_CONTEXT_H_INCLUDED
		#include <arm/context.h>
	#endif
	struct __arm_mcontext {
		ARM_CPU_REGISTERS	cpu;
		ARM_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__X86_64__) || defined(__WANT_X86_64_MCONTEXT)
	#ifndef __X86_64_CONTEXT_H_INCLUDED
		#include <x86_64/context.h>
	#endif
	struct __x86_64_mcontext {
		X86_64_CPU_REGISTERS	cpu;
		X86_64_FPU_REGISTERS	fpu;
	};
#endif

#if defined(__aarch64__) || defined(__WANT_AARCH64_MCONTEXT)
	#ifndef __aarch64_CONTEXT_H_INCLUDED
		#include <aarch64/context.h>
	#endif
	struct __aarch64_mcontext {
		AARCH64_CPU_REGISTERS	cpu;
		AARCH64_FPU_REGISTERS	fpu;
	};
#endif

/*<STAN_MACRO1>*/
#if defined(__X86__)
	typedef struct __x86_mcontext	mcontext_t;
	#define SET_REGIP	X86_SET_REGIP
	#define SET_REGSP	X86_SET_REGSP
	#define GET_REGIP	X86_GET_REGIP
	#define GET_REGSP	X86_GET_REGSP
#elif defined(__PPC__)
	typedef struct __ppc_mcontext	mcontext_t;
	#define SET_REGIP	PPC_SET_REGIP
	#define SET_REGSP	PPC_SET_REGSP
	#define GET_REGIP	PPC_GET_REGIP
	#define GET_REGSP	PPC_GET_REGSP
#elif defined(__MIPS__)
	typedef struct __mips_mcontext	mcontext_t;
	#define SET_REGIP	MIPS_SET_REGIP
	#define SET_REGSP	MIPS_SET_REGSP
	#define GET_REGIP	MIPS_GET_REGIP
	#define GET_REGSP	MIPS_GET_REGSP
#elif defined(__SH__)
	typedef struct __sh_mcontext	mcontext_t;
	#ifndef __SH_CONTEXT_H_INCLUDED
		#include <sh/context.h>
	#endif
	#define SET_REGIP	SH_SET_REGIP
	#define SET_REGSP	SH_SET_REGSP
	#define GET_REGIP	SH_GET_REGIP
	#define GET_REGSP	SH_GET_REGSP
#elif defined(__ARM__)
	typedef struct __arm_mcontext	mcontext_t;
	#define SET_REGIP	ARM_SET_REGIP
	#define SET_REGSP	ARM_SET_REGSP
	#define GET_REGIP	ARM_GET_REGIP
	#define GET_REGSP	ARM_GET_REGSP
#elif defined(__X86_64__)
	typedef struct __x86_64_mcontext	mcontext_t;
	#define SET_REGIP	X86_64_SET_REGIP
	#define SET_REGSP	X86_64_SET_REGSP
	#define GET_REGIP	X86_64_GET_REGIP
	#define GET_REGSP	X86_64_GET_REGSP
#elif defined(__aarch64__)
	typedef struct __aarch64_mcontext	mcontext_t;
	#define SET_REGIP	AARCH64_SET_REGIP
	#define SET_REGSP	AARCH64_SET_REGSP
	#define GET_REGIP	AARCH64_GET_REGIP
	#define GET_REGSP	AARCH64_GET_REGSP
#else
	#error Context structure not defined
#endif
/*</STAN_MACRO1>*/

#ifndef __SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#if defined(__SIGSET_T)
typedef __SIGSET_T	sigset_t;
#undef __SIGSET_T
#endif

#if defined(__STACK_T)
typedef __STACK_T	stack_t;
#undef __STACK_T
#endif

#if defined(__UCONTEXT_T)
typedef __UCONTEXT_T	ucontext_t;
#undef __UCONTEXT_T
#endif

#include <_pack64.h>

struct __ucontext_t {
  	struct __ucontext_t 	*uc_link;
  	sigset_t    			uc_sigmask;
	stack_t	    			uc_stack;
	mcontext_t  			uc_mcontext;
};

struct __ucontext32 {
  	_Uintptr32t 			uc_link;
  	sigset_t    			uc_sigmask;
	__32_64_STACK_T(_Uintptr32t, _Size32t)
							uc_stack;
	mcontext_t  			uc_mcontext;
};

__BEGIN_DECLS

#include <_packpop.h>


__END_DECLS
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/ucontext.h $ $Rev: 780356 $")
#endif
