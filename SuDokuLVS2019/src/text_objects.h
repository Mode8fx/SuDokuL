#include "include.h"

#ifndef TEXT_OBJECTS_H
#define TEXT_OBJECTS_H

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(LINUX) || defined(THREEDS)
#define STRCPY(dest, src) \
    strcpy(dest, src);
#else
#define STRCPY(dest, src) \
    strcpy_s(dest, src);
#endif

#if defined (WII_U) || defined(PSP) || defined(VITA) || defined(SWITCH) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(FUNKEY)
#define CONTROLS_STEP 1.89
#else
#define CONTROLS_STEP 1.6
#endif

#define CONTROLS_SPACER (fontSize * 0.75)

struct TextRect {
    Sint16 x;
    Sint16 y;
    Sint16 w;
    Sint16 h;
};

/* Single Characters */
struct TextCharObject {
#if !defined(SDL1)
    SDL_Surface *surface, *outline_surface;
    SDL_Texture *texture, *outline_texture;
#else
    SDL_Surface *texture, *outline_texture;
#endif
    SDL_Rect rect, outline_rect;
    Sint8 outlineOffset_x, outlineOffset_y;
};

/* Full Words/Phrases (can be animated) */
struct TextObject {
    string str;
    TextRect rect;
    Sint16 startPos_x, endPos_x;
    Sint16 startPos_y, endPos_y;
};

/* Fonts */
const SDL_Color color_black = {0, 0, 0};
const SDL_Color color_white = {255, 255, 255};
const SDL_Color color_blue = {0, 0, 192};
const SDL_Color color_gray_240 = {240, 240, 240};
const SDL_Color color_light_blue = {240, 240, 255};
extern TTF_Font *pixelFont;
extern TTF_Font *pixelFont_large;
extern TTF_Font *pixelFont_grid;
extern TTF_Font *pixelFont_grid_mini;

/* Text Objects */
/* General - Numbers */
extern TextCharObject gridNums_black[10];
extern TextCharObject gridNums_blue[10];
extern TextCharObject gridNums_blue_mini[10];
/* General - Everything */
extern TextCharObject textChars[127];
extern TextCharObject textChars_large[91];
extern char tempCharArray[64];
extern Uint8 charCounter;
extern Uint16 charWidthCounter;
/* Specific */
extern TextObject text_Loading;
extern TextObject text_Continue;
extern TextObject text_New_Game;
extern TextObject text_Easy;
extern TextObject text_Normal;
extern TextObject text_Hard;
extern TextObject text_Very_Hard;
extern TextObject text_Time;
extern TextObject text_Empty;
extern TextObject text_Game_Easy;
extern TextObject text_Game_Normal;
extern TextObject text_Game_Hard;
extern TextObject text_Game_VHard;
extern TextObject text_Paused;
extern TextObject text_Quit_to_Menu_1;
extern TextObject text_Quit_to_Menu_2;
extern TextObject text_You_Win;
extern TextObject text_Wow_Incredible;
extern TextObject text_Controls_Menu;
extern TextObject text_Video;
extern TextObject text_Sound;
extern TextObject text_Background;
extern TextObject text_Controller_Input;
extern TextObject text_Touch_Screen_Input;
extern TextObject text_A_Confirm;
extern TextObject text_B_Back;
extern TextObject text_B_Confirm;
extern TextObject text_A_Back;
extern TextObject text_Enabled;
extern TextObject text_Disabled;
extern TextObject text_WiimoteScheme_Horizontal;
extern TextObject text_WiimoteScheme_General;
extern TextObject text_WiimoteScheme_Vertical;
extern TextObject text_Resolution;
extern TextObject text_x;
extern TextObject text_Aspect_Ratio;
extern TextObject text_colon;
extern TextObject text_Native_Res;
extern TextObject text_Native_4_3;
extern TextObject text_Native_16_9;
extern TextObject text_Native_16_10;
extern TextObject text_Native_1_1;
extern TextObject text_Native_Aspect;
extern TextObject text_Integer_Scale;
extern TextObject text_On;
extern TextObject text_Off;
extern TextObject text_Apply;
extern TextObject text_Music;
extern TextObject text_Music_Volume;
extern TextObject text_SFX_Volume;
extern TextObject text_Background_Type;
extern TextObject text_Scroll_Speed;
extern TextObject text_Scroll_Direction;
extern TextObject text_Background_Size;
extern TextObject text_Reset_to_Default_1;
extern TextObject text_Reset_to_Default_2;
extern TextObject text_Controls_1;
extern TextObject text_Controls_2a;
extern TextObject text_Controls_2b;
extern TextObject text_Controls_2c;
extern TextObject text_Controls_3a;
extern TextObject text_Controls_3b;
extern TextObject text_Controls_3c;
extern TextObject text_Controls_4a;
extern TextObject text_Controls_4b;
extern TextObject text_Controls_4c;
extern TextObject text_Controls_5a;
extern TextObject text_Controls_5b;
extern TextObject text_Controls_6a;
extern TextObject text_Controls_6b;
extern TextObject text_Controls_7a;
extern TextObject text_Controls_7b;
extern TextObject text_Controls_7c;
extern TextObject text_Controls_P1;
extern TextObject text_Controls_8;
extern TextObject text_Controls_9a;
extern TextObject text_Controls_9b;
extern TextObject text_Controls_10a;
extern TextObject text_Controls_10b;
extern TextObject text_Controls_11a;
extern TextObject text_Controls_11b;
extern TextObject text_Controls_12a;
extern TextObject text_Controls_12b;
extern TextObject text_Controls_12c;
extern TextObject text_Controls_P2;
#if defined(WII)
extern TextObject text_Controls_2a_vertical;
extern TextObject text_Controls_2b_vertical;
extern TextObject text_Controls_2c_vertical;
extern TextObject text_Controls_3a_vertical;
extern TextObject text_Controls_3b_vertical;
extern TextObject text_Controls_3c_vertical;
extern TextObject text_Controls_4a_vertical;
extern TextObject text_Controls_4b_vertical;
extern TextObject text_Controls_4c_vertical;
extern TextObject text_Controls_5a_vertical;
extern TextObject text_Controls_5b_vertical;
extern TextObject text_Controls_6a_vertical;
extern TextObject text_Controls_6b_vertical;
extern TextObject text_Controls_7a_vertical;
extern TextObject text_Controls_7b_vertical;
extern TextObject text_Controls_7c_vertical;
extern TextObject text_Controls_9a_vertical;
extern TextObject text_Controls_9b_vertical;
extern TextObject text_Controls_10a_vertical;
extern TextObject text_Controls_10b_vertical;
extern TextObject text_Controls_11a_vertical;
extern TextObject text_Controls_11b_vertical;
extern TextObject text_Controls_12a_vertical;
extern TextObject text_Controls_12b_vertical;
extern TextObject text_Controls_12c_vertical;
extern TextObject text_Controls_2a_horizontal;
extern TextObject text_Controls_2b_horizontal;
extern TextObject text_Controls_2c_horizontal;
extern TextObject text_Controls_3a_horizontal;
extern TextObject text_Controls_3b_horizontal;
extern TextObject text_Controls_3c_horizontal;
extern TextObject text_Controls_4a_horizontal;
extern TextObject text_Controls_4b_horizontal;
extern TextObject text_Controls_4c_horizontal;
extern TextObject text_Controls_5a_horizontal;
extern TextObject text_Controls_5b_horizontal;
extern TextObject text_Controls_6a_horizontal;
extern TextObject text_Controls_6b_horizontal;
extern TextObject text_Controls_7a_horizontal;
extern TextObject text_Controls_7b_horizontal;
extern TextObject text_Controls_7c_horizontal;
extern TextObject text_Controls_9a_horizontal;
extern TextObject text_Controls_9b_horizontal;
extern TextObject text_Controls_10a_horizontal;
extern TextObject text_Controls_10b_horizontal;
extern TextObject text_Controls_11a_horizontal;
extern TextObject text_Controls_11b_horizontal;
extern TextObject text_Controls_12a_horizontal;
extern TextObject text_Controls_12b_horizontal;
extern TextObject text_Controls_12c_horizontal;
#endif
extern TextObject text_Controls_c_1;
extern TextObject text_Controls_c_2a;
extern TextObject text_Controls_c_3a;
extern TextObject text_Controls_c_4a;
extern TextObject text_Controls_c_5a;
extern TextObject text_Controls_c_6a;
extern TextObject text_Controls_c_P1;
extern TextObject text_Controls_c_8;
extern TextObject text_Controls_c_9a;
extern TextObject text_Controls_c_10a;
extern TextObject text_Controls_c_12a;
extern TextObject text_Controls_c_12b;
extern TextObject text_Controls_c_12c;
extern TextObject text_Controls_c_P2;
extern TextObject text_Credits_1;
extern TextObject text_Credits_2;
extern TextObject text_Credits_3;
extern TextObject text_Credits_P1;
extern TextObject text_Credits_4;
extern TextObject text_Credits_5b;
extern TextObject text_Credits_5a;
extern TextObject text_Credits_6b;
extern TextObject text_Credits_6a;
extern TextObject text_Credits_7b;
extern TextObject text_Credits_7a;
extern TextObject text_Credits_8b;
extern TextObject text_Credits_8a;
extern TextObject text_Credits_9b;
extern TextObject text_Credits_9a;
extern TextObject text_Credits_10b;
extern TextObject text_Credits_10a;
extern TextObject text_Credits_11b;
extern TextObject text_Credits_11a;
extern TextObject text_Credits_12a;
extern TextObject text_Credits_12b;
extern TextObject text_Credits_music2_1;
extern TextObject text_Credits_music2_2;
extern TextObject text_Credits_music2_3;
extern TextObject text_Credits_music2_4;
extern TextObject text_Credits_music2_5;
extern TextObject text_Credits_P2;
extern TextObject text_Credits_13;
extern TextObject text_Credits_14;
extern TextObject text_Credits_15;
extern TextObject text_Credits_16;
extern TextObject text_Credits_17;
extern TextObject text_Credits_P3;
extern TextObject text_Credits_18;
extern TextObject text_Credits_19;
extern TextObject text_Credits_20;
extern TextObject text_Credits_P4;
extern TextObject text_Credits_21;
extern TextObject text_Credits_22;
extern TextObject text_Credits_23a;
extern TextObject text_Credits_23b;
extern TextObject text_Credits_P5;
extern TextObject text_Credits_24;
extern TextObject text_Credits_25;
extern TextObject text_Credits_26;
extern TextObject text_Credits_27;
extern TextObject text_Credits_28;
extern TextObject text_Credits_28_1;
extern TextObject text_Credits_28_2;
extern TextObject text_Credits_29;
extern TextObject text_Credits_30;
extern TextObject text_Credits_P6;
extern TextObject text_Credits_31;
extern TextObject text_Credits_32;
extern TextObject text_Credits_33;
extern TextObject text_Credits_34;
extern TextObject text_Credits_35;
extern TextObject text_Credits_36;
extern TextObject text_Credits_37;
extern TextObject text_Credits_38;
extern TextObject text_Credits_39a;
extern TextObject text_Credits_39b;
extern TextObject text_Credits_40;
extern TextObject text_Credits_41;
extern TextObject text_Credits_42a;
extern TextObject text_Credits_42b;
extern TextObject text_Credits_P7;
extern TextObject text_Credits_P8;
extern TextObject text_Credits_P9;
extern TextObject text_PressStart;
extern TextObject text_Version_Number;
extern TextObject text_Play;
extern TextObject text_Controls;
extern TextObject text_Options;
extern TextObject text_Credits;
extern TextObject text_Quit;
extern SDL_Rect divider;
extern SDL_Rect youWinRect;

/* Font-Related Variables */
extern Uint16 fontSize;
extern Uint16 fontForceOffset1;
extern Uint16 fontForceOffset2;
extern Uint16 gridNumSize;
extern Uint16 text_pressStartAmplitude;
extern Uint16 text_standardAmplitude;
extern Uint16 text_menuChoice3;
extern Uint16 text_menuChoice1;
extern Uint16 text_menuChoice2;
extern Uint16 text_menuChoice4;
extern Uint16 text_menuChoice5;
extern Uint16 text_midScreen_Y;
extern Uint16 text_quitToMenu_Y;
extern Uint16 controlsMenuCursorPosition_X;
extern Uint16 deepMenuCursorPosition_X;
extern Uint16 videoMenuNumPosition_X;
extern Uint16 backgroundMenuNumPosition_X;


#define TEXT_PRESS_START_Y                (text_menuChoice3) /* 300 on 480p; top of text, not middle */
#define TEXT_VERSION_NUMBER_Y             (gameHeight - (text_Version_Number.rect.h * 1.5))
#define TEXT_PLAY_Y                       (text_menuChoice1)
#define TEXT_CONTROLS_Y                   (text_menuChoice2)
#define TEXT_OPTIONS_Y                    (text_menuChoice3)
#define TEXT_CREDITS_Y                    (text_menuChoice4)
#define TEXT_QUIT_Y                       (text_menuChoice5)
#define TEXT_CONTINUE_Y                   (text_menuChoice2)
#define TEXT_NEW_GAME_Y                   (text_menuChoice3)
#define TEXT_EASY_Y                       (text_menuChoice1)
#define TEXT_NORMAL_Y                     (text_menuChoice2)
#define TEXT_HARD_Y                       (text_menuChoice3)
#define TEXT_VERY_HARD_Y                  (text_menuChoice4)
#define TEXT_LOADING_Y                    (text_midScreen_Y)
#define TEXT_PAUSED_Y                     (text_midScreen_Y - fontSize)
#define TEXT_QUIT_TO_MENU_Y               (text_quitToMenu_Y)
#define TEXT_CONTROLS_MENU_Y              (text_menuChoice1)
#define TEXT_VIDEO_Y                      (text_menuChoice2)
#if defined(FUNKEY)
#define TEXT_SOUND_Y                      (text_menuChoice2)
#define TEXT_BACKGROUND_Y                 (text_menuChoice3)
#else
#define TEXT_SOUND_Y                      (text_menuChoice3)
#define TEXT_BACKGROUND_Y                 (text_menuChoice4)
#endif
#define TEXT_CONTROLLER_INPUT_Y           (text_menuChoice1)
#define TEXT_TOUCH_SCREEN_INPUT_Y         (text_menuChoice3)
#define TEXT_RESOLUTION_Y                 (text_menuChoice1)
#define TEXT_ASPECT_RATIO_Y               (text_menuChoice2)
#if !defined(ANDROID)
#define TEXT_INTEGER_SCALE_Y              (text_menuChoice3)
#else
#define TEXT_INTEGER_SCALE_Y              (text_menuChoice1)
#endif
#define TEXT_APPLY_Y                      (text_menuChoice4)
#define TEXT_SCORES_Y                     (text_menuChoice5)
#define TEXT_BACKGROUND_TYPE_Y            (text_menuChoice1)
#define TEXT_BACKGROUND_SIZE_Y            (text_menuChoice2)
#define TEXT_SCROLL_SPEED_Y               (text_menuChoice3)
#define TEXT_SCROLL_DIRECTION_Y           (text_menuChoice4)
#define TEXT_RESET_TO_DEFAULT_2_Y         (text_menuChoice5)
#define TEXT_MUSIC_Y                      (text_menuChoice1)
#define TEXT_MUSIC_VOLUME_Y               (text_menuChoice2)
#define TEXT_SFX_VOLUME_Y                 (text_menuChoice3)
#define TEXT_RESET_TO_DEFAULT_1_Y         (text_menuChoice4)
#define CONTROLS_MENU_CURSOR_POSITION_X   (controlsMenuCursorPosition_X)
#define VIDEO_MENU_CURSOR_POSITION_X      (deepMenuCursorPosition_X)
#define VIDEO_MENU_NUM_POSITION_X         (videoMenuNumPosition_X)
#define BACKGROUND_MENU_CURSOR_POSITION_X (deepMenuCursorPosition_X)
#define BACKGROUND_MENU_NUM_POSITION_X    (backgroundMenuNumPosition_X)
#define SOUND_MENU_CURSOR_POSITION_X      (deepMenuCursorPosition_X)
#define SOUND_MENU_NUM_POSITION_X         (backgroundMenuNumPosition_X) // shared with background
#define TEXT_A_CONFIRM_Y                  (text_menuChoice1 - CONTROLS_SPACER)
#define TEXT_B_BACK_Y                     (text_menuChoice1 + CONTROLS_SPACER)
#define TEXT_B_CONFIRM_Y                  (TEXT_A_CONFIRM_Y)
#define TEXT_A_BACK_Y                     (TEXT_B_BACK_Y)
constexpr auto BASE_FONT_SIZE =           20; // default font size (480 / 24)
#define TEXT_TIME_Y                       (gameSidebarSmall1Rect.y + (compactDisplay * gameSidebarSmall1Rect.h / 16) + (gameSidebarSmall1Rect.h / 4))
#define TEXT_EMPTY_Y                      (gameSidebarSmall2Rect.y + (compactDisplay * gameSidebarSmall2Rect.h / 16) + (gameSidebarSmall2Rect.h / 4))
#define TEXT_GAME_EASY_Y                  (gameSidebarSmall3Rect.y + (compactDisplay * gameSidebarSmall3Rect.h / 16) + (gameSidebarSmall3Rect.h - fontSize) / 2)
#define TEXT_GAME_NORMAL_Y                (TEXT_GAME_EASY_Y)
#define TEXT_GAME_HARD_Y                  (TEXT_GAME_EASY_Y)
#define TEXT_GAME_VHARD_Y                 (TEXT_GAME_EASY_Y)
#define TEXT_YOU_WIN_Y                    ((game_grid.rect.y + game_grid.rect.h + gameHeight - fontSize) / 2)
#define CONTROLS_MENU_ENDPOINT            (text_A_Confirm.rect.x + text_A_Confirm.rect.w)
#define SOUND_MENU_ENDPOINT               (SOUND_MENU_NUM_POSITION_X + (fontSize * 2))
#define BACKGROUND_MENU_ENDPOINT          (BACKGROUND_MENU_NUM_POSITION_X + (fontSize * 3))

extern void initStartingTextVariables();
extern void initTextObjectVals(TextObject *);
extern void adjustCharOutlineOffset(TextCharObject *, Uint8, float, float);
extern void renderTextChar(TextCharObject *);
extern void renderText(TextObject *);
extern void renderTextLarge(TextObject *);
extern void setTextPosX(TextCharObject *, Sint16, Sint8);
extern void setTextPosY(TextCharObject *, Sint16, Sint8);
extern void setTextCharWithOutline(const char *, TTF_Font *, SDL_Color text_color, SDL_Color outline_color, TextCharObject *, Uint8);
extern void setFontOutline(TTF_Font *, TextCharObject *, Uint8);
//extern void SET_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y);
//extern void SET_LARGE_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y);
//extern void SET_TEXT_WITH_OUTLINE_ANIMATED(text, textObj, pos_x, pos_y);
//extern void SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);
//extern void SET_LARGE_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);
extern void setAndRenderNumHelper(Uint8, Sint16, Sint16, float);
extern void setAndRenderNumThreeDigitCentered(Sint16, Sint16, Sint16);
extern void setAndRenderNumResolution(Sint16, Sint16, Sint16, Sint16);
extern void setAndRenderNumAspectRatio4_3(Sint16, Sint16);
extern void setAndRenderNumAspectRatio16_9(Sint16, Sint16);
extern void setAndRenderNumAspectRatio16_10(Sint16, Sint16);
extern void setAndRenderNumAspectRatio1_1(Sint16, Sint16);
//extern void SET_AND_RENDER_TIMER(pos_x_left, pos_y);
//extern void RENDER_NUM_EMPTY(pos_x_left, pos_y);
extern void setAndRenderColon(Sint16, Sint16);
extern void setAndRenderNumGridMainNormal(TextCharObject *, Uint8, Sint8);
extern void setAndRenderNumGridMainMini(TextCharObject *, Uint8, Sint8);
extern void setAndRenderNumGridSubNormal(TextCharObject *, Uint8);
extern void setAndRenderNumGridSubMini(TextCharObject *, Uint8);
extern void menuMoveTextRight(TextObject *, double);
extern void menuMoveTextLeft(TextObject *, double);
extern void menuMoveTextUp(TextObject *, double);
extern void menuMoveTextDown(TextObject *, double);
extern void destroyTextObjectTexture(TextCharObject *);
extern void renderTestText();
extern void setControlsText();
extern void renderDividerBetweenY(TextObject *textObj1, TextObject *textObj2);
extern void renderYouWinRect();
extern void renderControlsTextPage1();
extern void renderControlsTextPage2();
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII) || defined(GAMECUBE) || defined(THREEDS) || defined(FUNKEY))
extern void renderControlsTextPage3();
extern void renderControlsTextPage4();
#endif
extern void setCreditsText();
extern void renderCreditsTextPage1();
extern void renderCreditsTextPage2();
extern void renderCreditsTextPage3();
extern void renderCreditsTextPage4();
extern void renderCreditsTextPage5();
extern void renderCreditsTextPage6();
extern void renderCreditsTextPage7();
extern void renderCreditsTextPage8();
extern void renderCreditsTextPage9();
extern void controlsSetConfirmBackPos();

#define CHAR_AT_INDEX(index) textChars[tempCharArray[index]]

#define CHAR_AT_INDEX_LARGE(index) textChars_large[tempCharArray[index]]

#define SET_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y) \
    initTextObjectVals(&textObj);                          \
    SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);

#define SET_LARGE_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y) \
    initTextObjectVals(&textObj);                                \
    SET_LARGE_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);

#define SET_TEXT_WITH_OUTLINE_ANIMATED(text, textObj, pos_x, pos_y) \
    initTextObjectVals(&textObj);                                   \
    SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);      \
    initMenuOptionPositions(&textObj);

#define SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y)                              \
    textObj.str = text;                                                                        \
    STRCPY(tempCharArray, textObj.str.c_str());                                                \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                \
        textObj.rect.w += textChars[tempCharArray[uint_i]].rect.w;                             \
        textObj.rect.h = max(textObj.rect.h, (Sint16)textChars[tempCharArray[uint_i]].rect.h); \
    }                                                                                          \
    textObj.rect.x = (Sint16)(pos_x);                                                          \
    textObj.rect.y = (Sint16)(pos_y);

#define SET_LARGE_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y)                              \
    textObj.str = text;                                                                              \
    STRCPY(tempCharArray, textObj.str.c_str());                                                      \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                      \
        textObj.rect.w += textChars_large[tempCharArray[uint_i]].rect.w;                             \
        textObj.rect.h = max(textObj.rect.h, (Sint16)textChars_large[tempCharArray[uint_i]].rect.h); \
    }                                                                                                \
    textObj.rect.x = (Sint16)(pos_x);                                                                \
    textObj.rect.y = (Sint16)(pos_y);

#define SET_AND_RENDER_TIMER(pos_x_left, pos_y)     \
    i = 0;                                          \
    j = (int(timer_game.now) / 600);                \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0); \
    j = ((int(timer_game.now) / 60) % 10);          \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0); \
    setAndRenderColon(pos_x_left, pos_y);           \
    j = ((int(timer_game.now) % 60) / 10);          \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0); \
    j = (int(timer_game.now) % 10);                 \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0);

#define RENDER_NUM_EMPTY(pos_x_left, pos_y)         \
    i = 0;                                          \
    j = int(numEmpty) / 10;                         \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0); \
    j = int(numEmpty) % 10;                         \
    setAndRenderNumHelper(j, pos_x_left, pos_y, 0);

constexpr auto CREDITS_STEP = 1.6;

#if defined(WII_U) || defined(SWITCH) || defined(ANDROID) || defined(THREEDS) || defined(GAMECUBE)
#define CHEAT1_TEXT "press X or Y 8 times"
#define CHEAT2_TEXT "Or press (B then X/Y) x4"
#elif defined(FUNKEY)
#define CHEAT1_TEXT "press X or Y 8 times to"
#define CHEAT2_TEXT "Or press (B then X/Y) x4"
#elif defined(VITA) || defined(PSP)
#define CHEAT1_TEXT "press Square or Triangle 8 times"
#define CHEAT2_TEXT "Or press (Circle then Square/Triangle) x4"
#elif defined(WII)
#define CHEAT1_TEXT "press - (Wiimote) or X/Y 8 times"
#define CHEAT2_TEXT "Or press (B/1 then -/X/Y) x4"
#else
#define CHEAT1_TEXT "press the Period key 8 times"
#define CHEAT2_TEXT "Or press (Backspace then Period) x4"
#endif

#endif