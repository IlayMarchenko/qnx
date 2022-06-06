/*
 * $QNXLicenseC: 
 * Copyright 2014, QNX Software Systems.  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License"). You  
 * may not reproduce, modify or distribute this software except in  
 * compliance with the License. You may obtain a copy of the License  
 * at: http://www.apache.org/licenses/LICENSE-2.0  
 *  
 * Unless required by applicable law or agreed to in writing, software  
 * distributed under the License is distributed on an "AS IS" basis,  
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied. 
 * 
 * This file may contain contributions from others, either as  
 * contributors under the License or as licensors under other terms.   
 * Please review this entire file for other proprietary rights or license  
 * notices, as well as the QNX Development Suite License Guide at  
 * http://licensing.qnx.com/license-guide/ for other information. 
 * $ 
 */

/*
 * AArch64 MMU support
 */

#ifndef __AARCH64_MMU_H_INCLUDED
#define __AARCH64_MMU_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/*
 * Memory attributes that can be set by shm_ctl_special()
 */

#define	ARM_SHMCTL_SH		0x400u	/* shareability (if cacheable) */
#define	ARM_SHMCTL_SO		0x000u	/* strongly-ordered       (uncached) */
#define	ARM_SHMCTL_DEV		0x004u	/* shared device          (uncached) */
#define	ARM_SHMCTL_NC		0x040u	/* normal memory          (uncached) */
#define	ARM_SHMCTL_WT		0x008u	/* write-through          (cacheable) */
#define	ARM_SHMCTL_WB		0x00cu	/* write-back             (cacheable) */
#define	ARM_SHMCTL_WBWA		0x04cu	/* write-back/write-alloc (cacheable) */

/*
 * Access Permissions:
 *	00 - priv r/w, user n/a
 *	01 - priv r/w, user r/w
 *	10 - priv r/o, user n/a
 *	11 - priv r/o, user r/o
 */
#define	AARCH64_AP_MASK			3
#define	AARCH64_AP_RW			0
#define	AARCH64_AP_RO			2
#define	AARCH64_AP_USER			1

/*
 * Shareability:
 *	00 - non-shareable
 *	01 - UNPREDICTABLE
 *	10 - outer shareable
 *	11 - inner shareable
 */
#define	AARCH64_SH_NONE			0
#define	AARCH64_SH_OUTER		2
#define	AARCH64_SH_INNER		3

/*
 * Level 1 and 2 descriptors.
 *
 * If PTP_TYPE(ptp) == PTP_BLOCK, the attribute bits are identical to the
 * Level3 descriptor bits and specify the attributes for the block.
 *
 * If PTP_TYPE(ptp) == PTP_TABLE, the attribute bits specify hierarchical
 * control of access permissions in lower level tables.
 */
typedef _Uint64t	ptp_t;

#define	AARCH64_PTP_VALID		(1ULL << 0)
#define	AARCH64_PTP_TYPE(ptp)	((ptp) & 3UL)
#define	AARCH64_PTP_BLOCK		(1ULL << 0)
#define	AARCH64_PTP_TABLE		(3ULL << 0)
#define	AARCH64_PTP_PXNTable	(1ULL << 59)
#define	AARCH64_PTP_XNTable		(1ULL << 60)
#define	AARCH64_PTP_APTable(x)	((ptp_t)(x) << 61)
#define	AARCH64_PTP_NSTable		(1ULL << 63)

/*
 * Level 3 descriptors
 */
typedef	_Uint64t	pte_t;

#define	AARCH64_PTE_VALID		(3ULL << 0)
#define	AARCH64_PTE_ATTRINDX(x)	((pte_t)(x) << 2)
#define	AARCH64_PTE_NS			(1ULL << 5)
#define	AARCH64_PTE_AP(x)		((pte_t)(x) << 6)
#define	AARCH64_PTE_SH(x)		((pte_t)(x) << 8)
#define	AARCH64_PTE_AF			(1ULL << 10)
#define	AARCH64_PTE_nG			(1ULL << 11)
#define	AARCH64_PTE_CONTIG		(1ULL << 52)
#define	AARCH64_PTE_PXN			(1ULL << 53)
#define	AARCH64_PTE_XN			(1ULL << 54)
#define	AARCH64_PTE_UXN			(AARCH64_PTE_XN)
//use of the hw IGNORED bits as internal usage for bad page marker
#define	AARCH64_PTE_BAD		(1ULL << 55)
#define	AARCH64_PTP_INVALID	(1ULL << 56)

/*
 * Mask off ATTR/AP/SH bits
 */
#define	AARCH64_PTE_ATTR_BITS	(AARCH64_PTE_ATTRINDX(0b111))
#define	AARCH64_PTE_AP_BITS		(AARCH64_PTE_AP(0b11))
#define	AARCH64_PTE_SH_BITS		(AARCH64_PTE_SH(0b11))

/*
 * The startup program sets up MAIR_EL1 so that the AttrIndex[2:0] is
 * equivalent to ARMv7-A TEX[0]/C/B encodings.
 *
 * This provides backwards compatibility for shm_ctl_special() called by
 * legacy ARMv7-A code running in EL0 AArch32.
 *
 * Index  MAIR  ARMv8 meaning ARMv7 meaning
 * -----  ----  ------------- -------------
 *     0  0x00  device-nGnRnE strongly-ordered
 *     1  0x04  device-nGnRE  shared-device
 *     2  0xaa  normal-WTnWA  normal-WTnWA
 *     3  0xee  normal-WBnWA  normal-WBnWA
 *     4  0x44  normal-NC     normal-NC
 *     5  0x00  reserved      reserved
 *     6  0x00  impl defined  impl defined
 *     7  0xff  normal-WBWA   normal-WBWA
 */
#define	AARCH64_PTE_SODEV	(AARCH64_PTE_ATTRINDX(0))
#define	AARCH64_PTE_DEV		(AARCH64_PTE_ATTRINDX(1))
#define	AARCH64_PTE_WTnWA	(AARCH64_PTE_ATTRINDX(2))
#define	AARCH64_PTE_WBnWA	(AARCH64_PTE_ATTRINDX(3))
#define	AARCH64_PTE_NC		(AARCH64_PTE_ATTRINDX(4))
#define	AARCH64_PTE_RSVD5	(AARCH64_PTE_ATTRINDX(5))
#define	AARCH64_PTE_RSVD6	(AARCH64_PTE_ATTRINDX(6))
#define	AARCH64_PTE_WBWA	(AARCH64_PTE_ATTRINDX(7))

/*
 * Page Shareability
 */
#define	AARCH64_PTE_NSH		(AARCH64_PTE_SH(0))
#define	AARCH64_PTE_OSH		(AARCH64_PTE_SH(2))
#define	AARCH64_PTE_ISH		(AARCH64_PTE_SH(3))

/*
 * Page access permissions
 */
#define	AARCH64_PTE_KRO		(AARCH64_PTE_AP(AARCH64_AP_RO))
#define	AARCH64_PTE_KRW		(AARCH64_PTE_AP(AARCH64_AP_RW))
#define	AARCH64_PTE_URO		(AARCH64_PTE_AP(AARCH64_AP_RO|AARCH64_AP_USER))
#define	AARCH64_PTE_URW		(AARCH64_PTE_AP(AARCH64_AP_RW|AARCH64_AP_USER))

/*
 * TCR_EL1 configuration
 */
#define	AARCH64_TCR_EL1_TBI1		(1UL << 38)
#define	AARCH64_TCR_EL1_TBI0		(1UL << 37)
#define	AARCH64_TCR_EL1_AS			(1UL << 36)
#define	AARCH64_TCR_EL1_IPS(x)		((unsigned long)(x) << 32)
#define	AARCH64_TCR_EL1_TG1_4K		(0b10UL << 30)
#define	AARCH64_TCR_EL1_TG1_64K		(0b11UL << 30)
#define	AARCH64_TCR_EL1_SH1_NSH		(0b00UL << 28)
#define	AARCH64_TCR_EL1_SH1_OSH		(0b10UL << 28)
#define	AARCH64_TCR_EL1_SH1_ISH		(0b11UL << 28)
#define	AARCH64_TCR_EL1_ORGN1_NC	(0b00UL << 26)
#define	AARCH64_TCR_EL1_ORGN1_WBWA	(0b01UL << 26)
#define	AARCH64_TCR_EL1_ORGN1_WT	(0b10UL << 26)
#define	AARCH64_TCR_EL1_ORGN1_WBnWA	(0b11UL << 26)
#define	AARCH64_TCR_EL1_IRGN1_NC	(0b00UL << 24)
#define	AARCH64_TCR_EL1_IRGN1_WBWA	(0b01UL << 24)
#define	AARCH64_TCR_EL1_IRGN1_WT	(0b10UL << 24)
#define	AARCH64_TCR_EL1_IRGN1_WBnWA	(0b11UL << 24)
#define	AARCH64_TCR_EL1_EPD1		(1UL << 23)
#define	AARCH64_TCR_EL1_A1			(1UL << 22)
#define	AARCH64_TCR_EL1_T1SZ(n)		((unsigned long)(64 - (n)) << 16)
#define	AARCH64_TCR_EL1_TG0_4K		(0b00UL << 14)
#define	AARCH64_TCR_EL1_TG0_64K		(0b01UL << 14)
#define	AARCH64_TCR_EL1_SH0_NSH		(0b00UL << 12)
#define	AARCH64_TCR_EL1_SH0_OSH		(0b10UL << 12)
#define	AARCH64_TCR_EL1_SH0_ISH		(0b11UL << 12)
#define	AARCH64_TCR_EL1_ORGN0_NC	(0b00UL << 10)
#define	AARCH64_TCR_EL1_ORGN0_WBWA	(0b01UL << 10)
#define	AARCH64_TCR_EL1_ORGN0_WT	(0b10UL << 10)
#define	AARCH64_TCR_EL1_ORGN0_WBnWA	(0b11UL << 10)
#define	AARCH64_TCR_EL1_IRGN0_NC	(0b00UL << 8)
#define	AARCH64_TCR_EL1_IRGN0_WBWA	(0b01UL << 8)
#define	AARCH64_TCR_EL1_IRGN0_WT	(0b10UL << 8)
#define	AARCH64_TCR_EL1_IRGN0_WBnWA	(0b11UL << 8)
#define	AARCH64_TCR_EL1_EPD0		(1UL << 7)
#define	AARCH64_TCR_EL1_T0SZ(n)		((unsigned long)(64 - (n)))

/*
 * Virtual address space layout:
 *
 * 00000000.00000000 - 0000007f.ffffffff - 512GB (39 bits) user space
 * ffffff00.00000000 - ff7fffff.ffffffff - 512GB (39 bits) msgxfer space
 * ffffff80.00000000 - ffffffff.ffffffff - 512GB (39 bits) kernel space
 *
 * The bottom 512GB (user space) is mapped via TTBR0 using an L1 table.
 * TTBR0 specifies the ASID.
 *
 * The top 1TB is mapped via TTBR1 using a 2 entry L0 table.
 * Each processor has its own L0 table.
 *
 * L0[0] maps the XFER_BASE range used to map a user L1 table to access
 * another address space during message transfer operations.
 *
 * L0[1] maps the KERN_BASE range used for global system mappings.
 * This uses a single L1 table that maps the 512GB space, shared on all cpus.
 * This 512GB space is broken up as follows:
 *
 * ffffff80.00000000 - ffffff80.3fffffff - L3_BASE      (1GB)
 * ffffff80.40000000 - ffffff80.401fffff - L2_BASE      (2MB)
 * ffffff80.00000000 - ffffff80.00000fff - L1_BASE      (4KB)
 * ffffff80.40200000 - ffffff80.5fffffff - STARTUP_BASE (510MB)
 * ffffff80.60000000 - ffffff80.7fffffff - BOOTPGM_BASE (512MB)
 * ffffff80.80000000 - ffffffff.ffffffff - UNUSED_BASE	(511GB)
 *
 *	L1_BASE is a 4KB region that maps the L1 table for the system mappings.
 *	This is mapped by pointing L1[0] back to itself, which causes L1 to act
 *	as L2 and L3 tables so that L2[0] and L3[0] point to L1.
 *
 *	L2_BASE is a 2MB region that maps the L2 tables for the system mappings.
 *	It is mapped by an L2 table installed at L1[1], and pointing L2[0] at the
 *  L1 table so that it acts as an L3 table that mapps all the L2 tables.
 *
 *	L3_BASE is a 1GB region that maps the L3 tables for the system mappings.
 *	It is mapped via the recursive L1[0] entry, which causes all the L1 to
 *	act as an L2 table for this 1GB range so that its L2 entries act as L3
 *	tables.
 *
 * STARTUP_BASE is a 510MB region that contains startup created mappings.
 * This includes the syspage/cpupage and callout mappings.
 *
 * BOOTPGM_BASE is a 512MB region that maps the IFS bootstrap executables.
 *
 * UNUSED_BASE is the start of unused virtual address space mapped by L0[1].
 */

#define	__L0_SHIFT			39u
#define	__L1_SHIFT			30u
#define	__L2_SHIFT			21u
#define	__L3_SHIFT			12u
#define	__NPTE_PTBL			512u
#define	__MAX_VADDR_BITS	48u
#define	__L0_IDX(v)			((unsigned)((v) >> __L0_SHIFT) & (__NPTE_PTBL-1))
#define	__L1_IDX(v)			((unsigned)((v) >> __L1_SHIFT) & (__NPTE_PTBL-1))
#define	__L2_IDX(v)			((unsigned)((v) >> __L2_SHIFT) & (__NPTE_PTBL-1))
#define	__L3_IDX(v)			((unsigned)((v) >> __L3_SHIFT) & (__NPTE_PTBL-1))
#define	__L1_VOFF(v)		((v) & ((1ULL << __L1_SHIFT) - 1))
#define	__L2_VOFF(v)		((v) & ((1ULL << __L3_SHIFT) - 1))
#define	__L3_VOFF(v)		((v) & ((1ULL << __L3_SHIFT) - 1))

#define	AARCH64_USER_START		0ULL
#define	AARCH64_USER_END		(1ULL << __L0_SHIFT)
#define	AARCH64_SYS_BASE		(~((1ULL << __MAX_VADDR_BITS)-1))

#define	__L0_NPTE			2
#define	__L0_BASE_IDX		510ULL
#define	__L0_XFER_IDX		510ULL
#define	__L0_KERN_IDX		511ULL
#define	__XFER_BASE			(AARCH64_SYS_BASE + (__L0_XFER_IDX << __L0_SHIFT))
#define	__XFER_SIZE			(AARCH64_USER_END - AARCH64_USER_START)
#define	__KERN_BASE			(AARCH64_SYS_BASE + (__L0_KERN_IDX << __L0_SHIFT))

#define	__L1_L1_IDX			0ULL
#define	__L1_L2_IDX			1ULL
#define	__L1_L3_IDX			(__L1_L1_IDX)
#define	__L1_OFF			(__L1_L1_IDX << __L1_SHIFT)
#define	__L3_OFF			(__L1_L3_IDX << __L1_SHIFT)

#define	__L2_L2_IDX			0ULL
#define	__L2_STARTUP_IDX	1ULL
#define	__L2_BOOTPGM_IDX	256ULL
#define	__L2_BOOTPGM_SIZE	256ULL

#define	__L2_OFF			((__L1_L2_IDX << __L1_SHIFT) + \
							 (__L2_L2_IDX << __L2_SHIFT))

#define	__STARTUP_OFF		((__L1_L2_IDX << __L1_SHIFT) + \
							 (__L2_STARTUP_IDX << __L2_SHIFT))

#define	__BOOTPGM_OFF		((__L1_L2_IDX << __L1_SHIFT) + \
							 (__L2_BOOTPGM_IDX << __L2_SHIFT))

#define	__UNUSED_OFF		(__BOOTPGM_OFF + (__L2_BOOTPGM_SIZE << __L2_SHIFT))

#define	AARCH64_STARTUP_BASE	(__KERN_BASE + __STARTUP_OFF)
#define	AARCH64_BOOTPGM_BASE	(__KERN_BASE + __BOOTPGM_OFF)
#define	AARCH64_UNUSED_BASE		(__KERN_BASE + __UNUSED_OFF)

#define	__L1_BASE			((ptp_t *)(__KERN_BASE + __L1_OFF))
#define	__L2_BASE			((ptp_t *)(__KERN_BASE + __L2_OFF))
#define	__L3_BASE			((ptp_t *)(__KERN_BASE + __L1_OFF))
#define	__KVA(v)			((v) - __KERN_BASE)
#define	__L1_MAP(v)			(__KVA(v) >> __L1_SHIFT)
#define	__L2_MAP(v)			(__KVA(v) >> __L2_SHIFT)
#define	__L3_MAP(v)			(__KVA(v) >> __L3_SHIFT)

#define	__KTOL1(v)			((ptp_t *)__L1_BASE + __L1_MAP(v))
#define	__KTOL2(v)			((ptp_t *)__L2_BASE + __L2_MAP(v))
#define	__KTOL3(v)			((pte_t *)__L3_BASE + __L3_MAP(v))

#endif /* __AARCH64_MMU_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/aarch64/mmu.h $ $Rev: 815300 $") 
#endif

