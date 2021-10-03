#include "include.h"

#ifndef SUDOKUGEN_H
#define SUDOKUGEN_H

#define BACKTRACKING_VAL 100
#define TIMEOUT 10000

void test_main();
void test_PuzzleDifficulty();
void generateGridAndSolution(Uint16, Uint16);
Uint8 generateGrid_Backtracking();
Uint8 digHoles(Sint16, Sint16);
Sint16 solvePuzzle(Sint16);
Uint8 validateGridAndSolution();
void printBoard();
void printTempGrid();
void printSolutionGrid();

extern Sint8 grid[81];
extern Sint8 solutionGrid[81];
extern Sint8 tempGrid[81];
#define originalGrid tempGrid
extern Sint16 miniGrid[81];
extern Uint8 numEmpty;

#define INIT_POSSIBLE_VALS_ARR_BY_INDEX(index) \
    possibleValsArr[0] = 1;                    \
    possibleValsArr[1] = 2;                    \
    possibleValsArr[2] = 3;                    \
    possibleValsArr[3] = 4;                    \
    possibleValsArr[4] = 5;                    \
    possibleValsArr[5] = 6;                    \
    possibleValsArr[6] = 7;                    \
    possibleValsArr[7] = 8;                    \
    possibleValsArr[8] = 9;                    \
    srand(seed);                               \
    srand(rand() + index);                     \
    std::random_shuffle(possibleValsArr, possibleValsArr + 9);

#define UPDATE_NUM_EMPTY() \
    numEmpty = std::count(grid, grid + 81, 0);

#define CHECK_FOR_VICTORY()                   \
    k = 1;                                    \
    if (numEmpty == 0) {                      \
        for (j = 0; j < 81; j++) {            \
            if (grid[j] != solutionGrid[j]) { \
                k = 0;                        \
                break;                        \
            }                                 \
        }                                     \
        if (k) {                              \
            programState = 11;                \
        }                                     \
    }

#endif