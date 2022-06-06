/*
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
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
 *  aarch64/cache.h
 */
 
#ifndef _AARCH64_CACHE_H_INCLUDED
#define _AARCH64_CACHE_H_INCLUDED

#ifndef __CACHE_H_INCLUDED
#include <sys/cache.h>
#endif

#define __CPU_CACHE_FLUSH

static __inline__ void __attribute__((__unused__))
__cpu_cache_flush(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	uint64_t	linesize;
	uintptr_t	__dst;
	int			__nlines;

	/*
	 * Calculate minimum line size for dcache maintenance
	 */
	__asm__ __volatile__("mrs	%0, ctr_el0" : "=r"(linesize));
	linesize = 4 << ((linesize >> 16) & 0xf);

	__dst = (uintptr_t)vaddr & ~(linesize-1);
	__nlines = (((uintptr_t)vaddr + len + linesize-1)-__dst)/linesize;

	while(__nlines) {	
		/*
		 * Clean to PoC
		 */
		__asm__ __volatile__( "dc	cvac, %0;" : : "r" (__dst));
		__dst += linesize;
		__nlines--;
	}
	__asm__ __volatile__("dsb	sy");
}

#define __CPU_CACHE_INVAL

static __inline__ void __attribute__((__unused__))
__cpu_cache_inval(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	uint64_t	linesize;
	uintptr_t	__dst;
	int			__nlines;

	/*
	 * Calculate minimum line size for dcache maintenance
	 */
	__asm__ __volatile__("mrs	%0, ctr_el0" : "=r"(linesize));
	linesize = 4 << ((linesize >> 16) & 0xf);

	__dst = (uintptr_t)vaddr & ~(linesize-1);
	__nlines = (((uintptr_t)vaddr + len + linesize-1)-__dst)/linesize;

	while(__nlines) {	
		/*
		 * Clean and invalidate to PoC
		 */
		__asm__ __volatile__( "dc	civac, %0;" : : "r" (__dst));
		__dst += linesize;
		__nlines--;
	}
	__asm__ __volatile__("dsb	sy");
}

#endif /* _AARCH64_CACHE_H_INCLUDED */



#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/cache/public/aarch64/cache.h $ $Rev: 781268 $")
#endif
