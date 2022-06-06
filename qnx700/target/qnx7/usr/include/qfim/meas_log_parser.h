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


#ifndef _QFIM_MEAS_LOG_PARSER_H_INCLUDED
#define _QFIM_MEAS_LOG_PARSER_H_INCLUDED


/* --- libqfim headers --- */
#include <qfim/common.h>
#include <qfim/hash.h>
#include <qfim/meas.h>

/* --- Library headers --- */

/* --- System/standard library headers --- */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


__QFIM_BEGIN_DECLS


/** Type representing a parser of a stream of sequential measurements */
typedef struct qfim_meas_log_parser_s qfim_meas_log_parser_t;


/**
 * Type for a callback function invoked after each measurement is successfully parsed from the input stream of the parser.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __meas             Measurement parsed from the input stream. This object is only guaranteed to exist for the
 *                                    duration of the function call.
 * @param[in]      __meas_digest      Digest computed from the marshalled representation of the measurement read from the input
 *                                    stream. This object is only guaranteed to exist for the duration of the function call.
 *
 * @return  EOK to continue parsing measurments from the input stream, or a non-EOK value to stop parsing.
 */
typedef int qfim_meas_log_parser_meas_func_t(
        qfim_meas_log_parser_t *__meas_log_parser,
        const qfim_meas_t      *__meas,
        const qfim_digest_t    *__meas_digest);


/**
 * Creates a parser of a stream of marshalled measurements. In its initial state, the parser has no input stream, callback
 * function(s) or hash algorithm configured.
 *
 * @param[out]  __new_meas_log_parser  Populated with a pointer to the newly created measurement log parser when this function
 *                                     returns EOK, otherwise populated with NULL.
 *
 * @retval  EOK     Success. *__new_meas_log_parser contains a pointer to the newly created measurement log parser. The caller is
 *                  responsible for destroying the measurement log parser instance by passing it to qfim_meas_log_parser_destroy
 *                  when it is no longer needed.
 * @retval  EINVAL  __new_meas_log_parser specified as NULL.
 * @retval  ENOMEM  Unable to allocate the necessary memory for the measurement log parser.
 */
int qfim_meas_log_parser_create(qfim_meas_log_parser_t **__new_meas_log_parser);


/**
 * Sets the hash algorithm to be used by the measurement log parser for the calculation of measurement digests and the measurement
 * aggregate. Implicitly sets the initial value of the measurement aggregate to all zeroes.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __hash_alg         Hash algorithm.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser specified as NULL, or __hash_alg does not correspond to a supported hash algorithm.
 * @retval  EBUSY   Unable to modify hash algorithm or measurement aggregate; qfim_meas_log_parser_parse has already been called.
 *                  The qfim_meas_log_parser_reset function can be used to put the parser back into a state where the hash algorithm
 *                  and measurement aggregate may be modified.
 */
int qfim_meas_log_parser_set_initial_aggregate_zero(
        qfim_meas_log_parser_t *__meas_log_parser,
        qfim_hash_alg_t         __hash_alg);


/**
 * Sets the measurement log parser's hash algorithm and initial measurement aggregate value.
 *
 * @param[in,out]  __meas_log_parser    Measurement log parser.
 * @param[in]      __initial_aggregate  Digest containing the hash algorithm and initial measurement aggregate value.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser specified as NULL, or __digest->hash_alg does not correspond to a supported hash algorithm.
 * @retval  EBUSY   Unable to modify the hash algorithm or measurement aggregate; the parsing of measurements has already been
 *                  initiated via a call to qfim_meas_log_parser_parse. The qfim_meas_log_parser_reset function can be used to put the
 *                  parser back into a state where the hash algorithm and initial measurement aggregate may be modified.
 */
int qfim_meas_log_parser_set_initial_aggregate(
        qfim_meas_log_parser_t *__meas_log_parser,
        const qfim_digest_t    *__initial_aggregate);


/**
 * Associates a user-defined context with the measurement log parser.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __context          User-defined context. May be NULL.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 */
int qfim_meas_log_parser_set_context(
        qfim_meas_log_parser_t *__meas_log_parser,
        void                   *__context);


/**
 * Sets the measurement handler callback function that will be invoked after each measurement is successfully parsed from the
 * measurement log parser's input stream.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __meas_func        Measurement handler callback function. If NULL, no callback is invoked after each measurement
 *                                    is successfully parsed.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 */
int qfim_meas_log_parser_set_meas_func(
        qfim_meas_log_parser_t           *__meas_log_parser,
        qfim_meas_log_parser_meas_func_t *__meas_func);


/**
 * Disassociates the measurement log parser from its current input stream (if any) and sets the specified file (ISO C stream) as the
 * new input stream. If the host operating system supports both text and binary file modes, the file must be open in binary mode.
 * The caller should not manipulate the file while it is associated with the measurement log parser, otherwise behaviour is
 * undefined. The caller is responsible for closing this file once it has been disassociated from the measurement log parser or the
 * measurement log parser is destroyed.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __file             File (ISO C stream). If NULL, the measurement log parser will be set to have no input stream.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 * @retval  ENOMEM  Failed to allocate required memory.
 */
int qfim_meas_log_parser_set_input_file(
        qfim_meas_log_parser_t *__meas_log_parser,
        FILE                   *__file);


/**
 * Attempts to open the file at the specified path. If successful, the measurement log parser is disassociated from its current
 * input stream (if any) and the opened file is set as the new input stream. This file is closed automatically when a different
 * input stream is set or the measurement log parser is destroyed.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[in]      __path             Path to the file to open and set as the input stream. If NULL, the measurement log parser will
 *                                    be set to have no input stream.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 * @retval  ENOMEM  Failed to allocate required memory.
 * @return  Otherwise, the error code reported in response to the failed attempt to open the file at the specified path.
 */
int qfim_meas_log_parser_set_input_path(
        qfim_meas_log_parser_t *__meas_log_parser,
        const char             *__path);


/**
 * Parse measurement(s) from the measurement log parser's input stream and invoke any applicable callback function(s). Currently,
 * the only callback function supported is the measurement handler, which is set via the qfim_meas_log_parser_set_meas_func
 * function.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 * @param[out]     __length_read      Optional output parameter populated with the number of bytes read from the input stream
 *                                    regardless of whether or not this function returns EOK.
 *
 * @retval  EOK      Success. Either the end of the input stream was reached, or a callback function returned a non-EOK value to
 *                   interrupt parsing.
 * @retval  EINVAL   __meas_log_parser was specified as NULL.
 * @retval  EIO      A failure was encountered while reading from the input stream or computing a digest.
 * @retval  EBADMSG  A malformed measurement was read from the input stream.
 * @retval  EBUSY    Recursive invocation denied (parsing is already in progress).
 */
int qfim_meas_log_parser_parse(
        qfim_meas_log_parser_t *__meas_log_parser,
        qfim_off_t             *__length_read);


/**
 * Returns the user-defined context associated with the measurement log parser.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The user-defined context associated with the measurement log parser (may be NULL), or NULL if __meas_log_parser was
 *          specified as NULL.
 */
void *qfim_meas_log_parser_get_context(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Returns the latest value returned by a callback function invoked by the measurement log parser. Currently, the only callback
 * function supported is the measurement handler, which is set via the qfim_meas_log_parser_set_meas_func function.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The non-EOK value that interrupted the latest invocation of the qfim_meas_log_parser_parse function, or:
 * @retval  EINVAL  __meas_log_parser specified as NULL.
 * @retval  EOK     Either the qfim_meas_log_parser_parse function hasn't been invoked since the measurement log parser was
 *                  created/cleared, or the latest invocation of the qfim_meas_log_parser_parse function wasn't interrupted by a
 *                  callback function returning a non-EOK value.
 */
int qfim_meas_log_parser_get_func_result(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Returns the number of bytes successfully parsed since the measurement log parser was either created or last reset via the
 * qfim_meas_log_parser_reset function.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The number of bytes successfully parsed since creation/reset.
 */
qfim_off_t qfim_meas_log_parser_get_length_parsed(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Returns the number of measurements successfully parsed since the measurement log parser was either created or last reset via the
 * qfim_meas_log_parser_reset function.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The number of measurements successfully parsed since creation/reset.
 */
unsigned long qfim_meas_log_parser_get_num_meas_parsed(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Returns the last valid realtime offset (in nanoseconds) parsed out of a measurement since the measurement log parser was either
 * created or last reset via the qfim_meas_log_parser_reset function.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The last valid realtime offset (in nanoseconds) parsed out of a measurement since the measurement log parser was either
 *          created or last reset via the qfim_meas_log_parser_reset function, or 0 if no such realtime offset has been detected.
 */
uint64_t qfim_meas_log_parser_get_realtime_offset_nsec(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Returns the current measurement aggregate digest value.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @return  The current measurement aggregate digest value.
 */
const qfim_digest_t *qfim_meas_log_parser_get_aggregate(const qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Resets the state of the measurement log parser by:
 * - setting the aggregate back to the initial value that was configured via the qfim_meas_log_parser_set_initial_aggregate_zero or
 *   qfim_meas_log_parser_set_initial_aggregate function,
 * - setting the parsing statistics and state variables (length parsed, number of measurements parsed, realtime offset, etc.) back
 *   to their initial values, and
 * - seeking the input stream back to the original position it was in when it was configured via the
 *   qfim_meas_log_parser_set_input_file or qfim_meas_log_parser_set_input_path function.
 *
 * @param[in,out]  __meas_log_parser  Measurement log parser.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 * @retval  EBUSY   Cannot reset the parser while parsing is in progress (i.e., from a callback function).
 * @retval  EIO     Failed to seek the input stream back to its original position.
 */
int qfim_meas_log_parser_reset(qfim_meas_log_parser_t *__meas_log_parser);


/**
 * Destroy the measurement log parser.
 *
 * @param[in]  __meas_log_parser  Measurement log parser.
 *
 * @retval  EOK     Success. __meas_log_parser no longer refers to a valid measurement log parser; this pointer should be discarded.
 * @retval  EINVAL  __meas_log_parser was specified as NULL.
 * @retval  EBUSY   Cannot destroy the parser while parsing is in progress (i.e., from a callback function).
 */
int qfim_meas_log_parser_destroy(qfim_meas_log_parser_t *__meas_log_parser);


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_MEAS_LOG_PARSER_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/meas_log_parser.h $ $Rev: 823191 $")
#endif
