/*
 * $QNXLicenseC:
 * Copyright 2015 QNX Software Systems.
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
 * ARM VMSAv7 Support.
 */

#ifndef	__ARM_MMU_H_INCLUDED
#define	__ARM_MMU_H_INCLUDED

/*
 * -------------------------------------------------------------------------
 * System Control Register (SCTLR)
 * -------------------------------------------------------------------------
 */

#define	ARM_SCTLR_M			(1u << 0)
#define	ARM_SCTLR_A			(1u << 1)
#define	ARM_SCTLR_C			(1u << 2)
#define	ARM_SCTLR_SBO_3		(1u << 3)
#define	ARM_SCTLR_SBO_4		(1u << 4)
#define	ARM_SCTLR_CP15BEN	(1u << 5)
#define	ARM_SCTLR_SBO_6		(1u << 6)
#define	ARM_SCTLR_SBZ_7		(1u << 7)
#define	ARM_SCTLR_SBZ_8		(1u << 8)
#define	ARM_SCTLR_SBZ_9		(1u << 9)
#define	ARM_SCTLR_SW		(1u << 10)
#define	ARM_SCTLR_Z			(1u << 11)
#define	ARM_SCTLR_I			(1u << 12)
#define	ARM_SCTLR_V			(1u << 13)
#define	ARM_SCTLR_RR		(1u << 14)
#define	ARM_SCTLR_SBZ_15	(1u << 15)
#define	ARM_SCTLR_SBO_16	(1u << 16)
#define	ARM_SCTLR_HA		(1u << 17)
#define	ARM_SCTLR_SBO_18	(1u << 18)
#define	ARM_SCTLR_WXN		(1u << 19)
#define	ARM_SCTLR_UWXN		(1u << 20)
#define	ARM_SCTLR_FI		(1u << 21)
#define	ARM_SCTLR_SBO_22	(1u << 22)
#define	ARM_SCTLR_SBO_23	(1u << 23)
#define	ARM_SCTLR_VE		(1u << 24)
#define	ARM_SCTLR_EE		(1u << 25)
#define	ARM_SCTLR_SBZ_26	(1u << 26)
#define	ARM_SCTLR_NMFI		(1u << 27)
#define	ARM_SCTLR_TRE		(1u << 28)
#define	ARM_SCTLR_AFE		(1u << 29)
#define	ARM_SCTLR_TE		(1u << 30)
#define	ARM_SCTLR_SBZ_31	(1u << 31)

/*
 * -------------------------------------------------------------------------
 * Short descriptor format (32-bit physical addresses)
 * -------------------------------------------------------------------------
 */

typedef _Uint32t			pte32_t;

/*
 * L1 table descriptors.
 *
 * These can be either:
 * - section descriptor that maps 1MB of physically contiguous memory
 * - page table descriptor that specifies physical address of an L2 table
 */
#define	ARM_L1_TYPE			(3u << 0)
#define	ARM_L1_PT			(1u << 0)
#define	ARM_L1_SC			(1u << 1)

#define	ARM_L1_VALID(p)		(((p) & ARM_L1_TYPE) != 0)
#define	ARM_L1_SCN(p)		(((p) & ARM_L1_TYPE) == ARM_L1_SC)

/*
 * Section descriptor bits
 */
#define	ARM_SCN_PXN			(1u << 0)
#define	ARM_SCN_B			(1u << 2)
#define	ARM_SCN_C			(1u << 3)
#define	ARM_SCN_XN			(1u << 4)
#define	ARM_SCN_AP0			(1u << 10)
#define	ARM_SCN_AP1			(1u << 11)
#define	ARM_SCN_TEX0		(1u << 12)
#define	ARM_SCN_TEX1		(1u << 13)
#define	ARM_SCN_TEX2		(1u << 14)
#define	ARM_SCN_AP2			(1u << 15)
#define	ARM_SCN_S			(1u << 16)
#define	ARM_SCN_nG			(1u << 17)
#define	ARM_SCN_SS			(1u << 18)
#define	ARM_SCN_NS			(1u << 19)

#define	ARM_SCN_TEX_MASK	(7u << 12)
#define	ARM_SCN_ATTR_MASK	(ARM_SCN_TEX_MASK|ARM_SCN_C|ARM_SCN_B)

/*
 * Access permissions using AP[2:1] encodings (AP0 is always set to 1):
 * AP2 - not write access
 * AP1 - user access
 *
 * 00 - priv RW / user NA
 * 01 - priv RW / user RW
 * 10 - priv RO / user NA
 * 11 - priv RO / user RO
 */
#define	ARM_SCN_RO			ARM_SCN_AP2
#define	ARM_SCN_RW			0u
#define	ARM_SCN_USER		ARM_SCN_AP1
#define	ARM_SCN_URO			(ARM_SCN_AP0|ARM_SCN_RO|ARM_SCN_USER)
#define	ARM_SCN_URW			(ARM_SCN_AP0|ARM_SCN_RW|ARM_SCN_USER)
#define	ARM_SCN_KRO			(ARM_SCN_AP0|ARM_SCN_RO)
#define	ARM_SCN_KRW			(ARM_SCN_AP0|ARM_SCN_RW)

/*
 * Section attribute encodings (attribute index defined by TEX0/C/B):
 * 0 - Strongly Ordered
 * 1 - Device
 * 2 - Normal WTnWA
 * 3 - Normal WBnWA
 * 4 - Normal NC
 * 5 - reserved
 * 6 - implementation defined
 * 7 - Normal WBWA
 */
#define	ARM_SCN_SO			0u
#define	ARM_SCN_DEV			ARM_SCN_B
#define	ARM_SCN_WT			ARM_SCN_C
#define	ARM_SCN_WB			(ARM_SCN_C|ARM_SCN_B)
#define	ARM_SCN_NC			ARM_SCN_TEX0
#define	ARM_SCN_WA			(ARM_SCN_TEX0|ARM_SCN_C|ARM_SCN_B)

/*
 * L2 Descriptors.
 *
 * These can be either:
 * - large page descriptor to map a 64K page (16 contiguous entries)
 * - small page descriptor to map a 4K page
 */

#define	ARM_L2_TYPE			(3u << 0)
#define	ARM_L2_LP			(1u << 0)
#define	ARM_L2_SP			(1u << 1)

/*
 * Bits common to small and large page descriptors
 */
#define	ARM_L2_B			(1u << 2)
#define	ARM_L2_C			(1u << 3)
#define	ARM_L2_AP0			(1u << 4)
#define	ARM_L2_AP1			(1u << 5)
#define	ARM_L2_AP2			(1u << 9)
#define	ARM_L2_S			(1u << 10)
#define	ARM_L2_nG			(1u << 11)

#define	ARM_L2_VALID(p)		(((p) & ARM_L2_TYPE) != 0)
#define	ARM_L2_SMALL(p)		(((p) & ARM_L2_TYPE) == ARM_L2_SP)
#define	ARM_L2_LARGE(p)		(((p) & ARM_L2_TYPE) == ARM_L2_LP)

/*
 * Access permissions using AP[2:1] encodings (AP0 is always set to 1):
 * AP2 - not write access
 * AP1 - user access
 *
 * 00 - priv RW / user NA
 * 01 - priv RW / user RW
 * 10 - priv RO / user NA
 * 11 - priv RO / user RO
 */
#define	ARM_L2_RO			ARM_L2_AP2
#define	ARM_L2_RW			0u
#define	ARM_L2_USER			ARM_L2_AP1
#define	ARM_L2_URO			(ARM_L2_AP0|ARM_L2_RO|ARM_L2_USER)
#define	ARM_L2_URW			(ARM_L2_AP0|ARM_L2_RW|ARM_L2_USER)
#define	ARM_L2_KRO			(ARM_L2_AP0|ARM_L2_RO)
#define	ARM_L2_KRW			(ARM_L2_AP0|ARM_L2_RW)

/*
 * Small page descriptor bits
 */
#define	ARM_SP_XN			(1u << 0)
#define	ARM_SP_TEX0			(1u << 6)
#define	ARM_SP_TEX1			(1u << 7)
#define	ARM_SP_TEX2			(1u << 8)

#define	ARM_SP_TEX_MASK		(7u << 6)
#define	ARM_SP_ATTR_MASK	(ARM_SP_TEX_MASK|ARM_L2_C|ARM_L2_B)

/*
 * Small page attribute encodings (attribute index defined by TEX0/C/B):
 * 0 - Strongly Ordered
 * 1 - Device
 * 2 - Normal WTnWA
 * 3 - Normal WBnWA
 * 4 - Normal NC
 * 5 - reserved
 * 6 - implementation defined
 * 7 - Normal WBWA
 */
#define	ARM_SP_SO			0u
#define	ARM_SP_DEV			ARM_L2_B
#define	ARM_SP_WT			ARM_L2_C
#define	ARM_SP_WB			(ARM_L2_C|ARM_L2_B)
#define	ARM_SP_NC			ARM_SP_TEX0
#define	ARM_SP_WA			(ARM_SP_TEX0|ARM_L2_C|ARM_L2_B)

/*
 * Large page descriptor bits
 */
#define	ARM_LP_TEX0			(1u << 12)
#define	ARM_LP_TEX1			(1u << 13)
#define	ARM_LP_TEX2			(1u << 14)
#define	ARM_LP_XN			(1u << 15)

#define	ARM_LP_TEX_MASK		(7u << 12)
#define	ARM_LP_ATTR_MASK	(ARM_LP_TEX_MASK|ARM_L2_C|ARM_L2_B)

/*
 * Large page attribute encodings (attribute index defined by TEX0/C/B):
 * 0 - Strongly Ordered
 * 1 - Device
 * 2 - Normal WTnWA
 * 3 - Normal WBnWA
 * 4 - Normal NC
 * 5 - reserved
 * 6 - implementation defined
 * 7 - Normal WBWA
 */
#define	ARM_LP_SO			0u
#define	ARM_LP_DEV			ARM_L2_B
#define	ARM_LP_WT			ARM_L2_C
#define	ARM_LP_WB			(ARM_L2_C|ARM_L2_B)
#define	ARM_LP_NC			ARM_LP_TEX0
#define	ARM_LP_WA			(ARM_LP_TEX0|ARM_L2_C|ARM_L2_B)

/*
 * TTBR0/TTBR1 attributes
 */
#define ARM_TTBR_ATTR_MASK	0x7f
#define	ARM_TTBR_C			(1 << 0)
#define	ARM_TTBR_S			(1 << 1)
#define	ARM_TTBR_P			(1 << 2)
#define	ARM_TTBR_RGN(x)		(((x) & 3) << 3)
#define ARM_TTBR_IRGN(x)	((((x) & 1) << 6) | (((x) & 2) >> 1))
#define ARM_TTBR_NOS		(1 << 5)

#define ARM_TTBR_RGN_NC		ARM_TTBR_RGN(0)
#define ARM_TTBR_RGN_WA		ARM_TTBR_RGN(1)
#define ARM_TTBR_RGN_WT		ARM_TTBR_RGN(2)
#define ARM_TTBR_RGN_WB		ARM_TTBR_RGN(3)

#define ARM_TTBR_IRGN_NC	ARM_TTBR_IRGN(0)
#define ARM_TTBR_IRGN_WA	ARM_TTBR_IRGN(1)
#define ARM_TTBR_IRGN_WT	ARM_TTBR_IRGN(2)
#define ARM_TTBR_IRGN_WB	ARM_TTBR_IRGN(3)

/*
 * Page table manipulation
 */
#define	ARM_L1_SIZE			16384u
#define	ARM_L2_SIZE			1024u
#define	PGMASK				(__PAGESIZE-1)

#define	ARM_SCSIZE			(1024u*1024u)
#define	ARM_SCMASK			(ARM_SCSIZE-1)

#define	ARM_LPSIZE			65536u
#define	ARM_LPMASK			(ARM_LPSIZE-1)

#define	ARM_KPTE_MAP		1022u
#define	ARM_KPTE_BASE		(ARM_KPTE_MAP << 22)
#define	ARM_KPTP_BASE		(ARM_KPTE_BASE | (ARM_KPTE_MAP << 12))

/*
 * Pointer to (s/w managed) "page directory" entry that maps L2 table for v.
 * These map L2 page tables that can be accessed by ARM_KTOPTEP/ARM_KTOPTP.
 */
#define	ARM_KTOPDIR(v) \
		(pte32_t *)(ARM_KPTP_BASE | (((unsigned)(v) >> 20) & ~3))

/*
 * Pointer to L2 table entry that maps v.
 */
#define	ARM_KTOPTEP(v) \
		(pte32_t *)(ARM_KPTE_BASE | (((unsigned)(v) >> 10) & ~3))

/*
 * Pointer to base of L2 table that maps v.
 */
#define	ARM_KTOPTP(v) \
		(pte32_t *)(ARM_KPTE_BASE | (((unsigned)(v) >> 10) & 0x3ff000))

/*
 * -------------------------------------------------------------------------
 * Long descriptor format (LPAE 40-bit physical addresses)
 * -------------------------------------------------------------------------
 */

typedef	_Uint64t	pte64_t;

/*
 * Access Permissions:
 *	00 - priv r/w, user n/a
 *	01 - priv r/w, user r/w
 *	10 - priv r/o, user n/a
 *	11 - priv r/o, user r/o
 */
#define	ARM_LPAE_AP_MASK	(3u)
#define	ARM_LPAE_AP_RW		(0u)
#define	ARM_LPAE_AP_RO		(2u)
#define	ARM_LPAE_AP_USER	(1u)

/*
 * Shareability:
 *	00 - non-shareable
 *	01 - UNPREDICTABLE
 *	10 - outer shareable
 *	11 - inner shareable
 */
#define	ARM_LPAE_SH_NONE	(0u)
#define	ARM_LPAE_SH_OUTER	(2u)
#define	ARM_LPAE_SH_INNER	(3u)

/*
 * Level 1 and 2 descriptors.
 *
 * If PTP_TYPE(ptp) == PTP_BLOCK, the attribute bits are identical to the
 * Level3 descriptor bits and specify the attributes for the block.
 *
 * If PTP_TYPE(ptp) == PTP_TABLE, the attribute bits specify hierarchical
 * control of access permissions in lower level tables.
 */

#define	ARM_LPAE_PTP_TYPE		(3ull << 0)
#define	ARM_LPAE_PTP_BLK		(1ull << 0)
#define	ARM_LPAE_PTP_TBL		(3ull << 0)
#define	ARM_LPAE_PTP_PXNTable	(1ull << 59)
#define	ARM_LPAE_PTP_XNTable	(1ull << 60)
#define	ARM_LPAE_PTP_APTable(x)	((ptp_t)(x) << 61)
#define	ARM_LPAE_PTP_NSTable	(1ull << 63)

#define	ARM_LPAE_PTP_VALID(p)	(((p) & ARM_LPAE_PTP_TYPE) != 0)
#define	ARM_LPAE_PTP_BLOCK(p)	(((p) & ARM_LPAE_PTP_TYPE) == ARM_LPAE_PTP_BLK)

#define	ARM_LPAE_BLOCK_SHIFT	(21u)
#define	ARM_LPAE_BLOCK_SIZE		(1u << ARM_LPAE_BLOCK_SHIFT)
#define	ARM_LPAE_BLOCK_MASK		(ARM_LPAE_BLOCK_SIZE-1)

/*
 * Level 3 descriptors
 */

#define	ARM_LPAE_PTE_TYPE			(3ull << 0)
#define	ARM_LPAE_PTE_L3				(3ull << 0)
#define	ARM_LPAE_PTE_ATTRINDX(x)	((pte64_t)(x) << 2)
#define	ARM_LPAE_PTE_NS				(1ull << 5)
#define	ARM_LPAE_PTE_AP(x)			((pte64_t)(x) << 6)
#define	ARM_LPAE_PTE_SH(x)			((pte64_t)(x) << 8)
#define	ARM_LPAE_PTE_AF				(1ull << 10)
#define	ARM_LPAE_PTE_nG				(1ull << 11)
#define	ARM_LPAE_PTE_CONTIG			(1ull << 52)
#define	ARM_LPAE_PTE_PXN			(1ull << 53)
#define	ARM_LPAE_PTE_XN				(1ull << 54)
#define	ARM_LPAE_PTE_UXN			(ARM_LPAE_PTE_XN)

#define	ARM_LPAE_PTE_VALID(x)	(((x) & ARM_LPAE_PTE_TYPE) == ARM_LPAE_PTE_L3)
#define ARM_LPAE_L3_DESC_BAD        ((_Uint64t)1)               /* L3 with table bit not set is reserved & invalid (though okay for L2...) */
#define	ARM_LPAE_PTE_BAD(x)	(((x) & ARM_LPAE_PTE_TYPE) == ARM_LPAE_L3_DESC_BAD)

/*
 * Mask off ATTR/AP/SH bits
 */
#define	ARM_LPAE_PTE_ATTR_BITS	(ARM_LPAE_PTE_ATTRINDX(0b111))
#define	ARM_LPAE_PTE_AP_BITS	(ARM_LPAE_PTE_AP(0b11))
#define	ARM_LPAE_PTE_SH_BITS	(ARM_LPAE_PTE_SH(0b11))

/*
 * The startup program sets up MAIR0/1 so that the AttrIndex[2:0] is
 * equivalent to ARMv7-A TEX[0]/C/B encodings.
 */
#define	ARM_LPAE_PTE_SO		(ARM_LPAE_PTE_ATTRINDX(0))
#define	ARM_LPAE_PTE_DEV	(ARM_LPAE_PTE_ATTRINDX(1))
#define	ARM_LPAE_PTE_WTnWA	(ARM_LPAE_PTE_ATTRINDX(2))
#define	ARM_LPAE_PTE_WBnWA	(ARM_LPAE_PTE_ATTRINDX(3))
#define	ARM_LPAE_PTE_NC		(ARM_LPAE_PTE_ATTRINDX(4))
#define	ARM_LPAE_PTE_RSVD5	(ARM_LPAE_PTE_ATTRINDX(5))
#define	ARM_LPAE_PTE_RSVD6	(ARM_LPAE_PTE_ATTRINDX(6))
#define	ARM_LPAE_PTE_WBWA	(ARM_LPAE_PTE_ATTRINDX(7))

/*
 * Page Shareability
 */
#define	ARM_LPAE_PTE_NSH	(ARM_LPAE_PTE_SH(0))
#define	ARM_LPAE_PTE_OSH	(ARM_LPAE_PTE_SH(2))
#define	ARM_LPAE_PTE_ISH	(ARM_LPAE_PTE_SH(3))

/*
 * Page access permissions
 */
#define	ARM_LPAE_PTE_KRO	(ARM_LPAE_PTE_AP(ARM_LPAE_AP_RO))
#define	ARM_LPAE_PTE_KRW	(ARM_LPAE_PTE_AP(ARM_LPAE_AP_RW))
#define	ARM_LPAE_PTE_URO	(ARM_LPAE_PTE_AP(ARM_LPAE_AP_RO|ARM_LPAE_AP_USER))
#define	ARM_LPAE_PTE_URW	(ARM_LPAE_PTE_AP(ARM_LPAE_AP_RW|ARM_LPAE_AP_USER))

/*
 * TTBCR configuration
 */
#define	ARM_LPAE_TTBCR_EAE			(1u << 31)
#define	ARM_LPAE_TTBCR_SH1_NSH		(0b00u << 28)
#define	ARM_LPAE_TTBCR_SH1_OSH		(0b10u << 28)
#define	ARM_LPAE_TTBCR_SH1_ISH		(0b11u << 28)
#define	ARM_LPAE_TTBCR_ORGN1_NC		(0b00u << 26)
#define	ARM_LPAE_TTBCR_ORGN1_WBWA	(0b01u << 26)
#define	ARM_LPAE_TTBCR_ORGN1_WT		(0b10u << 26)
#define	ARM_LPAE_TTBCR_ORGN1_WBnWA	(0b11u << 26)
#define	ARM_LPAE_TTBCR_IRGN1_NC		(0b00u << 24)
#define	ARM_LPAE_TTBCR_IRGN1_WBWA	(0b01u << 24)
#define	ARM_LPAE_TTBCR_IRGN1_WT		(0b10u << 24)
#define	ARM_LPAE_TTBCR_IRGN1_WBnWA	(0b11u << 24)
#define	ARM_LPAE_TTBCR_EPD1			(1u << 23)
#define	ARM_LPAE_TTBCR_A1			(1u << 22)
#define	ARM_LPAE_TTBCR_T1SZ(n)		((unsigned)(32 - (n)) << 16)
#define	ARM_LPAE_TTBCR_SH0_NSH		(0b00u << 12)
#define	ARM_LPAE_TTBCR_SH0_OSH		(0b10u << 12)
#define	ARM_LPAE_TTBCR_SH0_ISH		(0b11u << 12)
#define	ARM_LPAE_TTBCR_ORGN0_NC		(0b00u << 10)
#define	ARM_LPAE_TTBCR_ORGN0_WBWA	(0b01u << 10)
#define	ARM_LPAE_TTBCR_ORGN0_WT		(0b10u << 10)
#define	ARM_LPAE_TTBCR_ORGN0_WBnWA	(0b11u << 10)
#define	ARM_LPAE_TTBCR_IRGN0_NC		(0b00u << 8)
#define	ARM_LPAE_TTBCR_IRGN0_WBWA	(0b01u << 8)
#define	ARM_LPAE_TTBCR_IRGN0_WT		(0b10u << 8)
#define	ARM_LPAE_TTBCR_IRGN0_WBnWA	(0b11u << 8)
#define	ARM_LPAE_TTBCR_EPD0			(1u << 7)
#define	ARM_LPAE_TTBCR_T0SZ(n)		((unsigned)(32 - (n)))

/*
 * Page table manipulation
 */

#define	ARM_LPAE_PTBL_SIZE	(4096u)
#define	ARM_LPAE_NPTE_PTBL	(512u)

#define	ARM_LPAE_L1_SIZE	(4u * sizeof(pte64_t))
#define	ARM_LPAE_L2_SIZE	ARM_LPAE_PTBL_SIZE
#define	ARM_LPAE_L3_SIZE	ARM_LPAE_PTBL_SIZE

#define	ARM_LPAE_L1_IDX(v)	(((v) >> 30) & (ARM_LPAE_NPTE_PTBL-1))
#define	ARM_LPAE_L2_IDX(v)	(((v) >> 21) & (ARM_LPAE_NPTE_PTBL-1))
#define	ARM_LPAE_L3_IDX(v)	(((v) >> 12) & (ARM_LPAE_NPTE_PTBL-1))

#define	ARM_LPAE_KPTE_MAP	(510u)
#define	ARM_LPAE_KERN_BASE	(0xc0000000u)
#define	ARM_LPAE_L3_BASE	(ARM_LPAE_KERN_BASE + (ARM_LPAE_KPTE_MAP << 21))
#define	ARM_LPAE_L3_OFF(v)	(((unsigned)(v) & ~ARM_LPAE_KERN_BASE) >> 12)
#define	ARM_LPAE_KTOL3(v)	((pte64_t *)ARM_LPAE_L3_BASE + ARM_LPAE_L3_OFF(v))

/*
 * -------------------------------------------------------------------------
 * Memory attributes that can be set by shm_ctl_special()
 * -------------------------------------------------------------------------
 */

#define	ARM_SHMCTL_SH		0x400u	/* shareability (if cacheable) */
#define	ARM_SHMCTL_SO		0x000u	/* strongly-ordered       (uncached) */
#define	ARM_SHMCTL_DEV		0x004u	/* shared device          (uncached) */
#define	ARM_SHMCTL_NC		0x040u	/* normal memory          (uncached) */
#define	ARM_SHMCTL_WT		0x008u	/* write-through          (cacheable) */
#define	ARM_SHMCTL_WB		0x00cu	/* write-back             (cacheable) */
#define	ARM_SHMCTL_WBWA		0x04cu	/* write-back/write-alloc (cacheable) */

/*
 * The following are only for source compatibility with old code.
 * NOTE: encodings using TEX[2:1] are no longer supported because of TEX remap.
 */
#define	ARM_PTE_C				ARM_L2_C
#define	ARM_PTE_B				ARM_L2_B
#define	ARM_PTE_CB				(ARM_L2_C|ARM_L2_B)
#define	ARM_PTE_V6_SP_XN		ARM_SP_XN
#define	ARM_PTE_V6_S			ARM_L2_S
#define	ARM_PTE_V6_SP_TEX_MASK	ARM_SP_TEX_MASK
#define	ARM_PTE_V6_SP_TEX(x)	(((unsigned)(x) & 7u) << 6)
#define	ARM_PTE_RW				ARM_SP_XN
#define	ARM_PTE_WT				ARM_SP_WT
#define	ARM_PTE_WB				ARM_SP_WB

/*
 * uses invalid pte with ARM_L2_AP2 set as a bad page marker
 */
#define	ARM_PTE_BAD				(ARM_L2_AP2)

/*
 * -------------------------------------------------------------------------
 * System Address Space Layout
 *
 * When using the ARMv7 short descriptor format tables:
 *	TTBR0 maps a 2GB user address space:   0x00000000-0x7fffffff
 * 	TTBR1 maps a 2GB system address space: 0x80000000-0xffffffff
 *
 * Each processor's TTBR1 points to a per-processor L1 table to allow the
 * system address space to contain per-processor translations.
 *
 * The system address space contains the following:
 *	80000000-e0000000	(C) used for dynamic kernel memory allocations
 *	fc400000-fdffffff	(C) maps L1 page table and mappings for callouts
 *	fe000000-feffffff	(C) maps boot programs (kdebug/procnto)
 *	ff000000-ff7fffff	(P) used for message passing
 *	ffff0000-ffff0fff	(C) exception vector table
 *	ffff1000-ffff1fff	(P) cpupage on SMP systems
 *	ffff4000-ffff7fff	(P) used to map L1 tables for message passing
 *	ffff8000-ffff9fff	(P) used to map L1 tables for inactive address spaces
 *	ffffa000-ffffafff	(P) used to map L2 tables for inactive address spaces
 *	ffffe000-ffffefff	(P) scratch page used for zeroing page tables
 *	fffff000-ffffffff	(P) scratch page used for planting breakpoints
 *
 * When using the ARMv7 long descriptor format tables:
 *	TTBR0 maps a 3GB user address space:   0x00000000-0xbfffffff
 * 	TTBR1 maps a 1GB system address space: 0xc0000000-0xffffffff
 *
 * Each processor's TTBR1 points to a per-processor L2 table to allow the
 * system address space to contain per-processor translations.
 *
 * The system address space contains the following:
 *	c0000000-f0000000	(C) used for dynamic kernel memory allocations
 *	fc400000-fdffffff	(C) maps L1 page table and mappings for callouts
 *	fe000000-feffffff	(C) maps boot programs (kdebug/procnto)
 *	ff000000-ff7fffff	(P) used for message passing
 *	ffff0000-ffff0fff	(C) exception vector table
 *	ffff1000-ffff1fff	(P) cpupage on SMP systems
 *
 * (C) indicates translations that are shared by all processors
 * (P) indicates translations that are per-processor
 * -------------------------------------------------------------------------
 */

/*
 * User address space
 */
#define	ARM_USER_END		0x80000000u
#define	ARM_LPAE_USER_END	0xc0000000u

/*
 * Obsolete range used by old startups to map up to 256MB of system RAM.
 */
#define	ARM_1TO1_BASE		0xe0000000u
#define	ARM_1TO1_SIZE		0x10000000u

/*
 * Addresses used by startup program to map:
 * - bootstrap page tables
 * - bootstrap programs in the image file system
 * - syspage/cpupage and callouts
 */
#define	ARM_STARTUP_BASE	0xfc400000u
#define	ARM_BOOTPGM_BASE	0xfe000000u

/*
 * Address range used to map parts of another address space for message passing
 */
#define	ARM_XFER_BASE		0xff000000u
#define	ARM_XFER_SIZE		0x00800000u

#define	ARM_TRAP_VECTORS	0xffff0000u
#define	ARM_SMP_CPUPAGE		0xffff1000u
#define	ARM_XFER_L1			0xffff4000u
#define	ARM_INACTIVE_L1		0xffff8000u
#define	ARM_INACTIVE_L2		0xffffa000u
#define	ARM_SCRATCH_PTBL	0xffffe000u
#define	ARM_SCRATCH_BKPT	0xfffff000u

#endif	/* __ARM_MMU_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/arm/mmu.h $ $Rev: 810600 $")
#endif
