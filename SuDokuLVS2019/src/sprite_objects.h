#include "shared.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if defined(VITA)
#define SPRITE_PATH_TILE                     "ux0:data/SuDokuL/graphics/tile.png"
#define SPRITE_PATH_LOGO_480                 "ux0:data/SuDokuL/graphics/logo_480.png"
#define SPRITE_PATH_LOGO_720                 "ux0:data/SuDokuL/graphics/logo_720.png"
#define SPRITE_PATH_LOGO_1080                "ux0:data/SuDokuL/graphics/logo_1080.png"
#define SPRITE_PATH_LOGO_1440                "ux0:data/SuDokuL/graphics/logo_1440.png"
#define SPRITE_PATH_LOGO_2160                "ux0:data/SuDokuL/graphics/logo_2160.png"
#define SPRITE_PATH_MENU_CURSOR              "ux0:data/SuDokuL/graphics/menu_cursor.png"
#define SPRITE_PATH_GRID_384                 "ux0:data/SuDokuL/graphics/grid_384.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_LEFT  "ux0:data/SuDokuL/graphics/grid_cursor_bottom_left.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_RIGHT "ux0:data/SuDokuL/graphics/grid_cursor_bottom_right.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_LEFT     "ux0:data/SuDokuL/graphics/grid_cursor_top_left.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_RIGHT    "ux0:data/SuDokuL/graphics/grid_cursor_top_right.png"
#define SPRITE_PATH_SIDEBAR_SMALL            "ux0:data/SuDokuL/graphics/sidebar_small.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_LEFT    "ux0:data/SuDokuL/graphics/grid_mini_bottom_left.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_RIGHT   "ux0:data/SuDokuL/graphics/grid_mini_bottom_right.png"
#define SPRITE_PATH_GRID_MINI_TOP_LEFT       "ux0:data/SuDokuL/graphics/grid_mini_top_left.png"
#define SPRITE_PATH_GRID_MINI_TOP_RIGHT      "ux0:data/SuDokuL/graphics/grid_mini_top_right.png"
#elif defined(PSP)
#define SPRITE_PATH_TILE                     "ms0:/PSP/GAME/sudokul/graphics/tile.png"
#define SPRITE_PATH_LOGO_480                 "ms0:/PSP/GAME/sudokul/graphics/logo_480.png"
#define SPRITE_PATH_LOGO_720                 "ms0:/PSP/GAME/sudokul/graphics/logo_720.png"
#define SPRITE_PATH_LOGO_1080                "ms0:/PSP/GAME/sudokul/graphics/logo_1080.png"
#define SPRITE_PATH_LOGO_1440                "ms0:/PSP/GAME/sudokul/graphics/logo_1440.png"
#define SPRITE_PATH_LOGO_2160                "ms0:/PSP/GAME/sudokul/graphics/logo_2160.png"
#define SPRITE_PATH_MENU_CURSOR              "ms0:/PSP/GAME/sudokul/graphics/menu_cursor.png"
#define SPRITE_PATH_GRID_384                 "ms0:/PSP/GAME/sudokul/graphics/grid_384.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_LEFT  "ms0:/PSP/GAME/sudokul/graphics/grid_cursor_bottom_left.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_RIGHT "ms0:/PSP/GAME/sudokul/graphics/grid_cursor_bottom_right.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_LEFT     "ms0:/PSP/GAME/sudokul/graphics/grid_cursor_top_left.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_RIGHT    "ms0:/PSP/GAME/sudokul/graphics/grid_cursor_top_right.png"
#define SPRITE_PATH_SIDEBAR_SMALL            "ms0:/PSP/GAME/sudokul/graphics/sidebar_small.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_LEFT    "ms0:/PSP/GAME/sudokul/graphics/grid_mini_bottom_left.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_RIGHT   "ms0:/PSP/GAME/sudokul/graphics/grid_mini_bottom_right.png"
#define SPRITE_PATH_GRID_MINI_TOP_LEFT       "ms0:/PSP/GAME/sudokul/graphics/grid_mini_top_left.png"
#define SPRITE_PATH_GRID_MINI_TOP_RIGHT      "ms0:/PSP/GAME/sudokul/graphics/grid_mini_top_right.png"
#else
#define SPRITE_PATH_TILE                     "graphics/tile.png"
#define SPRITE_PATH_LOGO_480                 "graphics/logo_480.png"
#define SPRITE_PATH_LOGO_720                 "graphics/logo_720.png"
#define SPRITE_PATH_LOGO_1080                "graphics/logo_1080.png"
#define SPRITE_PATH_LOGO_1440                "graphics/logo_1440.png"
#define SPRITE_PATH_LOGO_2160                "graphics/logo_2160.png"
#define SPRITE_PATH_MENU_CURSOR              "graphics/menu_cursor.png"
#define SPRITE_PATH_GRID_384                 "graphics/grid_384.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_LEFT  "graphics/grid_cursor_bottom_left.png"
#define SPRITE_PATH_GRID_CURSOR_BOTTOM_RIGHT "graphics/grid_cursor_bottom_right.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_LEFT     "graphics/grid_cursor_top_left.png"
#define SPRITE_PATH_GRID_CURSOR_TOP_RIGHT    "graphics/grid_cursor_top_right.png"
#define SPRITE_PATH_SIDEBAR_SMALL            "graphics/sidebar_small.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_LEFT    "graphics/grid_mini_bottom_left.png"
#define SPRITE_PATH_GRID_MINI_BOTTOM_RIGHT   "graphics/grid_mini_bottom_right.png"
#define SPRITE_PATH_GRID_MINI_TOP_LEFT       "graphics/grid_mini_top_left.png"
#define SPRITE_PATH_GRID_MINI_TOP_RIGHT      "graphics/grid_mini_top_right.png"
#endif

struct SpriteObject {
    SDL_Texture *texture;
    SDL_Rect rect;
    Sint32 width, height;
};

struct SpriteObjectWithPos {
    SDL_Texture *texture;
    SDL_Rect rect;
    Sint32 width, height;
    Sint16 startPos_x, endPos_x;
    Sint16 startPos_y, endPos_y;
};

#define PREPARE_SPRITE(spriteObj, spriteImage, pos_x, pos_y, scale)                       \
    spriteObj.texture = IMG_LoadTexture(renderer, spriteImage);                           \
    SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.width, &spriteObj.height); \
    SET_SPRITE_SCALE(spriteObj, scale);                                                   \
    spriteObj.rect.x = pos_x;                                                             \
    spriteObj.rect.y = pos_y;

#define SET_SPRITE_SCALE(spriteObj, scale)                                                      \
    spriteObj.rect.w = (int)(spriteObj.width * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale); \
    spriteObj.rect.h = (int)(spriteObj.height * min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT) * scale);

#define SPRITE_ENFORCE_INT_MULT(spriteObj, scale)                                                            \
    spriteObj.rect.w = (int)(spriteObj.width * ((int)ceil(min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT))) * scale); \
    spriteObj.rect.h = (int)(spriteObj.height * ((int)ceil(min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT))) * scale);

#define SET_SPRITE_SCALE_TILE()                  \
    tile.rect.w = tile.width * bgSettings.scale; \
    tile.rect.h = tile.height * bgSettings.scale;

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((gameWidth - obj.rect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION(obj, val) \
    ((gameWidth * val) - (obj.rect.w / 2))

#define OBJ_TO_MID_SIDEBAR(obj) \
    (game_sidebar_small.rect.x + (game_sidebar_small.rect.w - obj.rect.w) / 2)

#endif