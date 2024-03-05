#include "include.h"
#include "config.h"
#include "shared.h"
#include "sprite_objects.h"
#include "text_objects.h"

#ifndef MAIN_H
#define MAIN_H

/* SDL Window */
#if !defined(SDL1)
SDL_Window *window;
SDL_Renderer *renderer;
#else
SDL_Surface *windowScreen;
#endif
SDL_Event event;

/* SDL Rectangles */
SDL_Rect topRect;
SDL_Rect bottomRect;
SDL_Rect leftRect;
SDL_Rect rightRect;

/* SDL Controller */
#if defined(PSP) || defined(SDL1)
SDL_Joystick *controller = NULL;
#else
SDL_GameController *controller = nullptr;
#endif

/* Window Width and Height */
Uint16 gameWidth = 640;
Uint16 gameHeight = 480;
bool compactDisplay = false;
Uint8 defaultBGScale;
double gameWidthMult;
double gameHeightMult;
#if !defined(SDL1)
SDL_DisplayMode DM;
#endif
Uint32 frameTime;

/* Settings */
SDL_RWops *settingsFile;
SDL_RWops *saveFile;
BackgroundSettings bgSettings;
BGScroll bgScroll;
ControlSettings controlSettings;
VideoSettings videoSettings;
SoundSettings soundSettings;

/* Window Width and Height */
SDL_Rect centerViewport;

/* Sound */
Mix_Music *bgm_1;
Mix_Music *bgm_2;
Mix_Music *bgm_3;
Mix_Music *bgm_4;
Mix_Music *bgm_5;
Mix_Music *bgm_6;
Mix_Music *bgm_7;
Mix_Music *bgm_8;
Mix_Chunk *sfx;

/* Grid-Related Variables */
double gridSizeA;
double gridSizeB;
double gridSizeC;
double gridSizeD;
double gridSize;
double gridSizeA3;
Uint16 gridPosX;
Uint16 gridPosY;
Uint16 gridStartingPosX[9];
Uint16 gridStartingPosY[9];
Sint8 numOffset_large_x[9];
Sint8 numOffset_large_y[9];
Sint8 numOffset_small_x[9];
Sint8 numOffset_small_y[9];

/* General Input */
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
Uint8 heldButtons;
Sint8 cheat1Counter;
Sint8 cheat2Counter;
Sint8 songChangeCounter;

/* Menu Cursors */
Sint8 menuCursorIndex_main;
Sint8 menuCursorIndex_continue;
Sint8 menuCursorIndex_play;
Sint8 menuIndex_controls;
Sint8 menuCursorIndex_options;
Sint8 menuCursorIndex_controls;
Sint8 menuCursorIndex_video;
Sint8 menuCursorIndex_sound;
Sint8 menuCursorIndex_background;
Sint8 menuIndex_credits;

/* Textures */
SpriteObject *tile;
SpriteObject tile1;
SpriteObject tile2;
SpriteObject tile3;
SpriteObject tile_cave;
SpriteObject tile_desert;
SpriteObject tile_grasslands;
SpriteObject tile_grasslands2;
SpriteObject tile_snowymountain;
SpriteObjectWithPos logo;
SpriteObjectWithPos menuCursor;
SpriteObject game_grid;
//SpriteObjectWithPos gridCursor;
SpriteObjectWithPos gridCursor_bottom_left;
SpriteObjectWithPos gridCursor_bottom_right;
SpriteObjectWithPos gridCursor_top_left;
SpriteObjectWithPos gridCursor_top_right;
SpriteObject game_sidebar_small;
SDL_Rect gameSidebarSmall1Rect;
SDL_Rect gameSidebarSmall2Rect;
SDL_Rect gameSidebarSmall3Rect;

SpriteObjectWithPos miniGrid_bottom_left;
SpriteObjectWithPos miniGrid_bottom_right;
SpriteObjectWithPos miniGrid_top_left;
SpriteObjectWithPos miniGrid_top_right;
SpriteObjectWithPos *currMiniGrid;

/* Fonts */
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
/* Specific */
TextObject text_Loading;
TextObject text_Continue;
TextObject text_New_Game;
TextObject text_Easy;
TextObject text_Normal;
TextObject text_Hard;
TextObject text_Very_Hard;
TextObject text_Time;
TextObject text_Empty;
TextObject text_Game_Easy;
TextObject text_Game_Normal;
TextObject text_Game_Hard;
TextObject text_Game_VHard;
TextObject text_Paused;
TextObject text_Quit_to_Menu_1;
TextObject text_Quit_to_Menu_2;
TextObject text_You_Win;
TextObject text_Controls_Menu;
TextObject text_Video;
TextObject text_Sound;
TextObject text_Background;
TextObject text_Controller_Input;
TextObject text_Touch_Screen_Input;
TextObject text_A_Confirm;
TextObject text_B_Back;
TextObject text_B_Confirm;
TextObject text_A_Back;
TextObject text_Enabled;
TextObject text_Disabled;
TextObject text_Resolution;
TextObject text_x;
TextObject text_Aspect_Ratio;
TextObject text_colon;
TextObject text_Native_Res;
TextObject text_Native_4_3;
TextObject text_Native_16_9;
TextObject text_Native_16_10;
TextObject text_Native_1_1;
TextObject text_Native_Aspect;
TextObject text_Integer_Scale;
TextObject text_On;
TextObject text_Off;
TextObject text_Apply;
TextObject text_Music;
TextObject text_Music_Volume;
TextObject text_SFX_Volume;
TextObject text_Background_Type;
TextObject text_Scroll_Speed;
TextObject text_Scroll_Direction;
TextObject text_Background_Size;
TextObject text_Reset_to_Default_1;
TextObject text_Reset_to_Default_2;
TextObject text_Controls_1;
TextObject text_Controls_2a;
TextObject text_Controls_2b;
TextObject text_Controls_2c;
TextObject text_Controls_3a;
TextObject text_Controls_3b;
TextObject text_Controls_3c;
TextObject text_Controls_4a;
TextObject text_Controls_4b;
TextObject text_Controls_4c;
TextObject text_Controls_5a;
TextObject text_Controls_5b;
TextObject text_Controls_6a;
TextObject text_Controls_6b;
TextObject text_Controls_7a;
TextObject text_Controls_7b;
TextObject text_Controls_7c;
TextObject text_Controls_P1;
TextObject text_Controls_8;
TextObject text_Controls_9a;
TextObject text_Controls_9b;
TextObject text_Controls_10a;
TextObject text_Controls_10b;
TextObject text_Controls_11a;
TextObject text_Controls_11b;
TextObject text_Controls_12a;
TextObject text_Controls_12b;
TextObject text_Controls_12c;
TextObject text_Controls_P2;
TextObject text_Controls_c_1;
TextObject text_Controls_c_2a;
TextObject text_Controls_c_3a;
TextObject text_Controls_c_4a;
TextObject text_Controls_c_5a;
TextObject text_Controls_c_6a;
TextObject text_Controls_c_P1;
TextObject text_Controls_c_8;
TextObject text_Controls_c_9a;
TextObject text_Controls_c_10a;
TextObject text_Controls_c_12a;
TextObject text_Controls_c_12b;
TextObject text_Controls_c_12c;
TextObject text_Controls_c_P2;
TextObject text_Credits_1;
TextObject text_Credits_2;
TextObject text_Credits_3;
TextObject text_Credits_P1;
TextObject text_Credits_4;
TextObject text_Credits_5b;
TextObject text_Credits_5a;
TextObject text_Credits_6b;
TextObject text_Credits_6a;
TextObject text_Credits_7b;
TextObject text_Credits_7a;
TextObject text_Credits_8b;
TextObject text_Credits_8a;
TextObject text_Credits_9b;
TextObject text_Credits_9a;
TextObject text_Credits_10b;
TextObject text_Credits_10a;
TextObject text_Credits_11b;
TextObject text_Credits_11a;
TextObject text_Credits_12a;
TextObject text_Credits_12b;
TextObject text_Credits_music2_1;
TextObject text_Credits_music2_2;
TextObject text_Credits_music2_3;
TextObject text_Credits_P2;
TextObject text_Credits_13;
TextObject text_Credits_14;
TextObject text_Credits_15;
TextObject text_Credits_16;
TextObject text_Credits_17;
TextObject text_Credits_P3;
TextObject text_Credits_18;
TextObject text_Credits_19;
TextObject text_Credits_20;
TextObject text_Credits_P4;
TextObject text_Credits_21;
TextObject text_Credits_22;
TextObject text_Credits_23a;
TextObject text_Credits_23b;
TextObject text_Credits_P5;
TextObject text_Credits_24;
TextObject text_Credits_25;
TextObject text_Credits_26;
TextObject text_Credits_27;
TextObject text_Credits_28;
TextObject text_Credits_28_1;
TextObject text_Credits_28_2;
TextObject text_Credits_29;
TextObject text_Credits_30;
TextObject text_Credits_P6;
TextObject text_Credits_31;
TextObject text_Credits_32;
TextObject text_Credits_33;
TextObject text_Credits_34;
TextObject text_Credits_35;
TextObject text_Credits_36;
TextObject text_Credits_37;
TextObject text_Credits_38;
TextObject text_Credits_39;
TextObject text_Credits_40;
TextObject text_Credits_41;
TextObject text_Credits_42a;
TextObject text_Credits_42b;
TextObject text_Credits_P7;
TextObject text_Credits_P8;
TextObject text_Credits_P9;
TextObject text_PressStart;
TextObject text_Version_Number;
TextObject text_Play;
TextObject text_Controls;
TextObject text_Options;
TextObject text_Credits;
TextObject text_Quit;
SDL_Rect divider;

/* Game Logic Variables */
Sint8 gridCursorIndex_x;
Sint8 gridCursorIndex_y;
Sint8 miniGridCursorIndex_x;
Sint8 miniGridCursorIndex_y;
Sint8 miniGridState;
Sint8 lastMiniGridState;
Sint8 temp_mouseIndex_x;
Sint8 temp_mouseIndex_y;
Uint16 gridCursorCornerStep;
bool justClickedInMiniGrid;

/* Font-Related Variables */
Uint16 fontSize;
Uint16 fontForceOffset1;
Uint16 fontForceOffset2;
Uint16 gridNumSize;
Uint16 text_pressStartAmplitude;
Uint16 text_standardAmplitude;
Uint16 text_menuChoice3;
Uint16 text_menuChoice1;
Uint16 text_menuChoice2;
Uint16 text_menuChoice4;
Uint16 text_menuChoice5;
Uint16 text_midScreen_Y;
Uint16 text_quitToMenu_Y;
Uint16 controlsMenuCursorPosition_X;
Uint16 deepMenuCursorPosition_X;
Uint16 videoMenuNumPosition_X;
Uint16 backgroundMenuNumPosition_X;

/* Time */
double deltaTime;
Timer timer_global;
double time_anim1;
double time_anim_PressStart;
Timer timer_game;
double timer_buttonHold;
double timer_buttonHold_repeater;
Timer timer_paused;
bool canContinue = false;
bool gameCompleted = false;

/* Program State */
Uint8 programState;
bool changedProgramState;

/* General-use Variables */
Sint8 i, j, k;
Sint8 char_x1, char_y1, char_x2, char_y2;
Sint32 int_i;
Uint32 uint_i;
double d;

/* Other */
bool isRunning;
bool wentPastTitleScreen = 0;

/* Window */
double screenScale = 1;
bool isWindowed = true;
bool isIntegerScale = true;
bool windowSizeChanged = false;

#endif