#include "shared.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

constexpr auto MUSIC_CHANNEL = 0;
constexpr auto SFX_CHANNEL = 1;

extern void playMusicAtIndex(Sint8);
extern void stopMusic(Mix_Music *);
extern void playMusic(Mix_Music *);

#endif