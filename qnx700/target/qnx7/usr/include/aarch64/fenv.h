/*-
 * Copyright (c) 2004-2005 David Schultz <das@FreeBSD.ORG>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef	_FENV_H_
#define	_FENV_H_

#include <yvals.h>

#ifndef	__fenv_static
#define	__fenv_static	static
#endif

typedef	_Uint64t	fenv_t;
typedef	_Uint64t	fexcept_t;

/* Exception flags */
#define	FE_INVALID	0x00000001
#define	FE_DIVBYZERO	0x00000002
#define	FE_OVERFLOW	0x00000004
#define	FE_UNDERFLOW	0x00000008
#define	FE_INEXACT	0x00000010
#define	FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT | \
			 FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

/*
 * Rounding modes
 *
 * We can't just use the hardware bit values here, because that would
 * make FE_UPWARD and FE_DOWNWARD negative, which is not allowed.
 */
#define	FE_TONEAREST	0x0
#define	FE_UPWARD	0x1
#define	FE_DOWNWARD	0x2
#define	FE_TOWARDZERO	0x3
#define	_ROUND_MASK	(FE_TONEAREST | FE_DOWNWARD | \
			 FE_UPWARD | FE_TOWARDZERO)
#define	_ROUND_SHIFT	22

__BEGIN_DECLS

/* Default floating-point environment */
extern const fenv_t	__fe_dfl_env;
#define	FE_DFL_ENV	(&__fe_dfl_env)

/* We need to be able to map status flag positions to mask flag positions */
#define _FPUSW_SHIFT	8
#define	_ENABLE_MASK	((_Uint64t)FE_ALL_EXCEPT << _FPUSW_SHIFT)

#define	__mrs_fpcr(__r)	({ __asm __volatile("mrs %0, fpcr" : "=r" (__r)); })
#define	__msr_fpcr(__r)	({ __asm __volatile("msr fpcr, %0" : : "r" (__r)); })

#define	__mrs_fpsr(__r)	({ __asm __volatile("mrs %0, fpsr" : "=r" (__r)); })
#define	__msr_fpsr(__r)	({ __asm __volatile("msr fpsr, %0" : : "r" (__r)); })

__fenv_static __inline__ int __attribute__((__unused__))
feclearexcept(const int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	__r &= (fexcept_t)~__excepts;
	__msr_fpsr(__r);
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
fegetexceptflag(fexcept_t * const __flagp, const int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	*__flagp = __r & (fexcept_t)__excepts;
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
fesetexceptflag(const fexcept_t * const __flagp, const int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	__r &= (fexcept_t)~__excepts;
	__r |= *__flagp & (fexcept_t)__excepts;
	__msr_fpsr(__r);
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
feraiseexcept(const int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	__r |= (fexcept_t)__excepts;
	__msr_fpsr(__r);
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
fetestexcept(const int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	return (__r & (fexcept_t)__excepts);
}

__fenv_static __inline__ int __attribute__((__unused__))
fegetround(void)
{
	fenv_t __r;

	__mrs_fpcr(__r);
	return ((__r >> _ROUND_SHIFT) & (fexcept_t)_ROUND_MASK);
}

__fenv_static __inline__ int __attribute__((__unused__))
fesetround(const int __round)
{
	fenv_t __r;

	if (__round & ~_ROUND_MASK) {
		return (-1);
	}
	__mrs_fpcr(__r);
	__r &= (fexcept_t)~(_ROUND_MASK << _ROUND_SHIFT);
	__r |= (fexcept_t)(__round << _ROUND_SHIFT);
	__msr_fpcr(__r);
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
fegetenv(fenv_t * const __envp)
{
	fenv_t __r;

	__mrs_fpcr(__r);
	*__envp = __r & _ENABLE_MASK;

	__mrs_fpsr(__r);
	*__envp |= __r & (fexcept_t)(FE_ALL_EXCEPT | (_ROUND_MASK << _ROUND_SHIFT));

	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
feholdexcept(fenv_t * const __envp)
{
	fenv_t __r;

	__mrs_fpcr(__r);
	*__envp = __r & _ENABLE_MASK;
	__r &= ~(_ENABLE_MASK);
	__msr_fpcr(__r);

	__mrs_fpsr(__r);
	*__envp |= __r & (fexcept_t)(FE_ALL_EXCEPT | (_ROUND_MASK << _ROUND_SHIFT));
	__r &= ~(_ENABLE_MASK);
	__msr_fpsr(__r);
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
fesetenv(const fenv_t *__envp)
{

	__msr_fpcr((*__envp) & _ENABLE_MASK);
	__msr_fpsr((*__envp) & (fexcept_t)(FE_ALL_EXCEPT | (_ROUND_MASK << _ROUND_SHIFT)));
	return (0);
}

__fenv_static __inline__ int __attribute__((__unused__))
feupdateenv(const fenv_t * const __envp)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	fesetenv(__envp);
	feraiseexcept((int)(__r & (fexcept_t)FE_ALL_EXCEPT));
	return (0);
}

#if defined(__EXT_BSD) || defined(__EXT_QNX)

/* We currently provide no external definitions of the functions below. */

static __inline__ int __attribute__((__unused__))
feenableexcept(const int __mask)
{
	fenv_t __old_r, __new_r;

	__mrs_fpcr(__old_r);
	__new_r = __old_r | (fexcept_t)((__mask & FE_ALL_EXCEPT) << _FPUSW_SHIFT);
	__msr_fpcr(__new_r);
	return ((__old_r >> _FPUSW_SHIFT) & (fexcept_t)FE_ALL_EXCEPT);
}

static __inline__ int __attribute__((__unused__))
fedisableexcept(const int __mask)
{
	fenv_t __old_r, __new_r;

	__mrs_fpcr(__old_r);
	__new_r = __old_r & (fexcept_t)~((__mask & FE_ALL_EXCEPT) << _FPUSW_SHIFT);
	__msr_fpcr(__new_r);
	return ((__old_r >> _FPUSW_SHIFT) & (fexcept_t)FE_ALL_EXCEPT);
}

static __inline__ int __attribute__((__unused__))
fegetexcept(void)
{
	fenv_t __r;

	__mrs_fpcr(__r);
	return ((__r & _ENABLE_MASK) >> _FPUSW_SHIFT);
}

#endif /* defined(__EXT_BSD) || defined(__EXT_QNX) */

__END_DECLS

#endif	/* !_FENV_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/m/dist/freebsd/lib/msun/aarch64/fenv.h $ $Rev: 814256 $")
#endif
