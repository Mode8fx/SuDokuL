//#include "game_logic.h"
//#include "main.h"
//#include "sound_logic.h"

//void setGridNum(Sint8 index, Sint8 num) {
//    grid[index] = num;
//    updateNumEmpty();
//    checkForVictory();
//    miniGridState = 0;
//    setGridCursorByLargeX();
//    setGridCursorByLargeY();
//}
//
//void setGridCursorByLargeX() {
//    gridCursor_bottom_left.rect.x = GRID_X_AT_COL(gridCursorIndex_x) - gridCursorCornerStep;
//    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;
//    gridCursor_bottom_right.rect.x = GRID_X_AT_COL(gridCursorIndex_x) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);
//    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;
//}
//
//void setGridCursorByLargeY() {
//    gridCursor_bottom_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);
//    gridCursor_top_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) - gridCursorCornerStep;
//    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;
//    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;
//}
//
//void gameHandleCheatRevealCell() {
//    if (KEY_PRESSED(INPUT_SWAP) && miniGridState == 0) {
//        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
//        if (originalGrid[i] == 0) {
//            if (++cheatCounter >= 8) {
//                Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
//                setGridNum(i, solutionGrid[i]);
//                cheatCounter = 0;
//            }
//        }
//    }
//}