/* Copyright (c) 2015-2018, NVIDIA CORPORATION.  All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */
#ifndef _IMG_DEV_H_
#define _IMG_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_surface.h"
#include "nvmedia_image.h"
#include "nvmedia_icp.h"
#include "nvmedia_isc.h"
#include "dev_error.h"

/* Major Version number */
#define EXTIMGDEV_VERSION_MAJOR   1
/* Minor Version number */
#define EXTIMGDEV_VERSION_MINOR   14

#define MAX_AGGREGATE_IMAGES 4

#define CAM_ENABLE_DEFAULT 0x0001  // only enable cam link 0
#define CAM_MASK_DEFAULT   0x0000  // do not mask any link
#define CSI_OUT_DEFAULT    0x3210  // cam link i -> csiout i

/* Count enabled camera links */
#define EXTIMGDEV_MAP_COUNT_ENABLED_LINKS(enable) \
             ((enable & 0x1) + ((enable >> 4) & 0x1) + \
             ((enable >> 8) & 0x1) + ((enable >> 12) & 0x1))
/* Convert aggegate number to cam_enable */
#define EXTIMGDEV_MAP_N_TO_ENABLE(n) \
             ((((1 << n) - 1) & 0x0001) + ((((1 << n) - 1) << 3) &0x0010) + \
              ((((1 << n) - 1) << 6) & 0x0100) + ((((1 << n) - 1) << 9) & 0x1000))

/* Macro to set the ExtImgDevVersion number */
#define EXTIMGDEV_SET_VERSION(x, _major, _minor) \
    x.major = _major; \
    x.minor = _minor;

typedef void ExtImgDevDriver;

typedef struct {
    /* Major version */
    uint8_t major;
    /* Minor version */
    uint8_t minor;
} ExtImgDevVersion;

typedef struct {
    uint32_t                enable; // camera[3..0] enable, value:0/1. eg 0x1111
    uint32_t                mask;   // camera[3..0] mask,   value:0/1. eg 0x0001
    uint32_t                csiOut; // camera[3..0] csi outmap, value:0/1/2/3. eg. 0x3210
} ExtImgDevMapInfo;

typedef struct {
    char                       *moduleName;
    char                       *resolution;
    char                       *inputFormat;
    char                       *interface;
    uint32_t                    i2cDevice;
    uint32_t                    desAddr;
    uint32_t                    brdcstSerAddr;
    uint32_t                    serAddr[MAX_AGGREGATE_IMAGES];
    uint32_t                    brdcstSensorAddr;
    uint32_t                    sensorAddr[MAX_AGGREGATE_IMAGES];
    uint32_t                    e2pPhysicalAddr;
    uint32_t                    e2pAddr[MAX_AGGREGATE_IMAGES];
    uint32_t                    sensorsNum;
    NvMediaBool                 enableEmbLines; /* TBD : this flag will be optional for
                                                 * on chip ISP in the sensor
                                                 * such as OV10635,
                                                 * if not, this flag is mandatory */
    char                       *board; /* Optional */
    NvMediaBool                 initialized; /* Optional:
                                              * Already initialized doesn't need to */
    NvMediaBool                 slave;  /* Optional :
                                         * Doesn't need to control sensor/serializer
                                         * through aggregator */
    NvMediaBool                 enableSimulator; /* Optional
                                                  * This flag is not to open actual
                                                  * isc-dev, it is for running isc
                                                  * without actual device. */
    ExtImgDevMapInfo           *camMap;
    NvMediaBool                 enableVirtualChannels;
    uint32_t                    reqFrameRate; /* Optional
                                               * default frame rate will be 30fps. */
    NvMediaBool                 selfTestFlag; /* Optional
                                               * sensor self safety test flag
                                               * currently supported only by OV10640 */
    NvMediaBool                 enableExtSync; /* Enable external synchronization */
    float_t                     dutyRatio; /* FRSYNC duty ratio */
    NvMediaBool                 isCaptureS16Format; /* Capture frmt S16/U16: 0: (U16, Xavier), 1: (S16, Parker) */
    char                       *sensorIdentifier[MAX_AGGREGATE_IMAGES];
} ExtImgDevParam;

typedef struct {
    uint16_t              width;
    uint16_t              height;
    uint32_t              embLinesTop;
    uint32_t              embLinesBottom;
    NvMediaBool           embDataType; /* 0 : EMB coming with pixel data
                                          1 : EMB coming in CSI packet with different data type */
    NvMediaICPInputFormatType   inputFormatType;
    NvMediaBitsPerPixel         bitsPerPixel;
    NvMediaRawPixelOrder        pixelOrder;
    NvMediaICPInterfaceType     interface;
    NvMediaICPCsiPhyMode        phyMode;
    NvMediaBool                 doubledPixel; /* for raw11x2 or raw16 */
    uint32_t                vcId[NVMEDIA_ICP_MAX_VIRTUAL_GROUPS];
    uint32_t                frameRate;
    uint32_t                pixelFrequency; /* either calculated by (VTS * HTS * frame rate) * sensorsNum,
                                                   or actual PCLK * sensorsNum, unit is Hz */
    uint32_t                mipiSpeed[2];   /* in a case of fixed MIPI speed regardless of the sensor module in kHz
                                             index 0 is for DPHY, index 1 is for CPHY */
    NvMediaBool             enableExtSync;  /* Enable external synchronization */
    float_t                 dutyRatio;      /* FRSYNC duty ratio */
    uint8_t                 tpgEnable;      /* Enable tpg for user to enable tpgEnable flag in NvMediaICPSettings */
} ExtImgDevProperty;

typedef struct {
    ExtImgDevDriver            *driver;
    ExtImgDevProperty           property;
    // ISC
    NvMediaISCRootDevice       *iscRoot;
    NvMediaISCDevice           *iscDeserializer;
    NvMediaISCDevice           *iscSerializer[MAX_AGGREGATE_IMAGES];
    NvMediaISCDevice           *iscSensor[MAX_AGGREGATE_IMAGES];
    NvMediaISCDevice           *iscBroadcastSerializer;
    NvMediaISCDevice           *iscBroadcastSensor;
    NvMediaISCDevice           *iscEeprom[MAX_AGGREGATE_IMAGES];
    uint32_t                    sensorsNum;
    uint32_t                    remapIdx[MAX_AGGREGATE_IMAGES];
    NvMediaBool                 simulator;
} ExtImgDevice;

ExtImgDevice *
ExtImgDevInit(ExtImgDevParam *configParam);

void
ExtImgDevDeinit(ExtImgDevice *device);

NvMediaStatus
ExtImgDevStart(ExtImgDevice *device);

void
ExtImgDevStop(ExtImgDevice *device);

NvMediaStatus
ExtImgDevGetError(
    ExtImgDevice *device,
    uint32_t *link,
    ExtImgDevFailureType *errorType);

NvMediaStatus
ExtImgDevRegisterCallback(
    ExtImgDevice *device,
    uint32_t sigNum,
    void (*cb)(void *),
    void *context);

/*
 * Possible values are:
 *      NVMEDIA_STATUS_OK
 *      NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 *      NVMEDIA_STATUS_INCOMPATIBLE_VERSION if the client version does
 *                                          not match with the core version
 */
NvMediaStatus
ExtImgDevCheckVersion(
    ExtImgDevVersion *version
);

/**
 * Provides change history for the ExtImgDev API.
 *
 * <b> Version 1.0 </b> April 11, 2016
 * - Initial release
 *
 * <b> Version 1.1 </b> June 16, 2016
 * - Added \ref ExtImgDevCheckVersion API
 *
 * <b> Version 1.2 </b> June 21, 2016
 * - Added \ref enableVirtualChannels and vcId variables
 *
 * <b> Version 1.3 </b> June 28, 2016
 * - Added \ref ExtImgDevCheckVersion API
 *
 * <b> Version 1.4 </b> Sep 16, 2016
 * - Added reqFrameRate in \ref ExtImgDevParam
 * - Added frameRate in \ref ExtImgDevProperty
 *
 * <b> Version 1.5 </b> Oct 11, 2016
 * - Added pixelFrequency in \ref ExtImgDevProperty
 *
 * <b> Version 1.6 </b> Oct 25, 2016
 * - Changed \ref ExtImgDevStart function return type from void to NvMediaStatus
 * - Added remapIdx & simulator variables in \ref ExtImgDevice
 *
 * <b> Version 1.7 </b> Feb 24, 2017
 * - Added selfTestFlag in \ref ExtImgDevParam
 *
 * <b> Version 1.8 </b> March 19, 2017
 * - Added enableExtSync in \ref ExtImgDevParam and ExtImgDevProperty
 * - Added dutyRatio in \ref ExtImgDevParam and ExtImgDevProperty
 *
 * <b> Version 1.9 </b> March 19, 2017
 * - Added tpgEnable in \ref ExtImgDevParam for user to set tpg flag
 * - Use fixed-size type instead of standard C type
 *
 * <b> Version 1.10 </b> September 21, 2017
 * - Added embDataType in \ref ExtImgDevProperty to indicate the embedded data coming in CSI packets
 *
 * <b> Version 1.11 </b> January 8, 2018
 * - Added e2pPhysicalAddr and e2pAddr in \ref ExtImgDevParam
 * - Added iscEeprom in \ref ExtImgDevice
 *
 * <b> Version 1.12 </b> January 13, 2018
 * - Added phyMode in \ref ExtImgDevProperty to indicate DPHY or CPHY mode
 *
 * <b> Version 1.13 </b> March 21, 2018
 * - Added mipiSpeed in \ref ExtImgDevProperty to set the mipi speed
 *
 * <b> Version 1.14 </b> July 26, 2018
 * - Added sensorIdentifier in \ref ExtImgDevProperty to set string identifier for the image sensor
 */

#ifdef __cplusplus
};      /* extern "C" */
#endif

#endif /* _IMG_DEV_H_ */
