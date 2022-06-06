/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
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

#ifndef _THREADS_H_INCLUDED
#define _THREADS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _TIME_H_INCLUDED
#include <time.h>
#endif

#if defined(__SYNC_T)
typedef __SYNC_T sync_t;
#undef __SYNC_T
#endif

#if defined(__THRD_COND_T)
typedef __THRD_COND_T cnd_t;
#undef __THRD_COND_T
#endif

#if defined(__THRD_THRD_T)
typedef __THRD_THRD_T thrd_t;
#undef __THRD_THRD_T
#endif

#if defined(__THRD_TSS_T)
typedef __THRD_TSS_T tss_t;
#undef __THRD_TSS_T
#endif

#if defined(__THRD_MTX_T)
typedef __THRD_MTX_T mtx_t;
#undef __THRD_MTX_T
#endif

#if defined(__THRD_ONCE_T)
typedef __THRD_ONCE_T once_flag;
#undef __THRD_ONCE_T
#endif

__BEGIN_DECLS
#include <_pack64.h>

/* <STAN_MACRO1> */
#if !defined(__cplusplus)
#define thread_local _Thread_local
#endif
#define ONCE_FLAG_INIT __THRD_ONCE_INIT
/* </STAN_MACRO1> */
#define TSS_DTOR_ITERATIONS 4

typedef void (*tss_dtor_t)(void*);
typedef int (*thrd_start_t)(void*);

enum {
	mtx_plain = 0x1,
	mtx_recursive = 0x2,
	mtx_timed = 0x4,
};

enum {
	thrd_success,
	thrd_timedout,
	thrd_busy,
	thrd_error,
	thrd_nomem,
};

void call_once(once_flag *__flag, void (*__func)(void));

int cnd_broadcast(cnd_t *__cond);
void cnd_destroy(cnd_t *__cond);
int cnd_init(cnd_t *__cond);
int cnd_signal(cnd_t *__cond);
int cnd_timedwait(cnd_t *_Restrict __cond, mtx_t *_Restrict __mtx, const struct timespec *_Restrict __ts);
int cnd_wait(cnd_t *__cond, mtx_t *__mtx);

void mtx_destroy(mtx_t *__mtx);
int mtx_init(mtx_t *__mtx, int __type);
int mtx_lock(mtx_t *__mtx);
int mtx_timedlock(mtx_t *_Restrict __mtx, const struct timespec *_Restrict __ts);
int mtx_trylock(mtx_t *__mtx);
int mtx_unlock(mtx_t *__mtx);

int thrd_create(thrd_t *__thr, thrd_start_t __func, void *__arg);
thrd_t thrd_current(void);
int thrd_detach(thrd_t __thr);
int thrd_equal(thrd_t __thr0, thrd_t __thr1);
void thrd_exit(int __res) __attribute__((__noreturn__));
int thrd_join(thrd_t __thr, int *__res);
int thrd_sleep(const struct timespec *__duration, struct timespec *__remaining);
void thrd_yield(void);

int tss_create(tss_t *__key, tss_dtor_t __dtor);
void tss_delete(tss_t __key);
void *tss_get(tss_t __key);
int tss_set(tss_t __key, void *__val);

#include <_packpop.h>
__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/threads.h $ $Rev: 812331 $")
#endif
