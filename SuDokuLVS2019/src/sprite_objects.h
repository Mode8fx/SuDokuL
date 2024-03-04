#include "shared.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if defined(SDL1)
#define SDL_RenderCopy(renderer, currSprite, srcrect, outputRect) SDL_BlitSurface(currSprite, srcrect, windowScreen, outputRect)
#define SDL_DestroyTexture(texture) SDL_FreeSurface(texture)
#endif

// temporary quick fix
#if defined(WII)
#define tile->rect.w 32
#define tile->rect.h 32
#endif

struct SpriteObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *texture;
#endif
    SDL_Rect rect;
    Sint32 width, height;
};

struct SpriteObjectWithPos {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *texture;
#endif
    SDL_Rect rect;
    Sint32 width, height;
    Sint16 startPos_x, endPos_x;
    Sint16 startPos_y, endPos_y;
};

/* Textures */
extern SpriteObject *tile;
extern SpriteObject tile1;
extern SpriteObject tile2;
extern SpriteObject tile3;
extern SpriteObject tile_cave;
extern SpriteObject tile_desert;
extern SpriteObject tile_grasslands;
extern SpriteObject tile_grasslands2;
extern SpriteObject tile_snowymountain;
extern SpriteObjectWithPos logo;
extern SpriteObjectWithPos menuCursor;
extern SpriteObject game_grid;
//extern SpriteObjectWithPos gridCursor;
extern SpriteObjectWithPos gridCursor_bottom_left;
extern SpriteObjectWithPos gridCursor_bottom_right;
extern SpriteObjectWithPos gridCursor_top_left;
extern SpriteObjectWithPos gridCursor_top_right;
extern SpriteObject game_sidebar_small;
extern SDL_Rect gameSidebarSmall1Rect;
extern SDL_Rect gameSidebarSmall2Rect;
extern SDL_Rect gameSidebarSmall3Rect;

extern SpriteObjectWithPos miniGrid_bottom_left;
extern SpriteObjectWithPos miniGrid_bottom_right;
extern SpriteObjectWithPos miniGrid_top_left;
extern SpriteObjectWithPos miniGrid_top_right;
extern SpriteObjectWithPos *currMiniGrid;

#if !defined(SDL1)
#define PREPARE_SPRITE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale)                  \
    spriteObj.texture = IMG_LoadTexture_RW(renderer, SDL_RWFromMem(spriteImage_data, spriteImage_len), 1); \
    SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.width, &spriteObj.height);                  \
    SET_SPRITE_SCALE(spriteObj, scale);                                                                    \
    spriteObj.rect.x = pos_x;                                                                              \
    spriteObj.rect.y = pos_y;
#else
#define PREPARE_SPRITE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale) \
    spriteObj.texture = IMG_Load_RW(SDL_RWFromMem(spriteImage_data, spriteImage_len), 1); \
    spriteObj.width = spriteObj.texture->w;                                               \
	spriteObj.height = spriteObj.texture->h;                                              \
    SET_SPRITE_SCALE(spriteObj, scale);                                                   \
    spriteObj.rect.x = pos_x;                                                             \
    spriteObj.rect.y = pos_y;
#endif

#define SET_SPRITE_SCALE(spriteObj, scale)                                   \
    spriteObj.rect.w = (Uint16)(spriteObj.width * GAME_HEIGHT_MULT * scale); \
    spriteObj.rect.h = (Uint16)(spriteObj.height * GAME_HEIGHT_MULT * scale);

#define SPRITE_ENFORCE_INT_MULT(spriteObj, scale)                                            \
    spriteObj.rect.w = (Uint16)(spriteObj.width * ((Uint16)ceil(GAME_HEIGHT_MULT)) * scale); \
    spriteObj.rect.h = (Uint16)(spriteObj.height * ((Uint16)ceil(GAME_HEIGHT_MULT)) * scale);

#define SET_SPRITE_SCALE_TILE()                    \
    tile->rect.w = tile->width * bgSettings.scale; \
    tile->rect.h = tile->height * bgSettings.scale;

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((gameWidth - obj.rect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION(obj, val) \
    ((gameWidth * val) - (obj.rect.w / 2))

#define OBJ_TO_MID_RECT_X(r, obj) \
    (r.x + (r.w - obj.rect.w) / 2)

#endif