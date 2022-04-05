#ifndef INCLUDE_H
#define INCLUDE_H

#if defined(PSP)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <mikmod.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif

#include <iostream>
// #include <stdio.h>
#include <string.h>
//#include <sstream>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//#include <chrono>
#include <algorithm>

#if defined(WII_U)
#include <unistd.h>
#include <whb/sdcard.h>
#elif defined(VITA)
#include <psp2/kernel/processmgr.h>
#elif defined(SWITCH)
#include <switch.h>
#elif defined(PSP)
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#endif

using namespace std;

#endif