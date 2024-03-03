#include "general.h"
#include "menu_logic.h"
#include "config.h"
#include "sprite_objects.h"
#include "window.h"
#include "shared.h"

void updateMainMenuCursorPositionX() {
    switch (menuCursorIndex_main) {
    case 0:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Play) - menuCursorXOffset());
        break;
    case 1:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Controls) - menuCursorXOffset());
        break;
    case 2:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Options) - menuCursorXOffset());
        break;
#if !defined(ANDROID)
    case 4:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Quit) - menuCursorXOffset());
        break;
#endif
    default:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Credits) - menuCursorXOffset());
        break;
    }
}

void updateContinueMenuCursorPositionX() {
    switch (menuCursorIndex_play) {
        case 0:
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Continue) - menuCursorXOffset());
            break;
        default:
            menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_New_Game) - menuCursorXOffset());
            break;
    }
}

void updatePlayMenuCursorPositionX() {
    switch (menuCursorIndex_play) {
    case 0:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Easy) - menuCursorXOffset());
        break;
    case 1:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Normal) - menuCursorXOffset());
        break;
    case 2:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Hard) - menuCursorXOffset());
        break;
    default:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Very_Hard) - menuCursorXOffset());
        break;
    }
}

void updateOptionsMenuCursorPositionX() {
    switch (menuCursorIndex_options) {
    case 0:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Controls_Menu) - menuCursorXOffset());
        break;
    case 1:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Video) - menuCursorXOffset());
        break;
    case 2:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Sound) - menuCursorXOffset());
        break;
    case 3:
        menuCursor.rect.x = (int)(OBJ_TO_MID_SCREEN_X(text_Background) - menuCursorXOffset());
        break;
    default:
        break;
    }
}

void updateControlsMenuCursorPositionX() {
    menuCursor.rect.x = (int)(CONTROLS_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

void updateVideoMenuCursorPositionX() {
    menuCursor.rect.x = (int)(VIDEO_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

void updateSoundMenuCursorPositionX() {
    menuCursor.rect.x = (int)(SOUND_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

void updateBackgroundMenuCursorPositionX() {
    menuCursor.rect.x = (int)(BACKGROUND_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

// Settings are re-loaded so that any unsaved changes from the video menu are undone
void menuHandleBackButton(Uint8 state) {
    if (keyPressed(INPUT_BACK)) {
        time_anim1 = 0;
        programState = state;
        menuResetCursorPositions(state);
        loadSettingsFile();
        changedProgramState = true;
    }
}

void menuHandleBackButtonWithSettings(Uint8 state) {
    if (keyPressed(INPUT_BACK)) {
        time_anim1 = 0;
        programState = state;
        menuResetCursorPositions(state);
        saveCurrentSettings();
        changedProgramState = true;
    }
}

void menuResetCursorPositions(Uint8 state) {
    switch (state) {
    case 2:
        menuCursorIndex_play = 0;
        menuCursorIndex_options = 0;
        break;
    case 13:
        menuCursorIndex_controls = 0;
        menuCursorIndex_video = 0;
        menuCursorIndex_sound = 0;
        menuCursorIndex_background = 0;
        break;
    default:
        break;
    }
}

void updateMenuCursorPositionY(Sint8 cursor) {
    menuCursor.rect.y = TEXT_PLAY_Y + (FONT_SIZE / 2) - (menuCursor.rect.h / 2) + (cursor * (FONT_SIZE * 2));
}

void menuHandleMenuButton() {
    if (keyPressed(INPUT_SELECT)) {
        time_anim1 = 0;
        savePuzzle();
        programState = 2;
        updateMenuCursorPositionY(menuCursorIndex_main);
    }
}

void menuHandleVertCursorMovement(Sint8 &cursor, Uint8 numOptions, Uint8 numSkip) {
    if (keyPressed(INPUT_DOWN)) {
        if (++cursor >= numOptions)
			cursor = numSkip;
        updateMenuCursorPositionY(cursor);
    }
    if (keyPressed(INPUT_UP)) {
        if (--cursor < numSkip)
            cursor = numOptions - 1;
        updateMenuCursorPositionY(cursor);
    }
}

void controlsMenuHandleVertCursorMovement() {
    if (keyPressed(INPUT_DOWN)) {
        menuCursorIndex_controls = (menuCursorIndex_controls + 1) % 2;
        updateControlsMenuCursorPositionY();
    }
    if (keyPressed(INPUT_UP)) {
        if (--menuCursorIndex_controls < 0)
            menuCursorIndex_controls = 1;
        updateControlsMenuCursorPositionY();
    }
}

void updateControlsMenuCursorPositionY() {
    menuCursor.rect.y = TEXT_PLAY_Y + (FONT_SIZE / 2) - (menuCursor.rect.h / 2) + (menuCursorIndex_controls * 2 * (FONT_SIZE * 2));
}

void menuHandleVertCursorMovementMouse(Sint8 &cursor, TextObject textObj, Sint8 index) {
    if (mouseIsInRect(textObj.rect)) {
        cursor = index;
        updateMenuCursorPositionY(cursor);
    }
}

bool mouseIsInRect(TextRect r) {
    return (mouseInput_x >= r.x)
        && (mouseInput_x <= (r.x + r.w))
        && (mouseInput_y >= r.y)
        && (mouseInput_y <= (r.y + r.h));
}

void menuHandleVertCursorMovementMouseWithSetting(Sint8 &cursor, TextObject textObj, Sint16 endpointX, Sint8 index) {
    if (mouseIsInRectWithSetting(textObj.rect, endpointX)) {
        cursor = index;
        updateMenuCursorPositionY(cursor);
    }
}

void controlsMenuHandleVertCursorMovementMouse(TextObject textObj, Sint8 index) {
    if (mouseIsInRectWithSetting(textObj.rect, CONTROLS_MENU_ENDPOINT)) {
        menuCursorIndex_controls = index;
        updateControlsMenuCursorPositionY();
    }
}

bool mouseIsInRectWithSetting(TextRect r, Sint16 endpointX) {
    return (mouseInput_x >= r.x)
        && (mouseInput_x <= (endpointX))
        && (mouseInput_y >= r.y)
        && (mouseInput_y <= (r.y + r.h));
}
void setBGType() {
    switch (bgSettings.type) {
		case 2:
			tile = &tile2;
            break;
        case 3:
            tile = &tile3;
			break;
        case 4:
            tile = &tile_grasslands;
			break;
        case 5:
            tile = &tile_grasslands2;
            break;
        case 6:
            tile = &tile_desert;
            break;
        case 7:
            tile = &tile_cave;
			break;
        case 8:
            tile = &tile_snowymountain;
			break;
        default:
            tile = &tile1;
			break;
    }
}

void setBGScrollSpeed() {
    bgScroll.speed_x = cos(((double)bgSettings.scrollDir) * 5 * PI / 180);
    bgScroll.speed_y = sin(((double)bgSettings.scrollDir) * 5 * PI / 180);
}

// Used for both menu and game
bool mouseMoved() {
    return (mouseInput_x != mouseInput_x_last) || (mouseInput_y != mouseInput_y_last) || keyPressed(INPUT_CONFIRM_ALT);
}

void updateMousePosViewportMouse() {
    mouseInput_x = (Sint32)(mouseInput_x / screenScale - centerViewport.x);
    mouseInput_y = (Sint32)(mouseInput_y / screenScale - centerViewport.y);
}

void updateMousePosViewportTouch() {
#if defined(WII_U)
    mouseInput_x = (Sint32)((mouseInput_x * SCALING_WIDTH / centerViewport.w) - centerViewport.x);
    mouseInput_y = (Sint32)((mouseInput_y * SCALING_HEIGHT / centerViewport.h) - centerViewport.y);
#elif !defined(ANDROID)
    mouseInput_x = (Sint32)(mouseInput_x * screenScale);
    mouseInput_y = (Sint32)(mouseInput_y * screenScale);
#endif
}
