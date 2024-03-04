#include "window.h"
#include "shared.h"
#include "general.h"

void snapWindow_x(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII)) && !defined(SDL1)
	if (isWindowed) {
		d = ((float)SDL_GetWindowSurface(window)->w / size);
		if ((d - floor(d)) >= pow(1 - range, floor(d))) {
			if ((size * ceil(d)) < DM.w) {
				SDL_SetWindowSize(window, size * (short)(ceil(d)), SDL_GetWindowSurface(window)->h);
			}
		} else if ((d - floor(d)) < 1 - pow(1 - range, (short)(floor(d))) && (SDL_GetWindowSurface(window)->w % size != 0)) {
			SDL_SetWindowSize(window, size * (short)floor(d), SDL_GetWindowSurface(window)->h);
		}
	}
#endif
}

void snapWindow_y(double range, Uint16 size) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII)) && !defined(SDL1)
	if (isWindowed) {
		d = ((float)SDL_GetWindowSurface(window)->h / size);
		if ((d - floor(d)) >= pow(1 - range, (short)(floor(d)))) {
			if ((size * ceil(d)) < DM.h) {
				SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)ceil(d));
			}
		} else if ((d - floor(d)) < 1 - pow(1 - range, (short)(floor(d))) && (SDL_GetWindowSurface(window)->h % size != 0)) {
			SDL_SetWindowSize(window, SDL_GetWindowSurface(window)->w, size * (short)floor(d));
		}
	}
#endif
}