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
 *  x86/string.h
 *
 * This file is for inline optimized string functions
 *

 */

#ifndef _X86_STRING_H_INCLUDED
#define _X86_STRING_H_INCLUDED

#ifndef _STRING_H_INCLUDED
#error x86/string.h should not be included directly.
#endif

#if (defined(__GNUC__) || defined(__INTEL_COMPILER)) && defined(__OPTIMIZE__)

#undef __HAVE_ARCH_MEMCPY
#undef __HAVE_ARCH_MEMCMP
#undef __HAVE_ARCH_MEMMOVE
#undef __HAVE_ARCH_MEMCHR
#undef __HAVE_ARCH_MEMSET
#undef __HAVE_ARCH_MEMSCAN

#undef __HAVE_ARCH_STRLEN
#undef __HAVE_ARCH_STRNLEN

#undef __HAVE_ARCH_STRCPY
#undef __HAVE_ARCH_STRNCPY

#undef __HAVE_ARCH_STRCAT
#undef __HAVE_ARCH_STRNCAT

#undef __HAVE_ARCH_STRCMP
#undef __HAVE_ARCH_STRNCMP

#undef __HAVE_ARCH_STRCHR
#undef __HAVE_ARCH_STRRCHR

#undef __HAVE_ARCH_STRTOK
#undef __HAVE_ARCH_STRSTR
#undef __HAVE_ARCH_STRSPN
#undef __HAVE_ARCH_STRCSPN
#undef __HAVE_ARCH_STRPBRK

#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/x86/string.h $ $Rev: 806926 $")
#endif
