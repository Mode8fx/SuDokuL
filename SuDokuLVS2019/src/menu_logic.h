#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

#include "include.h"
#include "shared.h"
#include "config.h"
#include "text_objects.h"
#include "sprite_objects.h"
#include "window.h"

/* Menu Cursors */
extern Sint8 menuCursorIndex_main;
extern Sint8 menuCursorIndex_continue;
extern Sint8 menuCursorIndex_play;
extern Sint8 menuIndex_controls;
extern Sint8 menuCursorIndex_options;
extern Sint8 menuCursorIndex_controls;
extern Sint8 menuCursorIndex_video;
extern Sint8 menuCursorIndex_sound;
extern Sint8 menuCursorIndex_background;
extern Sint8 menuIndex_credits;
extern Sint8 wiimoteSchemeTempVal;

extern void updateMainMenuCursorPositionX();
extern void updateContinueMenuCursorPositionX();
extern void updatePlayMenuCursorPositionX();
extern void updateOptionsMenuCursorPositionX();
extern bool menuHandleBackButton(Uint8);
extern bool menuHandleBackButtonWithSettings(Uint8);
extern void menuResetCursorPositions(Uint8);
extern void updateMenuCursorPositionY(Sint8);
extern void menuHandleMenuButton();
extern void menuHandleVertCursorMovement(Sint8 &, Uint8, Uint8);
extern void controlsMenuHandleVertCursorMovement();
extern void updateControlsMenuCursorPositionY();
extern void menuHandleVertCursorMovementMouse(Sint8 &, TextObject, Sint8);
extern void menuHandleVertCursorMovementMouseWithSetting(Sint8 &, TextObject, Sint16, Sint8);
extern void controlsMenuHandleVertCursorMovementMouse(TextObject, Sint8);
extern void resetBGToDefault();
extern void setBGType();
extern void setBGScrollSpeed();
extern inline void updateControlsMenuCursorPositionX();
extern inline void updateVideoMenuCursorPositionX();
extern inline void updateSoundMenuCursorPositionX();
extern inline void updateBackgroundMenuCursorPositionX();
extern inline bool mouseIsInRect(TextRect);
extern inline bool mouseIsInRectWithSetting(TextRect, Sint16);
extern inline bool mouseMoved();
extern inline void updateMousePosViewportMouse();
extern inline void updateMousePosViewportTouch();

inline void updateControlsMenuCursorPositionX() {
  menuCursor.rect.x = (int)(CONTROLS_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

inline void updateVideoMenuCursorPositionX() {
  menuCursor.rect.x = (int)(VIDEO_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

inline void updateSoundMenuCursorPositionX() {
  menuCursor.rect.x = (int)(SOUND_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

inline void updateBackgroundMenuCursorPositionX() {
  menuCursor.rect.x = (int)(BACKGROUND_MENU_CURSOR_POSITION_X - menuCursorXOffset());
}

inline bool mouseIsInRect(TextRect r) {
  return (mouseInput_x >= r.x)
    && (mouseInput_x <= (r.x + r.w))
    && (mouseInput_y >= r.y)
    && (mouseInput_y <= (r.y + r.h));
}

inline bool mouseIsInRectWithSetting(TextRect r, Sint16 endpointX) {
  return (mouseInput_x >= r.x)
    && (mouseInput_x <= (endpointX))
    && (mouseInput_y >= r.y)
    && (mouseInput_y <= (r.y + r.h));
}

// Used for both menu and game
inline bool mouseMoved() {
  return (mouseInput_x != mouseInput_x_last) || (mouseInput_y != mouseInput_y_last) || keyPressed(INPUT_CONFIRM_ALT);
}

inline void updateMousePosViewportMouse() {
#if defined(WII)
  mouseInput_x = (int)(mouseInput_x / screenScale);
  mouseInput_y = (int)(mouseInput_y / screenScale);
#else
  mouseInput_x = (int)(mouseInput_x / screenScale - centerViewport.x);
  mouseInput_y = (int)(mouseInput_y / screenScale - centerViewport.y);
#endif
}

inline void updateMousePosViewportTouch() {
#if defined(WII_U)
  mouseInput_x = (int)((mouseInput_x * SCALING_WIDTH / centerViewport.w) - centerViewport.x);
  mouseInput_y = (int)((mouseInput_y * SCALING_HEIGHT / centerViewport.h) - centerViewport.y);
#elif !defined(ANDROID)
  mouseInput_x = (int)(mouseInput_x * screenScale);
  mouseInput_y = (int)(mouseInput_y * screenScale);
#endif
}

#endif