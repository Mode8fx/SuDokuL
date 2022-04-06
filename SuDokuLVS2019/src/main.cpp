#include "include.h"
#include "config.h"
#include "game_logic.h"
#include "general.h"
#include "menu_logic.h"
#include "shared.h"
#include "sound_logic.h"
#include "sprite_objects.h"
#include "text_objects.h"
#include "transitions.h"
#include "sudokuGen.h"
#include "puzzleBank.h"

/* SDL Window */
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

/* SDL Rectangles */
SDL_Rect rightRect;
SDL_Rect bottomRect;
SDL_Rect divider;

/* SDL Settings File */
SDL_RWops *settingsFile;

/* SDL Controller */
#if defined(PSP)
SDL_Joystick *controller = NULL;
#else
SDL_GameController *controller = nullptr;
#endif

/* Window Width and Height */
Uint16 gameWidth = 640;
Uint16 gameHeight = 480;
SDL_DisplayMode DM;
#if defined(WII_U)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[5]   =  {  320, 640, 720,  800,  960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[5]  =  {  240, 480, 576,  600,  720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[5]  =  {  480, 854, 960, 1176, 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[5] =  {  272, 480, 544,  664,  720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[2] =  {  720, 1152 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[2] = {  480, 720 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[1] =   { 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[1] =  {  548 };
#elif defined(VITA)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[3]    = { 320, 640, 726 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[3]   = { 240, 480, 544 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[3]   = { 480, 854, 960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[3]  = { 272, 480, 544 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[1]  = { 720 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[1] = { 480 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[1]   = { 960 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[1]  = { 410 };
#elif defined(SWITCH)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[9]    = {  320,  640,  720,  800,  960, 1024, 1152, 1280, 1440 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[9]   = {  240,  480,  576,  600,  720,  768,  864,  960, 1080 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[8]  = {  480,  854,  960, 1176, 1280, 1360, 1600, 1920 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[8] = {  272,  480,  544,  664,  720,  768,  900, 1080 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[6]  = {  720, 1152, 1280, 1440, 1600, 1680 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[6] = {  480,  720,  800,  900, 1024, 1050 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[1]   = { 1280 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[1]  = {  548 };
#elif defined(PSP)
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[2] = { 320, 362 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[2] = { 240, 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[2] = { 426, 480 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[2] = { 240, 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[1] = { 435 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[1] = { 272 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[1] = { 480 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[1] = { 205 };
#else
const Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[12]   = {  320,  640,  720,  800,  960, 1024, 1152, 1280, 1440, 1600, 1920, 2880 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[12]  = {  240,  480,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[10]  = {  480,  854,  960, 1176, 1280, 1360, 1600, 1920, 2560, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[10] = {  272,  480,  544,  664,  720,  768,  900, 1080, 1440, 2160 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[9]  = {  720, 1152, 1280, 1440, 1600, 1680, 1920, 2560, 3840 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[9] = {  480,  720,  800,  900, 1024, 1050, 1200, 1600, 2400 };
const Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[4]   = { 1280, 2560, 3440, 5120 };
const Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[4]  = {  548, 1080, 1440, 2160 };
#endif
VideoSettings videoSettings;
SDL_Rect centerViewport;

/* Sound */
Mix_Music *bgm;
Mix_Chunk *sfx;
SoundSettings soundSettings;

/* Keyboard State */
const Uint8 *keyState = SDL_GetKeyboardState(NULL); // scancodes

/* Textures */
SpriteObject tile;
SpriteObjectWithPos logo;
SpriteObjectWithPos menuCursor;
SpriteObject game_grid;
//SpriteObjectWithPos gridCursor;
SpriteObjectWithPos gridCursor_bottom_left;
SpriteObjectWithPos gridCursor_bottom_right;
SpriteObjectWithPos gridCursor_top_left;
SpriteObjectWithPos gridCursor_top_right;
SpriteObject game_sidebar_small;

SpriteObjectWithPos miniGrid_bottom_left;
SpriteObjectWithPos miniGrid_bottom_right;
SpriteObjectWithPos miniGrid_top_left;
SpriteObjectWithPos miniGrid_top_right;
SpriteObjectWithPos *currMiniGrid;

/* Fonts */
SDL_Color color_black = {0, 0, 0};
SDL_Color color_white = {255, 255, 255};
SDL_Color color_blue = {0, 0, 192};
SDL_Color color_gray_240 = {240, 240, 240};
SDL_Color color_light_blue = {240, 240, 255};
TTF_Font *pixelFont;
TTF_Font *pixelFont_large;
TTF_Font *pixelFont_grid;
TTF_Font *pixelFont_grid_mini;

/* Text Objects */
/* General - Numbers */
TextCharObject gridNums_black[10];
TextCharObject gridNums_blue[10];
TextCharObject gridNums_blue_mini[10];
/* General - Everything */
TextCharObject textChars[127];
TextCharObject textChars_large[91];
char tempCharArray[64];
Uint8 charCounter;
Uint16 charWidthCounter;

/* Time */
double deltaTime;
Timer timer_global;
double time_anim1;
double time_anim_PressStart;
Timer timer_game;
double timer_buttonHold;
Uint8 heldButtons;
double timer_buttonHold_repeater;

/* Program State */
Uint8 programState;
bool changedProgramState;

/* Background */
BackgroundSettings bgSettings;
BGScroll bgScroll;

/* Controls */
ControlSettings controlSettings;

/* Menu Cursors */
Sint8 menuCursorIndex_main;
Sint8 menuCursorIndex_play;
Sint8 menuIndex_controls;
Sint8 menuCursorIndex_options;
Sint8 menuCursorIndex_controls;
Sint8 menuCursorIndex_video;
Sint8 menuCursorIndex_sound;
Sint8 menuCursorIndex_background;
Sint8 menuIndex_credits;

/* Game Variables */
Sint8 gridCursorIndex_x;
Sint8 gridCursorIndex_y;
Sint8 miniGridState;
Sint8 lastMiniGridState;
Sint8 miniGridCursorIndex_x;
Sint8 miniGridCursorIndex_y;
Sint8 temp_mouseIndex_x;
Sint8 temp_mouseIndex_y;
Sint8 cheatCounter;
bool justClickedInMiniGrid;

/* General-use Variables */
Sint8 i, j, k;
Sint8 char_x1, char_y1, char_x2, char_y2;
Sint32 int_i;
Uint32 uint_i;
double d;

/* Other */
Sint16 controllerAxis_leftStickX;
Sint16 controllerAxis_leftStickX_last;
Sint16 controllerAxis_leftStickY;
Sint16 controllerAxis_leftStickY_last;
Uint32 keyInputs;
Uint8  dirInputs;
Sint32 mouseInput_x;
Sint32 mouseInput_x_last;
Sint32 mouseInput_y;
Sint32 mouseInput_y_last;
double screenScale;
bool isRunning;
bool isWindowed;
bool isIntegerScale = true;
bool wentPastTitleScreen = 0;

int main(int argv, char** args) {
	/* [Wii U] Set SD Card Mount Path */
#if defined(WII_U)
	if (!WHBMountSdCard()) {
		return 0;
	}
	if (WHBGetSdCardMountPath() == NULL) {
		return 0;
	}
	string sdPathStr = "/wiiu/apps/SuDokuL";
	const char *sdPathStart = WHBGetSdCardMountPath();
	sdPathStr = sdPathStart + sdPathStr;
	const char *sdPath = sdPathStr.c_str();
	chdir(sdPath);
#endif

	/* [Vita] Disable rear touch pad */
#if defined(VITA)
	SDL_setenv("VITA_DISABLE_TOUCH_BACK", "1", 1);
#endif

	/* [Switch] Set SD Card mount path */
#if defined(SWITCH)
	chdir("/switch/SuDokuL");
#endif

#if defined(PSP)
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_EVENTS) != 0) {
#else
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS) != 0) {
#endif
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	TTF_Init();

	INIT_DEFAULT_BG_SCALE();

	/* Get settings from settings.bin */
	LOAD_SETTINGS_FILE();
	/* Set Video Settings */
	SDL_GetCurrentDisplayMode(0, &DM);
#if !defined(ANDROID)
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_9)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_9)];
			break;
		case 2:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_10)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_10)];
			break;
		case 3:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_21_9)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_21_9)];
			break;
		default:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_4_3)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_4_3)];
			break;
	}
#else
	videoSettings.widthSetting = SYSTEM_WIDTH;
	videoSettings.heightSetting = SYSTEM_HEIGHT;
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
#endif
	gameWidth = videoSettings.widthSetting;
	gameHeight = videoSettings.heightSetting;

	INIT_STARTING_WIDTH_HEIGHT_MULTS();
	INIT_STARTING_SHARED_VARIABLES();
	INIT_STARTING_TEXT_VARIABLES();
	SET_BG_SCROLL_SPEED();

	/* Set Window/Renderer */
#if defined(PSP)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#elif defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#else
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
	SET_SCALING();

	/* Initialize Sound */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
#if !defined(ANDROID)
		SDL_Log(Mix_GetError());
#endif
	}
	sfx = Mix_LoadWAV(SFX_1);
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL, (int)(soundSettings.sfxVolume * 128.0 / 100));

	/* Controller */
#if !defined(PSP)
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
#else
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	controller = SDL_JoystickOpen(0);
#endif

	/* Set Background Scrolling Variables */
	//bgSettings.scrollDir = 22;
	//SET_BG_SCROLL_SPEED();
	//bgSettings.speedMult = 15;
	//bgSettings.scale = max(min((int)min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT), 5), 1);

	/* Set Textures */
	PREPARE_SPRITE(tile, SPRITE_PATH_TILE, 0, 0, 1);
	SET_SPRITE_SCALE_TILE();
	if (gameHeight < 480) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_272, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 272);
	} else if (gameHeight < 544) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_480, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 1);
	} else if (gameHeight < 720) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_544, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 544);
	} else if (gameHeight < 1080) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_720, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 720);
	} else if (gameHeight < 1440) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_1080, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 1080);
	} else if (gameHeight < 2160) {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_1440, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 1440);
	} else {
		PREPARE_SPRITE(logo, SPRITE_PATH_LOGO_2160, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 2160);
	}
	logo.startPos_y = logo.rect.y;
	logo.endPos_y = (gameHeight * 3 / 16 - (logo.rect.h / 2));
	logo.startPos_x = logo.endPos_y; /* functionally, this is a second startPos_y, not x */
	logo.endPos_x = logo.endPos_y - (gameHeight * 3 / 4); /* functionally, this is a second endPos_y, not x */
	PREPARE_SPRITE(menuCursor, SPRITE_PATH_MENU_CURSOR, 0, 0, 1);
	PREPARE_SPRITE(game_grid, SPRITE_PATH_GRID_384, GRID_POS_X, GRID_POS_Y, 1);
	PREPARE_SPRITE(gridCursor_bottom_left, SPRITE_PATH_GRID_CURSOR_BOTTOM_LEFT, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_bottom_left, 1);
	PREPARE_SPRITE(gridCursor_bottom_right, SPRITE_PATH_GRID_CURSOR_BOTTOM_RIGHT, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_bottom_right, 1);
	PREPARE_SPRITE(gridCursor_top_left, SPRITE_PATH_GRID_CURSOR_TOP_LEFT, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_top_left, 1);
	PREPARE_SPRITE(gridCursor_top_right, SPRITE_PATH_GRID_CURSOR_TOP_RIGHT, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_top_right, 1);
	const Uint16 gridCursorCornerStep = gridCursor_bottom_left.rect.w / 4;
	PREPARE_SPRITE(game_sidebar_small, SPRITE_PATH_SIDEBAR_SMALL, SIDEBAR_SMALL_POS_X, SIDEBAR_SMALL_1_POS_Y, 1);
	PREPARE_SPRITE(miniGrid_bottom_left, SPRITE_PATH_GRID_MINI_BOTTOM_LEFT, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_bottom_right, SPRITE_PATH_GRID_MINI_BOTTOM_RIGHT, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_top_left, SPRITE_PATH_GRID_MINI_TOP_LEFT, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_top_right, SPRITE_PATH_GRID_MINI_TOP_RIGHT, 0, 0, 1);

	/* Set Rectangles */
	// The larger the difference between the display resolution and game resolution, the larger the right and bottom rectangles need to be... I think
	rightRect.x = gameWidth;
	rightRect.y = 0;
	rightRect.w = (tile.rect.w * 2) * 3840 / gameWidth;
	rightRect.h = (gameHeight + tile.rect.h) * 2160 / gameHeight;
	bottomRect.x = 0;
	bottomRect.y = gameHeight;
	bottomRect.w = (gameHeight + tile.rect.w) * 3840 / gameWidth;
	bottomRect.h = (tile.rect.h * 2) * 2160 / gameHeight;
	divider.w = gameWidth * 17 / 20;
	divider.h = gameHeight / 96;
	divider.x = (gameWidth - divider.w) / 2;
	divider.y = 0;

	/* Set Text */
	/* General - Fonts */
	pixelFont = TTF_OpenFont(FONT_COMMODORE, FONT_SIZE);
	pixelFont_large = TTF_OpenFont(FONT_COMMODORE, FONT_SIZE * 1.5);
	pixelFont_grid = TTF_OpenFont(FONT_COMMODORE, GRID_NUM_SIZE);
	pixelFont_grid_mini = TTF_OpenFont(FONT_COMMODORE, (int)GRID_SIZE_A);
	char tempCharArr[2];
	tempCharArr[1] = '\0';
	/* General */
	for (k = 32; k < LEN(textChars); k++) {
		tempCharArr[0] = k;
		SET_TEXT_CHAR_WITH_OUTLINE(tempCharArr, pixelFont, color_white, color_black, textChars[k]);
		ADJUST_CHAR_OUTLINE_OFFSET(textChars, k, -1, -1.5);
	}
	/* General (Large) */
	for (k = 32; k < 91; k++) {
		tempCharArr[0] = k;
		SET_TEXT_CHAR_WITH_OUTLINE(tempCharArr, pixelFont_large, color_light_blue, color_blue, textChars_large[k]);
		ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, k, -1, -1.5);
	}
	/* Grid Player Numbers */
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		SET_TEXT_CHAR_WITH_OUTLINE(tempCharArr, pixelFont_grid, color_gray_240, color_black, gridNums_black[k]);
		ADJUST_CHAR_OUTLINE_OFFSET(gridNums_black, k, -1, -1.5);
	}
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		SET_TEXT_CHAR_WITH_OUTLINE(tempCharArr, pixelFont_grid, color_light_blue, color_blue, gridNums_blue[k]);
		ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue, k, -1, -1.5);
	}
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		SET_TEXT_CHAR_WITH_OUTLINE(tempCharArr, pixelFont_grid_mini, color_light_blue, color_blue, gridNums_blue_mini[k]);
		ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, k, -1, -1.5);
	}
	/* Fix Outlines */
	//FIX_CHAR_OUTLINE_OFFSETS();
	/* Test Strings */
	//SET_TEXT_WITH_OUTLINE("A B C D E F G H I J K L M", text_test_1, OBJ_TO_MID_SCREEN_X(text_test_1), FONT_SIZE * 1);
	//SET_TEXT_WITH_OUTLINE("N O P Q R S T U V W X Y Z", text_test_2, OBJ_TO_MID_SCREEN_X(text_test_2), FONT_SIZE * 3);
	//SET_TEXT_WITH_OUTLINE("a b c d e f g h i j k l m", text_test_3, OBJ_TO_MID_SCREEN_X(text_test_3), FONT_SIZE * 5);
	//SET_TEXT_WITH_OUTLINE("n o p q r s t u v w x y z", text_test_4, OBJ_TO_MID_SCREEN_X(text_test_4), FONT_SIZE * 7);
	//SET_TEXT_WITH_OUTLINE("1 2 3 4 5 6 7 8 9 0",       text_test_5, OBJ_TO_MID_SCREEN_X(text_test_5), FONT_SIZE * 9);
	//SET_TEXT_WITH_OUTLINE("! \" ( ) + , - . / = :",    text_test_6, OBJ_TO_MID_SCREEN_X(text_test_6), FONT_SIZE * 11);
	//SET_TEXT_WITH_OUTLINE("The quick brown fox",       text_test_7, OBJ_TO_MID_SCREEN_X(text_test_7), FONT_SIZE * 13);
	//SET_TEXT_WITH_OUTLINE("jumped over the lazy dog",  text_test_8, OBJ_TO_MID_SCREEN_X(text_test_8), FONT_SIZE * 15);
	/* Title Screen */
#if defined(WII_U) || defined(VITA) || defined(PSP) || defined(ANDROID)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Start", text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#elif defined(SWITCH)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press +",     text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#else
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Enter", text_PressStart,    OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#endif
	SET_TEXT_WITH_OUTLINE_ANIMATED("v1.2",        text_Version_Number, (gameWidth - (text_Version_Number.rect.w * 1.25)), TEXT_VERSION_NUMBER_Y);
	text_Version_Number.endPos_x = text_Version_Number.startPos_x + (gameWidth * 3 / 16);
	/* Main Menu */
	SET_TEXT_WITH_OUTLINE_ANIMATED("Play",     text_Play,             OBJ_TO_MID_SCREEN_X(text_Play),       TEXT_PLAY_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Controls", text_Controls,         OBJ_TO_MID_SCREEN_X(text_Controls),   TEXT_CONTROLS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Options",  text_Options,          OBJ_TO_MID_SCREEN_X(text_Options),    TEXT_OPTIONS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Credits",  text_Credits,          OBJ_TO_MID_SCREEN_X(text_Credits),    TEXT_CREDITS_Y + (gameWidth * 3 / 4));
#if !defined(ANDROID)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Quit",     text_Quit,             OBJ_TO_MID_SCREEN_X(text_Quit),       TEXT_QUIT_Y + (gameWidth * 3 / 4));
#endif
	/* Play Menu */
	SET_TEXT_WITH_OUTLINE("Easy",             text_Easy,             OBJ_TO_MID_SCREEN_X(text_Easy),       TEXT_EASY_Y);
	SET_TEXT_WITH_OUTLINE("Normal",           text_Normal,           OBJ_TO_MID_SCREEN_X(text_Normal),     TEXT_NORMAL_Y);
	SET_TEXT_WITH_OUTLINE("Hard",             text_Hard,             OBJ_TO_MID_SCREEN_X(text_Hard),       TEXT_HARD_Y);
	SET_TEXT_WITH_OUTLINE("Very Hard",        text_Very_Hard,        OBJ_TO_MID_SCREEN_X(text_Very_Hard),  TEXT_VERY_HARD_Y);
	/* Loading Screen */
	SET_TEXT_WITH_OUTLINE("Loading...",       text_Loading,          OBJ_TO_MID_SCREEN_X(text_Loading),    TEXT_LOADING_Y);
	/* Game */
	SET_TEXT_WITH_OUTLINE("Time",             text_Time,             OBJ_TO_MID_SIDEBAR(text_Time),        TEXT_TIME_Y);
	game_sidebar_small.rect.y = SIDEBAR_SMALL_2_POS_Y;
	SET_TEXT_WITH_OUTLINE("Empty",            text_Empty,            OBJ_TO_MID_SIDEBAR(text_Empty),       TEXT_EMPTY_Y);
	game_sidebar_small.rect.y = SIDEBAR_SMALL_3_POS_Y;
	SET_TEXT_WITH_OUTLINE("Easy",             text_Game_Easy,        OBJ_TO_MID_SIDEBAR(text_Game_Easy),   TEXT_GAME_EASY_Y);
	SET_TEXT_WITH_OUTLINE("Normal",           text_Game_Normal,      OBJ_TO_MID_SIDEBAR(text_Game_Normal), TEXT_GAME_NORMAL_Y);
	SET_TEXT_WITH_OUTLINE("Hard",             text_Game_Hard,        OBJ_TO_MID_SIDEBAR(text_Game_Hard),   TEXT_GAME_HARD_Y);
	SET_TEXT_WITH_OUTLINE("V.Hard",           text_Game_VHard,       OBJ_TO_MID_SIDEBAR(text_Game_VHard),  TEXT_GAME_VHARD_Y);
	SET_TEXT_WITH_OUTLINE("Paused",           text_Paused,           OBJ_TO_MID_SCREEN_X(text_Paused),     TEXT_PAUSED_Y);
#if defined(WII_U) || defined(VITA) || defined(PSP)
	SET_TEXT_WITH_OUTLINE("Press Select",     text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(SWITCH)
	SET_TEXT_WITH_OUTLINE("Press -",          text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Press Back", text_Quit_to_Menu_1, OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#else
	SET_TEXT_WITH_OUTLINE("Press Q",          text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#endif
	SET_TEXT_WITH_OUTLINE("to Quit",          text_Quit_to_Menu_2, OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_2), TEXT_QUIT_TO_MENU_Y + (CONTROLS_SPACER * 2));
	SET_TEXT_WITH_OUTLINE("You Win!",         text_You_Win,          OBJ_TO_MID_SCREEN_X(text_You_Win),    TEXT_YOU_WIN_Y);
	/* Controls */
	SET_CONTROLS_TEXT();
	CONTROLS_SET_CONFIRM_BACK_POS();
	/* Options Menu */
	SET_TEXT_WITH_OUTLINE("Controls",         text_Controls_Menu,    OBJ_TO_MID_SCREEN_X(text_Controls_Menu), TEXT_CONTROLS_MENU_Y);
	SET_TEXT_WITH_OUTLINE("Video",            text_Video,            OBJ_TO_MID_SCREEN_X(text_Video),      TEXT_VIDEO_Y);
	SET_TEXT_WITH_OUTLINE("Sound",            text_Sound,            OBJ_TO_MID_SCREEN_X(text_Sound),      TEXT_SOUND_Y);
	SET_TEXT_WITH_OUTLINE("Background",       text_Background,       OBJ_TO_MID_SCREEN_X(text_Background), TEXT_BACKGROUND_Y);
	//SET_TEXT_WITH_OUTLINE("Scores",           text_Scores,           OBJ_TO_MID_SCREEN_X(text_Scores),     TEXT_SCORES_Y);
	/* Controls Menu */
	SET_TEXT_WITH_OUTLINE("Controller Input", text_Controller_Input, CONTROLS_MENU_CURSOR_POSITION_X,                 TEXT_CONTROLLER_INPUT_Y);
#if !defined(ANDROID) && !defined(PSP)
	SET_TEXT_WITH_OUTLINE("Touch Screen",     text_Touch_Screen_Input, CONTROLS_MENU_CURSOR_POSITION_X,               TEXT_TOUCH_SCREEN_INPUT_Y);
#endif
#if defined(VITA) || defined(PSP)
	SET_TEXT_WITH_OUTLINE("X - Confirm", text_A_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_A_Confirm, 0.75), TEXT_A_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("O - Back", text_B_Back, OBJ_TO_SCREEN_AT_FRACTION(text_B_Back, 0.75), TEXT_B_BACK_Y);
	SET_TEXT_WITH_OUTLINE("O - Confirm", text_B_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_B_Confirm, 0.75), TEXT_B_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("X - Back", text_A_Back, OBJ_TO_SCREEN_AT_FRACTION(text_A_Back, 0.75), TEXT_A_BACK_Y);
#else
	SET_TEXT_WITH_OUTLINE("A - Confirm",      text_A_Confirm,        OBJ_TO_SCREEN_AT_FRACTION(text_A_Confirm, 0.75), TEXT_A_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("B - Back",         text_B_Back,           OBJ_TO_SCREEN_AT_FRACTION(text_B_Back,    0.75), TEXT_B_BACK_Y);
	SET_TEXT_WITH_OUTLINE("B - Confirm",      text_B_Confirm,        OBJ_TO_SCREEN_AT_FRACTION(text_B_Confirm, 0.75), TEXT_B_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("A - Back",         text_A_Back,           OBJ_TO_SCREEN_AT_FRACTION(text_A_Back,    0.75), TEXT_A_BACK_Y);
#endif
#if !defined(ANDROID) && !defined(PSP)
	SET_TEXT_WITH_OUTLINE("Enabled",          text_Enabled,          OBJ_TO_SCREEN_AT_FRACTION(text_Enabled,   0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
	SET_TEXT_WITH_OUTLINE("Disabled",         text_Disabled,         OBJ_TO_SCREEN_AT_FRACTION(text_Disabled,  0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
#endif
	/* Video Menu */
#if defined(WII_U)
	string warningString;
	warningString = "( Recommended: 1280x720 )";
	SET_TEXT_WITH_OUTLINE(warningString,      text_Video_Warning, OBJ_TO_MID_SCREEN_X(text_Video_Warning), TEXT_VIDEO_WARNING_Y);
#elif defined(VITA)
	string warningString;
	warningString = "( Recommended: 960x544 )";
	SET_TEXT_WITH_OUTLINE(warningString,      text_Video_Warning, OBJ_TO_MID_SCREEN_X(text_Video_Warning), TEXT_VIDEO_WARNING_Y);
#elif defined(SWITCH)
	string warningString;
	warningString = "( Recommended: 1920x1080 )";
	SET_TEXT_WITH_OUTLINE(warningString, text_Video_Warning, OBJ_TO_MID_SCREEN_X(text_Video_Warning), TEXT_VIDEO_WARNING_Y);
#elif defined(PSP)
	string warningString;
	warningString = "( Recommended: 480x272 )";
	SET_TEXT_WITH_OUTLINE(warningString, text_Video_Warning, OBJ_TO_MID_SCREEN_X(text_Video_Warning), TEXT_VIDEO_WARNING_Y);
#else
	SET_TEXT_WITH_OUTLINE(" ",                text_Video_Warning, OBJ_TO_MID_SCREEN_X(text_Video_Warning), TEXT_VIDEO_WARNING_Y);
#endif
#if !defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Resolution",       text_Resolution,       VIDEO_MENU_CURSOR_POSITION_X,         TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("x",                text_x,                0,                                    TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Aspect Ratio",     text_Aspect_Ratio,     VIDEO_MENU_CURSOR_POSITION_X,         TEXT_ASPECT_RATIO_Y);
#endif
	SET_TEXT_WITH_OUTLINE(":",                text_colon,            0,                                    TEXT_ASPECT_RATIO_Y);
	SET_TEXT_WITH_OUTLINE("Integer Scale",    text_Integer_Scale,    VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("On",               text_On,               VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Off",              text_Off,              VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
#if !defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Exit Game and Apply Changes", text_Apply, VIDEO_MENU_CURSOR_POSITION_X,         TEXT_APPLY_Y);
#endif
	/* Music Menu */
	SET_TEXT_WITH_OUTLINE("Music",            text_Music,            SOUND_MENU_CURSOR_POSITION_X,         TEXT_MUSIC_Y);
	SET_TEXT_WITH_OUTLINE("Music Volume",     text_Music_Volume,     SOUND_MENU_CURSOR_POSITION_X,         TEXT_MUSIC_VOLUME_Y);
	SET_TEXT_WITH_OUTLINE("SFX Volume",       text_SFX_Volume,       SOUND_MENU_CURSOR_POSITION_X,         TEXT_SFX_VOLUME_Y);
	/* Background Menu */
	SET_TEXT_WITH_OUTLINE("Scroll Speed",     text_Scroll_Speed,     BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_SCROLL_SPEED_Y);
	SET_TEXT_WITH_OUTLINE("Scroll Direction", text_Scroll_Direction, BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_SCROLL_DIRECTION_Y);
	SET_TEXT_WITH_OUTLINE("Background Size",  text_Background_Size,  BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_BACKGROUND_SIZE_Y);
	SET_TEXT_WITH_OUTLINE("Reset To Default", text_Reset_to_Default, BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_RESET_TO_DEFAULT_Y);
	/* Credits */
	SET_CREDITS_TEXT();

	/* Set Initial Time Values */
	timer_global.now = SDL_GetTicks() / 1000.0;
	time_anim1 = 0;

	/* Set Other Initial Variable Values */
	menuCursorIndex_main = 0;
	menuCursorIndex_play = 0;
	menuCursorIndex_options = 0;
	menuCursorIndex_controls = 0;
	menuCursorIndex_video = 0;
	menuCursorIndex_sound = 0;
	menuCursorIndex_background = 0;
	programState = 0;
	time_anim_PressStart = 0;
	isRunning = true;
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(ANDROID)
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	isWindowed = false;
#else
	isWindowed = true;
#endif

	while (isRunning) {
		/* Update Timers */
		UPDATE_TIMER(timer_global);
		deltaTime = timer_global.now - timer_global.last;
		time_anim1 += deltaTime;
		if (heldButtons > 0) {
			timer_buttonHold += deltaTime;
		} else {
			timer_buttonHold = 0;
			timer_buttonHold_repeater = 0;
		}

		keyInputs = 0;
		dirInputs = 0;
#if !defined(PSP)
		/* Update Controller Axes */
		controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
		controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
		if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
			controllerAxis_leftStickX = 0;
		}
		if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
			controllerAxis_leftStickY = 0;
		}
		/* Update Key Presses and Mouse Input */
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN: // keycodes
					if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
						keyInputs |= INPUT_UP;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
						keyInputs |= INPUT_DOWN;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
						keyInputs |= INPUT_LEFT;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
						keyInputs |= INPUT_RIGHT;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2 || event.key.keysym.sym == SDLK_KP_ENTER) {
						keyInputs |= INPUT_CONFIRM;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_BACKSPACE) {
						keyInputs |= INPUT_BACK;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						keyInputs |= INPUT_START;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_q) {
						keyInputs |= INPUT_SELECT;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_PERIOD || event.key.keysym.sym == SDLK_KP_PERIOD) {
						keyInputs |= INPUT_SWAP;
						break;
					}
					if (event.key.keysym.sym == SDLK_MINUS) {
						keyInputs |= INPUT_PREV_TRACK;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_EQUALS) {
						keyInputs |= INPUT_NEXT_TRACK;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_KP_0) {
						keyInputs |= INPUT_NUM_0;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_1) {
						keyInputs |= INPUT_NUM_1;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_2) {
						keyInputs |= INPUT_NUM_2;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP_3) {
						keyInputs |= INPUT_NUM_3;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP_4) {
						keyInputs |= INPUT_NUM_4;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP_5) {
						keyInputs |= INPUT_NUM_5;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_KP_6) {
						keyInputs |= INPUT_NUM_6;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_KP_7) {
						keyInputs |= INPUT_NUM_7;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_KP_8) {
						keyInputs |= INPUT_NUM_8;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_9 || event.key.keysym.sym == SDLK_KP_9) {
						keyInputs |= INPUT_NUM_9;
						cheatCounter = 0;
						break;
					}
					if (event.key.keysym.sym == SDLK_f) {
						keyInputs |= INPUT_FULLSCREEN;
						break;
					}
#if defined(ANDROID)
					if (event.key.keysym.sym == SDLK_AC_BACK) {
						keyInputs |= INPUT_BACK;
						keyInputs |= INPUT_START;
						keyInputs |= INPUT_SELECT;
						break;
					}
#endif
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(ANDROID) && !defined(PSP)
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
					mouseInput_x = (Sint32)(mouseInput_x / screenScale - centerViewport.x);
					mouseInput_y = (Sint32)(mouseInput_y / screenScale - centerViewport.y);
					cheatCounter = 0;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
						mouseInput_x = (Sint32)(mouseInput_x / screenScale - centerViewport.x);
						mouseInput_y = (Sint32)(mouseInput_y / screenScale - centerViewport.y);
						keyInputs |= INPUT_CONFIRM_ALT;
						cheatCounter = 0;
						break;
					}
					if (event.button.button == SDL_BUTTON_RIGHT) {
						keyInputs |= INPUT_BACK;
						cheatCounter = 0;
						break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					justClickedInMiniGrid = false;
					break;
#endif
				case SDL_CONTROLLERBUTTONDOWN:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						dirInputs |= UP_PRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						dirInputs |= DOWN_PRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						dirInputs |= LEFT_PRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						dirInputs |= RIGHT_PRESSED;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
						if (!controlSettings.swapConfirmAndBack) {
							keyInputs |= INPUT_CONFIRM;
						} else {
							keyInputs |= INPUT_BACK;
						}
						cheatCounter = 0;
						break;
					}
#if defined(WII_U) || defined(SWITCH)
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
						if (!controlSettings.swapConfirmAndBack) {
							keyInputs |= INPUT_BACK;
						}
						else {
							keyInputs |= INPUT_CONFIRM;
						}
						cheatCounter = 0;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
						keyInputs |= INPUT_START;
						cheatCounter = 0;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
						keyInputs |= INPUT_SELECT;
						cheatCounter = 0;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X || event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
						keyInputs |= INPUT_SWAP;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
						keyInputs |= INPUT_PREV_TRACK;
						cheatCounter = 0;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
						keyInputs |= INPUT_NEXT_TRACK;
						cheatCounter = 0;
						break;
					}
					break;
				case SDL_CONTROLLERBUTTONUP:
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
						dirInputs |= UP_DEPRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
						dirInputs |= DOWN_DEPRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
						dirInputs |= LEFT_DEPRESSED;
						break;
					}
					if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
						dirInputs |= RIGHT_DEPRESSED;
						break;
					}
					break;
				case SDL_FINGERDOWN:
					if (controlSettings.enableTouchscreen) {
						mouseInput_x = event.tfinger.x * gameWidth;
						mouseInput_y = event.tfinger.y * gameHeight;
						mouseInput_x = (Sint32)(mouseInput_x / screenScale - centerViewport.x);
						mouseInput_y = (Sint32)(mouseInput_y / screenScale - centerViewport.y);
						keyInputs |= INPUT_CONFIRM_ALT;
						cheatCounter = 0;
					}
					break;
				case SDL_FINGERMOTION:
					if (controlSettings.enableTouchscreen) {
						mouseInput_x = event.tfinger.x * gameWidth;
						mouseInput_y = event.tfinger.y * gameHeight;
						mouseInput_x = (Sint32)(mouseInput_x / screenScale - centerViewport.x);
						mouseInput_y = (Sint32)(mouseInput_y / screenScale - centerViewport.y);
						cheatCounter = 0;
					}
					break;
				case SDL_FINGERUP:
					if (controlSettings.enableTouchscreen) {
						justClickedInMiniGrid = false;
					}
					break;
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(PSP) && !defined(ANDROID)
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						if (SDL_GetWindowSurface(window)->w < gameWidth)
							SDL_SetWindowSize(window, gameWidth, SDL_GetWindowSurface(window)->h);
						if (SDL_GetWindowSurface(window)->h < gameHeight)
							SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, gameHeight);
						SET_SCALING();
					}
					break;
#endif
				default:
					break;
			}
		}
#else
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_JOYAXISMOTION:
					if (event.jaxis.which == 0) {
						if (event.jaxis.axis == 0) {
							controllerAxis_leftStickX = event.jaxis.value;
							if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
								controllerAxis_leftStickX = 0;
							}
						}
						if (event.jaxis.axis == 1) {
							controllerAxis_leftStickY = event.jaxis.value;
							if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
								controllerAxis_leftStickY = 0;
							}
						}
					}
					break;
				case SDL_JOYBUTTONDOWN:
					if (event.jbutton.which == 0) {
						if (event.jbutton.button == 8) { // Up
							dirInputs |= UP_PRESSED;
							break;
						}
						if (event.jbutton.button == 6) { // Down
							dirInputs |= DOWN_PRESSED;
							break;
						}
						if (event.jbutton.button == 7) { // Left
							dirInputs |= LEFT_PRESSED;
							break;
						}
						if (event.jbutton.button == 9) { // Right
							dirInputs |= RIGHT_PRESSED;
							break;
						}
						if (event.jbutton.button == 1) { // O
							if (!controlSettings.swapConfirmAndBack) {
								keyInputs |= INPUT_CONFIRM;
							} else {
								keyInputs |= INPUT_BACK;
							}
							cheatCounter = 0;
							break;
						}
						if (event.jbutton.button == 2) { // X
							if (!controlSettings.swapConfirmAndBack) {
								keyInputs |= INPUT_BACK;
							} else {
								keyInputs |= INPUT_CONFIRM;
							}
							cheatCounter = 0;
							break;
						}
						if (event.jbutton.button == 11) { // Start
							keyInputs |= INPUT_START;
							cheatCounter = 0;
							break;
						}
						if (event.jbutton.button == 10) { // Select
							keyInputs |= INPUT_SELECT;
							cheatCounter = 0;
							break;
						}
						if (event.jbutton.button == 0 || event.cbutton.button == 3) { // Triangle || Square
							keyInputs |= INPUT_SWAP;
							break;
						}
						if (event.jbutton.button == 4) { // L
							keyInputs |= INPUT_PREV_TRACK;
							cheatCounter = 0;
							break;
						}
						if (event.jbutton.button == 5) { // R
							keyInputs |= INPUT_NEXT_TRACK;
							cheatCounter = 0;
							break;
						}
					}
					break;
				case SDL_JOYBUTTONUP:
					if (event.jbutton.button == 8) { // Up
						dirInputs |= UP_DEPRESSED;
						break;
					}
					if (event.jbutton.button == 6) { // Down
						dirInputs |= DOWN_DEPRESSED;
						break;
					}
					if (event.jbutton.button == 7) { // Left
						dirInputs |= LEFT_DEPRESSED;
						break;
					}
					if (event.jbutton.button == 9) { // Right
						dirInputs |= RIGHT_DEPRESSED;
						break;
					}
					break;
				default:
					break;
			}
		}
#endif
		if ((controllerAxis_leftStickX < 0) && !(controllerAxis_leftStickX_last < 0)) {
			dirInputs |= LEFT_PRESSED;
		} else if (!(controllerAxis_leftStickX < 0) && (controllerAxis_leftStickX_last < 0)) { // a little redundant, but easier to read
			dirInputs |= LEFT_DEPRESSED;
		}
		if ((controllerAxis_leftStickX > 0) && !(controllerAxis_leftStickX_last > 0)) {
			dirInputs |= RIGHT_PRESSED;
		} else if (!(controllerAxis_leftStickX > 0) && (controllerAxis_leftStickX_last > 0)) {
			dirInputs |= RIGHT_DEPRESSED;
		}
		if ((controllerAxis_leftStickY < 0) && !(controllerAxis_leftStickY_last < 0)) {
			dirInputs |= UP_PRESSED;
		} else if (!(controllerAxis_leftStickY < 0) && (controllerAxis_leftStickY_last < 0)) {
			dirInputs |= UP_DEPRESSED;
		}
		if ((controllerAxis_leftStickY > 0) && !(controllerAxis_leftStickY_last > 0)) {
			dirInputs |= DOWN_PRESSED;
		} else if (!(controllerAxis_leftStickY > 0) && (controllerAxis_leftStickY_last > 0)) {
			dirInputs |= DOWN_DEPRESSED;
		}
		DIR_HANDLER(UP_PRESSED, UP_DEPRESSED, INPUT_UP);
		DIR_HANDLER(DOWN_PRESSED, DOWN_DEPRESSED, INPUT_DOWN);
		DIR_HANDLER(LEFT_PRESSED, LEFT_DEPRESSED, INPUT_LEFT);
		DIR_HANDLER(RIGHT_PRESSED, RIGHT_DEPRESSED, INPUT_RIGHT);
		if (timer_buttonHold > 0.5) {
			timer_buttonHold_repeater += deltaTime;
			if (timer_buttonHold_repeater >= 0.033) {
				if (BUTTON_HELD(INPUT_UP)) {
					keyInputs |= INPUT_UP;
				}
				if (BUTTON_HELD(INPUT_DOWN)) {
					keyInputs |= INPUT_DOWN;
				}
				if (BUTTON_HELD(INPUT_LEFT)) {
					keyInputs |= INPUT_LEFT;
				}
				if (BUTTON_HELD(INPUT_RIGHT)) {
					keyInputs |= INPUT_RIGHT;
				}
				timer_buttonHold_repeater -= 0.033;
			}
		}

		/* Key Presses (Always Active) */
		if (KEY_PRESSED(INPUT_FULLSCREEN)) {
			SDL_TOGGLE_FULLSCREEN();
		}
		if (KEY_PRESSED(INPUT_PREV_TRACK) && wentPastTitleScreen) {
			if (--soundSettings.musicIndex < 1)
				soundSettings.musicIndex = 7;
			PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
			if (programState != 20) { // If you save in the Video settings menu, possible undesired video settings would also be saved (this could be fixed, but it's just not worth the trouble for such a small issue)
				SAVE_CURRENT_SETTINGS();
			}
		}
		if (KEY_PRESSED(INPUT_NEXT_TRACK) && wentPastTitleScreen) {
			if (++soundSettings.musicIndex > 7)
				soundSettings.musicIndex = 1;
			PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
			if (programState != 20) {
				SAVE_CURRENT_SETTINGS();
			}
		}

		/* Clear Screen */
		// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		// SDL_RenderClear(renderer);

		/* Draw Tile Background */
		bgScroll.speedStep_x += bgSettings.speedMult * bgScroll.speed_x * deltaTime;
		bgScroll.speedStep_x_int = int(bgScroll.speedStep_x) % tile.rect.h;
		bgScroll.speedStep_y += bgSettings.speedMult * bgScroll.speed_y * deltaTime;
		bgScroll.speedStep_y_int = int(bgScroll.speedStep_y) % tile.rect.w;
		for (bgScroll.j = -tile.rect.h; bgScroll.j <= gameHeight + tile.rect.h; bgScroll.j += tile.rect.h) {
			for (bgScroll.i = -tile.rect.w; bgScroll.i <= gameWidth + tile.rect.w; bgScroll.i += tile.rect.w) {
				tile.rect.x = bgScroll.i + bgScroll.speedStep_x_int;
				tile.rect.y = bgScroll.j + bgScroll.speedStep_y_int;
				SDL_RenderCopy(renderer, tile.texture, NULL, &tile.rect);
			}
		}

		switch (programState) {
			/* 0 = Title Screen */
			case 0:
				time_anim_PressStart += deltaTime;
				/* Key Presses */
				if (KEY_PRESSED(INPUT_CONFIRM) || KEY_PRESSED(INPUT_CONFIRM_ALT) || KEY_PRESSED(INPUT_START)) {
					Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
					if (!wentPastTitleScreen) {
						wentPastTitleScreen = true;
						PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
					}
					time_anim1 = 0;
					programState = 1;
				}
				/* Animate Text */
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, TEXT_PRESS_START_AMPLITUDE));
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				RENDER_TEXT(text_PressStart);
				RENDER_TEXT(text_Version_Number);
				break;
			/* 1 = Title Screen -> Main Menu */
			case 1:
				TRANSITION_GRAPHICS_FROM_TITLE_SCREEN();
				TRANSITION_GRAPHICS_TO_MAIN_MENU(-1);
				TRANSITION_TO_STATE_WITH_TIMER(time_anim1, 1, 2);
				UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main);
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, TEXT_PRESS_START_AMPLITUDE));
				break;
			/* 2 = Main Menu */
			case 2:
				if (changedProgramState) {
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main);
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(3);
#if !defined(ANDROID)
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_main, 5);
#else
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_main, 4);
#endif
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_main, text_Play, 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_main, text_Controls, 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_main, text_Options, 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_main, text_Credits, 3);
#if !defined(ANDROID)
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_main, text_Quit, 4);
#endif
				}
#if !defined(ANDROID)
				if (KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) && (MOUSE_IS_IN_RECT(text_Play.rect)
					|| MOUSE_IS_IN_RECT(text_Controls.rect) || MOUSE_IS_IN_RECT(text_Options.rect)
					|| MOUSE_IS_IN_RECT(text_Credits.rect) || MOUSE_IS_IN_RECT(text_Quit.rect)))) {
#else
				if (KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) && (MOUSE_IS_IN_RECT(text_Play.rect)
					|| MOUSE_IS_IN_RECT(text_Controls.rect) || MOUSE_IS_IN_RECT(text_Options.rect)
					|| MOUSE_IS_IN_RECT(text_Credits.rect)))) {
#endif
					time_anim1 = 0;
					switch (menuCursorIndex_main) {
						case 0:
							programState = 7;
							UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_play);
							break;
						case 1:
							programState = 12;
							menuIndex_controls = 0;
							break;
						case 2:
							programState = 13;
							UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_options);
							break;
						case 3:
							programState = 18;
							menuIndex_credits = 0;
							break;
						default:
							isRunning = 0;
							break;
					}
				}
				/* Animate Cursor */
				UPDATE_MAIN_MENU_CURSOR_POSITION_X();
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Play);
				RENDER_TEXT(text_Controls);
				RENDER_TEXT(text_Options);
				RENDER_TEXT(text_Credits);
#if !defined(ANDROID)
				RENDER_TEXT(text_Quit);
#endif
				break;
			/* 3 = Main Menu -> Title Screen */
			case 3:
				time_anim_PressStart = 0;
				TRANSITION_GRAPHICS_FROM_MAIN_MENU();
				TRANSITION_GRAPHICS_TO_TITLE_SCREEN();
				TRANSITION_TO_STATE_WITH_TIMER(time_anim1, 1, 0);
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, TEXT_PRESS_START_AMPLITUDE));
				break;
			/* 7 = Play Menu */
			case 7:
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(2);
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_play, 4);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_play, text_Easy, 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_play, text_Normal, 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_play, text_Hard, 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_play, text_Very_Hard, 3);
				}
				if (KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) && (MOUSE_IS_IN_RECT(text_Easy.rect)
					|| MOUSE_IS_IN_RECT(text_Normal.rect) || MOUSE_IS_IN_RECT(text_Hard.rect) || MOUSE_IS_IN_RECT(text_Very_Hard.rect)))) {
					programState = 8;
				}
				/* Animate Cursor */
				UPDATE_PLAY_MENU_CURSOR_POSITION_X();
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Easy);
				RENDER_TEXT(text_Normal);
				RENDER_TEXT(text_Hard);
				RENDER_TEXT(text_Very_Hard);
				break;
			/* 8 = Generating Puzzle Screen */
			case 8:
				/* Draw Text */
				RENDER_TEXT(text_Loading);
				/* Update Screen */
				SDL_RenderPresent(renderer);
				switch (menuCursorIndex_play) {
					case 0:
						ZERO_OUT_ARRAY(grid);
						ZERO_OUT_ARRAY(originalGrid);
						ZERO_OUT_ARRAY(solutionGrid);
						ZERO_OUT_ARRAY(miniGrid);
						if (!generateGridAndSolution(RANDINT(30, 35), 52)) { // it will always be the minimum, hence the use of RANDINT
							setPremadePuzzle(0, RANDINT(0, 999));
						}
						programState = 9;
						break;
					case 1:
						ZERO_OUT_ARRAY(grid);
						ZERO_OUT_ARRAY(originalGrid);
						ZERO_OUT_ARRAY(solutionGrid);
						ZERO_OUT_ARRAY(miniGrid);
						if (!generateGridAndSolution(RANDINT(50, 52), 75)) { // it will always be the minimum, hence the use of RANDINT
							setPremadePuzzle(1, RANDINT(0, 999));
						}
						programState = 9;
						break;
					case 2:
						ZERO_OUT_ARRAY(grid);
						ZERO_OUT_ARRAY(originalGrid);
						ZERO_OUT_ARRAY(solutionGrid);
						ZERO_OUT_ARRAY(miniGrid);
						// generateGridAndSolution(75, 300); // requires backtracking
						setPremadePuzzle(2, RANDINT(0, 999));
						programState = 9;
						break;
					case 3:
						ZERO_OUT_ARRAY(grid);
						ZERO_OUT_ARRAY(originalGrid);
						ZERO_OUT_ARRAY(solutionGrid);
						ZERO_OUT_ARRAY(miniGrid);
						// generateGridAndSolution(300, 500); // requires more backtracking
						setPremadePuzzle(3, RANDINT(0, 999));
						programState = 9;
						break;
					default:
						break;
				}
				timer_game.now = 0.0;
				gridCursorIndex_x = 0;
				gridCursorIndex_y = 0;
				SET_GRID_CURSOR_BY_LARGE_X();
				SET_GRID_CURSOR_BY_LARGE_Y();
				miniGridState = 0;
				UPDATE_NUM_EMPTY();
				break;
			/* 9 = Game */
			case 9:
				/* Update Timer */
				timer_game.now += deltaTime;
				if (timer_game.now > 5999) {
					timer_game.now = 5999;
				}
				/* Key Presses */
				if (KEY_PRESSED(INPUT_START)) {
					programState = 10;
				}
				if (MOUSE_MOVED()) {
					GAME_HANDLE_MOUSE_MOVEMENT_MAIN();
					GAME_HANDLE_MOUSE_MOVEMENT_MINI();
				}
				GAME_HANDLE_MAIN_GRID_NAVIGATION();
				GAME_HANDLE_MINI_GRID_NAVIGATION();
				GAME_HANDLE_NUM_KEY_PRESSES();
				GAME_HANDLE_CHEAT_REVEAL_CELL();
				lastMiniGridState = miniGridState;
				/* Draw Grid */
				SDL_RenderCopy(renderer, game_grid.texture, NULL, &game_grid.rect);
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						SET_AND_RENDER_NUM_GRID_MAIN_NORMAL(gridNums_black, int(originalGrid[i]), i);
					} else if (grid[i]) {
						SET_AND_RENDER_NUM_GRID_MAIN_NORMAL(gridNums_blue, int(grid[i]), i);
					} else {
						for (j = 1; j < 10; j++) {
							if (miniGrid[i] & (1<<j)) {
								SET_AND_RENDER_NUM_GRID_MAIN_MINI(gridNums_blue_mini, int(j), i);
							}
						}
					}
				}
				if (miniGridState == 1) {
					SDL_RenderCopy(renderer, currMiniGrid->texture, NULL, &currMiniGrid->rect);
					for (i = 1; i < 10; i++) {
						SET_AND_RENDER_NUM_GRID_SUB_NORMAL(gridNums_blue, int(i));
					}
				} else if (miniGridState == 2) {
					SDL_RenderCopy(renderer, currMiniGrid->texture, NULL, &currMiniGrid->rect);
					for (i = 1; i < 10; i++) {
						SET_AND_RENDER_NUM_GRID_SUB_MINI(gridNums_blue_mini, int(i));
					}
				}
				/* Draw Cursor */
				SDL_RenderCopy(renderer, gridCursor_bottom_left.texture, NULL, &gridCursor_bottom_left.rect);
				SDL_RenderCopy(renderer, gridCursor_bottom_right.texture, NULL, &gridCursor_bottom_right.rect);
				SDL_RenderCopy(renderer, gridCursor_top_left.texture, NULL, &gridCursor_top_left.rect);
				SDL_RenderCopy(renderer, gridCursor_top_right.texture, NULL, &gridCursor_top_right.rect);
				DRAW_SIDEBAR();
				break;
			/* 10 = Pause Screen */
			case 10:
				/* Key Presses */
#if !defined(ANDROID)
				if (KEY_PRESSED(INPUT_START)) {
#else
				if (KEY_PRESSED(INPUT_START) || KEY_PRESSED(INPUT_CONFIRM_ALT)) {
#endif
					programState = 9;
				}
				MENU_HANDLE_MENU_BUTTON();
				DRAW_SIDEBAR();
				RENDER_TEXT(text_Paused);
				RENDER_TEXT(text_Quit_to_Menu_1);
				RENDER_TEXT(text_Quit_to_Menu_2);
				break;
			/* 11 = Victory Screen */
			case 11:
				/* Key Presses */
				if (KEY_PRESSED(INPUT_START)) {
					programState = 2;
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main);
				}
				/* Draw Grid */
				SDL_RenderCopy(renderer, game_grid.texture, NULL, &game_grid.rect);
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						SET_AND_RENDER_NUM_GRID_MAIN_NORMAL(gridNums_black, int(originalGrid[i]), i);
					} else if (grid[i]) {
						SET_AND_RENDER_NUM_GRID_MAIN_NORMAL(gridNums_blue, int(grid[i]), i);
					} else {
						for (j = 1; j < 10; j++) {
							if (miniGrid[i] & (1<<j)) {
								SET_AND_RENDER_NUM_GRID_MAIN_MINI(gridNums_blue_mini, int(j), i);
							}
						}
					}
				}
				DRAW_SIDEBAR();
				RENDER_TEXT(text_You_Win);
				break;
			/* 12 = Controls Screen */
			case 12:
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(2);
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP)
				if (KEY_PRESSED(INPUT_RIGHT) && menuIndex_controls < 1) {
#elif defined(ANDROID)
				if ((KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM_ALT)) && menuIndex_controls < 1) {
#else
				if (KEY_PRESSED(INPUT_RIGHT) && menuIndex_controls < 3) {
#endif
					menuIndex_controls++;
				} else if (KEY_PRESSED(INPUT_LEFT) && menuIndex_controls > 0) {
					menuIndex_controls--;
				}
				//RENDER_TEST_TEXT();
				switch (menuIndex_controls) {
					case 0:
						RENDER_CONTROLS_TEXT_PAGE_1();
						break;
					case 1:
						RENDER_CONTROLS_TEXT_PAGE_2();
						break;
#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(PSP) && !defined(ANDROID)
					case 2:
						RENDER_CONTROLS_TEXT_PAGE_3();
						break;
					case 3:
						RENDER_CONTROLS_TEXT_PAGE_4();
						break;
#endif
					default:
						break;
				}
				break;
			/* 13 = Options Menu */
			case 13:
				if (changedProgramState) {
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_options);
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(2);
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_options, 4);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_options, text_Controls_Menu, 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_options, text_Video, 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_options, text_Sound, 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_options, text_Background, 3);
					// MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_options, text_Scores, 3);
				}
				if (KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) && (MOUSE_IS_IN_RECT(text_Controls_Menu.rect)
					|| MOUSE_IS_IN_RECT(text_Video.rect) || MOUSE_IS_IN_RECT(text_Sound.rect) || MOUSE_IS_IN_RECT(text_Background.rect)))) {
					time_anim1 = 0;
					switch (menuCursorIndex_options) {
						case 0:
							programState = 28;
							changedProgramState = true;
							break;
						case 1:
							programState = 20;
							changedProgramState = true;
							break;
						case 2:
							programState = 22;
							changedProgramState = true;
							break;
						case 3:
							programState = 24;
							changedProgramState = true;
							break;
						case 4:
							programState = 26;
							break;
						default:
							break;
					}
				}
				/* Animate Cursor */
				UPDATE_OPTIONS_MENU_CURSOR_POSITION_X();
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Controls_Menu);
				RENDER_TEXT(text_Video);
				RENDER_TEXT(text_Sound);
				RENDER_TEXT(text_Background);
				// RENDER_TEXT(text_Scores);
				break;
			/* 18 = Credits Screen */
			case 18:
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(2);
#if !defined(ANDROID)
				if (KEY_PRESSED(INPUT_RIGHT) && menuIndex_credits < 6) {
#else
				if ((KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM_ALT)) && menuIndex_credits < 6) {
#endif
					menuIndex_credits++;
				}
				else if (KEY_PRESSED(INPUT_LEFT) && menuIndex_credits > 0) {
					menuIndex_credits--;
				}
				switch (menuIndex_credits) {
					case 0:
						RENDER_CREDITS_TEXT_PAGE_1();
						break;
					case 1:
						RENDER_CREDITS_TEXT_PAGE_2();
						break;
					case 2:
						RENDER_CREDITS_TEXT_PAGE_3();
						break;
					case 3:
						RENDER_CREDITS_TEXT_PAGE_4();
						break;
					case 4:
						RENDER_CREDITS_TEXT_PAGE_5();
						break;
					case 5:
						RENDER_CREDITS_TEXT_PAGE_6();
						break;
					case 6:
						RENDER_CREDITS_TEXT_PAGE_7();
						break;
					default:
						break;
				}
				break;
			/* 20 = Video Menu */
			case 20:
				if (changedProgramState) {
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_video);
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON(13);
				if (KEY_PRESSED(INPUT_LEFT)) {
					switch (menuCursorIndex_video) {
#if !defined(ANDROID)
						case 0:
							switch (videoSettings.aspectRatioIndex) {
								case 0:
									if (--videoSettings.resolutionIndex < 0)
										videoSettings.resolutionIndex = LEN(RESOLUTION_OPTIONS_WIDTH_4_3) - 1;
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex];
									break;
								case 1:
									if (--videoSettings.resolutionIndex < 0)
										videoSettings.resolutionIndex = LEN(RESOLUTION_OPTIONS_WIDTH_16_9) - 1;
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex];
									break;
								case 2:
									if (--videoSettings.resolutionIndex < 0)
										videoSettings.resolutionIndex = LEN(RESOLUTION_OPTIONS_WIDTH_16_10) - 1;
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex];
									break;
								case 3:
									if (--videoSettings.resolutionIndex < 0)
										videoSettings.resolutionIndex = LEN(RESOLUTION_OPTIONS_WIDTH_21_9) - 1;
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex];
									break;
								default:
									break;
							}
							break;
						case 1:
							if (--videoSettings.aspectRatioIndex < 0)
								videoSettings.aspectRatioIndex = 3;
							videoSettings.resolutionIndex = 0;
							switch (videoSettings.aspectRatioIndex) {
								case 0:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex];
									break;
								case 1:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex];
									break;
								case 2:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex];
									break;
								case 3:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex];
									break;
								default:
									break;
							}
							break;
						case 2:
							SDL_TOGGLE_INTEGER_SCALE();
							break;
#else
						case 0:
							SDL_TOGGLE_INTEGER_SCALE();
							break;
#endif
						default:
							break;
					}
				}
#if !defined(ANDROID)
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) &&
					(MOUSE_IS_IN_RECT_WITH_SETTING(text_Resolution.rect, (VIDEO_MENU_NUM_POSITION_X + (FONT_SIZE * 9)))
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Aspect_Ratio.rect, (VIDEO_MENU_NUM_POSITION_X + (FONT_SIZE * 3)))
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Integer_Scale.rect, (text_Off.rect.x + text_Off.rect.w))
					|| MOUSE_IS_IN_RECT(text_Apply.rect)))) {
#else
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT))) {
#endif
					switch (menuCursorIndex_video) {
#if !defined(ANDROID)
						case 0:
							switch (videoSettings.aspectRatioIndex) {
								case 0:
									videoSettings.resolutionIndex = (videoSettings.resolutionIndex + 1) % LEN(RESOLUTION_OPTIONS_WIDTH_4_3);
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex];
									break;
								case 1:
									videoSettings.resolutionIndex = (videoSettings.resolutionIndex + 1) % LEN(RESOLUTION_OPTIONS_WIDTH_16_9);
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex];
									break;
								case 2:
									videoSettings.resolutionIndex = (videoSettings.resolutionIndex + 1) % LEN(RESOLUTION_OPTIONS_WIDTH_16_10);
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex];
									break;
								case 3:
									videoSettings.resolutionIndex = (videoSettings.resolutionIndex + 1) % LEN(RESOLUTION_OPTIONS_WIDTH_21_9);
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex];
									break;
								default:
									break;
							}
							break;
						case 1:
							videoSettings.aspectRatioIndex = (videoSettings.aspectRatioIndex + 1) % 4;
							videoSettings.resolutionIndex = 0;
							switch (videoSettings.aspectRatioIndex) {
								case 0:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex];
									break;
								case 1:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex];
									break;
								case 2:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex];
									break;
								case 3:
									videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_21_9[videoSettings.resolutionIndex];
									videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_21_9[videoSettings.resolutionIndex];
									break;
								default:
									break;
							}
							break;
						case 2:
							SDL_TOGGLE_INTEGER_SCALE();
							break;
						case 3:
							if (KEY_PRESSED(INPUT_CONFIRM) || KEY_PRESSED(INPUT_CONFIRM_ALT)) {
								if (settingsFile == NULL) {
									INITIALIZE_SETTINGS_FILE_WITH_SETTINGS(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen, 1, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale);
								} else {
									SAVE_CURRENT_SETTINGS();
								}
								// isRunning = false;
								// End the program here; otherwise, text and sprites will be resized and look weird for one frame before closing
								SDL_DESTROY_ALL();
								SYSTEM_SPECIFIC_CLOSE();
								return 0;
							}
							break;
#else
						case 0:
							SDL_TOGGLE_INTEGER_SCALE();
							break;
#endif
						default:
							break;
					}
				}
#if !defined(ANDROID)
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_video, 4);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_video, text_Resolution, (VIDEO_MENU_NUM_POSITION_X + (FONT_SIZE * 9)), 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_video, text_Aspect_Ratio, (VIDEO_MENU_NUM_POSITION_X + (FONT_SIZE * 3)), 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_video, text_Integer_Scale, (text_Off.rect.x + text_Off.rect.w), 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(menuCursorIndex_video, text_Apply, 3);
				}
#else
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_video, 1);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_video, text_Integer_Scale, (VIDEO_MENU_NUM_POSITION_X + (FONT_SIZE * 9)), 0);
				}
#endif
				/* Animate Cursor */
				UPDATE_VIDEO_MENU_CURSOR_POSITION_X();
				/* Set and Draw Numbers */
#if !defined(ANDROID)
				SET_AND_RENDER_NUM_RESOLUTION(videoSettings.widthSetting, videoSettings.heightSetting, VIDEO_MENU_NUM_POSITION_X, TEXT_RESOLUTION_Y);
				switch (videoSettings.aspectRatioIndex) {
					case 0:
						SET_AND_RENDER_NUM_ASPECT_RATIO_4_3(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 1:
						SET_AND_RENDER_NUM_ASPECT_RATIO_16_9(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 2:
						SET_AND_RENDER_NUM_ASPECT_RATIO_16_10(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 3:
						SET_AND_RENDER_NUM_ASPECT_RATIO_21_9(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					default:
						break;
				}
#endif
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
#if !defined(ANDROID)
				RENDER_TEXT(text_Video_Warning);
				RENDER_TEXT(text_Resolution);
				RENDER_TEXT(text_Aspect_Ratio);
				RENDER_TEXT(text_Apply);
#endif
				RENDER_TEXT(text_Integer_Scale);
				if (isIntegerScale) {
					RENDER_TEXT(text_On);
				} else {
					RENDER_TEXT(text_Off);
				}
				break;
			/* 22 = Sound Menu */
			case 22:
				if (changedProgramState) {
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_sound);
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON_WITH_SETTINGS(13);
				if (KEY_PRESSED(INPUT_LEFT)) {
					switch (menuCursorIndex_sound) {
						case 0:
							if (--soundSettings.musicIndex < 1)
								soundSettings.musicIndex = 7;
							PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
							break;
						case 1:
							Mix_VolumeMusic((int)(--soundSettings.bgmVolume * 128.0 / 100));
							if (soundSettings.bgmVolume < 0)
								soundSettings.bgmVolume = 0;
							break;
						case 2:
							Mix_Volume(SFX_CHANNEL, ((int)(--soundSettings.sfxVolume * 128.0 / 100)));
							if (soundSettings.sfxVolume < 0)
								soundSettings.sfxVolume = 0;
							else
								Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
							break;
						default:
							break;
					}
				}
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) &&
					(MOUSE_IS_IN_RECT_WITH_SETTING(text_Music.rect, SOUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Music_Volume.rect, SOUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_SFX_Volume.rect, SOUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Reset_to_Default.rect, SOUND_MENU_ENDPOINT)))) {
					switch (menuCursorIndex_sound) {
						case 0:
							if (++soundSettings.musicIndex > 7)
                                soundSettings.musicIndex = 1;
							PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
							break;
						case 1:
							Mix_VolumeMusic((int)(++soundSettings.bgmVolume * 128.0 / 100));
							if (soundSettings.bgmVolume > 100)
                                soundSettings.bgmVolume = 100;
							break;
						case 2:
							Mix_Volume(SFX_CHANNEL, (int)(++soundSettings.sfxVolume * 128.0 / 100));
							if (soundSettings.sfxVolume > 100)
                                soundSettings.sfxVolume = 100;
							else
								Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
							break;
						case 3:
							if (KEY_PRESSED(INPUT_CONFIRM) || KEY_PRESSED(INPUT_CONFIRM_ALT)) {
								if (soundSettings.musicIndex != 1) {
									soundSettings.musicIndex = 1;
									soundSettings.bgmVolume = 90;
									PLAY_MUSIC_AT_INDEX(soundSettings.musicIndex);
								} else {
									soundSettings.bgmVolume = 90;
								}
								soundSettings.sfxVolume = 50;
								Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
								Mix_Volume(SFX_CHANNEL, (int)(soundSettings.sfxVolume * 128.0 / 100));
							}
							break;
						default:
							break;
					}
				}
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_sound, 4);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_sound, text_Music, SOUND_MENU_ENDPOINT, 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_sound, text_Music_Volume, SOUND_MENU_ENDPOINT, 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_sound, text_SFX_Volume, SOUND_MENU_ENDPOINT, 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_sound, text_Reset_to_Default, SOUND_MENU_ENDPOINT, 3);
				}
				/* Animate Cursor */
				UPDATE_SOUND_MENU_CURSOR_POSITION_X();
				/* Set and Draw Numbers */
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(soundSettings.musicIndex, SOUND_MENU_NUM_POSITION_X, TEXT_MUSIC_Y);
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(soundSettings.bgmVolume, SOUND_MENU_NUM_POSITION_X, TEXT_MUSIC_VOLUME_Y);
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(soundSettings.sfxVolume, SOUND_MENU_NUM_POSITION_X, TEXT_SFX_VOLUME_Y);
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Music);
				RENDER_TEXT(text_Music_Volume);
				RENDER_TEXT(text_SFX_Volume);
				RENDER_TEXT(text_Reset_to_Default);
				break;
			/* 24 = Background Menu */
			case 24:
				if (changedProgramState) {
					UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_background);
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON_WITH_SETTINGS(13);
				if (KEY_PRESSED(INPUT_LEFT)) {
					switch (menuCursorIndex_background) {
						case 0:
							bgSettings.speedMult -= 5;
							if (bgSettings.speedMult < 0)
								bgSettings.speedMult = 100;
							break;
						case 1:
							if (--bgSettings.scrollDir < 0)
								bgSettings.scrollDir = 71;
							SET_BG_SCROLL_SPEED();
							break;
						case 2:
							bgSettings.scale--;
							if (bgSettings.scale < 1)
								bgSettings.scale = 10;
							SET_SPRITE_SCALE_TILE();
							break;
						default:
							break;
					}
				}
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) &&
					(MOUSE_IS_IN_RECT_WITH_SETTING(text_Scroll_Speed.rect, BACKGROUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Scroll_Direction.rect, BACKGROUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Background_Size.rect, BACKGROUND_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Reset_to_Default.rect, BACKGROUND_MENU_ENDPOINT)))) {
					switch (menuCursorIndex_background) {
						case 0:
							bgSettings.speedMult = (bgSettings.speedMult + 5) % 105;
							break;
						case 1:
							bgSettings.scrollDir = (bgSettings.scrollDir + 1) % 72;
							SET_BG_SCROLL_SPEED();
							break;
						case 2:
							bgSettings.scale++;
							if (bgSettings.scale > 10)
								bgSettings.scale = 1;
							SET_SPRITE_SCALE_TILE();
							break;
						case 3:
							if (KEY_PRESSED(INPUT_CONFIRM) || KEY_PRESSED(INPUT_CONFIRM_ALT)) {
								bgSettings.scrollDir = 22;
								SET_BG_SCROLL_SPEED();
								bgSettings.speedMult = 15;
								//bgSettings.scale = max(min((int)min(GAME_WIDTH_MULT, GAME_HEIGHT_MULT), 5), 1);
								bgSettings.scale = DEFAULT_BG_SCALE;
								SET_SPRITE_SCALE_TILE();
							}
						default:
							break;
					}
				}
				MENU_HANDLE_VERT_CURSOR_MOVEMENT(menuCursorIndex_background, 4);
				if (MOUSE_MOVED()) {
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_background, text_Scroll_Speed, BACKGROUND_MENU_ENDPOINT, 0);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_background, text_Scroll_Direction, BACKGROUND_MENU_ENDPOINT, 1);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_background, text_Background_Size, BACKGROUND_MENU_ENDPOINT, 2);
					MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(menuCursorIndex_background, text_Reset_to_Default, BACKGROUND_MENU_ENDPOINT, 3);
				}
				/* Animate Cursor */
				UPDATE_BACKGROUND_MENU_CURSOR_POSITION_X();
				/* Set and Draw Numbers */
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(bgSettings.speedMult, BACKGROUND_MENU_NUM_POSITION_X, TEXT_SCROLL_SPEED_Y);
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED((bgSettings.scrollDir * 5), BACKGROUND_MENU_NUM_POSITION_X, TEXT_SCROLL_DIRECTION_Y);
				SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(bgSettings.scale, BACKGROUND_MENU_NUM_POSITION_X, TEXT_BACKGROUND_SIZE_Y);
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Scroll_Speed);
				RENDER_TEXT(text_Scroll_Direction);
				RENDER_TEXT(text_Background_Size);
				RENDER_TEXT(text_Reset_to_Default);
				break;
			/* 26 = Scores Menu */
			case 26:
				MENU_HANDLE_BACK_BUTTON(13);
				break;
			/* 28 = Controls Menu */
			case 28:
				if (changedProgramState) {
					UPDATE_CONTROLS_MENU_CURSOR_POSITION_Y();
					changedProgramState = false;
				}
				/* Key Presses */
				MENU_HANDLE_BACK_BUTTON_WITH_SETTINGS(13);
				if (KEY_PRESSED(INPUT_LEFT)) {
					switch (menuCursorIndex_controls) {
						case 0:
							controlSettings.swapConfirmAndBack = !controlSettings.swapConfirmAndBack;
							CONTROLS_SET_CONFIRM_BACK_POS();
							break;
						case 1:
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
							break;
						default:
							break;
					}
				}
#if !defined(ANDROID) && !defined(PSP)
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) &&
					(MOUSE_IS_IN_RECT_WITH_SETTING(text_Controller_Input.rect, CONTROLS_MENU_ENDPOINT)
					|| MOUSE_IS_IN_RECT_WITH_SETTING(text_Touch_Screen_Input.rect, CONTROLS_MENU_ENDPOINT)))) {
#else
				if (KEY_PRESSED(INPUT_RIGHT) || KEY_PRESSED(INPUT_CONFIRM) || (KEY_PRESSED(INPUT_CONFIRM_ALT) &&
					(MOUSE_IS_IN_RECT_WITH_SETTING(text_Controller_Input.rect, CONTROLS_MENU_ENDPOINT)))) {
#endif
					switch (menuCursorIndex_controls) {
						case 0:
							controlSettings.swapConfirmAndBack = !controlSettings.swapConfirmAndBack;
							CONTROLS_SET_CONFIRM_BACK_POS();
							break;
						case 1:
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
							break;
						default:
							break;
					}
				}
#if !defined(ANDROID) && !defined(PSP)
				CONTROLS_MENU_HANDLE_VERT_CURSOR_MOVEMENT();
#endif
				if (MOUSE_MOVED()) {
					CONTROLS_MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(text_Controller_Input, 0);
#if !defined(ANDROID) && !defined(PSP)
					CONTROLS_MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(text_Touch_Screen_Input, 1);
#endif
				}
				/* Animate Cursor */
				UPDATE_CONTROLS_MENU_CURSOR_POSITION_X();
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				RENDER_TEXT(text_Controller_Input);
#if !defined(ANDROID) && !defined(PSP)
				RENDER_TEXT(text_Touch_Screen_Input);
#endif
				if (controlSettings.swapConfirmAndBack) {
					RENDER_TEXT(text_A_Confirm);
					RENDER_TEXT(text_B_Back);
				} else {
					RENDER_TEXT(text_B_Confirm);
					RENDER_TEXT(text_A_Back);
				}
#if !defined(ANDROID) && !defined(PSP)
				if (controlSettings.enableTouchscreen) {
					RENDER_TEXT(text_Enabled);
				} else {
					RENDER_TEXT(text_Disabled);
				}
#endif
				break;
			default:
				break;
		}

		/* Miscellaneous */
		controllerAxis_leftStickX_last = controllerAxis_leftStickX;
		controllerAxis_leftStickY_last = controllerAxis_leftStickY;
		if (KEY_PRESSED(INPUT_CONFIRM_ALT)) { // fix the cursor resetting back to the last-tapped position
			mouseInput_x = 0;
			mouseInput_y = 0;
		}
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;

		/* Draw Black Rectangles (to fix background scrolling bug for some aspect ratios in fullscreen) */
		SDL_RenderFillRect(renderer, &rightRect);
		SDL_RenderFillRect(renderer, &bottomRect);

		/* Update Screen */
        SDL_RenderPresent(renderer);
	}

	SDL_DESTROY_ALL();
	SYSTEM_SPECIFIC_CLOSE();

	return 0;
}