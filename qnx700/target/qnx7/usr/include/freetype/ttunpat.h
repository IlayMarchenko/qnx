/***************************************************************************/
/*                                                                         */
/*  ttunpat.h                                                              */
/*                                                                         */
/*    Definitions for the unpatented TrueType hinting system.              */
/*    Obsolete, retained for backwards compatibility.                      */
/*                                                                         */
/*  Copyright 2003-2016 by                                                 */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  Written by Graham Asher <graham.asher@btinternet.com>                  */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


#ifndef TTUNPAT_H_
#define TTUNPAT_H_


#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef FREETYPE_H
#error "freetype.h of FreeType 1 has been loaded!"
#error "Please fix the directory search order for header files"
#error "so that freetype.h of FreeType 2 is found first."
#endif


FT_BEGIN_HEADER


 /***************************************************************************
  *
  * @constant:
  *   FT_PARAM_TAG_UNPATENTED_HINTING
  *
  * @description:
  *   Deprecated.
  *
  *   Previously: A constant used as the tag of an @FT_Parameter structure to
  *   indicate that unpatented methods only should be used by the TrueType
  *   bytecode interpreter for a typeface opened by @FT_Open_Face.
  *
  */
#define FT_PARAM_TAG_UNPATENTED_HINTING  FT_MAKE_TAG( 'u', 'n', 'p', 'a' )

  /* */


FT_END_HEADER


#endif /* TTUNPAT_H_ */


/* END */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/freetype/dist/freetype-2.6.5/include/freetype/ttunpat.h $ $Rev: 810671 $")
#endif
