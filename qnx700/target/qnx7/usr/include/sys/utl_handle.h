/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.  Free development
 * licenses are available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef _UTL_HANDLE_H_INCLUDED
#define _UTL_HANDLE_H_INCLUDED

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

/**
 * @file utl_handle.h
 *
 * This API allows an integer handle to be associated with a void pointer. The handle has a reference count associated with it.
 * While the reference count is greater than zero, the handle can be used to lookup the pointer. Once the reference count reaches
 * zero, a callback function is called to free the pointer associated with the handle and for a long time following this it can be
 * expected that attempts to use the handle will return a @c NULL pointer.
 *
 * The API is designed to allow thread safe, race free access and revocation of a block of memory. For example, a handle might be
 * convey the @c sigevent @c sigev_value used to deliver pulses using a call to @c ionotify(). In normal operation, the
 * @c sigev_value from a pulse can be converted to the desired pointer. To terminate the operation, one simply releases the last
 * reference count for the handle and calls @c ionotify() to disarm the event. Any pulses that have already been sent but are
 * waiting to be processed will not have a handle that can be converted to a pointer and can be safely ignored.
 *
 * As new handles are obtained and old ones destroyed, at some point old handles will again be convertible to non-@c NULL pointers.
 * The minimum time an invalid handle will not become valid again is 65536 divided by the handle creation rate. Thus if 100 handles
 * are being created and destroyed every second, a handle that becomes invalid will remain invalid for at least 10 minutes.
 *
 * A maximum of 65536 handles may be created from any pool.
 */

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif


/** @cond */
__BEGIN_DECLS
/** @endcond */

struct _utl_handle_pool;
typedef struct _utl_handle_pool utl_handle_pool_t;

/**
 * Callback function to free or otherwise handle memory that is no longer associated with a handle.
 *
 * This function will be called from whatever thread the call to utl_handle_release() that triggered it was made from.
 *
 * @param[in] ptr The pointer that was associated with the handle.
 *
 * @retval None
 */
typedef void (*utl_handle_destroy_f)(void *ptr);

/**
 * Create a new handle pool.
 *
 * @param[in] free_func Function to free, or otherwise deal with, memory associated with handles that cease to be valid.
 *
 * @return The handle pool.
 */
utl_handle_pool_t *utl_handle_create_pool(utl_handle_destroy_f free_func);

/**
 * Destroy a handle pool.
 *
 * Frees up the memory associated with a handle pool. Optionally the function can call the free function associated with the pool to
 * free the memory associated with any still valid handles.

 * @param[in] pool         The handle pool to destroy.
 * @param[in] free_handles Call the free function associated with the pool for each handle that is still valid.
 *
 * @retval None
 */
void utl_handle_destroy_pool(utl_handle_pool_t *pool, bool free_handles);

/**
 * Return a handle to be associated with a void pointer.
 *
 * Following this call the handle has a reference count of one.
 *
 * In the event of error, @c 0 is returned and @c errno will be set. The possible errors are:
 * - @c ENOMEM  - Not enough memory to perform operation.
 * - @c ENOBUFS - Limit of number of handles (65536) reached.
 *
 * @param[in] pool The handle pool.
 * @param[in] ptr  The pointer to associate with a handle.
 *
 * @return The handle associated with the pointer. A value of @c 0 will never be returned except in the case of an error.
 */
uint32_t utl_handle_add(utl_handle_pool_t *pool, void *ptr);

/**
 * Return the pointer associated with a handle or @c NULL if the handle is not valid.
 *
 * If a non-NULL pointer is returned, the reference count is incremented by one.
 *
 * @param[in] pool   The handle pool.
 * @param[in] handle The handle to convert to a pointer.
 *
 * @return The pointer associated with the handle or @c NULL if the handle isn't valid.
 */
void *utl_handle_acquire(utl_handle_pool_t *pool, uint32_t handle);

/**
 * Decrement the reference count of a handle.
 *
 * If the reference count reaches zero, the free function associated with the pool will be called and further calls to
 * utl_handle_acquire() with the handle will return @c NULL.
 *
 * @param[in] pool   The handle pool.
 * @param[in] handle The handle to release.
 *
 * @retval None
 */
void utl_handle_release(utl_handle_pool_t *pool, uint32_t handle);

/** @cond */
__END_DECLS
/** @endcond */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/utlfd/public/sys/utl_handle.h $ $Rev: 810649 $")
#endif
