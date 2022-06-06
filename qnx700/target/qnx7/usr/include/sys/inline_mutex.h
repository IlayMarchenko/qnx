/*
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
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

/**
 * @file	inline_mutex.h
 * @brief	Inline functions for manipulating mutexes.
 * 			Provides only limited error checking.
 */

#ifndef _INLINE_MUTEX_H_INCLUDED
#define _INLINE_MUTEX_H_INCLUDED

#ifndef __TARGET_NTO_H_INCLUDED
# include _NTO_HDR_(sys/target_nto.h)
#endif

#ifndef __STORAGE_H_INCLUDED
# include _NTO_HDR_(sys/storage.h)
#endif

#ifndef _ERRNO_H_DECLARED
# include _NTO_HDR_(errno.h)
#endif

#include _NTO_CPU_HDR_(smpxchg.h)

#ifndef __mutex_smp_cmpxchg
# define __mutex_smp_cmpxchg(_d, _c, _s)	(_smp_cmpxchg((_d), (_c), (_s)))
#endif

#ifndef __mutex_smp_xchg
# define __mutex_smp_xchg(_d, _n)	(_smp_xchg((_d), (_n)))
#endif

#if defined(__SYNC_T)
typedef __SYNC_T		sync_t;
#undef __SYNC_T
#endif

/*
 * Including <sys/neutrino.h> for these definitions bring along other header
 * files that may not be required or wanted in code that only includes
 * pthread.h.
 */
extern int SyncMutexLock_r(sync_t *__mutex);
extern int SyncMutexUnlock_r(sync_t *__mutex);

static inline int
_mutex_lock(sync_t * const mux)
{
	const unsigned	owner = __tls()->__owner;

	if (__mutex_smp_cmpxchg(&mux->__owner, 0, owner) == 0) {
		return EOK;
	}

	return SyncMutexLock_r(mux);
}

static inline int
_mutex_trylock(sync_t * const mux)
{
	const unsigned	owner = __tls()->__owner;

	if (__mutex_smp_cmpxchg(&mux->__owner, 0, owner) == 0) {
		return EOK;
	}

	return EBUSY;
}

static inline int
_mutex_unlock(sync_t * const mux)
{
	const unsigned	owner = __tls()->__owner;

	__cpu_membarrier();
	if (__mutex_smp_cmpxchg(&mux->__owner, owner, 0) == owner) {
		return EOK;
	}

	return SyncMutexUnlock_r(mux);
}

static inline int
_mutex_haslock(const sync_t * const mux)
{
	return ((mux->__owner & ~_NTO_SYNC_WAITING) == __tls()->__owner);
}

static inline unsigned
_mutex_owner(const sync_t * const mux)
{
	unsigned	owner;

	switch (mux->__owner) {
	case _NTO_SYNC_INITIALIZER:
	case _NTO_SYNC_DESTROYED:
	case _NTO_SYNC_NAMED_SEM:
	case _NTO_SYNC_SEM:
	case _NTO_SYNC_COND:
	case _NTO_SYNC_SPIN:
	case _NTO_SYNC_JOB:
	case _NTO_SYNC_DEAD:
		owner = _NTO_SYNC_MUTEX_FREE;
		break;

	default:
		owner = mux->__owner & ~_NTO_SYNC_WAITING;
		break;
	}

	return owner;
}

static inline void
_mutex_init(sync_t * const mux)
{
	/*
	 * Cannot use PTHREAD_MUTEX_INITIALIZER here, as that would create a
	 * dependency on pthread.h.
	 * Use _NTO_SYNC_MUTEX_FREE for the owner as there is no need to go into the
	 * kernel on first lock for default-style mutexes.
	 */
	const sync_t	init_mux = { {0U}, _NTO_SYNC_MUTEX_FREE };
	*mux = init_mux;
}

static inline int
_mutex_isfree(const sync_t * const mux)
{
	switch (mux->__owner) {
	case _NTO_SYNC_MUTEX_FREE:
	case _NTO_SYNC_INITIALIZER:
		return 1;

	default:
		return 0;
	}
}

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/inline_mutex.h $ $Rev: 788295 $")
#endif
