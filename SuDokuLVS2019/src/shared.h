#include "include.h"

#ifndef SHARED_H
#define SHARED_H

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

extern Uint16 gameWidth;
extern Uint16 gameHeight;

#define INIT_STARTING_WIDTH_HEIGHT_MULTS()              \
	const double gameWidthMult = (gameWidth / 640.0);   \
	const double gameHeightMult = (gameHeight / 480.0); \

#define INIT_STARTING_SHARED_VARIABLES()                                                                                         \
	const double gridSizeA = (12 * GAME_HEIGHT_MULT);                                                                            \
	const double gridSizeB = (4 * GAME_HEIGHT_MULT);                                                                             \
	const double gridSizeC = (6 * GAME_HEIGHT_MULT);                                                                             \
	const double gridSizeD = (12 * GAME_HEIGHT_MULT);                                                                            \
	const double gridSize = (27 * GRID_SIZE_A + 6 * GRID_SIZE_B + 2 * GRID_SIZE_C + 2 * GRID_SIZE_D);                            \
	const double gridSizeA3 = (3 * GRID_SIZE_A);                                                                                 \
	const Uint16 gridPosX = (Uint16)((gameWidth / 2) - (GRID_SIZE / 2) + (GRID_SIZE * 5 / 24));                                  \
	const Uint16 gridPosY = (Uint16)((gameHeight - GRID_SIZE) / 2);                                                              \
	const Uint16 sideBarSizeX = (Uint16)(GRID_SIZE / 3);                                                                         \
	const Uint16 sideBarSizeY = (Uint16)(GRID_SIZE / 4);                                                                         \
	const Uint16 sidebarSmallPosX = (Uint16)(GRID_POS_X - SIDEBAR_SIZE_X - (GRID_SIZE / 12));                                    \
	const Uint16 sidebarSmall1PosY = (Uint16)(GRID_POS_Y + (GRID_SIZE / 16));                                                    \
	const Uint16 sidebarSmall2PosY = (Uint16)(GRID_POS_Y + SIDEBAR_SMALL_SIZE_Y + (GRID_SIZE / 8));                              \
	const Uint16 sidebarSmall3PosY = (Uint16)(GRID_POS_Y + (2 * SIDEBAR_SMALL_SIZE_Y) + (GRID_SIZE * 3 / 16));                   \
	const Uint16 gridStartingPosX[9] = {                                                                                         \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((0 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((1 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((2 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((3 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((4 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((5 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((6 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((7 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_X + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((8 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
	};                                                                                                                           \
	const Uint16 gridStartingPosY[9] = {                                                                                         \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (0 * GRID_SIZE_A3) + (0 * GRID_SIZE_B) + ((0 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (1 * GRID_SIZE_A3) + (1 * GRID_SIZE_B) + ((1 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (2 * GRID_SIZE_A3) + (2 * GRID_SIZE_B) + ((2 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (3 * GRID_SIZE_A3) + (3 * GRID_SIZE_B) + ((3 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (4 * GRID_SIZE_A3) + (4 * GRID_SIZE_B) + ((4 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (5 * GRID_SIZE_A3) + (5 * GRID_SIZE_B) + ((5 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (6 * GRID_SIZE_A3) + (6 * GRID_SIZE_B) + ((6 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (7 * GRID_SIZE_A3) + (7 * GRID_SIZE_B) + ((7 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
		(Uint16)((GRID_POS_Y + GRID_SIZE_D) + (8 * GRID_SIZE_A3) + (8 * GRID_SIZE_B) + ((8 / 3) * (GRID_SIZE_C - GRID_SIZE_B))), \
	};

#define GAME_WIDTH_MULT       (gameWidthMult)
#define GAME_HEIGHT_MULT      (gameHeightMult)
#ifdef WII_U
#define DEFAULT_WIDTH         1280
#define DEFAULT_HEIGHT        720
#define DEFAULT_RI            4
#define DEFAULT_ARI           1
#else
#define DEFAULT_WIDTH         640
#define DEFAULT_HEIGHT        480
#define DEFAULT_RI            1
#define DEFAULT_ARI           0
#endif
#define DEFAULT_BG_SCALE      (max(DEFAULT_WIDTH / 640, DEFAULT_HEIGHT / 480))

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

#define MENU_CURSOR_X_OFFSET ((menuCursor.rect.w * 2.5) + SIN_WAVE(timer_global.now, 0.5, TEXT_STANDARD_AMPLITUDE))

#define UPDATE_TIMER(timer) \
    timer.last = timer.now; \
    timer.now = SDL_GetTicks() / 1000.0;

#define KEY_PRESSED(key) \
    (keyInputs & key)

#define BUTTON_HELD(button) \
	(heldButtons & button)

#define INIT_MENU_OPTION_POSITIONS(textObj)                                \
    textObj.startPos_x         = textObj.rect.x;                           \
    textObj.startPos_y         = textObj.rect.y;                           \
    textObj.endPos_x           = textObj.startPos_x + (gameWidth * 3 / 4); \
    textObj.endPos_y           = textObj.startPos_y - (gameWidth * 3 / 4);

#define LOAD_SETTINGS_FILE()                                                                                                                   \
	settingsFile = SDL_RWFromFile("settings.bin", "rb");                                                                                       \
	if (settingsFile == NULL) {                                                                                                                \
		INITIALIZE_SETTINGS_FILE_WITH_SETTINGS(DEFAULT_RI, DEFAULT_ARI, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 90, 50, 15, 22, DEFAULT_BG_SCALE);   \
	} else {                                                                                                                                   \
		SDL_RWread(settingsFile, &videoSettings, sizeof(VideoSettings), 1);                                                                    \
		SDL_RWread(settingsFile, &soundSettings, sizeof(SoundSettings), 1);                                                                    \
		SDL_RWread(settingsFile, &bgSettings, sizeof(BackgroundSettings), 1);                                                                  \
		SDL_RWclose(settingsFile);                                                                                                             \
	}

#define INITIALIZE_SETTINGS_FILE_WITH_SETTINGS(ri, ari, gw, gh, mi, bgmv, sfxv, sm, sd, s) \
    settingsFile = SDL_RWFromFile("settings.bin", "w+b");                                  \
    if (settingsFile != NULL) {                                                            \
		videoSettings.resolutionIndex = ri;                                                \
		videoSettings.aspectRatioIndex = ari;                                              \
        videoSettings.widthSetting = gw;                                                   \
        videoSettings.heightSetting = gh;                                                  \
		soundSettings.musicIndex = mi;                                                     \
		soundSettings.bgmVolume = bgmv;                                                    \
		soundSettings.sfxVolume = sfxv;                                                    \
		bgSettings.speedMult = sm;                                                         \
		bgSettings.scrollDir = sd;                                                         \
		bgSettings.scale = s;                                                              \
		SDL_RWwrite(settingsFile, &videoSettings.resolutionIndex, sizeof(Uint8), 1);       \
		SDL_RWwrite(settingsFile, &videoSettings.aspectRatioIndex, sizeof(Uint8), 1);      \
        SDL_RWwrite(settingsFile, &videoSettings.widthSetting, sizeof(Uint16), 1);         \
        SDL_RWwrite(settingsFile, &videoSettings.heightSetting, sizeof(Uint16), 1);        \
		SDL_RWwrite(settingsFile, &soundSettings.musicIndex, sizeof(Sint8), 1);            \
		SDL_RWwrite(settingsFile, &soundSettings.bgmVolume, sizeof(Sint8), 1);             \
		SDL_RWwrite(settingsFile, &soundSettings.sfxVolume, sizeof(Sint8), 1);             \
		SDL_RWwrite(settingsFile, &bgSettings.speedMult, sizeof(Sint8), 1);                \
		SDL_RWwrite(settingsFile, &bgSettings.scrollDir, sizeof(Sint8), 1);                \
		SDL_RWwrite(settingsFile, &bgSettings.scale, sizeof(Sint8), 1);                    \
        SDL_RWclose(settingsFile);                                                         \
    }

#define SAVE_CURRENT_SETTINGS() \
	INITIALIZE_SETTINGS_FILE_WITH_SETTINGS(videoSettings.resolutionIndex, videoSettings.aspectRatioIndex, videoSettings.widthSetting, videoSettings.heightSetting, \
	soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale);

#define SDL_TOGGLE_FULLSCREEN()                                 \
	if (isWindowed)                                             \
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); \
	else                                                        \
		SDL_SetWindowFullscreen(window, 0);                     \
	isWindowed = !isWindowed;
	//SDL_ShowCursor(isWindowed);

#define SDL_DESTROY_ALL()                                \
	/* Destroy Everything and Quit Game */               \
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
	Mix_FreeMusic(bgm);                                  \
	Mix_FreeChunk(sfx);                                  \
	Mix_CloseAudio();                                    \
	Mix_Quit();                                          \
	/* Controller */                                     \
	if (controller != NULL) {                            \
		SDL_GameControllerClose(controller);             \
	}                                                    \
	/* Renderer and Window */                            \
	SDL_DestroyRenderer(renderer);                       \
	SDL_DestroyWindow(window);                           \
	SDL_Quit();                                          \
	/* [Wii U] SD Card */                                \
	UNMOUNT_SD_CARD();

#ifdef WII_U
#define UNMOUNT_SD_CARD() WHBUnmountSdCard();
#else
#define UNMOUNT_SD_CARD()
#endif

#endif