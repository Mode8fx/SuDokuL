#include "include.h"
#include "shared.h"

#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

#if !defined(ANDROID)
#define UPDATE_MAIN_MENU_CURSOR_POSITION_X()                                                      \
    switch (menuCursorIndex_main) {                                                               \
        case 0:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Play) - MENU_CURSOR_X_OFFSET);     \
            break;                                                                                \
        case 1:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Controls) - MENU_CURSOR_X_OFFSET); \
            break;                                                                                \
        case 2:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Options) - MENU_CURSOR_X_OFFSET);  \
            break;                                                                                \
        case 3:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Credits) - MENU_CURSOR_X_OFFSET);  \
            break;                                                                                \
        default:                                                                                  \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Quit) - MENU_CURSOR_X_OFFSET);     \
            break;                                                                                \
    }
#else
#define UPDATE_MAIN_MENU_CURSOR_POSITION_X()                                                      \
    switch (menuCursorIndex_main) {                                                               \
        case 0:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Play) - MENU_CURSOR_X_OFFSET);     \
            break;                                                                                \
        case 1:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Controls) - MENU_CURSOR_X_OFFSET); \
            break;                                                                                \
        case 2:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Options) - MENU_CURSOR_X_OFFSET);  \
            break;                                                                                \
        default:                                                                                  \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Credits) - MENU_CURSOR_X_OFFSET);  \
            break;                                                                                \
    }
#endif

#define UPDATE_PLAY_MENU_CURSOR_POSITION_X()                                                       \
    switch (menuCursorIndex_play) {                                                                \
        case 0:                                                                                    \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Easy) - MENU_CURSOR_X_OFFSET);      \
            break;                                                                                 \
        case 1:                                                                                    \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Normal) - MENU_CURSOR_X_OFFSET);    \
            break;                                                                                 \
        case 2:                                                                                    \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Hard) - MENU_CURSOR_X_OFFSET);      \
            break;                                                                                 \
        default:                                                                                   \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Very_Hard) - MENU_CURSOR_X_OFFSET); \
            break;                                                                                 \
    }

#define UPDATE_OPTIONS_MENU_CURSOR_POSITION_X()                                                        \
    switch (menuCursorIndex_options) {                                                                 \
        case 0:                                                                                        \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Controls_Menu) - MENU_CURSOR_X_OFFSET); \
            break;                                                                                     \
        case 1:                                                                                        \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Video) - MENU_CURSOR_X_OFFSET);         \
            break;                                                                                     \
        case 2:                                                                                        \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Sound) - MENU_CURSOR_X_OFFSET);         \
            break;                                                                                     \
        case 3:                                                                                        \
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Background) - MENU_CURSOR_X_OFFSET);    \
            break;                                                                                     \
        default:                                                                                       \
            break;                                                                                     \
    }

#define UPDATE_CONTROLS_MENU_CURSOR_POSITION_X() \
    menuCursor.rect.x = (int)(CONTROLS_MENU_CURSOR_POSITION_X - MENU_CURSOR_X_OFFSET);

#define UPDATE_VIDEO_MENU_CURSOR_POSITION_X() \
    menuCursor.rect.x = (int)(VIDEO_MENU_CURSOR_POSITION_X - MENU_CURSOR_X_OFFSET);

#define UPDATE_SOUND_MENU_CURSOR_POSITION_X() \
    menuCursor.rect.x = (int)(SOUND_MENU_CURSOR_POSITION_X - MENU_CURSOR_X_OFFSET);

#define UPDATE_BACKGROUND_MENU_CURSOR_POSITION_X() \
    menuCursor.rect.x = (int)(BACKGROUND_MENU_CURSOR_POSITION_X - MENU_CURSOR_X_OFFSET);

// Settings are re-loaded so that any unsaved changes from the video menu are undone
#define MENU_HANDLE_BACK_BUTTON(state)                                   \
    if (KEY_PRESSED(INPUT_BACK)) {                                       \
        time_anim1 = 0;                                                  \
        programState = state;                                            \
        switch (state) {                                                 \
            case 2:                                                      \
                UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main);     \
                break;                                                   \
            case 13:                                                     \
                UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_options);  \
                break;                                                   \
            default:                                                     \
            break;                                                       \
        }                                                                \
        LOAD_SETTINGS_FILE();                                            \
    }

#define MENU_HANDLE_BACK_BUTTON_WITH_SETTINGS(state)                    \
    if (KEY_PRESSED(INPUT_BACK)) {                                      \
        time_anim1 = 0;                                                 \
        programState = state;                                           \
        switch (state) {                                                \
            case 2:                                                     \
                UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main);    \
                break;                                                  \
            case 13:                                                    \
                UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_options); \
                break;                                                  \
            default:                                                    \
            break;                                                      \
        }                                                               \
        SAVE_CURRENT_SETTINGS();                                        \
    }

#define UPDATE_MENU_CURSOR_POSITION_Y(cursor) \
    menuCursor.rect.y = TEXT_PLAY_Y + (FONT_SIZE / 2) - (menuCursor.rect.h / 2) + (cursor * (FONT_SIZE * 2));

#define MENU_HANDLE_MENU_BUTTON()                            \
    if (KEY_PRESSED(INPUT_SELECT)) {                         \
        time_anim1 = 0;                                      \
        programState = 2;                                    \
        UPDATE_MENU_CURSOR_POSITION_Y(menuCursorIndex_main); \
    }

#define MENU_HANDLE_VERT_CURSOR_MOVEMENT(cursor, numOptions) \
    if (KEY_PRESSED(INPUT_DOWN)) {                           \
        cursor = (cursor + 1) % numOptions;                  \
        UPDATE_MENU_CURSOR_POSITION_Y(cursor);               \
    }                                                        \
    if (KEY_PRESSED(INPUT_UP)) {                             \
        if (--cursor < 0)                                    \
            cursor = numOptions - 1;                         \
        UPDATE_MENU_CURSOR_POSITION_Y(cursor);               \
    }

#define CONTROLS_MENU_HANDLE_VERT_CURSOR_MOVEMENT()                    \
    if (KEY_PRESSED(INPUT_DOWN)) {                                     \
        menuCursorIndex_controls = (menuCursorIndex_controls + 1) % 2; \
        UPDATE_CONTROLS_MENU_CURSOR_POSITION_Y();                      \
    }                                                                  \
    if (KEY_PRESSED(INPUT_UP)) {                                       \
        if (--menuCursorIndex_controls < 0)                            \
            menuCursorIndex_controls = 1;                              \
        UPDATE_CONTROLS_MENU_CURSOR_POSITION_Y();                      \
    }

#define UPDATE_CONTROLS_MENU_CURSOR_POSITION_Y() \
    menuCursor.rect.y = TEXT_PLAY_Y + (FONT_SIZE / 2) - (menuCursor.rect.h / 2) + (menuCursorIndex_controls * 2 * (FONT_SIZE * 2));


#define MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(cursor, textObj, index) \
    if (MOUSE_IS_IN_RECT(textObj.rect)) {                              \
        cursor = index;                                                \
        UPDATE_MENU_CURSOR_POSITION_Y(cursor);                         \
    }

#define MOUSE_IS_IN_RECT(r) \
    ((mouseInput_x >= r.x) && (mouseInput_x <= (r.x + r.w)) && (mouseInput_y >= r.y) && (mouseInput_y <= (r.y + r.h)))

#define MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE_WITH_SETTING(cursor, textObj, endpointX, index) \
    if (MOUSE_IS_IN_RECT_WITH_SETTING(textObj.rect, endpointX)) {                              \
        cursor = index;                                                                        \
        UPDATE_MENU_CURSOR_POSITION_Y(cursor);                                                 \
    }

#define CONTROLS_MENU_HANDLE_VERT_CURSOR_MOVEMENT_MOUSE(textObj, index)        \
    if (MOUSE_IS_IN_RECT_WITH_SETTING(textObj.rect, CONTROLS_MENU_ENDPOINT)) { \
        menuCursorIndex_controls = index;                                      \
        UPDATE_CONTROLS_MENU_CURSOR_POSITION_Y();                              \
    }

#define MOUSE_IS_IN_RECT_WITH_SETTING(r, endpointX) \
    ((mouseInput_x >= r.x) && (mouseInput_x <= (endpointX)) && (mouseInput_y >= r.y) && (mouseInput_y <= (r.y + r.h)))

#define SET_BG_SCROLL_SPEED()                                              \
    bgScroll.speed_x = cos(((double)bgSettings.scrollDir) * 5 * PI / 180); \
    bgScroll.speed_y = sin(((double)bgSettings.scrollDir) * 5 * PI / 180);

#endif