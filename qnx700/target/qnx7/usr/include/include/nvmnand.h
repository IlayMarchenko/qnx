/*
 * Copyright (c) 2013-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and
 * proprietary rights in and to this software and related documentation.  Any
 * use, reproduction, disclosure or distribution of this software and related
 * documentation without an express license agreement from NVIDIA Corporation
 * is strictly prohibited.
 */

/**
 * @file nvmnand.h
 * @brief <b> NVIDIA mNAND library </b>
 *
 * @b Description: This files declares the interface for using mNAND
 * with encapsulation of different vendor commands for health related
 * information.
 *
 */

#ifndef __NV_MNAND_H__
#define __NV_MNAND_H__

/**
 * @defgroup qnx_mnand_group mNAND Interface
 *
 * Interacts with mNAND via vendor-specific
 * commands or more generic commands (JDEC spec. 4.51).
 * @ingroup qnx_lib_group
 * @{
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * Defines the maximum erase count a block can have.
 */
#define MAX_ERASE_CNT    0xFFFF

/**
 * Defines the sector size.
 */
#ifndef SECTOR_SZ
#define SECTOR_SZ               512
#endif

/* forward declaration */
struct __mnand_chip;
struct __mnand_operations;

/**
 * Holds information about an individual block.
 */
typedef struct __mnand_block_info {
    uint16_t block_number;    /*! block#, absolute */
    uint16_t block_age;       /*! age (aka erase, p/e) count */
    uint16_t block_type;      /*! block type */
        #define MNAND_UNKNOWN_BLOCK         (1 << 0)
        #define MNAND_MLC_BLOCK             (1 << 1)
        #define MNAND_SLC_BLOCK             (1 << 2)
        #define MNAND_UNKNOWN_BAD_BLOCK     (1 << 8)
        #define MNAND_MANF_BAD_BLOCK        (1 << 9)
        #define MNAND_RUNTIME_BAD_BLOCK     (1 << 10)
        #define MNAND_SYSTEM_BLOCK          (1 << 11)
    uint16_t valid;           /* is this entry valid? */
} mnand_block_info;

/**
 * Holds information on the mNAND lifetime element.
 */
typedef union __mnand_life_time_element {
    uint16_t spare_blocks;    /*! Number of spare blocks in this region. */
    double   percentage;      /*! Life time in percentage. */
} mnand_life_time_element;

/**
 * Holds information on the mNAND lifetime.
 */
typedef struct __mnand_life_time_info {
    mnand_life_time_element life_time;
    uint8_t  life_time_type;  /*! Specifies how lifetime is represented. */
        #define MNAND_LIFETIME_INVALID     (1 << 0)
        #define MNAND_LIFETIME_IN_BLOCK    (1 << 1)
        #define MNAND_LIFETIME_IN_PERCENT  (1 << 2)
} mnand_life_time_info;

/**
 * Holds information on the refresh element.
 */
typedef union __mnand_refresh_element {
    uint16_t block;           /*! last block being refresh */
    double   percentage;      /*! refresh percentage */
} mnand_refresh_element;

/**
 * Holds information on the refresh progress.
 */
typedef struct __mnand_refresh_progress {
    mnand_refresh_element progress;
    uint8_t progress_type;    /*! how the progress being presented */
        #define MNAND_RFSH_PROG_INVALID     (1 << 0)
        #define MNAND_RFSH_PROG_IN_BLOCK    (1 << 1)
        #define MNAND_RFSH_PROG_IN_PERCENT  (1 << 2)
} mnand_refresh_progress;

/**
 * Holds information on refresh properties.
 */
typedef struct __mnand_refresh_properties {
    uint32_t rfsh_days;               /*! whole chip refreshes in given days */
    uint32_t def_rfsh_interval;       /*! default refresh interval, in msec */
    uint32_t min_rfsh_interval;       /*! minimum refresh interval, in msec */
    uint32_t shutdown_rfsh_interval;  /*! minimum shutdown refresh interval, in msec */
    uint32_t rfsh_calibrate_cnt;      /*! minimum refreshes before re-calibration */
} mnand_refresh_properties;

/**
 * Holds the summary of ages.
 */
typedef struct __mnand_ages_element {
    uint16_t min_age;         /*! min. age in this region */
    uint16_t max_age;         /*! max. age in this region */
    double   avg_age;         /*! avg. age in this region */
    uint32_t total_age;       /*! total age (if available) */
    uint8_t valid;            /*! is this entry valid? */
} mnand_ages_info;

/**
 * Holds a summary of given block type (or region).
 */
typedef struct __mnand_summary_element {
    mnand_life_time_info life;/*! life time information */
    mnand_ages_info ages;     /*! ages information */
    uint8_t valid;            /*! is this entry valid? */
} mnand_summary_element;

/**
 * Holds an aggregation of summaries.
 */
typedef struct __mnand_summary_info {
    mnand_summary_element mlc;    /*! MLC region */
    mnand_summary_element slc;    /*! SLC region */
    mnand_summary_element total;  /*! per chip */
    /** Number of factory bad blocks, where -1 indicates an invalid count. */
    int32_t factory_bb_cnt;
    /** Number of runtime bad blocks, where -1 indicates an invalid count. */
    int32_t runtime_bb_cnt;
} mnand_summary_info;

/**
 * CID
 */
typedef struct __mnand_cid_info {
    uint8_t data[16];    /*! JDEC spec. 4.51, table 64, 128bit wide */
} mnand_cid_info;

/**
 * CSD
 */
typedef struct __mnand_csd_info {
    uint8_t data[16];    /*! JDEC spec. 4.51, table 67, 128bit wide */
} mnand_csd_info;

/**
 * EXT CSD
 */
typedef struct __mnand_ext_csd_info {
    uint8_t data[512];   /*! JDEC spec. 4.51, table 82, 512byte wide */
} mnand_ext_csd_info;

/**
 * Defines mNAND devices.
 */
typedef enum __mnand_device_type {
    MNAND_CATCH_ALL = 0,   /*! "catch-all", used when none matched */
    MNAND_HYNIX_F26 = 1,   /*! Hynix F26 */
    MNAND_HYNIX_F20 = 2,   /*! Hynix F20 */
    MNAND_HYNIX_F16 = 3,   /*! Hynix F16 */
    MNAND_SAMSUNG50 = 4,   /*! Samsung eMMC5.0 */
    MNAND_SAMSUNG51 = 5,   /*! Samsung eMMC5.1 */
    MNAND_TOSHIBA   = 6,   /*! Toshiba */
} MNAND_DEVICE_TYPE;

/**
 * mNAND EOL status enumeration
 */
typedef enum __mnand_eol_status {
    MNAND_EOL_OK = 0,        /*! Not yet EOL */
    MNAND_EOL_DETECTED = 1,  /*! EOL detected */
} MNAND_EOL_STATUS;

/**
 * mNAND operation status used in the API
 */
typedef enum __mnand_status {
    MNAND_OK = 0,            /*! OK */
    MNAND_ENOMEM = 1,        /*! memory allocation error */
    MNAND_EIO = 2,           /*! I/O error */
    MNAND_EINVAL = 3,        /*! invalid operation */
    MNAND_EOPEN = 4,         /*! error opening device node */
    MNAND_UNSUPPORTED = 5,   /*! not supported operation */
    MNAND_UNKNOWN_ERR = 6,   /*! unknown error */
} MNAND_STATUS;

typedef uint32_t (*__mnand_get_block_tabsize)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_open)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_close)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_cid)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_csd)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_xcsd)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_card_status)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_block_info)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_update_summary)(struct __mnand_chip *chip);
typedef MNAND_STATUS (*__mnand_check_eol)(struct __mnand_chip *chip,
    MNAND_EOL_STATUS *eol_status);
typedef MNAND_STATUS (*__mnand_set_xcsd)(struct __mnand_chip *chip,
    uint8_t index, uint8_t value);
typedef MNAND_STATUS (*__mnand_send_refresh)(struct __mnand_chip *chip,
    int32_t cached, uint8_t block_type, int32_t num_blocks, mnand_refresh_progress *progress);
typedef MNAND_STATUS (*__mnand_get_rfsh_progress)(struct __mnand_chip *chip,
    double *rfsh_progress);

/**
 * mNAND operation block
 */
struct __mnand_operations {
    __mnand_open               open;             /*! mNAND specific, mandatory */
    __mnand_close              close;            /*! mNAND specific, mandatory */
    __mnand_send_refresh       send_rfsh;        /*! mNAND specific */
    __mnand_get_rfsh_progress  get_rfsh_progress;/*! mNAND specific */
    __mnand_update_block_info  update_blk_info;  /*! mNAND specific */
    __mnand_update_summary     update_summary;   /*! mNAND specific */
    __mnand_check_eol          check_eol;        /*! mNAND specific */
    __mnand_update_card_status update_card_status;    /*! common */
    __mnand_update_cid         update_cid;       /*! common */
    __mnand_update_csd         update_csd;       /*! common */
    __mnand_update_xcsd        update_xcsd;      /*! common */
    __mnand_set_xcsd           set_xcsd;         /*! common */
};

/**
 * mNAND chip information
 */
struct __mnand_chip {
    int32_t fd;                     /*! file descriptor */
    char desc[80];                  /*! chip desciption, mNAND specific */
    struct __mnand_operations *ops; /*! mNAND specific opertions */
    int32_t num_blocks;             /*! Number of blocks available, where 0=unavailable. */
    mnand_block_info *block_info;   /*! block info list, indexd by num_blocks */
    int32_t refresh_available;      /*! force refresh is available */
    mnand_refresh_properties rfsh_properties;  /*! refresh properties */
    int32_t summary_available;      /*! summary info is available */
    mnand_summary_info *summary;    /*! summary info, not NULL when available */
    mnand_cid_info cid;             /*! CID */
    mnand_csd_info csd;             /*! CSD */
    mnand_ext_csd_info xcsd;        /*! EXT CSD */
    uint32_t card_status;           /*! card status */
    MNAND_DEVICE_TYPE dev_type;     /*! device type */
    void *priv;                     /*! mNAND specific private "handle" */
};

typedef struct __mnand_operations mnand_operations;
typedef struct __mnand_chip mnand_chip;

/* prototypes for wrapper functions */

/**
 * Returns the status of BKOPS_EN bit.
 *
 * @param[in] chip - pointer to chip handle.
 * @param[in] xcsd - pointer to EXT CSD (if given it will be used
 *               else EXT CSD is read from mNAND),
 * @param[out] enabled - store the BKOPS_EN bit.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_get_bkops_en(mnand_chip *chip, mnand_ext_csd_info *xcsd,
    int32_t *enabled);

/**
 * Is Device Cache enabled
 *
 * @param chip - pointer to chip handle
 * @param is_en - store the status of cache
 *
 * @retval  MNAND_OK, success
 * @retval  else problem with operation
 */
MNAND_STATUS mnand_get_is_cache_en(mnand_chip *chip, bool *is_en);

/**
 * Get Device Cache size in kb
 *
 * @param chip - pointer to chip handle
 * @param cache_size - store device Cache size in kb
 *
 * @retval  MNAND_OK, success
 * @retval  else problem with operation
 */
MNAND_STATUS mnand_get_cache_size(mnand_chip *chip, uint32_t *cache_size);

/**
 * Get Device Cache flush policy
 *
 * @param chip - pointer to chip handle
 * @param cache_flush_policy - store device cache flush policy
 *
 * @retval  MNAND_OK, success
 * @retval  else problem with operation
 */
MNAND_STATUS mnand_get_cache_flush_policy(mnand_chip *chip,
        uint8_t *cache_flush_policy);

/**
 * Returns the status of BKOPS.
 *
 * @param[in] chip - pointer to chip handle.
 * @param[in] xcsd - pointer to EXT CSD (if given it will be used
 *               else EXT CSD is read from mNAND).
 * @param[out] stat - store the status of BKOPS.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_get_bkops_status(mnand_chip *chip, mnand_ext_csd_info *xcsd,
    uint8_t *stat);

/**
 * Marks the start of BKOPS.
 *
 * @param chip - pointer to chip handle.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_set_bkops_start(mnand_chip *chip);

/**
 * Enables power-off notification.
 *
 * @param chip - pointer to chip handle.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_enable_power_off_notification(mnand_chip *chip);

/**
 * Sends power-off notification.
 *
 * @param chip - pointer to chip handle.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_send_power_off_notification(mnand_chip *chip);

/**
 * "Opens" the mNAND chip. This function must be called first to
 * establish mNAND health related content. The function identifies the mNAND.
 * It allocates and initializes various health related data structures.
 *
 * mnand_open and mnand_close to be used in pair.
 *
 * @param devname - pointer to device name (e.g. /dev/emmc0)
 * @param chip - the mNAND chip handle to be initialized.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_open(const char *devname, mnand_chip *chip);

/**
 * "Closes" (aka releases) the mNAND chip. This function needs to be
 * called last to free up health related resource and various data
 * structures.
 *
 * mnand_open and mnand_close to be used in pair.
 *
 * @param chip - the mNAND chip handle to be used.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.n.
 */
MNAND_STATUS mnand_close(mnand_chip *chip);

/**
 * "Binds" the mNAND chip. This function needs to be called first to
 * establish mNAND health related content. Identification of mNAND will
 * be performed. Various health related data structures will be allocated,
 * initialized, and set up.
 *
 * mnand_bind and mnand_unbind to be used in pair.
 *
 * Note: this function uses existed file descriptor (unlike mnand_open,
 *       which takes a pathname for device node).
 *
 * @param fd - file descriptor to mNAND device.
 * @param chip - the mNAND chip handle to be initialized.
 *
 * @retval  MNAND_OK indicates success;
 *          otherwise there is a problem with the operation.
 */
MNAND_STATUS mnand_bind(int32_t fd, mnand_chip *chip);

/**
 * "Unbinds" (aka releases) the mNAND chip. This function needs to be
 * called last to free up health related resource and various data
 * structures.
 *
 * mnand_bind and mnand_unbind to be used in pair.
 *
 * @note The file descriptor used in "bind" will NOT be closed.
 *
 * @param chip - the mNAND chip handle to be used.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_unbind(mnand_chip *chip);

/**
 * Updates the CID field inside mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_cid(mnand_chip *chip);

/**
 * Updates the CSD field inside mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_csd(mnand_chip *chip);

/**
 * Updates the EXT CSD field inside mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_xcsd(mnand_chip *chip);

/**
 * Updates the card status field inside mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_card_status(mnand_chip *chip);

/**
 * Updates the list of block info inside the mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_block_info(mnand_chip *chip);

/**
 * Updates the summary info inside the mNAND chip handle.
 *
 * @param chip - the mNAND chip handle to be updated.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_update_summary_info(mnand_chip *chip);

/**
 * Checks EOL status.
 *
 * @param chip - the mNAND chip handle to be updated.
 * @param eol_status - EOL status (MNAND_EOL_DETECTED = EOL set)
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_check_eol_status(mnand_chip *chip, MNAND_EOL_STATUS *eol_status);

/**
 * Sets the EXT CSD register.
 *
 * @param chip - the mNAND chip handle to be used.
 * @param index - which EXT CSD register to be set.
 * @param value - the value of EXT CSD register to be set.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_set_xcsd(mnand_chip *chip, uint8_t index, uint8_t value);

/**
 * Sends a "refresh" command to the mNAND chip. The purpose is to force data
 * rotation to improve the data retention.
 *
 * @param chip - the mNAND chip handle to be used.
 * @param block_type - which region (SLC/MLC) to be used.
 * @param num_blocks - Number of blocks to be refreshed.
 * @param progress - refresh progress.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_send_refresh(mnand_chip *chip, uint8_t block_type,
    int32_t num_blocks, mnand_refresh_progress *progress);

/**
 * Extracts the age info from the mNAND chip.
 *
 * @param chip - the mNAND chip handle to be used.
 * @param block_type - which region (SLC/MLC) to be used.
 * @param total_age - the sum of the ages from the blocks.
 * @param blk_count - Number of blocks in the specified region.
 * @param avg_age - average age of the blocks,
 *                  can be used when total_age/blk_counot not available.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_extract_age_info(mnand_chip *chip, int32_t block_type,
    uint64_t *total_age, int32_t *blk_count, double *avg_age);

/**
 * Extracts refresh progress from the mNAND chip.
 *
 * @param chip - the mNAND chip handle to be used.
 * @param rfsh_progress - current refresh progress (in percentage)
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_get_refresh_progress(mnand_chip *chip, double *rfsh_progress);

/**
 * Extracts spare count info from the mNAND chip.
 *
 * @param chip - the mNAND chip handle to be used.
 * @param life_time_info - information on life time.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
MNAND_STATUS mnand_extract_life_time_info(mnand_chip *chip,
    mnand_life_time_info *life_time_info);

/**
 * Reads data sectors into the given buffer (pointed by virtual address).
 *
 * @note This function uses existed file descriptor. There is no need to
 *       do `mnand_bind` first because no health information is needed.
 *
 * @param fd - file descriptor pint to mNAND device, the descriptor
 *             can be obtained outside the scope of librrary (i.e. without
 *             using mnand_open and using mnand_chip.fd).
 * @param start_sector - the starting sector to be read.
 * @param sector_cnt - the number of sectors to be read.
 * @param virtaddr - buffer address (in virtual address form).
 *
 * @return  Number of sectors read or -1 if there is a problem with the operation.
 */
int32_t mnand_read_sectors_virt(int32_t fd, uint32_t start_sector,
    uint32_t sector_cnt, void *virtaddr);

/**
 * Reads data sectors into given buffer (pointed by physical address).
 *
 * @note This function uses existed file descriptor. There is no need to
 *       do `mnand_bind` first because no health info needed.
 *
 * @param fd - file descriptor point to mNAND device, the descriptor
 *             can be obtained outside the scope of librrary (i.e. without
 *             using mnand_open and using mnand_chip.fd)
 * @param start_sector - the starting sector to be read.
 * @param sector_cnt - the number of sectors to be read.
 * @param physaddr - buffer address (in physical address form)
 *
 * @return  Number of sectors read or -1 if there is a problem with the operation.
 */
int32_t mnand_read_sectors_phys(int32_t fd, uint32_t start_sector,
    uint32_t sector_cnt, off_t physaddr);

/**
 * Trims the whole device.
 *
 * Note: this function uses existed file descriptor. There is no need to
 *       do mnand_bind first, as no health info needed.
 *
 * @return Success indicator. Supported values are:
 *         - 0: Indicates success.
 *         - -1: Indicates a problem with the operation.
 */
int32_t mnand_trim_all(int32_t fd);

/**
 * Writes data sectors from given buffer (pointed by virtual address).
 *
 * Note: this function uses existed file descriptor. There is no need to
 *       do mnand_bind first, as no health info needed.
 *
 * @param fd - file descriptor point to mNAND device, the descriptor
 *             can be obtained outside the scope of librrary (i.e. without
 *             using mnand_open and using mnand_chip.fd)
 * @param start_sector - the starting sector to be written
 * @param sector_cnt - the number of sectors to be written
 * @param virtaddr - buffer address (in virtual address form)
 *
 * @return  Number of sectors written or -1 if there is a problem with the operation.
 */
int32_t mnand_write_sectors_virt(int32_t fd, uint32_t start_sector,
    uint32_t sector_cnt, void *virtaddr);

/**
 * Writes data sectors from given buffer (pointed by physical address).
 *
 * Note: this function uses existed file descriptor. There is no need to
 *       do mnand_bind first, as no health info needed.
 *
 * @param fd - file descriptor point to mNAND device, the descriptor
 *             can be obtained outside the scope of librrary (i.e. without
 *             using mnand_open and using mnand_chip.fd)
 * @param start_sector - the starting sector to be written
 * @param sector_cnt - the number of sectors to be written
 * @param physaddr - buffer address (in physical address form)
 *
 * @return Number of sectors written or -1 if there is a problem with the operation.
 */
int32_t mnand_write_sectors_phys(int32_t fd, uint32_t start_sector,
    uint32_t sector_cnt, off_t physaddr);

/* inline helpers */

/**
 * Returns the validity of the block, given the pointer of block info.
 *
 * @param blk - pointer to block info
 *
 * @return  Non-zero if the block info is valid; otherwise, 0.
 */
static inline int32_t mnand_is_valid_block(mnand_block_info *blk)
{
    assert(blk != NULL);

    return (blk->valid != 0);
}

/**
 * Determines whether a given block is bad.
 *
 * @param blk - pointer to block info.
 *
 * @return  Non-zero if the block is a bad block; otherwise, 0.
 */
static inline int32_t mnand_is_bad_block(mnand_block_info *blk)
{
    assert(blk != NULL);

    return mnand_is_valid_block(blk) && ((blk->block_type &
        (MNAND_UNKNOWN_BAD_BLOCK | MNAND_MANF_BAD_BLOCK |
        MNAND_RUNTIME_BAD_BLOCK)) || (blk->block_age == MAX_ERASE_CNT)) ? 1 : 0;
}

/**
 * Determines whether a given block is a usable block.
 * @note If a block is bad, then the system block is unusable.
 *
 * @param blk - pointer to block info.
 *
 * @return  Non-zero if the block is unusable; otherwise, 0.
 */
static inline int32_t mnand_is_usable_block(mnand_block_info *blk)
{
    assert(blk != NULL);

    return (!mnand_is_valid_block(blk) || mnand_is_bad_block(blk) ||
        (blk->block_type & MNAND_SYSTEM_BLOCK)) ? 0 : 1;
}

/**
 * Determines whether given block is a usable block, and matches given block type.
 *
 * @param blk      - pointer to block info
 * @param blk_type - block type to match
 *
 * @return  Non-zero if the block is usable; otherwise, 0.
 */
static inline int32_t mnand_is_usable_block_with_type(mnand_block_info *blk,
    uint16_t blk_type)
{
    assert((blk != NULL) && (blk_type != 0));

    return (mnand_is_usable_block(blk) && (blk->block_type & blk_type)) ? 1 : 0;
}

/**
 * Determines whether given block is in SLC region.
 *
 * @param blk - pointer to block info
 *
 * @return  Non-zero if the block is in the SLC region; otherwise, 0.
 */
static inline int32_t mnand_is_slc_block(mnand_block_info *blk)
{
    assert(blk != NULL);

    return mnand_is_valid_block(blk) &&
        (blk->block_type & MNAND_SLC_BLOCK) ? 1 : 0;
}

/**
 * Determines whether given block is in MLC region.
 *
 * @param blk - pointer to block info.
 *
 * @return  Non-zero if the block is in the MLC region; otherwise, 0.
 */
static inline int32_t mnand_is_mlc_block(mnand_block_info *blk)
{
    assert(blk != NULL);

    return mnand_is_valid_block(blk) &&
        (blk->block_type & MNAND_MLC_BLOCK) ? 1 : 0;
}

/**
 * Indicates whether the summary is available.
 *
 * @param chip - pointer to chip handle.
 * @return  Non-zero if a summary is available; otherwise, 0.
 */
static inline int32_t mnand_is_summary_available(mnand_chip *chip)
{
    assert(chip != NULL);

    return (chip->summary_available != 0);
}

/**
 * Indicates whether force refresh is available.
 *
 * @param chip - pointer to chip handle.
 *
 * @return  Non-zero if force refresh is available; otherwise, 0.
 */
static inline int32_t mnand_is_refresh_available(mnand_chip *chip)
{
    assert(chip != NULL);

    return (chip->refresh_available != 0);
}

/**
 * Indicates whether the block info is available.
 *
 * @param chip - pointer to chip handle.
 *
 * @return  Non-zero if block info is available; otherwise, 0.
 */
static inline int32_t mnand_is_block_info_available(mnand_chip *chip)
{
    assert(chip != NULL);

    return (chip->num_blocks > 0);
}

/**
 * Determines whether eMMC cache is enabled.
 *
 * @param[in]  chip A pointer to chip handle.
 * @param[out] enabled A pointer to a location where the function returns
 *             the CACHE_EN bit.
 *
 * @retval  MNAND_OK Indicates success; otherwise,
 *          there is a problem with operation.
 */
static inline MNAND_STATUS mnand_get_cache_en(mnand_chip *chip, int32_t *enabled)
{
    MNAND_STATUS status;

    assert((chip != NULL) && (enabled != NULL));

    status = mnand_update_xcsd(chip);
    if (status != MNAND_OK) {
        return status;
    } else {
        *enabled = chip->xcsd.data[33] & 0x1; /*! EXT_CSD[CACHE_CTRL]: CACHE_EN */
    }
    return MNAND_OK;
}

/** @} */

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif /* __NV_MNAND_H__ */
