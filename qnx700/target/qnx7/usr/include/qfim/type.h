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


#ifndef _QFIM_TYPE_H_INCLUDED
#define _QFIM_TYPE_H_INCLUDED


/* --- libqfim headers --- */
#include <qfim/common.h>

/* --- Library headers --- */

/* --- System/standard library headers --- */
#include <stddef.h>


__QFIM_BEGIN_DECLS


/** Type representing a class of objects that can be recorded within the payload of a measurement */
typedef struct qfim_type_s qfim_type_t;


/**
 * Returns the type associated with the specified type identifier.
 *
 * @param[in]  __type_id  Type identifier.
 *
 * @return  The type associated with the specified type identifier, or NULL if no type is associated with the specified type
 *          identifier.
 */
const qfim_type_t *qfim_type_from_id(int __type_id);


/**
 * Returns the type identifier associated with the type.
 *
 * @param[in]  __type  Type.
 *
 * @return  The type identifier associated with the type, or QFIM_TYPE_ID_INVALID if __type is specified as NULL or the type is not
 *          associated with a valid type identifier.
 */
int qfim_type_get_id(const qfim_type_t *__type);


/**
 * Returns the name of the type.
 *
 * @param[in]  __type  Type.
 *
 * @return  String representing the name of the type, or NULL if __type is specified as NULL.
 */
const char *qfim_type_get_name(const qfim_type_t *__type);


/**
 * Generates a null-terminated string representation of the specified instance of a type, truncating it if necessary to fit within
 * the destination buffer.
 *
 * @param[in]   __type                Type.
 * @param[in]   __obj                 Object (instance of the type).
 * @param[in]   __obj_size            Size of the object (in bytes).
 * @param[out]  __str                 Destination buffer into which the string reperesentation of the object will be written. May be
 *                                    specified as NULL if __str_size is specified as 0.
 * @param[in]   __str_size            The size of the destination buffer (in bytes).
 * @param[out]  __untruncated_strlen  Optional output parameter populated with the length of the string representation of the value
 *                                    excluding the null terminator. If this value is equal to or greater than __str_size, the
 *                                    string representation of the value was truncated to fit within the bounds of the buffer.
 *
 * @retval  EOK     Success. If __str_size > 0, __str has been populated with a null-terminated string representation of the value.
 *                  If *__untruncated_strlen >= __str_size, the string representation was truncated to fit within the output buffer.
 * @retval  EINVAL  __type was specified as NULL, __str was specified as NULL with __str_size > 0, or the specified value is not a
 *                  valid instance of the specified type.
 * @retval  ENOSYS  This function hasn't been implemented for the specified type.
 */
int qfim_type_obj_to_str(
        const qfim_type_t *__type,
        const void        *__obj,
        size_t             __obj_size,
        char              *__str,
        size_t             __str_size,
        size_t            *__untruncated_strlen);


__QFIM_END_DECLS


#endif /* #ifndef _QFIM_TYPE_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/qfim/public/qfim/type.h $ $Rev: 823191 $")
#endif
