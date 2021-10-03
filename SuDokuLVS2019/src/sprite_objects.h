#include "shared.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

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