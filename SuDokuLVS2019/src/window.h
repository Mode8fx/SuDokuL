#include "include.h"

#ifndef WINDOW_H
#define WINDOW_H

/* SDL Window */
#if !defined(SDL1)
extern SDL_Window *window;
extern SDL_Renderer *renderer;
#else
extern SDL_Surface *windowScreen;
#endif
extern SDL_Event event;

/* SDL Rectangles */
extern SDL_Rect topRect;
extern SDL_Rect bottomRect;
extern SDL_Rect leftRect;
extern SDL_Rect rightRect;

/* Window */
extern float screenScale;
extern bool isWindowed;
extern bool isIntegerScale;
extern bool windowSizeChanged;

void snapWindow_x(double, Uint16);
void snapWindow_y(double, Uint16);

#endif