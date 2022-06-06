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
 *  sys/auxv.h
 *

 *
 */
#ifndef __AUXV_H_INCLUDED
#define __AUXV_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

#include <_pack64.h>

typedef struct {
	int			a_type;
	union {
		int			a_val;
		_Uintptr32t	a_ptr;
		_Uintptr32t	a_fcn;
	}			a_un;
} auxv32_t;

typedef struct {
	int			a_type;
	union {
		_Int64t		a_val;
		_Uintptr64t	a_ptr;
		_Uintptr64t	a_fcn;
	}			a_un;
} auxv64_t;

typedef struct {
	int				a_type;
	union {
		long			a_val;
		void			*a_ptr;
		void			(*a_fcn)(void);
	} 				a_un;
} auxv_t;

enum _auxv_e_at {
	AT_NULL = 0,
	AT_IGNORE,
	AT_EXECFD,
	AT_PHDR,
	AT_PHENT,
	AT_PHNUM,
	AT_PAGESZ,
	AT_BASE,
	AT_FLAGS,
	AT_ENTRY,
#if defined(__X86__)
	AT_LIBPATH = 10,
	AT_FPHW,
	AT_INTP_DEVICE,		/* SCO Sys V ABI */
	AT_INTP_INODE,		/* SCO Sys V ABI */
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__PPC__)
	AT_DCACHEBSIZE = 10,
	AT_ICACHEBSIZE,
	AT_UCACHEBSIZE,
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__MIPS__)
	AT_NOTELF = 10,
	AT_UID,
	AT_EUID,
	AT_GID,
	AT_EGID,
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__SH__)
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__ARM__)
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__X86_64__)
	AT_NOTELF = 10,
	AT_UID,
	AT_EUID,
	AT_GID,
	AT_EGID,
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#elif defined(__aarch64__)
	AT_NOTELF = 10,
	AT_UID,
	AT_EUID,
	AT_GID,
	AT_EGID,
	AT_RANDOM = 43,		/* QNX Extension */
	AT_FREE_STACK = 44,	/* QNX Extension */
	AT_INTP_DEVICE = 45,/* QNX Extension */
	AT_INTP_INODE = 46, /* QNX Extension */
	AT_EXEFILE = 47,	/* QNX Extension */
	AT_LIBPATH = 48,	/* QNX Extension */
	AT_DATA = 49,		/* QNX Extension */
#endif
	AT_NUM
};

extern auxv_t		*_auxv;

#include <_packpop.h>

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/sys/auxv.h $ $Rev: 818563 $")
#endif
