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

/**
 * @file utl_fd.h
 *
 * Utility functions for monitoring and processing I/O on file descriptors and timers.
 *
 * @par Overview
 *
 * @todo Provide some further detail and examples here for this API.
 */

#ifndef __UTL_FD_H_INCLUDED
#define __UTL_FD_H_INCLUDED

#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef _UNISTD_H_INCLUDED
#include <unistd.h>
#endif

#ifndef __SELECT_H_INCLUDED
#include <sys/select.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

struct sigevent;

/**
 * Event types that can be monitored for or received in the callback function for monitored
 * file descriptors and timeouts.
 *
 * @see utl_fd_event_f
 */
typedef enum
{
    /** Data is available for reading on the file descriptor. */
    UTL_FD_EVENT_READ = 0x01,
    /** Room is available for writing on the file descriptor. */
    UTL_FD_EVENT_WRITE = 0x02,
    /** Out-of-band data is available on the file descriptor. */
    UTL_FD_EVENT_OOBAND = 0x04,
    /** A timer created using utl_fd_add_timer expired. */
    UTL_FD_EVENT_TIMEOUT = 0x08,
    /** The file descriptor being monitored is no longer valid. */
    UTL_FD_EVENT_BAD_FD = 0x10,
    /** An event associated with a sigevent has been received. */
    UTL_FD_EVENT_SIGEVENT = 0x20,
    /** A sigevent returned from @c utl_fd_request_sigevent is no longer valid because the notify set
        was moved to a different group. */
    UTL_FD_EVENT_STALE_SIGEVENT = 0x40,
} utl_fd_event_t;

/**
 * Callback function used to notify the caller about timer events or events related to operations on a file descriptor.
 *
 * @param[in] notify_set The string representing the notify set for the fd or timer.
 * @param[in] fd         The file descriptor the event affects, or @c -1 for a timer or sigevent event (@c event is #UTL_FD_EVENT_TIMEOUT, #UTL_FD_EVENT_SIGEVENT or #UTL_FD_EVENT_STALE_SIGEVENT).
 * @param[in] event      The event type for the notification.
 * @param[in] cb_data    The original @c cb_data passed in to utl_fd_set_events() or utl_fd_add_timer().
 *
 * @see utl_fd_set_events, utl_fd_remove, utl_fd_add_timer & utl_fd_remove_timer
 */
typedef void (*utl_fd_event_f)(const char *notify_set, int fd, utl_fd_event_t event, void *cb_data);

/**
 * Event types that can be used to notify an event loop that the set of file descriptors or timers has changed
 * or that it should termimate.  These are needed only if you are implementing your own event loop rather than
 * using @c utl_fd_monitor_loop().
 *
 * @see utl_fd_register_event_loop_handler, utl_fd_event_loop_f
 */
typedef enum
{
    /** Indicates the set of file descriptors or timers in the group might have changed. Typically this should
     * cause a call to @c select() or @c MsgReceive() to be interrupted to allow the set of file descriptors or
     * timeout to be change.
     */
    UTL_FD_EVENT_LOOP_CHANGED = 1,
    /** Indicates that the event loop should terminate.  */
    UTL_FD_EVENT_LOOP_TERMINATE = 2,
} utl_fd_event_loop_event_t;

/**
 * Callback function used to provide a notification about an event associated with implementing an event loop.
 *
 * @param[in] group_id   The id of the group with which the event is associated.
 * @param[in] event      The event.
 * @param[in] cb_data    The original @c cb_data passed to @c utl_fd_register_event_loop_handler().
 *
 * @retval None
 *
 * @see utl_fd_register_event_loop_handler, utl_fd_terminate_event_loop, utl_fd_notify_event_loop
 */
typedef void (*utl_fd_event_loop_f)(const char *group_id, utl_fd_event_loop_event_t event, void *cb_data);

/**
 * Options for the @c utl_fd_change_loop_options() function.
 */
typedef enum
{
    /** Indicates that the event loop should exit when there are no file descriptors to monitor and no timers.
     * This option is enabled by default.
     */
    UTL_FD_OPTION_EXIT_WHEN_EMPTY = 1,
    /** Request that the event loop monitor for lost connections. By default this option is enabled for the
     * NULL group and disabled for all others; this is usually the appropriate behavior since only a single
     * channel is able to use the _NTO_CHF_COID_DISCONNECT flag which is necessary for this feature. Without this
     * option being used there might be no notification of when a file descriptor ceases to be valid following
     * the exit of the resource manager supporting it.  Despite the option being handled by a single event handler
     * notifications of UTL_FD_EVENT_BAD_FD events will still be made in the thread associated with the group
     * with which the handler has been registered.
     *
     * An event loop that supports detecting connection loss should call @c utl_fd_notify_connection_loss() when
     * it becomes aware of a connection being lost.
     */
    UTL_FD_OPTION_DETECT_CONNECTION_LOSS = 2,
} utl_fd_loop_option_t;

/**
 * Set the events to be monitored for a file descriptor.
 *
 * Depending on the event types selected, a callback function will be called when there is data available to be read or when the
 * file descriptor can be written. The callback function is called from the thread that utl_fd_process_fd_sets() or
 * utl_fd_process_event() is called from.
 *
 * @param[in] fd         The file descriptor to be monitored.
 * @param[in] events     The bitwise OR of zero or more event types from utl_fd_event_t to monitor. The events that can be requested
 *                       are #UTL_FD_EVENT_READ, #UTL_FD_EVENT_WRITE and #UTL_FD_EVENT_OOBAND.
 * @param[in] notify_set A string that indicates the notify set for the file descriptor. By default the notify set has no effect. By
 *                       use of utl_fd_set_group() notify sets can be assigned to groups that can then be processed in different
 *                       threads. This parameter may be @c NULL to assign to the default notify set. A file descriptor may be
 *                       associated with different notify sets though each must monitor different events.
 * @param[in] event_cb   Function to be called when an event occurs on the file descriptor.
 * @param[in] cb_data    Arbitrary data to be passed to the callback function.
 *
 * @retval None
 *
 * @see utl_fd_event_t
 */
void utl_fd_set_events(int fd, unsigned int events, const char *notify_set, utl_fd_event_f event_cb, void *cb_data);

/**
 * Stop monitoring a file descriptor.
 *
 * This removes all notifications for the given file descriptor.
 *
 * @param[in] fd The file descriptor being monitored.
 *
 * @retval None
 */
void utl_fd_remove(int fd);

/**
 * Removes a notify set freeing all memory associated with it.
 *
 * File descriptors that are associated with the notify set will no longer be monitored.
 *
 * @param[in] notify_set The name of the notify set. If this is @c NULL the call is ignored.
 *
 * @retval None
 */
void utl_fd_remove_notify_set(const char *notify_set);

/**
 * Removes a group freeing all memory associated with it.
 *
 * Frees up memory associated with a group and in the case of groups that have been used with utl_fd_message_loop
 * closes the channel that was created.
 *
 * Any notify sets associated with the group are moved to an internal group which is ignored. To have any file descriptors or timers
 * that were previously associated with the group monitored, the notify sets they are in must be assigned to another group.
 *
 * The @c NULL group is treated specially as it is not explicitly created and cannot be destroyed.  Calling
 * @c utl_fd_remove_group with the @c NULL group will close the channel that is associated with the group but not
 * affect anything else.
 *
 * @param[in] group_id The group to remove.
 *
 * @retval None
 */
void utl_fd_remove_group(const char *group_id);

/**
 * Assign a notify set to a group.
 *
 * To allow file descriptors to be monitored and timers triggered from different threads, they can be assigned to different notify
 * sets and notify sets can be assigned to a group which are then handled as a unit. By default all notify sets are associated with
 * a @c NULL group.
 *
 * @param[in] notify_set Notify set to be assigned to a group.
 * @param[in] group_id   The group the notify set should be assigned to. This may be @c NULL to remove any group assignment.
 *
 * @retval None
 */
void utl_fd_set_group(const char *notify_set, const char *group_id);

/**
 * Add a one shot timer that will call a function after the specified elapsed time.
 *
 * Calling this function with the same combination of notify set, callback function and callback data as an existing
 * timer will update that timer.
 *
 * @param[in] notify_set A string that indicates the notify set of the timer. By default the notify set has no effect. By use of
 *                       utl_fd_set_group() notify sets can be assigned to groups that can then be processed in different threads.
 * @param[in] timeout    Time after which the timer should expire in milliseconds.
 * @param[in] event_cb   Function to be called when the time expires.
 * @param[in] cb_data    Arbitrary data to be passed to the callback function.
 *
 * @retval None
 *
 * @see utl_fd_remove_timer
 */
void utl_fd_add_timer(const char *notify_set, unsigned int timeout, utl_fd_event_f event_cb, void *cb_data);

/**
 * Remove the timer with the given callback function and data.
 *
 * @param[in] notify_set The notify set associated with the timer.
 * @param[in] event_cb   Callback function associated with the timer.
 * @param[in] cb_data    Callback data associated with the timer.
 *
 * @retval None
 *
 * @see utl_fd_add_timer
 */
void utl_fd_remove_timer(const char *notify_set, utl_fd_event_f event_cb, void *cb_data);

/**
 * Initializes a sigevent structure and associate a callback with it.
 *
 * Initializes a sigevent structure and associates a callback with it such that the callback will be called
 * if the event is ever delivered.
 *
 * @c utl_fd_request_sigevent() is only useful if @c utl_fd_monitor_loop() is used as a message loop.
 *
 * @param[in] notify_set A string that indicates the notify set of the timer. By default the notify set has no effect. By use of
 *                       utl_fd_set_group() notify sets can be assigned to groups that can then be processed in different threads.
 * @param[in]  event_cb  Function to be called when the time expires.
 * @param[in]  cb_data   Arbitrary data to be passed to the callback function.
 * @param[out] event     A sigevent structure to be initialized.
 *
 * @retval None
 *
 * @see utl_fd_release_sigevent
 */
void utl_fd_request_sigevent(const char *notify_set, utl_fd_event_f event_cb, void *cb_data, struct sigevent *event);

/**
 * Disassociates a sigevent structure from a callback.
 *
 * @param[in] notify_set The notify set associated with the timer.
 * @param[in] event      An event previously initialzed by calling utl_fd_request_sigevent.
 * @param[in] cb_data    Callback data associated with the timer.
 *
 * @retval None
 *
 * @see utl_fd_request_sigevent
 */
void utl_fd_release_sigevent(const char *notify_set, const struct sigevent *event);

/**
 * Update the given fd sets with the file descriptors in the indicated group.
 *
 * This function and the utl_fd_process_fd_sets() function support creation of a select() based event loop for monitoring file
 * descriptors.
 *
 * @param[in]     group_id   The id of the group to process. This may be @c NULL for the default group.
 * @param[in,out] read_set   The @c fd_set to be updated for read events. This may be @c NULL if it is known that no file
 *                           descriptor is being monitored for read events.
 * @param[in,out] write_set  The @c fd_set to be updated for write events. This may be @c NULL if it is known that no file
 *                           descriptor is being monitored for write events.
 * @param[in,out] except_set The @c fd_set to be updated for exceptional events. This may be @c NULL if it is known that no file
 *                           descriptor can generate these events.
 * @param[in,out] fd_max     The largest fd that was updated in the set if this is greater than the value that was passed in.
 * @param[in,out] timeout    If non-NULL, this will be updated if a timer in the group would expire earlier than the passed in
 *                           timeout.
 *
 * @retval 1    At least one file descriptor was added to an @c fd_set or a timer is active.
 * @retval 0    There were no file descriptors to add and no timers.
 * @retval -1   An error occurred. The specific error is contained in @c errno.
 */
int utl_fd_update_fd_sets(const char *group_id, fd_set *read_set, fd_set *write_set, fd_set *except_set, int *fd_max,
                          struct timeval * timeout);

/**
 * Issue callbacks for registered file descriptors within an @c fd_set.
 *
 * This should be called following any call to @c select() that returns a positive value or where select returns @c -1 with an
 * @c errno of @c EBADF. Calls made when select returns an error might result in callbacks being made for bad file descriptors.
 *
 * @param[in]     group_id   The id of the group to process. This may be @c NULL for the default group.
 * @param[in]     num_fds    The number of file descriptors in @c read_set and @c write_set or @c -1 to verify the file descriptors
 *                           and issue callbacks for any bad ones. This can usually just be the return value from the call to
 *                           @c select(). If @c 0 is passed the effect is identical to calling utl_fd_process_timeout().
 * @param[in,out] read_set   The @c fd_set containing the file descriptors that are ready for reading. Any file descriptors that are
 *                           processed by this function are cleared from the set. This parameter may be @c NULL if it is known that
 *                           there are no file descriptors that were monitored for read events.
 * @param[in,out] write_set  The @c fd_set containing the file descriptors that are ready for writing. Any file descriptors that are
 *                           processed by this function are cleared from the set. This parameter may be @c NULL if it is known that
 *                           there are no file descriptors that were monitored for write events.
 * @param[in,out] except_set The @c fd_set containing the file descriptors that have exceptional events pending. Any file
 *                           descriptors that are processed by this function are cleared from the set. This parameter may be @c NULL
 *                           if it is known that there are no file descriptors that could have exceptional events.
 *
 * @return The number of file descriptors processed and cleared from the fd sets. This will be zero if @c num_fds is @c -1.
 */
int utl_fd_process_fd_sets(const char *group_id, int num_fds, fd_set *read_set, fd_set *write_set, fd_set *except_set);

/**
 * Change options associated with an event loop.
 *
 * Allows options that affect the behavior of the event loop used for a group to be changed.  The options
 * typically have to be set prior to starting the event loop.
 *
 * @param[in]  group_id   The id of the group to change options on.
 * @param[in]  set        If true, the indicated options are set, otherwise they are cleared.
 * @param[in]  options    Options to set of clear. This should usually be one or more values from
 *                        @c utl_fd_loop_option_t ORed together.  If a custom event loop is used rather than
 *                        @c utl_fd_monitor_loop() then the meaning of options is determined by it.
 *
 * @return The resulting options.
 *
 * @see utl_fd_loop_option_t
 */
int utl_fd_change_loop_options(const char *group_id, bool set, int options);

/**
 * Provide notification of the loss of a connection.
 *
 * A thread that has created a channel using the flag _NTO_CHF_COID_DISCONNECT should call this function with
 * the value included in any pulse it receives with a _PULSE_CODE_COIDDEATH code.  This should only be needed
 * if custom event loops are used.  If events are received through calling @c utl_fd_monitor_loop() then
 * connection loss detection will be handled automatically.
 *
 * @param[in]  coid  Connection id provided as the value of a _PULSE_CODE_COIDDEATH pulse.
 *
 * @retval None
 *
 * #see ChannelCreate
 */
void utl_fd_notify_connection_loss(int coid);

/**
 * Enter an event loop monitoring the file descriptors associated with a group.
 *
 * Event loops may be nested, that is while executing a callback function for a file descriptor or timer called
 * one call to @c utl_fd_event_loop() one may make a second, recursive, call to @c utl_fd_event_loop() with the
 * same @c group_id.  One must not however call @c utl_fd_event_loop() with the same @c group_id from more than
 * one thread.
 *
 * By default the function will terminate when there are no more file descriptors to monitor and no timers set.
 * If this is not desired the behavior can be changed by calling @c utl_fd_change_loop_options().  The function
 * may also be explicitly terminated by calling @c utl_fd_terminate_event_loop().
 *
 * @param[in] group_id The id of the group to monitor. This may be @c NULL for the default group.
 *
 * @retval None
 *
 * @see utl_fd_terminate_event_loop, utl_fd_change_loop_options
 */
void utl_fd_monitor_loop(const char *group_id);

/**
 * Register a handler to be notified of events associated with an event loop.
 *
 * This should be used only if you are implementing your own event/message loop rather than using
 * @c utl_fd_monitor_loop() or @c utl_fd_event_loop(). There can only be a single event loop handler for a given
 * group at any one time.  If a process intends to allow for nested event loops it is important that it calls
 * this function on entry each loop and on exit calls it once again to restore the old handler.
 *
 * @param[in] group_id      The id of the group the handler is associated with.
 * @param[in] handler       Callback function to receive event notifications.
 * @param[in] cb_data       Arbitrary data to be passed to the callback function.
 * @param[out] old_handler  Pointer to a location to be assigned the current callback funciton.  This may be NULL
 *                          if nested event loops are not being supported or when @c utl_fd_register_event_loop_handler
 *                          is being called to restore a previous callback.
 * @param[out] old_cb_data  Pointer to a location to be assigned the current callback function's callback data.
 *                          This can be @c NULL whenever @c old_handler is @c NULL.
 *
 * @retval None
 */
void utl_fd_register_event_loop_handler(const char *group_id, utl_fd_event_loop_f handler, void *cb_data, utl_fd_event_loop_f *old_handler, void **old_cb_data);

/**
 * Request termination of the event loop for the indicated group.
 *
 * This function calls the current event loop handler with a UTL_FD_EVENT_LOOP_TERMINATE event. A call to this
 * function will terminate the most recent call to @c utl_fd_event_loop() or @c utl_fd_monitor_loop() if either
 * of these has been called and should also terminate any custom event loop.
 *
 * Calling @c utl_fd_terminate_event_loop() is equivalent to calling @c utl_fd_notify_event_loop() with a @c
 * UTL_FD_EVENT_LOOP_TERMINATE event.
 *
 * @param[in] group_id  The id of the group associated with the event loop to terminate.
 *
 * @retval None
 */
void utl_fd_terminate_event_loop(const char *group_id);

/**
 * Send an event to an event loop.
 *
 * This function calls the function that was most recently registered for the group by calling @c
 * utl_fd_register_event_loop_handler().
 *
 * @param[in] group_id  The id of the group associated with the event loop.
 * @param[in] event     Event to send.
 *
 * @retval None
 */
void utl_fd_notify_event_loop(const char *group_id, utl_fd_event_loop_event_t event);

/**
 * The utility event value mask.
 *
 * This mask indicates the bits of an event that are used internally by the API, and consequently the bits available for a caller to
 * define (the zero bits).
 *
 * @see utl_fd_update_event
 */
#define UTL_FD_EVENT_VALUE_MASK 0xf00fffff

/**
 * Arm the resource manager associated with each file descriptor in the group to deliver an event when data can be read or written
 * on the file descriptors.
 *
 * The type of event passed in must be one of @c SIGEV_PULSE, @c SIGEV_SIGNAL_CODE or @c SIGEV_SIGNAL_THREAD. The actual event used
 * will have bits changed in its values, the bits affected are those given by #UTL_FD_EVENT_VALUE_MASK. The caller is free to use
 * any of the zero bits in the mask for its own purpose. This might for example be useful to allow the same event code to be used
 * for this function as for other purposes, the owner of the delivered pulse or signal being distinguished by these bits.
 *
 * @param[in]     group_id  The id of the group that should be armed.
 * @param[in]     event     The event that should be used for arming.
 * @param[in,out] timeout   If non-NULL, this will be updated if a timer in the group would expire earlier than the passed in
 *                          timeout. The value returned can be used with @c TimerTimeout() using the @c CLOCK_MONOTONIC clock.
 *
 * @retval 1    At least one file descriptor was successfully armed or a timer is active.
 * @retval 0    There were no armed file descriptors and no timers.
 * @retval -1   An error occurred. The specific error is contained in @c errno.
 */
int utl_fd_update_event(const char *group_id, struct sigevent *event, uint64_t *timeout);

/**
 * Process the file descriptor associated with a given event.
 *
 * @param[in] group_id    The id of the group associated with the event.
 * @param[in] event_code  The code received with the event.
 * @param[in] event_value The value received with the event.
 *
 * @retval None
 */
void utl_fd_process_event(const char *group_id, int event_code, int event_value);

/**
 * Issue callbacks for any expired timers in the group.
 *
 * This should be called in the event a call to MsgReceive() times out.
 *
 * @param[in] group_id The id of the group to handle timers for.
 *
 * @retval None
 */
void utl_fd_process_timeout(const char *group_id);

/** @cond */
__END_DECLS
/** @endcond */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/utlfd/public/sys/utl_fd.h $ $Rev: 810649 $")
#endif
