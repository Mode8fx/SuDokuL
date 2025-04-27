#include "text_objects.h"
#include "general.h"
#include "shared.h"
#include "window.h"
#include "sprite_objects.h"

void initStartingTextVariables() {
	fontSize = (max(gameHeight / 24, 8));
	if (fontSize == 11) {
		fontSize = 10; // for PSP; 11 looks kinda jagged and weird compared to 10
		fontForceOffset1 = 3;
		fontForceOffset2 = 2;
	} else {
		fontForceOffset1 = 0;
		fontForceOffset2 = 0;
	}
	deepMenuCursorPosition_X = (gameWidth / 6);
	if (!compactDisplay) {
		controlsMenuCursorPosition_X = (gameWidth / 8);
	} else {
		controlsMenuCursorPosition_X = (gameWidth / 12);
	}
	videoMenuNumPosition_X = (gameWidth * 3 / 5);
	backgroundMenuNumPosition_X = (gameWidth * 2 / 3);
	text_pressStartAmplitude = (fontSize / 2);
	text_standardAmplitude = (fontSize / 10);
	text_menuChoice3 = (gameHeight * 5 / 8);
	text_menuChoice1 = (TEXT_PRESS_START_Y - (fontSize * 4));
	text_menuChoice2 = (TEXT_PRESS_START_Y - (fontSize * 2));
	text_menuChoice4 = (TEXT_PRESS_START_Y + (fontSize * 2));
	text_menuChoice5 = (TEXT_PRESS_START_Y + (fontSize * 4));
	text_midScreen_Y = ((gameHeight - fontSize) / 2);
	text_quitToMenu_Y = (Uint16)(TEXT_PAUSED_Y + (fontSize * 2.5));
}

void initTextObjectVals(TextObject *textObj) {
	textObj->rect.x = 0;
	textObj->rect.y = 0;
	textObj->rect.w = 0;
	textObj->rect.h = 0;
}

void initMenuOptionPositions(TextObject *textObj) {
	textObj->startPos_x = textObj->rect.x;
	textObj->startPos_y = textObj->rect.y;
	textObj->endPos_x = textObj->startPos_x + (gameWidth * 3 / 4);
	textObj->endPos_y = textObj->startPos_y - (gameWidth * 3 / 4);
}

void renderText(TextObject *textObj) {
	STRCPY(tempCharArray, textObj->str.c_str());
	Uint16 charWidthCounter = 0;
	for (Uint8 charCounter = 0; charCounter < textObj->str.length(); charCounter++) {
		setTextPosX(&CHAR_AT_INDEX(charCounter), (textObj->rect.x + charWidthCounter));
		setTextPosY(&CHAR_AT_INDEX(charCounter), textObj->rect.y);
		renderTextChar(&textChars[tempCharArray[charCounter]]);
		charWidthCounter += CHAR_AT_INDEX(charCounter).charWidth;
	}
}

void renderTextLarge(TextObject *textObj) {
	STRCPY(tempCharArray, textObj->str.c_str());
	Uint16 charWidthCounter = 0;
	for (Uint8 charCounter = 0; charCounter < textObj->str.length(); charCounter++) {
		setTextPosX(&CHAR_AT_INDEX_LARGE(charCounter), (textObj->rect.x + charWidthCounter));
		setTextPosY(&CHAR_AT_INDEX_LARGE(charCounter), textObj->rect.y);
		renderTextChar(&textChars_large[tempCharArray[charCounter]]);
		charWidthCounter += CHAR_AT_INDEX_LARGE(charCounter).charWidth;
	}
}

void setTextPosX(TextCharObject *textObj, Sint16 pos_x) {
    textObj->rect.x = pos_x;
}

void setTextPosY(TextCharObject*textObj, Sint16 pos_y) {
    textObj->rect.y = pos_y;
}

#if defined(PSP)

#define TTF_RENDERTEXT TTF_RenderText_Blended
void setTextCharWithOutline(const char *text, TTF_Font *font, SDL_Color text_color, SDL_Color outline_color, TextCharObject *textObj,
	Uint8 minOutlineSize, Sint8 outlineAddX, Sint8 outlineAddY, bool trim, bool keepSurface) {
	SDL_Surface* text_surface = TTF_RENDERTEXT(font, text, text_color);
	SDL_Surface* text_rgba = SDL_ConvertSurfaceFormat(text_surface, SDL_PIXELFORMAT_RGBA5551, 0);
	SDL_FreeSurface(text_surface);
	text_surface = text_rgba;
	textObj->charWidth = text_surface->w;
	textObj->charHeight = text_surface->h;

	int outline_size = setFontOutline(font, textObj, minOutlineSize);
	SDL_Surface *outline_surface = TTF_RENDERTEXT(font, text, outline_color);
	TTF_SetFontOutline(font, 0);
	textObj->outlineOffset_x = (Sint8)max((int)(outline_size * 0.5), 1) + outlineAddX;
	textObj->outlineOffset_y = (Sint8)max((int)(outline_size * 0.9), 1) + outlineAddY;

	SDL_Rect dstRect = { textObj->outlineOffset_x, textObj->outlineOffset_y, text_surface->w, text_surface->h };
	SDL_Surface *outline_rgba = SDL_ConvertSurfaceFormat(outline_surface, SDL_PIXELFORMAT_RGBA5551, 0);
	SDL_FreeSurface(outline_surface);
	outline_surface = outline_rgba;

	SDL_BlitSurface(text_surface, NULL, outline_surface, &dstRect);
	if (trim) {
		SDL_Surface *cropped = trimTransparentEdges(outline_surface);
		SDL_FreeSurface(outline_surface);
		outline_surface = cropped;
	}


	textObj->texture = SDL_CreateTextureFromSurface(renderer, outline_surface);
	textObj->rect.w = outline_surface->w;
	textObj->rect.h = outline_surface->h;

	if (keepSurface) {
		textObj->surface = outline_surface;
	} else {
		SDL_FreeSurface(outline_surface);
	}

	textObj->charOffset_x = (Sint8)(gridSizeA3 - textObj->rect.w) / 2;
	textObj->charOffset_y = (Sint8)(gridSizeA3 - textObj->rect.h) / 2;
	SDL_FreeSurface(text_surface);
}

#else

#define TTF_RENDERTEXT TTF_RenderText_Solid
#if defined(ANDROID)
#define PIXEL_FORMAT SDL_PIXELFORMAT_ABGR8888
#else
#define PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888
#endif
void setTextCharWithOutline(const char *text, TTF_Font *font, SDL_Color text_color, SDL_Color outline_color, TextCharObject *textObj,
	Uint8 minOutlineSize, Sint8 outlineAddX, Sint8 outlineAddY, bool trim, bool keepSurface) {
	SDL_Surface *text_surface = TTF_RENDERTEXT(font, text, text_color);
	textObj->charWidth = text_surface->w;
	textObj->charHeight = text_surface->h;

	int outline_size = setFontOutline(font, textObj, minOutlineSize);
	SDL_Surface *outline_surface = TTF_RENDERTEXT(font, text, outline_color);
	TTF_SetFontOutline(font, 0);
	textObj->outlineOffset_x = (Sint8)max((int)(outline_size * 0.5), 1) + outlineAddX;
	textObj->outlineOffset_y = (Sint8)max((int)(outline_size * 0.9), 1) + outlineAddY;

	SDL_Rect dstRect = { textObj->outlineOffset_x, textObj->outlineOffset_y, text_surface->w, text_surface->h };
#if !defined(SDL1)
	SDL_Surface *outline_rgba = SDL_ConvertSurfaceFormat(outline_surface, PIXEL_FORMAT, 0);
	SDL_FreeSurface(outline_surface);
	outline_surface = outline_rgba;

	SDL_BlitSurface(text_surface, NULL, outline_surface, &dstRect);
	if (trim) {
		SDL_Surface *cropped = trimTransparentEdges(outline_surface);
		SDL_FreeSurface(outline_surface);
		outline_surface = cropped;
	}

	textObj->texture = SDL_CreateTextureFromSurface(renderer, outline_surface);
	textObj->rect.w = outline_surface->w;
	textObj->rect.h = outline_surface->h;

	if (keepSurface) {
		textObj->surface = outline_surface;
	} else {
		SDL_FreeSurface(outline_surface);
	}
#else
	SDL_Surface *combined = SDL_CreateRGBSurface(0, outline_surface->w, outline_surface->h,
		32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	SDL_BlitSurface(outline_surface, NULL, combined, NULL);
	SDL_BlitSurface(text_surface, NULL, combined, &dstRect);

	if (trim) {
		SDL_SetAlpha(combined, 0, 0);
		SDL_Surface *cropped = trimTransparentEdges(combined);
		SDL_FreeSurface(combined);
		combined = cropped;
	}

	textObj->texture = combined;
	textObj->rect.w = combined->w;
	textObj->rect.h = combined->h;

	SDL_FreeSurface(outline_surface);
#endif

	textObj->charOffset_x = (Sint8)(gridSizeA3 - textObj->rect.w) / 2;
	textObj->charOffset_y = (Sint8)(gridSizeA3 - textObj->rect.h) / 2;
	SDL_FreeSurface(text_surface);
}

#endif

int setFontOutline(TTF_Font *font, TextCharObject *textObj, Uint8 minSize) {
	int size = max((textObj->charHeight / 10), max(int(ceil(gameHeightMult)), (int)minSize));
	TTF_SetFontOutline(font, size);
	return size;
}

static Uint8 getAlphaAt(SDL_Surface* surface, int x, int y) {
	Uint8 r, g, b, a;
	Uint8 *pixelAddr = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

	Uint32 pixelValue = 0;
	memcpy(&pixelValue, pixelAddr, surface->format->BytesPerPixel);
	SDL_GetRGBA(pixelValue, surface->format, &r, &g, &b, &a);
	return a;
}


SDL_Surface *trimTransparentEdges(SDL_Surface *src) {
	if (!src || !(src->format->Amask)) return SDL_ConvertSurface(src, src->format, 0);

	if (SDL_MUSTLOCK(src)) SDL_LockSurface(src);

	int w = src->w, h = src->h;
	int top = 0, bottom = h - 1, left = 0, right = w - 1;

	// Find top
	for (; top < h; ++top) {
		for (int x = 0; x < w; ++x) {
			if (getAlphaAt(src, x, top) != 0) goto foundTop;
		}
	}
foundTop:

	// Find bottom
	for (; bottom > top; --bottom) {
		for (int x = 0; x < w; ++x) {
			if (getAlphaAt(src, x, bottom) != 0) goto foundBottom;
		}
	}
foundBottom:

	// Find left
	for (; left < w; ++left) {
		for (int y = top; y <= bottom; ++y) {
			if (getAlphaAt(src, left, y) != 0) goto foundLeft;
		}
	}
foundLeft:

	// Find right
	for (; right > left; --right) {
		for (int y = top; y <= bottom; ++y) {
			if (getAlphaAt(src, right, y) != 0) goto foundRight;
		}
	}
foundRight:

	if (SDL_MUSTLOCK(src)) SDL_UnlockSurface(src);

	int new_w = right - left + 1;
	int new_h = bottom - top + 1;

	SDL_Rect crop = { left, top, new_w, new_h };
	SDL_Surface *trimmed = SDL_CreateRGBSurface(0, new_w, new_h,
		src->format->BitsPerPixel, src->format->Rmask, src->format->Gmask, src->format->Bmask, src->format->Amask);
	SDL_BlitSurface(src, &crop, trimmed, NULL);

	return trimmed;
}



void setAndRenderNumThreeDigitCentered(Sint16 num, Sint16 pos_x_centered, Sint16 pos_y) {
    i = 0;
    if (num > 99) {
        setAndRenderNumHelper(num / 100, pos_x_centered, pos_y, 0);
        setAndRenderNumHelper((num / 10) % 10, pos_x_centered, pos_y, 0);
        setAndRenderNumHelper(num % 10, pos_x_centered, pos_y, 0);
    } else if (num > 9) {
        setAndRenderNumHelper(num / 10, pos_x_centered, pos_y, 0.5);
        setAndRenderNumHelper(num % 10, pos_x_centered, pos_y, 0.5);
    } else {
        setAndRenderNumHelper((Sint8)num, pos_x_centered, pos_y, 1);
    }
}

void setAndRenderNumResolution(Sint16 width, Sint16 height, Sint16 pos_x_left, Sint16 pos_y) {
	if (width == 0) {
		switch (videoSettings.aspectRatioIndex) {
			case 1:
				renderText(&text_Native_4_3);
				break;
			case 2:
				renderText(&text_Native_16_9);
				break;
			case 3:
				renderText(&text_Native_16_10);
				break;
			case 4:
				renderText(&text_Native_1_1);
				break;
			default:
				renderText(&text_Native_Res);
				break;
		}
		return;
	}
    i = 0;
    if (width > 999) {
        setAndRenderNumHelper(width / 1000, pos_x_left, pos_y, 0);
    }
    setAndRenderNumHelper((width / 100) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper((width / 10) % 10, pos_x_left, pos_y, 0);
    setAndRenderNumHelper(width % 10, pos_x_left, pos_y, 0);
    text_x.rect.x = pos_x_left + (i * fontSize);
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

void renderAspectRatioChoice() {
	switch (videoSettings.aspectRatioIndex) {
		case 0:
			renderText(&text_Native_Aspect);
			break;
		case 1:
			setAndRenderNumAspectRatio4_3(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
			break;
		case 2:
			setAndRenderNumAspectRatio16_9(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
			break;
		case 3:
			setAndRenderNumAspectRatio16_10(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
			break;
		case 4:
			setAndRenderNumAspectRatio1_1(VIDEO_MENU_NUM_POSITION_X, TEXT_ASPECT_RATIO_Y);
			break;
		default:
			break;
	}
}

void renderFrameRateChoice() {
	switch (addon131Settings.frameRateIndex) {
		case 1:
			renderText(&text_Frame_Rate_20);
			break;
		case 2:
			renderText(&text_Frame_Rate_30);
			break;
		case 3:
			renderText(&text_Frame_Rate_40);
			break;
		case 4:
			renderText(&text_Frame_Rate_50);
			break;
		case 5:
			renderText(&text_Frame_Rate_60);
			break;
		default:
			renderText(&text_Frame_Rate_Uncapped);
			break;
	}
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

void setAndRenderNumAspectRatio1_1(Sint16 pos_x_left, Sint16 pos_y) {
	i = 0;
	setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
	setAndRenderColon(pos_x_left, pos_y);
	setAndRenderNumHelper(1, pos_x_left, pos_y, 0);
}

void setAndRenderNumGridMainNormal(TextCharObject *textNumsObj, Uint8 num, Sint8 index) {
	setTextPosX(&textNumsObj[num], GRID_X_AT_COL(index % 9) + textNumsObj[num].charOffset_x);
	setTextPosY(&textNumsObj[num], GRID_Y_AT_ROW(index / 9) + textNumsObj[num].charOffset_y);
	renderTextCharIgnoreOffset(&textNumsObj[num]);
}

void setAndRenderNumGridMainMini(TextCharObject *textNumsObj, Uint8 num, Sint8 index) {
	setTextPosX(&textNumsObj[num], GRID_X_AT_COL(index % 9) + (Sint16)(((num - 1) % 3) * gridSizeA) + static_cast<int>(gameHeightMult));
	setTextPosY(&textNumsObj[num], GRID_Y_AT_ROW(index / 9) + (Sint16)(((num - 1) / 3) * gridSizeA) + static_cast<int>(gameHeightMult));
	renderTextCharIgnoreOffset(&textNumsObj[num]);
}

void setAndRenderNumGridSubNormal(TextCharObject *textNumsObj, Uint8 num) {
	setTextPosX(&textNumsObj[num], miniGrid_shared_2.rect.x + (Sint16)(gridSizeD + (((num - 1) % 3) + 1) * gridSizeA3B + textNumsObj[num].charOffset_x));
	setTextPosY(&textNumsObj[num], miniGrid_shared_2.rect.y + (Sint16)(((num - 1) / 3) * gridSizeA3B + textNumsObj[num].charOffset_y));
	renderTextCharIgnoreOffset(&textNumsObj[num]);
}

void setAndRenderNumGridSubMini(TextCharObject *textNumsObj, Uint8 num) {
	setTextPosX(&textNumsObj[num], miniGrid_shared_2.rect.x + (Sint16)(gridSizeD + (((num - 1) % 3) + 1) * gridSizeA3B + gridSizeA) + 1);
	setTextPosY(&textNumsObj[num], miniGrid_shared_2.rect.y + (Sint16)(((num - 1) / 3) * gridSizeA3B + gridSizeA) + 1);
	renderTextCharIgnoreOffset(&textNumsObj[num]);
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
#if !defined(SDL1)
	SDL_DestroyTexture(textObj->texture);
#else
	SDL_FreeSurface(textObj->texture);
#endif
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
#if defined(WII_U) || defined(THREEDS)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP * 5))                  );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(VITA)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP * 5))                  );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(PSP)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("X",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("O",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)", text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP * 5))                  );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Square / Triangle",     text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(SWITCH)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("- (paused)",     text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP * 5))                   );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
	#elif defined(WII)
	// General
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Point Wiimote",         text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A / 2",                 text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B / 1",                 text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Home / R",              text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("+ / Start",             text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("- / Z",          text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(while paused)",        text_Controls_7b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("- (Wiimote)",           text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_7c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c,  0.3), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
	// Vertical
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Point Wiimote",         text_Controls_2b_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c_vertical, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b_vertical,  0,                                                 0                                                           );
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c_vertical, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b_vertical,  0,                                                 0                                                           );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c_vertical, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("1 / L",                 text_Controls_5a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b_vertical, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("2 / R",                 text_Controls_6a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a_vertical, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b_vertical, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a_vertical,  0,                                                 0                                                           );
	SET_TEXT_WITH_OUTLINE("+ / Start",             text_Controls_9a_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b_vertical, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a_vertical);
	SET_TEXT_WITH_OUTLINE_HELPER("- / Z",          text_Controls_10a_vertical, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a_vertical, 0.3), (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(while paused)",        text_Controls_7b_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b_vertical, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b_vertical, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b_vertical, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a_vertical, 0,                                                 0                                                           );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b_vertical, 0,                                                 0                                                           );
	SET_TEXT_WITH_OUTLINE("+ / - (Wiimote)",       text_Controls_12a_vertical, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a_vertical, 0.3), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("X / Y / Home",          text_Controls_7c_vertical,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c_vertical,  0.3),  (fontSize * (CONTROLS_STEP * 7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b_vertical, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b_vertical, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c_vertical, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c_vertical, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	// Horizontal
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  3)));
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b_horizontal,  0,  0                                                                                                            );
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c_horizontal, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("2 / A (GC/CC)",         text_Controls_3a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b_horizontal,  0,                                                 0                                                             );
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c_horizontal, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("1 / B (GC/CC)",         text_Controls_4a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b_horizontal,  0,                                                 0                                                             );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c_horizontal, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b_horizontal, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Home / R",              text_Controls_6a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b_horizontal, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a_horizontal,  0,                                                 0                                                             );
	SET_TEXT_WITH_OUTLINE("+ / Start",             text_Controls_9a_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b_horizontal, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a_horizontal);
	SET_TEXT_WITH_OUTLINE_HELPER("- / Z",          text_Controls_10a_horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a_horizontal, 0.3), (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(while paused)",        text_Controls_7b_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b_horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b_horizontal, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a_horizontal, 0,                                                 0                                                             );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b_horizontal, 0,                                                 0                                                             );
	SET_TEXT_WITH_OUTLINE("A / B (Wiimote)",       text_Controls_12a_horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a_horizontal, 0.3), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_7c_horizontal,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c_horizontal, 0.3),  (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b_horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b_horizontal, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c_horizontal, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c_horizontal, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	#elif defined(FUNKEY)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize* (CONTROLS_STEP * 1))                    );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b,  0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Select",         text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(paused)",              text_Controls_7b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                            0                                       );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_7c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(ANDROID)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Touch Screen",          text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Tap",                   text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("+",                     text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Back (paused)",  text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP * 5))                   );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5)));
#elif defined(PC)
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (KB+M)",       text_Controls_1,     OBJ_TO_MID_SCREEN_X(text_Controls_1),                (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Arrow Keys/WASD",                text_Controls_2a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),    (fontSize * (CONTROLS_STEP *  3)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mouse",                          text_Controls_2b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),    (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",                       text_Controls_2c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),    (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Enter",                          text_Controls_3a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),    (fontSize * (CONTROLS_STEP *  5)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Left Click",                     text_Controls_3b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),    (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",                        text_Controls_3c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),    (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("Backspace",                      text_Controls_4a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),    (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Right Click",                    text_Controls_4b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4b, 0.3),    (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Back",                           text_Controls_4c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),    (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("-",                              text_Controls_5a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),    (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",                     text_Controls_5b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),    (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("=",                              text_Controls_6a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),    (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",                      text_Controls_6b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),    (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("F11",                            text_Controls_7a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7a, 0.3),    (fontSize * (CONTROLS_STEP * 13))                  );
	SET_TEXT_WITH_OUTLINE("Toggle",                         text_Controls_7b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7b, 0.7),    (fontSize * (CONTROLS_STEP * 13)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Fullscreen",                     text_Controls_7c,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_7c, 0.7),    (fontSize * (CONTROLS_STEP * 13)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(1/4)",                          text_Controls_P1,    (gameWidth - (text_Controls_P1.rect.w * 1.25)),      (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (KB+M)",              text_Controls_8,     OBJ_TO_MID_SCREEN_X(text_Controls_8),                (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Esc",                            text_Controls_9a,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),    (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                          text_Controls_9b,    OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),    (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Q (while paused)",               text_Controls_10a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3),   (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",                   text_Controls_10b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7),   (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("Numbers",                        text_Controls_11a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11a, 0.3),   (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Input",                    text_Controls_11b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_11b, 0.7),   (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(".",                              text_Controls_12a,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3),   (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_12b,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7),   (fontSize * (CONTROLS_STEP *  9)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_12c,   OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7),   (fontSize * (CONTROLS_STEP *  9)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/4)",                          text_Controls_P2,    (gameWidth - (text_Controls_P2.rect.w * 1.25)),      (gameHeight - (text_Controls_P2.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME (CONTROLLER)", text_Controls_c_1,   OBJ_TO_MID_SCREEN_X(text_Controls_c_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                          text_Controls_c_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                              text_Controls_c_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                              text_Controls_c_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                              text_Controls_c_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                              text_Controls_c_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Right Stick",                    text_Controls_c_7a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_7a, 0.3),  (fontSize * (CONTROLS_STEP * 13))                  );
	SET_TEXT_WITH_OUTLINE("(3/4)",                          text_Controls_c_P1,  (gameWidth - (text_Controls_c_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P1.rect.h * 1.5))   );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME (CONTROLLER)",        text_Controls_c_8,   OBJ_TO_MID_SCREEN_X(text_Controls_c_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                          text_Controls_c_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_c_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Select (paused)",         text_Controls_c_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_10a, 0.3), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("X / Y",                          text_Controls_c_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",                   text_Controls_c_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",                      text_Controls_c_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_c_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(4/4)",                          text_Controls_c_P2,  (gameWidth - (text_Controls_c_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_c_P2.rect.h * 1.5)));
#else // Gamecube + Default
	SET_LARGE_TEXT_WITH_OUTLINE("MENU + GAME",     text_Controls_1,   OBJ_TO_MID_SCREEN_X(text_Controls_1),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("D-Pad",                 text_Controls_2a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_2b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2b, 0.3),  (fontSize * (CONTROLS_STEP *  3)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Navigate",              text_Controls_2c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_2c, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("A",                     text_Controls_3a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3a, 0.3),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_3b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3b, 0.3),  (fontSize * (CONTROLS_STEP *  5)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Confirm",               text_Controls_3c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_3c, 0.7),  (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("B",                     text_Controls_4a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4a, 0.3),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_4b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("Back",                  text_Controls_4c,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_4c, 0.7),  (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("L",                     text_Controls_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5a, 0.3),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("Prev. Song",            text_Controls_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_5b, 0.7),  (fontSize * (CONTROLS_STEP *  9))                  );
	SET_TEXT_WITH_OUTLINE("R",                     text_Controls_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6a, 0.3),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE("Next Song",             text_Controls_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_6b, 0.7),  (fontSize * (CONTROLS_STEP * 11))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7a,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7b,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_7c,  0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("(1/2)",                 text_Controls_P1,  (gameWidth - (text_Controls_P1.rect.w * 1.25)),    (gameHeight - (text_Controls_P1.rect.h * 1.5))     );
	SET_LARGE_TEXT_WITH_OUTLINE("GAME",            text_Controls_8,   OBJ_TO_MID_SCREEN_X(text_Controls_8),              (fontSize * (CONTROLS_STEP *  1))                  );
	SET_TEXT_WITH_OUTLINE("Start",                 text_Controls_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9a, 0.3),  (fontSize * (CONTROLS_STEP *  3))                  );
	SET_TEXT_WITH_OUTLINE("Pause",                 text_Controls_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Controls_9b, 0.7),  (fontSize * (CONTROLS_STEP *  3))                  );
	initTextObjectVals(&text_Controls_10a);
	SET_TEXT_WITH_OUTLINE_HELPER("Z (paused)",     text_Controls_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10a, 0.3), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE("Quit to Menu",          text_Controls_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_10b, 0.7), (fontSize * (CONTROLS_STEP *  5))                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11a, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE(" ",                     text_Controls_11b, 0,                                                 0                                                  );
	SET_TEXT_WITH_OUTLINE("X / Y",                 text_Controls_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12a, 0.3), (fontSize * (CONTROLS_STEP *  7))                  );
	SET_TEXT_WITH_OUTLINE("Quick Toggle",          text_Controls_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12b, 0.7), (fontSize * (CONTROLS_STEP *  7)) - CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("Mini-Grid",             text_Controls_12c, OBJ_TO_SCREEN_AT_FRACTION(text_Controls_12c, 0.7), (fontSize * (CONTROLS_STEP *  7)) + CONTROLS_SPACER);
	SET_TEXT_WITH_OUTLINE("(2/2)",                 text_Controls_P2,  (gameWidth - (text_Controls_P2.rect.w * 1.25)),    (gameHeight - (text_Controls_P2.rect.h * 1.5))     );
#endif
}

void renderDividerBetweenY(TextObject *textObj1, TextObject *textObj2) {
//#if defined(PC)
//    divider.y = (textObj1->rect.y + textObj2->rect.y + fontSize - divider.h) / 2;
//#if !defined(SDL1)
//    SDL_RenderFillRect(renderer, &divider);
//#else
//	SDL_FillRect(windowScreen, &divider, 0);
//#endif
//#endif
}

void renderYouWinRect() {
	if (compactDisplay) {
#if !defined(SDL1)
		SDL_RenderFillRect(renderer, &youWinRect);
#else
		SDL_FillRect(windowScreen, &youWinRect, 0);
#endif
	}
}

#if defined(WII)
inline static void renderControlsTextPage1_Wii_General() {
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
}

inline static void renderControlsTextPage1_Wii_Vertical() {
	renderText(&text_Controls_2a_vertical);
	renderText(&text_Controls_2b_vertical);
	renderText(&text_Controls_2c_vertical);
	renderDividerBetweenY(&text_Controls_2c_vertical, &text_Controls_3c_vertical);
	renderText(&text_Controls_3a_vertical);
	renderText(&text_Controls_3b_vertical);
	renderText(&text_Controls_3c_vertical);
	renderDividerBetweenY(&text_Controls_3c_vertical, &text_Controls_4c_vertical);
	renderText(&text_Controls_4a_vertical);
	renderText(&text_Controls_4b_vertical);
	renderText(&text_Controls_4c_vertical);
	renderDividerBetweenY(&text_Controls_4c_vertical, &text_Controls_5b_vertical);
	renderText(&text_Controls_5a_vertical);
	renderText(&text_Controls_5b_vertical);
	renderDividerBetweenY(&text_Controls_5b_vertical, &text_Controls_6b_vertical);
	renderText(&text_Controls_6a_vertical);
	renderText(&text_Controls_6b_vertical);
	renderDividerBetweenY(&text_Controls_6b_vertical, &text_Controls_7a_vertical);
	renderText(&text_Controls_7a_vertical);
}

inline static void renderControlsTextPage1_Wii_Horizontal() {
	renderText(&text_Controls_2a_horizontal);
	renderText(&text_Controls_2b_horizontal);
	renderText(&text_Controls_2c_horizontal);
	renderDividerBetweenY(&text_Controls_2c_horizontal, &text_Controls_3c_horizontal);
	renderText(&text_Controls_3a_horizontal);
	renderText(&text_Controls_3b_horizontal);
	renderText(&text_Controls_3c_horizontal);
	renderDividerBetweenY(&text_Controls_3c_horizontal, &text_Controls_4c_horizontal);
	renderText(&text_Controls_4a_horizontal);
	renderText(&text_Controls_4b_horizontal);
	renderText(&text_Controls_4c_horizontal);
	renderDividerBetweenY(&text_Controls_4c_horizontal, &text_Controls_5b_horizontal);
	renderText(&text_Controls_5a_horizontal);
	renderText(&text_Controls_5b_horizontal);
	renderDividerBetweenY(&text_Controls_5b_horizontal, &text_Controls_6b_horizontal);
	renderText(&text_Controls_6a_horizontal);
	renderText(&text_Controls_6b_horizontal);
	renderDividerBetweenY(&text_Controls_6b_horizontal, &text_Controls_7a_horizontal);
	renderText(&text_Controls_7a_horizontal);
}

inline static void renderControlsTextPage2_Wii_General() {
	renderText(&text_Controls_9a);
	renderText(&text_Controls_9b);
	renderDividerBetweenY(&text_Controls_9a, &text_Controls_10a);
	renderText(&text_Controls_10a);
	renderText(&text_Controls_7b);
	renderText(&text_Controls_10b);
	renderDividerBetweenY(&text_Controls_10a, &text_Controls_11a);
	renderText(&text_Controls_11a);
	renderText(&text_Controls_11b);
	renderDividerBetweenY(&text_Controls_11a, &text_Controls_12a);
	renderText(&text_Controls_12a);
	renderText(&text_Controls_7c);
	renderText(&text_Controls_12b);
	renderText(&text_Controls_12c);
}

inline static void renderControlsTextPage2_Wii_Vertical() {
	renderText(&text_Controls_9a_vertical);
	renderText(&text_Controls_9b_vertical);
	renderDividerBetweenY(&text_Controls_9a_vertical, &text_Controls_10a_vertical);
	renderText(&text_Controls_10a_vertical);
	renderText(&text_Controls_7b_vertical);
	renderText(&text_Controls_10b_vertical);
	renderDividerBetweenY(&text_Controls_10a_vertical, &text_Controls_11a_vertical);
	renderText(&text_Controls_11a_vertical);
	renderText(&text_Controls_11b_vertical);
	renderDividerBetweenY(&text_Controls_11a_vertical, &text_Controls_12a_vertical);
	renderText(&text_Controls_12a_vertical);
	renderText(&text_Controls_7c_vertical);
	renderText(&text_Controls_12b_vertical);
	renderText(&text_Controls_12c_vertical);
}

inline static void renderControlsTextPage2_Wii_Horizontal() {
	renderText(&text_Controls_9a_horizontal);
	renderText(&text_Controls_9b_horizontal);
	renderDividerBetweenY(&text_Controls_9a_horizontal, &text_Controls_10a_horizontal);
	renderText(&text_Controls_10a_horizontal);
	renderText(&text_Controls_7b_horizontal);
	renderText(&text_Controls_10b_horizontal);
	renderDividerBetweenY(&text_Controls_10a_horizontal, &text_Controls_11a_horizontal);
	renderText(&text_Controls_11a_horizontal);
	renderText(&text_Controls_11b_horizontal);
	renderDividerBetweenY(&text_Controls_11a_horizontal, &text_Controls_12a_horizontal);
	renderText(&text_Controls_12a_horizontal);
	renderText(&text_Controls_7c_horizontal);
	renderText(&text_Controls_12b_horizontal);
	renderText(&text_Controls_12c_horizontal);
}
#endif

void renderControlsTextPage1() {
	renderTextLarge(&text_Controls_1);
#if defined(WII)
	switch (controlSettings.wiimoteScheme) {
		case 0:
			renderControlsTextPage1_Wii_Horizontal();
			break;
		case 1:
			renderControlsTextPage1_Wii_General();
			break;
		case 2:
			renderControlsTextPage1_Wii_Vertical();
			break;
	}
#elif defined(FUNKEY)
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
#else
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
#endif
	renderText(&text_Controls_P1);
}

void renderControlsTextPage2() {
	renderTextLarge(&text_Controls_8);
#if defined(WII)
	switch (controlSettings.wiimoteScheme) {
		case 0:
			renderControlsTextPage2_Wii_Horizontal();
			break;
		case 1:
			renderControlsTextPage2_Wii_General();
			break;
		case 2:
			renderControlsTextPage2_Wii_Vertical();
			break;
	}
#elif defined(FUNKEY)
	renderText(&text_Controls_9a);
	renderText(&text_Controls_9b);
	renderDividerBetweenY(&text_Controls_9a, &text_Controls_10a);
	renderText(&text_Controls_10a);
	renderText(&text_Controls_7b);
	renderText(&text_Controls_10b);
	renderDividerBetweenY(&text_Controls_10a, &text_Controls_11a);
	renderText(&text_Controls_11a);
	renderText(&text_Controls_11b);
	renderDividerBetweenY(&text_Controls_11a, &text_Controls_12a);
	renderText(&text_Controls_12a);
	renderText(&text_Controls_7c);
	renderText(&text_Controls_12b);
	renderText(&text_Controls_12c);
#else
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
#endif
	renderText(&text_Controls_P2);
}

#if defined(PC)
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
	renderText(&text_Controls_c_7a);
	renderText(&text_Controls_7b);
	renderText(&text_Controls_7c);
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
	if (compactDisplay) {
		SET_LARGE_TEXT_WITH_OUTLINE("CODE,DESIGN,MOST ART",     text_Credits_1, OBJ_TO_MID_SCREEN_X(text_Credits_1),         (fontSize * (CREDITS_STEP * 1))              );
	} else {
		SET_LARGE_TEXT_WITH_OUTLINE("CODING, DESIGN, MOST ART", text_Credits_1, OBJ_TO_MID_SCREEN_X(text_Credits_1),         (fontSize * (CREDITS_STEP * 1))              );
	}
    SET_TEXT_WITH_OUTLINE("Mode8fx",                    text_Credits_2,   OBJ_TO_MID_SCREEN_X(text_Credits_2),               (fontSize * (CREDITS_STEP *    5))           );
    SET_TEXT_WITH_OUTLINE("https://github.com/Mode8fx", text_Credits_3,   OBJ_TO_MID_SCREEN_X(text_Credits_3),               (fontSize * (CREDITS_STEP * 6.25))           );
	SET_TEXT_WITH_OUTLINE("(1/9)",                      text_Credits_P1,  (gameWidth - (text_Credits_P1.rect.w * 1.25)),     (gameHeight - (text_Credits_P1.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("MUSIC",                text_Credits_4,   OBJ_TO_MID_SCREEN_X(text_Credits_4),               (fontSize * (CREDITS_STEP *     1))          );
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_5b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5b, 0.25),  (fontSize * (CREDITS_STEP *   3.5))          );
    SET_TEXT_WITH_OUTLINE("\"Wonder Flow\"",            text_Credits_5a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_5a, 0.75),  (fontSize * (CREDITS_STEP *   3.5))          );
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_6b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6b, 0.25),  (fontSize * (CREDITS_STEP *  4.75))          );
    SET_TEXT_WITH_OUTLINE("\"Sudoku Padawan\"",         text_Credits_6a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_6a, 0.75),  (fontSize * (CREDITS_STEP *  4.75))          );
    SET_TEXT_WITH_OUTLINE("Nuke of Anarchy",            text_Credits_7b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7b, 0.25),  (fontSize * (CREDITS_STEP *     6))          );
    SET_TEXT_WITH_OUTLINE("\"Electroquest\"",           text_Credits_7a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_7a, 0.75),  (fontSize * (CREDITS_STEP *     6))          );
    SET_TEXT_WITH_OUTLINE("Soundscape",                 text_Credits_8b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8b, 0.25),  (fontSize * (CREDITS_STEP *  7.25))          );
    SET_TEXT_WITH_OUTLINE("\"Main Menu\"",              text_Credits_8a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_8a, 0.75),  (fontSize * (CREDITS_STEP *  7.25))          );
    SET_TEXT_WITH_OUTLINE("Okeanos",                    text_Credits_9b,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9b, 0.25),  (fontSize * (CREDITS_STEP *   8.5))          );
    SET_TEXT_WITH_OUTLINE("\"Insomnia\"",               text_Credits_9a,  OBJ_TO_SCREEN_AT_FRACTION(text_Credits_9a, 0.75),  (fontSize * (CREDITS_STEP *   8.5))          );
    SET_TEXT_WITH_OUTLINE("Solon",                      text_Credits_10b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10b, 0.25), (fontSize * (CREDITS_STEP *  9.75))          );
    SET_TEXT_WITH_OUTLINE("\"Ontario\"",                text_Credits_10a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_10a, 0.75), (fontSize * (CREDITS_STEP *  9.75))          );
    SET_TEXT_WITH_OUTLINE("Noiseless",                  text_Credits_11b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11b, 0.25), (fontSize * (CREDITS_STEP *    11))          );
    SET_TEXT_WITH_OUTLINE("\"Addiction\"",              text_Credits_11a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_11a, 0.75), (fontSize * (CREDITS_STEP *    11))          );
	SET_TEXT_WITH_OUTLINE("Magnar Harestad",            text_Credits_12b, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_12b, 0.25), (fontSize * (CREDITS_STEP * 12.25))          );
	SET_TEXT_WITH_OUTLINE("\"Ancient Days\"",           text_Credits_12a, OBJ_TO_SCREEN_AT_FRACTION(text_Credits_12a, 0.75), (fontSize * (CREDITS_STEP * 12.25))          );
	SET_TEXT_WITH_OUTLINE("(2/9)",                      text_Credits_P2,  (gameWidth - (text_Credits_P2.rect.w * 1.25)),     (gameHeight - (text_Credits_P2.rect.h * 1.5)));
	if (compactDisplay) {
		SET_TEXT_WITH_OUTLINE("All music obtained",   text_Credits_music2_1, OBJ_TO_MID_SCREEN_X(text_Credits_music2_1), (fontSize * (CREDITS_STEP * 5)));
		SET_TEXT_WITH_OUTLINE("from modarchive.org",  text_Credits_music2_2, OBJ_TO_MID_SCREEN_X(text_Credits_music2_2), (fontSize * (CREDITS_STEP * 6.25)));
		SET_TEXT_WITH_OUTLINE("\"Ancient Days\"",     text_Credits_music2_3, OBJ_TO_MID_SCREEN_X(text_Credits_music2_3), (fontSize * (CREDITS_STEP * 8.25)));
		SET_TEXT_WITH_OUTLINE("edited by Mode8fx",    text_Credits_music2_4, OBJ_TO_MID_SCREEN_X(text_Credits_music2_4), (fontSize * (CREDITS_STEP * 9.5)));
		SET_TEXT_WITH_OUTLINE("for looping purposes", text_Credits_music2_5, OBJ_TO_MID_SCREEN_X(text_Credits_music2_5), (fontSize * (CREDITS_STEP * 10.75)));
	} else {
    SET_TEXT_WITH_OUTLINE("All music obtained from modarchive.org", text_Credits_music2_1, OBJ_TO_MID_SCREEN_X(text_Credits_music2_1), (fontSize * (CREDITS_STEP *    5)));
		SET_TEXT_WITH_OUTLINE("\"Ancient Days\" edited by Mode8fx", text_Credits_music2_2, OBJ_TO_MID_SCREEN_X(text_Credits_music2_2), (fontSize * (CREDITS_STEP *    7)));
		SET_TEXT_WITH_OUTLINE("for looping purposes",               text_Credits_music2_3, OBJ_TO_MID_SCREEN_X(text_Credits_music2_3), (fontSize * (CREDITS_STEP * 8.25)));
	}
	SET_TEXT_WITH_OUTLINE("(3/9)",                      text_Credits_P3,  (gameWidth - (text_Credits_P3.rect.w * 1.25)),     (gameHeight - (text_Credits_P3.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("LIBRARIES",            text_Credits_13,  OBJ_TO_MID_SCREEN_X(text_Credits_13),              (fontSize * (CREDITS_STEP *  1))            );
#if defined(SDL1)
	SET_TEXT_WITH_OUTLINE("SDL",                        text_Credits_14,  OBJ_TO_MID_SCREEN_X(text_Credits_14),              (fontSize * (CREDITS_STEP *  5))            );
	SET_TEXT_WITH_OUTLINE("SDL_image",                  text_Credits_15,  OBJ_TO_MID_SCREEN_X(text_Credits_15),              (fontSize * (CREDITS_STEP *  7))            );
	SET_TEXT_WITH_OUTLINE("SDL_ttf",                    text_Credits_16,  OBJ_TO_MID_SCREEN_X(text_Credits_16),              (fontSize * (CREDITS_STEP *  9))            );
	SET_TEXT_WITH_OUTLINE("SDL_mixer",                  text_Credits_17,  OBJ_TO_MID_SCREEN_X(text_Credits_17),              (fontSize * (CREDITS_STEP * 11))            );
#else
    SET_TEXT_WITH_OUTLINE("SDL2",                       text_Credits_14,  OBJ_TO_MID_SCREEN_X(text_Credits_14),              (fontSize * (CREDITS_STEP *  5))            );
    SET_TEXT_WITH_OUTLINE("SDL2_image",                 text_Credits_15,  OBJ_TO_MID_SCREEN_X(text_Credits_15),              (fontSize * (CREDITS_STEP *  7))            );
    SET_TEXT_WITH_OUTLINE("SDL2_ttf",                   text_Credits_16,  OBJ_TO_MID_SCREEN_X(text_Credits_16),              (fontSize * (CREDITS_STEP *  9))            );
    SET_TEXT_WITH_OUTLINE("SDL2_mixer",                 text_Credits_17,  OBJ_TO_MID_SCREEN_X(text_Credits_17),              (fontSize * (CREDITS_STEP * 11))            );
#endif
	SET_TEXT_WITH_OUTLINE("(4/9)",                         text_Credits_P4,  (gameWidth - (text_Credits_P4.rect.w * 1.25)), (gameHeight - (text_Credits_P4.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("FONT",                    text_Credits_18,  OBJ_TO_MID_SCREEN_X(text_Credits_18),          (fontSize * (CREDITS_STEP *    1))           );
    SET_TEXT_WITH_OUTLINE("Commodore Pixelized v1.2",      text_Credits_19,  OBJ_TO_MID_SCREEN_X(text_Credits_19),          (fontSize * (CREDITS_STEP *    5))           );
    SET_TEXT_WITH_OUTLINE("by Devin Cook",                 text_Credits_20,  OBJ_TO_MID_SCREEN_X(text_Credits_20),          (fontSize * (CREDITS_STEP * 6.25))           );
	SET_TEXT_WITH_OUTLINE("(5/9)",                         text_Credits_P5,  (gameWidth - (text_Credits_P5.rect.w * 1.25)), (gameHeight - (text_Credits_P5.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("SOUND EFFECTS",           text_Credits_21,  OBJ_TO_MID_SCREEN_X(text_Credits_21),          (fontSize * (CREDITS_STEP *    1))           );
    SET_TEXT_WITH_OUTLINE("Luke.RUSTLTD",                  text_Credits_22,  OBJ_TO_MID_SCREEN_X(text_Credits_22),          (fontSize * (CREDITS_STEP *    5))           );
    SET_TEXT_WITH_OUTLINE("https://opengameart.org",       text_Credits_23a, OBJ_TO_MID_SCREEN_X(text_Credits_23a),         (fontSize * (CREDITS_STEP * 6.25))           );
	SET_TEXT_WITH_OUTLINE("/content/10-8bit-coin-sounds",  text_Credits_23b, OBJ_TO_MID_SCREEN_X(text_Credits_23b),         (fontSize * (CREDITS_STEP *  7.5))           );
	SET_TEXT_WITH_OUTLINE("(6/9)",                         text_Credits_P6,  (gameWidth - (text_Credits_P6.rect.w * 1.25)), (gameHeight - (text_Credits_P6.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("THANKS FOR PLAYING!",     text_Credits_24,  OBJ_TO_MID_SCREEN_X(text_Credits_24),          (fontSize * (CREDITS_STEP *    1))           );
    SET_TEXT_WITH_OUTLINE("Here are a couple cheats...",   text_Credits_25,  OBJ_TO_MID_SCREEN_X(text_Credits_25),          (fontSize * (CREDITS_STEP *  3.3))           );
    SET_TEXT_WITH_OUTLINE("If you get stuck on a puzzle,", text_Credits_26,  OBJ_TO_MID_SCREEN_X(text_Credits_26),          (fontSize * (CREDITS_STEP * 4.45))           );
    SET_TEXT_WITH_OUTLINE(CHEAT1_TEXT,                     text_Credits_27,  OBJ_TO_MID_SCREEN_X(text_Credits_27),          (fontSize * (CREDITS_STEP *  5.6))           );
#if defined(FUNKEY)
		SET_TEXT_WITH_OUTLINE("reveal the highlighted cell.",    text_Credits_28, OBJ_TO_MID_SCREEN_X(text_Credits_28), (fontSize * (CREDITS_STEP * 6.75))               );
#else
		SET_TEXT_WITH_OUTLINE("to reveal the highlighted cell.", text_Credits_28, OBJ_TO_MID_SCREEN_X(text_Credits_28), (fontSize * (CREDITS_STEP * 6.75))               );
#endif
	SET_TEXT_WITH_OUTLINE(CHEAT2_TEXT,                     text_Credits_28_1, OBJ_TO_MID_SCREEN_X(text_Credits_28_1),       (fontSize * (CREDITS_STEP *  7.9))           );
	SET_TEXT_WITH_OUTLINE("to clear all incorrect cells.", text_Credits_28_2, OBJ_TO_MID_SCREEN_X(text_Credits_28_2),       (fontSize * (CREDITS_STEP * 9.05))           );
    SET_TEXT_WITH_OUTLINE("I hope you enjoy the game!",    text_Credits_29,  OBJ_TO_MID_SCREEN_X(text_Credits_29),          (fontSize * (CREDITS_STEP * 10.2))           );
    SET_TEXT_WITH_OUTLINE("- Mode8fx",                     text_Credits_30,  OBJ_TO_MID_SCREEN_X(text_Credits_30),          (fontSize * (CREDITS_STEP * 12.5))           );
	SET_TEXT_WITH_OUTLINE("(7/9)",                         text_Credits_P7,  (gameWidth - (text_Credits_P7.rect.w * 1.25)), (gameHeight - (text_Credits_P7.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("WANT MORE?",              text_Credits_31,  OBJ_TO_MID_SCREEN_X(text_Credits_31),          (fontSize * (CREDITS_STEP *     1))          );
		if (compactDisplay) {
			SET_TEXT_WITH_OUTLINE("SuDokuL is available",  text_Credits_32, OBJ_TO_MID_SCREEN_X(text_Credits_32),   (fontSize * (CREDITS_STEP *   3.5)));
			SET_TEXT_WITH_OUTLINE("on a wide variety of",  text_Credits_33, OBJ_TO_MID_SCREEN_X(text_Credits_33),   (fontSize * (CREDITS_STEP *  4.75)));
			SET_TEXT_WITH_OUTLINE("homebrew-enabled",      text_Credits_34, OBJ_TO_MID_SCREEN_X(text_Credits_34),   (fontSize * (CREDITS_STEP *     6)));
			SET_TEXT_WITH_OUTLINE("systems, old and new.", text_Credits_35, OBJ_TO_MID_SCREEN_X(text_Credits_35),   (fontSize * (CREDITS_STEP *  7.25)));
			SET_TEXT_WITH_OUTLINE("Play it everywhere!",   text_Credits_36, OBJ_TO_MID_SCREEN_X(text_Credits_36),   (fontSize * (CREDITS_STEP *   8.5)));
			SET_TEXT_WITH_OUTLINE("", text_Credits_37,     OBJ_TO_MID_SCREEN_X(text_Credits_37),                    (fontSize * (CREDITS_STEP *     0)));
			SET_TEXT_WITH_OUTLINE("", text_Credits_38,     OBJ_TO_MID_SCREEN_X(text_Credits_38),                    (fontSize * (CREDITS_STEP *     0)));
			SET_TEXT_WITH_OUTLINE("https://github.com/",   text_Credits_39a, OBJ_TO_MID_SCREEN_X(text_Credits_39a), (fontSize * (CREDITS_STEP * 11.25)));
			SET_TEXT_WITH_OUTLINE("Mode8fx/SuDokuL",       text_Credits_39b, OBJ_TO_MID_SCREEN_X(text_Credits_39b), (fontSize * (CREDITS_STEP *  12.5)));
		} else {
			SET_TEXT_WITH_OUTLINE("SuDokuL is available on a wide",     text_Credits_32,  OBJ_TO_MID_SCREEN_X(text_Credits_32),  (fontSize * (CREDITS_STEP *  3.5)));
			SET_TEXT_WITH_OUTLINE("variety of homebrew-enabled",        text_Credits_33,  OBJ_TO_MID_SCREEN_X(text_Credits_33),  (fontSize * (CREDITS_STEP * 4.75)));
			SET_TEXT_WITH_OUTLINE("systems, old and new.",              text_Credits_34,  OBJ_TO_MID_SCREEN_X(text_Credits_34),  (fontSize * (CREDITS_STEP *    6)));
			SET_TEXT_WITH_OUTLINE("Play it everywhere!",                text_Credits_35,  OBJ_TO_MID_SCREEN_X(text_Credits_35),  (fontSize * (CREDITS_STEP * 7.25)));
			SET_TEXT_WITH_OUTLINE("",                                   text_Credits_36,  OBJ_TO_MID_SCREEN_X(text_Credits_36),  (fontSize * (CREDITS_STEP *    0)));
			SET_TEXT_WITH_OUTLINE("",                                   text_Credits_37,  OBJ_TO_MID_SCREEN_X(text_Credits_37),  (fontSize * (CREDITS_STEP *    0)));
			SET_TEXT_WITH_OUTLINE("",                                   text_Credits_38,  OBJ_TO_MID_SCREEN_X(text_Credits_38),  (fontSize * (CREDITS_STEP *    0)));
			SET_TEXT_WITH_OUTLINE("",                                   text_Credits_39a, OBJ_TO_MID_SCREEN_X(text_Credits_39a), (fontSize * (CREDITS_STEP * 12.5)));
			SET_TEXT_WITH_OUTLINE("https://github.com/Mode8fx/SuDokuL", text_Credits_39b, OBJ_TO_MID_SCREEN_X(text_Credits_39b), (fontSize * (CREDITS_STEP * 12.5)));
		}
	SET_TEXT_WITH_OUTLINE("(8/9)",                      text_Credits_P8,  (gameWidth - (text_Credits_P8.rect.w * 1.25)), (gameHeight - (text_Credits_P8.rect.h * 1.5)));
    SET_LARGE_TEXT_WITH_OUTLINE("MOST BACKGROUND ART",  text_Credits_40,  OBJ_TO_MID_SCREEN_X(text_Credits_40),          (fontSize * (CREDITS_STEP *    1))           );
    SET_TEXT_WITH_OUTLINE("kddove85",                   text_Credits_41,  OBJ_TO_MID_SCREEN_X(text_Credits_41),          (fontSize * (CREDITS_STEP *    5))           );
    SET_TEXT_WITH_OUTLINE("https://opengameart.org",    text_Credits_42a, OBJ_TO_MID_SCREEN_X(text_Credits_42a),         (fontSize * (CREDITS_STEP * 6.25))           );
	SET_TEXT_WITH_OUTLINE("/content/2d-tilesets",       text_Credits_42b, OBJ_TO_MID_SCREEN_X(text_Credits_42b),         (fontSize * (CREDITS_STEP *  7.5))           );
	SET_TEXT_WITH_OUTLINE("(9/9)",                      text_Credits_P9,  (gameWidth - (text_Credits_P9.rect.w * 1.25)), (gameHeight - (text_Credits_P9.rect.h * 1.5)));
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
    renderText(&text_Credits_12a);
	renderText(&text_Credits_12b);
    renderText(&text_Credits_P2);
}

void renderCreditsTextPage3() {
	renderTextLarge(&text_Credits_4);
	renderText(&text_Credits_music2_1);
	renderText(&text_Credits_music2_2);
	renderText(&text_Credits_music2_3);
	renderText(&text_Credits_music2_4);
	renderText(&text_Credits_music2_5);
	renderText(&text_Credits_P3);
}

void renderCreditsTextPage4() {
    renderTextLarge(&text_Credits_18);
    renderText(&text_Credits_19);
    renderText(&text_Credits_20);
    renderText(&text_Credits_P4);
}

void renderCreditsTextPage5() {
	renderTextLarge(&text_Credits_40);
	renderText(&text_Credits_41);
	renderText(&text_Credits_42a);
	renderText(&text_Credits_42b);
	renderText(&text_Credits_P5);
}

void renderCreditsTextPage6() {
    renderTextLarge(&text_Credits_21);
    renderText(&text_Credits_22);
    renderText(&text_Credits_23a);
	renderText(&text_Credits_23b);
    renderText(&text_Credits_P6);
}

void renderCreditsTextPage7() {
    renderTextLarge(&text_Credits_13);
    renderText(&text_Credits_14);
    renderText(&text_Credits_15);
    renderText(&text_Credits_16);
    renderText(&text_Credits_17);
    renderText(&text_Credits_P7);
}

void renderCreditsTextPage8() {
    renderTextLarge(&text_Credits_24);
    renderText(&text_Credits_25);
    renderText(&text_Credits_26);
    renderText(&text_Credits_27);
    renderText(&text_Credits_28);
	renderText(&text_Credits_28_1);
	renderText(&text_Credits_28_2);
    renderText(&text_Credits_29);
    renderText(&text_Credits_30);
    renderText(&text_Credits_P8);
}

void renderCreditsTextPage9() {
    renderTextLarge(&text_Credits_31);
    renderText(&text_Credits_32);
    renderText(&text_Credits_33);
    renderText(&text_Credits_34);
    renderText(&text_Credits_35);
    renderText(&text_Credits_36);
    renderText(&text_Credits_37);
    renderText(&text_Credits_38);
    renderText(&text_Credits_39a);
    renderText(&text_Credits_39b);
    renderText(&text_Credits_P9);
}

void controlsSetConfirmBackPos() {
#if defined(WII_U) || defined(VITA) || defined(SWITCH) || defined(ANDROID)
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_3a.rect.y = (Sint16)((fontSize * (CONTROLS_STEP * 5)) - CONTROLS_SPACER);
        text_Controls_4a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
    } else {
        text_Controls_3a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
        text_Controls_4a.rect.y = (Sint16)((fontSize * (CONTROLS_STEP * 5)) - CONTROLS_SPACER);
    }
#elif defined(PC)
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_c_3a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 5));
        text_Controls_c_4a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
    } else {
        text_Controls_c_3a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
        text_Controls_c_4a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 5));
    }
#else
    if (controlSettings.swapConfirmAndBack) {
        text_Controls_3a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 5));
        text_Controls_4a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
    } else {
        text_Controls_3a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 7));
        text_Controls_4a.rect.y = (Sint16)(fontSize * (CONTROLS_STEP * 5));
    }
#endif
}

Uint64 fps_lastTime = 0;
double fps_freq;
Uint8 fps_frameCount = 0;
Uint8 fps_frameCountLastSecond = 0;

void printFPS() {
	fps_frameCount++;
#if !defined(SDL1)
	Uint64 currentTime = SDL_GetPerformanceCounter();
	if (fps_lastTime == 0) {
		fps_lastTime = currentTime;
		fps_freq = (double)SDL_GetPerformanceFrequency();
	}

	double elapsed = (double)(currentTime - fps_lastTime) / fps_freq;
	if (elapsed >= 1.0) {
		fps_frameCountLastSecond = fps_frameCount;
		fps_frameCount = 0;
		fps_lastTime = currentTime;
	}
#else
	Uint64 currentTime = SDL_GetTicks();

	if (currentTime > fps_lastTime + 1000) {
		fps_frameCountLastSecond = fps_frameCount;
		fps_frameCount = 0;
		fps_lastTime = currentTime;
	}
#endif
	Sint16 fps_counterX = gameWidth / 2;
	Sint16 fps_counterY = gameHeight * 7 / 8;
	i = 0;
	setAndRenderNumHelper(int(fps_frameCountLastSecond) / 10, fps_counterX, fps_counterY, 0);
	setAndRenderNumHelper(int(fps_frameCountLastSecond) % 10, fps_counterX + 20, fps_counterY, 0);
}
