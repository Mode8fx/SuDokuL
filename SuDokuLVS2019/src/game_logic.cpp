#include "general.h"
#include "sprite_objects.h"
#include "game_logic.h"
#include "config.h"
#include "sound_logic.h"
#include "window.h"
#include "menu_logic.h"
#include "sudokuGen.h"

static void positionMiniGridShared(Sint16 x, Sint16 y) {
  miniGrid_shared_1.rect.x = x;
  miniGrid_shared_2.rect.x = x;
  miniGrid_shared_3.rect.x = x;
  miniGrid_shared_1.rect.y = y;
  miniGrid_shared_2.rect.y = y + miniGrid_shared_1.rect.h;
  miniGrid_shared_3.rect.y = miniGrid_shared_2.rect.y + miniGrid_shared_2.rect.h;
}

void gameHandleMainGridNavigation() {
    if (miniGridState == 0) {
        if (keyPressed(INPUT_LEFT)) {
            if (--gridCursorIndex_x < 0)
                gridCursorIndex_x = 8;
            setGridCursorByLargeX();
        }
        if (keyPressed(INPUT_RIGHT)) {
            gridCursorIndex_x = (gridCursorIndex_x + 1) % 9;
            setGridCursorByLargeX();
        }
        if (keyPressed(INPUT_UP)) {
            if (--gridCursorIndex_y < 0)
                gridCursorIndex_y = 8;
            setGridCursorByLargeY();
        }
        if (keyPressed(INPUT_DOWN)) {
            gridCursorIndex_y = (gridCursorIndex_y + 1) % 9;
            setGridCursorByLargeY();
        }
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
        if ((keyPressed(INPUT_CONFIRM) || clickedWithinGrid()) && originalGrid[i] == 0) {
          Sint16 start_x = GRID_X_AT_COL(gridCursorIndex_x) + (Sint16)(gridSizeA * 1.5);
          Sint16 start_y = GRID_Y_AT_ROW(gridCursorIndex_y) + (Sint16)(gridSizeA * 2.5);
          Sint16 miniGrid_shared_height = miniGrid_shared_1.rect.h + miniGrid_shared_2.rect.h + miniGrid_shared_3.rect.h;
          if (gridCursorIndex_x < 4) {
            if (gridCursorIndex_y < 4) {
              currMiniGridCursor = &miniGrid_top_left;
              currMiniGridNum = 2;
              currMiniGridCursor->rect.x = start_x;
              currMiniGridCursor->rect.y = start_y;
              positionMiniGridShared(currMiniGridCursor->rect.x + (Sint16)(gridSizeD * 2), currMiniGridCursor->rect.y + (Sint16)(gridSizeD * 2));
            } else {
              currMiniGridCursor = &miniGrid_bottom_left;
              currMiniGridNum = 0;
              currMiniGridCursor->rect.x = start_x;
              positionMiniGridShared(currMiniGridCursor->rect.x + (Sint16)(gridSizeD * 2), start_y - miniGrid_shared_height - (Sint16)(gridSizeD * 4));
              currMiniGridCursor->rect.y = miniGrid_shared_1.rect.y + miniGrid_shared_height - (Sint16)(gridSizeD * 2);
            }
          } else {
            Sint16 size_x = miniGrid_shared_1.rect.w + (Sint16)(gridSizeD * 2);
            if (gridCursorIndex_y < 4) {
              currMiniGridCursor = &miniGrid_top_right;
              currMiniGridNum = 3;
              currMiniGridCursor->rect.y = start_y;
              positionMiniGridShared(start_x - size_x, currMiniGridCursor->rect.y + (Sint16)(gridSizeD * 2));
              currMiniGridCursor->rect.x = miniGrid_shared_1.rect.x + miniGrid_shared_1.rect.w - (Sint16)(gridSizeD * 2);
            } else {
              currMiniGridCursor = &miniGrid_bottom_right;
              currMiniGridNum = 1;
              positionMiniGridShared(start_x - size_x, start_y - miniGrid_shared_height - (Sint16)(gridSizeD * 4));
              currMiniGridCursor->rect.x = miniGrid_shared_1.rect.x + miniGrid_shared_1.rect.w - (Sint16)(gridSizeD * 2);
              currMiniGridCursor->rect.y = miniGrid_shared_1.rect.y + miniGrid_shared_height - (Sint16)(gridSizeD * 2);
            }
          }
          miniGridCursorIndex_x = max((grid[i] - 1) % 3, 0);
          miniGridCursorIndex_y = (grid[i] - 1) / 3;
          miniGridState = 1;
          setGridCursorBySmallX();
          setGridCursorBySmallY();
        }
    }
}

// This looks complicated, but it's slightly more efficient than a simple for loop on average
void gameHandleMouseMovementMain() {
    if (miniGridState == 0 && !justClickedInMiniGrid) {
        temp_mouseIndex_x = -1;
        temp_mouseIndex_y = -1;
        if (mouseBoundsX(0, 8)) {
            if (mouseBoundsX(0, 2)) {
                if (mouseBoundsX(0, 0)) {
                    temp_mouseIndex_x = 0;
                } else if (mouseBoundsX(1, 1)) {
                    temp_mouseIndex_x = 1;
                } else if (mouseBoundsX(2, 2)) {
                    temp_mouseIndex_x = 2;
                }
            } else if (mouseBoundsX(3, 5)) {
                if (mouseBoundsX(3, 3)) {
                    temp_mouseIndex_x = 3;
                } else if (mouseBoundsX(4, 4)) {
                    temp_mouseIndex_x = 4;
                } else if (mouseBoundsX(5, 5)) {
                    temp_mouseIndex_x = 5;
                }
            } else if (mouseBoundsX(6, 8)) {
                if (mouseBoundsX(6, 6)) {
                    temp_mouseIndex_x = 6;
                } else if (mouseBoundsX(7, 7)) {
                    temp_mouseIndex_x = 7;
                } else if (mouseBoundsX(8, 8)) {
                    temp_mouseIndex_x = 8;
                }
            }
        }
        if (mouseBoundsY(0, 8)) {
            if (mouseBoundsY(0, 2)) {
                if (mouseBoundsY(0, 0)) {
                    temp_mouseIndex_y = 0;
                } else if (mouseBoundsY(1, 1)) {
                    temp_mouseIndex_y = 1;
                } else if (mouseBoundsY(2, 2)) {
                    temp_mouseIndex_y = 2;
                }
            } else if (mouseBoundsY(3, 5)) {
                if (mouseBoundsY(3, 3)) {
                    temp_mouseIndex_y = 3;
                } else if (mouseBoundsY(4, 4)) {
                    temp_mouseIndex_y = 4;
                } else if (mouseBoundsY(5, 5)) {
                    temp_mouseIndex_y = 5;
                }
            } else if (mouseBoundsY(6, 8)) {
                if (mouseBoundsY(6, 6)) {
                    temp_mouseIndex_y = 6;
                } else if (mouseBoundsY(7, 7)) {
                    temp_mouseIndex_y = 7;
                } else if (mouseBoundsY(8, 8)) {
                    temp_mouseIndex_y = 8;
                }
            }
        }
        if (temp_mouseIndex_x > -1 && temp_mouseIndex_y > -1) {
            gridCursorIndex_x = temp_mouseIndex_x;
            gridCursorIndex_y = temp_mouseIndex_y;
            setGridCursorByLargeX();
            setGridCursorByLargeY();
        }
    }
}

inline bool mouseBoundsX(Sint8 start, Sint8 end) {
    return ((mouseInput_x >= GRID_X_AT_COL(start)) && (mouseInput_x < (GRID_X_AT_COL(end) + (gridSizeA3))));
}

inline bool mouseBoundsY(Sint8 start, Sint8 end) {
    return ((mouseInput_y >= GRID_Y_AT_ROW(start)) && (mouseInput_y < (GRID_Y_AT_ROW(end) + (gridSizeA3))));
}

inline bool clickedWithinGrid() {
#if defined(WII)
    return keyPressed(INPUT_CONFIRM_ALT) && !(clickedInRect(&gameSidebarSmall1Rect) || clickedInRect(&gameSidebarSmall2Rect) || clickedInRect(&gameSidebarSmall3Rect));
#else
    return (keyPressed(INPUT_CONFIRM_ALT) && mouseIsInsideGridSquare());
#endif
}

inline bool clickedInRect(SDL_Rect *rect) {
	return (keyPressed(INPUT_CONFIRM_ALT) && mouseInput_x >= rect->x && mouseInput_x < (rect->x + rect->w) && mouseInput_y >= rect->y && mouseInput_y < (rect->y + rect->h));
}

// easier to code/check than gameHandleMouseMovementMain()... but also less efficient
inline bool mouseIsInsideGridSquare() {
    return ((mouseBoundsX(0, 0) || mouseBoundsX(1, 1) || mouseBoundsX(2, 2) || mouseBoundsX(3, 3) || mouseBoundsX(4, 4)
        || mouseBoundsX(5, 5) || mouseBoundsX(6, 6) || mouseBoundsX(7, 7) || mouseBoundsX(8, 8)) &&
        (mouseBoundsY(0, 0) || mouseBoundsY(1, 1) || mouseBoundsY(2, 2) || mouseBoundsY(3, 3) || mouseBoundsY(4, 4)
            || mouseBoundsY(5, 5) || mouseBoundsY(6, 6) || mouseBoundsY(7, 7) || mouseBoundsY(8, 8)));
}

void gameHandleMiniGridNavigation() {
    if (miniGridState > 0) {
        if (keyPressed(INPUT_LEFT)) {
            if (--miniGridCursorIndex_x < 0) {
                if (miniGridCursorIndex_y == 0) {
                    miniGridCursorIndex_x = 2;
                } else if (miniGridCursorIndex_x == -2) {
                    miniGridCursorIndex_x = 2;
                }
            }
            setGridCursorBySmallX();
        }
        if (keyPressed(INPUT_RIGHT)) {
            if (++miniGridCursorIndex_x > 2) {
                miniGridCursorIndex_x = -(miniGridCursorIndex_y != 0);
            }
            setGridCursorBySmallX();
        }
        if (keyPressed(INPUT_UP)) {
            if (--miniGridCursorIndex_y < 0 || (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1))
                miniGridCursorIndex_y = 2;
            setGridCursorBySmallY();
        }
        if (keyPressed(INPUT_DOWN)) {
            miniGridCursorIndex_y = (miniGridCursorIndex_y + 1) % 3;
            if (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1)
                miniGridCursorIndex_y = 1;
            setGridCursorBySmallY();
        }
        if (lastMiniGridState > 0) {
            if ((keyPressed(INPUT_BACK) || clickedOutsideMiniGrid())) {
                miniGridState = 0;
                if ((!keyPressed(INPUT_BACK)) || keyPressed(INPUT_BACK_ALT)) {
                  gameHandleMouseMovementMain();
                }
                setGridCursorByLargeX();
                setGridCursorByLargeY();
            }
            else if ((keyPressed(INPUT_CONFIRM) || clickedWithinMiniGrid())) {
                i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
                if (miniGridCursorIndex_x > -1) {
                    if (miniGridState == 1) {
                        setGridNum(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));
                    } else if (grid[i] == 0) {
                        setGridMiniNum(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));
                    }
                } else if (miniGridCursorIndex_y == 1) {
                    swapMiniGridState();
                } else {
                    setGridNum(i, 0);
                }
                if (keyPressed(INPUT_CONFIRM_ALT)) {
                    justClickedInMiniGrid = true;
                }
            }
        }
        if (keyPressed(INPUT_SWAP)) {
            swapMiniGridState();
        }
    }
}

void gameHandleMouseMovementMini() {
    if (miniGridState > 0) {
        temp_mouseIndex_x = -2;
        temp_mouseIndex_y = -2;
        if (mouseBoundsMiniX(-1, 2)) {
            if (mouseBoundsMiniX(-1, 0)) {
                if (mouseBoundsMiniX(-1, -1)) {
                    temp_mouseIndex_x = -1;
                } else if (mouseBoundsMiniX(0, 0)) {
                    temp_mouseIndex_x = 0;
                }
            } else if (mouseBoundsMiniX(1, 2)) {
                if (mouseBoundsMiniX(1, 1)) {
                    temp_mouseIndex_x = 1;
                } else if (mouseBoundsMiniX(2, 2)) {
                    temp_mouseIndex_x = 2;
                }
            }
        }
        if (mouseBoundsMiniY(0, 2)) {
            if (mouseBoundsMiniY(0, 0)) {
                temp_mouseIndex_y = 0;
            } else if (mouseBoundsMiniY(1, 1)) {
                temp_mouseIndex_y = 1;
            } else if (mouseBoundsMiniY(2, 2)) {
                temp_mouseIndex_y = 2;
            }
        }
        if (temp_mouseIndex_x > -2 && temp_mouseIndex_y > -2
                && !(temp_mouseIndex_x == -1 && temp_mouseIndex_y == 0)) {
            miniGridCursorIndex_x = temp_mouseIndex_x;
            miniGridCursorIndex_y = temp_mouseIndex_y;
            setGridCursorBySmallX();
            setGridCursorBySmallY();
        }
    }
}

inline bool mouseBoundsMiniX(Sint8 start, Sint8 end) {
    return (mouseInput_x >= xAtMiniGridIndex(start) && (mouseInput_x < (xAtMiniGridIndex(end) + (gridSizeA3))));
}

inline bool mouseBoundsMiniY(Sint8 start, Sint8 end) {
    return (mouseInput_y >= yAtMiniGridIndex(start) && (mouseInput_y < (yAtMiniGridIndex(end) + (gridSizeA3))));
}

inline bool clickedWithinMiniGrid() {
    return (keyPressed(INPUT_CONFIRM_ALT) && mouseIsInsideGridSquareMini());
}

// easier to code/check than gameHandleMouseMovementMini()... but also less efficient
inline bool mouseIsInsideGridSquareMini() {
    return ((mouseBoundsMiniX(-1, -1) || mouseBoundsMiniX(0, 0) || mouseBoundsMiniX(1, 1) || mouseBoundsMiniX(2, 2)) &&
        (mouseBoundsMiniY(0, 0) || mouseBoundsMiniY(1, 1) || mouseBoundsMiniY(2, 2)) &&
        !(mouseBoundsMiniX(-1, -1) && mouseBoundsMiniY(0, 0)));
}

inline bool clickedOutsideMiniGrid() {
    return (keyPressed(INPUT_CONFIRM_ALT) && !(mouseBoundsMiniX(-1, 2) && mouseBoundsMiniY(0, 2)));
}

void setGridNum(Sint8 index, Sint8 num) {
    grid[index] = num;
    updateNumEmpty();
    checkForVictory();
    miniGridState = 0;
    setGridCursorByLargeX();
    setGridCursorByLargeY();
}

void gameHandleNumKeyPresses() {
    checkNumKeyPress(INPUT_NUM_0, 0);
    checkNumKeyPress(INPUT_NUM_1, 1);
    checkNumKeyPress(INPUT_NUM_2, 2);
    checkNumKeyPress(INPUT_NUM_3, 3);
    checkNumKeyPress(INPUT_NUM_4, 4);
    checkNumKeyPress(INPUT_NUM_5, 5);
    checkNumKeyPress(INPUT_NUM_6, 6);
    checkNumKeyPress(INPUT_NUM_7, 7);
    checkNumKeyPress(INPUT_NUM_8, 8);
    checkNumKeyPress(INPUT_NUM_9, 9);
}

void checkNumKeyPress(Uint32 key, Sint8 num) {
    if (keyPressed(key)) {
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
        if (miniGridState == 1) {
            setGridNum(i, num);
        } else if (grid[i] == 0) {
            setGridMiniNum(i, num);
        }
    }
}

inline void swapMiniGridState() {
  miniGridState = (miniGridState == 1) ? 2 : 1;
}

inline void setGridMiniNum(Sint8 index, Sint8 num) {
    miniGrid[index] ^= (1 << num);
}

void setGridCursorByLargeX() {
    gridCursor_bottom_left.rect.x = GRID_X_AT_COL(gridCursorIndex_x) - gridCursorCornerStep;
    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;
    gridCursor_bottom_right.rect.x = GRID_X_AT_COL(gridCursorIndex_x) + (Sint16)gridSizeA3 - (gridCursorCornerStep * 2);
    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;
}

void setGridCursorByLargeY() {
    gridCursor_bottom_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + (Sint16)gridSizeA3 - (gridCursorCornerStep * 2);
    gridCursor_top_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) - gridCursorCornerStep;
    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;
    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;
}

void gameHandleCheatRevealCell() {
    if ((keyPressed(INPUT_SWAP) || clickedInRect(&gameSidebarSmall1Rect)) && miniGridState == 0) {
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;
        if (originalGrid[i] == 0) {
            if (++cheat1Counter >= 8) {
                setGridNum(i, solutionGrid[i]);
                Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
                resetCheatCounters();
            }
        }
    } else if (keyPressed(INPUT_CONFIRM_ALT)) {
        cheat1Counter = 0;
    }
}

void gameHandleCheatClearIncorrectCells() {
    if (((keyPressed(INPUT_BACK)) || (keyPressed(INPUT_SWAP)) || clickedInRect(&gameSidebarSmall2Rect)) && miniGridState == 0) {
        if (clickedInRect(&gameSidebarSmall2Rect) || ((keyPressed(INPUT_BACK)) == (cheat2Counter % 2 == 0))) {
            if (++cheat2Counter >= 8) {
                for (i = 0; i < 81; i++) {
                    if (originalGrid[i] == 0 && grid[i] != solutionGrid[i]) {
                        grid[i] = 0;
                    }
                }
                Mix_PlayChannel(SFX_CHANNEL, sfx, 0);
                resetCheatCounters();
            }
        } else {
            cheat2Counter = 0;
        }
    } else if (keyPressed(INPUT_CONFIRM_ALT)) {
        cheat2Counter = 0;
    }
}

void gameHandleChangeSong() {
  if (keyPressed(INPUT_CONFIRM_ALT)) {
    if (clickedInRect(&gameSidebarSmall3Rect)) {
      if (++songChangeCounter >= 3) {
        if (++soundSettings.musicIndex > 8) {
          soundSettings.musicIndex = 1;
        }
        playMusicAtIndex(soundSettings.musicIndex);
        if (programState != 20) {
          saveCurrentSettings();
        }
        songChangeCounter = 0;
      }
      return;
    }
    songChangeCounter = 0;
  }
}

inline Sint16 xAtMiniGridIndex(Sint8 index) {
  return (Sint16)(miniGrid_shared_2.rect.x + gridSizeD + ((index + 1) * gridSizeA3) + ((index + 1) * gridSizeB));
}

inline Sint16 yAtMiniGridIndex(Sint8 index) {
  return (Sint16)(miniGrid_shared_2.rect.y + (index * gridSizeA3) + (index * gridSizeB));
}

void setGridCursorBySmallX() {
    gridCursor_bottom_left.rect.x = xAtMiniGridIndex(miniGridCursorIndex_x) - gridCursorCornerStep;
    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;
    gridCursor_bottom_right.rect.x = xAtMiniGridIndex(miniGridCursorIndex_x) + (Sint16)gridSizeA3 - (gridCursorCornerStep * 2);
    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;
}

void setGridCursorBySmallY() {
    gridCursor_bottom_left.rect.y = yAtMiniGridIndex(miniGridCursorIndex_y) + (Sint16)gridSizeA3 - (gridCursorCornerStep * 2);
    gridCursor_top_left.rect.y = yAtMiniGridIndex(miniGridCursorIndex_y) - gridCursorCornerStep;
    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;
    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;
}

void drawSidebar() {
  Sint16 pos_x_left_s1 = gameSidebarSmall1Rect.x + (gameSidebarSmall1Rect.w / 8) + fontForceOffset1;
  Sint16 pos_y_s1 = text_Time.rect.y + (gameSidebarSmall1Rect.h / 2) - fontSize;
  Sint16 pos_x_left_s2 = gameSidebarSmall2Rect.x + (gameSidebarSmall2Rect.w * 23 / 64) + fontForceOffset1;
  Sint16 pos_y_s2 = text_Empty.rect.y + (gameSidebarSmall2Rect.h / 2) - fontSize;
  // In SDL1, the y-coordinate gets reset to 0 if it's offscreen... for some reason
  SDL_Rect tempRect = gameSidebarSmall1Rect_2;
  SDL_RenderCopy(renderer, game_sidebar_small_2.texture, &game_sidebar_small_2.srcRect, &tempRect);
  SDL_RenderCopy(renderer, game_sidebar_small_3.texture, &game_sidebar_small_3.srcRect, &gameSidebarSmall1Rect_3);
  tempRect = gameSidebarSmall2Rect_2;
  SDL_RenderCopy(renderer, game_sidebar_small_2.texture, &game_sidebar_small_2.srcRect, &tempRect);
  SDL_RenderCopy(renderer, game_sidebar_small_3.texture, &game_sidebar_small_3.srcRect, &gameSidebarSmall2Rect_3);
  tempRect = gameSidebarSmall3Rect_2;
  SDL_RenderCopy(renderer, game_sidebar_small_2.texture, &game_sidebar_small_2.srcRect, &tempRect);
  SDL_RenderCopy(renderer, game_sidebar_small_3.texture, &game_sidebar_small_3.srcRect, &gameSidebarSmall3Rect_3);
  if (!compactDisplay) {
    SDL_RenderCopy(renderer, game_sidebar_small_1.texture, &game_sidebar_small_1.srcRect, &gameSidebarSmall1Rect_1);
    SDL_RenderCopy(renderer, game_sidebar_small_1.texture, &game_sidebar_small_1.srcRect, &gameSidebarSmall2Rect_1);
    SDL_RenderCopy(renderer, game_sidebar_small_1.texture, &game_sidebar_small_1.srcRect, &gameSidebarSmall3Rect_1);
  }
  i = 0;
  renderText(&text_Time);
  setAndRenderNumHelper((int(timer_game.now) / 600), pos_x_left_s1, pos_y_s1, 0);
  setAndRenderNumHelper(((int(timer_game.now) / 60) % 10), pos_x_left_s1, pos_y_s1, 0);
  setAndRenderColon(pos_x_left_s1, pos_y_s1);
  setAndRenderNumHelper(((int(timer_game.now) % 60) / 10), pos_x_left_s1, pos_y_s1, 0);
  setAndRenderNumHelper((int(timer_game.now) % 10), pos_x_left_s1, pos_y_s1, 0);
  i = 0;
  renderText(&text_Empty);
  setAndRenderNumHelper(int(numEmpty) / 10, pos_x_left_s2, pos_y_s2, 0);
  setAndRenderNumHelper(int(numEmpty) % 10, pos_x_left_s2, pos_y_s2, 0);
  switch (menuCursorIndex_play) {
  case 0:
    renderText(&text_Game_Easy);
    break;
  case 1:
    renderText(&text_Game_Normal);
    break;
  case 2:
    renderText(&text_Game_Hard);
    break;
  case 3:
    renderText(&text_Game_VHard);
    break;
  default:
    break;
  }
}