#ifndef _QWDI_MSG_H
#define _QWDI_MSG_H

/*
 * QNX WLAN DRIVER INTEGRATION (QWDI) public header file
 *
 * $QNXLicenseC:
 * Copyright 2015, QNX Software Systems. All Rights Reserved.
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
 *
 * The interface names and definitions in this file are based on the following:
 *
 * WPA Supplicant
 * ==============
 * Copyright (c) 2003-2015, Jouni Malinen <j@w1.fi> and contributors
 * All Rights Reserved.
 *
 * This program is licensed under the BSD license (the one with
 * advertisement clause removed).
 *
 * If you are submitting changes to the project, please see CONTRIBUTIONS
 * file for more instructions.
 *
 * License
 * -------
 *
 * This software may be distributed, used, and modified under the terms of
 * BSD license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name(s) of the above-listed copyright holder(s) nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define QWDI_VERSION 0x0205

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define QWDI_RET_SUCCESS           0x00
#define QWDI_RET_ERR_GENERAL       0x01
#define QWDI_RET_ERR_INVALID_PARAM 0x02
#define QWDI_RET_ERR_UNHANDLED_CMD 0x03

#define QWDI_IFNAMSIZ 15

#define QWDI_NETIF_NAME(DEVNAME) DEVNAME"0"

#define QWDI_MAX_SCAN_SSID 16
#define QWDI_MAX_SCAN_FREQ 38
#define QWDI_MAX_EXTRA_IES_LEN 512
#define QWDI_MAX_SSID_STR_LEN 32
#define QWDI_MAX_RESPONSE_SIZE 4000
#define QWDI_MAX_SEQ_LEN  8
#define QWDI_MAX_KEY_LEN  32
#define QWDI_MAX_NOA_LEN  64
#define QWDI_MAX_COUNTRY_LEN 4
#define QWDI_MAX_HEAD_BUFF_LEN 256
#define QWDI_MAX_TAIL_BUFF_LEN 512
#define QWDI_MAX_PROBE_RESP_LEN 768
#define QWDI_MAX_SUPPORT_RATES 12
#define QWDI_MAX_MGMT_FRAME_LEN 1800
#define QWDI_MAX_SUPPORT_MCS 16
#define QWDI_MAX_CHANNEL_NUM 50

#define QWDI_PMKID_LEN  16

#define QWDI_ETH_ALEN 6

/*from driver.h*/
#define QWDI_IEEE80211_MODE_INFRA   0
#define QWDI_IEEE80211_MODE_IBSS    1
#define QWDI_IEEE80211_MODE_AP      2
#define QWDI_IEEE80211_MODE_MESH	5

#define QWDI_IEEE80211_CAP_ESS  0x0001
#define QWDI_IEEE80211_CAP_IBSS 0x0002
#define QWDI_IEEE80211_CAP_PRIVACY  0x0010
#define QWDI_IEEE80211_CAP_RRM	0x1000

#define QWDI_WPA_CIPHER_NONE BIT(0)
#define QWDI_WPA_CIPHER_WEP40 BIT(1)
#define QWDI_WPA_CIPHER_WEP104 BIT(2)
#define QWDI_WPA_CIPHER_TKIP BIT(3)
#define QWDI_WPA_CIPHER_CCMP BIT(4)
#define QWDI_WPA_CIPHER_AES_128_CMAC BIT(5)
#define QWDI_WPA_CIPHER_GCMP BIT(6)
#define QWDI_WPA_CIPHER_SMS4 BIT(7)
#define QWDI_WPA_CIPHER_GCMP_256 BIT(8)
#define QWDI_WPA_CIPHER_CCMP_256 BIT(9)
#define QWDI_WPA_CIPHER_BIP_GMAC_128 BIT(11)
#define QWDI_WPA_CIPHER_BIP_GMAC_256 BIT(12)
#define QWDI_WPA_CIPHER_BIP_CMAC_256 BIT(13)
#define QWDI_WPA_CIPHER_GTK_NOT_USED BIT(14)

enum {
    QWDI_WPS_MODE_NONE /* no WPS provisioning being used */,
    QWDI_WPS_MODE_OPEN /* WPS provisioning with AP that is in open mode */,
    QWDI_WPS_MODE_PRIVACY /* WPS provisioning with AP that is using protection            */
};

/*from defs.h*/
#define QWDI_WPA_AUTH_ALG_OPEN      (1 << 0)
#define QWDI_WPA_AUTH_ALG_SHARED    (1 << 1)
#define QWDI_WPA_AUTH_ALG_LEAP      (1 << 2)
#define QWDI_WPA_AUTH_ALG_FT        (1 << 3)
#define QWDI_WPA_AUTH_ALG_SAE       (1 << 4)

#define QWDI_WPA_PROTO_WPA BIT(0)
#define QWDI_WPA_PROTO_RSN BIT(1)
#define QWDI_WPA_PROTO_WAPI BIT(2)
#define QWDI_WPA_PROTO_OSEN BIT(3)

#define QWDI_WPA_KEY_MGMT_IEEE8021X BIT(0)
#define QWDI_WPA_KEY_MGMT_PSK BIT(1)
#define QWDI_WPA_KEY_MGMT_NONE BIT(2)
#define QWDI_WPA_KEY_MGMT_IEEE8021X_NO_WPA BIT(3)
#define QWDI_WPA_KEY_MGMT_WPA_NONE BIT(4)
#define QWDI_WPA_KEY_MGMT_FT_IEEE8021X BIT(5)
#define QWDI_WPA_KEY_MGMT_FT_PSK BIT(6)
#define QWDI_WPA_KEY_MGMT_IEEE8021X_SHA256 BIT(7)
#define QWDI_WPA_KEY_MGMT_PSK_SHA256 BIT(8)
#define QWDI_WPA_KEY_MGMT_WPS BIT(9)
#define QWDI_WPA_KEY_MGMT_SAE BIT(10)
#define QWDI_WPA_KEY_MGMT_FT_SAE BIT(11)
#define QWDI_WPA_KEY_MGMT_WAPI_PSK BIT(12)
#define QWDI_WPA_KEY_MGMT_WAPI_CERT BIT(13)
#define QWDI_WPA_KEY_MGMT_CCKM BIT(14)
#define QWDI_WPA_KEY_MGMT_OSEN BIT(15)
#define QWDI_WPA_KEY_MGMT_IEEE8021X_SUITE_B BIT(16)
#define QWDI_WPA_KEY_MGMT_IEEE8021X_SUITE_B_192 BIT(17)


/*From ieee802_11_defs.h */
#define QWDI_WLAN_EID_RSN 48

/* HT Capabilities Info field within HT Capabilities element */
#define QWDI_HT_CAP_INFO_LDPC_CODING_CAP        ((unsigned short) BIT(0))
#define QWDI_HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ((unsigned short) BIT(1))
#define QWDI_HT_CAP_INFO_SMPS_MASK              ((unsigned short) (BIT(2) | BIT(3)))
#define QWDI_HT_CAP_INFO_SMPS_STATIC            ((unsigned short) 0)
#define QWDI_HT_CAP_INFO_SMPS_DYNAMIC           ((unsigned short) BIT(2))
#define QWDI_HT_CAP_INFO_SMPS_DISABLED          ((unsigned short) (BIT(2) | BIT(3)))
#define QWDI_HT_CAP_INFO_GREEN_FIELD            ((unsigned short) BIT(4))
#define QWDI_HT_CAP_INFO_SHORT_GI20MHZ          ((unsigned short) BIT(5))
#define QWDI_HT_CAP_INFO_SHORT_GI40MHZ          ((unsigned short) BIT(6))
#define QWDI_HT_CAP_INFO_TX_STBC                ((unsigned short) BIT(7))
#define QWDI_HT_CAP_INFO_RX_STBC_MASK           ((unsigned short) (BIT(8) | BIT(9)))
#define QWDI_HT_CAP_INFO_RX_STBC_1              ((unsigned short) BIT(8))
#define QWDI_HT_CAP_INFO_RX_STBC_12             ((unsigned short) BIT(9))
#define QWDI_HT_CAP_INFO_RX_STBC_123            ((unsigned short) (BIT(8) | BIT(9)))
#define QWDI_HT_CAP_INFO_DELAYED_BA             ((unsigned short) BIT(10))
#define QWDI_HT_CAP_INFO_MAX_AMSDU_SIZE         ((unsigned short) BIT(11))
#define QWDI_HT_CAP_INFO_DSSS_CCK40MHZ          ((unsigned short) BIT(12))
/* B13 - Reserved (was PSMP support during P802.11n development) */
#define QWDI_HT_CAP_INFO_40MHZ_INTOLERANT       ((unsigned short) BIT(14))
#define QWDI_HT_CAP_INFO_LSIG_TXOP_PROTECT_SUPPORT  ((unsigned short) BIT(15))

/* VHT Capability Defines */
#define QWDI_VHT_CAP_SHORT_GI_80                ((unsigned int) BIT(5))
#define QWDI_VHT_CAP_SHORT_GI_160               ((unsigned int) BIT(6))

/* HT Capabilities element */
struct qwdi_ieee80211_ht_cap {
    unsigned short ht_capabilities_info; /* little endian */
    unsigned char  a_mpdu_params;
    unsigned char  supported_mcs_set[16];
    unsigned short ht_extended_capabilities; /* little endian */
    unsigned int   tx_bf_capability_info; /* little endian */
    unsigned char  asel_capabilities;
} __attribute__ ((packed));

struct qwdi_ieee80211_vht_cap {
    unsigned int vht_capabilities_info;/* little endian */
    struct {
        unsigned short rx_map; /*little endian */
        unsigned short rx_highest;/*little endian */
        unsigned short tx_map;/*little endian */
        unsigned short tx_highest;/*little endian */
    } vht_supported_mcs_set;
} __attribute__ ((packed));

#define QWDI_WLAN_FC_TYPE_MGMT      0
#define QWDI_WLAN_FC_TYPE_CTRL      1
#define QWDI_WLAN_FC_TYPE_DATA      2

#define QWDI_WLAN_FC_STYPE_ACTION       13


/*From ap_config.h */
#define QWDI_NUM_WEP_KEYS 4

/*ToDo defined in WPA_2_1, remove it if no use in WPA_2_5*/
#define QWDI_WPA_BAND_SELECT_DUAL_BAND 0
#define QWDI_WPA_BAND_SELECT_2_4G_ONLY 1
#define QWDI_WPA_BAND_SELECT_5G_ONLY 2

#define QWDI_SCANTYPE_ACTIVE            0   /* d11 scan active */
#define QWDI_SCANTYPE_PASSIVE           1   /* d11 scan passive */

#define QWDI_SCAN_REQ_GUI_SCAN 2
#define QWDI_SCAN_REQ_APP_SCAN 3

/**
 * struct qwdi_driver_capa - Driver capability information
 * modified from driver.h
 */
struct qwdi_driver_capa {
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WPA         0x00000001
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WPA2        0x00000002
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WPA_PSK     0x00000004
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WPA2_PSK    0x00000008
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WPA_NONE    0x00000010
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_FT          0x00000020
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_FT_PSK      0x00000040
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_WAPI_PSK    0x00000080
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B     0x00000100
#define QWDI_WPA_DRIVER_CAPA_KEY_MGMT_SUITE_B_192 0x00000200

    unsigned int key_mgmt;

#define QWDI_WPA_DRIVER_CAPA_ENC_WEP40          0x00000001
#define QWDI_WPA_DRIVER_CAPA_ENC_WEP104         0x00000002
#define QWDI_WPA_DRIVER_CAPA_ENC_TKIP           0x00000004
#define QWDI_WPA_DRIVER_CAPA_ENC_CCMP           0x00000008
#define QWDI_WPA_DRIVER_CAPA_ENC_WEP128         0x00000010
#define QWDI_WPA_DRIVER_CAPA_ENC_GCMP           0x00000020
#define QWDI_WPA_DRIVER_CAPA_ENC_GCMP_256       0x00000040
#define QWDI_WPA_DRIVER_CAPA_ENC_CCMP_256       0x00000080
#define QWDI_WPA_DRIVER_CAPA_ENC_BIP            0x00000100
#define QWDI_WPA_DRIVER_CAPA_ENC_BIP_GMAC_128   0x00000200
#define QWDI_WPA_DRIVER_CAPA_ENC_BIP_GMAC_256   0x00000400
#define QWDI_WPA_DRIVER_CAPA_ENC_BIP_CMAC_256   0x00000800
#define QWDI_WPA_DRIVER_CAPA_ENC_GTK_NOT_USED   0x00001000

    unsigned int enc;

#define QWDI_WPA_DRIVER_AUTH_OPEN       0x00000001
#define QWDI_WPA_DRIVER_AUTH_SHARED     0x00000002
#define QWDI_WPA_DRIVER_AUTH_LEAP       0x00000004
    unsigned int auth;

/* Driver generated WPA/RSN IE */
#define QWDI_WPA_DRIVER_FLAGS_DRIVER_IE                 0x00000001
/* Driver needs static WEP key setup after association command */
#define QWDI_WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC      0x00000002
/* Driver takes care of all DFS operations */
#define QWDI_WPA_DRIVER_FLAGS_DFS_OFFLOAD               0x00000004
/* Driver takes care of RSN 4-way handshake internally; PMK is configured with
 * struct wpa_driver_ops::set_key using alg = WPA_ALG_PMK */
#define QWDI_WPA_DRIVER_FLAGS_4WAY_HANDSHAKE            0x00000008
#define QWDI_WPA_DRIVER_FLAGS_WIRED                     0x00000010
/* Driver provides separate commands for authentication and association (SME in
 * wpa_supplicant). */
#define QWDI_WPA_DRIVER_FLAGS_SME                       0x00000020
/* Driver supports AP mode */
#define QWDI_WPA_DRIVER_FLAGS_AP                        0x00000040
/* Driver needs static WEP key setup after association has been completed */
#define QWDI_WPA_DRIVER_FLAGS_SET_KEYS_AFTER_ASSOC_DONE 0x00000080
/* Driver supports dynamic HT 20/40 MHz channel changes during BSS lifetime */
#define WPA_DRIVER_FLAGS_HT_2040_COEX                   0x00000100
/* Driver supports concurrent P2P operations */
#define QWDI_WPA_DRIVER_FLAGS_P2P_CONCURRENT            0x00000200
/*
 * Driver uses the initial interface as a dedicated management interface, i.e.,
 * it cannot be used for P2P group operations or non-P2P purposes.
 */
#define QWDI_WPA_DRIVER_FLAGS_P2P_DEDICATED_INTERFACE   0x00000400
/* This interface is P2P capable (P2P GO or P2P Client) */
#define QWDI_WPA_DRIVER_FLAGS_P2P_CAPABLE               0x00000800
/* Driver supports station and key removal when stopping an AP */
#define QWDI_WPA_DRIVER_FLAGS_AP_TEARDOWN_SUPPORT       0x00001000
/*
 * Driver uses the initial interface for P2P management interface and non-P2P
 * purposes (e.g., connect to infra AP), but this interface cannot be used for
 * P2P group operations.
 */
#define QWDI_WPA_DRIVER_FLAGS_P2P_MGMT_AND_NON_P2P      0x00002000
/*
 * Driver is known to use sane error codes, i.e., when it indicates that
 * something (e.g., association) fails, there was indeed a failure and the
 * operation does not end up getting completed successfully later.
 */
#define QWDI_WPA_DRIVER_FLAGS_SANE_ERROR_CODES          0x00004000
/* Driver supports off-channel TX */
#define QWDI_WPA_DRIVER_FLAGS_OFFCHANNEL_TX             0x00008000
/* Driver indicates TX status events for EAPOL Data frames */
#define QWDI_WPA_DRIVER_FLAGS_EAPOL_TX_STATUS           0x00010000
/* Driver indicates TX status events for Deauth/Disassoc frames */
#define QWDI_WPA_DRIVER_FLAGS_DEAUTH_TX_STATUS          0x00020000
/* Driver supports roaming (BSS selection) in firmware */
#define QWDI_WPA_DRIVER_FLAGS_BSS_SELECTION             0x00040000
/* Driver supports operating as a TDLS peer */
#define QWDI_WPA_DRIVER_FLAGS_TDLS_SUPPORT              0x00080000
/* Driver requires external TDLS setup/teardown/discovery */
#define QWDI_WPA_DRIVER_FLAGS_TDLS_EXTERNAL_SETUP       0x00100000
/* Driver indicates support for Probe Response offloading in AP mode */
#define QWDI_WPA_DRIVER_FLAGS_PROBE_RESP_OFFLOAD        0x00200000
/* Driver supports U-APSD in AP mode */
#define QWDI_WPA_DRIVER_FLAGS_AP_UAPSD                  0x00400000
/* Driver supports inactivity timer in AP mode */
#define QWDI_WPA_DRIVER_FLAGS_INACTIVITY_TIMER          0x00800000
/* Driver expects user space implementation of MLME in AP mode */
#define QWDI_WPA_DRIVER_FLAGS_AP_MLME                   0x01000000
/* Driver supports SAE with user space SME */
#define QWDI_WPA_DRIVER_FLAGS_SAE                       0x02000000
/* Driver makes use of OBSS scan mechanism in wpa_supplicant */
#define QWDI_WPA_DRIVER_FLAGS_OBSS_SCAN                 0x04000000

/* Driver supports IBSS (Ad-hoc) mode */
#define QWDI_WPA_DRIVER_FLAGS_IBSS                      0x08000000
/* Driver supports radar detection */
#define QWDI_WPA_DRIVER_FLAGS_RADAR                     0x10000000
/* Driver supports a dedicated interface for P2P Device */
#define QWDI_WPA_DRIVER_FLAGS_DEDICATED_P2P_DEVICE      0x20000000
/* Driver supports QoS Mapping */
#define QWDI_WPA_DRIVER_FLAGS_QOS_MAPPING               0x40000000
/* Driver supports CSA in AP mode */
#define QWDI_WPA_DRIVER_FLAGS_AP_CSA                    0x80000000
/* Driver supports mesh */
#define WPA_DRIVER_FLAGS_MESH                   0x0000000100000000ULL
/* Driver support ACS offload */
#define WPA_DRIVER_FLAGS_ACS_OFFLOAD            0x0000000200000000ULL
/* Driver supports key management offload */
#define WPA_DRIVER_FLAGS_KEY_MGMT_OFFLOAD       0x0000000400000000ULL
/* Driver supports TDLS channel switching */
#define WPA_DRIVER_FLAGS_TDLS_CHANNEL_SWITCH    0x0000000800000000ULL
/* Driver supports IBSS with HT datarates */
#define WPA_DRIVER_FLAGS_HT_IBSS                0x0000001000000000ULL
/* Driver supports IBSS with VHT datarates */
#define WPA_DRIVER_FLAGS_VHT_IBSS               0x0000002000000000ULL
/* Driver supports automatic band selection */
#define WPA_DRIVER_FLAGS_SUPPORT_HW_MODE_ANY    0x0000004000000000ULL

#ifdef __QNXNTO__ /* PR 281605 */
#define QWDI_WPA_DRIVER_FLAGS_MASK              0xFFFFFFFFFFFFFFFFULL
    /**
     * Indicates that the driver should perform the FT 4-way handshake
     * internally; PMK is configured with struct wpa_driver_ops::set_key
     * using alg = WPA_ALG_PMK. This is used in conjunction with
     * WPA_DRIVER_FLAGS_4WAY_HANDSHAKE since it's a special case on
     * top of that capability.
     */
#define QWDI_WPA_DRIVER_FLAGS_FT_4WAY_HANDSHAKE         0x01000000
#endif

    unsigned long long flags;

#define QWDI_WPA_DRIVER_SMPS_MODE_STATIC             0x00000001
#define QWDI_WPA_DRIVER_SMPS_MODE_DYNAMIC            0x00000002
    unsigned int smps_modes;
    unsigned int wmm_ac_supported:1;
    unsigned int mac_addr_rand_scan_supported:1;
    unsigned int mac_addr_rand_sched_scan_supported:1;
    /* Maximum number of supported active probe SSIDs */
    int max_scan_ssids;
    /* Maximum number of supported active probe SSIDs for sched_scan */
    int max_sched_scan_ssids;
    /* Whether sched_scan (offloaded scanning) is supported */
    int sched_scan_supported;
    /* Maximum number of supported match sets for sched_scan */
    int max_match_sets;

    /**
        * max_remain_on_chan - Maximum remain-on-channel duration in msec
        */
    unsigned int max_remain_on_chan;

    /**
        * max_stations - Maximum number of associated stations the driver
        * supports in AP mode
        */
    unsigned int max_stations;

    /**
     * probe_resp_offloads - Bitmap of supported protocols by the driver
     * for Probe Response offloading.
     */
/* Driver Probe Response offloading support for WPS ver. 1 */
#define QWDI_WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS      0x00000001
/* Driver Probe Response offloading support for WPS ver. 2 */
#define QWDI_WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS2     0x00000002
/* Driver Probe Response offloading support for P2P */
#define QWDI_WPA_DRIVER_PROBE_RESP_OFFLOAD_P2P      0x00000004
/* Driver Probe Response offloading support for IEEE 802.11u (Interworking) */
#define QWDI_WPA_DRIVER_PROBE_RESP_OFFLOAD_INTERWORKING 0x00000008
    unsigned int probe_resp_offloads;

    unsigned int max_acl_mac_addrs;

    /**
         * Number of supported concurrent channels
         */
    unsigned int num_multichan_concurrent;

    /**
         * extended_capa - extended capabilities in driver/device
         *
         * Must be allocated and freed by driver and the pointers must be
         * valid for the lifetime of the driver, i.e., freed in deinit()
         */
    const unsigned char *extended_capa, *extended_capa_mask;
    unsigned int extended_capa_len;

    struct qwdi_wowlan_triggers {
        unsigned char any;
        unsigned char disconnect;
        unsigned char magic_pkt;
        unsigned char gtk_rekey_failure;
        unsigned char eap_identity_req;
        unsigned char four_way_handshake;
        unsigned char rfkill_release;
    } wowlan_triggers;
/* Driver adds the DS Params Set IE in Probe Request frames */
#define QWDI_WPA_DRIVER_FLAGS_DS_PARAM_SET_IE_IN_PROBES 0x00000001
/* Driver adds the WFA TPC IE in Probe Request frames */
#define QWDI_WPA_DRIVER_FLAGS_WFA_TPC_IE_IN_PROBES      0x00000002
/* Driver handles quiet period requests */
#define QWDI_WPA_DRIVER_FLAGS_QUIET                     0x00000004
  /**
     * Driver is capable of inserting the current TX power value into the body of
     * transmitted frames.
     * Background: Some Action frames include a TPC Report IE. This IE contains a
     * TX power field, which has to be updated by lower layers. One such Action
     * frame is Link Measurement Report (part of RRM). Another is TPC Report (part
     * of spectrum management). Note that this insertion takes place at a fixed
     * offset, namely the 6th byte in the Action frame body.
     */
#define QWDI_WPA_DRIVER_FLAGS_TX_POWER_INSERTION        0x00000008
    unsigned int rrm_flags;

    /* Driver concurrency capabilities */
    unsigned int conc_capab;
    /* Maximum number of concurrent channels on 2.4 GHz */
    unsigned int max_conc_chan_2_4;
    /* Maximum number of concurrent channels on 5 GHz */
    unsigned int max_conc_chan_5_0;
};

/* p2p state */
#define QWDI_P2P_DISC_ST_SCAN   0
#define QWDI_P2P_DISC_ST_LISTEN 1
#define QWDI_P2P_DISC_ST_SEARCH 2

/* QWDI command definitions */
enum qwdi_commands {
    QWDI_CMD_NONE,
    QWDI_CMD_GET_BSSID,
    QWDI_CMD_GET_SSID,
    QWDI_CMD_SET_KEY,
    QWDI_CMD_INIT,
    QWDI_CMD_DEINIT,
    QWDI_CMD_SET_PARAM,
    QWDI_CMD_SET_COUNTERMEASURES,
    QWDI_CMD_DEAUTHENTICATE,
    QWDI_CMD_ASSOCIATE,
    QWDI_CMD_ADD_PMKID,
    QWDI_CMD_REMOVE_PMKID,
    QWDI_CMD_FLUSH_PMKID,
    QWDI_CMD_GET_CAPA,
    QWDI_CMD_POLL,
    QWDI_CMD_GET_IFNAME,
    QWDI_CMD_GET_MAC_ADDR,
    QWDI_CMD_SEND_EAPOL,
    QWDI_CMD_SET_OPERSTATE,
    QWDI_CMD_MLME_SETPROTECTION,
    QWDI_CMD_GET_HW_FEATURE_DATA,
    QWDI_CMD_SEND_MLME,
    QWDI_CMD_UPDATE_FT_IES,
    QWDI_CMD_SEND_FT_ACTION,
    QWDI_CMD_GET_SCAN_RESULTS,
    QWDI_CMD_SET_COUNTRY,
    QWDI_CMD_GLOBAL_INIT,
    QWDI_CMD_GLOBAL_DEINIT,
    QWDI_CMD_INIT2,
    QWDI_CMD_GET_INTERFACES,
    QWDI_CMD_SCAN2,
    QWDI_CMD_SCHED_SCAN,
    QWDI_CMD_STOP_SCHED_SCAN,
    QWDI_CMD_AUTHENTICATE,
    QWDI_CMD_SET_AP,
    QWDI_CMD_HAPD_INIT,
    QWDI_CMD_HAPD_DEINIT,
    QWDI_CMD_SET_IEEE8021X,
    QWDI_CMD_SET_PRIVACY,
    QWDI_CMD_GET_SEQNUM,
    QWDI_CMD_FLUSH,
    QWDI_CMD_SET_GENERIC_ELEM,
    QWDI_CMD_READ_STA_DATA,
    QWDI_CMD_HAPD_SEND_EAPOL,
    QWDI_CMD_STA_DEAUTH,
    QWDI_CMD_STA_DISASSOC,
    QWDI_CMD_STA_REMOVE,
    QWDI_CMD_HAPD_GET_SSID,
    QWDI_CMD_HAPD_SET_SSID,
    QWDI_CMD_HAPD_SET_COUNTERMEASURES,
    QWDI_CMD_STA_ADD,
    QWDI_CMD_GET_INACT_SEC,
    QWDI_CMD_STA_CLEAR_STATS,
    QWDI_CMD_SET_FREQ,
    QWDI_CMD_SET_RTS,
    QWDI_CMD_SET_FRAG,
    QWDI_CMD_STA_SET_FLAGS,
    QWDI_CMD_SET_TX_QUEUE_PARAMS,
    QWDI_CMD_IF_ADD,
    QWDI_CMD_IF_REMOVE,
    QWDI_CMD_SET_STA_VLAN,
    QWDI_CMD_COMMIT,
    QWDI_CMD_SEND_ETHER,
    QWDI_CMD_SET_RADIUS_ACL_AUTH,
    QWDI_CMD_SET_RADIUS_ACL_EXPIRE,
    QWDI_CMD_SET_AP_WPS_IE,
    QWDI_CMD_SET_SUPP_PORT,
    QWDI_CMD_WDS_STA,
    QWDI_CMD_SEND_ACTION,
    QWDI_CMD_SEND_ACTION_CANCEL_WAIT,
    QWDI_CMD_REMAIN_ON_CHANNEL,
    QWDI_CMD_CANCEL_REMAIN_ON_CHANNEL,
    QWDI_CMD_SET_PRIORITY,
    QWDI_CMD_PROBE_REQ_REPORT,
    QWDI_CMD_DEINIT_AP,
    QWDI_CMD_DEINIT_P2P_CLI,
    QWDI_CMD_SUSPEND,
    QWDI_CMD_RESUME,
    QWDI_CMD_SIGNAL_MONITOR,
    QWDI_CMD_SEND_FRAME,
    QWDI_CMD_SHARED_FREQ,
    QWDI_CMD_GET_NOA,
    QWDI_CMD_SET_NOA,
    QWDI_CMD_SET_P2P_POWERSAVE,
    QWDI_CMD_AMPDU,
    QWDI_CMD_GET_RADIO_NAME,
    QWDI_CMD_P2P_FIND,
    QWDI_CMD_P2P_LISTEN,
    QWDI_CMD_P2P_CONNECT,
    QWDI_CMD_WPS_SUCCESS_CB,
    QWDI_CMD_P2P_GROUP_FORMATION_FAILED,
    QWDI_CMD_P2P_SET_PARAMS,
    QWDI_CMD_P2P_PROV_DISC_REQ,
    QWDI_CMD_P2P_SD_REQUEST,
    QWDI_CMD_P2P_SD_CANCEL_REQUEST,
    QWDI_CMD_P2P_SD_RESPONSE,
    QWDI_CMD_P2P_SERVICE_UPDATE,
    QWDI_CMD_P2P_REJECT,
    QWDI_CMD_P2P_INVITE,
    QWDI_CMD_SEND_TDLS_MGMT,
    QWDI_CMD_TDLS_OPER,
    QWDI_CMD_WNM_OPER,
    QWDI_CMD_SIGNAL_POLL,
    QWDI_CMD_SET_AUTHMODE,
    QWDI_CMD_SET_REKEY_INFO,
    QWDI_CMD_STA_ASSOC,
    QWDI_CMD_STA_AUTH,
    QWDI_CMD_ADD_TSPEC,
    QWDI_CMD_ADD_STA_NODE,
    QWDI_CMD_POLL_CLIENT,
    QWDI_CMD_RADIO_DISABLE,
    QWDI_CMD_SWITCH_CHANNEL,
    QWDI_CMD_DRIVER_CMD,
    QWDI_CMD_DISABLE,
    QWDI_CMD_ENABLE,
    /* additional commands for QWDI implementation*/
    QWDI_CMD_GET_SCAN_RESULTS_SIZE,
    QWDI_CMD_GET_ASSOC_INFO,
    QWDI_CMD_SET_P2P_MODE, /*may be used to release p2p resource in firmware if anything goes wrong, device can choose to ignore it */
    QWDI_CMD_P2P_SET_AP, /*for p2p GO role */
    QWDI_CMD_GET_SCAN_COMPLETE,
    QWDI_CMD_TEST,
    QWDI_CMD_AFTER_LAST,
    QWDI_CMD_MAX = QWDI_CMD_AFTER_LAST - 1

};


enum qwdi_events {
    QWDI_EVENT_NONE,
    QWDI_EVENT_ASSOC,
    QWDI_EVENT_DISASSOC,
    QWDI_EVENT_MICHAEL_MIC_FAILURE,
    QWDI_EVENT_SCAN_RESULTS,
    QWDI_EVENT_ASSOCINFO,
    QWDI_EVENT_INTERFACE_STATUS,
    QWDI_EVENT_PMKID_CANDIDATE,
    QWDI_EVENT_STKSTART,
    QWDI_EVENT_TDLS,
    QWDI_EVENT_FT_RESPONSE,
    QWDI_EVENT_IBSS_RSN_START,
    QWDI_EVENT_AUTH,
    QWDI_EVENT_DEAUTH,
    QWDI_EVENT_ASSOC_REJECT,
    QWDI_EVENT_AUTH_TIMED_OUT,
    QWDI_EVENT_ASSOC_TIMED_OUT,
    QWDI_EVENT_FT_RPB_RX,
    QWDI_EVENT_WPS_BUTTON_PUSHED,
    QWDI_EVENT_TX_STATUS,
    QWDI_EVENT_RX_FROM_UNKNOWN,
    QWDI_EVENT_RX_MGMT,
    QWDI_EVENT_RX_ACTION,
    QWDI_EVENT_REMAIN_ON_CHANNEL,
    QWDI_EVENT_MLME_RX,
    QWDI_EVENT_RX_PROBE_REQ,
    QWDI_EVENT_NEW_STA,
    QWDI_EVENT_EAPOL_RX,
    QWDI_EVENT_SIGNAL_CHANGE,
    QWDI_EVENT_INTEFACE_ENABLED,
    QWDI_EVENT_INTERFACE_DISABLED,
    QWDI_EVENT_CHANNEL_LIST_CHANGED,
    QWDI_EVENT_INTERFACE_UNAVAILABLE,
    QWDI_EVENT_BEST_CHANNEL,
    QWDI_EVENT_UNPROT_DEAUTH,
    QWDI_EVENT_UNPROT_DISASSOC,
    QWDI_EVENT_STATION_LOW_ACK,
    QWDI_EVENT_P2P_DEV_FOUND,
    QWDI_EVENT_P2P_GO_NEG_REQ_RX,
    QWDI_EVENT_P2P_GO_NEWG_COMPLETED,
    QWDI_EVENT_P2P_PROV_DISC_REQUEST,
    QWDI_EVENT_P2P_PROV_DISC_RESPONSES,
    QWDI_EVENT_P2P_SD_REQUEST,
    QWDI_EVENT_P2P_SD_RESPONSE,
    QWDI_EVENT_IBSS_PEER_LOST,
    QWDI_EVENT_DRIVER_GTK_REKEY,
    QWDI_EVENT_SCHED_SCAN_STOPPED,
    QWDI_EVENT_DRIVER_CLIENT_POLL_OK,
    QWDI_EVENT_EAPOL_TX_STATUS,
    QWDI_EVENT_CH_SWITCH,
    QWDI_EVENT_WNM,
    QWDI_EVENT_START_ROAMING,
    QWDI_EVENT_ROAM_TO_SPECIFIC_AP,
    QWDI_EVENT_SMART_CONFIG_SYNC,
    QWDI_EVENT_SMART_CONFIG_DECODE,
    QWDI_EVENT_CANCEL_REMAIN_ON_CHANNEL,
    /* additional events for QWDI */
    QWDI_EVENT_ASSOC_IND,
    QWDI_EVENT_TEST,
    QWDI_EVENT_AFTER_LAST,
    QWDI_EVENT_MAX = QWDI_EVENT_AFTER_LAST - 1
};


#define DCMD_QWDI_CMD 0x1000
/* Interface Type supported */
typedef enum {
    /**
     * QWDI_WPA_IF_STATION - Station mode interface
     */
    QWDI_WPA_IF_STATION,

    /**
     * QWDI_WPA_IF_AP_VLAN - AP mode VLAN interface
     *
     * This interface shares its address and Beacon frame with the main
     * BSS.
     */
    QWDI_WPA_IF_AP_VLAN,

    /**
     * QWDI_WPA_IF_AP_BSS - AP mode BSS interface
     *
     * This interface has its own address and Beacon frame.
     */
    QWDI_WPA_IF_AP_BSS,

    /**
     * QWDI_WPA_IF_P2P_GO - P2P Group Owner
     */
    QWDI_WPA_IF_P2P_GO,

    /**
     * QWDI_WPA_IF_P2P_CLIENT - P2P Client
     */
    QWDI_WPA_IF_P2P_CLIENT,

    /**
     * QWDI_WPA_IF_P2P_GROUP - P2P Group interface (will become either
     * QWDI_WPA_IF_P2P_GO or QWDI_ WPA_IF_P2P_CLIENT, but the role is not yet known)
     */
    QWDI_WPA_IF_P2P_GROUP,

    /**
     * QWDI_WPA_IF_P2P_DEVICE - P2P Device interface is used to indentify the
     * abstracted P2P Device function in the driver
     */
    QWDI_WPA_IF_P2P_DEVICE,

    /**
     * QWDI_WPA_IF_UNKNOWN - unknow yet
     */
    QWDI_WPA_IF_UNKNOWN

} QwdiIfType_e;


/* interface role, somewhat related to interface type */
typedef enum
{
    QWDI_IF_MODE_SYS,
    QWDI_IF_MODE_STA,
    QWDI_IF_MODE_SAP,
    QWDI_IF_MODE_P2PDEV,
    QWDI_IF_MODE_P2PCL,
    QWDI_IF_MODE_P2PGO,
    QWDI_IF_MODE_IBSS,
    QWDI_IF_MODE_NETMON,
    QWDI_IF_MODE_MAX,
    QWDI_IF_MODE_UNKNOWN
} QwdiIfMode_e;

typedef struct _QwdiWmmAcParams {
    int cwmin;
    int cwmax;
    int aifs;
    int txop_limit; /* in units of 32us */
    int admission_control_mandatory;
} QwdiWmmAcParams_t;

typedef struct _QwdiKey {
    unsigned int key_len;
    char    key[QWDI_MAX_KEY_LEN];
} QwdiKey_t;

typedef struct _QwdiWepKeys {
    unsigned char idx;
    QwdiKey_t keys[QWDI_NUM_WEP_KEYS];
    int keys_set;
    int default_len; /* key length used for dynamic key generation */
}QwdiWepKeys_t ;



/* Message header */
typedef struct _QwdiMsgHeader {
    unsigned int     command_id;  /* command identifier*/
    unsigned int     msg_size;    /* number of bytes in message payload; doesn't include this header*/
} QwdiMsgHeader_t;

#define QWDI_MAX_EVENT_DATA_SIZE 2048

typedef struct _QwdiEventHeader {
    unsigned int event_id;
    unsigned int event_size;
}QwdiEventHeader_t;

/* Event structure */
typedef struct _QwdiEvent {
    QwdiEventHeader_t hdr;
    unsigned char  eventBuffer[QWDI_MAX_EVENT_DATA_SIZE];
} QwdiEvent_t;

typedef struct _QwdiInitReq {
    unsigned int version; /* supplicant's version */
    char ifname[QWDI_IFNAMSIZ+1];    
} QwdiInitReq_t;

typedef struct _QwdiInitRsp {
    unsigned int version; /* driver preferred wpa_supplicant version*/
    QwdiIfType_e iftype;
    QwdiIfMode_e ifmode;
    int  scan_timeout; /* scan timeout in seconds */
    char ifname[QWDI_IFNAMSIZ+1];
    int  p2p_supported;
    int  roc_timeout_offset; /*remain on channel timeout offset in microseconds*/
    int  version_mismatch; /*driver can't support the version of wpa_supplicant */
} QwdiInitRsp_t;

typedef struct _QwdiSetFreqReq {
    int mode;
    int freq;
    int channel;
    int ht_enabled;
    int sec_channel_offset;
    int vht_enabled;
    int center_freq1;
    int center_freq2;
    int bandwidth;
    int valid; /*the values in the structure are set by supplicant*/
}QwdiSetFreqReq_t;

typedef QwdiSetFreqReq_t QwdiHapdFreqParams_t;


typedef struct _QwdiSsid {
    unsigned int    ssid_len;
    char    ssid[QWDI_MAX_SSID_STR_LEN];
} QwdiSsid_t;

#define QWDI_SCAN_FLAG_SUPP_RATES   BIT(0) /* remove 802.11b rates from supported rates in probe request frames */
#define QWDI_SCAN_FLAG_FLUSH        BIT(1) /* flush old cached BSSes, only report BSSes detected after this scan request */
#define QWDI_SCAN_FLAG_LOW_PRIORITY BIT(2) /* driver to use a lower scan priority */
#define QWDI_SCAN_FLAG_RANDOM_ADDR  BIT(3) /* river to randomize MAC address */
typedef struct _QwdiScanReq {
    QwdiSsid_t    ssids[QWDI_MAX_SCAN_SSID];
    unsigned char num_ssids;
    QwdiSsid_t    filter_ssids[QWDI_MAX_SCAN_SSID];
    unsigned char num_filter_ssids;
    unsigned int  freqs[QWDI_MAX_SCAN_FREQ];
    unsigned char num_freqs;
    unsigned char extra_ies[QWDI_MAX_EXTRA_IES_LEN];
    unsigned short extra_ies_len;
    unsigned char scan_type; /* ToDo check if WPA2.5 still need it */
    int           scan_band; /* ToDo check if WPA2.5 still need it */
    int           band_select;/* ToDo check if WPA2.5 still need it */
    int           scan_req_type; /* ToDo check if WPA2.5 still need it */
    int           wps_active_scan;
    int           filter_rssi;
    int           flag;
    unsigned char mac_addr[QWDI_ETH_ALEN];
    unsigned char mac_addr_mask[QWDI_ETH_ALEN];
} QwdiScanReq_t;

typedef struct _Qwdi_Variable_IE {
    unsigned char type;
    unsigned char length; /*bytes in data */
    unsigned char data[1];
}Qwdi_Variable_IE_t;


typedef struct _Qwdi_Bssid_Info {
    unsigned int  length; /*total length of bssid info */
    unsigned char  mac_addr[QWDI_ETH_ALEN];
    QwdiSsid_t     ssid;
    unsigned int   flags;
    unsigned short caps;
    int            rssi;
    int            freq;
    unsigned short beacon_int;
    int            qual;
    int            noise;
    unsigned long long tsf;
    unsigned int   age;
    unsigned int est_throughput;
    int snr;
    unsigned int   ie_len;
    unsigned char  ie[1];
} Qwdi_Bssid_Info_t;

typedef struct _QwdiGetScanResultsRsp {
    unsigned int num_bssid;
    unsigned int list_size; /*bssid list size, equals all the length added together*/
    Qwdi_Bssid_Info_t bssid[1];
}QwdiGetScanResultsRsp_t;

typedef struct _QwdiGetScanResultsSizeRsp {
    int scan_result_size;
    int num_bssid;
    int set_timeout;
} QwdiGetScanResultsSizeRsp_t;

typedef struct _QwdiGetScanCompleteRsp {
    int completed;
    int set_timeout;
} QwdiGetScanCompleteRsp_t;

typedef enum _QwdiWpaAlg {
    QWDI_WPA_ALG_NONE,
    QWDI_WPA_ALG_WEP,
    QWDI_WPA_ALG_TKIP,
    QWDI_WPA_ALG_CCMP,
    QWDI_WPA_ALG_IGTK,
    QWDI_WPA_ALG_PMK,
    QWDI_WPA_ALG_GCMP,
    QWDI_WPA_ALG_SMS4,
    QWDI_WPA_ALG_KRK,
    QWDI_WPA_ALG_GCMP_256,
    QWDI_WPA_ALG_CCMP_256,
    QWDI_WPA_ALG_BIP_GMAC_128,
    QWDI_WPA_ALG_BIP_GMAC_256,
    QWDI_WPA_ALG_BIP_CMAC_256
} QwdiWpaAlg_e;

typedef struct _QwdiSetKeyReq {
    char ifname[QWDI_IFNAMSIZ+1];
    QwdiWpaAlg_e   alg;
    unsigned char  addr[QWDI_ETH_ALEN];
    int            key_idx;
    int            set_tx;
    unsigned char  seq[QWDI_MAX_SEQ_LEN];
    int            seq_len;
    unsigned char  key[QWDI_MAX_KEY_LEN];
    int            key_len;
    int            key_mgmt;
} QwdiSetKeyReq_t;

typedef struct _QwdiGetMacAddrRsp {
    unsigned char  addr[QWDI_ETH_ALEN];
}QwdiGetMacAddrRsp_t;

typedef struct _QwdiHapdInitReq {
    unsigned int version; /*hostapd version */
    char ifname[QWDI_IFNAMSIZ+1];
    int  ieee80211n;
    unsigned short ht_capab;
    int  isolate;
    int  max_tx_power;
    int  wmm_uapsd;
    int  wmm_enabled;
    QwdiWmmAcParams_t wmm_ac_params[4];
    int  ieee80211ac;
    unsigned int vht_capab;
} QwdiHapdInitReq_t;

typedef struct _QwdiHapdInitRsp {
    unsigned int version; /* driver preferred hostapd version */
    QwdiIfType_e iftype;
    unsigned char  addr[QWDI_ETH_ALEN];
    int          version_mismatch; /* driver can't support the version of hostapd */
} QwdiHapdInitRsp_t;

typedef struct _QwdiAssociateReq {
    unsigned char  bssid[QWDI_ETH_ALEN];
    unsigned char  bssid_hint[QWDI_ETH_ALEN];
    QwdiSsid_t     ssid;
    int            freq; /*deprecated use freq_params instead*/
    QwdiHapdFreqParams_t freq_params;
    int            freq_hint;
    int            bg_scan_period;
    int            beacon_int;
    unsigned int   wpa_proto;
    int pairwise_suite;
    int group_suite;
    int key_mgmt_suite;
    int            auth_alg;
    int            mode;
    QwdiKey_t      wep_key[QWDI_NUM_WEP_KEYS];
    int            wep_tx_keyidx;
    int            mgmt_frame_protection;
    unsigned char ft_md[6];
    int           passphrase_len;
    unsigned char passphrase[64];
    unsigned char psk[QWDI_MAX_KEY_LEN];
    int drop_unencrypted;
    unsigned char prev_bssid[QWDI_ETH_ALEN];
    int reassoc; /* if 1 use prev_bssid */
    int wps;
    int p2p;
    int uapsd;
    int fixed_bssid;
    int fixed_freq;
    int sta_uapsd;
    int disable_ht;
    struct qwdi_ieee80211_ht_cap htcaps;
    struct qwdi_ieee80211_ht_cap htcaps_mask;  /* struct ieee80211_ht_capabilities * */
    int disable_vht;
    struct qwdi_ieee80211_vht_cap vhtcaps;
    struct qwdi_ieee80211_vht_cap vhtcaps_mask;
    /**
        * band_select - Band operation mode (2.4Ghz only, 5Ghz only or both)
        * deprecated for WPA2.5
        **/
    int band_select;

    /**
         * ap_handover - set to 1 if inter-AP handovers are allowed
         * deprecated for WPA2.5
         **/
    int ap_handover;
    int req_key_mgmt_offload;
    int rrm_used;
    unsigned int   ie_len;
    unsigned int   ft_ies_len;
    unsigned char  ie[1]; /*include ie_len legth of IE followed by ft_ies_len length of FT IE */
} QwdiAssociateReq_t;

typedef struct _QwdiGetBssidRsp {
    unsigned char  bssid[QWDI_ETH_ALEN];
} QwdiGetBssidRsp_t;

typedef struct _QwdiAddPmkidReq {
    unsigned char  bssid[QWDI_ETH_ALEN];
    unsigned char  pmkid[QWDI_PMKID_LEN];
}QwdiAddPmkidReq_t;

typedef struct _QwdiRemovePmkidReq {
    unsigned char  bssid[QWDI_ETH_ALEN];
    unsigned char  pmkid[QWDI_PMKID_LEN];
}QwdiRemovePmkidReq_t;


typedef struct _QwdiRemainOnChannelReq {
    unsigned int freq;
    unsigned int duration;
}QwdiRemainOnChannelReq_t;

typedef struct _QwdiRemainOnChannelRsp {
    unsigned int roc_id;
}QwdiRemainOnChannelRsp_t;

typedef struct _QwdiCancelRemainOnChannelReq {
    unsigned int roc_id;
}QwdiCancelRemainOnChannelReq_t;


typedef struct _QwdiDeauthenticateReq {
    unsigned char  addr[QWDI_ETH_ALEN];
    unsigned int   reason_code;
}QwdiDeauthenticateReq_t;

typedef struct _QwdiGetSsidRsp {
    QwdiSsid_t ssid;
}QwdiGetSsidRsp_t;

typedef struct _QwdiHapdGetSsidRsp {
    QwdiSsid_t ssid;
}QwdiHapdGetSsidRsp_t;

typedef struct _QwdiHapdSetSsidReq {
    QwdiSsid_t ssid;
}QwdiHapdSetSsidReq_t;

typedef struct _QwdiGetNoaRsp {
    unsigned char buf[QWDI_MAX_NOA_LEN];
    unsigned int  buf_len;
}QwdiGetNoaRsp_t;

typedef struct _QwdiSetNoaReq {
    unsigned int count;
    unsigned int start;
    unsigned int duration;
}QwdiSetNoaReq_t;

typedef struct _QwdiSetCountryReq {
    unsigned char country[QWDI_MAX_COUNTRY_LEN];
}QwdiSetCountryReq_t;

typedef struct _QwdiSetFragReq {
    unsigned int frag_threshold;
}QwdiSetFragReq_t;

typedef struct _QwdiSetRtsReq {
    unsigned int rts_threshold;
}QwdiSetRtsReq_t;

typedef struct _QwdiProbeReqReportReq {
    int report;
}QwdiProbeReqReportReq_t;

typedef struct _QwdiSetP2pPowerSaveReq {
    int legacy_ps;
    int opp_ps;
    int ctwindow;
}QwdiSetP2pPowerSaveReq_t;

typedef struct _QwdiSetApWpsIeReq {
    int beacon_ie_len;
    int proberesp_ie_len;
    int assocresp_ie_len;
    /* ies followed */
}QwdiSetApWpsIeReq_t;


typedef struct _QwdiStaDeauthReq {
    unsigned char own_addr[QWDI_ETH_ALEN];
    unsigned char addr[QWDI_ETH_ALEN];
    int           reason;
}QwdiStaDeauthReq_t;

typedef struct _QwdiStaDisassocReq {
    unsigned char own_addr[QWDI_ETH_ALEN];
    unsigned char addr[QWDI_ETH_ALEN];
    int           reason;
}QwdiStaDisassocReq_t;


typedef struct _QwdiSetCounterMeasuresReq {
    int           enabled;
}QwdiSetCounterMeasuresReq_t;

typedef struct _QwdiIfAddReq {
    char ifname[QWDI_IFNAMSIZ+1];
    QwdiIfType_e if_type;
    unsigned char  addr[QWDI_ETH_ALEN];
    int          use_existing;
}QwdiIfAddReq_t;

typedef struct _QwdiIfAddRsp {
    unsigned char force_ifname[QWDI_IFNAMSIZ+1];
    unsigned char if_addr[QWDI_ETH_ALEN];
}QwdiIfAddRsp_t;

typedef struct _QwdiIfRemoveReq {
    char ifname[QWDI_IFNAMSIZ+1];
    QwdiIfType_e if_type;
}QwdiIfRemoveReq_t;


typedef struct _QwdiSetApReq {
    unsigned char  beacon_head[QWDI_MAX_HEAD_BUFF_LEN];
    unsigned char  beacon_tail[QWDI_MAX_TAIL_BUFF_LEN];
    unsigned char  proberesp[QWDI_MAX_PROBE_RESP_LEN];
    int head_len;
    int tail_len;
    int proberesp_len;
    int dtim_period;
    int beacon_int;
    int basic_rates[QWDI_MAX_SUPPORT_RATES];
    int current_rates[QWDI_MAX_SUPPORT_RATES];
    int basic_rates_len;
    int current_rates_len;
    QwdiSsid_t ssid;
    int hide_ssid;
    unsigned int pairwise_ciphers;
    unsigned int group_cipher;
    unsigned int key_mgmt_suites;
    unsigned int auth_algs;
    unsigned int wpa_version;
    unsigned char beacon_ies[QWDI_MAX_EXTRA_IES_LEN];
    unsigned char proberesp_ies[QWDI_MAX_EXTRA_IES_LEN];
    unsigned char assocresp_ies[QWDI_MAX_EXTRA_IES_LEN];
    int beacon_ies_len;
    int proberesp_ies_len;
    int assocresp_ies_len;
    int isolate;
    int cts_protect;
    int preamble;
    int short_slot_time;
    int ht_opmode;
    int interworking;
    unsigned char hessid[QWDI_ETH_ALEN];
    unsigned char access_network_type;
    int ap_max_inactivity;
    int disable_dgaf;
    QwdiWepKeys_t wep;
    int max_num_sta;
    unsigned char p2p_go_ctwindow;
    unsigned int smps_mode;
    int osen;
    int reenable;
    QwdiHapdFreqParams_t freq;
}QwdiSetApReq_t;

typedef struct _QwdiSendActionReq {
    unsigned int  freq;
    unsigned int  wait_time;
    int           no_cck;
    unsigned char dst[QWDI_ETH_ALEN];
    unsigned char src[QWDI_ETH_ALEN];
    unsigned char bssid[QWDI_ETH_ALEN];
    int data_len;
    unsigned char data[QWDI_MAX_MGMT_FRAME_LEN];
}QwdiSendActionReq_t;

typedef struct _QwdiSendMlmeReq {
    int noack;
    int data_len;
    unsigned char data[QWDI_MAX_MGMT_FRAME_LEN];
    unsigned int freq;
}QwdiSendMlmeReq_t;

typedef struct _QwdiChannelInfo {
    unsigned int chan;
    unsigned int freq;
    unsigned int flag;
    unsigned char max_tx_power;
    /*struct dl_list survey_list;*/
    char min_nf;
    /*long double interference_factor; */
}QwdiChannelInfo_t;

typedef enum _QwdiHwMode {
    QWDI_HW_MODE_IEEE80211B,
    QWDI_HW_MODE_IEEE80211G,
    QWDI_HW_MODE_IEEE80211A,
    QWDI_HW_MODE_IEEE80211AD,
    QWDI_MAX_HW_MODES_NUM
} QwdiHwMode_e;

typedef struct _QwdiHwFeature {
    QwdiHwMode_e mode;
    int num_channels;
    QwdiChannelInfo_t channels[QWDI_MAX_CHANNEL_NUM];
    int num_rates;
    int rates[QWDI_MAX_SUPPORT_RATES];
    unsigned short ht_capab;
    unsigned char mcs_set[QWDI_MAX_SUPPORT_MCS];
    unsigned char mcs_set_num;
    unsigned char a_mpdu_params;
    unsigned int vht_capab;
    unsigned char vht_mcs_set[QWDI_MAX_SUPPORT_MCS];
    unsigned char vht_mcs_set_num;
    unsigned int flags;
}QwdiHwFeature_t;

typedef struct _QwdiGetHwFeatureDataRsp {
    int num_modes;
    QwdiHwFeature_t hw_modes[QWDI_MAX_HW_MODES_NUM];
}QwdiGetHwFeatureDataRsp_t;

typedef struct _QwdiSetOperStateReq {
    int operstate;
}QwdiSetOperStateReq_t;

typedef struct _QwdiGetCapaRsp{
    int has_capability;
    struct qwdi_driver_capa capa;
} QwdiGetCapaRsp_t;

typedef struct _QwdiGetAssocInfoRsp {
    int reassoc;
    unsigned int   freq;
    unsigned char  addr[QWDI_ETH_ALEN];
    unsigned int   req_ies_len;
    unsigned int   resp_ies_len;
    unsigned int   beacon_ies_len;
    unsigned char  ie[1]; /*req_ies + resp_ies + beacon_ies */
}QwdiGetAssocInfoRsp_t;

typedef struct _QwdiSharedFreqRsp {
    int freq;
}QwdiSharedFreqRsp_t;

typedef struct _QwdiSetP2pModeReq {
    unsigned char  mode;
    unsigned int   channel;
    unsigned short listen_ms;
}QwdiSetP2pModeReq_t;

/* event structures */

typedef struct _QwdiScanInfo {
    int aborted;
    int scan_type;
    int sched_scan;
    int set_timeout;
    unsigned int freqs[QWDI_MAX_SCAN_FREQ];
    unsigned int num_freqs;
    QwdiSsid_t ssids[QWDI_MAX_SCAN_SSID];
    unsigned int num_ssids;
}QwdiScanInfo_t;

typedef struct _QwdiAssocInfo {
    int reassoc;
    unsigned int   freq;
    unsigned char  addr[QWDI_ETH_ALEN];
    unsigned int   req_ies_len;
    unsigned int   resp_ies_len;
    unsigned int   beacon_ies_len;
    unsigned char  ie[1]; /*req_ies + resp_ies + beacon_ies */
}QwdiAssocInfo_t;

typedef struct _QwdiAssocInd {
    int reassoc;
    unsigned int   freq;
    unsigned char  addr[QWDI_ETH_ALEN];
    unsigned int   req_ies_len;
    unsigned char  ie[1]; /*req_ies */
}QwdiAssocInd_t;

typedef struct _QwdiDisassocInfo {
    int            locally_generated;
    unsigned short reason_code;
    unsigned char  addr[QWDI_ETH_ALEN];
    unsigned int   ies_len;
    unsigned char  ie[1]; /*ies */
}QwdiDisassocInfo_t;

typedef struct _QwdiRemainOnChannelInfo {
    unsigned int freq;
    unsigned int duration;
    unsigned int roc_id;
}QwdiRemainOnChannelInfo_t;

typedef struct _QwdiTxStatus {
    unsigned short type;
    unsigned short stype;
    int            ack;
    unsigned char  dst[QWDI_ETH_ALEN];
    int            data_len;
    unsigned char  data[QWDI_MAX_MGMT_FRAME_LEN];
}QwdiTxStatus_t;

typedef struct _QwdiRxMgmt {
    int frame_len;
    unsigned int datarate;
    int freq; /*Frequency (in MHz) on which the frame was received */
    int ssi_signal; /*Signal strength in dBm (or 0 if not available) */
    unsigned char frame[QWDI_MAX_MGMT_FRAME_LEN];
}QwdiRxMgmt_t;

typedef struct _QwdiMichaelMicFailure {
    int unicast;
    unsigned char  src[QWDI_ETH_ALEN];
}QwdiMichaelMicFailure_t;

#endif /*_QWDI_MSG_H*/

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/io-pkt/services/wpa-2.5/wpa_supplicant/public/qwdi_msg_2_5.h $ $Rev: 821239 $")
#endif


