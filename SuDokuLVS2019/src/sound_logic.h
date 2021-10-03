#ifndef SOUND_LOGIC_H
#define SOUND_LOGIC_H

#define MUSIC_1 "music/dgtlnnv2.mod"
#define MUSIC_2 "music/sudoku_padawan.mod"
#define MUSIC_3 "music/electroq.mod"
#define MUSIC_4 "music/mainmenu.mod"
#define MUSIC_5 "music/insomnia.mod"
#define MUSIC_6 "music/ontario.mod"
#define MUSIC_7 "music/addicti.mod"

#define MUSIC_CHANNEL 0
#define SFX_CHANNEL 1

#define PLAY_MUSIC_AT_INDEX(index)      \
	soundSettings.musicIndex = index;   \
	Mix_HaltMusic();                    \
	Mix_FreeMusic(bgm);                 \
	switch (soundSettings.musicIndex) { \
		case 1:                         \
			bgm = Mix_LoadMUS(MUSIC_1); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 2:                         \
			bgm = Mix_LoadMUS(MUSIC_2); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 3:                         \
			bgm = Mix_LoadMUS(MUSIC_3); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 4:                         \
			bgm = Mix_LoadMUS(MUSIC_4); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 5:                         \
			bgm = Mix_LoadMUS(MUSIC_5); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 6:                         \
			bgm = Mix_LoadMUS(MUSIC_6); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		case 7:                         \
			bgm = Mix_LoadMUS(MUSIC_7); \
			Mix_PlayMusic(bgm, -1);     \
			break;                      \
		default:                        \
			break;                      \
	}

#endif