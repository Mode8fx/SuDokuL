#include "include.h"
#include "shared.h"

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define GAME_HANDLE_MAIN_GRID_NAVIGATION()                                                                                \
    if (miniGridState == 0) {                                                                                             \
        if (KEY_PRESSED(INPUT_LEFT)) {                                                                                    \
            if (--gridCursorIndex_x < 0)                                                                                  \
                gridCursorIndex_x = 8;                                                                                    \
            SET_GRID_CURSOR_BY_LARGE_X();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_RIGHT)) {                                                                                   \
            gridCursorIndex_x = (gridCursorIndex_x + 1) % 9;                                                              \
            SET_GRID_CURSOR_BY_LARGE_X();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_UP)) {                                                                                      \
            if (--gridCursorIndex_y < 0)                                                                                  \
                gridCursorIndex_y = 8;                                                                                    \
            SET_GRID_CURSOR_BY_LARGE_Y();                                                                                 \
        }                                                                                                                 \
        if (KEY_PRESSED(INPUT_DOWN)) {                                                                                    \
            gridCursorIndex_y = (gridCursorIndex_y + 1) % 9;                                                              \
            SET_GRID_CURSOR_BY_LARGE_Y();                                                                                 \
        }                                                                                                                 \
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x;                                                                  \
        if ((KEY_PRESSED(INPUT_CONFIRM) || CLICKED_WITHIN_GRID()) && originalGrid[i] == 0) {                              \
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
            SET_GRID_CURSOR_BY_SMALL_X();                                                                                 \
            SET_GRID_CURSOR_BY_SMALL_Y();                                                                                 \
        }                                                                                                                 \
    }

#define GAME_HANDLE_MOUSE_MOVEMENT_MAIN()                       \
    if (miniGridState == 0 && !justClickedInMiniGrid) {         \
        temp_mouseIndex_x = -1;                                 \
        temp_mouseIndex_y = -1;                                 \
        if (MOUSE_BOUNDS_X(0, 8)) {                             \
            if (MOUSE_BOUNDS_X(0, 2)) {                         \
                if (MOUSE_BOUNDS_X(0, 0)) {                     \
                    temp_mouseIndex_x = 0;                      \
                } else if (MOUSE_BOUNDS_X(1, 1)) {              \
                    temp_mouseIndex_x = 1;                      \
                } else if (MOUSE_BOUNDS_X(2, 2)) {              \
                    temp_mouseIndex_x = 2;                      \
                }                                               \
            } else if (MOUSE_BOUNDS_X(3, 5)) {                  \
                if (MOUSE_BOUNDS_X(3, 3)) {                     \
                    temp_mouseIndex_x = 3;                      \
                } else if (MOUSE_BOUNDS_X(4, 4)) {              \
                    temp_mouseIndex_x = 4;                      \
                } else if (MOUSE_BOUNDS_X(5, 5)) {              \
                    temp_mouseIndex_x = 5;                      \
                }                                               \
            } else if (MOUSE_BOUNDS_X(6, 8)) {                  \
                if (MOUSE_BOUNDS_X(6, 6)) {                     \
                    temp_mouseIndex_x = 6;                      \
                } else if (MOUSE_BOUNDS_X(7, 7)) {              \
                    temp_mouseIndex_x = 7;                      \
                } else if (MOUSE_BOUNDS_X(8, 8)) {              \
                    temp_mouseIndex_x = 8;                      \
                }                                               \
            }                                                   \
        }                                                       \
        if (MOUSE_BOUNDS_Y(0, 8)) {                             \
            if (MOUSE_BOUNDS_Y(0, 2)) {                         \
                if (MOUSE_BOUNDS_Y(0, 0)) {                     \
                    temp_mouseIndex_y = 0;                      \
                } else if (MOUSE_BOUNDS_Y(1, 1)) {              \
                    temp_mouseIndex_y = 1;                      \
                } else if (MOUSE_BOUNDS_Y(2, 2)) {              \
                    temp_mouseIndex_y = 2;                      \
                }                                               \
            } else if (MOUSE_BOUNDS_Y(3, 5)) {                  \
                if (MOUSE_BOUNDS_Y(3, 3)) {                     \
                    temp_mouseIndex_y = 3;                      \
                } else if (MOUSE_BOUNDS_Y(4, 4)) {              \
                    temp_mouseIndex_y = 4;                      \
                } else if (MOUSE_BOUNDS_Y(5, 5)) {              \
                    temp_mouseIndex_y = 5;                      \
                }                                               \
            } else if (MOUSE_BOUNDS_Y(6, 8)) {                  \
                if (MOUSE_BOUNDS_Y(6, 6)) {                     \
                    temp_mouseIndex_y = 6;                      \
                } else if (MOUSE_BOUNDS_Y(7, 7)) {              \
                    temp_mouseIndex_y = 7;                      \
                } else if (MOUSE_BOUNDS_Y(8, 8)) {              \
                    temp_mouseIndex_y = 8;                      \
                }                                               \
            }                                                   \
        }                                                       \
        if (temp_mouseIndex_x > -1 && temp_mouseIndex_y > -1) { \
            gridCursorIndex_x = temp_mouseIndex_x;              \
            gridCursorIndex_y = temp_mouseIndex_y;              \
            SET_GRID_CURSOR_BY_LARGE_X();                       \
            SET_GRID_CURSOR_BY_LARGE_Y();                       \
        }                                                       \
    }

#define MOUSE_BOUNDS_X(start, end) \
    ((mouseInput_x >= GRID_X_AT_COL(start)) && (mouseInput_x < (GRID_X_AT_COL(end) + (GRID_SIZE_A3))))

#define MOUSE_BOUNDS_Y(start, end) \
    ((mouseInput_y >= GRID_Y_AT_ROW(start)) && (mouseInput_y < (GRID_Y_AT_ROW(end) + (GRID_SIZE_A3))))

#define CLICKED_WITHIN_GRID() \
    (KEY_PRESSED(INPUT_CONFIRM_ALT) && MOUSE_IS_INSIDE_GRID_SQUARE())

// easier to code/check than GAME_HANDLE_MOUSE_MOVEMENT_MAIN()... but also less efficient
#define MOUSE_IS_INSIDE_GRID_SQUARE() \
    ((MOUSE_BOUNDS_X(0,0) || MOUSE_BOUNDS_X(1,1) || MOUSE_BOUNDS_X(2,2) || MOUSE_BOUNDS_X(3,3) || MOUSE_BOUNDS_X(4,4) \
    || MOUSE_BOUNDS_X(5,5) || MOUSE_BOUNDS_X(6,6) || MOUSE_BOUNDS_X(7,7) || MOUSE_BOUNDS_X(8,8)) &&                   \
    (MOUSE_BOUNDS_Y(0,0) || MOUSE_BOUNDS_Y(1,1) || MOUSE_BOUNDS_Y(2,2) || MOUSE_BOUNDS_Y(3,3) || MOUSE_BOUNDS_Y(4,4)  \
    || MOUSE_BOUNDS_Y(5,5) || MOUSE_BOUNDS_Y(6,6) || MOUSE_BOUNDS_Y(7,7) || MOUSE_BOUNDS_Y(8,8)))

#define GAME_HANDLE_MINI_GRID_NAVIGATION()                                                                  \
    if (miniGridState > 0) {                                                                                \
        if (KEY_PRESSED(INPUT_LEFT)) {                                                                      \
            if (--miniGridCursorIndex_x < 0)                                                                \
                if (miniGridCursorIndex_y == 0) {                                                           \
                    miniGridCursorIndex_x = 2;                                                              \
                } else if (miniGridCursorIndex_x == -2) {                                                   \
                    miniGridCursorIndex_x = 2;                                                              \
                }                                                                                           \
            SET_GRID_CURSOR_BY_SMALL_X();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_RIGHT)) {                                                                     \
            if (++miniGridCursorIndex_x > 2) {                                                              \
                miniGridCursorIndex_x = -(miniGridCursorIndex_y != 0);                                      \
            }                                                                                               \
            SET_GRID_CURSOR_BY_SMALL_X();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_UP)) {                                                                        \
            if (--miniGridCursorIndex_y < 0 || (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1)) \
                miniGridCursorIndex_y = 2;                                                                  \
            SET_GRID_CURSOR_BY_SMALL_Y();                                                                   \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_DOWN)) {                                                                      \
            miniGridCursorIndex_y = (miniGridCursorIndex_y + 1) % 3;                                        \
            if (miniGridCursorIndex_y == 0 && miniGridCursorIndex_x == -1)                                  \
                miniGridCursorIndex_y = 1;                                                                  \
            SET_GRID_CURSOR_BY_SMALL_Y();                                                                   \
        }                                                                                                   \
        if (lastMiniGridState > 0) {                                                                        \
            if ((KEY_PRESSED(INPUT_BACK) || CLICKED_OUTSIDE_MINI_GRID())) {                                 \
                miniGridState = 0;                                                                          \
                SET_GRID_CURSOR_BY_LARGE_X();                                                               \
                SET_GRID_CURSOR_BY_LARGE_Y();                                                               \
                GAME_HANDLE_MOUSE_MOVEMENT_MAIN();                                                          \
            }                                                                                               \
            if ((KEY_PRESSED(INPUT_CONFIRM) || CLICKED_WITHIN_MINI_GRID())) {                               \
                i = (gridCursorIndex_y * 9) + gridCursorIndex_x;                                            \
                if (miniGridCursorIndex_x > -1) {                                                           \
                    if (miniGridState == 1) {                                                               \
                        SET_GRID_NUM(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));         \
                    } else if (grid[i] == 0) {                                                              \
                        SET_GRID_MINI_NUM(i, ((miniGridCursorIndex_y * 3) + miniGridCursorIndex_x + 1));    \
                    }                                                                                       \
                } else if (miniGridCursorIndex_y == 1) {                                                    \
                    SWAP_MINI_GRID_STATE();                                                                 \
                } else {                                                                                    \
                    SET_GRID_NUM(i, 0);                                                                     \
                }                                                                                           \
                if (KEY_PRESSED(INPUT_CONFIRM_ALT)) {                                                       \
                    justClickedInMiniGrid = true;                                                           \
                }                                                                                           \
            }                                                                                               \
        }                                                                                                   \
        if (KEY_PRESSED(INPUT_SWAP)) {                                                                      \
            SWAP_MINI_GRID_STATE();                                                                         \
        }                                                                                                   \
    }

#define GAME_HANDLE_MOUSE_MOVEMENT_MINI()                                  \
    if (miniGridState > 0) {                                               \
        temp_mouseIndex_x = -2;                                            \
        temp_mouseIndex_y = -2;                                            \
        if (MOUSE_BOUNDS_MINI_X(-1, 2)) {                                  \
            if (MOUSE_BOUNDS_MINI_X(-1, 0)) {                              \
                if (MOUSE_BOUNDS_MINI_X(-1, -1)) {                         \
                    temp_mouseIndex_x = -1;                                \
                } else if (MOUSE_BOUNDS_MINI_X(0, 0)) {                    \
                    temp_mouseIndex_x = 0;                                 \
                }                                                          \
            } else if (MOUSE_BOUNDS_MINI_X(1, 2)) {                        \
                if (MOUSE_BOUNDS_MINI_X(1, 1)) {                           \
                    temp_mouseIndex_x = 1;                                 \
                } else if (MOUSE_BOUNDS_MINI_X(2, 2)) {                    \
                    temp_mouseIndex_x = 2;                                 \
                }                                                          \
            }                                                              \
        }                                                                  \
        if (MOUSE_BOUNDS_MINI_Y(0, 2)) {                                   \
            if (MOUSE_BOUNDS_MINI_Y(0, 0)) {                               \
                temp_mouseIndex_y = 0;                                     \
            } else if (MOUSE_BOUNDS_MINI_Y(1, 1)) {                        \
                temp_mouseIndex_y = 1;                                     \
            } else if (MOUSE_BOUNDS_MINI_Y(2, 2)) {                        \
                temp_mouseIndex_y = 2;                                     \
            }                                                              \
        }                                                                  \
        if (temp_mouseIndex_x > -2 && temp_mouseIndex_y > -2               \
                && !(temp_mouseIndex_x == -1 && temp_mouseIndex_y == 0)) { \
            miniGridCursorIndex_x = temp_mouseIndex_x;                     \
            miniGridCursorIndex_y = temp_mouseIndex_y;                     \
            SET_GRID_CURSOR_BY_SMALL_X();                                  \
            SET_GRID_CURSOR_BY_SMALL_Y();                                  \
        }                                                                  \
    }

#define MOUSE_BOUNDS_MINI_X(start, end) \
    (mouseInput_x >= X_AT_MINI_GRID_INDEX(start) && (mouseInput_x < (X_AT_MINI_GRID_INDEX(end) + (GRID_SIZE_A3))))

#define MOUSE_BOUNDS_MINI_Y(start, end) \
    (mouseInput_y >= Y_AT_MINI_GRID_INDEX(start) && (mouseInput_y < (Y_AT_MINI_GRID_INDEX(end) + (GRID_SIZE_A3))))

#define CLICKED_WITHIN_MINI_GRID() \
    (KEY_PRESSED(INPUT_CONFIRM_ALT) && MOUSE_IS_INSIDE_GRID_SQUARE_MINI())

// easier to code/check than GAME_HANDLE_MOUSE_MOVEMENT_MINI()... but also less efficient
#define MOUSE_IS_INSIDE_GRID_SQUARE_MINI() \
    ((MOUSE_BOUNDS_MINI_X(-1,-1) || MOUSE_BOUNDS_MINI_X(0,0) || MOUSE_BOUNDS_MINI_X(1,1) || MOUSE_BOUNDS_MINI_X(2,2)) && \
    (MOUSE_BOUNDS_MINI_Y(0,0) || MOUSE_BOUNDS_MINI_Y(1,1) || MOUSE_BOUNDS_MINI_Y(2,2)) && \
    !(MOUSE_BOUNDS_MINI_X(-1,-1) && MOUSE_BOUNDS_MINI_Y(0,0)))

#define CLICKED_OUTSIDE_MINI_GRID() \
    (KEY_PRESSED(INPUT_CONFIRM_ALT) && !(MOUSE_BOUNDS_MINI_X(-1,2) && MOUSE_BOUNDS_MINI_Y(0,2)))

#define SET_GRID_NUM(index, num)  \
    grid[index] = num;            \
    UPDATE_NUM_EMPTY();           \
    CHECK_FOR_VICTORY();          \
    miniGridState = 0;            \
    SET_GRID_CURSOR_BY_LARGE_X(); \
    SET_GRID_CURSOR_BY_LARGE_Y();

#define GAME_HANDLE_NUM_KEY_PRESSES()    \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_0, 0); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_1, 1); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_2, 2); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_3, 3); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_4, 4); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_5, 5); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_6, 6); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_7, 7); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_8, 8); \
    CHECK_NUM_KEY_PRESS(INPUT_NUM_9, 9); \

#define CHECK_NUM_KEY_PRESS(key, num)                    \
    if (KEY_PRESSED(key)) {                              \
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x; \
        if (miniGridState == 1) {                        \
            SET_GRID_NUM(i, num);                        \
        } else if (grid[i] == 0) {                       \
            SET_GRID_MINI_NUM(i, num);                   \
        }                                                \
    }

#define SWAP_MINI_GRID_STATE() \
    if (miniGridState == 1) {  \
        miniGridState = 2;     \
    } else {                   \
        miniGridState = 1;     \
    }

#define SET_GRID_MINI_NUM(index, num) \
    miniGrid[index] ^= (1 << num);

#define SET_GRID_CURSOR_BY_LARGE_X()                                                                               \
    gridCursor_bottom_left.rect.x = GRID_X_AT_COL(gridCursorIndex_x) - gridCursorCornerStep;                       \
    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;                                                    \
    gridCursor_bottom_right.rect.x = GRID_X_AT_COL(gridCursorIndex_x) + GRID_SIZE_A3 - (gridCursorCornerStep * 3); \
    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;

#define SET_GRID_CURSOR_BY_LARGE_Y()                                                                               \
    gridCursor_bottom_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);  \
    gridCursor_top_left.rect.y = GRID_Y_AT_ROW(gridCursorIndex_y) - gridCursorCornerStep;                          \
    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;                                                \
    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;

#define SET_GRID_CURSOR_BY_SMALL_X() \
    gridCursor_bottom_left.rect.x = X_AT_MINI_GRID_INDEX(miniGridCursorIndex_x) - gridCursorCornerStep;                       \
    gridCursor_top_left.rect.x = gridCursor_bottom_left.rect.x;                                                               \
    gridCursor_bottom_right.rect.x = X_AT_MINI_GRID_INDEX(miniGridCursorIndex_x) + GRID_SIZE_A3 - (gridCursorCornerStep * 3); \
    gridCursor_top_right.rect.x = gridCursor_bottom_right.rect.x;

#define SET_GRID_CURSOR_BY_SMALL_Y()                                                                                          \
    gridCursor_bottom_left.rect.y = Y_AT_MINI_GRID_INDEX(miniGridCursorIndex_y) + GRID_SIZE_A3 - (gridCursorCornerStep * 3);  \
    gridCursor_top_left.rect.y = Y_AT_MINI_GRID_INDEX(miniGridCursorIndex_y) - gridCursorCornerStep;                          \
    gridCursor_bottom_right.rect.y = gridCursor_bottom_left.rect.y;                                                           \
    gridCursor_top_right.rect.y = gridCursor_top_left.rect.y;

#define X_AT_MINI_GRID_INDEX(index) \
    (currMiniGrid->rect.x + (GRID_SIZE_D * 3) + ((index + 1) * GRID_SIZE_A3) + ((index + 1) * GRID_SIZE_B))

#define Y_AT_MINI_GRID_INDEX(index) \
    (currMiniGrid->rect.y + (GRID_SIZE_D * 3) + (index * GRID_SIZE_A3) + (index * GRID_SIZE_B))

#define GAME_HANDLE_CHEAT_REVEAL_CELL()                  \
    if (KEY_PRESSED(INPUT_SWAP) && miniGridState == 0) { \
        i = (gridCursorIndex_y * 9) + gridCursorIndex_x; \
        if (originalGrid[i] == 0) {                      \
            if (++cheatCounter >= 8) {                   \
                Mix_PlayChannel(SFX_CHANNEL, sfx, 0);    \
                SET_GRID_NUM(i, solutionGrid[i]);        \
                cheatCounter = 0;                        \
            }                                            \
        }                                                \
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