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
 *  sys/kdebug.h
 *

 */
#ifndef __KDEBUG_H_INCLUDED
#define __KDEBUG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define KDEBUG_PROC_CURRENT			2
#define KDEBUG_PROC_HAS_REQUEST		2
#define KDEBUG_DEBUG_CURRENT		1
#define KDEBUG_CURRENT				1

enum {
	KDEBUG_TYPE_PROCESS,
	KDEBUG_TYPE_OBJECT
};

struct kdebug_entry {
	struct kdebug_entry				*next;
	struct kdebug_entry				**prev;
	unsigned						pad[6];
	signed char						handle;
	char							type;
	unsigned short					flags;
	void							*ptr;
};

#define KDEBUG_FLAG_DEBUGGED		0x0001		/* set by kernel debugger when it assigns a handle */
#define KDEBUG_FLAG_UNLOADED		0x0002		/* set by proc when process image is removed */
#define KDEBUG_FLAG_STOP_ON_ENTRY	0x0004		/* set be kdebug when stopping on first instr */

enum {
	KDREQ_VADDRINFO,
	KDREQ_PATH,
	KDREQ_PARKIT,
	KDREQ_INVOKE,
	KDREQ_UNPARKIT,
	KDREQ_DUMP_SWEEP,
	KDREQ_SHUTDOWN_REPORT
};

union kd_request {
	struct kdr_hdr {
		unsigned	req;
	}							hdr;	/*in*/

	struct kdr_vaddrinfo {
		struct kdr_hdr		hdr; 		/*in*/
		struct kdebug_entry	*entry;		/*in*/
		_Uintptrt			vaddr;		/*in*/
		_Paddr64t			paddr;		/*out*/
		_Paddr64t			size;		/*out*/
		unsigned			prot;		/*out*/
	}							vaddrinfo;

	struct kdr_path {
		struct kdr_hdr		hdr; 		/*in*/
		struct kdebug_entry	*entry;		/*in*/
		char				*buff;		/*in*/
		unsigned			len;		/*in/out*/
	}							path;

	struct kdr_parkit {
		struct kdr_hdr	hdr;			/*in*/
		unsigned		cpu;			/*in*/
	}							parkit;

	struct kdr_unparkit {
		struct kdr_hdr	hdr;			/*in*/
		unsigned		cpu;			/*in*/
	}							unparkit;

	struct kdr_invoke {
		struct kdr_hdr	hdr;			/*in*/
		void			*ptr;			/*in/out*/
		void			(*output)(char *p, unsigned len);	/*in*/
	}							invoke;

	struct kdr_dump_sweep {
		struct kdr_hdr	hdr;			/*in*/
		int				do_filter;		/*in*/
		_Paddr64t		paddr;			/*in/out*/
		_Paddr64t		size;			/*out*/
	}							dump_sweep;

	struct kdr_shutdown_report {
		struct kdr_hdr	hdr;				/*in*/
		unsigned				sigcode;	/*in*/
		const void				*regs;		/*in*/
	}							shutdown_report;
};


typedef int (*kdrequest_t)(union kd_request *);

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_INFO_SIZED(__sname, __kdebugentryp, __voidp, __requestfn, __kdebugprivatep, __ccharp, __kdumpprivatep) \
	struct __sname { \
		unsigned char					proc_version; \
		unsigned char					debug_version; \
		unsigned short					flags; \
		__kdebugentryp					process_list; \
		__kdebugentryp					resident_list; \
		__voidp							unused1; \
		__requestfn						request; \
		__kdebugprivatep				kdbg_private; \
		__voidp							unused2; \
		__ccharp						timestamp; \
		__voidp							unused3; \
		__kdumpprivatep					kdump_private; \
		void							*reserved[5]; \
	};
__KDEBUG_INFO_SIZED(kdebug_info, struct kdebug_entry*, void*, kdrequest_t, const struct kdebug_private*, const char*, const struct kdump_private*);
__KDEBUG_INFO_SIZED(kdebug_info32, _Uint32t, _Uint32t, _Uint32t, _Uint32t, _Uint32t, _Uint32t);		/* <STAN_TAGNAME/> */
__KDEBUG_INFO_SIZED(kdebug_info64, _Uint64t, _Uint64t, _Uint64t, _Uint64t, _Uint64t, _Uint64t);		/* <STAN_TAGNAME/> */

struct kdebug_callback {
	unsigned short					kdebug_version;
	unsigned short					callback_len;
	int								(*watch_entry)(struct kdebug_entry *entry, _Uintptrt entry_vaddr);
	unsigned						(*fault_entry)(struct kdebug_entry *entry, unsigned sigcode, void *regs);
	void							(*msg_entry)(const char *msg, unsigned len);
	void							(*update_plist)(struct kdebug_entry *entry);
	struct cpu_extra_state			*extra;
	void							*reserved[7];
};


#define KDEBUG_FLAG_DIRTY			0x0001

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_VECTOR_ENTRY_SIZED(__sname, __voidp, __voidpp) \
	struct __sname { \
		__voidp			free; \
		__voidpp		vector; \
		unsigned short	nentries; \
		unsigned short	nfree; \
	}
__KDEBUG_VECTOR_ENTRY_SIZED(kdebug_vector_entry, void*, void**);
__KDEBUG_VECTOR_ENTRY_SIZED(kdebug_vector_entry32, _Uint32t, _Uint32t);
__KDEBUG_VECTOR_ENTRY_SIZED(kdebug_vector_entry64, _Uint64t, _Uint64t);

#define KDEBUG_VECTOR_VER			1

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDEBUG_PRIVATE_SIZED(__sname, __voidp, __voidpp, __vector_entryp) \
	struct __sname { \
		unsigned						flags; \
		__voidp							actives;			/* pointer to the active array pointer */ \
		__voidp							aspaces;			/* pointer to the aspaces_prp array pointer */ \
		__voidpp						irqstack;			/* pointer to irq stack */ \
		__vector_entryp					process_vector;		/* pointer to process vector */ \
		unsigned short					vector_ver;			/* version of vector type */ \
		unsigned short					th_tid_off;			/* offset within active to tid-1 */ \
		unsigned short					th_reg_off;			/* offset within active to registers */ \
		unsigned short					th_process_off;		/* offset within active to process entry */ \
		unsigned short					pr_pid_off;			/* offset within process to pid */ \
		unsigned short					pr_debug_name_off;	/* offset within process to name pointer */ \
		unsigned short					irq_reg_off;		/* offset within irq stack to registers */ \
		unsigned short					pr_threads_off;		/* offset within process to threads vector */ \
		unsigned short					pr_kdebug_off;		/* offset within process to kdebug_entry */ \
		unsigned short					th_pri_off;			/* offset within thread entry of priority */ \
		unsigned short					pr_memory_off;		/* offset within process entry of memory */ \
		unsigned short					th_client_off;		/* offset within thread to client*/ \
	}
__KDEBUG_PRIVATE_SIZED(kdebug_private, void*, void**, struct kdebug_vector_entry*);
__KDEBUG_PRIVATE_SIZED(kdebug_private32, _Uint32t, _Uint32t, _Uint32t);
__KDEBUG_PRIVATE_SIZED(kdebug_private64, _Uint64t, _Uint64t, _Uint64t);

#define KDUMP_VERSION 1

typedef void (*kdump_dump_sweep_t)(int do_filter, _Paddr64t *ppaddr, _Paddr64t *psize);

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __KDUMP_PRIVATE_SIZED(__sname, __voidp, __uintptrtp, __kdump_sweep) \
	struct __sname { \
		/* Following fields are for old vm; NULL pmem_root implies new vm */ \
		__voidp						pmem_root;				/* root of phys mem structures */ \
		__uintptrtp					colour_mask;			/* pointer to colour mask */ \
		unsigned short				as_pgdir_off;			/* offset within aspace entry of pgdir */ \
		unsigned short				paddr_size;				/* bytes in a paddr_t */ \
		/* following fields are for new vm */ \
		unsigned short				kdump_version;			/* version of kdump structure */ \
		__kdump_sweep				dump_sweep;				/* pmem iterator function */ \
		unsigned short				as_hat_off;				/* offset within aspace entry of hat_aspace */ \
	}
__KDUMP_PRIVATE_SIZED(kdump_private, void*, _Uintptrt*, kdump_dump_sweep_t);
__KDUMP_PRIVATE_SIZED(kdump_private32, _Uint32t, _Uint32t, _Uint32t);
__KDUMP_PRIVATE_SIZED(kdump_private64, _Uint64t, _Uint64t, _Uint64t);

#define KDEBUG_PRIVATE_SEGS			0x00000001			/* private flags */

#define KDEBUG_PRIVATE_INDIRECT		0x8000				/* If set in offset, target is a pointer */

struct kprintf_ringbuffer {
	_Uint32t			buf_magic;
	_Uint32t			buf_size;
	volatile _Uint32t	buf_idx;
	_Uint32t			pad[5];
	char				buf[1];
};

#define KPRINTF_ACTIVE_RINGBUFFER	0xbeefeeee
#define KPRINTF_INACTIVE_RINGBUFFER 0xdeadbeef

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/kdebug.h $ $Rev: 798933 $")
#endif
