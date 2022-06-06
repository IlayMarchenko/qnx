/*
 * Copyright (c) 2015-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef PCM_MIXER_SLOTS_MIB_H
#define PCM_MIXER_SLOTS_MIB_H

/**
 * This defines the
 *  - names of the PCM devices
 *  - Identifiers for PCM devices
 *  - names of the available switches
 *  - input and output identifier for the slots of
 *    the switches
 */

/**
* Interface version
*/
#define PCM_MIXER_SLOTS_MIB_VERION_MAJOR       0
#define PCM_MIXER_SLOTS_MIB_VERION_MINOR       1

/**
* PCM device list
*/

#define PCM_ID_NONE                         0
/**
* PCM Playback devices
*/
#define PCM_PLAY_MPL_1_ID                   1
#define PCM_PLAY_MPL_1                      "MPL1"

#define PCM_PLAY_MPL_2_ID                   2
#define PCM_PLAY_MPL_2                      "MPL2"

#define PCM_PLAY_MPL_3_ID                   3
#define PCM_PLAY_MPL_3                      "MPL3"

#define PCM_PLAY_MPL_4_ID                   4
#define PCM_PLAY_MPL_4                      "MPL4"

#define PCM_PLAY_MPL_8_ID                   5
#define PCM_PLAY_MPL_8                      "MPL8"

#define PCM_PLAY_TEL_6_ID                   6
#define PCM_PLAY_TEL_6                      "TEL6"

#define PCM_PLAY_ANN_11_ID                  7
#define PCM_PLAY_ANN_11                     "ANN11"

#define PCM_PLAY_MPL_5_ID                   8
#define PCM_PLAY_MPL_5                      "MPL5"

#define PCM_PLAY_TEL_2_ID                   9
#define PCM_PLAY_TEL_2                      "TEL2"

#define PCM_PLAY_TEL_5_ID                   10
#define PCM_PLAY_TEL_5                      "TEL5"

#define PCM_PLAY_ANN_4_ID                   11
#define PCM_PLAY_ANN_4                      "ANN4"

#define PCM_PLAY_TEL_3_ID                   12
#define PCM_PLAY_TEL_3                      "TEL3"

#define PCM_PLAY_ANN_7_ID                   13
#define PCM_PLAY_ANN_7                      "ANN7"

#define PCM_PLAY_MPL_6_ID                   14
#define PCM_PLAY_MPL_6                      "MPL6"

#define PCM_PLAY_WAV_1_ID                   15
#define PCM_PLAY_WAV_1                      "WAV1"

#define PCM_PLAY_WAV_2_ID                   16
#define PCM_PLAY_WAV_2                      "WAV2"

#define PCM_PLAY_ANN_2_ID                   17
#define PCM_PLAY_ANN_2                      "ANN2"

#define PCM_PLAY_ANN_M_ID                   18
#define PCM_PLAY_ANN_M                      "ANN_M"

#define PCM_PLAY_MPL_7_ID                   19
#define PCM_PLAY_MPL_7                      "MPL7"

#define PCM_PLAY_TEL_4_ID                   20
#define PCM_PLAY_TEL_4                      "TEL4"

#define PCM_PLAY_ANN_8_ID                   21
#define PCM_PLAY_ANN_8                      "ANN8"

#define PCM_PLAY_SSE_UL_1_ID                22
#define PCM_PLAY_SSE_UL_1                   "SSE_UL_1"

#define PCM_PLAY_TEL_UL_SCON1_ID            23
#define PCM_PLAY_TEL_UL_SCON1               "TEL_UL_SCON1"

#define PCM_PLAY_TEL_UL_SCON2_ID            24
#define PCM_PLAY_TEL_UL_SCON2               "TEL_UL_SCON2"

/**
* PCM Capture devices
*/
#define PCM_CAP_SDS_UL_ID                   25
#define PCM_CAP_SDS_UL                      "SDS_UL"

#define PCM_CAP_MIC_6_ID                    26
#define PCM_CAP_MIC_6                       "MIC6"

#define PCM_CAP_MIC_2_ID                    27
#define PCM_CAP_MIC_2                       "MIC2"

#define PCM_CAP_MIC_5_ID                    28
#define PCM_CAP_MIC_5                       "MIC5"

#define PCM_CAP_MIC_3_ID                    29
#define PCM_CAP_MIC_3                       "MIC3"

#define PCM_CAP_MIC_4_ID                    30
#define PCM_CAP_MIC_4                       "MIC4"

#define PCM_CAP_SSE_BUNDLE_1_ID             31
#define PCM_CAP_SSE_BUNDLE_1                "SSE_BUNDLE_1"

#define PCM_CAP_ENT_1_ID                    32
#define PCM_CAP_ENT_1                       "ENT1"

#define PCM_CAP_ENT_2_ID                    33
#define PCM_CAP_ENT_2                       "ENT2"

#define PCM_CAP_TEL_DL_SCON1_ID             34
#define PCM_CAP_TEL_DL_SCON1                "TEL_DL_SCON1"

#define PCM_CAP_TEL_DL_SCON2_ID             35
#define PCM_CAP_TEL_DL_SCON2                "TEL_DL_SCON2"

/**
* Mixer switch list
*/
#define MIXER_SWITCH_ID_NONE               0
#define MIXER_SWITCH_ID_NONE_NAME          "NONE"

/* Mixer switch ENT */
#define MIXER_SWITCH_ENT                "MS_ENT"
/* inputs */
#define MIXER_SWITCH_IN_MPL_1              1
#define MIXER_SWITCH_IN_MPL_1_NAME         "MPL1"
#define MIXER_SWITCH_IN_MPL_5              2
#define MIXER_SWITCH_IN_MPL_5_NAME         "MPL5"
#define MIXER_SWITCH_IN_MPL_6              3
#define MIXER_SWITCH_IN_MPL_6_NAME         "MPL6"
#define MIXER_SWITCH_IN_WAV_1              4
#define MIXER_SWITCH_IN_WAV_1_NAME         "WAV1"
#define MIXER_SWITCH_IN_MPL_2              5
#define MIXER_SWITCH_IN_MPL_2_NAME         "MPL2"
#define MIXER_SWITCH_IN_MPL_3              6
#define MIXER_SWITCH_IN_MPL_3_NAME         "MPL3"
#define MIXER_SWITCH_IN_MPL_4              7
#define MIXER_SWITCH_IN_MPL_4_NAME         "MPL4"
#define MIXER_SWITCH_IN_MPL_7              8
#define MIXER_SWITCH_IN_MPL_7_NAME         "MPL7"
#define MIXER_SWITCH_IN_MPL_8              9
#define MIXER_SWITCH_IN_MPL_8_NAME         "MPL8"
/* outputs */
#define MIXER_SWITCH_OUT_TDM_MPL           1
#define MIXER_SWITCH_OUT_TDM_MPL_NAME      "TDM_MPL"

/* Mixer switch ANN */
#define MIXER_SWITCH_ANN                "MS_ANN"
/* inputs */
#define MIXER_SWITCH_IN_ANN_4             1
#define MIXER_SWITCH_IN_ANN_4_NAME        "ANN4"
#define MIXER_SWITCH_IN_ANN_7             2
#define MIXER_SWITCH_IN_ANN_7_NAME        "ANN7"
#define MIXER_SWITCH_IN_ANN_2             3
#define MIXER_SWITCH_IN_ANN_2_NAME        "ANN2"
#define MIXER_SWITCH_IN_WAV_2             4
#define MIXER_SWITCH_IN_WAV_2_NAME        "WAV2"
#define MIXER_SWITCH_IN_ANN_8             5
#define MIXER_SWITCH_IN_ANN_8_NAME        "ANN8"
#define MIXER_SWITCH_IN_ANN_11            6
#define MIXER_SWITCH_IN_ANN_11_NAME       "ANN11"
/* outputs */
#define MIXER_SWITCH_OUT_TDM_ANN_2        1
#define MIXER_SWITCH_OUT_TDM_ANN_2_NAME   "TDM_ANN2"

/* Mixer switch Phone Downlink */
#define MIXER_SWITCH_PHONE_DL           "MS_PH_DL"
/* inputs */
#define MIXER_SWITCH_IN_TEL_2             1
#define MIXER_SWITCH_IN_TEL_2_NAME        "TEL2"
#define MIXER_SWITCH_IN_TEL_3             2
#define MIXER_SWITCH_IN_TEL_3_NAME        "TEL3"
#define MIXER_SWITCH_IN_TEL_DL_NAD        3
#define MIXER_SWITCH_IN_TEL_DL_NAD_NAME   "TEL_DL_NAD"
#define MIXER_SWITCH_IN_TEL_DL_HF_1       4
#define MIXER_SWITCH_IN_TEL_DL_HF_1_NAME  "TEL_DL_HF1"
#define MIXER_SWITCH_IN_TEL_DL_HF_2       5
#define MIXER_SWITCH_IN_TEL_DL_HF_2_NAME  "TEL_DL_HF2"
#define MIXER_SWITCH_IN_TEL_4             6
#define MIXER_SWITCH_IN_TEL_4_NAME        "TEL4"
#define MIXER_SWITCH_IN_TEL_5             7
#define MIXER_SWITCH_IN_TEL_5_NAME        "TEL5"
#define MIXER_SWITCH_IN_TEL_6             8
#define MIXER_SWITCH_IN_TEL_6_NAME        "TEL6"
/* outputs */
#define MIXER_SWITCH_OUT_TEL_DL_SCON_1         1
#define MIXER_SWITCH_OUT_TEL_DL_SCON_1_NAME    "TEL_DL_SCON1"
#define MIXER_SWITCH_OUT_TEL_DL_HS             2
#define MIXER_SWITCH_OUT_TEL_DL_HS_NAME        "TEL_DL_HS"
#define MIXER_SWITCH_OUT_TEL_DL_SCON_2         3
#define MIXER_SWITCH_OUT_TEL_DL_SCON_2_NAME    "TEL_DL_SCON2"
#define MIXER_SWITCH_OUT_TDM_TEL               4
#define MIXER_SWITCH_OUT_TDM_TEL_NAME          "TDM_TEL"

/* Mixer switch bluetooth handsfree */
#define MIXER_SWITCH_BT_HANDSFREE       "MS_BT_HF"
/* inputs */
#define MIXER_SWITCH_IN_TEL_UL_HF_1       1
#define MIXER_SWITCH_IN_TEL_UL_HF_1_NAME  "TEL_UL_HF1"
#define MIXER_SWITCH_IN_TEL_UL_HF_2       2
#define MIXER_SWITCH_IN_TEL_UL_HF_2_NAME  "TEL_UL_HF2"
#define MIXER_SWITCH_IN_TEL_DL_HS         3
#define MIXER_SWITCH_IN_TEL_DL_HS_NAME    "TEL_DL_HS"
#define MIXER_SWITCH_IN_BT_SCO1_DL        4
#define MIXER_SWITCH_IN_BT_SCO1_DL_NAME   "BT_SCO1_DL"
#define MIXER_SWITCH_IN_BT_SCO2_DL        5
#define MIXER_SWITCH_IN_BT_SCO2_DL_NAME   "BT_SCO2_DL"
/* outputs */
#define MIXER_SWITCH_OUT_BT_SCO1_UL       1
#define MIXER_SWITCH_OUT_BT_SCO1_UL_NAME  "BT_SCO1_UL"
#define MIXER_SWITCH_OUT_BT_SCO2_UL       2
#define MIXER_SWITCH_OUT_BT_SCO2_UL_NAME  "BT_SCO2_UL"
#define MIXER_SWITCH_OUT_TEL_DL_HF_1      3
#define MIXER_SWITCH_OUT_TEL_DL_HF_1_NAME "TEL_DL_HF1"
#define MIXER_SWITCH_OUT_TEL_DL_HF_2      4
#define MIXER_SWITCH_OUT_TEL_DL_HF_2_NAME "TEL_DL_HF2"
#define MIXER_SWITCH_OUT_TEL_UL_HS        5
#define MIXER_SWITCH_OUT_TEL_UL_HS_NAME   "TEL_UL_HS"

/* Mixer switch Phone uplink */
#define MIXER_SWITCH_PHONE_UL           "MS_PH_UL"
/* inputs */
#define MIXER_SWITCH_IN_TEL_UL_HS         1
#define MIXER_SWITCH_IN_TEL_UL_HS_NAME    "TEL_UL_HS"
#define MIXER_SWITCH_IN_SSE_UL_1          2
#define MIXER_SWITCH_IN_SSE_UL_1_NAME     "SSE_UL_1"
#define MIXER_SWITCH_IN_TEL_UL_SCON1      3
#define MIXER_SWITCH_IN_TEL_UL_SCON1_NAME "TEL_UL_SCON1"
#define MIXER_SWITCH_IN_TEL_UL_SCON2      4
#define MIXER_SWITCH_IN_TEL_UL_SCON2_NAME "TEL_UL_SCON2"

/* outputs */
#define MIXER_SWITCH_OUT_SDS_UL           1
#define MIXER_SWITCH_OUT_SDS_UL_NAME      "SDS_UL"
#define MIXER_SWITCH_OUT_MIC_2            2
#define MIXER_SWITCH_OUT_MIC_2_NAME       "MIC2"
#define MIXER_SWITCH_OUT_TEL_UL_NAD       3
#define MIXER_SWITCH_OUT_TEL_UL_NAD_NAME  "TEL_UL_NAD"
#define MIXER_SWITCH_OUT_TEL_UL_HF_1      4
#define MIXER_SWITCH_OUT_TEL_UL_HF_1_NAME "TEL_UL_HF1"
#define MIXER_SWITCH_OUT_TEL_UL_HF_2      5
#define MIXER_SWITCH_OUT_TEL_UL_HF_2_NAME "TEL_UL_HF2"
#define MIXER_SWITCH_OUT_MIC_4            6
#define MIXER_SWITCH_OUT_MIC_4_NAME       "MIC4"
#define MIXER_SWITCH_OUT_MIC_3            7
#define MIXER_SWITCH_OUT_MIC_3_NAME       "MIC3"
#define MIXER_SWITCH_OUT_MIC_5            8
#define MIXER_SWITCH_OUT_MIC_5_NAME       "MIC5"
#define MIXER_SWITCH_OUT_MIC_6            9
#define MIXER_SWITCH_OUT_MIC_6_NAME       "MIC6"

/* Mixer switch signal dumper */
#define MIXER_SWITCH_SIGNAL_DUMP        "MS_SD"
/* inputs */
#define MIXER_SWITCH_IN_NAD_UL            1
#define MIXER_SWITCH_IN_NAD_UL_NAME       "NAD_UL"
#define MIXER_SWITCH_IN_NAD_DL            2
#define MIXER_SWITCH_IN_NAD_DL_NAME       "NAD_DL"
#define MIXER_SWITCH_IN_BT_UL             3
#define MIXER_SWITCH_IN_BT_UL_NAME        "BT_UL"
#define MIXER_SWITCH_IN_BT_DL             4
#define MIXER_SWITCH_IN_BT_DL_NAME        "BT_DL"
#define MIXER_SWITCH_IN_RCC_PLAY          5
#define MIXER_SWITCH_IN_RCC_PLAY_NAME     "RCC_PLAY"
#define MIXER_SWITCH_IN_RCC_CAP           6
#define MIXER_SWITCH_IN_RCC_CAP_NAME      "RCC_CAP"
/* outputs */
#define MIXER_SWITCH_OUT_DUMP_1           1
#define MIXER_SWITCH_OUT_DUMP_1_NAME      "DUMP1"
#define MIXER_SWITCH_OUT_DUMP_2           2
#define MIXER_SWITCH_OUT_DUMP_2_NAME      "DUMP2"
#define MIXER_SWITCH_OUT_DUMP_3           3
#define MIXER_SWITCH_OUT_DUMP_3_NAME      "DUMP3"
#define MIXER_SWITCH_OUT_DUMP_4           4
#define MIXER_SWITCH_OUT_DUMP_4_NAME      "DUMP4"

#endif /* PCM_MIXER_SLOTS_MIB_H */
