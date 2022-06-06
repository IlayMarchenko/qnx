/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image Processing Pipeline API </b>
 *
 * @b Description: This file contains the \ref image_ipp_api "Image Processing
 * Pipeline API."
 */

#ifndef _NVMEDIA_IPP_H
#define _NVMEDIA_IPP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_surface.h"
#include "nvmedia_image.h"
#include "nvmedia_icp.h"
#include "nvmedia_isc.h"
#include "nvmedia_isp_legacy.h"

/**
 * \defgroup image_ipp_api Image Processing Pipeline (IPP)
 *
 * The NvMedia Image Processing Pipeline (IPP) is a framework that controls all
 * NvMedia processing components. It does the following:
 * @li Manages and synchronizes each of the component threads
 * @li Provides callbacks for global timestamps and events
 * @li Supports Embedded Line Information for specific functionality
 *
 * For information on IPP architecture and functionality,
 * see the "Multimedia Programming" chapter in the <em>Development Guide</em>.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/**
 * \defgroup image_ipp_types Basic IPP Types
 * The Image Processing Pipeline API provides common IPP processing functions.
 * @ingroup basic_api_top
 * @{
 */

/** \brief Major Version number. */
#define NVMEDIA_IPP_VERSION_MAJOR   2u
/** \brief Minor Version number. */
#define NVMEDIA_IPP_VERSION_MINOR   16u
/** Version information. */
#define NVMEDIA_IPP_VERSION_INFO    (((uint8_t)'N' << 24) | ((uint8_t)'V' << 16) | (NVMEDIA_IPP_VERSION_MAJOR << 8) | NVMEDIA_IPP_VERSION_MINOR)

/**
 * \brief A handle representing IPP manager object.
 */
typedef void NvMediaIPPManager;

/**
 * \hideinitializer
 * \brief Maximum number of IPP pipelines in IPP manager.
 */
#define NVMEDIA_MAX_COMPONENTS_PER_PIPELINE 32

/**
 * \hideinitializer
 * \brief Maximum number of IPP components in IPP pipeline.
 */
#define NVMEDIA_MAX_PIPELINES_PER_MANAGER   12

/**
 * \brief A handle representing IPP pipeline object.
 */
typedef void NvMediaIPPPipeline;

/**
 * \brief A handle representing an IPP component object.
 */
typedef void NvMediaIPPComponent;

/**
 * \hideinitializer
 * \brief Specifies the IPP ISP version.
 */
typedef enum {
    /** Specifies ISP version 4. */
    NVMEDIA_IPP_ISP_VERSION_4,
    /** Specifies ISP version 5. */
    NVMEDIA_IPP_ISP_VERSION_5
} NvMediaIPPISPVersion;

/**
 * \hideinitializer
 * \brief Specifies IPP component types.
 */
typedef enum {
    /** \hideinitializer Specifies the capture component. */
    NVMEDIA_IPP_COMPONENT_ICP = 0,
    /** Specifies the image signal processing component. */
    NVMEDIA_IPP_COMPONENT_ISP,
    /** Specifies the Control Algorithm component. */
    NVMEDIA_IPP_COMPONENT_ALG,
    /** Specifies the sensor control component. */
    NVMEDIA_IPP_COMPONENT_ISC,
    /** Specifies the image output component. */
    NVMEDIA_IPP_COMPONENT_OUTPUT,
    /** Specifies the file reader. */
    NVMEDIA_IPP_COMPONENT_FILE_READER,
    /** Specifies the CaptureEx component. */
    NVMEDIA_IPP_COMPONENT_ICP_EX,
} NvMediaIPPComponentType;

/** Maximum number of streams. */
#define NVMEDIA_IPP_STREAM_MAX_TYPES    2

/**
 * \brief Holds image information.
 */
typedef struct {
    /** Holds a unique frame ID. */
    uint32_t frameId;
    /** Holds a camera ID. */
    uint32_t cameraId;
    /** Holds a frame capture time-stamp using global time in microseconds. */
    NvMediaGlobalTime frameCaptureGlobalTimeStamp;
    /** Holds a clock base used for frame capture time-stamp. */
    NvMediaTimeBase frameCaptureTimeBase;
    /** Specifies the frame capture TSC. */
    uint64_t frameCaptureTSC;
    /** Holds a frame sequence number, that is, a monotonically increasing
     frame counter. */
    uint32_t frameSequenceNumber;
} NvMediaIPPImageInformation;

/*@} <!-- Ends image_ipp_types Basic IPP types --> */

/** \defgroup nvmedia_ipp_properties IPP Properties
  * Defines IPP Properties.
  * @{
  */

/**
 * Specifies flicker detection/correction modes.
 */
typedef enum
{
    /** Specifies flicker correction off. */
    NVMEDIA_IPP_AE_ANTI_FLICKER_MODE_OFF,
    /** Specifies flicker correction to 50Hz mode. */
    NVMEDIA_IPP_AE_ANTI_FLICKER_MODE_50Hz,
    /** Specifies flicker correction to 60Hz mode. */
    NVMEDIA_IPP_AE_ANTI_FLICKER_MODE_60Hz,
    /** Specifies flicker correction to auto mode. */
    NVMEDIA_IPP_AE_ANTI_FLICKER_MODE_AUTO
} NvMediaIPPAeAntiFlickerMode;

/**
 * Defines detected flicker modes.
 */
typedef enum
{
    /** Indicates no flicker detected. */
    NVMEDIA_IPP_COMPUTED_ANTI_FLICKER_MODE_NONE,
    /** Indicates illuminant frequency of 50 Hz. */
    NVMEDIA_IPP_COMPUTED_ANTI_FLICKER_MODE_50Hz,
    /** Indicates illuminant frequency of 60 Hz. */
    NVMEDIA_IPP_COMPUTED_ANTI_FLICKER_MODE_60Hz
} NvMediaIPPComputedAntiFlicker;

/**
 * Holds a 4x4 matrix of floats.
 */
typedef struct
{
    /** Holds a 2d array. */
    float_t array[4][4];
} NvMediaIPPMathFloatMatrix;

/**
 * Defines auto exposure current states.
 */
typedef enum
{
    /** Indicates auto exposure is off. */
    NVMEDIA_IPP_AE_STATE_INACTIVE,
    /** Indicates auto exposure doesn't yet have a good set
     of control values for the current scene. */
    NVMEDIA_IPP_AE_STATE_SEARCHING,
    /** Indicates auto exposure has a good set of
     control values for the current scene. */
    NVMEDIA_IPP_AE_STATE_CONVERGED,
    /** Indicates auto exposure has timed out searching for a
     good set of values for the current scene. */
    NVMEDIA_IPP_AE_STATE_TIMEOUT
} NvMediaIPPAeState;

/**
 * Defines various auto white balance states.
 */
typedef enum
{
    /** Indicates auto white balance is off. */
    NVMEDIA_IPP_AWB_STATE_INACTIVE,
    /** Indicates auto white balance doesn't yet have a good set
      of control values for the current scene. */
    NVMEDIA_IPP_AWB_STATE_SEARCHING,
    /** Indicates auto white balance has a good set of
     control values for the current scene. */
    NVMEDIA_IPP_AWB_STATE_CONVERGED,
    /** Indicates auto white balance has timed out searching for a
     good set of values for the current scene. */
    NVMEDIA_IPP_AWB_STATE_TIMEOUT
} NvMediaIPPAwbState;

/** \defgroup nvmedia_ipp_property_structures IPP Property structures
 * Defines IPP Property structures.
 *
 * @{
 */

/**
 * Holds control properties associated with the camera.
 * Use these properties to control the settings of ISP and the camera.
 */
typedef struct
{
    /** Holds a flag to indicate manual or auto exposure. */
    NvMediaBool manualAE;

    /** Holds sensor exposure time and sensor gain for each sensor exposure
     mode. Sensor gain values within this structure must be within
     gainRange limits. */
    NvMediaISCExposureControl exposureControl;

    /** Holds a flag to indicate manual or auto white balance. */
    NvMediaBool manualAWB;

    /** Holds white balance color correction gains. */
    NvMediaISCWBGainControl wbGains;

    /** Holds anti-flicker mode. */
    NvMediaIPPAeAntiFlickerMode aeAntiFlickerMode;

    /** Holds ISP digital gain. */
    float_t ispDigitalGain;
} NvMediaIPPPropertyControls;

/**
 * Holds dynamic properties associated with the camera.
 */
typedef struct
{
    /** Holds auto exposure state. */
    NvMediaIPPAeState aeState;

    /** Holds sensor exposure time and sensor gain for each sensor exposure
     mode. Sensor gain valus within this structure must be within
     sensorGainRange limits.
     */
    NvMediaISCExposureControl exposureControl;

    /** Holds auto white balance state. */
    NvMediaIPPAwbState awbState;

    /** Holds the two sets of white balance gain control values
     calculated by the plugin Control Algorithm, one to apply in sensor or
     before hdr merge and other to apply in ISP after hdr merge. */
    NvMediaISCWBGainControl wbGains[2];

    /** Holds digital gain applied in ISP. */
    float_t ispDigitalGain;

    /** Holds current scene brightness. */
    float_t brightness;

    /** Holds auto white balance CCT. */
    uint32_t awbCCT;

    /** Holds color correction matrix. */
    NvMediaIPPMathFloatMatrix colorCorrectionMatrix;

    /** Holds computed anti-flicker. */
    NvMediaIPPComputedAntiFlicker computedAntiFlicker;
} NvMediaIPPPropertyDynamic;

/**
 * Maximum numbers of knee points for companding curve.
 */
#define NVMEDIA_IPP_MAX_KNEEPOINTS 24

/**
 * Holds static properties associated with a camera.
 */
typedef struct
{
    /** Holds active array size of sensor excluding embedded lines. */
    NvMediaISPSize activeArraySize;

    /** Holds ISP maximum digital gain. */
    float_t ispMaxDigitalGain;

    /** Holds the number of companding curve knee points. */
     unsigned int numKneePoints;

     /** Holds the companding curve knee points. */
     NvMediaPoint kneePoints[NVMEDIA_IPP_MAX_KNEEPOINTS];

    /** A pointer to the camera module name and camera-specific configuration
     string. */
    NvMediaISCModuleConfig *moduleConfig;

} NvMediaIPPPropertyStatic;

/**
 * Defines IPP pipeline property types.
 */
typedef enum {
    /**
     * Specifies use of only embedded data statistics.
     * This property takes the NvMediaBool data type.
     * Possible values are:
     * - \ref NVMEDIA_TRUE
     * - \ref NVMEDIA_FALSE (Default)
     *
     * If set, the pipeline uses only the embedded data stats.
     * This property must be set when there is no ISP component.
     */
    NVMEDIA_IPP_PIPELINE_PROPERTY_ONLY_EMB_STATS = 0,
    /**
     * Specifies use of trigger-based capture.
     * This property requires an NvMediaBool data type.
     * Possible values are:
     * - \ref NVMEDIA_TRUE
     * - \ref NVMEDIA_FALSE (Default)
     *
     * If set, the pipeline is configured for trigger based capture.
     * NvMediaIPPPipelineSingleCapture() does the trigger.
     */
    NVMEDIA_IPP_PIPELINE_PROPERTY_TRIGGER_BASED_CAPTURE,
    /**
     * Specifies the settings delay (in number of frames)
     * from the time when the sensor is programmed. The range of values is
     * [0,10]; the default is 2.
     *
     * This property requires a \c uint32_t data type.
     * It is used only when sensor does not have any embedded lines.
     */
    NVMEDIA_IPP_PIPELINE_PROPERTY_SETTINGS_DELAY,
} NvMediaIPPPipelinePropertyType;

/**
 * Holds the IPP pipeline property.
*/
typedef struct {
    /** Holds the IPP pipeline property type. */
    NvMediaIPPPipelinePropertyType type;
    /** A pointer to the property specific data. */
    void *value;
} NvMediaIPPPipelineProperty;

/**
 * \brief Sets the IPP pipeline properties. Must be called before creating
 * any IPP components.
 * \param[in] ippPipeline   A pointer to the IPP pipeline.
 * \param[in] numProperties Number of entries in the properties list.
 * \param[in] properties    A pointer to a list of IPP pipeline properties.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the property type is not supported.
 */
NvMediaStatus
NvMediaIPPPipelineSetProperties(
    NvMediaIPPPipeline *ippPipeline,
    uint32_t numProperties,
    NvMediaIPPPipelineProperty *properties);

/** @} <!-- Ends nvmedia_ipp_property_structures IPP Property structures --> */
/** @} <!-- Ends nvmedia_ipp_properties IPP Properties --> */

/**
 * \defgroup version_info_ipp_api IPP Version Information
 *
 * Provides version information for the NvMedia IPP library.
 * @{
 */

/**
 * \brief Holds version information for the NvMedia IPP library.
 */
typedef struct {
    /*! Holds library version information */
    NvMediaVersion libVersion;
} NvMediaIPPVersionInfo;

/**
 * \brief Returns the version information for the NvMedia IPP library.
 * \param[out] versionInfo A pointer to a \ref NvMediaIPPVersionInfo structure
 *                        to be filled by the function.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaIPPGetVersionInfo(
    NvMediaIPPVersionInfo *versionInfo
);

/** @} <!-- Ends version_info_ipp_api IPP Version Information sub-group -> */

/**
 * \defgroup ipp_manager_creation IPP Manager
 * Defines IPP manager-related structures and functions.
 * @{
 */


/**
 * \brief Allocates an Image Processing Pipeline manager object. The object is
 *  a container for all of the pipelines created with its handle.
 * \param[in] versionInfo Set to \ref NVMEDIA_IPP_VERSION_INFO. Used to
 *                        determine the version of the API with which the
 *                        client application was
 *                        compiled. If the application and NvMedia IPP
 *                        library have different version numbers, the function
 *                        returns NULL, and the client application must be
 *                        recompiled with the latest library and header files.
 * \param[in] device      A pointer to the already created \ref NvMediaDevice.
 * \return \ref NvMediaIPPManager, the new IPP manager's handle if successful,
 *  or NULL otherwise.
 */
NvMediaIPPManager *
NvMediaIPPManagerCreate(
    uint32_t versionInfo,
    NvMediaDevice *device
);

/**
 * \brief Destroys an IPP manager object.
 * \param[in] ippManager A pointer to the IPP manager object to destroy.
 * \return void
 */
void
NvMediaIPPManagerDestroy(
    NvMediaIPPManager *ippManager
);

/**
 * \brief Defines the global time callback function prototype. The client must
 *  create a function with the same function signature.
 * \param clientContext The client context that was passed to
 *                  NvMediaIPPManagerSetTimeSource().
 * \param timeValue A pointer to the location where the callback is to write the
 *                  absolute global time, a 64-bit number measured in
 *                  microseconds.
 */
typedef NvMediaStatus NvMediaIPPGetAbsoluteGlobalTime(
        void *clientContext,
        NvMediaGlobalTime *timeValue);

/**
 * \brief Sets the callback function for image time-stamping.
 *
 * NvMedia IPP does not have access to an internal time source sufficient for
 * absolute global timestamping. The client application can establish a
 * callback function to provide an absolute global time. When the capture
 * component receives a frame, it calls this callback function and applies the
 * timestamp to the image. You may call %NvMediaIPPManagerSetTimeSource()
 * after creating the NvMedia IPP manager.
 *
 * If the application does not establish a callback function, NvMedia IPP uses
 * the kernel-based timestamp obtained from ktime_get_ts() to get the clock
 * monotonic time.
 *
 * \param[in] ippManager            A pointer to the IPP manager object.
 * \param[in] clientContext         Context of the caller application. If not
 * \param[in] getAbsoluteGlobalTime A pointer to a function that
 *                                  returns the absolute global time.
 *                                  If not needed, set to NULL.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPManagerSetTimeSource(
    NvMediaIPPManager *ippManager,
    void *clientContext,
    NvMediaIPPGetAbsoluteGlobalTime getAbsoluteGlobalTime
);
/*@} <!-- Ends ipp_manager_creation IPP Manager --> */

/**
 * \defgroup ipp_pipeline_creation IPP Pipeline
 * Defines IPP pipeline-related structures and functions.
 * @{
 */

/**
 * \brief Allocates an IPP pipeline object.
 * \param[in] ippManager A pointer to the \ref NvMediaIPPManager.
 * \return \ref NvMediaIPPPipeline, the new IPP pipeline's handle if
 *  successful, or NULL otherwise.
 */
NvMediaIPPPipeline *
NvMediaIPPPipelineCreate(
    NvMediaIPPManager *ippManager
);

/**
 * \brief Destroys an IPP pipeline object and all components created with the
 *  handle. May be called after the pipeline has been stopped with
 *  NvMediaIPPPipelineStop().
 * \param[in] ippPipeline A pointer to the IPP pipeline object to destroy.
 * \return void
 */
void
NvMediaIPPPipelineDestroy(
    NvMediaIPPPipeline *ippPipeline
);

/**
 * \brief Triggers the pipeline to do a single capture.
 * If called multiple times, triggers are queued.
 * Pipeline must be configured for trigger-based capture.
 * \param[in] ippPipeline A pointer to the IPP pipeline.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineSingleCapture(
    NvMediaIPPPipeline *ippPipeline
);

/**
 * \brief Specifies event types.
 */
typedef enum {
    /** Specifies event Info: End of file. */
    NVMEDIA_IPP_EVENT_INFO_EOF,
    /** Specifies event info: Component processed one frame. */
    NVMEDIA_IPP_EVENT_INFO_PROCESSING_DONE,
    /** Specifies event info: One frame captured. */
    NVMEDIA_IPP_EVENT_INFO_FRAME_CAPTURE,
    /** Specifies event warning: Capture frame drop. */
    NVMEDIA_IPP_EVENT_WARNING_CAPTURE_FRAME_DROP,
    /** Specifies event error: Internal failure. */
    NVMEDIA_IPP_EVENT_ERROR_INTERNAL_FAILURE,
    /** Specifies event error: I2C transmission failure. */
    NVMEDIA_IPP_EVENT_ERROR_I2C_TRANSMISSION_FAILURE,
    /** Specifies event warning: CSI frame discontinuity. */
    NVMEDIA_IPP_EVENT_WARNING_CSI_FRAME_DISCONTINUITY,
    /** Specifies event error: CSI input stream error. */
    NVMEDIA_IPP_EVENT_ERROR_CSI_INPUT_STREAM_FAILURE
} NvMediaIPPEventType;

/**
 * \brief Holds additional event information.
 */
typedef struct {
    /** Holds information about the image associated with the event. This
     field is not populated for all event types. */
    NvMediaIPPImageInformation imageInformation;
    /**
     * Holds capture error information.
     * This field is populated only for following event type:
     * - \ref NVMEDIA_IPP_EVENT_ERROR_CSI_INPUT_STREAM_FAILURE
     */
    NvMediaICPErrorInfo captureErrorInfo;
} NvMediaIPPEventData;

/**
 * \brief Defines a function prototype for event callbacks.
 *  The client must create a function
 *  with the same function signature.
 * \param clientContext The client context that was passed to
 *                      \ref NvMediaIPPManagerSetEventCallback.
 * \param componentType Component reporting the event.
 * \param ippComponent  A pointer to the IPP component handle.
 * \param eventType     Event type.
 * \param eventData     A pointer to additional event information data.
 */
typedef void NvMediaIPPEventCallback(
        void *clientContext,
        NvMediaIPPComponentType componentType,
        NvMediaIPPComponent *ippComponent,
        NvMediaIPPEventType eventType,
        NvMediaIPPEventData *eventData);

/**
 * \brief Sets a callback function for IPP events.
 *
 * May be called after the NvMedia IPP manager is created.
 *
 * \note The event callback function is called from the thread context of an
 * NvMedia IPP component. Therefore the called function must not perform
 * blocking calls, and overall processing must be kept to a minimum.
 *
 * \param[in] ippManager    A pointer to the \ref NvMediaIPPManager.
 * \param[in] clientContext Context of the client. If not needed, set to
 *                          NULL.
 * \param[in] eventCallback A pointer to an event callback function. This
 *                          function is called when an event occurs in the
 *                          IPP pipeline.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPManagerSetEventCallback(
    NvMediaIPPManager *ippManager,
    void *clientContext,
    NvMediaIPPEventCallback eventCallback
);

/**
 * \brief Starts the IPP pipeline.
 *
 * This function assumes that all the IPP components have been created and
 * attached together to form a pipeline.
 *
 * When invoked, all the component threads are activated. After a pipeline has
 * started, no more components can be added to the pipeline or attached
 * together.
 *
 * \param[in] ippPipeline A pointer to the IPP pipeline to start.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineStart(
    NvMediaIPPPipeline *ippPipeline
);

/**
 * \brief Stops the IPP pipeline.
 *
 * This function signals all components in the pipeline. Every component then
 * stops its processing thread and goes into stopped mode.
 *
 * Subsequently, the NvMediaIPPPipelineStart() function can restart the
 * pipeline.
 *
 * \param[in] ippPipeline A pointer to the IPP pipeline to stop.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineStop(
    NvMediaIPPPipeline *ippPipeline
);

/**
 * \brief Applies control properties to the pipeline.
 * \param[in] ippPipeline A pointer to the IPP pipeline.
 * \param[in] controlProperties A pointer to a client-allocated and filled
 *                              structure of control properties.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineApplyControlProperties(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPPropertyControls *controlProperties
);

/**
 * \brief Gets static properties of the pipeline, that is, properties that do
 * not change during the pipeline's lifetime.
 * \param[in] ippPipeline A pointer to the IPP pipeline.
 * \param[out] staticProperties A pointer to a client allocated structure
 *  to be filled with the static properties of the pipeline.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineGetStaticProperties(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPPropertyStatic *staticProperties
);

/**
 * \brief Gets default control properties for the pipeline.
 * \param[in] ippPipeline A pointer to the IPP pipeline.
 * \param[out] defaultControlsProperties A pointer to a client allocated
                       structure
 *  to be filled with the default control properties of the pipeline.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPPipelineGetDefaultControlsProperties(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPPropertyControls *defaultControlsProperties
);

/*@} <!-- Ends ipp_pipeline_creation IPP Pipeline --> */

/**
 * \defgroup ipp_plugin_algorithm IPP Control Algorithm Plugin
 * Defines IPP Control Algorithm Plugin related structures and functions.
 * @{
 */

/**
 * \brief Holds an opaque handle representing a Control Algorithm plugin.
 */
typedef void NvMediaIPPPlugin;

/**
 * Holds stream data for Control Algorithm plugin input.
 */
typedef struct
{
    /** Specifies whether the statistics are enabled or not. */
    NvMediaBool enabled;
    union {
        struct {
            /** A pointer to histogram statistics. */
            NvMediaISPStatsHistogramMeasurement *histogramStats[2];
            /** A pointer to LAC statistics. */
            NvMediaISPStatsLacMeasurementV4 *lacStats[2];
            /** A pointer to flicker band statistics. */
            NvMediaISPStatsFlickerBandMeasurement *flickerBandStats;
        } v4;
        struct {
            /** A pointer to histogram statistics. */
            NvMediaISPStatsHistogramMeasurementV5 *histogramStats[2];
            /** A pointer to LAC statistics. */
            NvMediaISPStatsLacMeasurementV5 *lacStats[2];
            /** A pointer to flicker band statistics. */
            NvMediaISPStatsFlickerBandMeasurementV5 *flickerBandStats;
        } v5;
    };
} NvMediaIPPPluginInputStreamData;

/**
 * Holds Control Algorithm plugin input parameters.
 */
typedef struct
{
    /** Image information. */
    NvMediaIPPImageInformation imageInfo;
    /** A pointer to properties that determine the operation mode of the Plugin
     Control Algorithm. */
    NvMediaIPPPropertyControls *controlsProperties;
    /** Holds exposure control values associated with the currently processed
     image. */
    NvMediaISCExposureControl exposureControl;
    /** Holds the two sets of white balance gain control values, one
     *  associated with sensor before hdr merge and other associated
     *  with ISP after hdr merge. */
    NvMediaISCWBGainControl whiteBalanceGainControl[2];
    /** Holds top embedded data of current image. */
    NvMediaISCEmbeddedDataBuffer topEmbeddedData;
    /** Holds bottom embedded data of current image. */
    NvMediaISCEmbeddedDataBuffer bottomEmbeddedData;
    /** Holds an array of NvMediaIPPPluginInputStreamData. */
    NvMediaIPPPluginInputStreamData streamData[NVMEDIA_IPP_STREAM_MAX_TYPES];
    /** Holds first run flag. */
    NvMediaBool firstRun;
    /** Holds scene brightness. */
     float_t brightness;
} NvMediaIPPPluginInput;

/**
 * Holds stream-specific settings of Control Algorithm plugin output.
 */
typedef struct
{
    union {
        struct {
            /** Holds validity flags for histogram settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool histogramSettingsValid[2];
            /** Holds histogram settings.
              * Settings are applied if the \ref histogramSettingsValid is set
              * to NVMEDIA_TRUE. */
            NvMediaISPStatsHistogramSettingsV4 histogramSettings[2];
            /** Holds validity flags for LAC settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool lacSettingsValid[2];
            /** Holds LAC settings.
              * Settings are applied if \ref lacSettingsValid is set to
              * NVMEDIA_TRUE. */
            NvMediaISPStatsLacSettingsV4 lacSettings[2];
            /** Holds validity flags for flicker band settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool flickerBandSettingsValid;
            /** Holds flicker band settings.
              * Settings are applied if \ref flickerBandSettingsValid is set to
              * NVMEDIA_TRUE. */
            NvMediaISPStatsFlickerBandSettingsV4 flickerBandSettings;
        } v4;
        struct {
            /** Holds validity flags for histogram settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool histogramSettingsValid[2];
            /** Holds histogram settings.
              * Settings are applied if \ref histogramSettingsValid is set to
              * NVMEDIA_TRUE. */
            NvMediaISPStatsHistogramSettingsV5 histogramSettings[2];
            /** Holds validity flags for LAC settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool lacSettingsValid[2];
            /** Holds LAC settings.
              * Settings are applied if \ref lacSettingsValid is set to
              * NVMEDIA_TRUE. */
            NvMediaISPStatsLacSettingsV5 lacSettings[2];
            /** Holds validity flags for flicker band settings.
              * Set to NVMEDIA_TRUE if the settings are required. */
            NvMediaBool flickerBandSettingsValid;
            /** Holds flicker band settings.
              * Settings are applied if \ref flickerBandSettingsValid is set to
              * NVMEDIA_TRUE. */
            NvMediaISPStatsFlickerBandSettingsV5 flickerBandSettings;
        } v5;
    };
} NvMediaIPPPluginOutputStreamSettings;

/**
 * Maximum numbers of exposure sets for bracketed exposure.
 */
#define NVMEDIA_IPP_MAX_EXPOSURE_SETS 8

/**
 * Holds Control Algorithm plugin output parameters for bracketed exposure.
 */
typedef struct
{
    /** Holds flag to indicate bracketed or continuous exposure. */
    NvMediaBool useBracketedExp;
    /** Holds the auto exposure state. */
    NvMediaIPPAeState aeState;
    /** Holds the number of sets. */
    uint32_t numExposureControl;
    /** Holds the exposure control values calculated by the Plugin Control
     Algorithm. */
    NvMediaISCExposureControl exposureControl[NVMEDIA_IPP_MAX_EXPOSURE_SETS];
    /** Holds the auto white balance state. */
    NvMediaIPPAwbState awbState;
    /** Holds the two sets of white balance gain control values
     *  calculated by the Plugin Control Algorithm, one to apply
     *  in sensor or before hdr merge and the other to apply in ISP
     *  after hdr merge. */
    NvMediaISCWBGainControl whiteBalanceGainControl[2];
    /** Holds a color correction matrix for use with sRGB output
     *  type. */
    NvMediaIPPMathFloatMatrix colorCorrectionMatrix;
    /** Holds a color correction matrix for use with rec2020 output
     *  type. */
    NvMediaIPPMathFloatMatrix colorCorrectionsMatrixRec2020;
    /** Holds ISP digital gain calculated by the plugin control
     *  algorithm. */
    float_t ispDigitalGain;
    /** Holds an array of \ref NvMediaIPPPluginOutputStreamSettings. */
    NvMediaIPPPluginOutputStreamSettings streamSettings[NVMEDIA_IPP_STREAM_MAX_TYPES];
    /** Holds CCT estimated by plugin.  */
    float_t awbCCT;
} NvMediaIPPPluginOutputEx;

/**
 * \brief Defines a function prototype that gets a sensor attribute.
 * \param[in] parentControlAlgorithmHandle  Handle passed during
 *                            the create plugin call.
 * \param[in] type Sensor attribute type.
 * \param[in] size Size of the attribute.
 * \param[out] attribute A pointer to a sensor attribute value.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_BAD_PARAMETER if the input parameters are not valid.
 * - \ref NVMEDIA_STATUS_NOT_SUPPORTED if the functionality is not supported
 *    or the attribute is not supported by the device driver.
 * - \ref NVMEDIA_STATUS_ERROR if another error occurred.
 */
typedef NvMediaStatus NvMediaIPPGetSensorAttr(
        NvMediaIPPComponent *parentControlAlgorithmHandle,
        NvMediaISCSensorAttrType type,
        uint32_t size,
        void *attribute);

/**
 * Holds the Control Algorithm plugin support functions descriptor.
 * This structure is filled by the
 * parent Control Algorithm. The plugin driver must make a copy of this
 * structure and use
 * the function pointers from it to call the support functions.
 */
typedef struct
{
    /** A pointer to a function to get a sensor attribute. */
    NvMediaIPPGetSensorAttr *getSensorAttribute;
} NvMediaIPPPluginSupportFuncs;

/**
 * \brief Creates a Plugin Control Algorithm callback.
 *
 * The client must create a callback function with the same function signature.
 * That function is called when the IPP Control Algorithm component is created.
 * \param[in] parentControlAlgorithmHandle A handle representing the parent
 *                    Control Algorithm component. The plugin Control
 *                    Algorithm must store this handle internally. This handle
 *                    must be passed to any support function.
 * \param[in] supportFunctions A pointer to a list of function pointers which
 *                    the Plugin
 *                    Control Algorithm can call. The parent Control Algorithm
 *                    fills this structure. The plugin driver must
 *                    copy this structure and use the function
 *                    pointers to call the support functions.
 * \param[in] staticProperties A pointer to static properties associated with
 *                    the camera.
 * \param[in] clientContext A pointer to a client context passed in the Control
 *                    Algorithm configuration structure.
 * \param[out] pluginHandle The Plugin Control Algorithm's handle.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
typedef NvMediaStatus NvMediaIPPluginCreateFunc(
        NvMediaIPPComponent *parentControlAlgorithmHandle,
        NvMediaIPPPluginSupportFuncs *supportFunctions,
        NvMediaIPPPropertyStatic *staticProperties,
        void *clientContext,
        NvMediaIPPPlugin **pluginHandle,
        NvMediaIPPISPVersion ispVersion);

/**
 * \brief Creates a Plugin Control Algorithm Destroy callback function.
 *
 * The client must create a function with the same function signature. That
 *  function is called when the IPP Control Algorithm component is destroyed.
 * \param[in] pluginHandle The Plugin Control Algorithm's handle.
 * \return void
 */
typedef void NvMediaIPPPluginDestroyFunc(
        NvMediaIPPPlugin *pluginHandle);

/**
 * \brief Creates the Plugin Control Algorithm Process callback function
 *  for bracketed exposure.
 *
 * The client must create a function with
 *  the same function signature. That function is called when the IPP Control
 *  Algorithm component is processing the statistics information for an image.
 * \param[in] pluginHandle Plugin Control Algorithm handle.
 * \param[in] pluginInput A pointer to the input parameters for the plugin
 *                    Control Algorithm.
 * \param[out] pluginOutput Output parameters that the plugin Control
 *                    Algorithm generates.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *   \ref NVMEDIA_STATUS_OK if successful, or
 *   \ref NVMEDIA_STATUS_ERROR otherwise.
 */
typedef NvMediaStatus NvMediaIPPPluginProcessExFunc(
        NvMediaIPPPlugin *pluginHandle,
        NvMediaIPPPluginInput *pluginInput,
        NvMediaIPPPluginOutputEx *pluginOutput);
/**
 * Holds the Control Algorithm plugin function descriptor. This structure
 * must be filled by the client
 * and passed to the Control Algorithm component as a configuration parameter.
 */
typedef struct
{
    /** A pointer to the Plugin Control Algorithm Create function. */
    NvMediaIPPluginCreateFunc *createFunc;
    /** A pointer to the Plugin Control Algorithm Destroy function. */
    NvMediaIPPPluginDestroyFunc *destroyFunc;
    /** A pointer to Plugin Control Algorithm Process function. */
    NvMediaIPPPluginProcessExFunc *processExFunc;
} NvMediaIPPPluginFuncs;

/*@} <!-- Ends ipp_plugin_algorithm IPP Control Algorithm Plugin --> */

/**
 * \defgroup ipp_component IPP Component
 * Defines IPP component-related structures and functions.
 * @{
 */

/**
 * \hideinitializer
 * \brief Specifies IPP port types.
 */
typedef enum {
    /** \hideinitializer Image port 1. */
    NVMEDIA_IPP_PORT_IMAGE_1,
    /** Specifies image port 2. */
    NVMEDIA_IPP_PORT_IMAGE_2,
    /** Specifies statistics port 1. */
    NVMEDIA_IPP_PORT_STATS_1,
    /** Specifies sensor control port 1. */
    NVMEDIA_IPP_PORT_SENSOR_CONTROL_1,
    /** Specifies capture port for aggregate images. */
    NVMEDIA_IPP_PORT_IMAGE_CAPTURE_AGGREGATE
} NvMediaIPPPortType;

/**
 * \brief Holds new buffer pool parameters for initializing an IPP component.
 *
 */
typedef struct {
    /*! Holds port type associated with the pool. */
    NvMediaIPPPortType portType;
    /*! Holds number of pool buffer elements. */
    uint32_t poolBuffersNum;
    /*! Holds image width. */
    uint32_t width;
    /*! Holds image height. */
    uint32_t height;
    /*! Holds image surface type. */
    NvMediaSurfaceType surfaceType;
    /*! Holds image surface allocation attributes (\ref NvMediaSurfAllocAttr).
     */
    NvMediaSurfAllocAttr surfAllocAttrs[NVM_SURF_ALLOC_ATTR_MAX];
    /*! Holds number of surface allocation attributes. */
    uint32_t numSurfAllocAttrs;
    /*! Holds images count. */
    uint32_t imagesCount;
} NvMediaIPPBufferPoolParamsNew;

/**
 * \brief Holds image group buffer pool parameters for initializing an IPP
 *  component.
 */
typedef struct {
    /*! Holds port type associated with the pool. */
    NvMediaIPPPortType portType;
    /*! Holds number of pool buffer elements. */
    uint32_t poolBuffersNum;
    /*! Holds an array of surface type and allocation attributes for allocating
     \ref NvMediaImageGroup. */
    struct {
        /*! Holds image surface type. */
        NvMediaSurfaceType surfaceType;
        /*! Holds image surface allocation attributes
         (\ref NvMediaSurfAllocAttr). */
        NvMediaSurfAllocAttr surfAllocAttrs[NVM_SURF_ALLOC_ATTR_MAX];
        /*! Holds number of surface allocation attributes. */
        uint32_t numSurfAllocAttrs;
        /*! Holds a Boolean which specifies whether the top embedded is valid.
         */
        NvMediaBool topEmbeddedDataValid;
        /*! Holds a Boolean which specifies whether the bottom embedded is
         valid. */
        NvMediaBool bottomEmbeddedDataValid;
    } imageConfig[NVMEDIA_MAX_IMAGE_GROUP_SIZE];
    /*! Holds number of image configs. */
    uint32_t numImageConfigs;
} NvMediaIPPBufferPoolParamsImgGrp;

/**
 * \brief Holds configuration for an ICP component.
 */
typedef struct {
    /*! A pointer to an area that holds the capture settings. */
    NvMediaICPSettings *settings;
    /*! Holds the number of sibling images per captured frame. Zero
     indicates the non-aggregated case. */
    uint32_t siblingsNum;
} NvMediaIPPIcpComponentConfig;

/**
 * \brief Defines the prototype for the file-reader image-read callback
 *  function.
 *
 *  The client must create a callback function with the same function
 *  signature. The IPP File Reader component calls that function
 *  to read an image into the framework.
 *  The component passes a pointer to an area that holds the
 *  entire image/frame.
 * \param[in] clientContext   A pointer to the client's context.
 * \param[in] imageGroup      A pointer to the image group that the function
 *                            is to read.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *   \ref NVMEDIA_STATUS_OK if successful, or
 *   \ref NVMEDIA_STATUS_ERROR otherwise.
 */
typedef NvMediaStatus (*NvMediaIPPImgGrpReadCallback)(
        void *clientContext,
        NvMediaImageGroup *imageGroup
);

/**
 * \brief Holds configuration information for a file reader component.
 */
typedef struct {
    /*! Holds context of the client, or NULL. */
    void *clientContext;
    /*! Holds a callback function for accepting an image from NvMedia IPP
     client. */
    NvMediaIPPImgGrpReadCallback imageGroupReadCallback;
    /*! Holds the number of sibling images per frame. Zero
     indicates the non-aggregated case. */
    uint32_t siblingsNum;
} NvMediaIPPFileReaderComponentConfig;

/**
 * \brief Holds configuration information for an ISC component.
 */
typedef struct {
    NvMediaISCDevice           *iscSensorDevice;
} NvMediaIPPIscComponentConfig;

/**
 * \brief Bit mask for NVMEDIA_IPP_ISP_OUTPUT2_MODE_X values.
 */
#define NVMEDIA_IPP_ISP_OUTPUT2_MODE_MASK       (7 << 4)
#define NVMEDIA_IPP_ISP_OUTPUT2_MODE_NONE       0

/**
 * \hideinitializer
 * \brief Specifies IPP ISP attribute flags.
 */
typedef enum {
    /*! Indicates a NON-HDR ISP pipeline must be set in the ISP component. */
    NVMEDIA_IPP_ISP_MODE_NONHDR = (1 << 0),
    /*! Indicates the single ISP pipeline mode is enabled. */
    NVMEDIA_IPP_ISP_SINGLE_PIPELINE_MODE = (1 << 1),
    /*! Indicates the second ISP output mode 1 is selected. */
    NVMEDIA_IPP_ISP_OUTPUT2_MODE_1 = (1 << 4),
    /*! Indicates the second ISP output mode 2 is selected. */
    NVMEDIA_IPP_ISP_OUTPUT2_MODE_2 = (2 << 4),
    /*! Indicates the second ISP output mode 3 is selected. */
    NVMEDIA_IPP_ISP_OUTPUT2_MODE_3 = (3 << 4),
    /*! Indicates the second ISP output mode 4 is selected. */
    NVMEDIA_IPP_ISP_OUTPUT2_MODE_4 = (4 << 4),
    /*! Indicates the second ISP output mode 5 is selected. */
    NVMEDIA_IPP_ISP_OUTPUT2_MODE_5 = (5 << 4)
} NvMediaIPPIspAttrFlags;

/**
 * \brief Holds configuration information for an ISP component.
 */
typedef struct {
    /*! Holds ISP select. */
    NvMediaISPSelect ispSelect;
    /*! Holds the ISP-setting attribute flag, which specifies bit-wise OR`ed
     flags defined in the enum \ref NvMediaIPPIspAttrFlags. */
    uint32_t ispSettingAttr;
} NvMediaIPPIspComponentConfig;

/**
 * \brief Holds configuration information for a Control Algorithm component.
 */
typedef struct {
    /*! Holds image width. */
    uint32_t width;
    /*! Holds image height. */
    uint32_t height;
    /*! Holds image raw pixel order. */
    NvMediaRawPixelOrder pixelOrder;
    /*! Holds image bits per pixel. */
    NvMediaBitsPerPixel bitsPerPixel;
    /*! A pointer to a Plugin Control Algorithm function. Set to NULL if no
     plugin is required. */
    NvMediaIPPPluginFuncs *pluginFuncs;
    /* Holds client context passed to plugin Control Algorithm. */
    void *clientContext;
    /*! Holds an ISC sensor device handle used to get sensor properties. */
    NvMediaISCDevice *iscSensorDevice;
} NvMediaIPPControlAlgorithmComponentConfig;

/**
 * \brief Specifies metadata types.
 */
typedef enum {
    /*! Specifies image information. Data corresponds to
     \ref NvMediaIPPImageInformation. */
    NVMEDIA_IPP_METADATA_IMAGE_INFO,
    /*! Specifies control properties. Data corresponds to
     \ref NvMediaIPPPropertyControls. */
    NVMEDIA_IPP_METADATA_CONTROL_PROPERTIES,
    /*! Specifies dynamic properties. Data corresponds
     to \ref NvMediaIPPPropertyDynamic. */
    NVMEDIA_IPP_METADATA_DYNAMIC_PROPERTIES,
    /*! Specifies embedded data. Data corresponds to
     \ref NvMediaISCEmbeddedData.
        The top and bottom embedded lines are not provided. To get them, use
        \ref NVMEDIA_IPP_METADATA_EMBEDDED_DATA_TOP and
        \ref NVMEDIA_IPP_METADATA_EMBEDDED_DATA_BOTTOM. */
    NVMEDIA_IPP_METADATA_EMBEDDED_DATA_ISC,
    /*! Specifies the top embedded line whose size and base register are
     defined by the \a size and \a baseRegAddress fields of
       \ref NvMediaISCEmbeddedDataBuffer.  */
    NVMEDIA_IPP_METADATA_EMBEDDED_DATA_TOP,
    /*! Specifies the bottom embedded line whose size and base register are
     defined by the \a size and \a baseRegAddress fields of
       \ref NvMediaISCEmbeddedDataBuffer.  */
    NVMEDIA_IPP_METADATA_EMBEDDED_DATA_BOTTOM,
    /*! Specifies the number of metadata types */
    NVMEDIA_IPP_METADATA_MAX_TYPES
} NvMediaIPPMetadataType;

/**
 * \brief Gets the size of the specified metadata type.
 * \param[in] metadata A pointer to a buffer holding metadata.
 * \param[in] type Type of the requested metadata.
 * \return The size.
 */
uint32_t
NvMediaIPPMetadataGetSize(
    void *metadata,
    NvMediaIPPMetadataType type
);

/**
 * \brief Gets the data of the specified metadata type.
 * \param[in] metadata A pointer to the buffer holding the metadata.
 * \param[in] type Type of the requested metadata.
 * \param[out] buffer A pointer to the destination buffer.
 * \param[in] size The size of the requested data.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_ERROR if the size does not match the returned size
 *    from NvMediaIPPMetadataGetSize().
 */
NvMediaStatus
NvMediaIPPMetadataGet(
    void *metadata,
    NvMediaIPPMetadataType type,
    void *buffer,
    uint32_t size);

/**
 * \brief Gets the address of the data of the specified metadata type.
 * \param[in] metadata A pointer to a buffer holding the metadata.
 * \param[in] type Type of the requested metadata.
 * \param[out] buffer A pointer to a pointer into the metadata. The function
 *                    stores the address of the specified type of metadata in
 *                    it.
 * \param[out] size   A pointer to the size of the area allocated for the
 *                    specified type of metadata in the meta data buffer; in
 *                    other words, the size of the area indicated by \a buffer.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPMetadataGetAddress(
    void *metadata,
    NvMediaIPPMetadataType type,
    void **buffer,
    uint32_t *size);

/**
 * \brief Creates an IPP component object for image group processing.
 *
 * This function creates a component and its thread
 * and associates it with a pipeline.
 *
 * After the component is created it is not attached to any other component.
 * The NvMediaIPPComponentAttach() function must be called to create the
 * desired pipeline.
 *
 * Creating a component requires a component type, buffer pools, and a
 * configuration.
 *
 * \param[in] ippPipeline     A pointer to the NvMedia IPP pipeline to which
 *                            the component belongs.
 * \param[in] componentType   Type of the component. Currently the following
 *                            types are supported:
 *  - \ref NVMEDIA_IPP_COMPONENT_ICP
 *  - \ref NVMEDIA_IPP_COMPONENT_ICP_EX
 *  - \ref NVMEDIA_IPP_COMPONENT_ISP
 *  - \ref NVMEDIA_IPP_COMPONENT_ALG
 *  - \ref NVMEDIA_IPP_COMPONENT_ISC
 *  - \ref NVMEDIA_IPP_COMPONENT_OUTPUT
 *  - \ref NVMEDIA_IPP_COMPONENT_FILE_READER
 * \param[in] bufferPools     A pointer to a NULL terminated list of pointers
 *                    to new buffer pool parameters.
 * \param[in] componentConfig A pointer to a component specific configuration.
 * \return \ref NvMediaIPPComponent, the new IPP component's handle if
 *  successful, or NULL otherwise.
 */
NvMediaIPPComponent *
NvMediaIPPComponentCreateNew(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPComponentType componentType,
    NvMediaIPPBufferPoolParamsNew **bufferPools,
    void *componentConfig
);

/**
 * \brief Creates an IPP component object for image group processing.
 *
 * This function creates a component and its thread and associates it with a
 * pipeline.
 *
 * After the component is created it is not attached to any other component.
 * The NvMediaIPPComponentAttach() function must be called to create the desired
 * pipeline.
 *
 * Creating a component requires a component type, buffer pools, and a
 * configuration.
 *
 * \param[in] ippPipeline A pointer to the NvMedia IPP pipeline to which the
 *  component belongs.
 * \param[in] componentType Type of the component. Currently the following
 *                    types are supported:
 *  - \ref NVMEDIA_IPP_COMPONENT_ICP_EX
 *  - \ref NVMEDIA_IPP_COMPONENT_FILE_READER
 * \param[in] bufferPools A pointer to a NULL terminated list of pointers
 *                    to image group buffer pool parameters.
 * \param[in] componentConfig A pointer to a component specific configuration.
 * \return \ref NvMediaIPPComponent, the new IPP component's handle if
 *  successful, or NULL otherwise.
 */
NvMediaIPPComponent *
NvMediaIPPComponentCreateImgGrp(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPComponentType componentType,
    NvMediaIPPBufferPoolParamsImgGrp **bufferPools,
    void *componentConfig
);

/**
 * \brief Adds an IPP component to a pipeline.
 *
 * When a component is created, it belongs to its parent pipeline. In some
 * cases, however, a component must belong to multiple pipelines. Only the
 * capture component can be added to multiple pipelines because it handles
 * aggregated images that are sent to different pipelines.
 *
 * \param[in] ippPipeline A pointer to the NvMedia IPP pipeline to which the
 *                    component is to be added.
 * \param[in] ippComponent The IPP component's handle.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentAddToPipeline(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPComponent *ippComponent);

/**
 * \brief Attaches an output port of an IPP source component to an input port
 * of a destination component.
 * \param[in] ippPipeline A pointer to the NvMedia IPP pipeline to which the
 *                    components belong.
 * \param[in] srcComponent A pointer to the source component.
 * \param[in] dstComponent A pointer to the destination component.
 * \param[in] portType Specifies the type of ports to be attached. The
 *                     components are compatible only if the source has an
 *                     output port and the destination has an input port of this
 *                     type.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *    \ref NVMEDIA_STATUS_OK if successful, or
 *    \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentAttach(
    NvMediaIPPPipeline *ippPipeline,
    NvMediaIPPComponent *srcComponent,
    NvMediaIPPComponent *dstComponent,
    NvMediaIPPPortType portType
);

/**
 * \brief Holds a handle representing an IPP component output object.
 */
typedef struct {
    NvMediaImage *image;
    /** A pointer to a metadata buffer. */
    void *metadata;
    /** Holds the metadata size. */
    uint32_t metadataSize;
} NvMediaIPPComponentOutput;

/**
 * \brief Gets output from a component. Works only with a
 * \ref NVMEDIA_IPP_COMPONENT_OUTPUT component.
 *
 * If the frame is not available the function blocks until the frame becomes
 * available or the timeout expires. When processing is complete, the
 * client must return the frame by calling
 * NvMediaIPPComponentReturnOutput().
 *
 * \param[in] component Component handle.
 * \param[in] millisecondTimeout Time-out in milliseconds.
 * Use \ref NVMEDIA_IMAGE_TIMEOUT_INFINITE for infinite timeout.
 * \param[out] output A pointer to the output structure which the component is
 *                    to fill.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_TIMED_OUT if output is not received within
 *   \a millisecondTimeout time.
 * - \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentGetOutput(
    NvMediaIPPComponent *component,
    uint32_t millisecondTimeout,
    NvMediaIPPComponentOutput *output
);

/**
 * \brief Returns output to a component. Only a
 * \ref NVMEDIA_IPP_COMPONENT_OUTPUT component may be used.
 *
 * This function must be called for each output structure obtained by a call to
 * NvMediaIPPComponentGetOutput(). In the output structure, only the image
 * member must be set. When an image is returned, the associated metadata is
 * destroyed.
 *
 * The client application must return all the images that were obtained from
 * the output component. The images need not be returned in the order they were
 * obtained, though. Thus the client application may hold on to a buffer for
 * processing after it has released some buffers that were obtained later.
 *
 * \note The source component needs more buffers for output in the buffer pool
 * if the images are returned out of order. If the source component does not
 * have enough buffer for capturing or processing, pipeline errors may result.
 *
 * \param[in] component Component handle.
 * \param[out] output A pointer to the output structure to be returned.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentReturnOutput(
    NvMediaIPPComponent *component,
    NvMediaIPPComponentOutput *output
);

/**
 * \brief Holds a handle representing an IPP component output object.
 */
typedef struct {
    NvMediaImageGroup imageGroup;
    /** A pointer to the metadata buffer. */
    void *metadata;
    /** Holds the metadata size. */
    uint32_t metadataSize;
} NvMediaIPPComponentOutputImgGrp;

/**
 * \brief Gets image group output from a component. Only the
 *  \ref NVMEDIA_IPP_COMPONENT_OUTPUT supports this functionality.
 * \param[in] component Component handle.
 * \param[in] millisecondTimeout Time-out in milliseconds.
 * Use \ref NVMEDIA_IMAGE_TIMEOUT_INFINITE for an infinite timeout.
 * \param[out] output A pointer to the output structure to be filled by the
 *                    component.
 * \return \ref NvMediaStatus, the completion status of the operation:
 * - \ref NVMEDIA_STATUS_OK if successful.
 * - \ref NVMEDIA_STATUS_TIMED_OUT if the output is not received within
 *    \a millisecondTimeout time.
 * - \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentGetOutputImgGrp(
    NvMediaIPPComponent *component,
    uint32_t millisecondTimeout,
    NvMediaIPPComponentOutputImgGrp *output
);

/**
 * \brief Returns image group output to a component. Only the
 *  \ref NVMEDIA_IPP_COMPONENT_OUTPUT supports this functionality. This
 *  function must be called for each output structure
 *  received by NvMediaIPPComponentGetOutput().
 * \param[in] component Component handle.
 * \param[out] output A pointer to an output structure to be returned.
 * \return \ref NvMediaStatus, the completion status of the operation:
 *  \ref NVMEDIA_STATUS_OK if successful, or
 *  \ref NVMEDIA_STATUS_ERROR otherwise.
 */
NvMediaStatus
NvMediaIPPComponentReturnOutputImgGrp(
    NvMediaIPPComponent *component,
    NvMediaIPPComponentOutputImgGrp *output
);

/**
 * \brief Destroys an IPP component object.
 *
 * This function destroys an IPP component object and its thread.
 *
 * When the pipeline is destroyed with \c NvMediaIPPPipelineDestroy(), all
 * components created with this pipeline handle are also destroyed.
 *
 * \param[in] ippComponent A pointer to the IPP component object to destroy.
 * \return void
 */
void
NvMediaIPPComponentDestroy(
    NvMediaIPPComponent *ippComponent
);
/** @} <!-- Ends ipp_component IPP Component --> */

/*
 * \defgroup history_ipp History
 * Provides change history for the NvMedia Image Processing Pipeline API.
 *
 * \section history_ipp Version History
 *
 * <b> Version 1.0 </b> July 8, 2014
 * - Initial release
 *
 * <b> Version 1.1 </b> November 4, 2014
 * - Added IPP control, static and dynamic properties
 *
 * <b> Version 1.2 </b> January 15, 2015
 * - Added fileLoopBackCount to FileReader ComponentConfig
 *
 * <b> Version 1.3 </b> January 16, 2015
 * - Added plugin Control Algorithm related functions and structures
 * - Renamed Camera Driver to Control Algorithm
 * - Added version information to IPP manager create API
 *
 * <b> Version 1.4 </b> January 28, 2015
 * - Added metadata to NvMediaIPPComponentOutput
 *
 * <b> Version 1.5 </b> February 27, 2015
 * - Fixed a typo in NvMediaIPPCompandingControl
 * - Changed pointers in NvMediaIPPPluginOutput to the actual types.
 *
 * <b> Version 1.6 </b> March 25, 2015
 * - Removed list of sensor modes from NvMediaIPPPropertyStatic
 *
 * <b> Version 1.7 </b> March 26, 2015
 * - Added global time-stamp to info structure
 * - Changed the \ref NvMediaIPPGetAbsoluteGlobalTime to use 64-bit
 *   microsecond based time-stamp.
 *
 * <b> Version 1.8 </b> March 30, 2015
 * - Added NVMEDIA_IPP_PORT_IMAGE_CAPTURE_X capture ports
 *
 * <b> Version 1.9 </b> April 14, 2015
 * - Added \ref NvMediaIPPStreamType.
 * - Changed \ref NvMediaIPPPluginInput to have separate stats data for
 *   different streams.
 * - Changed \ref NvMediaIPPPluginOutput to have separate settings for different
 *   streams.
 *
 * <b> Version 1.10 </b> April 23, 2015
 * - Added reserved member to \ref NvMediaIPPLensShadingControl structure to
 *   resolve C and C++ structure size differences.
 *
 * <b> Version 1.11 </b> April 29, 2015
 * - Removed dynamicProperties from \ref NvMediaIPPPluginOutput structure
 * - Added aeLock, aeState, awbLock & awbState in \ref NvMediaIPPPluginOutput
 *   structure.
 *
 * <b> Version 1.12 </b> May 26, 2015
 * - Updated \ref NvMediaIPPEventCallback callback API
 *
 * <b> Version 1.13 </b> June 16, 2015
 * - Added port type NVMEDIA_IPP_PORT_IMAGE_CAPTURE_AGGREGATE
 * - Added metadataFileName to \ref NvMediaIPPFileWriterComponentConfig
 *
 * <b> Version 1.14 </b> July 17, 2015
 * - Added iscSensorDevice to \ref NvMediaIPPFileReaderComponentConfig,
 *   \ref NvMediaIPPIcpComponentConfig and
 *   \ref NvMediaIPPControlAlgorithmComponentConfig.
 *
 * <b> Version 1.15 </b> September 4, 2015
 * - Added sensorMode to \ref NvMediaIPPExposureControl
 *
 * <b> Version 1.16 </b> September 4, 2015
 * - Added NVMEDIA_IPP_EVENT_WARNING_CAPTURE_RECOVERY to
 *   \ref NvMediaIPPEventType.
 *
 * <b> Version 1.17 </b> December 8, 2015
 * - Removed ISP control functions.
 * - Added ISP version 4 support.
 *
 * <b> Version 1.18 </b> January 7, 2016
 * - Added ChannelGainRatio (Gain ratio between exposure channels).
 *
 * <b> Version 1.19 </b> January 27, 2016
 * - Added \ref NvMediaIPPPropertyStatic to \ref NvMediaIPPPluginInput.
 *
 * <b> Version 1.20 </b> Jan 27, 2016
 * - Added firstRun flag to \ref NvMediaIPPPluginInput.
 *
 * <b> Version 1.21 </b> March 11, 2016
 * - Increased maximum IPP pipelines in IPP manager to 12.
 *
 * <b> Version 1.22 </b> March 28, 2016
 * - Added NVMEDIA_IPP_EVENT_ERROR_I2C_TRANSMISSION_FAILURE event type.
 *
 * <b> Version 1.23 </b> March 29, 2016
 * - Added \ref NVMEDIA_IPP_MAX_LTM_DATA_SIZE define for max LTM data size.
 *
 * <b> Version 1.24 </b> May 3, 2016
 * - Added \ref NvMediaIPPIspAttrFlags to \ref NvMediaIPPIspComponentConfig.
 *
 * <b> Version 1.25 </b> May 4, 2016
 * - Added ModuleConfig to static properties
 *
 * <b> Version 1.26 </b> May 11, 2016
 * - Changed \ref NvMediaIPPImageInformation frameSequenceNumber type to
 *   unsigned int.
 *
 * <b> Version 1.27 </b> May 23, 2016
 * - Added NVMEDIA_IPP_EVENT_WARNING_CSI_DISCONTINUITY to
 *   \ref NvMediaIPPEventType.
 *
 * <b> Version 1.28 </b> June 16, 2016
 * - Added NVMEDIA_IPP_COMPONENT_CAPTURE_EX component for virtual channels
 *   capture support.
 *
 * <b> Version 1.29 </b> June 24, 2016
 * - Added \ref NvMediaIPPPipelineSetProperties new API to set pipeline
 *   properties.
 *
 * <b> Version 1.30 </b> June 29, 2016
 * - Added \ref NvMediaIPPPluginProcessExFunc new plugin process function for
 *   bracketed exposure.
 *
 * <b> Version 1.31 </b> July 18, 2016
 * - Added support for event based capture \ref NvMediaIPPPipelineSingleCapture.
 *
 * <b> Version 1.32 </b> September 12, 2016
 * - Added \ref NVMEDIA_IPP_PIPELINE_PROPERTY_SETTINGS_DELAY property to support
 *   sensor without embedded lines
 *
 * <b> Version 1.33 </b> October 10, 2016
 * - Added new support function for getting sensor attributes
 *   \ref NvMediaIPPGetSensorAttr.
 *
 * <b> Version 1.34 </b> February 3, 2017
 * - Added \ref NVMEDIA_IPP_METADATA_EMBEDDED_DATA_ISC for ISC embedded data
 *   inside \ref NvMediaIPPMetadataType.
 *
 * <b> Version 1.35 </b> March 10, 2017
 * - Added capture error info in \ref NvMediaIPPEventData
 * - Added new event type for CSI input stream error in \ref NvMediaIPPEventType
 *
 * <b> Version 1.36 </b> March 31, 2017
 * - Removed ISP stats version 3 support from
 *   \ref NvMediaIPPPluginOutputStreamSettings
 *   and \ref NvMediaIPPPluginInputStreamData.
 *
 * <b> Version 1.37 </b> April 13, 2017
 * - Fixed violation MISRA-C rule 10.1 in NVMEDIA_IPP_VERSION_INFO macro.
 *
 * <b> Version 2.00 </b> April 27, 2017
 * - Removed PRE_PROCESSING, POST_PROCESSING & DISPLAY components
 * - Removed ipaDevice argument from \ref NvMediaIPPManagerCreate
 * - Removed iscSensorDevice & registerImageBuffersWithIPA from CAPTURE &
 *   FILE_READER component config.
 * - Removed iscRootDevice, iscAggregatorDevice & iscSerializerDevice from ISC
 *   component config.
 * - Removed ispSettingsFile & registerImageBuffersWithIPA from ISP component
 *   config.
 * - Removed logging callback \ref NvMediaIPPPluginSupportFuncs
 * - Removed parseConfigurationFunc from \ref NvMediaIPPPluginFuncs
 * - Removed IPP session related APIs. Use
 *   \ref NvMediaIPPPipelineApplyControlProperties to apply control properties.
 * - Removed unused data structures & enums
 * - Removed captureIntent, aeExposureCompensation, requestId from
 *   \ref NvMediaIPPPropertyControls.
 * - Removed exposureTimeRange from \ref NvMediaIPPPropertyControls use
 *   GetSensorAttr API to get the exposure time range.
 * - Removed companding control from \ref NvMediaIPPPluginInput.
 * - Removed lens shading from \ref NvMediaIPPPluginOutput &
 *   \ref NvMediaIPPPluginOutputEx.
 * - Removed ISP stats version 3 support from
 *   \ref NvMediaIPPPluginOutputStreamSettings
     and \ref NvMediaIPPPluginInputStreamData.
 *
 * <b> Version 2.01 </b> May 5, 2017
 * - Removed NvMediaICPInterfaceFormat from \ref NvMediaIPPIcpComponentConfig
 *
 * <b> Version 2.02 </b> April 27, 2017
 * - Replaced NvMediaIPPExposureControl with NvMediaISCExposureControl
     - ISP digital gain is added in impacted plugin structures
     - Sensor mode & hdrRatio have been removed
 * - Replaced NvMediaIPPWBGainControl use NvMediaISCWBGainControl
 * - Removed NvMediaIPPSensorExposureMode use NvMediaISCExposureMode
 * - Removed notion of human & machine vision streams
 * - Removed NvMediaIPPCameraSensorMode
     - ActiveArraySize is added in NvMediaIPPPropertyStatic
     - For frame rate use GetSensorAttr API
     - Suface type have been removed
 * - Removed AE & AWB lock flags
 * - Removed valid flag for color correction
 * - Removed requestId from NvMediaIPPPropertyDynamic
 * - Removed sensorCFA from NvMediaIPPPropertyStatic
 * - Removed exposure time range & sensor analog gain range &
     channelGainRaio from NvMediaIPPPropertyStatic use GetSensorAttr API
 *
 * <b> Version 2.03 </b> May 15, 2017
 * - Added deprecated warning message for \ref NvMediaIPPComponentCreate
 *
 * <b> Version 2.04 </b> May 23, 2017
 * - Replaced NvMediaIPPEmbeddedDataInformation with
 *   \ref NvMediaISCEmbeddedDataBuffer.
 * - Removed frameCaptureTimeStamp from NvMediaIPPImageInformation
 * - Removed AE & AWB modes and replaced with NvMediaBool
 * - Removed unused event types.
 * - Removed NVMEDIA_IPP_PORT_IMAGE_CAPTURE_* ports use Image ports
 * - Renamed NVMEDIA_IPP_COMPONENT_CAPTURE to NVMEDIA_IPP_COMPONENT_ICP
 * - Renamed NVMEDIA_IPP_COMPONENT_CONTROL_ALGORITHM to
 *   NVMEDIA_IPP_COMPONENT_ALG.
 * - Renamed NVMEDIA_IPP_COMPONENT_SENSOR_CONTROL to NVMEDIA_IPP_COMPONENT_ISC.
 * - Renamed NVMEDIA_IPP_COMPONENT_CAPTURE_EX to NVMEDIA_IPP_COMPONENT_ICP.
 * - Changed \ref NvMediaIPPPluginInputStreamData &
 *   \ref NvMediaIPPPluginOutputStreamSettings to have union for all stats.
 *
 * <b> Version 2.05 </b> May 17, 2017
 * - Added companding params in \ref NvMediaIPPPropertyStatic.
 * - Added brightness value in \ref NvMediaIPPPluginInputEx.
 * - Added awbCCT value in \ref NvMediaIPPPluginOutputEx.
 * - Renamed CurrentSceneLux to brightness in \ref NvMediaIPPPropertyDynamic.
 * - Changed whiteBalanceGainControl to be an array of two in
 *   \ref NvMediaIPPPluginOutputEx.
 * - Removed \ref NvMediaIPPPluginOutput struct and processFunc in
 *   \ref NvMediaIPPPluginFuncs.
 * - Added useBracketedExp flag in \ref NvMediaIPPPluginInputEx.
 *
 * <b> Version 2.06 </b> June 27, 2017
 * - Added file read callback functions
 *
 * <b> Version 2.07 </b> July 28, 2017
 * - Removed deprecated file writer component
 *
 * <b> Version 2.08 </b> Aug 17, 2017
 * - Add ISP Version 5 Stats structs to Plugin Interface
 * - Update NvMediaIPPISPVersion enum to add NVMEDIA_IPP_ISP_VERSION_5
 *
 * <b> Version 2.09 </b> August 25, 2017
 * - Add new APIs to support \ref NvMediaImageGroup.
 *
 * <b> Version 2.10 </b> September 05, 2017
 * - Add colorCorrectionsMatrixRec2020 in \ref NvMediaIPPPluginOutputEx.
 *
 * <b> Version 2.11 </b> September 07, 2017
 * - Add new attribute flags in \ref NvMediaIPPIspAttrFlags.
 *
 * <b> Version 2.12 </b> September 12, 2017
 * - Deprecated \ref NvMediaIPPBufferPoolParams, \ref NvMediaIPPComponentCreate
 *
 * <b> Version 2.13 </b> September 14, 2017
 * - Added frameCaptureTimeBase member to \ref NvMediaIPPImageinformation
 *
 * <b> Version 2.14 </b> September 25, 2017
 * - Add new ISP attribute flags in \ref NvMediaIPPIspAttrFlags.
 *
 * <b> Version 2.15 </b> October 13, 2017
 * - Remove NVMEDIA_IPP_METADATA_LTM_DATA metadata enum
 * - Remove NVMEDIA_IPP_MAX_LTM_DATA_SIZE define
 *
 * <b> Version 2.16 </b> January 19, 2018
 * - Added frameCaptureTSC for TSC value in \ref NvMediaIPPImageinformation
 */
/*@}*/

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IPP_H */
