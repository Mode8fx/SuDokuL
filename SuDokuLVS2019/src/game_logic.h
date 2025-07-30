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
extern Sint8 savedMiniGridState;
extern Sint8 temp_mouseIndex_x;
extern Sint8 temp_mouseIndex_y;
extern Sint16 gridCursorCornerStep;
extern bool justClickedInMiniGrid;

extern void gameHandleMainGridNavigation();
extern void gameHandleMouseMovementMain();
extern inline bool mouseBoundsX(Sint8, Sint8);
extern inline bool mouseBoundsY(Sint8, Sint8);
extern inline bool clickedWithinGrid();
extern inline bool clickedInRect(SDL_Rect *);
extern inline bool mouseIsInsideGridSquare();
extern void gameHandleMiniGridNavigation();
extern void gameHandleMouseMovementMini();
extern inline bool mouseBoundsMiniX(Sint8, Sint8);
extern inline bool mouseBoundsMiniY(Sint8, Sint8);
extern inline bool clickedWithinMiniGrid();
extern inline bool mouseIsInsideGridSquareMini();
extern inline bool clickedOutsideMiniGrid();
extern void setGridNum(Sint8, Sint8);
extern void gameHandleNumKeyPresses();
extern void checkNumKeyPress(Uint32, Sint8);
extern inline void swapMiniGridState();
extern inline void setGridMiniNum(Sint8, Sint8);
extern void setGridCursorByLargeX();
extern void setGridCursorByLargeY();
extern void setGridCursorBySmallX();
extern void setGridCursorBySmallY();
extern inline Sint16 xAtMiniGridIndex(Sint8);
extern inline Sint16 yAtMiniGridIndex(Sint8);
extern void gameHandleCheatRevealCell();
extern void gameHandleCheatClearIncorrectCells();
extern void gameHandleChangeSong();
extern void gameHandleCheatDebugMenu();
extern void drawSidebar();
#endif