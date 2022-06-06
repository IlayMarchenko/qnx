// -*- C++ -*-
//===------------------------ support/nto/xlocale.h -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_SUPPORT_NTO_XLOCALE_H
#define _LIBCPP_SUPPORT_NTO_XLOCALE_H

#if defined(__QNXNTO__)

#include <ctype.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdarg.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef const char *locale_t;
#ifdef __cplusplus
}
#endif

#include "../xlocale/xlocale.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int isascii(int);

#define LC_COLLATE_MASK _M_COLLATE
#define LC_CTYPE_MASK _M_CTYPE
#define LC_MONETARY_MASK _M_MONETARY
#define LC_NUMERIC_MASK _M_NUMERIC
#define LC_TIME_MASK _M_TIME
#define LC_MESSAGES_MASK _M_MESSAGES
#define LC_ALL_MASK _M_ALL

static inline locale_t newlocale(int, const char *name, locale_t) {
    const char *oldloc = setlocale(LC_ALL, NULL);
    const char *newloc = setlocale(LC_ALL, name);
    setlocale(LC_ALL, oldloc);
    return newloc;
}

static inline locale_t uselocale(locale_t loc) {
    const char *oldloc = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, loc);
    return oldloc;
}

static inline int freelocale(locale_t loc) {
  return 0;
}

static inline int vasprintf(char **s, const char *format, va_list va) {
  int ret;
  char *buf;
  ret = vsnprintf(NULL, 0, format, va);
  if (ret < 0 || (buf = (char*)malloc(ret+1)) == NULL) {
    va_end(va);
    return -1;
  }
  ret = vsnprintf(buf, ret+1, format, va);
  if (ret < 0) {
    free(buf);
    return -1;
  }
  *s = buf;
  return ret;
}

static inline size_t mbsnrtowcs(wchar_t *dst, const char **src, size_t nmc, size_t nwc, mbstate_t *ps) {
  size_t i;
  const char *s = *src;

  if (!dst) {
    nwc = (size_t)-1;
  }

  for (i=0; i < nwc && nmc != 0; ++i) {
    wchar_t wc;
    int len = mbrtowc(&wc, s, nmc, ps);
    if (len < 0) {
      return -1;
    }

    s += len;
    nmc -= len;
    if (dst) {
      dst[i] = wc;
      *src = s;
    }
    if (len == 0) {
      if (dst) {
        *src = NULL;
      }
      break;
    }
  }
  return i;
}

static inline size_t wcsnrtombs(char *dst, const wchar_t **src, size_t nwc, size_t nmc, mbstate_t *ps) {
  size_t nbytes = 0;
  size_t i;
  const wchar_t *ws = *src;

  if (!dst) {
    nmc = (size_t)-1;
  }

  for (i=0; i < nwc && nmc > nbytes; ++i) {
    char buf[MB_LEN_MAX];
    int len = wcrtomb(buf, ws[i], ps);
    if (len == -1) {
        return -1;
    } else if ((nbytes+=len) > nmc) {
        errno = EILSEQ;
        return -1;
    }
    if (dst) {
      memcpy(dst, buf, len);
      dst += len;
      *src = &ws[i+1];
    }
    if (ws[i] == L'\0') {
      if (dst) {
        *src = NULL;
      }
      nbytes--;
      break;
    }
  }

  return nbytes;
}

#ifdef __cplusplus
}
#endif

#endif // defined(__QNXNTO__)
#endif // _LIBCPP_SUPPORT_NTO_XLOCALE_H

