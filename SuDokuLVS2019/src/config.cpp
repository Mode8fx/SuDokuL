#include "config.h"
#include "shared.h"
#include "window.h"
#include "general.h"
#include "menu_logic.h"
#include "game_logic.h"

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

static void handleAnalogInput_SDL2() {
	controllerAxis_leftStickX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	controllerAxis_leftStickY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
	if ((controllerAxis_leftStickX > -STICK_DEADZONE) && (controllerAxis_leftStickX < STICK_DEADZONE)) {
		controllerAxis_leftStickX = 0;
	}
	if ((controllerAxis_leftStickY > -STICK_DEADZONE) && (controllerAxis_leftStickY < STICK_DEADZONE)) {
		controllerAxis_leftStickY = 0;
	}
}

static void handleAnalogInput_SDL1() {
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

static void handleKeyboardKeys() {
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
		resetCheatCounters();
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

static void handleButtonDown_SDL2() {
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
		resetCheatCounters();
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

static void handleButtonUp_SDL2() {
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

static void handleButtonDown_SDL1() {
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
			resetCheatCounters();
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

static void handleButtonUp_SDL1() {
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

static void dirHandler(Uint8 pressedVal, Uint8 depressedVal, Uint8 inputVal) {
	if (dirInputs & pressedVal) {
		keyInputs |= inputVal;
		heldButtons |= inputVal;
		resetCheatCounters();
	} else if (dirInputs & depressedVal) {
		heldButtons &= ~inputVal;
	}
}

static void handleInputPressDepress() {
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
#if (defined(PSP) || defined(SDL1))
		/* Handle Key Presses (PSP and SDL1) */
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				/* Handle Analog Input (PSP and SDL1) */
				case SDL_JOYAXISMOTION:
					handleAnalogInput_SDL1();
					break;
				/* Handle Button Input (PSP and SDL1) */
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
#else
		/* Handle Analog Input (SDL2) */
		handleAnalogInput_SDL2();
		/* Handle Key Presses and Mouse Input (SDL2) */
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII))
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
				/* Handle Keyboard Input (SDL2) */
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