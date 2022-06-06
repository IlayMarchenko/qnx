/*
 * $QNXLicenseC:
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



/*
 *  dcmd_ptpd.h   QNX devctl definitions
 *

 */
#ifndef __DCMD_PTPD_H_INCLUDED
#define __DCMD_PTPD_INCLUDED

#include <devctl.h>
#include <stdint.h>

#define DCMD_PTPD_DELAYMS				__DIOF(_DCMD_NET, 10, MyTimeInternal )
#define DCMD_PTPD_DELAYSM				__DIOF(_DCMD_NET, 11, MyTimeInternal )
#define DCMD_PTPD_STATUS				__DIOF(_DCMD_NET, 12, MyStatusInternal )
#define DCMD_PTPD_INFO					__DIOF(_DCMD_NET, 13, MyPTPDINFOInternal )
#define DCMD_PTPD_SET_PDELAY_INTERVAL	__DIOT(_DCMD_NET, 14, MyPDelayIntervalInternal )
#define DCMD_PTPD_GET_TIME				__DIOF(_DCMD_NET, 15, MyTimeInternal )
#define DCMD_PTPD_SEND_SIGNALING_MSG	__DION(_DCMD_NET, 16 )
#define DCMD_PTPD_GET_PDELAY_INTERVAL	__DIOF(_DCMD_NET, 17, MyPDelayIntervalInternal )

#define DEFAULT_PTPD_PATH		"/dev/ptpd"


/**
* \brief Time structure to handle Linux time information
 */
typedef struct {
	uint32_t seconds;
	uint32_t nanoseconds;
} MyTimeInternal;

#define PTPD_STATUS_NO_ERROR				0x00
#define PTPD_STATUS_LINK_DOWN				0x01
#define PTPD_STATUS_GRANDMASTER_FAILURE		0x02
/**
* \brief PTP internal Status structure
 */
typedef uint32_t		MyStatusInternal;

/**
* \brief PTP information structure
 */
typedef struct {
	int64_t peerdelay;
	int32_t neighborrateratio;
	uint8_t	neighborrateratio_valid;
} MyPTPDINFOInternal;

/**
* \brief PTP PDelay Interval structure
 */
typedef uint32_t		MyPDelayIntervalInternal;

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/services/ptpd/ptpd/public/dcmd_ptpd.h $ $Rev: 794323 $")
#endif
