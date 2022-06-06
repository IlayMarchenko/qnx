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

/* lzo1a.h -- public interface of the LZO1A compression algorithm

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2014 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */


#ifndef __LZO1A_H_INCLUDED
#define __LZO1A_H_INCLUDED 1

#ifndef __LZOCONF_H_INCLUDED
#include "lzoconf.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
//
************************************************************************/

/* Memory required for the wrkmem parameter.
 * When the required size is 0, you can also pass a NULL pointer.
 */

#define LZO1A_MEM_COMPRESS      ((lzo_uint32_t) (8192L * lzo_sizeof_dict_t))
#define LZO1A_MEM_DECOMPRESS    (0)


LZO_EXTERN(int)
lzo1a_compress          ( const lzo_bytep src, lzo_uint  src_len,
                                lzo_bytep dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem );

LZO_EXTERN(int)
lzo1a_decompress        ( const lzo_bytep src, lzo_uint  src_len,
                                lzo_bytep dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem /* NOT USED */ );


/***********************************************************************
// better compression ratio at the cost of more memory and time
************************************************************************/

#define LZO1A_99_MEM_COMPRESS   ((lzo_uint32_t) (65536L * lzo_sizeof_dict_t))

LZO_EXTERN(int)
lzo1a_99_compress       ( const lzo_bytep src, lzo_uint  src_len,
                                lzo_bytep dst, lzo_uintp dst_len,
                                lzo_voidp wrkmem );



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */


/* vim:set ts=4 sw=4 et: */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/lzo2/public/lzo/lzo1a.h $ $Rev: 822936 $")
#endif
