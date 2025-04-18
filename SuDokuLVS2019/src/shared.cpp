#include "shared.h"
#include "general.h"
#include "sprite_objects.h"
#include "config.h"
#include "window.h"
#include "sudokuGen.h"
#include "puzzleBank.h"
#include "menu_logic.h"

#if defined(SDL1) && !(defined(LINUX) || defined(CONSOLE))
FILE _iob[] = { *stdin, *stdout, *stderr };

FILE * __cdecl __iob_func(void) {
	return _iob;
}
#endif

Sint64 seekPos;

void loadSettingsFile() {
#if defined(LINUX)
	mkdir((string(getenv("HOME")) + "/.sudokul").c_str(), 0777);
#elif defined(VITA)
	mkdir("ux0:data/SuDokuL", 0777);
#endif
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "rb");
	if (settingsFile == NULL) {
		initializeSettingsFileWithSettings(true, true, DEFAULT_RI, DEFAULT_ARI, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 90, 50, 1, 15, 22, defaultBGScale, defaultFrameRateIndex, defaultWindowedSetting);
	} else {
		SDL_RWread(settingsFile, &controlSettings, sizeof(ControlSettings), 1);
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);
		SDL_RWread(settingsFile, &soundSettings, sizeof(SoundSettings), 1);
		SDL_RWread(settingsFile, &bgSettings, sizeof(BackgroundSettings), 1);
		SDL_RWread(settingsFile, &addon131Settings, sizeof(Addon131Settings), 1);
		SDL_RWread(settingsFile, &addon134Settings, sizeof(Addon134Settings), 1);
		SDL_RWclose(settingsFile);
	}
}

void reloadVideoSettings() {
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "rb");
	if (settingsFile != NULL) {
		seekPos = SDL_RWseek(settingsFile, sizeof(ControlSettings), RW_SEEK_SET);
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);
		seekPos = SDL_RWseek(settingsFile, sizeof(ControlSettings) + sizeof(VideoSettings) + sizeof(SoundSettings) + sizeof(BackgroundSettings) + sizeof(Addon131Settings), RW_SEEK_SET);
		SDL_RWread(settingsFile, &addon134Settings, sizeof(Addon134Settings), 1);
		SDL_RWclose(settingsFile);
	}
}

void initializeSettingsFileWithSettings(Sint8 scab, Sint8 et, Sint8 ri, Sint8 ari, Sint16 gw, Sint16 gh, Sint8 mi, Sint8 bgmv, Sint8 sfxv, Sint8 t, Sint8 sm, Sint8 sd, Sint8 s, Sint8 fr, Sint8 ws) {
	controlSettings.swapConfirmAndBack = scab;
	controlSettings.enableTouchscreen = et;
	videoSettings.resolutionIndex = ri;
	videoSettings.aspectRatioIndex = ari;
	videoSettings.widthSetting = gw;
	videoSettings.heightSetting = gh;
	soundSettings.musicIndex = mi;
	soundSettings.bgmVolume = bgmv;
	soundSettings.sfxVolume = sfxv;
	bgSettings.type = t;
	bgSettings.speedMult = sm;
	bgSettings.scrollDir = sd;
	bgSettings.scale = s;
	addon131Settings.frameRateIndex = fr;
	addon134Settings.windowedSetting = ws;
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "w+b");
	if (settingsFile != NULL) {
		SDL_RWwrite(settingsFile, &controlSettings.swapConfirmAndBack, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &controlSettings.enableTouchscreen, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.resolutionIndex, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.aspectRatioIndex, sizeof(Uint8), 1);
		SDL_RWwrite(settingsFile, &videoSettings.widthSetting, sizeof(Uint16), 1);
		SDL_RWwrite(settingsFile, &videoSettings.heightSetting, sizeof(Uint16), 1);
		SDL_RWwrite(settingsFile, &soundSettings.musicIndex, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &soundSettings.bgmVolume, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &soundSettings.sfxVolume, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.type, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.speedMult, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.scrollDir, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &bgSettings.scale, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &addon131Settings.frameRateIndex, sizeof(Sint8), 1);
		SDL_RWwrite(settingsFile, &addon134Settings.windowedSetting, sizeof(Sint8), 1);
		SDL_RWclose(settingsFile);
	}
}

void loadSavedPuzzle() {
	saveFile = SDL_RWFromFile(SAVE_FILE, "rb");
	if (saveFile == NULL) {
		// This shouldn't happen, but go to the New Game menu as a fallback
		programState = 7;
	} else {
		SDL_RWread(saveFile, &gameCompleted, sizeof(gameCompleted), 1);
		SDL_RWread(saveFile, &grid, sizeof(grid), 1);
		SDL_RWread(saveFile, &originalGrid, sizeof(originalGrid), 1);
		SDL_RWread(saveFile, &solutionGrid, sizeof(solutionGrid), 1);
		SDL_RWread(saveFile, &miniGrid, sizeof(miniGrid), 1);
		SDL_RWread(saveFile, &timer_game.now, sizeof(timer_game.now), 1);
		SDL_RWread(saveFile, &menuCursorIndex_play, sizeof(menuCursorIndex_play), 1);
		SDL_RWclose(saveFile);
		programState = 9;
	}
}

void savePuzzle() {
	saveFile = SDL_RWFromFile(SAVE_FILE, "w+b");
	if (saveFile != NULL) {
		SDL_RWwrite(saveFile, &gameCompleted, sizeof(gameCompleted), 1);
		SDL_RWwrite(saveFile, &grid, sizeof(grid), 1);
		SDL_RWwrite(saveFile, &originalGrid, sizeof(originalGrid), 1);
		SDL_RWwrite(saveFile, &solutionGrid, sizeof(solutionGrid), 1);
		SDL_RWwrite(saveFile, &miniGrid, sizeof(miniGrid), 1);
		SDL_RWwrite(saveFile, &timer_game.now, sizeof(timer_game.now), 1);
		SDL_RWwrite(saveFile, &menuCursorIndex_play, sizeof(menuCursorIndex_play), 1);
		SDL_RWclose(saveFile);
	}
}

void initDefaultBGScale() {
#if defined(FUNKEY)
	defaultBGScale = 4;
#elif defined(VITA)
	defaultBGScale = 2;
#elif defined(WII_U) || defined(SWITCH)
	defaultBGScale = 3;
#else
	defaultBGScale = max((Uint8)(max(int(ceil(DEFAULT_WIDTH / 640.0)), int(ceil(DEFAULT_HEIGHT / 480.0)))), (Uint8)1);
#endif
}

void initDefaultFrameRate() {
	defaultFrameRateIndex = 5;
}

void initDefaultWindowedSetting() {
	defaultWindowedSetting = 1;
}

void initStartingWidthHeightMults() {
	gameWidthMult = (gameWidth / 640.0);
	gameHeightMult = (gameHeight / 480.0);
}

void initStartingSharedVariables() {
	double gameGridMult = game_grid_2.rect.w / 192.0; // should be the same as gameHeightMult*2, but just in case
	gridSizeA = (6 * gameGridMult); // length of 1/3 of a cell (one mini-cell)
	gridSizeB = (2 * gameGridMult); // length of divider between cells in the same group of three rows/columns
	gridSizeC = (3 * gameGridMult); // length of divider between groups of three rows/columns
	gridSizeD = (6 * gameGridMult); // length of grid border
	gridSizeA3 = (3 * gridSizeA);
	for (int i = 0; i < 9; i++) {
		gridStartingPosX[i] = (Sint16)((gridPosX + gridSizeD) + (i * gridSizeA3) + (i * gridSizeB) + ((gridSizeC - gridSizeB) * (i / 3)));
		gridStartingPosY[i] = (Sint16)((gridPosY + gridSizeD) + (i * gridSizeA3) + (i * gridSizeB) + ((gridSizeC - gridSizeB) * (i / 3)));
	}
	//gridSize = (27 * gridSizeA + 6 * gridSizeB + 2 * gridSizeC + 2 * gridSizeD);
	gridSize = game_grid_2.rect.w;
	gridSizeD3 = gridSizeD * 3;
	gridSizeA3_half = (Sint16)(gridSizeA3 / 2);
	gridSizeA3B = gridSizeA3 + gridSizeB;
	gridNumSize = (Uint16)(gridSizeA * 3);
}

void updateGlobalTimer() {
	timer_global.last = timer_global.now;
	currTicks = SDL_GetTicks();
	timer_global.now = (currTicks - timer_paused.now) / 1000.0;
}

void preparePauseTimer() {
	timer_paused.last = SDL_GetTicks();
}

void updatePauseTimer() {
	timer_paused.now += (SDL_GetTicks() - timer_paused.last);
}

void saveCurrentSettings() {
	initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen,
		videoSettings.resolutionIndex, videoSettings.aspectRatioIndex, videoSettings.widthSetting, videoSettings.heightSetting,
		soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume,
		bgSettings.type, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale,
		addon131Settings.frameRateIndex, addon134Settings.windowedSetting);
}

void setNativeResolution() {
	Sint32 int_i;
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			int_i = SYSTEM_HEIGHT * 4 / 3;
			if (int_i <= SYSTEM_WIDTH) {
				gameWidth = int_i;
				gameHeight = SYSTEM_HEIGHT;
			} else {
				gameWidth = SYSTEM_WIDTH;
				gameHeight = SYSTEM_WIDTH * 3 / 4;
			}
			break;
		case 2:
			int_i = SYSTEM_HEIGHT * 16 / 9;
			if (int_i <= SYSTEM_WIDTH) {
				gameWidth = int_i;
				gameHeight = SYSTEM_HEIGHT;
			} else {
				gameWidth = SYSTEM_WIDTH;
				gameHeight = SYSTEM_WIDTH * 9 / 16;
			}
			break;
		case 3:
			int_i = SYSTEM_HEIGHT * 16 / 10;
			if (int_i <= SYSTEM_WIDTH) {
				gameWidth = int_i;
				gameHeight = SYSTEM_HEIGHT;
			} else {
				gameWidth = SYSTEM_WIDTH;
				gameHeight = SYSTEM_WIDTH * 10 / 16;
			}
			break;
		case 4:
			if (SYSTEM_HEIGHT <= SYSTEM_WIDTH) {
				gameWidth = SYSTEM_HEIGHT;
				gameHeight = SYSTEM_HEIGHT;
			}
			else {
				gameWidth = SYSTEM_WIDTH;
				gameHeight = SYSTEM_WIDTH;
			}
			break;
		default:
			gameWidth = SYSTEM_WIDTH;
			gameHeight = SYSTEM_HEIGHT;
			break;
	}
}

void setResolution(Sint8 increment) {
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_4_3, RESOLUTION_OPTIONS_HEIGHT_4_3, LEN(RESOLUTION_OPTIONS_WIDTH_4_3), increment);
			break;
		case 2:
			setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_9, RESOLUTION_OPTIONS_HEIGHT_16_9, LEN(RESOLUTION_OPTIONS_WIDTH_16_9), increment);
			break;
		case 3:
			setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_10, RESOLUTION_OPTIONS_HEIGHT_16_10, LEN(RESOLUTION_OPTIONS_WIDTH_16_10), increment);
			break;
		case 4:
			setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_1_1, RESOLUTION_OPTIONS_HEIGHT_1_1, LEN(RESOLUTION_OPTIONS_WIDTH_1_1), increment);
			break;
		default:
			break;
	}
}

void setResolutionByOptions(const Uint16 *resolutionOptions_width, const Uint16 *resolutionOptions_height, Uint8 numOptions, Sint8 increment) {
	videoSettings.resolutionIndex += increment;
	if (videoSettings.resolutionIndex < 0) {
		videoSettings.resolutionIndex = numOptions - 1;
	}
	else if (videoSettings.resolutionIndex > numOptions - 1) {
		videoSettings.resolutionIndex = 0;
	}
	videoSettings.widthSetting = resolutionOptions_width[videoSettings.resolutionIndex];
	videoSettings.heightSetting = resolutionOptions_height[videoSettings.resolutionIndex];
	if (videoSettings.widthSetting > SYSTEM_WIDTH || videoSettings.heightSetting > SYSTEM_HEIGHT) {
		setResolutionByOptions(resolutionOptions_width, resolutionOptions_height, numOptions, increment);
	}
}

void setAspectRatioByOptions(Sint8 increment) {
	videoSettings.aspectRatioIndex += increment;
	if (videoSettings.aspectRatioIndex < 0) {
		videoSettings.aspectRatioIndex = 4;
	} else if (videoSettings.aspectRatioIndex > 4) {
		videoSettings.aspectRatioIndex = 0;
	}
	videoSettings.resolutionIndex = 0;
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex];
			break;
		case 2:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex];
			break;
		case 3:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex];
			break;
		case 4:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_1_1[videoSettings.resolutionIndex];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_1_1[videoSettings.resolutionIndex];
			break;
		default:
			videoSettings.widthSetting = 0;
			videoSettings.heightSetting = 0;
			break;
	}
}

#define NUM_FRAMERATE_OPTIONS 5

void setFrameRateByOptions(Sint8 increment) {
	addon131Settings.frameRateIndex += increment;
	if (addon131Settings.frameRateIndex < 0) {
		addon131Settings.frameRateIndex = NUM_FRAMERATE_OPTIONS;
	} else if (addon131Settings.frameRateIndex > NUM_FRAMERATE_OPTIONS) {
		addon131Settings.frameRateIndex = 0;
	}
	switch (addon131Settings.frameRateIndex) {
		case 1:
			frameRate = 20;
			break;
		case 2:
			frameRate = 30;
			break;
		case 3:
			frameRate = 40;
			break;
		case 4:
			frameRate = 50;
			break;
		case 5:
			frameRate = 60;
			break;
		default:
			frameRate = (Uint8)min((int)displayRefreshRate, 255);
			break;
	}
	ticksPerFrame = (Uint32)(1000 / frameRate);
}

Uint16 menuCursorXOffset() {
	return (Uint16)((menuCursor.rect.w * 2.5) + SIN_WAVE(timer_global.now, 0.5, text_standardAmplitude));
}

void sdlToggleFullscreen() {
#if !(defined(CONSOLE) || defined(SDL1))
	isWindowed = !isWindowed;
	if (isWindowed)
		SDL_SetWindowFullscreen(window, 0);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	setScaling();
#endif
}

void sdlToggleIntegerScale() {
	//isIntegerScale = !isIntegerScale;
	////setScaling();
	//windowSizeChanged = true;
}

void toggleDualScreen() {
#if defined(THREEDS)
	addon134Settings.windowedSetting = !addon134Settings.windowedSetting;
	// 3DS SDL2 doesn't support this...
	//if (addon134Settings.windowedSetting) {
	//	window = windowTop;
	//	renderer = rendererTop;
	//} else {
	//	window = windowBottom;
	//	renderer = rendererBottom;
	//}
#endif
}

void setScaling() {
#if !defined(ANDROID)
	if (isIntegerScale) {
		Sint32 intScreenScale = min((int)(SCALING_WIDTH / gameWidth), (int)(SCALING_HEIGHT / gameHeight));
		if (intScreenScale < 1) intScreenScale = 1;
		centerViewport.w = gameWidth * intScreenScale;
		centerViewport.h = gameHeight * intScreenScale;
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / intScreenScale), 0);
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / intScreenScale), 0);
#if !defined(SDL1)
		SDL_RenderSetScale(renderer, (float)intScreenScale, (float)intScreenScale);
		SDL_RenderSetViewport(renderer, &centerViewport);
#endif
		screenScale = (float)intScreenScale;
	} else {
		screenScale = (float)SCALING_WIDTH / gameWidth;
		if ((float)SCALING_HEIGHT / gameHeight < screenScale) {
			screenScale = (float)SCALING_HEIGHT / gameHeight;
		}
		if (screenScale < 1) screenScale = 1;
		centerViewport.w = (int)(gameWidth * screenScale);
		centerViewport.h = (int)(gameHeight * screenScale);
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / screenScale), 0);
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / screenScale), 0);
#if !defined(SDL1)
		SDL_RenderSetScale(renderer, screenScale, screenScale);
		SDL_RenderSetViewport(renderer, &centerViewport);
#endif
	}
	updateBorderRects();
	//SDL_RenderSetClipRect(renderer, &centerViewport);
#endif
}

void updateBorderRects() {
	topRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 50;
	topRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 100;
	topRect.w = SCALING_WIDTH + 100;
	topRect.h = (SCALING_HEIGHT - gameHeight) / 2 + 100;
	bottomRect.x = topRect.x;
	bottomRect.y = gameHeight;
	bottomRect.w = topRect.w;
	bottomRect.h = topRect.h;
	leftRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 100;
	leftRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 50;
	leftRect.w = (SCALING_WIDTH - gameWidth) / 2 + 100;
	leftRect.h = SCALING_HEIGHT + 100;
	rightRect.x = gameWidth;
	rightRect.y = leftRect.y;
	rightRect.w = leftRect.w;
	rightRect.h = leftRect.h;
}

void renderBackground() {
	double speedStep = bgSettings.speedMult * deltaTime;
	bgScroll.speedStep_x += speedStep * bgScroll.speed_x;
	bgScroll.speedStep_x_int = static_cast<int>(floor(bgScroll.speedStep_x)) % tile->rect.h;
	bgScroll.speedStep_y += speedStep * bgScroll.speed_y;
	bgScroll.speedStep_y_int = static_cast<int>(floor(bgScroll.speedStep_y)) % tile->rect.w;
	int start_x = -tile->rect.w + bgScroll.speedStep_x_int;
	int start_y = -tile->rect.h + bgScroll.speedStep_y_int;
	for (int j = start_y; j <= bgScroll.final_y; j += tile->rect.h) {
		for (int i = start_x; i <= bgScroll.final_x; i += tile->rect.w) {
#if defined(SDL1)
			SDL_Rect outputRect = { i, j, tile->rect.w, tile->rect.h };
			SDL_RenderCopy(renderer, tile->texture, NULL, &outputRect);
#else
			tile->rect.x = i;
			tile->rect.y = j;
			SDL_RenderCopy(renderer, tile->texture, NULL, &tile->rect);
#endif
		}
	}
}

void renderBackgroundNotBehindGrid() {
	bgScroll.speedStep_x += bgSettings.speedMult * bgScroll.speed_x * deltaTime;
	bgScroll.speedStep_x_int = static_cast<int>(floor(bgScroll.speedStep_x)) % tile->rect.h;
	bgScroll.speedStep_y += bgSettings.speedMult * bgScroll.speed_y * deltaTime;
	bgScroll.speedStep_y_int = static_cast<int>(floor(bgScroll.speedStep_y)) % tile->rect.w;
	int start_x = -tile->rect.w + bgScroll.speedStep_x_int;
	int start_y = -tile->rect.h + bgScroll.speedStep_y_int;
	for (int j = start_y; j <= bgScroll.final_y; j += tile->rect.h) {
		for (int i = start_x; i <= bgScroll.final_x; i += tile->rect.w) {
			if (i >= game_grid_2.rect.x && i <= bg_max_x && j >= game_grid_2.rect.y && j <= bg_max_y) {
				continue;
			}
#if defined(SDL1)
			SDL_Rect outputRect = { i, j, tile->rect.w, tile->rect.h };
			SDL_RenderCopy(renderer, tile->texture, NULL, &outputRect);
#else
			tile->rect.x = i;
			tile->rect.y = j;
			SDL_RenderCopy(renderer, tile->texture, NULL, &tile->rect);
#endif
		}
	}
}

void renderBorderRects() {
#if defined(SDL1)
	SDL_FillRect(windowScreen, &topRect, 0);
	SDL_FillRect(windowScreen, &bottomRect, 0);
	SDL_FillRect(windowScreen, &leftRect, 0);
	SDL_FillRect(windowScreen, &rightRect, 0);
#else
	SDL_RenderFillRect(renderer, &topRect);
	SDL_RenderFillRect(renderer, &bottomRect);
	SDL_RenderFillRect(renderer, &leftRect);
	SDL_RenderFillRect(renderer, &rightRect);
#endif
}

void sdlDestroyAll() {
	/* Destroy Everything */
	/* Textures */
	SDL_DestroyTexture(tile1.texture);
	SDL_DestroyTexture(tile2.texture);
	SDL_DestroyTexture(tile3.texture);
	SDL_DestroyTexture(tile_cave.texture);
	SDL_DestroyTexture(tile_desert.texture);
	SDL_DestroyTexture(tile_grasslands.texture);
	SDL_DestroyTexture(tile_grasslands2.texture);
	SDL_DestroyTexture(tile_snowymountain.texture);
	SDL_DestroyTexture(logo_1.texture);
	SDL_DestroyTexture(logo_2.texture);
	SDL_DestroyTexture(logo_3.texture);
	SDL_DestroyTexture(menuCursor.texture);
	SDL_DestroyTexture(game_grid_1.texture);
	SDL_DestroyTexture(game_grid_2.texture);
	SDL_DestroyTexture(game_grid_3.texture);
	SDL_DestroyTexture(gridCursor_bottom_left.texture);
	SDL_DestroyTexture(gridCursor_bottom_right.texture);
	SDL_DestroyTexture(gridCursor_top_left.texture);
	SDL_DestroyTexture(gridCursor_top_right.texture);
	SDL_DestroyTexture(game_sidebar_small_1.texture);
	SDL_DestroyTexture(game_sidebar_small_2.texture);
	SDL_DestroyTexture(game_sidebar_small_3.texture);
	SDL_DestroyTexture(miniGrid_bottom_left.texture);
	SDL_DestroyTexture(miniGrid_bottom_right.texture);
	SDL_DestroyTexture(miniGrid_top_left.texture);
	SDL_DestroyTexture(miniGrid_top_right.texture);
	/* Text Objects */
	for (i = 32; i < LEN(textChars); i++) {
		destroyTextObjectTexture(&textChars[i]);
	}
	for (i = 0; i < 10; i++) {
		destroyTextObjectTexture(&gridNums_black[i]);
		destroyTextObjectTexture(&gridNums_blue[i]);
	}
	/* Fonts */
	TTF_CloseFont(pixelFont);
	TTF_CloseFont(pixelFont_grid);
	TTF_CloseFont(pixelFont_grid_mini);
	TTF_Quit();
	/* Sound */
	Mix_HaltMusic();
	Mix_FreeMusic(bgm_1);
	Mix_FreeMusic(bgm_2);
	Mix_FreeMusic(bgm_3);
	Mix_FreeMusic(bgm_4);
	Mix_FreeMusic(bgm_5);
	Mix_FreeMusic(bgm_6);
	Mix_FreeMusic(bgm_7);
	Mix_FreeMusic(bgm_8);
	Mix_FreeChunk(sfx);
	Mix_CloseAudio();
	Mix_Quit();
	/* Controller */
	closeController();
	/* Renderer and Window */
#if !defined(SDL1)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
#else
	SDL_FreeSurface(windowScreen);
#endif
	SDL_Quit();
}

void closeController() {
#if defined(PSP) || defined(SDL1)
	for (auto& joystick : controllers) {
		SDL_JoystickClose(joystick);
}
#else
	for (auto& gameController : controllers) {
		if (gameController != NULL) {
			SDL_GameControllerClose(gameController);
		}
	}
#endif
	controllers.clear();
}

void systemSpecificClose() {
#if defined(WII_U)
	WHBUnmountSdCard();
	WHBProcInit();
	WHBProcShutdown();
#elif defined(VITA)
	sceKernelExitProcess(0);
#elif defined(PSP)
	sceKernelExitGame();
#endif
}