/*
 * Copyright (c) 2015-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Sensor Control (ISC)</b>
 *
 * This file contains the Image Sensor Control API.
 */

#ifndef _NVMEDIA_ISC_H
#define _NVMEDIA_ISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_icp.h"

/**
 * \defgroup nvmedia_isc_api Image Sensor Control (ISC)
 *
 * The Image Sensor Control API encompasses all NvMedia I2C control related
 * functions. This includes the necessary programming of all I2C controlled components
 * such as aggregators, serializers, bridges and image sensors.
 *
 * NvMediaISC provides a transaction based approach of controlling the devices
 * attached to the I2C port of the Tegra device.
 *
 * NvMediaISC needs a device driver for each attached device. This provides the
 * flexibility of adding new devices easily.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/**
 * \defgroup nvmedia_isc_types Basic ISC Types
 * The Image Sensor Control API provides common ISC processing functions.
 * @ingroup basic_api_top
 *
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_ISC_VERSION_MAJOR   2
/** \brief Minor Version number */
#define NVMEDIA_ISC_VERSION_MINOR   4

/** \brief Device address to use for an ISC simulator device. Select the
 * NVMEDIA_ISC_I2C_SIMULATOR port to use simulator mode for all devices. */
#define NVMEDIA_ISC_SIMULATOR_ADDRESS   0xFF1
/** Bits reserved to contain I2C bus number in `ISC_RDEV_CFG(csi, i2c)`. */
#define RDEV_CFG_I2C_BITS           8
/** Bits reserved to contain CSI port in `ISC_SLV_RDEV_CFG(csi, i2c)`. */
#define RDEV_CFG_CSI_BITS           (RDEV_CFG_I2C_BITS + 8)
/** Bit reserved to contain slave mode flag in `ISC_SLV_RDEV_CFG(csi, i2c)`. */
#define RDEV_CFG_SLV_BIT            (RDEV_CFG_CSI_BITS + 1)

/** \brief Macro to create root device configuration
 * to generate the configuration of the root device by its connected CSI port
 * and I2C bus.
 * \param[in] csi The CSI port number defined in NvMediaICPInterfaceType.
 * \param[in] i2c The I2C bus number defined in NvMediaISC_I2CPort.
 */
#define ISC_RDEV_CFG(csi, i2c)   (((uint32_t)(csi) << RDEV_CFG_I2C_BITS) | (i2c))

/** \brief Extended macro to create root device configuration
 * to generate the configuration of the root device by its connected CSI port
 * and I2C bus with an option to disable power control from root device.
 * \param[in] csi The CSI port number defined in NvMediaICPInterfaceType.
 * \param[in] i2c The I2C bus number defined in NvMediaISC_I2CPort.
 * \param[in] disPwrCtrl The flag to disable power control, possible values are 0 or 1.
 *            If the value is 0,
 *            root device will turn on the power of devices in \ref NvMediaISCRootDeviceCreate.
 *            If the value is 1,
 *            root device won't turn on the power of devices in \ref NvMediaISCRootDeviceCreate.
 */
#define ISC_RDEV_CFG_EX(csi, i2c, disPwrCtrl) \
         ((i2c & 0xffu) | \
          ((uint32_t)(csi & 0xffu) << RDEV_CFG_I2C_BITS) | \
          ((uint32_t)(disPwrCtrl & 1u) << RDEV_CFG_SLV_BIT))

/** \brief Macro to create a slave root device configuration when the application is
 * being run on slave tegra.
 * to generate the configuration of the root device by its connected CSI port
 * and I2C bus.
 * \param[in] csi The CSI port number defined in NvMediaICPInterfaceType.
 * \param[in] i2c The I2C bus number defined in NvMediaISC_I2CPort.
 */
#define ISC_SLV_RDEV_CFG(csi, i2c) \
        ((i2c) | ((uint32_t)(csi) << RDEV_CFG_I2C_BITS) | ((uint32_t)(1u) << RDEV_CFG_CSI_BITS))

/** \brief Macro to initialize \ref NvMediaISCAdvancedConfig parameter.
 * Clears the parameter and updates with the
 * \ref NvMediaISCAdvancedConfig::clientContext pointer.
 * \param[in] cfg The configuration to initialize.
 * \param[in] ctx The \a clientContext pointer to be updated.
 */
#define ADV_CONFIG_INIT(cfg, ctx) \
        do { \
            memset(&cfg, 0, sizeof(cfg)); \
            cfg.clientContext = (void *)(ctx); \
        } while (0)

struct NvMediaISCExposureControl;

struct NvMediaISCWBGainControl;

struct NvMediaISCEmbeddedData;

struct NvMediaISCModuleConfig;

/**
 * \brief  Holds an opaque handle representing a NvMediaISCDevice object.
 */
typedef void NvMediaISCDevice;

/**
 * \brief  Holds an opaque handle representing an NvMediaISCDevice driver.
 */
typedef void NvMediaISCDriverHandle;

/**
 * \brief  Holds an opaque handle representing a device transaction used by the
 * device driver.
 */
typedef void NvMediaISCTransactionHandle;
/*@} <!-- Ends nvmedia_isc_types Basic ISC types --> */

/**
 * \defgroup version_info_isc_api ISC Version Information
 *
 * Provides version information for the NvMedia ISC library.
 * @{
 */

/**
 * \brief Holds version information for the NvMedia ISC library.
 */
typedef struct {
    /*! Library version information */
    NvMediaVersion libVersion;
} NvMediaISCVersionInfo;

/**
 * \brief Returns the version information for the NvMedia ISC library.
 * \param[in,out] versionInfo A pointer to a \ref NvMediaISCVersionInfo structure
 *                that NvMediaISCGetVersionInfo() fills with data.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaISCGetVersionInfo(
    NvMediaISCVersionInfo *versionInfo
);

/**
 * \brief Gets the version compatibility for the NvMedia ISC library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaISCGetVersion(
    NvMediaVersion *version
);

/** @} <!-- Ends version_info_isc_api ISC Version Information sub-group -> */

/**
 * \defgroup isc_root_device_api ISC Root Device
 *
 * Manages NvMediaISCRootDevice objects that are the root of the Nvmedia
 * ISC object system.
 *
 * The NvMediaISCRootDevice object manages an I2C port on the host hardware device.
 * @{
 */

/**
 * \hideinitializer
 * \brief Defines the I2C buses on the host hardware device.
 */
typedef enum {
    /** i2c-0 */
    NVMEDIA_ISC_I2C_BUS_0 = 0,
    /** i2c-1 */
    NVMEDIA_ISC_I2C_BUS_1 = 1,
    /** i2c-2 */
    NVMEDIA_ISC_I2C_BUS_2 = 2,
    /** i2c-3 */
    NVMEDIA_ISC_I2C_BUS_3 = 3,
    /** i2c-4 */
    NVMEDIA_ISC_I2C_BUS_4 = 4,
    /** i2c-5 */
    NVMEDIA_ISC_I2C_BUS_5 = 5,
    /** i2c-6 */
    NVMEDIA_ISC_I2C_BUS_6 = 6,
    /** i2c-7 */
    NVMEDIA_ISC_I2C_BUS_7 = 7,
    /** i2c-8 */
    NVMEDIA_ISC_I2C_BUS_8 = 8,
    /** i2c-9 */
    NVMEDIA_ISC_I2C_BUS_9 = 9,
    /** i2c-10 */
    NVMEDIA_ISC_I2C_BUS_10 = 10,
    /** i2c-11 */
    NVMEDIA_ISC_I2C_BUS_11 = 11,
    /** Port SIMPULATOR (20) */
    NVMEDIA_ISC_I2C_SIMULATOR = 255,
} NvMediaISC_I2CPort;

/**
 * \brief  An opaque handle for an NvMediaISCRootDevice object.
 */
typedef void NvMediaISCRootDevice;

/**
 * \brief Creates an \ref NvMediaISCRootDevice object.
 * \param[in] portCfg The CSI/I2C ports that this root device.
 * Using macro `ISC_RDEV_CFG(csi, i2c)` to generate this value is strongly recommended.
 * In the case when the application is being run on a slave Tegra while master Tegra
 * is in charge of controlling isc devices, using macro 'ISC_SLV_RDEV_CFG(csi, i2c)'
 * is strongly recommended.
 * The following I2C ports are supported:
 * \n \ref NVMEDIA_ISC_I2C_BUS_0
 * \n \ref NVMEDIA_ISC_I2C_BUS_1
 * \n \ref NVMEDIA_ISC_I2C_BUS_2
 * \n \ref NVMEDIA_ISC_I2C_BUS_3
 * \n \ref NVMEDIA_ISC_I2C_BUS_4
 * \n \ref NVMEDIA_ISC_I2C_BUS_5
 * \n \ref NVMEDIA_ISC_I2C_BUS_6
 * \n \ref NVMEDIA_ISC_I2C_BUS_7
 * \n \ref NVMEDIA_ISC_I2C_BUS_8
 * \n \ref NVMEDIA_ISC_I2C_BUS_9
 * \n \ref NVMEDIA_ISC_I2C_BUS_10
 * \n \ref NVMEDIA_ISC_I2C_BUS_11
 * \n \ref NVMEDIA_ISC_I2C_SIMULATOR
 * \n The following CSI ports are supported:
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_A
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_B
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_AB
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_C
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_D
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_CD
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_E
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_F
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_EF
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_G
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_H
 * \n \ref NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_GH
 * \return device The new device's handle or NULL if unsuccessful.
 */
NvMediaISCRootDevice *
NvMediaISCRootDeviceCreate(
    uint32_t portCfg
);

/**
 * \brief Destroys an \ref NvMediaISCRootDevice object.
 * \param[in] device Handle of the device to destroy.
 * \return void
 */
void
NvMediaISCRootDeviceDestroy(
    NvMediaISCRootDevice *device
);

/*@} <!-- Ends isc_root_device_api ISC Root Device --> */

/**
 * \defgroup isc_device_driver_api ISC Device Driver
 *
 * The \ref NvMediaISCDeviceDriver object defines the device driver.
 * The core NvMediaISC calls the driver when the client calls the related
 * public NvMediaICS function.
 *
 * Before the client can create an NvMediaISCRootDevice object (a device), it must provide
 * a device driver. When the client creates the driver, it specifies pointers to support
 * functions, which are the functions that the device driver can call.
 * The client defines the support functions with the \ref NvMediaISCSupportFunctions struct.
 *
 * The \ref NvMediaISCDeviceDriver object contains data fields and function pointers.
 *
 * @par Data Fields
 * \li deviceName The name of the device. This is a null-terminated string.
 * \li regLength  Target device offset length in bytes.
 * \li dataLength Target device data length in bytes.
 *
 * @par Function Pointers
 *  - DriverCreate (mandatory)
 * \n   Invoked when the client calls the \ref NvMediaISCDeviceCreate function.
 *  - DriverDestroy (mandatory)
 * \n   Invoked when the client calls the \ref NvMediaISCDeviceDestroy function.
 *  - CheckPresence (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCCheckPresence function.
 *  - CheckLink (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCCheckLink function.
 *  - SetDefaults (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetDefaults function.
 *  - SetDeviceConfig (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetDeviceConfig function.
 *  - ReadParameters (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCReadParameters function.
 *  - WriteParameters (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCWriteParameters function.
 *  - ParseEmbeddedData (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCParseEmbeddedData function.
 *  - GetTemperature (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetTemperature function.
 *  - SetExposure (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetExposure function.
 *  - ReadRegister (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCReadRegister function.
 *  - WriteRegister (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCWriteRegister function.
 *  - DumpRegisters (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCDumpRegisters function.
 *  - GetErrorStatus (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetErrorStatus function.
 *  - SetBracketedExposure (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetBracketedExposure function.
 *  - SetCompandingCurve (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetCompandingCurve function.
 *  - GetSensorFrameId (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetSensorFrameId
 *      function.
 *  - SetWBGain (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetWBGain function.
 *  - GetSensorAttr (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetSensorAttr function.
 *  - GetModuleConfig (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetModuleConfig
 *      function.
 *  - SetSensorCharAttr (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCSetCharacterizationAttr
 *      function.
 *  - GetSensorCharAttr (optional)
 * \n   Invoked when the client calls the \ref NvMediaISCGetCharacterizationAttr
 *      function.
 *
 *
 * The \ref NvMediaISCSupportFunctions structure holds the following functions:
 *\li Read
 * \n   Reads I2C data from the device.
 *\li Write
 * \n   Writes I2C data to the device.
 *\li Wait
 * \n   Waits for the specified interval, in microseconds.
 *
 * Here is a sample device driver implementation that writes one register
 * upon calling the \ref NvMediaISCSetDefaults function.
 *
 * @par Header File
 *
 * \code
 *
 * #include <nvmedia_isc.h>
 *
 * NvMediaISCDeviceDriver *GetSAMPLEDEVICEDriver(void);
 *
 * \endcode
 *
 * <b>Source File</b>
 * \code
 *
 * #include "isc_sample_device.h"
 *
 * NvMediaISCSupportFunctions *s_supportFuncs;
 *
 * static NvMediaStatus
 * DriverCreate(
 *     NvMediaISCDriverHandle **handle,
 *     NvMediaISCSupportFunctions *supportFunctions,
 *     void *clientContext)
 * {
 *     if(!handle || !supportFunctions)
 *         return NVMEDIA_STATUS_BAD_PARAMETER;
 *
 *     // Save support function pointer
 *     s_supportFuncs = supportFunctions;
 *
 *     // Can be used to maintain local device context
 *     // or can be set to NULL.
 *     *handle = NULL;
 *
 *     return NVMEDIA_STATUS_OK;
 * }
 *
 * static NvMediaStatus
 * SetDefaults(
 *     NvMediaISCDriverHandle *handle,
 *     NvMediaISCTransactionHandle *transaction)
 * {
 *     NvMediaISCSupportFunctions *funcs;
 *     NvMediaStatus status;
 *     uint32_t data[2];
 *
 *     data[0] = 0x12;  // Register address
 *     data[1] = 0x32;  // Register data
 *
 *     // Write data to register
 *     status = s_supportFuncs->Write(
 *         transaction, // transaction
 *         2,           // dataLength
 *         data);       // data
 *
 *     return status;
 * }
 *
 * static NvMediaISCDeviceDriver deviceDriver = {
 *     .deviceName = "Sample Sensor Device",
 *     .DriverCreate = DriverCreate,
 *     .SetDefaults = SetDefaults
 * };
 *
 * NvMediaISCDeviceDriver *
 * GetSAMPLEDEVICEDriver(void)
 * {
 *     // Return device driver descriptor structure
 *     return &deviceDriver;
 * }
 *
 * \endcode
 *
 * @{
 */

/**
 * \brief  Holds the support functions that the device driver can call.
 * The functions in this structure provide I2C communication primitives
 * and also a wait function.
 */
typedef struct {
    /** Holds the function for reading I2C bytes from the device. */
    NvMediaStatus (* Read)(
        NvMediaISCTransactionHandle *transaction,
        uint32_t deviceIndex,
        uint32_t regLength,
        uint8_t *regData,
        uint32_t dataLength,
        uint8_t *data);
    /** Holds the function for writing I2C bytes to the device. */
    NvMediaStatus (* Write)(
        NvMediaISCTransactionHandle *transaction,
        uint32_t deviceIndex,
        uint32_t dataLength,
        const uint8_t *data);
    /** Holds the function for waiting the specified interval, in microseconds. */
    NvMediaStatus (* Wait)(
        NvMediaISCTransactionHandle *transaction,
        uint32_t microSecond);
} NvMediaISCSupportFunctions;

/**
* \hideinitializer
* \brief ISC sensor attributes
*/
typedef enum {
    /** Unique ID per instance of camera module.
      * Data type: char[32] */
    NVMEDIA_ISC_SENSOR_ATTR_FUSE_ID,
    /** Minimum possible gain values.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_GAIN_MIN,
    /** Maximum possible gain values.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_GAIN_MAX,
    /** Minimum possible exposure time values in seconds.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_ET_MIN,
    /** Maximum possible exposure time values in seconds.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_ET_MAX,
    /** Fine integration time values in seconds.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_ET_FINE,
    /** Exposure time step values in seconds.
      * Data type: double[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_ET_STEP,
    /** Maximum possible HDR ratio value.
      * Data type: uint32_t */
    NVMEDIA_ISC_SENSOR_ATTR_HDR_MAX,
    /** Gain factor between the exposures.
      * If non zero, possible factors are 1, x, 1/x.
      * Data type: float_t */
    NVMEDIA_ISC_SENSOR_ATTR_GAIN_FACTOR,
    /** Quantum efficiency ratio in split pixel HDR sensor technology.
      * Data type: float_t[NVMEDIA_ISC_EXPOSURE_MODE_MAX] */
    NVMEDIA_ISC_SENSOR_ATTR_QE_PIXEL_RATIO,
    /** Frames per second.
      * Data type: float_t */
    NVMEDIA_ISC_SENSOR_ATTR_FRAME_RATE,
    /** Active number of exposures.
      * Data type: uint32_t */
    NVMEDIA_ISC_SENSOR_ATTR_NUM_EXPOSURES,
} NvMediaISCSensorAttrType;


/**
* \hideinitializer
* \brief ISC sensor characterization attributes
*/
typedef enum {
    /** Single exposure enable flag.
      * Data type: NvMediaBool[NVMEDIA_ISC_EXPOSURE_MAX] */
    NVMEDIA_ISC_CHAR_ATTR_SINGLE_EXP,
} NvMediaISCSensorCharAttr;


/**
 * \brief  Holds device driver data.
 */
typedef struct {
    /** Holds the device name. */
    char *deviceName;
    /** Holds the target device offset length in bytes. */
    int32_t regLength;
    /** Holds the target device data length in bytes. */
    int32_t dataLength;
    /** Holds the function that creates the driver. */
    NvMediaStatus (* DriverCreate)(
        NvMediaISCDriverHandle **handle,
        NvMediaISCSupportFunctions *supportFunctions,
        void *clientContext);
    /** Holds the function that destroys the driver. */
    NvMediaStatus (* DriverDestroy)(
        NvMediaISCDriverHandle *handle);
    /** Holds the function that checks the pre-sense of the device. */
    NvMediaStatus (* CheckPresence)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction);
    /** Holds the function that initiates a link check to the device.
      * The device is identified by the \a linkIndex argument.
      * In case when the device has multiple kinds of links per devices,
      * additional \a linkType argument can be used as optional. */
    NvMediaStatus (* CheckLink)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t linkIndex,
        uint32_t linkType);
    /** Holds the function that sets device defaults. */
    NvMediaStatus (* SetDefaults)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction);
    /** Holds the function that sets a specific configuration to the device. The configuration
      * number definition is located in the device driver's header file. */
    NvMediaStatus (* SetDeviceConfig)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t enumeratedDeviceConfig);
    /** Holds the function that reads parameters from a device. The parameter type and parameter
      * structure definition are located in the device driver's header file. */
    NvMediaStatus (* ReadParameters)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t parameterType,
        uint32_t parameterSize,
        void *parameter);
    /** Holds the function that writes parameters to a device. The parameter type and parameter
      * structure definition are located in the device driver's header file. */
    NvMediaStatus (* WriteParameters)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t parameterType,
        uint32_t parameterSize,
        void *parameter);
    /** Holds the function that parses the embedded data returned as part of the captured buffer.
      * The data type and the parsed data structure definition are
      * located in the device driver's header file. */
    NvMediaStatus (* ParseEmbeddedData)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t lineCount,
        uint32_t *lineLength,
        uint8_t *lineData[],
        struct NvMediaISCEmbeddedData *parsedInformation);
    /** Holds the function that gets the sensor frame ID from embedded lines. */
    NvMediaStatus (* GetSensorFrameId)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t lineCount,
        uint32_t *lineLength,
        uint8_t *lineData[],
        uint32_t *sensorFrameId);
    /** Holds the function that gets the device's temperature. */
    NvMediaStatus (* GetTemperature)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        float_t *temperature);
    /** Holds the function that sets exposure control. */
    NvMediaStatus (* SetExposure)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        struct NvMediaISCExposureControl *exposureControl);
    /** Holds the function that sets white balance control. */
    NvMediaStatus (* SetWBGain)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        struct NvMediaISCWBGainControl *wbControl);
    /** Holds the function that reads device register. */
    NvMediaStatus (* ReadRegister)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t deviceIndex,
        uint32_t registerNum,
        uint32_t dataLength,
        uint8_t *dataBuff);
    /** Holds the function that writes the device register. */
    NvMediaStatus (* WriteRegister)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t deviceIndex,
        uint32_t registerNum,
        uint32_t dataLength,
        uint8_t *dataBuff);
    /** Holds the function that dumps device registers. */
    NvMediaStatus (* DumpRegisters)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction);
    /** Holds the function that gets error information from a device. */
    NvMediaStatus (* GetErrorStatus)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t parameterSize,
        void *parameter);
    /** Holds the function that gets module configuration. */
    NvMediaStatus (* GetModuleConfig)(
        NvMediaISCDriverHandle *handle,
        struct NvMediaISCModuleConfig *moduleConfig);
    /** Holds the function that sets bracketed exposure control. */
    NvMediaStatus (* SetBracketedExposure)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t numExposureControls,
        struct NvMediaISCExposureControl *exposureControls);
    /** Holds the function that gets sensor attributes. */
    NvMediaStatus (* GetSensorAttr)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCSensorAttrType type,
        uint32_t size,
        void *attribute);
    /** Holds the function that sets companding curve */
    NvMediaStatus (* SetCompandingCurve)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        uint32_t numPoints,
        NvMediaPoint *kneePoints);
    /** Holds the function that sets characterization attributes. */
    NvMediaStatus (* SetSensorCharAttr)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCTransactionHandle *transaction,
        NvMediaISCSensorCharAttr type,
        uint32_t size,
        void *attribute);
    /** Holds the function that gets characterization attributes. */
    NvMediaStatus (* GetSensorCharAttr)(
        NvMediaISCDriverHandle *handle,
        NvMediaISCSensorCharAttr type,
        uint32_t size,
        void *attribute);
} NvMediaISCDeviceDriver;

/*@} <!-- Ends isc_device_driver_api ISC Device driver --> */

/**
 * \defgroup isc_device_api ISC Device
 *
 * An ISC device represents a device that is attached or linked to the root I2C
 * port.
 *
 * @{
 */

/**
 * \hideinitializer
 * \brief Infinite time-out
 */
#define NVMEDIA_ISC_TIMEOUT_INFINITE  0xFFFFFFFF

/**
 * Holds the description of the target I2C device.
 */
typedef struct {
    /** Holds the client context. */
    void *clientContext;
} NvMediaISCAdvancedConfig;

/**
 * \brief Creates an \ref NvMediaISCDevice object.
 * \param[in] rootDevice A pointer to the root device that you created
 *            with NvMediaISCRootDeviceCreate().
 * \param[in] deviceAddressList The list of I2C device addresses corresponding to
                                this \ref NvMediaISCDevice object
 * \param[in] numDevices The number of I2C addresses in the above list
 * \param[in] deviceDriver The driver structure that defines the behavior of the
 *  device.
 * \param[in] advancedConfig Advanced configuration.
 * \return device The new device's handle or NULL if unsuccessful.
 */
NvMediaISCDevice *
NvMediaISCDeviceCreate(
    NvMediaISCRootDevice *rootDevice,
    uint32_t *deviceAddressList,
    uint32_t numDevices,
    NvMediaISCDeviceDriver *deviceDriver,
    NvMediaISCAdvancedConfig *advancedConfig
);

/**
 * \brief Destroys an NvMediaISCDevice device.
 * \param[in] device The device to destroy.
 */
void
NvMediaISCDeviceDestroy(
    NvMediaISCDevice *device
);

/**
 * \brief Check that the device is present.
 * \param[in] device The device to use.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 *         by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if the device is not present.
 */
NvMediaStatus
NvMediaISCCheckPresence(
    NvMediaISCDevice *device
);

/**
 * \brief check the result of link detection of the numbered instance.
 * \param[in] device The device to use.
 * \param[in] instanceNumber The attached device's instance number.
 * \param[in] link The specific link defined by the device (optional).
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 *      by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if the device is failed to detect the particular link.
 */
NvMediaStatus
NvMediaISCCheckLink(
    NvMediaISCDevice *device,
    uint32_t instanceNumber,
    uint32_t link
);

/**
 * \brief Sets defaults for the device.
 * \param[in] device The device to use.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occurred.
 */
NvMediaStatus
NvMediaISCSetDefaults(
    NvMediaISCDevice *device
);

/**
 * \brief Sets enumerated device configuration to the device.
 * This configuration is device specific and it is defined in the
 * device driver's header file.
 * \param[in] device The device to use.
 * \param[in] enumeratedDeviceConfig Configuration number.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCSetDeviceConfig(
    NvMediaISCDevice *device,
    uint32_t enumeratedDeviceConfig
);

/**
 * \brief Reads device specific parameters. This read is implemented in
 * the device driver and the device driver's header file contains the definitions
 * for the parameters.
 * \param[in] device The device to use.
 * \param[in] parameterType Device specific parameter type.
 * \param[in] parameterSize Size of the parameter structure
 * \param[out] parameter Device specific parameter
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if a read error occurred.
 */
NvMediaStatus
NvMediaISCReadParameters(
    NvMediaISCDevice *device,
    uint32_t parameterType,
    uint32_t parameterSize,
    void *parameter
);

/**
 * \brief Writes device specific parameters. This write is implemented in
 * the device driver and the device driver's header file contains the definitions
 * for the parameters.
 * \param[in] device The device to use.
 * \param[in] parameterType Device specific parameter type.
 * \param[in] parameterSize Size of the parameter structure
 * \param[in] parameter Device specific parameter.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occurred.
 */
NvMediaStatus
NvMediaISCWriteParameters(
    NvMediaISCDevice *device,
    uint32_t parameterType,
    uint32_t parameterSize,
    void *parameter
);

/**
 * \brief Parses embedded data in the captured image.
 * \param[in] device The device to use.
 * \param[in] lineCount Number of lines to parse.
 * \param[in] lineLength Line length of each line in bytes.
 * \param[in] lineData Array of pointers containing the line data.
 * \param[out] parsedInformation Pointer to the parsed information structure.
 * This information is device specific.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported.
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if the line information is invalid.
 */
NvMediaStatus
NvMediaISCParseEmbeddedData(
    NvMediaISCDevice *device,
    uint32_t lineCount,
    uint32_t *lineLength,
    uint8_t *lineData[],
    struct NvMediaISCEmbeddedData *parsedInformation
);

/**
 * \brief Gets sensor frame ID from embedded data.
 * \param[in] device The device to use.
 * \param[in] lineCount Number of lines to parse.
 * \param[in] lineLength Line length of each line in bytes.
 * \param[in] lineData Array of pointers containing the line data.
 * \param[out] sensorFrameId The sensor frame ID.
 * This information is device-specific.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if the line information is invalid
 */
NvMediaStatus
NvMediaISCGetSensorFrameId(
    NvMediaISCDevice *device,
    uint32_t lineCount,
    uint32_t *lineLength,
    uint8_t *lineData[],
    uint32_t *sensorFrameId
);

/**
 * \brief Gets a device temperature.
 * \param[in] device The device to use.
 * \param[out] temperature The device's temperature in Celsius.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occurred.
 */
NvMediaStatus
NvMediaISCGetTemperature(
    NvMediaISCDevice *device,
    float_t *temperature
);

/**
 * \hideinitializer
 * \brief Exposure mode.
 */
typedef enum {
    /**  Long exposure mode. */
    NVMEDIA_ISC_EXPOSURE_MODE_LONG,
    /**  Short exposure mode. */
    NVMEDIA_ISC_EXPOSURE_MODE_SHORT,
    /**  Very short exposure mode. */
    NVMEDIA_ISC_EXPOSURE_MODE_VERY_SHORT,
    /**  Exposure mode count. */
    NVMEDIA_ISC_EXPOSURE_MODE_MAX
} NvMediaISCExposureMode;

/**
 * \brief  Exposure control structure.
 */
typedef struct NvMediaISCExposureControl {
    /** Exposure time for each exposure mode. */
    struct {
        float_t value;
        NvMediaBool valid;
    } exposureTime[NVMEDIA_ISC_EXPOSURE_MODE_MAX];
    /** Sensor gain for each exposure mode. */
    struct {
        float_t value;
        NvMediaBool valid;
    } sensorGain[NVMEDIA_ISC_EXPOSURE_MODE_MAX];
    uint8_t sensorFrameId;
} NvMediaISCExposureControl;

/**
 * \brief  Holds the white balance control structure.
 */
typedef struct NvMediaISCWBGainControl {
    /** White balance for each exposure mode
        in R Gr Gb B order. */
    struct {
        float_t value[4];
        NvMediaBool valid;
    } wbGain[NVMEDIA_ISC_EXPOSURE_MODE_MAX];
} NvMediaISCWBGainControl;

/**
 * \brief  Holds the embedded data buffer structure.
 */
typedef struct {
    /** Holds the address of the first register. */
    uint32_t baseRegAddress;
    /** Holds the data size. */
    uint32_t size;
    /** Holds the buffer size. */
    uint32_t bufferSize;
    /** Holds the actual data. */
    uint8_t *data;
} NvMediaISCEmbeddedDataBuffer;

/**
 * \brief  Holds the embedded data structure.
 */
typedef struct NvMediaISCEmbeddedData {
    NvMediaISCEmbeddedDataBuffer top;
    NvMediaISCEmbeddedDataBuffer bottom;
    /** Parsed exposure control */
    NvMediaISCExposureControl exposureControl;
    /** Parsed WB gains in R Gr Gb B order. */
    NvMediaISCWBGainControl wbControl;
    /** Parsed frame counter */
    uint32_t frameSequenceNumber;
} NvMediaISCEmbeddedData;

/**
 * \brief Sets exposure control parameters.
 * \param[in] device A pointer to the device to use.
 * \param[out] exposureControl A pointer to exposure control parameters.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCSetExposure(
    NvMediaISCDevice *device,
    NvMediaISCExposureControl *exposureControl
);

/**
 * \brief Sets white balance control parameters.
 * \param[in] device The device to use.
 * \param[out] wbControl White Balance control parameters.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */

NvMediaStatus
NvMediaISCSetWBGain(
    NvMediaISCDevice *device,
    NvMediaISCWBGainControl *wbControl
);

/**
 * \brief Reads a device register.
 * \param[in] device The device to use.
 * \param[in] deviceIndex The index of the device address passed during
                          \ref NvMediaISCDeviceCreate.
 * \param[in] registerAddress The register address to read from.
 * \param[in] dataByteNumber Number of bytes to read.
 * \param[in] dataBuffer The data buffer to read to.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCReadRegister(
    NvMediaISCDevice *device,
    uint32_t deviceIndex,
    uint32_t registerAddress,
    uint32_t dataByteNumber,
    uint8_t *dataBuffer
);

/**
 * \brief Reads a device register.
 * \param[in] device The device to use.
 * \param[in] deviceIndex The index of the device address passed during
                          \ref NvMediaISCDeviceCreate.
 * \param[in] registerAddress The register address to write to.
 * \param[in] dataByteNumber Number of bytes to write.
 * \param[in] dataBuffer The data buffer to be written to the register.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCWriteRegister(
    NvMediaISCDevice *device,
    uint32_t deviceIndex,
    uint32_t registerAddress,
    uint32_t dataByteNumber,
    uint8_t *dataBuffer
);

/**
 * \brief Dumps all device register to the standard output.
 * \param[in] device The device to use.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCDumpRegisters(
    NvMediaISCDevice *device
);

/**
 * \brief Gets error information about an ISC device.
 * \param[in] device The device to use.
 * \param[in] parameterSize Size of the error information structure
 * \param[out] parameter Device specific error information structure
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCGetErrorStatus(
    NvMediaISCDevice *device,
    uint32_t parameterSize,
    void *parameter
);

/**
 * \brief Registers a callback function to handle error messages.
 * \param[in] device The root device to use.
 * \param[in] sigNum The signal number to use for notifying errors.
 * \param[in] cbFunc The callback function to handle the signal.
 * \param[in] context Can be used to store local context.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCRootDeviceRegisterCallback(
    NvMediaISCRootDevice *device,
    int32_t sigNum,
    void (*cbFunc)(void *),
    void *context
);

 /**
 * \hideinitializer
 * \brief ISC Power control items
 */
typedef enum {
    /** Aggregator Power */
    NVMEDIA_ISC_PWR_AGGREGATOR,
    /** LINK 0 Power */
    NVMEDIA_ISC_PWR_LINK_0,
    /** LINK 1 PWR */
    NVMEDIA_ISC_PWR_LINK_1,
    /** LINK 2 PWR */
    NVMEDIA_ISC_PWR_LINK_2,
    /** LINK 3 PWR */
    NVMEDIA_ISC_PWR_LINK_3,
} NvMediaISCPowerItems;

/**
 * \brief Turns ON/OFF the power of a specific sub-device.
 * \param[in] device The root device to use.
 * \param[in] powerItem The power item to control the power in the root device.
 * \param[in] powerOn The power state after this call.
 * Possible values are:
 * \li \ref NVMEDIA_TRUE   turn power on
 * \li \ref NVMEDIA_FALSE  turn power off
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCRootDevicePowerControl(
    NvMediaISCRootDevice *device,
    NvMediaISCPowerItems  powerItem,
    NvMediaBool powerOn
);

/**
 * \brief Get sensor attribute.
 * \param[in] device The device to use.
 * \param[in] type Sensor attribute type.
 * \param[in] size Size of the attribute.
 * \param[out] attribute Sensor attribute value.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if the input parameters are not valid.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported or
 * the attribute is not supported by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if any other error occurred.
 */
NvMediaStatus
NvMediaISCGetSensorAttr(
    NvMediaISCDevice *device,
    NvMediaISCSensorAttrType type,
    uint32_t size,
    void *attribute
);

 /**
 * \hideinitializer
 * \brief Holds the ISC Module ISP configuration.
 */
typedef struct NvMediaISCModuleConfig {
    /** Holds the camera module name. */
    char cameraModuleCfgName[128];
    /** Holds the camera-specific configuration string. */
    const char *cameraModuleConfigPass1;
    const char *cameraModuleConfigPass2;
} NvMediaISCModuleConfig;

/**
 * \brief Gets the Module ISP configuration.
 * \param[in] device A pointer to the device to use.
 * \param[out] moduleConfig A pointer to the module ISP configuration.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if any other error occurred.
 */
NvMediaStatus
NvMediaISCGetModuleConfig(
    NvMediaISCDevice *device,
    NvMediaISCModuleConfig *moduleConfig
);

/**
 * \brief Sets bracketed exposure control parameters.
 * \param[in] device A pointer to the device to use.
 * \param[in] numExposureControls Number of entries in exposureControls array
 * \param[in] exposureControls An array of exposure control parameters.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCSetBracketedExposure(
    NvMediaISCDevice *device,
    uint32_t numExposureControls,
    NvMediaISCExposureControl *exposureControls
);

/**
 * \brief Sets the companding curve control parameters.
 * \param[in] device A pointer to the device to use.
 * \param[in] numPoints Number of points in the kneePoints array
 * \param[in] kneePoints An array of points
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if an input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if some other error occured.
 */
NvMediaStatus
NvMediaISCSetCompandingCurve(
    NvMediaISCDevice *device,
    uint32_t numPoints,
    NvMediaPoint *kneePoints
);

/**
 * \brief Gets the power ON/OFF status of a specific sub-device.
 * \param[in] device The root device to use.
 * \param[in] powerItem The power item to get  power status in the root device.
 * \param[in] powerStatus The power state of the power item provided
 * Possible values are:
 * \n \ref NVMEDIA_TRUE   power is on
 * \n \ref NVMEDIA_FALSE  power is off
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 * by the device driver.
 * \n \ref NVMEDIA_STATUS_ERROR if any other error occurred.
 */
NvMediaStatus
NvMediaISCRootDeviceGetPowerStatus(
    NvMediaISCRootDevice *device,
    NvMediaISCPowerItems  powerItem,
    NvMediaBool *powerStatus
);

/**
 * \brief Enables or disables pulse width modulation (PWM) for the external
 *  synchronization.
 * \param[in] device The root device to use.
 * \param[in] enable The PWM state.
 * Possible values are:
 * \n \ref NVMEDIA_TRUE   PWM is enabled.
 * \n \ref NVMEDIA_FALSE  PWM is disabled.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_ERROR if other error occurred.
 */
NvMediaStatus
NvMediaISCRootDeviceEnableSync(
    NvMediaISCRootDevice *device,
    NvMediaBool enable
);

/**
 * \brief Sets the pulse width modulation (PWM) frequency and duty.
 * \param[in] device The root device to use.
 * \param[in] freq PWM frequency.
 * \param[in] dutyRatio High level ratio in one PWM period.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_ERROR if other error occurred.
 */
NvMediaStatus
NvMediaISCRootDeviceSetSyncConfig(
    NvMediaISCRootDevice *device,
    float_t freq,
    float_t dutyRatio
);

/**
 * \brief Gets the pulse width modulation (PWM) frequency and duty.
 * \param[in] device The root device to use.
 * \param[out] freq PWM frequency.
 * \param[out] dutyRatio High level ratio in one PWM period.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \n \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported.
 * \n \ref NVMEDIA_STATUS_ERROR if other error occurred.
 */
NvMediaStatus
NvMediaISCRootDeviceGetSyncConfig(
    NvMediaISCRootDevice *device,
    float_t *freq,
    float_t *dutyRatio
);

/**
 * \brief Set sensor characterization attribute.
 * \param[in] device The device to use.
 * \param[in] type Sensor characterization attribute type.
 * \param[in] size Size of the attribute.
 * \param[out] attribute Sensor characterization attribute value.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if the input parameters are not valid.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported or
 * the attribute is not supported by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if any other error occurred.
 */
NvMediaStatus
NvMediaISCSetCharacterizationAttr(
    NvMediaISCDevice *device,
    NvMediaISCSensorCharAttr type,
    uint32_t size,
    void *attribute
);


/**
 * \brief Get sensor characterization attribute.
 * \param[in] device The device to use.
 * \param[in] type Sensor characterization attribute type.
 * \param[in] size Size of the attribute.
 * \param[out] attribute Sensor characterization attribute value.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if the input parameters are not valid.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported or
 * the attribute is not supported by the device driver.
 * \li \ref NVMEDIA_STATUS_ERROR if any other error occurred.
 */
NvMediaStatus
NvMediaISCGetCharacterizationAttr(
    NvMediaISCDevice *device,
    NvMediaISCSensorCharAttr type,
    uint32_t size,
    void *attribute
);

/*@} <!-- Ends isc_device_api ISC Device --> */

/*
 * \defgroup history_isc History
 * Provides change history for the NvMedia Image Sensor Control API.
 *
 * \section history_isc Version History
 *
 * <b> Version 1.0 </b> April 1, 2014
 * - Initial release
 *
 * <b> Version 1.1 </b> April 3, 2015
 * - Add mode in \ref NvMediaISCEmbeddedData
 *
 * <b> Version 1.2 </b> April 16, 2015
 * - Add new port config macro \ref ISC_ROOT_DEVICE_CFG
 * - The \a advancedConfig attribute is being used in \ref NvMediaISCDeviceCreate
 * - Add new callback function \ref NvMediaISCRootDeviceRegisterCallback to handle device errors
 *
 * <b> Version 1.3 </b> April 24, 2015
 * - Moved the \a regLength and \a dataLength attributes from \ref NvMediaISCAdvancedConfig
 *   in \ref NvMediaISCDeviceDriver.
 * - Add macro \ref ADV_CONFIG_INIT
 *
 * <b> Version 1.4 </b> April 28, 2015
 * - Add hdrRatio in \ref NvMediaISCExposureControl structure
 * - Add conversionGain in \ref NvMediaISCEmbeddedData structure
 *
 * <b> Version 1.5 </b> July 13, 2015
 * - Add exposureMidpointTime in \ref NvMediaISCEmbeddedData structure
 * - Add NVMEDIA_ISC_I2C_SIMULATOR in \ref NVMEDIA_ISC_I2C_SIMULATOR
 * - Add new function \ref NvMediaISCRootDevicePowerControl and \ref NvMediaISCPowerItems
 * - Modify the input paramater cbFunc of NvMediaISCRootDeviceRegisterCallback
 * - Add function \ref NvMediaISCGetErrorStatus to get error information from device
 * - Add \ref NvMediaISCSensorProperties structure
 * - Add \ref NvMediaISCGetSensorProperties to get sensor properties
 *
 * <b> Version 1.6 </b> September 9, 2015
 * - Add SensorMode in \ref NvMediaISCExposureControl structure
 *
 * <b> Version 1.7 </b> September 21, 2015
 * - Increase I2C ports to support 12 I2C busses
 *
 * <b> Version 1.8 </b> December 09, 2015
 * - Add channelGainRatio for sensors which only allow same or fixed ratio gain in exposure channels
 *
 * <b> Version 1.9 </b> January 22, 2016
 * - Add NvMediaISCRootDeviceGetPowerStatus function
 *
 * <b> Version 1.10 </b> May 5, 2016
 * - Add NvMediaISCModuleConfig structure and NvMediaISCGetModuleConfig function.
 *
 * <b> Version 1.11 </b> May 11, 2016
 * - Add \ref NvMediaISCCheckVersion API
 *
 * <b> Version 1.12 </b> June 7, 2016
 * - Add NVMEDIA_ISC_SIMULATOR_ADDRESS to use for ISC simulator devices
 *
 * <b> Version 1.13 </b> June 20, 2016
 * - Add frameSequenceNumber in \ref NvMediaISCEmbeddedData
 *
 * <b> Version 1.14 </b> July 6, 2016
 * - Add ISC_ROOT_DEVICE_CFG_EX macro
 *
 * <b> Version 1.15 </b> July 8, 2016
 * - Add \ref NvMediaISCSetBracketedExposure new API for settings bracketed exposure
 *
 * <b> Version 1.16 </b> Oct 10, 2016
 * - Add sensor attribbutes \ref NvMediaISCSensorAttrType & new API \ref NvMediaISCGetSensorAttr
 *
 * <b> Version 1.17 </b> November 21, 2016
 * - Add \ref NvMediaISCRootDeviceEnableSync new API for enabling/disabling PWM
 * - Add \ref NvMediaISCRootDeviceSetSyncConfig new API for setting PWM's frequency and duty
 * - Add \ref NvMediaISCRootDeviceGetSyncConfig new API for getting PWM's frequency and duty
 *
 * <b> Version 1.18 </b> Jan 5, 2017
 * - Add \ref NvMediaISCSetCompandingCurve API for setting companding curve
 *
 * <b> Version 1.19 </b> Jan 27, 2017
 * - Add \ref Add const modifier to data parameter in NvmediaISCSupportFuntion Write.
 *
 * <b> Version 2.00 </b> April 19, 2017
 * - Deprecated NvMediaISCDeviceType and EnableLink from \ref NvMediaISCDeviceDriver.
 * - Updated to use stdint.h
 * - Replaced float with float_t
 * - Removed unused input param from NvMediaISCRootDeviceCreate
 * - Deprecated queueElementsNumber and queueElementSize from \ref NvMediaISCRootDeviceCreate
 * - Deprecated unused or not supported APIs as below list.
 *     NvMediaISCRootDeviceDoTransaction
 *     NvMediaISCRootDeviceSync
 *     NvMediaISCUpdateDeviceAddress
 *     NvMediaISCSetDeviceLinkMode
 *     NvMediaISCGetLinkStatus
 *     NvMediaISCSetPriority
 * - NvMediaISCGetLinkStatus is replaced by \ref NvMediaISCCheckLink
 * - Updated NvMediaISCCheckLink to have one more argument to specify which link
 *   to enable as optional.
 * - Renamed ISC_ROOT_DEVICE_CFG_EX to ISC_SLV_RDEV_CFG
 * - Renamed ISC_ROOT_DEVICE_CFG to ISC_RDEV_CFG
 * - Deprecated parentDevice, instanceNumber from NvMediaISCDeviceCreate
 * - Deprecated NvMediaISCGetSensorProperties, repleaced by \ref NvMediaISCGetSensorAttr
 *
 * <b> Version 2.1 </b> May 12, 2017
 * - Added \ref NvMediaISCGetVersion API to get the version of NvMedia ISC library
 * - NvMediaISCCheckVersion is deprecated. Use NvMediaISCGetVersion() instead
 *
 * <b> Version 2.2 </b> May 23, 2017
 * - Deprecated NvMediaISCSensorMode
 * - Deprecated mode & exposureMidpointTime from \ref NvMediaISCEmbeddedData
 * - Deprecated sensorMode & hdrRatio from \ref NvMediaISCExposureControl
 * - Replaced exposure in \ref NvMediaISCEmbeddedData with \ref NvMediaISCExposureControl
 * - Replaced wbGains in \ref NvMediaISCEmbeddedData with \ref NvMediaISCWBGainControl
 *
 * <b> Version 2.3 </b> May 26, 2017
 * - Add device list for ISC handle creation
 *
 * <b> Version 2.4 </b> Feb 26, 2018
 * - Add ISC_RDEV_CFG_EX to have an option to disable power control in \ref NvMediaISCRootDeviceCreate
 *
 * <b> Version 2.5 </b> April 30, 2018
 * - Add sensor characterization attributes \ref NvMediaISCSensorCharAttr
 * - Add new APIs \ref NvMediaISCSetCharacterizationAttr \ref NvMediaISCGetCharacterizationAttr
 *
 */

/*@} <!-- Ends nvmedia_isc_api Image Sensor Control --> */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_ISC_H */
