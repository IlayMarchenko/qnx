/*
 * Copyright (c) 2012-2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef INCLUDED_NVFLIPPER_H
#define INCLUDED_NVFLIPPER_H

enum nvFlipperFormat {
    nvFlipperFormat_A8R8G8B8
};

struct nvFlipperLut {
    unsigned short *r;     /* array of 16-bit red values, value should be of form ((color << 8) | color) */
    unsigned short *g;     /* array of 16-bit green values, value should be of form ((color << 8) | color) */
    unsigned short *b;     /* array of 16-bit blue values, value should be of form ((color << 8) | color)*/
};

int nvInitFlipper(
        enum nvFlipperFormat format, /* Specifies format of frame buffer */
        int display_head, /* Display Head to use */
        /* Callback that presents pointer to the backbuffer that application
         * can fill and size of the buffer. fb_width, fb_height are width,
         * height of the visible framebuffer. Total Size of framebuffer
         * = (fb_pitch * fb_height). fb_pitch should be used to seek to next
         * row of the framebuffer.
         * Registered callback should return non-zero value for flip to
         * continue. 0 to stop issuing the callback.
         */
        int (*callback)(void *buffer, unsigned int fb_width,
            unsigned int fb_height, unsigned int fb_pitch));

void nvDeinitFlipper(void);

int nvSetLutFlipper(int head, int window, struct nvFlipperLut *lut);

#endif  // INCLUDED_NVFLIPPER_H
