/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
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

#ifndef _MATH_H_INCLUDED
#define _MATH_H_INCLUDED

#include <yvals.h>

_C_LIB_DECL
#include <_pack64.h>

#if defined( __EXT_XOPEN_EX) || defined(__EXT_POSIX1_198808)
#define M_E			2.7182818284590452354	/* e */
#define M_LOG2E		1.4426950408889634074	/* log 2e */
#define M_LOG10E	0.43429448190325182765	/* log 10e */
#define M_LN2		0.69314718055994530942	/* log e2 */
#define M_LN10		2.30258509299404568402	/* log e10 */
#define M_PI		3.14159265358979323846	/* pi */
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#define M_PI_4		0.78539816339744830962	/* pi/4 */
#define M_1_PI		0.31830988618379067154	/* 1/pi */
#define M_2_PI		0.63661977236758134308	/* 2/pi */
#define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */

#define MAXFLOAT	((float)3.40282346638528860e+38)
#endif

#define HUGE_VAL	__builtin_huge_val()

#if defined(_HAS_C9X) || defined(__EXT_POSIX1_200112)
#define HUGE_VALF	__builtin_huge_valf()
#define HUGE_VALL	__builtin_huge_vall()
#define INFINITY	__builtin_inff()
#define NAN			__builtin_nanf("")

#define FP_INFINITE		0x01
#define FP_NAN			0x02
#define FP_NORMAL		0x04
#define FP_SUBNORMAL	0x08
#define FP_ZERO			0x10

#define FP_ILOGB0	(-__INT_MAX__)
#define FP_ILOGBNAN	(__INT_MAX__)

#define MATH_ERRNO			1
#define MATH_ERREXCEPT		2
#define math_errhandling	MATH_ERREXCEPT

#define __fp_generic(x, fnf, fn, fnl)	\
  (sizeof(x) == sizeof(float) ? fnf(x) : \
   sizeof(x) == sizeof(double) ? fn(x) : \
   fnl(x))

#define fpclassify(x)	__fp_generic(x, __fpclassifyf, __fpclassifyd, __fpclassifyl)
#define isfinite(x)		__fp_generic(x, __isfinitef, __isfinite, __isfinitel)
#define isinf(x)		__fp_generic(x, __isinff, __isinf, __isinfl)
#define isnan(x)		__fp_generic(x, __inline_isnanf, __inline_isnan, __inline_isnanl)
#define isnormal(x)		__fp_generic(x, __isnormalf, __isnormal, __isnormall)
#define signbit(x)		__fp_generic(x, __signbitf, __signbit, __signbitl)

#define isgreater(x, y)			__builtin_isgreater((x), (y))
#define isgreaterequal(x, y)	__builtin_isgreaterequal((x), (y))
#define isless(x, y)			__builtin_isless((x), (y))
#define islessequal(x, y)		__builtin_islessequal((x), (y))
#define islessgreater(x, y)		__builtin_islessgreater((x), (y))
#define isunordered(x, y)		__builtin_isunordered((x), (y))

int __fpclassifyd(double);
int __fpclassifyf(float);
int __fpclassifyl(long double);
int __isfinitef(float);
int __isfinite(double);
int __isfinitel(long double);
int __isinff(float);
int __isinf(double);
int __isinfl(long double);
int __isnormalf(float);
int __isnormal(double);
int __isnormall(long double);
int __signbit(double);
int __signbitf(float);
int __signbitl(long double);

static __inline int
__inline_isnan(__const double __x)
{
    return (__x != __x);
}

static __inline int
__inline_isnanf(__const float __x)
{
    return (__x != __x);
}

static __inline int
__inline_isnanl(__const long double __x)
{
    return (__x != __x);
}

#if defined(__FLT_EVAL_METHOD__) && (__FLT_EVAL_METHOD__-0) == 0
typedef double double_t;
typedef float float_t;
#elif (__FLT_EVAL_METHOD__-0) == 1
typedef double double_t;
typedef double float_t;
#elif (__FLT_EVAL_METHOD__-0) == 2
typedef long double double_t;
typedef long double float_t;
#endif
#endif /* __EXT_ANSIC_199901 || __EXT_POSIX1_200112 */

#if defined( __EXT_XOPEN_EX) || defined(__EXT_POSIX1_198808) || defined(__EXT_BSD)
extern int signgam;
#endif

double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double cos(double);
double sin(double);
double tan(double);
double cosh(double);
double sinh(double);
double tanh(double);
double exp(double);
double frexp(double, int *);
double ldexp(double, int);
double log(double);
double log10(double);
double modf(double, double *);
double pow(double, double);
double sqrt(double);
double ceil(double);
double fabs(double);
double floor(double);
double fmod(double, double);

#if defined(__EXT_XOPEN_EX) || defined(__EXT_POSIX1_198808)
double j0(double);
double j1(double);
double jn(int, double);
double scalb(double, double);
double y0(double);
double y1(double);
double yn(int, double);
/* int (isnan)(double); */
#endif

#if defined(_HAS_C9X) || defined(__EXT_XOPEN_EX) || defined(__EXT_POSIX1_198808)
double acosh(double);
double asinh(double);
double atanh(double);
double cbrt(double);
double erf(double);
double erfc(double);
double expm1(double);
double hypot(double, double);
int ilogb(double);
double lgamma(double);
double log1p(double);
double logb(double);
double nextafter(double, double);
double remainder(double, double);
double rint(double);
#endif

#if defined(__EXT_BSD)
float j0f(float);
float j1f(float);
float jnf(int, float);
float y0f(float);
float y1f(float);
float ynf(int, float);
#endif

#if defined(__EXT_BSD) || defined(__EXT_QNX)
double lgamma_r(double, int *);
float lgammaf_r(float, int *);
long double lgammal_r(long double, int *);
#endif

#if defined(_HAS_C9X) || defined(__EXT_POSIX1_200112)
float acosf(float);
long double acosl(long double);
float asinf(float);
long double asinl(long double);
float atanf(float);
long double atanl(long double);
float atan2f(float, float);
long double atan2l(long double, long double);
float cosf(float);
long double cosl(long double);
float sinf(float);
long double sinl(long double);
float tanf(float);
long double tanl(long double);
float acoshf(float);
long double acoshl(long double);
float asinhf(float);
long double asinhl(long double);
float atanhf(float);
long double atanhl(long double);
float coshf(float);
long double coshl(long double);
float sinhf(float);
long double sinhl(long double);
float tanhf(float);
long double tanhl(long double);
float expf(float);
long double expl(long double);
double exp2(double);
float exp2f(float);
long double exp2l(long double);
float expm1f(float);
long double expm1l(long double);
float frexpf(float, int *);
long double frexpl(long double, int *);
int ilogbf(float);
int ilogbl(long double);
float ldexpf(float, int);
long double ldexpl(long double, int);
float logf(float);
long double logl(long double);
float log10f(float);
long double log10l(long double);
float log1pf(float);
long double log1pl(long double);
double log2(double);
float log2f(float);
long double log2l(long double);
float logbf(float);
long double logbl(long double);
float modff(float, float *);
long double modfl(long double, long double *);
double scalbn(double, int);
float scalbnf(float, int);
long double scalbnl(long double, int);
double scalbln(double, long int);
float scalblnf(float, long int);
long double scalblnl(long double, long int);
float cbrtf(float);
long double cbrtl(long double);
float fabsf(float);
long double fabsl(long double);
float hypotf(float, float);
long double hypotl(long double, long double);
float powf(float, float);
long double powl(long double, long double);
float sqrtf(float);
long double sqrtl(long double);
float erff(float);
long double erfl(long double);
float erfcf(float);
long double erfcl(long double);
float lgammaf(float);
long double lgammal(long double);
double tgamma(double);
float tgammaf(float);
long double tgammal(long double);
float ceilf(float);
long double ceill(long double);
float floorf(float);
long double floorl(long double);
double nearbyint(double);
float nearbyintf(float);
long double nearbyintl(long double);
float rintf(float);
long double rintl(long double);
long int lrint(double);
long int lrintf(float);
long int lrintl(long double);
long long int llrint(double);
long long int llrintf(float);
long long int llrintl(long double);
double round(double);
float roundf(float);
long double roundl(long double);
long int lround(double);
long int lroundf(float);
long int lroundl(long double);
long long int llround(double);
long long int llroundf(float);
long long int llroundl(long double);
double trunc(double);
float truncf(float);
long double truncl(long double);
float fmodf(float, float);
long double fmodl(long double, long double);
float remainderf(float, float);
long double remainderl(long double, long double);
double remquo(double, double, int *);
float remquof(float, float, int *);
long double remquol(long double, long double, int *);
double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);
double nan(const char *);
float nanf(const char *);
long double nanl(const char *);
float nextafterf(float, float);
long double nextafterl(long double, long double);
double nexttoward(double, long double);
float nexttowardf(float, long double);
long double nexttowardl(long double, long double);
double fdim(double, double);
float fdimf(float, float);
long double fdiml(long double, long double);
double fmax(double, double);
float fmaxf(float, float);
long double fmaxl(long double, long double);
double fmin(double, double);
float fminf(float, float);
long double fminl(long double, long double);
double fma(double, double, double);
float fmaf(float, float, float);
long double fmal(long double, long double, long double);
#endif

#if defined(__EXT_XOPEN_EX) || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE+0 < 200112) || defined(__EXT_UNIX_HIST)
double gamma(double) __attribute__((__const__,__deprecated__)); /* use lgamma */
#endif
#if defined(__EXT_BSD) || defined(__EXT_UNIX_HIST)
double gamma_r(double, int *) __attribute__((__const__,__deprecated__)); /* use lgamma_r */
float gammaf(float) __attribute__((__const__,__deprecated__)); /* use lgammaf */
float gammaf_r(float, int *) __attribute__((__const__,__deprecated__)); /* use lgammaf_r */
#endif

#if defined(__EXT_BSD) || defined(__EXT_UNIX_MISC)
double drem(double, double) __attribute__((__const__,__deprecated__)); /* use remainder */
float dremf(float, float) __attribute__((__const__,__deprecated__)); /* use remainder */
double significand(double) __attribute__((__const__,__deprecated__)); /* use scalbnf(x, -ilogbf(x)) */
float significandf(float) __attribute__((__const__,__deprecated__)); /* use scalbn(x, -ilogb(x)) */
int finite(double) __attribute__((__const__,__deprecated__)); /* use isfinite macro */
int finitef(float) __attribute__((__const__,__deprecated__)); /* use isfinite macro */
int isnanf(float) __attribute__((__const__,__deprecated__)); /* use isnan macro */
int isinff(float) __attribute__((__const__,__deprecated__)); /* use isinf macro */
float scalbf(float, float) __attribute__((__const__,__deprecated__)); /* use scalbn */
#endif

#include <_packpop.h>
_END_C_LIB_DECL

#endif /* _MATH_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/m/lib/public/math.h $ $Rev: 814221 $")
#endif
