#ifndef CONFIG_H
#define CONFIG_H

#define INPUT_UP          (1 << 0)
#define INPUT_DOWN        (1 << 1)
#define INPUT_LEFT        (1 << 2)
#define INPUT_RIGHT       (1 << 3)
#define INPUT_CONFIRM     (1 << 4)  // A Button
#define INPUT_BACK        (1 << 5)  // B Button
#define INPUT_START       (1 << 6)  // Pause
#define INPUT_SELECT      (1 << 7)  // Back to Menu
#define INPUT_SWAP        (1 << 8)  // X/Y Button; swap between Large/Mini grid
#define INPUT_PREV_TRACK  (1 << 9)  // L Button; previous song
#define INPUT_NEXT_TRACK  (1 << 10) // R Button; previous song
#define INPUT_CONFIRM_ALT (1 << 11) // Click; functions differently from normal Confirm when using mouse controls
#define INPUT_NUM_0       (1 << 20)
#define INPUT_NUM_1       (1 << 21)
#define INPUT_NUM_2       (1 << 22)
#define INPUT_NUM_3       (1 << 23)
#define INPUT_NUM_4       (1 << 24)
#define INPUT_NUM_5       (1 << 25)
#define INPUT_NUM_6       (1 << 26)
#define INPUT_NUM_7       (1 << 27)
#define INPUT_NUM_8       (1 << 28)
#define INPUT_NUM_9       (1 << 29)
#define INPUT_FULLSCREEN  (1 << 30)

#define STICK_DEADZONE  13107 // (32767 * 0.4)

#define LEFT_PRESSED    (1 << 0)
#define LEFT_DEPRESSED  (1 << 1)
#define RIGHT_PRESSED   (1 << 2)
#define RIGHT_DEPRESSED (1 << 3)
#define UP_PRESSED      (1 << 4)
#define UP_DEPRESSED    (1 << 5)
#define DOWN_PRESSED    (1 << 6)
#define DOWN_DEPRESSED  (1 << 7)

#define DIR_HANDLER(pressedVal, depressedVal, inputVal)  \
	if (dirInputs & pressedVal) {                        \
		keyInputs |= inputVal;                           \
		heldButtons |= inputVal;                         \
		cheatCounter = 0;                                \
	} else if (dirInputs & depressedVal) {               \
		heldButtons &= ~inputVal;                        \
	}

#endif