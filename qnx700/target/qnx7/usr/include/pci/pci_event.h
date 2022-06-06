#ifndef _PCI_EVENT_H_
#define _PCI_EVENT_H_
/*
 * $QNXLicenseC:
 * Copyright (c) 2012, 2016 QNX Software Systems. All Rights Reserved.
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

#include <pci/pci.h>
#include <pthread.h>


/*
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 PCI server event API's

 The PCI library provides a set of event notification API's that allow the
 caller to easily register a handler function to be called whenever the event
 of interest occurs. This mechanism eliminates the need for the caller to have
 to manage connections or otherwise worry about the details of event delivery
 and instead concentrate on the details of handling the event occurrence.

 The use of the event notification API's requires at least one event processing
 server module to be loaded. See /etc/system/config/pci/pci_server-template.cfg
 for a description on how to load server modules.

 Below is the current list of events which are supported and the server module
 which provides the notification. Note that some modules will handle more than
 one event and there may be more than one module which handles a given event

 1. device insertion and removal      - pci_server-event_handler.so
 2. link state change                 - pci_server-event_handler.so
 3. link bandwidth change             - pci_server-event_handler.so

 See also 'pci_event_type_e' below for more details on which events are
 currently supported, which server module provides that support and other
 details on the event delivery

 General Usage
 -------------
 In general, events of interest, and optionally their attributes, are
 established with the pci_event_create() API.

 This function will return a unique 'pci_event_t' which is then associated with
 the event and which can be used to register for notification of that specific
 event. Event creation is separate from and independent of event notification
 registration.

 In order to receive notification of specific events, events of interest
 (identified by their 'pci_event_t') are registered with the pci_event_reg()
 API. In addition to the event of interest, the caller provides the following
 additional information

	1 a registration identifier (pci_event_regid_t) which will identify the
	  entity for which occurrence of the specific event type should be
	  delivered
	2 a handler function to be called when the event occurs on the entity
	  identified by the 'pci_event_regid_t'
	3 an optional pointer to a 'pci_err_t' variable which will hold the reason
	  for event registration failure

 When the event occurs, the registered handler function will be called with
 event specific data of type 'pci_event_data_t'. See the description of
 'pci_event_data_t' below for the fields applicable to each event type.

 In addition, the 'pci_event_type_e' that was associated with the 'pci_event_t'
 at registration time is provided so that the same handler can be registered for
 multiple event types if desired.

 The 'pci_event_t'used when registering is also provided. This will allow the
 handler function to obtain any optional event attributes established at event
 creation time. One obvious use would be to retrieve the event specific
 attribute associated with the event (see pci_event_attr_set_specific()) which
 could be a pointer to a data area specifically related to the event or set of
 events.

 Once a user has registered an event, the 'pci_event_t' can be destroyed if it
 is no longer required. In all cases, once a 'pci_event_t' is no longer of
 interest it should be destroyed with pci_event_destroy()

 Event Attributes
 ----------------
 Prior to calling pci_event_create(), the user may optionally specify certain
 attributes of the event. Each attribute which may be specified has a
 pci_event_attr_set_*() and pci_event_attr_get_*() API. Similar to POSIX, this
 mechanism provides for an easily extendible list of event attributes while
 preserving existing API's.
 An event attributes object can be initialized as an automatic or static variable
 or with the pci_event_attr_init() API

 Once a user has registered an event, the 'pci_event_attr_t' can be destroyed
 if it is no longer required. In all cases, once a 'pci_event_attr_t' is no
 longer of interest it should be destroyed with pci_event_attr_destroy()

 ** Important **
 Even if a 'pci_event_t' is destroyed after registration, the 'pci_event_t'
 passed to the handler function, as well as any of its attributes (obtainable
 with the pci_event_attr_get() API) will still be valid

 Event handling threads
 ----------------------
 By default, when the event registration API pci_event_reg() is called for the
 first time, an event handler thread is created on behalf of the process. The
 'pthread_t' for this thread can be obtained with the pci_event_get_thread_id()
 API. After the caller has unregistered all events, the event handler thread
 terminates.

 There are 4 API's which allow users complete control over the processing of
 events (see below for usage details)

	pci_event_attr_set_thread_attr()
	pci_event_attr_get_thread_attr()
	pci_event_attr_set_thread_id()
	pci_event_get_thread_id()

 These API's are optional and if not utilized, all event notifications will be
 handled by a single event handler thread created when the first event is
 successfully registered as previously described.
 The default event thread (named "pci_events") will be created with default
 thread attributes as per pthread_attr_init() however it will have the flag
 PTHREAD_CREATE_DETACHED set as per pthread_attr_setdetachstate(). This thread
 will terminate when the last event is unregistered.

 The user can change the name of an event thread with pthread_setname_np() and
 the 'pthread_t' returned from pci_event_get_thread_id()

 If the user wishes for the event handling thread to have non default thread
 attributes, the following sequence can be used

	pci_event_attr_t event_attr;
	pthread_attr_t thread_attr;

	pci_event_attr_init(&event_attr);
	pthread_attr_init(&thread_attr);

	set the desired thread attributes of the event handling thread
	pthread_attr_set*(&thread_attr, ...);
	pthread_attr_set*(&thread_attr, ...);
	pthread_attr_set*(&thread_attr, ...);

	pci_event_attr_set_thread_attr(&event_attr, &thread_attr);
	pci_event_create(event_type, event_attr);

 Assuming pci_event_create() is successful, the 'pci_event_t' returned can be
 registered for event notification. If registration is successful, an event
 handling thread will be created with the thread attributes established above.

 It is important to note that if another event is created with pci_event_create()
 using the same 'event_attr' above, then when that event is successfully
 registered, another separate event handling thread will be created for that
 event. This is because the 'pci_event_attr_t' being used when the event is
 created, has had pci_event_attr_set_thread_attr() called on it. If the user
 simply wishes to have subsequent events associated with the same event handling
 thread that was created when the first event was registered, then one of three
 options are available

	1. call pci_event_create() with the 'pci_event_attr_t' argument set to NULL
	2. call pci_event_create() with a 'pci_event_attr_t' argument which has not
	   had pci_event_attr_set_thread_attr() called on it or which has had the
	   'pthread_attr_t' canceled (see pci_event_attr_set_thread_attr())
	3. call pci_event_create() with a 'pci_event_attr_t' argument which has had
	   pci_event_attr_set_thread_id() called on it using the 'pthread_t'
	   returned from a successful call to pci_event_get_thread_id() using the
	   'pci_evthdl_t' returned from the registration of the first event

 Associating events with a specific event handling thread (assuming there is more
 than one) is accomplished similar to the above however all except the first
 event registered should use a separate 'pci_event_attr_t' which has had
 pci_event_attr_set_thread_id() called on it

 For example

	pci_event_attr_t event_attr_first;
	pci_event_attr_t event_attr_remaining;
	pthread_attr_t thread_attr;

	pci_event_attr_init(&event_attr_first);
	pci_event_attr_init(&event_attr_remaining);
	pthread_attr_init(&thread_attr);

	set the desired thread attributes of the first event handling thread
	pthread_attr_set*(&thread_attr, ...);
	pthread_attr_set*(&thread_attr, ...);
	pthread_attr_set*(&thread_attr, ...);

    associate the event thread attributes with 'event_attr_first' an create the event
	pci_event_attr_set_thread_attr(&event_attr_first, &thread_attr);
	pci_event_t event_1 = pci_event_create(event_type, event_attr_first);

	register the event, creating the event handling thread
	pci_evthdl_t evthdl_1 = pci_event_reg(..., event_1, ..., ...);
	pthread_t event_thread_1 = pci_event_get_thread_id(evthdl_1);

	associate 'event_attr_remaining' with 'event_thread_1'
	pci_event_attr_set_thread_id(&event_attr_remaining, event_thread_1);

	create and register all remaining events to be associated with 'event_thread_1'
	pci_event_t event_2 = pci_event_create(event_type, event_attr_remaining);
	pci_evthdl_t evthdl_2 = pci_event_reg(..., event_2, ..., ...);
	pci_event_t event_3 = pci_event_create(event_type, event_attr_remaining);
	pci_evthdl_t evthdl_3 = pci_event_reg(..., event_3, ..., ...);
	pci_event_t event_4 = pci_event_create(event_type, event_attr_remaining);
	pci_evthdl_t evthdl_4 = pci_event_reg(..., event_4, ..., ...);

	... etc ...

 This sequence can be repeated as many times as required in order to register
 the events of interest and have them associated with specific event handling
 threads


 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

/*
 ===============================================================================
 pci_event_type_e

 This type specifies the current set of supported events that can be passed to
 pci_event_create()

 For each event, the following event specific information is provided

	 Registration ID: this will specify the identifier to use to register for
					  event notification
	 Handler Data Field: when the 'pci_event_data_t' parameter is passed to the
						 handler function, this identifies which field of that
						 parameter to use to obtain the event specific data

*/
typedef enum
{
	/* LINK events, 0x100 - 0x1FF */
pci_event_type_e_LINK_first = 0x100,

	pci_event_type_e_LINK_STATE_CHANGE = pci_event_type_e_LINK_first,
	/*
	 * Event: pci_event_type_e_LINK_STATE_CHANGE
	 * Required Server Module: pci_server-event_handler.so
	 * Registration ID: BDF of the Root or Downstream Switch Port for the link
	 * Handler Data Field: link_event.link_state
	 */

	pci_event_type_e_LINK_BW_CHANGE,
	/*
	 * Event: pci_event_type_e_LINK_BW_CHANGE
	 * Required Server Module: pci_server-event_handler.so
	 * Registration ID: BDF of the Root or Downstream Switch Port for the link
	 * Handler Data Field: link_event.bw_change
	 */

pci_event_type_e_LINK_last = pci_event_type_e_LINK_first + 0xFF,

	/* SLOT events, 0x200 - 0x2FF */
pci_event_type_e_SLOT_first,

	/*
	 * Event: slot insertion/removal events
	 * Required Server Module: pci_server-event_handler.so and
	 *                         pci_server-buscfg-hotplug.so
	 * Registration ID: the chassis/slot of interest
	 * Handler Data Field: slot_event.bdf
	 *
	 * Note:
	 * Although the pci_server-buscfg-hotplug.so module is not strictly
	 * required in order to receive removal or insertion event notifications,
	 * it is required in order to restore the state of a removed device when it
	 * is re-inserted
	 */
	pci_event_type_e_SLOT_DEVICE_INSERT = pci_event_type_e_SLOT_first,
	pci_event_type_e_SLOT_DEVICE_REMOVE,

	/*
	 * Event: slot button press, power and mrl events
	 * Required Server Module: Not currently supported
	 * Registration ID: the chassis/slot of interest
	 * Handler Data Field: slot_event.cs
	 */
	pci_event_type_e_SLOT_ATTN_BUTTON_PRESS,
	pci_event_type_e_SLOT_POWER_FAULT,
	pci_event_type_e_SLOT_MRL_OPEN,
	pci_event_type_e_SLOT_MRL_CLOSED,

pci_event_type_e_SLOT_last = pci_event_type_e_SLOT_first + 0xFF,

	/* HW specific events, >= 0x10000 */
pci_event_type_e_HW_SPECIFIC_first = 0x10000,

	/*
	 * Event: HW specific events
	 * Required Server Module: Not currently supported
	 * Registration ID: BDF for the device of interest
	 * Handler Data Field: event_data
	 */

} pci_event_type_e;

/*
 ===============================================================================
 pci_event_link_e

 This type is used to identify the specific data for certain link events

*/
typedef enum
{
	pci_event_link_state_UP = (1u << 0),
	pci_event_link_state_DOWN = (pci_event_link_state_UP << 1),
	pci_event_link_bw_change_AUTONOMOUS = (pci_event_link_state_DOWN << 1),
	pci_event_link_bw_change_MANAGEMENT = (pci_event_link_bw_change_AUTONOMOUS << 1),

} pci_event_link_e;

/*
 ===============================================================================
 pci_event_data_t

 This type defines the different data associated with each event type described
 by 'pci_event_type_e' above

*/
#ifndef uintptr64_t
typedef uint64_t	uintptr64_t;
#endif
typedef union __attribute__((aligned((8))))
{
	uintptr64_t event_data;	/* untyped data, event specific interpretation */
	union
	{
		/*
		 * when a slot event occurs (for example, device removal or insertion),
		 * the 'bdf' for that device is provided to the registered handler. Note
		 * that the PCI_FUNC() of the 'bdf' argument passed to the registered
		 * handler of an insertion event will always be zero. The hander can use
		 * existing API's to determine whether or not the inserted device is a
		 * multi-function device and access the other functions accordingly
		 */
		pci_bdf_t bdf;
		pci_cs_t cs;
	} slot_event;
	union
	{
		/*
		 * 'link_state' will be either pci_event_link_state_UP or
		 * pci_event_link_state_DOWN
		 */
		pci_event_link_e link_state;

		/*
		 * 'bw_change' will be a mask containing the inclusive OR of
		 * pci_event_link_bw_change_AUTONOMOUS and
		 * pci_event_link_bw_change_MANAGEMENT (ie. both will be set if both
		 * events occur at the same time)
		 */
		pci_event_link_e bw_change;
	} link_event;

} pci_event_data_t;


/*
 ===============================================================================
 pci_event_t

 This type is returned from a successful call to pci_event_create() and is used
 to register for notification of the event

*/
typedef uintptr_t pci_event_t;

/*
 ===============================================================================
 pci_event_attr_t

 This type can be used to specify optional attributes associated with the
 'pci_event_t' returned from a successful pci_event_create() call.
 The 'pci_event_attr_t' can be statically initialized with PCI_EVENT_ATTR_INIT
 or it can be initialized with the pci_event_attr_init() call

 See also the pci_event_attr_set_*() and the pci_event_create() API's below

*/
typedef uintptr_t pci_event_attr_t;

extern const pci_event_attr_t * const pci_event_attr_initializer;
#define PCI_EVENT_ATTR_INIT		(*pci_event_attr_initializer)

/*
 ===============================================================================
 pci_evthdl_t

 this type represents a unique token received from the PCI server when a
 successful event registration call is made. It can be passed to other event
 API's including event de-registration

*/
typedef void *pci_evthdl_t;

/*
 ===============================================================================
 pci_event_create
 pci_event_destroy

 On success, pci_event_create() returns a 'pci_event_t' for the specified
 event type. An optional <event_attr> can be used to specify the attributes of
 the event or 0 can be provided if default attributes are desired

 The <event_attr> can be initialized with PCI_EVENT_ATTR_INIT or the
 pci_event_attr_init() API and the attributes apply only in the context of the
 current pci_event_create() call. That is, if any pci_event_attr_set_*() API's
 are called using <event_attr> AFTER a successful call to pci_event_create(),
 those attributes will not be associated with the returned 'pci_event_t' and
 therefore all attributes should be established prior to calling
 pci_event_create()

 When the caller is finished with the 'pci_event_t' it should be released by
 calling pci_event_destroy(). This can be done immediately after event
 registration if desired

 ** Important **
 Even if a 'pci_event_t' is destroyed after registration, the 'pci_event_t'
 passed to the handler function, as well as any of its attributes (obtainable
 with the pci_event_attr_get() API) will still be valid

 A value of 0 will be returned on any error

*/
pci_event_t pci_event_create(const pci_event_type_e event_type, const pci_event_attr_t event_attr);
pci_err_t pci_event_destroy(pci_event_t event);

/*
 ===============================================================================
 pci_event_reg
 pci_event_unreg
 pci_event_handler_f

 These functions will register and unregister respectively for notification of
 the event returned from a successful call to pci_event_create() when it occurs
 on the device identified by <regid>. The <regid> parameter is event type
 specific (see pci_event_type_e above).

 For example, when registering for notification of a slot event, the <regid>
 parameter would specify the slot of interest however when registering for a
 link event, the <regid> would be the BDF of the Root Port or Downstream Switch
 port for the link.

 The <handler> function (of type 'pci_event_handler_f') will be called with the
 'pci_event_type_e', event specific data pointed to by 'pci_event_data_t' as
 well as the 'pci_event_t' used during registration. The 'pci_event_t' can be
 used to obtain event specific information beyond just the event type and data

 ** Important **
 Even if a 'pci_event_t' is destroyed after registration, the 'pci_event_t'
 passed to the handler function, as well as any of its attributes (obtainable
 with the pci_event_attr_get() API) will still be valid

*/
typedef void (*pci_event_handler_f)(const pci_event_type_e event_type, const pci_event_data_t *event_data, pci_event_t event);

typedef union
{
	pci_bdf_t bdf;
	pci_cs_t cs;
	uint64_t pad;
} pci_event_regid_t __attribute__((aligned(8)/*, transparent_union*/));

pci_evthdl_t pci_event_reg(const pci_event_regid_t regid, const pci_event_t event, pci_event_handler_f handler, pci_err_t *err);
pci_err_t pci_event_unreg(pci_evthdl_t evthdl);


/*
 ===============================================================================
 pci_event_attr_init
 pci_event_attr_destroy

 Initialize and destroy respectively, a 'pci_event_attr_t' object.
 Initialization can also be accomplished with the PCI_EVENT_ATTR_INIT initializer

 A successful pci_event_attr_init() call will leave the 'pci_event_attr_t'
 object in the default state, similar to the use of PCI_EVENT_ATTR_INIT

 A 'pci_event_attr_t' object can be used multiple times and the attributes
 modified for each call to pci_event_create() however the attributes established
 at the time of successful event creation are the only ones associated with the
 'pci_event_t'

 When the caller is finished with the 'pci_event_attr_t' it should be released
 by calling pci_event_attr_destroy(). This can be done immediately after event
 creation if desired

 ** Important **
 Even if a 'pci_event_attr_t' is destroyed after event creation or registration,
 the 'pci_event_t' passed to the handler function, as well as any of its
 attributes (obtainable with the pci_event_attr_get() API) will still be valid

 See also pci_event_create() above

 NOTE:

 It is considered a programming error to pass an uninitialized or otherwise
 invalid 'pci_event_attr_t' object to either the pci_event_create() function or
 any of the pci_event_attr_set/get_*() functions

*/
pci_err_t pci_event_attr_init(pci_event_attr_t *event_attr);
pci_err_t pci_event_attr_destroy(pci_event_attr_t *event_attr);

/*
 ===============================================================================
 pci_event_attr_get

 Given an <event>, return a handle to the 'pci_event_attr_t' associated with it.
 If the <event_attr> parameter was 0 when the event was created with a successful
 call to pci_event_create(), the 'pci_event_attr_t' object returned by this
 function will be the default

 A value of 0 can be returned on any error

*/
pci_event_attr_t pci_event_attr_get(const pci_event_t event);

/*
 ===============================================================================
 pci_event_attr_set_pulse_priority
 pci_event_attr_get_pulse_priority

 Set/get the priority of the event pulse sent by the PCI server to the callers
 event handler thread

 A value of -1 will cause the pulse to be delivered at the priority of the
 calling process and is the default value

*/
pci_err_t pci_event_attr_set_pulse_priority(pci_event_attr_t *event_attr, const int_t priority);
pci_err_t pci_event_attr_get_pulse_priority(const pci_event_attr_t event_attr, int_t *priority);

/*
 ===============================================================================
 pci_event_attr_set_specific
 pci_event_attr_get_specific

 Set/get a user specific data area pointer for <event_attr>. The size of the
 area in bytes should be provided

 These functions can be used to allow an event specific handler access to caller
 specific data by using the pci_event_attr_get() and pci_event_attr_get_specific()
 API's

 An example is the 'pci_devhdl_t' obtained from a pci_device_attach() call

*/
pci_err_t pci_event_attr_set_specific(pci_event_attr_t *event_attr, void *specific, const size_t size);
pci_err_t pci_event_attr_get_specific(const pci_event_attr_t event_attr, void **specific);

/*
 ===============================================================================
 pci_event_attr_set_thread_attr
 pci_event_attr_get_thread_attr

 The set function allows the caller to indicate that a separate event handling
 thread should be spawned for any registered 'pci_event_t' associated with
 <event_attr> and that the spawned thread should be created with attributes as
 specified by <thread_attr>.

 The POSIX pthread_attr_*() functions can be used to establish <thread_attr>.
 The caller is responsible for destroying the 'pthread_attr_t' object when it
 has finished with it. This can be done after calling
 pci_event_attr_set_thread_attr() if desired

 Note that in order to set the scheduling parameters of a thread using the
 attributes object, the PTHREAD_EXPLICIT_SCHED flag should be set.
 See pthread_attr_setinheritsched() for details.
 Also, if you wish the thread to terminate itself after the last event using
 that thread unregisters, make sure to set the PTHREAD_CREATE_DETACHED flag.
 See pthread_attr_setdetachstate() for details

 The set function is mutually exclusive to pci_event_attr_set_thread_id() and if
 called on a 'pci_event_attr_t' object which has already been associated with
 another event handling thread with pci_event_attr_set_thread_id() or is already
 associated with a 'pthread_attr_t', will return PCI_ERR_EALREADY

 If <thread_attr> is NULL, any previously associated 'pthread_attr_t' will be
 dissociated from <event_attr>. This is effectively a cancellation of any
 previous pci_event_attr_set_thread_attr() call with a non-NULL <thread_attr>.
 Note however that the caller is still responsible for destroying the
 'pthread_attr_t'
 If NULL is provided and no association exists but pci_event_attr_set_thread_id()
 has been called on <event_attr>, PCI_ERR_EINVAL will be returned

 The get function allows the caller to retrieve the 'pthread_attr_t' currently
 associated with the 'pci_event_attr_t'. It will return PCI_ERR_ENOENT if no
 'pthread_attr_t' is associated with <event_attr>.

 On success, the 'pthread_attr_t' returned will be a copy of the 'pthread_attr_t'
 provided at the time of the last successful pci_event_attr_set_thread_attr()
 call. The caller is free to use the pthread_attr_set*() API's on the returned
 'pthread_attr_t' object however in order for the updated settings to take
 effect when the event is created, the caller must cancel the current association
 and establish a new one with the updated settings similar to the following
 procedure

	pthread_attr_t attr;
	pci_err_t r = pci_event_attr_get_thread_attr(event_attr, &attr);
	if (r == PCI_ERR_OK)
	{
		pthread_attr_set*(&attr, ...);
		pthread_attr_set*(&attr, ...);

		...etc...

        cancel existing association and set the new one
		r = pci_event_attr_set_thread_attr(&event_attr, NULL);
		if (r == PCI_ERR_OK)
		{
			r = pci_event_attr_set_thread_attr(&event_attr, &attr);
		}
	}

*/
pci_err_t pci_event_attr_set_thread_attr(pci_event_attr_t *event_attr, const pthread_attr_t *thread_attr);
pci_err_t pci_event_attr_get_thread_attr(const pci_event_attr_t event_attr, pthread_attr_t *thread_attr);

/*
 ===============================================================================
 pci_event_attr_set_thread_id

 This function allows the caller to specify the 'pthread_t' of an existing event
 handling thread that should be used to handle subsequent events which are
 created with <event_attr> and allows for complete control over which events are
 handled by which event handling threads.

 This function is mutually exclusive to pci_event_attr_set_thread_attr() and if
 called on a 'pci_event_attr_t' object which has already been associated with
 a 'pthread_attr_t' with pci_event_attr_set_thread_attr(), will return
 PCI_ERR_EALREADY

 If <event_attr> is not associated with a 'pthread_attr_t', this function may
 be called multiple times with the same or a different <tid> however the last
 <tid> specified before calling pci_event_create() with <event_attr> will be
 used.

 A <tid> value of -1 will cancel any association with an existing event thread

*/
pci_err_t pci_event_attr_set_thread_id(pci_event_attr_t *event_attr, pthread_t tid);

/*
 ===============================================================================
 pci_event_get_thread_id

 When a caller successfully registers an event for notification, that event is
 associated with and handled by an event handling thread. The thread it is
 associated with can be optionally controlled with the attribute setting API's
 described above and/or the POSIX pthread_*() API's.

 This function will provide the caller with the 'pthread_t' of the thread a
 particular event is associated with allowing complete control over things such
 as the scheduling attributes of the thread and to also allow additional events
 to be associated with an existing event handling thread by using the
 pci_event_attr_set_thread_id() API.

 Returns the 'pthread_t' for the thread assigned to handle the event identified
 by the 'pci_evthdl_t' returned from a successful event registration

 On any error, -1 will be returned

*/
pthread_t pci_event_get_thread_id(const pci_evthdl_t evthdl);



#endif	/* _PCI_EVENT_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/pci/public/pci/pci_event.h $ $Rev: 817491 $")
#endif
