/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file nvmedia_vcp.h
 * \brief <b> NVIDIA Media Interface: Video Capture Processing </b>
 *
 * This file contains the \ref capture_api "Video Capture Processing API".
 */

#ifndef _NVMEDIA_VCP_H
#define _NVMEDIA_VCP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_video.h"

/**
 * \defgroup capture_api Video Capture
 * \ingroup nvmedia_video_top
 *
 * Captures uncompressed video data, writing
 * the results to a \ref NvMediaVideoSurface "NvMediaVideoSurface".
 *
 * A specific NvMedia implementation may support capturing multiple
 * types of uncompressed video data. However, NvMediaVideoCapture objects
 * are able to capture a specific type of uncompressed video data.
 * This type must be specified during creation.
 *
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_VCP_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_VCP_VERSION_MINOR   3

/**
 * \hideinitializer
 * \brief Infinite time-out for \ref NvMediaVideoCaptureGetFrameEx
 */
#define NVMEDIA_VIDEO_CAPTURE_TIMEOUT_INFINITE  0xFFFFFFFF

/**
 * \brief Determines the video capture interface type for CSI interface
 */
typedef enum {
    /*! Interface: CSI, port: A */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_A,
    /*! Interface: CSI, port: B */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_B,
    /*! Interface: CSI, port: AB */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_AB,
    /*! Interface: CSI, port: C */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_C,
    /*! Interface: CSI, port: D */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_D,
    /*! Interface: CSI, port: CD */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_CD,
    /*! Interface: CSI, port: E */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_E,
    /*! Interface: CSI, port: F */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_F,
    /*! Interface: CSI, port: EF */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_EF,
    /*! Interface: CSI, port: G */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_G,
    /*! Interface: CSI, port: H */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_H,
    /*! Interface: CSI, port: GH */
    NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_GH,
} NvMediaVideoCaptureInterfaceType;

/**
 * \brief Determines the video capture input format type
 */
typedef enum {
    /*! Input format: YUV 4:2:2 */
    NVMEDIA_VIDEO_CAPTURE_INPUT_FORMAT_TYPE_YUV422,
    /*! Input format: YUV 4:4:4 */
    NVMEDIA_VIDEO_CAPTURE_INPUT_FORMAT_TYPE_YUV444,
    /*! Input format: RGBA */
    NVMEDIA_VIDEO_CAPTURE_INPUT_FORMAT_TYPE_RGB888
} NvMediaVideoCaptureInputFormatType;

/**
 * \brief Video capture settings for CSI format
 */
typedef struct {
    /*! Interface type */
    NvMediaVideoCaptureInterfaceType interfaceType;
    /*! Input format */
    NvMediaVideoCaptureInputFormatType inputFormatType;
    /*! Capture surface type */
    NvMediaSurfaceType surfaceType;
    /*! Capture width */
    uint16_t width;
    /*! Capture height */
    uint16_t height;
    /*! Horizontal start position */
    uint16_t startX;
    /*! Vertical start position */
    uint16_t startY;
    /*! Extra lines (in the larger field for interlaced capture) */
    uint16_t extraLines;
    /*! Interlaced format */
    NvMediaBool interlace;
    /*! Extra lines delta between the two fields */
    uint16_t interlacedExtraLinesDelta;
    /*! Number of CSI interface lanes active */
    uint32_t interfaceLanes;
    /*! TPG enabled */
    uint8_t tpgEnable;
    /*! Pixel clock frequency. This parameter is mandatory.
     *  If the video format is standard, you can obtain the frequency
     *  from the SMPTE/CEA or VESA standard.
     *  If not, check the pixel clock frequency in the specification of
     *  the input device, or with the chip vender. */
    uint32_t pixelFrequency;
    /*! MIPI THS-SETTLE time. Interpretation of the value is SOC-specific. */
    uint16_t thsSettle;
} NvMediaVideoCaptureSettings;

/**
 * \brief Video capture object created by \ref NvMediaVideoCaptureCreate.
 */
typedef struct {
    /*! The surface type that will be returned upon capturing an image.
    */
    NvMediaSurfaceType surfaceType;
    /*! Width of the captured surface */
    uint16_t width;
    /*! Height of the captured surface */
    uint16_t height;
    /*! Number of frame buffers used to create the video capture object */
    unsigned char numBuffers;
} NvMediaVideoCapture;

/**
 * \brief Get the version information for the NvMedia VCP library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                        to be filled by the function.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaVideoCaptureGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates a capture object used to capture various formats
 *        of analog or digital video input.
 *        into a \ref NvMediaVideoSurface "NvMediaVideoSurface". The supported surfaces
 *        must be obtained by /ref NvMediaSurfaceFormatGetType with:
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, PLANAR, UINT, 8, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUYV, 422, PACKED, UINT, 8, PL)
 * - \ref NVM_SURF_FMT_SET_ATTR_RGBA (attr, RGBA, UINT, 8, PL)
 * \param[in] settings Determines the settings for the capture. Used only for the CSI interface.
 *        For VIP set it to NULL.
 * \return \ref NvMediaVideoCapture The new video capture's handle or NULL if unsuccessful.
 */
NvMediaVideoCapture *
NvMediaVideoCaptureCreate(
   NvMediaVideoCaptureSettings *settings
);

/**
 * \brief Destroyx a video capture created by \ref NvMediaVideoCaptureCreate.
 * \param[in] capture A pointer to the video capture to be destroyed.
 */
void
NvMediaVideoCaptureDestroy(
    NvMediaVideoCapture *capture
);

/**
 * \brief Stops a video capture.
 * \param[in] capture The video capture to be stopped.
 */
void
NvMediaVideoCaptureStop(
    NvMediaVideoCapture *capture
);

/**
 * \brief Gets a captured frame with frame status.
 * This function blocks until a frame is available
 * or until the timeout (in milliseconds) has been reached.  To block
 * without a timeout, specify \ref NVMEDIA_VIDEO_CAPTURE_TIMEOUT_INFINITE
 * for \a millisecondTimeout.
 * The returned \ref NvMediaVideoSurface must be passed back to the \ref NvMediaVideoCapture
 * object using NvMediaVideoCaptureReleaseFrame() after it has been processed.
 * NvMediaVideoSurface gets NULL if surface capture object does not have
 * sufficient buffers in the internal pool, meaning that too few NvMediaVideoSurface objects have
 * been added to the capture object pool. When NvMediaVideoCaptureGetFrameEx()
 * returns an \ref NVMEDIA_STATUS_OK, that surface is idle and ready for immediate use.
 * \param[in] capture A pointer to the video capture to be used.
 * \param[in] millisecondTimeout Time-out, in milliseconds
 * \param[in,out] surface Indirect pointer to a surface that is ready for use.
 * \return \ref NvMediaStatus The completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : surface has valid value, it is good to use.
 * \n \ref NVMEDIA_STATUS_NONE_PENDING : surface is NULL, there is no fed frame,
 *         internel pool is empty.
 * \n \ref NVMEDIA_STATUS_TIMED_OUT : surface is NULL, the frame is not ready for use.
 * \n \ref NVMEDIA_STATUS_ERROR : surface is NULL, HW gives up to capture anymore.
 *         Please remove the frames from pool using NvMediaVideoCaptureStop.
 */
NvMediaStatus
NvMediaVideoCaptureGetFrameEx(
    NvMediaVideoCapture *capture,
    uint32_t millisecondTimeout,
    NvMediaVideoSurface **surface
);

/**
 * \brief Adds a video frame to the video capture pool. The pool size is determined by
 * the \a maxBuffers parameter. See \ref NvMediaVideoCaptureCreate.
 * \param[in] capture The video capture object to be used.
 * \param[in] surface The surface to be added to the pool.
 * \param[in] millisecondTimeout Time-out in milliseconds.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_ERROR
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 */
NvMediaStatus
NvMediaVideoCaptureFeedFrame(
    NvMediaVideoCapture *capture,
    NvMediaVideoSurface *surface,
    uint32_t millisecondTimeout
);

/**
 * \brief Gets a frame from the internal pool that user fed with NvMediaVideoCaptureFeedFrame
 * after HW gives up to capture.
 * This function should be called until getting NVMEDIA_STATUS_ERROR.
 * \param[in] capture The video capture object to be used.
 * \param[in] surface The frame was fed from user but HW gives up to capture.
 * \return \ref NvMediaStatus The completion status of the operation.
 * \n \ref NVMEDIA_STATUS_OK : returning the frame that user fed.
 * \n \ref NVMEDIA_STATUS_ERROR : nothing to return.
 */
NvMediaStatus
NvMediaVideoCaptureReleaseFrame(
    NvMediaVideoCapture *capture,
    NvMediaVideoSurface **surface
);

/**
 * \brief Return extra lines data stored in a captured surface.
 *        Currently only NvMediaSurfaceType_R8G8B8A8 surface type
 *        is supported.
 * \param[in] capture The video capture to be used.
 * \param[in] surface Surface to get the extra lines from.
 * \param[in] extraBuf The buffer where the extra line data is stored.
 * \param[in] srcRect The source rectangle extracted out as extra lines. If NULL,
 *        the extra lines (defined at the time of capture creation) from
 *        the source surface are extracted.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL
 * \n \ref NVMEDIA_STATUS_ERROR if the surface type is not supported
 */
NvMediaStatus
NvMediaVideoCaptureGetExtraLines(
    NvMediaVideoCapture *capture,
    NvMediaVideoSurface *surface,
    void *extraBuf,
    NvMediaRect *srcRect
);

/*
 * \defgroup history_nvmedia_vcp History
 * Provides change history for the NvMedia Video Capture API.
 *
 * \section history_nvmedia_vcp Version History
 *
 * <b> Version 1.0 </b> March 21, 2017
 * - Initial release
 *
 * <b> Version 1.1 </b> April 25, 2017
 * The following APIs are deprecated -
     NvMediaVideoCaptureListVideoSurfaces()
     NvMediaVideoCaptureGetFrame(). Use NvMediaVideoCaptureGetFrameEx() instead.
     NvMediaVideoCaptureStart()
     NvMediaVideoCaptureDebugGetStatus()
     NvMediaVideoCaptureReturnFrame()
     NvMediaVideoCaptureCheckAvailableFrame(). Use NvMediaVideoCaptureReleaseFrame() instead.
 * NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_C, NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_D,
   NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_CSI_F are newly added to NvMediaVideoCaptureInterfaceType
 * NvMediaVideoCaptureGetVersion() is added to get the version of NvMedia VCP library
 * NvMediaVideoCaptureInterfaceFormat is now deprecated. Only CSI format is supported.
 * interfaceFormat member is removed from \ref NvMediaVideoCapture
 * interfaceFormat & numBuffers inputs are removed from NvMediaVideoCaptureCreate() API.
 * Internal ring buffer based capture is no more supported.
 * externalBuffer member is removed from \ref NvMediaVideoCaptureSettings.
 *
 * <b> Version 1.2 </b> May 19, 2017
 * Removed NvMediaVideoCaptureSurfaceFormatType
 * NvMediaVideoCaptureSettings now takes NvMediaSurfaceType to indicate capture surface format
 * Removed NVMEDIA_VIDEO_CAPTURE_INPUT_FORMAT_TYPE_YUV420
 *   from \ref NvMediaVideoCaptureInputFormatType
 * Removed NVMEDIA_VIDEO_CAPTURE_CSI_INTERFACE_TYPE_TPG_EF
 *
 * <b> Version 1.3 </b> November 18, 2017
 * Added CSI interfaces G & H
 *
 */

/** @} */
#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_VCP_H */
