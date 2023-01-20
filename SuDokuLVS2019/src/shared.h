#include "include.h"

#ifndef SHARED_H
#define SHARED_H

struct ControlSettings {
	Sint8 swapConfirmAndBack;
	Sint8 enableTouchscreen;
};

struct VideoSettings {
	Sint8 resolutionIndex;
	Sint8 aspectRatioIndex;
	Uint16 widthSetting;
	Uint16 heightSetting;
};

struct SoundSettings {
	Sint8 musicIndex;
	Sint8 bgmVolume;
	Sint8 sfxVolume;
};

struct BackgroundSettings {
	Sint8 speedMult; // Scroll Speed
	Sint8 scrollDir; // Scroll Direction
	Sint8 scale; // Background Size
};

struct BGScroll {
	double speed_x, speed_y;
	double speedStep_x, speedStep_y;
	Sint16 speedStep_x_int, speedStep_y_int;
	Sint16 i;
	Sint16 j;
};

struct Timer {
	double now;
	double last;
};

/* Window Width and Height */
extern Uint16 gameWidth;
extern Uint16 gameHeight;
extern Uint16 defaultBGScale;
extern double gameWidthMult;
extern double gameHeightMult;

/* Grid-Related Variables */
extern double gridSizeA;
extern double gridSizeB;
extern double gridSizeC;
extern double gridSizeD;
extern double gridSize;
extern double gridSizeA3;
extern Uint16 gridPosX;
extern Uint16 gridPosY;
extern Uint16 sideBarSizeX;
extern Uint16 sideBarSizeY;
extern Uint16 sidebarSmallPosX;
extern Uint16 sidebarSmall1PosY;
extern Uint16 sidebarSmall2PosY;
extern Uint16 sidebarSmall3PosY;
extern Uint16 gridStartingPosX[9];
extern Uint16 gridStartingPosY[9];

/* Settings */
extern SDL_RWops *settingsFile;
extern BackgroundSettings bgSettings;
extern BGScroll bgScroll;
extern ControlSettings controlSettings;
extern VideoSettings videoSettings;
extern SoundSettings soundSettings;

/* Window Width and Height */
extern Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[14];
extern Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[14];
extern Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[12];
extern Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[12];
extern Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[10];
extern Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[10];
extern Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[6];
extern Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[6];
extern SDL_Rect centerViewport;

/* Sound */
extern Mix_Music *bgm_1;
extern Mix_Music *bgm_2;
extern Mix_Music *bgm_3;
extern Mix_Music *bgm_4;
extern Mix_Music *bgm_5;
extern Mix_Music *bgm_6;
extern Mix_Music *bgm_7;
extern Mix_Chunk *sfx;

#define INIT_DEFAULT_BG_SCALE()                                \
	uint_i = (max(DEFAULT_WIDTH / 640, DEFAULT_HEIGHT / 480)); \
	defaultBGScale = max((Uint16)(uint_i), (Uint16)1);

#define INIT_STARTING_WIDTH_HEIGHT_MULTS()        \
	gameWidthMult = (gameWidth / 640.0);   \
	gameHeightMult = (gameHeight / 480.0); \

#define INIT_STARTING_SHARED_VARIABLES()                                                                            \
	gridSizeA = (12 * GAME_HEIGHT_MULT);                                                                            \
	gridSizeB = (4 * GAME_HEIGHT_MULT);                                                                             \
	gridSizeC = (6 * GAME_HEIGHT_MULT);                                                                             \
	gridSizeD = (12 * GAME_HEIGHT_MULT);                                                                            \
	gridSize = (27 * GRID_SIZE_A + 6 * GRID_SIZE_B + 2 * GRID_SIZE_C + 2 * GRID_SIZE_D);                            \
	gridSizeA3 = (3 * GRID_SIZE_A);                                                                                 \
	gridPosX = (Uint16)((gameWidth / 2) - (GRID_SIZE / 2) + (GRID_SIZE * 5 / 24));                                  \
	gridPosY = (Uint16)((gameHeight - GRID_SIZE) / 2);                                                              \
	sideBarSizeX = (Uint16)(GRID_SIZE / 3);                                                                         \
	sideBarSizeY = (Uint16)(GRID_SIZE / 4);                                                                         \
	sidebarSmallPosX = (Uint16)(GRID_POS_X - SIDEBAR_SIZE_X - (GRID_SIZE / 12));                                    \
	sidebarSmall1PosY = (Uint16)(GRID_POS_Y + (GRID_SIZE / 16));                                                    \
	sidebarSmall2PosY = (Uint16)(GRID_POS_Y + SIDEBAR_SMALL_SIZE_Y + (GRID_SIZE / 8));                              \
	sidebarSmall3PosY = (Uint16)(GRID_POS_Y + (2 * SIDEBAR_SMALL_SIZE_Y) + (GRID_SIZE * 3 / 16));                   \
	gridStartingPosX[0] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((0 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[1] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((1 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[2] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((2 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[3] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((3 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[4] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((4 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[5] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((5 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[6] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((6 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[7] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((7 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosX[8] = (Uint16)((GRID_POS_X + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((8 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[0] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((0 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[1] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((1 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[2] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((2 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[3] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((3 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[4] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((4 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[5] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((5 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[6] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((6 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[7] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((7 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	gridStartingPosY[8] = (Uint16)((GRID_POS_Y + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((8 / 3) * (GRID_SIZE_C - GRID_SIZE_B))); \
	INIT_NUM_OFFSETS();

#if !defined(ANDROID)
#define SYSTEM_WIDTH  DM.w
#define SYSTEM_HEIGHT DM.h
#else
#define SYSTEM_WIDTH  max(DM.w, DM.h)
#define SYSTEM_HEIGHT min(DM.w, DM.h)
#endif
#define GAME_WIDTH_MULT       (gameWidthMult)
#define GAME_HEIGHT_MULT      (gameHeightMult)
#if defined(WII_U)
#define DEFAULT_WIDTH         1280
#define DEFAULT_HEIGHT        720
#define DEFAULT_RI            5
#define DEFAULT_ARI           1
#elif defined(VITA)
#define DEFAULT_WIDTH         960
#define DEFAULT_HEIGHT        544
#define DEFAULT_RI            3
#define DEFAULT_ARI           1
#elif defined(SWITCH)
#define DEFAULT_WIDTH         1920
#define DEFAULT_HEIGHT        1080
#define DEFAULT_RI            8
#define DEFAULT_ARI           1
#elif defined(PSP)
#define DEFAULT_WIDTH         480
#define DEFAULT_HEIGHT        272
#define DEFAULT_RI            1
#define DEFAULT_ARI           1
#elif defined(ANDROID)
#define DEFAULT_WIDTH         SYSTEM_WIDTH
#define DEFAULT_HEIGHT        SYSTEM_HEIGHT
#define DEFAULT_RI            0
#define DEFAULT_ARI           0
#else
#define DEFAULT_WIDTH         640
#define DEFAULT_HEIGHT        480
#define DEFAULT_RI            2
#define DEFAULT_ARI           0
#endif
#define DEFAULT_BG_SCALE      (defaultBGScale)

// the grid is a square; these sizes represent both X and Y dimensions
#define GRID_SIZE_A           (gridSizeA) // length of 1/3 of a cell (one mini-cell)
#define GRID_SIZE_B           (gridSizeB) // length of divider between cells in the same group of three rows/columns
#define GRID_SIZE_C           (gridSizeC) // length of divider between groups of three rows/columns
#define GRID_SIZE_D           (gridSizeD) // length of grid border
#define GRID_SIZE             (gridSize)
#define GRID_SIZE_A3          (gridSizeA3)
#define GRID_POS_X            (gridPosX)
#define GRID_POS_Y            (gridPosY)
#define SIDEBAR_SIZE_X        (sideBarSizeX)
#define SIDEBAR_SMALL_SIZE_Y  (sideBarSizeY)
#define SIDEBAR_SMALL_POS_X   (sidebarSmallPosX)
#define SIDEBAR_SMALL_1_POS_Y (sidebarSmall1PosY)
#define SIDEBAR_SMALL_2_POS_Y (sidebarSmall2PosY)
#define SIDEBAR_SMALL_3_POS_Y (sidebarSmall3PosY)
// #define TIMER_POSITION_X   (SIDEBAR_SMALL_POS_X + (SIDEBAR_SIZE_X / 8))
// #define TIMER_POSITION_Y   (SIDEBAR_SMALL_1_POS_Y + (SIDEBAR_SIZE_Y * 3 / 16))
#define GRID_STARTING_POS_X   (gridStartingPosX[0])
#define GRID_STARTING_POS_Y   (gridStartingPosY[0])
#define GRID_X_AT_COL(index)  (gridStartingPosX[index])
#define GRID_Y_AT_ROW(index)  (gridStartingPosY[index])
#if defined(VITA)
//const Sint8 numOffset_large_x[9] = { 2,2,2,2,2,2,2,2,2 };
//const Sint8 numOffset_large_y[9] = { 1,1,0,1,1,0,0,0,1 };
//const Sint8 numOffset_small_x[9] = { 0,0,0,0,0,0,0,0,0 };
//const Sint8 numOffset_small_y[9] = { -1,0,-1,0,-1,-1,-1,-1,-1 };
#define INIT_NUM_OFFSETS()                                                                                                                                       \
	d = (double)gameHeight / SCALING_HEIGHT;                                                                                                                     \
	const Sint8 numOffset_large_x[9] = { (Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d),(Sint8)(2*d) }; \
	const Sint8 numOffset_large_y[9] = { (Sint8)(d),(Sint8)(d),0,(Sint8)(d),(Sint8)(d),0,0,0,(Sint8)(d) };                                                       \
	const Sint8 numOffset_small_x[9] = { 0,0,0,0,0,0,0,0,0 };                                                                                                    \
	Sint8 numOffset_small_y[9] = { (Sint8)(-d),0,(Sint8)(-d),0,(Sint8)(-d),(Sint8)(-d),(Sint8)(-d),(Sint8)(-d),(Sint8)(-d) };                                    \
	if (gameHeight <= 240) {                                                                                                                                     \
		for (i = 0; i < 9; i++) numOffset_small_y[i] -= 1;                                                                                                       \
	}
#elif defined(PSP)
//const Sint8 numOffset_large_x[9] = { 1,1,1,1,1,1,1,1,1 };
//const Sint8 numOffset_large_y[9] = { 0,0,-1,0,0,-1,-1,0,-1 };
//const Sint8 numOffset_small_x[9] = { 1,1,1,1,1,1,1,1,1 };
//const Sint8 numOffset_small_y[9] = { 1,1,0,1,1,0,1,1,0 };
#define INIT_NUM_OFFSETS()                                                                                                                     \
	d = (double)gameHeight / SCALING_HEIGHT;                                                                                                   \
	const Sint8 numOffset_large_x[9] = { (Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d) }; \
	const Sint8 numOffset_large_y[9] = { 0,0,(Sint8)(-d),0,0,(Sint8)(-d),(Sint8)(-d),0,(Sint8)(-d) };                                          \
	const Sint8 numOffset_small_x[9] = { (Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d),(Sint8)(d) }; \
	const Sint8 numOffset_small_y[9] = { (Sint8)(d),(Sint8)(d),0,(Sint8)(d),(Sint8)(d),0,(Sint8)(d),(Sint8)(d),0 };
#else
#define INIT_NUM_OFFSETS()                                    \
	const Sint8 numOffset_large_x[9] = { 0,0,0,0,0,0,0,0,0 }; \
	const Sint8 numOffset_large_y[9] = { 0,0,0,0,0,0,0,0,0 }; \
	const Sint8 numOffset_small_x[9] = { 0,0,0,0,0,0,0,0,0 }; \
	const Sint8 numOffset_small_y[9] = { 0,0,0,0,0,0,0,0,0 };
#endif

#define MENU_CURSOR_X_OFFSET ((menuCursor.rect.w * 2.5) + SIN_WAVE(timer_global.now, 0.5, TEXT_STANDARD_AMPLITUDE))

#define UPDATE_GLOBAL_TIMER()             \
    timer_global.last = timer_global.now; \
    timer_global.now = (SDL_GetTicks() - timer_paused.now) / 1000.0;

#define PREPARE_PAUSE_TIMER() \
	timer_paused.last = SDL_GetTicks();

#define UPDATE_PAUSE_TIMER() \
	timer_paused.now += (SDL_GetTicks() - timer_paused.last);

#define KEY_PRESSED(key) \
    (keyInputs & key)

#define BUTTON_HELD(button) \
	(heldButtons & button)

#define INIT_MENU_OPTION_POSITIONS(textObj)                                \
    textObj.startPos_x         = textObj.rect.x;                           \
    textObj.startPos_y         = textObj.rect.y;                           \
    textObj.endPos_x           = textObj.startPos_x + (gameWidth * 3 / 4); \
    textObj.endPos_y           = textObj.startPos_y - (gameWidth * 3 / 4);

#if defined(VITA)
#define SETTINGS_FILE "ux0:data/SuDokuL/settings.bin"
#else
#define SETTINGS_FILE "settings.bin"
#endif

extern void loadSettingsFile();

extern void initializeSettingsFileWithSettings(Sint8, Sint8, Sint8, Sint8, Sint16, Sint16, Sint8, Sint8, Sint8, Sint8, Sint8, Sint8);

#define SAVE_CURRENT_SETTINGS()                                                                                                 \
	initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen,               \
		videoSettings.resolutionIndex, videoSettings.aspectRatioIndex, videoSettings.widthSetting, videoSettings.heightSetting, \
		soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume,                                             \
		bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale);

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP)
#define SDL_TOGGLE_FULLSCREEN()
#else
#define SDL_TOGGLE_FULLSCREEN()                                 \
	isWindowed = !isWindowed;                                   \
	if (isWindowed)                                             \
		SDL_SetWindowFullscreen(window, 0);                     \
	else                                                        \
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); \
	SET_SCALING();
#endif

#define SDL_TOGGLE_INTEGER_SCALE()    \
	isIntegerScale = !isIntegerScale; \
	SET_SCALING();

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP)
#define SCALING_WIDTH DEFAULT_WIDTH
#define SCALING_HEIGHT DEFAULT_HEIGHT
#else
#define SCALING_WIDTH SDL_GetWindowSurface(window)->w
#define SCALING_HEIGHT SDL_GetWindowSurface(window)->h
#endif

#if defined(ANDROID)
#define SET_SCALING()
#else
#define SET_SCALING()                                                                            \
	if (isIntegerScale) {                                                                        \
		int_i = min((int)(SCALING_WIDTH / gameWidth), (int)(SCALING_HEIGHT / gameHeight));       \
		if (int_i < 1) int_i = 1;                                                                \
		centerViewport.w = gameWidth * int_i;                                                    \
		centerViewport.h = gameHeight * int_i;                                                   \
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / int_i), 0);        \
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / int_i), 0);       \
		SDL_RenderSetScale(renderer, int_i, int_i);                                              \
		SDL_RenderSetViewport(renderer, &centerViewport);                                        \
		screenScale = (double)int_i;                                                             \
	} else {                                                                                     \
		screenScale = (double)SCALING_WIDTH / gameWidth;                                         \
		if ((double)SCALING_HEIGHT / gameHeight < screenScale) {                                 \
			screenScale = (double)SCALING_HEIGHT / gameHeight;                                   \
		}                                                                                        \
		if (screenScale < 1) screenScale = 1;                                                    \
		centerViewport.w = (int)(gameWidth * screenScale);                                       \
		centerViewport.h = (int)(gameHeight * screenScale);                                      \
		centerViewport.x = max((int)((SCALING_WIDTH - centerViewport.w) / 2 / screenScale), 0);  \
		centerViewport.y = max((int)((SCALING_HEIGHT - centerViewport.h) / 2 / screenScale), 0); \
		SDL_RenderSetScale(renderer, screenScale, screenScale);                                  \
		SDL_RenderSetViewport(renderer, &centerViewport);                                        \
	}                                                                                            \
	UPDATE_BORDER_RECTS();
	//SDL_RenderSetClipRect(renderer, &centerViewport);
#endif

#define UPDATE_BORDER_RECTS()                             \
	topRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 50;    \
	topRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 100; \
	topRect.w = SCALING_WIDTH + 100;                      \
	topRect.h = (SCALING_HEIGHT - gameHeight) / 2 + 100;  \
	bottomRect.x = topRect.x;                             \
	bottomRect.y = gameHeight;                            \
	bottomRect.w = topRect.w;                             \
	bottomRect.h = topRect.h;                             \
	leftRect.x = -(SCALING_WIDTH - gameWidth) / 2 - 100;  \
	leftRect.y = -(SCALING_HEIGHT - gameHeight) / 2 - 50; \
	leftRect.w = (SCALING_WIDTH - gameWidth) / 2 + 100;   \
	leftRect.h = SCALING_HEIGHT + 100;                    \
	rightRect.x = gameWidth;                              \
	rightRect.y = leftRect.y;                             \
	rightRect.w = leftRect.w;                             \
	rightRect.h = leftRect.h;

#define RENDER_BORDER_RECTS()                  \
	SDL_RenderFillRect(renderer, &topRect);    \
	SDL_RenderFillRect(renderer, &bottomRect); \
	SDL_RenderFillRect(renderer, &leftRect);   \
	SDL_RenderFillRect(renderer, &rightRect);

#define SDL_DESTROY_ALL()                                \
	/* Destroy Everything */                             \
	/* Textures */                                       \
	SDL_DestroyTexture(tile.texture);                    \
	SDL_DestroyTexture(logo.texture);                    \
	SDL_DestroyTexture(menuCursor.texture);              \
	SDL_DestroyTexture(game_grid.texture);               \
	SDL_DestroyTexture(gridCursor_bottom_left.texture);  \
	SDL_DestroyTexture(gridCursor_bottom_right.texture); \
	SDL_DestroyTexture(gridCursor_top_left.texture);     \
	SDL_DestroyTexture(gridCursor_top_right.texture);    \
	SDL_DestroyTexture(game_sidebar_small.texture);      \
	SDL_DestroyTexture(miniGrid_bottom_left.texture);    \
	SDL_DestroyTexture(miniGrid_bottom_right.texture);   \
	SDL_DestroyTexture(miniGrid_top_left.texture);       \
	SDL_DestroyTexture(miniGrid_top_right.texture);      \
	/* Text Objects */                                   \
	for (i = 32; i < LEN(textChars); i++) {              \
		DESTROY_TEXT_OBJECT_TEXTURE(textChars[i]);       \
	}                                                    \
	for (i = 0; i < 10; i++) {                           \
		DESTROY_TEXT_OBJECT_TEXTURE(gridNums_black[i]);  \
		DESTROY_TEXT_OBJECT_TEXTURE(gridNums_blue[i]);   \
	}                                                    \
	/* Fonts */                                          \
	TTF_CloseFont(pixelFont);                            \
	TTF_CloseFont(pixelFont_grid);                       \
	TTF_CloseFont(pixelFont_grid_mini);                  \
	TTF_Quit();                                          \
	/* Sound */                                          \
	Mix_HaltMusic();                                     \
	Mix_FreeMusic(bgm_1);                                \
	Mix_FreeMusic(bgm_2);                                \
	Mix_FreeMusic(bgm_3);                                \
	Mix_FreeMusic(bgm_4);                                \
	Mix_FreeMusic(bgm_5);                                \
	Mix_FreeMusic(bgm_6);                                \
	Mix_FreeMusic(bgm_7);                                \
	Mix_FreeChunk(sfx);                                  \
	Mix_CloseAudio();                                    \
	Mix_Quit();                                          \
	/* Controller */                                     \
	CLOSE_CONTROLLER();                                  \
	/* Renderer and Window */                            \
	SDL_DestroyRenderer(renderer);                       \
	SDL_DestroyWindow(window);                           \
	SDL_Quit();

#if defined(PSP)
#define CLOSE_CONTROLLER() SDL_JoystickClose(controller);
#else
#define CLOSE_CONTROLLER()                   \
	if (controller != NULL) {                \
		SDL_GameControllerClose(controller); \
	}
#endif

#if defined(WII_U)
#define SYSTEM_SPECIFIC_CLOSE() WHBUnmountSdCard();
#elif defined(VITA)
#define SYSTEM_SPECIFIC_CLOSE() sceKernelExitProcess(0);
#elif defined(PSP)
#define SYSTEM_SPECIFIC_CLOSE() sceKernelExitGame();
#else
#define SYSTEM_SPECIFIC_CLOSE()
#endif

#endif