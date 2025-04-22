#ifndef INCLUDE_GRAPHICS_H
#define INCLUDE_GRAPHICS_H

#include "graphics_include/all_res/tile1.h"
#include "graphics_include/all_res/tile2.h"
#include "graphics_include/all_res/tile3.h"
#include "graphics_include/all_res/tile_cave.h"
#include "graphics_include/all_res/tile_desert.h"
#include "graphics_include/all_res/tile_grasslands.h"
#include "graphics_include/all_res/tile_grasslands2.h"
#include "graphics_include/all_res/tile_snowymountain.h"
#include "graphics_include/all_res/logo_240_1.h"
#include "graphics_include/all_res/logo_240_2.h"
#include "graphics_include/all_res/logo_240_3.h"
#include "graphics_include/all_res/grid_384_1.h"
#include "graphics_include/all_res/grid_384_2.h"
#include "graphics_include/all_res/grid_384_3.h"
#include "graphics_include/all_res/grid_cursor_bottom_left.h"
#include "graphics_include/all_res/grid_cursor_bottom_right.h"
#include "graphics_include/all_res/grid_cursor_top_left.h"
#include "graphics_include/all_res/grid_cursor_top_right.h"
#include "graphics_include/all_res/menu_cursor.h"
#include "graphics_include/all_res/sidebar_small_1.h"
#include "graphics_include/all_res/sidebar_small_2.h"
#include "graphics_include/all_res/sidebar_small_3.h"

#if defined(LOW_RES) // For devices that exclusively run at 240p (e.g. 3DS)
#define GRAPHICS_SCALE 2.0
#include "graphics_include/low_res/grid_mini.h"
#include "graphics_include/low_res/grid_mini_bottom_left.h"
#include "graphics_include/low_res/grid_mini_bottom_right.h"
#include "graphics_include/low_res/grid_mini_top_left.h"
#include "graphics_include/low_res/grid_mini_top_right.h"
#define logo_272_1_png NULL
#define logo_272_1_png_len 0
#define logo_272_2_png NULL
#define logo_272_2_png_len 0
#define logo_272_3_png NULL
#define logo_272_3_png_len 0
#define logo_480_1_png NULL
#define logo_480_1_png_len 0
#define logo_480_2_png NULL
#define logo_480_2_png_len 0
#define logo_480_3_png NULL
#define logo_480_3_png_len 0
#define logo_544_1_png NULL
#define logo_544_1_png_len 0
#define logo_544_2_png NULL
#define logo_544_2_png_len 0
#define logo_544_3_png NULL
#define logo_544_3_png_len 0
#define logo_720_1_png NULL
#define logo_720_1_png_len 0
#define logo_720_2_png NULL
#define logo_720_2_png_len 0
#define logo_720_3_png NULL
#define logo_720_3_png_len 0
#define logo_1080_1_png NULL
#define logo_1080_1_png_len 0
#define logo_1080_2_png NULL
#define logo_1080_2_png_len 0
#define logo_1080_3_png NULL
#define logo_1080_3_png_len 0
#define logo_1440_1_png NULL
#define logo_1440_1_png_len 0
#define logo_1440_2_png NULL
#define logo_1440_2_png_len 0
#define logo_1440_3_png NULL
#define logo_1440_3_png_len 0
#define logo_2160_1_png NULL
#define logo_2160_1_png_len 0
#define logo_2160_2_png NULL
#define logo_2160_2_png_len 0
#define logo_2160_3_png NULL
#define logo_2160_3_png_len 0

#else

#define GRAPHICS_SCALE 1.0
#include "graphics_include/normal_res/grid_mini.h"
#include "graphics_include/normal_res/grid_mini_bottom_left.h"
#include "graphics_include/normal_res/grid_mini_bottom_right.h"
#include "graphics_include/normal_res/grid_mini_top_left.h"
#include "graphics_include/normal_res/grid_mini_top_right.h"

#include "graphics_include/normal_res/logo_272_1.h"
#include "graphics_include/normal_res/logo_272_2.h"
#include "graphics_include/normal_res/logo_272_3.h"

#if defined(PSP)
#define logo_480_1_png NULL
#define logo_480_1_png_len 0
#define logo_480_2_png NULL
#define logo_480_2_png_len 0
#define logo_480_3_png NULL
#define logo_480_3_png_len 0
#define logo_544_1_png NULL
#define logo_544_1_png_len 0
#define logo_544_2_png NULL
#define logo_544_2_png_len 0
#define logo_544_3_png NULL
#define logo_544_3_png_len 0
#else
#include "graphics_include/normal_res/logo_480_1.h"
#include "graphics_include/normal_res/logo_480_2.h"
#include "graphics_include/normal_res/logo_480_3.h"
#include "graphics_include/normal_res/logo_544_1.h"
#include "graphics_include/normal_res/logo_544_2.h"
#include "graphics_include/normal_res/logo_544_3.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII) || defined(GAMECUBE)
#define logo_720_1_png NULL
#define logo_720_1_png_len 0
#define logo_720_2_png NULL
#define logo_720_2_png_len 0
#define logo_720_3_png NULL
#define logo_720_3_png_len 0
#else
#include "graphics_include/normal_res/logo_720_1.h"
#include "graphics_include/normal_res/logo_720_2.h"
#include "graphics_include/normal_res/logo_720_3.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII) || defined(GAMECUBE)
#define logo_1080_1_png NULL
#define logo_1080_1_png_len 0
#define logo_1080_2_png NULL
#define logo_1080_2_png_len 0
#define logo_1080_3_png NULL
#define logo_1080_3_png_len 0
#else
#include "graphics_include/normal_res/logo_1080_1.h"
#include "graphics_include/normal_res/logo_1080_2.h"
#include "graphics_include/normal_res/logo_1080_3.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII_U) || defined(SWITCH) || defined(WII) || defined(GAMECUBE)
#define logo_1440_1_png NULL
#define logo_1440_1_png_len 0
#define logo_1440_2_png NULL
#define logo_1440_2_png_len 0
#define logo_1440_3_png NULL
#define logo_1440_3_png_len 0
#define logo_2160_1_png NULL
#define logo_2160_1_png_len 0
#define logo_2160_2_png NULL
#define logo_2160_2_png_len 0
#define logo_2160_3_png NULL
#define logo_2160_3_png_len 0
#else
#include "graphics_include/normal_res/logo_1440_1.h"
#include "graphics_include/normal_res/logo_1440_2.h"
#include "graphics_include/normal_res/logo_1440_3.h"
#include "graphics_include/normal_res/logo_2160_1.h"
#include "graphics_include/normal_res/logo_2160_2.h"
#include "graphics_include/normal_res/logo_2160_3.h"
#endif

#endif

#endif
