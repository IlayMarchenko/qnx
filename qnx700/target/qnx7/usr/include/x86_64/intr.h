/*
 * $QNXLicenseC:
 * Copyright 2014, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * X86_64 interrupt classes
 *
 */
#ifndef __X86_64_INTR_H_INCLUDED
#define __X86_64_INTR_H_INCLUDED

/*
 * X86 specific interrupt classes
 */
#define	X86_64_INTR_CLASS_NMI			(0x8000U << 16)
#define X86_64_INTR_NMI					(X86_64_INTR_CLASS_NMI + 0)
#define X86_64_INTR_CLASS_MSI			(_NTO_INTR_CLASS_EXTERNAL + 256)
#define	X86_64_INTR_CLASS_APIC			(0x8001U << 16)
/*
 * the following APIC defined interrupt numbers do not apply to startup-apic.
 * The interrupt number for these devices should be obtained from the HWINFO
 * section of the syspage
*/
#define X86_64_INTR_APIC_TIMER			(X86_64_INTR_CLASS_APIC + 0)
#define X86_64_INTR_APIC_THERMAL		(X86_64_INTR_CLASS_APIC + 1)
#define X86_64_INTR_APIC_PERFORMANCE	(X86_64_INTR_CLASS_APIC + 2)
#define X86_64_INTR_APIC_LINT0			(X86_64_INTR_CLASS_APIC + 3)
#define X86_64_INTR_APIC_LINT1			(X86_64_INTR_CLASS_APIC + 4)
#define X86_64_INTR_APIC_ERROR			(X86_64_INTR_CLASS_APIC + 5)

/*
** Definitions for X86_64 GDT and IDT entries. Missing entries are invalid.
**
** 00 -               08 -                10 - LDT            18 - 
** 20 - Kernel CS(0)  28 - Kernel DS(0)   30 - Proc CS(1)     38 - Proc DS(1)
** 40 -               48 - User32 CS(3)   50 - User DS(3)     58 - User CS(3)
** 60 -               68 -                70 -                78 -             
** 80 -               88 -                90 -                98 -           
** A0 -               A8 -                B0 -                B8 -
** C0 -               C8 -                D0 -                D8 -
** E0 -               E8 -                F0 -                F8 -

**100 - TSSl cpu0    108 - TSSh cpu0     110 - FS cpu0       118 -
**120 - TSSl cpu1    128 - TSSh cpu1     130 - FS cpu1       118 -
**140 - TSSl cpu2    128 - TSSh cpu2     130 - FS cpu2       118 -
continue on with TSS/FS pattern for each CPU in the system...

*/

/*
** There is only one LDT for the system and it is overlaid ontop of the GDT.
*/
/*
** IDT - 48 entries plus whatever is used for hardware interrupts
** vec
** 00  000 - Div 0        008 - Debug       010 - NMI          018 - Brkpoint
** 04  020 - INTO         028 - BOUND       030 - ILL OPCODE   038 - Dev NA
** 08  040 - Double fault 048 - reserved    050 - Inv TSS      058 - Seg NP
** 0c  060 - Stack fault  068 - GP fault    070 - Page fault   078 - reserved
** 10  080 - FPU error    088 - Alignment   090 - Reserved     098 - Reserved
** 14  0A0 - Reserved     0A8 - Reserved    0B0 - Reserved     0B8 - Reserved
** 18  0C0 - Reserved     0C8 - Reserved    0D0 - Reserved     0D8 - Reserved
** 1c  0E0 - Reserved     0E8 - Reserved    0F0 - Reserved     0F8 - Reserved
** 20  100 - Kdebug trap  108 - Kdebug msg  110 -              118 -         
** 24  120 -              128 -             130 - SMP IPI      138 - SMP IPI
** 28  140 - Kernel call  148 -             150 -              158 -
** 2c  160 -              168 -             170 -              178 - APIC spurious
** 30  180 - Hardware vectors....
*/

#endif

/* __SRCVERSION("intr.h $Rev: 778261 $"); */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/startup/lib/public/x86_64/intr.h $ $Rev: 778261 $")
#endif
