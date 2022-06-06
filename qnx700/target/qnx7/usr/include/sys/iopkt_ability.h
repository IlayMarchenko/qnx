/*
 * $QNXLicenseC:
 * Copyright 2012 QNX Software Systems. All Rights Reserved.
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
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef __IOPKT_ABILITY_H_INCLUDED
#define __IOPKT_ABILITY_H_INCLUDED

#define _IOPKT_ABILITY_NW_BIND_PRIVPORT		"network/bind/privport"
#define _IOPKT_ABILITY_NW_INTERFACE_GETPRIV	"network/interface/getpriv"
#define _IOPKT_ABILITY_NW_INTERFACE_SETPRIV	"network/interface/setpriv"
#define _IOPKT_ABILITY_NW_ROUTE_SET		"network/route/set"
#define _IOPKT_ABILITY_NW_SOCKET_RAWSOCK	"network/socket/rawsock"

#ifdef _KERNEL
#define _IOPKT_ABILITY_INVALID			(-1)


#define QNX_DROPROOT_STD		0x0001
#define QNX_DROPROOT_INTERRUPT		0x0002
#define QNX_DROPROOT_CONNECTION		0x0004
#define QNX_DROPROOT_TIMER		0x0008
#define QNX_DROPROOT_PROT_EXEC		0x0010
#define QNX_DROPROOT_PATHSPACE		0x0020
#define QNX_DROPROOT_QNET		0x0040
#define QNX_DROPROOT_PUBLIC_CHANNEL	0x0080
#endif


#endif /* __IO_PKT_ABILITY_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/sys/sys/iopkt_ability.h $ $Rev: 771217 $")
#endif
