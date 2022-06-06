/*
 * Copyright (c) 2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

/**
 * @file
 * @brief <b>NVIDIA AURIX Interface: Tegra AURIX Communication Protocol Support</b>
 *
 * @b Description: This file declares an interface for TACP support.
 */

#ifndef _TACP_H
#define _TACP_H

/**
 * @defgroup tegra_AURIX_group Tegra AURIX Communication Protocol
 *
 * Describes the supported NVIDIA<sup>&reg;</sup> Tegra<sup>&reg;</sup>
 * AURIX Communication Protocol (TACP).
 * For more information, see [AURIX Setup and Configuration](../aurix_setup.html).
 * @{
 */

/** Defines GMSL camera IDs. */
typedef enum {
    TACP_GMSL_A = 0x01,
    TACP_GMSL_B = 0x02,
    TACP_GMSL_C = 0x04,
    TACP_GMSL_D = 0x08
} tacp_gmsl_id;

/** Defines flags for camera positions. */
typedef enum{
    /* Camera group A */
    TACP_CAM_A0 = 0x01,
    TACP_CAM_A1 = 0x02,
    TACP_CAM_A2 = 0x04,
    TACP_CAM_A3 = 0x08,
    /* Camera group B */
    TACP_CAM_B0 = 0x10,
    TACP_CAM_B1 = 0x20,
    TACP_CAM_B2 = 0x40,
    TACP_CAM_B3 = 0x80,
    /* Camera group C */
    TACP_CAM_C0 = 0x0100,
    TACP_CAM_C1 = 0x0200,
    TACP_CAM_C2 = 0x0400,
    TACP_CAM_C3 = 0x0800,
    /* Camera group D */
    TACP_CAM_D0 = 0x1000,
    TACP_CAM_D1 = 0x2000,
    TACP_CAM_D2 = 0x4000,
    TACP_CAM_D3 = 0x8000
} tacp_cam_id;

/** Defines Tegra positions. */
typedef enum {
    TACP_TEGRA_A = 0x41,
    TACP_TEGRA_B = 0x42
} tacp_tegra_id;

typedef enum {
    TACP_TEGRA = 0x01,
    TACP_MXM
} tacp_hdmi_owner;

/** Defines the fan states. */
typedef enum {
    TACP_FAN_GOOD_STATE = 0x00,
    TACP_FAN_BAD_STATE
} tacp_fan_state;

typedef enum {
    TACP_CAM_MASTER = 0x01,
    TACP_CAM_SLAVE
} tacp_cam_mode;

/** Defines the TACP interface states. */
typedef enum {
    TACP_REQ_FILE_OP_FAIL = -6,
    TACP_REQ_TIMEOUT,
    TACP_REQ_INVALID,
    TACP_REQ_DENIED,
    TACP_REQ_FAILED,
    TACP_REQ_CONNECT_ERR,
    TACP_REQ_ACCEPTED,
} tacp_return_t;

/**
 * Requests to turn on power for the selected camera group(s).
 *
 * @param cam_gmsl Aggregator id from @c tacp_gmsl_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to a connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_cam_pwr_on(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Requests to turn off power for the selected camera group(s).
 *
 * @param cam_gmsl Aggregator id from @c tacp_gmsl_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_cam_pwr_off(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Requests to turn on power to the selected camera unit(s).
 *
 * @param cam_id Aggregator id from @c tacp_cam_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_cam_units_pwr_on(tacp_cam_id cam_id, tacp_cam_mode cam_master);

/**
 * Requests to turn off power for the selected camera unit(s).
 *
 * @param cam_id Aggregator id from @c tacp_cam_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_cam_units_pwr_off(tacp_cam_id cam_id, tacp_cam_mode cam_master);

/**
 * Requests for GMSL ownership.
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_request_gmsl_ownership(void);

/**
 * Requests for FPD-Link ownership.
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_request_fpdl_ownership(void);

/**
 * Sets ownership of the FPD-Link.
 *
 * @param tegra_hdmi id (tegra or mxm) from @c tacp_tegra_id.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_hdmi_owner(tacp_hdmi_owner tegra_hdmi);

/**
 * Requests to set PCIe reset and I2C ownership (plx switch only) of PCIe switch
 * and X550 device.
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_request_pci_ownership(void);

/**
 * Requests to enable Aggregator power.
 *
 * @param cam_gmsl Aggregator id from @c tacp_gmsl_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_aggreg_pwr_on(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Requests to disable Aggregator power.
 *
 * @param cam_gmsl Aggregator id from @c tacp_gmsl_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_aggreg_pwr_off(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Requests to set frsync source ownership.
 *
 * @param tegra_id id(tegra a or tegra b) from @c tacp_tegra_id.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_frsync_owner(tacp_tegra_id tegra_id);

/**
 * Requests to set frsync enable for the selected camera group(s).
 *
 * @param cam_gmsl Aggregator id from @c tegra_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_frsync_enable(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Requests to set frsync disable for the selected camera group(s).
 *
 * @param cam_gmsl Aggregator id from @c tegra_id with bitwise.
 * @param cam_master requested mode of operation from @c tacp_cam_mode.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_DENIED if request is for slave mode.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_set_frsync_disable(tacp_gmsl_id cam_gmsl, tacp_cam_mode cam_master);

/**
 * Reports the current fan state to the remote MCU.
 *
 * @param fan_state tegra current fan sate from @c tacp_fan_state.
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_report_fan_state(tacp_fan_state fan_state);

/**
 * Requests the remote MCU firmware version.
 *
 * @param[in,out] version a pointer to a char array. it contains/returns the
 * firmware version in one byte as per tacp protocol definition. memory allocation for this
 * should be done in client program.
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 */
extern tacp_return_t tacp_get_fw_version(unsigned char *version);

/**
 * Requests to get the camera power status of the camera group(s).
 *
 * @param[in,out] cam_gmsl a pointer to a unsigned char array. it contains/returns the
 * status in bit mask of already powered on camera group(s).
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_get_cam_pwr_status(unsigned char *cam_gmsl);

/**
 * Requests to get the camera power status of the camera unit(s).
 *
 * @param[in,out] cam_id a pointer to a unsigned short int array. it contains/returns the
 * status in bit mask of already powered on camera unit(s).
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_get_cam_unit_pwr_status(unsigned short int *cam_id);

/**
 * Requests to get the camera aggregator power status.
 *
 * @param[in,out] cam_gmsl a pointer to a unsigned char array. it contains/returns the
 * status in bit mask of already powered on aggregator(s).
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_get_aggreg_pwr_status(unsigned char *cam_gmsl);

/**
 * Requests to get the camera `frsync_enable` buffer status.
 *
 * @param[in,out] cam_gmsl a pointer to a unsigned char array. it contains/returns the
 * status in bit mask of already frsync enabled camera group(s).
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_get_frsync_enable_status(unsigned char *cam_gmsl);

/**
 * Sends a ping to the remote MCU.
 *
 * @retval TACP_REQ_ACCEPTED if successful.
 * @retval TACP_REQ_TIMEOUT if timeout happens while receiving response from remote.
 * @retval TACP_REQ_FAILED if request failed due to a remote MCU internal issue.
 * @retval TACP_REQ_CONNECT_ERR if request failed due to connection issue.
 * @retval TACP_REQ_INVALID if invalid request.
 */
extern tacp_return_t tacp_ping(void);

/** @} */
#endif
