#include "include_graphics.h"
#include "sprite_objects.h"
#include "window.h"

#if !defined(SDL1)
#define SDL_SRCCOLORKEY SDL_TRUE
#endif

/*
 * Prepares a sprite object from a 3-byte (no alpha) PNG and applies scaling+transparency only as needed. Scaling and transparency both add performance overhead when rendering.
 * Sprite loading roughly works as follows:
 * 1. Load the image data into a surface.
 * 2. Convert the surface to a new surface of pixel format (RGB24), which does not contain alpha transparency.
 * 3. Set the scale of the sprite object relative to the default resolution (480p).
 * 4. If the scale is unchanged and no alpha is used (i.e. the object is the exact same size as the sprite it comes from), use the surface as-is.
 * 5. Scale the sprite and apply color key (color #FF00FF is transparent) as needed.
 * 6. Set the position of the sprite object.
 */
void prepareSprite(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale, bool useAlpha, Sint8 intScaleType) {
  if (spriteObj.texture) {
#if defined(SDL1)
    SDL_FreeSurface(spriteObj.texture);
#else
    SDL_DestroyTexture(spriteObj.texture);
#endif
    spriteObj.texture = NULL;  // optional: clear the pointer to avoid dangling references
  }

  SDL_Surface *temp_surface_unformatted = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  if (!temp_surface_unformatted) {
    SDL_Log("Failed to load image: %s", IMG_GetError());
    return;
  }
  SDL_Surface *temp_surface = SDL_ConvertSurfaceFormat(temp_surface_unformatted, SDL_PIXELFORMAT_RGB24, 0);
	SDL_FreeSurface(temp_surface_unformatted);

  spriteObj.width = temp_surface->w;
  spriteObj.height = temp_surface->h;
  if (intScaleType) {
    setSpriteScale_EnforceIntMult(spriteObj, scale, (bool)(intScaleType - 1));
  } else {
    setSpriteScale(spriteObj, scale);
  }
  bool scaleIsUnchanged = spriteObj.rect.h == spriteObj.height;

  if (scaleIsUnchanged && !useAlpha) {
#if defined(SDL1)
    spriteObj.texture = SDL_DisplayFormat(temp_surface);
#else
    spriteObj.texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
#endif
    SDL_FreeSurface(temp_surface);
    spriteObj.rect.x = pos_x;
    spriteObj.rect.y = pos_y;
    return;
  }

  SDL_Surface *scaledImage = nullptr;
  // Convert or scale with optional colorkey
  if (scaleIsUnchanged) {
    scaledImage = SDL_ConvertSurface(temp_surface, temp_surface->format, 0);
  } else {
    scaledImage = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, temp_surface->format->BitsPerPixel, temp_surface->format->Rmask, temp_surface->format->Gmask, temp_surface->format->Bmask, temp_surface->format->Amask);
  }
  if (!scaledImage) {
    SDL_Log("Failed to create scaled surface: %s", SDL_GetError());
    SDL_FreeSurface(temp_surface);
    return;
  }

  if (useAlpha) {
    SDL_SetColorKey(scaledImage, SDL_SRCCOLORKEY, SDL_MapRGB(scaledImage->format, 0xFF, 0x00, 0xFF));
  }

#if defined(SDL1)
  SDL_SoftStretch(temp_surface, NULL, scaledImage, NULL);
  spriteObj.texture = scaledImage; // Used as-is for SDL1
#else
  SDL_BlitScaled(temp_surface, NULL, scaledImage, NULL);
  spriteObj.texture = SDL_CreateTextureFromSurface(renderer, scaledImage);
  SDL_FreeSurface(scaledImage);
#endif

  SDL_FreeSurface(temp_surface);

  spriteObj.rect.x = pos_x;
  spriteObj.rect.y = pos_y;
}

void setSpriteScale(SpriteObject &spriteObj, double scale) {
  spriteObj.rect.w = static_cast<Uint16>(spriteObj.width * gameHeightMult * scale);
  spriteObj.rect.h = static_cast<Uint16>(spriteObj.height * gameHeightMult * scale);
}

void setSpriteScale_EnforceIntMult(SpriteObject &spriteObj, double scale, bool roundUp) {
	Uint16 roundedMult = roundUp ? static_cast<Uint16>(ceil(gameHeightMult)) : static_cast<Uint16>(floor(gameHeightMult));
  spriteObj.rect.w = static_cast<Uint16>(spriteObj.width * roundedMult * scale);
  spriteObj.rect.h = static_cast<Uint16>(spriteObj.height * roundedMult * scale);
}

void setSpriteScaleTile() {
  Sint8 tileSizeResMult = gameHeight < 960 ? 1 : 2;
  prepareSprite(tile1, tile1_png, tile1_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile2, tile2_png, tile2_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile3, tile3_png, tile3_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile_cave, tile_cave_png, tile_cave_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile_desert, tile_desert_png, tile_desert_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile_grasslands, tile_grasslands_png, tile_grasslands_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile_grasslands2, tile_grasslands2_png, tile_grasslands2_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  prepareSprite(tile_snowymountain, tile_snowymountain_png, tile_snowymountain_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false, ROUND_DOWN);
  bgScroll.final_x = gameWidth + tile->rect.w;
  bgScroll.final_y = gameHeight + tile->rect.h;
#if defined(THREEDS)
  bg_max_x = game_grid_2.rect.x + game_grid_2.rect.w - tile->rect.w;
  bg_max_y = game_grid_3.rect.y - tile->rect.h;
#endif
}

void prepareLogo() {
  if (gameHeight < 272) {
    double logoScale = 480.0 / 240;
    prepareSprite(logo_1, logo_240_1_png, logo_240_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_240_2_png, logo_240_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_240_3_png, logo_240_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 480) {
    double logoScale = 480.0 / 272;
    prepareSprite(logo_1, logo_272_1_png, logo_272_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_272_2_png, logo_272_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_272_3_png, logo_272_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 544) {
    double logoScale = 480.0 / 480;
    prepareSprite(logo_1, logo_480_1_png, logo_480_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_480_2_png, logo_480_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_480_3_png, logo_480_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 720) {
    double logoScale = 480.0 / 544;
    prepareSprite(logo_1, logo_544_1_png, logo_544_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_544_2_png, logo_544_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_544_3_png, logo_544_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 1080) {
    double logoScale = 480.0 / 720;
    prepareSprite(logo_1, logo_720_1_png, logo_720_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_720_2_png, logo_720_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_720_3_png, logo_720_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 1440) {
    double logoScale = 480.0 / 1080;
    prepareSprite(logo_1, logo_1080_1_png, logo_1080_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_1080_2_png, logo_1080_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_1080_3_png, logo_1080_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else if (gameHeight < 2160) {
    double logoScale = 480.0 / 1440;
    prepareSprite(logo_1, logo_1440_1_png, logo_1440_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_1440_2_png, logo_1440_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_1440_3_png, logo_1440_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  } else {
    double logoScale = 480.0 / 2160;
    prepareSprite(logo_1, logo_2160_1_png, logo_2160_1_png_len, 0, 0, logoScale, true, NO_ROUND);
    prepareSprite(logo_2, logo_2160_2_png, logo_2160_2_png_len, 0, 0, logoScale, false, NO_ROUND);
    prepareSprite(logo_3, logo_2160_3_png, logo_2160_3_png_len, 0, 0, logoScale, true, NO_ROUND);
  }
  Uint16 logoHeight = (logo_1.rect.h + logo_2.rect.h + logo_3.rect.h);
  logo_1.rect.x = (gameWidth / 2) - (logo_1.rect.w / 2);
  logo_1.rect.y = gameHeight * 3 / 8 - (logoHeight / 2);
  logo_1.startPos_y = logo_1.rect.y;
  logo_1.endPos_y = (gameHeight * 3 / 16 - (logoHeight / 2));
  logo_1.startPos_x = logo_1.endPos_y; /* functionally, this is a second startPos_y, not x */
  logo_1.endPos_x = logo_1.endPos_y - (gameHeight * 3 / 4); /* functionally, this is a second endPos_y, not x */
  logo_2.rect.x = logo_1.rect.x;
  logo_2.rect.y = logo_1.rect.y + logo_1.rect.h;
  logo_2.startPos_y = logo_2.rect.y;
  logo_2.endPos_y = logo_1.endPos_y + logo_1.rect.h;
  logo_2.startPos_x = logo_2.endPos_y;
  logo_2.endPos_x = logo_2.endPos_y - (gameHeight * 3 / 4);
  logo_3.rect.x = logo_1.rect.x;
  logo_3.rect.y = logo_1.rect.y + logo_1.rect.h + logo_2.rect.h;
  logo_3.startPos_y = logo_3.rect.y;
  logo_3.endPos_y = logo_2.endPos_y + logo_2.rect.h;
  logo_3.startPos_x = logo_3.endPos_y;
  logo_3.endPos_x = logo_3.endPos_y - (gameHeight * 3 / 4);
}

void prepareSidebar() {
  prepareSprite(game_sidebar_small_1, sidebar_small_1_png, sidebar_small_1_png_len, 0, 0, 2, true, NO_ROUND);
  prepareSprite(game_sidebar_small_2, sidebar_small_2_png, sidebar_small_2_png_len, 0, 0, 2, false, NO_ROUND);
  prepareSprite(game_sidebar_small_3, sidebar_small_3_png, sidebar_small_3_png_len, 0, 0, 2, true, NO_ROUND);
  if (!compactDisplay) {
    gameSidebarSmall1Rect_1.x = (Sint16)(gridPosX - SIDEBAR_SMALL_SIZE_X - (gridSize / 12));
    gameSidebarSmall1Rect_1.y = (Sint16)(gridPosY + (gridSize / 16));
    gameSidebarSmall2Rect_1.x = gameSidebarSmall1Rect_1.x;
    gameSidebarSmall2Rect_1.y = (Sint16)(gridPosY + SIDEBAR_SMALL_SIZE_Y + (gridSize / 8));
    gameSidebarSmall3Rect_1.x = gameSidebarSmall1Rect_1.x;
    gameSidebarSmall3Rect_1.y = (Sint16)(gridPosY + (2 * SIDEBAR_SMALL_SIZE_Y) + (gridSize * 3 / 16));
  }
  else {
    gameSidebarSmall1Rect_1.x = (Sint16)((gameWidth / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall1Rect_1.y = -(Sint16)(SIDEBAR_SMALL_SIZE_Y / 4);
    gameSidebarSmall2Rect_1.x = (Sint16)((gameWidth / 2) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall2Rect_1.y = gameSidebarSmall1Rect_1.y;
    gameSidebarSmall3Rect_1.x = (Sint16)((gameWidth * 4 / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall3Rect_1.y = gameSidebarSmall1Rect_1.y;
  }
  gameSidebarSmall1Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall1Rect_1.h = game_sidebar_small_1.rect.h;
  gameSidebarSmall1Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall1Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall1Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall1Rect_3.h = game_sidebar_small_3.rect.h;
  gameSidebarSmall1Rect_2.x = gameSidebarSmall1Rect_1.x;
  gameSidebarSmall1Rect_2.y = gameSidebarSmall1Rect_1.y + gameSidebarSmall1Rect_1.h;
  gameSidebarSmall1Rect_3.x = gameSidebarSmall1Rect_1.x;
  gameSidebarSmall1Rect_3.y = gameSidebarSmall1Rect_2.y + gameSidebarSmall1Rect_2.h;
  gameSidebarSmall1Rect = gameSidebarSmall1Rect_1;
  gameSidebarSmall1Rect.w = gameSidebarSmall1Rect_1.w;
  gameSidebarSmall1Rect.h = gameSidebarSmall1Rect_1.h + gameSidebarSmall1Rect_2.h + gameSidebarSmall1Rect_3.h;
  gameSidebarSmall2Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall2Rect_1.h = game_sidebar_small_1.rect.h;
  gameSidebarSmall2Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall2Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall2Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall2Rect_3.h = game_sidebar_small_3.rect.h;
  gameSidebarSmall2Rect_2.x = gameSidebarSmall2Rect_1.x;
  gameSidebarSmall2Rect_2.y = gameSidebarSmall2Rect_1.y + gameSidebarSmall2Rect_1.h;
  gameSidebarSmall2Rect_3.x = gameSidebarSmall2Rect_1.x;
  gameSidebarSmall2Rect_3.y = gameSidebarSmall2Rect_2.y + gameSidebarSmall2Rect_2.h;
  gameSidebarSmall2Rect = gameSidebarSmall2Rect_1;
  gameSidebarSmall2Rect.w = gameSidebarSmall1Rect.w;
  gameSidebarSmall2Rect.h = gameSidebarSmall1Rect.h;
  gameSidebarSmall3Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall3Rect_1.h = game_sidebar_small_1.rect.h;
  gameSidebarSmall3Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall3Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall3Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall3Rect_3.h = game_sidebar_small_3.rect.h;
  gameSidebarSmall3Rect_2.x = gameSidebarSmall3Rect_1.x;
  gameSidebarSmall3Rect_2.y = gameSidebarSmall3Rect_1.y + gameSidebarSmall3Rect_1.h;
  gameSidebarSmall3Rect_3.x = gameSidebarSmall3Rect_1.x;
  gameSidebarSmall3Rect_3.y = gameSidebarSmall3Rect_2.y + gameSidebarSmall3Rect_2.h;
  gameSidebarSmall3Rect = gameSidebarSmall3Rect_1;
  gameSidebarSmall3Rect.w = gameSidebarSmall1Rect.w;
  gameSidebarSmall3Rect.h = gameSidebarSmall1Rect.h;
}
