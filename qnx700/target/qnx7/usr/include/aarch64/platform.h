/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
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
 *  aarch64/platform.h
 *
 */

#ifndef _AARCH_PLATFORM_H_INCLUDED
#define _AARCH_PLATFORM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error aarch64/platform.h should not be included directly.
#endif

#if defined(__QNXNTO__)

#define __JMPBUFSIZE 	(13*2)		/* _jmp_buf uses unsigned array */
typedef unsigned long __jmpbufalign;

#else
#error Not configured for target
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/aarch64/platform.h $ $Rev: 780423 $")
#endif
