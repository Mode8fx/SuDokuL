#include "include_graphics.h"
#include "sprite_objects.h"
#include "window.h"

void prepareSprite(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale, bool useAlpha) {
#if !defined(SDL1)
#if defined(USE_BMP)
  SDL_Surface *temp_surface = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  if (useAlpha) {
    SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0xFF, 0x00, 0xFF));
  }
  spriteObj.texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
  SDL_FreeSurface(temp_surface);
#else
  spriteObj.texture = IMG_LoadTexture_RW(renderer, SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
#endif
  SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.width, &spriteObj.height);
  setSpriteScale(spriteObj, scale);
#else
  spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  if (useAlpha) {
    SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF));
  }
  spriteObj.width = spriteObj.texture->w;
  spriteObj.height = spriteObj.texture->h;
  setSpriteScale(spriteObj, scale);
  scaledImage = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, spriteObj.texture->format->BitsPerPixel, spriteObj.texture->format->Rmask, spriteObj.texture->format->Gmask, spriteObj.texture->format->Bmask, spriteObj.texture->format->Amask);
  if (useAlpha) {
    SDL_SetColorKey(scaledImage, SDL_SRCCOLORKEY, SDL_MapRGB(scaledImage->format, 0xFF, 0, 0xFF));
  }
  SDL_SoftStretch(spriteObj.texture, NULL, scaledImage, NULL);
  SDL_FreeSurface(spriteObj.texture);
  spriteObj.texture = scaledImage;
#endif
  spriteObj.rect.x = pos_x;
  spriteObj.rect.y = pos_y;
}

void prepareSpriteKeepScale(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale, bool useAlpha) {
#if !defined(SDL1)
  prepareSprite(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale, useAlpha);
#else
  spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  if (useAlpha) {
    SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF));
  }
  spriteObj.width = spriteObj.texture->w;
  spriteObj.height = spriteObj.texture->h;
  setSpriteScale(spriteObj, scale);
  spriteObj.rect.x = pos_x;
  spriteObj.rect.y = pos_y;
#endif
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
#if defined(SDL1)
  prepareSprite(tile1, tile1_img, tile1_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile2, tile2_img, tile2_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile3, tile3_img, tile3_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile_cave, tile_cave_img, tile_cave_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile_desert, tile_desert_img, tile_desert_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile_grasslands, tile_grasslands_img, tile_grasslands_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile_grasslands2, tile_grasslands2_img, tile_grasslands2_img_len, 0, 0, bgSettings.scale, false);
  prepareSprite(tile_snowymountain, tile_snowymountain_img, tile_snowymountain_img_len, 0, 0, bgSettings.scale, false);
  tileSizeScaled = 32 * bgSettings.scale * gameHeightMult;
  bgScroll.final_x = gameWidth + tileSizeScaled;
  bgScroll.final_y = gameHeight + tileSizeScaled;
#else
  tile->rect.w = tile->width * bgSettings.scale;
  tile->rect.h = tile->height * bgSettings.scale;
  bgScroll.final_x = gameWidth + tile->rect.w;
  bgScroll.final_y = gameHeight + tile->rect.h;
#endif
#if defined(THREEDS)
  bg_max_x = game_grid_middle.rect.x + game_grid_middle.rect.w - tile->rect.w;
  bg_max_y = game_grid_bottom.rect.y - tile->rect.h;
#endif
}
