/*
 * $QNXtpLicenseC:
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

/*
 * Copyright (c) 1994-2000 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 *
 */

#ifndef _STRING_H_INCLUDED
#define _STRING_H_INCLUDED
#define _STRING_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__SIZE_T)
typedef __SIZE_T	size_t;
#undef __SIZE_T
#endif

#if defined(__RSIZE_T)
typedef __RSIZE_T	rsize_t;
#undef __RSIZE_T
#endif

#if defined(__ERRNO_T)
typedef __ERRNO_T	errno_t;
#undef __ERRNO_T
#endif

#ifndef NULL
# define NULL _NULL
#endif

#if defined(__EXT_UNIX_MISC) && !defined(_STRINGS_H_INCLUDED)
#include <strings.h>
#endif

__BEGIN_DECLS

extern void *memchr(const void *__s, int __c, size_t __n);
extern char *strchr(const char *__s, int __c);
extern char *strpbrk(const char *__s1, const char *__s2);
extern char *strrchr(const char *__s, int __c);
extern char *strstr(const char *__s1, const char *__s2);
#if defined(__EXT_UNIX_MISC)
extern char *strcasestr(const char *__s1, const char *__s2);
#endif

extern int   memcmp(const void *__s1, const void *__s2, size_t __n);
extern void *memcpy(void *__dst, const void *__src, size_t __nbytes);
extern void *memmove(void *__s1, const void *__s2, size_t __n);
#ifndef __MEMSET_DEFINED
#define __MEMSET_DEFINED
extern void *memset(void *__s, int __c, size_t __n);
#endif
extern char *strcat(char *__s1, const char *__s2);
extern int strcmp(const char *__s1, const char *__s2);
extern int strcoll(const char *__s1, const char *__s2);
extern size_t strxfrm(char *__s1, const char *__s2, size_t __n);
extern char *strcpy(char *__s1, const char *__s2);
extern size_t strcspn(const char *__s1, const char *__s2);
extern char *strerror(int __errnum);
extern size_t strlen(const char *__s);
extern size_t strnlen(const char *__str, size_t __maxlen);
extern char *strncat(char *__s1, const char *__s2, size_t __n);
extern int strncmp(const char *__s1, const char *__s2, size_t __n);
extern char *strncpy(char *__s1, const char *__s2, size_t __n);
extern size_t strspn(const char *__s1, const char *__s2);
extern char *strtok(char *__s1, const char *__s2);

extern char *strsignal(int __signo);

#if defined(__EXT_POSIX1_199506)
extern char *strtok_r(char *__s1, const char *__s2, char **__s3);
#endif

#if defined(__EXT_POSIX1_200112)
extern int	strerror_r(int __errnum, char * __buf, size_t __len);
#endif

#if defined(__EXT_POSIX1_200112) || defined(__EXT_XOPEN_EX)
extern void *memccpy(void * __restrict __s1, const void * __restrict __s2, int __c, size_t __n);
extern char *strdup(const char *__string);
#endif

#if defined(__EXT_POSIX1_200809)
extern char    *stpcpy(char * __restrict __dst , const char * __restrict __src);
extern char    *stpncpy(char * __restrict __dst , const char * __restrict __src, size_t __num);
#endif

#if defined(__EXT_QNX)

/* WATCOM's Additional Functions (non-ANSI, non-POSIX) */

struct iovec;
extern size_t memcpyv(const struct iovec *__dst, int __dparts, size_t __doff, const struct iovec *__src, int __sparts, size_t __soff);
extern int memicmp(const void *__s1, const void *__s2, size_t __n);
extern int _memicmp(const void *__s1, const void *__s2, size_t __n);
extern char *_strdup(const char *__string);
extern int _stricmp(const char *__s1, const char *__s2);
extern char *strlwr(char *__string);
extern char *_strlwr(char *__string);
extern int _strnicmp(const char *__s1, const char *__s2, size_t __n);
extern char *strrev(char *__string);
extern char *strupr(char *__string);
extern char *_strupr(char *__string);

/* QNX's Additional Functions (non-ANSI, non-POSIX) */

extern void __strerror(int __max, int __errnum, char *__buf);
extern int straddstr(const char *__str, int __len, char **__pbuf, size_t *__pmaxbuf);
extern errno_t memset_s(void *v, rsize_t smax, int c, rsize_t n);

#endif

/* Variants that are guaranteed to be safely callable from kernel mode (ISRs and
   kernel hooks). That is, they make no use of kernel-unsafe optimizations. */

extern void *__memcpy_isr(void *__s1, const void *__s2, size_t __n);
extern void *__memset_isr(void *__s, int __c, size_t __n);
extern void *__memchr_isr(const void *__s, int __c, size_t __n);
extern char *__strcpy_isr(char *__s1, const char *__s2);
extern char *__strchr_isr(const char *__s, int __c);
extern size_t __strlen_isr(const char *__s);

#if defined(__EXT_QNX)
#define memcpy_isr __memcpy_isr
#define memset_isr __memset_isr
#define memchr_isr __memchr_isr
#define strcpy_isr __strcpy_isr
#define strchr_isr __strchr_isr
#define strlen_isr __strlen_isr
#endif

#if defined(__EXT_UNIX_MISC)
extern char *strsep(char **__stringp, const char *__delim);
#endif

#if defined(__EXT_BSD)
size_t strlcat(char *__s1, const char *__s2, size_t __n);
size_t strlcpy(char *__s1, const char *__s2, size_t __n);
#endif

__END_DECLS

#if defined(__X86__)
# include <x86/string.h>
#endif

#if  __GNUC__ &&  __USE_FORTIFY_LEVEL > 0
# include <string_chk.h>
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/string.h $ $Rev: 813412 $")
#endif
