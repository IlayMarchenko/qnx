/* Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

#ifndef _NV_SENSOR_CTRL_H
#define _NV_SENSOR_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_image.h"
#include "nvmedia_isc.h"


/* Sensor Control Major Version Number */
#define NV_SENSOR_CTRL_VERSION_MAJOR   1
/* Sensor Control Minor Version Number */
#define NV_SENSOR_CTRL_VERSION_MINOR   0

/* Sensor Control Version Info */
#define NV_SENSORCTRL_VERSION_INFO   (('N' << 24) | ('V' << 16) | \
                                     (NV_SENSOR_CTRL_VERSION_MAJOR << 8) | \
                                     NV_SENSOR_CTRL_VERSION_MINOR)
/* Sensor Exposure Modes*/
#define EXP_MODE_T1 (1 << 0)
#define EXP_MODE_T2 (1 << 1)
#define EXP_MODE_T3 (1 << 2)
#define EXP_MODE_HDR (EXP_MODE_T1 |\
                      EXP_MODE_T2 |\
                      EXP_MODE_T3)

/**
 * \brief Holds Sensor Control settings.
 */
typedef struct {
    /**  Holds capture module name */
    char                       *moduleName;
    /**  Holds capture frame resolution */
    char                       *resolution;
    /**  Holds capture frame format */
    char                       *inputFormat;
    /**  Holds capture interface */
    char                       *interface;
    /**  Holds i2c device for configuring CSI device */
    unsigned int                i2cDevice;
    /**  Holds de-serializer device address */
    unsigned int                desAddr;
    /**  Holds serializer device address */
    unsigned int                serAddr;
    /**  Holds sensor device address */
    unsigned int                sensorAddr;
    /**  Holds capture image top embedded lines */
    unsigned int                embeddedLinesTop;
    /**  Holds capture image bottom embedded lines */
    unsigned int                embeddedLinesBottom;
    /**  Holds flag to enable simulator */
    NvMediaBool                 enableSimulator;
    /**  Optional flag to set capture frame rate
     *  If zero, default supported frame rate will be used */
    unsigned int                frameRate;
    /**  Optional flag to set capture bayer order
     *   If NULL, default supported bayer order will be used */
    char                       *bayerOrder;
} NvSensorCtrlParams;

/**
 * \brief Holds Sensor Property
 */
typedef struct {
    /**  Holds capture image width */
    unsigned int                width;
    /**  Holds capture image height */
    unsigned int                height;
    /**  Holds capture image frame rate */
    unsigned int                frameRate;
    /**  Holds capture image top embedded lines */
    unsigned int                embLinesTop;
    /**  Holds capture image bottom embedded lines */
    unsigned int                embLinesBottom;
    /**  Holds capture image embedded data type */
    unsigned int                embDataType;
    /**  Holds capture image format type */
    NvMediaICPInputFormatType   inputFormatType;
    /**  Holds capture image number of bits per pixel */
    NvMediaBitsPerPixel         bitsPerPixel;
    /**  Holds capture image raw pixel order */
    NvMediaRawPixelOrder        pixelOrder;
    /**  Holds simulator mode flag */
    NvMediaBool                 simulator;
} NvSensorProperty;


/**
 * \brief Holds SensorControl Device
 */
typedef struct {
    /**  Holds sensor device's handle */
    NvMediaISCDevice   *iscSensor;
    /**  Holds sensor properties */
    NvSensorProperty    property;
} NvSensorCtrlDevice;


/**
 * \brief Initialize the SensorControl driver.
 * \param[in] versionInfo to be set to NV_SENSORCTRL_VERSION_INFO
 * \param[in] params SensorControl settings
 * \return \ref NvSensorCtrlDevice The new SensorControl Device handle or NULL if unsuccessful.
 */
NvSensorCtrlDevice *
NvSensorCtrlInit(
    unsigned int versionInfo,
    NvSensorCtrlParams *params
);


/**
 * \brief Set requested Exposure Mode
 * \param[in] device  SensorControl device handle
 * \param[in] expMode Exposure Mode to be set
 *            valid values: EXP_MODE_T1, EXP_MODE_T2,
 *                          EXP_MODE_T3, EXP_MODE_HDR
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the device pointer or exposureMode is invalid.
 * \n \ref NVMEDIA_STATUS_NOT_INITIALIZED if the sensor control device is not initilalized.
 * \n \ref NVMEDIA_STATUS_ERROR when no other error code applies (A catch-all error).
 */
NvMediaStatus
NvSensorCtrlSetExpMode(
    NvSensorCtrlDevice *device,
    unsigned int expMode
);


/**
 * \brief Start the SensorControl driver.
 * \param[in] device SensorControl device handle
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the device pointer is invalid.
 * \n \ref NVMEDIA_STATUS_NOT_INITIALIZED if the sensor control device is not initilalized.
 * \n \ref NVMEDIA_STATUS_ERROR when no other error code applies (A catch-all error).
 */
NvMediaStatus
NvSensorCtrlStart(
    NvSensorCtrlDevice *device
);


/**
 * \brief Stop and de-initiliatize the SensorControl driver.
 * \param[in] device SensorControl device handle
 */
void
NvSensorCtrlFini(
    NvSensorCtrlDevice *device
);

/**
 * Provides change history for the NvSensorCtrl API.
 *
 * <b> Version 1.0 </b> March 07, 2017
 * - Initial release
 *
 */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NV_SENSOR_CTRL_H */
