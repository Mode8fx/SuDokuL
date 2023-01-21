#include "shared.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

#define MUSIC_1 "music/dgtlnnv2.mod"
#define MUSIC_2 "music/sudoku_padawan.mod"
#define MUSIC_3 "music/electroq.mod"
#define MUSIC_4 "music/mainmenu.mod"
#define MUSIC_5 "music/insomnia.mod"
#define MUSIC_6 "music/ontario.mod"
#define MUSIC_7 "music/addicti.mod"
#define SFX_1   "sfx/coin1.wav"

constexpr auto MUSIC_CHANNEL = 0;
constexpr auto SFX_CHANNEL = 1;

extern void playMusicAtIndex(Sint8);
extern void stopMusic(Mix_Music *);
extern void playMusic(Mix_Music *);

#endif