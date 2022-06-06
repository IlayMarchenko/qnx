/*
 * $QNXLicenseC:
 * Copyright (c) 2016-2017, QNX Software Systems. All Rights Reserved.
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


#ifndef _QFIM_HASH_H_INCLUDED
#define _QFIM_HASH_H_INCLUDED


/* --- libqfim headers --- */
#include <qfim/common.h>

/* --- Library headers --- */

/* --- System/standard library headers --- */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


__QFIM_BEGIN_DECLS


/** Enumeration of supported hash algorithms */
typedef enum qfim_hash_alg_e {
    QFIM_HASH_ALG_INVALID = -1,
    QFIM_HASH_ALG_NONE,
    QFIM_HASH_ALG_SHA256,
    QFIM_HASH_ALG_SHA384,
    QFIM_HASH_ALG_SHA512,
    QFIM_NUM_HASH_ALGS,
} qfim_hash_alg_t;


#define QFIM_NONE_DIGEST_VALUE_LENGTH    0
#define QFIM_SHA256_DIGEST_VALUE_LENGTH  32
#define QFIM_SHA384_DIGEST_VALUE_LENGTH  48
#define QFIM_SHA512_DIGEST_VALUE_LENGTH  64
#define QFIM_MAX_DIGEST_VALUE_LENGTH     QFIM_SHA512_DIGEST_VALUE_LENGTH


/**
 * Digest value, along with the associated hash algorithm used to produce it. The digest value is represented as an array of bytes
 * large enough to accommodate the digest of any of the supported hash algorithms. The digest length associated with a particular
 * hash algorithm can be determined via the qfim_get_digest_value_length function. */
typedef struct qfim_digest_s {
    qfim_hash_alg_t hash_alg;
    uint8_t         value[QFIM_MAX_DIGEST_VALUE_LENGTH];
} qfim_digest_t;


/**
 * Initializer for a qfim_digest_t object. Puts the into the same state as a call to the qfim_digest_set function with
 * __hash_alg == QFIM_HASH_ALG_NONE.
 */
#define QFIM_DIGEST_NONE_INITIALIZER  {}


/** Type representing an instance of the stateful QFIM hasher interface */
typedef struct qfim_hasher_s qfim_hasher_t;


/**
 * Returns a null-terminated string representing the display name of the specified hash algorithm.
 *
 * @param[in]  __hash_alg  Hash algorithm.
 *
 * @return  Display name of the specified hash algorithm, or NULL if __hash_alg < 0 or __hash_alg >= QFIM_NUM_HASH_ALGS.
 */
const char *qfim_hash_alg_get_name(qfim_hash_alg_t __hash_alg);


/**
 * Returns a null-terminated string representing a symbolic name of the specified hash algorithm (e.g., for command line arguments).
 *
 * @param[in]  __hash_alg  Hash algorithm.
 *
 * @return  Symbolic name of the specified hash algorithm, or NULL if __hash_alg < 0 or __hash_alg >= QFIM_NUM_HASH_ALGS.
 */
const char *qfim_hash_alg_get_token(qfim_hash_alg_t __hash_alg);


/**
 * Returns the digest value size corresponding to the specified hash algorithm.
 *
 * @param[in]  __hash_alg  Hash algorithm.
 *
 * @retval  QFIM_SHA256_DIGEST_VALUE_LENGTH  when __hash_alg == QFIM_HASH_ALG_SHA256,
 * @retval  QFIM_SHA384_DIGEST_VALUE_LENGTH  when __hash_alg == QFIM_HASH_ALG_SHA384,
 * @retval  QFIM_SHA512_DIGEST_VALUE_LENGTH  when __hash_alg == QFIM_HASH_ALG_SHA512, and
 * @retval  0                                in all other cases.
 */
size_t qfim_hash_alg_get_digest_value_length(qfim_hash_alg_t __hash_alg);


/**
 * Returns the hash algorithm whose symbolic name matches the specified string (e.g., from command line arguments).
 *
 * @param[in]  __token  String to convert to a hash algorithm.
 *
 * @return  Hash algorithm whose symbolic name matches the specified string, or QFIM_HASH_ALG_INVALID if there is no such hash
 *          algorithm or __token is specified as NULL.
 */
qfim_hash_alg_t qfim_hash_alg_from_token(const char *__token);


/**
 * Sets the digest to the specified hash algorithm and value.
 *
 * @param[out]  __digest        Digest.
 * @param[in]   __hash_alg      Hash algorithm.
 * @param[in]   __digest_value  Digest value. The length of the digest value in bytes is determined from the specified hash
 *                              alogrithm and will be at most QFIM_MAX_DIGEST_VALUE_LENGTH. May be NULL only if __hash_alg is
 *                              specified as QFIM_HASH_ALG_NONE.
 *
 * @retval  EOK     Success. __digest now contains the specified hash algorithm and digest value, and any bytes beyond the valid
 *                  digest length for that hash algorithm are zeroed out.
 * @retval  EINVAL  Invalid argument(s) (__digest == NULL, __hash_alg not one of the valid hash algorithms defined in enum
 *                  qfim_hash_alg_e and/or __digest_value == NULL for any hash algorithm other than QFIM_HASH_ALG_NONE).
 */
int qfim_digest_set(
        qfim_digest_t   *__digest,
        qfim_hash_alg_t  __hash_alg,
        const uint8_t   *__digest_value);


/**
 * Compares two digests and returns true if they are equal.
 *
 * @param[in]  __left_digest   Left-hand digest operand of the comparison.
 * @param[in]  __right_digest  Right-hand digest operand of the comparison.
 *
 * @return  true if both digests have the same hash algorithm and the same digest value, or if both are NULL. false if either digest
 *          specifies an invalid hash algorithm.
 */
bool qfim_digest_equals(
        const qfim_digest_t *__left_digest,
        const qfim_digest_t *__right_digest);


/**
 * Creates a hasher instance.
 *
 * @param[out]  __new_hasher  Populated with a newly created hasher instance on success, otherwise set to NULL.
 *
 * @retval  EOK     Success. *__new_hasher contains a pointer to the newly created hasher instance. The caller is responsible for
 *                  destroying the hasher instance by passing it to qfim_hasher_destroy when it is no longer needed.
 * @retval  EINVAL  __new_hasher specified as NULL.
 */
int qfim_hasher_create(qfim_hasher_t **__new_hasher);


/**
 * Resets the specified hasher. Any digest calculation already in progress is cancelled.
 *
 * @param[in,out]  __hasher  Hasher instance.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __hasher specified as NULL.
 */
int qfim_hasher_reset(qfim_hasher_t *__hasher);


/**
 * Initiates a new digest calculation using the specified has algorithm.
 *
 * @param[in,out]  __hasher    Hasher instance. Any digest calculation already in progress is discarded.
 * @param[in]      __hash_alg  Hash algorithm.
 *
 * @retval  EOK      Success.
 * @retval  EINVAL   __hasher specified as NULL or __hash_alg is not one of the valid hash alogrithms in qfim_hash_alg_t.
 * @retval  ENOTSUP  The specified hash algorithm is not supported by the underlying cryptographic library.
 * @retval  EIO      An unexpected failure was detected in the underlying cryptographic library.
 */
int qfim_hasher_digest_begin(
        qfim_hasher_t   *__hasher,
        qfim_hash_alg_t  __hash_alg);


/**
 * Updates an in-progress digest calculation using the specified data. If this function returns a value other than EOK, any
 * in-progress digest calculation is cancelled.
 *
 * @param[in,out]  __hasher     Hasher instance.
 * @param[in]      __data       Pointer to the data to incorporate into the digest calculation.
 * @param[in]      __data_size  Size of the data to incorporate into the digest calculation.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __hasher specified as NULL, or __data == NULL and __data_size > 0 specified.
 * @retval  EPROTO  A digest calculation is not currently in progress.
 * @retval  EIO     An unexpected failure was detected in the underlying cryptographic library.
 */
int qfim_hasher_digest_update(
        qfim_hasher_t *__hasher,
        const void    *__data,
        size_t         __data_size);


/**
 * Returns the hash algorithm of the digest calculation currently in progress for the specified hasher instance.
 *
 * @param[in]  __hasher  Hasher instance.
 *
 * @return  The hash algorithm of the in-progress digest calculation, or QFIM_HASH_ALG_INVALID if either __hasher is specified as
 *          NULL or there is no digest calculation currently in progress.
 */
qfim_hash_alg_t qfim_hasher_get_hash_alg_in_progress(const qfim_hasher_t *__hasher);


/**
 * Completes an in-progress digest calculation and outputs the resulting digest. If this function returns a value other than EOK,
 * any in-progress digest calculation is cancelled.
 *
 * @param[in,out]  __hasher  Hasher instance.
 * @param[out]     __digest  Resulting digest. Only populated if this function returns EOK.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __hasher or __digest specified as NULL.
 * @retval  EPROTO  A digest calculation is not currently in progress.
 * @retval  EIO     An unexpected failure was detected in the underlying cryptographic library.
 */
int qfim_hasher_digest_end(
        qfim_hasher_t *__hasher,
        qfim_digest_t *__digest);


/**
 * Computes the digest of the specified data. Any in-progress digest calculation is cancelled.
 *
 * @param[in,out]  __hasher     Hasher instance.
 * @param[in]      __hash_alg   Hash algorithm.
 * @param[in]      __data       Pointer to the data to incorporate into the digest calculation.
 * @param[in]      __data_size  Size of the data to incorporate into the digest calculation.
 * @param[out]     __digest     Resulting digest. Only populated if this function returns EOK.
 *
 * @retval  EOK      Success.
 * @retval  EINVAL   __hasher or __digest specified as NULL, __hash_alg is not one of the valid hash alogrithms in enum
 *                   qfim_hash_alg_e, or __data == NULL and __data_size > 0 specified.
 * @retval  ENOTSUP  The specified hash algorithm is not supported by the underlying cryptographic library.
 * @retval  EIO      An unexpected failure was detected in the underlying cryptographic library.
 */
int qfim_hasher_digest(
        qfim_hasher_t   *__hasher,
        qfim_hash_alg_t  __hash_alg,
        const void      *__data,
        size_t           __data_size,
        qfim_digest_t   *__digest);


/**
 * Performs an "extend" operation on two digests, storing the result in the left-hand operand. (The extend operation is defined as
 * the computation of the digest of the concatenation of the left- and right-hand digests.) Any in-progress digest calculation is
 * cancelled.
 *
 * @param[in,out]  __hasher        Hasher instance.
 * @param[in,out]  __left_digest   Left-hand digest.
 * @param[in]      __right_digest  Right-hand digest.
 *
 * @retval  EOK      Success.
 * @retval  EINVAL   __hasher, __left_digest and/or __right_digest specified as NULL, different hash algorithms are specified in
*                    each of the digests, or the hash algorithm specified in the digests is not one of the valid hash alogrithms in
*                    qfim_hash_alg_t.
 * @retval  ENOTSUP  The hash algorithm specified in the digests is not supported by the underlying cryptographic library.
 * @retval  EIO      An unexpected failure was detected in the underlying cryptographic library.
 */
int qfim_hasher_extend(
        qfim_hasher_t       *__hasher,
        qfim_digest_t       *__left_digest,
        const qfim_digest_t *__right_digest);


/**
 * Destroys a hasher instance.
 *
 * @param[in]  __hasher  Hasher instance.
 *
 * @retval  EOK     Success. The __hasher pointer no longer refers to a valid hasher instance.
 * @retval  EINVAL  __hasher specified as NULL.
 */
int qfim_hasher_destroy(qfim_hasher_t *__hasher);


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_HASH_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/hash.h $ $Rev: 823191 $")
#endif
