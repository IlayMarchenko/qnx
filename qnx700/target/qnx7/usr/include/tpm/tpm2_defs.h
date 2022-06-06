/*
 * Copyright 2016, QNX Software Systems.
 *
 * This code was derived from the linux kernel, more specifically from:
 * drivers/char/tpm/tpm.h (4.9)
 * drivers/char/tpm/tpm2-cmd.c (4.9)
 *
 * The linux code had a GNU General Public License and the following copyrights:
 * Copyright (C) 2004 IBM Corporation
 * Copyright (C) 2015 Intel Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 */

#ifndef _TPM_TPM2_DEFS_H_INCLUDED
#define _TPM_TPM2_DEFS_H_INCLUDED

/* sorted headers from this project */
#ifndef _TPM_TPM_DEFS_H_INCLUDED
#include "tpm/tpm_defs.h"
#endif

/* sorted system headers */
#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

/* tpm2_const */
#define TPM2_PLATFORM_PCR                                                                         24
#define TPM2_PCR_SELECT_MIN                                            ((TPM2_PLATFORM_PCR + 7) / 8)
#define TPM2_TIMEOUT_A                                                                           750
#define TPM2_TIMEOUT_B                                                                          2000
#define TPM2_TIMEOUT_C                                                                           200
#define TPM2_TIMEOUT_D                                                                            30
#define TPM2_DURATION_SHORT                                                                       20
#define TPM2_DURATION_MEDIUM                                                                     750
#define TPM2_DURATION_LONG                                                                      2000

#define TPM_DEFAULT_TIMEOUT_A_MAX                        max(TPM_FALLBACK_TIMEOUT_A, TPM2_TIMEOUT_A)
#define TPM_DEFAULT_TIMEOUT_B_MAX                        max(TPM_FALLBACK_TIMEOUT_B, TPM2_TIMEOUT_B)
#define TPM_DEFAULT_TIMEOUT_C_MAX                        max(TPM_FALLBACK_TIMEOUT_C, TPM2_TIMEOUT_C)
#define TPM_DEFAULT_TIMEOUT_D_MAX                        max(TPM_FALLBACK_TIMEOUT_D, TPM2_TIMEOUT_D)

/* tpm2_structures */
#define TPM2_ST_NO_SESSIONS                                                                   0x8001
#define TPM2_ST_SESSIONS                                                                      0x8002

/* tpm2_return_codes */
#define TPM2_RC_HASH                                                                          0x0083 /* RC_FMT1 */
#define TPM2_RC_INITIALIZE                                                                    0x0100 /* RC_VER1 */
#define TPM2_RC_DISABLED                                                                      0x0120
#define TPM2_RC_TESTING                                                                       0x090A /* RC_WARN */

/* tpm2_algorithms */
#define TPM2_ALG_SHA1                                                                         0x0004
#define TPM2_ALG_KEYEDHASH                                                                    0x0008
#define TPM2_ALG_SHA256                                                                       0x000B
#define TPM2_ALG_SHA384                                                                       0x000C
#define TPM2_ALG_SHA512                                                                       0x000D
#define TPM2_ALG_NULL                                                                         0x0010
#define TPM2_ALG_SM3_256                                                                      0x0012

/* tpm2_command_codes */
#define TPM2_CC_FIRST                                                                         0x011F
#define TPM2_CC_SELF_TEST                                                                     0x0143
#define TPM2_CC_STARTUP                                                                       0x0144
#define TPM2_CC_SHUTDOWN                                                                      0x0145
#define TPM2_CC_CREATE                                                                        0x0153
#define TPM2_CC_LOAD                                                                          0x0157
#define TPM2_CC_UNSEAL                                                                        0x015E
#define TPM2_CC_FLUSH_CONTEXT                                                                 0x0165
#define TPM2_CC_GET_CAPABILITY                                                                0x017A
#define TPM2_CC_GET_RANDOM                                                                    0x017B
#define TPM2_CC_PCR_READ                                                                      0x017E
#define TPM2_CC_PCR_EXTEND                                                                    0x0182
#define TPM2_CC_LAST                                                                          0x018F

/* tpm2_permanent_handles */
/* #define TPM2_RS_PW                                                                        0x40000009 */

/* tpm2_capabilities */
#define TPM2_CAP_TPM_PROPERTIES                                                                    6

/* Property tags for TPM2_CAP_TPM_PROPERTIES.  Type uint32_t (TPM_PT) */
#define TPM2_PT_GROUP                                               ((uint32_t)UINT32_C(0x00000100))
#define TPM2_PT_FIXED                                                ((uint32_t)(TPM2_PT_GROUP * 1))
#define TPM2_PT_FAMILY_INDICATOR                                     ((uint32_t)(TPM2_PT_FIXED + 0))

/* tpm2_startup_types */
#define TPM2_SU_CLEAR                                                                         0x0000
#define TPM2_SU_STATE                                                                         0x0001

/* tpm2_object_attributes */
/* #define TPM2_OA_USER_WITH_AUTH                                                                BIT(6) */

/* tpm2_session_attributes */
/* #define TPM2_SA_CONTINUE_SESSION                                                              BIT(0) */

typedef struct tpm2_startup_in_s
{
    uint16_be_t startup_type;
} __attribute__((__packed__)) tpm2_startup_in_t;

typedef struct tpm2_self_test_in_s
{
    uint8_t full_test;
} __attribute__((__packed__)) tpm2_self_test_in_t;

typedef struct tpm2_pcr_read_in_s
{
    uint32_be_t pcr_selects_cnt;
    uint16_be_t hash_alg;
    uint8_t pcr_select_size;
    uint8_t pcr_select[TPM2_PCR_SELECT_MIN];
} __attribute__((__packed__)) tpm2_pcr_read_in_t;

typedef struct tpm2_pcr_read_out_s
{
    uint32_be_t update_cnt;
    uint32_be_t pcr_selects_cnt;
    uint16_be_t hash_alg;
    uint8_t pcr_select_size;
    uint8_t pcr_select[TPM2_PCR_SELECT_MIN];
    uint32_be_t digests_cnt;
    uint16_be_t digest_size;
    uint8_t digest[TPM_DIGEST_SIZE];
} __attribute__((__packed__)) tpm2_pcr_read_out_t;

typedef struct tpm2_null_auth_area_s
{
    uint32_be_t handle;
    uint16_be_t nonce_size;
    uint8_t attributes;
    uint16_be_t auth_size;
} __attribute__((__packed__)) tpm2_null_auth_area_t;

typedef struct tpm2_pcr_extend_in_s
{
    uint32_be_t pcr_idx;
    uint32_be_t auth_area_size;
    tpm2_null_auth_area_t auth_area;
    uint32_be_t digest_cnt;
    uint16_be_t hash_alg;
    uint8_t digest[TPM_DIGEST_SIZE];
} __attribute__((__packed__)) tpm2_pcr_extend_in_t;

typedef struct tpm2_get_tpm_pt_in_s
{
    uint32_be_t cap_id;
    uint32_be_t property_id;
    uint32_be_t property_cnt;
} __attribute__((__packed__)) tpm2_get_tpm_pt_in_t;

typedef struct tpm2_get_tpm_pt_out_s
{
    uint8_t more_data;
    uint32_be_t subcap_id;
    uint32_be_t property_cnt;
    uint32_be_t property_id;
    uint32_be_t value;
} __attribute__((__packed__)) tpm2_get_tpm_pt_out_t;

typedef struct tpm2_get_random_in_s
{
    uint16_be_t size;
} __attribute__((__packed__)) tpm2_get_random_in_t;

typedef struct tpm2_get_random_out_s
{
    uint16_be_t size;
    uint8_t buffer[TPM_MAX_RNG_DATA];
} __attribute__((__packed__)) tpm2_get_random_out_t;

typedef union tpm2_cmd_params_u
{
    tpm2_startup_in_t startup_in;
    tpm2_self_test_in_t selftest_in;
    tpm2_pcr_read_in_t pcrread_in;
    tpm2_pcr_read_out_t pcrread_out;
    tpm2_pcr_extend_in_t pcrextend_in;
    tpm2_get_tpm_pt_in_t get_tpm_pt_in;
    tpm2_get_tpm_pt_out_t get_tpm_pt_out;
    tpm2_get_random_in_t getrandom_in;
    tpm2_get_random_out_t getrandom_out;
} tpm2_cmd_params_ut;

typedef struct tpm2_cmd_s
{
    tpm_cmd_header_ut header;
    tpm2_cmd_params_ut params;
} __attribute__((__packed__)) tpm2_cmd_t;

typedef union tpm_common_cmd_u
{
    tpm_cmd_header_ut header;
    tpm_cmd_t tpm;
    tpm2_cmd_t tpm2;
} tpm_common_cmd_ut;

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _TPM_TPM2_DEFS_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/tpm/public/tpm/tpm2_defs.h $ $Rev: 820218 $")
#endif
