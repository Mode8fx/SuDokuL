#include "shared.h"

#ifndef TEXT_OBJECTS_H
#define TEXT_OBJECTS_H

#if defined(VITA)
#define FONT_COMMODORE "ux0:data/SuDokuL/fonts/Commodore Pixelized v1.2.ttf"
#else
#define FONT_COMMODORE "fonts/Commodore Pixelized v1.2.ttf"
#endif

#define INIT_STARTING_TEXT_VARIABLES()                                                                 \
	const Uint16 fontSize = (max(gameHeight / 24, 8));                                                 \
    const Uint16 gridNumSize = (GRID_SIZE_A * 3);                                                      \
    const Uint16 text_pressStartAmplitude = (FONT_SIZE / 2);                                           \
    const Uint16 text_standardAmplitude = (FONT_SIZE / 10);                                            \
    const Uint16 text_menuChoice3 = (gameHeight * 5 / 8);                                              \
    const Uint16 text_menuChoice1 = (TEXT_PRESS_START_Y - (FONT_SIZE * 4));                            \
    const Uint16 text_menuChoice2 = (TEXT_PRESS_START_Y - (FONT_SIZE * 2));                            \
    const Uint16 text_menuChoice4 = (TEXT_PRESS_START_Y + (FONT_SIZE * 2));                            \
    const Uint16 text_menuChoice5 = (TEXT_PRESS_START_Y + (FONT_SIZE * 4));                            \
    const Uint16 text_videoWarning_Y = (TEXT_PRESS_START_Y + (FONT_SIZE * 5));                         \
    const Uint16 text_midScreen_Y = ((gameHeight - FONT_SIZE) / 2);                                    \
    const Uint16 text_quitToMenu_Y = (TEXT_PAUSED_Y + (FONT_SIZE * 2.5));                              \
    const Uint16 deepMenuCursorPosition_X = (gameWidth / 6);                                           \
    const Uint16 videoMenuNumPosition_X = (gameWidth * 3 / 5);                                         \
    const Uint16 backgroundMenuNumPosition_X = (gameWidth * 2 / 3);

#define FONT_SIZE                         (fontSize)
#define GRID_NUM_SIZE                     (gridNumSize)
#define TEXT_PRESS_START_AMPLITUDE        (text_pressStartAmplitude)
#define TEXT_STANDARD_AMPLITUDE           (text_standardAmplitude)
#define TEXT_PRESS_START_Y                (text_menuChoice3) /* 300 on 480p; top of text, not middle */
#define TEXT_VERSION_NUMBER_Y             (gameHeight - (text_Version_Number.rect.h * 1.5))
#define TEXT_PLAY_Y                       (text_menuChoice1)
#define TEXT_CONTROLS_Y                   (text_menuChoice2)
#define TEXT_OPTIONS_Y                    (text_menuChoice3)
#define TEXT_CREDITS_Y                    (text_menuChoice4)
#define TEXT_QUIT_Y                       (text_menuChoice5)
#define TEXT_EASY_Y                       (text_menuChoice1)
#define TEXT_NORMAL_Y                     (text_menuChoice2)
#define TEXT_HARD_Y                       (text_menuChoice3)
#define TEXT_VERY_HARD_Y                  (text_menuChoice4)
#define TEXT_LOADING_Y                    (text_midScreen_Y)
#define TEXT_PAUSED_Y                     (text_midScreen_Y - FONT_SIZE)
#define TEXT_QUIT_TO_MENU_Y               (text_quitToMenu_Y)
#define TEXT_CONTROLS_MENU_Y              (text_menuChoice1)
#define TEXT_VIDEO_Y                      (text_menuChoice2)
#define TEXT_SOUND_Y                      (text_menuChoice3)
#define TEXT_BACKGROUND_Y                 (text_menuChoice4)
#define TEXT_CONTROLLER_INPUT_Y           (text_menuChoice1)
#define TEXT_TOUCH_SCREEN_INPUT_Y         (text_menuChoice3)
#define TEXT_VIDEO_WARNING_Y              (text_videoWarning_Y)
#define TEXT_RESOLUTION_Y                 (text_menuChoice1)
#define TEXT_ASPECT_RATIO_Y               (text_menuChoice2)
#if !defined(ANDROID)
#define TEXT_INTEGER_SCALE_Y                 (text_menuChoice3)
#else
#define TEXT_INTEGER_SCALE_Y                 (text_menuChoice1)
#endif
#define TEXT_APPLY_Y                      (text_menuChoice4)
#define TEXT_SCORES_Y                     (text_menuChoice5)
#define TEXT_SCROLL_SPEED_Y               (text_menuChoice1)
#define TEXT_SCROLL_DIRECTION_Y           (text_menuChoice2)
#define TEXT_BACKGROUND_SIZE_Y            (text_menuChoice3)
#define TEXT_RESET_TO_DEFAULT_Y           (text_menuChoice4)
#define TEXT_MUSIC_Y                      (text_menuChoice1)
#define TEXT_MUSIC_VOLUME_Y               (text_menuChoice2)
#define TEXT_SFX_VOLUME_Y                 (text_menuChoice3)
#define CONTROLS_MENU_CURSOR_POSITION_X   (gameWidth / 8)
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
#define BASE_FONT_SIZE                    20 // default font size (480 / 24)
#define TEXT_TIME_Y                       (game_sidebar_small.rect.y + (game_sidebar_small.rect.h / 4))
#define TEXT_EMPTY_Y                      (game_sidebar_small.rect.y + (game_sidebar_small.rect.h / 4))
#define TEXT_GAME_EASY_Y                  (game_sidebar_small.rect.y + (game_sidebar_small.rect.h - FONT_SIZE) / 2)
#define TEXT_GAME_NORMAL_Y                (TEXT_GAME_EASY_Y)
#define TEXT_GAME_HARD_Y                  (TEXT_GAME_EASY_Y)
#define TEXT_GAME_VHARD_Y                 (TEXT_GAME_EASY_Y)
#define TEXT_YOU_WIN_Y                    ((game_grid.rect.y + game_grid.rect.h + gameHeight - FONT_SIZE) / 2)
#define CONTROLS_MENU_ENDPOINT            (text_A_Confirm.rect.x + text_A_Confirm.rect.w)
#define SOUND_MENU_ENDPOINT               (SOUND_MENU_NUM_POSITION_X + (FONT_SIZE * 2))
#define BACKGROUND_MENU_ENDPOINT          (BACKGROUND_MENU_NUM_POSITION_X + (FONT_SIZE * 3))

struct TextRect {
    Sint16 x;
    Sint16 y;
    Sint16 w;
    Sint16 h;
};

/* Single Characters */
struct TextCharObject {
    SDL_Surface *surface, *outline_surface;
    SDL_Texture *texture, *outline_texture;
    SDL_Rect rect, outline_rect;
    Sint8 outlineOffset_x, outlineOffset_y;
};

/* Full Words/Phrases */
struct TextObject {
    string str;
    TextRect rect;
};

/* Full Words/Phrases (Animated) */
struct TextObjectAnimated {
    string str;
    TextRect rect;
    Sint16 startPos_x, endPos_x;
    Sint16 startPos_y, endPos_y;
};

#define INIT_TEXT_OBJECT_VALS(textObj) \
    textObj.rect.x = 0;                \
    textObj.rect.y = 0;                \
    textObj.rect.w = 0;                \
    textObj.rect.h = 0;

#define CHAR_AT_INDEX(index) textChars[tempCharArray[index]]

#define CHAR_AT_INDEX_LARGE(index) textChars_large[tempCharArray[index]]

#define ADJUST_CHAR_OUTLINE_OFFSET(arr, c, x, y)                                                    \
    if (x > 0) {                                                                                    \
        arr[c].outlineOffset_x += max((int)(x * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), 1);  \
    } else if (x < 0) {                                                                             \
        arr[c].outlineOffset_x += min((int)(x * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), -1); \
    }                                                                                               \
    if (y > 0) {                                                                                    \
        arr[c].outlineOffset_y += max((int)(y * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), 1);  \
    } else if (y < 0) {                                                                             \
        arr[c].outlineOffset_y += min((int)(y * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), -1); \
    }

#define FIX_CHAR_OUTLINE_OFFSETS()                                       \
	ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'I', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'M', 1, 0);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'W', 1, 0);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'c', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'g', 0, 1);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'i', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'j', -1, 1);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'l', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'm', 1, 0);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'p', 0, 1);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'q', 0, 1);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'w', 1, 0);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'y', 0, 1);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '4', 1, 0);                    \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '!', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '\"', 0, -1);                  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '(', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, ')', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '+', 0, -1);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, ',', -1, 1);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '-', 0, -1);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '.', -1, 0);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '=', 0, -1);                   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, ':', -1, 0);                   \
	ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'I', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'M', 1, 0);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'W', 1, 0);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'c', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'g', 0, 1);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'i', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'j', -1, 1);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'l', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'm', 1, 0);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'p', 0, 1);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'q', 0, 1);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'w', 1, 0);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, 'y', 0, 1);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '4', 1, 0);              \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '!', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '\"', 0, -1);            \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '(', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, ')', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '+', 0, -1);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, ',', -1, 1);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '-', 0, -1);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '.', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, '=', 0, -1);             \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars_large, ':', -1, 0);             \
    ADJUST_CHAR_OUTLINE_OFFSET(gridNums_black, '4' - 48, 1, 0);          \
    ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue, '4' - 48, 1, 0);           \
    if (GRID_SIZE_A <= 12) {                                             \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '1' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '2' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '3' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '4' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '5' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '6' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '7' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '8' - 48, 0, -1); \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '9' - 48, 0, -1); \
    } else {                                                             \
        ADJUST_CHAR_OUTLINE_OFFSET(gridNums_blue_mini, '4' - 48, 1, 0);  \
    }

// unused (FIX_CHAR_OUTLINE_OFFSETS should work for everything)
#define FIX_CHAR_OUTLINE_OFFSETS_272()                  \
	ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'I', -1, 0);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'c', -1, 0);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'g', 0, 1);   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'i', -1, 0);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'j', -1, 1);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'l', -1, 0);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'p', 0, 1);   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'q', 0, 1);   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, 'y', 0, 1);   \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '!', -4, 0);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '\"', 0, -4); \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, ',', -4, 1);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '-', 0, -1);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '.', -4, -1); \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, '=', 0, -1);  \
    ADJUST_CHAR_OUTLINE_OFFSET(textChars, ':', -4, -1);

#define RENDER_TEXT_CHAR(textObj)                                                   \
    SDL_RenderCopy(renderer, textObj.outline_texture, NULL, &textObj.outline_rect); \
    SDL_RenderCopy(renderer, textObj.texture, NULL, &textObj.rect);

#define RENDER_TEXT(textObj)                                                                                                         \
    STRCPY(tempCharArray, textObj.str.c_str());                                                                                      \
    charWidthCounter = 0;                                                                                                            \
    for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {                                                       \
        SET_TEXT_POS_X(CHAR_AT_INDEX(charCounter), (textObj.rect.x + charWidthCounter), CHAR_AT_INDEX(charCounter).outlineOffset_x); \
        SET_TEXT_POS_Y(CHAR_AT_INDEX(charCounter), textObj.rect.y, CHAR_AT_INDEX(charCounter).outlineOffset_y);                      \
        RENDER_TEXT_CHAR(textChars[tempCharArray[charCounter]]);                                                                     \
        charWidthCounter += CHAR_AT_INDEX(charCounter).rect.w;                                                                       \
    }

#define RENDER_TEXT_LARGE(textObj)                                                                                                               \
    STRCPY(tempCharArray, textObj.str.c_str());                                                                                                  \
    charWidthCounter = 0;                                                                                                                        \
    for (charCounter = 0; charCounter < textObj.str.length(); charCounter++) {                                                                   \
        SET_TEXT_POS_X(CHAR_AT_INDEX_LARGE(charCounter), (textObj.rect.x + charWidthCounter), CHAR_AT_INDEX_LARGE(charCounter).outlineOffset_x); \
        SET_TEXT_POS_Y(CHAR_AT_INDEX_LARGE(charCounter), textObj.rect.y, CHAR_AT_INDEX_LARGE(charCounter).outlineOffset_y);                      \
        RENDER_TEXT_CHAR(textChars_large[tempCharArray[charCounter]]);                                                                           \
        charWidthCounter += CHAR_AT_INDEX_LARGE(charCounter).rect.w;                                                                             \
    }

#define SET_TEXT_POS_X(textObj, pos_x, offset) \
    textObj.rect.x = (pos_x);                  \
    textObj.outline_rect.x = (pos_x) + (offset);

#define SET_TEXT_POS_Y(textObj, pos_y, offset) \
    textObj.rect.y = (pos_y);                  \
    textObj.outline_rect.y = (pos_y) + (offset);

#define SET_TEXT_CHAR_WITH_OUTLINE(text, font, text_color, outline_color, textObj)             \
    textObj.surface = TTF_RenderText_Solid(font, text, text_color);                            \
    textObj.texture = SDL_CreateTextureFromSurface(renderer, textObj.surface);                 \
    TTF_SizeText(font, text, &textObj.rect.w, &textObj.rect.h);                                \
    SET_FONT_OUTLINE(font, textObj);                                                           \
    textObj.outline_surface = TTF_RenderText_Solid(font, text, outline_color);                 \
    textObj.outline_texture = SDL_CreateTextureFromSurface(renderer, textObj.outline_surface); \
    TTF_SizeText(font, text, &textObj.outline_rect.w, &textObj.outline_rect.h);                \
    TTF_SetFontOutline(font, 0);                                                               \
    SDL_FreeSurface(textObj.surface);                                                          \
    SDL_FreeSurface(textObj.outline_surface);

#define SET_FONT_OUTLINE(font, textObj) \
    TTF_SetFontOutline(font, max((textObj.rect.h / 10), int(ceil(GAME_HEIGHT_MULT))));

#define SET_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y) \
    TextObject textObj;                                    \
    INIT_TEXT_OBJECT_VALS(textObj);                        \
    SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);

#define SET_LARGE_TEXT_WITH_OUTLINE(text, textObj, pos_x, pos_y) \
    TextObject textObj;                                          \
    INIT_TEXT_OBJECT_VALS(textObj);                              \
    SET_LARGE_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);

#define SET_TEXT_WITH_OUTLINE_ANIMATED(text, textObj, pos_x, pos_y) \
    TextObjectAnimated textObj;                                     \
    INIT_TEXT_OBJECT_VALS(textObj);                                 \
    SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y);      \
    INIT_MENU_OPTION_POSITIONS(textObj);

#define SET_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y)                              \
    textObj.str = text;                                                                        \
    STRCPY(tempCharArray, textObj.str.c_str());                                                \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                \
        textObj.rect.w += textChars[tempCharArray[uint_i]].rect.w;                             \
        textObj.rect.h = max(textObj.rect.h, (Sint16)textChars[tempCharArray[uint_i]].rect.h); \
    }                                                                                          \
    textObj.rect.x = pos_x;                                                                    \
    textObj.rect.y = pos_y;

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(ANDROID)
#define STRCPY(dest, src) \
    strcpy(dest, src);
#else
#define STRCPY(dest, src) \
    strcpy_s(dest, src);
#endif

#define SET_LARGE_TEXT_WITH_OUTLINE_HELPER(text, textObj, pos_x, pos_y)                              \
    textObj.str = text;                                                                              \
    STRCPY(tempCharArray, textObj.str.c_str());                                                      \
    for (uint_i = 0; uint_i < textObj.str.length(); uint_i++) {                                      \
        textObj.rect.w += textChars_large[tempCharArray[uint_i]].rect.w;                             \
        textObj.rect.h = max(textObj.rect.h, (Sint16)textChars_large[tempCharArray[uint_i]].rect.h); \
    }                                                                                                \
    textObj.rect.x = pos_x;                                                                          \
    textObj.rect.y = pos_y;

#define SET_AND_RENDER_NUM_HELPER(digit, pos_x_left, pos_y, i_offset)                                                            \
    SET_TEXT_POS_X(textChars[(digit + 48)], (pos_x_left + ((i + i_offset) * FONT_SIZE)), textChars[digit + 48].outlineOffset_x); \
    i++;                                                                                                                         \
    SET_TEXT_POS_Y(textChars[(digit + 48)], pos_y, textChars[digit + 48].outlineOffset_y);                                       \
    RENDER_TEXT_CHAR(textChars[(digit + 48)]);

#define SET_AND_RENDER_NUM_THREE_DIGIT_CENTERED(num, pos_x_centered, pos_y) \
    i = 0;                                                                  \
    if (num > 99) {                                                         \
        j = num / 100;                                                      \
        SET_AND_RENDER_NUM_HELPER(j, pos_x_centered, pos_y, 0);             \
        j = (num / 10) % 10;                                                \
        SET_AND_RENDER_NUM_HELPER(j, pos_x_centered, pos_y, 0);             \
        j = num % 10;                                                       \
        SET_AND_RENDER_NUM_HELPER(j, pos_x_centered, pos_y, 0);             \
    } else if (num > 9) {                                                   \
        j = num / 10;                                                       \
        SET_AND_RENDER_NUM_HELPER(j, pos_x_centered, pos_y, 0.5);           \
        j = num % 10;                                                       \
        SET_AND_RENDER_NUM_HELPER(j, pos_x_centered, pos_y, 0.5);           \
    } else {                                                                \
        SET_AND_RENDER_NUM_HELPER(num, pos_x_centered, pos_y, 1);           \
    }

#define SET_AND_RENDER_NUM_RESOLUTION(width, height, pos_x_left, pos_y)   \
    i = 0;                                                                \
    if (width > 999) {                                                    \
        SET_AND_RENDER_NUM_HELPER(width / 1000, pos_x_left, pos_y, 0);    \
    }                                                                     \
    SET_AND_RENDER_NUM_HELPER((width / 100) % 10, pos_x_left, pos_y, 0);  \
    SET_AND_RENDER_NUM_HELPER((width / 10) % 10, pos_x_left, pos_y, 0);   \
    SET_AND_RENDER_NUM_HELPER(width % 10, pos_x_left, pos_y, 0);          \
    text_x.rect.x = pos_x_left + (i * FONT_SIZE);                         \
    i++;                                                                  \
    text_x.rect.y = pos_y;                                                \
    RENDER_TEXT(text_x);                                                  \
    if (height > 999) {                                                   \
        SET_AND_RENDER_NUM_HELPER(height / 1000, pos_x_left, pos_y, 0);   \
    }                                                                     \
    SET_AND_RENDER_NUM_HELPER((height / 100) % 10, pos_x_left, pos_y, 0); \
    SET_AND_RENDER_NUM_HELPER((height / 10) % 10, pos_x_left, pos_y, 0);  \
    SET_AND_RENDER_NUM_HELPER(height % 10, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_NUM_ASPECT_RATIO_4_3(pos_x_left, pos_y) \
    i = 0;                                                     \
    SET_AND_RENDER_NUM_HELPER(4, pos_x_left, pos_y, 0);        \
    SET_AND_RENDER_COLON(pos_x_left, pos_y);                   \
    SET_AND_RENDER_NUM_HELPER(3, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_NUM_ASPECT_RATIO_16_9(pos_x_left, pos_y) \
    i = 0;                                                      \
    SET_AND_RENDER_NUM_HELPER(1, pos_x_left, pos_y, 0);         \
    SET_AND_RENDER_NUM_HELPER(6, pos_x_left, pos_y, 0);         \
    SET_AND_RENDER_COLON(pos_x_left, pos_y);                    \
    SET_AND_RENDER_NUM_HELPER(9, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_NUM_ASPECT_RATIO_16_10(pos_x_left, pos_y) \
    i = 0;                                                       \
    SET_AND_RENDER_NUM_HELPER(1, pos_x_left, pos_y, 0);          \
    SET_AND_RENDER_NUM_HELPER(6, pos_x_left, pos_y, 0);          \
    SET_AND_RENDER_COLON(pos_x_left, pos_y);                     \
    SET_AND_RENDER_NUM_HELPER(1, pos_x_left, pos_y, 0);          \
    SET_AND_RENDER_NUM_HELPER(0, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_NUM_ASPECT_RATIO_21_9(pos_x_left, pos_y) \
    i = 0;                                                      \
    SET_AND_RENDER_NUM_HELPER(2, pos_x_left, pos_y, 0);         \
    SET_AND_RENDER_NUM_HELPER(1, pos_x_left, pos_y, 0);         \
    SET_AND_RENDER_COLON(pos_x_left, pos_y);                    \
    SET_AND_RENDER_NUM_HELPER(9, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_TIMER(pos_x_left, pos_y)         \
    i = 0;                                              \
    j = (int(timer_game.now) / 600);                    \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0); \
    j = ((int(timer_game.now) / 60) % 10);              \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0); \
    SET_AND_RENDER_COLON(pos_x_left, pos_y);            \
    j = ((int(timer_game.now) % 60) / 10);              \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0); \
    j = (int(timer_game.now) % 10);                     \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0);

#define RENDER_NUM_EMPTY(pos_x_left, pos_y)             \
    i = 0;                                              \
    j = int(numEmpty) / 10;                             \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0); \
    j = int(numEmpty) % 10;                             \
    SET_AND_RENDER_NUM_HELPER(j, pos_x_left, pos_y, 0);

#define SET_AND_RENDER_COLON(pos_x_left, pos_y)       \
    text_colon.rect.x = pos_x_left + (i * FONT_SIZE); \
    i++;                                              \
    text_colon.rect.y = pos_y;                        \
    RENDER_TEXT(text_colon);

#define SET_AND_RENDER_NUM_GRID_MAIN_NORMAL(textNumsObj, num, index)                                                                                                              \
    k = index / 9;                                                                                                                                                                \
    SET_TEXT_POS_X(textNumsObj[num], GRID_X_AT_COL(index % 9) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.w) / 2) + numOffset_large_x[k], textNumsObj[num].outlineOffset_x); \
    SET_TEXT_POS_Y(textNumsObj[num], GRID_Y_AT_ROW(k) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.h) / 2) + numOffset_large_y[k], textNumsObj[num].outlineOffset_y);         \
    RENDER_TEXT_CHAR(textNumsObj[num]);

#define SET_AND_RENDER_NUM_GRID_MAIN_MINI(textNumsObj, num, index)                                                                                             \
    k = index / 9;                                                                                                                                             \
    SET_TEXT_POS_X(textNumsObj[num], GRID_X_AT_COL(index % 9) + (((num - 1) % 3) * GRID_SIZE_A) + 1 + numOffset_small_x[k], textNumsObj[num].outlineOffset_x); \
    SET_TEXT_POS_Y(textNumsObj[num], GRID_Y_AT_ROW(k) + (((num - 1) / 3) * GRID_SIZE_A) + numOffset_small_y[k], textNumsObj[num].outlineOffset_y);             \
    RENDER_TEXT_CHAR(textNumsObj[num]);

#define SET_AND_RENDER_NUM_GRID_SUB_NORMAL(textNumsObj, num)                                                                                                                                                                                                 \
    k = (num - 1) / 3;                                                                                                                                                                                                                                       \
    SET_TEXT_POS_X(textNumsObj[num], currMiniGrid->rect.x + (GRID_SIZE_D * 3) + (((num - 1) % 3) + 1) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.w) / 2) + numOffset_large_x[k], textNumsObj[num].outlineOffset_x); \
    SET_TEXT_POS_Y(textNumsObj[num], currMiniGrid->rect.y + (GRID_SIZE_D * 3) + k * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.h) / 2) + numOffset_large_y[k], textNumsObj[num].outlineOffset_y);                     \
    RENDER_TEXT_CHAR(textNumsObj[num]);

#define SET_AND_RENDER_NUM_GRID_SUB_MINI(textNumsObj, num)                                                                                                                                 \
    SET_TEXT_POS_X(textNumsObj[num], currMiniGrid->rect.x + (GRID_SIZE_D * 3) + (((num - 1) % 3) + 1) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + GRID_SIZE_A, textNumsObj[num].outlineOffset_x); \
    SET_TEXT_POS_Y(textNumsObj[num], currMiniGrid->rect.y + (GRID_SIZE_D * 3) + ((num - 1) / 3) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + GRID_SIZE_A, textNumsObj[num].outlineOffset_y);       \
    RENDER_TEXT_CHAR(textNumsObj[num]);

#define MENU_MOVE_TEXT_RIGHT(textObj, timer) \
    textObj.rect.x = (Uint16)(textObj.endPos_x - MOVE_FAST_THEN_DECELERATE(textObj.endPos_x - textObj.startPos_x, 1, timer));

#define MENU_MOVE_TEXT_LEFT(textObj, timer) \
    textObj.rect.x = (Uint16)(textObj.startPos_x + MOVE_FAST_THEN_DECELERATE(textObj.endPos_x - textObj.startPos_x, 1, timer));

#define MENU_MOVE_TEXT_UP(textObj, timer) \
    textObj.rect.y = (Uint16)(textObj.endPos_y + MOVE_FAST_THEN_DECELERATE(textObj.startPos_y - textObj.endPos_y, 1, timer));

#define MENU_MOVE_TEXT_DOWN(textObj, timer) \
    textObj.rect.y = (Uint16)(textObj.startPos_y - MOVE_FAST_THEN_DECELERATE(textObj.startPos_y - textObj.endPos_y, 1, timer));

#define DESTROY_TEXT_OBJECT_TEXTURE(textObj) \
    SDL_DestroyTexture(textObj.texture);     \
    SDL_DestroyTexture(textObj.outline_texture);

#define RENDER_TEST_TEXT()    \
    bgSettings.speedMult = 0; \
    RENDER_TEXT(text_test_1); \
    RENDER_TEXT(text_test_2); \
    RENDER_TEXT(text_test_3); \
    RENDER_TEXT(text_test_4); \
    RENDER_TEXT(text_test_5); \
    RENDER_TEXT(text_test_6); \
    RENDER_TEXT(text_test_7); \
    RENDER_TEXT(text_test_8);

#define CONTROLS_SPACER (FONT_SIZE * 0.75)

#if defined(WII_U)
#define CONTROLS_STEP 1.89
#define SET_CONTROLS_TEXT()                                                                                                                                                     \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Select (while paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(VITA)
#define CONTROLS_STEP 1.89
#define SET_CONTROLS_TEXT()                                                                                                                                                     \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Select (while paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(PSP)
#define CONTROLS_STEP 1.89
#define SET_CONTROLS_TEXT()                                                                                                                                                     \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Select (while paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(SWITCH)
#define CONTROLS_STEP 1.89
#define SET_CONTROLS_TEXT()                                                                                                                                                     \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("- (while paused)",      text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(ANDROID)
#define CONTROLS_STEP 1.6
#define SET_CONTROLS_TEXT()                                                                                                                                                     \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Back (while paused)",   text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   ); \
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#else
#define CONTROLS_STEP 1.6
#define SET_CONTROLS_TEXT()                                                                                                                                                                  \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (KB+M)",       text_Controls_1,     OBJ_TO_MID_SCREEN_X(text_Controls_1),                (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Arrow Keys/WASD",                text_Controls_2a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mouse",                          text_Controls_2b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",                       text_Controls_2c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Enter",                          text_Controls_3a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Left Click",                     text_Controls_3b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",                        text_Controls_3c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Backspace",                      text_Controls_4a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Right Click",                    text_Controls_4b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Back",                           text_Controls_4c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("-",                              text_Controls_5a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",                     text_Controls_5b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("=",                              text_Controls_6a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),    (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",                      text_Controls_6b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("F",                              text_Controls_7a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7a, 0.3),    (FONT_SIZE * (CONTROLS_STEP * 13))                  ); \
	SET_TEXT_WITH_OUTLINE("Toggle",                         text_Controls_7b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 13)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Fullscreen",                     text_Controls_7c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 13)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(1/4)",                          text_Controls_P1,    (gameWidth - (text_Controls_P1.rect.w * 1.25)),      (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (KB+M)",              text_Controls_8,     OBJ_TO_MID_SCREEN_X(text_Controls_8),                (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Esc",                            text_Controls_9a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                          text_Controls_9b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Q (while paused)",               text_Controls_10a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",                   text_Controls_10b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Numbers",                        text_Controls_11a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Input",                    text_Controls_11b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(".",                              text_Controls_12a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_12b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  9)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_12c,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  9)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/4)",                          text_Controls_P2,    (gameWidth - (text_Controls_P2.rect.w * 1.25)),      (gameHeight - (text_Controls_P2.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (CONTROLLER)", text_Controls_c_1,   OBJ_TO_MID_SCREEN_X(text_Controls_c_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                          text_Controls_c_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("A",                              text_Controls_c_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("B",                              text_Controls_c_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                              text_Controls_c_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                              text_Controls_c_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("(3/4)",                          text_Controls_c_P1,  (gameWidth - (text_Controls_c_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P1.rect.h * 1.5))    ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (CONTROLLER)",        text_Controls_c_8,   OBJ_TO_MID_SCREEN_X(text_Controls_c_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Start",                          text_Controls_c_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Select (while paused)",          text_Controls_c_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Select (paused)",                text_Controls_c_10aa, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_10aa, 0.3), (FONT_SIZE * (CONTROLS_STEP *  5))                ); \
	SET_TEXT_WITH_OUTLINE("X / Y",                          text_Controls_c_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_c_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_c_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(4/4)",                          text_Controls_c_P2,  (gameWidth - (text_Controls_c_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P2.rect.h * 1.5)));
#endif

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(PSP) || defined(ANDROID)
#define RENDER_DIVIDER_BETWEEN_Y(textObj1, textObj2)
#else
#define RENDER_DIVIDER_BETWEEN_Y(textObj1, textObj2)                             \
    divider.y = (textObj1.rect.y + textObj2.rect.y + FONT_SIZE - divider.h) / 2; \
    SDL_RenderFillRect(renderer, &divider);
#endif

#define RENDER_CONTROLS_TEXT_PAGE_1()                             \
	RENDER_TEXT_LARGE(text_Controls_1);                           \
	RENDER_TEXT(text_Controls_2a);                                \
	RENDER_TEXT(text_Controls_2b);                                \
	RENDER_TEXT(text_Controls_2c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_2c, text_Controls_3c); \
	RENDER_TEXT(text_Controls_3a);                                \
	RENDER_TEXT(text_Controls_3b);                                \
	RENDER_TEXT(text_Controls_3c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_3c, text_Controls_4c); \
	RENDER_TEXT(text_Controls_4a);                                \
	RENDER_TEXT(text_Controls_4b);                                \
	RENDER_TEXT(text_Controls_4c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_4c, text_Controls_5b); \
	RENDER_TEXT(text_Controls_5a);                                \
	RENDER_TEXT(text_Controls_5b);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_5b, text_Controls_6b); \
	RENDER_TEXT(text_Controls_6a);                                \
	RENDER_TEXT(text_Controls_6b);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_6b, text_Controls_7a); \
	RENDER_TEXT(text_Controls_7a);                                \
	RENDER_TEXT(text_Controls_7b);                                \
	RENDER_TEXT(text_Controls_7c);                                \
	RENDER_TEXT(text_Controls_P1);

#define RENDER_CONTROLS_TEXT_PAGE_2()                               \
	RENDER_TEXT_LARGE(text_Controls_8);                             \
	RENDER_TEXT(text_Controls_9a);                                  \
	RENDER_TEXT(text_Controls_9b);                                  \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_9a, text_Controls_10a);  \
	RENDER_TEXT(text_Controls_10a);                                 \
	RENDER_TEXT(text_Controls_10b);                                 \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_10a, text_Controls_11a); \
	RENDER_TEXT(text_Controls_11a);                                 \
	RENDER_TEXT(text_Controls_11b);                                 \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_11a, text_Controls_12a); \
	RENDER_TEXT(text_Controls_12a);                                 \
	RENDER_TEXT(text_Controls_12b);                                 \
	RENDER_TEXT(text_Controls_12c);                                 \
	RENDER_TEXT(text_Controls_P2);

#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(PSP) && !defined(ANDROID)
#define RENDER_CONTROLS_TEXT_PAGE_3()                             \
	RENDER_TEXT_LARGE(text_Controls_c_1);                         \
	RENDER_TEXT(text_Controls_c_2a);                              \
	RENDER_TEXT(text_Controls_2c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_2c, text_Controls_3c); \
	RENDER_TEXT(text_Controls_c_3a);                              \
	RENDER_TEXT(text_Controls_3c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_3c, text_Controls_4c); \
	RENDER_TEXT(text_Controls_c_4a);                              \
	RENDER_TEXT(text_Controls_4c);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_4c, text_Controls_5b); \
	RENDER_TEXT(text_Controls_c_5a);                              \
	RENDER_TEXT(text_Controls_5b);                                \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_5b, text_Controls_6b); \
	RENDER_TEXT(text_Controls_c_6a);                              \
	RENDER_TEXT(text_Controls_6b);                                \
	RENDER_TEXT(text_Controls_c_P1);

#define RENDER_CONTROLS_TEXT_PAGE_4()                                  \
	RENDER_TEXT_LARGE(text_Controls_c_8);                              \
	RENDER_TEXT(text_Controls_c_9a);                                   \
	RENDER_TEXT(text_Controls_9b);                                     \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_c_9a, text_Controls_c_10a); \
    if (videoSettings.aspectRatioIndex == 0) {                         \
	    RENDER_TEXT(text_Controls_c_10aa);                             \
    } else {                                                           \
        RENDER_TEXT(text_Controls_c_10a);                              \
    }                                                                  \
	RENDER_TEXT(text_Controls_10b);                                    \
    RENDER_DIVIDER_BETWEEN_Y(text_Controls_10a, text_Controls_c_12a);  \
	RENDER_TEXT(text_Controls_c_12a);                                  \
	RENDER_TEXT(text_Controls_c_12b);                                  \
	RENDER_TEXT(text_Controls_c_12c);                                  \
	RENDER_TEXT(text_Controls_c_P2);
#endif

#define CREDITS_STEP 1.6

#define SET_CREDITS_TEXT()                                                                                                                                                   \
    SET_LARGE_TEXT_WITH_OUTLINE("CODING, DESIGN, AND ART", text_Credits_1, OBJ_TO_MID_SCREEN_X(text_Credits_1),              (FONT_SIZE * (CREDITS_STEP *    1))          ); \
    SET_TEXT_WITH_OUTLINE("Mips96",                     text_Credits_2,   OBJ_TO_MID_SCREEN_X(text_Credits_2),               (FONT_SIZE * (CREDITS_STEP *    5))          ); \
    SET_TEXT_WITH_OUTLINE("https://github.com/Mips96",  text_Credits_3, OBJ_TO_MID_SCREEN_X(text_Credits_3),                 (FONT_SIZE * (CREDITS_STEP * 6.25))          ); \
	SET_TEXT_WITH_OUTLINE("(1/7)",                      text_Credits_P1,  (gameWidth - (text_Credits_P1.rect.w * 1.25)),     (gameHeight - (text_Credits_P1.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("MUSIC",                text_Credits_4,   OBJ_TO_MID_SCREEN_X(text_Credits_4),               (FONT_SIZE * (CREDITS_STEP *     1))         ); \
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5b, 0.25),  (FONT_SIZE * (CREDITS_STEP *   3.5))         ); \
    SET_TEXT_WITH_OUTLINE("\"Wonder Flow\"",            text_Credits_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5a, 0.75),  (FONT_SIZE * (CREDITS_STEP *   3.5))         ); \
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6b, 0.25),  (FONT_SIZE * (CREDITS_STEP *  4.75))         ); \
    SET_TEXT_WITH_OUTLINE("\"Sudoku Padawan\"",         text_Credits_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6a, 0.75),  (FONT_SIZE * (CREDITS_STEP *  4.75))         ); \
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_7b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7b, 0.25),  (FONT_SIZE * (CREDITS_STEP *     6))         ); \
    SET_TEXT_WITH_OUTLINE("\"Electroquest\"",           text_Credits_7a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7a, 0.75),  (FONT_SIZE * (CREDITS_STEP *     6))         ); \
    SET_TEXT_WITH_OUTLINE("Soundscape",                 text_Credits_8b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8b, 0.25),  (FONT_SIZE * (CREDITS_STEP *  7.25))         ); \
    SET_TEXT_WITH_OUTLINE("\"Main Menu\"",              text_Credits_8a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8a, 0.75),  (FONT_SIZE * (CREDITS_STEP *  7.25))         ); \
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9b, 0.25),  (FONT_SIZE * (CREDITS_STEP *   8.5))         ); \
    SET_TEXT_WITH_OUTLINE("\"Insomnia\"",               text_Credits_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9a, 0.75),  (FONT_SIZE * (CREDITS_STEP *   8.5))         ); \
    SET_TEXT_WITH_OUTLINE("Solon",                      text_Credits_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10b, 0.25), (FONT_SIZE * (CREDITS_STEP *  9.75))         ); \
    SET_TEXT_WITH_OUTLINE("\"Ontario\"",                text_Credits_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10a, 0.75), (FONT_SIZE * (CREDITS_STEP *  9.75))         ); \
    SET_TEXT_WITH_OUTLINE("Noiseless",                  text_Credits_11b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11b, 0.25), (FONT_SIZE * (CREDITS_STEP *    11))         ); \
    SET_TEXT_WITH_OUTLINE("\"Addiction\"",              text_Credits_11a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11a, 0.75), (FONT_SIZE * (CREDITS_STEP *    11))         ); \
    SET_TEXT_WITH_OUTLINE("All music obtained from modarchive.org", text_Credits_12, OBJ_TO_MID_SCREEN_X(text_Credits_12),   (FONT_SIZE * (CREDITS_STEP * 12.75))         ); \
	SET_TEXT_WITH_OUTLINE("(2/7)",                      text_Credits_P2,  (gameWidth - (text_Credits_P2.rect.w * 1.25)),     (gameHeight - (text_Credits_P2.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("LIBRARIES",            text_Credits_13,  OBJ_TO_MID_SCREEN_X(text_Credits_13),              (FONT_SIZE * (CREDITS_STEP *  1))            ); \
    SET_TEXT_WITH_OUTLINE("SDL2",                       text_Credits_14,  OBJ_TO_MID_SCREEN_X(text_Credits_14),              (FONT_SIZE * (CREDITS_STEP *  5))            ); \
    SET_TEXT_WITH_OUTLINE("SDL2_image",                 text_Credits_15,  OBJ_TO_MID_SCREEN_X(text_Credits_15),              (FONT_SIZE * (CREDITS_STEP *  7))            ); \
    SET_TEXT_WITH_OUTLINE("SDL2_ttf",                   text_Credits_16,  OBJ_TO_MID_SCREEN_X(text_Credits_16),              (FONT_SIZE * (CREDITS_STEP *  9))            ); \
    SET_TEXT_WITH_OUTLINE("SDL2_mixer",                 text_Credits_17,  OBJ_TO_MID_SCREEN_X(text_Credits_17),              (FONT_SIZE * (CREDITS_STEP * 11))            ); \
	SET_TEXT_WITH_OUTLINE("(3/7)",                      text_Credits_P3,  (gameWidth - (text_Credits_P3.rect.w * 1.25)),     (gameHeight - (text_Credits_P3.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("FONT",                 text_Credits_18,  OBJ_TO_MID_SCREEN_X(text_Credits_18),              (FONT_SIZE * (CREDITS_STEP *    1))          ); \
    SET_TEXT_WITH_OUTLINE("Commodore Pixelized v1.2",   text_Credits_19,  OBJ_TO_MID_SCREEN_X(text_Credits_19),              (FONT_SIZE * (CREDITS_STEP *    5))          ); \
    SET_TEXT_WITH_OUTLINE("by Devin Cook",              text_Credits_20,  OBJ_TO_MID_SCREEN_X(text_Credits_20),              (FONT_SIZE * (CREDITS_STEP * 6.25))          ); \
	SET_TEXT_WITH_OUTLINE("(4/7)",                      text_Credits_P4,  (gameWidth - (text_Credits_P4.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("SOUND EFFECTS",        text_Credits_21,  OBJ_TO_MID_SCREEN_X(text_Credits_21),              (FONT_SIZE * (CREDITS_STEP *    1))          ); \
    SET_TEXT_WITH_OUTLINE("Luke.RUSTLTD",               text_Credits_22,  OBJ_TO_MID_SCREEN_X(text_Credits_22),              (FONT_SIZE * (CREDITS_STEP *    5))          ); \
    SET_TEXT_WITH_OUTLINE("opengameart.org",            text_Credits_23,  OBJ_TO_MID_SCREEN_X(text_Credits_23),              (FONT_SIZE * (CREDITS_STEP * 6.25))          ); \
	SET_TEXT_WITH_OUTLINE("(5/7)",                      text_Credits_P5,  (gameWidth - (text_Credits_P5.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("THANKS FOR PLAYING!",  text_Credits_24,  OBJ_TO_MID_SCREEN_X(text_Credits_24),              (FONT_SIZE * (CREDITS_STEP *    1))          ); \
    SET_TEXT_WITH_OUTLINE("Here's a cheat...",          text_Credits_25,  OBJ_TO_MID_SCREEN_X(text_Credits_25),              (FONT_SIZE * (CREDITS_STEP *  3.5))          ); \
    SET_TEXT_WITH_OUTLINE("If you get stuck on a puzzle,", text_Credits_26, OBJ_TO_MID_SCREEN_X(text_Credits_26),            (FONT_SIZE * (CREDITS_STEP * 4.75))          ); \
    SET_TEXT_WITH_OUTLINE(CHEAT_TEXT,                   text_Credits_27,  OBJ_TO_MID_SCREEN_X(text_Credits_27),              (FONT_SIZE * (CREDITS_STEP *    6))          ); \
    SET_TEXT_WITH_OUTLINE("to reveal the highlighted cell.", text_Credits_28, OBJ_TO_MID_SCREEN_X(text_Credits_28),          (FONT_SIZE * (CREDITS_STEP * 7.25))          ); \
    SET_TEXT_WITH_OUTLINE("I hope you enjoy the game!", text_Credits_29,  OBJ_TO_MID_SCREEN_X(text_Credits_29),              (FONT_SIZE * (CREDITS_STEP *  8.5))          ); \
    SET_TEXT_WITH_OUTLINE("- Mips96",                   text_Credits_30,  OBJ_TO_MID_SCREEN_X(text_Credits_30),              (FONT_SIZE * (CREDITS_STEP *   11))          ); \
	SET_TEXT_WITH_OUTLINE("(6/7)",                      text_Credits_P6,  (gameWidth - (text_Credits_P6.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5))); \
    SET_LARGE_TEXT_WITH_OUTLINE("WANT MORE?",           text_Credits_31,  OBJ_TO_MID_SCREEN_X(text_Credits_31),              (FONT_SIZE * (CREDITS_STEP *     1))          ); \
    SET_TEXT_WITH_OUTLINE("SuDokuL is available on:",   text_Credits_32,  OBJ_TO_MID_SCREEN_X(text_Credits_32),              (FONT_SIZE * (CREDITS_STEP *   3.5))          ); \
    SET_TEXT_WITH_OUTLINE("PC",                         text_Credits_33,  OBJ_TO_MID_SCREEN_X(text_Credits_33),              (FONT_SIZE * (CREDITS_STEP *  4.75))          ); \
    SET_TEXT_WITH_OUTLINE("Android",                    text_Credits_34,  OBJ_TO_MID_SCREEN_X(text_Credits_34),              (FONT_SIZE * (CREDITS_STEP *     6))          ); \
    SET_TEXT_WITH_OUTLINE("Switch",                     text_Credits_35,  OBJ_TO_MID_SCREEN_X(text_Credits_35),              (FONT_SIZE * (CREDITS_STEP *  7.25))          ); \
    SET_TEXT_WITH_OUTLINE("Wii U",                      text_Credits_36,  OBJ_TO_MID_SCREEN_X(text_Credits_36),              (FONT_SIZE * (CREDITS_STEP *   8.5))          ); \
    SET_TEXT_WITH_OUTLINE("Vita",                       text_Credits_37,  OBJ_TO_MID_SCREEN_X(text_Credits_37),              (FONT_SIZE * (CREDITS_STEP *  9.75))          ); \
    SET_TEXT_WITH_OUTLINE("PSP",                        text_Credits_38,  OBJ_TO_MID_SCREEN_X(text_Credits_38),              (FONT_SIZE * (CREDITS_STEP *    11))          ); \
    SET_TEXT_WITH_OUTLINE("https://github.com/Mips96/SuDokuL", text_Credits_39, OBJ_TO_MID_SCREEN_X(text_Credits_39),        (FONT_SIZE * (CREDITS_STEP * 12.75))          ); \
	SET_TEXT_WITH_OUTLINE("(7/7)",                      text_Credits_P7,  (gameWidth - (text_Credits_P7.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5)));

#if defined(WII_U) || defined(SWITCH) || defined(ANDROID)
#define CHEAT_TEXT "press X or Y 10 times"
#elif defined(VITA) || defined(PSP)
#define CHEAT_TEXT "press Square or Triangle 10 times"
#else
#define CHEAT_TEXT "press the Period key 10 times"
#endif

#define RENDER_CREDITS_TEXT_PAGE_1()   \
    RENDER_TEXT_LARGE(text_Credits_1); \
    RENDER_TEXT(text_Credits_2);       \
    RENDER_TEXT(text_Credits_3);       \
    RENDER_TEXT(text_Credits_P1);

#define RENDER_CREDITS_TEXT_PAGE_2()                              \
    RENDER_TEXT_LARGE(text_Credits_4);                            \
    RENDER_TEXT(text_Credits_5a);                                 \
    RENDER_TEXT(text_Credits_5b);                                 \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_5a, text_Credits_6a);   */ \
    RENDER_TEXT(text_Credits_6a);                                 \
    RENDER_TEXT(text_Credits_6b);                                 \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_6a, text_Credits_7a);   */ \
    RENDER_TEXT(text_Credits_7a);                                 \
    RENDER_TEXT(text_Credits_7b);                                 \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_7a, text_Credits_8a);   */ \
    RENDER_TEXT(text_Credits_8a);                                 \
    RENDER_TEXT(text_Credits_8b);                                 \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_8a, text_Credits_9a);   */ \
    RENDER_TEXT(text_Credits_9a);                                 \
    RENDER_TEXT(text_Credits_9b);                                 \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_9a, text_Credits_10a);  */ \
    RENDER_TEXT(text_Credits_10a);                                \
    RENDER_TEXT(text_Credits_10b);                                \
    /* RENDER_DIVIDER_BETWEEN_Y(text_Credits_10a, text_Credits_11a); */ \
    RENDER_TEXT(text_Credits_11a);                                \
    RENDER_TEXT(text_Credits_11b);                                \
    RENDER_TEXT(text_Credits_12);                                 \
    RENDER_TEXT(text_Credits_P2);

#define RENDER_CREDITS_TEXT_PAGE_5()    \
    RENDER_TEXT_LARGE(text_Credits_13); \
    RENDER_TEXT(text_Credits_14);       \
    RENDER_TEXT(text_Credits_15);       \
    RENDER_TEXT(text_Credits_16);       \
    RENDER_TEXT(text_Credits_17);       \
    RENDER_TEXT(text_Credits_P5);

#define RENDER_CREDITS_TEXT_PAGE_3()    \
    RENDER_TEXT_LARGE(text_Credits_18); \
    RENDER_TEXT(text_Credits_19);       \
    RENDER_TEXT(text_Credits_20);       \
    RENDER_TEXT(text_Credits_P3);

#define RENDER_CREDITS_TEXT_PAGE_4()    \
    RENDER_TEXT_LARGE(text_Credits_21); \
    RENDER_TEXT(text_Credits_22);       \
    RENDER_TEXT(text_Credits_23);       \
    RENDER_TEXT(text_Credits_P4);

#define RENDER_CREDITS_TEXT_PAGE_6()    \
    RENDER_TEXT_LARGE(text_Credits_24); \
    RENDER_TEXT(text_Credits_25);       \
    RENDER_TEXT(text_Credits_26);       \
    RENDER_TEXT(text_Credits_27);       \
    RENDER_TEXT(text_Credits_28);       \
    RENDER_TEXT(text_Credits_29);       \
    RENDER_TEXT(text_Credits_30);       \
    RENDER_TEXT(text_Credits_P6);

#define RENDER_CREDITS_TEXT_PAGE_7()    \
    RENDER_TEXT_LARGE(text_Credits_31); \
    RENDER_TEXT(text_Credits_32);       \
    RENDER_TEXT(text_Credits_33);       \
    RENDER_TEXT(text_Credits_34);       \
    RENDER_TEXT(text_Credits_35);       \
    RENDER_TEXT(text_Credits_36);       \
    RENDER_TEXT(text_Credits_37);       \
    RENDER_TEXT(text_Credits_38);       \
    RENDER_TEXT(text_Credits_39);       \
    RENDER_TEXT(text_Credits_P7);

#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID)
#define CONTROLS_SET_CONFIRM_BACK_POS()                                                \
    if (controlSettings.swapConfirmAndBack) {                                          \
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)) - CONTROLS_SPACER; \
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));                   \
    } else {                                                                           \
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));                   \
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)) - CONTROLS_SPACER; \
    }
#elif defined(PSP)
#define CONTROLS_SET_CONFIRM_BACK_POS()                              \
    if (controlSettings.swapConfirmAndBack) {                        \
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)); \
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7)); \
    } else {                                                         \
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7)); \
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)); \
    }
#else
#define CONTROLS_SET_CONFIRM_BACK_POS()                                \
    if (controlSettings.swapConfirmAndBack) {                          \
        text_Controls_c_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)); \
        text_Controls_c_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7)); \
    } else {                                                           \
        text_Controls_c_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7)); \
        text_Controls_c_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)); \
    }
#endif

#endif