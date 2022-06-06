#ifndef _PCI_H_
#define _PCI_H_
/*
 * $QNXLicenseC:
 * Copyright (c) 2012, 2016 QNX Software Systems. All Rights Reserved.
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

#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>


/*
 ===============================================================================
 pci_verbosity

 This variable is used to control PCI API logging. The higher its value, the
 more system log entries will be recorded

*/
extern uint_t pci_verbosity;

/*
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 Environment Variables

 The following section defines the names of all the environment variables
 utilized by the PCI server and its associated modules. All names and paths
 should be fully qualified unless otherwise specified

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

/*
 PCI_ENVVAR_PCI_HW_MODULE [required]

 This define specifies the name of the environment variable which contains the
 name of the board specific HW dependent module. This variable is required to be
 present in the environment of the PCI server and all driver processes
*/
#define PCI_ENVVAR_PCI_HW_MODULE	"PCI_HW_MODULE"

/*
 PCI_ENVVAR_PCI_SLOG_MODULE [optional]

 This define specifies the name of the environment variable which contains the
 name of the system logging module. This variable is optional and is only
 required if system logging facilities are required. This environment variable
 need only be present in the environment of processes for which logging is
 required however if logging in a driver it is generally useful to want logging
 in the PCI server as well
*/
#define PCI_ENVVAR_PCI_SLOG_MODULE	"PCI_SLOG_MODULE"

/*
 PCI_ENVVAR_CAP_MODULE_DIR [optional]

 This define specifies the name of the environment variable which contains the
 name of the directory in which the capabilities modules reside. If unspecified,
 the default location is used (see PCI_CAP_MODULE_DIR_DEFAULT). Although this
 environment variable can be individually set for different processes, mixing
 and matching modules is not generally desirable.
 This environment variable can be used for example to allow a new driver to make
 use of a newer version of modules while the remaining components continue to
 use an older version. Of course the opposite is also true
*/
#define PCI_ENVVAR_CAP_MODULE_DIR	"PCI_CAP_MODULE_DIR"
#define PCI_CAP_MODULE_DIR_DEFAULT	"/lib/dll/pci"

/*
 PCI_ENVVAR_HW_CONFIG [optional]

 This define specifies the name of the environment variable which contains board
 specific configuration information such as PCI Interrupt Pin assignment and/or
 IRQ mapping, slot and chassis numbering information, etc. It may contain other
 HW module specific information in the future as well

 Example configuration files can be found in /etc/system/config/pci/
*/
#define PCI_ENVVAR_HW_CONFIG		"PCI_HW_CONFIG_FILE"

/*
 PCI_ENVVAR_VERBOSITY [optional]

 This define specifies the name of the environment variable which contains the
 base verbosity level for PCI server related logging. This optional environment
 variable allows the verbosity level to be specified without having to recompile
 any code which utilizes the PCI server library and modules. It is particularly
 relevant to the backwards compatibility module to obtain slogger entries for
 driver software which has not yet been ported to the new PCI server API's
 and/or which doesn't currently manipulate the 'pci_verbosity' variable under
 command line control.

 The value given to this environment variable should be an unsigned integer and
 specifies the base verbosity level (which by default is 0). For programs
 which do not manipulate the 'pci_verbosity' variable (like driver software
 which uses the pci_bkwd_compat.so module) the value behaves the same as
 incrementing the verbosity parameter by the value of the PCI_BASE_VERBOSITY
 environment variable. For programs which do manipulate the 'pci_verbosity'
 variable, this base level changes the default from 0 to the specified value and
 any command line options to increase 'pci_verbosity' will increase it from the
 base value set in the environment variable
*/
#define PCI_ENVVAR_VERBOSITY		"PCI_BASE_VERBOSITY"

/*
 PCI_ENVVAR_PCI_DBG_MODULE [optional]

 This define specifies the name of the environment variable which contains the
 name of the debug module. This variable is optional and is only required if
 debugging facilities are required. Note that this environment variable must be
 present in the environment of all processes to be debugged
*/
#define PCI_ENVVAR_PCI_DBG_MODULE	"PCI_DEBUG_MODULE"

/*
 PCI_ENVVAR_PCI_SERVER_BUSCFG_MODULE [optional]

 This define specifies the name of the environment variable which contains the
 name of the optional bus configuration module for the PCI server. This variable
 is optional and is only required if the PCI server will configure the PCI bus
 (ie. assign secondary/subordinate bus numbers to bridges, (re)calculate address
 spaces requirements and assign them to devices by updating BAR registers, etc).
 If the PCI server will only be enumerating an existing configuration, a bus
 configuration module will not be required and the environment variable will be
 ignored.

 If a configuration will be performed, this environment variable is still
 optional and the generic module identified by PCI_SERVER_BUSCFG_MODULE_DEFAULT
 will be used by default. The PCI_ENVVAR_PCI_SERVER_BUSCFG_MODULE environment
 variable allows for alternative and/or board specific configuration modules to
 be utilized
*/
#define PCI_ENVVAR_PCI_SERVER_BUSCFG_MODULE	"PCI_SERVER_BUSCFG_MODULE"
#define PCI_SERVER_BUSCFG_MODULE_DEFAULT	"/lib/dll/pci/pci_server-buscfg-generic.so"

/*
 PCI_ENVVAR_PCI_MODULE_BLACKLIST [optional]

 This define specifies the name of the environment variable which contains the
 list of modules which are black listed and will not be used. The blacklist is
 checked at the point that a module load is attempted. Once a module has been
 successfully loaded, the blacklist will no longer be consulted for that module
 so it is important that the blacklist is created before a module is loaded for
 the first time.

 While generally applicable to any PCI module, its main purpose is to control
 the use of capability modules without modifying the driver software itself.
 For example, a driver written to make use of MSI-X and MSI's (preferentially
 in that order) could be started with the MSI-X capability module blacklisted
 so that it will defer to using MSI's without changing software or requiring a
 command line option to the driver.

 Because this is an environment variable, this control can be provided on a per
 driver basis however note that when this environment variable is specified for
 the PCI server, the effect is more global in nature. Any blacklisted capability
 modules in the server environment will actually prevent their use for all
 driver software regardless of the setting of the variable in that drivers
 environment. Drivers will still be able to read the device capabilities but
 will not be able to enable them and hence not use them

 If multiple modules will be blacklisted they can be separated with a colon (:)

 Modules can be specified as a simple name or with a leading '/'. If a simple
 name is used, the module must exist in the "/lib/dll/pci/" directory. If the
 first character of the name is '/', the name must specify the full path to the
 module. Only an exact pathname match will prevent the loading of a module. This
 should be kept in mind if the capability module directory has been altered
 with the PCI_CAP_MODULE_DIR environment variable

 NOTE

 Because a vid/did specific capability module is always checked for before a
 generic capability module, if you are using a vid/did specific capability
 module and wish to prevent the use of that capability, both the vid/did
 specific and the generic modules should be blacklisted
*/
#define PCI_ENVVAR_PCI_MODULE_BLACKLIST		"PCI_MODULE_BLACKLIST"

/*
 PCI_ENVVAR_PCI_SERVER_NODE_NAME [optional]

 This define specifies the name of the environment variable which contains the
 node name used to communicate with the PCI server. This variable is optional
 and is only required if the PCI server will be started with a different node
 name (with either the '-n' server command line option or the SERVER_NODE_NAME
 parameter in the server configuration file specified with the --config server
 command line option, the '-n' option taking precedence)

 It is not generally required or encouraged to change this parameter

*/
#define PCI_ENVVAR_PCI_SERVER_NODE_NAME		"PCI_SERVER_NODE_NAME"
#define PCI_SERVER_NODE_NAME_DEFAULT		"/dev/pci"


/*
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 Types and Macros

 The following section defines types and macros used in driver software
 development

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifndef bool_t
typedef bool	bool_t;
#endif	/* bool_t */

#ifndef int_t
typedef int		int_t;
#endif	/* int_t */

#ifndef NELEMENTS
#define NELEMENTS(x)	((uint_t)(sizeof((x)) / sizeof((x)[0])))
#endif	/* NELEMENTS */

/*
 ===============================================================================
 pci_cs_t

 Base type which encodes a Chassis/Slot number which uniquely identifies which
 slot in which chassis a device resides.

 The encoding is as follows

 	cccs ssss ssss ssss

 Encoding/Decoding of the 'pci_cs_t' is accomplished with the PCI_CS*() macros

 There is a maximum of 32 slots per chassis as defined by the Slot
 Identification capability however there are 13 bits for slot numbers to
 accommodate the size of the 'physical slot number' field in the slot
 capabilities register of PCIe root ports. Choosing an 16 bit data type for
 'pci_cs_t' permits up to 8 chassis' (7 expansion chassis').

 Slot numbers start at 1. If PCI_SLOT() == 0, it means that the device is not
 in a slot.

 As far a chassis numbers go, even if there is no chassis based bridges in the
 system, a chassis number of 0 will exist. That is, a board with PCI devices on
 it (perhaps including slots) will logically reside in a chassis 0

 ===============================================================================
*/
typedef uint16_t		pci_cs_t;

#define PCI_CHASSIS(_cs_)		((((pci_cs_t)(_cs_)) >> 13) & 0x7u)
#define PCI_SLOT(_cs_)			((((pci_cs_t)(_cs_)) >> 0) & 0x1FFFu)
#define PCI_CS(_c_, _s_) \
		((pci_cs_t) \
			( \
				(((_c_) & 0x7u) << 13) | \
				(((_s_) & 0x1FFFu) << 0) \
			) \
		)

#define PCI_CS_NONE				((pci_cs_t)-1)		/* non-existent or illegal chassis/slot */
#define PCI_CS_MAX_CHASSIS		(PCI_CHASSIS((pci_cs_t)-1) + 1)	/* max chassis */
#define PCI_CS_MAX_SLOTS		(PCI_SLOT((pci_cs_t)-1) + 1)		/* max slots */

/*
 ===============================================================================
 pci_bdf_t

 Base type which encodes a Bus/Device/Function which uniquely identifies a PCI
 device node. The encoding is as follows

 	xxxx xxxx xxxx xxxa bbbb bbbb dddd dfff

 Encoding/Decoding of the 'pci_bdf_t' is accomplished with the PCI_*() macros

 ARI (Alternate Routing ID Interpretation) encoding is as follows

 	xxxx xxxx xxxx xxxa bbbb bbbb ffff ffff

 There is no 'device' field. It is implied to be 0
 
 Note that bit 16 is used to determine whether or not the BDF encoding should be
 interpreted as in ARI format or not

 ===============================================================================
*/
typedef uint32_t		pci_bdf_t;

/* macros to obtain the Bus, Device and Function numbers from a BDF */
#define PCI_FUNC(_bdf_)		(PCI_IS_ARI((_bdf_)) ? _PCI_ARI_FUNC((_bdf_)) : _PCI_BDF_FUNC((_bdf_)))
#define PCI_DEV(_bdf_)		(PCI_IS_ARI((_bdf_)) ? _PCI_ARI_DEV((_bdf_)) : _PCI_BDF_DEV((_bdf_)))
#define PCI_BUS(_bdf_)		(PCI_IS_ARI((_bdf_)) ? _PCI_ARI_BUS((_bdf_)) : _PCI_BDF_BUS((_bdf_)))

#define PCI_BDF_NONE		((pci_bdf_t)-1)		/* non-existent or illegal device */

/* macros for the maximum number of Buses, Devices and Functions */
#define PCI_MAX_BUSES			256					/* fixed for both BDF and ARI encoding */
#define PCI_BDF_MAX_DEVS		(_PCI_BDF_DEV((pci_bdf_t)-1) + 1)	/* max devices */
#define PCI_BDF_MAX_FUNCS		(_PCI_BDF_FUNC((pci_bdf_t)-1) + 1)	/* max functions */
#define PCI_ARI_MAX_DEVS		(_PCI_ARI_DEV((pci_bdf_t)-1) + 1)	/* max ARI devices */
#define PCI_ARI_MAX_FUNCS		(_PCI_ARI_FUNC((pci_bdf_t)-1) + 1)	/* max ARI functions */

/* macros to encode both a regular and an ARI BDF */
#define PCI_BDF(_b_, _d_, _f_) \
		((pci_bdf_t) \
			( \
				(((_b_) & 0xFFu) << 8) | \
				(((_d_) & 0x1Fu) << 3) | \
				(((_f_) & 0x7u) << 0) \
			) \
		)
#define PCI_BDF_ARI(_b_, _f_) \
		((pci_bdf_t) \
			( \
				(((_b_) & 0xFFu) << 8) | \
				(((_f_) & 0xFFu) << 0) | \
				(1u << _PCI_ARI_BIT) \
			) \
		)

/* macro to test whether a BDF is an ARI encoding */
#define PCI_IS_ARI(_bdf_)	(((_bdf_) & (1u << _PCI_ARI_BIT)) != 0)

/* the following are internal and are only intended to be utilized by the previous macros */
#define _PCI_ARI_BIT			16
#define _PCI_BDF_FUNC(_bdf_)	((((pci_bdf_t)(_bdf_)) >> 0) & 0x7u)
#define _PCI_BDF_DEV(_bdf_)		((((pci_bdf_t)(_bdf_)) >> 3) & 0x1Fu)
#define _PCI_BDF_BUS(_bdf_)		((((pci_bdf_t)(_bdf_)) >> 8) & 0xFFu)
#define _PCI_ARI_FUNC(_bdf_)	((((pci_bdf_t)(_bdf_)) >> 0) & 0xFFu)
#define _PCI_ARI_DEV(_bdf_)		((pci_bdf_t)0)
#define _PCI_ARI_BUS(_bdf_)		((((pci_bdf_t)(_bdf_)) >> 8) & 0xFFu)


/*
 ===============================================================================
 pci_devhdl_t

 this type represents a unique token received from the PCI server when a
 successful pci_device_attach() call is made
 ===============================================================================
*/
typedef void *		pci_devhdl_t;

/*
 ===============================================================================
 pci_attachFlags_t

 When attaching to the PCI server, the following flags can be specified.
 The first 2 are mutually exclusive and at least one selection must be made. By
 default, pci_attachFlags_e_SHARED is assumed. Any remaining flags can be
 optionally OR'd in
 ===============================================================================
*/
typedef enum
{
	/*=== mutually exclusive flags ===*/

	/*
	 * pci_attachFlags_e_SHARED
	 *
	 * read/write any except no access to address space or IRQ information and no
	 * ability to enable capabilities unless pci_attachFlags_e_OWNER is included
	 */
	pci_attachFlags_e_SHARED = 0,
	/*
	 * read any, write owner (pci_attachFlags_e_OWNER implied). Successful
	 * attachment with this flag set prevents any other attaches from occurring
	 */
	pci_attachFlags_e_EXCLUSIVE = 1,

	/*=== bitwise inclusive flags ===*/

	/*
	 * pci_attachFlags_e_OWNER
	 *
	 * implied for pci_attachFlags_e_EXCLUSIVE. Permits access to the address space
	 * and IRQ information as well as the ability to enable device capabilities.
	 * There can be only one owner unless pci_attachFlags_e_MULTI is set on the very
	 * first attach which includes pci_attachFlags_e_OWNER
	 */
	pci_attachFlags_e_OWNER = (1u << 1),
	/*
	 * pci_attachFlags_e_MULTI
	 *
	 * if this flag is set on the first attach with pci_attachFlags_e_OWNER set, then subsequent
	 * attaches will be permitted with the pci_attachFlags_e_OWNER and pci_attachFlags_e_MULTI
	 * flags set. If this flag is not set on first attach with pci_attachFlags_e_OWNER set, then
	 * subsequent attaches with pci_attachFlags_e_OWNER set will be rejected regardless of the
	 * inclusion of pci_attachFlags_e_MULTI. That is, all multiply owned attachers MUST include
	 * both the pci_attachFlags_e_OWNER and pci_attachFlags_e_MULTI flags.
	 *
	 * It will be considered an error to include pci_attachFlags_e_MULTI with pci_attachFlags_e_EXCLUSIVE
	 * or without pci_attachFlags_e_OWNER
	 */
	pci_attachFlags_e_MULTI = (1u << 2),


	/*=== some predefined combinations ===*/

	pci_attachFlags_OWNER = (pci_attachFlags_e_SHARED | pci_attachFlags_e_OWNER),
	pci_attachFlags_MULTI_OWNER = (pci_attachFlags_e_SHARED | pci_attachFlags_e_OWNER | pci_attachFlags_e_MULTI),
	pci_attachFlags_EXCLUSIVE_OWNER = pci_attachFlags_e_EXCLUSIVE | pci_attachFlags_e_OWNER,

	pci_attachFlags_DEFAULT = pci_attachFlags_OWNER,

} pci_attachFlags_t;

/*
 ===============================================================================
 pci_err_t

 PCI specific error codes
 ===============================================================================
*/
typedef enum
{
	PCI_ERR_OK = EOK,
	PCI_ERR_EINVAL = EINVAL,
	PCI_ERR_EALREADY = EALREADY,
	PCI_ERR_ENODEV = ENODEV,
	PCI_ERR_ENOENT = ENOENT,
	PCI_ERR_EIO = EIO,
	PCI_ERR_ENOTSUP = ENOTSUP,
	PCI_ERR_ENOMEM = ENOMEM,
	PCI_ERR_EEXIST = EEXIST,
	PCI_ERR_EAGAIN = EAGAIN,

pci_err_t_first = 400,					/* higher than highest value in errno.h */

	PCI_ERR_REG_UNIMPLEMENTED = pci_err_t_first,
	PCI_ERR_LOCK_FAILURE,

	PCI_ERR_NOT_OWNER,
	PCI_ERR_ATTACH_LIMIT,
	PCI_ERR_ATTACH_EXCLUSIVE,
	PCI_ERR_ATTACH_SHARED,
	PCI_ERR_ATTACH_OWNED,

	PCI_ERR_IRQ_NOT_AVAIL,
	PCI_ERR_IRQ_CFG,

	PCI_ERR_ASPACE_NOT_AVAIL,
	PCI_ERR_ASPACE_CFG,
	PCI_ERR_ASPACE_INVALID,

	PCI_ERR_CAP_ENOTSUP,
	PCI_ERR_CAP_NIRQ,
	PCI_ERR_MSI_ENABLED,
	PCI_ERR_MSIX_ENABLED,

	PCI_ERR_MODULE_INIT,
	PCI_ERR_MODULE_SYM,
	PCI_ERR_MOD_COMPAT,
	PCI_ERR_MOD_API_COMPAT,
	PCI_ERR_NO_MODULE,
	PCI_ERR_MODULE_NOT_ENABLED,
	PCI_ERR_MODULE_BLACKLISTED,

	PCI_ERR_SLOG,
	PCI_ERR_SLOG_VERBOSITY,
	PCI_ERR_SLOG_TYPE,

	PCI_ERR_MMAP_DEV,
	PCI_ERR_MMAP_MEM,

	PCI_ERR_DEV_NOT_AVAIL,

	PCI_ERR_PCIe_LINK_RETRAIN,
	PCI_ERR_PCIe_LINK_NOT_ACTIVE,

	PCI_ERR_CFG_ACCESS,

pci_err_t_last,

} pci_err_t;

/*
 ===============================================================================
 pci_reqType_t

 Functions that take a 'pci_req_t' parameter can specify one of the following
 request types.

 pci_reqType_e_MANDATORY	- the request must be satisfied with requested
 	 	 	 	 	 	 	  constraints or the request fails
 pci_reqType_e_ADVISORY		- every attempt should be made to meet the request
 	 	 	 	 	  	  	  constraints, however if that is not possible the
 	 	 	 	 	  	  	  call will not fail
 pci_reqType_e_UNSPECIFIED	- the request constraints are not specified. The PCI
 	 	 	 	 	 	 	  server is free to choose any request constraints
 ===============================================================================
*/
typedef enum
{
	pci_reqType_e_MANDATORY = 100,
	pci_reqType_e_ADVISORY,
	pci_reqType_e_UNSPECIFIED,

} pci_reqType_t;

/*
 ===============================================================================
 Types which represent common Type 0/1 PCI Configuration space register values
 ===============================================================================
*/
typedef uint16_t	pci_vid_t;
typedef uint16_t	pci_did_t;
typedef uint16_t	pci_cmd_t;
typedef uint16_t	pci_stat_t;
typedef uint32_t	pci_ccode_t;	/* class/subclass (see below) */
typedef uint8_t		pci_revid_t;
typedef uint8_t		pci_hdrType_t;
typedef uint8_t		pci_capid_t;
typedef uint8_t		pci_latency_t;	/* latency timer */
typedef uint8_t		pci_clsize_t;	/* cache line size */

/*
 'pci_ccode_t' contains 3 bytes as defined in the PCI spec and as shown below

  MSb                                        LSb
  	  0000 0000 CCCC CCCC cccc cccc rrrr rrrr

  C - represents the base class
  c - represents the sub class
  r - represents a register level programming interface

  The following macros can be used to encode/decode the specific fields
*/
#define PCI_CCODE_CLASS(_cc_)		((((pci_ccode_t)(_cc_)) >> 16) & 0xFFu)
#define PCI_CCODE_SUBCLASS(_cc_)	((((pci_ccode_t)(_cc_)) >> 8) & 0xFFu)
#define PCI_CCODE_REG_IF(_cc_)		((((pci_ccode_t)(_cc_)) >> 0) & 0xFFu)
#define PCI_CCODE(_C_, _c_, _r_) \
		((pci_ccode_t) \
			( \
				(((_C_) & 0xFFu) << 16) | \
				(((_c_) & 0xFFu) << 8) | \
				(((_r_) & 0xFFu) << 0) \
			) \
		)

/* the following are wildcard values for pci_device_find() */
#define PCI_VID_ANY		((pci_vid_t)0xFFFFu)
#define PCI_DID_ANY		((pci_did_t)0xFFFFu)
#define PCI_CCODE_ANY	PCI_CCODE(0xFFu, PCI_CCODE_SUBCLASS_ANY, PCI_CCODE_REG_IF_ANY)

/*
 * and in addition, pci_device_find() allows the subclass and register interface
 * values to be independently wildcarded to widen the search. The following
 * values can be used independently or together for the subclass and register
 * interface respectively when constructing a classcode to search on
 *
 * ex.	PCI_CCODE(<base class>, PCI_CCODE_SUBCLASS_ANY, PCI_CCODE_REG_IF_ANY)
 * 		PCI_CCODE(<base class>, <subclass>, PCI_CCODE_REG_IF_ANY)
*/
#define PCI_CCODE_SUBCLASS_ANY	0xFFu
#define PCI_CCODE_REG_IF_ANY	0xFFu

/*
 ===============================================================================
 Types which represent Type 0 specific PCI Configuration space register values
 ===============================================================================
*/
typedef uint16_t	pci_ssid_t;
typedef uint16_t	pci_ssvid_t;

/*
 ===============================================================================
 Types which represent Type 1 specific PCI Configuration space register values
 ===============================================================================
*/
typedef uint8_t		pci_busnum_t;	/* primary/secondary/subordinate bus numbers */
typedef uint16_t	pci_bctrl_t;	/* bridge control register */


/*
 ===============================================================================
 pci_ba_val_t

 Type which can hold a 64 bit base address value.

 ===============================================================================
*/
typedef uint64_t	pci_ba_val_t;

/*
 ===============================================================================
 pci_asType_e
 pci_asAttr_e

 Address space types and attributes

 ===============================================================================
*/
typedef enum
{
	/* pci_ba_t.type must be one of the following ... */
	pci_asType_e_NONE = 0,
	pci_asType_e_MEM,			/* memory */
	pci_asType_e_IO,			/* I/O */

} pci_asType_e;

typedef enum
{
	pci_asAttr_e_NONE = 0,
	pci_asAttr_e_ALIGN_MEM_MIN = 4,		/* memory has a minimum 16 byte alignment */
	pci_asAttr_e_ALIGN_IO_MIN = 2,		/* I/O has a minimum 4 byte alignment */

	/* pci_ba_t.attr can be a bitwise inclusive OR of the following flags */
	pci_asAttr_e_ALIGN = (0x3Fu << 0),
	/* The alignment value represents a 2^val shift. That is, a value of 5
	 * represents an alignment requirement of 2^5 = 32 bytes. The maximum
	 * alignment is 2^63 */

	/* a 2bit field occupying bits 15 and 14, encode the address space size as
	 * 16, 32, or 64 bit. In general 16 << ((attr & pci_asAttr_e_BIT_MASK) >> 14) */
	pci_asAttr_e_BIT_MASK = (0x3u << 14),
	pci_asAttr_e_16BIT = ((0 << 14) & pci_asAttr_e_BIT_MASK),
	pci_asAttr_e_32BIT = ((1 << 14) & pci_asAttr_e_BIT_MASK),
	pci_asAttr_e_64BIT = ((2 << 14) & pci_asAttr_e_BIT_MASK),
	pci_asAttr_e_128BIT = ((3 << 14) & pci_asAttr_e_BIT_MASK),	/* not used */

	pci_asAttr_e_PREFETCH = (1u << 16),
	pci_asAttr_e_spare = (1u << 17),
	pci_asAttr_e_CONTIG = (1u << 18),
	pci_asAttr_e_EXPANSION_ROM = (1u << 19),
	pci_asAttr_e_ENABLED = (1u << 20),	/* applicable to expansion ROM */

	pci_asAttr_e_SHARED = (1u << 21),	/* otherwise reserved (applicable to slot aspace reservations) */

	/* the following attributes are used when calling pci_device_map_as() */
	pci_asAttr_e_INBOUND = (1u << 22),	/* transfers from PCI space to CPU space */
	pci_asAttr_e_OUTBOUND = (1u << 23),	/* transfers from CPU space to PCI space */

} pci_asAttr_e;

/*
 ===============================================================================
 pci_ba_t

 Type which holds the relevant information required by driver software in order
 to access a devices memory mapped registers. One of more of these types are
 included in the value returned from a successful pci_device_read_ba() call
 ===============================================================================
*/
typedef struct
{
	pci_ba_val_t addr;
	uint64_t size;
	pci_asType_e type;
	pci_asAttr_e attr;
	int_t bar_num;
} pci_ba_t;


/*
 ===============================================================================
 pci_irq_t

 Type which holds the IRQ returned from pci_device_read_irq() and can be used in
 a call to InterruptAttach()/Interrupt_Detach()
 Negative values of 'pci_irq_t' indicate an invalid IRQ
 ===============================================================================
*/
typedef int_t		pci_irq_t;

/*
 ===============================================================================
 pci_version_t

 ===============================================================================
*/
typedef struct __attribute__((packed,aligned(4)))
{
	uint16_t major;
	uint16_t minor;
} pci_version_t;

/*
 ===============================================================================
 pci_cap_t

 A (semi) opaque pointer to a specific PCI capabilities structure
 ===============================================================================
*/
typedef struct __attribute__((packed,aligned(8)))
{
	pci_version_t api_version;
	uint32_t reserved;
	void *api_p;
} *pci_cap_t;

/*
 ===============================================================================
 pci_resetType_e

 A Reset type < pci_resetType_e_BUS is considered to be no reset (no-op)
 A Reset type > pci_resetType_e_FUNCTION is considered to be a HW specific reset

 The behaviour of HW specific resets, if supported, are defined by the HW
 dependent module. Refer to the release notes or 'use' information in the HW
 dependent module applicable to your platform for details
 ===============================================================================
*/
typedef enum
{
	pci_resetType_e_BUS = 1,		/* secondary bus reset */
	pci_resetType_e_FUNCTION,	/* function level reset */

} pci_resetType_e;

/*
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

 PCI server API's

 Together with pci/pci_ccode.h, pci/pci_id.h and pci/pci_event.h, the following
 represent the complete set of public API's implemented by the PCI server
 library. Individual capability modules may optionally provide their own set of
 API's. Those are defined in the corresponding cap*.h file. In addition, other
 modules which extend base functionality may also provide their own header file

 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

/*=========================== Miscellaneous API's ============================*/
const char * const pci_strerror(pci_err_t err);		/* thread safe */

/*================= device attach/detach and find API's ======================*/
pci_devhdl_t pci_device_attach(pci_bdf_t bdf, pci_attachFlags_t flags, pci_err_t *err);
pci_err_t pci_device_detach(pci_devhdl_t hdl);
pci_bdf_t pci_device_find(const uint_t idx, const pci_vid_t vid, const pci_did_t did, const pci_ccode_t classcode);

/* pci_bdf() returns the 'pci_bdf_t' associated with <hdl> or PCI_BDF_NONE if
 * the device does not exist or <hdl> is otherwise invalid. This is a convenience
 * function that allows drivers to only store the 'pci_devhdl_t' after
 * successful attachment */
pci_bdf_t pci_bdf(pci_devhdl_t hdl);

/*================== API's related to chassis' and slots =====================*/
/* return the chassis and slot that device 'bdf' resides in, slot == 0, means not in a slot */
pci_cs_t pci_device_chassis_slot(pci_bdf_t bdf);
/* return the device 'bdf' that resides in the specified chassis and slot. If
 * PCI_BDF_NONE is returned and <r> is not NULL, <r> will contain the reason
 * PCI_BDF_NONE was returned. If r == PCI_ERR_EINVAL it means the chassis/slot
 * provided was invalid. If r == PCI_ERR_ENODEV, it means the slot is empty
*/
pci_bdf_t pci_chassis_slot_device(pci_cs_t cs, pci_err_t *r);
/* return the bridge 'bdf' that is connected to the specified chassis and slot.
 * If PCI_BDF_NONE is returned it means the chassis/slot provided was invalid or
 * is otherwise not associated with a bridge or Root Port.
 * A PCI bridge (not PCIe Root Port) may be connected to several slots, In this
 * case the same BDF will be returned for each slot connected to the bridge
*/
pci_bdf_t pci_chassis_slot_bridge(pci_cs_t cs);

/*============= device configuration space register read API's ===============*/
pci_err_t pci_device_read_vid(pci_bdf_t bdf, pci_vid_t *vid);
pci_err_t pci_device_read_did(pci_bdf_t bdf, pci_did_t *did);
pci_err_t pci_device_read_revid(pci_bdf_t bdf, pci_revid_t *revid);
pci_err_t pci_device_read_ssid(pci_bdf_t bdf, pci_ssid_t *ssid);
pci_err_t pci_device_read_ssvid(pci_bdf_t bdf, pci_ssvid_t *ssvid);
pci_err_t pci_device_read_ccode(pci_bdf_t bdf, pci_ccode_t *ccode);
pci_err_t pci_device_read_hdrType(pci_bdf_t bdf, pci_hdrType_t *hdrType);
pci_err_t pci_device_read_cmd(pci_bdf_t bdf, pci_cmd_t *cmd);
pci_err_t pci_device_read_status(pci_bdf_t bdf, pci_stat_t *status);
pci_err_t pci_device_read_latency(pci_bdf_t bdf, pci_latency_t *latency);
pci_err_t pci_device_read_clsize(pci_bdf_t bdf, pci_clsize_t *cache_linesz);
bool_t pci_device_is_multi_func(pci_bdf_t bdf);

/* API's for handling capabilities. Capbility ID's are defined in the cap*.h files */
int_t pci_device_find_capid(pci_bdf_t bdf, pci_capid_t capid);
pci_err_t pci_device_read_capid(pci_bdf_t bdf, pci_capid_t *capid, uint_t idx);
pci_err_t pci_device_read_cap(pci_bdf_t bdf, pci_cap_t *cap, uint_t idx);

/* API's for retrieving device assigned IRQ's and base addresses */
pci_err_t pci_device_read_irq(pci_devhdl_t hdl, int_t *nirq, pci_irq_t *irq);
pci_err_t pci_device_read_ba(pci_devhdl_t hdl, int_t *nba, pci_ba_t *ba, pci_reqType_t reqType);

/* Expansion ROM enable/disable */
/* Callers responsibility to enable Memory Access bit in the command register */
pci_err_t pci_device_rom_enable(pci_devhdl_t hdl);
pci_err_t pci_device_rom_disable(pci_devhdl_t hdl);

/*
 * The following functions provide read access to the device dependent portion
 * of the 256/4096 byte PCI/PCIe configuration space from 0x40 to 0xFF/0xFFF.
 * The offset parameter must be aligned.
 * These functions should only be used if the corresponding information cannot
 * be obtained with a pre-existing library or capability module API. Also check
 * the capability module API's defined in <pci/cap_*.h> files
*/
pci_err_t pci_device_cfg_rd8(pci_bdf_t bdf, uint_t offset, uint8_t *val);
pci_err_t pci_device_cfg_rd16(pci_bdf_t bdf, uint_t offset, uint16_t *val);
pci_err_t pci_device_cfg_rd32(pci_bdf_t bdf, uint_t offset, uint32_t *val);
pci_err_t pci_device_cfg_rd64(pci_bdf_t bdf, uint_t offset, uint64_t *val);

/*========== device configuration space register write API's =================*/
/* <cmd_p> and <status_p> can be NULL if you don't want the register value after the write returned */
pci_err_t pci_device_write_cmd(pci_devhdl_t hdl, pci_cmd_t cmd, pci_cmd_t *cmd_p);
pci_err_t pci_device_write_status(pci_devhdl_t hdl, pci_stat_t status, pci_stat_t *status_p);

/*
 * The following functions provide write access to the device dependent portion
 * of the 256/4096 byte PCI/PCIe configuration space from 0x40 to 0xFF/0xFFF.
 * The offset parameter must be aligned.
 * Pass NULL for the <val_p> parameter if you don't want the register value after
 * write returned
*/
pci_err_t pci_device_cfg_wr8(pci_devhdl_t hdl, uint_t offset, uint8_t val, uint8_t *val_p);
pci_err_t pci_device_cfg_wr16(pci_devhdl_t hdl, uint_t offset, uint16_t val, uint16_t *val_p);
pci_err_t pci_device_cfg_wr32(pci_devhdl_t hdl, uint_t offset, uint32_t val, uint32_t *val_p);
pci_err_t pci_device_cfg_wr64(pci_devhdl_t hdl, uint_t offset, uint64_t val, uint64_t *val_p);

/*============== device capability enable/disable API's ======================*/
pci_err_t pci_device_cfg_cap_enable(pci_devhdl_t hdl, pci_reqType_t reqType, pci_cap_t cap);
pci_err_t pci_device_cfg_cap_disable(pci_devhdl_t hdl, pci_reqType_t reqType, pci_cap_t cap);
bool_t pci_device_cfg_cap_isenabled(pci_devhdl_t hdl, pci_cap_t cap);

/*=================== device address translation API =========================*/
/*
 * The following function is used by driver software in order to obtain any
 * translations required between CPU memory addresses and PCI addresses. The
 * <as> attributes should specify in the <as>->attr field whether the driver is
 * requesting translation for an outbound transfer (from CPU memory to PCI
 * device) or inbound transfer (from PCI device to CPU memory). All addresses
 * are specified as physical addresses
*/
pci_err_t pci_device_map_as(pci_devhdl_t hdl, const pci_ba_t * const as, pci_ba_t *as_xlate);

/*======================== bus/device reset API ==============================*/
/*
 * This function can be used to initiate a reset of a specific device (function
 * level reset if the device is PCIe and supports FLR as determined by the
 * device capabilities register or if the device is PCI and supports the
 * Advanced Features capability and FLR as per the AF capabilities register) or
 * of a PCI bus segment/PCIe link (secondary bus reset) if the device resides on
 * a PCI-to-PCI bridge (or PCIe Root Port that reports as a PCI-to-PCI bridge).
 *
 * In all cases, the specific device to be reset or the bus/link on which the
 * device resides is identified by <hdl>.
 *
 * A device cannot be reset unless the caller is the owner of the device.
 *
 * If the reset type is 'pci_resetType_e_BUS', all devices on the bus/link on
 * which the device identified by <hdl> resides and below will be reset. That
 * is, if <hdl> identifies a bridge device, then the reset will propagate to
 * each subordinate bus segment below the segment on which the bridge identified
 * by <hdl> resides.
 *
 * On successful return, the device identified by <hdl> will have been reset and
 * re-configured to the D0 initialized state. Any driver software utilizing the
 * device must comprehend this condition and perform any required device
 * specific initialization that may have been lost as a result of the reset
 * operation including, but not limited to, restoring the bus master bit in the
 * command register of affected devices.
 *
 * IMPORTANT
 *
 * Since this API can potentially impact multiple devices, the caller must be
 * sure of what they are doing. During the time that the reset is occurring,
 * configuration space accesses to the device(s) will be halted. There is
 * currently no in-band mechanism for preventing accesses to device specific
 * registers obtained from a successful call to pci_device_read_ba() and
 * mmap()'d by other driver software so it is the callers responsibility to
 * coordinate with such software as required.
 *
*/
pci_err_t pci_device_reset(pci_devhdl_t hdl, pci_resetType_e resetType);

/*
 ===============================================================================

 The following API's are for configuring the Type 1 bridge devices

 ===============================================================================
*/

pci_err_t pci_device_read_sec_status(pci_bdf_t bdf, pci_stat_t *sstatus);
pci_err_t pci_device_read_sec_latency(pci_bdf_t bdf, pci_latency_t *latency);
pci_err_t pci_device_read_bridge_ctrl(pci_bdf_t bdf, pci_bctrl_t *bctrl);
pci_err_t pci_device_read_pri_busnum(pci_bdf_t bdf, pci_busnum_t *busnum);
pci_err_t pci_device_read_sec_busnum(pci_bdf_t bdf, pci_busnum_t *busnum);
pci_err_t pci_device_read_sub_busnum(pci_bdf_t bdf, pci_busnum_t *busnum);

pci_err_t pci_device_read_mem_base(pci_bdf_t bdf, pci_ba_val_t *base);
pci_err_t pci_device_read_mem_limit(pci_bdf_t bdf, pci_ba_val_t *limit);
pci_err_t pci_device_read_pfmem_base(pci_bdf_t bdf, pci_ba_val_t *base);
pci_err_t pci_device_read_pfmem_limit(pci_bdf_t bdf, pci_ba_val_t *limit);
pci_err_t pci_device_read_io_base(pci_bdf_t bdf, pci_ba_val_t *base);
pci_err_t pci_device_read_io_limit(pci_bdf_t bdf, pci_ba_val_t *limit);

/* for all write functions, the 3rd parameter can be NULL if you don't want the register value after the write returned */
pci_err_t pci_device_write_sec_status(pci_devhdl_t hdl, pci_stat_t sstatus, pci_stat_t *sstatus_p);
pci_err_t pci_device_write_bridge_ctrl(pci_devhdl_t hdl, pci_bctrl_t bctrl, pci_bctrl_t *bctrl_p);
pci_err_t pci_device_write_pri_busnum(pci_devhdl_t hdl, pci_busnum_t busnum, pci_busnum_t *busnum_p);
pci_err_t pci_device_write_sec_busnum(pci_devhdl_t hdl, pci_busnum_t busnum, pci_busnum_t *busnum_p);
pci_err_t pci_device_write_sub_busnum(pci_devhdl_t hdl, pci_busnum_t busnum, pci_busnum_t *busnum_p);

pci_err_t pci_device_write_mem_base(pci_devhdl_t hdl, pci_ba_val_t base, pci_ba_val_t *base_p);
pci_err_t pci_device_write_mem_limit(pci_devhdl_t hdl, pci_ba_val_t limit, pci_ba_val_t *limit_p);
pci_err_t pci_device_write_pfmem_base(pci_devhdl_t hdl, pci_ba_val_t base, pci_ba_val_t *base_p);
pci_err_t pci_device_write_pfmem_limit(pci_devhdl_t hdl, pci_ba_val_t limit, pci_ba_val_t *limit_p);
pci_err_t pci_device_write_io_base(pci_devhdl_t hdl, pci_ba_val_t base, pci_ba_val_t *base_p);
pci_err_t pci_device_write_io_limit(pci_devhdl_t hdl, pci_ba_val_t limit, pci_ba_val_t *limit_p);



#endif	/* _PCI_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/pci/public/pci/pci.h $ $Rev: 819654 $")
#endif
