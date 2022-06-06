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

/* This file is an extension of trace.h for the QUIP class */

#ifndef __TRACE_QUIP_H_INCLUDED
#define __TRACE_QUIP_H_INCLUDED

#ifndef __TRACE_H_INCLUDED
#include <sys/trace.h>
#endif


/* TraceEvent() - external QUIP events */
// MMR functions have two events each: entry and exit
// the following MMR events are inserted from the service (high level) layer
// media playback
#define _NTO_TRACE_QUIP_MMR_PLAY               (0x00000000)
// media stop
#define _NTO_TRACE_QUIP_MMR_STOP               (0x00000002)
// media seek
#define _NTO_TRACE_QUIP_MMR_SEEK               (0x00000004)
// media change speed and/or direction of play (trickplay)
#define _NTO_TRACE_QUIP_MMR_SPEEDSET           (0x00000006)
// each context is able to play a stream of content independent of other contexts and has
//   an associate set of inputs, outputs, and parameters
// media: open a new handle to an existing context
#define _NTO_TRACE_QUIP_MMR_CONTEXTOPEN        (0x00000008)
// media: close handle to context
#define _NTO_TRACE_QUIP_MMR_CONTEXTCLOSE       (0x0000000A)
// media: create a new context and open context handle
#define _NTO_TRACE_QUIP_MMR_CONTEXTCREATE      (0x0000000C)
// media: destroy the context and close the handle
#define _NTO_TRACE_QUIP_MMR_CONTEXTDESTROY     (0x0000000E)
// media: set parameters associated with the context (verbosity, timeouts, security, etc)
#define _NTO_TRACE_QUIP_MMR_CONTEXTPARAMETERS  (0x00000010)
// media: send a command to the context
#define _NTO_TRACE_QUIP_MMR_COMMANDSEND        (0x00000012)
// media: attach an input file, device or playlist to context
#define _NTO_TRACE_QUIP_MMR_INPUTATTACH        (0x00000014)
// media: detach the input from the context and stop playback if necessary
#define _NTO_TRACE_QUIP_MMR_INPUTDETACH        (0x00000016)
// media: set parameters associated with the input of the context
#define _NTO_TRACE_QUIP_MMR_INPUTPARAMETERS    (0x00000018)
// media: sets a playlist
#define _NTO_TRACE_QUIP_MMR_LISTCHANGE         (0x0000001A)
// media: attach an output to the context and return an output ID
#define _NTO_TRACE_QUIP_MMR_OUTPUTATTACH       (0x0000001C)
// media: detach the output from the context
#define _NTO_TRACE_QUIP_MMR_OUTPUTDETACH       (0x0000001E)
// media: set parameters for the output device
#define _NTO_TRACE_QUIP_MMR_OUTPUTPARAMETERS   (0x00000020)
// the following events are inserted from the router plugin (low level) layer
#define _NTO_TRACE_QUIP_MMR_MMF_CREATE         (0x00000022)
#define _NTO_TRACE_QUIP_MMR_MMF_DESTROY        (0x00000024)
#define _NTO_TRACE_QUIP_MMR_MMF_SEEK           (0x00000026)
// the following bit patterns are ORed with the above MMR events to define entry and exit events for each API function
  #define QUIP_MMR_ENTRY                         (0x00000000)
  #define QUIP_MMR_EXIT                          (0x00000001)
// screen frame post events
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_0    (0x00000028)
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_1    (0x00000029)
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_2    (0x0000002A)
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_3    (0x0000002B)
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_4    (0x0000002C)
#define _NTO_TRACE_QUIP_SCREEN_FRAME_POST_5    (0x0000002D)
// difference between scheduled and actual post time in microseconds
#define _NTO_TRACE_QUIP_SCREEN_ALARM_ACTUAL_DIFF (0x0000002E)
// count of dropped frames
#define _NTO_TRACE_QUIP_SCREEN_FRAME_DROP      (0x0000002F)
// mmedia frame event
#define _NTO_TRACE_QUIP_MMEDIA_FRAME           (0x00000030)
#define _NTO_TRACE_QUIP_LAST        (_NTO_TRACE_QUIP_MMEDIA_FRAME)


#endif  // __TRACE_QUIP_H_INCLUDED

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/system/public/sys/trace_quip.h $ $Rev: 772917 $")
#endif
