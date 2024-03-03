#include "shared.h"
#include "general.h"
#include "sprite_objects.h"
#include "config.h"
#include "window.h"
#include "sudokuGen.h"
#include "puzzleBank.h"
#include "menu_logic.h"

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
	uint_i = (max(DEFAULT_WIDTH / 640, DEFAULT_HEIGHT / 480));
	defaultBGScale = max((Uint16)(uint_i), (Uint16)1);
}

void initStartingWidthHeightMults() {
	gameWidthMult = (gameWidth / 640.0);
	gameHeightMult = (gameHeight / 480.0);
}

void initStartingSharedVariables() {
	gridSizeA = (12 * GAME_HEIGHT_MULT);
	gridSizeB = (4 * GAME_HEIGHT_MULT);
	gridSizeC = (6 * GAME_HEIGHT_MULT);
	gridSizeD = (12 * GAME_HEIGHT_MULT);
	gridSizeA3 = (3 * GRID_SIZE_A);
	gridSize = (27 * GRID_SIZE_A + 6 * GRID_SIZE_B + 2 * GRID_SIZE_C + 2 * GRID_SIZE_D);
	if (!compactDisplay) {
		gridPosX = (Uint16)((gameWidth / 2) - (GRID_SIZE / 2) + (GRID_SIZE * 5 / 24));
	} else {
		gridPosX = (Uint16)((gameWidth / 2) - (GRID_SIZE / 2));
	}
	gridPosY = (Uint16)((gameHeight - GRID_SIZE) / 2);
	sideBarSizeX = (Uint16)(GRID_SIZE / 3);
	sideBarSizeY = (Uint16)(GRID_SIZE / 4);
	sidebarSmallPosX = (Uint16)(GRID_POS_X - SIDEBAR_SIZE_X - (GRID_SIZE / 12));
	sidebarSmall1PosY = (Uint16)(GRID_POS_Y + (GRID_SIZE / 16));
	sidebarSmall2PosY = (Uint16)(GRID_POS_Y + SIDEBAR_SMALL_SIZE_Y + (GRID_SIZE / 8));
	sidebarSmall3PosY = (Uint16)(GRID_POS_Y + (2 * SIDEBAR_SMALL_SIZE_Y) + (GRID_SIZE * 3 / 16));
	gridStartingPosX[0] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 0 / 3));
	gridStartingPosX[1] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 1 / 3));
	gridStartingPosX[2] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 2 / 3));
	gridStartingPosX[3] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 3 / 3));
	gridStartingPosX[4] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 4 / 3));
	gridStartingPosX[5] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 5 / 3));
	gridStartingPosX[6] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 6 / 3));
	gridStartingPosX[7] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 7 / 3));
	gridStartingPosX[8] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 8 / 3));
	gridStartingPosY[0] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 0 / 3));
	gridStartingPosY[1] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 1 / 3));
	gridStartingPosY[2] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 2 / 3));
	gridStartingPosY[3] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 3 / 3));
	gridStartingPosY[4] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 4 / 3));
	gridStartingPosY[5] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 5 / 3));
	gridStartingPosY[6] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 6 / 3));
	gridStartingPosY[7] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 7 / 3));
	gridStartingPosY[8] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((GRID_SIZE_C - GRID_SIZE_B) * 8 / 3));
	initNumOffsets();
}

void initNumOffsets() {
#if defined(VITA)
	d = (double)gameHeight / SCALING_HEIGHT;
	for (i = 0; i < 9; i++) {
		numOffset_large_x[i] = (Sint8)(2 * d);
		numOffset_large_y[i] = (Sint8)(d);
		numOffset_small_x[i] = 0;
		numOffset_small_y[i] = (Sint8)(-d);
	}
	numOffset_large_y[2] = 0;
	numOffset_large_y[5] = 0;
	numOffset_large_y[6] = 0;
	numOffset_large_y[7] = 0;
	numOffset_small_y[1] = 0;
	numOffset_small_y[3] = 0;
	if (gameHeight <= 240) {
		for (i = 0; i < 9; i++) numOffset_small_y[i] -= 1;
	}
#elif defined(PSP)
	d = (double)gameHeight / SCALING_HEIGHT;
	for (i = 0; i < 9; i++) {
		numOffset_large_x[i] = (Sint8)(d);
		numOffset_large_y[i] = 0;
		numOffset_small_x[i] = (Sint8)(d);
		numOffset_small_y[i] = (Sint8)(d);
	}
	numOffset_large_y[2] = (Sint8)(-d);
	numOffset_large_y[5] = (Sint8)(-d);
	numOffset_large_y[6] = (Sint8)(-d);
	numOffset_large_y[8] = (Sint8)(-d);
	numOffset_small_y[2] = 0;
	numOffset_small_y[5] = 0;
	numOffset_small_y[8] = 0;
#else
	for (i = 0; i < 9; i++) {
		numOffset_large_x[i] = 0;
		numOffset_large_y[i] = 0;
		numOffset_small_x[i] = 0;
		numOffset_small_y[i] = 0;
	}
#endif
}

void updateGlobalTimer() {
	timer_global.last = timer_global.now;
	timer_global.now = (SDL_GetTicks() - timer_paused.now) / 1000.0;
}

void preparePauseTimer() {
	timer_paused.last = SDL_GetTicks();
}

void updatePauseTimer() {
	timer_paused.now += (SDL_GetTicks() - timer_paused.last);
}

void initMenuOptionPositions(TextObject *textObj) {
	textObj->startPos_x = textObj->rect.x;
	textObj->startPos_y = textObj->rect.y;
	textObj->endPos_x = textObj->startPos_x + (gameWidth * 3 / 4);
	textObj->endPos_y = textObj->startPos_y - (gameWidth * 3 / 4);
}

void saveCurrentSettings() {
	initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen,
		videoSettings.resolutionIndex, videoSettings.aspectRatioIndex, videoSettings.widthSetting, videoSettings.heightSetting,
		soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume,
		bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale);
}

void setNativeResolution() {
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

Uint16 menuCursorXOffset() {
	return ((menuCursor.rect.w * 2.5) + SIN_WAVE(timer_global.now, 0.5, TEXT_STANDARD_AMPLITUDE));
}

void sdlToggleFullscreen() {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP))
	isWindowed = !isWindowed;
	if (isWindowed)
		SDL_SetWindowFullscreen(window, 0);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	setScaling();
#endif
}

void sdlToggleIntegerScale() {
	isIntegerScale = !isIntegerScale;
	//setScaling();
	windowSizeChanged = true;
}

void setScaling() {
#if !defined(ANDROID)
	if (isIntegerScale) {
		int_i = min((int)(SCALING_WIDTH / gameWidth), (int)(SCALING_HEIGHT / gameHeight));
		if (int_i < 1) int_i = 1;
		centerViewport.w = gameWidth * int_i;
		centerViewport.h = gameHeight * int_i;
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / int_i), 0);
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / int_i), 0);
		SDL_RenderSetScale(renderer, int_i, int_i);
		SDL_RenderSetViewport(renderer, &centerViewport);
		screenScale = (double)int_i;
	} else {
		screenScale = (double)SCALING_WIDTH / gameWidth;
		if ((double)SCALING_HEIGHT / gameHeight < screenScale) {
			screenScale = (double)SCALING_HEIGHT / gameHeight;
		}
		if (screenScale < 1) screenScale = 1;
		centerViewport.w = (int)(gameWidth * screenScale);
		centerViewport.h = (int)(gameHeight * screenScale);
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / screenScale), 0);
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / screenScale), 0);
		SDL_RenderSetScale(renderer, screenScale, screenScale);
		SDL_RenderSetViewport(renderer, &centerViewport);
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

void renderBorderRects() {
	SDL_RenderFillRect(renderer, &topRect);
	SDL_RenderFillRect(renderer, &bottomRect);
	SDL_RenderFillRect(renderer, &leftRect);
	SDL_RenderFillRect(renderer, &rightRect);
}

void sdlDestroyAll() {
	/* Destroy Everything */
	/* Textures */
	SDL_DestroyTexture(tile.texture);
	SDL_DestroyTexture(logo.texture);
	SDL_DestroyTexture(menuCursor.texture);
	SDL_DestroyTexture(game_grid.texture);
	SDL_DestroyTexture(gridCursor_bottom_left.texture);
	SDL_DestroyTexture(gridCursor_bottom_right.texture);
	SDL_DestroyTexture(gridCursor_top_left.texture);
	SDL_DestroyTexture(gridCursor_top_right.texture);
	SDL_DestroyTexture(game_sidebar_small.texture);
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void closeController() {
#if defined(PSP)
	SDL_JoystickClose(controller);
#else
	if (controller != NULL) {
		SDL_GameControllerClose(controller);
	}
#endif
}

void systemSpecificClose() {
#if defined(WII_U)
	WHBUnmountSdCard();
#elif defined(VITA)
	sceKernelExitProcess(0);
#elif defined(PSP)
	sceKernelExitGame();
#endif
}