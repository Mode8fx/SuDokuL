#ifndef INCLUDE_H
#define INCLUDE_H

#if defined(PSP) || defined(THREEDS)
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
#include <vector>

#if defined(WII_U)
#include <unistd.h>
#include <whb/sdcard.h>
#include <whb/proc.h>
#elif defined(VITA)
#include <psp2/kernel/processmgr.h>
#include <sys/stat.h>
#elif defined(SWITCH)
#include <switch.h>
#elif defined(PSP)
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#elif defined(WII)
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <dirent.h>
#include <fat.h>
#elif defined(GAMECUBE)
#include <gccore.h>
#include <ogc/pad.h>
#include <dirent.h>
#include <fat.h>
#elif defined(THREEDS)
#include <3ds.h>
#elif defined(LINUX)
#include <sys/stat.h>
#elif defined(EMSCRIPTEN)
#include <random>
#include <emscripten.h>
#endif

using namespace std;

#endif