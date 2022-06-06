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
 *  sys/utime.h utimbuf structure and prototypes
 *

 */
#ifndef _UTIME_H_INCLUDED
#define _UTIME_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__TIME_T)
typedef __TIME_T	time_t;
#undef __TIME_T
#endif

#include <_pack64.h>


struct __utimbuf32 {
    _Time32t    _actime;
    _Time32t    _modtime;
};

struct __utimbuf64 {
    _Time64t    _actime;
    _Time64t    _modtime;
};

struct utimbuf {
    time_t      actime;         /* access time */
    time_t      modtime;        /* modification time */
};

__BEGIN_DECLS

/*
 *  POSIX 1003.1 Prototype
 */
#if defined(__EXT_QNX)
extern int futime( int __fildes, const struct utimbuf * __times );
#endif
extern int utime( const char *__path, const struct utimbuf * __times );

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/utime.h $ $Rev: 806926 $")
#endif
