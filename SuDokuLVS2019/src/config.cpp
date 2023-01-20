#include "config.h"

void dirHandler(Uint8 pressedVal, Uint8 depressedVal, Uint8 inputVal) {
	if (dirInputs & pressedVal) {
		keyInputs |= inputVal;
		heldButtons |= inputVal;
		cheatCounter = 0;
	} else if (dirInputs & depressedVal) {
		heldButtons &= ~inputVal;
	}
}