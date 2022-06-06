/*
 * Copyright 2016, QNX Software Systems.
 *
 * This code was derived from the linux kernel, more specifically from:
 * drivers/char/tpm/tpm.h (4.9)
 * linux/include/tpm.h (4.9)
 *
 * The linux code had a GNU General Public License and the following copyrights:
 * Copyright (C) 2004,2007,2008 IBM Corporation
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 */

#ifndef _TPM_TPM_DEFS_H_INCLUDED
#define _TPM_TPM_DEFS_H_INCLUDED

/* sorted headers from this project */
#ifndef _TPM_HELPERS_H_INCLUDED
#include "tpm/helpers.h"
#endif

/* sorted system headers */
#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

#define BIT(bit) (1 << bit)

/* #define TPM_ANY_NUM                                                                           0xFFFF */
#define TPM_DIGEST_SIZE                                                                           20  /* Max TPM v1.2 PCR size */

/* this is for TPM1 only -- TPM2 uses TPM2_CC_FIRST & TPM2_CC_LAST */
#define TPM_MAX_ORDINAL                                                                          243

/* tpm_const */
/* #define TPM_MINOR                                                                                224*/ /* officially assigned */
#define TPM_BUFSIZE                                                                             4096
/* #define TPM_NUM_DEVICES                                                                        65536 */
#define TPM_RETRY                                                                                 50 /* 5 seconds */

/* these timeouts are for TPM1 only, just in case they cannot be read from the TPM */
/* tpm_fallback_timeouts */
#define TPM_FALLBACK_TIMEOUT_A                                                                   750
#define TPM_FALLBACK_TIMEOUT_B                                                                  2000
#define TPM_FALLBACK_TIMEOUT_C                                                                   750
#define TPM_FALLBACK_TIMEOUT_D                                                                   750

/* tpm_timeout */
#define TPM_TIMEOUT                                                                                5 /* msecs */
#define TPM_TIMEOUT_RETRY                                                                        100 /* msecs */

/* TPM addresses */
/* #define TPM_SUPERIO_ADDR                                                                        0x2E */
/* #define TPM_ADDR                                                                                0x4E */

/* Indexes the duration array */
#define TPM_SHORT                                                                                  0
#define TPM_MEDIUM                                                                                 1
#define TPM_LONG                                                                                   2
#define TPM_UNDEFINED                                                                              3

#define TPM_ERR_OK                                                                                 0
#define TPM_WARN_RETRY                                                                         0x800
#define TPM_WARN_DOING_SELFTEST                                                                0x802
#define TPM_ERR_DEACTIVATED                                                                      0x6
#define TPM_ERR_DISABLED                                                                         0x7
#define TPM_ERR_INVALID_POSTINIT                                                                  38

#define TPM_INPUT_HEADER_SIZE                                             sizeof(tpm_input_header_t)
#define TPM_OUTPUT_HEADER_SIZE                                           sizeof(tpm_output_header_t)
#define TPM_HEADER_SIZE                           max(TPM_INPUT_HEADER_SIZE, TPM_OUTPUT_HEADER_SIZE)

#define TPM_VID_INTEL                                                                         0x8086
#define TPM_VID_WINBOND                                                                       0x1050
#define TPM_VID_STM                                                                           0x104A

/* #define TPM_PPI_VERSION_LEN                                                                        3 */

/* tpm_device_flags */
#define TPM_CHIP_FLAG_REGISTERED                                                              BIT(0)
#define TPM_CHIP_FLAG_TPM2                                                                    BIT(1)
#define TPM_CHIP_FLAG_IRQ                                                                     BIT(2)
#define TPM_CHIP_FLAG_VIRTUAL                                                                 BIT(3)

typedef struct tpm_input_header_s
{
    uint16_be_t tag;
    uint32_be_t length;
    uint32_be_t ordinal;
} __attribute__((__packed__)) tpm_input_header_t;

typedef struct tpm_output_header_s
{
    uint16_be_t tag;
    uint32_be_t length;
    uint32_be_t return_code;
} __attribute__((__packed__)) tpm_output_header_t;

#define TPM_TAG_RQU_COMMAND                                                  native_to_be16_hdr(193)

typedef struct stclear_flags_s
{
    uint16_be_t tag;
    uint8_t deactivated;
    uint8_t disable_force_clear;
    uint8_t physical_presence;
    uint8_t physical_presence_lock;
    uint8_t b_global_lock;
} __attribute__((__packed__)) stclear_flags_t;

typedef struct tpm_version_s
{
    uint8_t major;
    uint8_t minor;
    uint8_t rev_major;
    uint8_t rev_minor;
} __attribute__((__packed__)) tpm_version_t;

typedef struct tpm_version_1_2_s
{
    uint16_be_t tag;
    uint8_t major;
    uint8_t minor;
    uint8_t rev_major;
    uint8_t rev_minor;
} __attribute__((__packed__)) tpm_version_1_2_t;

typedef struct timeout_s
{
    uint32_be_t a;
    uint32_be_t b;
    uint32_be_t c;
    uint32_be_t d;
} __attribute__((__packed__)) timeout_t;

typedef struct duration_s
{
    uint32_be_t tpm_short;
    uint32_be_t tpm_medium;
    uint32_be_t tpm_long;
} __attribute__((__packed__)) duration_t;

typedef struct permanent_flags_s
{
    uint16_be_t tag;
    uint8_t disable;
    uint8_t ownership;
    uint8_t deactivated;
    uint8_t read_pubek;
    uint8_t disable_owner_clear;
    uint8_t allow_maintenance;
    uint8_t physical_presence_lifetime_lock;
    uint8_t physical_presence_hw_enable;
    uint8_t physical_presence_cmd_enable;
    uint8_t cekp_used;
    uint8_t tpm_post;
    uint8_t tpm_post_lock;
    uint8_t fips;
    uint8_t op;
    uint8_t enable_revoke_ek;
    uint8_t nv_locked;
    uint8_t read_srk_pub;
    uint8_t tpm_established;
    uint8_t maintenance_done;
    uint8_t disable_full_da_logic_info;
} __attribute__((__packed__)) permanent_flags_t;

typedef union cap_u
{
    permanent_flags_t perm_flags;
    stclear_flags_t stclear_flags;
    bool owned;
    uint32_be_t num_pcrs;
    tpm_version_t tpm_version;
    tpm_version_1_2_t tpm_version_1_2;
    uint32_be_t manufacturer_id;
    timeout_t timeout;
    duration_t duration;
} cap_ut;

#define TPM_CAP_RESP_SIZE(cap_member)   (sizeof_member(tpm_cmd_t, header.out) + \
                                         sizeof_member(tpm_cmd_t, params.getcap_out.cap_size) + \
                                         sizeof_member(tpm_cmd_t, params.getcap_out.cap.cap_member))

#define TPM_CAP_SIZE(cap_member)                                 (sizeof_member(cap_ut, cap_member))

/* tpm_capabilities */
#define TPM_CAP_FLAG                                                           native_to_be32_hdr(4)
#define TPM_CAP_PROP                                                           native_to_be32_hdr(5)
#define CAP_VERSION_1_1                                                     native_to_be32_hdr(0x06)
#define CAP_VERSION_1_2                                                     native_to_be32_hdr(0x1A)

/* tpm_sub_capabilities */
#define TPM_CAP_PROP_PCR                                                   native_to_be32_hdr(0x101)
#define TPM_CAP_PROP_MANUFACTURER                                          native_to_be32_hdr(0x103)
#define TPM_CAP_FLAG_PERM                                                  native_to_be32_hdr(0x108)
#define TPM_CAP_FLAG_VOL                                                   native_to_be32_hdr(0x109)
#define TPM_CAP_PROP_OWNER                                                 native_to_be32_hdr(0x111)
#define TPM_CAP_PROP_TIS_TIMEOUT                                           native_to_be32_hdr(0x115)
#define TPM_CAP_PROP_TIS_DURATION                                          native_to_be32_hdr(0x120)

typedef struct tpm_getcap_params_in_s
{
    uint32_be_t cap;
    uint32_be_t subcap_size;
    uint32_be_t subcap;
} __attribute__((__packed__)) tpm_getcap_params_in_t;

typedef struct tpm_getcap_params_out_s
{
    uint32_be_t cap_size;
    cap_ut cap;
} __attribute__((__packed__)) tpm_getcap_params_out_t;

typedef struct tpm_readpubek_params_out_s
{
    uint8_t algorithm[4];
    uint8_t encscheme[2];
    uint8_t sigscheme[2];
    uint32_be_t paramsize;
    uint8_t parameters[12]; /*assuming RSA */
    uint32_be_t keysize;
    uint8_t modulus[256];
    uint8_t checksum[20];
} __attribute__((__packed__)) tpm_readpubek_params_out_t;

typedef union tpm_cmd_header_u
{
    tpm_input_header_t in;
    tpm_output_header_t out;
} tpm_cmd_header_ut;

typedef struct tpm_pcrread_out_s
{
    uint8_t pcr_result[TPM_DIGEST_SIZE];
} __attribute__((__packed__)) tpm_pcrread_out_t;

typedef struct tpm_pcrread_in_s
{
    uint32_be_t pcr_idx;
} __attribute__((__packed__)) tpm_pcrread_in_t;

typedef struct tpm_pcrextend_in_s
{
    uint32_be_t pcr_idx;
    uint8_t hash[TPM_DIGEST_SIZE];
} __attribute__((__packed__)) tpm_pcrextend_in_t;

/* 128 bytes is an arbitrary cap. This could be as large as TPM_BUFSIZE - 18
 * bytes, but 128 is still a relatively large number of random bytes and
 * anything much bigger causes users of struct tpm_cmd_t to start getting
 * compiler warnings about stack frame size. */
#define TPM_MAX_RNG_DATA    128

typedef struct tpm_getrandom_out_s
{
    uint32_be_t rng_data_len;
    uint8_t rng_data[TPM_MAX_RNG_DATA];
} __attribute__((__packed__)) tpm_getrandom_out_t;

typedef struct tpm_getrandom_in_s
{
    uint32_be_t num_bytes;
} __attribute__((__packed__)) tpm_getrandom_in_t;

typedef struct tpm_startup_in_s
{
    uint16_be_t startup_type;
} __attribute__((__packed__)) tpm_startup_in_t;

typedef union tpm_cmd_params_u
{
    tpm_getcap_params_out_t getcap_out;
    tpm_readpubek_params_out_t readpubek_out;
    uint8_t readpubek_out_buffer[sizeof(tpm_readpubek_params_out_t)];
    tpm_getcap_params_in_t getcap_in;
    tpm_pcrread_in_t pcrread_in;
    tpm_pcrread_out_t pcrread_out;
    tpm_pcrextend_in_t pcrextend_in;
    tpm_getrandom_in_t getrandom_in;
    tpm_getrandom_out_t getrandom_out;
    tpm_startup_in_t startup_in;
} tpm_cmd_params_ut;

typedef struct tpm_cmd_s
{
    tpm_cmd_header_ut header;
    tpm_cmd_params_ut params;
} __attribute__((__packed__)) tpm_cmd_t;

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _TPM_TPM_DEFS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/tpm/public/tpm/tpm_defs.h $ $Rev: 820218 $")
#endif
