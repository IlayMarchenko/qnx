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

#ifndef __DEBUG_H_INCLUDED
#define __DEBUG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if	!defined(_DEBUG_TARGET_ALL) \
 && !defined(_DEBUG_TARGET_X86) \
 && !defined(_DEBUG_TARGET_PPC) \
 && !defined(_DEBUG_TARGET_MIPS) \
 && !defined(_DEBUG_TARGET_ARM) \
 && !defined(_DEBUG_TARGET_X86_64) \
 && !defined(_DEBUG_TARGET_AARCH64)
	#if defined(__X86__)
		#define _DEBUG_TARGET_X86
	#elif defined(__PPC__)
		#define _DEBUG_TARGET_PPC
	#elif defined(__MIPS__)
		#define _DEBUG_TARGET_MIPS
	#elif defined(__SH__)
		#define _DEBUG_TARGET_SH
	#elif defined(__ARM__)
		#define _DEBUG_TARGET_ARM
	#elif defined(__X86_64__)
		#define _DEBUG_TARGET_X86_64
	#elif defined(__aarch64__)
		#define _DEBUG_TARGET_AARCH64
	#else
		#error not configured for system
	#endif
#endif

#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86)
#ifndef __X86_CONTEXT_H_INCLUDED
#include _NTO_HDR_(x86/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_PPC)
#ifndef __PPC_CONTEXT_H_INCLUDED
#include _NTO_HDR_(ppc/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_MIPS)
#ifndef __MIPS_CONTEXT_H_INCLUDED
#include _NTO_HDR_(mips/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_SH)
#ifndef __SH_CONTEXT_H_INCLUDED
#include _NTO_HDR_(sh/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_ARM)
#ifndef __ARM_CONTEXT_H_INCLUDED
#include _NTO_HDR_(arm/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86_64)
#ifndef __X86_64_CONTEXT_H_INCLUDED
#include _NTO_HDR_(x86_64/context.h)
#endif
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_AARCH64)
#ifndef __AARCH64_CONTEXT_H_INCLUDED
#include _NTO_HDR_(aarch64/context.h)
#endif
#endif

#ifndef __FAULT_H_INCLUDED
#include _NTO_HDR_(sys/fault.h)
#endif

#ifndef _SIGNAL_H_INCLUDED
#include _NTO_HDR_(signal.h)
#endif

#if defined(__PID_T)
typedef __PID_T		pid_t;
#undef __PID_T
#endif

#if defined(__PTHREAD_T)
typedef __PTHREAD_T	pthread_t;
#undef __PTHREAD_T
#endif

#if defined(__SIGSET_T)
typedef __SIGSET_T	sigset_t;
#undef __SIGSET_T
#endif

#if defined(__UID_T)
typedef __UID_T		uid_t;
#undef __UID_T
#endif

#if defined(__GID_T)
typedef __GID_T		gid_t;
#undef __GID_T
#endif

#if defined(__ITIMER)
struct _itimer __ITIMER;
#undef __ITIMER
#endif

#if defined(__TIMER_T)
typedef __TIMER_T timer_t;
#undef __TIMER_T
#endif

#if defined(__CLOCKID_T)
typedef __CLOCKID_T clockid_t;
#undef __CLOCKID_T
#endif

#if defined(__TIMER_INFO)
struct _timer_info __TIMER_INFO;
#undef __TIMER_INFO
#endif

#ifdef __TIMER_INFO32
struct _timer_info32 __TIMER_INFO32;
#undef __TIMER_INFO32
#endif

#ifdef __TIMER_INFO64
struct _timer_info64 __TIMER_INFO64;
#undef __TIMER_INFO64
#endif

__BEGIN_DECLS

#include _NTO_HDR_(_pack64.h)

#define _DEBUG_FLAG_STOPPED			0x00000001u	/* Thread is not running */
#define _DEBUG_FLAG_ISTOP			0x00000002u	/* Stopped at point of interest */
#define _DEBUG_FLAG_IPINVAL			0x00000010u	/* IP is not valid */
#define _DEBUG_FLAG_ISSYS			0x00000020u	/* System process */
#define _DEBUG_FLAG_SSTEP			0x00000040u	/* Stopped because of single step */
#define _DEBUG_FLAG_CURTID			0x00000080u	/* Thread is current thread */
#define _DEBUG_FLAG_TRACE_EXEC		0x00000100u	/* Stopped because of breakpoint */
#define _DEBUG_FLAG_TRACE_RD		0x00000200u	/* Stopped because of read access */
#define _DEBUG_FLAG_TRACE_WR		0x00000400u	/* Stopped because of write access */
#define _DEBUG_FLAG_TRACE_MODIFY	0x00000800u	/* Stopped because of modified memory */
#define _DEBUG_FLAG_RLC				0x00010000u	/* Run-on-Last-Close flag is set */
#define _DEBUG_FLAG_KLC				0x00020000u	/* Kill-on-Last-Close flag is set */
#define _DEBUG_FLAG_FORK			0x00040000u	/* Child inherits flags (Stop on fork/spawn) */
#define _DEBUG_FLAG_EXEC			0x00080000u	/* Stop on exec. */
#define _DEBUG_FLAG_MASK			0x000f0000u	/* Flags that can be changed */
#define _DEBUG_FLAG_THREAD_EV		0x00100000u	/* Stop on thread create/destroy */
#define _DEBUG_FLAG_64BIT			0x00200000u	/* Thread is 64 bit */

enum {
	_DEBUG_WHY_REQUESTED,
	_DEBUG_WHY_SIGNALLED,
	_DEBUG_WHY_FAULTED,
	_DEBUG_WHY_JOBCONTROL,
	_DEBUG_WHY_TERMINATED,
	_DEBUG_WHY_CHILD,
	_DEBUG_WHY_EXEC,
	_DEBUG_WHY_THREAD,
	/* _DEBUG_WHY_ events may have numeric value up to _DEBUG_WHY_MAX-1 */
	_DEBUG_WHY_MAX=0xFF
};

/* WHAT constants are specific to WHY reason they are associated with.
   Actual numeric value may be reused between different WHY reasons.  */
#define _DEBUG_WHAT_DESTROYED		0x00000000U	/* WHY_THREAD */
#define _DEBUG_WHAT_CREATED			0x00000001U	/* WHY_THREAD */
#define _DEBUG_WHAT_FORK			0x00000000U	/* WHY_CHILD */
#define _DEBUG_WHAT_VFORK			0x00000001U	/* WHY_CHILD */
#define _DEBUG_WHAT_SPAWN			0x00000002U /* WHY_CHILD */

#define _DEBUG_RUN_CLRSIG			0x00000001u	/* Clear pending signal */
#define _DEBUG_RUN_CLRFLT			0x00000002u	/* Clear pending fault */
#define _DEBUG_RUN_TRACE			0x00000004u	/* Trace mask flags interesting signals */
#define _DEBUG_RUN_HOLD				0x00000008u	/* Hold mask flags interesting signals */
#define _DEBUG_RUN_FAULT			0x00000010u	/* Fault mask flags interesting faults */
#define _DEBUG_RUN_VADDR			0x00000020u	/* Change ip before running */
#define _DEBUG_RUN_STEP				0x00000040u	/* Single step only one thread */
#define _DEBUG_RUN_STEP_ALL			0x00000080u	/* Single step one thread, other threads run */
#define _DEBUG_RUN_CURTID			0x00000100u	/* Change current thread (target thread) */
#define _DEBUG_RUN_ARM				0x00000200u	/* Deliver event at point of interest */
#define _DEBUG_RUN_THREAD			0x00000400u	/* Debugger is interested in thread created/destroyed events */
#define _DEBUG_RUN_CHILD			0x00000800u	/* Deliver event when process does spawn, fork vfork. */
#define _DEBUG_RUN_EXEC				0x00001000u	/* Deliver event when process does exec. */


typedef struct _debug_process_info {
	pid_t						pid;
	pid_t						parent;
	_Uint32t					flags;
	_Uint32t					umask;
	pid_t						child;
	pid_t						sibling;
	pid_t						pgrp;
	pid_t						sid;
	_Uint64t					base_address;
	_Uint64t					initial_stack;
	uid_t						uid;
	gid_t						gid;
	uid_t						euid;
	gid_t						egid;
	uid_t						suid;
	gid_t						sgid;
	sigset_t					sig_ignore;
	sigset_t					sig_queue;
	sigset_t					sig_pending;
	_Uint32t					num_chancons;
	_Uint32t					num_fdcons;
	_Uint32t					num_threads;
	_Uint32t					num_timers;
	_Uint64t					start_time;		/* Start time in nsec */
	_Uint64t					utime;			/* User running time in nsec */
	_Uint64t					stime;			/* System running time in nsec */
	_Uint64t					cutime;			/* terminated children user time in nsec */
	_Uint64t					cstime;			/* terminated children user time in nsec */
	_Uint8t						priority;		/* process base priority */
	_Uint8t						reserved2[7];
	_Uint8t						extsched[8];
	_Uint64t					pls;			/* Address of process local storage */
	_Uint64t					sigstub;		/* Address of process signal trampoline */
	_Uint64t					canstub;		/* Address of process thread cancellation trampoline */
	_Uint64t					private_mem;	/* Amount of MAP_PRIVATE memory */
	_Uint32t					appid;			/* Application id */
	_Uint32t					type_id;		/* Security type id */
	_Uint64t					reserved[8];
}							debug_process_t;

typedef struct _debug_thread_info32 {
	pid_t						pid;
	pthread_t					tid;
	_Uint32t					flags;
	_Uint16t					why;
	_Uint16t					what;
	_Uint64t					ip;
	_Uint64t					sp;
	_Uint64t					stkbase;
	_Uint64t					tls;
	_Uint32t					stksize;
	_Uint32t					tid_flags;
	_Uint8t						priority;
	_Uint8t						real_priority;
	_Uint8t						policy;
	_Uint8t						state;
	_Int16t						syscall;
	_Uint16t					last_cpu;
	_Uint32t					timeout;
	_Int32t						last_chid;
	sigset_t					sig_blocked;
	sigset_t					sig_pending;
	__siginfo32_t				info;
	union {
		struct {
			pthread_t					tid;
		}							join;
		struct {
			_Int32t						id;
			_Uintptr32t					sync;
		}							sync;
		struct {
			_Uint32t					nd;
			pid_t						pid;
			_Int32t						coid;
			_Int32t						chid;
			_Int32t						scoid;
		}							connect;
		struct {
			_Int32t						chid;
		}							channel;
		struct {
			pid_t						pid;
			_Uintptr32t					vaddr;
			_Uint32t					flags;
		}							waitpage;
		struct {
			_Uint32t					size;
		}							stack;
		struct {
			pthread_t					tid;
		}							thread_event;
		struct {
			pid_t						child;
		}							fork_event;
		_Uint64t						filler[4];
	}							blocked;
	_Uint64t					start_time;		/* thread start time in nsec */
	_Uint64t					sutime;			/* thread system + user running time in nsec */
	_Uint8t						extsched[8];
	_Uint64t					nsec_since_block;	/*how long thread has been blocked. 0 for STATE_READY or STATE_RUNNING. 
										  in nsec, but ms resolution. */
	_Uint64t					reserved2[4];
}							debug_thread32_t;

typedef struct _debug_thread_info64 {
	pid_t						pid;
	pthread_t					tid;
	_Uint32t					flags;
	_Uint16t					why;
	_Uint16t					what;
	_Uint64t					ip;
	_Uint64t					sp;
	_Uint64t					stkbase;
	_Uint64t					tls;
	_Uint32t					stksize;
	_Uint32t					tid_flags;
	_Uint8t						priority;
	_Uint8t						real_priority;
	_Uint8t						policy;
	_Uint8t						state;
	_Int16t						syscall;
	_Uint16t					last_cpu;
	_Uint32t					timeout;
	_Int32t						last_chid;
	sigset_t					sig_blocked;
	sigset_t					sig_pending;
	__siginfo32_t				__info32;
	union {
		struct {
			pthread_t					tid;
		}							join;
		struct {
			_Intptr64t					id;
			_Uintptr64t					sync;
		}							sync;
		struct {
			_Uint32t					nd;
			pid_t						pid;
			_Int32t						coid;
			_Int32t						chid;
			_Int32t						scoid;
		}							connect;
		struct {
			_Int32t						chid;
		}							channel;
		struct {
			pid_t						pid;
			_Uint32t					flags;
			_Uintptr64t					vaddr;
		}							waitpage;
		struct {
			_Size64t					size;
		}							stack;
		struct {
			pthread_t					tid;
		}							thread_event;
		struct {
			pid_t						child;
		}							fork_event;
		_Uint64t						filler[4];
	}							blocked;
	_Uint64t					start_time;		/* thread start time in nsec */
	_Uint64t					sutime;			/* thread system + user running time in nsec */
	_Uint8t						extsched[8];
	_Uint64t					nsec_since_block;	/*how long thread has been blocked. 0 for STATE_READY or STATE_RUNNING. 
										  in nsec, but ms resolution. */
	union {
		__siginfo32_t			info32;
		__siginfo64_t			info64;
		siginfo_t				info;
	};

	_Uint64t					reserved2[4];
}							debug_thread64_t;

typedef struct _debug_run32 {
	_Uint32t					flags;
	pthread_t					tid;
	sigset_t					trace;
	sigset_t					hold;
	fltset_t					fault;
	_Uintptr32t					ip;
}							debug_run32_t;

typedef struct _debug_run64 {
	_Uint32t					flags;
	pthread_t					tid;
	sigset_t					trace;
	sigset_t					hold;
	fltset_t					fault;
	_Uintptr32t					__ip32;
	_Uintptr64t					ip;
}							debug_run64_t;

typedef struct _debug_break32 {
	_Uint16t					type;
	_Int16t						size;	/* 1 to 8 for modify, otherwise zero, -1 to remove */
	_Uintptr32t					addr;
}							debug_break32_t;

typedef struct _debug_break64 {
	_Uint16t					type;
	_Int16t						size;	/* 1 to 8 for modify, otherwise zero, -1 to remove */
	_Uintptr32t					__addr32;
	_Uintptr64t					addr;
}							debug_break64_t;

#define	_DEBUG_BREAK_EXEC 		0x0001u	/* execution breakpoint */
#define _DEBUG_BREAK_RD 		0x0002u	/* read access (fail if not supported) */
#define _DEBUG_BREAK_WR 		0x0004u	/* write access (fail if not supported) */
#define _DEBUG_BREAK_RW 		0x0006u	/* read or write access (fail if not supported) */
#define _DEBUG_BREAK_MODIFY 	0x0008u	/* memory modified */
#define _DEBUG_BREAK_RDM 		0x000au	/* read access if suported otherwise modified */
#define _DEBUG_BREAK_WRM 		0x000cu	/* write access if suported otherwise modified */
#define _DEBUG_BREAK_RWM 		0x000eu	/* read or write access if suported otherwise modified */
#define _DEBUG_BREAK_MASK 		0x000fu	/* mask for matching for replacing/removing breakpoints */
#define _DEBUG_BREAK_HW 		0x0010u	/* only use hardware debugging (i.e. no singlestep */
/* then checking, or writing an invalid instruction to code) */
#define _DEBUG_BREAK_SOFT		0x8000u	/* breakpoint inserted/removed during context switch */

typedef struct _debug_irq32 {
	pid_t					pid;
	pthread_t				tid;
	_Uintptr32t				handler; /* const struct sigevent 	*(*handler)(void *area, int id); */
	_Uintptr32t				area;
	unsigned				flags;
	unsigned		 		latency;
	unsigned				mask_count;
	int						id;
	unsigned				vector;
	struct __sigevent32		event;
}							debug_irq32_t;

typedef struct _debug_irq64 {
	pid_t					pid;
	pthread_t				tid;
	_Uintptr32t				__handler32;
	_Uintptr32t				__area32;
	unsigned				flags;
	unsigned		 		latency;
	unsigned				mask_count;
	int						id;
	unsigned				vector;
	struct __sigevent32		__event32;
	_Uintptr64t				handler; /* const struct sigevent 	*(*handler)(void *area, int id); */
	_Uintptr64t				area;
	union {
		struct __sigevent32		event32;
		struct __sigevent64		event64;
		struct sigevent			event;
	};
}							debug_irq64_t;

typedef struct _debug_timer32 {
	timer_t					id;
	unsigned				spare;
	struct _timer_info32	info;
}							debug_timer32_t;

typedef struct _debug_timer64 {
	timer_t					id;
	unsigned				spare;
	struct _timer_info32	__info32;
	struct _timer_info64	info;
}							debug_timer64_t;

typedef struct _debug_channel {
	unsigned		chid;
	unsigned char	type;
	unsigned char	zero;
	unsigned short	flags;
	unsigned 		send_queue_depth;
	unsigned 		pulse_queue_depth;
	unsigned 		receive_queue_depth;
	unsigned 		reply_queue_depth;
	unsigned		type_id;
	unsigned		pad[5]; /* left for future expansion */
}							debug_channel_t;

typedef union _debug_gregs {
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86)
	X86_CPU_REGISTERS			x86;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_MIPS)
	MIPS_CPU_REGISTERS			mips;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_PPC)
	PPC_CPU_REGISTERS			ppc;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_ARM)
	ARM_CPU_REGISTERS			arm;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_SH)
	SH_CPU_REGISTERS			sh;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86_64)
	X86_64_CPU_REGISTERS		x86_64;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_AARCH64)
	AARCH64_CPU_REGISTERS		aarch64;
#endif
	_Uint64t						padding[1024];
}							debug_greg_t;

typedef union _debug_fpregs {
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86)
	X86_FPU_REGISTERS			x86;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_MIPS)
	MIPS_FPU_REGISTERS			mips;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_PPC)
	PPC_FPU_REGISTERS			ppc;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_ARM)
	ARM_FPU_REGISTERS			arm;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_SH)
	SH_FPU_REGISTERS			sh;	
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86_64)
	X86_64_FPU_REGISTERS		x86_64;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_AARCH64)
	AARCH64_FPU_REGISTERS		aarch64;
#endif
	_Uint64t						padding[1024];
}							debug_fpreg_t;

typedef union _debug_altregs {
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86)
/*	X86_ALT_REGISTERS			x86;	*/
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_MIPS)
	MIPS_ALT_REGISTERS			mips;	
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_PPC)
	PPC_ALT_REGISTERS			ppc;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_ARM)
	ARM_ALT_REGISTERS			arm;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_SH)
/*	SH_ALT_REGISTERS			sh;	*/
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86_64)
/*	X86_64_ALT_REGISTERS		x86_64;	*/
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_AARCH64)
/*	AARCH64_ALT_REGISTERS		aarch64;	*/
#endif
	_Uint64t						padding[1024];
}							debug_altreg_t;

typedef union _debug_perfregs {
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86)
	X86_PERFREGS				x86;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_MIPS)
	MIPS_PERFREGS				mips;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_PPC)
	PPC_PERFREGS				ppc;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_ARM)
	ARM_PERFREGS				arm;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_SH)
	SH_PERFREGS					sh;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_X86_64)
	X86_64_PERFREGS				x86_64;
#endif
#if defined(_DEBUG_TARGET_ALL) || defined(_DEBUG_TARGET_AARCH64)
	AARCH64_PERFREGS				aarch64;
#endif
	_Uint64t						padding[1024];
}							debug_perfreg_t;

#include _NTO_HDR_(_packpop.h)

#if (__PTR_BITS__ > 32) || !defined(WANT_OLD_DEVCTLS)
typedef debug_thread64_t	debug_thread_t;
typedef debug_break64_t		debug_break_t;
typedef debug_run64_t		debug_run_t;
typedef debug_irq64_t		debug_irq_t;
typedef debug_timer64_t		debug_timer_t;
#else
typedef debug_thread32_t	debug_thread_t;
typedef debug_break32_t		debug_break_t;
typedef debug_run32_t		debug_run_t;
typedef debug_irq32_t		debug_irq_t;
typedef debug_timer32_t		debug_timer_t;
#endif

__END_DECLS

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/debug.h $ $Rev: 810889 $")
#endif
