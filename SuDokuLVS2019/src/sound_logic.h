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
	STOP_MUSIC(bgm);                    \
	switch (soundSettings.musicIndex) { \
		case 1:                         \
			PLAY_MUSIC(MUSIC_1);        \
			break;                      \
		case 2:                         \
			PLAY_MUSIC(MUSIC_2);        \
			break;                      \
		case 3:                         \
			PLAY_MUSIC(MUSIC_3);        \
			break;                      \
		case 4:                         \
			PLAY_MUSIC(MUSIC_4);        \
			break;                      \
		case 5:                         \
			PLAY_MUSIC(MUSIC_5);        \
			break;                      \
		case 6:                         \
			PLAY_MUSIC(MUSIC_6);        \
			break;                      \
		case 7:                         \
			PLAY_MUSIC(MUSIC_7);        \
			break;                      \
		default:                        \
			break;                      \
	}

#define STOP_MUSIC(bgm) \
	Mix_HaltMusic();    \
	Mix_FreeMusic(bgm);

#if !defined(PSP)
#define PLAY_MUSIC(musicPath)                                             \
	bgm = Mix_LoadMUS(musicPath);                                         \
	Mix_PlayMusic(bgm, -1);
#else
#define PLAY_MUSIC(musicPath)                                             \
	bgm = Mix_LoadMUS(musicPath);                                         \
	if (bgm == NULL) SDL_Log("Failed to load music: %s", SDL_GetError()); \
	Mix_PlayMusic(bgm, 0);
#endif

#endif