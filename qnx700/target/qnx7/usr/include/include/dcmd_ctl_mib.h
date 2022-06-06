/*
 * Copyright (c) 2015-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef DCMD_CTL_MIB_H_INCLUDED
#define DCMD_CTL_MIB_H_INCLUDED

#include <ioctl.h>

/**
 * This header defines Custom APIs for MIB platform based on the CTL devctl interface.
 * The range of command numbers used is: 0x0000F100 to 0x0000F1FF.
 */

/**
 * Header file version
 */
#define DCMD_CTL_MIB_VERION_MAJOR   1
#define DCMD_CTL_MIB_VERION_MINOR   1

#define MAX_NAME_LENGTH             (256)
#define CMD_READ_ONLY               0
#define CMD_UPDATE_ALL              0xffff
#define RESOURCE_UNAVAILABLE        1

/**
 * ASRC Update Offsets
 */
#define ASRC_BITS                   (1 << 0)
#define ASRC_CHANNELS               (1 << 1)
#define ASRC_IN_FREQ                (1 << 2)
#define ASRC_OUT_FREQ               (1 << 3)
#define ASRC_RATIO_SOURCE           (1 << 4)

/**
 * I2S Update Offsets
 */
#define I2S_TX_MODE                 (1 << 0)
#define I2S_CLOCK_MODE              (1 << 1)
#define I2S_CLOCK_POLARITY          (1 << 2)
#define I2S_BITS                    (1 << 3)
#define I2S_CHANNELS                (1 << 4)
#define I2S_OFFSET                  (1 << 5)
#define I2S_LONG_SYNC               (1 << 6)
#define I2S_NUM_SLOTS               (1 << 7)
#define I2S_SOFT_RESET_REQUIRED     (1 << 8)

/**
 * SFC Update Offsets
 */
#define SFC_IN_CHANNELS             (1 << 0)
#define SFC_OUT_CHANNELS            (1 << 1)
#define SFC_IN_FREQ                 (1 << 2)
#define SFC_OUT_FREQ                (1 << 3)
#define SFC_BITS                    (1 << 4)
#define SFC_SOFT_RESET_REQUIRED     (1 << 5)

/**
 * AFC Update Offsets
 */
#define AFC_CUR_STATE              (1 << 0)
#define AFC_SOFT_RESET_REQUIRED    (1 << 1)
#define AFC_DST_MODULE             (1 << 2)
#define AFC_START_THRESHOLD        (1 << 3)
#define AFC_SRC_BURST              (1 << 4)
#define AFC_THRESHOLD_TYPE         (1 << 5)
#define AFC_PPM_DIFF               (1 << 6)
#define AFC_BITS                   (1 << 7)
#define AFC_CHANNELS               (1 << 8)

/**
 * AMX Update Offsets
 */
#define AMX_IN_STREAM_1             (1 << 0)
#define AMX_IN_STREAM_2             (1 << 1)
#define AMX_IN_STREAM_3             (1 << 2)
#define AMX_IN_STREAM_4             (1 << 3)
#define AMX_SOFT_RESET_REQUIRED     (1 << 4)

/**
 * ADX Update Offsets
 */
#define ADX_OUT_STREAM_1            (1 << 0)
#define ADX_OUT_STREAM_2            (1 << 1)
#define ADX_OUT_STREAM_3            (1 << 2)
#define ADX_OUT_STREAM_4            (1 << 3)
#define ADX_SOFT_RESET_REQUIRED     (1 << 5)

/**
 * ADMAIF defines
 */
#define ADMAIF_AMX_STREAM            (1 << 0)
#define ADMAIF_ADX_STREAM            (1 << 1)
#define ADMAIF_CIF_RX                (1 << 2)

/**
 * MVC defines
 */
#define MVC_BITS                    (1 << 0)
#define MVC_CHANNELS                (1 << 1)
#define MVC_TAR_VOL                 (1 << 2)
#define MVC_MUTE                    (1 << 3)
#define MVC_DURATION                (1 << 4)
#define MVC_CURVE_TYPE              (1 << 5)

/**
 * XBAR defines
 */
#define XBAR_UPDATE                (1 << 0)
#define XBAR_CLEAR                 (1 << 1)
#define MAX_NUM_ROUTES             (ahubrx_maxnum)

/**
 * DMIC Update Offsets
 */
#define DMIC_CHANNELS              (1 << 0)
#define DMIC_BITS                  (1 << 1)
#define DMIC_OSR                   (1 << 2)
#define DMIC_GAIN_TYPE             (1 << 3)

/**
 * DSPK Update Offsets
 */
#define DSPK_CHANNELS              (1 << 0)
#define DSPK_BITS                  (1 << 1)
#define DSPK_OSR                   (1 << 2)

/**
 * Module Active defines
 */
#define I2S_ACTIVE                  (1 << 0)
#define AFC_ACTIVE                  (1 << 1)
#define SFC_ACTIVE                  (1 << 2)
#define AMIXER_TX_ACTIVE            (1 << 3)
#define ASRC_ACTIVE                 (1 << 4)
#define MVC_ACTIVE                  (1 << 5)
#define DMIC_ACTIVE                 (1 << 6)
#define DSPK_ACTIVE                 (1 << 7)

/**
 * Module Reset defines
 */
#define I2S_RESET                  (1 << 0)
#define AFC_RESET                  (1 << 1)
#define SFC_RESET                  (1 << 2)
#define AMIXER_RESET               (1 << 3)
#define ASRC_RESET                 (1 << 4)
#define MVC_RESET                  (1 << 5)
#define DMIC_RESET                 (1 << 6)
#define DSPK_RESET                 (1 << 7)


/**
 * PCM defines
 */
#define PCM_UPDATE_RATE           (1 << 0)
#define PCM_CTRL_DUMP             (1 << 1)

/**
 * AMIXER defines
 */
#define AMIXER_OUTSTREAM            (1 << 0)
#define AMIXER_GAIN                 (1 << 1)
#define AMIXER_PEAK_WINDOW          (1 << 2)
#define AMIXER_DURATION_N3          (1 << 3)

/**
 * Print defines
 */
#define PRINTS_ENABLE             (1 << 0)
#define PRINTS_DISABLE            (1 << 1)
#define VERBOSE_LEVEL             (1 << 2)
#define PRINTS_SHOW               (1 << 3)

#if defined(CONFIG_ARCH_TEGRA_18x_SOC)
enum
{
    ahubrx_admaif1 = 0,
    ahubrx_admaif2,
    ahubrx_admaif3,
    ahubrx_admaif4,
    ahubrx_admaif5,
    ahubrx_admaif6,
    ahubrx_admaif7,
    ahubrx_admaif8,
    ahubrx_admaif9,
    ahubrx_admaif10,
    ahubrx_admaif11,
    ahubrx_admaif12,
    ahubrx_admaif13,
    ahubrx_admaif14,
    ahubrx_admaif15,
    ahubrx_admaif16,
    ahubrx_i2s1,
    ahubrx_i2s2,
    ahubrx_i2s3,
    ahubrx_i2s4,
    ahubrx_i2s5,
    ahubrx_i2s6,
    ahubrx_sfc1,
    ahubrx_sfc2,
    ahubrx_sfc3,
    ahubrx_sfc4,
    ahubrx1_mixer1,
    ahubrx2_mixer1,
    ahubrx3_mixer1,
    ahubrx4_mixer1,
    ahubrx5_mixer1,
    ahubrx6_mixer1,
    ahubrx7_mixer1,
    ahubrx8_mixer1,
    ahubrx9_mixer1,
    ahubrx10_mixer1,
    ahubrx1_dspk1,
    ahubrx1_dspk2,
    ahubrx1_spdif1,
    ahubrx2_spdif1,
    ahubrx_afc1,
    ahubrx_afc2,
    ahubrx_afc3,
    ahubrx_afc4,
    ahubrx_afc5,
    ahubrx_afc6,
    ahubrx_ope1,
    ahubrx_spkprot,
    ahubrx_mvc1,
    ahubrx_mvc2,
    ahubrx1_amx1,
    ahubrx2_amx1,
    ahubrx3_amx1,
    ahubrx4_amx1,
    ahubrx1_amx2,
    ahubrx2_amx2,
    ahubrx3_amx2,
    ahubrx4_amx2,
    ahubrx1_amx3,
    ahubrx2_amx3,
    ahubrx3_amx3,
    ahubrx4_amx3,
    ahubrx_adx1,
    ahubrx_adx2,
    ahubrx_adx3,
    ahubrx_adx4,
    ahubrx1_amx4,
    ahubrx2_amx4,
    ahubrx3_amx4,
    ahubrx4_amx4,
    ahubrx_admaif17,
    ahubrx_admaif18,
    ahubrx_admaif19,
    ahubrx_admaif20,
    ahubrx_asrc1,
    ahubrx_asrc2,
    ahubrx_asrc3,
    ahubrx_asrc4,
    ahubrx_asrc5,
    ahubrx_asrc6,
    ahubrx_asrc7,
    ahubrx_maxnum
} ahubrx;
#else
enum
{
    ahubrx_admaif1 = 0,
    ahubrx_admaif2,
    ahubrx_admaif3,
    ahubrx_admaif4,
    ahubrx_admaif5,
    ahubrx_admaif6,
    ahubrx_admaif7,
    ahubrx_admaif8,
    ahubrx_admaif9,
    ahubrx_admaif10,
    ahubrx_i2s1,
    ahubrx_i2s2,
    ahubrx_i2s3,
    ahubrx_i2s4,
    ahubrx_i2s5,
    ahubrx_sfc1,
    ahubrx_sfc2,
    ahubrx_sfc3,
    ahubrx_sfc4,
    ahubrx1_mixer1,
    ahubrx2_mixer1,
    ahubrx3_mixer1,
    ahubrx4_mixer1,
    ahubrx5_mixer1,
    ahubrx6_mixer1,
    ahubrx7_mixer1,
    ahubrx8_mixer1,
    ahubrx9_mixer1,
    ahubrx10_mixer1,
    ahubrx1_spdif1,
    ahubrx2_spdif1,
    ahubrx_afc1,
    ahubrx_afc2,
    ahubrx_afc3,
    ahubrx_afc4,
    ahubrx_afc5,
    ahubrx_afc6,
    ahubrx_ope1,
    ahubrx_ope2,
    ahubrx_spkprot,
    ahubrx_mvc1,
    ahubrx_mvc2,
    ahubrx1_amx1,
    ahubrx2_amx1,
    ahubrx3_amx1,
    ahubrx4_amx1,
    ahubrx1_amx2,
    ahubrx2_amx2,
    ahubrx3_amx2,
    ahubrx4_amx2,
    ahubrx_adx1,
    ahubrx_adx2,
    ahubrx_maxnum
} ahubrx;
#endif

#if defined(CONFIG_ARCH_TEGRA_18x_SOC)
typedef enum _ahubtx
{
    ahubtx_admaif1 = 0,
    ahubtx_admaif2,
    ahubtx_admaif3,
    ahubtx_admaif4,
    ahubtx_admaif5,
    ahubtx_admaif6,
    ahubtx_admaif7,
    ahubtx_admaif8,
    ahubtx_admaif9,
    ahubtx_admaif10,
    ahubtx_admaif11,
    ahubtx_admaif12,
    ahubtx_admaif13,
    ahubtx_admaif14,
    ahubtx_admaif15,
    ahubtx_admaif16,
    ahubtx_i2s1,
    ahubtx_i2s2,
    ahubtx_i2s3,
    ahubtx_i2s4,
    ahubtx_i2s5,
    ahubtx_i2s6,
    ahubtx_sfc1,
    ahubtx_sfc2,
    ahubtx_sfc3,
    ahubtx_sfc4,
    ahubtx1_mixer1,
    ahubtx2_mixer1,
    ahubtx3_mixer1,
    ahubtx4_mixer1,
    ahubtx5_mixer1,
    ahubtx1_amx1,
    ahubtx1_amx2,
    ahubtx1_amx3,
    ahubtx1_amx4,
    ahubtx_arad1,
    ahubtx1_spdif1,
    ahubtx2_spdif1,
    ahubtx_afc1,
    ahubtx_afc2,
    ahubtx_afc3,
    ahubtx_afc4,
    ahubtx_afc5,
    ahubtx_afc6,
    ahubtx_ope1,
    ahubtx_spkprot,
    ahubtx_mvc1,
    ahubtx_mvc2,
    ahubtx1_iqc1,
    ahubtx2_iqc1,
    ahubtx1_iqc2,
    ahubtx2_iqc2,
    ahubtx_dmic1,
    ahubtx_dmic2,
    ahubtx_dmic3,
    ahubtx_dmic4,
    ahubtx1_adx1,
    ahubtx2_adx1,
    ahubtx3_adx1,
    ahubtx4_adx1,
    ahubtx1_adx2,
    ahubtx2_adx2,
    ahubtx3_adx2,
    ahubtx4_adx2,
    ahubtx1_adx3,
    ahubtx2_adx3,
    ahubtx3_adx3,
    ahubtx4_adx3,
    ahubtx1_adx4,
    ahubtx2_adx4,
    ahubtx3_adx4,
    ahubtx4_adx4,
    ahubtx_admaif17,
    ahubtx_admaif18,
    ahubtx_admaif19,
    ahubtx_admaif20,
    ahubtx_asrc1,
    ahubtx_asrc2,
    ahubtx_asrc3,
    ahubtx_asrc4,
    ahubtx_asrc5,
    ahubtx_asrc6,
    ahubtx_maxnum,
    AHUBTX_INVALID
} ahubtx;
#else
typedef enum _ahubtx
{
    ahubtx_admaif1 = 0,
    ahubtx_admaif2,
    ahubtx_admaif3,
    ahubtx_admaif4,
    ahubtx_admaif5,
    ahubtx_admaif6,
    ahubtx_admaif7,
    ahubtx_admaif8,
    ahubtx_admaif9,
    ahubtx_admaif10,
    ahubtx_i2s1,
    ahubtx_i2s2,
    ahubtx_i2s3,
    ahubtx_i2s4,
    ahubtx_i2s5,
    ahubtx_sfc1,
    ahubtx_sfc2,
    ahubtx_sfc3,
    ahubtx_sfc4,
    ahubtx1_mixer1,
    ahubtx2_mixer1,
    ahubtx3_mixer1,
    ahubtx4_mixer1,
    ahubtx5_mixer1,
    ahubtx1_amx1,
    ahubtx1_amx2,
    ahubtx1_spdif1,
    ahubtx2_spdif1,
    ahubtx_afc1,
    ahubtx_afc2,
    ahubtx_afc3,
    ahubtx_afc4,
    ahubtx_afc5,
    ahubtx_afc6,
    ahubtx_ope1,
    ahubtx_ope2,
    ahubtx_spkprot,
    ahubtx_mvc1,
    ahubtx_mvc2,
    ahubtx1_iqc1,
    ahubtx2_iqc1,
    ahubtx1_iqc2,
    ahubtx2_iqc2,
    ahubtx_dmic1,
    ahubtx_dmic2,
    ahubtx_dmic3,
    ahubtx1_adx1,
    ahubtx2_adx1,
    ahubtx3_adx1,
    ahubtx4_adx1,
    ahubtx1_adx2,
    ahubtx2_adx2,
    ahubtx3_adx2,
    ahubtx4_adx2,
    ahubtx_maxnum,
    AHUBTX_INVALID
} ahubtx;
#endif

/**
 * Ahub components
 */
typedef struct asrc {
    int active;
    int bits;
    int channels;
    int cmd;
    int in_freq;
    int index;
    int out_freq;
    int ratio_source;
} asrc_t;

typedef struct i2s {
    int index;
    int cmd;
    int tx_mode;        /* 0: I2S 1: TDM*/
    int clock_mode;     /* 0: slave 1: master*/
    int clock_polarity; /* 0: negative edge 1: positive edge*/
    int bits;
    int channels;
    int offset;
    int long_sync;
    int num_slots;
    int active;
} i2s_t;

typedef struct sfc {
    int index;
    int cmd;
    int in_channels;
    int out_channels;
    int in_freq;
    int out_freq;
    int bits;
    int active;
} sfc_t;

typedef struct amx {
    int index;
    int cmd;
    int enable_in[4];
} amx_t;

typedef struct adx {
    int index;
    int cmd;
    int enable_out[4];
} adx_t;

typedef struct afc {
    int index;
    int cmd;
    int destination_module;
    int start_threshold;
    int src_burst;
    int threshold_type;
    int ppm_diff;
    int bits;
    int channels;
    int active;
} afc_t;

typedef struct mvc {
    int index;
    int cmd;
    int bits;
    int channels;
    double tar_vol;
    unsigned char mute;
    unsigned char curve_type;
    int duration;
} mvc_t;

typedef struct xbar {
    int rx_port[MAX_NUM_ROUTES];
    int cmd;
} xbar_t;

typedef struct dmic {
    int index;
    int cmd;
    int channels;
    int bits;
    int osr;
    int gain_type;
    int active;
} dmic_t;

typedef struct dspk {
    int index;
    int cmd;
    int channels;
    int bits;
    int osr;
    int active;
} dspk_t;

typedef struct common_cmd {
    int index;
    int value;
    int cmd;
} common_cmd_t;

typedef struct amixer {
    int index;
    int outstream;
    float gain;
    int peak_window;
    int duration_n3;
    int cmd;
    int active;
} amixer_t;

typedef struct pcm {
    char name[MAX_NAME_LENGTH];
    int rate;
    int enable_dump;
    int cmd;
} pcm_t;

typedef struct prints {
    int reg;
    int cmd;
} prints_t;

/**
 * Commands
 *
 */
#define DCMD_CTL_AHUB_I2S    _IOWR( 'Z', 0x0000F102, struct i2s)
#define DCMD_CTL_AHUB_SFC    _IOWR( 'Z', 0x0000F103, struct sfc)
#define DCMD_CTL_AHUB_XBAR   _IOWR( 'Z', 0x0000F104, struct xbar)
#define DCMD_CTL_PCM         _IOWR( 'Z', 0x0000F105, struct pcm)
#define DCMD_CTL_PRINTS      _IOWR( 'Z', 0x0000F106, struct prints)
#define DCMD_CTL_AHUB_AFC    _IOWR( 'Z', 0x0000F107, struct afc)
#define DCMD_CTL_AHUB_ACTIVE _IOWR( 'Z', 0x0000F110, struct common_cmd)
/* Parker specific DCMDs from here, to maintain backward compatibility */
#define DCMD_CTL_AHUB_RESET  _IOWR( 'Z', 0x0000F111, struct common_cmd)
#define DCMD_CTL_AHUB_DMIC   _IOWR( 'Z', 0x0000F112, struct dmic)
#define DCMD_CTL_AHUB_AMIXER _IOWR( 'Z', 0x0000F113, struct amixer)
#define DCMD_CTL_AHUB_ASRC   _IOWR( 'Z', 0x0000F114, struct asrc)
#define DCMD_CTL_AHUB_MVC    _IOWR( 'Z', 0x0000F115, struct mvc)
#define DCMD_CTL_AHUB_DSPK   _IOWR( 'Z', 0x0000F116, struct dspk)
/* ID 0x0000F120 is reserved for virtualization use-case */


#endif /* DCMD_CTL_MIB_H_INCLUDED */
