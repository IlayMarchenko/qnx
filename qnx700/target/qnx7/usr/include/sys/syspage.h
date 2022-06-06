/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __SYSPAGE_H_INCLUDED
#define __SYSPAGE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif


/* <STAN_MACRO1, STAN_MACRO5> */
#if __PTR_BITS__ == 32
	#define _SCPP32(__type, __field, ...)					\
		union {												\
			_Uintptr32t			__field##32;				\
			__type		(*__field) __VA_ARGS__;				\
		}
	#define _SCPP64(__type, __field, ...)					\
		_Uintptr64t		__field##64
	#define _SCPPONLY32(__type, __field, ...)				\
		__type		(*__field) __VA_ARGS__
	#define _SCPPONLY64(__type, __field, ...)				\
		_Uintptr64t		__field
#else
	#define _SCPP32(__type, __field, ...)					\
		_Uintptr32t		__field##32
	#define _SCPP64(__type, __field, ...)					\
		union {												\
			_Uintptr64t			__field##64;				\
			__type		(*__field) __VA_ARGS__;		\
		}
	#define _SCPPONLY32(__type, __field, ...)				\
		_Uintptr32t		__field
	#define _SCPPONLY64(__type, __field, ...)				\
		__type		(*__field) __VA_ARGS__
	#define SYSPAGE_SIZED_ARRAYS
#endif
#define _SCPPTR(__type, __field, ...)					\
	union {												\
		_Uintptr32t			__field##32;				\
		_Uintptr64t			__field##64;				\
		__type		(*__field) __VA_ARGS__;				\
	}
/* </STAN_MACRO1, STAN_MACRO5> */


/* Leave deprecated sections enabled for 32-bit, for right now */
#if !defined(ENABLE_DEPRECATED_SYSPAGE_SECTIONS)
# if __PTR_BITS__+0 == 32
#  define ENABLE_DEPRECATED_SYSPAGE_SECTIONS 1
# else
#  define ENABLE_DEPRECATED_SYSPAGE_SECTIONS 0
# endif
#endif

#if ENABLE_DEPRECATED_SYSPAGE_SECTIONS == 0
# undef ENABLE_DEPRECATED_SYSPAGE_SECTIONS
#endif

#if defined(ENABLE_DEPRECATED_SYSPAGE_SECTIONS)
# define DEPRECATED_SECTION_NAME(name)	name
#else
# define DEPRECATED_SECTION_NAME(name)	__mangle_name_to_cause_compilation_errs_##name
#endif

__BEGIN_DECLS

#if defined(__CLOCKADJUST)
struct _clockadjust __CLOCKADJUST;
#undef __CLOCKADJUST
#endif

struct _thread_local_storage;
struct _process_local_storage;
struct syspage_entry;
struct tracebuf;

#if defined(__SLIB_DATA_INDIRECT) && !defined(_syspage_ptr) && !defined(__SLIB)
struct syspage_entry *__get_syspage_ptr(void);
#define _syspage_ptr (__get_syspage_ptr())
#else
extern struct syspage_entry				*_syspage_ptr;
#endif

typedef struct {
	_Uint16t		entry_off;
	_Uint16t		entry_size;
} syspage_entry_info;

typedef struct {
	_Uint16t		entry_off;
	_Uint16t		entry_size;
	_Uint16t		element_size;
} syspage_array_info;

/*
 * Include CPU specific definition for network queries.
 */
#if	!defined(SYSPAGE_TARGET_ALL)				\
	&& !defined(SYSPAGE_TARGET_X86)				\
	&& !defined(SYSPAGE_TARGET_ARM)				\
	&& !defined(SYSPAGE_TARGET_X86_64)			\
	&& !defined(SYSPAGE_TARGET_AARCH64)
#if defined(__X86__)
#define SYSPAGE_TARGET_X86
#elif defined(__ARM__)
#define SYSPAGE_TARGET_ARM
#elif defined(__X86_64__)
#define SYSPAGE_TARGET_X86_64
#elif defined(__aarch64__)
#define SYSPAGE_TARGET_AARCH64
#else
#error not configured for system
#endif
#endif

#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86)
#include _NTO_HDR_(x86/syspage.h)
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_ARM)
#include _NTO_HDR_(arm/syspage.h)
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86_64)
#include _NTO_HDR_(x86_64/syspage.h)
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_AARCH64)
#include _NTO_HDR_(aarch64/syspage.h)
#endif

struct cpupage_entry {
	_SCPP32(struct _thread_local_storage, tls,);
	_SCPP32(struct _process_local_storage, pls,);
	_SCPP32(struct syspage_entry, syspage,);
	_Uint32t								cpu;
	_Uint32t								state;
	union {
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_AARCH64)
		struct aarch64_cpupage_entry		aarch64;
#endif
		struct {
			_Uint32t	dummy[8];
		}									dummy;
	} un;
	_SCPP64(struct _thread_local_storage, tls,);
	_SCPP64(struct _process_local_storage, pls,);
	_SCPP64(struct syspage_entry, syspage,);

	_Uint32t								spare[8];
};

enum {
	CPUPAGE_ADDR = -1,	/* R */
	CPUPAGE_TLS = 0,	/* R */
	CPUPAGE_PLS,		/* RW */
	CPUPAGE_SYSPAGE,	/* R */
	CPUPAGE_CPU,		/* R */
	CPUPAGE_STATE,		/* R */
	CPUPAGE_MAX
};

/*
 *  Architecture independent system page definitions
 */

/*
 *	System page types
 */
enum {
	SYSPAGE_X86,
	SYSPAGE_PPC,
	SYSPAGE_MIPS,
	SYSPAGE_SPARE,
	SYSPAGE_ARM,
	SYSPAGE_SH,
	/* additional 32 bit architectures go here */

	SYSPAGE_64BIT = 0x100,
	SYSPAGE_X86_64 = SYSPAGE_64BIT,
	SYSPAGE_AARCH64,
	/* additional 64 bit architectures go here */
};

#define QTIME_FLAG_TIMER_ON_CPU0		0x00000001u
#define QTIME_FLAG_CHECK_STABLE			0x00000002u
#define QTIME_FLAG_TICKLESS				0x00000004u
#define QTIME_FLAG_GLOBAL_CLOCKCYCLES	0x00000008u /* ClockCycles() is synchronized between all processors */


struct qtime_entry {
	_Uint64t					cycles_per_sec;	/* for ClockCycles */
	_Uint64t volatile			nsec_tod_adjust;
	_Uint64t volatile			nsec;
	_Uint32t					nsec_inc;
	_Uint32t					boot_time; /* UTC seconds when machine booted */

	struct _clockadjust			adjust;
	_Uint32t					timer_rate;	/* times 10^timer_scale */
	_Int32t						timer_scale;
	_Uint32t					timer_load;
	_Int32t						intr;
	_Uint32t					epoch;
	_Uint32t					flags;
	_Uint32t					rr_interval_mul;
	_Uint32t					spare0;
	_Uint64t volatile			nsec_stable;
	_Uint32t					spare[4];
};

struct intrspin;

struct debug_callout32 {
	_SCPP32(void, display_char, (struct syspage_entry *, char));
	_SCPP32(int, poll_key, (struct syspage_entry *));
	_SCPP32(int, break_detect, (struct syspage_entry *));
	_SCPP32(void, spare,);
};

struct debug_callout64 {
	_SCPP64(void, display_char, (struct syspage_entry *, char));
	_SCPP64(int, poll_key, (struct syspage_entry *));
	_SCPP64(int, break_detect, (struct syspage_entry *));
	_SCPP64(void, spare,);
};

#if __PTR_BITS__==32
	/* <STAN_MACRO1/> */
	#define debug_callout	debug_callout32
#else
	/* <STAN_MACRO1/> */
	#define debug_callout	debug_callout64
#endif

typedef enum {
	DEBUG_WATCHDOG_STOP = 0,
	DEBUG_WATCHDOG_CONTINUE,
	DEBUG_WATCHDOG_FEED
} debug_watchdog_cmd;

struct callout_entry {
	_SCPP32(void, reboot, (struct syspage_entry *, int));
	_SCPP32(int, power, (struct syspage_entry *, unsigned, _Uint64t *));
	_SCPP32(void, timer_load, (struct syspage_entry *, struct qtime_entry *));
	_SCPP32(int, timer_reload, (struct syspage_entry *, struct qtime_entry *));
	_SCPP32(unsigned, timer_value, (struct syspage_entry *, struct qtime_entry *));
	union {
		struct debug_callout32	debug32[2];
#if __PTR_BITS__==32
		struct debug_callout32	debug[2];
#endif
	};
	_SCPP32(void, debug_watchdog, (struct syspage_entry *, debug_watchdog_cmd));

	_SCPP64(void, reboot, (struct syspage_entry *, int));
	_SCPP64(int, power, (struct syspage_entry *, unsigned, _Uint64t *));
	_SCPP64(void, timer_load, (struct syspage_entry *, struct qtime_entry *));
	_SCPP64(int, timer_reload, (struct syspage_entry *, struct qtime_entry *));
	_SCPP64(unsigned, timer_value, (struct syspage_entry *, struct qtime_entry *));
	union {
		struct debug_callout64	debug64[2];
#if __PTR_BITS__==64
		struct debug_callout64	debug[2];
#endif
	};
	_SCPP64(void, debug_watchdog, (struct syspage_entry *, debug_watchdog_cmd));

	_Uint64t	spare[3];
};

struct callin_entry {
	_SCPP32(void, spare0,);
	_SCPP32(int, interrupt_mask, (unsigned, int));
	_SCPP32(int, interrupt_unmask, (unsigned, int));
	_SCPP32(int, trace_event, (_Intptrt *));
	_SCPP32(void, quiesce_cpus, (int));

	_SCPP64(void, spare0,);
	_SCPP64(int, interrupt_mask, (unsigned, int));
	_SCPP64(int, interrupt_unmask, (unsigned, int));
	_SCPP64(int, trace_event, (int *));
	_SCPP64(void, quiesce_cpus, (int));

	_Uint64t	spare[3];
};

#ifdef ENABLE_DEPRECATED_SYSPAGE_SECTIONS
/* 'meminfo' is deprecated - use the 'asinfo' section */
enum {
	MEMTYPE_NONE,
	MEMTYPE_RAM,
	MEMTYPE_IMAGEFSYS,
	MEMTYPE_BOOTRAM,
	MEMTYPE_RESERVED,
	MEMTYPE_IOMEM,
	MEMTYPE_FLASHFSYS
};

struct meminfo_entry {
	_Paddr32t		addr;
	_Uint32t		size;
	_Uint32t		type;
	_Uint32t		spare;
};
#endif

#define AS_NULL_OFF			((_Uint16t)-1)

#define AS_ATTR_READABLE	0x0001u
#define AS_ATTR_WRITABLE	0x0002u
#define AS_ATTR_CACHABLE	0x0004u
#define AS_ATTR_VISIBLE		0x0008u
#define AS_ATTR_KIDS		0x0010u
#define AS_ATTR_CONTINUED	0x0020u

#define AS_PRIORITY_DEFAULT	100

struct asinfo_entry {
	_Uint64t			start;
	_Uint64t			end;
	_Uint16t			owner;
	_Uint16t			name;
	_Uint16t			attr;
	_Uint16t			priority;
	_SCPPTR(int, alloc_checker, (struct syspage_entry *__sp, _Uint64t *__base, _Uint64t	*__len, _Sizet __size, _Sizet __align));
};

struct hwinfo_entry {
	__FLEXARY(_Uint32t, data); /* data[] variable sized, see <hw/sysinfo.h> */
};

#define SYSTEM_PRIVATE_FLAG_ABNORMAL_REBOOT	0x00000001u
#define	SYSTEM_PRIVATE_FLAG_EALREADY_NEW	0x00000002u
#define SYSTEM_PRIVATE_FLAG_TRACE_ACTIVE	0x00000004u
#define SYSTEM_PRIVATE_FLAG_ETB_RUNNING		0x00000008u

struct system_private_entry {
	_SCPP32(struct cpupage_entry, user_cpupageptr,);
	_SCPP32(struct syspage_entry, user_syspageptr,);
	_SCPP32(struct cpupage_entry, kern_cpupageptr,);
	_SCPP32(struct syspage_entry, kern_syspageptr,);
	_SCPP32(struct kdebug_info, kdebug_info,);			/* <STAN_TAGNAME/> */
	_SCPP32(struct kdebug_callback, kdebug_call,);
	struct {
		/* Could allow 64-bit physical address even though pointers are 32-bit */
		_Paddr32t						base;
		_Uint32t						entry;
	}								boot_pgm[4];
	_Uint32t						boot_idx;
	_Uint32t						cpupage_spacing;
	_Uint32t						private_flags;
	_Uint32t						pagesize;
	/* 'ramsize' is deprecated - use the 'asinfo' section */
	_Uint32t						DEPRECATED_SECTION_NAME(ramsize);  /* <STAN_FNNAMES8/> */
	_SCPP32(struct tracebuf, tracebuf,);
	/* Could allow 64-bit physical address even though pointers are 32-bit */
	_Paddr32t						kdump_info;
	_Uint32t						num_ready;
	_Uint32t						spare[2];
	union kernel_entry {
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86)
		struct x86_kernel_entry			x86;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_ARM)
		struct arm_kernel_entry			arm;
#endif
		_Uint32t					space[8];
	}								kercall;
	_SCPP64(struct cpupage_entry, user_cpupageptr,);
	_SCPP64(struct syspage_entry, user_syspageptr,);
	_SCPP64(struct cpupage_entry, kern_cpupageptr,);
	_SCPP64(struct syspage_entry, kern_syspageptr,);
	_SCPP64(struct kdebug_info, kdebug_info,);			/* <STAN_TAGNAME/> */
	_SCPP64(struct kdebug_callback, kdebug_call,);
	_SCPP64(struct tracebuf, tracebuf,);				/* <STAN_TAGNAME/> */
};

/*
 * System independent CPU flags (system dependent grow from bottom up)
 */
#define CPU_FLAG_FPU		(1U <<  31)  /* CPU has floating point support */
#define CPU_FLAG_MMU		(1U <<  30)  /* MMU is active */

struct cpuinfo_entry {
	_Uint32t		cpu;
	_Uint32t		speed;
	_Uint32t		flags;
	_Uint32t		smp_hwcoreid;
	_Uint64t		idle_history;
	_Uint32t		spare1;
	_Uint16t		name;
	_Uint8t			ins_cache;
	_Uint8t			data_cache;
};

#define CACHE_LIST_END		0xffU	/* terminate a cache hierarchy list */

/*
 * Cache flags
 */
#define CACHE_FLAG_INSTR	0x0001U	/* cache holds instructions */
#define CACHE_FLAG_DATA		0x0002U	/* cache holds data */
#define CACHE_FLAG_UNIFIED	0x0003U	/* cache holds both ins & data */
#define CACHE_FLAG_SHARED	0x0004U	/* cache is shared between multiple  */
									/* processors in an SMP system */
#define CACHE_FLAG_SNOOPED	0x0008U	/* cache implements a bus snooping */
									/* protocol */
#define CACHE_FLAG_VIRT_TAG	0x0010U	/* cache is virtually tagged */
#define CACHE_FLAG_VIRTUAL	0x0010U	/* backwards compatability flag for above */
#define CACHE_FLAG_WRITEBACK 0x0020U/* cache does writeback, not writethru */
#define CACHE_FLAG_CTRL_PHYS 0x0040U/* control function takes 32-bit paddrs */
#define CACHE_FLAG_SUBSET	0x0080U	/* this cache obeys the 'subset' property */
#define CACHE_FLAG_NONCOHERENT 0x0100U /* cache is non-coherent on SMP */
#define CACHE_FLAG_NONISA	0x0200U /* cache doesn't obey ISA cache instr */
#define CACHE_FLAG_NOBROADCAST 0x0400U /* cache ops aren't broadcast on bus for SMP */
#define CACHE_FLAG_VIRT_IDX	0x0800U	/* cache is virtually indexed */
#define CACHE_FLAG_CTRL_PHYS64 0x1000U /* control function takes 64-bit paddrs */

struct cacheattr_entry;
typedef unsigned __cache_rtn32(_Paddr32t, unsigned, int, struct cacheattr_entry *, volatile struct syspage_entry *);
typedef unsigned __cache_rtn64(_Paddr64t, unsigned, int, struct cacheattr_entry *, volatile struct syspage_entry *);
#if __PTR_BITS__==32
	typedef	__cache_rtn32	__cache_rtn;
#else
	typedef	__cache_rtn64	__cache_rtn;
#endif
struct cacheattr_entry {
	_Uint32t	next;
	_Uint32t	line_size;
	_Uint32t	num_lines;
	_Uint32t	flags;
	_SCPP32(__cache_rtn32, control,);
	_Uint16t	ways;
	_Uint16t	spare0[1];
	_SCPP64(__cache_rtn64, control,);
};

struct typed_strings_entry {
	char				data[4]; /* variable size */
};

struct strings_entry {
	char				data[4]; /* variable size */
};

/*
 * System independent interrupt flags
 * (system dependent grow from bottom up).
 */
#define INTR_FLAG_NMI					0x8000U
#define INTR_FLAG_CASCADE_IMPLICIT_EOI	0x4000U
#define INTR_FLAG_CPU_FAULT				0x2000U
#define INTR_FLAG_SMP_BROADCAST_MASK	0x1000U
#define INTR_FLAG_SMP_BROADCAST_UNMASK	0x0800U
/* INTR_FLAG_MSI allows a range of vectors to be flagged for use as MSI vectors */
#define INTR_FLAG_MSI                   0x0400U

/*
 * System independent interrupt code gen flags
 * (system dependent grow from bottom up).
 */
#define INTR_GENFLAG_LOAD_SYSPAGE		0x8000U
#define INTR_GENFLAG_LOAD_INTRINFO		0x4000U
#define INTR_GENFLAG_LOAD_LEVEL			0x2000U
#define INTR_GENFLAG_LOAD_INTRMASK		0x1000U
#define INTR_GENFLAG_NOGLITCH			0x0800U
#define INTR_GENFLAG_LOAD_CPUNUM		0x0400U
#define INTR_GENFLAG_ID_LOOP			0x0200U

struct __intrgen_data32 {
	_Uint16t	genflags;
	_Uint16t	size;
	_SCPP32(void, rtn, (void));
};

struct __intrgen_data64 {
	_Uint16t	genflags;
	_Uint16t	size;
	_Uint32t	spare;
	_SCPPTR(void, rtn, (void));
};

#if __PTR_BITS__==32
	/* <STAN_MACRO1/> */
	#define __intrgen_data	__intrgen_data32
#else
	/* <STAN_MACRO1/> */
	#define __intrgen_data	__intrgen_data64
#endif

#define INTR_CONFIG_FLAG_PREATTACH	0x0001U
#define INTR_CONFIG_FLAG_DISALLOWED	0x0002U
#define INTR_CONFIG_FLAG_IPI		0x0004U

struct old_intrinfo_entry {
	_Uint32t				vector_base;
	_Uint32t				num_vectors;
	_Uint32t				cascade_vector;
	_Uint32t				cpu_intr_base;
	_Uint16t				cpu_intr_stride;
	_Uint16t				flags;
	struct __intrgen_data32	id;
	struct __intrgen_data32	eoi;
	_SCPP32(int, mask, (struct syspage_entry *, int));
	_SCPP32(int, unmask, (struct syspage_entry *, int));
	_SCPP32(unsigned, config, (struct syspage_entry *, struct old_intrinfo_entry *, int));
	_Uint32t				local_stride;
	_Uint32t				spare[3];
};

struct new_intrinfo_entry {
	_Uint32t				vector_base;
	_Uint32t				num_vectors;
	_Uint32t				cascade_vector;
	_Uint32t				cpu_intr_base;
	_Uint16t				cpu_intr_stride;
	_Uint16t				flags;
	struct __intrgen_data64	id;
	struct __intrgen_data64	eoi;
	_SCPPTR(int, mask, (struct syspage_entry *, int));
	_SCPPTR(int, unmask, (struct syspage_entry *, int));
	_SCPPTR(unsigned, config, (struct syspage_entry *, struct new_intrinfo_entry *, int));
	_Uint32t				local_stride;
	_Uint32t				spare[3];
};

struct smp_entry {
	_SCPP32(void, send_ipi, (struct syspage_entry *, unsigned, unsigned, unsigned *));
	_SCPP32(void, start_addr,);
	_Uint32t			pending;
	_Uint32t			cpu;
	_SCPP64(void, send_ipi, (struct syspage_entry *, unsigned, unsigned, unsigned *));
	_SCPP64(void, start_addr,);
	_Uint64t			cpu2;
};

struct pminfo_entry {
	_Uint32t			wakeup_pending;
	_Uint32t			wakeup_condition;
	_Uint32t			spare[4];
	__FLEXARY(_Uint32t, managed_storage); /* _Uint32t managed_storage[] */
};

enum mdriver_state {
	MDRIVER_INIT,
	MDRIVER_STARTUP,
	MDRIVER_STARTUP_FINI,
	MDRIVER_KERNEL,
	MDRIVER_PROCESS,
	MDRIVER_INTR_ATTACH,
	MDRIVER_STARTUP_PREPARE,
	MDRIVER_STARTUP_FINI32		/* Called to end 32-bit if 64-bit will be continuing */
};

struct old_mdriver_entry {
	_Uint32t	intr;
	_SCPP32(int, handler, (int state, void *__data));
	_SCPP32(void, data,);
	/* This should allow 64-bit physical addresses even though it is a 32-bit function */
	_Paddr32t	data_paddr;
	_Uint32t	data_size;
	_Uint32t	name;
	_Uint32t	internal;
	_Uint32t	spare[1];
};

struct new_mdriver_entry {
	_Uint32t	intr;
	_Uint32t	data_size;
	_Paddr64t	data_paddr;
	_SCPPTR(int, handler, (int state, void *__data));
	_SCPPTR(void, data,);
	_Uint32t	name;
	_Uint32t	spare[1];
	_Uint64t	internal;
};


/* <STAN_MACRO1, STAN_MACRO5> */
#ifdef SYSPAGE_SIZED_ARRAYS
    #define mdriver_entry	new_mdriver_entry
    #define intrinfo_entry	new_intrinfo_entry

	#define _SP_OLD_ARRAY(__sect)		syspage_entry_info	old_##__sect
	#define _SP_NEW_ARRAY(__sect)				\
		union {									\
			syspage_array_info	new_##__sect;	\
			syspage_array_info	__sect;			\
		}

	#define _SYSPAGE_ELEMENT_SIZE( __base, __field )	\
				((__base)->__field.element_size)
#else
    #define mdriver_entry	old_mdriver_entry
    #define intrinfo_entry	old_intrinfo_entry

	#define _SP_NEW_ARRAY(__sect)		syspage_array_info	new_##__sect
	#define _SP_OLD_ARRAY(__sect)				\
		union {									\
			syspage_entry_info	old_##__sect;	\
			syspage_entry_info	__sect;			\
		}
	#define _SYSPAGE_ELEMENT_SIZE( __base, __field )	\
				(sizeof(struct __field##_entry))
#endif
/* </STAN_MACRO1, STAN_MACRO5> */


struct syspage_entry {
	_Uint16t			size;		/* size of syspage_entry */
	_Uint16t			total_size;	/* size of system page */
	_Uint16t			type;
	_Uint16t			num_cpu;
	syspage_entry_info	system_private;
	_SP_OLD_ARRAY(asinfo);
	syspage_entry_info	DEPRECATED_SECTION_NAME(meminfo);		  /* <STAN_FNNAMES8/> */
	syspage_entry_info	hwinfo;
	_SP_OLD_ARRAY(cpuinfo);
	_SP_OLD_ARRAY(cacheattr);
	syspage_entry_info	qtime;
	syspage_entry_info	callout;
	syspage_entry_info	callin;
	syspage_entry_info	typed_strings;
	syspage_entry_info	strings;
	_SP_OLD_ARRAY(intrinfo);
	syspage_entry_info	smp;
	syspage_entry_info	pminfo;
	_SP_OLD_ARRAY(mdriver);
	_Uint32t			spare0[1];
	union {
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86)
		struct {
		_Uint32t			__x86_spacer; /* DO NOT REMOVE - needed for backwards compatability */
		struct x86_syspage_entry 	x86;
		};
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_ARM)
		struct {
		_Uint32t			__arm_spacer; /* DO NOT REMOVE - needed for backwards compatability */
		struct arm_syspage_entry	arm;
		};
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_X86_64)
		struct x86_64_syspage_entry	x86_64;
#endif
#if defined(SYSPAGE_TARGET_ALL) || defined(SYSPAGE_TARGET_AARCH64)
		struct aarch64_syspage_entry	aarch64;
#endif
		_Uint64t					filler[20];
	} un;
	_SP_NEW_ARRAY(asinfo);
	_SP_NEW_ARRAY(cpuinfo);
	_SP_NEW_ARRAY(cacheattr);
	_SP_NEW_ARRAY(intrinfo);
	_SP_NEW_ARRAY(mdriver);
};

/* <STAN_MACRO5> */
#define _SYSPAGE_ENTRY_SIZE( __base, __field )	\
	((__base)->__field.entry_size)

#define SYSPAGE_ENTRY_SIZE( __field )       (_SYSPAGE_ENTRY_SIZE( _syspage_ptr, __field ))

#define SYSPAGE_ELEMENT_SIZE(__field)		(_SYSPAGE_ELEMENT_SIZE(_syspage_ptr, __field))

#define _SYSPAGE_ENTRY( __base, __field )								\
	((struct __field##_entry *)(void *)((char *)(__base) + (__base)->__field.entry_off))

#define _SYSPAGE_CPU_ENTRY_SIZE( __base, __cpu, __field )					\
	((__base)->un.__cpu.__field.entry_size)
#define _SYSPAGE_CPU_ENTRY( __base, __cpu, __field )					\
	((struct __cpu##_##__field##_entry *)(void *)((char *)(__base) + (__base)->un.__cpu.__field.entry_off))

#define SYSPAGE_ENTRY( __field )			(_SYSPAGE_ENTRY( _syspage_ptr, __field ))
#define SYSPAGE_CPU_ENTRY( __cpu, __field )	(_SYSPAGE_CPU_ENTRY( _syspage_ptr, __cpu, __field ))

#define SYSPAGE_ARRAY_ADJ_OFFSET(__field, __p, __adj_off)	\
				((struct __field##_entry *)((_Uintptrt)(__p) + (__adj_off)))
#define _SYSPAGE_ARRAY_IDX(__base, __field, __idx)	\
				(SYSPAGE_ARRAY_ADJ_OFFSET(__field, _SYSPAGE_ENTRY((__base), __field), (__idx) * _SYSPAGE_ELEMENT_SIZE((__base), __field)))
#define SYSPAGE_ARRAY_IDX(__field, __idx)	(_SYSPAGE_ARRAY_IDX(_syspage_ptr, __field,( __idx)))
/* </STAN_MACRO5> */

__END_DECLS

#endif /* __SYSPAGE_H_INCLUDED */


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/syspage.h $ $Rev: 816075 $")
#endif
