/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software. For more information visit
 * http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef __GPT_H_INCLUDED
#define __GPT_H_INCLUDED

#include <sys/cdefs.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

__BEGIN_DECLS

#ifndef EOK
# define EOK    0
#endif

/* Defined error codes used by libgpt */
#define GPT_GUID_EBADSTR      -1    /* Syntax error in GUID string             */
#define GPT_GUID_ETOOSMALL    -2    /* Buffer too small to hold a textual GUID */
#define GPT_EHDRSIG           -3    /* Invalid header signature                */
#define GPT_EHDRREV           -4    /* Invalid header revision                 */
#define GPT_EHDRCRC           -5    /* Bad header CRC checksum                 */
#define GPT_EBADSEQ           -6    /* Invalid UTF-8 sequence encountered      */
#define GPT_EBADCODE          -7    /* Invalid Unicode code point encountered  */
#define GPT_ENOSPACE          -8    /* Insufficient space to store string      */
#define GPT_PTYPE_EGUIDEX     -9    /* Partition-type GUID already defined     */
#define GPT_PTYPE_EALIASEX   -10    /* Partition-type alias already defined    */
#define GPT_PTYPE_ENOENT     -11    /* Partition type not found                */
#define GPT_BADENDIAN        -12    /* Unsupported platform endianness         */
#define GPT_ETOOMANY         -13    /* Too many entries                        */


/* Number of bytes in a binary GUID. */
#define GUID_NBYTES     16

/* The string length of a textually represented GUID. */
/*                            binary bytes                 */
/*                            |             hexdigits/byte */
/*                            |             |    dashes    */
/*                            |             |    |         */
#define GUID_STRLEN     ((GUID_NBYTES * 2) + 4)

/* The required buffer size for a textually represented GUID */
/* (one added for terminating NUL)                           */
#define GUID_STRSIZE    (GUID_STRLEN + 1)

typedef struct {
	uint8_t    byte[GUID_NBYTES];
} guid_t;


typedef struct {
	guid_t        guid;      /* Partition type GUID        */
	const char    *alias;    /* Partition type short name  */
	const char    *desc;     /* Partition type description */
} gpt_ptype_t;


/* Number of 16-bit UCL-2 characters in a stored */
/* partition name, including a terminating NUL.  */
#define GPT_PARTN_NAME_SIZE_UCL2   36

/* Maximum number of 8-bit UTF-8 characters in a */
/* partition name, including a terminating NUL.  */
/* The maximum sequence length per each code is  */
/* four bytes; the NUL character only uses 1.    */
#define GPT_PARTN_NAME_MAX_UTF8   (((GPT_PARTN_NAME_SIZE_UCL2 - 1) * 4) + 1)

typedef struct {
	/* Identifies EFI-compatible partition table header. This value         */
	/* must contain the ASCII string "EFI PART", encoded as the 64-bit      */
	/* constant 0x5452415020494645.                                         */
	uint64_t    signature;
#define GPT_SIGNATURE        0x5452415020494645ULL
#define GPT_SIGNATURE_STR    "EFI PART"
	/* The revision number for this header. This revision value is not      */
	/* related to the UEFI Specification version. This header is version    */
	/* 1.0, so the correct value is 0x00010000.                             */
	uint32_t    revision;
#define GPT_REVISION     0x00010000UL
	/* Size in bytes of the GPT Header. The header_size must be greater     */
	/* than or equal to 92 and must be less than or equal to the logical    */
	/* block size.                                                          */
	uint32_t    header_size;
	/* CRC32 checksum for the GPT Header structure. This value is computed  */
	/* by setting this field to 0, and computing the 32-bit CRC for         */
	/* header_size bytes.                                                   */
	uint32_t    header_crc32;
	/* Must be zero.                                                        */
	uint32_t    reserved0;
	/* The LBA that contains this data structure.                           */
	uint64_t    my_lba;
	/* LBA address of the alternate GPT Header.                             */
	uint64_t    alternate_lba;
	/* The first usable logical block that may be used by a partition       */
	/* described by a GUID Partition Entry.                                 */
	uint64_t    first_usable_lba;
	/* The last usable logical block that may be used by a partition        */
	/* described by a GUID Partition Entry.                                 */
	uint64_t    last_usable_lba;
	/* GUID that can be used to uniquely identify the disk.                 */
	guid_t      disk_guid;
	/* The starting LBA of the GUID Partition Entry array.                  */
	uint64_t    partition_entry_lba;
	/* The number of Partition Entries in the GUID Partition Entry array.   */
	/* The minimum (and default) number is 128.                             */
	uint32_t    number_of_partition_entries;
#define GPT_NPARTN_MIN    128
	/* The size, in bytes, of each the GUID Partition Entry structures in   */
	/* the GUID Partition Entry array. This field shall be set to a value   */
	/* of 128 x 2^n, where n is an integer greater than or equal to zero    */
	/* (e.g., 128, 256, 512, etc.). NOTE: Previous versions of this         */
	/* specification allowed any multiple of 8.                             */
	uint32_t    size_of_partition_entry;
	/* The CRC32 of the GUID Partition Entry array. Starts at               */
	/* partition_entry_lba and is computed over a byte length of            */
	/* number_of_partition_entries * size_of_partition_entry.               */
	uint32_t    partition_entry_array_crc32;
	/* [BlockSize - 92] The rest of the block is reserved by UEFI and       */
	/* must be zero.                                                        */
//	uint8_t     reserved1[0];
} __attribute__ ((__packed__)) gpt_header_t;

typedef struct {
	/* Unique ID that defines the purpose and type of this partition.       */
	/* A value of zero defines that this partition entry is not being used. */
	guid_t      partition_type_guid;
	/* GUID that is unique for every partition entry. Every partition ever  */
	/* created will have a unique GUID. This GUID must be assigned when the */
	/* GPT Partition Entry is created. The GPT Partition Entry is created   */
	/* whenever the number_of_partition_entries in the GPT Header is        */
	/* increased to include a larger range of addresses.                    */
	guid_t      unique_partition_guid;
	/* Starting LBA of the partition defined by this entry.                 */
	uint64_t    starting_lba;
	/* Ending LBA of the partition defined by this entry.                   */
	uint64_t    ending_lba;
	/* Attribute bits, all bits reserved by UEFI (see Table 19).            */
	uint64_t    attributes;
/* Bit 0: Required Partition -- If this bit is set, the partition is        */
/*        required for the platform to function.                            */
#define GPT_ATTR_REQUIRED    0x00000001
/* Bit 1: No Block IO Protocol -- If this bit is set, then firmware must    */
/*        not produce an EFI_BLOCK_IO_PROTOCOL device for this partition.   */
#define GPT_ATTR_NOBLOCK     0x00000002
/* Bit 2: Legacy BIOS Bootable -- This bit is set aside to let systems with */
/*        traditional PC-AT BIOS firmware implementations inform certain    */
/*        limited, special-purpose software running on these systems that   */
/*        a GPT partition may be bootable.                                  */
#define GPT_ATTR_BIOSBOOT    0x00000004
	/* Null-terminated UTF16LE (well, actually UCS-2) string containing the */
	/* human-readable name of the partition. 1 added for NUL character;     */
	/* GPT_PARTN_NAME_MAX is actual text.                                   */
	uint16_t    partition_name[GPT_PARTN_NAME_SIZE_UCL2];
	/* [size_of_partition_entry - 128] The rest of the GPT Partition Entry, */
	/* if any, is reserved by UEFI and must be zero.                        */
	/* We use a <size_of_partition_entry> of 128, hence the effective size  */
	/* of this field is zero. As it isn't used anywhere, it is commented    */
	/* out to avoid uncertainties with regard to sizeof(gpt_entry_t).  */
//  uint8_t     reserved[0];
} __attribute__ ((__packed__)) gpt_entry_t;


extern const char *gpt_strerror(int e);

extern int guid_eq(const guid_t *_g0, const guid_t *_g1);
extern int guid_from_str(guid_t *guid, const char *str);
extern int guid_to_str(char *buf, size_t bufsz, const guid_t *guid);
extern int guid_v4_random(guid_t *guid);

extern int gpt_ccitt32_crc(uint32_t *pcrc, const void *buf, size_t nbytes);
extern int gpt_ccitt32_crc_init(uint32_t *pcrc);
extern int gpt_ccitt32_crc_update(uint32_t *pcrc, const void *buf, size_t nbytes);
extern int gpt_ccitt32_crc_finish(uint32_t *pcrc);

extern int gpt_utf8_to_utf32(const uint8_t **psrc, uint32_t *dst);
extern int gpt_utf32_to_utf8(uint32_t c, uint8_t **pdst, uint8_t *end);
extern int gpt_utf16_to_utf32(const uint16_t **psrc, uint32_t *dst);
extern int gpt_utf32_to_utf16(uint32_t c, uint16_t **pdst, uint16_t *end);
extern int gpt_utf8_to_utf16_str(const uint8_t *src, uint16_t *dst, size_t dsize);
extern int gpt_utf16_to_utf8_str(const uint16_t *src, uint8_t *dst, size_t dsize);

extern int gpt_header_endian_swap(gpt_header_t *hdr);
extern int gpt_header_endianize(gpt_header_t *hdr);
extern int gpt_entry_endian_swap(gpt_entry_t *entry);
extern int gpt_entries_endian_swap(const gpt_header_t *hdr, void *entries, unsigned nentries);
extern int gpt_entries_endianize(const gpt_header_t *hdr, void *entries, unsigned nentries);
extern int gpt_calc_header_crc(uint32_t *pcrc, const gpt_header_t *hdr);
extern int gpt_check_header(const gpt_header_t *hdr);
extern int gpt_entry_array_crc(uint32_t *pcrc, const gpt_header_t *hdr, const void *entries);
extern int gpt_get_partn_name_mb(char *buf, size_t bufsz, const gpt_entry_t *entry);
extern int gpt_set_partn_name_mb(gpt_entry_t *entry, const char *name);

extern int gpt_ptype_add(const gpt_ptype_t **ptype, const guid_t *guid,
                         const char *alias, const char *desc);
extern int gpt_ptype_lookup_guid(const gpt_ptype_t **ptype, const guid_t *guid);
extern int gpt_ptype_lookup_alias(const gpt_ptype_t **ptype, const char *alias);

__END_DECLS

#endif /* __GPT_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/gpt/public/gpt.h $ $Rev: 820625 $")
#endif
