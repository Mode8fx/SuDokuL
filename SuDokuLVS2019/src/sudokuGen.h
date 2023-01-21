#include "include.h"

#ifndef SUDOKUGEN_H
#define SUDOKUGEN_H

constexpr auto BACKTRACKING_VAL = 100;
constexpr auto TIMEOUT = 4000;
constexpr auto MAX_TIMEOUT = 8000;

//void test_main();
//void test_PuzzleDifficulty();
Uint8 generateGridAndSolution(Uint16, Uint16);
Uint8 generateGrid_Backtracking();
Uint8 digHoles(Sint16, Sint16);
Sint16 solvePuzzle(Sint16);
Uint8 validateGridAndSolution();
void printBoard();
void printTempGrid();
void printSolutionGrid();
void initPossibleValsArrByIndex(Sint8);
extern void updateNumEmpty();
extern void checkForVictory();

extern Sint8 grid[81];
extern Sint8 solutionGrid[81];
extern Sint8 tempGrid[81];
#define originalGrid tempGrid
extern Sint16 miniGrid[81];
extern Uint8 numEmpty;

#endif