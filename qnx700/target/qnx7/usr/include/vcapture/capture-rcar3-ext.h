/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
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

#ifndef INCL__VCAPTURE_RCAR3_EXT__H
#define INCL__VCAPTURE_RCAR3_EXT__H

#include <vcapture/capture.h>

/**************************************************************/
/* Note:                                                      */
/* If you add new properties to this file, please add them to */
/* lib/capture/props-validation.c for validation too.         */
/**************************************************************/

#define CAPTURE_PROPERTY_RCAR3_VIN_INPUT_IFACE_FORMAT	CAPTURE_PROPERTY('R','3','V','I')
	/* R/W		int			 Input interface format for VIN. */

enum rcar3_vin_input_iface_fmt {
	RCAR3_VIN_INF_BT656_8BIT = 0,
	RCAR3_VIN_INF_BT601_BT709_8BIT,
	RCAR3_VIN_INF_BT656_10_12BIT,
	RCAR3_VIN_INF_BT601_BT709_10_12BIT,
	RCAR3_VIN_INF_RAW_8BIT,
	RCAR3_VIN_INF_BT601_BT1358_16BIT,
	RCAR3_VIN_INF_BT601_BT709_24BIT,
	RCAR3_VIN_INF_BT601_BT709_18BIT,
	NUM_VIN_INFs
};

#define CAPTURE_PROPERTY_RCAR3_CLKEN_HSYNC_SEL	CAPTURE_PROPERTY('R','3','C','H')
	/* R/W		int			Clock enable Hysnc Select (0, or 1).
							0: clock enable singal input is internally used as the clock enable signal.
							1: Hsync signal input is internally used as the clock enable signal */

#define CAPTURE_PROPERTY_RCAR3_VSYNC_TOGGLE_MODE	CAPTURE_PROPERTY('R','3','T','M')
	/* R/W		int			VSYNC Field Toggle Mode for VINx (0: disable, 1: enable) */

#define CAPTURE_PROPERTY_RCAR3_VSYNC_TOGGLE_PERIOD	CAPTURE_PROPERTY('R','3','T','P')
	 /* R/W		int			VSYNC Field Toggle Mode Transition Period for VINx (0 .. 15).
	  *						It is necessary to enable VSYNC Field Toggle mode (VINx) for
	  *						the transition period to take effect */
#define CAPTURE_PROPERTY_RCAR3_HSYNC_TOGGLE_MODE	CAPTURE_PROPERTY('R','3','H','M')
	/* R/W		int			HSYNC Field Toggle Mode for VINx (0: disable, 1: enable) */

#define CAPTURE_PROPERTY_RCAR3_HSYNC_TOGGLE_PERIOD	CAPTURE_PROPERTY('R','3','H','P')
	/* R/W      int					HSYNC Field Toggle Mode Transition Period for VINx (0 .. 4095).
	  *						It is necessary to enable HSYNC Field Toggle mode (VINx) for
	  *						the transition period to take effect */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/wfd/rcarh3/caplib/public/vcapture/capture-rcar3-ext.h $ $Rev: 815026 $")
#endif
