#include "include.h"

#ifndef GENERAL_H
#define GENERAL_H

/* Program State */
extern Uint8 programState;
extern bool changedProgramState;

constexpr auto PI = 3.14159265;

#define COPY_GRID(dest, source) \
    (memcpy(dest, source, 81 * sizeof(char)))

#define RANDINT(min, max) \
    (rand() % ((max) - (min) + 1) + min)

#define LEN(arr) \
    (sizeof(arr) / sizeof(arr[0]))

#define ZERO_OUT_ARRAY(arr) \
    (memset(arr, 0, sizeof(arr)))

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII))
#define PRINT(str) \
    cout << str << endl
#else
#define PRINT(str)
#endif

#define SIN_WAVE(timeVal, period, amplitude) \
    (sin((timeVal) * PI / (period)) * (amplitude))

#define COS_WAVE(timeVal, period, amplitude) \
    (cos((timeVal) * PI / (period)) * (amplitude))

#define MOVE_FAST_THEN_DECELERATE(dist, numSeconds, timeVal) \
    (0.5 * pow(((((numSeconds) - (timeVal)) / (numSeconds)) * sqrt(2 * (dist))), 2))

/* General-use Variables */
extern Sint8 i, j, k;
extern Sint8 char_x1, char_y1, char_x2, char_y2;
extern Sint32 int_i;
extern Uint32 uint_i;
extern double d;

/* Other */
extern bool isRunning;
extern bool wentPastTitleScreen;

#endif