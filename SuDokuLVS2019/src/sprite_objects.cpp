#include "sprite_objects.h"
#include "window.h"

void prepareSprite(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale) {
#if !defined(SDL1)
  spriteObj.texture = IMG_LoadTexture_RW(renderer, SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  SDL_QueryTexture(spriteObj.texture, NULL, NULL, &spriteObj.width, &spriteObj.height);
  setSpriteScale(spriteObj, scale);
#else
  spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF));
  spriteObj.width = spriteObj.texture->w;
  spriteObj.height = spriteObj.texture->h;
  setSpriteScale(spriteObj, scale);
  scaledImage = SDL_CreateRGBSurface(0, spriteObj.rect.w, spriteObj.rect.h, spriteObj.texture->format->BitsPerPixel, spriteObj.texture->format->Rmask, spriteObj.texture->format->Gmask, spriteObj.texture->format->Bmask, spriteObj.texture->format->Amask);
  SDL_SetColorKey(scaledImage, SDL_SRCCOLORKEY, SDL_MapRGB(scaledImage->format, 0xFF, 0, 0xFF));
  SDL_SoftStretch(spriteObj.texture, NULL, scaledImage, NULL);
  SDL_FreeSurface(spriteObj.texture);
  spriteObj.texture = scaledImage;
#endif
  spriteObj.rect.x = pos_x;
  spriteObj.rect.y = pos_y;
}

void prepareSpriteKeepScale(SpriteObject &spriteObj, const unsigned char *spriteImage_data, unsigned int spriteImage_len, int pos_x, int pos_y, double scale) {
#if !defined(SDL1)
  prepareSprite(spriteObj, spriteImage_data, spriteImage_len, pos_x, pos_y, scale);
#else
  spriteObj.texture = IMG_Load_RW(SDL_RWFromConstMem(spriteImage_data, spriteImage_len), 1);
  SDL_SetColorKey(spriteObj.texture, SDL_SRCCOLORKEY, SDL_MapRGB(spriteObj.texture->format, 0xFF, 0, 0xFF));
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
  prepareSprite(tile1, tile1_img, tile1_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile2, tile2_img, tile2_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile3, tile3_img, tile3_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile_cave, tile_cave_img, tile_cave_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile_desert, tile_desert_img, tile_desert_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile_grasslands, tile_grasslands_img, tile_grasslands_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile_grasslands2, tile_grasslands2_img, tile_grasslands2_img_len, 0, 0, bgSettings.scale);
  prepareSprite(tile_snowymountain, tile_snowymountain_img, tile_snowymountain_img_len, 0, 0, bgSettings.scale);
  tileSizeScaled = 32 * bgSettings.scale * gameHeightMult;
#else
  tile->rect.w = tile->width * bgSettings.scale;
  tile->rect.h = tile->height * bgSettings.scale;
#endif
}

