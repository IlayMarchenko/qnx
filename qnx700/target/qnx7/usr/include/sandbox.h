/*
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
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

#ifndef __SANDBOX_H__
#define __SANDBOX_H__

#include <stdint.h>
#include <sys/types.h>

/**
 * A binary representation of a sandbox rule.
 * The @sr_action field holds either EOK to accept a match or EACCES to reject a
 * match. @sr_len is the length of the GLB pattern, including a terminating NUL,
 * and @sr_pattern is the NUL-terminated GLOB pattern itself.
 */
typedef struct
{
	uint16_t	sr_action;
	uint16_t	sr_len;
	char		sr_pattern[];
} sandbox_rule_t;

extern int 	sandbox_parse_config(const char *__config, size_t __conflen,
								 iov_t *__iov, unsigned *__versionp);
extern void	sandbox_done_config(iov_t *__iov);

extern int	sandbox_create(const char *__confpath);
extern int	sandbox_attach(int __sbid, pid_t __pid);
extern int	sandbox_delete(int __sbid);

static inline size_t
sandbox_rule_align(size_t len)
{
	len += sizeof(sandbox_rule_t);
	return (len + sizeof(uintptr_t) - 1) & ~(sizeof(uintptr_t) - 1);
}

static inline sandbox_rule_t *
sandbox_rule_next(sandbox_rule_t * const rule)
{
	const size_t		len = sandbox_rule_align(rule->sr_len);
	const uintptr_t		r = (uintptr_t)rule + len;

	return (sandbox_rule_t *)r;
}

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/sandbox/public/sandbox.h $ $Rev: 789196 $")
#endif
