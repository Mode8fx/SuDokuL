#include "text_objects.h"
#include "general.h"
#include "shared.h"
#include "window.h"
#include "sprite_objects.h"

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

void initTextObjectVals(TextObject *textObj) {
	textObj->rect.x = 0;
	textObj->rect.y = 0;
	textObj->rect.w = 0;
	textObj->rect.h = 0;
}

void adjustCharOutlineOffset(TextCharObject *arr, Uint8 c, float x, float y) {
    if (x > 0) {
        arr[c].outlineOffset_x += max((int)(x * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), 1);
    } else if (x < 0) {
        arr[c].outlineOffset_x += min((int)(x * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), -1);
    }
    if (y > 0) {
        arr[c].outlineOffset_y += max((int)(y * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), 1);
    } else if (y < 0) {
        arr[c].outlineOffset_y += min((int)(y * GAME_HEIGHT_MULT * arr[c].rect.h / FONT_SIZE), -1);
    }
}

void renderTextChar(TextCharObject *textObj) {
	SDL_RenderCopy(renderer, textObj->outline_texture, NULL, &textObj->outline_rect);
	SDL_RenderCopy(renderer, textObj->texture, NULL, &textObj->rect);
}

void renderText(TextObject *textObj) {
	STRCPY(tempCharArray, textObj->str.c_str());
	charWidthCounter = 0;
	for (charCounter = 0; charCounter < textObj->str.length(); charCounter++) {
		setTextPosX(&CHAR_AT_INDEX(charCounter), (textObj->rect.x + charWidthCounter), CHAR_AT_INDEX(charCounter).outlineOffset_x);
		setTextPosY(&CHAR_AT_INDEX(charCounter), textObj->rect.y, CHAR_AT_INDEX(charCounter).outlineOffset_y);
		renderTextChar(&textChars[tempCharArray[charCounter]]);
		charWidthCounter += CHAR_AT_INDEX(charCounter).rect.w;
	}
}

void renderTextLarge(TextObject *textObj) {
	STRCPY(tempCharArray, textObj->str.c_str());
	charWidthCounter = 0;
	for (charCounter = 0; charCounter < textObj->str.length(); charCounter++) {
		setTextPosX(&CHAR_AT_INDEX_LARGE(charCounter), (textObj->rect.x + charWidthCounter), CHAR_AT_INDEX_LARGE(charCounter).outlineOffset_x);
		setTextPosY(&CHAR_AT_INDEX_LARGE(charCounter), textObj->rect.y, CHAR_AT_INDEX_LARGE(charCounter).outlineOffset_y);
		renderTextChar(&textChars_large[tempCharArray[charCounter]]);
		charWidthCounter += CHAR_AT_INDEX_LARGE(charCounter).rect.w;
	}
}

void setTextPosX(TextCharObject *textObj, Sint16 pos_x, Sint8 offset) {
    textObj->rect.x = (pos_x);
    textObj->outline_rect.x = (pos_x) + (offset);
}

void setTextPosY(TextCharObject*textObj, Sint16 pos_y, Sint8 offset) {
    textObj->rect.y = (pos_y);
    textObj->outline_rect.y = (pos_y) + (offset);
}

void setTextCharWithOutline(const char *text, TTF_Font *font, SDL_Color text_color, SDL_Color outline_color, TextCharObject *textObj) {
	textObj->surface = TTF_RenderText_Solid(font, text, text_color);
	textObj->texture = SDL_CreateTextureFromSurface(renderer, textObj->surface);
	TTF_SizeText(font, text, &textObj->rect.w, &textObj->rect.h);
	setFontOutline(font, textObj);
	textObj->outline_surface = TTF_RenderText_Solid(font, text, outline_color);
	textObj->outline_texture = SDL_CreateTextureFromSurface(renderer, textObj->outline_surface);
	TTF_SizeText(font, text, &textObj->outline_rect.w, &textObj->outline_rect.h);
	TTF_SetFontOutline(font, 0);
	SDL_FreeSurface(textObj->surface);
	SDL_FreeSurface(textObj->outline_surface);
}

void setFontOutline(TTF_Font *font, TextCharObject *textObj) {
	TTF_SetFontOutline(font, max((textObj->rect.h / 10), int(ceil(GAME_HEIGHT_MULT))));
}

void setAndRenderNumHelper(Uint8 digit, Sint16 pos_x_left, Sint16 pos_y, float i_offset) {
	setTextPosX(&textChars[(digit + 48)], (pos_x_left + ((i + i_offset) * FONT_SIZE)), textChars[digit + 48].outlineOffset_x);
	i++;
	setTextPosY(&textChars[(digit + 48)], pos_y, textChars[digit + 48].outlineOffset_y);
	renderTextChar(&textChars[(digit + 48)]);
}

void setAndRenderNumThreeDigitCentered(Sint16 num, Sint16 pos_x_centered, Sint16 pos_y) {
    i = 0;
    if (num > 99) {
        j = num / 100;
        setAndRenderNumHelper(j, pos_x_centered, pos_y, 0);
        j = (num / 10) % 10;
        setAndRenderNumHelper(j, pos_x_centered, pos_y, 0);
        j = num % 10;
        setAndRenderNumHelper(j, pos_x_centered, pos_y, 0);
    } else if (num > 9) {
        j = num / 10;
        setAndRenderNumHelper(j, pos_x_centered, pos_y, 0.5);
        j = num % 10;
        setAndRenderNumHelper(j, pos_x_centered, pos_y, 0.5);
    } else {
        setAndRenderNumHelper(num, pos_x_centered, pos_y, 1);
    }
}

void setAndRenderNumResolution(Sint16 width, Sint16 height, Sint16 pos_x_left, Sint16 pos_y) {
    i = 0;
    if (width > 999) {
        setAndRenderNumHelper(width / 1000, pos_x_left, pos_y, 0);
    }
    setAndRenderNumHelper((width / 100) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper((width / 10) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(width % 10, pos_x_left, pos_y, 0);
    text_x.rect.x = pos_x_left + (i * FONT_SIZE);
    i++;
    text_x.rect.y = pos_y;
    renderText(&text_x);
    if (height > 999) {
        setAndRenderNumHelper(height / 1000, pos_x_left, pos_y, 0);
    }
    setAndRenderNumHelper((height / 100) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper((height / 10) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(height % 10, pos_x_left, pos_y, 0);
}

void setAndRenderNumAspectRatio4_3(Sint16 pos_x_left, Sint16 pos_y) {
    i = 0;
    setAndRenderNumHelper(4, pos_x_left, pos_y, 0);
    setAndRenderColon(pos_x_left, pos_y);
    setAndRenderNumHelper(3, pos_x_left, pos_y, 0);
}

void setAndRenderNumAspectRatio16_9(Sint16 pos_x_left, Sint16 pos_y) {
    i = 0;
    setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(6, pos_x_left, pos_y, 0);
    setAndRenderColon(pos_x_left, pos_y);
    setAndRenderNumHelper(9, pos_x_left, pos_y, 0);
}

void setAndRenderNumAspectRatio16_10(Sint16 pos_x_left, Sint16 pos_y) {
    i = 0;
    setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(6, pos_x_left, pos_y, 0);
    setAndRenderColon(pos_x_left, pos_y);
    setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(0, pos_x_left, pos_y, 0);
}

void setAndRenderNumAspectRatio21_9(Sint16 pos_x_left, Sint16 pos_y) {
    i = 0;
    setAndRenderNumHelper(2, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
    setAndRenderColon(pos_x_left, pos_y);
    setAndRenderNumHelper(9, pos_x_left, pos_y, 0);
}

void setAndRenderColon(Sint16 pos_x_left, Sint16 pos_y) {
	text_colon.rect.x = pos_x_left + (i * FONT_SIZE);
	i++;
	text_colon.rect.y = pos_y;
	renderText(&text_colon);
}

void setAndRenderNumGridMainNormal(TextCharObject *textNumsObj, Uint8 num, Sint8 index) {
	k = index / 9;
	setTextPosX(&textNumsObj[num], GRID_X_AT_COL(index % 9) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.w) / 2) + numOffset_large_x[k], textNumsObj[num].outlineOffset_x);
	setTextPosY(&textNumsObj[num], GRID_Y_AT_ROW(k) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.h) / 2) + numOffset_large_y[k], textNumsObj[num].outlineOffset_y);
	renderTextChar(&textNumsObj[num]);
}

void setAndRenderNumGridMainMini(TextCharObject *textNumsObj, Uint8 num, Sint8 index) {
    k = index / 9;
    setTextPosX(&textNumsObj[num], GRID_X_AT_COL(index % 9) + (((num - 1) % 3) * GRID_SIZE_A) + 1 + numOffset_small_x[k], textNumsObj[num].outlineOffset_x);
    setTextPosY(&textNumsObj[num], GRID_Y_AT_ROW(k) + (((num - 1) / 3) * GRID_SIZE_A) + numOffset_small_y[k], textNumsObj[num].outlineOffset_y);
    renderTextChar(&textNumsObj[num]);
}

void setAndRenderNumGridSubNormal(TextCharObject *textNumsObj, Uint8 num) {
    k = (num - 1) / 3;
    setTextPosX(&textNumsObj[num], currMiniGrid->rect.x + (GRID_SIZE_D * 3) + (((num - 1) % 3) + 1) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.w) / 2) + numOffset_large_x[k], textNumsObj[num].outlineOffset_x);
    setTextPosY(&textNumsObj[num], currMiniGrid->rect.y + (GRID_SIZE_D * 3) + k * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + ((GRID_SIZE_A3 - textNumsObj[num].outline_rect.h) / 2) + numOffset_large_y[k], textNumsObj[num].outlineOffset_y);
    renderTextChar(&textNumsObj[num]);
}

void setAndRenderNumGridSubMini(TextCharObject *textNumsObj, Uint8 num) {
    setTextPosX(&textNumsObj[num], currMiniGrid->rect.x + (GRID_SIZE_D * 3) + (((num - 1) % 3) + 1) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + GRID_SIZE_A, textNumsObj[num].outlineOffset_x);
    setTextPosY(&textNumsObj[num], currMiniGrid->rect.y + (GRID_SIZE_D * 3) + ((num - 1) / 3) * ((GRID_SIZE_A3) + (GRID_SIZE_B)) + GRID_SIZE_A, textNumsObj[num].outlineOffset_y);
    renderTextChar(&textNumsObj[num]);
}

void menuMoveTextRight(TextObject *textObj, double timer) {
	textObj->rect.x = (Uint16)(textObj->endPos_x - MOVE_FAST_THEN_DECELERATE(textObj->endPos_x - textObj->startPos_x, 1, timer));
}

void menuMoveTextLeft(TextObject *textObj, double timer) {
	textObj->rect.x = (Uint16)(textObj->startPos_x + MOVE_FAST_THEN_DECELERATE(textObj->endPos_x - textObj->startPos_x, 1, timer));
}

void menuMoveTextUp(TextObject *textObj, double timer) {
	textObj->rect.y = (Uint16)(textObj->endPos_y + MOVE_FAST_THEN_DECELERATE(textObj->startPos_y - textObj->endPos_y, 1, timer));
}

void menuMoveTextDown(TextObject *textObj, double timer) {
	textObj->rect.y = (Uint16)(textObj->startPos_y - MOVE_FAST_THEN_DECELERATE(textObj->startPos_y - textObj->endPos_y, 1, timer));
}

void destroyTextObjectTexture(TextCharObject *textObj) {
	SDL_DestroyTexture(textObj->texture);
	SDL_DestroyTexture(textObj->outline_texture);
}

void renderTestText() {
    //bgSettings.speedMult = 0;
    //renderText(&text_test_1);
    //renderText(&text_test_2);
    //renderText(&text_test_3);
    //renderText(&text_test_4);
    //renderText(&text_test_5);
    //renderText(&text_test_6);
    //renderText(&text_test_7);
    //renderText(&text_test_8);
}

void setControlsText() {
#if defined(WII_U)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	setSelectBtnText();
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(VITA)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	setSelectBtnText();
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(PSP)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	setSelectBtnText();
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(SWITCH)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	setSelectBtnText();
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(ANDROID)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (FONT_SIZE * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))      );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (FONT_SIZE * (CONTROLS_STEP *  3))                  );
	setSelectBtnText();
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                   );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#else
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (KB+M)",       text_Controls_1,     OBJ_TO_MID_SCREEN_X(text_Controls_1),                (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Arrow Keys/WASD",                text_Controls_2a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mouse",                          text_Controls_2b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Navigate",                       text_Controls_2c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Enter",                          text_Controls_3a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  5)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Left Click",                     text_Controls_3b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  5)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Confirm",                        text_Controls_3c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Backspace",                      text_Controls_4a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Right Click",                    text_Controls_4b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4b, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Back",                           text_Controls_4c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("-",                              text_Controls_5a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Prev. Song",                     text_Controls_5b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("=",                              text_Controls_6a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),    (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("Next Song",                      text_Controls_6b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("F",                              text_Controls_7a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7a, 0.3),    (FONT_SIZE * (CONTROLS_STEP * 13))                  ); \
	SET_TEXT_WITH_OUTLINE("Toggle",                         text_Controls_7b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 13)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Fullscreen",                     text_Controls_7c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c, 0.7),    (FONT_SIZE * (CONTROLS_STEP * 13)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(1/4)",                          text_Controls_P1,    (gameWidth - (text_Controls_P1.rect.w * 1.25)),      (gameHeight - (text_Controls_P1.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (KB+M)",              text_Controls_8,     OBJ_TO_MID_SCREEN_X(text_Controls_8),                (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Esc",                            text_Controls_9a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Pause",                          text_Controls_9b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),    (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("Q (while paused)",               text_Controls_10a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Quit to Menu",                   text_Controls_10b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("Numbers",                        text_Controls_11a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Input",                    text_Controls_11b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE(".",                              text_Controls_12a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3),   (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_12b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  9)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_12c,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7),   (FONT_SIZE * (CONTROLS_STEP *  9)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(2/4)",                          text_Controls_P2,    (gameWidth - (text_Controls_P2.rect.w * 1.25)),      (gameHeight - (text_Controls_P2.rect.h * 1.5))      ); \
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (CONTROLLER)", text_Controls_c_1,   OBJ_TO_MID_SCREEN_X(text_Controls_c_1),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("D-Pad",                          text_Controls_c_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_2a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	SET_TEXT_WITH_OUTLINE("A",                              text_Controls_c_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_3a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  5))                  ); \
	SET_TEXT_WITH_OUTLINE("B",                              text_Controls_c_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_4a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("L",                              text_Controls_c_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_5a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  9))                  ); \
	SET_TEXT_WITH_OUTLINE("R",                              text_Controls_c_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_6a, 0.3),  (FONT_SIZE * (CONTROLS_STEP * 11))                  ); \
	SET_TEXT_WITH_OUTLINE("(3/4)",                          text_Controls_c_P1,  (gameWidth - (text_Controls_c_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P1.rect.h * 1.5))    ); \
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (CONTROLLER)",        text_Controls_c_8,   OBJ_TO_MID_SCREEN_X(text_Controls_c_8),              (FONT_SIZE * (CONTROLS_STEP *  1))                  ); \
	SET_TEXT_WITH_OUTLINE("Start",                          text_Controls_c_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_9a, 0.3),  (FONT_SIZE * (CONTROLS_STEP *  3))                  ); \
	setSelectBtnText();                                                                                                                                                                   \
	SET_TEXT_WITH_OUTLINE("X / Y",                          text_Controls_c_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12a, 0.3), (FONT_SIZE * (CONTROLS_STEP *  7))                  ); \
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_c_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12b, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) - CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_c_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12c, 0.7), (FONT_SIZE * (CONTROLS_STEP *  7)) + CONTROLS_SPACER); \
	SET_TEXT_WITH_OUTLINE("(4/4)",                          text_Controls_c_P2,  (gameWidth - (text_Controls_c_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P2.rect.h * 1.5)));
#endif
}


void setSelectBtnText() {
#if defined (SWITCH)
    initTextObjectVals(&text_Controls_10a);
    if (gameWidth == 320 && gameHeight == 240) {
        SET_TEXT_WITH_OUTLINE_HELPER("- (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    } else {
        SET_TEXT_WITH_OUTLINE_HELPER("- (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    }
#elif defined(ANDROID)
    initTextObjectVals(&text_Controls_10a);
    if (gameWidth == 320 && gameHeight == 240) {
        SET_TEXT_WITH_OUTLINE_HELPER("Back (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    } else {
        SET_TEXT_WITH_OUTLINE_HELPER("Back (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    }
#elif defined(VITA) || defined(WII_U) || defined(PSP)
    initTextObjectVals(&text_Controls_10a);
    if (gameWidth == 320 && gameHeight == 240) {
        SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    } else {
        SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    }
#else
    initTextObjectVals(&text_Controls_c_10a);
    if (gameWidth == 320 && gameHeight == 240) {
        SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_c_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    } else {
        SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_c_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_10a, 0.3), (FONT_SIZE * (CONTROLS_STEP * 5)));
    }
#endif
}

void renderDividerBetweenY(TextObject *textObj1, TextObject *textObj2) {
#if !(defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID) || defined(PSP))
    divider.y = (textObj1->rect.y + textObj2->rect.y + FONT_SIZE - divider.h) / 2;
    SDL_RenderFillRect(renderer, &divider);
#endif
}

void renderControlsTextPage1() {
	renderTextLarge(&text_Controls_1);
	renderText(&text_Controls_2a);
	renderText(&text_Controls_2b);
	renderText(&text_Controls_2c);
    renderDividerBetweenY(&text_Controls_2c, &text_Controls_3c);
	renderText(&text_Controls_3a);
	renderText(&text_Controls_3b);
	renderText(&text_Controls_3c);
    renderDividerBetweenY(&text_Controls_3c, &text_Controls_4c);
	renderText(&text_Controls_4a);
	renderText(&text_Controls_4b);
	renderText(&text_Controls_4c);
    renderDividerBetweenY(&text_Controls_4c, &text_Controls_5b);
	renderText(&text_Controls_5a);
	renderText(&text_Controls_5b);
    renderDividerBetweenY(&text_Controls_5b, &text_Controls_6b);
	renderText(&text_Controls_6a);
	renderText(&text_Controls_6b);
    renderDividerBetweenY(&text_Controls_6b, &text_Controls_7a);
	renderText(&text_Controls_7a);
	renderText(&text_Controls_7b);
	renderText(&text_Controls_7c);
	renderText(&text_Controls_P1);
}

void renderControlsTextPage2() {
	renderTextLarge(&text_Controls_8);
	renderText(&text_Controls_9a);
	renderText(&text_Controls_9b);
    renderDividerBetweenY(&text_Controls_9a, &text_Controls_10a);
	renderText(&text_Controls_10a);
	renderText(&text_Controls_10b);
    renderDividerBetweenY(&text_Controls_10a, &text_Controls_11a);
	renderText(&text_Controls_11a);
	renderText(&text_Controls_11b);
    renderDividerBetweenY(&text_Controls_11a, &text_Controls_12a);
	renderText(&text_Controls_12a);
	renderText(&text_Controls_12b);
	renderText(&text_Controls_12c);
	renderText(&text_Controls_P2);
}

#if !defined(WII_U) && !defined(VITA) && !defined(SWITCH) && !defined(ANDROID) && !defined(PSP)
void renderControlsTextPage3() {
	renderTextLarge(&text_Controls_c_1);
	renderText(&text_Controls_c_2a);
	renderText(&text_Controls_2c);
    renderDividerBetweenY(&text_Controls_2c, &text_Controls_3c);
	renderText(&text_Controls_c_3a);
	renderText(&text_Controls_3c);
    renderDividerBetweenY(&text_Controls_3c, &text_Controls_4c);
	renderText(&text_Controls_c_4a);
	renderText(&text_Controls_4c);
    renderDividerBetweenY(&text_Controls_4c, &text_Controls_5b);
	renderText(&text_Controls_c_5a);
	renderText(&text_Controls_5b);
    renderDividerBetweenY(&text_Controls_5b, &text_Controls_6b);
	renderText(&text_Controls_c_6a);
	renderText(&text_Controls_6b);
	renderText(&text_Controls_c_P1);
}

void renderControlsTextPage4() {
	renderTextLarge(&text_Controls_c_8);
	renderText(&text_Controls_c_9a);
	renderText(&text_Controls_9b);
    renderDividerBetweenY(&text_Controls_c_9a, &text_Controls_c_10a);
    renderText(&text_Controls_c_10a);
	renderText(&text_Controls_10b);
    renderDividerBetweenY(&text_Controls_10a, &text_Controls_c_12a);
	renderText(&text_Controls_c_12a);
	renderText(&text_Controls_c_12b);
	renderText(&text_Controls_c_12c);
	renderText(&text_Controls_c_P2);
}
#endif

void setCreditsText() {
    SET_LARGE_TEXT_WITH_OUTLINE("CODING, DESIGN, AND ART", text_Credits_1, OBJ_TO_MID_SCREEN_X(text_Credits_1),              (FONT_SIZE * (CREDITS_STEP *    1))          );
    SET_TEXT_WITH_OUTLINE("Mode8fx",                    text_Credits_2,   OBJ_TO_MID_SCREEN_X(text_Credits_2),               (FONT_SIZE * (CREDITS_STEP *    5))          );
    SET_TEXT_WITH_OUTLINE("https://github.com/Mode8fx", text_Credits_3,   OBJ_TO_MID_SCREEN_X(text_Credits_3),               (FONT_SIZE * (CREDITS_STEP * 6.25))          );
	SET_TEXT_WITH_OUTLINE("(1/7)",                      text_Credits_P1,  (gameWidth - (text_Credits_P1.rect.w * 1.25)),     (gameHeight - (text_Credits_P1.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("MUSIC",                text_Credits_4,   OBJ_TO_MID_SCREEN_X(text_Credits_4),               (FONT_SIZE * (CREDITS_STEP *     1))         );
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5b, 0.25),  (FONT_SIZE * (CREDITS_STEP *   3.5))         );
    SET_TEXT_WITH_OUTLINE("\"Wonder Flow\"",            text_Credits_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5a, 0.75),  (FONT_SIZE * (CREDITS_STEP *   3.5))         );
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6b, 0.25),  (FONT_SIZE * (CREDITS_STEP *  4.75))         );
    SET_TEXT_WITH_OUTLINE("\"Sudoku Padawan\"",         text_Credits_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6a, 0.75),  (FONT_SIZE * (CREDITS_STEP *  4.75))         );
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_7b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7b, 0.25),  (FONT_SIZE * (CREDITS_STEP *     6))         );
    SET_TEXT_WITH_OUTLINE("\"Electroquest\"",           text_Credits_7a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7a, 0.75),  (FONT_SIZE * (CREDITS_STEP *     6))         );
    SET_TEXT_WITH_OUTLINE("Soundscape",                 text_Credits_8b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8b, 0.25),  (FONT_SIZE * (CREDITS_STEP *  7.25))         );
    SET_TEXT_WITH_OUTLINE("\"Main Menu\"",              text_Credits_8a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8a, 0.75),  (FONT_SIZE * (CREDITS_STEP *  7.25))         );
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9b, 0.25),  (FONT_SIZE * (CREDITS_STEP *   8.5))         );
    SET_TEXT_WITH_OUTLINE("\"Insomnia\"",               text_Credits_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9a, 0.75),  (FONT_SIZE * (CREDITS_STEP *   8.5))         );
    SET_TEXT_WITH_OUTLINE("Solon",                      text_Credits_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10b, 0.25), (FONT_SIZE * (CREDITS_STEP *  9.75))         );
    SET_TEXT_WITH_OUTLINE("\"Ontario\"",                text_Credits_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10a, 0.75), (FONT_SIZE * (CREDITS_STEP *  9.75))         );
    SET_TEXT_WITH_OUTLINE("Noiseless",                  text_Credits_11b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11b, 0.25), (FONT_SIZE * (CREDITS_STEP *    11))         );
    SET_TEXT_WITH_OUTLINE("\"Addiction\"",              text_Credits_11a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11a, 0.75), (FONT_SIZE * (CREDITS_STEP *    11))         );
    SET_TEXT_WITH_OUTLINE("All music obtained from modarchive.org", text_Credits_12, OBJ_TO_MID_SCREEN_X(text_Credits_12),   (FONT_SIZE * (CREDITS_STEP * 12.75))         );
	SET_TEXT_WITH_OUTLINE("(2/7)",                      text_Credits_P2,  (gameWidth - (text_Credits_P2.rect.w * 1.25)),     (gameHeight - (text_Credits_P2.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("LIBRARIES",            text_Credits_13,  OBJ_TO_MID_SCREEN_X(text_Credits_13),              (FONT_SIZE * (CREDITS_STEP *  1))            );
    SET_TEXT_WITH_OUTLINE("SDL2",                       text_Credits_14,  OBJ_TO_MID_SCREEN_X(text_Credits_14),              (FONT_SIZE * (CREDITS_STEP *  5))            );
    SET_TEXT_WITH_OUTLINE("SDL2_image",                 text_Credits_15,  OBJ_TO_MID_SCREEN_X(text_Credits_15),              (FONT_SIZE * (CREDITS_STEP *  7))            );
    SET_TEXT_WITH_OUTLINE("SDL2_ttf",                   text_Credits_16,  OBJ_TO_MID_SCREEN_X(text_Credits_16),              (FONT_SIZE * (CREDITS_STEP *  9))            );
    SET_TEXT_WITH_OUTLINE("SDL2_mixer",                 text_Credits_17,  OBJ_TO_MID_SCREEN_X(text_Credits_17),              (FONT_SIZE * (CREDITS_STEP * 11))            );
	SET_TEXT_WITH_OUTLINE("(3/7)",                      text_Credits_P3,  (gameWidth - (text_Credits_P3.rect.w * 1.25)),     (gameHeight - (text_Credits_P3.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("FONT",                 text_Credits_18,  OBJ_TO_MID_SCREEN_X(text_Credits_18),              (FONT_SIZE * (CREDITS_STEP *    1))          );
    SET_TEXT_WITH_OUTLINE("Commodore Pixelized v1.2",   text_Credits_19,  OBJ_TO_MID_SCREEN_X(text_Credits_19),              (FONT_SIZE * (CREDITS_STEP *    5))          );
    SET_TEXT_WITH_OUTLINE("by Devin Cook",              text_Credits_20,  OBJ_TO_MID_SCREEN_X(text_Credits_20),              (FONT_SIZE * (CREDITS_STEP * 6.25))          );
	SET_TEXT_WITH_OUTLINE("(4/7)",                      text_Credits_P4,  (gameWidth - (text_Credits_P4.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("SOUND EFFECTS",        text_Credits_21,  OBJ_TO_MID_SCREEN_X(text_Credits_21),              (FONT_SIZE * (CREDITS_STEP *    1))          );
    SET_TEXT_WITH_OUTLINE("Luke.RUSTLTD",               text_Credits_22,  OBJ_TO_MID_SCREEN_X(text_Credits_22),              (FONT_SIZE * (CREDITS_STEP *    5))          );
    SET_TEXT_WITH_OUTLINE("opengameart.org",            text_Credits_23,  OBJ_TO_MID_SCREEN_X(text_Credits_23),              (FONT_SIZE * (CREDITS_STEP * 6.25))          );
	SET_TEXT_WITH_OUTLINE("(5/7)",                      text_Credits_P5,  (gameWidth - (text_Credits_P5.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("THANKS FOR PLAYING!",  text_Credits_24,  OBJ_TO_MID_SCREEN_X(text_Credits_24),              (FONT_SIZE * (CREDITS_STEP *    1))          );
    SET_TEXT_WITH_OUTLINE("Here's a cheat...",          text_Credits_25,  OBJ_TO_MID_SCREEN_X(text_Credits_25),              (FONT_SIZE * (CREDITS_STEP *  3.5))          );
    SET_TEXT_WITH_OUTLINE("If you get stuck on a puzzle,", text_Credits_26, OBJ_TO_MID_SCREEN_X(text_Credits_26),            (FONT_SIZE * (CREDITS_STEP * 4.75))          );
    SET_TEXT_WITH_OUTLINE(CHEAT_TEXT,                   text_Credits_27,  OBJ_TO_MID_SCREEN_X(text_Credits_27),              (FONT_SIZE * (CREDITS_STEP *    6))          );
    SET_TEXT_WITH_OUTLINE("to reveal the highlighted cell.", text_Credits_28, OBJ_TO_MID_SCREEN_X(text_Credits_28),          (FONT_SIZE * (CREDITS_STEP * 7.25))          );
    SET_TEXT_WITH_OUTLINE("I hope you enjoy the game!", text_Credits_29,  OBJ_TO_MID_SCREEN_X(text_Credits_29),              (FONT_SIZE * (CREDITS_STEP *  8.5))          );
    SET_TEXT_WITH_OUTLINE("- Mode8fx",                  text_Credits_30,  OBJ_TO_MID_SCREEN_X(text_Credits_30),              (FONT_SIZE * (CREDITS_STEP *   11))          );
	SET_TEXT_WITH_OUTLINE("(6/7)",                      text_Credits_P6,  (gameWidth - (text_Credits_P6.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("WANT MORE?",           text_Credits_31,  OBJ_TO_MID_SCREEN_X(text_Credits_31),              (FONT_SIZE * (CREDITS_STEP *     1))         );
    SET_TEXT_WITH_OUTLINE("SuDokuL is available on:",   text_Credits_32,  OBJ_TO_MID_SCREEN_X(text_Credits_32),              (FONT_SIZE * (CREDITS_STEP *   3.5))         );
    SET_TEXT_WITH_OUTLINE("PC",                         text_Credits_33,  OBJ_TO_MID_SCREEN_X(text_Credits_33),              (FONT_SIZE * (CREDITS_STEP *  4.75))         );
    SET_TEXT_WITH_OUTLINE("Android",                    text_Credits_34,  OBJ_TO_MID_SCREEN_X(text_Credits_34),              (FONT_SIZE * (CREDITS_STEP *     6))         );
    SET_TEXT_WITH_OUTLINE("Switch",                     text_Credits_35,  OBJ_TO_MID_SCREEN_X(text_Credits_35),              (FONT_SIZE * (CREDITS_STEP *  7.25))         );
    SET_TEXT_WITH_OUTLINE("Wii U",                      text_Credits_36,  OBJ_TO_MID_SCREEN_X(text_Credits_36),              (FONT_SIZE * (CREDITS_STEP *   8.5))         );
    SET_TEXT_WITH_OUTLINE("Vita",                       text_Credits_37,  OBJ_TO_MID_SCREEN_X(text_Credits_37),              (FONT_SIZE * (CREDITS_STEP *  9.75))         );
    SET_TEXT_WITH_OUTLINE("PSP",                        text_Credits_38,  OBJ_TO_MID_SCREEN_X(text_Credits_38),              (FONT_SIZE * (CREDITS_STEP *    11))         );
    SET_TEXT_WITH_OUTLINE("https://github.com/Mode8fx/SuDokuL", text_Credits_39, OBJ_TO_MID_SCREEN_X(text_Credits_39),        (FONT_SIZE * (CREDITS_STEP * 12.75))        );
	SET_TEXT_WITH_OUTLINE("(7/7)",                      text_Credits_P7,  (gameWidth - (text_Credits_P7.rect.w * 1.25)),     (gameHeight - (text_Credits_P4.rect.h * 1.5)));
}

void renderCreditsTextPage1() {
    renderTextLarge(&text_Credits_1);
    renderText(&text_Credits_2);
    renderText(&text_Credits_3);
    renderText(&text_Credits_P1);
}

void renderCreditsTextPage2() {
    renderTextLarge(&text_Credits_4);
    renderText(&text_Credits_5a);
    renderText(&text_Credits_5b);
    // renderDividerBetweenY(text_Credits_5a, text_Credits_6a);
    renderText(&text_Credits_6a);
    renderText(&text_Credits_6b);
    // renderDividerBetweenY(text_Credits_6a, text_Credits_7a);
    renderText(&text_Credits_7a);
    renderText(&text_Credits_7b);
    // renderDividerBetweenY(text_Credits_7a, text_Credits_8a);
    renderText(&text_Credits_8a);
    renderText(&text_Credits_8b);
    // renderDividerBetweenY(text_Credits_8a, text_Credits_9a);
    renderText(&text_Credits_9a);
    renderText(&text_Credits_9b);
    // renderDividerBetweenY(text_Credits_9a, text_Credits_10a);
    renderText(&text_Credits_10a);
    renderText(&text_Credits_10b);
    // renderDividerBetweenY(text_Credits_10a, text_Credits_11a);
    renderText(&text_Credits_11a);
    renderText(&text_Credits_11b);
    renderText(&text_Credits_12);
    renderText(&text_Credits_P2);
}

void renderCreditsTextPage3() {
    renderTextLarge(&text_Credits_18);
    renderText(&text_Credits_19);
    renderText(&text_Credits_20);
    renderText(&text_Credits_P3);
}

void renderCreditsTextPage4() {
    renderTextLarge(&text_Credits_21);
    renderText(&text_Credits_22);
    renderText(&text_Credits_23);
    renderText(&text_Credits_P4);
}

void renderCreditsTextPage5() {
    renderTextLarge(&text_Credits_13);
    renderText(&text_Credits_14);
    renderText(&text_Credits_15);
    renderText(&text_Credits_16);
    renderText(&text_Credits_17);
    renderText(&text_Credits_P5);
}

void renderCreditsTextPage6() {
    renderTextLarge(&text_Credits_24);
    renderText(&text_Credits_25);
    renderText(&text_Credits_26);
    renderText(&text_Credits_27);
    renderText(&text_Credits_28);
    renderText(&text_Credits_29);
    renderText(&text_Credits_30);
    renderText(&text_Credits_P6);
}

void renderCreditsTextPage7() {
    renderTextLarge(&text_Credits_31);
    renderText(&text_Credits_32);
    renderText(&text_Credits_33);
    renderText(&text_Credits_34);
    renderText(&text_Credits_35);
    renderText(&text_Credits_36);
    renderText(&text_Credits_37);
    renderText(&text_Credits_38);
    renderText(&text_Credits_39);
    renderText(&text_Credits_P7);
}

void controlsSetConfirmBackPos() {
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID)
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)) - CONTROLS_SPACER;
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
    } else {
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5)) - CONTROLS_SPACER;
    }
#elif defined(PSP)
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5));
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
    } else {
        text_Controls_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
        text_Controls_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5));
    }
#else
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_c_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5));
        text_Controls_c_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
    } else {
        text_Controls_c_3a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 7));
        text_Controls_c_4a.rect.y = (FONT_SIZE * (CONTROLS_STEP * 5));
    }
#endif
}