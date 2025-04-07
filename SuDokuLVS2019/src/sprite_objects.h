#include "shared.h"
#include "window.h"

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
    int width, height;
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
extern SpriteObject logo;
extern SpriteObject menuCursor;
#if defined(THREEDS)
extern SpriteObject game_grid_top;
extern SpriteObject game_grid_middle;
extern SpriteObject game_grid_bottom;
#else
extern SpriteObject game_grid;
#endif
//extern SpriteObject gridCursor;
extern SpriteObject gridCursor_bottom_left;
extern SpriteObject gridCursor_bottom_right;
extern SpriteObject gridCursor_top_left;
extern SpriteObject gridCursor_top_right;
extern SpriteObject game_sidebar_small;
extern SDL_Rect gameSidebarSmall1Rect;
extern SDL_Rect gameSidebarSmall2Rect;
extern SDL_Rect gameSidebarSmall3Rect;
#if defined(SDL1)
extern SDL_Surface *scaledImage;
extern Sint16 tileSizeScaled;
#endif

extern SpriteObject miniGrid_bottom_left;
extern SpriteObject miniGrid_bottom_right;
extern SpriteObject miniGrid_top_left;
extern SpriteObject miniGrid_top_right;
extern SpriteObject *currMiniGrid;

extern void prepareSprite(SpriteObject &, const unsigned char *, unsigned int, int, int, double, bool);
extern void prepareSpriteKeepScale(SpriteObject &, const unsigned char *, unsigned int, int, int, double, bool);
extern void setSpriteScale(SpriteObject &, double);
extern void spriteEnforceIntMult(SpriteObject &, double);
extern void setSpriteScaleTile();
extern inline void renderGrid();

inline void renderGrid() {
#if defined(THREEDS)
  SDL_RenderCopy(renderer, game_grid_top.texture, NULL, &game_grid_top.rect);
  SDL_RenderCopy(renderer, game_grid_middle.texture, NULL, &game_grid_middle.rect);
  SDL_RenderCopy(renderer, game_grid_bottom.texture, NULL, &game_grid_bottom.rect);
#else
  SDL_RenderCopy(renderer, game_grid.texture, NULL, &game_grid.rect);
#endif
}

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((gameWidth - obj.rect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION(obj, val) \
    ((gameWidth * val) - (obj.rect.w / 2))

#define OBJ_TO_MID_RECT_X(r, obj) \
    (r.x + (r.w - obj.rect.w) / 2)

#endif