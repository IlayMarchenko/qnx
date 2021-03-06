/********************************************************************************/
/*										*/
/*			TSS and Application Utilities				*/
/*			     Written by Ken Goldman				*/
/*		       IBM Thomas J. Watson Research Center			*/
/*	      $Id: tssutils.h 874 2016-12-19 15:23:05Z kgoldman $		*/
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

/* This is a semi-public header. The API is subject to change.

   It is useful rapid application development, and as sample code.  It is risky for production code.

*/

#ifndef TSSUTILS_H
#define TSSUTILS_H

#include <stdio.h>

#ifndef TPM_TSS
#define TPM_TSS
#endif

#include <tss2/TPM_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef TPM_RC (*UnmarshalFunction_t)(void *target, uint8_t **buffer, int32_t *size);
    typedef TPM_RC (*MarshalFunction_t)(void *source, uint16_t *written, uint8_t **buffer, int32_t *size);

    LIB_EXPORT
    TPM_RC TSS_Malloc(unsigned char **buffer, uint32_t size);
    LIB_EXPORT
    TPM_RC TSS_Realloc(unsigned char **buffer, uint32_t size);

    LIB_EXPORT
    TPM_RC TSS_Structure_Marshal(uint8_t		**buffer,
				 uint16_t		*written,
				 void 		*structure,
				 MarshalFunction_t 	marshalFunction);

    LIB_EXPORT 
    TPM_RC TSS_TPM2B_Copy(TPM2B *target, TPM2B *source, uint16_t targetSize);
    
    LIB_EXPORT 
    TPM_RC TSS_TPM2B_Append(TPM2B *target, TPM2B *source, uint16_t targetSize);
    
    LIB_EXPORT 
    TPM_RC TSS_TPM2B_Create(TPM2B *target, uint8_t *buffer, uint16_t size, uint16_t targetSize);
    
    LIB_EXPORT 
    TPM_RC TSS_TPM2B_CreateUint32(TPM2B *target, uint32_t source, uint16_t targetSize);
    
    LIB_EXPORT 
    TPM_RC TSS_TPM2B_StringCopy(TPM2B *target, const char *source, uint16_t targetSize);
    
    LIB_EXPORT 
    BOOL TSS_TPM2B_Compare(TPM2B *expect, TPM2B *actual);
    
#ifdef __cplusplus
}
#endif

#ifndef TPM_TSS_NOFILE
#include <tss2/tssfile.h>
#endif

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/tss/ibmtss/public/tss2/tssutils.h $ $Rev: 820787 $")
#endif
