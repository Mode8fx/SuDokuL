#include "shared.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

#if defined(SDL1)
#define Mix_LoadMUS_RW(rw, freesrc) Mix_LoadMUS_RW(rw)
#endif

constexpr auto MUSIC_CHANNEL = 0;
constexpr auto SFX_CHANNEL = 1;

extern void playMusicAtIndex(Sint8);
extern void stopMusic(Mix_Music *);
extern void playMusic(Mix_Music *);

#endif