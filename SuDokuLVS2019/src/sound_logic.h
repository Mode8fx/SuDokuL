#include "shared.h"

#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

#if defined (VITA)
#define MUSIC_1 "ux0:data/SuDokuL/music/dgtlnnv2.mod"
#define MUSIC_2 "ux0:data/SuDokuL/music/sudoku_padawan.mod"
#define MUSIC_3 "ux0:data/SuDokuL/music/electroq.mod"
#define MUSIC_4 "ux0:data/SuDokuL/music/mainmenu.mod"
#define MUSIC_5 "ux0:data/SuDokuL/music/insomnia.mod"
#define MUSIC_6 "ux0:data/SuDokuL/music/ontario.mod"
#define MUSIC_7 "ux0:data/SuDokuL/music/addicti.mod"
#define SFX_1   "ux0:data/SuDokuL/sfx/coin1.wav"
#else
#define MUSIC_1 "music/dgtlnnv2.mod"
#define MUSIC_2 "music/sudoku_padawan.mod"
#define MUSIC_3 "music/electroq.mod"
#define MUSIC_4 "music/mainmenu.mod"
#define MUSIC_5 "music/insomnia.mod"
#define MUSIC_6 "music/ontario.mod"
#define MUSIC_7 "music/addicti.mod"
#define SFX_1   "sfx/coin1.wav"
#endif

#define MUSIC_CHANNEL 0
#define SFX_CHANNEL 1

#define PLAY_MUSIC_AT_INDEX(index)      \
	soundSettings.musicIndex = index;   \
	Mix_HaltMusic();                    \
	switch (soundSettings.musicIndex) { \
		case 1:                         \
			PLAY_MUSIC(bgm_1);          \
			break;                      \
		case 2:                         \
			PLAY_MUSIC(bgm_2);          \
			break;                      \
		case 3:                         \
			PLAY_MUSIC(bgm_3);          \
			break;                      \
		case 4:                         \
			PLAY_MUSIC(bgm_4);          \
			break;                      \
		case 5:                         \
			PLAY_MUSIC(bgm_5);          \
			break;                      \
		case 6:                         \
			PLAY_MUSIC(bgm_6);          \
			break;                      \
		case 7:                         \
			PLAY_MUSIC(bgm_7);          \
			break;                      \
		default:                        \
			break;                      \
	}

#define STOP_MUSIC(bgm) \
	Mix_HaltMusic();    \
	Mix_FreeMusic(bgm);

#if !defined(PSP)
#define PLAY_MUSIC(bgm) \
	Mix_PlayMusic(bgm, -1);
#else
#define PLAY_MUSIC(bgm) \
	Mix_PlayMusic(bgm, 0);
#endif

#endif