/* wctype.h standard header */
#ifndef _WCTYPE
#define _WCTYPE
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

		/* MACROS */
#ifndef WEOF
#define WEOF	((wint_t)(-1))
#endif

		/* TYPE DEFINITIONS */

 #if 1200 <= _MSC_VER
 #ifndef _WCTYPE_T_DEFINED
  #define _WCTYPE_T_DEFINED
  #ifndef _WCTYPET
   #define _WCTYPET
typedef _Sizet wctype_t;
  #endif /* _WCTYPET */

  #ifndef _WINTT
   #define _WINTT
typedef _Wintt wint_t;
  #endif /* _WINTT */

 #endif /* _WCTYPE_T_DEFINED */

 #ifndef _WCTRANST
  #define _WCTRANST
typedef _Sizet wctrans_t;
 #endif /* _WCTRANST */

 #else /* 1200 <= _MSC_VER */
typedef _Sizet wctrans_t;

 #if !defined(__BORLANDC__) && !defined(_WCTYPE_T_DEFINED)
typedef _Sizet wctype_t;

 #elif !defined(_WCTYPE_T_DEFINED)
  #define _WCTYPE_T_DEFINED
typedef _Wchart wctype_t;
 #endif /* !defined(__BORLANDC__) */

#if defined(__WINT_T)
typedef __WINT_T wint_t;
#undef __WINT_T
#endif

 #endif /* 1200 <= _MSC_VER */

		/* ctype DECLARATIONS */
 #include <xwcc.h>

__BEGIN_DECLS
wctrans_t wctrans(const char *);
wctype_t wctype(const char *);
__END_DECLS

#endif /* _WCTYPE */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/wctype.h $ $Rev: 806926 $")
#endif
