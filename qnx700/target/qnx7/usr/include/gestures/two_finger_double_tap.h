/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software.   Free development licenses are
 * available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/**
 * @file two_finger_double_tap.h
 *
 * @brief Definition of the double tap gesture
 *
 * The two_finger_double_tap.h header file provides data type definitions and functions
 * for the two-finger double tap gesture. Your application must provide the callback
 * function to handle changes in gesture state.
 *
 */
 
#include "gestures/types.h"

#ifndef TWO_FINGER_DOUBLE_TAP_H_
#define TWO_FINGER_DOUBLE_TAP_H_

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Two-finger double tap gesture parameters
 *
 * This structure represents the parameters for the two-finger double tap gesture.
 */
typedef struct {
	unsigned max_displacement; /**< The maximum distance the fingers can move before
	                                the two-finger double tap gesture fails. */
	unsigned max_hold_ms;      /**< The maximum time the fingers can remain touching
	                                the screen before the two-finger double tap gesture fails. */
	unsigned max_delay_ms;     /**< The time between the first release and the second touch. */
} two_finger_double_tap_params_t;

/** @brief States for the two-finger double tap gesture
 *
 * This enumeration defines additional states the two-finger double tap gesture can transition between.
 */
typedef enum {
	TFDT_STATE_INIT = 0,       /**< The initial state of the two-finger double tap gesture. */
	TFDT_STATE_FIRST_TOUCH,    /**< The state of the two-finger double tap gesture after the first touch was detected. */
	TFDT_STATE_FIRST_RELEASE,  /**< The state of the two-finger double tap gesture after the first release was detected. */
	TFDT_STATE_SECOND_TOUCH,   /**< The state of the two-finger double tap gesture after the second touch was detected. */
	TFDT_STATE_SECOND_RELEASE  /**< The state of the two-finger double tap gesture after the second release was detected. */
} two_finger_double_tap_state_e;

/** @brief The two-finger double tap gesture data type
 *
 * This structure carries data about the two-finger double tap gesture.
 */
typedef struct {
	gesture_base_t base;             /**< The gesture base data structure. */
	two_finger_double_tap_params_t params;      /**< The two-finger double tap parameters. */
	gesture_coords_t first_touch[2];    /**< The coordinates of the first touch. */
	gesture_coords_t first_release[2];  /**< The coordinates of the first release. */
	gesture_coords_t second_touch[2];   /**< The coordinates of the second touch. */
	gesture_coords_t second_release[2]; /**< The coordinates of the second release. */
	gesture_coords_t centroid;      /**< The coordintes of the midpoint between the two touches. */
	gesture_coords_t last_centroid; /**< The coordintes of the midpoint between the previous two touches. */
	two_finger_double_tap_state_e dt_state;     /**< The intermediate state of the two-finger double tap. */
	int fail_timer;                  /**< The ID of the timer for this gesture. */
	unsigned down_count;             /**< The number of fingers that are simultaneously in contact with the touch device. */
} gesture_two_finger_double_tap_t;

/**
 * @brief Allocate and initialize the two-finger double tap gesture structure
 *
 * This function allocates a new two-finger double tap gesture data structure, initializes it with the specified
 * parameters and callback function, and adds it to the specified gesture set.
 *
 * @param params The two-finger double tap gesture parameters.
 * @param callback The function to invoke when the two-finger double tap gesture changes state.
 * @param set The gesture set to add this two-finger double tap gesture to.
 *
 * @return An initialized two-finger double tap gesture.
 */
gesture_two_finger_double_tap_t* two_finger_double_tap_gesture_alloc(two_finger_double_tap_params_t* params, gesture_callback_f callback, struct gestures_set* set);

/**
 * @brief Initialize the two-finger double tap parameters
 *
 * This function initializes the two-finger double tap parameters to default values.
 *
 * @param params The two-finger double tap gesture parameter structure to initialize.
 *
 * @return Nothing.
 */
void two_finger_double_tap_gesture_default_params(two_finger_double_tap_params_t* params);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* TWO_FINGER_DOUBLE_TAP_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/gestures/public/gestures/two_finger_double_tap.h $ $Rev: 812267 $")
#endif
