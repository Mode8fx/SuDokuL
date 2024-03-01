#include "include.h"
#include "text_objects.h"

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
extern Sint8 numOffset_large_x[9];
extern Sint8 numOffset_large_y[9];
extern Sint8 numOffset_small_x[9];
extern Sint8 numOffset_small_y[9];

/* Settings */
extern SDL_RWops *settingsFile;
extern BackgroundSettings bgSettings;
extern BGScroll bgScroll;
extern ControlSettings controlSettings;
extern VideoSettings videoSettings;
extern SoundSettings soundSettings;

/* Window Width and Height */
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[14] = { 320,  362,  640,  725,  768,  800,  960, 1024, 1152, 1280, 1440, 1600, 1920, 2880 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[14] = { 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[12] = { 426,  480,  853,  960, 1176, 1280, 1360, 1600, 1920, 2560, 3620, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[12] = { 240,  272,  480,  544,  664,  720,  768,  900, 1080, 1440, 2036, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[10] = { 435,  720, 1152, 1280, 1440, 1600, 1680, 1920, 2560, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[10] = { 272,  480,  720,  800,  900, 1024, 1050, 1200, 1600, 2400 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[6] = { 480,  960, 1280, 2560, 3440, 5120 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[6] = { 205,  410,  548, 1080, 1440, 2160 };
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

/* Time */
extern double deltaTime;
extern Timer timer_global;
extern double time_anim1;
extern double time_anim_PressStart;
extern Timer timer_game;
extern double timer_buttonHold;
extern double timer_buttonHold_repeater;
extern Timer timer_paused;

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
#define GRID_STARTING_POS_X   (gridStartingPosX[0])
#define GRID_STARTING_POS_Y   (gridStartingPosY[0])
#define GRID_X_AT_COL(index)  (gridStartingPosX[index])
#define GRID_Y_AT_ROW(index)  (gridStartingPosY[index])

#if defined(VITA)
const string rootDir = "ux0:data/SuDokuL/";
#else
const string rootDir = "";
#endif
#define SETTINGS_FILE (rootDir + "settings.bin").c_str()

extern void initDefaultBGScale();
extern void initStartingWidthHeightMults();
extern void initStartingSharedVariables();
extern void initNumOffsets();
extern void updateGlobalTimer();
extern void preparePauseTimer();
extern void updatePauseTimer();
extern void initMenuOptionPositions(TextObject *);
extern void loadSettingsFile();
extern void initializeSettingsFileWithSettings(Sint8, Sint8, Sint8, Sint8, Sint16, Sint16, Sint8, Sint8, Sint8, Sint8, Sint8, Sint8);
extern void saveCurrentSettings();
extern void setResolutionByOptions(const Uint16 *, const Uint16 *, Uint8, Sint8);
extern void setAspectRatioByOptions(Sint8);
extern Uint16 menuCursorXOffset();
extern void sdlToggleFullscreen();
extern void sdlToggleIntegerScale();
extern void setScaling();
extern void updateBorderRects();
extern void renderBorderRects();
extern void sdlDestroyAll();
extern void closeController();
extern void systemSpecificClose();

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP)
#define SCALING_WIDTH DEFAULT_WIDTH
#define SCALING_HEIGHT DEFAULT_HEIGHT
#else
#define SCALING_WIDTH SDL_GetWindowSurface(window)->w
#define SCALING_HEIGHT SDL_GetWindowSurface(window)->h
#endif

#endif