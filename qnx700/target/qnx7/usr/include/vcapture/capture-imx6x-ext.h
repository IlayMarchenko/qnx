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

#ifndef INCL__VCAPTURE_IMX6X_EXT__H
#define INCL__VCAPTURE_IMX6X_EXT__H

#include <vcapture/capture.h>

/**************************************************************/
/* Note:                                                      */
/* If you add new properties to this file, please add them to */
/* lib/capture/props-validation.c for validation too.         */
/**************************************************************/

#define CAPTURE_PROPERTY_IMX6X_VSYNC_TYPE	CAPTURE_PROPERTY('M','X','V','T')
	/* R/W		int			VSYNC signal type (0: internal VSYNC, 1: external VSYNC, or -1 for default). */

#define CAPTURE_PROPERTY_IMX6X_SENSOR_CLK_MODE	CAPTURE_PROPERTY('M','X','S','C')
	/* R/W		int			Sensor timing/data mode protocol, see the enum below. */

enum imx6x_sensor_clk_mode {
	SENSOR_CLK_MODE_GATED_CLK,                      /* 0 */
	SENSOR_CLK_MODE_NONGATED_CLK,                   /* 1 */
	SENSOR_CLK_MODE_CCIR656_PROGRESSIVE,            /* 2 */
	SENSOR_CLK_MODE_CCIR656_INTERLACED,             /* 3 */
	SENSOR_CLK_MODE_CCIR1120_PROGRESSIVE_DDR,       /* 4 */
	SENSOR_CLK_MODE_CCIR1120_PROGRESSIVE_SDR,       /* 5 */
	SENSOR_CLK_MODE_CCIR1120_INTERLACED_DDR,        /* 6 */
	SENSOR_CLK_MODE_CCIR1120_INTERLACED_SDR,        /* 7 */
};

#define CAPTURE_PROPERTY_IMX6X_ADAPTIVE_DEI_MOTION_MODE CAPTURE_PROPERTY( 'M', 'X', 'V', 'M' )
	/* R/W		int			Motion mode of adaptive deinterlacer (VDI), see the enum below. */

enum imx6x_vdi_motion_mode {
	VDI_MOTION_MODE_LOW,				/* 0 */
	VDI_MOTION_MODE_MED,				/* 1 */
	VDI_MOTION_MODE_HIGH,				/* 2 */
};


#define CAPTURE_PROPERTY_IMX6X_MIPI_VCHANNEL_NUM	CAPTURE_PROPERTY('M','X','V','C')
	/* R/W		int			MIPI virtual channel number (0 ~ 3, or -1 for default).
	*					deprecated property..please use CAPTURE_PROPERTY_CSI2_VCHANNEL_NUM instead. */

#define CAPTURE_PROPERTY_IMX6X_IDMAC_CHANNEL_NUM	CAPTURE_PROPERTY('M','X','P','C')
	/* R/W		int			physical idmac channel number (0 ~ 3 to indicate user-specified IDMAC channel): this is only for multi-capture.
							--- otherwise soc would use default for backward compatibility. */

#define CAPTURE_PROPERTY_IMX6X_FIELD_POSITION		CAPTURE_PROPERTY('M','X','F','P')
	/* R/W		int			the position of the fields, if there are two fields in a buffer.
	 *					when sensor clk is configured to CCIR INTERLACED mode, CSI captures two fields in one buffer.
	 *					0: the field stored in upper part of the buffer is TOP field, with the other one being BOTTOM field;
	 *					1: the field stored in upper part of the buffer is BOTTOM field, with the other one being TOP field. */

#define CAPTURE_PROPERTY_IMX6X_DDR_CLOCK_MHZ		CAPTURE_PROPERTY('M','X','C','K')
	/* R/W		int32_t			The dual-data rate clock (MHz) of the external CSI2 transmitter.
	*					deprecated property..please use CAPTURE_PROPERTY_CSI2_DDR_CLOCK_MHZ instead. */


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/wfd/imx6x/caplib/public/vcapture/capture-imx6x-ext.h $ $Rev: 815026 $")
#endif
