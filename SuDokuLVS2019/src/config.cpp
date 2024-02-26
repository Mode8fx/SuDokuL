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
		cheat1Counter = 0;
	} else if (dirInputs & depressedVal) {
		heldButtons &= ~inputVal;
	}
}