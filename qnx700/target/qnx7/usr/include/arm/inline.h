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
 *  arm/inline.h
 *

 */

#ifndef _ARM_INLINE_H_INCLUDED
#define _ARM_INLINE_H_INCLUDED

/*
 *  some handy pragma's for low-level work:
 */

#ifndef _ARM_INOUT_INCLUDED
#include <arm/inout.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

/* ldsp() - set the current stack pointer */
static __inline__ void ldsp(_Uintptrt __sp) {
	__asm__ __volatile__("mov	sp, %0" :: "r" (__sp));
}
#define ldesp(__sp)	ldsp(__sp)	/* backward compat */

/* rdsp() - obtain the current stack pointer */
static __inline__ _Uintptrt rdsp(void) {
	_Uintptrt sp;
	__asm__ ("mov	%0, sp" : "=r" (sp));
	return sp;
}

/*
 * -------------------------------------------------------------------------
 * Barriers
 * -------------------------------------------------------------------------
 */

static __inline__ void __attribute__((__unused__))
dmb(void)
{
	__asm__ __volatile__("dmb	sy" : : : "memory");
}

static __inline__ void __attribute__((__unused__))
dsb(void)
{
	__asm__ __volatile__("dsb	sy" : : : "memory");
}

static __inline__ void __attribute__((__unused__))
isb(void)
{
	__asm__ __volatile__("isb" : : : "memory");
}

/*
 * -------------------------------------------------------------------------
 * System registers
 * -------------------------------------------------------------------------
 */

static __inline__ unsigned __attribute__((__unused__))
arm_midr_get(void)
{
	unsigned	midr;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c0, 0" : "=r"(midr));
	return midr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_mpidr_get(void)
{
	unsigned	mpidr;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c0, 5" : "=r"(mpidr));
	return mpidr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_sctlr_get(void)
{
	unsigned	sctlr;
	__asm__ __volatile__("mrc	p15, 0, %0, c1, c0, 0" : "=r"(sctlr));
	return sctlr;
}

static __inline__ void __attribute__((__unused__))
arm_sctlr_set(unsigned sctlr)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c1, c0, 0" : : "r"(sctlr));
}

static __inline__ unsigned __attribute__((__unused__))
arm_actlr_get(void)
{
	unsigned	actlr;
	__asm__ __volatile__("mrc	p15, 0, %0, c1, c0, 1" : "=r"(actlr));
	return actlr;
}

static __inline__ void __attribute__((__unused__))
arm_actlr_set(unsigned val)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c1, c0, 1" : : "r"(val));
}

static __inline__ unsigned __attribute__((__unused__))
arm_clidr_get(void)
{
	unsigned	clidr;
	__asm__ __volatile__("mrc	p15, 1, %0, c0, c0, 1" : "=r"(clidr));
	return clidr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_ctr_get(void)
{
	unsigned	ctr;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c0, 1" : "=r"(ctr));
	return ctr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_cpacr_get(void)
{
	unsigned	cpacr;
	__asm__ __volatile__("mrc	p15, 0, %0, c1, c0, 2" : "=r"(cpacr));
	return cpacr;
}

static __inline__ void __attribute__((__unused__))
arm_cpacr_set(unsigned val)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c1, c0, 2" : : "r"(val));
}

static __inline__ unsigned __attribute__((__unused__))
arm_nsacr_get(void)
{
	unsigned	nsacr;
	__asm__ __volatile__("mrc	p15, 0, %0, c1, c1, 2" : "=r"(nsacr));
	return nsacr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_mmfr0_get(void)
{
	unsigned	id;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c1, 4" : "=r"(id));
	return id;
}

static __inline__ unsigned __attribute__((__unused__))
arm_mmfr3_get(void)
{
	unsigned	id;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c1, 7" : "=r"(id));
	return id;
}

static __inline__ unsigned __attribute__((__unused__))
arm_isar0_get(void)
{
	unsigned	id;
	__asm__ __volatile__("mrc	p15, 0, %0, c0, c2, 0" : "=r"(id));
	return id;
}

static __inline__ unsigned __attribute__((__unused__))
arm_mvfr0_get(void)
{
	unsigned	mvfr0;
	__asm__ __volatile__("vmrs	%0, mvfr0" : "=r"(mvfr0));
	return mvfr0;
}

static __inline__ unsigned __attribute__((__unused__))
arm_mvfr1_get(void)
{
	unsigned	mvfr1;
	__asm__ __volatile__("vmrs	%0, mvfr1" : "=r"(mvfr1));
	return mvfr1;
}

static __inline__ unsigned __attribute__((__unused__))
arm_fpsid_get(void)
{
	unsigned	fpsid;
	__asm__ __volatile__("vmrs	%0, fpsid" : "=r"(fpsid));
	return fpsid;
}

static __inline__ unsigned __attribute__((__unused__))
arm_ttbcr_get()
{
	unsigned	ttbcr;
	__asm__ __volatile__("mrc	p15, 0, %0, c2, c0, 2" : "=r"(ttbcr));
	return ttbcr;
}

static __inline__ unsigned __attribute__((__unused__))
arm_ttbr0_get()
{
	unsigned	ttbr0;
	__asm__ __volatile__("mrc	p15, 0, %0, c2, c0, 0" : "=r"(ttbr0));
	return ttbr0;
}

static __inline__ unsigned __attribute__((__unused__))
arm_ttbr1_get()
{
	unsigned	ttbr1;
	__asm__ __volatile__("mrc	p15, 0, %0, c2, c0, 1" : "=r"(ttbr1));
	return ttbr1;
}

static __inline__ void __attribute__((__unused__))
arm_ttbr0_set(unsigned ttbr0)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c2, c0, 0" : : "r"(ttbr0));
}

static __inline__ unsigned __attribute__((__unused__))
arm_contextidr_get()
{
	unsigned	idr;
	__asm__ __volatile__("mrc	p15, 0, %0, c13, c0, 1" : "=r"(idr));
	return idr;
}

static __inline__ void __attribute__((__unused__))
arm_contextidr_set(unsigned idr)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c13, c0, 1" : : "r"(idr));
}

static __inline__ _Uint64t __attribute__((__unused__))
lpae_ttbr1_get()
{
	unsigned	lo, hi;
	__asm__ __volatile__("mrrc	p15, 1, %0, %1, c2" : "=r"(lo), "=r"(hi));
	return ((_Uint64t)hi << 32) | lo;
}

static __inline__ _Uint64t __attribute__((__unused__))
lpae_ttbr0_get()
{
	unsigned	lo, hi;
	__asm__ __volatile__("mrrc	p15, 0, %0, %1, c2" : "=r"(lo), "=r"(hi));
	return ((_Uint64t)hi << 32) | lo;
}

static __inline__ void __attribute__((__unused__))
lpae_ttbr0_set(_Uint64t ttbr0)
{
	unsigned	lo = (unsigned)ttbr0;
	unsigned	hi = (unsigned)(ttbr0 >> 32);
	__asm__ __volatile__("mcrr	p15, 0, %0, %1, c2" : : "r"(lo), "r"(hi));
}

/*
 * -------------------------------------------------------------------------
 * TLB Maintenance
 * -------------------------------------------------------------------------
 */

static __inline__ void __attribute__((__unused__))
tlbimva(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c7, 1" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
tlbimvais(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c3, 1" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
tlbimvaa(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c7, 3" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
tlbimvaais(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c3, 3" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
tlbiasid(unsigned asid)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c7, 2" : : "r"(asid));
}

static __inline__ void __attribute__((__unused__))
tlbiasidis(unsigned asid)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c3, 2" : : "r"(asid));
}

static __inline__ void __attribute__((__unused__))
tlbiall(void)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c7, 0" : : "r"(0));
}

static __inline__ void __attribute__((__unused__))
tlbiallis(void)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c8, c3, 0" : : "r"(0));
}

/*
 * -------------------------------------------------------------------------
 * Cache Maintenance
 * -------------------------------------------------------------------------
 */

static __inline__ void __attribute__((__unused__))
bpiall()
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c5, 6" : : "r"(0));
}

static __inline__ void __attribute__((__unused__))
bpiallis()
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c1, 6" : : "r"(0));
}

static __inline__ void __attribute__((__unused__))
iciallu(void)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c5, 0" : : "r"(0));
}

static __inline__ void __attribute__((__unused__))
icialluis(void)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c1, 1" : : "r"(0));
}

static __inline__ void __attribute__((__unused__))
icimvau(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c5, 1" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
dccmvac(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c10, 1" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
dccmvau(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c11, 1" : : "r"(va));
}

static __inline__ void __attribute__((__unused__))
dccimvac(unsigned va)
{
	__asm__ __volatile__("mcr	p15, 0, %0, c7, c14, 1" : : "r"(va));
}

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/arm/inline.h $ $Rev: 815801 $")
#endif
