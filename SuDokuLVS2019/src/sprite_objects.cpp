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
void prepareSprite(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale, bool useAlpha) {
  SDL_Surface *temp_surface_unformatted = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  if (!temp_surface_unformatted) {
    SDL_Log("Failed to load image: %s", IMG_GetError());
    return;
  }
  SDL_Surface *temp_surface = SDL_ConvertSurfaceFormat(temp_surface_unformatted, SDL_PIXELFORMAT_RGB24, 0);
	SDL_FreeSurface(temp_surface_unformatted);

  spriteObj.width = temp_surface->w;
  spriteObj.height = temp_surface->h;
  setSpriteScale(spriteObj, scale);
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

void spriteEnforceIntMult(SpriteObject &spriteObj, double scale) {
  spriteObj.rect.w = static_cast<Uint16>(spriteObj.width * static_cast<Uint16>(ceil(gameHeightMult)) * scale);
  spriteObj.rect.h = static_cast<Uint16>(spriteObj.height * static_cast<Uint16>(ceil(gameHeightMult)) * scale);
}

void setSpriteScaleTile() {
  Sint8 tileSizeResMult = max(static_cast<Sint8>(std::floor(gameHeight / 480.0)), (Sint8)1);
#if defined(SDL1)
  prepareSprite(tile1, tile1_png, tile1_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile2, tile2_png, tile2_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile3, tile3_png, tile3_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile_cave, tile_cave_png, tile_cave_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile_desert, tile_desert_png, tile_desert_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile_grasslands, tile_grasslands_png, tile_grasslands_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile_grasslands2, tile_grasslands2_png, tile_grasslands2_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  prepareSprite(tile_snowymountain, tile_snowymountain_png, tile_snowymountain_png_len, 0, 0, bgSettings.scale * 2 * tileSizeResMult, false);
  tileSizeScaled = 32 * bgSettings.scale * gameHeightMult * tileSizeResMult;
  bgScroll.final_x = gameWidth + tileSizeScaled;
  bgScroll.final_y = gameHeight + tileSizeScaled;
#else
  tile->rect.w = tile->width * bgSettings.scale * tileSizeResMult;
  tile->rect.h = tile->height * bgSettings.scale * tileSizeResMult;
  bgScroll.final_x = gameWidth + tile->rect.w;
  bgScroll.final_y = gameHeight + tile->rect.h;
#endif
#if defined(THREEDS)
  bg_max_x = game_grid_2.rect.x + game_grid_2.rect.w - tile->rect.w;
  bg_max_y = game_grid_3.rect.y - tile->rect.h;
#endif
}
