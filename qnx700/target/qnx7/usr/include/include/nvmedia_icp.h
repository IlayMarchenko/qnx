/*
 * Copyright (c) 2014-2018, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file nvmedia_icp.h
 * \brief <b> NVIDIA Media Interface: Image Capture Processing </b>
 *
 * This file contains the \ref image_capture_api "Image Capture Processing API".
 */

#ifndef _NVMEDIA_ICP_H
#define _NVMEDIA_ICP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_surface.h"
#include "nvmedia_image.h"

/**
 * \defgroup image_capture_api Image Capture
 *
 * Captures uncompressed image data, writing
 * the results to an \ref NvMediaImage.
 *
 * A specific NvMedia implementation may support capturing multiple
 * types of uncompressed image data. However, NvMediaICP objects
 * are able to capture a specific type of uncompressed image data.
 * This type must be specified during creation.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_ICP_VERSION_MAJOR   4
/** \brief Minor Version number */
#define NVMEDIA_ICP_VERSION_MINOR   8

/**
 * \hideinitializer
 * \brief Defines an infinite time-out for \ref NvMediaICPGetFrameEx.
 */
#define NVMEDIA_IMAGE_CAPTURE_TIMEOUT_INFINITE  0xFFFFFFFF

/** Defines the maximum number of virtual groups */
#define NVMEDIA_ICP_MAX_VIRTUAL_GROUPS     4u

/** Defines the maximum number of virtual channels per virtual group */
#define NVMEDIA_ICP_MAX_VIRTUAL_CHANNELS   3u

/** Defines a macro that gets NvMediaICP handler from NvMediaICPEx handler.
 * \param[in] icpEx The NvMediaICPEx handler returned from NvMediaICPCreateEx.
 * \param[in] groupIdx The index of the capture group instance.
 */
#define NVMEDIA_ICP_HANDLER(icpEx, groupIdx) (icpEx->icp[groupIdx].hIcp)

/** Defines a macro that gets the NvMediaICPSettings handler from the
 *  NvMediaICPSettingsEx object.
 * \param[in] icpSettingsEx NvMediaICPSettingsEx object passed to NvMediaICPCreateEx.
 * \param[in] groupIdx The index of the capture group instance.
 * \param[in] vcIdx    The index of the capture virtual channel instance.
 */
#define NVMEDIA_ICP_SETTINGS_HANDLER(icpSettingsEx, groupIdx, vcIdx) \
        (&icpSettingsEx.virtualGroups[groupIdx].virtualChannels[vcIdx].icpSettings)

#define NVMEDIA_ICP_ERROR(_type_, _error_, _value_, _desc_)   \
        NVMEDIA_ICP_##_type_##_ERROR_##_error_ = _value_,

/**
 * \brief Determines the image capture interface type for CSI interface
 */
typedef enum {
    /*! Interface: CSI, port: A */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_A,
    /*! Interface: CSI, port: B */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_B,
    /*! Interface: CSI, port: AB */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_AB,
    /*! Interface: CSI, port: C */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_C,
    /*! Interface: CSI, port: D */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_D,
    /*! Interface: CSI, port: CD */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_CD,
    /*! Interface: CSI, port: E */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_E,
    /*! Interface: CSI, port: F */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_F,
    /*! Interface: CSI, port: EF */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_EF,
    /*! Interface: CSI, port: G */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_G,
    /*! Interface: CSI, port: H */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_H,
    /*! Interface: CSI, port: GH */
    NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_CSI_GH,
} NvMediaICPInterfaceType;

/**
 * \brief Determines the image capture input format type
 */
typedef enum {
    /*! Input format type : YUV 4:2:2 8bits */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_YUV422,
    /*! Input format type : YUV 4:2:2 10bits */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_YUV422_10,
    /*! Input format type : YUV 4:4:4 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_YUV444,
    /*! Input format type : RGBA */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RGB888,
    /*! Input format type: RAW 6 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW6,
    /*! Input format type: RAW 7 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW7,
    /*! Input format type: RAW 8 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW8,
    /*! Input format type: RAW 10 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW10,
    /*! Input format type: RAW 12 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW12,
    /*! Input format type: RAW 14 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW14,
    /*! Input format type: RAW 16 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW16,
    /*! Input format type: RAW 20 */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW20,
    /*! Input format type : User defined 1 (0x30) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_1,
    /*! Input format type : User defined 2 (0x31) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_2,
    /*! Input format type : User defined 3 (0x32) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_3,
    /*! Input format type : User defined 4 (0x33) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_4,
    /*! Input format type : User defined 5 (0x34) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_5,
    /*! Input format type : User defined 6 (0x35) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_6,
    /*! Input format type : User defined 7 (0x36) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_7,
    /*! Input format type : User defined 8 (0x37) */
    NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER_DEFINED_8
} NvMediaICPInputFormatType;

/**
 * \brief Capture input format
 */
typedef struct {
    /*! Capture input format type */
    NvMediaICPInputFormatType inputFormatType;
    /*! Number of bits per pixel
     *  It is used when the bits per pixel doesn't match with input format type */
    NvMediaBitsPerPixel bitsPerPixel;
} NvMediaICPInputFormat;

/**
 * \brief Specifies CSI phy mode.
 */
typedef enum {
    /* CSI is in Dphy mode */
    NVMEDIA_ICP_CSI_DPHY_MODE = 0,
    /* CSI is in CPHY mode */
    NVMEDIA_ICP_CSI_CPHY_MODE
} NvMediaICPCsiPhyMode;

/**
 * Holds image capture settings for the CSI format.
 */
typedef struct {
    /*! Holds the interface type. */
    NvMediaICPInterfaceType interfaceType;
    /*! Holds the input format. */
    NvMediaICPInputFormat inputFormat;
    /*! Holds the capture surface type */
    NvMediaSurfaceType surfaceType;
    /*! Holds the capture width. */
    uint16_t width;
    /*! Holds the capture height. */
    uint16_t height;
    /*! Holds the horizontal start position. */
    uint16_t startX;
    /*! Holds the vertical start position. */
    uint16_t startY;
    /*! Holds the embedded data lines. */
    uint16_t embeddedDataLines;
    /*! Holds the number of CSI interface lanes active. */
    uint32_t interfaceLanes;
    /*! Holds the pixel clock frequency. This parameter is mandatory.
     *  Can be calculated using: HTS * VTS * frame rate, unit is Hz. */
    uint32_t pixelFrequency;
    /*! Holds the mipi speed in kHz. */
    uint32_t mipiSpeed;
    /*! Holds the MIPI THS-SETTLE time. Interpretation of the value is SOC-specific. */
    uint16_t thsSettle;
    /*! Holds the flag of embedded data type.
     *  Enable this flag when embedded lines come with embedded data type in CSI packets. */
    NvMediaBool embeddedDataType;
    /*! TPG enabled */
    uint8_t tpgEnable;
    /*! Holds the CSI phy mode */
    NvMediaICPCsiPhyMode phyMode;
} NvMediaICPSettings;

/**
* Holds the image capture settings for the CSI format.
* group
*/
typedef struct {
    /*! Holds the interface type. */
    NvMediaICPInterfaceType interfaceType;
    /*! Holds the number of active CSI interface lanes.
     * In case of DPHY, each interfaceLane corresponds to 2 data lanes.
     * In case of CPHY, each interfaceLane corresponds to 3 data lanes. */
    uint32_t interfaceLanes;
    struct {
        struct {
            /* Holds the virtual Channel Index from CSI TX. */
            uint16_t virtualChannelIndex;
            /* Holds the image capture settings for CSI format. */
            NvMediaICPSettings icpSettings;
            /* Holds the clipping rectangle. */
            NvMediaRect clipRect;
        } virtualChannels[NVMEDIA_ICP_MAX_VIRTUAL_CHANNELS];
        /*! Holds the number of virtual channels per group */
        uint16_t numVirtualChannels;
    } virtualGroups[NVMEDIA_ICP_MAX_VIRTUAL_GROUPS];
    /*! Holds the number of virtual groups */
    uint16_t numVirtualGroups;
    /*! Holds the CSI phy mode */
    NvMediaICPCsiPhyMode phyMode;
} NvMediaICPSettingsEx;

/**
 * \brief Image capture object per virtual group.
 */
typedef void NvMediaICP;

/**
 * \brief Holds the image capture object created by \ref NvMediaICPCreateEx.
 */
typedef struct {
    /* Holds the number of virtual groups used. */
    uint16_t numVirtualGroups;
    struct {
        /* Holds the virtual Group Index. */
        uint16_t virtualGroupId;
        /* Holds the image capture handler. */
        NvMediaICP *hIcp;
    } icp[NVMEDIA_ICP_MAX_VIRTUAL_GROUPS];
} NvMediaICPEx;

/**
 * \brief Capture error status.
 */
typedef enum {
    /* Unrecognized or no errors */
    NVMEDIA_ICP_ERROR(CAPTURE, NONE,              0x0000, "Either no error occurred or error could not be translated")

    /* CSI mux frame errors */
    NVMEDIA_ICP_ERROR(CSI, FS_FAULT,              0x0001, "A frame start occurred before previous frame end")
    NVMEDIA_ICP_ERROR(CSI, FE_CSI_FAULT,          0x0002, "A NVCSI fault received at frame end")
    NVMEDIA_ICP_ERROR(CSI, FE_FRAMEID_FAULT,      0x0003, "Frame ID for FE packet does not match that of FS packet")
    NVMEDIA_ICP_ERROR(CSI, FE_FORCED_FAULT,       0x0004, "A frame end was injected by the CSI hardware")
    NVMEDIA_ICP_ERROR(CSI, PXL_ENABLE_FAULT ,     0x0005, "An illegal pixel encoding has been detected")

    /* VI channel sel errors */
    NVMEDIA_ICP_ERROR(VI, SHORT_FRAME,            0x0010, "FE packet arrived before the normal number of pixels has appeared ")
    NVMEDIA_ICP_ERROR(VI, FAULT_FE,               0x0011, "Data specific fault occurred on a channel")

    /* VI channel sel faults */
    NVMEDIA_ICP_ERROR(VI, PXL_MISSING_LE,         0x0100, "Two LS packets were detected without a LE packet between them")
    NVMEDIA_ICP_ERROR(VI, PXL_RUNAWAY,            0x0101, "More lines were received than expected")
    NVMEDIA_ICP_ERROR(VI, PXL_SPURIOUS,           0x0102, "A pixel data packet was received without a LS packet first")
    NVMEDIA_ICP_ERROR(VI, PXL_LONG_LINE,          0x0103, "More pixels were received than expected in a line")
    NVMEDIA_ICP_ERROR(VI, PXL_SHORT_LINE,         0x0104, "Fewer pixels were received than expected in a line")
    NVMEDIA_ICP_ERROR(VI, EMB_MISSING_LE,         0x0105, "Two LS packets were detected without a LE packet between them in emb data")
    NVMEDIA_ICP_ERROR(VI, EMB_RUNAWAY,            0x0106, "More lines were received than expected in emb data")
    NVMEDIA_ICP_ERROR(VI, EMB_SPURIOUS,           0x0107, "A pixel data packet was received without a LS packet first in emb data")
    NVMEDIA_ICP_ERROR(VI, EMB_LONG_LINE,          0x0108, "More pixels were received than expected in a line in emb data")
    NVMEDIA_ICP_ERROR(VI, EMB_INFRINGE,           0x0109, "Embedded data was received on a frame where no embedded data was expected")
    NVMEDIA_ICP_ERROR(VI, DTYPE_MISMATCH,         0x010A, "The pixel datatype changed in the middle of the line")
} NvMediaICPErrorStatus;

/**
 * \brief Holds the capture error information populated by \ref NvMediaICPGetErrorInfo.
 */
typedef struct {
    /* Holds the CSI stream index. */
    uint32_t csiStreamId;
    /* Holds the CSI frame index generated by CSI Tx */
    uint32_t csiFrameId;
    /* Holds the virtual channel index. */
    uint32_t virtualChannelId;
    /* Holds the CSI error status. */
    NvMediaICPErrorStatus errorStatus;
} NvMediaICPErrorInfo;

/**
 * \brief Checks the version compatibility for the NvMedia ICP library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 * \n \ref NVMEDIA_STATUS_INCOMPATIBLE_VERSION if the client version does
 *                                             not match with the core version.
 */
NvMediaStatus
NvMediaICPGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an image capture object used to capture various formats
 *        of input into an \ref NvMediaImage. The supported surfaces
 *        must be obtained by NvMediaSurfaceFormatGetType() with:
 * - \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RGGB/BGGR/GRBG/GBRG, INT, 8/10/12/16/20, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCB/BCCR/CRBC/CBRC, INT, 12, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCC/CCCR/CRCC/CCRC, INT, 12, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, SEMI_PLANAR/PLANAR, UINT, 8, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUYV, 422, PACKED, UINT, 8, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_RGBA (attr, RGBA, UINT, 8, PL)
 * \param[in] settings A pointer to the settings for the capture.
 * \return \ref NvMediaICPEx The new image capture's handle or NULL if unsuccessful.
 */
NvMediaICPEx *
NvMediaICPCreateEx(
    NvMediaICPSettingsEx *settings
);

/**
 * \brief Destroys the image capture object created by \ref NvMediaICPCreateEx.
 * \param[in] icpEx A pointer to the image capture object to be destroyed.
 * \return void
 */
void
NvMediaICPDestroyEx(
    NvMediaICPEx *icpEx
);

/**
 * \brief Adds an image to the image capture pool. The pool size is determined by
 * \ref NVMEDIA_MAX_CAPTURE_FRAME_BUFFERS.
 * \param[in] icp A pointer to the image capture object to be used.
 * \param[in] image The image to be added to the pool.
 * \param[in] millisecondTimeout Time-out in milliseconds
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 */
NvMediaStatus
NvMediaICPFeedFrame(
    NvMediaICP   *icp,
    NvMediaImage *image,
    uint32_t millisecondTimeout
);

/**
 * \brief Adds an image group to the image capture pool. The pool size is determined by
 * \ref NVMEDIA_MAX_CAPTURE_FRAME_BUFFERS.
 * \param[in] icp The image capture object to be used.
 * \param[in] imageGrp The NvMedia image group to be added to the pool.
 * \param[in] millisecondTimeout Time-out in milliseconds
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 */
NvMediaStatus
NvMediaICPFeedImageGroup(
    NvMediaICP   *icp,
    NvMediaImageGroup *imageGrp,
    unsigned int millisecondTimeout
);

/**
 * \brief Stops the image capture.
 * This function stops the HW engine from capturing the image.
 * To restart image capture:
 * 1. Call NvMediaICPReleaseFrame().
 * 2. Call NvMediaICPResume().
 *
 * \param[in] icp A pointer to the image capture object to be used.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if icp is NULL
 * \n \ref NVMEDIA_STATUS_ERROR if the image capture pool is not empty yet.
 */
NvMediaStatus
NvMediaICPStop(
    NvMediaICP *icp
);

/**
 * \brief Resumes the image capture.
 * This function resumes the capture process on the HW engine.
 * This function returns \ref NVMEDIA_STATUS_ERROR if the capture had not
 * previously been stopped with  NvMediaICPStop().
 * \param[in] icp  A pointer to the image capture object to be used.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if icp is NULL
 * \n \ref NVMEDIA_STATUS_ERROR if the capture engine hasn't stopped.
 */
NvMediaStatus
NvMediaICPResume(
    NvMediaICP *icp);

/**
 * \brief Gets a captured frame with frame status.
 * This function blocks until a frame is available
 * or until the timeout (in milliseconds) has been reached.  To block
 * without a timeout, specify \ref NVMEDIA_IMAGE_CAPTURE_TIMEOUT_INFINITE
 * for \a millisecondTimeout.
 * The returned \ref NvMediaImage should be passed back to the \ref NvMediaICP
 * object using \ref NvMediaICPFeedFrame after it has been processed if more
 * image capture are required.
 * NvMediaImage gets NULL if image capture object does not have
 * sufficient buffers in the internal pool, meaning that too few NvMediaImage have
 * been added to the capture object pool. When NvMediaICPGetFrameEx
 * returns an \ref NvMediaImage, that image is idle and ready for immediate use.
 * \param[in] icp A pointer to the image capture object to be used.
 * \param[in] millisecondTimeout Time-out in milliseconds
 * \param[in,out] image The image is ready for use.
 * \return \ref NvMediaStatus The completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : image has valid value, it is good to use.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : image is NULL, there is no fed frame,
 *         internel pool is empty.
 * \n \ref NVMEDIA_STATUS_TIMED_OUT : image is NULL, the frame is not ready for use.
 * \n \ref NVMEDIA_STATUS_ERROR : image is NULL, HW gives up to capture anymore.
 *         Please remove the frames from pool with NvMediaICPReleaseFrame().
 */
NvMediaStatus
NvMediaICPGetFrameEx(
    NvMediaICP *icp,
    uint32_t millisecondTimeout,
    NvMediaImage **image
);

/**
 * \brief Gets a captured image group with frame status.
 * This function blocks until a frame is available
 * or until the timeout (in milliseconds) has been reached.  To block
 * without a timeout, specify \ref NVMEDIA_IMAGE_CAPTURE_TIMEOUT_INFINITE
 * for \a millisecondTimeout.
 * \param[in] icp A pointer to the image capture object to be used.
 * \param[in] millisecondTimeout Time-out in milliseconds.
 * \param[in,out] imageGrp An indirect pointer to the NvMedia image group that
 *                is ready for use.
 * \return \ref NvMediaStatus Completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : image has valid value, it is good to use.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : image is NULL, there is no fed frame,
 *         internel pool is empty.
 * \n \ref NVMEDIA_STATUS_TIMED_OUT : image is NULL, the frame is not ready for use.
 * \n \ref NVMEDIA_STATUS_ERROR : image is NULL, HW gives up to capture anymore.
 */
NvMediaStatus
NvMediaICPGetImageGroup(
    NvMediaICP *icp,
    uint32_t millisecondTimeout,
    NvMediaImageGroup **imageGrp
);

/**
 * \brief Gets a frame from the internal pool that the client previously
 * supplied with NvMediaICPFeedFrame().
 * Call this function after the HW gives up on the capture.
 * This function must be repeatedly called until it returns
 * \ref NVMEDIA_STATUS_ERROR or \ref NVMEDIA_STATUS_NONE_PENDING.
 * \param[in] icp A pointer to the image capture object to be used.
 * \param[in,out] image Image that the caller provided but on which the HW gave
 *                up trying to capture.
 * \return \ref NvMediaStatus Completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : returning the frame that user fed.
 * \n \ref NVMEDIA_STATUS_ERROR : error while returning the frame.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : nothing to return.
 */
NvMediaStatus
NvMediaICPReleaseFrame(
    NvMediaICP *icp,
    NvMediaImage **image
);

/**
 * \brief Gets an image group from the internal pool that the client
 * previously supplied with NvMediaICPFeedImageGroup().
 * Call this function after the HW gives up on the capture.
 * This function must be repeatedly called until it returns
 * \ref NVMEDIA_STATUS_ERROR.
 * \param[in] icp A pointer to the image capture object to be used.
 * \param[in,out] imageGrp The image group was fed from user but HW gives up to capture.
 * \return \ref NvMediaStatus The completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : returning the image group that user fed.
 * \n \ref NVMEDIA_STATUS_ERROR : error while returning the image group.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : nothing to return.
 */
NvMediaStatus
NvMediaICPReleaseImageGroup(
    NvMediaICP *icp,
    NvMediaImageGroup **imageGrp
);

/**
 * \brief Gets the capture error information.
 * This function provides the capture error details such as CSI stream ID, frame ID
 * and  error status. You can use this information to determine a suitable response to
 * a CSI capture error.
 * \param[in] icp  A pointer to the image capture object to be used.
 * \param[in] icpErrorInfo A pointer to the structure where information is to be filled.
 * The info structure will not provide a meaningful value unless the retuned status is NVMEDIA_STATUS_OK
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK if info is populated and can be read
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if icp or icpErrorInfo is NULL
 */
NvMediaStatus
NvMediaICPGetErrorInfo(
    NvMediaICP *icp,
    NvMediaICPErrorInfo *icpErrorInfo
);

/**
 * \brief Waits for next SoF(Start of Frame).
 * This function blocks until the next SoF event is received.
 * This function works only if the capture pool is not empty.
 * If the pool is empty NVMEDIA_STATUS_NONE_PENDING error is returned.
 * \param[in] icp  A pointer to the image capture object to be used.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK : if upcoming SoF is received.
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER : if icp is NULL.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : if there is no fed frame,
 *         so the internal capture pool is empty.
 * \n \ref NVMEDIA_STATUS_ERROR : error while waiting for SoF excluding the above error
 *         cases.
 *
 */
NvMediaStatus
NvMediaICPWaitForSoF(
    NvMediaICP *icp
);

/*
 * \defgroup history_nvmedia_icp History
 * Provides change history for the NvMedia ICP API.
 *
 * \section history_nvmedia_icp Version History
 *
 * <b> Version 2.0 </b> April 4, 2016
 * - Initial release
 *
 * <b> Version 2.1 </b> May 11, 2016
 * - Added \ref NvMediaICPCheckVersion API
 *
 * <b> Version 2.2 </b> August 17, 2016
 * - Added \ref NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_UYVY image capture input
 * format type
 *
 * <b> Version 2.3 </b> August 31, 2016
 * - Added option for enabling embeddedDataType in \ref NvMediaICPSettings
 *
 * <b> Version 2.4 </b> Jan 23, 2017
 * - Added \ref NvMediaICPErrorInfo and \ref NvMediaICPGetErrorInfo
 *
 * <b> Version 2.5 </b> March 16, 2017
 * - Added \ref NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_USER ,
 * \ref NvMediaICPUserFormatType and option for enabling userFormatType in
 * \ref NvMediaICPInputFormat
 *
 * <b> Version 3.0 </b> April 19, 2017
 * Updated to use stdint.h instead of "unsigned int",
 *   "int", "unsigned short" and "char".
 * NvMediaICPCreate and NvMediaICPDestroy are now deprecated.
 * NvMediaICPGetFrame is now deprecated.
 * NvMediaICPInterfaceFormat is now deprecated, it will be always CSI.
 *
 * <b> Version 3.1 </b> May 12, 2017
 * - Added \ref NvMediaICPGetVersion API to get the version of NvMedia ICP library
 * - NvMediaICPCheckVersion is deprecated. Use NvMediaICPGetVersion() instead
 *
 * <b> Version 3.2 </b> May 19, 2017
 * Removed \ref NvMediaICPSurfaceFormatType
 * NvMediaICPSettings now takes NvMediaSurfaceType to indicate capture surface format
 * Removed NVMEDIA_IMAGE_CAPTURE_CSI_INTERFACE_TYPE_TPG0
 * Combined NvMediaICPUserFormatType with NvMediaICPInputFormatType
 * Removed NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_YUV420
 *   from \ref NvMediaICPInputFormatType
 * Added RAW6/RAW7/RAW8/RAW10/RAW12/RAW14 in NvMediaICPInputFormatType
 * Removed pixelOrder from \ref NvMediaICPInputFormat
 * Added tpgEnagle in \ref NvMediaICPSettings
 *
 * <b> Version 4.2 </b> June 12, 2017
 * Added virtualGroupIndex inside \ref NvMediaICPSettingsEx
 * Renamed virtualChannel to virtualGroup inside \ref NvMediaICPEx
 * Added \ref NvMediaICPFeedImageGroup and \ref NvMediaICPGetImageGroup APIs
 *
 * <b> Version 4.3 </b> October 5, 2017
 * - Added \ref NvMediaICPResume API
 *
 * <b> Version 4.4 </b> October 11, 2017
 * Changed the prototypes for \ref NvMediaICPGetImageGroup and
 * \ref NvMediaICPReleaseImageGroup to accept double pointer to imageGrp
 *
 * <b> Version 4.5 </b> November 10, 2017
 * Added YUV422_10, RAW16, RAW20 support in \ref NvMediaICPInputFormatType
 * \ref NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_YUV422_10,
 * \ref NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW16,
 * \ref NVMEDIA_IMAGE_CAPTURE_INPUT_FORMAT_TYPE_RAW20
 *
 * <b> Version 4.6 </b> November 18, 2017
 * Added additional CSI interfaces, CSI phy mode parameter to \ref NvMediaICPSettingsEX
 *
 * <b> Version 4.7 </b> March 16, 2018
 * Added mipiSpeed in \ref NvMediaICPSettings
 *
 * <b> Version 4.8 </b> September 12, 2018
 * Added NvMediaICPWaitForSoF in \ref NvMediaICPWaitForSoF
 *
 */
/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_ICP_H */
