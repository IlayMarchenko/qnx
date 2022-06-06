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
 *  search.h    Function prototypes for searching functions
 *

 */
#ifndef _SEARCH_H_INCLUDED
#define _SEARCH_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__SIZE_T)
typedef __SIZE_T    size_t;
#undef __SIZE_T
#endif

typedef struct {
        char    *key;
	void    *data;

} ENTRY;

typedef enum { FIND, ENTER } ACTION;
typedef enum { preorder, postorder, endorder, leaf } VISIT;

__BEGIN_DECLS

extern ENTRY *hsearch (ENTRY __item, ACTION __action);
extern void *lfind(const void *__key, const void *__base, size_t *__num, size_t __width, int (* __compare)(const void *, const void *));
extern void *lsearch(const void *__key, void *__base, size_t *__num, size_t __width, int (* __compare)(const void *, const void *));
extern void *tdelete(const void *__key, void **__rootp, int (*__compar)(const void *, const void *));
extern void *tfind(const void *__key, void *const *__rootp, int (*__compar)(const void *, const void *));
extern void *tsearch(const void *__key, void **__rootp, int (*__compar)(const void *, const void *));
extern int hcreate(size_t __nel);
extern void hdestroy(void);
#if defined(__EXT_XOPEN_EX)
extern void insque(void *__element, void *__pred);
extern void remque(void *__element);
#endif
extern void twalk(const void *__root, void (*__action)(const void *, VISIT, int));

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/search.h $ $Rev: 806926 $")
#endif
