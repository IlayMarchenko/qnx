/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
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

#ifndef FORKSAFE_MUTEX_H_
#define FORKSAFE_MUTEX_H_


#include <pthread.h>

/*
 * A forksafe_mutex_t is a replacement for a pthread_mutex that is
 * mutually exclusive with fork() calls.
 * 
 * The issue at hand is multi-threaded programs that fork, and what happens
 * when one thread calls fork() while other threads are in critical sections
 * of code.  POSIX says that following a fork(), the child's memory state is
 * a copy of the parent, but the child only contains a single thread -- any
 * other threads in the parent are not duplicated in the child.  If one of
 * those parent threads was in the middle of manipulating a data structure
 * when the fork() happened, that data structure will be in an undefined,
 * possibly inconsistent, state in the child following the fork() call.
 * Regular mutexes can be used to protect different threads from interfering
 * with each other, but protecting against fork requires the forking code
 * to be aware of the internals of your data structure synchronization.
 * 
 * One solution to this problem is atfork handlers -- you can register an
 * atfork handler that has a prepare() function that grabs all your mutexes,
 * and parent()/child() functions that release the mutexes.  This ensures
 * that no other threads can hold the mutexes across the fork call.  However,
 * if you have many different mutexes in different code that is only loosely
 * coupled, getting the locking order correct to avoid deadlock can be
 * tricky.
 * 
 * A forksafe_mutex_t is another alternative solution to this problem.  The
 * fork() function is aware of mutexes of this type, and fork() cannot execute
 * while any forksafe mutexes are held -- fork will block while any forksafe
 * mutexes are held, and while a fork() call is underway any attempts to lock
 * a forksafe mutex will block until the fork() has completed.
 * 
 * Be aware that forksafe mutexes have priority over fork calls.  This
 * means that if a forksafe mutex is held by one thread, a second thread
 * is blocked trying to fork(), and a third thread comes along and attempts
 * to lock a forksafe mutex, the third thread will succeed -- it will not
 * wait until after the fork() call is given a chance to run.  This means
 * that if you have a lot of different threads grabbing and releasing forksafe
 * mutexes, an attempt to call fork() may be blocked indefinitely -- it will
 * not be allowed to proceed until *all* forksafe mutexes are released.
 * 
 * Also be aware that while forksafe mutexes support priority inheritance
 * between users of the mutex, there is no priority inheritance between
 * the users of the mutex and a caller of fork().  A high priority thread
 * attempting to call fork() can be blocked by a low priority thread
 * holding a forksafe mutex.
 *
 * Note that you musn't hold a forksafe_mutex_t when you invoke fork(), or
 * an obvious deadlock will occur.  The same is true of a pthread_mutex_t
 * protected by an atfork handler.
 */


typedef struct {
	pthread_mutex_t 	__mtx;
} forksafe_mutex_t;


extern int forksafe_mutex_init(forksafe_mutex_t *__fs_p, const pthread_mutexattr_t *__attr_p);
extern int forksafe_mutex_destroy(forksafe_mutex_t *__fs_p);
extern int forksafe_mutex_lock(forksafe_mutex_t *__fs_p);
extern int forksafe_mutex_trylock(forksafe_mutex_t *__fs_p);
extern int forksafe_mutex_unlock(forksafe_mutex_t *__fs_p);

#define FORKSAFE_MUTEX_INITIALIZER 		{ .__mtx = PTHREAD_MUTEX_INITIALIZER }
#define FORKSAFE_RMUTEX_INITIALIZER 	{ .__mtx = PTHREAD_RMUTEX_INITIALIZER }

#endif /* FORKSAFE_MUTEX_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/forksafe_mutex.h $ $Rev: 800602 $")
#endif
