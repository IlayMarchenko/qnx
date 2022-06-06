/*
 * Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef DCMD_PCM_MIB_H_INCLUDED
#define DCMD_PCM_MIB_H_INCLUDED

#include <ioctl.h>

/**
 * This header defines Custom APIs for MIB platform based on the PCM devctl interface.
 * The range of command numbers used is: 0x0000F000 to 0x0000F0FF.
 */

/**
 * Header file version
 */
#define DCMD_PCM_MIB_VERION_MAJOR   1
#define DCMD_PCM_MIB_VERION_MINOR   0

/**
 * Codec types
 */
enum
{
    CODEC_TYPE_UNKNOWN = 0x0,
    CODEC_TYPE_CDDA,
    CODEC_TYPE_MPA,
    CODEC_TYPE_MP3,
    CODEC_TYPE_AC3,
    CODEC_TYPE_DTS,
    CODEC_TYPE_AACLC,
    CODEC_TYPE_AACHE,
    CODEC_TYPE_WMA,
    CODEC_TYPE_WMALSL,
    CODEC_TYPE_WMAPRO,
    CODEC_TYPE_SBC,
    CODEC_TYPE_FLAC,
    CODEC_TYPE_VORBIS,
    CODEC_TYPE_ALAC,
    CODEC_TYPE_MAX
};

/**
 * Media types
 */
#define MEDIA_TYPE_UNDEF            0x00
#define MEDIA_TYPE_DVD              0x12

/**
 * Bit-wise ASAD value definitons as per the MOST Audio sepc version 3.5
 */
#define PCM_CONF_100                0x20  /*  [ 0 0 C 0   0  0  0   0   ] = [0 0 1 0 0 0 0 0] = 20 */
#define PCM_CONF_110                0x30  /*  [ 0 0 C LFE 0  0  0   0   ] = [0 0 1 1 0 0 0 0] = 30 */
#define PCM_CONF_200                0xC0  /*  [ L R 0 0   0  0  0   0   ] = [1 1 0 0 0 0 0 0] = C0 */
#define PCM_CONF_210                0xD0  /*  [ L R 0 LFE 0  0  0   0   ] = [1 1 0 1 0 0 0 0] = D0 */
#define PCM_CONF_201                0xC8  /*  [ L R 0 0   BL 0  0   0   ] = [1 1 0 0 1 0 0 0] = C8 */
#define PCM_CONF_211                0xD8  /*  [ L R 0 LFE BL 0  0   0   ] = [1 1 0 1 1 0 0 0] = D8 */
#define PCM_CONF_202                0xCC  /*  [ L R 0 0   BL BR 0   0   ] = [1 1 0 0 1 1 0 0] = CC */
#define PCM_CONF_212                0xDC  /*  [ L R 0 LFE BL BR 0   0   ] = [1 1 0 1 1 1 0 0] = DC */
#define PCM_CONF_300                0xE0  /*  [ L R C 0   0  0  0   0   ] = [1 1 1 0 0 0 0 0] = E0 */
#define PCM_CONF_310                0xF0  /*  [ L R C LFE 0  0  0   0   ] = [1 1 1 1 0 0 0 0] = F0 */
#define PCM_CONF_301                0xE8  /*  [ L R C 0   BL 0  0   0   ] = [1 1 1 0 1 0 0 0] = E8 */
#define PCM_CONF_311                0xF8  /*  [ L R C LFE BL 0  0   0   ] = [1 1 1 1 1 0 0 0] = F8 */
#define PCM_CONF_302                0xEC  /*  [ L R C 0   BL BR 0   0   ] = [1 1 1 0 1 1 0 0] = EC */
#define PCM_CONF_312                0xFC  /*  [ L R C LFE BL BR 0   0   ] = [1 1 1 1 1 1 0 0] = FC */
#define PCM_CONF_304                0xEF  /*  [ L R C 0   BL BR BLC BRC ] = [1 1 1 0 1 1 1 1] = EF */
#define PCM_CONF_314                0xFF  /*  [ L R C LFE BL BR BLC BRC ] = [1 1 1 1 1 1 1 1] = FF */

/**
 * Encryption Method
 */
#define CA_METHOD_NONE              0x0
#define CA_METHOD_CSS               0x1
#define CA_METHOD_AACS              0x2

/**
 * Meta data for SAD Header
 */
typedef struct sad_metadata {
    unsigned char  media_type;
    unsigned char  pcm_conf;
    unsigned char  ca_method;
    unsigned char  codec_type;
    unsigned char  sample_width;
    unsigned int  sample_rate;
    unsigned int  bit_rate;
} sad_metadata_t;

/**
 * Commands
 *
 */
#define DCMD_PCM_GET_SAD_METADATA   _IOR( 'Z', 0x0000F000, struct sad_metadata)
#define DCMD_PCM_SET_SAD_METADATA   _IOW( 'Z', 0x0000F001, struct sad_metadata)

#endif /* DCMD_PCM_MIB_H_INCLUDED */
