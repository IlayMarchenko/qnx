/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
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

/**
*   @file capture.h
*   @brief Functions for the Video Capture Library
*
*   This file defines Video Capture API functions that are supported by
*   the Video Capture library.
*/

/**
*   @mainpage Video Capture Library Overview
*
*    The video capture API includes all the functions, data structures, and
*    constants needed for video capture. It does not handle video display, which
*    should be handled by another component, such as Screen.
*
*    The video capture API is thread-safe, unless stated otherwise for a
*    particular API function.
*/

/**
*   @defgroup capture_driver_device Driver and device
*   @brief The video capture API includes constants that specify the video
*          capture driver and device properties
*/

/**
*   @defgroup capture_data Data bus, data lane, and clock
*   @brief The video capture API includes constants that specify the video
*          capture data bus, data lane and clock properties
*/

/**
*   @defgroup capture_decoder I2C decoder path and slave address
*   @brief The video capture API includes constants that specify the video
*          capture I2C decoder path and slave address properties
*/

/**
*   @defgroup capture_video_standards Video standards
*   @brief The video capture API includes constants that specify the video
*          capture video standard properties
*/

/**
*   @defgroup capture_polarity Polarity
*   @brief The video capture API includes constants that specify the video
*          capture polarity properties
*/

/**
*   @defgroup capture_deinterlacing Deinterlacing
*   @brief The video capture API includes constants that specify the video
*          capture deinterlacing properties
*/

/**
*   @defgroup capture_source_format Source
*   @brief The video capture API includes constants that specify the video
*          capture source properties
*/

/**
*   @defgroup capture_dest_buffer Destination buffer
*   @brief The video capture API includes constants that specify the video
*          capture destination buffer properties
*/

/**
*   @defgroup capture_frame Video frame
*   @brief The video capture API includes constants that specify the video
*          capture video frame properties
*/

/**
*   @defgroup capture_external_source External source
*   @brief The video capture API includes constants that specify the video
*          capture external source properties
*/

/**
*   @defgroup capture_helper Helper macros
*   @brief The video capture API includes macros to help with interval
*          conversions.
*/

/**
*   @defgroup capture_properties Properties
*   @brief The video capture API includes constants, data types, enumerated
*          values, and macros specifying video capture properties
*/

/**
*   @defgroup capture_properties_video Video capture behavior
*   @brief The video capture API includes constants that specify the video
*          capture video capture behavior properties
*/

/**
*   @defgroup capture_properties_threads Threads
*   @brief The video capture API includes constants that specify thread priority
*/

/**
*   @defgroup capture_properties_debugging Debugging
*   @brief The video capture API includes constants that specify the video
*          capture debugging properties
*/

#ifndef	QNXVIDEOCAPTURE_PUBLIC_H
#define	QNXVIDEOCAPTURE_PUBLIC_H

#include <inttypes.h>
#include <sys/platform.h>

/**************************************************************/
/* Note:                                                      */
/* If you add new properties to this file, please add them to */
/* lib/capture/props-validation.c for validation too.         */
/**************************************************************/

__BEGIN_DECLS

struct _capture_context;

/**
* @brief  An opaque pointer (or handle) to a video capture context
*/
typedef struct _capture_context	*capture_context_t;

/* NOTE: 0x0001 is reserved. */
/**
*   @addtogroup capture_external_source
*   @{
*/
/**
* @brief Bit to set if the context to create is for an external source, instead
*        of a captured source
* @details The video capture API includes constants for managing the retrieval
*          and deinterlacing of frames brought in from an external source,
*          such as a USB memory stick. When you've set this constant, the
*          following properties are relevant:
*          - @c #CAPTURE_BUFFER_USAGE_RDONLY
*          - @c #CAPTURE_FLAG_FREE_BUFFER
*          - @c #CAPTURE_PROPERTY_BUFFER_FLAGS
*          - @c #CAPTURE_PROPERTY_BUFFER_INDEX
*          - @c #CAPTURE_PROPERTY_BUFFER_NFIELDS
*          - @c #CAPTURE_PROPERTY_BUFFER_PLANAR_OFFSETS
*          - @c #CAPTURE_PROPERTY_BUFFER_SEQNO
*          - @c #CAPTURE_PROPERTY_BUFFER_USAGE
*/
#define CAPTURE_FLAG_EXTERNAL_SOURCE UINT32_C(0x0002)
/** @} */   /* end of addtogroup capture_external_source */

/**
* @brief Create a video capture context
*
* This function:
*  - creates a new context for video capture
*  - returns a pointer to the context in @c #capture_context_t
*
* You must create a context before you can set video capture properties and
* start video capture. The context contains both mandatory information, such
* as device ID and input source ID (e.g., device 1, input source 2), and
* optional settings, such as brightness.
*
* You can create multiple contexts, but you can have only one context in use
* for each device-source combination. If you have created multiple contexts for
* the same device-source combination, @c capture_get_frame() will use the first
* context you have enabled with @c capture_set_property_i().
*
* Before your application exits, it must call @c capture_destroy_context() to
* destroy every context that it created. Failure to destroy a context before
* exiting can lead to memory corruption and unpredictable system behavior.
*
* @param flags Bitmask parameter; set to either @c 0 if the context to be
*              created is for a local device, or to @c #CAPTURE_FLAG_EXTERNAL_SOURCE
*              if the context to be created is for an external source.
*
* @return A pointer to a new context if successful; or @c NULL if an error
*         occurred (@c errno is set; refer to @c errno.h for more details). The
*         value that's observed for @c errno may vary as it is hardware dependent.
*/
extern capture_context_t capture_create_context( uint32_t flags );

/**
* @brief Disconnect from the video capture device, and destroy the video capture
*        context
*
* This function:
*  - disconnects from a video capture device
*  - destroys the specified context
*
* When this function returns, you can safely release the video capture buffers
* you have been using with this context.
*
* @note This function is not signal handler safe! You must create a separate
*       clean-up thread for signal handling. This signal-handling thread can
*       destroy the capture context by instructing another thread to call
*       @c capture_destroy_context().
*
* @param context The pointer to the video capture context to destroy.
*
* @return Nothing.
*/
extern void capture_destroy_context( capture_context_t context );

/**
* @brief Allocate driver-controlled memory for video capture
*
* This function allocates memory for video capture. Allocation of memory for
* driver allocated buffer memory differs based on whether your hardware
* supports dynamic buffer allocation. If your hardware doesn't support
* dynamically-allocated memory, calling @c capture_create_buffer() will fail if
* @c #CAPTURE_PROPERTY_FRAME_BUFFERS is set to anything other than NULL. Refer to
* <a href="manual/vc_buffer.xml">Buffers</a> from the Video Capture Developer's
* Guide for more information.
*
* Calls to @c capture_create_buffers() are synchronous. The function frees old
* buffers and creates the new buffers.
*
* To free an existing buffer without creating a new one:
* 1. Call @c capture_set_property_p() to set the buffer property
*    @c #CAPTURE_PROPERTY_FRAME_BUFFERS to NULL.
* 2. Call @c capture_update().
*
* The following code snippet can be useful reference on how to use
* @c capture_create_buffers():
* @code
*   ...
*   capture_set_property_i( context, CAPTURE_PROPERTY_DST_NBYTES, 320 * 240 * 4 );
*   capture_set_property_i( context, CAPTURE_PROPERTY_FRAME_NBUFFERS, 5 );
*
*   // Create 5 frame buffers with 320x240x4 bytes each.
*   capture_create_buffers( context, CAPTURE_PROPERTY_FRAME_BUFFERS );
*
*   // Get the buffers.
*   void **frame_buffers;
*
*   capture_get_property_p( context, CAPTURE_PROPERTY_FRAME_BUFFERS, (void**)&frame_buffers );
*   ...
* @endcode
*
* Call this function only when video capture is not in progress.
*
* Do not get a pointer to a buffer with @c capture_get_property_p(), then set
* the same pointer with @c capture_set_property_p():
* - If the buffer is driver-allocated, this sequence of calls will cause the
*   driver to free the buffer referenced by the pointer, then assume that the
*   application owns the now non-existent buffer, with unpredictable results.
* - If the buffer in question was initially application-allocated, then no ill
*   effects occur.
*
* @param context The pointer to the video capture context.
* @param property The video capture frame properties by @c capture_set_property_i().
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware.
*         For example, most drivers return an @c errno value of @c ENOTSUP if
*         they do not support this function.
*/
extern int capture_create_buffers( capture_context_t context, uint32_t property );

/**
* @brief Check if the specified property is supported
*
* This function checks if the connected video capture device or driver supports
* the property specified in the argument @c prop.
*
* Use the following code snippet as reference of how to use
* @c capture_is_property():
* @code
* void get_video_info(capture_context_t context) {
*   char *cur_norm = NULL;
*   if(capture_is_property(context, CAPTURE_PROPERTY_CURRENT_NORM)) {
*       capture_get_property_p(context, CAPTURE_PROPERTY_CURRENT_NORM, (void **)&cur_norm);
*   }
*   fprintf(stderr, "current norm: %s", cur_norm? cur_norm : "unavailable");
*   fprintf(stderr, "\n");
* }
* @endcode
*
* @param context The pointer to the video capture context.
* @param prop The property that is in question of whether or not it's supported.
*
* @return 1 if the specified property is supported; or 0 otherwise.
*/
extern int capture_is_property( capture_context_t context, uint32_t prop );

/**
* @brief Set a video frame capture property of type integer
*
* This function sets a video capture property to pass to the video capture
* device driver.
*
* Array resources, such as @c #CAPTURE_PROPERTY_FRAME_FLAGS and
* @c #CAPTURE_PROPERTY_FRAME_SEQNO are not allocated by default. They need to be
* set, then passed to the video capture driver. To do this you need to:
* - Call @c capture_set_property_i() for each capture property you need to set,
*   using the @c CAPTURE_PROPERTY_* constants to specify the device, brightness,
*   destination buffers, etc.
* - Call @c capture_set_property_p(), when you have set all the properties you
*   need to specify, to pass a pointer to this array to the video capture
*   library. The library stores this pointer and will update the array when
*   appropriate.
*
* You can instruct the video capture library to stop collecting and providing
* data for a property by setting the location for property in the array to NULL.
*
* @param context The pointer to the video capture context.
* @param prop The property to set.
* @param value The integer value of the property specified by @c prop.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware.
*/
extern int capture_set_property_i( capture_context_t context, uint32_t prop, int32_t value );

/**
* @brief Set a video frame capture property of type (void) pointer
*
* This function sets an array of video capture properties to pass
* to the video capture library.
*
* Array resources, such as @c #CAPTURE_PROPERTY_FRAME_FLAGS and
* @c #CAPTURE_PROPERTY_FRAME_SEQNO, are not allocated by default. They need to
* be set, then passed to the video capture driver. To do this, you must set the
* properties you need to specify by calling @c capture_set_property_i(), then
* pass a pointer to the array with these properties by calling
* @c capture_set_property_p().
*
* @note Allocate an array large enough to store the video capture properties.
*       The minimum number of elements in the array must be at least as large as
*       the corresponding capture property associated with the array you are
*       setting. For example, the minimum array sizes of
*       @c #CAPTURE_PROPERTY_FRAME_SEQNO and @c #CAPTURE_PROPERTY_FRAME_FLAGS
*       are determined by the size of @c #CAPTURE_PROPERTY_FRAME_NBUFFERS.
*
* @param context The pointer to the video capture context.
* @param prop The property to set.
* @param value A pointer to a buffer containing the new value of the property
*        to be set. This buffer must be of type @c void*.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware.
*/
extern int capture_set_property_p( capture_context_t context, uint32_t prop, void *value );

/**
* @brief Get a video frame capture property of type integer
*
* This function retrieves a video capture driver or device property, which may
* have been set by @c capture_set_property_p().
*
* @param context The pointer to the video capture context.
* @param prop The property to get.
* @param value A pointer to the location where the retrieved property is located.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware.
*/
extern int capture_get_property_i( capture_context_t context, uint32_t prop, int32_t *value );

/**
* @brief Get video frame capture property of type void*
*
* This function retrieves a video capture driver or device property.
*
* @param context The pointer to the video capture context.
* @param prop The property to retrieve.
* @param value A reference to the location where the retrieved property will be
*              placed.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware.
*/
extern int capture_get_property_p( capture_context_t context, uint32_t prop, void **value );

/**
* @brief Apply the capture settings
*
* This function applies (commits) all updates posted since it was last called to
* the driver.
*
* Functions such as @c capture_set_property_i() and @c capture_set_property_p()
* update memory but they don't apply updates to the video capture device. To
* apply updates, you must call @c capture_update(). This behavior allows the
* proper combining of discrete properties, such as @c *DST_X, @c *DST_Y and
* @c *DST_WIDTH. Once these properties are combined, a call to
* @c capture_update() commits all the changes to the device at the same time.
*
* @param context The pointer to the video capture context.
* @param flags Reserved. Don't use.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details). The return value and
*         the value that's observed for @c errno may vary as they are dependent
*         on the implementation by the library that handles your hardware. The
*         driver may @c slog*() more detailed error information. Use @c slog2info
*         to retrieve it.
*/
extern int capture_update( capture_context_t context, uint32_t flags );

/**
*   @addtogroup capture_properties_video
*   @{
*/
/**
* @brief Never time out; wait for frame indefinitely
*        Typically, drivers set the timeout to 30 days instead of using
*        an actual infinite timeout.
*/
#define	CAPTURE_TIMEOUT_INFINITE	(-1ULL)

/**
* @brief Return immediately, even if there is no frame
*/
#define	CAPTURE_TIMEOUT_NO_WAIT		(0)

/**
* @brief Get the latest frame and discard all the other queued frames
*/
#define	CAPTURE_FLAG_LATEST_FRAME UINT32_C(0x0001)
/** @} */   /* end of capture_properties_video */

/**
*   @addtogroup capture_external_source
*   @{
*/
/**
* @brief Request a free buffer in which to put a frame from an external source.
*/
#define CAPTURE_FLAG_FREE_BUFFER UINT32_C(0x0002)
/** @} */   /* end of addtogroup capture_external_source */

/**
*   @addtogroup capture_video_standards
*   @{
*/
/**
* @brief Indicate @c capture_get_frame should return immediately (usually
*        with an EINTR error) when @c #CAPTURE_PROPERTY_UNBLOCK is set.
*
* Normally this would be used to watch for device-specific events.
* Verify that @c CAPTURE_PROPERTY_UNBLOCK is supported before using the flag.
*/
#define CAPTURE_FLAG_ALLOW_UNBLOCK UINT32_C(0x0004)
/** @} */   /* end of addtogroup capture_video_standards */

/**
* @brief Get a frame from the video capture device
*
* This function retrieves frames from the device. If more than one frame is in
* the queue, depending on the behavior specified by the flags argument, this
* function will either retrieve the first queued frame in sequence or retrieve
* only the latest frame, dropping the others.
*
* The index returned by this function corresponds to the sequence number of the
* @c #CAPTURE_PROPERTY_FRAME_SEQNO property, if this array is provided. The
* application can use this property and the index returned by this function to
* calculate the number of frames that have been dropped since the last call to
* @c capture_get_frame().
*
* It's safe to call this function even if capturing hasn't started (i.e., 
* you haven't set the @c #CAPTURE_ENABLE property and called @c capture_update())
* yet. Your application must ensure that another thread will enable and disable
* capturing when required.
*
* The buffer used to get a frame is locked for exclusive use by your application
* until @c capture_release_frame() releases it back to the capture driver.
* To avoid overwriting a frame before it has been displayed, your application
* should use at least three capture buffers to:
*  1. Call @c capture_get_frame() to get the index of the captured video frame.
*  2. Hand the frame buffer over for display by a call to a Screen function such
*     as @c screen_post_window().
*  3. Call @c capture_get_frame() to get another frame.
*  4. When the frame in Step 1 is no longer being displayed, call
*     @c capture_release_frame() to release the buffer for reuse by the capture
*     driver.
*
* @param context The pointer to the video capture context.
* @param timeout The wait before timing out. Set to any of:
*                - The number of nanoseconds the function should wait for a
*                  frame before timing out. The function may return in less time
*                  than the period specified by this argument.
*                - @c #CAPTURE_TIMEOUT_INFINITE to wait indefinitely for a frame
*                  (never time out).
*                - @c #CAPTURE_TIMEOUT_NO_WAIT to return immediately, even if
*                  there is no frame.
* @param flags  A bitmask to change the behavior of this function. Set to 0 or
*               some combination of the following:
*               - @c #CAPTURE_FLAG_LATEST_FRAME to retrieve the latest frame,
*                 discarding all the other queued frames (the default behavior
*                 is to retrieve all queued frames in sequence).
*               - @c #CAPTURE_FLAG_FREE_BUFFER to retrieve a free buffer
*                 instead of a video frame.  The @c capture_get_free_buffer()
*                 macro can be used to do the same thing.
*               - @c #CAPTURE_FLAG_ALLOW_UNBLOCK to indicate the call should
*                 return immediately when some device-specific event occurs,
*                 normally with errno set to @c EINTR.
*
* @return The index of the captured buffer (@c #CAPTURE_PROPERTY_FRAME_BUFFERS)
*         if successful; or -1 if an error occurred (@c errno is set;
*         refer to @c errno.h for more details). The return value and the value
*         that's observed for @c errno may vary as they are dependent on the
*         implementation by the library that handles your hardware.
*/
extern int capture_get_frame( capture_context_t context, uint64_t timeout, uint32_t flags );

/**
* @brief Get a free video capture buffer when bringing in video from an external
*        source
*
* The macro @c capture_get_free_buffer() returns the index to a free buffer.
* Once your application populates the buffer and sets the appropriate capture
* properties, the client application calls @c capture_put_buffer() to place the
* capture buffer in the video capture stream. Use another thread to call
* @c capture_get_frame() to return a processed frame (for example, the frame is
* scaled or deinterlaced).
*
* Refer to @c capture_get_frame() for full description for this function.
*/
#define capture_get_free_buffer( context, timeout, flags )    \
		capture_get_frame( context, timeout, (flags) | CAPTURE_FLAG_FREE_BUFFER )

/**
* @brief Release a video frame buffer
*
* This function releases the frame specified in its @c idx argument and returns
* it to the capture queue. Your application should call this function after it
* has displayed a captured frame to ensure that the buffer locked by
* @c capture_get_frame() is made available for reuse.
*
* @param context The pointer to the video capture context.
* @param idx The index to the frame buffer to release.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details).
*         The return value and the value that's observed for @c errno may vary
*         as they are dependent on the implementation by the library that
*         handles your hardware.
*/
extern int capture_release_frame( capture_context_t context, uint32_t idx );

/**
* @brief Pass a buffer to the driver for deinterlacing a frame when bringing in
*        video from an external source
*
* This function passes a buffer to the driver for deinterlacing frames brought
* in from a video on an external source, such as a USB memory stick. It should
* be used only when the @c #CAPTURE_FLAG_EXTERNAL_SOURCE flag is set.
*
* Interlaced video frames (typical of analog video) contain two sequential
* fields, which doubles the perceived frame rate and improves the video
* quality. To display interlaced video in a system using a progressive display,
* the interlaced frames need to be separated into two fields in the correct
* sequence. Thus, displaying an interlaced video correctly on a progressive
* display requires at least two buffers for every interlaced frame. The
* @c capture_put_buffer() function passes a buffer to the driver, which it can
* use for the second frame extracted from the interlaced frame.
*
* @param ctx The pointer to the video capture context.
* @param idx The index to the frame buffer to inject into the capture driver.
* @param flags Flag specifying how to process the deinterlaced frame.
*
* @return 0 if successful; or -1 if an error occurred (@c errno
*         is set; refer to @c errno.h for more details).
*         The return value and the value that's observed for @c errno may vary
*         as they are dependent on the implementation by the library that
*         handles your hardware.
*/
extern int capture_put_buffer( capture_context_t ctx, uint32_t idx, uint32_t flags );

/**
*   @addtogroup capture_properties
*   @{
*/
/**
* @brief @c CAPTURE_PROPERTY() converts string constants into integers. This
*        macro is used to help define the capture properties
*/
#define CAPTURE_PROPERTY(a, b, c, d)	( (a) << 24 | (b) << 16 | (c) << 8 | (d) )
/** @} */   /* end of addtogroup capture_properties */

/**
*   @addtogroup capture_driver_device
*   @{
*/
/**
* @brief Return string information about the video capture driver and device;
*        all drivers support this property
*
*        The content of this property depends on the device that's set in
*        @c #CAPTURE_PROPERTY_DEVICE property.
*
*        Read <tt>const char *</tt>
*/
#define	CAPTURE_PROPERTY_DEVICE_INFO		CAPTURE_PROPERTY( 'Q', 'I', 'N', 'F' )

/**
* @brief Capture start(1) and stop(0)
*
*        Read/Write @c uint32_t
*/
#define	CAPTURE_ENABLE				CAPTURE_PROPERTY( 'Q', 'E', 'N', 'A' )

/**
* @brief Number of supported capture units
*         A capture driver can support a number of devices
*        (@c #CAPTURE_PROPERTY_NDEVICES); each device has at least one input
*        (@c #CAPTURE_PROPERTY_NSOURCES). Selection of the input is done by
*        choosing a device, and then a source.
*
*        Read @c uint32_t
*/
#define CAPTURE_PROPERTY_NDEVICES		CAPTURE_PROPERTY( 'Q', 'N', 'D', 'V' )

/**
* @brief Capture device in this context
* 
*        Once set, on some drivers, this property cannot be changed.
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DEVICE			CAPTURE_PROPERTY( 'Q', 'D', 'E', 'V' )

/**
* @brief Number of source inputs available after the device is set
*
*        Read @c uint32_t
*/
#define	CAPTURE_PROPERTY_NSOURCES		CAPTURE_PROPERTY( 'Q', 'N', 'S', 'R' )

/**
* @brief Contrast (@c -128 to @c 127)
*
*        Read/Write @c int32_t
*/
#define CAPTURE_PROPERTY_CONTRAST		CAPTURE_PROPERTY( 'Q', 'C', 'O', 'N' )

/**
* @brief Brightness (@c -128 to @c 127)
*
*        Read/Write @c int32_t
*/
#define CAPTURE_PROPERTY_BRIGHTNESS		CAPTURE_PROPERTY( 'Q', 'B', 'R', 'I' )

/**
* @brief Color saturation (@c -128 to @c 127)
*
*        Read/Write @c int32_t
*/
#define CAPTURE_PROPERTY_SATURATION		CAPTURE_PROPERTY( 'Q', 'S', 'A', 'T' )

/**
* @brief Color hue (@c -128 to @c 127)
*
*        Read/Write @c int32_t
*/
#define CAPTURE_PROPERTY_HUE			CAPTURE_PROPERTY( 'Q', 'H', 'U', 'E' )

/**
* @brief Sharpness (@c -128 to @c 127); where an image is blurred at @c -128 to
*        the sharpest at @c 127
*
*        Read/Write @c int32_t
*/
#define CAPTURE_PROPERTY_SHARPNESS		CAPTURE_PROPERTY( 'Q', 'S', 'R', 'P' )

/**
* @brief Deinterlacing flags (bit-field)
*
*        Use @c #CAPTURE_DEI_WEAVE_FLAG_BOTTOM_TOP
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DEINTERLACE_FLAGS	CAPTURE_PROPERTY( 'Q', 'D', 'E', 'I' )

/**
* @brief Used to specify the field order for weave deinterlacing. When set, the
*        weave order is to always weave bottom + top, possibly dropping an
*        unexpected first top field. When not set, the weave order is to always
*        weave top + bottom, possibly dropping an unexpected first bottom field.
* 
*/
#define CAPTURE_DEI_WEAVE_FLAG_BOTTOM_TOP	(1 << 0)

/**
* @brief Deinterlacing mode; refer to @ref Deinterlacing_Mode_Types
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DEINTERLACE_MODE	CAPTURE_PROPERTY( 'Q', 'D', 'E', 'M' )
/** @} */   /* end of addtogroup capture_driver_device */

/**
*   @addtogroup capture_deinterlacing
*   @{
*/
/**
*   @brief Types of deinterlacing modes
*   @anonenum Deinterlacing_Mode_Types Deinterlacing mode types
*/
enum capture_deinterlace_mode {
		/** Don't deinterlace. */
		CAPTURE_DEINTERLACE_NONE_MODE	= 0,
		/** Use weave deinterlacing mode. */
		CAPTURE_DEINTERLACE_WEAVE_MODE,
		/** Use bob deinterlacing mode. */
		CAPTURE_DEINTERLACE_BOB_MODE,
		/** Use alternate bob deinterlacing mode. */
		CAPTURE_DEINTERLACE_BOB2_MODE,
		/** Use alternate weave deinterlacing mode. */
		CAPTURE_DEINTERLACE_WEAVE2_MODE,
		/** Use motion adaptive deinterlacing mode. */
		CAPTURE_DEINTERLACE_MOTION_ADAPTIVE_MODE,
};
/** @} */   /* end of addtogroup capture_deinterlacing */

/**
*   @addtogroup capture_driver_device
*   @{
*/
/**
* @brief No signal mode; set default action if @"no carrier@" or @"no signal@" state
*        is detected
* @details Refer to @ref No_Signal_Mode_Types.
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_NO_SIGNAL_MODE		CAPTURE_PROPERTY( 'Q', 'N', 'O', 'S' )

/** 
*   @brief Types of no signal modes
*   @anonenum No_Signal_Mode_Types No signal mode types
*/
enum capture_no_signal_mode {
		/** Default behavior; defined by driver or hardware (unknown). */
		CAPTURE_NO_SIGNAL_DEFAULT_MODE	= 0,
		/** Show color or black-and-white noise (snow) on the display if there
		*   isn't an input video source. This is a common mode for hardware
		*   that doesn't support detection of video source signals
		*/
		CAPTURE_NO_SIGNAL_NOISE_MODE,
		/** Fill all frames with black (or close to black) color if no video
		*   source signal state is detected.
		*/
		CAPTURE_NO_SIGNAL_BLACK_MODE,
		/** Fill all frames with blue (or close to blue) color if no video
		*   source signal state is detected.
		*/
		CAPTURE_NO_SIGNAL_BLUE_MODE,
		/** Use a hardware or software pre-defined picture (usually with text
		*   @"NO SIGNAL@") if no video source signal state is detected.
		*/
		CAPTURE_NO_SIGNAL_TABLE_MODE,
};
/** @} */   /* end of addtogroup capture_driver_device */

/**
*   @addtogroup capture_dest_buffer
*   @{
*/
/**
* @brief Set default destination color space and values range of the color space.
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DST_COLOR_SPACE	CAPTURE_PROPERTY( 'Q', 'N', 'C', 'D' )
/** @} */   /* end of addtogroup capture_dest_buffer */

/**
*   @addtogroup capture_source_format
*   @{
*/
/**
* @brief A bit field that indicates the color space supported by
*        the capture device
*
*        Set this property according to the valid color space types
*        as defined by @ref Color_Space_Types.
*        The color space types may be used with bitwise operators and
*        the following flags to define @c #CAPTURE_PROPERTY_SRC_COLOR_SPACE:
*        - @c #CAPTURE_FLAG_COLOR_SPACE_LIMITED
*        - @c #CAPTURE_FLAG_COLOR_SPACE_YEXTEND
*        - @c #CAPTURE_FLAG_COLOR_SPACE_FULL
*        - @c #CAPTURE_FLAG_COLOR_SPACE_MASK
*
*        Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_SRC_COLOR_SPACE	CAPTURE_PROPERTY( 'Q', 'N', 'C', 'S' )

/**
*   @brief Types of color spaces
*   @anonenum Color_Space_Types Color space types
*/
enum capture_color_space {
		/** 
		* Use BT.601 (SDTV) defined primaries.
		*/
		CAPTURE_COLOR_SPACE_BT601 = 0,
		/** 
		* Use BT.709 (HDTV) defined primaries.
		*/
		CAPTURE_COLOR_SPACE_BT709,
		/** 
		* Use BT.2020 (UHDTV) defined primaries.
		*/
		CAPTURE_COLOR_SPACE_BT2020,
		/** 
		* Linear RGB color space.
		*/
		CAPTURE_COLOR_SPACE_LRGB,
		/** 
		* sRGB color space, use BT.709 (HDTV) defined primaries.
		*/
		CAPTURE_COLOR_SPACE_SRGB,
		/** 
		* Adobe RGB color space, similar to sRGB but with extended gamut range.
		*/
		CAPTURE_COLOR_SPACE_ADOBERGB,
};

/*
    Following flags could be ORed with selected color space from capture_colorspace enum.

    CAPTURE_FLAG_COLOR_SPACE_LIMITED - If color space is RGB use 16..235 RGB range. If color space is YUV use 16..235
                                       range for Y and 16..240 range for U and V.
    CAPTURE_FLAG_COLOR_SPACE_YEXTEND - If color space is RGB use 16..235 RGB range. If color space is YUV use 0..255
                                       extended range for Y and 16..240 range for U and V.
    CAPTURE_FLAG_COLOR_SPACE_FULL    - If color space is RGB use 0..255 extended RGB range. If color space is YUV use
                                       0..255 extended YUV range for all components. For a 10/12 bits per color component
                                       use full range of 0..1023/0..4095.
    CAPTURE_FLAG_COLOR_SPACE_MASK    - Mask to extract flags from color space data.
*/
/**
* @brief Use the following ranges for the specified color spaces:
*        - RGB: 16..235 RGB range
*        - YUV: 16..235 range for Y and 16..240 range for U and V
*/
#define CAPTURE_FLAG_COLOR_SPACE_LIMITED (0x00000000)

/**
* @brief Use the following ranges for the specified color spaces:
*        - RGB: 16..235 RGB range, works as CAPTURE_FLAG_COLOR_SPACE_LIMITED for RGB space.
*        - YUV: 0..255 range for Y and 16..240 range for U and V
*/
#define CAPTURE_FLAG_COLOR_SPACE_YEXTEND (0x01000000)

/**
* @brief Use the following ranges for the specified color spaces:
*        - RGB: 0..255 extended RGB range
*        - YUV: 0..255 extended YUV range for all components
*
*        For a 10/12 bits per color component, use full range of
*        0..1023/0..4095.
*
*/
#define CAPTURE_FLAG_COLOR_SPACE_FULL    (0x80000000)

/**
* @brief Mask to extract flags from color space data
*
*/
#define CAPTURE_FLAG_COLOR_SPACE_MASK    (0xFF000000)
/** @} */   /* end of addtogroup capture_source_format */

/**
*   @addtogroup capture_deinterlacing
*   @{
*/
/**
* @brief Minimum number of buffers required for a specific deinterlacing mode
*
*        Read @c uint32_t
*/
#define CAPTURE_PROPERTY_MIN_NBUFFERS		CAPTURE_PROPERTY( 'Q', 'M', 'N', 'B' )
/** @} */   /* end of addtogroup capture_deinterlacing */

/**
*   @addtogroup capture_external_source
*   @{
*/
/**
* @brief Mark the buffer as read-only
*/
#define CAPTURE_BUFFER_USAGE_RDONLY		0x001

/**
* @brief An array of buffer usage flags. Element @c i indicates if the capture
*        driver has read-only or read/write permission for buffer @c i. The
*        default is read/write permission.
*
*        Read/Write <tt>[] uint32_t</tt>
*/
#define CAPTURE_PROPERTY_BUFFER_USAGE		CAPTURE_PROPERTY( 'Q', 'B', 'U', 'S' )

/**
* @brief Index of the buffer to be injected by @c capture_put_buffer()
*
*        Write @c uint32_t
*/
#define CAPTURE_PROPERTY_BUFFER_INDEX		CAPTURE_PROPERTY( 'Q', 'B', 'I', 'X' )

/**
* @brief  Number of fields contained in the buffer to be injected by
*         @c capture_put_buffer()
*
*         Write @c uint32_t
*/
#define CAPTURE_PROPERTY_BUFFER_NFIELDS		CAPTURE_PROPERTY( 'Q', 'B', 'N', 'F' )

/**
* @brief  A per-buffer array. The array has one row per field. Each row
*         indicates the offset, in bytes, from base address for each of the Y,
*         U and V components of planar YUV formats.
*
*         This property is used for external sources. The library than handles
*         your hardware copies the data for the current frame rather than
*         storing a pointer to the array.
*
*         @c #CAPTURE_PROPERTY_BUFFER_PLANAR_OFFSETS has a dependency on:
*         - @c #CAPTURE_PROPERTY_BUFFER_INDEX
*         - @c #CAPTURE_PROPERTY_BUFFER_NFIELDS
*
*         Write <tt>[] [3] int32_t</tt>
*/
#define CAPTURE_PROPERTY_BUFFER_PLANAR_OFFSETS	CAPTURE_PROPERTY( 'Q', 'B', 'P', 'O' )

/**
* @brief  A per-buffer array of the following buffer flags:
*         - @c #CAPTURE_FRAME_FLAG_ERROR
*         - @c #CAPTURE_FRAME_FLAG_INTERLACED
*         - @c #CAPTURE_FRAME_FLAG_FIELD_BOTTOM
*
*         This property is used for external sources. The library than handles
*         your hardware copies the data for the current frame rather than
*         storing a pointer to the array.
*
*         @c #CAPTURE_PROPERTY_BUFFER_FLAGS has a dependency on:
*         - @c #CAPTURE_PROPERTY_BUFFER_INDEX
*         - @c #CAPTURE_PROPERTY_BUFFER_NFIELDS
*
*         Write <tt>[] uint32_t</tt>
*/
#define CAPTURE_PROPERTY_BUFFER_FLAGS		CAPTURE_PROPERTY( 'Q', 'B', 'F', 'L' )

/**
* @brief  A per-buffer array of sequence numbers. Each element indicates the
*         sequence number of the field contained in the buffer.
*
*         This property is used for external sources. The library than handles
*         your hardware copies the data for the current frame rather than
*         storing a pointer to the array.
*
*         @c #CAPTURE_PROPERTY_BUFFER_SEQNO has a dependency on:
*         - @c #CAPTURE_PROPERTY_BUFFER_INDEX
*         - @c #CAPTURE_PROPERTY_BUFFER_NFIELDS
*
*         Write <tt>[] uint32_t</tt>
*/
#define CAPTURE_PROPERTY_BUFFER_SEQNO		CAPTURE_PROPERTY( 'Q', 'B', 'S', 'N' )
/** @} */   /* end of addtogroup capture_external_source */

/**
*   @addtogroup capture_video_standards
*   @{
*/
/**
* @brief  Set the video standard
*
*         Refer to @ref Video_Standard_Macros.
*
*         Read/Write <tt>const char *</tt>
*/
#define CAPTURE_PROPERTY_NORM			CAPTURE_PROPERTY( 'Q', 'N', 'O', 'R' )

/**
* @brief When written, unblock any active capture_get_frame call; if not
*        blocked in this function, cause the next capture_get_frame call to
*        return immediately.  Usually EINTR would be returned, or ESRCH if the
*        capture driver is known to be in an unrecoverable state.
*
*        Write @c uint32_t (0, or a device-specific value)
*/
#define CAPTURE_PROPERTY_UNBLOCK CAPTURE_PROPERTY( 'Q', 'U', 'B', 'L' )

/**
* @brief  Use auto-detection to get the video standard
*
*         Read/Write <tt>const char *</tt>
*/
#define CAPTURE_NORM_AUTO			"AUTO"

/**
* @brief  Return the current detected video standard
*
*         Refer to @ref Video_Standard_Macros.
*
*         Read <tt>const char *</tt>
*/
#define	CAPTURE_PROPERTY_CURRENT_NORM		CAPTURE_PROPERTY( 'Q', 'Q', 'N', 'M' )

/**
* @brief  Video standard can't be detected; either there's no input, or the
*         video signal is lost
*/
#define CAPTURE_NORM_NONE			"NONE"

/**
* @brief  Detected standard is not known
*/
#define CAPTURE_NORM_UNKNOWN			"UNKNOWN"

/**
* @section Video_Standard_Macros Video standard macros
* @brief The video standard macros are common for @c #CAPTURE_PROPERTY_NORM and
*        @c #CAPTURE_PROPERTY_CURRENT_NORM.
*/
/** @brief Standard that's used in United States and Japan */
#define CAPTURE_NORM_NTSC_M_J			"NTSC_M_J"

/** @brief A pseudo-color system that transmits NTSC encoding (not a broadcast format) */
#define CAPTURE_NORM_NTSC_4_43			"NTSC_4_43"

/** @brief PAL format that uses 525 lines and 59.94 fields per second;
*          this video standard is used in Brazil
*/
#define CAPTURE_NORM_PAL_M			"PAL_M"

/** @brief PAL format using 625 lines and 50 fields per second with various
*          signal characteristics and color encodings
*/
#define CAPTURE_NORM_PAL_B_G_H_I_D		"PAL_B_G_H_I_D"

/** @brief PAL format with narrow bandwidth that's used in Argentina, Paraguay,
*          and Uruguay.
*/
#define CAPTURE_NORM_PAL_COMBINATION_N		"PAL_COMBINATION_N"

/** @brief Multi-system PAL support that uses 525 lines and 60 fields per second
*         (not a broadcast format)
*/
#define CAPTURE_NORM_PAL_60			"PAL_60"

/** @brief Video standard used mainly in France */
#define CAPTURE_NORM_SECAM			"SECAM"

/* These macros are based on CEA-861-E specification, only common widely used TV/camera video modes were added */
/** @brief VIC Format 1, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_640X480P_60HZ		"640x480p@60"

/** @brief VIC Format 2, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_720X480P_60HZ		"720x480p@60"

/** @brief VIC Format 4, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1280X720P_60HZ		"1280x720p@60"

/** @brief VIC Format 5, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080I_60HZ	"1920x1080i@60"

/** @brief VIC Format 6, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_720X480I_60HZ		"720x480i@60"

/** @brief VIC Format 16, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080P_60HZ	"1920x1080p@60"

/** @brief VIC Format 17, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_720X576P_50HZ		"720x576p@50"

/** @brief VIC Format 20, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080P_50HZ	"1920x1080p@50"

/** @brief VIC Format 21, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_720X576I_50HZ		"720x576i@50"

/** @brief VIC Format 32, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080P_24HZ	"1920x1080p@24"

/** @brief VIC Format 33, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080P_25HZ	"1920x1080p@25"

/** @brief VIC Format 34, based on CEA-861-E specification */
#define CAPTURE_NORM_CEA_1920X1080P_30HZ	"1920x1080p@30"
/** @} */   /* end of addtogroup capture_video_standards */

/**
*   @addtogroup capture_polarity
*   @{
*/
/**
* @brief  Specifies whether the field ID signal polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_INVERT_FID_POL		CAPTURE_PROPERTY( 'Q', 'L', 'F', 'I' )

/**
* @brief  Specifies whether the vertical synchronization polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
/* This property is defined incorrectly, it should be ( 'Q', 'L', 'V', 'S' ).
* Unfortunately, it has to remain misdefined to be compatible with drivers
* that you and other developers may have already written.
*/
#define CAPTURE_PROPERTY_INVERT_VSYNC_POL	CAPTURE_PROPERTY( 'Q', 'L', 'H', 'S' )

/**
* @brief  Specifies whether the horizontal synchronization polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
/* This property is defined incorrectly, it should be ( 'Q', 'L', 'H', 'S' ).
* Unfortunately, it has to remain misdefined to be compatible with drivers
* that you and other developers may have already written.
*/
#define CAPTURE_PROPERTY_INVERT_HSYNC_POL	CAPTURE_PROPERTY( 'Q', 'L', 'V', 'S' )

/**
* @brief  Specifies whether the clock polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_INVERT_CLOCK_POL	CAPTURE_PROPERTY( 'Q', 'L', 'P', 'C' )

/**
* @brief  Specifies whether the @"data_en@" pin/signal polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_INVERT_DATAEN_POL	CAPTURE_PROPERTY( 'Q', 'L', 'D', 'E' )

/**
* @brief  Specifies whether the data input polarity is inverted
*          - 0: Set polarity to not inverted
*          - 1: Set polarity to inverted
*          - -1: Don't set the polarity; use whatever polarity is already set
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_INVERT_DATA_POL CAPTURE_PROPERTY( 'Q', 'L', 'D', 'A' )
/** @} */   /* end of addtogroup capture_polarity */

/**
*   @addtogroup capture_source_format
*   @{
*/
/**
* @brief  Source format; a the format of the stream of pixels from the video
*         source
*         
*         When setting @c CAPTURE_PROPERTY_SRC_FORMAT, some valid values for
*         this property are defined by
*         <a href="../../com.qnx.doc.screen/topic/screen_8h_1Screen_Pixel_Format_Types.xml">
*         Screen pixel format types</a> in @c screen.h.
*         If @c CAPTURE_PROPERTY_SRC_FORMAT needs additional formats beyond
*         those in @c screen.h, then they must be defined in such a
*         way that they do not conflict with the definitions of the
*         Screen pixel format types.
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_SRC_FORMAT		CAPTURE_PROPERTY( 'Q', 'S', 'F', 'O' )

/**
* @brief  Source buffer stride, in bytes
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_SRC_STRIDE		CAPTURE_PROPERTY( 'Q', 'S', 'F', 'S' )

/**
* @brief  Width of the source, in pixels
*
*         Read/Write @c uint32_t
*/
#define	CAPTURE_PROPERTY_SRC_WIDTH		CAPTURE_PROPERTY( 'Q', 'S', 'W', 'I' )

/**
* @brief  Height of the source, in pixels
*
*         Read/Write @c uint32_t
*/
#define	CAPTURE_PROPERTY_SRC_HEIGHT		CAPTURE_PROPERTY( 'Q', 'S', 'H', 'E' )

/**
* @brief  Width of source viewport, in pixels
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_CROP_WIDTH		CAPTURE_PROPERTY( 'Q', 'C', 'W', 'I' )

/**
* @brief  Height of source viewport, in pixels
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_CROP_HEIGHT		CAPTURE_PROPERTY( 'Q', 'C', 'H', 'E' )
/** @} */   /* end of addtogroup capture_source_format */

/**
*   @addtogroup capture_driver_device
*   @{
*/
/**
* @brief  Video capture unit of the device.
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_SRC_INDEX		CAPTURE_PROPERTY( 'Q', 'S', 'I', 'D' )
/** @} */   /* end of addtogroup capture_driver_device */

/**
*   @addtogroup capture_source_format
*   @{
*/
/**
* @brief  Source viewport @c x offset
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_CROP_X			CAPTURE_PROPERTY( 'Q', 'C', 'X', 'P' )

/**
* @brief  Source viewport @c y offset
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_CROP_Y			CAPTURE_PROPERTY( 'Q', 'C', 'Y', 'P' )
/** @} */   /* end of addtogroup capture_source_format */

/**
*   @addtogroup capture_dest_buffer
*   @{
*/
/**
* @brief  Width of destination frame, in pixels
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DST_WIDTH		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'W' )

/**
* @brief  Height of destination frame buffer, in pixels
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DST_HEIGHT		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'H' )

/**
* @brief  Stride of destination frame buffer, in bytes
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_DST_STRIDE		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'S' )

/**
* @brief  Size of destination frame buffer, in bytes.
*
*         For planar YUV formats, the size of each allocated destination buffer
*         must be large enough for all the planes. 
*
*         For other formats, each allocated destination buffer
*         (@c #CAPTURE_PROPERTY_DST_NBYTES) must be at least the product of the
*         destination stride and the destination frame height
*         (@c #CAPTURE_PROPERTY_DST_STRIDE x @c #CAPTURE_PROPERTY_DST_HEIGHT).
*
*         Read/Write @c uint32_t
*/
#define	CAPTURE_PROPERTY_DST_NBYTES		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'B' )
/** @} */   /* end of addtogroup capture_dest_buffer */

/**
*   @addtogroup capture_frame
*   @{
*/
/**
* @brief  Number of frame buffers that have been specified in
*         @c #CAPTURE_PROPERTY_FRAME_BUFFERS.
*
*         Read/Write @c uint32_t
*/
#define	CAPTURE_PROPERTY_FRAME_NBUFFERS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'N' )

/*
 * NOTE: Array properties have special handling. The user's code must provide pointers to the arrays.
 * The pointers are stored in the capture library's context. The access modifiers in the properties
 * below are for the user's intended access of the arrays contents. If an array for a property is not set,
 * the capture library is not going to do the work associated with getting the data from
 * the hardware.
 * see the note and example of capture_set_property_p().
 */

/**
* @brief  Pointers to the video capture buffers
*
*         Read/Write <tt>[] void*</tt>
*/
#define CAPTURE_PROPERTY_FRAME_BUFFERS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'A' )

/**
* @brief  An array of @c CLOCK_MONOTONIC timestamps indexed by the buffer index
*
*         Read <tt>[] uint64_t</tt>
*/
#define	CAPTURE_PROPERTY_FRAME_TIMESTAMP	CAPTURE_PROPERTY( 'Q', 'F', 'B', 'T' )

/**
* @brief  An array of SMPTE (Society of Motion Picture and Television Engineers)
*         timecodes indexed by the buffer index; used for streams with
*         metadata
*/
#define	CAPTURE_PROPERTY_FRAME_TIMECODE		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'C' )

/**
* @brief  An array of frame sequence numbers indexed by the buffer index
*
*         Read <tt>[] uint32_t</tt>
*/
#define	CAPTURE_PROPERTY_FRAME_SEQNO		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'S' )

/**
* @brief  An array of frame flags indexed by the buffer index. Refer to
*         - @c #CAPTURE_FRAME_FLAG_ERROR
*         - @c #CAPTURE_FRAME_FLAG_INTERLACED
*         - @c #CAPTURE_FRAME_FLAG_FIELD_BOTTOM
*
*         Read <tt>[] uint32_t</tt>
*/
#define	CAPTURE_PROPERTY_FRAME_FLAGS		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'F' )

/**
* @brief  An array of frame sizes, in bytes, indexed by the buffer index
*
*         Read/Write <tt>[] uint32_t</tt>
*/
#define	CAPTURE_PROPERTY_FRAME_NBYTES		CAPTURE_PROPERTY( 'Q', 'F', 'B', 'B' )

/**
* @brief  There is an error in the frame
*/
#define	CAPTURE_FRAME_FLAG_ERROR		0x0001

/**
* @brief  Frame is interlaced. For more information about interlacing, refer to
*         @ref Deinterlacing_Mode_Types.
*/
#define	CAPTURE_FRAME_FLAG_INTERLACED		0x0002

/**
* @brief Indicator of the video frame field received.
*        When the video uses interlacing (i.e., @c #CAPTURE_FRAME_FLAG_INTERLACED
*        is set), then when the bottom field (even line numbers) is
*        received, @c #CAPTURE_FRAME_FLAG_FIELD_BOTTOM is set. When the top
*        field (odd line numbers) is received,
*        @c #CAPTURE_FRAME_FLAG_FIELD_BOTTOM is unset.
*/
#define	CAPTURE_FRAME_FLAG_FIELD_BOTTOM		0x0004

/**
* @brief  Indicator that the frame or field is shorter than expected. If the frame or
*         field is shorter because of errors in transmission, the flag
*         #CAPTURE_FRAME_FLAG_ERROR is also set. Otherwise, a shorter than
*         expected frame of field can be due to either of the following:
*         - an incorrect selection of analog broadcast standard (e.g., the hardware is
*           expecting a PAL 576i signal, but an NTSC 480i is used instead)
*         - an incomplete frame
*/
#define	CAPTURE_FRAME_FLAG_SHORT		0x0008
/** @} */   /* end of addtogroup capture_frame */

/**
*   @addtogroup capture_dest_buffer
*   @{
*/
/**
* @brief  Destination buffer format
*
*         When setting @c CAPTURE_PROPERTY_SRC_FORMAT, the valid values for
*         this property are defined by Screen pixel format types in @c screen.h.
*
*         Read/Write <tt>[] uint32_t</tt>
*
*/
#define CAPTURE_PROPERTY_DST_FORMAT		CAPTURE_PROPERTY( 'Q', 'D', 'F', 'F' )
/** @} */   /* end of addtogroup capture_dest_buffer */

/**
*   @addtogroup capture_dest_buffer
*   @{
*/
/**
* @brief  Offset from the base address for each of the Y, U, and V components of
*         planar YUV formats.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_PLANAR_OFFSETS		CAPTURE_PROPERTY( 'Q', 'P', 'L', 'O' )
/** @} */   /* end of addtogroup capture_dest_buffer */

/**
*   @addtogroup capture_properties_threads
*   @{
*/
/**
* @brief  Scheduling priority of the capture thread.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_THREAD_PRIORITY	CAPTURE_PROPERTY( 'Q', 'T', 'P', 'R' )
/** @} */   /* end of addtogroup capture_properties_threads */

/**
*   @addtogroup capture_data
*   @{
*/
/**
* @brief  Interface type
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_INTERFACE_TYPE		CAPTURE_PROPERTY('Q','P','I','F')
/** @} */   /* end of addtogroup capture_data */

/**
*   @addtogroup capture_data
*   @{
*/
/**
*   @brief Types of interfaces
*   @anonenum Interface_Types Interface types
*/
enum capture_iface_type {
    /** The interface is parallel. */
	CAPTURE_IF_PARALLEL = 0,
    /** The interface is a MIPI CSI2 interface. */
	CAPTURE_IF_MIPI_CSI2,
};
/** @} */   /* end of addtogroup capture_data */

/**
*   @addtogroup capture_data
*   @{
*/
/**
* @brief  Width of data bus for parallel interfaces. Valid values are 8, 10, 16,
*         etc.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_DATA_BUS_WIDTH		CAPTURE_PROPERTY( 'Q', 'D', 'B', 'W' )

/**
* @brief  Number of CSI2 data lanes.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_NUM_DATA_LANES	CAPTURE_PROPERTY('Q','C','N','D')

/**
* @brief  Position of CSI2 clock lane.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_CLK_LANE_POS	CAPTURE_PROPERTY('Q','C','C','P')

/**
* @brief  Position of CSI2 data lane 0.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_DATA0_LANE_POS	CAPTURE_PROPERTY('Q','C','D','0')

/**
* @brief  Position of CSI2 data lane 1.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
**         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_DATA1_LANE_POS	CAPTURE_PROPERTY('Q','C','D','1')

/**
* @brief  Position of CSI2 data lane 2.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_DATA2_LANE_POS	CAPTURE_PROPERTY('Q','C','D','2')

/**
* @brief  Position of CSI2 data lane 3.
*
*         Valid values are 1 to 4, or -1 to default
*         to the number or position that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_DATA3_LANE_POS	CAPTURE_PROPERTY('Q','C','D','3')

/**
* @brief   CSI2 Virtual Channel Identifier number.
*
*         Valid values are 0 to 3, or -1 to default
*         to the virtual channel indentifier number that's already set in the hardware.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_VCHANNEL_NUM	CAPTURE_PROPERTY('Q','C','V','N')

/**
* @brief   CSI2 dual date rate (DDR) clock frequency in MHz.
*
*         Used on the CSI2 receiver side, to match the DDR clock of the transmitter.
*
*         Read/Write @c int
*/
#define CAPTURE_PROPERTY_CSI2_DDR_CLOCK_MHZ	CAPTURE_PROPERTY('Q','C','D','C')

/** @} */   /* end of addtogroup capture_data */

/**
*   @addtogroup capture_properties_debugging
*   @{
*/
/**
* @brief  Log verbosity level. Default is 0; increase this value to
*         increase log verbosity for debugging.
*
*         Read/Write @c uint32_t
*/
#define CAPTURE_PROPERTY_VERBOSITY		CAPTURE_PROPERTY( 'Q', 'V', 'B', 'R' )

/**
* @brief  File log messages are written to. Default is @c stderr; A
*         NULL pointer disables logging.
*
*         Read/Write <tt>FILE*</tt>
*/
#define CAPTURE_PROPERTY_VERBOSITY_FILE		CAPTURE_PROPERTY('Q','V','B','F')

/**
* @brief  User-defined string that log messages will be prefixed with.
*
*         Read/Write <tt>char*</tt>
*/
#define CAPTURE_PROPERTY_LOGMSG_PREFIX		CAPTURE_PROPERTY('Q','L','M','P')
/** @} */   /* end of addtogroup capture_properties_debugging */

/**
*   @addtogroup capture_decoder
*   @{
*/
/**
* @brief  Device path of the I2C decoder (e.g., <tt>\/dev\/i2c0</tt>). This
*         property is only applicable to decoders that are connected via I2C.
*
*         Read/Write <tt>const char *</tt>
*/
#define CAPTURE_PROPERTY_DECODER_I2C_PATH	CAPTURE_PROPERTY('Q','D','I','P')

/**
* @brief  The 7-bit Slave address of the I2C decoder. This property is only
*         applicable to decoders that are connected via I2C.
*
*         Read/Write <tt>const char *</tt>
*/
#define CAPTURE_PROPERTY_DECODER_I2C_ADDR	CAPTURE_PROPERTY('Q','D','I','A')
/** @} */   /* end of addtogroup capture_decoder */

/**
*   @addtogroup capture_helper
*   @{
*/
/**
* @brief  Convert interval, argument @c x, from milliseconds to nanoseconds
*         
*         Required for the @c timeout argument of @c capture_get_frame().
*/
#define CAPTURE_INTERVAL_FROM_MS(x)		((x) * 1000000ULL)

/**
* @brief  Convert interval, argument @c x, from microseconds to nanoseconds
*         
*         Required for the @c timeout argument of @c capture_get_frame().
*/
#define CAPTURE_INTERVAL_FROM_US(x)		((x) * 1000ULL)

/**
* @brief  Convert interval, argument @c x, from nanoseconds to nanoseconds
*         
*         Required for the @c timeout argument of @c capture_get_frame().
*/
#define CAPTURE_INTERVAL_FROM_NS(x)		(x)

/**
* @brief  Convert interval, argument @c x, to milliseconds from nanoseconds
*/
#define CAPTURE_INTERVAL_TO_MS(x)		((x) / 1000000ULL)

/**
* @brief  Convert interval, argument @c x, to microseconds from nanoseconds
*/
#define CAPTURE_INTERVAL_TO_US(x)		((x) / 1000ULL)

/**
* @brief  Convert interval, argument @c x, to nanoseconds from nanoseconds
*/
#define CAPTURE_INTERVAL_TO_NS(x)		(x)

/**
* @brief  Amount of time, in nanoseconds, between NTSC fields
*/
#define CAPTURE_INTERVAL_NTSC_FIELD		16668333

/**
* @brief  Amount of time, in nanoseconds, between NTSC frames
*/
#define CAPTURE_INTERVAL_NTSC_FRAME		(CAPTURE_INTERVAL_NTSC_FIELD * 2)
/** @} */   /* end of addtogroup capture_helper */

__END_DECLS
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/capture/public/vcapture/capture.h $ $Rev: 816229 $")
#endif
