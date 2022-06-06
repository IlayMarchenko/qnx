/*
 * $QNXtpLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _UVM_UVM_EXTERN_H_
#define _UVM_UVM_EXTERN_H_

#include <uvm/uvm_param.h>

struct proc;

struct vmspace {
	struct proc	*vm_proc;
	int		vm_flags;
};
#define VM_USERSPACE    0x00000001
#define VM_SYSSPACE     0x00000002
/* Hints to copyin / copyout */
#define VM_OUTFORCE	0x00000004
#define VM_NOCTXT	0x00000008

#define VM_MSGLENCHECK  0x00000010
#define VM_USERMBUF	0x00000020

#define VM_SPACEMSK	0x00000003
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/sys/uvm/uvm_extern.h $ $Rev: 770515 $")
#endif
