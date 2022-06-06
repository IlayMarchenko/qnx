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
 *      ado_thread.c
 *              The header of wrappers around the pthread_* functions.
 */

#ifndef _ADO_THREAD_H_INCLUDED_
#define _ADO_THREAD_H_INCLUDED_

#include <sys/iofunc.h>
#include <pthread.h>

/***** defines **************/
#define ADO_MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER

#define ADO_MUTEX_TRACE
#if ADO_DEBUG
#define ado_pcm_lock(pcm, direction)		ado_pcm_lock_debug(pcm, direction, __FILE__, __LINE__)
#define ado_pcm_unlock(pcm, direction)		ado_pcm_unlock_debug(pcm, direction, __FILE__, __LINE__)
#define ado_pcm_trylock(pcm, direction)		ado_pcm_trylock_debug(pcm, direction, __FILE__, __LINE__)
#define ado_iofunc_attr_lock(attr)		    ado_iofunc_attr_lock_debug(attr, __FILE__, __LINE__)
#define ado_mixer_lock(mixer)				ado_mixer_lock_debug(mixer, __FILE__, __LINE__)
#define ado_mixer_unlock(mixer)				ado_mixer_unlock_debug(mixer, __FILE__, __LINE__)
#define ado_mixer_trylock(mixer)			ado_mixer_trylock_debug(mixer, __FILE__, __LINE__)
#define ado_iofunc_attr_unlock(attr)	    ado_iofunc_attr_unlock_debug(attr, __FILE__, __LINE__)
#define ado_iofunc_attr_trylock(attr)	    ado_iofunc_attr_trylock_debug(attr, __FILE__, __LINE__)
#define ado_mutex_init(mutex)			    ado_mutex_init_recursive_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_init_default(mutex)	    ado_mutex_init_default_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_init_recursive(mutex)	    ado_mutex_init_recursive_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_lock(mutex)			    ado_mutex_lock_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_trylock(mutex)		    ado_mutex_trylock_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_unlock(mutex)			    ado_mutex_unlock_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_destroy(mutex)		    ado_mutex_destroy_debug(mutex, __FILE__, __LINE__)
#else
#define ado_pcm_lock(pcm, direction)		ado_pcm_lock_nodebug(pcm, direction)
#define ado_pcm_unlock(pcm, direction)		ado_pcm_unlock_nodebug(pcm, direction)
#define ado_pcm_trylock(pcm, direction)		ado_pcm_trylock_nodebug(pcm, direction)
#define ado_mixer_lock(mixer)				ado_mixer_lock_nodebug(mixer)
#define ado_mixer_unlock(mixer)				ado_mixer_unlock_nodebug(mixer)
#define ado_mixer_trylock(mixer)			ado_mixer_trylock_nodebug(mixer)
#define ado_iofunc_attr_lock(attr)			iofunc_attr_lock(attr)
#define ado_iofunc_attr_unlock(attr)		iofunc_attr_unlock(attr)
#define ado_iofunc_attr_trylock(attr)		iofunc_attr_trylock(attr)
#define ado_mutex_init(mutex)				ado_mutex_init_recursive_nodebug(mutex)
#define ado_mutex_init_default(mutex)		pthread_mutex_init(mutex, NULL)
#define ado_mutex_init_recursive(mutex)		ado_mutex_init_recursive_nodebug(mutex)
#define ado_mutex_lock(mutex)				pthread_mutex_lock(mutex)
#define ado_mutex_trylock(mutex)			pthread_mutex_trylock(mutex)
#define ado_mutex_unlock(mutex)				pthread_mutex_unlock(mutex)
#define ado_mutex_destroy(mutex)			pthread_mutex_destroy(mutex)
#endif

#define ado_rwlock_init(rwl)        _rwlock_init(rwl, __FILE__, __LINE__)
#define ado_rwlock_destroy(rwl)     _rwlock_destroy(rwl, __FILE__, __LINE__)
#define ado_rwlock_rdlock(rwl)      _rwlock_rdlock(rwl, __FILE__, __LINE__)
#define ado_rwlock_wrlock(rwl)      _rwlock_wrlock(rwl, __FILE__, __LINE__)
#define ado_rwlock_unlock(rwl)      _rwlock_unlock(rwl, __FILE__, __LINE__)

/***** typedefs *************/
typedef pthread_mutex_t ado_mutex_t;
typedef struct ado_pcm ado_pcm_t;
typedef struct ado_mixer ado_mixer_t;

typedef struct ado_rwlock {
    pthread_key_t rdlock_key; // thread specific reader count
    pthread_key_t wrlock_key; // thread specific writer count
    pthread_mutex_t lock;   // access lock
    pthread_cond_t read, write; // reader and writer conditional wait
    unsigned int readers, writers, read_waiters, write_waiters; // reader and writer counters
} ado_rwlock_t;

/*** function prototypes ****/

/* thread.c */
int ado_mutex_init_default_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_init_recursive_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_lock_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_trylock_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_unlock_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_destroy_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_init_recursive_nodebug ( ado_mutex_t *mutex );

int ado_iofunc_attr_lock_debug (iofunc_attr_t *attr, char *filename, int line);
int ado_iofunc_attr_unlock_debug (iofunc_attr_t *attr, char *filename, int line);
int ado_iofunc_attr_trylock_debug (iofunc_attr_t *attr, char *filename, int line);

int ado_pcm_lock_nodebug ( ado_pcm_t *pcm, int direction );
int ado_pcm_unlock_nodebug ( ado_pcm_t *pcm, int direction );
int ado_pcm_trylock_nodebug ( ado_pcm_t *pcm, int direction );

int ado_mixer_lock_nodebug ( ado_mixer_t *mixer );
int ado_mixer_unlock_nodebug ( ado_mixer_t *mixer );
int ado_mixer_trylock_nodebug ( ado_mixer_t *mixer );

#if ADO_DEBUG
int ado_pcm_lock_debug ( ado_pcm_t *pcm, int direction, char *filename, int line);
int ado_pcm_unlock_debug ( ado_pcm_t *pcm, int direction, char *filename, int line);
int ado_pcm_trylock_debug ( ado_pcm_t *pcm, int direction, char *filename, int line);
int ado_mixer_lock_debug ( ado_mixer_t *mixer, char *filename, int line);
int ado_mixer_unlock_debug ( ado_mixer_t *mixer, char *filename, int line);
int ado_mixer_trylock_debug ( ado_mixer_t *mixer, char *filename, int line);
#endif

int _rwlock_init ( ado_rwlock_t *rwl , char *filename , int line );
int _rwlock_rdlock ( ado_rwlock_t *rwl , char *filename , int line );
int _rwlock_wrlock ( ado_rwlock_t *rwl , char *filename , int line );
int _rwlock_unlock ( ado_rwlock_t *rwl , char *filename , int line );
int _rwlock_destroy ( ado_rwlock_t *rwl , char *filename , int line );

#endif /* _ADO_THREAD_H_INCLUDED_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/audio/public/include/ado_thread.h $ $Rev: 811956 $")
#endif
