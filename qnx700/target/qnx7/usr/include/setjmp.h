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

#ifndef _SETJMP_H_INCLUDED
#define _SETJMP_H_INCLUDED
#define _SETJMP_H_DECLARED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__clang__)
#pragma clang system_header
#endif

#include <_pack64.h>

__BEGIN_DECLS

typedef struct _jmp_buf {
	union {
		unsigned int	__savearea[__JMPBUFSIZE];
		__jmpbufalign	__alignment__;
	}				__jmpbuf_un;
	int				__flg;
	long			__msk[2];
	void *			__aux_ptr;
} jmp_buf[1];

extern int _setjmp(jmp_buf __env);
extern void _longjmp(jmp_buf __env, int __val) __attribute__((__noreturn__));

extern void longjmp(jmp_buf __env, int __val) __attribute__((__noreturn__));

#if defined(__EXT_POSIX1_200112)
/*
 * POSIX requires a setjmp() function prototype but suppressing the macro
 * definition or defining an external identifier with the name setjmp
 * will cause undefined behaviour
 */
extern int setjmp(jmp_buf);
extern int sigsetjmp(jmp_buf __env, int __msk);
#endif

typedef jmp_buf sigjmp_buf;
extern void __sigjmp_prolog(sigjmp_buf __env, int __msk);
extern void siglongjmp(sigjmp_buf __env, int __val) __attribute__((__noreturn__));

#define sigsetjmp(__env, __msk)	(__sigjmp_prolog((__env), (__msk)), _setjmp(__env))
#define setjmp(__env)			sigsetjmp(__env, 1)
#define longjmp(__env, __val)	siglongjmp((__env), (__val))

#if defined(__PPC__)							\
	|| defined(__MIPS__)						\
	|| defined(__SH__)							\
	|| defined(__ARM__)							\
	|| defined(__X86__)							\
	|| defined(__X86_64__)						\
	|| defined(__aarch64__)
/*(no-op)*/
#else
# error not configured for system
#endif

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/setjmp.h $ $Rev: 806926 $")
#endif
