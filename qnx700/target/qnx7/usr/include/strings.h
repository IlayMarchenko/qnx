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
 *  strings.h    String functions (porting assist)
 *

 */
#ifndef _STRINGS_H_INCLUDED
#define _STRINGS_H_INCLUDED

#ifndef _STRING_H_INCLUDED
#include <string.h>
#endif

__BEGIN_DECLS

extern int  (bcmp)(const void *, const void *, size_t) __attribute__((__deprecated__)); /* use memcmp */
extern void (bcopy)(const void *, void *, size_t) __attribute__((__deprecated__)); /* use memmove */
extern void (bzero)(void *, size_t) __attribute__((__deprecated__)); /* use memset */
extern char *index(const char *, int) __attribute__((__deprecated__)); /* use strchr */
extern char *rindex(const char *, int) __attribute__((__deprecated__)); /* use strrchr */

extern int  ffs(int);
extern int  strcasecmp(const char *, const char *);
extern int  strncasecmp(const char *, const char *, size_t);

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/strings.h $ $Rev: 806926 $")
#endif
