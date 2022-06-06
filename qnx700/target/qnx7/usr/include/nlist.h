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





#ifndef _NLIST_H_INCLUDED
#define _NLIST_H_INCLUDED

struct nlist {
	char		*n_name;
	unsigned	n_type;
	unsigned long	n_value;
	unsigned	n_reserved;
};

#ifdef _KERNEL
/* The old layout of struct nlist before we became more standard */
struct nlist_old {
	char	n_name[12];
	long	n_value;
	int	n_type;
};
#endif


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/socket/public/nlist.h $ $Rev: 680336 $")
#endif
