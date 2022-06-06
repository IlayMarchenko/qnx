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

#ifndef TARGET_NTO_MFIB_H_
#define TARGET_NTO_MFIB_H_

#ifdef _KERNEL
#include <sys/mbuf.h>

#ifdef QNX_MFIB

static __inline void m_tag_set_fibmask(struct m_tag *mtag, int fibmask);
static __inline struct m_tag *m_tag_set_fibmask_mtag(struct mbuf *m, int fibmask);
static __inline struct m_tag *m_tag_get_fibmask_mtag(struct mbuf *m);
static __inline int m_tag_get_fibmask(struct m_tag *mtag);

static __inline struct m_tag *m_tag_set_fibmask_mtag(struct mbuf *m, int fibmask)
{
	struct m_tag *mtag;
	mtag = m_tag_get(PACKET_TAG_FIBMASK, sizeof(fibmask), M_NOWAIT);
	if (mtag == NULL) {
		return NULL;
	}
	m_tag_set_fibmask(mtag, fibmask);
	m_tag_prepend(m, mtag);

	return mtag;
}

static __inline struct m_tag *m_tag_get_fibmask_mtag(struct mbuf *m)
{
	return m_tag_find(m, PACKET_TAG_FIBMASK, NULL);
}

static __inline int m_tag_get_fibmask(struct m_tag *mtag)
{
	if (!mtag) {
		return -1;
	} else {
		return (*(int *)(mtag + 1));
	}
}

static __inline void m_tag_set_fibmask(struct m_tag *mtag, int fibmask)
{
	if (!mtag)
		return;

	(*(int*)(mtag + 1)) = fibmask;
}

#endif /* QNX_MFIB */
#endif /* _KERNEL */

#endif /* TARGET_NTO_MFIB_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/socket/public/sys/target_nto_mfib.h $ $Rev: 756969 $")
#endif
