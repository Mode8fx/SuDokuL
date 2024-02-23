#include "include.h"
#include "shared.h"

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

extern Sint8 gridCursorIndex_x;
extern Sint8 gridCursorIndex_y;
extern Sint8 miniGridCursorIndex_x;
extern Sint8 miniGridCursorIndex_y;
extern Sint8 miniGridState;
extern Uint16 gridCursorCornerStep;

//extern void GAME_HANDLE_MAIN_GRID_NAVIGATION();
//extern void GAME_HANDLE_MOUSE_MOVEMENT_MAIN();
extern bool mouseBoundsX(Sint8, Sint8);
extern bool mouseBoundsY(Sint8, Sint8);
extern bool clickedWithinGrid();
extern bool mouseIsInsideGridSquare();
//extern void GAME_HANDLE_MINI_GRID_NAVIGATION();
//extern void GAME_HANDLE_MOUSE_MOVEMENT_MINI();
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
//extern void DRAW_SIDEBAR();

#define GAME_HANDLE_MAIN_GRID_NAVIGATION()                                                                                \
    if (miniGridState == 0) {                                                                                             \
        if (KEY_PRESSED(INPUT_LEFT)) {                                                                                    \
            if (--gridCursorIndex_x < 0)                                                                                  \
                gridCursorIndex_x = 8;                                                                                    \
            setGridCursorByLargeX();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_RIGHT)) {                                                                                   \
            gridCursorIndex_x = (gridCursorIndex_x + 1) % 9;                                                              \
            setGridCursorByLargeX();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_UP)) {                                                                                      \
            if (--gridCursorIndex_y < 0)                                                                                  \
                gridCursorIndex_y = 8;                                                                                    \
            setGridCursorByLargeY();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_DOWN)) {                                                                                    \
            gridCursorIndex_y = (gridCursorIndex_y + 1) % 9;                                                              \
            setGridCursorByLargeY();                                                                                 \
        }                                                                                                                 \
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;                                                                  \
        if ((KEY_PRESSED(INPUT_CONFIRM) || clickedWithinGrid()) && originalGrid[i] == 0) {                              \
            if (gridCursorIndex_x < 4) {                                                                                  \
                 if (gridCursorIndex_y < 4) {                                                                             \
                    currMiniGrid = &miniGrid_top_left;                                                                    \
                    currMiniGrid->rect.x = GRID_X_AT_COL(gridCursorIndex_x) + (GRID_SIZE_A * 1.5);                        \
                    currMiniGrid->rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + (GRID_SIZE_A * 2.5);                        \
                 } else {                                                                                                 \
                    currMiniGrid = &miniGrid_bottom_left;                                                                 \
                    currMiniGrid->rect.x = GRID_X_AT_COL(gridCursorIndex_x) + (GRID_SIZE_A * 1.5);                        \
                    currMiniGrid->rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + (GRID_SIZE_A * 0.5) - currMiniGrid->rect.h; \
                 }                                                                                                        \
            } else {                                                                                                      \
                if (gridCursorIndex_y < 4) {                                                                              \
                    currMiniGrid = &miniGrid_top_right;                                                                   \
                    currMiniGrid->rect.x = GRID_X_AT_COL(gridCursorIndex_x) + (GRID_SIZE_A * 1.5) - currMiniGrid->rect.w; \
                    currMiniGrid->rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + (GRID_SIZE_A * 2.5);                        \
                } else {                                                                                                  \
                    currMiniGrid = &miniGrid_bottom_right;                                                                \
                    currMiniGrid->rect.x = GRID_X_AT_COL(gridCursorIndex_x) + (GRID_SIZE_A * 1.5) - currMiniGrid->rect.w; \
                    currMiniGrid->rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + (GRID_SIZE_A * 0.5) - currMiniGrid->rect.h; \
                }                                                                                                         \
            }                                                                                                             \
            miniGridCursorIndex_x = max((grid[i] - 1) % 3, 0);                                                            \
            miniGridCursorIndex_y = (grid[i] - 1) / 3;                                                                    \
            miniGridState = 1;                                                                                            \
            setGridCursorBySmallX();                                                                                 \
            setGridCursorBySmallY();                                                                                 \
        }                                                                                                                 \
    }

#define GAME_HANDLE_MOUSE_MOVEMENT_MAIN()                       \
    if (miniGridState == 0 && !justClickedInMiniGrid) {         \
        temp_mouseIndex_x = -1;                                 \
        temp_mouseIndex_y = -1;                                 \
        if (mouseBoundsX(0, 8)) {                             \
            if (mouseBoundsX(0, 2)) {                         \
                if (mouseBoundsX(0, 0)) {                     \
                    temp_mouseIndex_x = 0;                      \
                } else if (mouseBoundsX(1, 1)) {              \
                    temp_mouseIndex_x = 1;                      \
                } else if (mouseBoundsX(2, 2)) {              \
                    temp_mouseIndex_x = 2;                      \
                }                                               \
            } else if (mouseBoundsX(3, 5)) {                  \
                if (mouseBoundsX(3, 3)) {                     \
                    temp_mouseIndex_x = 3;                      \
                } else if (mouseBoundsX(4, 4)) {              \
                    temp_mouseIndex_x = 4;                      \
                } else if (mouseBoundsX(5, 5)) {              \
                    temp_mouseIndex_x = 5;                      \
                }                                               \
            } else if (mouseBoundsX(6, 8)) {                  \
                if (mouseBoundsX(6, 6)) {                     \
                    temp_mouseIndex_x = 6;                      \
                } else if (mouseBoundsX(7, 7)) {              \
                    temp_mouseIndex_x = 7;                      \
                } else if (mouseBoundsX(8, 8)) {              \
                    temp_mouseIndex_x = 8;                      \
                }                                               \
            }                                                   \
        }                                                       \
        if (mouseBoundsY(0, 8)) {                             \
            if (mouseBoundsY(0, 2)) {                         \
                if (mouseBoundsY(0, 0)) {                     \
                    temp_mouseIndex_y = 0;                      \
                } else if (mouseBoundsY(1, 1)) {              \
                    temp_mouseIndex_y = 1;                      \
                } else if (mouseBoundsY(2, 2)) {              \
                    temp_mouseIndex_y = 2;                      \
                }                                               \
            } else if (mouseBoundsY(3, 5)) {                  \
                if (mouseBoundsY(3, 3)) {                     \
                    temp_mouseIndex_y = 3;                      \
                } else if (mouseBoundsY(4, 4)) {              \
                    temp_mouseIndex_y = 4;                      \
                } else if (mouseBoundsY(5, 5)) {              \
                    temp_mouseIndex_y = 5;                      \
                }                                               \
            } else if (mouseBoundsY(6, 8)) {                  \
                if (mouseBoundsY(6, 6)) {                     \
                    temp_mouseIndex_y = 6;                      \
                } else if (mouseBoundsY(7, 7)) {              \
                    temp_mouseIndex_y = 7;                      \
                } else if (mouseBoundsY(8, 8)) {              \
                    temp_mouseIndex_y = 8;                      \
                }                                               \
            }                                                   \
        }                                                       \
        if (temp_mouseIndex_x > -1 && temp_mouseIndex_y > -1) { \
            gridCursorIndex_x = temp_mouseIndex_x;              \
            gridCursorIndex_y = temp_mouseIndex_y;              \
            setGridCursorByLargeX();                       \
            setGridCursorByLargeY();                       \
        }                                                       \
    }

#define GAME_HANDLE_MINI_GRID_NAVIGATION()                                                                  \
    if (miniGridState > 0) {                                                                                \
        if (KEY_PRESSED(INPUT_LEFT)) {                                                                      \
            if (--miniGridCursorIndex_x < 0)                                                                \
                if (miniGridCursorIndex_y == 0) {                                                           \
                    miniGridCursorIndex_x = 2;                                                              \
                } else if (miniGridCursorIndex_x == -2) {                                                   \
                    miniGridCursorIndex_x = 2;                                                              \
                }                                                                                           \
            setGridCursorBySmallX();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_RIGHT)) {                                                                     \
            if (++miniGridCursorIndex_x > 2) {                                                              \
                miniGridCursorIndex_x = -(miniGridCursorIndex_y != 0);                                      \
            }                                                                                               \
            setGridCursorBySmallX();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_UP)) {                                                                        \
            if (--miniGridCursorIndex_y < 0 || (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1)) \
                miniGridCursorIndex_y = 2;                                                                  \
            setGridCursorBySmallY();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_DOWN)) {                                                                      \
            miniGridCursorIndex_y = (miniGridCursorIndex_y + 1) % 3;                                        \
            if (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1)                                  \
                miniGridCursorIndex_y = 1;                                                                  \
            setGridCursorBySmallY();                                                                   \
        }                                                                                                   \
        if (lastMiniGridState > 0) {                                                                        \
            if ((KEY_PRESSED(INPUT_BACK) || clickedOutsideMiniGrid())) {                                 \
                miniGridState = 0;                                                                          \
                setGridCursorByLargeX();                                                               \
                setGridCursorByLargeY();                                                               \
            }                                                                                               \
            if ((KEY_PRESSED(INPUT_CONFIRM) || clickedWithinMiniGrid())) {                               \
                i = (gridCursorIndex_y * 9) + gridCursorIndex_x;                                            \
                if (miniGridCursorIndex_x > -1) {                                                           \
                    if (miniGridState == 1) {                                                               \
                        setGridNum(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));         \
                    } else if (grid[i] == 0) {                                                              \
                        setGridMiniNum(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));    \
                    }                                                                                       \
                } else if (miniGridCursorIndex_y == 1) {                                                    \
                    swapMiniGridState();                                                                 \
                } else {                                                                                    \
                    setGridNum(i, 0);                                                                     \
                }                                                                                           \
                if (KEY_PRESSED(INPUT_CONFIRM_ALT)) {                                                       \
                    justClickedInMiniGrid = true;                                                           \
                }                                                                                           \
            }                                                                                               \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_SWAP)) {                                                                      \
            swapMiniGridState();                                                                         \
        }                                                                                                   \
    }

#define GAME_HANDLE_MOUSE_MOVEMENT_MINI()                                  \
    if (miniGridState > 0) {                                               \
        temp_mouseIndex_x = -2;                                            \
        temp_mouseIndex_y = -2;                                            \
        if (mouseBoundsMiniX(-1, 2)) {                                  \
            if (mouseBoundsMiniX(-1, 0)) {                              \
                if (mouseBoundsMiniX(-1, -1)) {                         \
                    temp_mouseIndex_x = -1;                                \
                } else if (mouseBoundsMiniX(0, 0)) {                    \
                    temp_mouseIndex_x = 0;                                 \
                }                                                          \
            } else if (mouseBoundsMiniX(1, 2)) {                        \
                if (mouseBoundsMiniX(1, 1)) {                           \
                    temp_mouseIndex_x = 1;                                 \
                } else if (mouseBoundsMiniX(2, 2)) {                    \
                    temp_mouseIndex_x = 2;                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
        if (mouseBoundsMiniY(0, 2)) {                                   \
            if (mouseBoundsMiniY(0, 0)) {                               \
                temp_mouseIndex_y = 0;                                     \
            } else if (mouseBoundsMiniY(1, 1)) {                        \
                temp_mouseIndex_y = 1;                                     \
            } else if (mouseBoundsMiniY(2, 2)) {                        \
                temp_mouseIndex_y = 2;                                     \
            }                                                              \
        }                                                                  \
        if (temp_mouseIndex_x > -2 && temp_mouseIndex_y > -2               \
                && !(temp_mouseIndex_x == -1 && temp_mouseIndex_y == 0)) { \
            miniGridCursorIndex_x = temp_mouseIndex_x;                     \
            miniGridCursorIndex_y = temp_mouseIndex_y;                     \
            setGridCursorBySmallX();                                  \
            setGridCursorBySmallY();                                  \
        }                                                                  \
    }

#define DRAW_SIDEBAR()                                                                                                                                                \
    game_sidebar_small.rect.y = SIDEBAR_SMALL_1_POS_Y;                                                                                                                \
    SDL_RenderCopy(renderer, game_sidebar_small.texture, NULL, &game_sidebar_small.rect);                                                                             \
    RENDER_TEXT(text_Time);                                                                                                                                           \
    SET_AND_RENDER_TIMER(game_sidebar_small.rect.x + (game_sidebar_small.rect.w / 8), game_sidebar_small.rect.y + (game_sidebar_small.rect.h * 3 / 4) - FONT_SIZE);   \
    game_sidebar_small.rect.y = SIDEBAR_SMALL_2_POS_Y;                                                                                                                \
    SDL_RenderCopy(renderer, game_sidebar_small.texture, NULL, &game_sidebar_small.rect);                                                                             \
    RENDER_TEXT(text_Empty);                                                                                                                                          \
    RENDER_NUM_EMPTY(game_sidebar_small.rect.x + (game_sidebar_small.rect.w * 23 / 64), game_sidebar_small.rect.y + (game_sidebar_small.rect.h * 3 / 4) - FONT_SIZE); \
    game_sidebar_small.rect.y = SIDEBAR_SMALL_3_POS_Y;                                                                                                                \
    SDL_RenderCopy(renderer, game_sidebar_small.texture, NULL, &game_sidebar_small.rect);                                                                             \
    switch (menuCursorIndex_play) {                                                                                                                                   \
        case 0:                                                                                                                                                       \
            RENDER_TEXT(text_Game_Easy);                                                                                                                              \
            break;                                                                                                                                                    \
        case 1:                                                                                                                                                       \
            RENDER_TEXT(text_Game_Normal);                                                                                                                            \
            break;                                                                                                                                                    \
        case 2:                                                                                                                                                       \
            RENDER_TEXT(text_Game_Hard);                                                                                                                              \
            break;                                                                                                                                                    \
        case 3:                                                                                                                                                       \
            RENDER_TEXT(text_Game_VHard);                                                                                                                             \
            break;                                                                                                                                                    \
        default:                                                                                                                                                      \
            break;                                                                                                                                                    \
    }                                     

#endif