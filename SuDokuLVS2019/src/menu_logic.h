#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

#include "include.h"
#include "shared.h"
#include "text_objects.h"

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

extern void updateMainMenuCursorPositionX();
extern void updateContinueMenuCursorPositionX();
extern void updatePlayMenuCursorPositionX();
extern void updateOptionsMenuCursorPositionX();
extern void updateControlsMenuCursorPositionX();
extern void updateVideoMenuCursorPositionX();
extern void updateSoundMenuCursorPositionX();
extern void updateBackgroundMenuCursorPositionX();
extern void menuHandleBackButton(Uint8);
extern void menuHandleBackButtonWithSettings(Uint8);
extern void menuResetCursorPositions(Uint8);
extern void updateMenuCursorPositionY(Sint8);
extern void menuHandleMenuButton();
extern void menuHandleVertCursorMovement(Sint8 &, Uint8, Uint8);
extern void controlsMenuHandleVertCursorMovement();
extern void updateControlsMenuCursorPositionY();
extern void menuHandleVertCursorMovementMouse(Sint8 &, TextObject, Sint8);
extern bool mouseIsInRect(TextRect);
extern void menuHandleVertCursorMovementMouseWithSetting(Sint8 &, TextObject, Sint16, Sint8);
extern void controlsMenuHandleVertCursorMovementMouse(TextObject, Sint8);
extern bool mouseIsInRectWithSetting(TextRect, Sint16);
extern void resetBGToDefault();
extern void setBGType();
extern void setBGScrollSpeed();
extern bool mouseMoved();
extern void updateMousePosViewportMouse();
extern void updateMousePosViewportTouch();

#endif