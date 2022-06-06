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

#ifndef __STORAGE_H_INCLUDED
#define __STORAGE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include _NTO_HDR_(_pack64.h)

#if defined(__SA_ACTION_FUNC_T)
__SA_ACTION_FUNC_T
#undef __SA_ACTION_FUNC_T
#endif

#ifndef __SIGINFO_H_INCLUDED
#include <sys/siginfo.h>
#endif

__BEGIN_DECLS

/*
 * Routine to return pointer to thread local storage structure.
 */
extern struct _thread_local_storage		*__tls(void) __attribute__((__const__));


/* <STAN_MACRO1> */


/*
 * Thread local storage. This data is at the top of each threads stack.
 */

#define __TLS_FIELDS									\
	__STORAGE_PTR_TYPE(__exitfunc_t)	__exitfunc;		\
	__STORAGE_PTR_TYPE(void)			__arg;			\
	__STORAGE_PTR_TYPE(int)				__errptr;		\
	int									__errval; /* Not used for main() thread. */ \
	unsigned							__flags;		\
	int									__pid;			\
	int									__tid;			\
	unsigned							__owner;		\
	__STORAGE_PTR_TYPE(void)			__stackaddr;	\
	unsigned							__reserved1;	\
	unsigned							__numkeys;		\
	__STORAGE_PTR_TYPE(void *)			__keydata; /* Indexed by pthread_key_t */ \
	__STORAGE_PTR_TYPE(void)			__cleanup;		\
	__STORAGE_PTR_TYPE(void)			__fpuemu_data;	\
	__STORAGE_PTR_TYPE(void)			__ldd_data;	/* Used by the ldd. */ \
	__STORAGE_PTR_TYPE(__sa_action_func_t)	__sigaction;	


typedef void *__getgot_func_t(void *__pltaddr);
typedef void __mathemu_func_t(unsigned __sigcode, void **__pdata, void *__regs);
typedef void __threadwatch_func_t(int __tid);

/*
 * Process local storage.
 */

#define __PLS_FIELDS											\
	__STORAGE_PTR_TYPE(__getgot_func_t)			_getgot;		\
	__STORAGE_PTR_TYPE(__mathemu_func_t)		__mathemulator;	\
	__STORAGE_PTR_TYPE(void)					__dll_list;		\
	__STORAGE_PTR_TYPE(void)					__reserved[6];	\
	__STORAGE_PTR_TYPE(__threadwatch_func_t)	__threadwatch;


/* <STAN_MACRO5/> */
#define __STORAGE_PTR_TYPE(__type)	__type *
struct _thread_local_storage {
	__TLS_FIELDS
};

struct _process_local_storage {
	__PLS_FIELDS
};
#undef __STORAGE_PTR_TYPE

#define __STORAGE_PTR_TYPE(__type)	_Uintptr32t
struct _thread_local_storage32 {
	__TLS_FIELDS
};

struct _process_local_storage32 {
	__PLS_FIELDS
};
#undef __STORAGE_PTR_TYPE

#define __STORAGE_PTR_TYPE(__type)	_Uintptr64t
struct _thread_local_storage64 {
	__TLS_FIELDS
};

struct _process_local_storage64 {
	__PLS_FIELDS
};
#undef __STORAGE_PTR_TYPE


/* </STAN_MACRO1> */

__END_DECLS

#include _NTO_HDR_(_packpop.h)

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/storage.h $ $Rev: 780356 $")
#endif
