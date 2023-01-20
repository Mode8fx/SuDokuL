#include "include.h"
#include "general.h"
#include "sudokuGen.h"

#ifndef PUZZLEBANK_H
#define PUZZLEBANK_H

extern const Sint8 puzzles_easy[1000][2][81];
extern const Sint8 puzzles_normal[1000][2][81];
extern const Sint8 puzzles_hard[1000][2][81];
extern const Sint8 puzzles_veryHard[1000][2][81];
//int generatePuzzleBank();
void setPremadePuzzle(Uint8, Uint16);

//#define GENERATE_PUZZLES(arrayName, numPuzzles, minDiff, maxDiff) {                     \
//    puzzleFile << "const Sint8 " << arrayName << "[" << numPuzzles << "][2][81] = {\n"; \
//    for (i = 0; i < numPuzzles; i++) {                                                  \
//        puzzleFile << "\t{\n";                                                          \
//        puzzleFile << "\t\t{ ";                                                         \
//        generateGridAndSolution(minDiff, maxDiff);                                      \
//        for (j = 0; j < 80; j++) {                                                      \
//            puzzleFile << int(solutionGrid[j]) << ", ";                                 \
//        }                                                                               \
//        puzzleFile << int(solutionGrid[80]) << " }, \n";                                \
//        puzzleFile << "\t\t{ ";                                                         \
//        for (j = 0; j < 80; j++) {                                                      \
//            puzzleFile << int(originalGrid[j]) << ", ";                                 \
//        }                                                                               \
//        puzzleFile << int(originalGrid[80]) << " }\n";                                  \
//        puzzleFile << "\t}, \n";                                                        \
//        PRINT(arrayName << " " << (i + 1));                                             \
//    }                                                                                   \
//    puzzleFile << "};\n\n";                                                             \
//}

#endif