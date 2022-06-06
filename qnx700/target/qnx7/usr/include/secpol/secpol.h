/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.	 Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.	 Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef _SECPOL_H_INCLUDED
#define _SECPOL_H_INCLUDED

#include <stdint.h>
#include <sys/types.h>

/** @cond */
__BEGIN_DECLS
/** @endcond */

#define SECPOL_INVALID_TYPE 0xffffffff

// Policy id that represents no security policy being in effect
#define SECPOL_POLICY_ID_NO_POLICY	0
// Bit set in the policy id that indicates that the policy is immutable and cannot be changed once loaded.
#define SECPOL_POLICY_ID_IMMUTABLE	0x80000000

#define SECPOL_MAGIC   0x50434553
#define SECPOL_VERSION 1

/** Default security policy file */
#define SECPOL_DEFAULT_POLICY_FILE "/proc/boot/secpol.bin"

/** Blob entry providing location of size of blob within a secpol file.	 An array of these follows the secpol file
 * header.
 */
typedef struct {
	/** Type of data represented by blob */
	uint32_t type;
	/** Offset in file of data */
	uint32_t offset;
	/** Size of data in bytes */
	uint32_t size;
} secpol_blob_t;


/** Header for all secpol files */
typedef struct {
	/** Magic number to identify secpol files */
	uint32_t magic;
	/** File version */
	uint32_t version;
	/** Number of blobs contained in the file */
	uint32_t blob_count;
	/** blob_count blob headers */
	secpol_blob_t blobs[0];
} secpol_file_header_t;

typedef struct secpol_file_s secpol_file_t;

/**
 * Open a security policy file.
 *
 * @param[in] path	Path to the file.  If NULL SECPOL_DEFAULT_POLICY_FILE is used.
 * @param[in] flags Not currently used, must be zero.
 *
 * @return	A handle to the file.
 * @retval NULL Open failed.  The specific cause of the error is indicated by @c errno.
 */
secpol_file_t *secpol_open(const char *path, uint32_t flags);

/**
 * Close the security policy file.
 *
 * @param[in] handle  Handle to the security policy file.
 *
 * @retval None
 */
void secpol_close(secpol_file_t *handle);

/**
 * Find and possibly return a given blob.  This may either be used to find a blob of a particular type, typically
 * referenced by one of the SECPOL_BLOB_* constants.  It may also be used to iterate through all blobs in the file
 * with no prior knowledge of its contents by using SECPOL_BLOB_NEXT as the type.
 *
 * @param[in] handle		Handle to the security policy file.
 * @param[in] type			Type of blob to search for or the constant SECPOL_BLOB_NEXT to return the next blob in
 *							the file.
 * @param[out] blob_info	If non-NULL, updated with information on blob
 * @param[out] data			If non-NULL, updated to contain a pointer to the contents of the blob. This
 *							memory must be freed by the caller.
 *
 * @retval 0  Blob was found
 * @retval -1 An error occurred.  The specific cause of the error is indicated by @c errno.
 */
int secpol_find_blob(secpol_file_t *handle, uint32_t type, secpol_blob_t *blob_info, void **data);

/**
 * Reset the handle so that secpol_find_blob with SECPOL_BLOB_NEXT returns the first blob.
 *
 * @param[in] handle  Handle to the security policy file.
 *
 * @retval None
 */
void secpol_reset(secpol_file_t *handle);

/**
 * Return the type id associated with a type name
 *
 * @param[in] handle	 Handle to the security policy file.
 * @param[in] type_name	 Name of type
 *
 * @return Type id associated with name
 * @retval SECPOL_INVALID_TYPE if name was not found
 */
uint32_t secpol_get_type_id(secpol_file_t *handle, const char *type_name);

/**
 * Return the type name associated with a type id
 *
 * @param[in] handle	 Handle to the security policy file.
 * @param[in] type_id	 Id of the type
 *
 * @return Name of the type.
 * @retval NULL if the type id was not found.
 */
const char *secpol_get_type_name(secpol_file_t *handle, uint32_t type_id);

/**
 * Locate an entry associated with a type id in an array that is sorted by type id and where the first element is
 * the type id.
 *
 * @param[in] type_id  Type id to search for.
 * @param[in] array	   Array to search
 * @param[in] ecount   Number of elements
 * @param[in] esize	   Size of each element in bytes
 *
 * @return A pointer to the element
 * @retval NULL	 An element wasn't found with the indicated type id.
 */
void *secpol_find_entry(uint32_t type_id, void *array, uint32_t ecount, uint32_t esize);

typedef enum {
	/** Call was successful */
	SECPOL_OK = 1,
	/** Security policy file contains no ability data */
	SECPOL_ERROR_NO_DATA = 2,
	/** Security policy file is corrupt. */
	SECPOL_ERROR_BAD_CRC = 3,
	/** The policy id of the ability data does not match that being used by procnto. */
	SECPOL_ERROR_POLICY_MISMATCH = 4,
	/** Some other error occurred, the specific erro is indicated by @c errno. */
	SECPOL_ERROR_FAILED = 5,
} secpol_error_t;

typedef enum {
	// Verify the policy id in the policy file matches the policy being used by the system
	SECPOL_VERIFY_POLICY_ID = 1
} secpol_get_abilities_flags_t;

/**
 * Return the crc32 of block of data.
 *
 * @param[in] buffer	Pointer to a buffer of data
 * @param[in] length	Length of data
 *
 * @return The CRC
 */
uint32_t secpol_crc32(const void *buffer, uint32_t length);

/**
 * Return the policy id of any policy that has been pushed to procnto.	This should be used to verify that it
 * matches the policy id of any blob that is used from a policy file as mismatched policies might have unwanted
 * results.
 *
 * @param[out] policy_id	Address of a variable to receive the policy id.
 *
 * @retval 0  Call was successful
 * @retval -1 Request failed. The specific cause of the error is indicated by @c errno.
 */
int secpol_get_policy_id(uint32_t *policy_id);

/** Constant that can be passed to @c secpol_find_entry to return the next blob of any type. */
#define SECPOL_BLOB_NEXT 0xffffffff

/** TMAP - Blob for converting type names to and from type ids */
#define SECPOL_BLOB_TYPE_MAP 0x50414D54

/**
 * Initial data contained in a blob of type SECPOL_BLOB_TYPE_MAP.
 */
typedef struct {
	/** Blob type = SECPOL_BLOB_TYPE_MAP */
	uint32_t blob_type;
	/** Number of types */
	uint32_t type_count;
	/** Offset to an array of type_count uint32_t values containing the offset in the string table that contains the */
	/** name associated with a type id. */
	uint32_t id_to_name_offset;
	/** Offset to an array of type_count uint32_t containing type ids ordered by type name. */
	uint32_t sorted_id_offset;
	/** Offset in blob to string table, a packed array of type names. */
	uint32_t string_offset;
	/** Size of string table in bytes */
	uint32_t string_size;
} secpol_tm_blob_t;


/**
 * Blob type for the PMA1 blob, which defines security rules governing path manager attach operations, such as
 * resmgr_attach, name_attach and pathmgr_link.	 The data contained in this blob is of type secpol_pma_blob_t
 * with additional data following.
 */
#define SECPOL_BLOB_PMA_RULES 0x31414D50

/**
 * Initial data contained in a blob of type SECPOL_BLOB_PMA_RULES.
 */
typedef struct {
	/** Blob type = SECPOL_BLOB_PMA_RULES */
	uint32_t blob_type;
	/** Id that can be used to validate that blobs were generated from the same set of rules */
	uint32_t policy_id;
	/** Flags, not currently used, must be zero. */
	uint32_t flags;
	/** Offset in blob to an array secpol_pma_rule_list_t objects.	Each element provides information on paths
	 * that may be attached to by processes that are in a particular security domain.  The elements are ordered
	 * by increasing value of type id.
	 */
	uint32_t domains_offset;
	/** Number of elements in domains array */
	uint32_t domain_count;
	/**	 Offset in blob to array of rules.	Each element is of type secpol_pma_rule_t. */
	uint32_t rules_offset;
	/** Number of elements in rules array */
	uint32_t rule_count;
	/** Offset in blob to string table, a packed array of paths. */
	uint32_t paths_offset;
	/** Size of paths array in bytes */
	uint32_t paths_size;
	/** Must be zero */
	uint32_t zero[2];
} secpol_pma_blob_t;

/** Structure defining the offset and number of rules associated with a security domain. */
typedef struct {
	/** Type id associated with process trying to attach */
	uint32_t type_id;
	/** Index of the first rule for this process within the rules array. */
	uint32_t rule_index;
	/** Number of rules for the process */
	uint32_t rule_count;
} secpol_pma_rule_list_t;

/** Flags associated with a single pathmgr attach rule */
typedef enum {
	/** If set, the path associated with the rule should be matched with fnmatch */
	SECPOL_PMA_RULE_PATTERN = 1,
	/** If set, the path should match if it matches an initial directory portion of the path being attached. */
	SECPOL_PMA_RULE_LEADING_DIR = 2,
	/** If set a channel or a symlink may be attached to the path with no relabelling */
	SECPOL_PMA_RULE_LINK = 4,
} secpol_pma_rule_flag_t;

/** A single pathmgr attach rule. */
typedef struct {
	/** Offset relative to path string table of the path. */
	uint32_t path_offset;
	/** Zero or more flags from secpol_pma_rule_flag_t */
	uint32_t flags;
	/** The new type id to use for the channel (might be the same as the process type) */
	uint32_t new_type;
} secpol_pma_rule_t;

/** Blob type for the ABLE blob, which defines procmgr abilities that should be given to processes based on the
 * type id of the security domain they are associated with.	 These procmgr abilities might need to be combined with
 * others not derived from the security policy rules.
 */
#define SECPOL_BLOB_ABILITIES  0x454C4241

#define SECPOL_DYNAMIC_ABILITY_OFFSET 0x8000

/**
 * Initial data contained in a blob of type SECPOL_BLOB_ABILITIES.
 */
typedef struct {
	/** Blob type = SECPOL_BLOB_ABILITIES */
	uint32_t blob_type;
	/** Id that can be used to validate that blobs were generated from the same set of rules */
	uint32_t policy_id;
	/** Flags, not currently used, must be zero. */
	uint32_t flags;
	/** Offset in blob to an array secpol_ability_type_t objects.  Each element provides information on abilities
	 * that should be provided to a process with the given type.  The array is ordered by type_id.
	 */
	uint32_t types_offset;
	/** Number of elements in domains array */
	uint32_t type_count;
	/**	 Offset in blob to array of uint32_t items representing abilities. Ability numbers in excess of
	 * SECPOL_DYNAMIC_ABILITY_OFFSET represent dynamic abilities.
	 */
	uint32_t ability_offset;
	/** Size of ability array in bytes. */
	uint32_t ability_size;
	/** Offset to an array of uint32_t items representing the offsets in the dynamic ability name array of dynamic
	 *  abilities.
	 */
	uint32_t dyn_name_idx_offset;
	uint32_t dyn_name_idx_count;
	uint32_t dyn_names_offset;
	uint32_t dyn_names_size;
} secpol_ability_blob_t;

/** Information on procmgr abilities to be assigned to a type to support enforcement of the rules contained in
 * the security policy.
 */
typedef struct {
	/** Type id associated with security domain */
	uint32_t type_id;
	/** Offset to first ability entry in the ability array for this security domain */
	uint32_t ability_offset;
	/** Size in bytes of ability entries for this security domain */
	uint32_t ability_size;
	/** Number of ability entries for this security domain */
	uint32_t ability_count;
	/** crc32 computed over ability entries */
	uint32_t crc;
} secpol_ability_type_t;

/** Blob type for the QNET blob, which defines type ids of channels that a process may connect to over QNET.
 */
#define SECPOL_BLOB_QNET  0x54454E51

/**
 * Initial data contained in a blob of type SECPOL_BLOB_QNET.
 */
typedef struct {
	/** Blob type = SECPOL_BLOB_QNET */
	uint32_t blob_type;
	/** Id that can be used to validate that blobs were generated from the same set of rules */
	uint32_t policy_id;
	/** Flags, not currently used, must be zero. */
	uint32_t flags;
	/** Offset in blob to an array of secpol_qnet_type_t objects.  Each element provides information on channel
	 * type ids that may be connected to.  The array is ordered by type_id.
	 */
	uint32_t types_offset;
	/** Number of elements in array */
	uint32_t type_count;
	/** Offset in blob to array of uint32_t items representing channel type ids. */
	uint32_t channel_type_offset;
	/** Number of elements in array. */
	uint32_t channel_type_count;
} secpol_qnet_blob_t;

/** Information on type ids of channels that a process of a single type id may connect to over QNET.
 */
typedef struct {
	/** Type id associated with security domain */
	uint32_t type_id;
	/** Index of the first channel type id entry in the array for this security domain */
	uint32_t channel_type_index;
	/** Number of channel type id entries for this security domain */
	uint32_t channel_type_count;
} secpol_qnet_type_t;

/** @cond */
__END_DECLS
/** @endcond */

#endif


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/secpol/public/secpol/secpol.h $ $Rev: 819553 $")
#endif
