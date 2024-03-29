#include "config.h"
#include "shared.h"
#include "window.h"
#include "general.h"
#include "menu_logic.h"
#include "game_logic.h"

#if defined(WII)
Uint32 wii_keysDown;
Uint32 wii_keysUp;
#elif defined(GAMECUBE)
Uint32 gc_keysDown;
Uint32 gc_keysUp;
#endif

bool keyPressed(Uint32 key) {
	return (keyInputs & key);
}

bool buttonHeld(Uint32 button) {
	return (heldButtons & button);
}

void resetCheatCounters() {
	cheat1Counter = 0;
	cheat2Counter = 0;
	songChangeCounter = 0;
}

#if (defined(PSP) || defined(SDL1)) && !defined(FUNKEY)
inline static void handleAnalogInput_SDL1() {
	if (event.jaxis.which == 0) {
		if (event.jaxis.axis == 0) {
			controllerAxis_leftStickX = event.jaxis.value;
			if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
				controllerAxis_leftStickX = 0;
			}
		}
		if (event.jaxis.axis == 1) {
			controllerAxis_leftStickY = event.jaxis.value;
			if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
				controllerAxis_leftStickY = 0;
			}
		}
	}
}

inline static void handleButtonDown_SDL1() {
	if (event.jbutton.which == 0) {
		if (event.jbutton.button == 8) { // Up
			dirInputs |= UP_PRESSED;
			return;
		}
		if (event.jbutton.button == 6) { // Down
			dirInputs |= DOWN_PRESSED;
			return;
		}
		if (event.jbutton.button == 7) { // Left
			dirInputs |= LEFT_PRESSED;
			return;
		}
		if (event.jbutton.button == 9) { // Right
			dirInputs |= RIGHT_PRESSED;
			return;
		}
		if (event.jbutton.button == 1) { // O
			if (!controlSettings.swapConfirmAndBack) {
				keyInputs |= INPUT_CONFIRM;
				resetCheatCounters();
			}
			else {
				keyInputs |= INPUT_BACK;
			}
			return;
		}
		if (event.jbutton.button == 2) { // X
			if (!controlSettings.swapConfirmAndBack) {
				keyInputs |= INPUT_BACK;
			}
			else {
				keyInputs |= INPUT_CONFIRM;
				resetCheatCounters();
			}
			return;
		}
		if (event.jbutton.button == 11) { // Start
			keyInputs |= INPUT_START;
			resetCheatCounters();
			return;
		}
		if (event.jbutton.button == 10) { // Select
			keyInputs |= INPUT_SELECT;
			return;
		}
#if !defined(SDL1)
		if (event.jbutton.button == 0 || event.cbutton.button == 3) { // Triangle || Square
#else
		if (event.jbutton.button == 0) {
#endif
			keyInputs |= INPUT_SWAP;
			return;
		}
		if (event.jbutton.button == 4) { // L
			keyInputs |= INPUT_PREV_TRACK;
			resetCheatCounters();
			return;
		}
		if (event.jbutton.button == 5) { // R
			keyInputs |= INPUT_NEXT_TRACK;
			resetCheatCounters();
			return;
		}
	}
}

inline static void handleButtonUp_SDL1() {
	if (event.jbutton.button == 8) { // Up
		dirInputs |= UP_DEPRESSED;
		return;
	}
	if (event.jbutton.button == 6) { // Down
		dirInputs |= DOWN_DEPRESSED;
		return;
	}
	if (event.jbutton.button == 7) { // Left
		dirInputs |= LEFT_DEPRESSED;
		return;
	}
	if (event.jbutton.button == 9) { // Right
		dirInputs |= RIGHT_DEPRESSED;
		return;
	}
}
#elif defined(WII)
inline static void wii_mapWiimoteDir(Uint32 wiimoteInput, Uint32 output) {
	if (wii_keysDown & wiimoteInput) {
		dirInputs |= output;
	} else if (wii_keysUp & wiimoteInput) {
		dirInputs |= output << 1;
	}
}

inline static void wii_mapWiimoteButton(Uint32 wiimoteInput, Uint32 output) {
	if (wii_keysDown & wiimoteInput) {
		keyInputs |= output;
	} else if (wii_keysUp & wiimoteInput) {
		keyInputs &= ~output;
	}
}

inline static void wii_mapWiiCCDir(Uint32 ccInput, Uint32 output) {
	if (wii_keysDown & ccInput) {
		dirInputs |= output;
	} else if (wii_keysUp & ccInput) {
		dirInputs |= output << 1;
	}
}

inline static void wii_mapWiiCCButton(Uint32 ccInput, Uint32 output) {
	if (wii_keysDown & ccInput) {
		keyInputs |= output;
	} else if (wii_keysUp & ccInput) {
		keyInputs &= ~output;
	}
}

inline static void wii_mapGCDir(Uint32 gcInput, Uint32 output) {
	if (wii_keysDown & gcInput) {
		dirInputs |= output;
	} else if (wii_keysUp & gcInput) {
		dirInputs |= output << 1;
	}
}

inline static void wii_mapGCButton(Uint32 gcInput, Uint32 output) {
	if (wii_keysDown & gcInput) {
		keyInputs |= output;
	} else if (wii_keysUp & gcInput) {
		keyInputs &= ~output;
	}
}

inline static void handleWiimoteButtons() {
	switch (controlSettings.wiimoteScheme) {
		case 0:
			wii_mapWiimoteDir(WPAD_BUTTON_UP, LEFT_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_DOWN, RIGHT_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_LEFT, DOWN_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_RIGHT, UP_PRESSED);
			wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_SWAP);
			wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_SWAP);
			if (controlSettings.swapConfirmAndBack) {
				wii_mapWiimoteButton(WPAD_BUTTON_2, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_1, INPUT_BACK);
			} else {
				wii_mapWiimoteButton(WPAD_BUTTON_2, INPUT_BACK);
				wii_mapWiimoteButton(WPAD_BUTTON_1, INPUT_CONFIRM);
			}
			wii_mapWiimoteButton(WPAD_BUTTON_PLUS, INPUT_NEXT_TRACK);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SELECT);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SWAP);
			wii_mapWiimoteButton(WPAD_BUTTON_HOME, INPUT_START);
			break;
		case 1:
			wii_mapWiimoteDir(WPAD_BUTTON_UP, LEFT_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_DOWN, RIGHT_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_LEFT, DOWN_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_RIGHT, UP_PRESSED);
			if (controlSettings.swapConfirmAndBack) {
				if (programState != 9)
					wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_CONFIRM_ALT);
				wii_mapWiimoteButton(WPAD_BUTTON_2, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_BACK);
				wii_mapWiimoteButton(WPAD_BUTTON_1, INPUT_BACK);
			} else {
				wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_BACK);
				wii_mapWiimoteButton(WPAD_BUTTON_2, INPUT_BACK);
				if (programState != 9)
					wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_CONFIRM_ALT);
				wii_mapWiimoteButton(WPAD_BUTTON_1, INPUT_CONFIRM);
			}
			wii_mapWiimoteButton(WPAD_BUTTON_PLUS, INPUT_NEXT_TRACK);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SELECT);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SWAP);
			wii_mapWiimoteButton(WPAD_BUTTON_HOME, INPUT_START);
			break;
		case 2:
			wii_mapWiimoteDir(WPAD_BUTTON_UP, UP_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_DOWN, DOWN_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_LEFT, LEFT_PRESSED);
			wii_mapWiimoteDir(WPAD_BUTTON_RIGHT, RIGHT_PRESSED);
			if (controlSettings.swapConfirmAndBack) {
				if (programState != 9)
					wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_CONFIRM_ALT);
				wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_BACK);
			} else {
				wii_mapWiimoteButton(WPAD_BUTTON_A, INPUT_BACK);
				if (programState != 9)
					wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_CONFIRM);
				wii_mapWiimoteButton(WPAD_BUTTON_B, INPUT_CONFIRM_ALT);
			}
			wii_mapWiimoteButton(WPAD_BUTTON_1, INPUT_NEXT_TRACK);
			wii_mapWiimoteButton(WPAD_BUTTON_2, INPUT_PREV_TRACK);
			wii_mapWiimoteButton(WPAD_BUTTON_PLUS, INPUT_SWAP);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SELECT);
			wii_mapWiimoteButton(WPAD_BUTTON_MINUS, INPUT_SWAP);
			wii_mapWiimoteButton(WPAD_BUTTON_HOME, INPUT_START);
			break;
	}
	if (programState == 0)
		wii_mapWiimoteButton(WPAD_BUTTON_PLUS, INPUT_START);
}

inline static void handleWiiCCButtons() {
	wii_mapWiiCCDir(WPAD_CLASSIC_BUTTON_LEFT, LEFT_PRESSED);
	wii_mapWiiCCDir(WPAD_CLASSIC_BUTTON_RIGHT, RIGHT_PRESSED);
	wii_mapWiiCCDir(WPAD_CLASSIC_BUTTON_DOWN, DOWN_PRESSED);
	wii_mapWiiCCDir(WPAD_CLASSIC_BUTTON_UP, UP_PRESSED);
	if (controlSettings.swapConfirmAndBack) {
		wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_A, INPUT_CONFIRM);
		wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_B, INPUT_BACK);
	} else {
		wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_A, INPUT_BACK);
		wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_B, INPUT_CONFIRM);
	}
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_X, INPUT_SWAP);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_Y, INPUT_SWAP);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_FULL_L, INPUT_PREV_TRACK);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_FULL_R, INPUT_NEXT_TRACK);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_PLUS, INPUT_START);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_MINUS, INPUT_SELECT);
	wii_mapWiiCCButton(WPAD_CLASSIC_BUTTON_HOME, INPUT_START);
}

inline static void handleWiiGCButtons() {
	wii_mapGCDir(PAD_BUTTON_UP, UP_PRESSED);
	wii_mapGCDir(PAD_BUTTON_DOWN, DOWN_PRESSED);
	wii_mapGCDir(PAD_BUTTON_LEFT, LEFT_PRESSED);
	wii_mapGCDir(PAD_BUTTON_RIGHT, RIGHT_PRESSED);
	if (controlSettings.swapConfirmAndBack) {
		wii_mapGCButton(PAD_BUTTON_A, INPUT_CONFIRM);
		wii_mapGCButton(PAD_BUTTON_B, INPUT_BACK);
	} else {
		wii_mapGCButton(PAD_BUTTON_A, INPUT_BACK);
		wii_mapGCButton(PAD_BUTTON_B, INPUT_CONFIRM);
	}
	wii_mapGCButton(PAD_BUTTON_X, INPUT_SWAP);
	wii_mapGCButton(PAD_BUTTON_Y, INPUT_SWAP);
	wii_mapGCButton(PAD_TRIGGER_L, INPUT_PREV_TRACK);
	wii_mapGCButton(PAD_TRIGGER_R, INPUT_NEXT_TRACK);
	wii_mapGCButton(PAD_TRIGGER_Z, INPUT_SELECT);
	wii_mapGCButton(PAD_BUTTON_START, INPUT_START);
}
#elif defined(GAMECUBE)
inline static void gc_mapDir(Uint32 gcInput, Uint32 output) {
	if (gc_keysDown & gcInput) {
		dirInputs |= output;
	} else if (gc_keysUp & gcInput) {
		dirInputs |= output << 1;
	}
}

inline static void gc_mapButton(Uint32 gcInput, Uint32 output) {
	if (gc_keysDown & gcInput) {
		keyInputs |= output;
	} else if (gc_keysUp & gcInput) {
		keyInputs &= ~output;
	}
}

inline static void handleGCButtons() {
	gc_mapDir(PAD_BUTTON_UP, UP_PRESSED);
	gc_mapDir(PAD_BUTTON_DOWN, DOWN_PRESSED);
	gc_mapDir(PAD_BUTTON_LEFT, LEFT_PRESSED);
	gc_mapDir(PAD_BUTTON_RIGHT, RIGHT_PRESSED);
	if (controlSettings.swapConfirmAndBack) {
		gc_mapButton(PAD_BUTTON_A, INPUT_CONFIRM);
		gc_mapButton(PAD_BUTTON_B, INPUT_BACK);
	} else {
		gc_mapButton(PAD_BUTTON_A, INPUT_BACK);
		gc_mapButton(PAD_BUTTON_B, INPUT_CONFIRM);
	}
	gc_mapButton(PAD_BUTTON_X, INPUT_SWAP);
	gc_mapButton(PAD_BUTTON_Y, INPUT_SWAP);
	gc_mapButton(PAD_TRIGGER_L, INPUT_PREV_TRACK);
	gc_mapButton(PAD_TRIGGER_R, INPUT_NEXT_TRACK);
	gc_mapButton(PAD_TRIGGER_Z, INPUT_SELECT);
	gc_mapButton(PAD_BUTTON_START, INPUT_START);
	controllerAxis_leftStickX = PAD_StickX(0) * 256;
	controllerAxis_leftStickY = PAD_StickY(0) * -256;
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
}
#elif defined(FUNKEY)
inline static void handleKeyboardKeys_FunKey() {
	if (event.key.keysym.sym == 117) {
		keyInputs |= INPUT_UP;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 100) {
		keyInputs |= INPUT_DOWN;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 108) {
		keyInputs |= INPUT_LEFT;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 114) {
		keyInputs |= INPUT_RIGHT;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 97) {
		keyInputs |= INPUT_CONFIRM;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 98) {
		keyInputs |= INPUT_BACK;
		cheat1Counter = 0;
		songChangeCounter = 0;
		return;
	}
	if (event.key.keysym.sym == 115) {
		keyInputs |= INPUT_START;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 107) {
		keyInputs |= INPUT_SELECT;
		return;
	}
	if (event.key.keysym.sym == 120 || event.key.keysym.sym == 121) {
		keyInputs |= INPUT_SWAP;
		return;
	}
	if (event.key.keysym.sym == 109) {
		keyInputs |= INPUT_PREV_TRACK;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == 110) {
		keyInputs |= INPUT_NEXT_TRACK;
		resetCheatCounters();
		return;
	}
}
#else
inline static void handleAnalogInput_SDL2() {
	controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
}

inline static void handleButtonDown_SDL2() {
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
		dirInputs |= UP_PRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
		dirInputs |= DOWN_PRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
		dirInputs |= LEFT_PRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
		dirInputs |= RIGHT_PRESSED;
		return;
	}
#if defined(SWITCH)
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#else
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#endif
		if (!controlSettings.swapConfirmAndBack) {
			keyInputs |= INPUT_CONFIRM;
			resetCheatCounters();
		}
		else {
			keyInputs |= INPUT_BACK;
		}
		return;
	}
#if defined(SWITCH)
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B) {
#else
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
#endif
		if (!controlSettings.swapConfirmAndBack) {
			keyInputs |= INPUT_BACK;
		}
		else {
			keyInputs |= INPUT_CONFIRM;
			resetCheatCounters();
		}
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
		keyInputs |= INPUT_START;
		resetCheatCounters();
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) {
		keyInputs |= INPUT_SELECT;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X || event.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
		keyInputs |= INPUT_SWAP;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
		keyInputs |= INPUT_PREV_TRACK;
		resetCheatCounters();
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
		keyInputs |= INPUT_NEXT_TRACK;
		resetCheatCounters();
		return;
	}
}

inline static void handleButtonUp_SDL2() {
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) {
		dirInputs |= UP_DEPRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) {
		dirInputs |= DOWN_DEPRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
		dirInputs |= LEFT_DEPRESSED;
		return;
	}
	if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
		dirInputs |= RIGHT_DEPRESSED;
		return;
	}
}
#endif

#if defined(SDL1)
#define SDLK_RETURN2 SDLK_RETURN
#define SDLK_KP_0 SDLK_KP0
#define SDLK_KP_1 SDLK_KP1
#define SDLK_KP_2 SDLK_KP2
#define SDLK_KP_3 SDLK_KP3
#define SDLK_KP_4 SDLK_KP4
#define SDLK_KP_5 SDLK_KP5
#define SDLK_KP_6 SDLK_KP6
#define SDLK_KP_7 SDLK_KP7
#define SDLK_KP_8 SDLK_KP8
#define SDLK_KP_9 SDLK_KP9
#endif

inline static void handleKeyboardKeys() {
	if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) {
		keyInputs |= INPUT_UP;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
		keyInputs |= INPUT_DOWN;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a) {
		keyInputs |= INPUT_LEFT;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
		keyInputs |= INPUT_RIGHT;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_RETURN2 || event.key.keysym.sym == SDLK_KP_ENTER) {
		keyInputs |= INPUT_CONFIRM;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_BACKSPACE) {
		keyInputs |= INPUT_BACK;
		cheat1Counter = 0;
		songChangeCounter = 0;
		return;
	}
	if (event.key.keysym.sym == SDLK_ESCAPE) {
		keyInputs |= INPUT_START;
		keyInputs |= INPUT_BACK;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_q) {
		keyInputs |= INPUT_SELECT;
		return;
	}
	if (event.key.keysym.sym == SDLK_PERIOD || event.key.keysym.sym == SDLK_KP_PERIOD) {
		keyInputs |= INPUT_SWAP;
		return;
	}
	if (event.key.keysym.sym == SDLK_MINUS) {
		keyInputs |= INPUT_PREV_TRACK;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_EQUALS) {
		keyInputs |= INPUT_NEXT_TRACK;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_KP_0) {
		keyInputs |= INPUT_NUM_0;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_1) {
		keyInputs |= INPUT_NUM_1;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_2) {
		keyInputs |= INPUT_NUM_2;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP_3) {
		keyInputs |= INPUT_NUM_3;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP_4) {
		keyInputs |= INPUT_NUM_4;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP_5) {
		keyInputs |= INPUT_NUM_5;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_KP_6) {
		keyInputs |= INPUT_NUM_6;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_KP_7) {
		keyInputs |= INPUT_NUM_7;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_KP_8) {
		keyInputs |= INPUT_NUM_8;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_9 || event.key.keysym.sym == SDLK_KP_9) {
		keyInputs |= INPUT_NUM_9;
		resetCheatCounters();
		return;
	}
	if (event.key.keysym.sym == SDLK_f) {
		keyInputs |= INPUT_FULLSCREEN;
		return;
	}
#if defined(ANDROID)
	if (event.key.keysym.sym == SDLK_AC_BACK) {
		keyInputs |= INPUT_BACK;
		keyInputs |= INPUT_START;
		keyInputs |= INPUT_SELECT;
		return;
	}
#endif
}

inline static void dirHandler(Uint8 pressedVal, Uint8 depressedVal, Uint8 inputVal) {
	if (dirInputs & pressedVal) {
		keyInputs |= inputVal;
		heldButtons |= inputVal;
		resetCheatCounters();
	} else if (dirInputs & depressedVal) {
		heldButtons &= ~inputVal;
	}
}

inline static void handleInputPressDepress() {
	if ((controllerAxis_leftStickX < 0) && !(controllerAxis_leftStickX_last < 0)) {
		dirInputs |= LEFT_PRESSED;
	} else if (!(controllerAxis_leftStickX < 0) && (controllerAxis_leftStickX_last < 0)) { // a little redundant, but easier to read
		dirInputs |= LEFT_DEPRESSED;
	}
	if ((controllerAxis_leftStickX > 0) && !(controllerAxis_leftStickX_last > 0)) {
		dirInputs |= RIGHT_PRESSED;
	} else if (!(controllerAxis_leftStickX > 0) && (controllerAxis_leftStickX_last > 0)) {
		dirInputs |= RIGHT_DEPRESSED;
	}
	if ((controllerAxis_leftStickY < 0) && !(controllerAxis_leftStickY_last < 0)) {
		dirInputs |= UP_PRESSED;
	} else if (!(controllerAxis_leftStickY < 0) && (controllerAxis_leftStickY_last < 0)) {
		dirInputs |= UP_DEPRESSED;
	}
	if ((controllerAxis_leftStickY > 0) && !(controllerAxis_leftStickY_last > 0)) {
		dirInputs |= DOWN_PRESSED;
	} else if (!(controllerAxis_leftStickY > 0) && (controllerAxis_leftStickY_last > 0)) {
		dirInputs |= DOWN_DEPRESSED;
	}
	dirHandler(UP_PRESSED, UP_DEPRESSED, INPUT_UP);
	dirHandler(DOWN_PRESSED, DOWN_DEPRESSED, INPUT_DOWN);
	dirHandler(LEFT_PRESSED, LEFT_DEPRESSED, INPUT_LEFT);
	dirHandler(RIGHT_PRESSED, RIGHT_DEPRESSED, INPUT_RIGHT);
	if (timer_buttonHold > 0.5) {
		timer_buttonHold_repeater += deltaTime;
		if (timer_buttonHold_repeater >= 0.033) {
			if (buttonHeld(INPUT_UP)) {
				keyInputs |= INPUT_UP;
			}
			if (buttonHeld(INPUT_DOWN)) {
				keyInputs |= INPUT_DOWN;
			}
			if (buttonHeld(INPUT_LEFT)) {
				keyInputs |= INPUT_LEFT;
			}
			if (buttonHeld(INPUT_RIGHT)) {
				keyInputs |= INPUT_RIGHT;
			}
			timer_buttonHold_repeater -= 0.033;
		}
	}
}

void handlePlayerInput() {
	keyInputs = 0;
	dirInputs = 0;
#if defined(PSP)
	/* Handle Key Presses (PSP) */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			/* Handle Analog Input (PSP) */
			case SDL_JOYAXISMOTION:
				handleAnalogInput_SDL1();
				break;
			/* Handle Button Input (PSP) */
			case SDL_JOYBUTTONDOWN:
				handleButtonDown_SDL1();
				break;
			case SDL_JOYBUTTONUP:
				handleButtonUp_SDL1();
				break;
			default:
				break;
		}
	}
#elif defined(GAMECUBE)
	PAD_ScanPads();
	gc_keysDown = PAD_ButtonsDown(0);
	gc_keysUp = PAD_ButtonsUp(0);
	handleGCButtons();
#elif defined(FUNKEY)
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
				/* Handle Button Input (FunKey) */
			case SDL_KEYDOWN:
				handleKeyboardKeys_FunKey();
				break;
			default:
				break;
		}
	}
#elif defined(SDL1)
	/* Handle Key Presses (SDL1) */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			/* Handle Mouse Input (PC) */
#if !defined(THREEDS)
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
				updateMousePosViewportMouse();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
					updateMousePosViewportMouse();
					keyInputs |= INPUT_CONFIRM_ALT;
					break;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) {
					keyInputs |= INPUT_BACK;
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				justClickedInMiniGrid = false;
				break;
			/* Handle Keyboard Input (PC) */
			case SDL_KEYDOWN:
				handleKeyboardKeys();
				break;
#endif
			/* Handle Analog Input (SDL1) */
			case SDL_JOYAXISMOTION:
				handleAnalogInput_SDL1();
				break;
			/* Handle Button Input (SDL1) */
			case SDL_JOYBUTTONDOWN:
				handleButtonDown_SDL1();
				break;
			case SDL_JOYBUTTONUP:
				handleButtonUp_SDL1();
				break;
			default:
				break;
		}
	}
#elif defined(WII)
	WPAD_ScanPads();
	wii_keysDown = WPAD_ButtonsDown(0);
	wii_keysUp = WPAD_ButtonsUp(0);
	handleWiimoteButtons();
	handleWiiCCButtons();

	PAD_ScanPads();
	wii_keysDown = PAD_ButtonsDown(0);
	wii_keysUp = PAD_ButtonsUp(0);
	handleWiiGCButtons();

	controllerAxis_leftStickX = PAD_StickX(0) * 256;
	controllerAxis_leftStickY = PAD_StickY(0) * -256;
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
	/* Handle Mouse Input (Wii) */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
				updateMousePosViewportMouse();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (keyPressed(INPUT_CONFIRM_ALT)) {
					SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
					updateMousePosViewportMouse();
					break;
				}
			case SDL_MOUSEBUTTONUP:
				if (!keyPressed(INPUT_CONFIRM_ALT)) {
					justClickedInMiniGrid = false;
				}
				break;
		}
	}
#else
	/* Handle Analog Input (SDL2) */
	handleAnalogInput_SDL2();
	/* Handle Key Presses and Mouse Input (SDL2) */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(THREEDS))
			/* Handle Mouse Input (PC) */
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
				updateMousePosViewportMouse();
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_GetMouseState(&mouseInput_x, &mouseInput_y);
					updateMousePosViewportMouse();
					keyInputs |= INPUT_CONFIRM_ALT;
					break;
				}
				if (event.button.button == SDL_BUTTON_RIGHT) {
					keyInputs |= INPUT_BACK;
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				justClickedInMiniGrid = false;
				break;
			/* Handle Window Resizing (PC) */
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
					windowSizeChanged = true;
				}
				break;
#endif
			/* Handle Keyboard Input (PC) */
			case SDL_KEYDOWN:
				handleKeyboardKeys();
				break;
			/* Handle Button Input (SDL2) */
			case SDL_CONTROLLERBUTTONDOWN:
				handleButtonDown_SDL2();
				break;
			case SDL_CONTROLLERBUTTONUP:
				handleButtonUp_SDL2();
				break;
			/* Handle Touch Input (SDL2) */
			case SDL_FINGERDOWN:
				if (controlSettings.enableTouchscreen) {
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					updateMousePosViewportTouch();
					keyInputs |= INPUT_CONFIRM_ALT;
				}
				break;
			case SDL_FINGERMOTION:
				if (controlSettings.enableTouchscreen) {
					mouseInput_x = (Sint32)(event.tfinger.x * gameWidth);
					mouseInput_y = (Sint32)(event.tfinger.y * gameHeight);
					updateMousePosViewportTouch();
				}
				break;
			case SDL_FINGERUP:
				if (controlSettings.enableTouchscreen) {
					justClickedInMiniGrid = false;
				}
				break;
			default:
				break;
		}
	}
#endif
	/* Handle Press/Depress/Hold */
	handleInputPressDepress();
}