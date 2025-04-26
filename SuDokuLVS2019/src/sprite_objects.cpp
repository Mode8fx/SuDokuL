#include "include_graphics.h"
#include "sprite_objects.h"
#include "window.h"
#include "menu_logic.h"
#include "text_objects.h"
#include "game_logic.h"

SDL_Rect getTrimmedRect(SDL_Surface *surface) {
  SDL_Rect bounds = { 0, 0, 0, 0 };

  if (!surface || surface->format->BytesPerPixel != 3) {
    return bounds; // unsupported format or null
  }

  // Assume color key is magenta: RGB(255, 0, 255)
  Uint8 key_r = 255, key_g = 0, key_b = 255;

  Uint8 *pixels = static_cast<Uint8*>(surface->pixels);
  int pitch = surface->pitch;
  int w = surface->w;
  int h = surface->h;

  int top = h, left = w, bottom = 0, right = 0;
  bool found = false;

  for (int y = 0; y < h; ++y) {
    Uint8 *row = pixels + y * pitch;
    for (int x = 0; x < w; ++x) {
      Uint8 *pixel = row + x * 3;

      Uint8 r = pixel[0];
      Uint8 g = pixel[1];
      Uint8 b = pixel[2];

      if (!(r == key_r && g == key_g && b == key_b)) {
        if (x < left) left = x;
        if (x > right) right = x;
        if (y < top) top = y;
        if (y > bottom) bottom = y;
        found = true;
      }
    }
  }

  if (!found) {
    return { 0, 0, 0, 0 }; // fully transparent
  }

  bounds.x = left;
  bounds.y = top;
  bounds.w = right - left + 1;
  bounds.h = bottom - top + 1;
  return bounds;
}

static Sint16 setSpriteScale_w(int baseWidth, double scale, Sint8 scaleType) {
  switch (scaleType) {
  case ROUND_DOWN:
    return static_cast<Sint16>(baseWidth * floor(gameHeightMult * scale));
    break;
  case ROUND_UP:
    return static_cast<Sint16>(baseWidth * ceil(gameHeightMult * scale));
    break;
  case ROUND_DOWN_IGNORE_HEIGHT_MULT:
    return static_cast<Sint16>(baseWidth * scale);
    break;
  default: // NO_ROUND
    return static_cast<Sint16>(baseWidth * gameHeightMult * scale);
    break;
  }
}

static Sint16 setSpriteScale_h(int baseHeight, double scale, Sint8 scaleType) {
  switch (scaleType) {
  case ROUND_DOWN:
    return static_cast<Sint16>(baseHeight * floor(gameHeightMult * scale));
    break;
  case ROUND_UP:
    return static_cast<Sint16>(baseHeight * ceil(gameHeightMult * scale));
    break;
  case ROUND_DOWN_IGNORE_HEIGHT_MULT:
    return static_cast<Sint16>(baseHeight * scale);
    break;
  default: // NO_ROUND
    return static_cast<Sint16>(baseHeight * gameHeightMult * scale);
    break;
  }
}

/*
 * Prepares a sprite object from a 3-byte (no alpha) PNG and applies scaling+transparency+padding only as needed.
 * Scaling and transparency both add performance overhead when rendering, and some systems can't properly handle textures with a dimension less than 8px.
 */
void prepareSprite(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale, bool useAlpha, Sint8 scaleType) {
  // Destroy the texture/surface if it already exists
  if (spriteObj.texture) {
    SDL_DestroyTexture(spriteObj.texture);
    spriteObj.texture = NULL;
  }
  
  // Load the image data into a surface, and store the dimensions
  SDL_Surface *surface_unformatted = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  int original_w = surface_unformatted->w;
  int original_h = surface_unformatted->h;

  // Store what will later be the scaled dimensions of the image (pre-padding)
  spriteObj.rect.w = setSpriteScale_w(original_w, scale, scaleType);
  spriteObj.rect.h = setSpriteScale_h(original_h, scale, scaleType);

  // Convert it to a new surface with pixel format RGB24
  SDL_Surface *surface_main = SDL_CreateRGBSurface(0, original_w, original_h, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
  SDL_BlitSurface(surface_unformatted, NULL, surface_main, NULL);
  SDL_FreeSurface(surface_unformatted);

  // Convert it to a scaled surface if needed
  bool scaleIsChanged = (spriteObj.rect.w != original_w || spriteObj.rect.h != original_h);
	if (scaleIsChanged) {
    SDL_Surface *surface_scaled = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
    SDL_BlitScaled(surface_main, NULL, surface_scaled, NULL);
    SDL_FreeSurface(surface_main);
    surface_main = surface_scaled;
	}

  // Convert it to a new padded surface if needed
  int padded_w = (surface_main->w < 8) ? 8 : surface_main->w;
  int padded_h = (surface_main->h < 8) ? 8 : surface_main->h;
  bool needsPadding = (surface_main->w != padded_w || surface_main->h != padded_h);
  if (needsPadding) {
    SDL_Surface *surface_padded = SDL_CreateRGBSurface(0, padded_w, padded_h, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
    SDL_FillRect(surface_padded, NULL, SDL_MapRGB(surface_padded->format, 255, 0, 255)); // Fill magenta (important since we're blitting to only part of surface_padded)
    SDL_Rect dstrect = { 0, 0, surface_main->w, surface_main->h };
    SDL_BlitSurface(surface_main, NULL, surface_padded, &dstrect);
    SDL_FreeSurface(surface_main);
    surface_main = surface_padded;
  }
  // Store the actual scaled image dimensions in srcRect
  spriteObj.srcRect = getTrimmedRect(surface_main);
  spriteObj.srcRect.x = 0;
  spriteObj.srcRect.w = spriteObj.rect.w;

  // Apply color key
  if (useAlpha) {
    SDL_SetColorKey(surface_main, SDL_SRCCOLORKEY, SDL_MapRGB(surface_main->format, 0xFF, 0x00, 0xFF));
  }

  // Create texture from final surface
#if defined(SDL1)
  spriteObj.texture = surface_main; // Used as-is for SDL1
#else
  spriteObj.texture = SDL_CreateTextureFromSurface(renderer, surface_main);
  SDL_FreeSurface(surface_main);
#endif
}

SDL_Surface* prepareGridSurface(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y) {
  if (spriteObj.texture) {
    SDL_DestroyTexture(spriteObj.texture);
    spriteObj.texture = NULL;
  }

  SDL_Surface *temp_surface_unformatted = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, temp_surface_unformatted->w, temp_surface_unformatted->h,
    24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
  SDL_BlitSurface(temp_surface_unformatted, NULL, temp_surface, NULL);
  SDL_FreeSurface(temp_surface_unformatted);

  spriteObj.rect.w = setSpriteScale_w(temp_surface->w, 2, NO_ROUND);
  spriteObj.rect.h = setSpriteScale_h(temp_surface->h, 2, NO_ROUND);
  bool scaleIsUnchanged = spriteObj.rect.h == temp_surface->h;

  if (scaleIsUnchanged) {
    spriteObj.srcRect = { 0, 0, temp_surface->w, temp_surface->h };
    spriteObj.rect.x = pos_x;
    spriteObj.rect.y = pos_y;
    return temp_surface;
  }

  SDL_Surface *scaledImage = nullptr;
  // Convert or scale with optional colorkey
  if (scaleIsUnchanged) {
    scaledImage = SDL_ConvertSurface(temp_surface, temp_surface->format, 0);
  } else {
    scaledImage = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, temp_surface->format->BitsPerPixel, temp_surface->format->Rmask, temp_surface->format->Gmask, temp_surface->format->Bmask, temp_surface->format->Amask);
  }

  SDL_BlitScaled(temp_surface, NULL, scaledImage, NULL);
  SDL_FreeSurface(temp_surface);

  spriteObj.srcRect = { 0, 0, scaledImage->w, scaledImage->h };
  spriteObj.rect.x = pos_x;
  spriteObj.rect.y = pos_y;
  return scaledImage;
}

#if defined(SDL1)
void blitRGBAontoRGB24(SDL_Surface *src, SDL_Surface *dst, int dx, int dy) {
  if (!src || !dst) return;
  if (src->format->BytesPerPixel != 4 || dst->format->BytesPerPixel != 3) return;

  if (SDL_MUSTLOCK(src)) SDL_LockSurface(src);
  if (SDL_MUSTLOCK(dst)) SDL_LockSurface(dst);

  for (int y = 0; y < src->h; ++y) {
    Uint8* srcRow = (Uint8*)src->pixels + y * src->pitch;
    Uint8* dstRow = (Uint8*)dst->pixels + (y + dy) * dst->pitch + dx * 3;

    for (int x = 0; x < src->w; ++x) {
      Uint8 r = srcRow[x * 4 + 0];
      Uint8 g = srcRow[x * 4 + 1];
      Uint8 b = srcRow[x * 4 + 2];
      Uint8 a = srcRow[x * 4 + 3];

      if (a == 0) continue; // fully transparent
      float alpha = a / 255.0f;

      // Blend over destination
      dstRow[x * 3 + 0] = (Uint8)(r * alpha + dstRow[x * 3 + 0] * (1.0f - alpha));
      dstRow[x * 3 + 1] = (Uint8)(g * alpha + dstRow[x * 3 + 1] * (1.0f - alpha));
      dstRow[x * 3 + 2] = (Uint8)(b * alpha + dstRow[x * 3 + 2] * (1.0f - alpha));
    }
  }

  if (SDL_MUSTLOCK(src)) SDL_UnlockSurface(src);
  if (SDL_MUSTLOCK(dst)) SDL_UnlockSurface(dst);
}
#endif

void setSpriteScaleTile() {
  Sint8 tileSizeResMult = max(static_cast<Sint8>(std::floor(gameHeight / 480.0)), (Sint8)1);
  prepareSprite(tile1, tile1_png, tile1_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile2, tile2_png, tile2_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile3, tile3_png, tile3_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile_cave, tile_cave_png, tile_cave_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile_desert, tile_desert_png, tile_desert_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile_grasslands, tile_grasslands_png, tile_grasslands_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile_grasslands2, tile_grasslands2_png, tile_grasslands2_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  prepareSprite(tile_snowymountain, tile_snowymountain_png, tile_snowymountain_png_len, 0, 0, bgSettings.scale * tileSizeResMult, false, ROUND_DOWN_IGNORE_HEIGHT_MULT);
  bgScroll.final_x = gameWidth + tile->rect.w;
  bgScroll.final_y = gameHeight + tile->rect.h;
  bg_max_x = game_grid_2.rect.x + game_grid_2.rect.w - tile->rect.w;
  bg_max_y = game_grid_3.rect.y - tile->rect.h;
  setBGScrollSpeed();
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
  } else {
    gameSidebarSmall1Rect_1.x = (Sint16)((gameWidth / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall1Rect_1.y = -(Sint16)(SIDEBAR_SMALL_SIZE_Y / 4);
    gameSidebarSmall2Rect_1.x = (Sint16)((gameWidth / 2) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall2Rect_1.y = gameSidebarSmall1Rect_1.y;
    gameSidebarSmall3Rect_1.x = (Sint16)((gameWidth * 4 / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
    gameSidebarSmall3Rect_1.y = gameSidebarSmall1Rect_1.y;
  }
  gameSidebarSmall1Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall1Rect_1.h = game_sidebar_small_1.srcRect.h;
  gameSidebarSmall1Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall1Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall1Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall1Rect_3.h = game_sidebar_small_3.srcRect.h;
  gameSidebarSmall1Rect_2.x = gameSidebarSmall1Rect_1.x;
  gameSidebarSmall1Rect_2.y = gameSidebarSmall1Rect_1.y + gameSidebarSmall1Rect_1.h;
  gameSidebarSmall1Rect_3.x = gameSidebarSmall1Rect_1.x;
  gameSidebarSmall1Rect_3.y = gameSidebarSmall1Rect_2.y + gameSidebarSmall1Rect_2.h;
  gameSidebarSmall1Rect = gameSidebarSmall1Rect_1;
  gameSidebarSmall1Rect.w = gameSidebarSmall1Rect_1.w;
  gameSidebarSmall1Rect.h = gameSidebarSmall1Rect_1.h + gameSidebarSmall1Rect_2.h + gameSidebarSmall1Rect_3.h;
  gameSidebarSmall2Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall2Rect_1.h = game_sidebar_small_1.srcRect.h;
  gameSidebarSmall2Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall2Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall2Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall2Rect_3.h = game_sidebar_small_3.srcRect.h;
  gameSidebarSmall2Rect_2.x = gameSidebarSmall2Rect_1.x;
  gameSidebarSmall2Rect_2.y = gameSidebarSmall2Rect_1.y + gameSidebarSmall2Rect_1.h;
  gameSidebarSmall2Rect_3.x = gameSidebarSmall2Rect_1.x;
  gameSidebarSmall2Rect_3.y = gameSidebarSmall2Rect_2.y + gameSidebarSmall2Rect_2.h;
  gameSidebarSmall2Rect = gameSidebarSmall2Rect_1;
  gameSidebarSmall2Rect.w = gameSidebarSmall1Rect.w;
  gameSidebarSmall2Rect.h = gameSidebarSmall1Rect.h;
  gameSidebarSmall3Rect_1.w = game_sidebar_small_1.rect.w;
  gameSidebarSmall3Rect_1.h = game_sidebar_small_1.srcRect.h;
  gameSidebarSmall3Rect_2.w = game_sidebar_small_2.rect.w;
  gameSidebarSmall3Rect_2.h = game_sidebar_small_2.rect.h;
  gameSidebarSmall3Rect_3.w = game_sidebar_small_3.rect.w;
  gameSidebarSmall3Rect_3.h = game_sidebar_small_3.srcRect.h;
  gameSidebarSmall3Rect_2.x = gameSidebarSmall3Rect_1.x;
  gameSidebarSmall3Rect_2.y = gameSidebarSmall3Rect_1.y + gameSidebarSmall3Rect_1.h;
  gameSidebarSmall3Rect_3.x = gameSidebarSmall3Rect_1.x;
  gameSidebarSmall3Rect_3.y = gameSidebarSmall3Rect_2.y + gameSidebarSmall3Rect_2.h;
  gameSidebarSmall3Rect = gameSidebarSmall3Rect_1;
  gameSidebarSmall3Rect.w = gameSidebarSmall1Rect.w;
  gameSidebarSmall3Rect.h = gameSidebarSmall1Rect.h;
}

void renderMiniGrid() {
  if (miniGridState == 1) {
    renderSprite(miniGrid_shared_1);
    renderSprite(miniGrid_shared_2);
    renderSprite(miniGrid_shared_3);
    SDL_RenderCopy(renderer, currMiniGridCursor->texture, &currMiniGridCursor->srcRect, &currMiniGridCursor->rect);
    for (Sint8 num = 1; num < 10; num++) {
      setAndRenderNumGridSubNormal(gridNums_blue, int(num));
    }
  } else if (miniGridState == 2) {
    renderSprite(miniGrid_shared_1);
    renderSprite(miniGrid_shared_2);
    renderSprite(miniGrid_shared_3);
    SDL_RenderCopy(renderer, currMiniGridCursor->texture, &currMiniGridCursor->srcRect, &currMiniGridCursor->rect);
    for (Sint8 num = 1; num < 10; num++) {
      setAndRenderNumGridSubMini(gridNums_blue_mini, int(num));
    }
  }
}
