/*
 * $QNXtpLicenseC:
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





/* yvals.h values header for conforming compilers on various systems */
#ifndef _YVALS
#define _YVALS
#include <sys/platform.h>

 #if defined(__clang__)
  #define _CLANG	1

 #else	/* __clang__ */
  #define _CLANG	0
 #endif	/* __clang__ */

 #define _GCC43	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 3 <= __GNUC_MINOR__)	/* 4.3 or newer */
 #define _GCC44	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 4 <= __GNUC_MINOR__)	/* 4.4 or newer */
 #define _GCC45	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 5 <= __GNUC_MINOR__)	/* 4.5 or newer */
 #define _GCC46	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 6 <= __GNUC_MINOR__)	/* 4.6 or newer */
 #define _GCC47	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 7 <= __GNUC_MINOR__)	/* 4.7 or newer */
 #define _GCC48	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 8 <= __GNUC_MINOR__)	/* 4.8 or newer */
 #define _GCC49	(_CLANG || 4 < __GNUC__ \
	|| 4 == __GNUC__ && 9 <= __GNUC_MINOR__)	/* 4.9 or newer */
 #define _GCC0X	_GCC43	/* basic support for C++0X */

 #if __EDG__
#ifndef _DNK_RENAME
 #define _DNK_RENAME
#endif /* _DNK_RENAME */

 #define getenv_s	_Dnk_getenv_s

 #define iswalnum	_Dnk_iswalnum
 #define iswalpha	_Dnk_iswalpha
 #define iswcntrl	_Dnk_iswcntrl
 #define iswctype	_Dnk_iswctype
 #define iswdigit	_Dnk_iswdigit
 #define iswgraph	_Dnk_iswgraph
 #define iswlower	_Dnk_iswlower
 #define iswprint	_Dnk_iswprint
 #define iswpunct	_Dnk_iswpunct
 #define iswspace	_Dnk_iswspace
 #define iswupper	_Dnk_iswupper
 #define iswxdigit	_Dnk_iswxdigit

 #define localeconv	_Dnk_localeconv
 #define setlocale	_Dnk_setlocale

 #define strtol		_Dnk_strtol

 #define tolower	_Dnk_tolower
 #define toupper	_Dnk_toupper
 #endif /* __EDG__ */

/* You can predefine (on the compile command line, for example):

_ADDED_C_LIB=0 -- to omit declarations for C extensions
_HAS_C9X -- to turn ON C99 library support
_HAS_CHAR16_T_LANGUAGE_SUPPORT=1 -- to turn ON builtin char16_t/char32_t
_HAS_CPP0X=0 -- to turn OFF changes for C++0X (if present)
_HAS_FIXED_POINT=0 -- to turn OFF fixed-point extensions (if present)
_NO_LOCALES=1 -- to turn OFF named locales
_NO_MT -- to turn OFF thread synchronization
_STL_DB (or _STLP_DEBUG) -- to turn ON iterator/range debugging
_USE_EXISTING_SYSTEM_NAMES=0 -- to disable mappings (_Open to open)
__NO_LONG_LONG -- to define _Longlong as long, not long long

You can change (in this header AND ALL ITS COPIES):

_COMPILER_TLS -- from 0 to 1 if _TLS_QUAL is not nil
_FILE_OP_LOCKS -- from 0 to 1 for file atomic locks
_GLOBAL_LOCALE -- from 0 to 1 for shared locales instead of per-thread
_TLS_QUAL -- from nil to compiler TLS qualifier, such as __declspec(thread)
 */


#ifdef __EXT_ANSIC_199901
#define _C99	1
#endif

#if defined(__GNUC__) && (2 <= __GNUC__) && (!__STRICT_ANSI__)
#define _C99 1
#endif

#ifdef _SOFT_FLOAT
 /* no FPU hardware support */
 #define _FPP_TYPE _FPP_NONE
#else 
		/* DETERMINE MACHINE TYPE */

 #if defined(i386) || defined(__i386) \
	|| defined(__i386__) || defined(_M_IX86)	/* Pentium */
  #define _FPP_TYPE	_FPP_X86	/* Pentium FPP */
 #elif defined(_MIPS) || defined(_MIPS_) || defined(_M_MRX000) \
    || defined(__MIPS__)		/* MIPS */
  #define _FPP_TYPE	_FPP_MIPS	/* MIPS FPP */
 #elif defined(__ppc__) || defined(_POWER) || defined(_M_PPC) \
    || defined(__PPC__)	/* PowerPC */
  #define _FPP_TYPE	_FPP_PPC	/* PowerPC FPP */
 #elif (defined(_ARM_) || defined(__ARM__)) && defined(__ARM_ARCH_7A__)	/* ARMv7 */
  #define _FPP_TYPE	_FPP_ARM
 #elif defined(_ARM_) || defined(__ARM__)	/* ARM */
  #define _FPP_TYPE	_FPP_NONE
 #elif defined(_SH4_) || defined(__SH__)	/* SH4 */
  #define _FPP_TYPE	_FPP_SH4	/* Hitachi SH4 FPP */
 #elif defined(__X86_64__)
  #define _FPP_TYPE	_FPP_X86	/* Pentium FPP */
 #elif defined(__aarch64__)
  #define _FPP_TYPE	_FPP_AARCH64	/* ARMv8 FPP */
 #else /* system detector */
#error unknown compilation environment
 #endif /* system detector */
#endif

  #define _HAS_POSIX_C_LIB	1	/* use common Unix conventions */

#ifdef __QNX__
/* setting this will stop static and global definitions having a "= 0". */
#define _UNINITALIZED_IS_ZERO		1

/* set this to 1 to compile in atexit cleanup handlers */
#define _TERMINATION_CLEANUP		0

/* set this to 1 to add built-in support POSIX locales */
#define _ADD_POSIX					1

/* Search for locale file here if the LOCFILE envar is not set */
#define _DEFAULT_LOCFILE	"/usr/share/locale/locale.file"

#endif

 #if !defined(_RSIZE_MAX)
  #define _RSIZE_MAX    ((_Sizet)(-1) >> 1)     /* or sizeof largest object */
 #endif /* !defined(_RSIZE_MAX) */

		/* THREAD AND LOCALE CONTROL */
 #define _MULTI_THREAD	1	/* 0 for no thread locks */

#define _GLOBAL_LOCALE	1	/* 0 for per-thread locales, 1 for shared */
#define _FILE_OP_LOCKS	1	/* 0 for no FILE locks, 1 for atomic */

		/* THREAD-LOCAL STORAGE */
#define _COMPILER_TLS	0	/* 1 if compiler supports TLS directly */
#define _TLS_QUAL	/* TLS qualifier, such as __declspec(thread), if any */

 #if !defined(_ADDED_C_LIB)
  #define _ADDED_C_LIB	1	/* include declarations for C extensions */
 #endif /* !defined(_ADDED_C_LIB) */

 #if defined(_HAS_TR1)

 #elif !_IS_EMBEDDED && (1310 <= _MSC_VER || __EDG__ || 3 <= __GNUC__) && defined(__cplusplus)
  #define _HAS_TR1	1	/* enable TR1 */

 #else /* _HAS_TR1 */
  #define _HAS_TR1	0	/* disable TR1 */
 #endif /* _HAS_TR1 */

 #if defined(_HAS_CPP0X)

 #elif (1400 <= _MSC_VER || __EDG__ || __GNUC__) && (defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103)
  #define _HAS_CPP0X	1	/* enable C++0X changes */

 #if _HAS_CPP0X

 #else /* _HAS_CPP0X */
  #undef _HAS_CPP0X	/* don't ask */
  #define _HAS_CPP0X	0	/* enable C++0X changes */
 #endif /* _HAS_CPP0X */

 #else /* !defined(_HAS_CPP0X) */
  #define _HAS_CPP0X	0	/* disable C++0X changes */
 #endif /* !defined(_HAS_CPP0X) */

 #if defined(_HAS_C9X)

 #elif _C99 || _HAS_TR1
  #define _HAS_C9X      1

 #else /* !defined(_HAS_C9X) */
  #define _HAS_C9X      0
 #endif /* !defined(_HAS_C9X) */

 #ifndef _MULTI_THREAD

  #ifdef __CYGWIN__
   #define _MULTI_THREAD	0	/* Cygwin has dummy thread library */

  #else /* __CYGWIN__ */

   #if defined(_NO_MT) || defined(_DEBUG) && 1310 == _MSC_VER
    #define _MULTI_THREAD	0	/* 0 for no thread locks */

   #else /* defined(_NO_MT) || defined(_DEBUG) */
    #define _MULTI_THREAD	1
   #endif /* defined(_NO_MT) || defined(_DEBUG) */

  #endif /* __CYGWIN__ */
 #endif /* _MULTI_THREAD */

 #if defined(_HAS_CHAR16_T_LANGUAGE_SUPPORT)

 #elif _HAS_CPP0X && (_CLANG || _GCC44 || 403 <= __EDG_VERSION__)
  #define _HAS_CHAR16_T_LANGUAGE_SUPPORT	1	/* char16/32_t are keywords */

 #else /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */
  #define _HAS_CHAR16_T_LANGUAGE_SUPPORT	0	/* char16/32_t not keywords */
 #endif /* _HAS_CHAR16_T_LANGUAGE_SUPPORT */

 #if !defined(_HAS_FIXED_POINT)
  #define _HAS_FIXED_POINT	0	/* enable fixed-point extensions */
 #endif /* !defined(_HAS_FIXED_POINT) */

 #if !defined(_HAS_NOEXCEPT)

  #if _HAS_CPP0X
   #define _HAS_NOEXCEPT	1

  #else /* _HAS_CPP0X */
   #define _HAS_NOEXCEPT	0
  #endif /* _HAS_CPP0X */

 #endif /* !defined(_HAS_NOEXCEPT) */

 #if _HAS_NOEXCEPT == 0 || !defined(__cplusplus)
  #define _NOEXCEPT

 #else /* _HAS_NOEXCEPT == 0, etc. */
  #define _NOEXCEPT			noexcept
 #endif /* _HAS_NOEXCEPT == 0, etc. */

 #if !defined(_USE_EXISTING_SYSTEM_NAMES)
  #define _USE_EXISTING_SYSTEM_NAMES	1	/* _Open => open, etc. */
 #endif /* !defined(_USE_EXISTING_SYSTEM_NAMES) */

 #if __STDC_WANT_SAFER_LIB__
  #define __STDC_SAFER_LIB__	200510L
 #endif /* __STDC_WANT_SAFER_LIB__ */

 #if defined(__cplusplus)
  #define _EXTERN_C			extern "C" {
  #define _END_EXTERN_C		}
 #else
  #define _EXTERN_C
  #define _END_EXTERN_C
 #endif
 #define __BEGIN_DECLS		_EXTERN_C
 #define __END_DECLS		_END_EXTERN_C
 #define _C_LIB_DECL		_EXTERN_C
 #define _END_C_LIB_DECL	_END_EXTERN_C

 /* for compatibility with code currently using this */
 #define _CSTD

 #ifndef _NO_LOCALES
  #define _NO_LOCALES	0	/* define as 1 to disable named locales */
 #endif /* _NO_LOCALES */

 #ifndef _HAS_OPENCL
  #define _HAS_OPENCL	0
 #endif /* _HAS_OPENCL */

 #if defined(__OXILI_CLRUNTIME)	/* compiler test */
 typedef char *va_list;	/* Oxili does not allow variable arguments */

#define _PASTE(a, b)	__cl__internal__##a##b
#define _STATIC_CONST	static const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST	/* extern */ const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST_DECL	extern const \
	__attribute__((address_space(2)))
#define _EXTERN_CONST_DEF	/* extern */ const \
	__attribute__((address_space(2)))

void *__attribute__((overloadable)) __qcom_memcpy_DW(void *dest,
	const __attribute__((address_space(2))) void *src, int num);
void *__attribute__((overloadable)) __qcom_memcpy_DW(void *dest,
	const void *src, int num);

 #else /* defined(__OXILI_CLRUNTIME) */
#ifndef __QNXNTO__
#include <stdarg.h>
#endif

#define _PASTE(a, b)	a##b
#define _STATIC_CONST	static const

  #if !defined(_EXTERN_CONST)
#define _EXTERN_CONST	/* extern */ const
#define _EXTERN_CONST_DECL	extern const

   #if defined(__cplusplus)
#define _EXTERN_CONST_DEF	extern const

   #else /* defined(__cplusplus) */
#define _EXTERN_CONST_DEF	const
   #endif /* defined(__cplusplus) */

  #endif /* defined(_EXTERN_CONST) */
 #endif /* defined(__OXILI_CLRUNTIME) */

		/* VC++ COMPILER PARAMETERS */
#define _CDECL
#define _THROW_N(x, y)	_THROW_NCEE(x, y)

 #if defined(_WIN32_C_LIB)
  #ifndef _VA_LIST_DEFINED

   #if defined(__BORLANDC__)

   #elif defined(_M_ALPHA)
typedef struct
	{	/* define va_list for Alpha */
	char *a0;
	int offset;
	} va_list;

   #else /* defined(_M_ALPHA) */
typedef char *va_list;
   #endif /* defined(_M_ALPHA) */

   #define _VA_LIST_DEFINED
  #endif /* _VA_LIST_DEFINED */

 #endif /* defined(_WIN32_C_LIB) */

 #ifdef __NO_LONG_LONG

 #elif defined(_MSC_VER)
  #define _LONGLONG	__int64
  #define _ULONGLONG	unsigned __int64
  #define _LLONG_MAX	0x7fffffffffffffff
  #define _ULLONG_MAX	0xffffffffffffffff

 #else /* defined(__NO_LONG_LONG) && !defined (_MSC_VER) */
  #define _LONGLONG	long long
  #define _ULONGLONG	unsigned long long
  #define _LLONG_MAX	0x7fffffffffffffffLL
  #define _ULLONG_MAX	0xffffffffffffffffULL
 #endif /* __NO_LONG_LONG */

		/* MAKE MINGW LOOK LIKE WIN32 HEREAFTER */

 #if defined(__MINGW32__) || defined(__CYGWIN__)
  #define _WIN32_C_LIB	1
 #endif /* defined(__MINGW32__) etc. */

 #if _WIN32_C_LIB && !defined(__BORLANDC__)
  #undef _HAS_POSIX_C_LIB

  #if !defined(_SIZE_T) && !defined(_SIZET) \
	&& !defined(_BSD_SIZE_T_DEFINED_) \
	&& !defined(_SIZE_T_DEFINED)
   #define _SIZE_T
   #define _SIZET
   #define _BSD_SIZE_T_DEFINED_
   #define _STD_USING_SIZE_T
   #define _SIZE_T_DEFINED

typedef _Sizet size_t;

   #ifdef __cplusplus
namespace _Dinkum_std {
	using ::size_t;
	}
namespace _Dinkum_std_c {
	using ::size_t;
	}
   #endif /* __cplusplus */

  #endif /* !defined(_SIZE_T) etc. */

  #if !defined(_WCHAR_T_DEFINED)
   #define _WCHAR_T_DEFINED
   #define _WCHAR_T_
   #undef __need_wchar_t

   #ifndef __cplusplus
typedef unsigned short wchar_t;
   #endif /* __cplusplus */

  #endif /* !defined(_WCHAR_T) etc. */
 #endif /* _WIN32_C_LIB */

		/* FLOATING-POINT PROPERTIES */
#define _DBIAS	0x3fe	/* IEEE format double and float */
#define _DOFF	4
#define _FBIAS	0x7e
#define _FOFF	7

		/* INTEGER PROPERTIES */
#define _BITS_BYTE	8
#define _C2			1	/* 0 if not 2's complement */
#define _MBMAX		8	/* MB_LEN_MAX */
#define _ILONG		1	/* 0 if 16-bit int */

 #if defined(__s390__) || defined(__CHAR_UNSIGNED__) \
	|| defined(_CHAR_UNSIGNED)
  #define _CSIGN	0	/* 0 if char is not signed */

 #else /* defined(__s390__) etc. */
  #define _CSIGN	1
 #endif /* defined(__s390__) etc. */

#define _MAX_EXP_DIG	8	/* for parsing numerics */
#define _MAX_INT_DIG	32
#define _MAX_SIG_DIG	48

                /* wchar_t AND wint_t PROPERTIES */

 #if defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) \
        || defined (_MSL_WCHAR_T_TYPE)
  #define _WCHART
 #endif /* defined(_WCHAR_T) || defined(_WCHAR_T_DEFINED) */

 #if defined(_WINT_T)
  #define _WINTT
 #endif /* _WINT_T */

 #ifdef __cplusplus
  #define _WCHART
typedef wchar_t _Wchart;
 #endif /* __cplusplus */

		/* stdio PROPERTIES */
#define _FNAMAX	260
#define _FOPMAX	20
#define _TNAMAX	16

  #define _FD_NO(str) ((str)->_Handle)
 #define _FD_VALID(fd)	(0 <= (fd))	/* fd is signed integer */
 #define _FD_INVALID	(-1)
 #define _SYSCH(x)	x

#ifndef _SYSCH_T
typedef char _Sysch_t;
#define _SYSCH_T
#endif

		/* STORAGE ALIGNMENT PROPERTIES */

 #if defined(_LP64) || defined(__x86_64)	/* compiler test */
  #define _MEMBND	4U /* 16-byte boundaries (2^^4) */

 #else /* defined(_LP64) etc. */
  #define _MEMBND	3U /* eight-byte boundaries (2^^3) */
 #endif /* defined(_LP64) etc. */

		/* time PROPERTIES */
#define _CPS	1000
#define _TBIAS	((70 * 365LU + 17) * 86400)

		/* uchar PROPERTIES */
 #if !_HAS_CHAR16_T_LANGUAGE_SUPPORT	// sic
typedef unsigned short char16_t;
typedef unsigned int char32_t;
 #endif /* !_HAS_CHAR16_T_LANGUAGE_SUPPORT */

		/* MULTITHREAD PROPERTIES */

 #if _MULTI_THREAD
 #define _BEGIN_LOCK(kind)	{_Lockit _Lock(kind);
 #define _END_LOCK()		}

_EXTERN_C
void _Locksyslock(int __lockno);
void _Unlocksyslock(int __lockno);
_END_EXTERN_C

 #else /* _MULTI_THREAD */
 #define _BEGIN_LOCK(kind)	{
 #define _END_LOCK()		}

  #define _Locksyslock(x)	(void)0
  #define _Unlocksyslock(x)	(void)0
 #endif /* _MULTI_THREAD */

		/* LOCK MACROS */
 #define _LOCK_LOCALE	0
 #define _LOCK_MALLOC	1
 #define _LOCK_STREAM	2
 #define _LOCK_DEBUG	3
 #define _MAX_LOCK		4	/* one more than highest lock number */

#define _STRINGIZEX(x)	#x
#define _STRINGIZE(x)	_STRINGIZEX(x)

#endif /* _YVALS */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/yvals.h $ $Rev: 810364 $")
#endif
