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

#ifndef _QFIM_CLIENT_H_INCLUDED
#define _QFIM_CLIENT_H_INCLUDED


/* --- libqfim-client headers --- */

/* --- Library headers --- */
#include <qfim/common.h>
#include <qfim/type.h>

/* --- System/standard library headers --- */
#include <stddef.h>


__QFIM_BEGIN_DECLS


/**
 * Option flag for requesting a connection to the QNX Framework for Integrity Measurement (QFIM) daemon that supports the recording
 * of measurements */
#define QFIM_CLIENT_FLAGS_RECORD     0x00000001


/**
 * Option flag for requesting a connection to the QNX Framework for Integrity Measurement (QFIM) daemon that supports retrieval of
 * the measurement log */
#define QFIM_CLIENT_FLAGS_CHALLENGE  0x00000002


/** Context representing a client of the QNX Framework for Integrity Measurement (QFIM) daemon */
typedef struct qfim_client_s qfim_client_t;


/**
 * Creates a QNX Framework for Integrity Measurement (QFIM) client context and establishes a connection to the QFIM daemon.
 *
 * @param[out]  __new_client  Populated with a newly created client context on success, otherwise set to NULL.
 * @param[in]   __flags       Bitwise OR of one or more of the following QFIM_CLIENT_FLAGS_* values:
 *                                QFIM_CLIENT_FLAGS_RECORD:     Request a connection to the QFIM daemon that supports the recording
 *                                                              of measurements.
 *                                QFIM_CLIENT_FLAGS_CHALLENGE:  Request a connection to the QFIM daemon that supports retrieval of
 *                                                              the measurement log.
 *
 * @retval  EOK     Success. *__new_client contains a pointer to the newly created client context. The caller is responsible for
 *                  destroying the client context by passing it to qfim_client_destroy when it is no longer needed.
 * @retval  EINVAL  __new_client was specified as NULL, or an invalid value was specified for __flags.
 * @retval  ENOMEM  Unable to allocate memory necessary for the client context.
 * @retval  EAGAIN  No mutexes available.
 * @return  Or, the errno value obtained after a failed attempt to open one of the device files registered by the QFIM daemon.
 */
int qfim_client_create_connect(
        qfim_client_t **__new_client,
        unsigned int    __flags);


/**
 * Records a measurement in the QNX Framework for Integrity Measurement (QFIM) daemon's measurement log. The measurement will
 * contain:
 * a) an object of the specified type and size, and
 * b) a comment string generated via printf-style formatted I/O (if __comment_format specified as non-NULL).
 * If insufficient buffer space is available in the client context to hold the complete marshalled representation of the object and
 * comment string, this function will attempt to truncate the comment string to fit.
 *
 * @param[in,out]  __client          Client context.
 * @param[in]      __type            Type of the object to be recorded. Refer to <qfim/type.h> for further details.
 * @param[in]      __obj             The object to be recorded.
 * @param[in]      __obj_size        Size of the object to be recorded in bytes.
 * @param[in]      __comment_format  Optional format string for formatted I/O of a comment to associate with the object to be
 *                                   recorded.
 * @param[in]      ...               Additional arguments corresponding to the conversion specifiers in the __comment_format string.
 *
 * @retval  EOK        Success. The measurement has been recorded in the QFIM daemon's measurement log.
 * @retval  EINVAL     Invalid parameter(s) (e.g., __client specified as NULL, __type specified as NULL, __obj/__obj_size does not
 *                     correspond to a valid object of the specified type, etc.).
 * @retval  EMSGSIZE   The buffer in the client context was insufficient to hold the complete marshalled representation of the
 *                     object and comment string. If possible, the measurement was recorded with a truncated comment string.
 * @retval  EAGAIN     Insufficient resources available to lock the mutex associated with the client context.
 * @retval  ETIMEDOUT  A kernel timeout unblocked the thread while it was waiting to acquire the mutex associated with the client
 *                     context.
 */
int qfim_client_record_obj(
        qfim_client_t     *__client,
        const qfim_type_t *__type,
        const void        *__obj,
        size_t             __obj_size,
        const char        *__comment_format,
        ...
        ) __QFIM_CATTR_FUNC_FORMAT(__printf__, 5, 6);


/**
 * Destroys the specified client context, closing the associated connection to the QFIM daemon.
 *
 * @param[in]  __client  Client context.
 *
 * @retval  EOK     Success.
 * @retval  EINVAL  __client was specified as NULL.
 */
int qfim_client_destroy(qfim_client_t *__client);


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_CLIENT_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim-client/public/qfim/client.h $ $Rev: 823191 $")
#endif
