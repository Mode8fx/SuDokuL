#include "include.h"

#ifndef SUDOKUGEN_H
#define SUDOKUGEN_H

constexpr auto BACKTRACKING_VAL = 100;
constexpr auto TIMEOUT = 4000;

//void test_main();
//void test_PuzzleDifficulty();
extern Uint8 generateGridAndSolution(Uint16, Uint16, Uint32, Uint32);
extern Uint8 generateGrid_Backtracking();
extern Uint8 digHoles(Sint16, Sint16);
extern Sint16 solvePuzzle(Sint16);
extern Uint8 validateGridAndSolution();
extern void printBoard();
extern void printTempGrid();
extern void printSolutionGrid();
extern void initPossibleValsArrByIndex(Sint8);
extern void updateNumEmpty();
extern void checkForVictory();

extern Sint8 grid[81];
extern Sint8 solutionGrid[81];
extern Sint8 tempGrid[81];
#define originalGrid tempGrid
extern Sint16 miniGrid[81];
extern Uint8 numEmpty;

#endif