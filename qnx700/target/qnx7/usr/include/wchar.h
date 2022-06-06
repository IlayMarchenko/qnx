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
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#ifndef _WCHAR_H_INCLUDED
#define _WCHAR_H_INCLUDED
#define _WCHAR_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef NULL
# define NULL _NULL
#endif

#ifndef _Mbstinit
#define _Mbstinit(x)    _Mbstatet x = {0}
#endif /* _Mbstinit */


#ifndef _WCMIN
#error _WCMIN not defined
#endif

#define WCHAR_MIN       (_WCMIN)
#define WCHAR_MAX       (_WCMAX)
#ifndef WEOF
#define WEOF            ((wint_t)(-1))
#endif

#if defined(__MBSTATE_T)
typedef __MBSTATE_T     mbstate_t;
#undef __MBSTATE_T
#endif

#if defined(__WCHAR_T)
typedef __WCHAR_T       wchar_t;
#undef __WCHAR_T
#endif

#if defined(__WINT_T)
typedef __WINT_T        wint_t;
#undef __WINT_T
#endif

#if defined(__SIZE_T)
typedef __SIZE_T        size_t;
#undef __SIZE_T
#endif

#ifdef __FILE_T
typedef __FILE_T        _Filet;
typedef _Filet          FILE;
#undef __FILE_T
#endif

struct tm;

__BEGIN_DECLS

        /* stdio DECLARATIONS */
wint_t fgetwc(FILE *__stream);
wchar_t *fgetws(wchar_t *_Restrict __ws, int __n, FILE *_Restrict __stream);
wint_t fputwc(wchar_t __wc, FILE *__stream);
int fputws(const wchar_t *_Restrict __ws, FILE *_Restrict __stream);
int fwide(FILE *__stream, int __n);
int fwprintf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, ...);
int fwscanf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, ...);
int vfwscanf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vswscanf(const wchar_t *_Restrict __ws, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vwscanf(const wchar_t *_Restrict __format, __NTO_va_list __arg);
wint_t getwc(FILE *__stream);
wint_t getwchar(void);
wint_t putwc(wchar_t __wc, FILE *__stream);
wint_t putwchar(wchar_t __wc);
int swprintf(wchar_t *_Restrict __ws, size_t __n, const wchar_t *_Restrict __format, ...);
int swscanf(const wchar_t *_Restrict __ws, const wchar_t *_Restrict __format, ...);
wint_t ungetwc(wint_t __wc, FILE *__stream);
int vfwprintf(FILE *_Restrict __stream, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vswprintf(wchar_t *_Restrict __ws, size_t __n, const wchar_t *_Restrict __format, __NTO_va_list __arg);
int vwprintf(const wchar_t *_Restrict __format, __NTO_va_list __arg);
int wprintf(const wchar_t *_Restrict __format, ...);
int wscanf(const wchar_t *_Restrict __format, ...);

        /* stdlib DECLARATIONS */
size_t mbrlen(const char *_Restrict __s, size_t __n, mbstate_t *_Restrict __ps);
size_t mbrtowc(wchar_t *_Restrict __pwc, const char *_Restrict __s, size_t __n, mbstate_t *_Restrict __ps);
size_t mbsrtowcs(wchar_t *_Restrict __dst, const char **_Restrict __src, size_t __len, mbstate_t *_Restrict __ps);
int mbsinit(const mbstate_t * __ps);
size_t wcrtomb(char *_Restrict __s, wchar_t __wc, mbstate_t *_Restrict __ps);
size_t wcsrtombs(char *_Restrict __dst, const wchar_t **_Restrict __src, size_t __len, mbstate_t *_Restrict __ps);
long wcstol(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, int __base);
_Longlong wcstoll(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr, int __base);
unsigned long wcstoul(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, int __base);
_ULonglong wcstoull(const wchar_t *_Restrict, wchar_t **_Restrict __endptr, int __base);

        /* string DECLARATIONS */
wchar_t *wcscat(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2);
int wcscmp(const wchar_t *__ws1, const wchar_t *__ws2);
int wcscoll(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcscpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2);
size_t wcscspn(const wchar_t *__ws1, const wchar_t *__ws2);
size_t wcslen(const wchar_t *__ws);
wchar_t *wcsncat(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
int wcsncmp(const wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wcsncpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
size_t wcsspn(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcstok(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, wchar_t **_Restrict __ptr);
size_t wcsxfrm(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
int wmemcmp(const wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wmemcpy(wchar_t *_Restrict __ws1, const wchar_t *_Restrict __ws2, size_t __n);
wchar_t *wmemmove(wchar_t *__ws1, const wchar_t *__ws2, size_t __n);
wchar_t *wmemset(wchar_t *__ws, wchar_t __wc, size_t __n);

        /* time DECLARATIONS */
size_t wcsftime(wchar_t *_Restrict __ws, size_t __maxsize, const wchar_t *_Restrict __format, const struct tm *_Restrict __timeptr);

wint_t _Btowc(int __c);
int _Wctob(wint_t __wc);
double _WStod(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);
float _WStof(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);
long double _WStold(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr, long __base);

wchar_t *wmemchr(const wchar_t *__ws, wchar_t __wc, size_t __n);
wchar_t *wcschr(const wchar_t *__ws, wchar_t __wc);
wchar_t *wcspbrk(const wchar_t *__ws1, const wchar_t *__ws2);
wchar_t *wcsrchr(const wchar_t *__ws, wchar_t __wc);
wchar_t *wcsstr(const wchar_t *__ws1, const wchar_t *__ws2);
wint_t btowc(int __c);
double wcstod(const wchar_t *_Restrict __nptr, wchar_t **_Restrict __endptr);
float wcstof(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr);
long double wcstold(const wchar_t *_Restrict __ntpr, wchar_t **_Restrict __endptr);
int wctob(wint_t __wc);
__END_DECLS

#if __GNUC__  &&  __USE_FORTIFY_LEVEL > 0
#include <wchar_chk.h>
#endif

#endif /* _WCHAR_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/wchar.h $ $Rev: 806926 $")
#endif
