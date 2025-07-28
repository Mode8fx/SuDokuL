#include "general.h"
#include "menu_logic.h"
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

// VideoSettings (resolution and index only) are re-loaded so that any unsaved changes that can only be applied by closing the game are undone
bool menuHandleBackButton(Uint8 state) {
    if (keyPressed(INPUT_BACK)) {
        time_anim1 = 0;
        programState = state;
        menuResetCursorPositions(state);
        reloadVideoSettings();
        changedProgramState = true;
        return true;
    }
    return false;
}

bool menuHandleBackButtonWithSettings(Uint8 state) {
    if (keyPressed(INPUT_BACK)) {
        time_anim1 = 0;
#if defined(WII)
        if (programState == 28) {
            controlSettings.wiimoteScheme = wiimoteSchemeTempVal;
            keyInputs = 0;
            dirInputs = UP_DEPRESSED | DOWN_DEPRESSED | LEFT_DEPRESSED | RIGHT_DEPRESSED;
        }
#endif
        if (programState == 20) {
          reloadVideoSettings();
        }
        programState = state;
        menuResetCursorPositions(state);
        saveCurrentSettings();
        changedProgramState = true;
        return true;
    }
    return false;
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
    menuCursor.rect.y = TEXT_PLAY_Y + (fontSize / 2) - (menuCursor.rect.h / 2) + (cursor * (fontSize * 2));
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
        menuCursorIndex_controls = (menuCursorIndex_controls + 1) % 3;
        updateControlsMenuCursorPositionY();
    }
    if (keyPressed(INPUT_UP)) {
        if (--menuCursorIndex_controls < 0)
            menuCursorIndex_controls = 2;
        updateControlsMenuCursorPositionY();
    }
}

void updateControlsMenuCursorPositionY() {
    menuCursor.rect.y = TEXT_PLAY_Y + (fontSize / 2) - (menuCursor.rect.h / 2) + (menuCursorIndex_controls * 2 * (fontSize * 2));
}

void menuHandleVertCursorMovementMouse(Sint8 &cursor, TextObject textObj, Sint8 index) {
    if (mouseIsInRect(textObj.rect)) {
        cursor = index;
        updateMenuCursorPositionY(cursor);
    }
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

void resetBGToDefault() {
    bgSettings.type = 1;
    bgSettings.scrollDir = 22;
    bgSettings.speedMult = 15;
    //bgSettings.scale = max(min((int)min(gameWidthMult, gameHeightMult), 5), 1);
    bgSettings.scale = defaultBGScale;
    setSpriteScaleTile();
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
  setSpriteScaleTile();
}

void setBGScrollSpeed() {
  Sint8 tileSizeResMult = max(static_cast<Sint8>(std::floor(gameHeight / 480.0)), (Sint8)1);
#if defined(FUNKEY) // FunKey just doesn't handle cos and sin properly
  if (bgSettings.scrollDir == 18 || bgSettings.scrollDir == 36 || bgSettings.scrollDir == 54) {
    bgScroll.speed_x = cos(((double)bgSettings.scrollDir + 18) * 5 * PI / 180) * tileSizeResMult;
    bgScroll.speed_y = sin(((double)bgSettings.scrollDir + 18) * 5 * PI / 180) * tileSizeResMult;
  } else {
    bgScroll.speed_x = cos(((double)bgSettings.scrollDir) * 5 * PI / 180) * tileSizeResMult;
    bgScroll.speed_y = sin(((double)bgSettings.scrollDir) * 5 * PI / 180) * tileSizeResMult;
  }
#else
    bgScroll.speed_x = cos(((double)bgSettings.scrollDir) * 5 * PI / 180) * tileSizeResMult;
    bgScroll.speed_y = sin(((double)bgSettings.scrollDir) * 5 * PI / 180) * tileSizeResMult;
#endif
}
