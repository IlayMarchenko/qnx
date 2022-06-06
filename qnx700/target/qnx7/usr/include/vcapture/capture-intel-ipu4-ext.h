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

#ifndef INCL__VCAPTURE_INTEL_IPU4_EXT_H
#define INCL__VCAPTURE_INTEL_IPU4_EXT__H

#include <vcapture/capture.h>

/**************************************************************/
/* Note:                                                      */
/* If you add new properties to this file, please add them to */
/* lib/capture/props-validation.c for validation too.         */
/**************************************************************/

#define CAPTURE_PROPERTY_IPU4_CSI2_PORT_CONFIG      CAPTURE_PROPERTY( 'I', 'C', 'P', 'C' )
    /* R/W      [4] uint32_t    Array of 4 values that define the number of CSI2 lanes
     *                          to use for all 4 ports on the board.  This is written to
     *                          the port_config register on Apollo Lake.  Acceptable values
     *                          are from 0 to 4 where 0 indicates that this port will not
     *                          be used in this configuration. */

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/capture/public/public/vcapture/capture-intel-ipu4-ext.h $ $Rev: 815786 $")
#endif
