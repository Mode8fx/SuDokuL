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
		initializeSettingsFileWithSettings(true, true, DEFAULT_RI, DEFAULT_ARI, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 90, 50, 1, 15, 22, defaultBGScale, defaultFrameRateIndex);
	} else {
		SDL_RWread(settingsFile, &controlSettings, sizeof(ControlSettings), 1);
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);
		SDL_RWread(settingsFile, &soundSettings, sizeof(SoundSettings), 1);
		SDL_RWread(settingsFile, &bgSettings, sizeof(BackgroundSettings), 1);
		SDL_RWread(settingsFile, &addon131Settings, sizeof(Addon131Settings), 1);
		SDL_RWclose(settingsFile);
	}
}

void reloadVideoSettings() {
	settingsFile = SDL_RWFromFile(SETTINGS_FILE, "rb");
	if (settingsFile != NULL) {
		seekPos = SDL_RWseek(settingsFile, sizeof(ControlSettings), RW_SEEK_SET);
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);
		SDL_RWclose(settingsFile);
	}
}

void initializeSettingsFileWithSettings(Sint8 scab, Sint8 et, Sint8 ri, Sint8 ari, Sint16 gw, Sint16 gh, Sint8 mi, Sint8 bgmv, Sint8 sfxv, Sint8 t, Sint8 sm, Sint8 sd, Sint8 s, Sint8 fr) {
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
#if defined(THREEDS)
	defaultFrameRateIndex = 2;
#else
	defaultFrameRateIndex = 5;
#endif
}

void initStartingWidthHeightMults() {
	gameWidthMult = (gameWidth / 640.0);
	gameHeightMult = (gameHeight / 480.0);
}

void initStartingSharedVariables() {
	gridSizeA = (12 * gameHeightMult); // length of 1/3 of a cell (one mini-cell)
	gridSizeB = (4 * gameHeightMult);  // length of divider between cells in the same group of three rows/columns
	gridSizeC = (6 * gameHeightMult);  // length of divider between groups of three rows/columns
	gridSizeD = (12 * gameHeightMult); // length of grid border
	gridSizeA3 = (3 * gridSizeA);
	gridSize = (27 * gridSizeA + 6 * gridSizeB + 2 * gridSizeC + 2 * gridSizeD);
	gameSidebarSmall1Rect.w = (Sint16)SIDEBAR_SMALL_SIZE_X;
	gameSidebarSmall1Rect.h = (Sint16)SIDEBAR_SMALL_SIZE_Y;
	if (!compactDisplay) {
		gridPosX = (Uint16)((gameWidth / 2) - (gridSize / 2) + (gridSize * 5 / 24));
		gridPosY = (Uint16)((gameHeight - gridSize) / 2);
		gameSidebarSmall1Rect.x = (Sint16)(gridPosX - SIDEBAR_SMALL_SIZE_X - (gridSize / 12));
		gameSidebarSmall1Rect.y = (Sint16)(gridPosY + (gridSize / 16));
		gameSidebarSmall2Rect = gameSidebarSmall1Rect;
		gameSidebarSmall2Rect.y = (Sint16)(gridPosY + SIDEBAR_SMALL_SIZE_Y + (gridSize / 8));
		gameSidebarSmall3Rect = gameSidebarSmall1Rect;
		gameSidebarSmall3Rect.y = (Sint16)(gridPosY + (2 * SIDEBAR_SMALL_SIZE_Y) + (gridSize * 3 / 16));
	} else {
		gridPosX = (Sint16)((gameWidth / 2) - (gridSize / 2));
		gridPosY = (Sint16)((gameHeight - gridSize) * 875 / 1000);
		gameSidebarSmall1Rect.x = (Sint16)((gameWidth / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
		gameSidebarSmall1Rect.y = -(Sint16)(SIDEBAR_SMALL_SIZE_Y / 4);
		gameSidebarSmall2Rect = gameSidebarSmall1Rect;
		gameSidebarSmall2Rect.x = (Sint16)((gameWidth / 2) - (SIDEBAR_SMALL_SIZE_X / 2));
		gameSidebarSmall3Rect = gameSidebarSmall1Rect;
		gameSidebarSmall3Rect.x = (Sint16)((gameWidth * 4 / 5) - (SIDEBAR_SMALL_SIZE_X / 2));
	}
	gridStartingPosX[0] = (Sint16)((gridPosX + gridSizeD) + (0 * gridSizeA3) + (0 * gridSizeB) + ((gridSizeC - gridSizeB) * 0 / 3));
	gridStartingPosX[1] = (Sint16)((gridPosX + gridSizeD) + (1 * gridSizeA3) + (1 * gridSizeB) + ((gridSizeC - gridSizeB) * 1 / 3));
	gridStartingPosX[2] = (Sint16)((gridPosX + gridSizeD) + (2 * gridSizeA3) + (2 * gridSizeB) + ((gridSizeC - gridSizeB) * 2 / 3));
	gridStartingPosX[3] = (Sint16)((gridPosX + gridSizeD) + (3 * gridSizeA3) + (3 * gridSizeB) + ((gridSizeC - gridSizeB) * 3 / 3));
	gridStartingPosX[4] = (Sint16)((gridPosX + gridSizeD) + (4 * gridSizeA3) + (4 * gridSizeB) + ((gridSizeC - gridSizeB) * 4 / 3));
	gridStartingPosX[5] = (Sint16)((gridPosX + gridSizeD) + (5 * gridSizeA3) + (5 * gridSizeB) + ((gridSizeC - gridSizeB) * 5 / 3));
	gridStartingPosX[6] = (Sint16)((gridPosX + gridSizeD) + (6 * gridSizeA3) + (6 * gridSizeB) + ((gridSizeC - gridSizeB) * 6 / 3));
	gridStartingPosX[7] = (Sint16)((gridPosX + gridSizeD) + (7 * gridSizeA3) + (7 * gridSizeB) + ((gridSizeC - gridSizeB) * 7 / 3));
	gridStartingPosX[8] = (Sint16)((gridPosX + gridSizeD) + (8 * gridSizeA3) + (8 * gridSizeB) + ((gridSizeC - gridSizeB) * 8 / 3));
	gridStartingPosY[0] = (Sint16)((gridPosY + gridSizeD) + (0 * gridSizeA3) + (0 * gridSizeB) + ((gridSizeC - gridSizeB) * 0 / 3));
	gridStartingPosY[1] = (Sint16)((gridPosY + gridSizeD) + (1 * gridSizeA3) + (1 * gridSizeB) + ((gridSizeC - gridSizeB) * 1 / 3));
	gridStartingPosY[2] = (Sint16)((gridPosY + gridSizeD) + (2 * gridSizeA3) + (2 * gridSizeB) + ((gridSizeC - gridSizeB) * 2 / 3));
	gridStartingPosY[3] = (Sint16)((gridPosY + gridSizeD) + (3 * gridSizeA3) + (3 * gridSizeB) + ((gridSizeC - gridSizeB) * 3 / 3));
	gridStartingPosY[4] = (Sint16)((gridPosY + gridSizeD) + (4 * gridSizeA3) + (4 * gridSizeB) + ((gridSizeC - gridSizeB) * 4 / 3));
	gridStartingPosY[5] = (Sint16)((gridPosY + gridSizeD) + (5 * gridSizeA3) + (5 * gridSizeB) + ((gridSizeC - gridSizeB) * 5 / 3));
	gridStartingPosY[6] = (Sint16)((gridPosY + gridSizeD) + (6 * gridSizeA3) + (6 * gridSizeB) + ((gridSizeC - gridSizeB) * 6 / 3));
	gridStartingPosY[7] = (Sint16)((gridPosY + gridSizeD) + (7 * gridSizeA3) + (7 * gridSizeB) + ((gridSizeC - gridSizeB) * 7 / 3));
	gridStartingPosY[8] = (Sint16)((gridPosY + gridSizeD) + (8 * gridSizeA3) + (8 * gridSizeB) + ((gridSizeC - gridSizeB) * 8 / 3));
	initNumOffsets();
}

static void initNumOffsets_544() {
	//d = (double)gameHeight / SCALING_HEIGHT;
	d = 1.0;
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
}

static void initNumOffsets_272() {
	//d = (double)gameHeight / SCALING_HEIGHT;
	d = 1.0;
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
}

static void initNumOffsets_240() {
	//d = (double)gameHeight / SCALING_HEIGHT;
	d = 1.0;
	for (i = 0; i < 9; i++) {
		numOffset_large_x[i] = (Sint8)(d);
		numOffset_large_y[i] = 0;
		numOffset_small_x[i] = 0;
		numOffset_small_y[i] = 0;
	}
}

static void initNumOffsets_Standard() {
	for (i = 0; i < 9; i++) {
		numOffset_large_x[i] = 0;
		numOffset_large_y[i] = 0;
		numOffset_small_x[i] = 0;
		numOffset_small_y[i] = 0;
	}
}

void initNumOffsets() {
	if (gameHeight == 272) {
		initNumOffsets_272();
#if defined(SDL1)
	} else if (gameHeight == 240) {
		initNumOffsets_240();
#endif
	} else if (gameHeight == 544) {
		initNumOffsets_544();
	} else {
		initNumOffsets_Standard();
	}
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
		bgSettings.type, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale,
		addon131Settings.frameRateIndex);
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

void setFrameRateByOptions(Sint8 increment) {
	addon131Settings.frameRateIndex += increment;
	if (addon131Settings.frameRateIndex < 0) {
		addon131Settings.frameRateIndex = 5;
	}
	else if (addon131Settings.frameRateIndex > 5) {
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

void setScaling() {
#if !defined(ANDROID)
	if (isIntegerScale) {
		int_i = min((int)(SCALING_WIDTH / gameWidth), (int)(SCALING_HEIGHT / gameHeight));
		if (int_i < 1) int_i = 1;
		centerViewport.w = gameWidth * int_i;
		centerViewport.h = gameHeight * int_i;
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / int_i), 0);
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / int_i), 0);
#if !defined(SDL1)
		SDL_RenderSetScale(renderer, (float)int_i, (float)int_i);
		SDL_RenderSetViewport(renderer, &centerViewport);
#endif
		screenScale = (float)int_i;
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
	WHBProcInit();
	WHBProcShutdown();
#elif defined(VITA)
	sceKernelExitProcess(0);
#elif defined(PSP)
	sceKernelExitGame();
#endif
}