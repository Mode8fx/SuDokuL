#include "shared.h"

void loadSettingsFile() {
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "rb");
	if (settingsFile == NULL) {
		initializeSettingsFileWithSettings(true, true, DEFAULT_RI, DEFAULT_ARI, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 90, 50, 15, 22, DEFAULT_BG_SCALE);
	} else {
		SDL_RWread(settingsFile, &controlSettings, sizeof(ControlSettings), 1);
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);
		SDL_RWread(settingsFile, &soundSettings, sizeof(SoundSettings), 1);
		SDL_RWread(settingsFile, &bgSettings, sizeof(BackgroundSettings), 1);
		SDL_RWclose(settingsFile);
	}
}

void initializeSettingsFileWithSettings(Sint8 scab, Sint8 et, Sint8 ri, Sint8 ari, Sint16 gw, Sint16 gh, Sint8 mi, Sint8 bgmv, Sint8 sfxv, Sint8 sm, Sint8 sd, Sint8 s) {
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "w+b");
	if (settingsFile != NULL) {
		controlSettings.swapConfirmAndBack = scab;
		controlSettings.enableTouchscreen = et;
		videoSettings.resolutionIndex = ri;
		videoSettings.aspectRatioIndex = ari;
		videoSettings.widthSetting = gw;
		videoSettings.heightSetting = gh;
		soundSettings.musicIndex = mi;
		soundSettings.bgmVolume = bgmv;
		soundSettings.sfxVolume = sfxv;
		bgSettings.speedMult = sm;
		bgSettings.scrollDir = sd;
		bgSettings.scale = s;
		SDL_RWwrite(settingsFile, &controlSettings.swapConfirmAndBack, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &controlSettings.enableTouchscreen, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.resolutionIndex, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.aspectRatioIndex, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.widthSetting, sizeof(Uint16), 1);
		SDL_RWwrite(settingsFile, &videoSettings.heightSetting, sizeof(Uint16), 1);
		SDL_RWwrite(settingsFile, &soundSettings.musicIndex, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &soundSettings.bgmVolume, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &soundSettings.sfxVolume, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.speedMult, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.scrollDir, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.scale, sizeof(Sint8), 1);
		SDL_RWclose(settingsFile);
	}
}