/*
 * $QNXLicenseC:
 * Copyright (c) 2017, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef _QFIM_COMMON_H_INCLUDED
#define _QFIM_COMMON_H_INCLUDED


/* --- libqfim headers --- */

/* --- Library headers --- */

/* --- System/standard library headers --- */
#include <inttypes.h>
#include <stdint.h>
#if defined (__QNXNTO__) || defined (__linux__) || defined (__LINUX__)
#include <sys/cdefs.h>
#include <sys/types.h>
#endif


#if defined (__BEGIN_DECLS) && defined (__END_DECLS)
#define __QFIM_BEGIN_DECLS  __BEGIN_DECLS
#define __QFIM_END_DECLS    __END_DECLS
#else
#if defined (__cplusplus)
#define __QFIM_BEGIN_DECLS  extern "C" {
#define __QFIM_END_DECLS    }
#else
#define __QFIM_BEGIN_DECLS
#define __QFIM_END_DECLS
#endif
#endif


__QFIM_BEGIN_DECLS


#if defined (__GNUC__)
#if (__GNUC__ + 0) >= 6
#define __QFIM_CATTR_ENUMERATOR_DEPRECATED(__MSG)   __attribute__((__deprecated__((__MSG))))
#else
#define __QFIM_CATTR_ENUMERATOR_DEPRECATED(__MSG)
#endif
#define __QFIM_CATTR_FUNC_DEPRECATED(__MSG)         __attribute__((__deprecated__((__MSG))))
#define __QFIM_CATTR_FUNC_FORMAT(__FUNC_STYLE, __FORMAT_STR_PARAM_INDEX, __FIRST_FORMATTED_PARAM_INDEX)  \
        __attribute__((__format__(__FUNC_STYLE, (__FORMAT_STR_PARAM_INDEX), (__FIRST_FORMATTED_PARAM_INDEX))))
#else
#define __QFIM_CATTR_ENUMERATOR_DEPRECATED(__MSG)
#define __QFIM_CATTR_FUNC_DEPRECATED(__MSG)
#define __QFIM_CATTR_FUNC_FORMAT(__FUNC_STYLE, __FORMAT_STR_PARAM_INDEX, __FIRST_FORMATTED_PARAM_INDEX)
#endif


/*
 * qfim_off_t is defined as an alias of a signed integer type commonly used to represent file offsets on the target platform (i.e.,
 * the type of the offset parameter passed to the preferred variant of the fseek function for that platform).
 *
 * Currently, QFIM only provides functions that accept/output 64-bit file offsets, and thus requires that the target platform
 * support 64-bit file offsets.
 *
 * ,-------------------+-----------------------+--------------------------------------+----------------------------.
 * |  Target OS        |  Target Architecture  |  Build configuration                 |  qfim_off_t defined as...  |
 * +===================+=======================+======================================+============================+
 * |  QNX Neutrino     |  aarch64              |                                      |  off_t                     |
 * |  GNU/Linux        |  x86_64               |                                      |                            |
 * |                   +-----------------------+--------------------------------------+----------------------------+
 * |                   |  armv7                | _FILE_OFFSET_BITS=64                 |  off_t                     |
 * |                   |  x86                  +--------------------------------------+----------------------------+
 * |                   |                       | _FILE_OFFSET_BITS=32 (or undefined)  |  off64_t                   |
 * |                   |                       | _LARGEFILE64_SOURCE defined          |                            |
 * `-------------------+-----------------------+--------------------------------------+----------------------------'
 */
#if defined (__QNXNTO__)

/* Don't reference _FILE_OFFSET_BITS and _LARGEFILE64_SOURCE directly, but rather __OFF_BITS__ and __EXT_LF64SRC which are set by
 * sys/platform.h based on those feature-test macros */
#if (__OFF_BITS__ + 0) == 64
typedef off_t qfim_off_t;
#elif defined (__EXT_LF64SRC)
typedef off64_t qfim_off_t;
#else
#error "Only 64-bit file offsets are currently supported; must build with _FILE_OFFSET_BITS=64 and/or __LARGEFILE64_SOURCE defined"
#endif

#elif defined (__linux__) || defined (__LINUX__)

#if defined (__x86_64__) || defined (__aarch64__) || ( (_FILE_OFFSET_BITS + 0) == 64 )
typedef off_t qfim_off_t;
#elif defined (_LARGEFILE64_SOURCE)
typedef off64_t qfim_off_t;
#else
#error "Only 64-bit file offsets are currently supported; must build with _FILE_OFFSET_BITS=64 and/or __LARGEFILE64_SOURCE defined"
#endif

#else

#error "qfim_off_t not currently defined for the target platform"

#endif


/** Number of bits in the qfim_off_t type */
#define QFIM_OFF_BITS  64

/** Minimum value of the qfim_off_t type */
#define QFIM_OFF_MIN   INT64_MIN

/** Maximum value of the qfim_off_t type */
#define QFIM_OFF_MAX   INT64_MAX

/**
 * Output conversion specifier for the qfim_off_t type; to be used in a similar fashion to the PRI* constants defined in inttypes.h
 */
#define QFIM_OFF_PRI   PRId64

/**
 * Input conversion specifier for the qfim_off_t type; to be used in a similar fashion to the SCN* constants defined in inttypes.h
 */
#define QFIM_OFF_SCN   SCNd64


/*
 * Macros for comparing qfim_off_t and size_t values
 */
#if QFIM_OFF_MAX >= SIZE_MAX
#define QFIM_OFF_EQUALS_SIZE(__OFF, __SIZE)                       ( (__OFF) == (qfim_off_t)(__SIZE) )
#define QFIM_OFF_IS_GREATER_THAN_SIZE(__OFF, __SIZE)              ( (__OFF) > (qfim_off_t)(__SIZE) )
#define QFIM_OFF_IS_GREATER_THAN_OR_EQUAL_TO_SIZE(__OFF, __SIZE)  ( (__OFF) >= (qfim_off_t)(__SIZE) )
#define QFIM_OFF_IS_LESS_THAN_SIZE(__OFF, __SIZE)                 ( (__OFF) < (qfim_off_t)(__SIZE) )
#define QFIM_OFF_IS_LESS_THAN_OR_EQUAL_TO_SIZE(__OFF, __SIZE)     ( (__OFF) <= (qfim_off_t)(__SIZE) )
#else
#define QFIM_OFF_EQUALS_SIZE(__OFF, __SIZE)                       ( ( (__OFF) >= 0 ) && ( (size_t)(__OFF) == (__SIZE) ) )
#define QFIM_OFF_IS_GREATER_THAN_SIZE(__OFF, __SIZE)              ( ( (__OFF) >= 0 ) && ( (size_t)(__OFF) > (__SIZE) ) )
#define QFIM_OFF_IS_GREATER_THAN_OR_EQUAL_TO_SIZE(__OFF, __SIZE)  ( ( (__OFF) >= 0 ) && ( (size_t)(__OFF) >= (__SIZE) ) )
#define QFIM_OFF_IS_LESS_THAN_SIZE(__OFF, __SIZE)                 ( ( (__OFF) < 0 ) || ( (size_t)(__OFF) < (__SIZE) ) )
#define QFIM_OFF_IS_LESS_THAN_OR_EQUAL_TO_SIZE(__OFF, __SIZE)     ( ( (__OFF) < 0 ) || ( (size_t)(__OFF) <= (__SIZE) ) )
#endif


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_COMMON_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/common.h $ $Rev: 823191 $")
#endif
