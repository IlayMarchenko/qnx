/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems.
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

#ifndef DVFS_API_H
#define DVFS_API_H

/**
 * This structure may be used by applications to register a notification
 * handler
 */
typedef struct {
    int   reql;       // Requested power level by application
    int   capp_chid;  // Channel identifier of the requesting application
    pid_t capp_pid;   // Application's process identifier
} dvfs_data_t;

/**
 * This structure may be used by applications to read back various information
 * from DVFS
 */
typedef struct {
    int cpuload[32];  // CPU loads (if applicable)
    int temperature;  // Core temperature (if applicable)
    int pwrlevl;      // Current power level
    int mode;         // Current DVFS operating point
    int total_pwrlvl; // Total number of DVFS power levels
    int freq;         // Current freq
    int volt;         // Current volt
} dvfs_status_t;

/**
 * Definitions used to notify clients of changes to their desired minimum power level
 */
#define DVFS_NOTIFY_REJECTED          0x20           // Current level has been rejected due to temperature limits
#define DVFS_NOTIFY_RESTORED          0x21           // Previous level has been restored
#define DVFS_NOTIFY_TERMINATED        0x22           // Request has been terminated by driver (switching to manual/semi mode)

/**
 * DEVCTL definitions supported by DVFS resource manager
 */
#define DVFS_DEVCTL_SET_MIN           __DIOT(_DCMD_MISC, 0x100, dvfs_data_t)    // Set minimum operating point
#define DVFS_DEVCTL_UNSET_MIN         __DIOT(_DCMD_MISC, 0x101, dvfs_data_t)    // Unset minimum operating point
#define DVFS_DEVCTL_SET_MODE          __DIOT(_DCMD_MISC, 0x102, dvfs_data_t)    // Set operating mode (auto,semi,manual)
#define DVFS_DEVCTL_SET_PWR_LVL       __DIOT(_DCMD_MISC, 0x103, dvfs_data_t)    // Set power level (for semi/manual)
#define DVFS_DEVCTL_GETSTATUS         __DIOF(_DCMD_MISC, 0x104, dvfs_status_t)  // Read DVFS status
#define DVFS_DEVCTL_RUN_MAX           __DIOT(_DCMD_MISC, 0x105, dvfs_data_t)    // Run at highest possible operating point
#define DVFS_DEVCTL_RUN_MIN           __DIOT(_DCMD_MISC, 0x106, dvfs_data_t)    // Run at lowest possible operating point

/**
 *  DVFS operating modes:
 *   AUTO: DVFS will scale voltage/frequency based on cpu load and temperature
 *   SEMI: User will call voltage/frequency scaling API based on CPU load. DVFS will monitor/react to temperature
 *    MAN: User will call voltage/frequency scaling API based on CPU load and temperature
 */
#define DVFS_MODE_AUTO 0
#define DVFS_MODE_SEMI 1
#define DVFS_MODE_MAN  2
#define DVFS_MODE_MAX  2



#endif /* __DVFS_H__ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/dvfsmgr/public/hw/dvfs_api.h $ $Rev: 761947 $")
#endif
