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

#ifndef INCL__VCAPTURE_ADV_EXT__H
#define INCL__VCAPTURE_ADV_EXT__H

#include <vcapture/capture.h>

/**************************************************************/
/* Note:                                                      */
/* If you add new properties to this file, please add them to */
/* lib/capture/props-validation.c for validation too.         */
/**************************************************************/

#define CAPTURE_PROPERTY_ADV_SRC_TYPE		CAPTURE_PROPERTY( 'A', 'S', 'T', 'P' )
	/* R/W		uint32_t		The input type of ADV decoder (0 ~ 3).
	 *					0: CVBS (single-ended, if type 3 is supported).
	 *					1: S-Video/YC
	 *					2: PCbCr.
	 *					3: differential CVBS (not supported by all chips). */
enum adv_src_type {
	CAPTURE_ADV_SRC_SINGLE_ENDED_CVBS = 0,
	CAPTURE_ADV_SRC_YC,
	CAPTURE_ADV_SRC_PCBPR,
	CAPTURE_ADV_SRC_DIFFERENTIAL_CVBS,
	CAPTURE_ADV_SRC_TYPE_NUM
};

#define CAPTURE_PROPERTY_ADV_LOCK_STATUS	CAPTURE_PROPERTY( 'A', 'L', 'C', 'K' )
	/* R		uint32_t		Lock indicator.
	 *					0: unlocked.
	 *					1: locked. */

#define CAPTURE_PROPERTY_ADV_FSCLOCK_STATUS	CAPTURE_PROPERTY( 'A', 'F', 'S', 'C' )
	/* R		uint32_t		Fsc lock indicator.
	 *					0: unlocked.
	 *					1: locked. */

#define CAPTURE_PROPERTY_ADV_OUTPUT_FREQ	CAPTURE_PROPERTY( 'A', 'O', 'P', 'F' )
	/* R		uint32_t		Indicate whether 50Hz or 60Hz is present at output.
	 *					0: 60Hz.
	 *					1: 50Hz. */

#define CAPTURE_PROPERTY_ADV_WSS_STATUS		CAPTURE_PROPERTY( 'A', 'W', 'S', 'S' )
	/* R		uint32_t		Indicate whether Wide Screen Signaling is available.
	 *					0: unavailable.
	 *					1: available. */

#define CAPTURE_PROPERTY_DECODER_I2C_SERVER	CAPTURE_PROPERTY( 'A', 'I', 'C', 'S' )
	/* R/W		uint32_t		i2c servers as below */
enum {
	CAPTURE_I2C_SERVER_QNX = 0,
	CAPTURE_I2C_SERVER_NONQNX = 1,
	CAPTURE_I2C_SERVERS_NUM
};

#define CAPTURE_PROPERTY_ADV_RED_BALANCE	CAPTURE_PROPERTY( 'A', 'D', 'R', 'D' )
	/* R/W		uint32_t		Sets/reads red channel balance:
	 *					0x00: -312 mV offset applied to the red channel.
	 *					0x80: 0 mV offset applied to the red channel (default). 3200K.
	 *					0xFF: +312 mV offset applied to the red channel */

#define CAPTURE_PROPERTY_ADV_BLUE_BALANCE	CAPTURE_PROPERTY( 'A', 'D', 'B', 'L' )
	/* R/W		uint32_t		Sets/reads blue channel balance:
	 *					0x00: -312 mV offset applied to the blue channel.
	 *					0x80: 0 mV offset applied to the blue channel (default). 3200K.
	 *					0xFF: +312 mV offset applied to the blue channel */

enum {
	CAPTURE_ADV_DRIVE_STRENGTH_UNKNOWN = 0, /* Can be returned on read operation only, can't be set.                           */
	CAPTURE_ADV_DRIVE_STRENGTH_1X = 1,      /* Not recommended by ADI. But can greatly reduces EM noise and power consumption. */
	CAPTURE_ADV_DRIVE_STRENGTH_2X = 2,      /* Power on default value.                                                         */
	CAPTURE_ADV_DRIVE_STRENGTH_3X = 3,      /* Recommended if ADV718x is soldered on high distance from SOC.                   */
	CAPTURE_ADV_DRIVE_STRENGTH_4X = 4,      /* Greatly increases crosstalk and EM noise, use with caution.                     */
};

#define CAPTURE_PROPERTY_ADV_DRIVE_STRENGTH	CAPTURE_PROPERTY( 'A', 'D', 'D', 'S' )
	/* R/W		uint32_t		Sets/reads digital signals driver strength. It sets drive
	 *					strength for sync, clock and data signals simultaneously.
	 *					CAPTURE_ADV_DRIVE_STRENGTH_UNKNOWN can be only returned on
	 *					read if drive strength for different signals has different
	 *					values. Usually it must be set by board library only */

/*
 * The following norms (video standards) can be set via CAPTURE_PROPERTY_NORM, with
 * the case of the characters being ignored:
 * "AUTO_PAL_BGHID_NTSC_J_SECAM"
 * "AUTO_PAL_BGHID_NTSC_M_SECAM"
 * "AUTO_PAL_N_NTSC_J_SECAM"
 * "AUTO_PAL_N_NTSC_M_SECAM"
 * "NTSC_J"
 * "NTSC_M"
 * "PAL_60"
 * "NTSC_4_43"
 * "PAL_BGHID"
 * "PAL_N"
 * "PAL_M_NO_PEDESTAL"
 * "PAL_M"
 * "PAL_COMBINATION_N"
 * "PAL_COMBINATION_N_PEDESTAL"
 * "SECAM"
 * "SECAM_PEDESTAL"
 *
 * The available norms (video standards), which can be get via CAPTURE_PROPERTY_CURRENT_NORM,
 * are listed as below:
 * "NTSC_M_J"
 * "NTSC_4_43"
 * "PAL_M"
 * "PAL_60"
 * "PAL_B_G_H_I_D"
 * "SECAM"
 * "PAL_COMBINATION_N"
 * "SECAM_525"
 * */

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/capture/public/public/vcapture/capture-adv-ext.h $ $Rev: 801492 $")
#endif
