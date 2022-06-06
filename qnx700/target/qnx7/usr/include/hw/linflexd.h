/*
*
* Copyright (c) 2016, QNX Software Systems.
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
*/

/* LINFlexD Registers */
#define LINFLEXD_LINCR1			0x0	/* Control Register */
	#define LINFLEXD_LINCR1_CCD		(1 << 15)	/* Checksum Calculation disable */
	#define LINFLEXD_LINCR1_CFD		(1 << 14)	/* Checksum field disable */
	#define LINFLEXD_LINCR1_LASE		(1 << 13)	/* LIN Autosynchronization Enable */
	#define LINFLEXD_LINCR1_AUTOWU		(1 << 12)	/* Auto Wakeup */
	#define LINFLEXD_LINCR1_MBL		(1 << 8)	/* Master Break Length */
	#define LINFLEXD_LINCR1_BF		(1 << 7)	/* By-pass filter */
	#define LINFLEXD_LINCR1_LBKM		(1 << 5)	/* Loop Back mode */
	#define LINFLEXD_LINCR1_MME		(1 << 4)	/* Master mode enable */
	#define LINFLEXD_LINCR1_SSBL		(1 << 3)	/* Slave Mode Sync Break Length */
	#define LINFLEXD_LINCR1_RBLM		(1 << 2)	/* Receiver Buffer Locked mode */
	#define LINFLEXD_LINCR1_SLEEP		(1 << 1)	/* Sleep Mode Request */
	#define LINFLEXD_LINCR1_INIT		(1 << 0)	/* Initialization Mode Request */
#define LINFLEXD_LINIER			0x4
	// more interrupt enable bits to fill in
	#define LINFLEXD_LINIER_TOIE		(1 << 3)	/* Timeout Interrupt Enable */
	#define LINFLEXD_LINIER_DRIE		(1 << 2)	/* Data Reception complete Interrupt enable */
	#define LINFLEXD_LINIER_DTIE		(1 << 1)	/* Data Transmitted Interrupt enable */
	#define LINFLEXD_LINIER_HRIE		(1 << 0)	/* Header Received Interrupt */

#define LINFLEXD_LINSR			0x8
#define LINFLEXD_LINESR			0xC
	#define LINFLEXD_LINESR_SZF		(1 << 15)	/* Stuck at Zero Flag */
	#define LINFLEXD_LINESR_OCF		(1 << 14)	/* Output Compare Flag */
	#define LINFLEXD_LINESR_BEF		(1 << 13)	/* Bit Error Flag */
	#define LINFLEXD_LINESR_CEF		(1 << 12)	/* Checksum Error Flag */
	#define LINFLEXD_LINESR_SFEF		(1 << 11)	/* Sync Field Error Flag */
	#define LINFLEXD_LINESR_SDEF		(1 << 10)	/* Sync Delimiter Error Flag */
	#define LINFLEXD_LINESR_IDPEF		(1 << 9)	/* ID Parity Error Flag */
	#define LINFLEXD_LINESR_FEF		(1 << 8)	/* Framing Error Flag */
	#define LINFLEXD_LINESR_BOF		(1 << 7)	/* Buffer Overrun Flag */

#define LINFLEXD_UARTCR			0x10	/* UART Mode Control Register */
	#define LINFLEXD_UARTCR_MIS		(1 << 31)	/* Monitor Idle State */
	#define LINFLEXD_UARTCR_CSP		(1 << 28)	/* Configurable Sample Point (i) */
	#define LINFLEXD_UARTCR_OSR		(1 << 24)	/* Over Sampling Rate */
	#define LINFLEXD_UARTCR_ROSE		(1 << 23)	/* Reduced Over Sampling Enable */
	#define LINFLEXD_UARTCR_NEF		(1 << 20)	/* Number of expected frame */
	#define LINFLEXD_UARTCR_DTU_PCETX	(1 << 19)	/* Disable Timeout in UART mode */
	#define LINFLEXD_UARTCR_SBUR		(1 << 17)	/* Stop bits in UART reception mode */
	#define LINFLEXD_UARTCR_SBUR_MASK	(0x3 << 17)
	#define LINFLEXD_UARTCR_TDFL_TFC	(1 << 13)	/* Transmitter Data Field Length/TX FIFO Counter */
	#define LINFLEXD_UARTCR_RDFL_RFC	(1 << 10)	/* Reception Data Field Length /RX FIFO Counter */
	#define LINFLEXD_UARTCR_RFBM		(1 << 9)	/* RFBM Rx Fifo/Buffer mode */
	#define LINFLEXD_UARTCR_TFBM		(1 << 8)	/* Tx Fifo/Buffer mode */
	#define LINFLEXD_UARTCR_WL1		(1 << 7)	/* Word Length in UART mode */
	#define LINFLEXD_UARTCR_PC1		(1 << 6)	/* Parity Control */
	#define LINFLEXD_UARTCR_RXEN		(1 << 5)	/* Receiver Enable */
	#define LINFLEXD_UARTCR_TXEN		(1 << 4)	/* Transmitter Enable */
	#define LINFLEXD_UARTCR_PC0		(1 << 3)	/* Parity Control */
	#define LINFLEXD_UARTCR_PCE		(1 << 2)	/* Parity Control Enable */
	#define LINFLEXD_UARTCR_WL0		(1 << 1)	/* Word Length in UART mode */
	#define LINFLEXD_UARTCR_UART		(1 << 0)	/* UART Mode */
#define LINFLEXD_UARTSR			0x14	/* UART Mode Status Register */
	#define	LINFLEXD_UARTSR_SZF		(1 << 15)	/* Stuck at Zero flag */
	#define	LINFLEXD_UARTSR_OCF		(1 << 14)	/* Output Compare Flag */
	#define	LINFLEXD_UARTSR_PE		(1 << 10)	/* Parity Error flag */
	#define	LINFLEXD_UARTSR_RMB		(1 << 9)	/* Release Message Buffer */
	#define	LINFLEXD_UARTSR_FEF		(1 << 8)	/* Framing Error flag */
	#define	LINFLEXD_UARTSR_BOF		(1 << 7)	/* FIFO/Buffer overrun flag */
	#define	LINFLEXD_UARTSR_RDI		(1 << 6)	/* Receiver Data Input signal */
	#define	LINFLEXD_UARTSR_WUF		(1 << 5)	/* Wakeup flag */
	#define	LINFLEXD_UARTSR_RFNE		(1 << 4)	/* Receive FIFO Not Empty */
	#define	LINFLEXD_UARTSR_TO		(1 << 3)	/* Timeout */
	#define	LINFLEXD_UARTSR_DRFRFE		(1 << 2)	/* Data Reception Completed Flag / Rx FIFO Empty Flag */
	#define	LINFLEXD_UARTSR_DTFTFF		(1 << 1)	/* Data Transmission Completed Flag / TX FIFO Full Flag */
	#define	LINFLEXD_UARTSR_NF		(1 << 0)	/* Noise flag */
#define LINFLEXD_LINTCSR		0x18
#define LINFLEXD_LINOCR			0x1C
#define LINFLEXD_LINTOCR		0x20
#define LINFLEXD_LINFBRR		0x24
#define LINFLEXD_LINIBRR		0x28
#define LINFLEXD_LINCFR			0x2C
#define LINFLEXD_LINCR2			0x30
#define LINFLEXD_BIDR			0x34
#define LINFLEXD_BDRL			0x38
#define LINFLEXD_BDRM			0x3C
#define LINFLEXD_IFER			0x40
#define LINFLEXD_IFMI			0x44
#define LINFLEXD_IFMR			0x48
#define LINFLEXD_IFCR0			0x4C
#define LINFLEXD_IFCR1			0x50
#define LINFLEXD_IFCR2			0x54
#define LINFLEXD_IFCR3			0x58
#define LINFLEXD_IFCR4			0x5C
#define LINFLEXD_IFCR5			0x60
#define LINFLEXD_IFCR6			0x64
#define LINFLEXD_IFCR7			0x68
#define LINFLEXD_IFCR8			0x6C
#define LINFLEXD_IFCR9			0x70
#define LINFLEXD_IFCR10			0x74
#define LINFLEXD_IFCR11			0x78
#define LINFLEXD_IFCR12			0x7C
#define LINFLEXD_IFCR13			0x80
#define LINFLEXD_IFCR14			0x84
#define LINFLEXD_IFCR15			0x88
#define LINFLEXD_GCR			0x8C
#define LINFLEXD_UARTPTO		0x90
#define LINFLEXD_UARTCTO		0x94
#define LINFLEXD_DMATXE			0x98
#define LINFLEXD_DMARXE			0x9C





#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/devc/public/hw/linflexd.h $ $Rev: 823226 $")
#endif
