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


#ifndef _QFIM_MEAS_H_INCLUDED
#define _QFIM_MEAS_H_INCLUDED


/* --- libqfim headers --- */
#include <qfim/common.h>
#include <qfim/type.h>

/* --- Library headers --- */

/* --- System/standard library headers --- */
#include <stddef.h>
#include <stdint.h>


__QFIM_BEGIN_DECLS


/** Flag indicating that the associated measurement contains a valid client identifier */
#define QFIM_MEAS_FLAGS_CLIENT_ID_VALID                 0x1

/** Flag indicating that the associated measurement conatins a valid monotonic timestamp value */
#define QFIM_MEAS_FLAGS_TIMESTAMP_MONOTONIC_NSEC_VALID  0x2

/** Flag indicating that the associated measurement conatins a valid realtime clock offset value */
#define QFIM_MEAS_FLAGS_REALTIME_OFFSET_NSEC_VALID      0x4


/** Type representing a measurement relevant to the assessment of system integrity */
typedef struct qfim_meas_s qfim_meas_t;


/**
 * Returns a bitmap of the flags associated with the measurement. This value can be bitwise-ANDed with the QFIM_MEAS_FLAGS_*
 * constants to determine which flag(s) are set.
 *
 * @param[in]  __meas  Measurement.
 *
 * @return  Bitmap of flags associated with the measurement, or 0 if __meas is specified as NULL.
 */
unsigned int qfim_meas_get_flags(const qfim_meas_t *__meas);


/**
 * Returns an OS-specific identifier of the client process that recorded the measurement. The QFIM daemon sets this to the server
 * connection identifier (SCOID) associated with the client process.
 *
 * @param[in]  __meas  Measurement.
 *
 * @return  An OS-specific identifier of the client process that recorded the measurement, or 0 if either __meas is specified as
 *          NULL or the measurement's QFIM_MEAS_FLAGS_CLIENT_ID_VALID flag isn't set.
 */
int32_t qfim_meas_get_client_id(const qfim_meas_t *__meas);


/**
 * Returns a monotonic timestamp (in nanoseconds since system power-on) indicating when the measurement was recorded. The QFIM
 * daemon sets this to the value of the monotonic system clock (i.e., CLOCK_MONOTONIC).
 *
 * @param[in]  __meas  Measurement.
 *
 * @return  A monotonic timestamp (in nanoseconds), or 0 if either __meas is specified as NULL or the measurement's
 *          QFIM_MEAS_FLAGS_TIMESTAMP_MONOTONIC_NSEC_VALID flag isn't set.
 */
uint64_t qfim_meas_get_timestamp_monotonic_nsec(const qfim_meas_t *__meas);


/**
 * Returns an offset (in nanoseconds) that can be added to the measurement's monotonic timestamp to obtain an epoch timestamp
 * expressed as the number of nanoseconds elapsed since 1970-01-01T00:00:00Z not counting leap seconds (i.e., CLOCK_REALTIME).
 * The QFIM daemon only includes a realtime offset in a measurement when it detects that the system's realtime clock offset has
 * changed since the last time it was recorded in a measurement.
 *
 * @param[in]  __meas  Measurement.
 *
 * @return  A realtime offset (in nanoseconds), or 0 if either __meas is specified as NULL or the measurement's
 *          QFIM_MEAS_FLAGS_REALTIME_OFFSET_NSEC_VALID flag isn't set.
 */
uint64_t qfim_meas_get_realtime_offset_nsec(const qfim_meas_t *__meas);


/**
 * Returns the number of objects (i.e., typed values) associated with the measurement. These objects represent the payload of the
 * measurement provided by the client process that recorded the measurement.
 *
 * @param[in]  __meas  Measurement.
 *
 * @return  The number of objects associated with the measurement, or 0 if __meas is specified as NULL.
 */
size_t qfim_meas_get_num_objs(const qfim_meas_t *__meas);


/**
 * Returns the integer type identifier associated with the marshalled representation of the object at the specified index in the
 * measurement. Note that the return value may or may not be equal to the integer type identifier associated with the type returned
 * by the qfim_meas_get_obj_type function for the specified object. In other words, callers should not assume that the integer type
 * identifier returned by this function can be resolved into a type using the qfim_type_from_id function--instead, use the
 * qfim_meas_get_obj_type function for this purpose.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The integer type identifier associated with the marshalled representation of the object at the specified index in the
 *          measurement, or QFIM_TYPE_ID_INVALID if __meas is specified as NULL or there is no valid marshalled representation of
 *          an object at the specified index in the measurement.
 */
int qfim_meas_get_obj_marshalled_type_id(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the marshalled representation of the object at the specified index in the measurement as an array of bytes. The length of
 * the array can be obtained via the qfim_meas_get_obj_marshalled_length function.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The marshalled representation of the object at the specified index in the measurement as an array of bytes, or NULL if
 *          __meas is specified as NULL or there is no valid marshalled representation of an object at the specified index in the
 *          measurement.
 */
const uint8_t *qfim_meas_get_obj_marshalled(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the length of the marshalled representation of the object at the specified index in the measurement obtained via the
 * qfim_meas_get_obj_marshalled function.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The length of the marshalled representation of the object at the specified index in the measurement, or 0 if __meas is
 *          specified as NULL or there is no valid marshalled representation of an object at the specified index in the measurement.
 */
size_t qfim_meas_get_obj_marshalled_length(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the type of the object at the specified index in the measurement.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The type of the object at the specified index in the measurement, or NULL if:
 *          a) __meas is specified as NULL,
 *          b) __obj_index is equal to or greater than the number of objects in the measurement, or
 *          c) the integer type identifier associated with the object could not be resolved into a type.
 */
const qfim_type_t *qfim_meas_get_obj_type(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the status of the object at the specified index in the measurement.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @retval  EOK      The value returned via qfim_meas_get_obj_value is considered a valid instance of the type returned by the
 *                   qfim_meas_get_obj_type function.
 *          EINVAL   __meas was specified as NULL, __obj_index is equal to or greater than the number of objects in the measurement,
 *                   or the integer type identifier recorded for the object could not be resolved into a valid type.
 *          ENOMEM   Failed to allocate the memory required for the object.
 *          EBADMSG  The marshalled representation of the object is invalid.
 */
int qfim_meas_get_obj_status(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the object at the specified index in the measurement.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The value of the object at the specified index in the measurement, or NULL if:
 *          a) __meas is specified as NULL,
 *          b) __obj_index is equal to or greater than the number of objects in the measurement, or
 *          c) a failure was encountered while allocating, initializing or unmarshalling the object, as indicated by the
 *             qfim_meas_get_obj_status function returning non-EOK value.
 */
const void *qfim_meas_get_obj(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


/**
 * Returns the size (in bytes) of the object at the specified index in the measurement.
 *
 * @param[in]  __meas       Measurement.
 * @param[in]  __obj_index  Index of the object.
 *
 * @return  The size (in bytes) of the object at the specified index in the measurement, or 0 if:
 *          a) __meas is specified as NULL,
 *          b) __obj_index is equal to or greater than the number of objects in the measurement,
 *          c) the integer type identifier associated with the object could not be resolved into a valid type, or
 *          d) the length of the marshalled representation of the object doesn't correspond to a valid instance of the object's
 *             type.
 *          Note that 0 may also be a valid object size. If the qfim_meas_get_obj_status function returns EOK for an object, the
 *          return values of qfim_meas_get_obj and qfim_meas_get_obj_size should both be considered valid.
 */
size_t qfim_meas_get_obj_size(
        const qfim_meas_t *__meas,
        size_t             __obj_index);


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_MEAS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/meas.h $ $Rev: 823191 $")
#endif
