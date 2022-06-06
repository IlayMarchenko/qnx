/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * This software is QNX Confidential Information subject to
 * confidentiality restrictions. DISCLOSURE OF THIS SOFTWARE IS
 * PROHIBITED UNLESS AUTHORIZED BY QNX SOFTWARE SYSTEMS IN WRITING.
 *
 * You must obtain a written license from and pay applicable license
 * fees to QNX Software Systems before you may reproduce, modify or
 * distribute this software, or any work that includes all or part
 * of this software. For more information visit
 * http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information. $
 */

#ifndef __FS_TEMPLATE_H_INCLUDED
#define __FS_TEMPLATE_H_INCLUDED

#include <sys/platform.h>
#include <sys/types.h>

/* TODO: Place all on-disk structure definitions here */
#define TEMPLATEFS_NAME_MAX 255
#define TEMPLATEFS_DIR_LINK_MAX USHRT_MAX
#define TEMPLATEFS_SYMLINK_MAX 255
#define TEMPLATEFS_PATH_MAX PATH_MAX
#define TEMPLATEFS_MAX_FSIZE UINT_MAX

#endif /* __FS_TEMPLATE_H_INCLUDED */


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/blk/fs/template/public/sys/fs_template.h $ $Rev: 778722 $")
#endif
