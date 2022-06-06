/*
 * $QNXtpLicenseC:
 * Copyright 2013, QNX Software Systems. All Rights Reserved.
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

#ifndef _IF_ALIASIOCTL_H
#define _IF_ALIASIOCTL_H

#include <net/if.h>
#include <sys/sockio.h>

#define SIOCSETALIAS SIOCSIFGENERIC
#define SIOCGETALIAS SIOCGIFGENERIC

#define ALIAS_INPUT	0x1
#define ALIAS_OUTPUT	0x2

#define ALIAS_REQ_VERSION 1
#define ALIAS_LIST_MAX 8

enum alias_ioctl_cmd {
	ALIAS_ADD_CHILD,
	ALIAS_REM_CHILD,
	ALIAS_GET_CHILDREN
};

struct alias_ioctl_get_req {
	int			version;
	enum alias_ioctl_cmd	cmd;
	int			link_type;
	int			num_children;	/* actual number of aliased children */
	char			ifnames[ALIAS_LIST_MAX * IFNAMSIZ];
};

struct alias_ioctl_set_req {
	int			version;
	enum alias_ioctl_cmd	cmd;
	int			link_type;
	char			ifname[IFNAMSIZ];
};

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/socket/public/net/if_aliasioctl.h $ $Rev: 756969 $")
#endif
