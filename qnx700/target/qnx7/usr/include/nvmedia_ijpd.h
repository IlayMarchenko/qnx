/*
 * Copyright (c) 2014-2017, NVIDIA CORPORATION.  All rights reserved.  All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */

/**
 * \file
 * \brief <b> NVIDIA Media Interface: Image JPEG Decode Processing (IJDP)</b>
 *
 * @b Description: This file contains the \ref image_jpeg_decode_api "Image JPEG Decode Processing API".
 */

#ifndef _NVMEDIA_IJPD_H
#define _NVMEDIA_IJPD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvmedia_common.h"

/**
 * \defgroup image_jpeg_decode_api Image JPEG Decoder
 *
 * The NvMediaIJPD object takes a JPEG bitstream and decompress it to image data.
 *
 * @ingroup nvmedia_image_top
 * @{
 */

/** \brief Major version number */
#define NVMEDIA_IJPD_VERSION_MAJOR   1
/** \brief Minor version number */
#define NVMEDIA_IJPD_VERSION_MINOR   3

/**
 * \hideinitializer
 * \brief JPEG decode set alpha
 */
#define NVMEDIA_JPEG_DEC_ATTRIBUTE_ALPHA_VALUE     (1 << 0)
/**
 * \hideinitializer
 * \brief JPEG decode set color standard
 */
#define NVMEDIA_JPEG_DEC_ATTRIBUTE_COLOR_STANDARD  (1 << 1)
/**
 * \hideinitializer
 * \brief JPEG decode render flag rotate 0
 */
#define NVMEDIA_IJPD_RENDER_FLAG_ROTATE_0          0
/**
 * \hideinitializer
 * \brief JPEG decode render flag rotate 90
 */
#define NVMEDIA_IJPD_RENDER_FLAG_ROTATE_90         1
/**
 * \hideinitializer
 * \brief JPEG decode render flag rotate 180
 */
#define NVMEDIA_IJPD_RENDER_FLAG_ROTATE_180        2
/**
 * \hideinitializer
 * \brief JPEG decode render flag rotate 270
 */
#define NVMEDIA_IJPD_RENDER_FLAG_ROTATE_270        3
/**
 * \hideinitializer
 * \brief JPEG decode render flag flip horizontal
 */
#define NVMEDIA_IJPD_RENDER_FLAG_FLIP_HORIZONTAL   (1 << 2)
/**
 * \hideinitializer
 * \brief JPEG decode render flag flip vertical
 */
#define NVMEDIA_IJPD_RENDER_FLAG_FLIP_VERTICAL     (1 << 3)
/**
 * \hideinitializer
 * \brief JPEG decode max number of app markers supported
 */
#define NVMEDIA_MAX_JPEG_APP_MARKERS               16

/**
 * Holds image JPEG decoder attributes.
 */
typedef struct {
/** \brief Specifies the color standard, defined in \ref NvMediaColorStandard.
 *  The corresponding attribute mask is \ref NVMEDIA_JPEG_DEC_ATTRIBUTE_COLOR_STANDARD
 */
    NvMediaColorStandard colorStandard;
/** \brief Specifies the alpha value. It can take one of 0 or 0xFF.
 *  The corresponding attribute mask is \ref NVMEDIA_JPEG_DEC_ATTRIBUTE_ALPHA_VALUE
 */
    uint32_t alphaValue;
} NVMEDIAJPEGDecAttributes;

/**
 * Holds image JPEG decoder marker Info.
 */
typedef struct {
/** \brief Specifies the App info marker.
 */
  uint16_t marker;
/** \brief Specifies the App info marker length.
*/
  uint16_t len;
/** \brief Specifies the App info marker data.
*/
  void    *pMarker;
} NvMediaJPEGAppMarkerInfo;

/**
 * Holds image JPEG decoder stream information.
 */
typedef struct {
/** \brief Specifies the stream-encoded width, in pixels.
 */
  uint16_t width;
/** \brief Specifies the stream-encoded height, in pixels.
 */
  uint16_t height;
/** \brief Specifies whether partial acceleration is needed for the stream.
 */
  uint8_t  partialAccel;
/** \brief Specifies the number of App merkers in the stream.
 */
  uint8_t  num_app_markers;
/** \brief Specifies the marker info.
 */
  NvMediaJPEGAppMarkerInfo appMarkerInfo[NVMEDIA_MAX_JPEG_APP_MARKERS];
} NVMEDIAJPEGDecInfo;

/**
 * Holds information for decoding a JPEG stream into
 * an image surface. NvMediaIJPDCreate() uses this struct
 * to create JPEG decoder objects.
 */
typedef struct {
    /** Max width of decoded JPEG image supported. */
    uint16_t maxWidth;
    /** Max height of decoded JPEG image supported. */
    uint16_t maxHeight;
    /** Max size in bytes of JPEG bitstream supported. */
    uint32_t maxBitstreamBytes;
    /** Flag indicates support partial acceleration or not */
    uint8_t supportPartialAccel;
} NvMediaIJPD;

/**
 * \brief Gets the version compatibility for the NvMedia IJPGD library.
 * \param[in] version A pointer to a \ref NvMediaVersion structure
 *                    of the client.
 * \return \ref NvMediaStatus The status of the operation.
 * Possible values are:
 * \n \ref NVMEDIA_STATUS_OK
 * \n \ref NVMEDIA_STATUS_BAD_PARAMETER if the pointer is invalid.
 */
NvMediaStatus
NvMediaIJPDGetVersion(
    NvMediaVersion *version
);

/**
 * Creates a JPEG decoder object capable of decoding a JPEG stream into
 * an image surface.
 * \param[in] device The \ref NvMediaDevice "device" this image JPEG decoder will use.
 * \param[in] maxWidth The maximum width of output surface to support.
 *      you can use NvMediaIJPDResize() to enlarge this limit for an existing decoder.
 * \param[in] maxHeight The maximum height of output surface to support. You can use
 * \c %NvMediaIJPDResize() to enlarge this limit for an existing decoder.
 * \param[in] maxBitstreamBytes The maximum JPEG bitstream size in bytes to support.
 *      Use \c %NvMediaIJPDResize() to enlarge this limit for an existing decoder.
 * \param[in] supportPartialAccel Indicates that the JPEG decode object supports
 *      partial acceleration.
 *      \n If it does, set this argument to the character '1' (true).
 *      \n If it does not, set this argument to the character '0' (false).
 * \retval NvMediaIJPD The new image JPEG decoder handle or NULL if unsuccessful.
 */
NvMediaIJPD *
NvMediaIJPDCreate(
    NvMediaDevice *device,
    uint16_t maxWidth,
    uint16_t maxHeight,
    uint32_t maxBitstreamBytes,
    uint8_t supportPartialAccel
);

/**
 * Destroys an NvMedia image JPEG decoder.
 * \param[in] decoder A pointer to the JPEG decoder to destroy.
 */
void NvMediaIJPDDestroy(NvMediaIJPD *decoder);

/**
 * \brief Resizes an existing image JPEG decoder.
 * \param[in] decoder A pointer to the JPEG decoder to use.
 * \param[in] maxWidth  The new maximum width of output surface to support.
 * \param[in] maxHeight The new maximum height of output surface to support.
 * \param[in] maxBitstreamBytes The new maximum JPEG bitstream size in bytes to support.
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is invalid.
 * \li \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaIJPDResize (
   NvMediaIJPD *decoder,
   uint16_t maxWidth,
   uint16_t maxHeight,
   uint32_t maxBitstreamBytes
);

/**
 * \brief Sets attributes of an existing image JPEG decoder.
 * \param[in] decoder  A pointer to the JPEG decoder to use.
 * \param[in] attributeMask An attribute mask.
 *  Supported mask are:
 * \li \ref NVMEDIA_JPEG_DEC_ATTRIBUTE_ALPHA_VALUE
 * \li \ref NVMEDIA_JPEG_DEC_ATTRIBUTE_COLOR_STANDARD
 * \param[in] attributes Attributes data.
 * Supported attribute structures:
 * \li \ref NVMEDIAJPEGDecAttributes
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaIJPDSetAttributes(
   NvMediaIJPD *decoder,
   uint32_t attributeMask,
   void *attributes
);

/**
 * \brief A helper function that determines whether the JPEG decoder HW engine can decode
 * the input JPEG stream. Possible outcomes are:
 *
 * * __Decode possible__. If JPEG decoder supports decode of this stream,
 * this function returns \ref NVMEDIA_STATUS_OK and the \ref NVMEDIAJPEGDecInfo
 * info will be filled out. This function also determines
 * whether you must allocate the \ref NvMediaIJPD object when you call NvMediaIJPDCreate().
 * You specify that object with the \c %NvMediaIJPDCreate() \a supportPartialAccel parameter.
 *
 * * __Decode not possible__. If JPEG decoder cannot decode this stream,
 * this function returns \ref NVMEDIA_STATUS_NOT_SUPPORTED.
 *
 * \param[in,out] info A pointer to the information to be filled.
 * \param[in] numBitstreamBuffers The number of bitstream buffers.
 * \param[in] bitstreams The bitstream buffer.
 *
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_NOT_SUPPORTED if stream not supported
 * \li \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaIJPDGetInfo (
   NVMEDIAJPEGDecInfo *info,
   uint32_t numBitstreamBuffers,
   const NvMediaBitstreamBuffer *bitstreams
);

/**
 * Decodes a JPEG image. The decode pipeline produces a
 * result equivalent to the following sequence:
 *
 * 1. Decodes the full JPEG image.
 * 2. Downscales the 8x8 block padded image by the \a downscaleLog2 factor.
 *    That is, a "width" by "height" JPEG is downscaled to:
 *
 *        ((width + 7) & ~7) >> downscaleLog2
 *
 *    by
 *
 *        ((height + 7) & ~7) >> downscaleLog2
 *
 * 3. From the downscaled image, removes the rectangle described by *srcRect*
 *    and optionally (a) mirrors the image horizontally and/or vertically and/or
 *    (b) rotates the image.
 * 4. Scales the transformed source rectangle to the *dstRect*
 *    on the output surface.
 *
 * @par Specifying Dimensions
 *
 * The JPEG decoder object must have *maxWidth* and *maxHeight* values
 * that are greater than or equal to the post-downscale JPEG image.
 * Additionally, it must have a *maxBitstreamBytes* value that is greater than
 * or equal to the total number of bytes in the bitstream buffers. You
 * set these values when you create the JPEG decoder object
 * with NvMediaIJPDCreate().
 * Alternatively, you can user NvMediaIJPDResize() to change the dimensions
 * of an existing JPEG decoder object.
 *
 * If the JPEG decoder object has inadequate dimensions, \c %NvMediaIJPDRender()
 * returns \ref NVMEDIA_STATUS_INSUFFICIENT_BUFFERING.
 *
 *
 * @par Supporting Partial Acceleration
 *
 * If the JPEG stream requires partial acceleration, created the JPEG
 * decoder object with *supportPartialAccel* set to '1'.
 * Otherwise,  the function returns \ref NVMEDIA_STATUS_BAD_PARAMETER.
 *
 * Use NvMediaIJPDGetInfo() to determine whether a
 * stream requires paritialAccel.
 *
 * @par Determining Supported JPEG Streams
 *
 * If the JPEG stream is not supported, the function returns
 * \ref NVMEDIA_STATUS_NOT_SUPPORTED.
 *
 * Use @c %NvMediaIJPDGetInfo() to determine whether a
 * stream is unsupported.
 *
 * \note \c %NvMediaIJPDRender() with the NVJPG 1.0 codec does not support rotation.
 *
 * \param[in] decoder  A pointer to the JPEG decoder to use.
 * \param[in] output The video surface to render to. This surface type must be
 *                   obtained by \ref NvMediaSurfaceFormatGetType with
 *       \ref NVM_SURF_FMT_SET_ATTR_RGBA(attr, RGBA, UINT, 8, PL)
 * \param[in] srcRect The source rectangle. The rectangle from the post-downscaled image to be
 *      transformed and scaled to the *dstRect*. You can achieve horizontal and/or
 *      vertical mirroring by swapping the left-right and/or top-bottom
 *      coordinates. If NULL, the full post-downscaled surface is implied.
 * \param[in] dstRect The destination rectangle on the output surface. If NULL, a
 *      rectangle the full size of the output surface is implied.
 * \param[in] downscaleLog2 A value clamped between 0 and 3 inclusive, gives downscale factors
 *      of 1 to 8.
 * \param[in] numBitstreamBuffers The number of bitstream buffers.
 * \param[in] bitstreams The bitstream buffer. \c %NvMediaIJPDRender()
 *     copies the data out
 *     of these buffers so the caller is free to reuse them as soon as
 *     \c %NvMediaIJPDRender() returns.
 * \param[in] flags Flags that specify a clockwise rotation of the source in
 *     degrees and horizontal and vertical flipping.
 *     If both are specified, the image is flipped before it is rotated.
 *     You can set the *flags* argument to any one of the following:
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_0
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_90
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_180
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_270
 *
 *     Additionally, you can use the bitwise OR operation to
 *     apply either or both of the following:
 *     \li NVMEDIA_RENDER_FLAG_FLIP_HORIZONTAL
 *     \li NVMEDIA_RENDER_FLAG_FLIP_VERTICAL
 *
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaIJPDRender(
   NvMediaIJPD *decoder,
   NvMediaImage *output,
   const NvMediaRect *srcRect,
   const NvMediaRect *dstRect,
   uint8_t downscaleLog2,
   uint32_t numBitstreamBuffers,
   const NvMediaBitstreamBuffer *bitstreams,
   uint32_t flags
);

/**
 * Decodes a JPEG image into YUV format.
 * This function is similar to NvMediaIJPDRender() except that
 * the output surface is in YUV format, not RGBA format. Also, clipping
 * and scaling (other than downscaleLog2 scaling) are not supported, so
 * there are no source or destination rectangle parameters.
 *
 *   \note \c %NvMediaIJPDRenderYUV()
 *       with the NVJPG 1.0 codec has the following limitations:
 *   \li It supports chroma subsample conversion to 420 and 420H from any input
 *       format except 400.
 *   \li It does not simultaneously support downscaleLog2 and subsample conversion.

 * \param[in] decoder  A pointer to the JPEG decoder to use.
 * \param[in] output The video surface to render to. This surface type must be
 *       obtained by /ref NvMediaSurfaceFormatGetType with:
 *      \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 420, SEMI_PLANAR/PLANAR, UINT, 8, PL)
 *      \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 422, SEMI_PLANAR/PLANAR, UINT, 8, PL)
 *      \ref NVM_SURF_FMT_SET_ATTR_YUV(attr, YUV, 444, SEMI_PLANAR/PLANAR, UINT, 8, PL)
 * \param[in] downscaleLog2 A value between 0 and 3 inclusive that gives downscale
 *       factors of 1 to 8.
 * \param[in] numBitstreamBuffers The number of bitstream buffers.
 * \param[in] bitstreams The bitstream buffer. \c %NvMediaIJPDRenderYUV()
 *       copies the data out
 *       of these buffers so the caller is free to reuse them as soon as
 *       \c %NvMediaIJPDRenderYUV() returns.
 * \param[in] flags Flags that specify a clockwise rotation of the source in degrees and horizontal
 *       and vertical flipping. If both are specified, flipping is performed before rotating.
 *     You can set the \a flags argument to any one of the following:
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_0
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_90
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_180
 *     \li NVMEDIA_RENDER_FLAG_ROTATE_270
 *
 *     Additionally, you can use the bitwise OR operation to
 *     apply either or both of the following:
 *     \li NVMEDIA_RENDER_FLAG_FLIP_HORIZONTAL
 *     \li NVMEDIA_RENDER_FLAG_FLIP_VERTICAL
 *
 * \return \ref NvMediaStatus The completion status of the operation.
 * Possible values are:
 * \li \ref NVMEDIA_STATUS_OK if successful.
 * \li \ref NVMEDIA_STATUS_BAD_PARAMETER if any of the input parameter is NULL.
 * \li \ref NVMEDIA_STATUS_ERROR
 */
NvMediaStatus
NvMediaIJPDRenderYUV(
   NvMediaIJPD *decoder,
   NvMediaImage *output,
   uint8_t downscaleLog2,
   uint32_t numBitstreamBuffers,
   const NvMediaBitstreamBuffer *bitstreams,
   uint32_t flags
);

/*
 * \defgroup history_nvmedia_ijpd History
 * Provides change history for the NvMedia Image Jpeg Decode API.
 *
 * \section history_nvmedia_ijpd Version History
 *
 * <b> Version 1.0 </b> November 9, 2015
 * - Initial release
 *
 * <b> Version 1.1 </b> May 11, 2016
 * - Added \ref NvMediaIJPDCheckVersion API
 *
 * <b> Version 1.2 </b> May 15, 2017
 * - Added \ref NvMediaIJPDGetVersion API to get the version of NvMedia IJPD library
 * - NvMediaIJPDCheckVersion is deprecated. Use NvMediaIJPDGetVersion() instead
 * - All NvMedia data types are moved to standard data types
 *
 * <b> Version 1.3 </b> October 5, 2017
 * - Added \ref NvMediaJPEGAppMarkerInfo to store the App info.
 */

/** @} */

#ifdef __cplusplus
};     /* extern "C" */
#endif

#endif /* _NVMEDIA_IJPD_H */
