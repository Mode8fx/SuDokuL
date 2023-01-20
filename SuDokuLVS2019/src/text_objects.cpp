#include "text_objects.h"

void initStartingTextVariables() {
    fontSize = (max(gameHeight / 24, 8));
    gridNumSize = (GRID_SIZE_A * 3);
    text_pressStartAmplitude = (FONT_SIZE / 2);
    text_standardAmplitude = (FONT_SIZE / 10);
    text_menuChoice3 = (gameHeight * 5 / 8);
    text_menuChoice1 = (TEXT_PRESS_START_Y - (FONT_SIZE * 4));
    text_menuChoice2 = (TEXT_PRESS_START_Y - (FONT_SIZE * 2));
    text_menuChoice4 = (TEXT_PRESS_START_Y + (FONT_SIZE * 2));
    text_menuChoice5 = (TEXT_PRESS_START_Y + (FONT_SIZE * 4));
    text_videoWarning_Y = (TEXT_PRESS_START_Y + (FONT_SIZE * 5));
    text_midScreen_Y = ((gameHeight - FONT_SIZE) / 2);
    text_quitToMenu_Y = (TEXT_PAUSED_Y + (FONT_SIZE * 2.5));
    deepMenuCursorPosition_X = (gameWidth / 6);
    videoMenuNumPosition_X = (gameWidth * 3 / 5);
    backgroundMenuNumPosition_X = (gameWidth * 2 / 3);
}