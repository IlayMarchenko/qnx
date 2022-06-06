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

#ifndef _TIME_H_INCLUDED
#define _TIME_H_INCLUDED
#define _TIME_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__TIME_T)
typedef __TIME_T    time_t;
#undef __TIME_T
#endif

#if defined (__EXT_QNX)
typedef _Time32t time32_t;
typedef _Time64t time64_t;
#endif  /* __EXT_QNX */

#if defined(__CLOCK_T)
typedef __CLOCK_T   clock_t;
#undef __CLOCK_T
#endif

#if defined(__SIZE_T)
typedef __SIZE_T    size_t;
#undef __SIZE_T
#endif

#if defined(__TIMER_T)
typedef __TIMER_T   timer_t;
#undef __TIMER_T
#endif

#if defined(__CLOCKID_T)
typedef __CLOCKID_T clockid_t;
#undef __CLOCKID_T
#endif

#if defined(__TIMESPEC)
__TIMESPEC;
#undef __TIMESPEC
#endif

#include _NTO_HDR_(_pack64.h)

#ifndef NULL
# define NULL _NULL
#endif

#ifndef __SYSCONF_DEFINED
#define __SYSCONF_DEFINED
__BEGIN_DECLS
extern long _sysconf(int __name);
__END_DECLS
#endif

/* Unix98 says that the value of CLOCKS_PER_SEC is required to be 1
 * million on all XSI-conformant systems, and it may be variable on
 * other systems and it should not be assumed that CLOCKS_PER_SEC is a
 * compile-time constant. */

#define CLOCKS_PER_SEC  1000000

#if defined(__EXT_QNX) || !defined(__EXT_POSIX1_200112)
/* CLK_TCK removed in 1003.1-2001 */
# define CLK_TCK _sysconf(3) /* 3 == _SC_CLK_TCK */
#endif

struct itimerspec {
    struct timespec it_value,
                    it_interval;
    } ;

/*  Clock types */
#define CLOCK_REALTIME              0
#if defined(__EXT_QNX)
# define CLOCK_SOFTTIME             1
#endif
#if defined(__EXT_POSIX1_200112)    /* POSIX 1003.1j D10 */
# define CLOCK_MONOTONIC            2
#endif
#if defined(__EXT_POSIX1_200112)    /* POSIX 1003.1d D14 */
# define CLOCK_PROCESS_CPUTIME_ID   3
# define CLOCK_THREAD_CPUTIME_ID    4
#endif

/* Timer settime flags */
#define TIMER_ABSTIME       0x80000000u
#if defined(__EXT_QNX)
#define TIMER_TOLERANCE		0x40000000u
#define TIMER_PRECISE		0x20000000u
#endif

#if defined(__EXT_ANSIC_201112)
#define TIME_UTC 1
#endif

__BEGIN_DECLS

#if defined(__EXT_POSIX1_199309)

struct sigevent; /* for C++ */

extern int clock_getres(clockid_t __clock_id, struct timespec *__res);
extern int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
#if defined(__NYI)
extern int clock_setres(clockid_t __clock_id, struct timespec *__res);
#endif
extern int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
#if defined(__EXT_POSIX1_200112)        /* Approved 1003.1d D14 */
#if defined(__PID_T)
typedef __PID_T pid_t;
#undef __PID_T
#endif
extern int clock_getcpuclockid(pid_t __pid, clockid_t *__clock_id);
#endif
extern int nanosleep(const struct timespec *__rqtp, struct timespec *__rmtp);
extern int timer_create(clockid_t __clock_id, struct sigevent *__evp, timer_t *__timerid);
extern int timer_delete(timer_t __timerid);
extern int timer_getoverrun(timer_t __timerid);
extern int timer_gettime(timer_t __timerid, struct itimerspec *__value);
extern int timer_settime(timer_t __timerid, int __flags, const struct itimerspec *__value, struct itimerspec *__ovalue);
#endif

#if defined(__EXT_QNX)
extern int nanosleep_abs(clockid_t __clock_id, const struct timespec *__rqtp);
extern int nanosleep_rel(clockid_t __clock_id, const struct timespec *__rqtp, struct timespec *__rmtp);
#endif

#if defined(__EXT_POSIX1_200112)    /* Approved 1003.1j D10 */
extern int clock_nanosleep(clockid_t __clock_id, int __flags, const struct timespec *__rqtp, struct timespec *__rmtp);
#endif

#if defined(__EXT_QNX)
extern int timer_getexpstatus(timer_t __timerid);
#endif

#if defined(__EXT_QNX)
extern int nanospin_calibrate(int __disable);
extern int nanospin(const struct timespec *__rqtp);
extern void nanospin_count(unsigned long __count);
extern int nanospin_ns(unsigned long __nsec);
extern unsigned long nanospin_ns_to_count(unsigned long __nsec);
extern int timer_timeout(clockid_t __id, int __flags, const struct sigevent *__notify, const struct timespec *__ntime, struct timespec *__otime);
extern int timer_timeout_r(clockid_t __id, int __flags, const struct sigevent *__notify, const struct timespec *__ntime, struct timespec *__otime);
extern void nsec2timespec(struct timespec *__ts, _Uint64t __nsec);
extern _Uint64t timespec2nsec(const struct timespec *__ts);
# define timespec2nsec(__ts) ((_Uint64t)(__ts)->tv_sec*(_Uint64t)1000000000+(_Uint64t)(_Int64t)(__ts)->tv_nsec)
# define TIMESPEC_VALID(__ts) (((__ts)->tv_nsec >= 0) && ((__ts)->tv_nsec < 1000000000L))
#endif

struct  tm {
        int  tm_sec;    /* seconds after the minute -- [0,61] */
        int  tm_min;    /* minutes after the hour   -- [0,59] */
        int  tm_hour;   /* hours after midnight     -- [0,23] */
        int  tm_mday;   /* day of the month         -- [1,31] */
        int  tm_mon;    /* months since January     -- [0,11] */
        int  tm_year;   /* years since 1900                   */
        int  tm_wday;   /* days since Sunday        -- [0,6]  */
        int  tm_yday;   /* days since January 1     -- [0,365]*/
        int  tm_isdst;  /* Daylight Savings Time flag */
        long int tm_gmtoff; /* Offset from gmt */
        const char *tm_zone;    /* String for zone name */
};

extern char *asctime(const struct tm *__timeptr);
extern char *ctime(const time_t *__timer);
extern clock_t clock(void);
extern double difftime(time_t __t1, time_t __t0);
extern struct tm *gmtime(const time_t *__timer);
extern struct tm *localtime(const time_t *__timer);
extern time_t mktime(struct tm *__timeptr);
extern size_t strftime(char *__s, size_t __maxsiz, const char *__fmt, const struct tm *__tp);
extern time_t time(time_t *__timer);

#define __leap_year(__year) (((__year) % 4) == 0 && (((__year) % 100) != 0 || ((__year) % 400) == 100))

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)

extern char *asctime_r(const struct tm *__timeptr, char *__buff);
extern char *ctime_r(const time_t *__timer, char *__buff);
extern struct tm *gmtime_r(const time_t *__timer, struct tm *__tm);
extern struct tm *localtime_r(const time_t *__timer, struct tm *__tm);
extern void tzset(void);

#if defined(__SLIB_DATA_INDIRECT) && !defined(tzname) && !defined(__SLIB)
  char **__get_tzname_ptr(void);
  #define tzname (__get_tzname_ptr())
#else
  extern char    *tzname[]; /*  time zone names */
#endif
#if defined(__EXT_XOPEN_EX)
#if defined(__SLIB_DATA_INDIRECT) && !defined(daylight) && !defined(__SLIB)
  int *__get_daylight_ptr(void);
  #define daylight *(__get_daylight_ptr())
#else
  extern int     daylight;    /* d.s.t. indicator */
#endif
#if defined(__SLIB_DATA_INDIRECT) && !defined(timezone) && !defined(__SLIB)
  long int *__get_timezone_ptr(void);
  #define timezone *(__get_timezone_ptr())
#else
  extern long  int  timezone;    /* # of seconds from GMT */
#endif
#endif

#endif

#if defined(__EXT_XOPEN_EX)
extern struct tm *getdate(const char *__string);
extern char *strptime(const char *__buf, const char *__format, struct tm *__tm);
#endif

#if defined(__EXT_UNIX_MISC)
extern time_t timegm (struct tm *__tp);
#endif

#if defined(__EXT_ANSIC_201112)
extern int timespec_get(struct timespec *__ts, int __base);
#endif

#include _NTO_HDR_(_packpop.h)

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/time.h $ $Rev: 807855 $")
#endif
