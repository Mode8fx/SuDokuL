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

#if defined(PSP) || defined(SDL1)
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) != 0) {
#else
	if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS) != 0) {
#endif
#if !defined(SDL1) && !defined(ANDROID)
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
#endif
		return 1;
	}
	TTF_Init();

	initDefaultBGScale();

	/* Get settings from settings.bin */
	loadSettingsFile();
	/* Set Video Settings */
#if !defined(SDL1)
	SDL_GetCurrentDisplayMode(0, &DM);
#endif
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
#endif
	gameWidth = videoSettings.widthSetting;
	gameHeight = videoSettings.heightSetting;
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
	initStartingSharedVariables();
	initStartingTextVariables();
	setBGScrollSpeed();

	/* Set Window/Renderer */
#if defined(PSP)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#elif defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(WII)
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SYSTEM_WIDTH, SYSTEM_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#elif defined(SDL1)
	SDL_WM_SetCaption("SuDokuL", NULL);
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	windowScreen = SDL_SetVideoMode(SYSTEM_WIDTH, SYSTEM_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
#else
	window = SDL_CreateWindow("SuDokuL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif
	setScaling();

	/* Set only things that are used on the initial loading screen */
	/* Set Textures */
	PREPARE_SPRITE(tile1, tile1_png, tile1_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile2, tile2_png, tile2_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile3, tile3_png, tile3_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile_cave, tile_cave_png, tile_cave_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile_desert, tile_desert_png, tile_desert_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile_grasslands, tile_grasslands_png, tile_grasslands_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile_grasslands2, tile_grasslands2_png, tile_grasslands2_png_len, 0, 0, 1);
	PREPARE_SPRITE(tile_snowymountain, tile_snowymountain_png, tile_snowymountain_png_len, 0, 0, 1);
	setBGType();
	SET_SPRITE_SCALE_TILE();
	/* Set Rectangles */
	updateBorderRects();
	/* General - Fonts */
	pixelFont = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, fontSize);
	char tempCharArr[2];
	tempCharArr[1] = '\0';
	/* General */
	for (k = 32; k < LEN(textChars); k++) {
		tempCharArr[0] = k;
		setTextCharWithOutline(tempCharArr, pixelFont, color_white, color_black, &textChars[k]);
		adjustCharOutlineOffset(textChars, k, -1, -1.5);
	}
	/* Loading Screen */
	SET_TEXT_WITH_OUTLINE("Loading...", text_Loading, OBJ_TO_MID_SCREEN_X(text_Loading), TEXT_LOADING_Y);

	/* Render loading screen */
#if defined(PSP) || defined(VITA) || defined(WII_U) || defined(WII)
	updateGlobalTimer();
	deltaTime = timer_global.now - timer_global.last;
	bgScroll.speedStep_x += bgSettings.speedMult * bgScroll.speed_x * deltaTime;
	bgScroll.speedStep_x_int = int(bgScroll.speedStep_x) % tile->rect.h;
	bgScroll.speedStep_y += bgSettings.speedMult * bgScroll.speed_y * deltaTime;
	bgScroll.speedStep_y_int = int(bgScroll.speedStep_y) % tile->rect.w;
	for (bgScroll.j = -tile->rect.h; bgScroll.j <= gameHeight + tile->rect.h; bgScroll.j += tile->rect.h) {
		for (bgScroll.i = -tile->rect.w; bgScroll.i <= gameWidth + tile->rect.w; bgScroll.i += tile->rect.w) {
			tile->rect.x = bgScroll.i + bgScroll.speedStep_x_int;
			tile->rect.y = bgScroll.j + bgScroll.speedStep_y_int;
			SDL_RenderCopy(renderer, tile->texture, NULL, &tile->rect);
		}
	}
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
#if defined(SDL1) // also applies to PSP SDL1
	SDL_JoystickEventState(SDL_ENABLE);
	controller = SDL_JoystickOpen(0);
	SDL_JoystickEventState(SDL_ENABLE);
#elif defined(PSP)
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	controller = SDL_JoystickOpen(0);
#else
	for (i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			break;
		}
	}
#endif

	/* Set Background Scrolling Variables */
	//bgSettings.scrollDir = 22;
	//setBGScrollSpeed();
	//bgSettings.speedMult = 15;
	//bgSettings.scale = max(min((int)min(gameWidthMult, gameHeightMult), 5), 1);

	/* Set Textures */
	if (gameHeight < 272) {
		PREPARE_SPRITE(logo, logo_240_png, logo_240_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 240);
	} else if (gameHeight < 480) {
		PREPARE_SPRITE(logo, logo_272_png, logo_272_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 272);
	} else if (gameHeight < 544) {
		PREPARE_SPRITE(logo, logo_480_png, logo_480_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 1);
	} else if (gameHeight < 720) {
		PREPARE_SPRITE(logo, logo_544_png, logo_544_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 544);
	} else if (gameHeight < 1080) {
		PREPARE_SPRITE(logo, logo_720_png, logo_720_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 720);
	} else if (gameHeight < 1440) {
		PREPARE_SPRITE(logo, logo_1080_png, logo_1080_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 1080);
	} else if (gameHeight < 2160) {
		PREPARE_SPRITE(logo, logo_1440_png, logo_1440_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 1440);
	} else {
		PREPARE_SPRITE(logo, logo_2160_png, logo_2160_png_len, (gameWidth / 2) - (logo.rect.w / 2), gameHeight * 3 / 8 - (logo.rect.h / 2), 480.0 / 2160);
	}
	logo.startPos_y = logo.rect.y;
	logo.endPos_y = (gameHeight * 3 / 16 - (logo.rect.h / 2));
	logo.startPos_x = logo.endPos_y; /* functionally, this is a second startPos_y, not x */
	logo.endPos_x = logo.endPos_y - (gameHeight * 3 / 4); /* functionally, this is a second endPos_y, not x */
	PREPARE_SPRITE(menuCursor, menu_cursor_png, menu_cursor_png_len, 0, 0, 1);
	PREPARE_SPRITE(game_grid, grid_384_png, grid_384_png_len, gridPosX, gridPosY, 1);
	PREPARE_SPRITE(gridCursor_bottom_left, grid_cursor_bottom_left_png, grid_cursor_bottom_left_png_len, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_bottom_left, 1);
	PREPARE_SPRITE(gridCursor_bottom_right, grid_cursor_bottom_right_png, grid_cursor_bottom_right_png_len, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_bottom_right, 1);
	PREPARE_SPRITE(gridCursor_top_left, grid_cursor_top_left_png, grid_cursor_top_left_png_len, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_top_left, 1);
	PREPARE_SPRITE(gridCursor_top_right, grid_cursor_top_right_png, grid_cursor_top_right_png_len, 0, 0, 1);
	SPRITE_ENFORCE_INT_MULT(gridCursor_top_right, 1);
	gridCursorCornerStep = gridCursor_bottom_left.rect.w / 4;
	PREPARE_SPRITE(game_sidebar_small, sidebar_small_png, sidebar_small_png_len, gameSidebarSmall1Rect.x, gameSidebarSmall1Rect.y, 1);
	PREPARE_SPRITE(miniGrid_bottom_left, grid_mini_bottom_left_png, grid_mini_bottom_left_png_len, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_bottom_right, grid_mini_bottom_right_png, grid_mini_bottom_right_png_len, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_top_left, grid_mini_top_left_png, grid_mini_top_left_png_len, 0, 0, 1);
	PREPARE_SPRITE(miniGrid_top_right, grid_mini_top_right_png, grid_mini_top_right_png_len, 0, 0, 1);

	/* Set Rectangles */
	divider.w = gameWidth * 17 / 20;
	divider.h = gameHeight / 96;
	divider.x = (gameWidth - divider.w) / 2;
	divider.y = 0;

	/* Set Text */
	/* General - Fonts */
	pixelFont_large = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, (int)(fontSize * 1.5));
	pixelFont_grid = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, gridNumSize);
	pixelFont_grid_mini = TTF_OpenFontRW(SDL_RWFromConstMem(Commodore_Pixelized_v1_2_ttf, Commodore_Pixelized_v1_2_ttf_len), 1, (int)gridSizeA);
	/* General (Large) */
	for (k = 32; k < 91; k++) {
		tempCharArr[0] = k;
		setTextCharWithOutline(tempCharArr, pixelFont_large, color_light_blue, color_blue, &textChars_large[k]);
		adjustCharOutlineOffset(textChars_large, k, -1, -1.5);
	}
	/* Grid Player Numbers */
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid, color_gray_240, color_black, &gridNums_black[k]);
		adjustCharOutlineOffset(gridNums_black, k, -1, -1.5);
	}
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid, color_light_blue, color_blue, &gridNums_blue[k]);
		adjustCharOutlineOffset(gridNums_blue, k, -1, -1.5);
	}
	for (k = 0; k < 10; k++) {
		tempCharArr[0] = k + 48;
		setTextCharWithOutline(tempCharArr, pixelFont_grid_mini, color_light_blue, color_blue, &gridNums_blue_mini[k]);
		adjustCharOutlineOffset(gridNums_blue_mini, k, -1, -1.5);
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
#if defined(WII_U) || defined(VITA) || defined(ANDROID) || defined(PSP)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Start", text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#elif defined(SWITCH)
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press +",     text_PressStart, OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#else
	SET_TEXT_WITH_OUTLINE_ANIMATED("Press Enter", text_PressStart,    OBJ_TO_MID_SCREEN_X(text_PressStart), TEXT_PRESS_START_Y);
#endif
	SET_TEXT_WITH_OUTLINE_ANIMATED("v1.3",     text_Version_Number, (gameWidth - (text_Version_Number.rect.w * 1.25)), TEXT_VERSION_NUMBER_Y);
	text_Version_Number.endPos_x = text_Version_Number.startPos_x + (gameWidth * 3 / 16);
	/* Main Menu */
	SET_TEXT_WITH_OUTLINE_ANIMATED("Play",     text_Play,             OBJ_TO_MID_SCREEN_X(text_Play),       TEXT_PLAY_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Controls", text_Controls,         OBJ_TO_MID_SCREEN_X(text_Controls),   TEXT_CONTROLS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Options",  text_Options,          OBJ_TO_MID_SCREEN_X(text_Options),    TEXT_OPTIONS_Y + (gameWidth * 3 / 4));
	SET_TEXT_WITH_OUTLINE_ANIMATED("Credits",  text_Credits,          OBJ_TO_MID_SCREEN_X(text_Credits),    TEXT_CREDITS_Y + (gameWidth * 3 / 4));
#if !defined(ANDROID)
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
#if defined(WII_U) || defined(VITA) || defined(PSP)
	SET_TEXT_WITH_OUTLINE("Press Select to",  text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(SWITCH)
	SET_TEXT_WITH_OUTLINE("Press - to",       text_Quit_to_Menu_1,   OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
#elif defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Press Back to",    text_Quit_to_Menu_1, OBJ_TO_MID_SCREEN_X(text_Quit_to_Menu_1), TEXT_QUIT_TO_MENU_Y);
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
#if !defined(ANDROID)
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
#if defined(ANDROID)
	SET_TEXT_WITH_OUTLINE("Status Bar",       text_Integer_Scale,    VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Show",             text_On,               VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Hide",             text_Off,              VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
#else
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Integer Scale", text_Integer_Scale,   VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Int. Scale",   text_Integer_Scale,    VIDEO_MENU_CURSOR_POSITION_X,         TEXT_INTEGER_SCALE_Y);
	}
	SET_TEXT_WITH_OUTLINE("On",               text_On,               VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
	SET_TEXT_WITH_OUTLINE("Off",              text_Off,              VIDEO_MENU_NUM_POSITION_X,            TEXT_INTEGER_SCALE_Y);
#endif
#if !defined(ANDROID)
	if (!compactDisplay) {
		SET_TEXT_WITH_OUTLINE("Exit Game and Apply Changes", text_Apply, VIDEO_MENU_CURSOR_POSITION_X,     TEXT_APPLY_Y);
	} else {
		SET_TEXT_WITH_OUTLINE("Quit and Apply Changes", text_Apply,  VIDEO_MENU_CURSOR_POSITION_X,         TEXT_APPLY_Y);
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

#if defined(PSP) || defined(VITA) || defined(WII_U) || defined(WII)
	updatePauseTimer();
#endif

	while (isRunning) {
		/* Update Timers */
		updateGlobalTimer();
		deltaTime = timer_global.now - timer_global.last;
		time_anim1 += deltaTime;
		if (heldButtons > 0) {
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
			if (programState != 20) { // If you save in the Video settings menu, possible undesired video settings would also be saved (this could be fixed, but it's just not worth the trouble for such a small issue)
				saveCurrentSettings();
			}
		}
		if (keyPressed(INPUT_NEXT_TRACK) && wentPastTitleScreen) {
			if (++soundSettings.musicIndex > 8)
				soundSettings.musicIndex = 1;
			playMusicAtIndex(soundSettings.musicIndex);
			if (programState != 20) {
				saveCurrentSettings();
			}
		}

		if (windowSizeChanged && isIntegerScale) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII)) && !defined(SDL1)
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
		bgScroll.speedStep_x += bgSettings.speedMult * bgScroll.speed_x * deltaTime;
		bgScroll.speedStep_x_int = int(bgScroll.speedStep_x) % tile->rect.h;
		bgScroll.speedStep_y += bgSettings.speedMult * bgScroll.speed_y * deltaTime;
		bgScroll.speedStep_y_int = int(bgScroll.speedStep_y) % tile->rect.w;
		for (bgScroll.j = -tile->rect.h; bgScroll.j <= gameHeight + tile->rect.h; bgScroll.j += tile->rect.h) {
			for (bgScroll.i = -tile->rect.w; bgScroll.i <= gameWidth + tile->rect.w; bgScroll.i += tile->rect.w) {
				tile->rect.x = bgScroll.i + bgScroll.speedStep_x_int;
				tile->rect.y = bgScroll.j + bgScroll.speedStep_y_int;
				SDL_RenderCopy(renderer, tile->texture, NULL, &tile->rect);
			}
		}

		switch (programState) {
			/* 0 = Title Screen */
			case 0:
				time_anim_PressStart += deltaTime;
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
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, text_pressStartAmplitude));
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				renderText(&text_PressStart);
				renderText(&text_Version_Number);
				break;
			/* 1 = Title Screen -> Main Menu */
			case 1:
				transitionGraphicsFromTitleScreen();
				transitionGraphicsToMainMenu(-1);
				transitionToStateWithTimer(time_anim1, 1, 2);
				updateMenuCursorPositionY(menuCursorIndex_main);
				text_PressStart.rect.y = (Uint16)(TEXT_PRESS_START_Y - SIN_WAVE(time_anim_PressStart, 1.25, text_pressStartAmplitude));
				break;
			/* 2 = Main Menu */
			case 2:
				if (changedProgramState) {
					updateMenuCursorPositionY(menuCursorIndex_main);
					changedProgramState = false;
				}
				/* Key Presses + Animate Cursor */
#if !defined(ANDROID)
				menuHandleVertCursorMovement(menuCursorIndex_main, 5, 0);
#else
				menuHandleVertCursorMovement(menuCursorIndex_main, 4, 0);
#endif
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Play, 0);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Controls, 1);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Options, 2);
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Credits, 3);
#if !defined(ANDROID)
					menuHandleVertCursorMovementMouse(menuCursorIndex_main, text_Quit, 4);
#endif
				}
				updateMainMenuCursorPositionX();
				menuHandleBackButton(3);
#if !defined(ANDROID)
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				renderText(&text_Play);
				renderText(&text_Controls);
				renderText(&text_Options);
				renderText(&text_Credits);
#if !defined(ANDROID)
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				renderText(&text_Easy);
				renderText(&text_Normal);
				renderText(&text_Hard);
				renderText(&text_Very_Hard);
				break;
			/* 8 = Generating Puzzle Screen */
			case 8:
				/* Draw Text */
				renderText(&text_Loading);
				renderBorderRects();
				/* Update Screen */
#if !defined(SDL1)
				SDL_RenderPresent(renderer);
#else
				SDL_Flip(windowScreen);
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
				SDL_RenderCopy(renderer, game_grid.texture, NULL, &game_grid.rect);
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						setAndRenderNumGridMainNormal(gridNums_black, int(originalGrid[i]), i);
					} else if (grid[i]) {
						setAndRenderNumGridMainNormal(gridNums_blue, int(grid[i]), i);
					} else {
						for (j = 1; j < 10; j++) {
							if (miniGrid[i] & (1<<j)) {
								setAndRenderNumGridMainMini(gridNums_blue_mini, int(j), i);
							}
						}
					}
				}
				if (miniGridState == 1) {
					SDL_RenderCopy(renderer, currMiniGrid->texture, NULL, &currMiniGrid->rect);
					for (i = 1; i < 10; i++) {
						setAndRenderNumGridSubNormal(gridNums_blue, int(i));
					}
				} else if (miniGridState == 2) {
					SDL_RenderCopy(renderer, currMiniGrid->texture, NULL, &currMiniGrid->rect);
					for (i = 1; i < 10; i++) {
						setAndRenderNumGridSubMini(gridNums_blue_mini, int(i));
					}
				}
				/* Draw Cursor */
				SDL_RenderCopy(renderer, gridCursor_bottom_left.texture, NULL, &gridCursor_bottom_left.rect);
				SDL_RenderCopy(renderer, gridCursor_bottom_right.texture, NULL, &gridCursor_bottom_right.rect);
				SDL_RenderCopy(renderer, gridCursor_top_left.texture, NULL, &gridCursor_top_left.rect);
				SDL_RenderCopy(renderer, gridCursor_top_right.texture, NULL, &gridCursor_top_right.rect);
				drawSidebar();
				break;
			/* 10 = Pause Screen */
			case 10:
				/* Key Presses */
#if !defined(ANDROID)
				if (keyPressed(INPUT_START)) {
#else
				if (keyPressed(INPUT_START) || keyPressed(INPUT_CONFIRM_ALT)) {
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
				SDL_RenderCopy(renderer, game_grid.texture, NULL, &game_grid.rect);
				for (i = 0; i < 81; i++) {
					if (originalGrid[i]) {
						setAndRenderNumGridMainNormal(gridNums_black, int(originalGrid[i]), i);
					} else if (grid[i]) {
						setAndRenderNumGridMainNormal(gridNums_blue, int(grid[i]), i);
					} else {
						for (j = 1; j < 10; j++) {
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
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(WII)
				if (keyPressed(INPUT_RIGHT) && menuIndex_controls < 1) {
#elif defined(ANDROID)
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_controls < 1) {
#else
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_controls < 3) {
#endif
					menuIndex_controls++;
				} else if (keyPressed(INPUT_LEFT) && menuIndex_controls > 0) {
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
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII))
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
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
				if ((keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM_ALT)) && menuIndex_credits < 8) {
					menuIndex_credits++;
				}
				else if (keyPressed(INPUT_LEFT) && menuIndex_credits > 0) {
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
#if !defined(ANDROID)
				menuHandleVertCursorMovement(menuCursorIndex_video, 4, 0);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Resolution, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 9)), 0);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Aspect_Ratio, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 3)), 1);
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Integer_Scale, (text_Off.rect.x + text_Off.rect.w), 2);
					menuHandleVertCursorMovementMouse(menuCursorIndex_video, text_Apply, 3);
				}
#else
				menuHandleVertCursorMovement(menuCursorIndex_video, 1);
				if (mouseMoved()) {
					menuHandleVertCursorMovementMouseWithSetting(menuCursorIndex_video, text_Integer_Scale, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 9)), 0);
				}
#endif
				updateVideoMenuCursorPositionX();
				menuHandleBackButton(13);
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_video) {
#if !defined(ANDROID)
						case 0:
							switch (videoSettings.aspectRatioIndex) {
								case 1:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_4_3, RESOLUTION_OPTIONS_HEIGHT_4_3, LEN(RESOLUTION_OPTIONS_WIDTH_4_3), -1);
									break;
								case 2:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_9, RESOLUTION_OPTIONS_HEIGHT_16_9, LEN(RESOLUTION_OPTIONS_WIDTH_16_9), -1);
									break;
								case 3:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_10, RESOLUTION_OPTIONS_HEIGHT_16_10, LEN(RESOLUTION_OPTIONS_WIDTH_16_10), -1);
									break;
								case 4:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_1_1, RESOLUTION_OPTIONS_HEIGHT_1_1, LEN(RESOLUTION_OPTIONS_WIDTH_1_1), -1);
									break;
								default:
									break;
							}
							break;
						case 1:
							setAspectRatioByOptions(-1);
							break;
						case 2:
							sdlToggleIntegerScale();
							break;
#else
						case 0:
							sdlToggleFullscreen();
							break;
#endif
						default:
							break;
					}
				}
#if !defined(ANDROID)
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT) &&
					(mouseIsInRectWithSetting(text_Resolution.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 9)))
					|| mouseIsInRectWithSetting(text_Aspect_Ratio.rect, (VIDEO_MENU_NUM_POSITION_X + (fontSize * 3)))
					|| mouseIsInRectWithSetting(text_Integer_Scale.rect, (text_Off.rect.x + text_Off.rect.w))
					|| mouseIsInRect(text_Apply.rect)))) {
#else
				if (keyPressed(INPUT_RIGHT) || keyPressed(INPUT_CONFIRM) || (keyPressed(INPUT_CONFIRM_ALT))) {
#endif
					switch (menuCursorIndex_video) {
#if !defined(ANDROID)
						case 0:
							switch (videoSettings.aspectRatioIndex) {
								case 1:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_4_3, RESOLUTION_OPTIONS_HEIGHT_4_3, LEN(RESOLUTION_OPTIONS_WIDTH_4_3), 1);
									break;
								case 2:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_9, RESOLUTION_OPTIONS_HEIGHT_16_9, LEN(RESOLUTION_OPTIONS_WIDTH_16_9), 1);
									break;
								case 3:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_16_10, RESOLUTION_OPTIONS_HEIGHT_16_10, LEN(RESOLUTION_OPTIONS_WIDTH_16_10), 1);
									break;
								case 4:
									setResolutionByOptions(RESOLUTION_OPTIONS_WIDTH_1_1, RESOLUTION_OPTIONS_HEIGHT_1_1, LEN(RESOLUTION_OPTIONS_WIDTH_1_1), 1);
									break;
								default:
									break;
							}
							break;
						case 1:
							setAspectRatioByOptions(1);
							break;
						case 2:
							sdlToggleIntegerScale();
							break;
						case 3:
							if (keyPressed(INPUT_CONFIRM) || keyPressed(INPUT_CONFIRM_ALT)) {
								if (settingsFile == NULL) {
									initializeSettingsFileWithSettings(controlSettings.swapConfirmAndBack, controlSettings.enableTouchscreen, 1, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, soundSettings.musicIndex, soundSettings.bgmVolume, soundSettings.sfxVolume, bgSettings.type, bgSettings.speedMult, bgSettings.scrollDir, bgSettings.scale);
								} else {
									saveCurrentSettings();
								}
								// isRunning = false;
								// End the program here; otherwise, text and sprites will be resized and look weird for one frame before closing
								sdlDestroyAll();
								systemSpecificClose();
								return 0;
							}
							break;
#else
						case 0:
							sdlToggleFullscreen();
							break;
#endif
						default:
							break;
					}
				}
				/* Set and Draw Numbers */
#if !defined(ANDROID)
				setAndRenderNumResolution(videoSettings.widthSetting, videoSettings.heightSetting, VIDEO_MENU_NUM_POSITION_X, TEXT_RESOLUTION_Y);
				switch (videoSettings.aspectRatioIndex) {
					case 0:
						renderText(&text_Native_Aspect);
						break;
					case 1:
						setAndRenderNumAspectRatio4_3(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 2:
						setAndRenderNumAspectRatio16_9(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 3:
						setAndRenderNumAspectRatio16_10(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					case 4:
						setAndRenderNumAspectRatio1_1(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
						break;
					default:
						break;
				}
#endif
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
#if !defined(ANDROID)
				renderText(&text_Resolution);
				renderText(&text_Aspect_Ratio);
				renderText(&text_Apply);
#endif
				renderText(&text_Integer_Scale);
#if defined(ANDROID)
				if (isWindowed) {
#else
				if (isIntegerScale) {
#endif
					renderText(&text_On);
				} else {
					renderText(&text_Off);
				}
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
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
							SET_SPRITE_SCALE_TILE();
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
							SET_SPRITE_SCALE_TILE();
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
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
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
#if !defined(ANDROID) && !defined(PSP)
				controlsMenuHandleVertCursorMovement();
#endif
				if (mouseMoved()) {
					controlsMenuHandleVertCursorMovementMouse(text_Controller_Input, 0);
#if !defined(ANDROID) && !defined(PSP)
					controlsMenuHandleVertCursorMovementMouse(text_Touch_Screen_Input, 1);
#endif
				}
				updateControlsMenuCursorPositionX();
				menuHandleBackButtonWithSettings(13);
				if (keyPressed(INPUT_LEFT)) {
					switch (menuCursorIndex_controls) {
						case 0:
							controlSettings.swapConfirmAndBack = !controlSettings.swapConfirmAndBack;
							controlsSetConfirmBackPos();
							break;
						case 1:
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
							break;
						default:
							break;
					}
				}
#if !defined(ANDROID) && !defined(PSP)
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
							controlSettings.enableTouchscreen = !controlSettings.enableTouchscreen;
							break;
						default:
							break;
					}
				}
				/* Draw Logo and Text */
				SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
				SDL_RenderCopy(renderer, menuCursor.texture, NULL, &menuCursor.rect);
				renderText(&text_Controller_Input);
#if !defined(ANDROID) && !defined(PSP)
				renderText(&text_Touch_Screen_Input);
#endif
				if (controlSettings.swapConfirmAndBack) {
					renderText(&text_A_Confirm);
					renderText(&text_B_Back);
				} else {
					renderText(&text_B_Confirm);
					renderText(&text_A_Back);
				}
#if !defined(ANDROID) && !defined(PSP)
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
		renderBorderRects();

		/* Update Screen */
#if !defined(SDL1)
		SDL_RenderPresent(renderer);
#else
		SDL_Flip(windowScreen);
#endif

		/* Cap Framerate */
		frameTime = SDL_GetTicks() - (Uint32)timer_global.now;
		if (frameTime < 8) { // 1000 / 120 FPS = 8.333; after rounding down, 1000 / 8 = 125 FPS
			SDL_Delay(8 - frameTime);
		}
	}

	sdlDestroyAll();
	systemSpecificClose();

	return 0;
}