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
 *  dcmd_all.h   Non-portable low-level devctl definitions
 *

 */
#ifndef __DCMD_ALL_H_INCLUDED
#define __DCMD_ALL_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
 #include <devctl.h>
#endif

#if defined(__OFF64_T)
typedef __OFF64_T	off64_t;
#undef __OFF64_T
#endif

#include <_pack64.h>


/*
 * Desc:  This call gets O_ status flags as described in <fcntl.h>.
 * Args:  Pointer to int in which flags are returned.
 * Notes: Clients usually use fcntl(fd, F_GETFL); cover function
 *        to generate this request.
 */
#define DCMD_ALL_GETFLAGS		__DIOF(_DCMD_ALL, 1, int)

/*
 * Desc:  This call sets O_ status flags as described in <fcntl.h>.
 * Args:  Pointer to int from which flags are taken.
 * Notes: Clients usually use fcntl(fd, F_SETFL, flags); cover function
 *        to generate this request.
 */
#define DCMD_ALL_SETFLAGS		__DIOT(_DCMD_ALL, 2, int)


/*
 * Desc:  This call gets mount ST_* mount Flags as described in
 *        <sys/statvfs.h>
 * Args:  Pointer to int in which flags are returned.
 * Notes: Sometimes generated by access() to determine write or
 *        execute modes.
 */
#define DCMD_ALL_GETMOUNTFLAGS	__DIOF(_DCMD_ALL, 3, int)

/*
 * Desc:  Get 'owner' of fd.
 * Args:  Pointer to pid_t in which current owner is returned.
 * Notes: Clients usually use fcntl(fd, F_GETOWN); cover function
 *        to generate this request.  Generally used WRT sockets
 *        where 'owner' will receive SIGIO and SIGURG signals.
 */
#define DCMD_ALL_GETOWN	__DIOF(_DCMD_ALL, 4, pid_t)

/*
 * Desc:  Set 'owner' of fd.
 * Args:  Pointer to pid_t from which current owner is taken.
 * Notes: Clients usually use fcntl(fd, F_SETOWN, pid); cover
 *        to generate this request.
 * 
 */
#define DCMD_ALL_SETOWN	__DIOT(_DCMD_ALL, 5, pid_t)

/*
 * Desc:  Pass file advice to filesystem
 * Args:  Pointer to struct _fadvise with advice filled
 * Notes: Clients usually use posix_fadvise(fd, offset, len, advice);
 *        cover to generate this request
 */
struct _fadvise {
	int				advice;
	int				spare;
	off64_t			offset;
	off64_t			len;
};
#define DCMD_ALL_FADVISE __DIOT(_DCMD_ALL, 6, struct _fadvise)

#include <_packpop.h>

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/sys/dcmd_all.h $ $Rev: 780356 $")
#endif
