// Copyright (C) 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
**********************************************************************
*   Copyright (C) 1999-2006, International Business Machines
*   Corporation and others.  All Rights Reserved.
**********************************************************************
*   file name:  umisc.h
*   encoding:   US-ASCII
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 1999oct15
*   created by: Markus W. Scherer
*/

#ifndef UMISC_H
#define UMISC_H

#include "unicode/utypes.h"

/**
 * \file
 * \brief  C API:misc definitions 
 *
 *  This file contains miscellaneous definitions for the C APIs. 
 */

U_CDECL_BEGIN

/** A struct representing a range of text containing a specific field 
 *  @stable ICU 2.0
 */
typedef struct UFieldPosition {
  /**
   * The field 
   * @stable ICU 2.0
   */
  int32_t field;
  /**
   * The start of the text range containing field 
   * @stable ICU 2.0
   */
  int32_t beginIndex;
  /** 
   * The limit of the text range containing field 
   * @stable ICU 2.0
   */
  int32_t endIndex;
} UFieldPosition;

#if !UCONFIG_NO_SERVICE
/**
 * Opaque type returned by registerInstance, registerFactory and unregister for service registration.
 * @stable ICU 2.6
 */
typedef const void* URegistryKey;
#endif

U_CDECL_END

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/icu/icu-58.1/source/common/unicode/umisc.h $ $Rev: 817488 $")
#endif
