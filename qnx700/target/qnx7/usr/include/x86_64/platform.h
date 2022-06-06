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
 *  x86_64/platform.h
 *

 */

#ifndef _X86_64_PLATFORM_H_INCLUDED
#define _X86_64_PLATFORM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error x86_64/platform.h should not be included directly.
#endif

#if defined(__QNXNTO__)

#define __JMPBUFSIZE	(8*2)	/* setjmp uses unsigneds, we need longs */
typedef	unsigned long		__jmpbufalign;


#else
#error Not configured for target
#endif



#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/x86_64/platform.h $ $Rev: 780674 $")
#endif
