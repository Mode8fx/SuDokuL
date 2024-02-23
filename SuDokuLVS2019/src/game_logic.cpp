#include "general.h"
#include "sprite_objects.h"
#include "game_logic.h"
#include "config.h"
#include "sound_logic.h"
#include "sudokuGen.h"

bool mouseBoundsX(Sint8 start, Sint8 end) {
    return ((mouseInput_x >= GRID_X_AT_COL(start)) && (mouseInput_x < (GRID_X_AT_COL(end) + (GRID_SIZE_A3))));
}

bool mouseBoundsY(Sint8 start, Sint8 end) {
    return ((mouseInput_y >= GRID_Y_AT_ROW(start)) && (mouseInput_y < (GRID_Y_AT_ROW(end) + (GRID_SIZE_A3))));
}

bool clickedWithinGrid() {
    return (KEY_PRESSED(INPUT_CONFIRM_ALT) && mouseIsInsideGridSquare());
}

// easier to code/check than GAME_HANDLE_MOUSE_MOVEMENT_MAIN()... but also less efficient
bool mouseIsInsideGridSquare() {
    return ((mouseBoundsX(0, 0) || mouseBoundsX(1, 1) || mouseBoundsX(2, 2) || mouseBoundsX(3, 3) || mouseBoundsX(4, 4)
        || mouseBoundsX(5, 5) || mouseBoundsX(6, 6) || mouseBoundsX(7, 7) || mouseBoundsX(8, 8)) &&
        (mouseBoundsY(0, 0) || mouseBoundsY(1, 1) || mouseBoundsY(2, 2) || mouseBoundsY(3, 3) || mouseBoundsY(4, 4)
            || mouseBoundsY(5, 5) || mouseBoundsY(6, 6) || mouseBoundsY(7, 7) || mouseBoundsY(8, 8)));
}

bool mouseBoundsMiniX(Sint8 start, Sint8 end) {
    return (mouseInput_x >= xAtMiniGridIndex(start) && (mouseInput_x < (xAtMiniGridIndex(end) + (GRID_SIZE_A3))));
}

bool mouseBoundsMiniY(Sint8 start, Sint8 end) {
    return (mouseInput_y >= yAtMiniGridIndex(start) && (mouseInput_y < (yAtMiniGridIndex(end) + (GRID_SIZE_A3))));
}

bool clickedWithinMiniGrid() {
    return (KEY_PRESSED(INPUT_CONFIRM_ALT) && mouseIsInsideGridSquareMini());
}

// easier to code/check than GAME_HANDLE_MOUSE_MOVEMENT_MINI()... but also less efficient
bool mouseIsInsideGridSquareMini() {
    return ((mouseBoundsMiniX(-1, -1) || mouseBoundsMiniX(0, 0) || mouseBoundsMiniX(1, 1) || mouseBoundsMiniX(2, 2)) &&
        (mouseBoundsMiniY(0, 0) || mouseBoundsMiniY(1, 1) || mouseBoundsMiniY(2, 2)) &&
        !(mouseBoundsMiniX(-1, -1) && mouseBoundsMiniY(0, 0)));
}

bool clickedOutsideMiniGrid() {
    return (KEY_PRESSED(INPUT_CONFIRM_ALT) && !(mouseBoundsMiniX(-1, 2) && mouseBoundsMiniY(0, 2)));
}

void setGridNum(Sint8 index, Sint8 num) {
    grid[index] = num;
    updateNumEmpty();
    checkForVictory();
    miniGridState = 0;
    setGridCursorByLargeX();
    setGridCursorByLargeY();
}

void setGridCursorByLargeX() {
    gridCursor_bottom_left.rect.x = GRID_X_AT_COL(gridCursorIndex_x) - gridCursorCornerStep;
    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;
    gridCursor_bottom_right.rect.x = GRID_X_AT_COL(gridCursorIndex_x) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);
    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;
}

void setGridCursorByLargeY() {
    gridCursor_bottom_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);
    gridCursor_top_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) - gridCursorCornerStep;
    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;
    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;
}

void gameHandleCheatRevealCell() {
    if (KEY_PRESSED(INPUT_SWAP) && miniGridState == 0) {
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
        if (originalGrid[i] == 0) {
            if (++cheatCounter >= 8) {
                Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
                setGridNum(i, solutionGrid[i]);
                cheatCounter = 0;
            }
        }
    }
}

Sint16 xAtMiniGridIndex(Sint8 index) {
    return (currMiniGrid->rect.x + (GRID_SIZE_D * 3) + ((index + 1) * GRID_SIZE_A3) + ((index + 1) * GRID_SIZE_B));
}

Sint16 yAtMiniGridIndex(Sint8 index) {
    return (currMiniGrid->rect.y + (GRID_SIZE_D * 3) + (index * GRID_SIZE_A3) + (index * GRID_SIZE_B));
}