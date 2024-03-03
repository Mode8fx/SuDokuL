#include "include.h"
#include "shared.h"

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

/* Game Variables */
extern Sint8 gridCursorIndex_x;
extern Sint8 gridCursorIndex_y;
extern Sint8 miniGridCursorIndex_x;
extern Sint8 miniGridCursorIndex_y;
extern Sint8 miniGridState;
extern Sint8 lastMiniGridState;
extern Sint8 temp_mouseIndex_x;
extern Sint8 temp_mouseIndex_y;
extern Uint16 gridCursorCornerStep;
extern bool justClickedInMiniGrid;

extern void gameHandleMainGridNavigation();
extern void gameHandleMouseMovementMain();
extern bool mouseBoundsX(Sint8, Sint8);
extern bool mouseBoundsY(Sint8, Sint8);
extern bool clickedWithinGrid();
extern bool clickedInRect(SDL_Rect *);
extern bool mouseIsInsideGridSquare();
extern void gameHandleMiniGridNavigation();
extern void gameHandleMouseMovementMini();
extern bool mouseBoundsMiniX(Sint8, Sint8);
extern bool mouseBoundsMiniY(Sint8, Sint8);
extern bool clickedWithinMiniGrid();
extern bool mouseIsInsideGridSquareMini();
extern bool clickedOutsideMiniGrid();
extern void setGridNum(Sint8, Sint8);
extern void gameHandleNumKeyPresses();
extern void checkNumKeyPress(Uint32, Sint8);
extern void swapMiniGridState();
extern void setGridMiniNum(Sint8, Sint8);
extern void setGridCursorByLargeX();
extern void setGridCursorByLargeY();
extern void setGridCursorBySmallX();
extern void setGridCursorBySmallY();
extern Sint16 xAtMiniGridIndex(Sint8);
extern Sint16 yAtMiniGridIndex(Sint8);
extern void gameHandleCheatRevealCell();
extern void gameHandleCheatClearIncorrectCells();
extern void gameHandleChangeSong();
extern void drawSidebar();
#endif