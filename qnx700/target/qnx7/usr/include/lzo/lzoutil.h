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

/* lzoutil.h -- utilitiy functions for use by applications [DEPRECATED]

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2014 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
 */


#ifndef __LZOUTIL_H_INCLUDED
#define __LZOUTIL_H_INCLUDED 1

#ifndef __LZOCONF_H_INCLUDED
#include "lzoconf.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
// LZO-v1 deprecated macros (which were used in the old example programs)
// DO NOT USE
************************************************************************/

#define lzo_alloc(a,b)      (malloc((a)*(b)))
#define lzo_malloc(a)       (malloc(a))
#define lzo_free(a)         (free(a))

#define lzo_fread(f,b,s)    (fread(b,1,s,f))
#define lzo_fwrite(f,b,s)   (fwrite(b,1,s,f))


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* already included */


/* vim:set ts=4 sw=4 et: */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/lzo2/public/lzo/lzoutil.h $ $Rev: 822936 $")
#endif
