#ifndef INCLUDE_GRAPHICS_H
#define INCLUDE_GRAPHICS_H

#if defined(USE_BMP) // Better performance, but higher RAM+disk space usage

#include "graphics_include_bmp/grid_cursor_bottom_left.h"
#include "graphics_include_bmp/grid_cursor_bottom_right.h"
#include "graphics_include_bmp/grid_cursor_top_left.h"
#include "graphics_include_bmp/grid_cursor_top_right.h"
#include "graphics_include_bmp/grid_mini_bottom_left.h"
#include "graphics_include_bmp/grid_mini_bottom_right.h"
#include "graphics_include_bmp/grid_mini_top_left.h"
#include "graphics_include_bmp/grid_mini_top_right.h"
#include "graphics_include_bmp/menu_cursor.h"
#include "graphics_include_bmp/sidebar_small.h"
#include "graphics_include_bmp/tile1.h"
#include "graphics_include_bmp/tile2.h"
#include "graphics_include_bmp/tile3.h"
#include "graphics_include_bmp/tile_cave.h"
#include "graphics_include_bmp/tile_desert.h"
#include "graphics_include_bmp/tile_grasslands.h"
#include "graphics_include_bmp/tile_grasslands2.h"
#include "graphics_include_bmp/tile_snowymountain.h"
#include "graphics_include_bmp/logo_240.h"

#if defined(THREEDS)
#include "graphics_include_bmp/grid_384_top.h"
#include "graphics_include_bmp/grid_384_middle.h"
#include "graphics_include_bmp/grid_384_bottom.h"
#define logo_272_img NULL
#define logo_272_img_len 0
#define logo_480_img NULL
#define logo_480_img_len 0
#define logo_544_img NULL
#define logo_544_img_len 0
#define logo_720_img NULL
#define logo_720_img_len 0
#define logo_1080_img NULL
#define logo_1080_img_len 0
#define logo_1440_img NULL
#define logo_1440_img_len 0
#define logo_2160_img NULL
#define logo_2160_img_len 0
#else
#include "graphics_include_bmp/grid_384.h"
#include "graphics_include_bmp/logo_272.h"
#include "graphics_include_bmp/logo_480.h"
#include "graphics_include_bmp/logo_544.h"
#include "graphics_include_bmp/logo_720.h"
#include "graphics_include_bmp/logo_1080.h"
#include "graphics_include_bmp/logo_1440.h"
#include "graphics_include_bmp/logo_2160.h"
#endif

#else

#include "graphics_include/grid_384.h"
#include "graphics_include/grid_cursor_bottom_left.h"
#include "graphics_include/grid_cursor_bottom_right.h"
#include "graphics_include/grid_cursor_top_left.h"
#include "graphics_include/grid_cursor_top_right.h"
#include "graphics_include/grid_mini_bottom_left.h"
#include "graphics_include/grid_mini_bottom_right.h"
#include "graphics_include/grid_mini_top_left.h"
#include "graphics_include/grid_mini_top_right.h"
#include "graphics_include/menu_cursor.h"
#include "graphics_include/sidebar_small.h"
#include "graphics_include/tile1.h"
#include "graphics_include/tile2.h"
#include "graphics_include/tile3.h"
#include "graphics_include/tile_cave.h"
#include "graphics_include/tile_desert.h"
#include "graphics_include/tile_grasslands.h"
#include "graphics_include/tile_grasslands2.h"
#include "graphics_include/tile_snowymountain.h"
#include "graphics_include/logo_240.h"

#if defined(FUNKEY)
#define logo_272_img NULL
#define logo_272_img_len 0
#else
#include "graphics_include/logo_272.h"
#endif

#if defined(PSP) || defined(FUNKEY)
#define logo_480_img NULL
#define logo_480_img_len 0
#define logo_544_img NULL
#define logo_544_img_len 0
#else
#include "graphics_include/logo_480.h"
#include "graphics_include/logo_544.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII) || defined(GAMECUBE) || defined(FUNKEY)
#define logo_720_img NULL
#define logo_720_img_len 0
#else
#include "graphics_include/logo_720.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII) || defined(GAMECUBE) || defined(FUNKEY)
#define logo_1080_img NULL
#define logo_1080_img_len 0
#else
#include "graphics_include/logo_1080.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII_U) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(FUNKEY)
#define logo_1440_img NULL
#define logo_1440_img_len 0
#define logo_2160_img NULL
#define logo_2160_img_len 0
#else
#include "graphics_include/logo_1440.h"
#include "graphics_include/logo_2160.h"
#endif

#endif

#endif