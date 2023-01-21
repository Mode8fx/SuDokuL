#include "include.h"

#ifndef WINDOW_H
#define WINDOW_H

/* SDL Window */
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;

/* SDL Rectangles */
extern SDL_Rect topRect;
extern SDL_Rect bottomRect;
extern SDL_Rect leftRect;
extern SDL_Rect rightRect;

/* Window */
extern double screenScale;
extern bool isWindowed;
extern bool isIntegerScale;

#endif