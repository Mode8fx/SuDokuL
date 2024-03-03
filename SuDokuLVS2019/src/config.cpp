#include "config.h"

bool keyPressed(Uint32 key) {
	return (keyInputs & key);
}

bool buttonHeld(Uint32 button) {
	return (heldButtons & button);
}

void dirHandler(Uint8 pressedVal, Uint8 depressedVal, Uint8 inputVal) {
	if (dirInputs & pressedVal) {
		keyInputs |= inputVal;
		heldButtons |= inputVal;
		resetCheatCounters();
	} else if (dirInputs & depressedVal) {
		heldButtons &= ~inputVal;
	}
}

void resetCheatCounters() {
	cheat1Counter = 0;
	cheat2Counter = 0;
	songChangeCounter = 0;
}