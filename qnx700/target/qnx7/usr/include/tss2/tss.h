/********************************************************************************/
/*										*/
/*			   TSS Primary API 					*/
/*			     Written by Ken Goldman				*/
/*		       IBM Thomas J. Watson Research Center			*/
/*	      $Id:tss.h 656 2016-06-28 16:49:29Z kgoldman $			*/
/*										*/
/* (c) Copyright IBM Corporation 2015.						*/
/*										*/
/* All rights reserved.								*/
/* 										*/
/* Redistribution and use in source and binary forms, with or without		*/
/* modification, are permitted provided that the following conditions are	*/
/* met:										*/
/* 										*/
/* Redistributions of source code must retain the above copyright notice,	*/
/* this list of conditions and the following disclaimer.			*/
/* 										*/
/* Redistributions in binary form must reproduce the above copyright		*/
/* notice, this list of conditions and the following disclaimer in the		*/
/* documentation and/or other materials provided with the distribution.		*/
/* 										*/
/* Neither the names of the IBM Corporation nor the names of its		*/
/* contributors may be used to endorse or promote products derived from		*/
/* this software without specific prior written permission.			*/
/* 										*/
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS		*/
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT		*/
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	*/
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT		*/
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,	*/
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT		*/
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,	*/
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY	*/
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT		*/
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE	*/
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.		*/
/********************************************************************************/

#ifndef TSS_H
#define TSS_H

#ifndef TPM_TSS
#define TPM_TSS
#endif

#include <tss2/TPM_Types.h>
#include <tss2/Parameters.h>

/* include this as a convenience to applications */
#include <tss2/tsserror.h>
#include <tss2/tssprint.h>

typedef struct TSS_CONTEXT TSS_CONTEXT; 
   
#ifdef __cplusplus
extern "C" {
#endif

    /* extra parameters as required */

    typedef struct {
	const char 		*bindPassword;
	TPM2B_DIGEST 	salt;
    } StartAuthSession_Extra;
	
    typedef union {
	StartAuthSession_Extra 	StartAuthSession;
    } EXTRA_PARAMETERS;

    LIB_EXPORT
    TPM_RC TSS_Create(TSS_CONTEXT **tssContext);

    LIB_EXPORT
    TPM_RC TSS_Delete(TSS_CONTEXT *tssContext);

    LIB_EXPORT
    TPM_RC TSS_Execute(TSS_CONTEXT *tssContext,
		       RESPONSE_PARAMETERS *out,	
		       COMMAND_PARAMETERS *in,
		       EXTRA_PARAMETERS *extra,
		       TPM_CC commandCode,
		       ...);

#define TPM_TRACE_LEVEL		1
#define TPM_DATA_DIR		2
#define TPM_COMMAND_PORT	3
#define TPM_PLATFORM_PORT	4
#define TPM_SERVER_NAME		5
#define TPM_INTERFACE_TYPE	6
#define TPM_DEVICE		7
#define TPM_ENCRYPT_SESSIONS	8
#define TPM_SERVER_TYPE		9

    LIB_EXPORT
    TPM_RC TSS_SetProperty(TSS_CONTEXT *tssContext,
			   int property,
			   const char *value);

#ifdef __cplusplus
}
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/tss/ibmtss/public/tss2/tss.h $ $Rev: 820787 $")
#endif
