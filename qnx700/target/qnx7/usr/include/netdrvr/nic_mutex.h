/*
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef _NETDRVR_NIC_MUTEX_H_INCLUDED
#define _NETDRVR_NIC_MUTEX_H_INCLUDED

#include <stdbool.h>

/* io-pkt pseudo-thread safe mutex for devnp drivers
 * These functions must only be used within the stack context.
 */
typedef unsigned nic_mutex_t;

/* nic_mutex_t variables must be initialized to one of these values before
 * they are used. The initial state (locked/unlocked) depends on the value
 * used.
 */
#define NIC_MUTEX_UNLOCKED_VALUE 0x20141203U
#define NIC_MUTEX_LOCKED_VALUE   0x10CC4B1DU

/* Lock mutex without blocking the stack, if possible
 *
 * Error conditions are handled internally and they result in io-pkt panic.
 */
void nic_mutex_lock(nic_mutex_t *mutex);

/* Try to lock mutex, but do not block
 *
 * The function retuns:
 *  true  if it was able to lock the mutex
 *  false if it was unable to lock the mutex
 *
 * Error conditions are handled internally and they result in io-pkt panic.
 */
bool nic_mutex_trylock(nic_mutex_t *mutex);

/* Unlock mutex
 *
 * Error conditions are handled internally and they result in io-pkt panic.
 */
void nic_mutex_unlock(nic_mutex_t *mutex);

#endif /* _NETDRVR_NIC_MUTEX_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/sys/lib/libnetdrvr/public/netdrvr/nic_mutex.h $ $Rev: 773095 $")
#endif
