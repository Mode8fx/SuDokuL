#include "include.h"
#include "config.h"
#include "shared.h"
#include "sprite_objects.h"
#include "text_objects.h"

#ifndef MAIN_H
#define MAIN_H

/* Window Width and Height */
Uint16 gameWidth = 640;
Uint16 gameHeight = 480;
Uint16 defaultBGScale;
double gameWidthMult;
double gameHeightMult;
SDL_DisplayMode DM;

/* Settings */
SDL_RWops *settingsFile;
BackgroundSettings bgSettings;
BGScroll bgScroll;
ControlSettings controlSettings;
VideoSettings videoSettings;
SoundSettings soundSettings;

/* Window Width and Height */
Uint16 RESOLUTION_OPTIONS_WIDTH_4_3[14]    = {  320,  362,  640,  725,  768,  800,  960, 1024, 1152, 1280, 1440, 1600, 1920, 2880 };
Uint16 RESOLUTION_OPTIONS_HEIGHT_4_3[14]   = {  240,  272,  480,  544,  576,  600,  720,  768,  864,  960, 1080, 1200, 1440, 2160 };
Uint16 RESOLUTION_OPTIONS_WIDTH_16_9[12]   = {  426,  480,  853,  960, 1176, 1280, 1360, 1600, 1920, 2560, 3620, 3840 };
Uint16 RESOLUTION_OPTIONS_HEIGHT_16_9[12]  = {  240,  272,  480,  544,  664,  720,  768,  900, 1080, 1440, 2036, 2160 };
Uint16 RESOLUTION_OPTIONS_WIDTH_16_10[10]  = {  435,  720, 1152, 1280, 1440, 1600, 1680, 1920, 2560, 3840 };
Uint16 RESOLUTION_OPTIONS_HEIGHT_16_10[10] = {  272,  480,  720,  800,  900, 1024, 1050, 1200, 1600, 2400 };
Uint16 RESOLUTION_OPTIONS_WIDTH_21_9[6]    = {  480,  960, 1280, 2560, 3440, 5120 };
Uint16 RESOLUTION_OPTIONS_HEIGHT_21_9[6]   = {  205,  410,  548, 1080, 1440, 2160 };
SDL_Rect centerViewport;

/* Sound */
Mix_Music *bgm_1;
Mix_Music *bgm_2;
Mix_Music *bgm_3;
Mix_Music *bgm_4;
Mix_Music *bgm_5;
Mix_Music *bgm_6;
Mix_Music *bgm_7;
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
Uint16 sideBarSizeX;
Uint16 sideBarSizeY;
Uint16 sidebarSmallPosX;
Uint16 sidebarSmall1PosY;
Uint16 sidebarSmall2PosY;
Uint16 sidebarSmall3PosY;
Uint16 gridStartingPosX[9];
Uint16 gridStartingPosY[9];

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
Sint8 cheatCounter;

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

/* Text Objects */
TextObject text_Loading;
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
TextObject text_Video_Warning;
TextObject text_Resolution;
TextObject text_x;
TextObject text_Aspect_Ratio;
TextObject text_colon;
TextObject text_Integer_Scale;
TextObject text_On;
TextObject text_Off;
TextObject text_Apply;
TextObject text_Music;
TextObject text_Music_Volume;
TextObject text_SFX_Volume;
TextObject text_Scroll_Speed;
TextObject text_Scroll_Direction;
TextObject text_Background_Size;
TextObject text_Reset_to_Default;
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
TextObject text_Credits_12;
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
TextObject text_Credits_23;
TextObject text_Credits_P5;
TextObject text_Credits_24;
TextObject text_Credits_25;
TextObject text_Credits_26;
TextObject text_Credits_27;
TextObject text_Credits_28;
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
TextObject text_Credits_P7;
TextObject text_PressStart;
TextObject text_Version_Number;
TextObject text_Play;
TextObject text_Controls;
TextObject text_Options;
TextObject text_Credits;
TextObject text_Quit;

/* Font-Related Variables */
Uint16 fontSize;
Uint16 gridNumSize;
Uint16 text_pressStartAmplitude;
Uint16 text_standardAmplitude;
Uint16 text_menuChoice3;
Uint16 text_menuChoice1;
Uint16 text_menuChoice2;
Uint16 text_menuChoice4;
Uint16 text_menuChoice5;
Uint16 text_videoWarning_Y;
Uint16 text_midScreen_Y;
Uint16 text_quitToMenu_Y;
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
double screenScale = 1;
bool isRunning;
bool isWindowed = true;
bool isIntegerScale = true;
bool wentPastTitleScreen = 0;

#endif