/*
 * Copyright (c) 2013-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: EGL Stream </b>
 *
 * @b Description: This file contains the \ref eglstream_api "EGL Stream API".
 */

#ifndef _NVMEDIA_EGLSTREAM_H
#define _NVMEDIA_EGLSTREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_core.h"
#include "nvmedia_surface.h"
#include "nvmedia_video.h"
#include "nvmedia_image.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>

/**
 * \defgroup eglstream_api EGL Stream API
 *
 * The EGL Stream API encompasses all NvMedia EGL Stream related functionality.
 * EGL Stream support enables interaction with EGL based surfaces.
 *
 * @ingroup nvmedia_common_top
 * @{
 */

/** \brief Major Version number */
#define NVMEDIA_EGLSTREAM_VERSION_MAJOR   1
/** \brief Minor Version number */
#define NVMEDIA_EGLSTREAM_VERSION_MINOR   3

/**
 * \hideinitializer
 * \brief Infinite time-out for NvMedia EGL functions
 */
#define NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE  0xFFFFFFFF

/**
 * \brief A handle representing an EGL stream producer object.
 */
typedef struct NvMediaEGLStreamProducer {
    /*! Input surface type */
    NvMediaSurfaceType type;
    /*! Input surface width */
    EGLint width;
    /*! Input surface height */
    EGLint height;
} NvMediaEGLStreamProducer;

/**
 * \brief Get the version compatibility for the NvMedia EGLStream library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaEglStreamGetVersion(
    NvMediaVersion *version
);

/**
 * \brief Creates an EGL stream producer object.
 * \param[in] device A pointer to the device resource manager connection, which is used for the allocation.
 * \param[in] eglDisplay A pointer to the EGL display.
 * \param[in] eglStream EGL stream handle.
 * \param[in] type Type of the used surface. The supported types are:
 * \n \ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, RGBA/BGRA/ARGB, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR/PLANAR, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, SEMI_PLANAR/PLANAR, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, LUMA, NONE, PACKED, UINT, 10/16, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, XUYV, NONE, PACKED, UINT, 2_10_10_10, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RGGB/BGGR/GRBG/GBRG, INT, 12, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCB/BCCR/CRBC/CBRC, INT, 12, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCC/CCCR/CRCC/CCRC, INT, 12, PL/BL)
 * \param[in] width Width of the EGL stream producer.
 * \param[in] height Height of the EGL stream producer.
 * \retval NvMediaEGLStreamProducer The new EGL stream producer's handle or NULL if unsuccessful.
 */
NvMediaEGLStreamProducer *
NvMediaEglStreamProducerCreate(
    NvMediaDevice *device,
    EGLDisplay eglDisplay,
    EGLStreamKHR eglStream,
    NvMediaSurfaceType type,
    EGLint width,
    EGLint height
);

/**
 * Holds the attributes for an EGL stream producer.
 */
typedef struct {
    /** Specifies whether multiple producers send the same image.
        Set to NVMEDIA_FALSE to disable this mode.
        Default setting is \a multiSend disabled.
        \note The multiple sending mode must be enabled on all producers that
        are used to send an image to multiple EGLStreams. */
    NvMediaBool multiSend;
} NvMediaEglStreamProducerAttributes;

/**
 * \hideinitializer
 * \brief Defines the multiSend attribute.
 */
#define NVMEDIA_EGL_STREAM_PRODUCER_ATTRIBUTE_MULTISEND       (1 << 0)

/** \brief Changes attributes of an NvMediaEGLStreamProducer.
 *
 * \param[in] producer A pointer to the target producer.
 * \param[in] attributeMask Specifies which attributes are set. The value
 *       can be any combination of the binary OR of the following attributes:
 * \n \ref NVMEDIA_EGL_STREAM_PRODUCER_ATTRIBUTE_MULTISEND
 * \param[in] attributes A pointer to a structure that holds all the
 *        attributes, but only those are used which are indicated in the
 *        \a attributeMask.
 *
 * @par Example: Enabling Multiple Sending On A Producer
 *
 * @code
 *
 * NvMediaEglStreamProducerAttributes producerAttributes = { .multiSend = NVMEDIA_TRUE };
 * NvMediaEglStreamProducerSetAttributes(
 *   producerHandle,
 *   NVMEDIA_EGL_STREAM_PRODUCER_ATTRIBUTE_MULTISEND,
 *   & producerAttributes);
 *
 * @endcode
 */
void
NvMediaEglStreamProducerSetAttributes(
    NvMediaEGLStreamProducer *producer,
    uint32_t attributeMask,
    NvMediaEglStreamProducerAttributes *attributes
);
/**
 * \brief Destroys an EGL stream producer object.
 * \param[in] producer The EGL stream producer to destroy.
 */
void
NvMediaEglStreamProducerDestroy(
    NvMediaEGLStreamProducer *producer
);

/**
 * \brief Posts a surface to be sent to an EGL stream connection.
 * \param[in] producer The EGL stream producer object to use
 * \param[in] surface The surface to send
 * \param[in] timeStamp The desired time to display the surface or
 *   NULL if immedate displaying is required.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaEglStreamProducerPostSurface(
    NvMediaEGLStreamProducer *producer,
    NvMediaVideoSurface *surface,
    NvMediaTime *timeStamp
);

/**
 * \brief Retrieves a surface that was sent to an EGL stream using the
 * \ref NvMediaEglStreamProducerPostSurface function and the EGL stream has processed
 * and released it.
 *
 * At any point in time after streaming starts, EGLStream is required to hold at
 * least one buffer. This is to ensure the consumer has at least one buffer on
 * which to work.  As a result, applications must ensure that at least two surfaces
 * are posted to EGLStream before calling NvMediaEglStreamProducerGetSurface()
 * with the \a millisecondTimeout parameter set to \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 *
 * Consider the following sequence:
 *
 * 1. The producer posts surface1.
 * 2. The consumer acquires, processes, and releases surface1.
 *
 * In the above sequence, the producer cannot get surface1 by calling
 * NvMediaEglStreamProducerGetSurface(). Instead, it must post another surface,
 * say surface2, before it can get surface1.
 *
 * For information on multiple consumer support, see the "EGLStream Support for
 * Multiple Consumers/Producers" topic in the "Graphics Programming" chapter in the
 * <a class="el" href="../../index.html" target="_blank">Development Guide</a>.
 *
 * \param[in] producer The EGL stream producer object to use
 * \param[in] surface The surface pointer to receive
 * \param[in] millisecondTimeout The desired time-out. For infinite time-out
 *  use \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaEglStreamProducerGetSurface(
    NvMediaEGLStreamProducer *producer,
    NvMediaVideoSurface **surface,
    uint32_t millisecondTimeout
);

/**
 * \brief A handle representing an EGL stream consumer object.
 */
typedef struct NvMediaEGLStreamConsumer {
    /*! Input surface type */
    NvMediaSurfaceType type;
} NvMediaEGLStreamConsumer;

/**
 * \brief Creates an EGL stream consumer object.
 * \param[in] device The device's resource manager connection is used for the allocation.
 * \param[in] dpy EGL display handle
 * \param[in] stream EGL stream handle
 * \param[in] type Type of the used surface.
              The supported types are obtained by /ref NvMediaSurfaceFormatGetType with:
 * \n \ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, RGBA/BGRA/ARGB, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR/PLANAR, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, SEMI_PLANAR/PLANAR, UINT, 8, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, LUMA, NONE, PACKED, UINT, 10/16, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, XUYV, NONE, PACKED, UINT, 2_10_10_10, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RGGB/BGGR/GRBG/GBRG, INT, 12, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCB/BCCR/CRBC/CBRC, INT, 12, PL/BL)
 * \n \ref NVM_SURF_FMT_SET_ATTR_RAW (attr, RCCC/CCCR/CRCC/CCRC, INT, 12, PL/BL)
 * \return \ref NvMediaEGLStreamConsumer The new EGL stream consumer's handle or NULL if unsuccessful.
 */
NvMediaEGLStreamConsumer *
NvMediaEglStreamConsumerCreate(
    NvMediaDevice *device,
    EGLDisplay dpy,
    EGLStreamKHR stream,
    NvMediaSurfaceType type
);

/**
 * \brief Destroys an EGL stream consumer object.
 * \param[in] consumer The EGL stream consumer to destroy.
 * \return void
 */
void
NvMediaEglStreamConsumerDestroy(
    NvMediaEGLStreamConsumer *consumer
);

/**
 * \brief Acquires a surface that was sent by an EGL stream producer.
 * \param[in] consumer The EGL stream consumer object to use
 * \param[in] surface The surface pointer to receive
 * \param[in] millisecondTimeout The desired time-out. For infinite time-out
 *  use \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 * \param[in] timeStamp The desired time to display the surface or
 *   NULL if immedate displaying is required.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaEglStreamConsumerAcquireSurface(
    NvMediaEGLStreamConsumer *consumer,
    NvMediaVideoSurface **surface,
    uint32_t millisecondTimeout,
    NvMediaTime *timeStamp
);

/**
 * \brief Releases a surface that was received by the
 *   \ref NvMediaEglStreamConsumerAcquireSurface function.
 * \param[in] consumer The EGL stream consumer object to use
 * \param[in] surface The surface to release
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaEglStreamConsumerReleaseSurface(
    NvMediaEGLStreamConsumer *consumer,
    NvMediaVideoSurface* surface
);

/** \brief Deprecated function for legacy applications */
#define NvMediaVideoSurfaceStreamProducerCreate NvMediaEglStreamProducerCreate
/** \brief Deprecated function for legacy applications */
#define NvMediaVideoSurfaceStreamProducerDestroy NvMediaEglStreamProducerDestroy
/** \brief Deprecated function for legacy applications */
#define NvMediaPostSurface NvMediaEglStreamProducerPostSurface
/** \brief Deprecated function for legacy applications */
#define NvMediaGetSurface NvMediaEglStreamProducerGetSurface
/** \brief Deprecated function for legacy applications */
#define NvMediaEglConsumerCreate NvMediaEglStreamConsumerCreate
/** \brief Deprecated function for legacy applications */
#define NvMediaEglConsumerDestroy NvMediaEglStreamConsumerDestroy
/** \brief Deprecated function for legacy applications */
#define NvMediaEglConsumerSurfaceAcquire NvMediaEglStreamConsumerAcquireSurface
/** \brief Deprecated function for legacy applications */
#define NvMediaEglConsumerSurfaceRelease NvMediaEglStreamConsumerReleaseSurface

/**
 * \brief Posts an image to be sent to an EGL stream connection.
 *
 * For information on multiple consumer support, see the "Using NvMedia EGLStream
 * to Send to Multiple Consumers" topic in the "Graphics Guide" chapter in the
 * <a class="el" href="../../index.html" target="_blank">Development Guide</a>.
 *
 * \param[in] producer The EGL stream producer object to use.
 * \param[in] image The image to send.
 * \param[in] timeStamp The desired time to display the image or
 *   NULL if immediate displaying is required.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamProducerPostImage(
    NvMediaEGLStreamProducer *producer,
    NvMediaImage *image,
    NvMediaTime *timeStamp
);

/**
 * \brief Retrieves an image that was sent to an EGL stream using the
 * \ref NvMediaEglStreamProducerPostImage function and the EGL stream has processed
 * and released it.
 *
 * At any point in time after streaming starts, EGLStream is required to hold at
 * least one buffer. This is to ensure the consumer has at least one buffer on
 * which to work.  As a result, applications must ensure that at least two images
 * are posted to EGLStream before calling NvMediaEglStreamProducerGetImage()
 * with the \a millisecondTimeout parameter set to \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 *
 * Consider the following sequence:
 *
 * 1. The producer posts image1.
 * 2. The consumer acquires, processes, and releases image1.
 *
 * In the above sequence, the producer cannot get image1 by calling
 * NvMediaEglStreamProducerGetImage(). Instead, it must post another image,
 * say image2, before it can get image1.
 *
 * For information on multiple consumer support, see the "EGLStream Support for
 * Multiple Consumers/Producers" topic in the "Graphics Programming" chapter in the
 * <a class="el" href="../../index.html" target="_blank">Development Guide</a>.
 *
 * \param[in] producer The EGL stream producer object to use
 * \param[in] image The image pointer to receive
 * \param[in] millisecondTimeout The desired time-out. For infinite time-out
 *  use \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamProducerGetImage(
    NvMediaEGLStreamProducer *producer,
    NvMediaImage **image,
    uint32_t millisecondTimeout
);

/**
 * \brief Acquire an image that was sent by an EGL stream producer.
 * \param[in] consumer The EGL stream consumer object to use
 * \param[in] image The image pointer to receive
 * \param[in] millisecondTimeout The desired time-out. For infinite time-out
 *  use \ref NVMEDIA_EGL_STREAM_TIMEOUT_INFINITE.
 * \param[in] timeStamp The desired time to display the image or
 *   NULL if immediate displaying is required.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamConsumerAcquireImage(
    NvMediaEGLStreamConsumer *consumer,
    NvMediaImage **image,
    uint32_t millisecondTimeout,
    NvMediaTime *timeStamp
);

/**
 * \brief Releases an image that was received by the
 *   \ref NvMediaEglStreamConsumerAcquireImage function.
 * \param[in] consumer The EGL stream consumer object to use
 * \param[in] image The image to release
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamConsumerReleaseImage(
    NvMediaEGLStreamConsumer *consumer,
    NvMediaImage* image
);

/**
 * \brief Posts a block of metadata to be sent to an EGL stream connection.
 * \param[in] producer A pointer to the EGL stream producer object to use.
 * \param[in] blockIdx Block index for the desired EGLstream metadata block.
 * \param[in] dataBuf  A pointer to the data buffer to be sent.
 * \param[in] offset   The desired offset of the data to be stored in EGL stream
 *                     metadata blocks.
 * \param[in] size     The size of the data buffer to send.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamProducerPostMetaData(
    NvMediaEGLStreamProducer *producer,
    uint32_t blockIdx,
    const void *dataBuf,
    uint32_t offset,
    uint32_t size
);

/**
 * \brief Acquires specified metadata block that was sent by an EGL stream producer.
 * \param[in] consumer A pointer to the EGL stream consumer object to use.
 * \param[in] blockIdx Block index for the desired EGLstream metadata block.
 * \param[in] dataBuf  A pointer to the data buffer to receive the metadata.
 * \param[in] offset   The desired offset of the data to be queried in EGL stream
 *                     metadata blocks.
 * \param[in] size     The size of the buffer to receive the metadata.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER
 * \n \ref NVMEDIA_STATUS_TIMED_OUT
 * \n \ref NVMEDIA_STATUS_ERROR
 * \ingroup image_eglstream
 */
NvMediaStatus
NvMediaEglStreamConsumerAcquireMetaData(
    NvMediaEGLStreamConsumer *consumer,
    uint32_t blockIdx,
    void *dataBuf,
    uint32_t offset,
    uint32_t size
);

/*
 * \defgroup history_nvmedia_eglstream History
 * Provides change history for the NvMedia EglStream API.
 *
 * \section history_nvmedia_eglstream Version History
 *
 * <b> Version 1.0 </b> October 1, 2015
 * - Initial release
 *
 * <b> Version 1.1 </b> May 11, 2016
 * - Added \ref NvMediaEglStreamCheckVersion API
 *
 * <b> Version 1.2 </b> May 12, 2017
 * - Added \ref NvMediaEglStreamGetVersion API to get the version of NvMedia EglStream library
 * - NvMediaEglStreamCheckVersion is deprecated. Use NvMediaEglStreamGetVersion() instead
 * - All NvMedia data types are moved to standard data types
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_EGLSTREAM_H */
