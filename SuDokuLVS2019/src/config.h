#include "include.h"

#ifndef CONFIG_H
#define CONFIG_H

/* General Input */
extern Sint16 controllerAxis_leftStickX;
extern Sint16 controllerAxis_leftStickX_last;
extern Sint16 controllerAxis_leftStickY;
extern Sint16 controllerAxis_leftStickY_last;
extern Uint32 keyInputs;
extern Uint8  dirInputs;
extern Sint32 mouseInput_x;
extern Sint32 mouseInput_x_last;
extern Sint32 mouseInput_y;
extern Sint32 mouseInput_y_last;
extern Uint8 heldButtons;
extern Sint8 cheatCounter;

constexpr auto INPUT_UP          = (1 << 0);
constexpr auto INPUT_DOWN        = (1 << 1);
constexpr auto INPUT_LEFT        = (1 << 2);
constexpr auto INPUT_RIGHT       = (1 << 3);
constexpr auto INPUT_CONFIRM     = (1 << 4); // A Button
constexpr auto INPUT_BACK        = (1 << 5); // B Button
constexpr auto INPUT_START       = (1 << 6); // Pause
constexpr auto INPUT_SELECT      = (1 << 7); // Back to Menu
constexpr auto INPUT_SWAP        = (1 << 8); // X/Y Button; swap between Large/Mini grid
constexpr auto INPUT_PREV_TRACK  = (1 << 9); // L Button; previous song
constexpr auto INPUT_NEXT_TRACK  = (1 << 10); // R Button; previous song
constexpr auto INPUT_CONFIRM_ALT = (1 << 11); // Click; functions differently from normal Confirm when using mouse controls
constexpr auto INPUT_NUM_0       = (1 << 20);
constexpr auto INPUT_NUM_1       = (1 << 21);
constexpr auto INPUT_NUM_2       = (1 << 22);
constexpr auto INPUT_NUM_3       = (1 << 23);
constexpr auto INPUT_NUM_4       = (1 << 24);
constexpr auto INPUT_NUM_5       = (1 << 25);
constexpr auto INPUT_NUM_6       = (1 << 26);
constexpr auto INPUT_NUM_7       = (1 << 27);
constexpr auto INPUT_NUM_8       = (1 << 28);
constexpr auto INPUT_NUM_9       = (1 << 29);
constexpr auto INPUT_FULLSCREEN  = (1 << 30);

constexpr auto STICK_DEADZONE    = 13107;

constexpr auto LEFT_PRESSED      = (1 << 0);
constexpr auto LEFT_DEPRESSED    = (1 << 1);
constexpr auto RIGHT_PRESSED     = (1 << 2);
constexpr auto RIGHT_DEPRESSED   = (1 << 3);
constexpr auto UP_PRESSED        = (1 << 4);
constexpr auto UP_DEPRESSED      = (1 << 5);
constexpr auto DOWN_PRESSED      = (1 << 6);
constexpr auto DOWN_DEPRESSED    = (1 << 7);

extern void dirHandler(Uint8, Uint8, Uint8);

#endif