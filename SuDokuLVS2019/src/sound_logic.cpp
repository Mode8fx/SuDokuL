#include "sound_logic.h"

void playMusicAtIndex(Sint8 index) {
	soundSettings.musicIndex = index;
	Mix_HaltMusic();
	switch (soundSettings.musicIndex) {
		case 1:
			playMusic(bgm_1);
			break;
		case 2:
			playMusic(bgm_2);
			break;
		case 3:
			playMusic(bgm_3);
			break;
		case 4:
			playMusic(bgm_4);
			break;
		case 5:
			playMusic(bgm_5);
			break;
		case 6:
			playMusic(bgm_6);
			break;
		case 7:
			playMusic(bgm_7);
			break;
		case 8:
			playMusic(bgm_8);
			break;
		default:
			break;
	}
}

void stopMusic(Mix_Music *bgm) {
	Mix_HaltMusic();
	Mix_FreeMusic(bgm);
}

void playMusic(Mix_Music *bgm) {
#if defined(PSP)
	Mix_PlayMusic(bgm, 0);
#else
	Mix_PlayMusic(bgm, -1);
#endif
}