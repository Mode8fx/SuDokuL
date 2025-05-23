#include "shared.h"
#include "window.h"

#ifndef SPRITE_OBJECTS_H
#define SPRITE_OBJECTS_H

#if defined(SDL1)
#define renderSprite(currSprite) SDL_BlitSurface(currSprite.texture, &currSprite.srcRect, windowScreen, &currSprite.rect)
#define SDL_RenderCopy(renderer, currSprite, srcrect, outputRect) SDL_BlitSurface(currSprite, srcrect, windowScreen, outputRect)
#define SDL_DestroyTexture(texture) SDL_FreeSurface(texture)
#define SDL_BlitScaled(src, srcrect, dst, dstrect) SDL_SoftStretch(src, srcrect, dst, dstrect)
#else
#define renderSprite(currSprite) SDL_RenderCopy(renderer, currSprite.texture, &currSprite.srcRect, &currSprite.rect)
#define SDL_SRCCOLORKEY SDL_TRUE
#endif

#define NO_ROUND 0
#define ROUND_DOWN 1
#define ROUND_UP 2
#define ROUND_DOWN_IGNORE_HEIGHT_MULT 3

struct SpriteObject {
#if !defined(SDL1)
    SDL_Texture *texture;
#else
    SDL_Surface *texture;
#endif
    SDL_Rect srcRect;
    SDL_Rect rect;
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
extern SpriteObject logo_1;
extern SpriteObject logo_2;
extern SpriteObject logo_3;
extern SpriteObject menuCursor;
extern SpriteObject game_grid_1;
extern SpriteObject game_grid_2;
extern SpriteObject game_grid_3;
extern SpriteObject game_grid_blit;
extern int bg_max_x;
extern int bg_max_y;
//extern SpriteObject gridCursor;
extern SpriteObject gridCursor_bottom_left;
extern SpriteObject gridCursor_bottom_right;
extern SpriteObject gridCursor_top_left;
extern SpriteObject gridCursor_top_right;
extern SpriteObject game_sidebar_small_1;
extern SpriteObject game_sidebar_small_2;
extern SpriteObject game_sidebar_small_3;
extern SDL_Rect gameSidebarSmall1Rect;
extern SDL_Rect gameSidebarSmall1Rect_1; // sidebar rect number, top/middle/bottom
extern SDL_Rect gameSidebarSmall1Rect_2;
extern SDL_Rect gameSidebarSmall1Rect_3;
extern SDL_Rect gameSidebarSmall2Rect;
extern SDL_Rect gameSidebarSmall2Rect_1;
extern SDL_Rect gameSidebarSmall2Rect_2;
extern SDL_Rect gameSidebarSmall2Rect_3;
extern SDL_Rect gameSidebarSmall3Rect;
extern SDL_Rect gameSidebarSmall3Rect_1;
extern SDL_Rect gameSidebarSmall3Rect_2;
extern SDL_Rect gameSidebarSmall3Rect_3;

extern SpriteObject miniGrid_shared_1;
extern SpriteObject miniGrid_shared_2;
extern SpriteObject miniGrid_shared_3;
extern SpriteObject miniGrid_bottom_left;  // 0
extern SpriteObject miniGrid_bottom_right; // 1
extern SpriteObject miniGrid_top_left;     // 2
extern SpriteObject miniGrid_top_right;    // 3
extern SpriteObject *currMiniGridCursor;
extern Sint8 currMiniGridNum;

extern void prepareSprite(SpriteObject &, const unsigned char *, unsigned int, int, int, double, bool, Sint8);
SDL_Surface* prepareGridSurface(SpriteObject &, const unsigned char *, unsigned int, int, int);
#if defined(SDL1)
extern void blitRGBAontoRGB24(SDL_Surface *src, SDL_Surface *dst, int dx, int dy);
#endif
extern void setSpriteScaleTile();
extern void prepareLogo();
extern void prepareSidebar();
extern inline void renderGrid();
extern inline void renderLogo();
extern void renderMiniGrid();

inline void renderGrid() {
  renderSprite(game_grid_1);
  renderSprite(game_grid_2);
  renderSprite(game_grid_3);
}

inline void renderLogo() {
  renderSprite(logo_1);
  renderSprite(logo_2);
  renderSprite(logo_3);
}

#define OBJ_TO_MID_SCREEN_X(obj) \
    ((gameWidth - obj.rect.w) / 2)

#define OBJ_TO_SCREEN_AT_FRACTION(obj, val) \
    ((gameWidth * val) - (obj.rect.w / 2))

#define OBJ_TO_MID_RECT_X(r, obj) \
    (r.x + (r.w - obj.rect.w) / 2)

#endif