#include "include.h"
#include "text_objects.h"

#ifndef SHARED_H
#define SHARED_H

#if defined(SDL1) && !(defined(LINUX) || defined(THREEDS))
extern FILE _iob[];

extern "C" FILE * __cdecl __iob_func(void);
#endif

#if defined(WII)
#define wiimoteScheme enableTouchscreen
#endif

struct ControlSettings {
	bool swapConfirmAndBack;
#if defined(WII)
	Sint8 enableTouchscreen;
#else
	bool enableTouchscreen;
#endif
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
	Sint8 type; // Background Type
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
extern bool compactDisplay;
extern Uint8 defaultBGScale;
#if !defined(SDL1)
extern SDL_DisplayMode DM;
#endif
extern double gameWidthMult;
extern double gameHeightMult;

/* Grid-Related Variables */
extern double gridSizeA;
extern double gridSizeB;
extern double gridSizeC;
extern double gridSizeD;
extern double gridSize;
extern double gridSizeA3;
extern Sint16 gridPosX;
extern Sint16 gridPosY;
extern Sint16 gridStartingPosX[9];
extern Sint16 gridStartingPosY[9];
extern Sint8 numOffset_large_x[9];
extern Sint8 numOffset_large_y[9];
extern Sint8 numOffset_small_x[9];
extern Sint8 numOffset_small_y[9];

/* Settings */
extern SDL_RWops *settingsFile;
extern SDL_RWops *saveFile;
extern BackgroundSettings bgSettings;
extern BGScroll bgScroll;
extern ControlSettings controlSettings;
extern VideoSettings videoSettings;
extern SoundSettings soundSettings;

/* Window Width and Height */
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[15] =    { 0, 320,  362,  640,  725,  768,  800,  960, 1024, 1152, 1280, 1440, 1600, 1920, 2880 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[15] =   { 0, 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[14] =   { 0, 426,  480,  640,  854,  960, 1176, 1280, 1360, 1600, 1920, 2560, 3620, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[14] =  { 0, 240,  272,  360,  480,  544,  664,  720,  768,  900, 1080, 1440, 2036, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[12] =  { 0, 435,  640,  720, 1152, 1280, 1440, 1600, 1680, 1920, 2560, 3456 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[12] = { 0, 272,  400,  480,  720,  800,  900, 1024, 1050, 1200, 1600, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_1_1[15] =    { 0, 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_1_1[15] =   { 0, 240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
extern SDL_Rect centerViewport;

/* Sound */
extern Mix_Music *bgm_1;
extern Mix_Music *bgm_2;
extern Mix_Music *bgm_3;
extern Mix_Music *bgm_4;
extern Mix_Music *bgm_5;
extern Mix_Music *bgm_6;
extern Mix_Music *bgm_7;
extern Mix_Music *bgm_8;
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
extern bool canContinue;
extern bool gameCompleted;

#if defined(ANDROID)
#define SYSTEM_WIDTH  max(DM.w, DM.h)
#define SYSTEM_HEIGHT min(DM.w, DM.h)
#elif defined(FUNKEY)
#define SYSTEM_WIDTH  240
#define SYSTEM_HEIGHT 240
#elif defined(THREEDS)
#define SYSTEM_WIDTH  400
#define SYSTEM_HEIGHT 240
#elif defined(SDL1)
#define SYSTEM_WIDTH  640
#define SYSTEM_HEIGHT 480
#else
#define SYSTEM_WIDTH  DM.w
#define SYSTEM_HEIGHT DM.h
#endif
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(ANDROID) || defined(WII) || defined(GAMECUBE) || defined(FUNKEY) || defined(THREEDS)
#define DEFAULT_WIDTH         SYSTEM_WIDTH
#define DEFAULT_HEIGHT        SYSTEM_HEIGHT
#define DEFAULT_RI            0
#define DEFAULT_ARI           0
#else
#define DEFAULT_WIDTH         640
#define DEFAULT_HEIGHT        480
#define DEFAULT_RI            3
#define DEFAULT_ARI           1
#endif

// the grid is a square; these sizes represent both X and Y dimensions
#define SIDEBAR_SMALL_SIZE_X  (gridSize / 3)
#define SIDEBAR_SMALL_SIZE_Y  (gridSize / 4)
#define GRID_STARTING_POS_X   (gridStartingPosX[0])
#define GRID_STARTING_POS_Y   (gridStartingPosY[0])
#define GRID_X_AT_COL(index)  (gridStartingPosX[index])
#define GRID_Y_AT_ROW(index)  (gridStartingPosY[index])

#if defined(VITA)
const string rootDir = "ux0:data/SuDokuL/";
#elif defined(WII)
const string rootDir = "sd:/apps/SuDokuL/";
#elif defined(GAMECUBE)
const string rootDir = "/SuDokuL/";
#elif defined(THREEDS)
const string rootDir = "sdmc:/3ds/SuDokuL/";
#elif defined(FUNKEY)
const string rootDir = "/mnt/FunKey/.sudokul/";
#elif defined(LINUX)
const string rootDir = ("%s/.sudokul", getenv("HOME"));
#else
const string rootDir = "";
#endif
#define SETTINGS_FILE (rootDir + "settings.bin").c_str()
#define SAVE_FILE (rootDir + "save.bin").c_str()

extern void loadSettingsFile();
extern void initializeSettingsFileWithSettings(Sint8, Sint8, Sint8, Sint8, Sint16, Sint16, Sint8, Sint8, Sint8, Sint8, Sint8, Sint8, Sint8);
extern void loadSavedPuzzle();
extern void savePuzzle();
extern void initDefaultBGScale();
extern void initStartingWidthHeightMults();
extern void initStartingSharedVariables();
extern void initNumOffsets();
extern void updateGlobalTimer();
extern void preparePauseTimer();
extern void updatePauseTimer();
extern void initMenuOptionPositions(TextObject *);
extern void saveCurrentSettings();
extern void setNativeResolution();
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

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(FUNKEY) || defined(LINUX)
#define SCALING_WIDTH DEFAULT_WIDTH
#define SCALING_HEIGHT DEFAULT_HEIGHT
#elif defined(SDL1)
#define SCALING_WIDTH SDL_GetVideoInfo()->current_w
#define SCALING_HEIGHT SDL_GetVideoInfo()->current_h
#else
#define SCALING_WIDTH SDL_GetWindowSurface(window)->w
#define SCALING_HEIGHT SDL_GetWindowSurface(window)->h
#endif

#define INIT_DEBUG() SDL_RWops *debugFile;

#define MAKE_DEBUG_FILE(name, body)                            \
	debugFile = SDL_RWFromFile((rootDir + name).c_str(), "w+b"); \
	SDL_RWwrite(debugFile, body, sizeof(body), 1);               \
	SDL_RWclose(debugFile);

#endif