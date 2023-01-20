#include "include.h"
#include "config.h"

#ifndef MAIN_H
#define MAIN_H

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

#endif