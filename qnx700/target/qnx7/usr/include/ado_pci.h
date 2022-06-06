/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
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





/*
 *      ado_pci.c
 *	    - Manifests for audio pci bus access.
 */

#ifndef _ADO_PCI_H_INCLUDED_
#define _ADO_PCI_H_INCLUDED_


/***** structures ***********/
struct ado_pci
{
	int_t         index;
	pci_devhdl_t  handle;				/* handle returned by pci_attach_device() call */
	pci_vid_t     vendor;
	pci_did_t     device;
	pci_ssid_t    subsystem;
	pci_ssvid_t   subsysvendor;
	pci_revid_t   revision;
	pci_irq_t     irq;
	uint64_t      iobase[7];
	uint64_t      iolen[7];
	uint64_t      membase[7];
	uint64_t      memlen[7];
	pci_cap_t     cap_msix;
	pci_cap_t     cap_msi;
	uint32_t      spare[32];
};

/*** function prototypes ****/

/* pci.c */
struct ado_pci *ado_pci_device ( uint32_t vendor , uint32_t device , char *args);
void ado_pci_release ( struct ado_pci *pci );
pci_err_t ado_pci_map_DMA_address (struct ado_pci *pci, uint64_t phyaddr, uint64_t size, pci_ba_t *xlate);

#endif /* _ADO_PCI_H_INCLUDED_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/audio/public/include/ado_pci.h $ $Rev: 808169 $")
#endif
