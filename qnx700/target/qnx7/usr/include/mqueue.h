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
 *  mqueue.h: POSIX 1003.1b message queues and access functions
 *

 */

#if !defined _MQUEUE_H_INCLUDED
#define _MQUEUE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if !defined __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#if !defined _SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#if !defined _FCNTL_H_INCLUDED
#include <fcntl.h>
#endif

__BEGIN_DECLS

#include <_pack64.h>

/* <STAN_MACRO1, STAN_MACRO5/> */
#define __MQ_ATTR(__type, __pref)	\
	__type __pref##_maxmsg;   /* maximum number of messages stored */	\
	__type __pref##_msgsize;  /* maximum message length */				\
	__type __pref##_flags;												\
	__type __pref##_curmsgs;  /* current number of messages stored */	\
	__type __pref##_sendwait; /* # of processes waiting to send */		\
	__type __pref##_recvwait; /* # of processes waiting to receive */

struct mq_attr {
	__MQ_ATTR(long, mq)
};

struct __msg_mq_attr {
	__MQ_ATTR(_Int32t, __mq)
};

/* Flag definitions */
/* #define MQ_NONBLOCK         O_NONBLOCK */
#if (O_NONBLOCK & 0x1f)
    #error O_NONBLOCK overlaps other flags
#endif

typedef int mqd_t;

extern mqd_t mq_open(const char *__name, int __oflag, ...);
extern int   mq_close(mqd_t __mqdes);
extern int   mq_send(mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len, 
                      unsigned __msg_prio);
extern ssize_t   mq_receive(mqd_t __mqdes, char *__msg_ptr, size_t __msg_len,
                      unsigned *__msg_prio);
extern int   mq_notify(mqd_t __mqdes, const struct sigevent *__notification);
extern int   mq_getattr(mqd_t __mqdes, struct mq_attr *__mqstat);
extern int   mq_setattr(mqd_t __mqdes, const struct mq_attr *__mqstat,
                      struct mq_attr *__omqstat);
extern int   mq_unlink (const char *__name);
#if defined(__EXT_POSIX1_200112)		/* Approved 1003.1d D14 */
struct timespec;
extern int   mq_timedsend(mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len, 
                      unsigned __msg_prio, const struct timespec *__abs_timeout);
extern ssize_t   mq_timedreceive(mqd_t __mqdes, char *__msg_ptr, size_t __msg_len,
                      unsigned *__msg_prio, const struct timespec *__abs_timeout);
#endif

/* non posix versions of timed send and timed receive. These are not affected by a Time-of-Day (TOD) change 
 * Note: the __abs_mono_timeout parameter must be relative to the CLOCK_MONOTINIC clock. example: 
 * 
 *		ClockTime(CLOCK_MONOTONIC, NULL, &timenow); 
 *		to.tv_sec = timenow/1000000000LL + my_timeout_secs;
 *		to.tv_nsec = timenow % 1000000000LL;
 *		result = mq_timedsend_monotonic (mq, msg, sizeof (msg), 0, &to);
 *
 */
#ifdef __EXT_QNX

extern int   mq_timedsend_monotonic(mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len, 
                      unsigned __msg_prio, const struct timespec *__abs_mono_timeout);
extern ssize_t   mq_timedreceive_monotonic(mqd_t __mqdes, char *__msg_ptr, size_t __msg_len,
                      unsigned *__msg_prio, const struct timespec *__abs_mono_timeout);

#endif

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/mqueue.h $ $Rev: 820165 $")
#endif
