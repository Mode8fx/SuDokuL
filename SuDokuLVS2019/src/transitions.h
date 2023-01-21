#include "include.h"

#ifndef MENU_TRANSITIONS_H
#define MENU_TRANSITIONS_H

extern void transitionGraphicsFromTitleScreen();
extern void transitionGraphicsToTitleScreen();
extern void transitionGraphicsFromMainMenu();
extern void transitionGraphicsToMainMenu(Sint8);
extern void transitionToStateWithTimer(double, Sint8, Uint8);

#endif