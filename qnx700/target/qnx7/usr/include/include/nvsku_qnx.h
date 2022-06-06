/*
 * Copyright (c) 2007-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software and related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef __NVSKU_H
#define __NVSKU_H
#include <stdbool.h>

int get_board_sku(void);
int get_board_rev(void);
int get_board_proj(void);
int get_board_bom(void);
bool is_base_board_e1888(void);
int get_board_skuinfo(int *proj, int *sku, int *rev, int verbose);

#endif
