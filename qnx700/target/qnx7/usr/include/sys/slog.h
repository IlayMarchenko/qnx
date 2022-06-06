/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __SLOG_H_INCLUDED
#define __SLOG_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define _SLOG_SHUTDOWN  0   /* Shut down the system NOW. eg: for OEM use */
#define _SLOG_CRITICAL  1   /* Unexpected unrecoverable error. eg: hard disk error */
#define _SLOG_ERROR     2   /* Unexpected recoverable error. eg: needed to reset a hw controller */
#define _SLOG_WARNING   3   /* Expected error. eg: parity error on a serial port */
#define _SLOG_NOTICE    4   /* Warnings. eg: Out of paper */
#define _SLOG_INFO      5   /* Information. eg: Printing page 3 */
#define _SLOG_DEBUG1    6   /* Debug messages eg: Normal detail */
#define _SLOG_DEBUG2    7   /* Debug messages eg: Fine detail */

#define _SLOG_SEVMAXVAL 0x7 /* The largest number for severity field */


/*
** Each log event contains an opcode field followed by a time
** field in seconds and a count and severity and msec field. Data follows...
** Count is in 32 bit words.
**
** p        cccccccc   mmmmmm mmmmtsss   [p]id [c]ount,[m]sec,[t]ext,[s]everity
** mmmmmmmm mmmmMMMM MMMMMMMM MMMMMMMM   [m]inor,[M]ajor
** SSSSSSSS SSSSSSSS SSSSSSSS SSSSSSSS   [S]econds
*/
#define _SLOG_HDRINTS               3
#define _SLOG_GETSEC(op)            (op)
#define _SLOG_GETMSEC(op)           (((op)>>4)&0x3ff)
#define _SLOG_GETCOUNT(op)          (((op) >> 16) & 0xff)
#define _SLOG_GETTEXT(op)           ((op) & 0x8)
#define _SLOG_TEXTBIT               0x8
#define _SLOG_PIDBIT                0x80000000
#define _SLOG_GETSEVERITY(op)       ((op) & 0x7)
#define _SLOG_GETMINOR(op)          (((op) >> 20) & 0xfff)
#define _SLOG_GETMAJOR(op)          ((op) & 0xfffff)
#define _SLOG_SETCODE(ma, mi)       ((ma) | ((mi) << 20))

#define _SLOG_MAXSIZE                ((0xff+3-1)*sizeof(int))    /* Maximum event size in bytes */

typedef struct {
	int        pid;
	int        tid;
	unsigned   sec;    /* From 1980 */
	unsigned   msec;
	int        severity;
	int        major;
	int        minor;
	int        len;
	int        residual;  /* Non-zero means the event was split across a buffer. */
	unsigned   flags;
	char      *buf;
} slogdecode_t;

/* Flag definitions */
#define _SLOGDECODE_ISTEXT 0x01
#define _SLOGDECODE_ISPID  0x02

__BEGIN_DECLS

int slogb(int code, int severity, void *data, int size);
int vslogf(int code, int severity, const char *fmt, __NTO_va_list __arg ) __attribute__((__format__(__printf__, 3, 0)));
int slogf(int code, int severity, const char *fmt, ...) __attribute__((__format__(__printf__, 3, 4)));
int slogi(int code, int severity, int nargs, ...);
int slogdecode(char *buf, int len, slogdecode_t *rec);
extern int _slogfd;

__END_DECLS

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/sys/slog.h $ $Rev: 780356 $")
#endif
