#ifndef INCLUDE_GRAPHICS_H
#define INCLUDE_GRAPHICS_H

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
#include "graphics_include/logo_272.h"

#if defined(PSP)
#define logo_480_png NULL
#define logo_480_png_len 0
#define logo_544_png NULL
#define logo_544_png_len 0
#else
#include "graphics_include/logo_480.h"
#include "graphics_include/logo_544.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII)
#define logo_720_png NULL
#define logo_720_png_len 0
#else
#include "graphics_include/logo_720.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII)
#define logo_1080_png NULL
#define logo_1080_png_len 0
#else
#include "graphics_include/logo_1080.h"
#endif

#if defined(PSP) || defined(VITA) || defined(WII_U) || defined(SWITCH) || defined(WII)
#define logo_1440_png NULL
#define logo_1440_png_len 0
#define logo_2160_png NULL
#define logo_2160_png_len 0
#else
#include "graphics_include/logo_1440.h"
#include "graphics_include/logo_2160.h"
#endif

#endif