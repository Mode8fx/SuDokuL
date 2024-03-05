/* The algorithm used for generating a sudoku puzzle and measuring its
 * difficulty is adapted from:
 * https://dlbeer.co.nz/articles/sudoku.html
 */

#include "include.h"
#include "general.h"
#include "sudokuGen.h"

using namespace std;

/* BOARD BY INDEX
 * 
 *   0  1  2|  3  4  5|  6  7  8
 *   9 10 11| 12 13 14| 15 16 17
 *  18 19 20| 21 22 23| 24 25 26
 * -----------------------------
 *  27 28 29| 30 31 32| 33 34 35
 *  36 37 38| 39 40 41| 42 43 44
 *  45 46 47| 48 49 50| 51 52 53
 * -----------------------------
 *  54 55 56| 57 58 59| 60 61 62
 *  63 64 65| 66 67 68| 69 70 71
 *  72 73 74| 75 76 77| 78 79 80
 */

Sint8 relevantIndicesTable_All[81][20] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 18, 27, 36, 45, 54, 63, 72, 10, 11, 19, 20},
    {0, 2, 3, 4, 5, 6, 7, 8, 10, 19, 28, 37, 46, 55, 64, 73, 9, 11, 18, 20},
    {0, 1, 3, 4, 5, 6, 7, 8, 11, 20, 29, 38, 47, 56, 65, 74, 9, 10, 18, 19},
    {0, 1, 2, 4, 5, 6, 7, 8, 12, 21, 30, 39, 48, 57, 66, 75, 13, 14, 22, 23},
    {0, 1, 2, 3, 5, 6, 7, 8, 13, 22, 31, 40, 49, 58, 67, 76, 12, 14, 21, 23},
    {0, 1, 2, 3, 4, 6, 7, 8, 14, 23, 32, 41, 50, 59, 68, 77, 12, 13, 21, 22},
    {0, 1, 2, 3, 4, 5, 7, 8, 15, 24, 33, 42, 51, 60, 69, 78, 16, 17, 25, 26},
    {0, 1, 2, 3, 4, 5, 6, 8, 16, 25, 34, 43, 52, 61, 70, 79, 15, 17, 24, 26},
    {0, 1, 2, 3, 4, 5, 6, 7, 17, 26, 35, 44, 53, 62, 71, 80, 15, 16, 24, 25},
    {10, 11, 12, 13, 14, 15, 16, 17, 0, 18, 27, 36, 45, 54, 63, 72, 1, 2, 19, 20},
    {9, 11, 12, 13, 14, 15, 16, 17, 1, 19, 28, 37, 46, 55, 64, 73, 0, 2, 18, 20},
    {9, 10, 12, 13, 14, 15, 16, 17, 2, 20, 29, 38, 47, 56, 65, 74, 0, 1, 18, 19},
    {9, 10, 11, 13, 14, 15, 16, 17, 3, 21, 30, 39, 48, 57, 66, 75, 4, 5, 22, 23},
    {9, 10, 11, 12, 14, 15, 16, 17, 4, 22, 31, 40, 49, 58, 67, 76, 3, 5, 21, 23},
    {9, 10, 11, 12, 13, 15, 16, 17, 5, 23, 32, 41, 50, 59, 68, 77, 3, 4, 21, 22},
    {9, 10, 11, 12, 13, 14, 16, 17, 6, 24, 33, 42, 51, 60, 69, 78, 7, 8, 25, 26},
    {9, 10, 11, 12, 13, 14, 15, 17, 7, 25, 34, 43, 52, 61, 70, 79, 6, 8, 24, 26},
    {9, 10, 11, 12, 13, 14, 15, 16, 8, 26, 35, 44, 53, 62, 71, 80, 6, 7, 24, 25},
    {19, 20, 21, 22, 23, 24, 25, 26, 0, 9, 27, 36, 45, 54, 63, 72, 1, 2, 10, 11},
    {18, 20, 21, 22, 23, 24, 25, 26, 1, 10, 28, 37, 46, 55, 64, 73, 0, 2, 9, 11},
    {18, 19, 21, 22, 23, 24, 25, 26, 2, 11, 29, 38, 47, 56, 65, 74, 0, 1, 9, 10},
    {18, 19, 20, 22, 23, 24, 25, 26, 3, 12, 30, 39, 48, 57, 66, 75, 4, 5, 13, 14},
    {18, 19, 20, 21, 23, 24, 25, 26, 4, 13, 31, 40, 49, 58, 67, 76, 3, 5, 12, 14},
    {18, 19, 20, 21, 22, 24, 25, 26, 5, 14, 32, 41, 50, 59, 68, 77, 3, 4, 12, 13},
    {18, 19, 20, 21, 22, 23, 25, 26, 6, 15, 33, 42, 51, 60, 69, 78, 7, 8, 16, 17},
    {18, 19, 20, 21, 22, 23, 24, 26, 7, 16, 34, 43, 52, 61, 70, 79, 6, 8, 15, 17},
    {18, 19, 20, 21, 22, 23, 24, 25, 8, 17, 35, 44, 53, 62, 71, 80, 6, 7, 15, 16},
    {28, 29, 30, 31, 32, 33, 34, 35, 0, 9, 18, 36, 45, 54, 63, 72, 37, 38, 46, 47},
    {27, 29, 30, 31, 32, 33, 34, 35, 1, 10, 19, 37, 46, 55, 64, 73, 36, 38, 45, 47},
    {27, 28, 30, 31, 32, 33, 34, 35, 2, 11, 20, 38, 47, 56, 65, 74, 36, 37, 45, 46},
    {27, 28, 29, 31, 32, 33, 34, 35, 3, 12, 21, 39, 48, 57, 66, 75, 40, 41, 49, 50},
    {27, 28, 29, 30, 32, 33, 34, 35, 4, 13, 22, 40, 49, 58, 67, 76, 39, 41, 48, 50},
    {27, 28, 29, 30, 31, 33, 34, 35, 5, 14, 23, 41, 50, 59, 68, 77, 39, 40, 48, 49},
    {27, 28, 29, 30, 31, 32, 34, 35, 6, 15, 24, 42, 51, 60, 69, 78, 43, 44, 52, 53},
    {27, 28, 29, 30, 31, 32, 33, 35, 7, 16, 25, 43, 52, 61, 70, 79, 42, 44, 51, 53},
    {27, 28, 29, 30, 31, 32, 33, 34, 8, 17, 26, 44, 53, 62, 71, 80, 42, 43, 51, 52},
    {37, 38, 39, 40, 41, 42, 43, 44, 0, 9, 18, 27, 45, 54, 63, 72, 28, 29, 46, 47},
    {36, 38, 39, 40, 41, 42, 43, 44, 1, 10, 19, 28, 46, 55, 64, 73, 27, 29, 45, 47},
    {36, 37, 39, 40, 41, 42, 43, 44, 2, 11, 20, 29, 47, 56, 65, 74, 27, 28, 45, 46},
    {36, 37, 38, 40, 41, 42, 43, 44, 3, 12, 21, 30, 48, 57, 66, 75, 31, 32, 49, 50},
    {36, 37, 38, 39, 41, 42, 43, 44, 4, 13, 22, 31, 49, 58, 67, 76, 30, 32, 48, 50},
    {36, 37, 38, 39, 40, 42, 43, 44, 5, 14, 23, 32, 50, 59, 68, 77, 30, 31, 48, 49},
    {36, 37, 38, 39, 40, 41, 43, 44, 6, 15, 24, 33, 51, 60, 69, 78, 34, 35, 52, 53},
    {36, 37, 38, 39, 40, 41, 42, 44, 7, 16, 25, 34, 52, 61, 70, 79, 33, 35, 51, 53},
    {36, 37, 38, 39, 40, 41, 42, 43, 8, 17, 26, 35, 53, 62, 71, 80, 33, 34, 51, 52},
    {46, 47, 48, 49, 50, 51, 52, 53, 0, 9, 18, 27, 36, 54, 63, 72, 28, 29, 37, 38},
    {45, 47, 48, 49, 50, 51, 52, 53, 1, 10, 19, 28, 37, 55, 64, 73, 27, 29, 36, 38},
    {45, 46, 48, 49, 50, 51, 52, 53, 2, 11, 20, 29, 38, 56, 65, 74, 27, 28, 36, 37},
    {45, 46, 47, 49, 50, 51, 52, 53, 3, 12, 21, 30, 39, 57, 66, 75, 31, 32, 40, 41},
    {45, 46, 47, 48, 50, 51, 52, 53, 4, 13, 22, 31, 40, 58, 67, 76, 30, 32, 39, 41},
    {45, 46, 47, 48, 49, 51, 52, 53, 5, 14, 23, 32, 41, 59, 68, 77, 30, 31, 39, 40},
    {45, 46, 47, 48, 49, 50, 52, 53, 6, 15, 24, 33, 42, 60, 69, 78, 34, 35, 43, 44},
    {45, 46, 47, 48, 49, 50, 51, 53, 7, 16, 25, 34, 43, 61, 70, 79, 33, 35, 42, 44},
    {45, 46, 47, 48, 49, 50, 51, 52, 8, 17, 26, 35, 44, 62, 71, 80, 33, 34, 42, 43},
    {55, 56, 57, 58, 59, 60, 61, 62, 0, 9, 18, 27, 36, 45, 63, 72, 64, 65, 73, 74},
    {54, 56, 57, 58, 59, 60, 61, 62, 1, 10, 19, 28, 37, 46, 64, 73, 63, 65, 72, 74},
    {54, 55, 57, 58, 59, 60, 61, 62, 2, 11, 20, 29, 38, 47, 65, 74, 63, 64, 72, 73},
    {54, 55, 56, 58, 59, 60, 61, 62, 3, 12, 21, 30, 39, 48, 66, 75, 67, 68, 76, 77},
    {54, 55, 56, 57, 59, 60, 61, 62, 4, 13, 22, 31, 40, 49, 67, 76, 66, 68, 75, 77},
    {54, 55, 56, 57, 58, 60, 61, 62, 5, 14, 23, 32, 41, 50, 68, 77, 66, 67, 75, 76},
    {54, 55, 56, 57, 58, 59, 61, 62, 6, 15, 24, 33, 42, 51, 69, 78, 70, 71, 79, 80},
    {54, 55, 56, 57, 58, 59, 60, 62, 7, 16, 25, 34, 43, 52, 70, 79, 69, 71, 78, 80},
    {54, 55, 56, 57, 58, 59, 60, 61, 8, 17, 26, 35, 44, 53, 71, 80, 69, 70, 78, 79},
    {64, 65, 66, 67, 68, 69, 70, 71, 0, 9, 18, 27, 36, 45, 54, 72, 55, 56, 73, 74},
    {63, 65, 66, 67, 68, 69, 70, 71, 1, 10, 19, 28, 37, 46, 55, 73, 54, 56, 72, 74},
    {63, 64, 66, 67, 68, 69, 70, 71, 2, 11, 20, 29, 38, 47, 56, 74, 54, 55, 72, 73},
    {63, 64, 65, 67, 68, 69, 70, 71, 3, 12, 21, 30, 39, 48, 57, 75, 58, 59, 76, 77},
    {63, 64, 65, 66, 68, 69, 70, 71, 4, 13, 22, 31, 40, 49, 58, 76, 57, 59, 75, 77},
    {63, 64, 65, 66, 67, 69, 70, 71, 5, 14, 23, 32, 41, 50, 59, 77, 57, 58, 75, 76},
    {63, 64, 65, 66, 67, 68, 70, 71, 6, 15, 24, 33, 42, 51, 60, 78, 61, 62, 79, 80},
    {63, 64, 65, 66, 67, 68, 69, 71, 7, 16, 25, 34, 43, 52, 61, 79, 60, 62, 78, 80},
    {63, 64, 65, 66, 67, 68, 69, 70, 8, 17, 26, 35, 44, 53, 62, 80, 60, 61, 78, 79},
    {73, 74, 75, 76, 77, 78, 79, 80, 0, 9, 18, 27, 36, 45, 54, 63, 55, 56, 64, 65},
    {72, 74, 75, 76, 77, 78, 79, 80, 1, 10, 19, 28, 37, 46, 55, 64, 54, 56, 63, 65},
    {72, 73, 75, 76, 77, 78, 79, 80, 2, 11, 20, 29, 38, 47, 56, 65, 54, 55, 63, 64},
    {72, 73, 74, 76, 77, 78, 79, 80, 3, 12, 21, 30, 39, 48, 57, 66, 58, 59, 67, 68},
    {72, 73, 74, 75, 77, 78, 79, 80, 4, 13, 22, 31, 40, 49, 58, 67, 57, 59, 66, 68},
    {72, 73, 74, 75, 76, 78, 79, 80, 5, 14, 23, 32, 41, 50, 59, 68, 57, 58, 66, 67},
    {72, 73, 74, 75, 76, 77, 79, 80, 6, 15, 24, 33, 42, 51, 60, 69, 61, 62, 70, 71},
    {72, 73, 74, 75, 76, 77, 78, 80, 7, 16, 25, 34, 43, 52, 61, 70, 60, 62, 69, 71},
    {72, 73, 74, 75, 76, 77, 78, 79, 8, 17, 26, 35, 44, 53, 62, 71, 60, 61, 69, 70}};
Sint8 grid[81];
Sint8 tempGrid[81];
Sint8 currGrid[81];
Sint8 bestGrid[81];
Sint8 solutionGrid[81];
Sint16 miniGrid[81];
Uint8 numEmpty;

Sint16 finalDifficulty;
Sint8 foundSolution;
Sint8 numHoles;
Sint8 numHolesBest;
Sint16 bestDifficulty;
Sint16 difficulty;
Sint8 randomIndex;
Sint8 currNumVals;
Sint8 passed;
// Sint8 cellIsPossibleForValue;
Sint8 row, col, val, cell, blockRow, blockCol, cellRow, cellCol;

Sint8 possibleValsArr[9];

Uint32 seed;

Uint32 startTime;

Uint32 beginning;

//void test_main() {
//    // srand(0);
//    // shuffleBoard();
//    seed = 102;
//    generateGrid_Backtracking();
//    COPY_GRID(solutionGrid, grid);
//    cout << endl << "ORIGINAL:" << endl;
//    printBoard();
//    digHoles(250, 300);
//    cout << endl << "DUG:" << endl;
//    printBoard();
//    cout << endl << "SOLVED:" << endl;
//    printSolutionGrid();
//    cout << "Difficulty: " << int(difficulty) << endl;
//    cout << "finalDifficulty variable: " << int(finalDifficulty) << endl;
//    cout << "numHoles variable: " << int(numHoles) << endl;
//}

//void test_PuzzleDifficulty() {
//    Uint8 myGrid[81] =
//        {5, 3, 4, 0, 0, 8, 0, 1, 0,
//         0, 0, 0, 0, 0, 2, 0, 9, 0,
//         0, 0, 0, 0, 0, 7, 6, 0, 4,
//         0, 0, 0, 5, 0, 0, 1, 0, 0,
//         1, 0, 0, 0, 0, 0, 0, 0, 3,
//         0, 0, 9, 0, 0, 1, 0, 0, 0,
//         3, 0, 5, 4, 0, 0, 0, 0, 0,
//         0, 8, 0, 2, 0, 0, 0, 0, 0,
//         0, 6, 0, 7, 0, 0, 3, 8, 2};
//    COPY_GRID(tempGrid, myGrid);
//    solvePuzzle(0);
//    numHoles = std::count(tempGrid, tempGrid + 81, 0);
//    difficulty = finalDifficulty * BACKTRACKING_VAL + numHoles;
//    PRINT("Difficulty: " << (int) difficulty);
//}

/* Generates player grid in grid and solution grid in solutionGrid, and stores
 * difficulty in difficulty.
 */
Uint8 generateGridAndSolution(Uint16 minDiff, Uint16 maxDiff) {
    seed = SDL_GetTicks();
    srand(seed);
    // If either step fails (it times out or an invalid puzzle is created), retry the entire process
    // If the MAX_TIMEOUT has passed, give up and use a pre-generated puzzle
    beginning = SDL_GetTicks();
    while (true) {
        if (generateGrid_Backtracking() != 0) {
            if (SDL_GetTicks() - beginning > MAX_TIMEOUT) {
                return 0;
            }
            continue;
        }
        COPY_GRID(solutionGrid, grid);
        if (digHoles(minDiff, maxDiff) != 0) {
            if (SDL_GetTicks() - beginning > MAX_TIMEOUT) {
                return 0;
            }
            continue;
        }
        break;
    }

    updateNumEmpty();


    /* At this point:
     * grid = the grid that is actually used by the player and printed onto the screen
     * tempGrid (also defined as originalGrid for readability) = the original, static grid
     * solutionGrid = the solved grid
     * currGrid = unused
     * bestGrid = unused
     * miniGrid = the player grid that contains mini numbers (currently empty, set exclusively by player)
     */
    PRINT(endl << "PLAYER BOARD:");
    printBoard();
    PRINT(endl << "SOLUTION:");
    printSolutionGrid();
    return 1;
}

Uint8 generateGrid_Backtracking() {
    srand(rand());
    ZERO_OUT_ARRAY(grid);
    ZERO_OUT_ARRAY(tempGrid);
    ZERO_OUT_ARRAY(currGrid);
    ZERO_OUT_ARRAY(bestGrid);
    ZERO_OUT_ARRAY(solutionGrid);
    ZERO_OUT_ARRAY(miniGrid);
    // std::random_shuffle(possibleValsArr, possibleValsArr + 9);
    // std::random_shuffle(cellIndices, cellIndices + 81);

    i = 0;
    initPossibleValsArrByIndex(i);
    j = 0;
    while (i < 81) {
        char_x1 = true; /* flag */
        for (k = 0; k < 20; k++) {
            if (grid[relevantIndicesTable_All[i][k]] == possibleValsArr[j]) {
                j++;
                while (j > 8) {
                    // PRINT("SET " << (int) cellIndices[i] << " TO 0");
                    grid[i] = 0;
                    i--;
                    initPossibleValsArrByIndex(i);
                    for (char_x2 = 0; char_x2 < 9; char_x2++) {
                        if (possibleValsArr[char_x2] == grid[i]) {
                            j = char_x2 + 1;
                            break;
                        }
                    }
                    // j = grid[i] + 1;
                }
                char_x1 = false;
                break;
            }
        }
        if (char_x1) {
            // PRINT("SET " << (int)cellIndices[i] << " TO " << (int) possibleValsArr[j]);
            grid[i] = possibleValsArr[j];
            i++;
            initPossibleValsArrByIndex(i);
            j = 0;
        }
    }
    return 0;
}

Uint8 digHoles(short minDifficulty, short maxDifficulty) {
    /* Set Initial Time Values */
    startTime = SDL_GetTicks();

    // srand(seed);
    srand(rand());
    COPY_GRID(currGrid, grid);
    COPY_GRID(bestGrid, grid);
    bestDifficulty = 0;
    difficulty = 0;
    numHoles = 0;
    numHolesBest = 0;
    COPY_GRID(tempGrid, currGrid);
    finalDifficulty = -1;
    foundSolution = false;
    solvePuzzle(0);
    
    while (difficulty < minDifficulty || difficulty > maxDifficulty) {
        randomIndex = RANDINT(0, 80);
        if (currGrid[randomIndex] != 0) {
            currGrid[randomIndex] = 0;
            numHoles++;
        } else {
            currGrid[randomIndex] = solutionGrid[randomIndex];
            numHoles--;
        }
        randomIndex = RANDINT(0, 80); /* runs marginally faster than a for(i = 0; i < 2; i++) loop */
        if (currGrid[randomIndex] != 0) {
            currGrid[randomIndex] = 0;
            numHoles++;
        }
        else {
            currGrid[randomIndex] = solutionGrid[randomIndex];
            numHoles--;
        }
        COPY_GRID(tempGrid, currGrid);
        finalDifficulty = -1;
        foundSolution = false;
        solvePuzzle(0);
        
        if (finalDifficulty < 0) /* -2 = multiple solutions, -1 = no solution */
            difficulty = -10;
        else
            difficulty = finalDifficulty * BACKTRACKING_VAL + numHoles;
            // PRINT(int(difficulty));
        if ((difficulty > bestDifficulty) && (difficulty <= maxDifficulty)) {
            bestDifficulty = difficulty;
            COPY_GRID(bestGrid, currGrid);
            numHolesBest = numHoles;
        } else {
            COPY_GRID(currGrid, bestGrid);
            numHoles = numHolesBest;
        }
        if ((SDL_GetTicks() - startTime) > TIMEOUT) {
            PRINT("Puzzle generation timed out. Retrying.");
            return 1;
        }
    }
    COPY_GRID(grid, currGrid);
    return validateGridAndSolution();
    // return difficulty;
}

Sint16 solvePuzzle(Sint16 recursiveDifficulty) {
    Sint8 bestMode = -1;
    Sint8 bestCellOrVal = -1;
    Sint8 fewestPossibleVals = 10;
    Sint8 bestSetIndex = -1;
    Sint8 counter = 0;
    Sint8 curr_i;
    Sint8 gridIndex;
    Sint8 cellToChangeVal;
    Sint8 bsi_blockRow, bsi_blockCol, bsi_cellRow, bsi_cellCol;
    Sint8 possibleValsByCell[81][9];
    Sint8 possibleCellsByVal_Row[9][9][9];
    Sint8 possibleCellsByVal_Col[9][9][9];
    Sint8 possibleCellsByVal_Block[9][9][9];
    ZERO_OUT_ARRAY(possibleValsByCell);
    for (i = 0; i < 81; i++) {
        if (tempGrid[i] == 0) {
            currNumVals = 0;
            for (j = 9; j > 0; j--) {
                passed = true;
                for (k = 0; (Uint32)k < LEN(relevantIndicesTable_All[i]); k++) {
                    if (j == tempGrid[relevantIndicesTable_All[i][k]]) {
                        passed = false;
                        break;
                    }
                }
                if (passed) {
                    possibleValsByCell[i][j - 1] = 1;
                    currNumVals += 1;
                }
            }
            if (currNumVals < fewestPossibleVals) {
                bestMode = 0;
                bestCellOrVal = i;
                fewestPossibleVals = currNumVals;
            }
        }
    }
    /* If there are no cells remaining, return 0 */
    if (bestCellOrVal == -1) {
        if (!foundSolution) {
            foundSolution = true;
            COPY_GRID(grid, tempGrid);
            finalDifficulty = recursiveDifficulty;
            return -1;
        } else { // found multiple solutions
            finalDifficulty = -2;
            return -2;
        }
    }
    /* Next, set-oriented freedom analysis: Get the value with the least number of possible cells (within each set (row, column, or block), see which value is pigeonholed into the fewest cells) */
    /* Rows */
    ZERO_OUT_ARRAY(possibleCellsByVal_Row);
    for (row = 0; row < 9; row++) {
        for (val = 0; val < 9; val++) {
            currNumVals = 0;
            for (cell = 0; cell < 9; cell++) {
                // cellIsPossibleForValue = possibleValsByCell[(row * 9) + cell][val];
                if (possibleValsByCell[(row * 9) + cell][val]) {
                    possibleCellsByVal_Row[row][val][cell] = 1;
                    currNumVals += 1;
                }
            }
            if (0 < currNumVals && currNumVals < fewestPossibleVals) {
                bestMode = 1;
                bestCellOrVal = val + 1;
                fewestPossibleVals = currNumVals;
                bestSetIndex = row;
            }
        }
    }
    /* Columns */
    ZERO_OUT_ARRAY(possibleCellsByVal_Col);
    for (col = 0; col < 9; col++) {
        for (val = 0; val < 9; val++) {
            currNumVals = 0;
            for (cell = 0; cell < 9; cell++) {
                // cellIsPossibleForValue = possibleValsByCell[(cell * 9) + col][val];
                if (possibleValsByCell[(cell * 9) + col][val]) {
                    possibleCellsByVal_Col[col][val][cell] = 1;
                    currNumVals += 1;
                }
            }
            if (0 < currNumVals && currNumVals < fewestPossibleVals) {
                bestMode = 2;
                bestCellOrVal = val + 1;
                fewestPossibleVals = currNumVals;
                bestSetIndex = col;
            }
        }
    }
    /* Blocks */
    ZERO_OUT_ARRAY(possibleCellsByVal_Block);
    for (blockRow = 0; blockRow < 3; blockRow++) {
        for (blockCol = 0; blockCol < 3; blockCol++) {
            for (val = 0; val < 9; val++) {
                currNumVals = 0;
                for (cellRow = 0; cellRow < 3; cellRow++) {
                    for (cellCol = 0; cellCol < 3; cellCol++) {
                        // cellIsPossibleForValue = possibleValsByCell[(blockRow * 27) + (blockCol * 3) + (cellRow * 9) + cellCol][val];
                        if (possibleValsByCell[(blockRow * 27) + (blockCol * 3) + (cellRow * 9) + cellCol][val]) {
                            possibleCellsByVal_Block[(blockRow * 3) + blockCol][val][(cellRow * 3) + cellCol] = 1;
                            currNumVals += 1;
                        }
                    }
                }
                if (0 < currNumVals && currNumVals < fewestPossibleVals) {
                    bestMode = 3;
                    bestCellOrVal = val + 1;
                    fewestPossibleVals = currNumVals;
                    bestSetIndex = (blockRow * 3) + blockCol;
                }
            }
        }
    }
    /* Fill the most likely value from the previous steps and recurse */
    switch(bestMode) {
        case 0:
            for (curr_i = 0; curr_i < 9; curr_i++) {
                if (possibleValsByCell[bestCellOrVal][curr_i] == 1) {
                    tempGrid[bestCellOrVal] = curr_i + 1;
                    counter++;
                    // currDifficulty = pow((counter - 1), 2);
                    // resultFlag = solvePuzzle(recursiveDifficulty + currDifficulty);
                    if (solvePuzzle(recursiveDifficulty + short(pow((counter - 1), 2))) == -2)
                        return -2;
                    tempGrid[bestCellOrVal] = 0;
                }
            }
            break;
        case 1:
            for (curr_i = 0; curr_i < 9; curr_i++) {
                if (possibleCellsByVal_Row[bestSetIndex][bestCellOrVal - 1][curr_i] == 1) {
                    gridIndex = (bestSetIndex * 9) + curr_i;
                    cellToChangeVal = tempGrid[gridIndex];
                    tempGrid[gridIndex] = bestCellOrVal;
                    counter++;
                    // currDifficulty = pow((counter - 1), 2);
                    // resultFlag = solvePuzzle(recursiveDifficulty + currDifficulty);
                    if (solvePuzzle(recursiveDifficulty + short(pow((counter - 1), 2))) == -2)
                        return -2;
                    tempGrid[gridIndex] = cellToChangeVal;
                }
            }
            break;
        case 2:
            for (curr_i = 0; curr_i < 9; curr_i++) {
                if (possibleCellsByVal_Col[bestSetIndex][bestCellOrVal - 1][curr_i] == 1) {
                    gridIndex = (curr_i * 9) + bestSetIndex;
                    cellToChangeVal = tempGrid[gridIndex];
                    tempGrid[gridIndex] = bestCellOrVal;
                    counter++;
                    // currDifficulty = pow((counter - 1), 2);
                    // resultFlag = solvePuzzle(recursiveDifficulty + currDifficulty);
                    if (solvePuzzle(recursiveDifficulty + short(pow((counter - 1), 2))) == -2)
                        return -2;
                    tempGrid[gridIndex] = cellToChangeVal;
                }
            }
            break;
        case 3:
            bsi_blockRow = bestSetIndex / 3;
            bsi_blockCol = bestSetIndex % 3;
            for (curr_i = 0; curr_i < 9; curr_i++) {
                if (possibleCellsByVal_Block[bestSetIndex][bestCellOrVal - 1][curr_i] == 1) {
                    bsi_cellRow = curr_i / 3;
                    bsi_cellCol = curr_i % 3;
                    gridIndex = (bsi_blockRow * 27) + (bsi_blockCol * 3) + (bsi_cellRow * 9) + bsi_cellCol;
                    cellToChangeVal = tempGrid[gridIndex];
                    tempGrid[gridIndex] = bestCellOrVal;
                    counter++;
                    // currDifficulty = pow((counter - 1), 2);
                    // resultFlag = solvePuzzle(recursiveDifficulty + currDifficulty);
                    if (solvePuzzle(recursiveDifficulty + short(pow((counter - 1), 2))) == -2)
                        return -2;
                    tempGrid[gridIndex] = cellToChangeVal;
                }
            }
            break;
        default:
            break;
    }
    return -1;
}

Uint8 validateGridAndSolution() {
    i = 0;
    for (i = 0; i < 81; i++) {
        if (!((grid[i] == solutionGrid[i]) || (grid[i] == 0))) {
            PRINT("Invalid grid generated. Retrying.");
            return 1;
        }
    }
    return 0;
}

#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP) || defined(WII))
void printBoard() {
    cout << endl;
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << " ---------------------" << endl;
        }
        for (col = 0; col < 3; col++) {
            if (grid[(row * 9) + col] != 0)
                cout << " " << int(grid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 3; col < 6; col++) {
            if (grid[(row * 9) + col] != 0)
                cout << " " << int(grid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 6; col < 9; col++) {
            if (grid[(row * 9) + col] != 0)
                cout << " " << int(grid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << endl;
    }
}

void printTempGrid() {
    cout << endl;
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << " ---------------------" << endl;
        }
        for (col = 0; col < 3; col++) {
            if (tempGrid[(row * 9) + col] != 0)
                cout << " " << int(tempGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 3; col < 6; col++) {
            if (tempGrid[(row * 9) + col] != 0)
                cout << " " << int(tempGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 6; col < 9; col++) {
            if (tempGrid[(row * 9) + col] != 0)
                cout << " " << int(tempGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << endl;
    }
}

void printSolutionGrid() {
    cout << endl;
    for (row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << " ---------------------" << endl;
        }
        for (col = 0; col < 3; col++) {
            if (solutionGrid[(row * 9) + col] != 0)
                cout << " " << int(solutionGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 3; col < 6; col++) {
            if (solutionGrid[(row * 9) + col] != 0)
                cout << " " << int(solutionGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << " |";
        for (col = 6; col < 9; col++) {
            if (solutionGrid[(row * 9) + col] != 0)
                cout << " " << int(solutionGrid[(row * 9) + col]);
            else
                cout << "  ";
        }
        cout << endl;
    }
}
#else
void printBoard() {
}

void printTempGrid() {
}

void printSolutionGrid() {
}
#endif

void initPossibleValsArrByIndex(Sint8 index) {
    possibleValsArr[0] = 1;
    possibleValsArr[1] = 2;
    possibleValsArr[2] = 3;
    possibleValsArr[3] = 4;
    possibleValsArr[4] = 5;
    possibleValsArr[5] = 6;
    possibleValsArr[6] = 7;
    possibleValsArr[7] = 8;
    possibleValsArr[8] = 9;
    srand(seed);
    srand(rand() + index);
    std::random_shuffle(possibleValsArr, possibleValsArr + 9);
}

void updateNumEmpty() {
    numEmpty = (Uint8)std::count(grid, grid + 81, 0);
}

void checkForVictory() {
    k = 1;
    if (numEmpty == 0) {
        for (j = 0; j < 81; j++) {
            if (grid[j] != solutionGrid[j]) {
                k = 0;
                break;
            }
        }
        if (k) {
            programState = 11;
        }
    }
}
