#include "shared.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if defined(SDL1)
#define SDL_RenderCopy(renderer, currSprite, srcrect, outputRect) SDL_BlitSurface(currSprite, srcrect, windowScreen, outputRect)
#define SDL_DestroyTexture(texture) SDL_FreeSurface(texture)
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
#if defined(SDL1)
extern SDL_Surface *scaledImage;
extern Sint16 tileSizeScaled;
#endif

extern SpriteObjectWithPos miniGrid_bottom_left;
extern SpriteObjectWithPos miniGrid_bottom_right;
extern SpriteObjectWithPos miniGrid_top_left;
extern SpriteObjectWithPos miniGrid_top_right;
extern SpriteObjectWithPos *currMiniGrid;

#if !defined(SDL1)
#define PREPARE_SPRITE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale)                  \
    spriteObj.texture = IMG_LoadTexture_RW(renderer, SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1); \
    SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.width, &spriteObj.height);                  \
    SET_SPRITE_SCALE(spriteObj, scale);                                                                    \
    spriteObj.rect.x = pos_x;                                                                              \
    spriteObj.rect.y = pos_y;

#define PREPARE_SPRITE_KEEP_SCALE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale) \
		PREPARE_SPRITE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale)
#else
#define PREPARE_SPRITE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale) \
    spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1); \
    SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF)); \
    spriteObj.width = spriteObj.texture->w;                                               \
	  spriteObj.height = spriteObj.texture->h;                                              \
    SET_SPRITE_SCALE(spriteObj, scale);                                                   \
    scaledImage = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, spriteObj.texture->format->BitsPerPixel, spriteObj.texture->format->Rmask, spriteObj.texture->format->Gmask, spriteObj.texture->format->Bmask, spriteObj.texture->format->Amask); \
    SDL_SetColorKey(scaledImage, SDL_SRCCOLORKEY, SDL_MapRGB(scaledImage->format, 0xFF, 0, 0xFF)); \
    SDL_SoftStretch(spriteObj.texture, NULL, scaledImage, NULL);                          \
    SDL_FreeSurface(spriteObj.texture);                                                   \
		spriteObj.texture = scaledImage;                                                      \
    spriteObj.rect.x = pos_x;                                                             \
    spriteObj.rect.y = pos_y;

#define PREPARE_SPRITE_KEEP_SCALE(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale) \
    spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1); \
    SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF)); \
    spriteObj.width = spriteObj.texture->w;                                               \
	  spriteObj.height = spriteObj.texture->h;                                              \
    SET_SPRITE_SCALE(spriteObj, scale);                                                   \
    spriteObj.rect.x = pos_x;                                                             \
    spriteObj.rect.y = pos_y;
#endif

#define SET_SPRITE_SCALE(spriteObj, scale)                                 \
    spriteObj.rect.w = (Uint16)(spriteObj.width * gameHeightMult * scale); \
    spriteObj.rect.h = (Uint16)(spriteObj.height * gameHeightMult * scale);

#define SPRITE_ENFORCE_INT_MULT(spriteObj, scale)                                          \
    spriteObj.rect.w = (Uint16)(spriteObj.width * ((Uint16)ceil(gameHeightMult)) * scale); \
    spriteObj.rect.h = (Uint16)(spriteObj.height * ((Uint16)ceil(gameHeightMult)) * scale);

#if defined(SDL1)
#define SET_SPRITE_SCALE_TILE()                    \
    PREPARE_SPRITE(tile1, tile1_img, tile1_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile2, tile2_img, tile2_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile3, tile3_img, tile3_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile_cave, tile_cave_img, tile_cave_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile_desert, tile_desert_img, tile_desert_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile_grasslands, tile_grasslands_img, tile_grasslands_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile_grasslands2, tile_grasslands2_img, tile_grasslands2_img_len, 0, 0, bgSettings.scale); \
    PREPARE_SPRITE(tile_snowymountain, tile_snowymountain_img, tile_snowymountain_img_len, 0, 0, bgSettings.scale); \
    tileSizeScaled = 32 * bgSettings.scale * gameHeightMult;
#else
#define SET_SPRITE_SCALE_TILE()                    \
    tile->rect.w = tile->width * bgSettings.scale; \
    tile->rect.h = tile->height * bgSettings.scale;
#endif

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((gameWidth - obj.rect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION(obj, val) \
    ((gameWidth * val) - (obj.rect.w / 2))

#define OBJ_TO_MID_RECT_X(r, obj) \
    (r.x + (r.w - obj.rect.w) / 2)

#endif