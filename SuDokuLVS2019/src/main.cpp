#include "main.h"
#include "game_logic.h"
#include "general.h"
#include "menu_logic.h"
#include "sound_logic.h"
#include "transitions.h"
#include "sudokuGen.h"
#include "puzzleBank.h"
#include "window.h"
#include "text_objects.h"
#include "include_fonts.h"
#include "include_graphics.h"
#include "include_music.h"
#include "include_sfx.h"

bool isContinue = false;
bool showFPS = false;
#if defined(THREEDS)
bool useNew3DSClockSpeed = true;
#endif

#if defined(EMSCRIPTEN)
void mainloop() {
#elif defined(ANDROID)
int SDL_main(int argv, char** args) {
#else
int main(int argv, char** args) {
#endif
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

#if defined(PSP) || defined(SDL1)
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0) {
#else
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS) != 0) {
#endif
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
#endif
#if !defined(EMSCRIPTEN)
		return 1;
#endif
	}

#if defined(SDL1) && !defined(PC)
	SDL_ShowCursor(0);
#endif

	/* [3DS] Enable New 3DS clock speed*/
#if defined(THREEDS)
	osSetSpeedupEnable(useNew3DSClockSpeed);
#endif

	TTF_Init();

#if !defined(SDL1)
	SDL_GetCurrentDisplayMode(0, &DM);
	displayRefreshRate = DM.refresh_rate;
#else
	displayRefreshRate = 60;
#endif

	initDefaultBGScale();
	initDefaultFrameRate();
	initDefaultWindowedSetting();

	/* Get settings from settings.bin */
	loadSettingsFile();
	/* Set Video Settings */
#if !defined(ANDROID)
	switch (videoSettings.aspectRatioIndex) {
		case 1:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_4_3)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_4_3[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_4_3)];
			break;
		case 2:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_9)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_9[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_9)];
			break;
		case 3:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_16_10)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_16_10[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_16_10)];
			break;
		case 4:
			videoSettings.widthSetting = RESOLUTION_OPTIONS_WIDTH_1_1[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_WIDTH_1_1)];
			videoSettings.heightSetting = RESOLUTION_OPTIONS_HEIGHT_1_1[videoSettings.resolutionIndex % LEN(RESOLUTION_OPTIONS_HEIGHT_1_1)];
			break;
		default:
			videoSettings.widthSetting = 0;
			videoSettings.heightSetting = 0;
	}
#else
	videoSettings.widthSetting = SYSTEM_WIDTH;
	videoSettings.heightSetting = SYSTEM_HEIGHT;
	SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");
	SDL_SetHint(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, "1");
	SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
#endif
#if defined(THREEDS)
	if (addon134Settings.windowedSetting) {
		SYSTEM_WIDTH = 400;
	} else {
		SYSTEM_WIDTH = 320;
	}
	gameWidth = SYSTEM_WIDTH;
	gameHeight = SYSTEM_HEIGHT;
#else
	gameWidth = videoSettings.widthSetting;
	gameHeight = videoSettings.heightSetting;
#endif
	if (gameWidth == 0 || gameHeight == 0) {
		setNativeResolution();
	}
	if (gameWidth < 240) {
		gameWidth = 240;
	}
	if (gameHeight < 240) {
		gameHeight = 240;
	}
	if (gameWidth > SYSTEM_WIDTH) {
		gameWidth = SYSTEM_WIDTH;
	}
	if (gameHeight > SYSTEM_HEIGHT) {
		gameHeight = SYSTEM_HEIGHT;
	}
	compactDisplay = (gameHeight * 4 / 3) - 2 > gameWidth;

	initStartingWidthHeightMults();
	initStartingTextVariables();
	setBGScrollSpeed();

	/* Set Window/Renderer */
#if defined(FUNKEY)
	SDL_WM_SetCaption("SuDokuL", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(SYSTEM_WIDTH, SYSTEM_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
#elif defined(SDL1)
	SDL_WM_SetCaption("SuDokuL", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(SYSTEM_WIDTH, SYSTEM_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
#if defined(PSP)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#elif defined(EMSCRIPTEN)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gameWidth, gameHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#elif defined(THREEDS)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED_DISPLAY(!addon134Settings.windowedSetting), SDL_WINDOWPOS_CENTERED_DISPLAY(addon134Settings.windowedSetting), gameWidth, gameHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
#elif !defined(PC)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#endif
#endif
	setScaling();

	/* Set only things that are used on the initial loading screen */
	/* Set Textures */
	setBGType();
	setFrameRateByOptions(0);
	/* Set Rectangles */
	updateBorderRects();
	/* General - Fonts */
	pixelFont = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, fontSize);
	char tempCharArr[2];
	tempCharArr[1] = '\0';
	/* General */
	for (Sint8 k = 32; k < LEN(textChars); k++) {
		tempCharArr[0] = k;
		setTextCharWithOutline(tempCharArr, pixelFont, color_white, color_black, &textChars[k], 1, 0, 0, false, false);
	}
	/* Loading Screen */
	SET_TEXT_WITH_OUTLINE("Loading...", text_Loading, OBJ_TO_MID_SCREEN_X(text_Loading), TEXT_LOADING_Y);

	/* Render loading screen */
#if !(defined(PC) || defined(SWITCH))
	updateGlobalTimer();
	deltaTime = (timer_global.now - timer_global.last);
	renderBackground();
	renderText(&text_Loading);
	renderBorderRects();
#if !defined(SDL1)
	SDL_RenderPresent(renderer);
#else
	SDL_Flip(windowScreen);
#endif
	preparePauseTimer();
#endif

	/* Initialize Sound */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
#if !(defined(ANDROID) || defined(SDL1))
		SDL_Log(Mix_GetError());
#endif
	}
	bgm_1 = Mix_LoadMUS_RW(SDL_RWFromConstMem(dgtlnnv2_mod, dgtlnnv2_mod_len), 1);
	bgm_2 = Mix_LoadMUS_RW(SDL_RWFromConstMem(sudoku_padawan_mod, sudoku_padawan_mod_len), 1);
	bgm_3 = Mix_LoadMUS_RW(SDL_RWFromConstMem(electroq_mod, electroq_mod_len), 1);
	bgm_4 = Mix_LoadMUS_RW(SDL_RWFromConstMem(mainmenu_mod, mainmenu_mod_len), 1);
	bgm_5 = Mix_LoadMUS_RW(SDL_RWFromConstMem(insomnia_mod, insomnia_mod_len), 1);
	bgm_6 = Mix_LoadMUS_RW(SDL_RWFromConstMem(ontario_mod, ontario_mod_len), 1);
	bgm_7 = Mix_LoadMUS_RW(SDL_RWFromConstMem(addicti_mod, addicti_mod_len), 1);
	bgm_8 = Mix_LoadMUS_RW(SDL_RWFromConstMem(ancient_days__mod, ancient_days__mod_len), 1);
	sfx = Mix_LoadWAV_RW(SDL_RWFromConstMem(coin1_wav, coin1_wav_len), 1);
	Mix_VolumeMusic((int)(soundSettings.bgmVolume * 128.0 / 100));
	Mix_Volume(SFX_CHANNEL, (int)(soundSettings.sfxVolume * 128.0 / 100));

	/* Controller */
#if defined(SDL1)
	SDL_JoystickEventState(SDL_ENABLE);
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		SDL_Joystick *gameController = SDL_JoystickOpen(i);
		if (gameController) {
			controllers.push_back(gameController);
		}
}
	SDL_JoystickEventState(SDL_ENABLE);
#elif defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		SDL_Joystick *gameController = SDL_JoystickOpen(i);
		if (gameController) {
			controllers.push_back(gameController);
		}
	}
#else
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			SDL_GameController *gameController = SDL_GameControllerOpen(i);
			if (gameController) {
				controllers.push_back(gameController);
			}
		}
	}
#endif

	/* Set Background Scrolling Variables */
	//bgSettings.scrollDir = 22;
	//setBGScrollSpeed();
	//bgSettings.speedMult = 15;
	//bgSettings.scale = max(min((int)min(gameWidthMult, gameHeightMult), 5), 1);

	/* Set Textures */
	prepareLogo();
	if (gameHeightMult < 1.5) {
		prepareSprite(menuCursor, menu_cursor_png, menu_cursor_png_len, 0, 0, 2, true, ROUND_DOWN);
	} else {
		prepareSprite(menuCursor, menu_cursor_png, menu_cursor_png_len, 0, 0, 2, true, NO_ROUND);
	}
	prepareSprite(game_grid_1, grid_384_1_png, grid_384_1_png_len, 0, 0, 2, true, NO_ROUND);
	SDL_Surface *game_grid_2_clean = prepareGridSurface(game_grid_2, grid_384_2_png, grid_384_2_png_len, 0, 0);
	SDL_Surface *game_grid_2_blit;
	prepareSprite(game_grid_3, grid_384_3_png, grid_384_3_png_len, 0, 0, 2, true, NO_ROUND);
	if (!compactDisplay) {
		gridPosX = (Uint16)((gameWidth / 2) - (game_grid_2.rect.w / 2) + (game_grid_2.rect.w * 5 / 24));
		gridPosY = (Uint16)((gameHeight - game_grid_2.rect.w) / 2);
	} else {
		gridPosX = (Sint16)((gameWidth / 2) - (game_grid_2.rect.w / 2));
		gridPosY = (Sint16)((gameHeight - game_grid_2.rect.w) * 875 / 1000);
	}
	game_grid_1.rect.x = gridPosX;
	game_grid_1.rect.y = gridPosY;
	game_grid_2.rect.x = gridPosX;
	game_grid_2.rect.y = gridPosY + game_grid_1.rect.h;
	game_grid_3.rect.x = gridPosX;
	game_grid_3.rect.y = gridPosY + game_grid_1.rect.h + game_grid_2.rect.h;
	initStartingSharedVariables();
	bg_max_x = game_grid_2.rect.x + game_grid_2.rect.w - tile->rect.w;
	bg_max_y = game_grid_3.rect.y - tile->rect.h;
	prepareSprite(gridCursor_bottom_left, grid_cursor_bottom_left_png, grid_cursor_bottom_left_png_len, 0, 0, 2, true, ROUND_UP);
	prepareSprite(gridCursor_bottom_right, grid_cursor_bottom_right_png, grid_cursor_bottom_right_png_len, 0, 0, 2, true, ROUND_UP);
	prepareSprite(gridCursor_top_left, grid_cursor_top_left_png, grid_cursor_top_left_png_len, 0, 0, 2, true, ROUND_UP);
	prepareSprite(gridCursor_top_right, grid_cursor_top_right_png, grid_cursor_top_right_png_len, 0, 0, 2, true, ROUND_UP);
	gridCursorCornerStep = gridCursor_bottom_left.rect.w / 3;
	prepareSidebar();
	prepareSprite(miniGrid_shared_1, grid_mini_1_png, grid_mini_1_png_len, 0, 0, 2, true, NO_ROUND);
	prepareSprite(miniGrid_shared_2, grid_mini_2_png, grid_mini_2_png_len, 0, 0, GRAPHICS_SCALE, false, NO_ROUND);
	prepareSprite(miniGrid_shared_3, grid_mini_3_png, grid_mini_3_png_len, 0, 0, 2, true, NO_ROUND);
	prepareSprite(miniGrid_bottom_left, grid_mini_bottom_left_png, grid_mini_bottom_left_png_len, 0, 0, GRAPHICS_SCALE, true, NO_ROUND);
	prepareSprite(miniGrid_bottom_right, grid_mini_bottom_right_png, grid_mini_bottom_right_png_len, 0, 0, GRAPHICS_SCALE, true, NO_ROUND);
	prepareSprite(miniGrid_top_left, grid_mini_top_left_png, grid_mini_top_left_png_len, 0, 0, GRAPHICS_SCALE, true, NO_ROUND);
	prepareSprite(miniGrid_top_right, grid_mini_top_right_png, grid_mini_top_right_png_len, 0, 0, GRAPHICS_SCALE, true, NO_ROUND);

	/* Set Rectangles */
	//divider.w = gameWidth * 17 / 20;
	//divider.h = gameHeight / 96;
	//divider.x = (gameWidth - divider.w) / 2;
	//divider.y = 0;

	/* Set Text */
	/* General - Fonts */
	pixelFont_large = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, (int)(fontSize * 1.5));
	pixelFont_grid = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, gridNumSize);
	pixelFont_grid_mini = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, (int)gridSizeA);
	/* General (Large) */
	Sint8 extraOffsetY = (gameHeight < 480) ? 1 : 0;
	for (Sint8 k = 32; k < 91; k++) {
		tempCharArr[0] = k;
		setTextCharWithOutline(tempCharArr, pixelFont_large, color_light_blue, color_blue, &textChars_large[k], 2, 0, 0, false, false);
	}
	/* Grid Player Numbers */
	for (Sint8 k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid, color_gray_240, color_black, &gridNums_black[k], 2, 0, extraOffsetY, true, true);
	}
	for (Sint8 k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid, color_light_blue, color_blue, &gridNums_blue[k], 2, 0, extraOffsetY, true, false);
	}
	for (Sint8 k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid_mini, color_light_blue, color_blue, &gridNums_blue_mini[k], 1, 0, 0, true, false);
	}
	/* Test Strings */
	//SET_TEXT_WITH_OUTLINE("A B C D E F G H I J K L M", text_test_1, OBJ_TO_MID_SCREEN_X(text_test_1), fontSize * 1);
	//SET_TEXT_WITH_OUTLINE("N O P Q R S T U V W X Y Z", text_test_2, OBJ_TO_MID_SCREEN_X(text_test_2), fontSize * 3);
	//SET_TEXT_WITH_OUTLINE("a b c d e f g h i j k l m", text_test_3, OBJ_TO_MID_SCREEN_X(text_test_3), fontSize * 5);
	//SET_TEXT_WITH_OUTLINE("n o p q r s t u v w x y z", text_test_4, OBJ_TO_MID_SCREEN_X(text_test_4), fontSize * 7);
	//SET_TEXT_WITH_OUTLINE("1 2 3 4 5 6 7 8 9 0",       text_test_5, OBJ_TO_MID_SCREEN_X(text_test_5), fontSize * 9);
	//SET_TEXT_WITH_OUTLINE("! \" ( ) + , - . / = :",    text_test_6, OBJ_TO_MID_SCREEN_X(text_test_6), fontSize * 11);
	//SET_TEXT_WITH_OUTLINE("The quick brown fox",       text_test_7, OBJ_TO_MID_SCREEN_X(text_test_7), fontSize * 13);
	//SET_TEXT_WITH_OUTLINE("jumped over the lazy dog",  text_test_8, OBJ_TO_MID_SCREEN_X(text_test_8), fontSize * 15);
	/* Title Screen */
#if defined(SWITCH) || defined(WII)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press +",     text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#elif !defined(PC)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Start", text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#else
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Enter", text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#endif
	SET_TEXT_WITH_OUTLINE_ANIMATED("v1.4",    text_Version_Number, (gameWidth - (text_Version_Number.rect.w * 1.25)), TEXT_VERSION_NUMBER_Y);
	if (compactDisplay) {
		text_Version_Number.endPos_x = text_Version_Number.startPos_x + (gameWidth * 8 / 32);
	} else {
		text_Version_Number.endPos_x = text_Version_Number.startPos_x + (gameWidth * 7 / 32);
	}
	/* Main Menu */
	SET_TEXT_WITH_OUTLINE_ANIMATED("Play",     text_Play,             OBJ_TO_MID_SCREEN_X(text_Play),       TEXT_PLAY_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Controls", text_Controls,         OBJ_TO_MID_SCREEN_X(text_Controls),   TEXT_CONTROLS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Options",  text_Options,          OBJ_TO_MID_SCREEN_X(text_Options),    TEXT_OPTIONS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Credits",  text_Credits,          OBJ_TO_MID_SCREEN_X(text_Credits),    TEXT_CREDITS_Y + (gameWidth * 3 / 4));
#if !defined(NO_QUIT)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Quit",     text_Quit,             OBJ_TO_MID_SCREEN_X(text_Quit),       TEXT_QUIT_Y + (gameWidth * 3 / 4));
#endif
	/* Continue Menu */
	SET_TEXT_WITH_OUTLINE("Continue",         text_Continue,         OBJ_TO_MID_SCREEN_X(text_Continue),   TEXT_CONTINUE_Y);
	SET_TEXT_WITH_OUTLINE("New Game",         text_New_Game,         OBJ_TO_MID_SCREEN_X(text_New_Game),   TEXT_NEW_GAME_Y);
	/* Play Menu */
	SET_TEXT_WITH_OUTLINE("Easy",             text_Easy,             OBJ_TO_MID_SCREEN_X(text_Easy),       TEXT_EASY_Y);
	SET_TEXT_WITH_OUTLINE("Normal",           text_Normal,           OBJ_TO_MID_SCREEN_X(text_Normal),     TEXT_NORMAL_Y);
	SET_TEXT_WITH_OUTLINE("Hard",             text_Hard,             OBJ_TO_MID_SCREEN_X(text_Hard),       TEXT_HARD_Y);
	SET_TEXT_WITH_OUTLINE("Very Hard",        text_Very_Hard,        OBJ_TO_MID_SCREEN_X(text_Very_Hard),  TEXT_VERY_HARD_Y);
	/* Game */
	SET_TEXT_WITH_OUTLINE("Time",             text_Time,             OBJ_TO_MID_RECT_X(gameSidebarSmall1Rect, text_Time),        TEXT_TIME_Y);
	SET_TEXT_WITH_OUTLINE("Empty",            text_Empty,            OBJ_TO_MID_RECT_X(gameSidebarSmall2Rect, text_Empty),       TEXT_EMPTY_Y);
	SET_TEXT_WITH_OUTLINE("Easy",             text_Game_Easy,        OBJ_TO_MID_RECT_X(gameSidebarSmall3Rect, text_Game_Easy),   TEXT_GAME_EASY_Y);
	SET_TEXT_WITH_OUTLINE("Normal",           text_Game_Normal,      OBJ_TO_MID_RECT_X(gameSidebarSmall3Rect, text_Game_Normal), TEXT_GAME_NORMAL_Y);
	SET_TEXT_WITH_OUTLINE("Hard",             text_Game_Hard,        OBJ_TO_MID_RECT_X(gameSidebarSmall3Rect, text_Game_Hard),   TEXT_GAME_HARD_Y);
	SET_TEXT_WITH_OUTLINE("V.Hard",           text_Game_VHard,       OBJ_TO_MID_RECT_X(gameSidebarSmall3Rect, text_Game_VHard),  TEXT_GAME_VHARD_Y);
	SET_TEXT_WITH_OUTLINE("Paused",           text_Paused,           OBJ_TO_MID_SCREEN_X(text_Paused),     TEXT_PAUSED_Y);
#if defined(SWITCH)
	SET_TEXT_WITH_OUTLINE("Press - to",       text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Press Back to",    text_Quit_to_Menu_1, OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(WII)
	SET_TEXT_WITH_OUTLINE("Press -/Z to",     text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(GAMECUBE)
	SET_TEXT_WITH_OUTLINE("Press Z to",       text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif !defined(PC)
	SET_TEXT_WITH_OUTLINE("Press Select to",  text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#else
	SET_TEXT_WITH_OUTLINE("Press Q/Select to", text_Quit_to_Menu_1,  OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#endif
	SET_TEXT_WITH_OUTLINE("Save and Quit",    text_Quit_to_Menu_2,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_2), TEXT_QUIT_TO_MENU_Y + (CONTROLS_SPACER * 2));
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("You Win!",     text_You_Win,          OBJ_TO_MID_SCREEN_X(text_You_Win),        TEXT_YOU_WIN_Y);
		SET_TEXT_WITH_OUTLINE("Amazing! You're a sudoku master!", text_Wow_Incredible, OBJ_TO_MID_SCREEN_X(text_Wow_Incredible), TEXT_YOU_WIN_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("You Win!",     text_You_Win,          OBJ_TO_MID_SCREEN_X(text_You_Win),        TEXT_QUIT_TO_MENU_Y);
		SET_TEXT_WITH_OUTLINE("Wow! You're a sudoku master!", text_Wow_Incredible, OBJ_TO_MID_SCREEN_X(text_Wow_Incredible), TEXT_QUIT_TO_MENU_Y);
	}
	/* Controls */
	setControlsText();
	controlsSetConfirmBackPos();
	/* Options Menu */
	SET_TEXT_WITH_OUTLINE("Controls",         text_Controls_Menu,    OBJ_TO_MID_SCREEN_X(text_Controls_Menu), TEXT_CONTROLS_MENU_Y);
	SET_TEXT_WITH_OUTLINE("Video",            text_Video,            OBJ_TO_MID_SCREEN_X(text_Video),      TEXT_VIDEO_Y);
	SET_TEXT_WITH_OUTLINE("Sound",            text_Sound,            OBJ_TO_MID_SCREEN_X(text_Sound),      TEXT_SOUND_Y);
	SET_TEXT_WITH_OUTLINE("Background",       text_Background,       OBJ_TO_MID_SCREEN_X(text_Background), TEXT_BACKGROUND_Y);
	//SET_TEXT_WITH_OUTLINE("Scores",           text_Scores,           OBJ_TO_MID_SCREEN_X(text_Scores),     TEXT_SCORES_Y);
	/* Controls Menu */
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Controller Input", text_Controller_Input, CONTROLS_MENU_CURSOR_POSITION_X, TEXT_CONTROLLER_INPUT_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Button Input", text_Controller_Input, CONTROLS_MENU_CURSOR_POSITION_X, TEXT_CONTROLLER_INPUT_Y);
	}
#if defined(WII)
	SET_TEXT_WITH_OUTLINE("Wiimote Controls", text_Touch_Screen_Input, CONTROLS_MENU_CURSOR_POSITION_X, TEXT_TOUCH_SCREEN_INPUT_Y);
#elif defined(MOUSE_INPUT) && !(defined(ANDROID) || defined(THREEDS))
	SET_TEXT_WITH_OUTLINE("Touch Screen",     text_Touch_Screen_Input, CONTROLS_MENU_CURSOR_POSITION_X, TEXT_TOUCH_SCREEN_INPUT_Y);
#else
	SET_TEXT_WITH_OUTLINE("",                 text_Touch_Screen_Input, CONTROLS_MENU_CURSOR_POSITION_X, TEXT_TOUCH_SCREEN_INPUT_Y);
#endif
#if defined(VITA) || defined(PSP)
	SET_TEXT_WITH_OUTLINE("X - Confirm", text_A_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_A_Confirm, 0.75), TEXT_A_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("O - Back", text_B_Back, OBJ_TO_SCREEN_AT_FRACTION(text_B_Back, 0.75), TEXT_B_BACK_Y);
	SET_TEXT_WITH_OUTLINE("O - Confirm", text_B_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_B_Confirm, 0.75), TEXT_B_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("X - Back", text_A_Back, OBJ_TO_SCREEN_AT_FRACTION(text_A_Back, 0.75), TEXT_A_BACK_Y);
#elif defined(WII)
	SET_TEXT_WITH_OUTLINE("A/2 - Confirm", text_A_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_A_Confirm, 0.75), TEXT_A_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("B/1 - Back", text_B_Back, OBJ_TO_SCREEN_AT_FRACTION(text_B_Back, 0.75), TEXT_B_BACK_Y);
	SET_TEXT_WITH_OUTLINE("B/1 - Confirm", text_B_Confirm, OBJ_TO_SCREEN_AT_FRACTION(text_B_Confirm, 0.75), TEXT_B_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("A/2 - Back", text_A_Back, OBJ_TO_SCREEN_AT_FRACTION(text_A_Back, 0.75), TEXT_A_BACK_Y);
#else
	SET_TEXT_WITH_OUTLINE("A - Confirm",      text_A_Confirm,        OBJ_TO_SCREEN_AT_FRACTION(text_A_Confirm, 0.75), TEXT_A_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("B - Back",         text_B_Back,           OBJ_TO_SCREEN_AT_FRACTION(text_B_Back,    0.75), TEXT_B_BACK_Y);
	SET_TEXT_WITH_OUTLINE("B - Confirm",      text_B_Confirm,        OBJ_TO_SCREEN_AT_FRACTION(text_B_Confirm, 0.75), TEXT_B_CONFIRM_Y);
	SET_TEXT_WITH_OUTLINE("A - Back",         text_A_Back,           OBJ_TO_SCREEN_AT_FRACTION(text_A_Back,    0.75), TEXT_A_BACK_Y);
#endif
#if defined(WII)
	SET_TEXT_WITH_OUTLINE("Horizontal Focus", text_WiimoteScheme_Horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_WiimoteScheme_Horizontal, 0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
	SET_TEXT_WITH_OUTLINE("General",          text_WiimoteScheme_General, OBJ_TO_SCREEN_AT_FRACTION(text_WiimoteScheme_General, 0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
	SET_TEXT_WITH_OUTLINE("Vertical Focus",   text_WiimoteScheme_Vertical, OBJ_TO_SCREEN_AT_FRACTION(text_WiimoteScheme_Vertical, 0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
#elif defined(MOUSE_INPUT) && !(defined(ANDROID) || defined(THREEDS))
	SET_TEXT_WITH_OUTLINE("Enabled",          text_Enabled,          OBJ_TO_SCREEN_AT_FRACTION(text_Enabled,   0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
	SET_TEXT_WITH_OUTLINE("Disabled",         text_Disabled,         OBJ_TO_SCREEN_AT_FRACTION(text_Disabled,  0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
#else
	SET_TEXT_WITH_OUTLINE("",                 text_Enabled,         OBJ_TO_SCREEN_AT_FRACTION(text_Enabled,    0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
	SET_TEXT_WITH_OUTLINE("",                 text_Disabled,        OBJ_TO_SCREEN_AT_FRACTION(text_Disabled,   0.75), TEXT_TOUCH_SCREEN_INPUT_Y);
#endif
	/* Video Menu */
#if !(defined(ANDROID) || defined(THREEDS))
	SET_TEXT_WITH_OUTLINE("Resolution",       text_Resolution,       VIDEO_MENU_CURSOR_POSITION_X,         TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("x",                text_x,                0,                                    TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Aspect Ratio",     text_Aspect_Ratio,     VIDEO_MENU_CURSOR_POSITION_X,         TEXT_ASPECT_RATIO_Y);
#endif
	SET_TEXT_WITH_OUTLINE(":",                text_colon,            0,                                    TEXT_ASPECT_RATIO_Y);
	SET_TEXT_WITH_OUTLINE("Native",           text_Native_Res,       VIDEO_MENU_NUM_POSITION_X,            TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Native 4:3",       text_Native_4_3,       VIDEO_MENU_NUM_POSITION_X,            TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Native 16:9",      text_Native_16_9,      VIDEO_MENU_NUM_POSITION_X,            TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Native 16:10",     text_Native_16_10,     VIDEO_MENU_NUM_POSITION_X,            TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Native 1:1",       text_Native_1_1,       VIDEO_MENU_NUM_POSITION_X,            TEXT_RESOLUTION_Y);
	SET_TEXT_WITH_OUTLINE("Native",           text_Native_Aspect,    VIDEO_MENU_NUM_POSITION_X,            TEXT_ASPECT_RATIO_Y);
	SET_TEXT_WITH_OUTLINE("Frame Rate",       text_Frame_Rate,       VIDEO_MENU_CURSOR_POSITION_X,         TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("Uncapped",         text_Frame_Rate_Uncapped, VIDEO_MENU_NUM_POSITION_X,         TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("20 FPS",           text_Frame_Rate_20,    VIDEO_MENU_NUM_POSITION_X,            TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("30 FPS",           text_Frame_Rate_30,    VIDEO_MENU_NUM_POSITION_X,            TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("40 FPS",           text_Frame_Rate_40,    VIDEO_MENU_NUM_POSITION_X,            TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("50 FPS",           text_Frame_Rate_50,    VIDEO_MENU_NUM_POSITION_X,            TEXT_FRAME_RATE_Y);
	SET_TEXT_WITH_OUTLINE("60 FPS",           text_Frame_Rate_60,    VIDEO_MENU_NUM_POSITION_X,            TEXT_FRAME_RATE_Y);
#if defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Status Bar",       text_Integer_Scale,    VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Show",             text_On,               VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Hide",             text_Off,              VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
#elif defined(THREEDS)
	SET_TEXT_WITH_OUTLINE("Display", text_Integer_Scale, VIDEO_MENU_CURSOR_POSITION_X, TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Top Screen", text_On, VIDEO_MENU_NUM_POSITION_X, TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Bottom Screen", text_Off, VIDEO_MENU_NUM_POSITION_X, TEXT_INTEGER_SCALE_Y);
#else
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Integer Scale", text_Integer_Scale,   VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Int. Scale",   text_Integer_Scale,    VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	}
	SET_TEXT_WITH_OUTLINE("On",               text_On,               VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Off",              text_Off,              VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
#endif
#if !defined(NO_QUIT)
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Exit Game and Apply Changes", text_Apply, VIDEO_MENU_CURSOR_POSITION_X,     TEXT_APPLY_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Quit and Apply Changes", text_Apply,  VIDEO_MENU_CURSOR_POSITION_X,         TEXT_APPLY_Y);
	}
#else
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Save Changes (Restart To Apply)", text_Apply, VIDEO_MENU_CURSOR_POSITION_X, TEXT_APPLY_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Save (Restart To Apply)", text_Apply, VIDEO_MENU_CURSOR_POSITION_X, TEXT_APPLY_Y);
	}
#endif
	/* Music Menu */
	SET_TEXT_WITH_OUTLINE("Music",            text_Music,            SOUND_MENU_CURSOR_POSITION_X,         TEXT_MUSIC_Y);
	SET_TEXT_WITH_OUTLINE("Music Volume",     text_Music_Volume,     SOUND_MENU_CURSOR_POSITION_X,         TEXT_MUSIC_VOLUME_Y);
	SET_TEXT_WITH_OUTLINE("SFX Volume",       text_SFX_Volume,       SOUND_MENU_CURSOR_POSITION_X,         TEXT_SFX_VOLUME_Y);
	SET_TEXT_WITH_OUTLINE("Reset To Default", text_Reset_to_Default_1, SOUND_MENU_CURSOR_POSITION_X,       TEXT_RESET_TO_DEFAULT_1_Y);
	/* Background Menu */
	SET_TEXT_WITH_OUTLINE("Type",             text_Background_Type,  BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_BACKGROUND_TYPE_Y);
	SET_TEXT_WITH_OUTLINE("Size",             text_Background_Size,  BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_BACKGROUND_SIZE_Y);
	SET_TEXT_WITH_OUTLINE("Scroll Speed",     text_Scroll_Speed,     BACKGROUND_MENU_CURSOR_POSITION_X,    TEXT_SCROLL_SPEED_Y);
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Scroll Direction", text_Scroll_Direction, BACKGROUND_MENU_CURSOR_POSITION_X, TEXT_SCROLL_DIRECTION_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Scroll Dir.", text_Scroll_Direction, BACKGROUND_MENU_CURSOR_POSITION_X, TEXT_SCROLL_DIRECTION_Y);
	}
	SET_TEXT_WITH_OUTLINE("Reset To Default", text_Reset_to_Default_2, BACKGROUND_MENU_CURSOR_POSITION_X,  TEXT_RESET_TO_DEFAULT_2_Y);
	/* Credits */
	setCreditsText();

	/* Set Initial Time Values */
	//timer_global.now = (SDL_GetTicks() - timer_paused.now) / 1000.0;
	time_anim1 = 0;

	/* Set Other Initial Variable Values */
	menuCursorIndex_main = 0;
	menuCursorIndex_continue = 1;
	menuCursorIndex_play = 0;
	menuCursorIndex_options = 0;
	menuCursorIndex_controls = 0;
	menuCursorIndex_video = 0;
	menuCursorIndex_sound = 0;
	menuCursorIndex_background = 0;
	programState = 0;
	time_anim_PressStart = 0;
	isRunning = true;

#if defined(ANDROID)
	sdlToggleFullscreen();
#endif

#if !(defined(PC) || defined(SWITCH))
	updatePauseTimer();
#endif

	while (isRunning) {
		/* Update Timers */
		updateGlobalTimer();
		deltaTime = timer_global.now - timer_global.last;
		time_anim1 += deltaTime;
		if (heldDirs > 0) {
			timer_buttonHold += deltaTime;
		} else {
			timer_buttonHold = 0;
			timer_buttonHold_repeater = 0;
		}
#if defined(SDL1)
		SDL_FillRect(windowScreen, NULL, 0x000000);
#else
		SDL_RenderClear(renderer);
#endif

		handlePlayerInput();

		/* Key Presses (Always Active) */
		if (keyPressed(INPUT_FULLSCREEN)) {
			sdlToggleFullscreen();
		}
		if (keyPressed(INPUT_PREV_TRACK) && wentPastTitleScreen) {
			if (--soundSettings.musicIndex < 1)
				soundSettings.musicIndex = 8;
			playMusicAtIndex(soundSettings.musicIndex);
#if !defined(WII_U) // SDL2 counts the "Close Software" button as pressing L for... some reason
			if (programState != 20) { // If you save in the Video settings menu, possible undesired video settings would also be saved (this could be fixed, but it's just not worth the trouble for such a small issue)
				saveCurrentSettings();
			}
#endif
		}
		if (keyPressed(INPUT_NEXT_TRACK) && wentPastTitleScreen) {
			if (++soundSettings.musicIndex > 8)
				soundSettings.musicIndex = 1;
			playMusicAtIndex(soundSettings.musicIndex);
#if !defined(WII_U) // SDL2 counts the "Close Software" button as pressing L for... some reason
			if (programState != 20) {
				saveCurrentSettings();
			}
#endif
		}

		if (windowSizeChanged) {
#if defined(PC) && !defined(SDL1)
			if (SDL_GetWindowSurface(window)->w < gameWidth)
				SDL_SetWindowSize(window, gameWidth, SDL_GetWindowSurface(window)->h);
			if (SDL_GetWindowSurface(window)->h < gameHeight)
				SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, gameHeight);
			// If you resize the window to within 6% of an integer ratio, snap to that ratio
			snapWindow_x(0.06, gameWidth);
			snapWindow_y(0.06, gameHeight);
			setScaling();
#endif
			windowSizeChanged = false;
		}

		/* Clear Screen */
		// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		// SDL_RenderClear(renderer);

		/* Draw Tile Background */
		if (programState == 9 || programState == 11) {
			renderBackgroundNotBehindGrid();
		} else {
			renderBackground();
		}

		switch (programState) {
			/* 0 = Title Screen */
			case 0:
				time_anim_PressStart += deltaTime;
#if defined(FUNKEY)
				if (time_anim_PressStart >= 2.5) {
					time_anim_PressStart -= 2.5;
				}
#endif
				/* Key Presses */
				if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT) || keyPressed(INPUT_START)) {
					Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
					if (!wentPastTitleScreen) {
						wentPastTitleScreen = true;
						playMusicAtIndex(soundSettings.musicIndex);
					}
					time_anim1 = 0;
					programState = 1;
				}
				/* Animate Text */
				text_PressStart.rect.y = (Sint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, text_pressStartAmplitude));
				/* Draw Logo and Text */
				renderLogo();
				renderText(&text_PressStart);
				renderText(&text_Version_Number);
				break;
			/* 1 = Title Screen -> Main Menu */
			case 1:
				transitionGraphicsFromTitleScreen();
				transitionGraphicsToMainMenu(-1);
				transitionToStateWithTimer(time_anim1, 1, 2);
				updateMenuCursorPositionY(menuCursorIndex_main);
				text_PressStart.rect.y = (Sint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, text_pressStartAmplitude));
				if (buttonHeld(INPUT_LEFT) && keyPressed(INPUT_SWAP)) {
					showFPS = !showFPS;
				}
#if defined(THREEDS)
				if (buttonHeld(INPUT_DOWN) && buttonHeld(INPUT_RIGHT) && keyPressed(INPUT_SWAP)) {
					useNew3DSClockSpeed = !useNew3DSClockSpeed;
					osSetSpeedupEnable(useNew3DSClockSpeed);
				}
#endif
				break;
			/* 2 = Main Menu */
			case 2:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_main);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
#if !defined(NO_QUIT)
				menuHandleVertCursorMovement(menuCursorIndex_main, 5, 0);
#else
				menuHandleVertCursorMovement(menuCursorIndex_main, 4, 0);
#endif
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Play, 0);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Controls, 1);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Options, 2);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Credits, 3);
#if !defined(NO_QUIT)
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Quit, 4);
#endif
				}
				updateMainMenuCursorPositionX();
				menuHandleBackButton(3);
#if !defined(NO_QUIT)
				if (keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) && (mouseIsInRect(text_Play.rect)
					|| mouseIsInRect(text_Controls.rect) || mouseIsInRect(text_Options.rect)
					|| mouseIsInRect(text_Credits.rect) || mouseIsInRect(text_Quit.rect)))) {
#else
				if (keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) && (mouseIsInRect(text_Play.rect)
					|| mouseIsInRect(text_Controls.rect) || mouseIsInRect(text_Options.rect)
					|| mouseIsInRect(text_Credits.rect)))) {
#endif
					time_anim1 = 0;
					switch (menuCursorIndex_main) {
						case 0:
							canContinue = false;
							saveFile = SDL_RWFromFile(SAVE_FILE, "rb");
							if (saveFile != NULL) {
								SDL_RWread(saveFile, &gameCompleted, sizeof(gameCompleted), 1);
								SDL_RWclose(saveFile);
								if (gameCompleted) {
									programState = 7;
								} else {
									canContinue = true;
									programState = 6;
								}
							} else {
								programState = 7;
							}
							changedProgramState = true;
							break;
						case 1:
							programState = 12;
							menuIndex_controls = 0;
							break;
						case 2:
							programState = 13;
							changedProgramState = true;
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
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Play);
				renderText(&text_Controls);
				renderText(&text_Options);
				renderText(&text_Credits);
#if !defined(NO_QUIT)
				renderText(&text_Quit);
#endif
				break;
			/* 3 = Main Menu -> Title Screen */
			case 3:
				time_anim_PressStart = 0;
				transitionGraphicsFromMainMenu();
				transitionGraphicsToTitleScreen();
				transitionToStateWithTimer(time_anim1, 1, 0);
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, text_pressStartAmplitude));
				break;
			/* Continue Menu */
			case 6:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_continue);
					changedProgramState = false;
				}
				menuHandleVertCursorMovement(menuCursorIndex_continue, 3, 1);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouse(menuCursorIndex_continue, text_Continue, 1);
					menuHandleVertCursorMovementMouse(menuCursorIndex_continue, text_New_Game, 2);
				}
				updateContinueMenuCursorPositionX();
				menuHandleBackButton(2);
				if (keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) && (mouseIsInRect(text_Continue.rect)
					|| mouseIsInRect(text_New_Game.rect)))) {
					if (menuCursorIndex_continue == 1) {
						isContinue = true;
						programState = 8;
					} else {
						programState = 7;
					}
					changedProgramState = true;
				}
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Continue);
				renderText(&text_New_Game);
				break;
			/* 7 = Play Menu */
			case 7:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_play);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
				menuHandleVertCursorMovement(menuCursorIndex_play, 4, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouse(menuCursorIndex_play, text_Easy, 0);
					menuHandleVertCursorMovementMouse(menuCursorIndex_play, text_Normal, 1);
					menuHandleVertCursorMovementMouse(menuCursorIndex_play, text_Hard, 2);
					menuHandleVertCursorMovementMouse(menuCursorIndex_play, text_Very_Hard, 3);
				}
				updatePlayMenuCursorPositionX();
				if (canContinue) {
					menuHandleBackButton(6);
				} else {
					menuHandleBackButton(2);
				}
				if (keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) && (mouseIsInRect(text_Easy.rect)
					|| mouseIsInRect(text_Normal.rect) || mouseIsInRect(text_Hard.rect) || mouseIsInRect(text_Very_Hard.rect)))) {
					isContinue = false;
					programState = 8;
				}
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Easy);
				renderText(&text_Normal);
				renderText(&text_Hard);
				renderText(&text_Very_Hard);
				break;
			/* 8 = Generating Puzzle Screen */
			case 8:
#if !(defined(WII) || defined(GAMECUBE))
				/* Draw Text */
				renderText(&text_Loading);
				renderBorderRects();
				/* Update Screen */
#if !defined(SDL1)
				SDL_RenderPresent(renderer);
#else
				SDL_Flip(windowScreen);
#endif
#endif
				preparePauseTimer();
				if (isContinue) {
					loadSavedPuzzle();
				} else {
					switch (menuCursorIndex_play) {
						case 0:
							ZERO_OUT_ARRAY(grid);
							ZERO_OUT_ARRAY(originalGrid);
							ZERO_OUT_ARRAY(solutionGrid);
							ZERO_OUT_ARRAY(miniGrid);
							if (!generateGridAndSolution(RANDINT(30, 35), 52)) { // it will always be the minimum, hence the use of RANDINT
								setPremadePuzzle(0, RANDINT(0, 999));
							}
							timer_game.now = 0.0;
							gameCompleted = false;
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
							timer_game.now = 0.0;
							gameCompleted = false;
							programState = 9;
							break;
						case 2:
							ZERO_OUT_ARRAY(grid);
							ZERO_OUT_ARRAY(originalGrid);
							ZERO_OUT_ARRAY(solutionGrid);
							ZERO_OUT_ARRAY(miniGrid);
							// generateGridAndSolution(75, 300); // requires backtracking
							setPremadePuzzle(2, RANDINT(0, 999));
							timer_game.now = 0.0;
							gameCompleted = false;
							programState = 9;
							break;
						case 3:
							ZERO_OUT_ARRAY(grid);
							ZERO_OUT_ARRAY(originalGrid);
							ZERO_OUT_ARRAY(solutionGrid);
							ZERO_OUT_ARRAY(miniGrid);
							// generateGridAndSolution(300, 500); // requires more backtracking
							setPremadePuzzle(3, RANDINT(0, 999));
							timer_game.now = 0.0;
							gameCompleted = false;
							programState = 9;
							break;
						default:
							break;
					}
				}
				if (game_grid_2.texture) {
					SDL_DestroyTexture(game_grid_2.texture);
					game_grid_2.texture = NULL;
				}
				game_grid_2_blit = SDL_ConvertSurface(game_grid_2_clean, game_grid_2_clean->format, 0);
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						setTextPosX(&gridNums_black[int(originalGrid[i])], GRID_X_AT_COL(i % 9) + gridNums_black[int(originalGrid[i])].charOffset_x - gridPosX);
						setTextPosY(&gridNums_black[int(originalGrid[i])], GRID_Y_AT_ROW(i / 9) + gridNums_black[int(originalGrid[i])].charOffset_y - gridPosY - game_grid_1.rect.h);
#if defined(SDL1)
						blitRGBAontoRGB24(gridNums_black[int(originalGrid[i])].texture, game_grid_2_blit, gridNums_black[int(originalGrid[i])].rect.x, gridNums_black[int(originalGrid[i])].rect.y);
#else
						SDL_BlitScaled(gridNums_black[int(originalGrid[i])].surface, NULL, game_grid_2_blit, &gridNums_black[int(originalGrid[i])].rect);
#endif
					}
				}
#if defined(SDL1)
				game_grid_2.texture = game_grid_2_blit;
#else
				game_grid_2.texture = SDL_CreateTextureFromSurface(renderer, game_grid_2_blit);
				SDL_FreeSurface(game_grid_2_blit);
#endif
				updatePauseTimer();
				gridCursorIndex_x = 0;
				gridCursorIndex_y = 0;
				setGridCursorByLargeX();
				setGridCursorByLargeY();
				miniGridState = 0;
				updateNumEmpty();
				break;
			/* 9 = Game */
			case 9:
				/* Update Timer */
				timer_game.now += deltaTime;
				if (timer_game.now > 5999) {
					timer_game.now = 5999;
				}
				/* Key Presses */
				if (keyPressed(INPUT_START)) {
					programState = 10;
				}
				if (mouseMoved()) {
					gameHandleMouseMovementMain();
					gameHandleMouseMovementMini();
				}
				gameHandleMainGridNavigation();
				gameHandleMiniGridNavigation();
				gameHandleNumKeyPresses();
				gameHandleCheatRevealCell();
				gameHandleCheatClearIncorrectCells();
				gameHandleChangeSong();
				lastMiniGridState = miniGridState;
				/* Draw Grid */
				renderGrid();
				for (Sint8 col = 0; col < 9; col++) {
					for (Sint8 row = 0; row < 9; row++) {
						Sint8 cell = (row * 9) + col;
						if (originalGrid[cell]) {
							//setAndRenderNumGridMainNormal(gridNums_black, int(originalGrid[cell]), cell);
						} else if (grid[cell]) {
							setAndRenderNumGridMainNormal(gridNums_blue, int(grid[cell]), cell);
						} else {
							for (Sint8 num = 1; num < 10; num++) {
								if (miniGrid[cell] & (1 << num)) {
									setAndRenderNumGridMainMini(gridNums_blue_mini, int(num), cell);
								}
							}
						}
					}
				}
				renderMiniGrid();
				/* Draw Cursor */
				renderSprite(gridCursor_bottom_left);
				renderSprite(gridCursor_bottom_right);
				renderSprite(gridCursor_top_left);
				renderSprite(gridCursor_top_right);
				drawSidebar();
				break;
			/* 10 = Pause Screen */
			case 10:
				/* Key Presses */
#if defined(ANDROID)
				if (keyPressed(INPUT_START) || keyPressed(INPUT_CONFIRM_ALT)) {
#else
				if (keyPressed(INPUT_START)) {
#endif
					programState = 9;
				}
				menuHandleMenuButton();
				drawSidebar();
				renderText(&text_Paused);
				renderText(&text_Quit_to_Menu_1);
				renderText(&text_Quit_to_Menu_2);
				break;
			/* 11 = Victory Screen */
			case 11:
				/* Key Presses */
				if (keyPressed(INPUT_START)) {
					gameCompleted = true;
					savePuzzle();
					programState = 2;
					updateMenuCursorPositionY(menuCursorIndex_main);
				}
				/* Draw Grid */
				renderGrid();
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						//setAndRenderNumGridMainNormal(gridNums_black, int(originalGrid[i]), i);
					} else if (grid[i]) {
						setAndRenderNumGridMainNormal(gridNums_blue, int(grid[i]), i);
					} else {
						for (Sint8 j = 1; j < 10; j++) {
							if (miniGrid[i] & (1<<j)) {
								setAndRenderNumGridMainMini(gridNums_blue_mini, int(j), i);
							}
						}
					}
				}
				drawSidebar();
				if (menuCursorIndex_play == 3) {
					renderYouWinRect();
					renderText(&text_Wow_Incredible);
				} else {
					renderYouWinRect();
					renderText(&text_You_Win);
				}
				break;
			/* 12 = Controls Screen */
			case 12:
				/* Key Presses */
				menuHandleBackButton(2);
#if defined(ANDROID)
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_controls < 1) {
#elif defined(WII)
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_UP)) && menuIndex_controls < 1) {
#elif !defined(PC)
				if (keyPressed(INPUT_RIGHT) && menuIndex_controls < 1) {
#else
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_controls < 3) {
#endif
					menuIndex_controls++;
#if defined(WII)
				} else if ((keyPressed(INPUT_LEFT) || keyPressed(INPUT_DOWN)) && menuIndex_controls > 0) {
#else
				} else if (keyPressed(INPUT_LEFT) && menuIndex_controls > 0) {
#endif
					menuIndex_controls--;
				}
				//renderTestText();
				switch (menuIndex_controls) {
					case 0:
						renderControlsTextPage1();
						break;
					case 1:
						renderControlsTextPage2();
						break;
#if defined(PC)
					case 2:
						renderControlsTextPage3();
						break;
					case 3:
						renderControlsTextPage4();
						break;
#endif
					default:
						break;
				}
				break;
			/* 13 = Options Menu */
			case 13:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_options);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
				menuHandleVertCursorMovement(menuCursorIndex_options, 4, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouse(menuCursorIndex_options, text_Controls_Menu, 0);
					menuHandleVertCursorMovementMouse(menuCursorIndex_options, text_Video, 1);
					menuHandleVertCursorMovementMouse(menuCursorIndex_options, text_Sound, 2);
					menuHandleVertCursorMovementMouse(menuCursorIndex_options, text_Background, 3);
					// menuHandleVertCursorMovementMouse(menuCursorIndex_options, text_Scores, 3);
				}
				updateOptionsMenuCursorPositionX();
				menuHandleBackButton(2);
				if (keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) && (mouseIsInRect(text_Controls_Menu.rect)
					|| mouseIsInRect(text_Video.rect) || mouseIsInRect(text_Sound.rect) || mouseIsInRect(text_Background.rect)))) {
					time_anim1 = 0;
					switch (menuCursorIndex_options) {
						case 0:
							programState = 28;
							wiimoteSchemeTempVal = controlSettings.enableTouchscreen;
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
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Controls_Menu);
				renderText(&text_Video);
				renderText(&text_Sound);
				renderText(&text_Background);
				// renderText(&text_Scores);
				break;
			/* 18 = Credits Screen */
			case 18:
				/* Key Presses */
				menuHandleBackButton(2);
#if defined(WII)
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT) || keyPressed(INPUT_UP)) && menuIndex_credits < 8) {
#else
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_credits < 8) {
#endif
					menuIndex_credits++;
				}
#if defined(WII)
				else if ((keyPressed(INPUT_LEFT) || keyPressed(INPUT_DOWN)) && menuIndex_credits > 0) {
#else
				else if (keyPressed(INPUT_LEFT) && menuIndex_credits > 0) {
#endif
					menuIndex_credits--;
				}
				switch (menuIndex_credits) {
					case 0:
						renderCreditsTextPage1();
						break;
					case 1:
						renderCreditsTextPage2();
						break;
					case 2:
						renderCreditsTextPage3();
						break;
					case 3:
						renderCreditsTextPage4();
						break;
					case 4:
						renderCreditsTextPage5();
						break;
					case 5:
						renderCreditsTextPage6();
						break;
					case 6:
						renderCreditsTextPage7();
						break;
					case 7:
						renderCreditsTextPage8();
						break;
					case 8:
						renderCreditsTextPage9();
						break;
					default:
						break;
				}
				break;
			/* 20 = Video Menu */
			case 20:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_video);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
#if defined(FUNKEY)
				menuHandleVertCursorMovement(menuCursorIndex_video, 1, 0);
#elif defined(ANDROID)
				menuHandleVertCursorMovement(menuCursorIndex_video, 2, 0);
#elif defined(THREEDS)
				menuHandleVertCursorMovement(menuCursorIndex_video, 3, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Integer_Scale, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 13)), 0);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Frame_Rate, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 8)), 1);
					//menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Integer_Scale, (text_Off.rect.x + text_Off.rect.w), 3);
					menuHandleVertCursorMovementMouse(menuCursorIndex_video, text_Apply, 2);
				}
#else
				menuHandleVertCursorMovement(menuCursorIndex_video, 4, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Resolution, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 9)), 0);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Aspect_Ratio, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 5)), 1);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Frame_Rate, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 8)), 2);
					//menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Integer_Scale, (text_Off.rect.x + text_Off.rect.w), 3);
					menuHandleVertCursorMovementMouse(menuCursorIndex_video, text_Apply, 3);
				}
#endif
				updateVideoMenuCursorPositionX();
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_video) {
#if defined(FUNKEY)
						case 0:
							setFrameRateByOptions(-1);
							break;
#elif defined(ANDROID)
						case 0:
							setFrameRateByOptions(-1);
							break;
						case 1:
							sdlToggleFullscreen();
							break;
#elif defined(THREEDS)
						case 0:
							toggleDualScreen();
							break;
						case 1:
							setFrameRateByOptions(-1);
							break;
#else
						case 0:
							setResolution(-1);
							break;
						case 1:
							setAspectRatioByOptions(-1);
							break;
						case 2:
							setFrameRateByOptions(-1);
							break;
						//case 3:
						//	sdlToggleIntegerScale();
						//	break;
#endif
						default:
							break;
					}
				}
#if defined(ANDROID)
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT))) {
#elif defined(THREEDS)
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Integer_Scale.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 13)))
					|| mouseIsInRectWithSetting(text_Frame_Rate.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 8)))
					|| mouseIsInRect(text_Apply.rect)))) {
#else
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Resolution.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 9)))
					|| mouseIsInRectWithSetting(text_Aspect_Ratio.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 5)))
					|| mouseIsInRectWithSetting(text_Frame_Rate.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 8)))
					//|| mouseIsInRectWithSetting(text_Integer_Scale.rect, (text_Off.rect.x + text_Off.rect.w))
					|| mouseIsInRect(text_Apply.rect)))) {
#endif
					switch (menuCursorIndex_video) {
#if defined(FUNKEY)
						case 0:
							setFrameRateByOptions(1);
							break;
#elif defined(ANDROID)
						case 0:
							setFrameRateByOptions(1);
							break;
						case 1:
							sdlToggleFullscreen();
							break;
#elif defined(THREEDS)
						case 0:
							toggleDualScreen();
							break;
						case 1:
							setFrameRateByOptions(1);
							break;
						case 2:
							if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT)) {
								if (settingsFile == NULL) {
									initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen, 1, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume, bgSettings.type, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale, addon131Settings.frameRateIndex, addon134Settings.windowedSetting);
								} else {
									saveCurrentSettings();
								}
								sdlDestroyAll();
								systemSpecificClose();
								return 0;
							}
							break;
#else
						case 0:
							setResolution(1);
							break;
						case 1:
							setAspectRatioByOptions(1);
							break;
						case 2:
							setFrameRateByOptions(1);
							break;
						//case 3:
						//	sdlToggleIntegerScale();
						//	break;
						case 3:
							if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT)) {
								if (settingsFile == NULL) {
									initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen, 1, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume, bgSettings.type, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale, addon131Settings.frameRateIndex, addon134Settings.windowedSetting);
								} else {
									saveCurrentSettings();
								}
								// isRunning = false;
								// End the program here; otherwise, text and sprites will be resized and look weird for one frame before closing
#if !defined(NO_QUIT)
								sdlDestroyAll();
								systemSpecificClose();
								return 0;
#else
								time_anim1 = 0;
								programState = 13;
								menuResetCursorPositions(13);
								changedProgramState = true;
#endif
							}
							break;
#endif
						default:
							break;
					}
				}
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Frame_Rate);
				renderFrameRateChoice();
#if defined(ANDROID)
				renderText(&text_Integer_Scale);
				if (isWindowed) {
					renderText(&text_On);
				} else {
					renderText(&text_Off);
				}
#elif defined(THREEDS)
				renderText(&text_Integer_Scale);
				if (addon134Settings.windowedSetting) {
					renderText(&text_On);
				} else {
					renderText(&text_Off);
				}
				renderText(&text_Apply);
#elif !defined(FUNKEY)
				renderText(&text_Resolution);
				renderText(&text_Aspect_Ratio);
				setAndRenderNumResolution(videoSettings.widthSetting, videoSettings.heightSetting, VIDEO_MENU_NUM_POSITION_X, TEXT_RESOLUTION_Y);
				renderAspectRatioChoice();
				renderText(&text_Apply);
#endif
				menuHandleBackButtonWithSettings(13);
				break;
			/* 22 = Sound Menu */
			case 22:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_sound);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
				menuHandleVertCursorMovement(menuCursorIndex_sound, 4, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_sound, text_Music, SOUND_MENU_ENDPOINT, 0);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_sound, text_Music_Volume, SOUND_MENU_ENDPOINT, 1);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_sound, text_SFX_Volume, SOUND_MENU_ENDPOINT, 2);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_sound, text_Reset_to_Default_1, SOUND_MENU_ENDPOINT, 3);
				}
				updateSoundMenuCursorPositionX();
				menuHandleBackButtonWithSettings(13);
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_sound) {
						case 0:
							if (--soundSettings.musicIndex < 1)
								soundSettings.musicIndex = 8;
							playMusicAtIndex(soundSettings.musicIndex);
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
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Music.rect, SOUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Music_Volume.rect, SOUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_SFX_Volume.rect, SOUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Reset_to_Default_1.rect, SOUND_MENU_ENDPOINT)))) {
					switch (menuCursorIndex_sound) {
						case 0:
							if (++soundSettings.musicIndex > 8)
                                soundSettings.musicIndex = 1;
							playMusicAtIndex(soundSettings.musicIndex);
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
							if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT)) {
								if (soundSettings.musicIndex != 1) {
									soundSettings.musicIndex = 1;
									soundSettings.bgmVolume = 90;
									playMusicAtIndex(soundSettings.musicIndex);
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
				/* Set and Draw Numbers */
				setAndRenderNumThreeDigitCentered(soundSettings.musicIndex, SOUND_MENU_NUM_POSITION_X, TEXT_MUSIC_Y);
				setAndRenderNumThreeDigitCentered(soundSettings.bgmVolume, SOUND_MENU_NUM_POSITION_X, TEXT_MUSIC_VOLUME_Y);
				setAndRenderNumThreeDigitCentered(soundSettings.sfxVolume, SOUND_MENU_NUM_POSITION_X, TEXT_SFX_VOLUME_Y);
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Music);
				renderText(&text_Music_Volume);
				renderText(&text_SFX_Volume);
				renderText(&text_Reset_to_Default_1);
				break;
			/* 24 = Background Menu */
			case 24:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_background);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
				menuHandleVertCursorMovement(menuCursorIndex_background, 5, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_background, text_Background_Type, BACKGROUND_MENU_ENDPOINT, 0);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_background, text_Background_Size, BACKGROUND_MENU_ENDPOINT, 1);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_background, text_Scroll_Speed, BACKGROUND_MENU_ENDPOINT, 2);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_background, text_Scroll_Direction, BACKGROUND_MENU_ENDPOINT, 3);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_background, text_Reset_to_Default_2, BACKGROUND_MENU_ENDPOINT, 4);
				}
				updateBackgroundMenuCursorPositionX();
				menuHandleBackButtonWithSettings(13);
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_background) {
						case 0:
							if (--bgSettings.type < 1)
								bgSettings.type = 8;
							setBGType();
							break;
						case 1:
							bgSettings.scale--;
							if (bgSettings.scale < 1)
								bgSettings.scale = 10;
							setSpriteScaleTile();
							break;
						case 2:
							bgSettings.speedMult -= 5;
							if (bgSettings.speedMult < 0)
								bgSettings.speedMult = 100;
							break;
						case 3:
							if (--bgSettings.scrollDir < 0)
								bgSettings.scrollDir = 71;
							setBGScrollSpeed();
							break;
						default:
							break;
					}
				}
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Background_Type.rect, BACKGROUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Scroll_Speed.rect, BACKGROUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Scroll_Direction.rect, BACKGROUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Background_Size.rect, BACKGROUND_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Reset_to_Default_2.rect, BACKGROUND_MENU_ENDPOINT)))) {
					switch (menuCursorIndex_background) {
						case 0:
							if (++bgSettings.type > 8)
								bgSettings.type = 1;
							setBGType();
							break;
						case 1:
							bgSettings.scale++;
							if (bgSettings.scale > 10)
								bgSettings.scale = 1;
							setSpriteScaleTile();
							break;
						case 2:
							bgSettings.speedMult = (bgSettings.speedMult + 5) % 105;
							break;
						case 3:
							bgSettings.scrollDir = (bgSettings.scrollDir + 1) % 72;
							setBGScrollSpeed();
							break;
						case 4:
							if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT)) {
								resetBGToDefault();
								setBGType();
							}
						default:
							break;
					}
				}
				/* Set and Draw Numbers */
				setAndRenderNumThreeDigitCentered(bgSettings.type, BACKGROUND_MENU_NUM_POSITION_X, TEXT_BACKGROUND_TYPE_Y);
				setAndRenderNumThreeDigitCentered(bgSettings.speedMult, BACKGROUND_MENU_NUM_POSITION_X, TEXT_SCROLL_SPEED_Y);
				setAndRenderNumThreeDigitCentered((bgSettings.scrollDir * 5), BACKGROUND_MENU_NUM_POSITION_X, TEXT_SCROLL_DIRECTION_Y);
				setAndRenderNumThreeDigitCentered(bgSettings.scale, BACKGROUND_MENU_NUM_POSITION_X, TEXT_BACKGROUND_SIZE_Y);
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Background_Type);
				renderText(&text_Background_Size);
				renderText(&text_Scroll_Speed);
				renderText(&text_Scroll_Direction);
				renderText(&text_Reset_to_Default_2);
				break;
			/* 26 = Scores Menu */
			case 26:
				menuHandleBackButton(13);
				break;
			/* 28 = Controls Menu */
			case 28:
				if (changedProgramState) {
					updateControlsMenuCursorPositionY();
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
#if defined(MOUSE_INPUT) && !(defined(ANDROID) || defined(THREEDS))
				controlsMenuHandleVertCursorMovement();
				if (mouseMoved()) {
					controlsMenuHandleVertCursorMovementMouse(text_Controller_Input, 0);
					controlsMenuHandleVertCursorMovementMouse(text_Touch_Screen_Input, 1);
				}
#endif
				updateControlsMenuCursorPositionX();
				menuHandleBackButtonWithSettings(13);
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_controls) {
						case 0:
							controlSettings.swapConfirmAndBack = !controlSettings.swapConfirmAndBack;
							controlsSetConfirmBackPos();
							break;
						case 1:
#if defined(WII)
							wiimoteSchemeTempVal -= 1;
							if (wiimoteSchemeTempVal < 0)
								wiimoteSchemeTempVal = 2;
#else
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
#endif
							break;
						default:
							break;
					}
				}
#if defined(MOUSE_INPUT) && !(defined(ANDROID) || defined(THREEDS))
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Controller_Input.rect, CONTROLS_MENU_ENDPOINT)
					|| mouseIsInRectWithSetting(text_Touch_Screen_Input.rect, CONTROLS_MENU_ENDPOINT)))) {
#else
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Controller_Input.rect, CONTROLS_MENU_ENDPOINT)))) {
#endif
					switch (menuCursorIndex_controls) {
						case 0:
							controlSettings.swapConfirmAndBack = !controlSettings.swapConfirmAndBack;
							controlsSetConfirmBackPos();
							break;
						case 1:
#if defined(WII)
							wiimoteSchemeTempVal = (wiimoteSchemeTempVal + 1) % 3;
#else
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
#endif
						default:
							break;
					}
				}
				/* Draw Logo and Text */
				renderLogo();
				renderSprite(menuCursor);
				renderText(&text_Controller_Input);
				renderText(&text_Touch_Screen_Input);
				if (controlSettings.swapConfirmAndBack) {
					renderText(&text_A_Confirm);
					renderText(&text_B_Back);
				} else {
					renderText(&text_B_Confirm);
					renderText(&text_A_Back);
				}
#if defined(WII)
				switch (wiimoteSchemeTempVal) {
					case 0:
						renderText(&text_WiimoteScheme_Horizontal);
						break;
					case 1:
						renderText(&text_WiimoteScheme_General);
						break;
					case 2:
						renderText(&text_WiimoteScheme_Vertical);
						break;
					default:
						break;
				}
#else
				if (controlSettings.enableTouchscreen) {
					renderText(&text_Enabled);
				} else {
					renderText(&text_Disabled);
				}
#endif
				break;
			default:
				break;
		}

		/* Miscellaneous */
		controllerAxis_leftStickX_last = controllerAxis_leftStickX;
		controllerAxis_leftStickY_last = controllerAxis_leftStickY;
		//if (keyPressed(INPUT_CONFIRM_ALT)) { // fix the cursor resetting back to the last-tapped position
		//	mouseInput_x = 0;
		//	mouseInput_y = 0;
		//}
		mouseInput_x_last = mouseInput_x;
		mouseInput_y_last = mouseInput_y;

		/* Draw Black Rectangles (to fix background scrolling bug for some aspect ratios in fullscreen) */
#if !(defined(FUNKEY) || defined(THREEDS))
		renderBorderRects();
#endif

		/* Update Screen */
		if (showFPS) {
			printFPS();
		}
#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(windowScreen);
#endif

		/* Cap Framerate */
#if defined(SDL1)
		if (true) {
#else
		if (frameRate < displayRefreshRate) {
#endif
			frameTime = SDL_GetTicks() - currTicks;
			if (frameTime < ticksPerFrame) {
				SDL_Delay(ticksPerFrame - frameTime);
			}
		}
	}

	sdlDestroyAll();
	systemSpecificClose();

#if !defined(EMSCRIPTEN)
	return 0;
#endif
}

#if defined(EMSCRIPTEN)
int main() {
	emscripten_set_main_loop(mainloop, 0, 1);
	return 0;
}
#endif