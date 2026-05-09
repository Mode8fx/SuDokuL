#include "shared.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

#if defined(SDL1)
#define Mix_LoadMUS_RW(rw, freesrc) Mix_LoadMUS_RW(rw)
#endif

constexpr auto MUSIC_CHANNEL = 0;
constexpr auto SFX_CHANNEL = 1;
constexpr Sint8 MUSIC_TRACK_COUNT = 8;
constexpr Sint8 MUSIC_MODE_LOOP = 0;
constexpr Sint8 MUSIC_MODE_IN_ORDER = 1;
constexpr Sint8 MUSIC_MODE_RANDOM = 2;

extern void fillRandomMusicBag(bool);
extern void clearRandomMusicSequence();
extern void normalizeMusicSettings();
extern void setMusicMode(Sint8);
extern void cycleMusicMode(Sint8);
extern void advanceMusicTrack(bool);
extern bool updateMusicPlayback();
extern void playMusicAtIndex(Sint8);
extern void stopMusic(Mix_Music *);
extern void playMusic(Mix_Music *);

#endif