/*
 * $QNXtpLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems (QSS) and its licensors.  Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by QSS by written agreement.  For more information
 * (including whether this source code file has been published) please
 * email licensing@qnx.com. $
*/


#ifndef _DRVR_FBMA_H_INCLUDED
#define _DRVR_FBMA_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#include <sys/types.h>

typedef struct fbma_attr fbma_attr_t;
typedef struct fbma_ctx  fbma_ctx_t;

typedef struct fbma_mem {
    void            *p;
    paddr_t         paddr;
    paddr64_t       paddr64;
} fbma_buf_t;


/* Fixed Block Memory Allocator main user functions
 * An instance of the allocator is created with fbma_create().  The allocator
 * behaviour is controlled via the 'fbma_attr_t attr' parameter which is
 * created/controlled with the attribute functions defined below.
 * Fixed Block Memory allocation/free is performed with the fbma_alloc()
 * and fbma_free() functions.  Finally, the allocator is destroyed with the
 * fbma_destroy() function
 */

fbma_ctx_t * fbma_create( fbma_attr_t * attr );
void         fbma_destroy( fbma_ctx_t * hdl );
void *       fbma_alloc( fbma_ctx_t * hdl, fbma_buf_t * buf );
void         fbma_free( fbma_ctx_t * hdl, void * p );

/* Fixed Block Memory Allocator Attribute Functions
 * An attribute struture is created with the fbm_attr_create() function.
 * The The attributes can get set/read with the accessor functions.
 * Finally, the attribute structure is destroyed with fbma_attr_destroy()
 *
 */

/* attributes */
#define FBMA_FLAG_NOCACHE           0x1
#define FBMA_FLAG_MPHYS             0x2
#define FBMA_FLAG_MPHYS64           0x4
#define FBMA_FLAG_SHARED            0x8
#define FBMA_FLAG_NOCROSS_PAGE      0x10

#define FBMA_BLKSZ_MIN              4
#define FBMA_PAGESZ_MIN             256
#define FBMA_ALIGN_MIN              4


/* prototypes */
fbma_attr_t * fbma_attr_create( void );
void          fbma_attr_destroy( fbma_attr_t * attr );

int           fbma_attr_flags_set( fbma_attr_t * attr, int flags );
int           fbma_attr_flags_get( fbma_attr_t * attr );
int           fbma_attr_blksz_set( fbma_attr_t * attr, size_t blksz );
size_t        fbma_attr_blksz_get( fbma_attr_t * attr );
int           fbma_attr_nblk_set( fbma_attr_t * attr, size_t nblk );
size_t        fbma_attr_nblk_get( fbma_attr_t * attr );
int           fbma_attr_align_set( fbma_attr_t * attr, size_t align );
size_t        fbma_attr_align_get( fbma_attr_t * attr );
int           fbma_attr_maxpool_set( fbma_attr_t * attr, size_t max );
size_t        fbma_attr_maxpool_get( fbma_attr_t * attr );
int           fbma_attr_pagesz_set( fbma_attr_t * attr, size_t pagesz );
size_t        fbma_attr_pagesz_get( fbma_attr_t * attr );


#endif  /* _DRVR_FBMA_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/usb/public/sys/fbma.h $ $Rev: 756950 $")
#endif
