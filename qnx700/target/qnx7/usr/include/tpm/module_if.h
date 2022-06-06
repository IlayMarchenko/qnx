/*
 * Copyright 2016, QNX Software Systems.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 */

#ifndef _TPM_MODULE_IF_H_INCLUDED
#define _TPM_MODULE_IF_H_INCLUDED

/* sorted headers from this project */
#ifndef _TPM_HELPERS_H_INCLUDED
#include "tpm/helpers.h"
#endif

/* sorted system headers */
#ifndef _STDBOOL_H_INCLUDED
#include <stdbool.h>
#endif

#ifndef _STDINT_H_INCLUDED
#include <stdint.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

/** @cond */
__BEGIN_DECLS
/** @endcond */

#define TPM_MOD_IF_VERSION                                                                         1
#define TPM_MOD_IF_VERSION_MIN                                                                     1

#define TPM_MOD_IF_CORE_SIZE                         (size_t)(sizeof(size_t) + 4 * sizeof(uint32_t))

#define TPM_MOD_IF_MODFLAG_AUTO_STARTUP                                         (uint32_t)0x00000001

#define TPM_MOD_IF_COMMAND_STATE_UNKNOWN                                        (uint32_t)0x00000000
#define TPM_MOD_IF_COMMAND_STATE_COMPLETED                                      (uint32_t)0x00000001
#define TPM_MOD_IF_COMMAND_STATE_CANCELLED                                      (uint32_t)0x00000002

/** TPM module msglog flags */
#define TMLOG_SHUTDOWN                                                                             0
#define TMLOG_CRITICAL                                                                             1
#define TMLOG_ERROR                                                                                2
#define TMLOG_WARNING                                                                              3
#define TMLOG_NOTICE                                                                               4
#define TMLOG_INFO                                                                                 5
#define TMLOG_DEBUG1                                                                               6
#define TMLOG_DEBUG2                                                                               7

/** TPM module io access flags */
#define TPM_MOD_FLAG_PM_ACCESS_NONE                                             (uint32_t)0x00000000
#define TPM_MOD_FLAG_PM_ACCESS_READ                                             (uint32_t)0x00000001
#define TPM_MOD_FLAG_PM_ACCESS_WRITE                                            (uint32_t)0x00000002

typedef struct tpm_module_if_s tpm_module_if_t;
typedef struct tpm_service_s tpm_service_t;
typedef struct tpm_module_s tpm_module_t;
typedef struct tpm_device_s tpm_device_t;
typedef struct tpm_service_private_s tpm_service_private_t;
typedef struct svc_msglog_info_s svc_msglog_info_t;

/* an entry point with the name "tpm_module_if_exchange" is expected to be present
 * in the module DLL, and needs to be of type tpm_module_if_exchange_ft */
typedef int tpm_module_if_exchange_ft(tpm_module_if_t *module_if, void *reserved);

/* pointer version of the function type */
typedef tpm_module_if_exchange_ft * tpm_module_if_exchange_f;

/* declarations of the power management function types */
typedef int tpm_pm_suspend_ft(tpm_module_if_t *module_if);
typedef int tpm_pm_resume_ft(tpm_module_if_t *module_if);
typedef int tpm_pm_set_access_ft(tpm_module_if_t *module_if, uint32_t access_flags);

/* pointer version of the above function types */
typedef tpm_pm_suspend_ft * tpm_pm_suspend_f;
typedef tpm_pm_resume_ft * tpm_pm_resume_f;
typedef tpm_pm_set_access_ft * tpm_pm_set_access_f;

/* declarations of the tpm service supplied function types */
typedef int svc_msglog_ft(tpm_module_if_t *module_if, uint32_t flags, const char *format, ...) __attribute__((format (__printf__, 3, 4)));
typedef int svc_msglog_ex_ft(svc_msglog_info_t *msglog_info, const char *format, ...) __attribute__((format (__printf__, 2, 3)));

typedef uint32_t svc_tpm_get_retcode_ft(void);
typedef void svc_tpm_set_retcode_ft(uint32_t retcode);
typedef int svc_tpm_get_timeouts_ft(tpm_module_if_t *module_if);
typedef int svc_tpm_wait_for_stat_ft(tpm_module_if_t *module_if, uint8_t mask, uint64_t timeout_ns, bool check_cancelled);
typedef int svc_tpm_chip_register_ft(tpm_module_if_t *module_if);
typedef int svc_tpm_chip_unregister_ft(tpm_module_if_t *module_if);
typedef int svc_tpm_gen_interrupt_ft(tpm_module_if_t *module_if);
typedef uint64_t svc_tpm_calc_ordinal_duration_ft(tpm_module_if_t *module_if, uint32_t ordinal);
typedef int svc_tpm_do_selftest_ft(tpm_module_if_t *module_if);

typedef int svc_tpm2_gen_interrupt_ft(tpm_module_if_t *module_if);
typedef int svc_tpm2_probe_ft(tpm_module_if_t *module_if);
typedef uint64_t svc_tpm2_calc_ordinal_duration_ft(tpm_module_if_t *module_if, uint32_t ordinal);
typedef int svc_tpm2_do_selftest_ft(tpm_module_if_t *module_if);

/* pointer version of the above function types */
typedef svc_msglog_ft * svc_msglog_f;
typedef svc_msglog_ex_ft * svc_msglog_ex_f;

typedef svc_tpm_get_retcode_ft * svc_tpm_get_retcode_f;
typedef svc_tpm_set_retcode_ft * svc_tpm_set_retcode_f;
typedef svc_tpm_get_timeouts_ft * svc_tpm_get_timeouts_f;
typedef svc_tpm_wait_for_stat_ft * svc_tpm_wait_for_stat_f;
typedef svc_tpm_chip_register_ft * svc_tpm_chip_register_f;
typedef svc_tpm_chip_unregister_ft * svc_tpm_chip_unregister_f;
typedef svc_tpm_gen_interrupt_ft * svc_tpm_gen_interrupt_f;
typedef svc_tpm_calc_ordinal_duration_ft * svc_tpm_calc_ordinal_duration_f;
typedef svc_tpm_do_selftest_ft * svc_tpm_do_selftest_f;

typedef svc_tpm2_gen_interrupt_ft * svc_tpm2_gen_interrupt_f;
typedef svc_tpm2_probe_ft * svc_tpm2_probe_f;
typedef svc_tpm2_calc_ordinal_duration_ft * svc_tpm2_calc_ordinal_duration_f;
typedef svc_tpm2_do_selftest_ft * svc_tpm2_do_selftest_f;

/* declarations of the HW module supplied function types */
typedef int tpm_mod_init_ft(tpm_module_if_t *module_if);
typedef int tpm_mod_fini_ft(tpm_module_if_t *module_if);
typedef int tpm_mod_response_receive_ft(tpm_module_if_t *module_if, uint8_t *buf, size_t *read_size);
typedef int tpm_mod_command_send_ft(tpm_module_if_t *module_if, const uint8_t *buf, size_t *write_size);
typedef int tpm_mod_command_cancel_ft(tpm_module_if_t *module_if);
typedef int tpm_mod_command_get_cancelled_status_ft(tpm_module_if_t *module_if, uint8_t status, bool *cancelled);
typedef int tpm_mod_command_get_completed_status_ft(tpm_module_if_t *module_if, uint8_t status, bool *completed);
typedef int tpm_mod_adjust_timeouts_ft(tpm_module_if_t *module_if);
typedef int tpm_mod_get_status_ft(tpm_module_if_t *module_if, uint8_t *status);

/* pointer version of the above function types */
typedef tpm_mod_init_ft * tpm_mod_init_f;
typedef tpm_mod_fini_ft * tpm_mod_fini_f;
typedef tpm_mod_response_receive_ft * tpm_mod_response_receive_f;
typedef tpm_mod_command_send_ft * tpm_mod_command_send_f;
typedef tpm_mod_command_cancel_ft * tpm_mod_command_cancel_f;
typedef tpm_mod_command_get_cancelled_status_ft * tpm_mod_command_get_cancelled_status_f;
typedef tpm_mod_command_get_completed_status_ft * tpm_mod_command_get_completed_status_f;
typedef tpm_mod_adjust_timeouts_ft * tpm_mod_adjust_timeouts_f;
typedef tpm_mod_get_status_ft * tpm_mod_get_status_f;

struct tpm_module_if_s
{
    /** The size of this structure.  Filled in by the tpm service. */
    size_t size;

    /** The tpm module interface version the tpm service is using. */
    uint32_t svc_if_version_used;
    /** The lowest compatible tpm module interface version the service can use. */
    uint32_t svc_if_version_min;
    /** The tpm module interface version the module is using. */
    uint32_t mod_if_version_used;
    /** The lowest compatible tpm module interface version the module can use. */
    uint32_t mod_if_version_min;

    /**
     * All attributes above this point are guaranteed to be in all versions and anything that
     * follows is subject to be incompatible based on version information above.
     * TPM_MOD_IF_CORE_SIZE is the size of the structure up to this point, and this define does not
     * change from version to version.
     */

    /** Service information filled in by the tpm service. */
    const tpm_service_t *svc;
    /** Module information */
    tpm_module_t *mod;
    /** Device information */
    tpm_device_t *dev;

    /** Private data of the tpm module.  For exclusive use by the tpm module. */
    void *mod_priv;
    /** Private data of the tpm service.  For exclusive use by the tpm service. */
    tpm_service_private_t *svc_priv;

    /* All versions of this structure need to keep the above information as is, and in the same
     * order, and expansion of the structure is done from this point.  Updating this structure
     * requires the TPM_MOD_IF_VERSION to be updated. */
};

/* Information structure filled in by the tpm service. */
struct tpm_service_s
{
    /** The size of this structure.  Filled in by the tpm service. */
    size_t size;

    uint64_t reserved;

    /** Functions implemented by the service, made available to the module. */
    helpers_get_monotonic_time_f get_monotonic_time;
    helpers_nssleep_f nssleep;
    helpers_poll_until_f poll_until;

    svc_msglog_f msglog;
    svc_msglog_ex_f msglog_ex;

    svc_tpm_get_retcode_f tpm_get_retcode;
    svc_tpm_set_retcode_f tpm_set_retcode;
    svc_tpm_get_timeouts_f tpm_get_timeouts;
    svc_tpm_wait_for_stat_f tpm_wait_for_stat;
    svc_tpm_chip_register_f tpm_chip_register;
    svc_tpm_chip_unregister_f tpm_chip_unregister;
    svc_tpm_gen_interrupt_f tpm_gen_interrupt;
    svc_tpm_calc_ordinal_duration_f tpm_calc_ordinal_duration;
    svc_tpm_do_selftest_f tpm_do_selftest;

    svc_tpm2_gen_interrupt_f tpm2_gen_interrupt;
    svc_tpm2_probe_f tpm2_probe;
    svc_tpm2_calc_ordinal_duration_f tpm2_calc_ordinal_duration;
    svc_tpm2_do_selftest_f tpm2_do_selftest;

    tpm_pm_suspend_f pm_suspend;
    tpm_pm_resume_f pm_resume;

    /* All versions of this structure need to keep the above information as is, and in the same
     * order, and expansion of the structure is done from this point.  Updating this structure
     * requires the TPM_MOD_IF_VERSION to be updated. */
};

/* Information structure filled in by the device module (except where indicated). */
struct tpm_module_s
{
    /** The size of this structure.  Filled in by the tpm service. */
    size_t size;

    /** The null-terminated device module name. */
    char mod_name[32];
    /** The null-terminated hw module version. */
    char version[32];

    /** flags that relate to the tpm module. */
    uint32_t flags;

    uint64_t reserved;

    /** Functions implemented by the module. */
    tpm_mod_init_f init;
    tpm_mod_fini_f fini;
    tpm_mod_response_receive_f response_receive;
    tpm_mod_command_send_f command_send;
    tpm_mod_command_cancel_f command_cancel;
    tpm_mod_command_get_cancelled_status_f command_get_cancelled_status;
    tpm_mod_command_get_completed_status_f command_get_completed_status;
    tpm_mod_get_status_f get_status;
    tpm_mod_adjust_timeouts_f adjust_timeouts;

    tpm_pm_set_access_f pm_set_access;
    tpm_pm_suspend_f pm_suspend;
    tpm_pm_resume_f pm_resume;

    /* All versions of this structure need to keep the above information as is, and in the same
     * order, and expansion of the structure is done from this point.  Updating this structure
     * requires the TPM_MOD_IF_VERSION to be updated.  Reserved fields' values should never be
     * changed by the module, and could be renamed in later versions. */
};

struct tpm_device_s
{
    /** The size of this structure.  Filled in by the tpm service. */
    size_t size;

    uint64_t timeout_a_ns;
    uint64_t timeout_b_ns;
    uint64_t timeout_c_ns;
    uint64_t timeout_d_ns;

    bool timeout_adjusted;

    uint64_t polling_time_ns;

    uint32_t flags;

    uint64_t duration_ns[3];

    size_t tpm_buffer_size;

    /* All versions of this structure need to keep the above information as is, and in the same
     * order, and expansion of the structure is done from this point.  Updating this structure
     * requires the TPM_MOD_IF_VERSION to be updated. */
};

struct svc_msglog_info_s
{
    tpm_module_if_t *module_if;
    const uint32_t flags;
    const char* filename;
    const char* function;
    const uint32_t line;
};

/** @cond */
__END_DECLS
/** @endcond */

#endif /* _TPM_MODULE_IF_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/services/tpm/public/tpm/module_if.h $ $Rev: 820218 $")
#endif
