/* xtinfo.h internal header */
#ifndef _XTINFO
#define _XTINFO
#include <time.h>
#include <sys/platform.h>
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

		/* type definitions */
typedef struct
	{	/* format strings for date and time */
	const char *_Am_pm;
	const char *_Days;
		const char *_Abday;
		const char *_Day;
	const char *_Months;
		const char *_Abmon;
		const char *_Mon;
	const char *_Formats;
		const char *_D_t_fmt;
		const char *_D_fmt;
		const char *_T_fmt;
		const char *_T_fmt_ampm;
	const char *_Era_Formats;
		const char *_Era_D_t_fmt;
		const char *_Era_D_fmt;
		const char *_Era_T_fmt;
		const char *_Era_T_fmt_ampm;
	const char *_Era;
	const char *_Alt_digits;
	const char *_Isdst;
	const char *_Tzone;
#ifdef __QNX__
	const char *_Reserved[8];
#endif /* __QNX__ */
	} _Tinfo;

		/* declarations */
__BEGIN_DECLS
size_t _CStrftime(char *, size_t, const char *,
	const struct tm *, const _Tinfo *);
#ifdef __QNX__
extern _Tinfo _Times;
#endif /* __QNX__ */
_Tinfo *_Getptimes(void);
__END_DECLS
#endif /* _XTINFO */

/*
 * Copyright (c) 1992-2013 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V6.40:1566 */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/c/public/xtinfo.h $ $Rev: 806926 $")
#endif
