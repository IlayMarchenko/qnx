/*
*
* You must obtain a written license from and pay applicable license fees to QNX
* Software Systems before you may reproduce, modify or distribute this software,
* or any work that includes all or part of this software. Free development
* licenses are available for evaluation and non-commercial purposes. For more
* information visit http://licensing.qnx.com or email licensing@qnx.com.
*
* This file may contain contributions from others. Please review this entire
* file for other proprietary rights or license notices, as well as the QNX
* Development Suite License Guide at http://licensing.qnx.com/license-guide/
* for other information.
*
*/

/* lzo_asm.h -- assembler prototypes for the LZO data compression library

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2014 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */


#ifndef __LZO_ASM_H_INCLUDED
#define __LZO_ASM_H_INCLUDED 1

#ifndef __LZOCONF_H_INCLUDED
#include "lzoconf.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
// i386 assembly decompressors
//
// NOTE:
// ====
//
// - For reasons of speed all fast assembler decompressors (having '_fast'
//   in their name) can access (write to) up to 3 bytes past the end of
//   the decompressed ("dst") block. Data past the end of the compressed
//   ("src") block is never accessed (read from).
//   [ technical note: because data is transferred in 32-bit units ]
//
// - Please also see asm/i386/00README.TXT and doc/LZO.FAQ for more
//   important details about the assembler versions.
//
************************************************************************/

LZO_EXTERN(int) lzo1c_decompress_asm
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1c_decompress_asm_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);

LZO_EXTERN(int) lzo1f_decompress_asm_fast
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1f_decompress_asm_fast_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);

LZO_EXTERN(int) lzo1x_decompress_asm
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1x_decompress_asm_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1x_decompress_asm_fast
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1x_decompress_asm_fast_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);

LZO_EXTERN(int) lzo1y_decompress_asm
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1y_decompress_asm_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1y_decompress_asm_fast
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);
LZO_EXTERN(int) lzo1y_decompress_asm_fast_safe
                                (const lzo_bytep src, lzo_uint  src_len,
                                       lzo_bytep dst, lzo_uintp dst_len,
                                       lzo_voidp wrkmem);


/***********************************************************************
// checksum and misc functions
************************************************************************/

#if 0

LZO_EXTERN(lzo_uint32_t)
lzo_crc32_asm(lzo_uint32_t c, const lzo_bytep buf, lzo_uint len,
              const lzo_uint32_tp tab);

LZO_EXTERN(lzo_uint32_t)
lzo_crc32_asm_small(lzo_uint32_t c, const lzo_bytep buf, lzo_uint len);

LZO_EXTERN(int)
lzo_cpuid_asm(lzo_uint32_tp /* lzo_uint32_t info[16] */ );

LZO_EXTERN(lzo_uint32_t)
lzo_rdtsc_asm(lzo_uint32_tp /* lzo_uint32_t ticks[2] */ );

#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */


/* vim:set ts=4 sw=4 et: */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/lzo2/public/lzo/lzo_asm.h $ $Rev: 822936 $")
#endif
