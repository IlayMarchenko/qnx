/*
 * Copyright 2016, QNX Software Systems.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 */

#ifndef _TPM_HELPERS_H_INCLUDED
#define _TPM_HELPERS_H_INCLUDED

/* sorted headers from this project */

/* sorted system headers */
#ifndef _GULLIVER_H_INCLUDED
#include <gulliver.h>
#endif

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

typedef uint16_t uint16_be_t;
typedef uint32_t uint32_be_t;
typedef uint64_t uint64_be_t;
typedef uint16_t uint16_le_t;
typedef uint32_t uint32_le_t;
typedef uint64_t uint64_le_t;

#define ENDIAN_RET16_HDR(__x) (typeof(__x))((((__x) >> 8) & 0xff) | \
                                            (((__x) & 0xff) << 8))

#define ENDIAN_RET32_HDR(__x) (typeof(__x))((((__x) >> 24) & 0xff) | \
                                            (((__x) >> 8) & 0xff00) | \
                                            (((__x) & 0xff00) << 8) | \
                                            (((__x) & 0xff) << 24))

#define ENDIAN_RET64_HDR(__x) (typeof(__x))((((__x) >> 56) & 0xffull) | \
                                            (((__x) >> 40) & 0xff00ull) | \
                                            (((__x) >> 24) & 0xff0000ull) | \
                                            (((__x) >>  8) & 0xff000000ull) | \
                                            (((__x) & 0xff000000ull) <<  8) | \
                                            (((__x) & 0xff0000ull) << 24) | \
                                            (((__x) & 0xff00ull) << 40) | \
                                            (((__x) & 0xffull) << 56))

/* The following macros are versions of the non _HDR macros defined in NTO, but that can be used
 * in all headers, being processed by the pre-processor.  The non _HDR functions cannot be used this
 * way because in some architectures, the macros end up executing code. */
#if defined(__LITTLEENDIAN__)
#define ENDIAN_BE16_HDR(__x) ((uint16_t)(ENDIAN_RET16_HDR(__x)))
#define ENDIAN_BE32_HDR(__x) ((uint32_t)(ENDIAN_RET32_HDR(__x)))
#define ENDIAN_BE64_HDR(__x) ((uint64_t)(ENDIAN_RET64_HDR(__x)))
#define ENDIAN_LE16_HDR(__x) ((uint16_t)(__x))
#define ENDIAN_LE32_HDR(__x) ((uint32_t)(__x))
#define ENDIAN_LE64_HDR(__x) ((uint64_t)(__x))
#else
#define ENDIAN_BE16_HDR(__x) ((uint16_t)(__x))
#define ENDIAN_BE32_HDR(__x) ((uint32_t)(__x))
#define ENDIAN_BE64_HDR(__x) ((uint64_t)(__x))
#define ENDIAN_LE16_HDR(__x) ((uint16_t)(ENDIAN_RET16_HDR(__x)))
#define ENDIAN_LE32_HDR(__x) ((uint32_t)(ENDIAN_RET32_HDR(__x)))
#define ENDIAN_LE64_HDR(__x) ((uint64_t)(ENDIAN_RET64_HDR(__x)))
#endif

#define native_to_be16(x) ((uint16_be_t)ENDIAN_BE16((uint16_t)x))
#define native_to_be32(x) ((uint32_be_t)ENDIAN_BE32((uint32_t)x))
#define native_to_be64(x) ((uint64_be_t)ENDIAN_BE64((uint64_t)x))
#define native_to_be16_hdr(x) ((uint16_be_t)ENDIAN_BE16_HDR((uint16_t)x))
#define native_to_be32_hdr(x) ((uint32_be_t)ENDIAN_BE32_HDR((uint32_t)x))
#define native_to_be64_hdr(x) ((uint64_be_t)ENDIAN_BE64_HDR((uint64_t)x))
#define be16_to_native(x) ((uint16_t)ENDIAN_BE16((uint16_be_t)x))
#define be32_to_native(x) ((uint32_t)ENDIAN_BE32((uint32_be_t)x))
#define be64_to_native(x) ((uint64_t)ENDIAN_BE64((uint64_be_t)x))
#define be16_to_native_hdr(x) ((uint16_t)ENDIAN_BE16_HDR((uint16_be_t)x))
#define be32_to_native_hdr(x) ((uint32_t)ENDIAN_BE32_HDR((uint32_be_t)x))
#define be64_to_native_hdr(x) ((uint64_t)ENDIAN_BE64_HDR((uint64_be_t)x))

#define native_to_le16(x) ((uint16_le_t)ENDIAN_LE16((uint16_t)x))
#define native_to_le32(x) ((uint32_le_t)ENDIAN_LE32((uint32_t)x))
#define native_to_le64(x) ((uint64_le_t)ENDIAN_LE64((uint64_t)x))
#define native_to_le16_hdr(x) ((uint16_le_t)ENDIAN_LE16_HDR((uint16_t)x))
#define native_to_le32_hdr(x) ((uint32_le_t)ENDIAN_LE32_HDR((uint32_t)x))
#define native_to_le64_hdr(x) ((uint64_le_t)ENDIAN_LE64_HDR((uint64_t)x))
#define le16_to_native(x) ((uint16_t)ENDIAN_LE16((uint16_le_t)x))
#define le32_to_native(x) ((uint32_t)ENDIAN_LE32((uint32_le_t)x))
#define le64_to_native(x) ((uint64_t)ENDIAN_LE64((uint64_le_t)x))
#define le16_to_native_hdr(x) ((uint16_t)ENDIAN_LE16_HDR((uint16_le_t)x))
#define le32_to_native_hdr(x) ((uint32_t)ENDIAN_LE32_HDR((uint32_le_t)x))
#define le64_to_native_hdr(x) ((uint64_t)ENDIAN_LE64_HDR((uint64_le_t)x))

#define helpers_ms_to_ns(ms_time) ((uint64_t)ms_time * (uint64_t)1000000)
#define helpers_us_to_ns(us_time) ((uint64_t)us_time * (uint64_t)1000)

#define sizeof_member(composite, member) sizeof(((composite *)0)->member)

/* This function returns true if we should continue polling and false otherwise.  If we stop polling
 * then error_condition is set to true if an error occurred and false otherwise.  If an error
 * occurrred, errno will be set. */
typedef int helpers_poll_check_cb_ft(void *poll_data, bool *continue_polling);
typedef helpers_poll_check_cb_ft * helpers_poll_check_cb_f;

typedef uint64_t helpers_get_monotonic_time_ft(uint64_t forward_offset_ns);
typedef helpers_get_monotonic_time_ft * helpers_get_monotonic_time_f;

typedef int helpers_nssleep_ft(uint64_t sleep_time_ns, uint64_t max_monotonic_time_ns);
typedef helpers_nssleep_ft * helpers_nssleep_f;

typedef int helpers_poll_until_ft(uint64_t polling_time_ns, uint64_t monotonic_timeout_ns, helpers_poll_check_cb_f poll_check_f, void *poll_data);
typedef helpers_poll_until_ft * helpers_poll_until_f;

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _TPM_HELPERS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/tpm/public/tpm/helpers.h $ $Rev: 820218 $")
#endif
