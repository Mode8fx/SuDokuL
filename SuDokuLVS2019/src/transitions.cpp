#include "transitions.h"
#include "general.h"
#include "shared.h"
#include "sprite_objects.h"
#include "menu_logic.h"
#include "window.h"

void transitionGraphicsFromTitleScreen() {
    /* Animate Logo and Text */
    logo.rect.y = logo.endPos_y + (Sint16)MOVE_FAST_THEN_DECELERATE(logo.startPos_y - logo.endPos_y, 1, time_anim1);
    menuMoveTextRight(&text_PressStart, time_anim1);
    menuMoveTextRight(&text_Version_Number, time_anim1);
    /* Check For Finished Animation */
    if (time_anim1 >= 1) {
        logo.rect.y = logo.endPos_y;
        updateMainMenuCursorPositionX();
        updateMenuCursorPositionY(menuCursorIndex_main);
    }
    /* Draw Logo and Text */
    SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
    renderText(&text_PressStart);
    renderText(&text_Version_Number);
}

void transitionGraphicsToTitleScreen() {
    /* Animate Logo and Text */
    logo.rect.y = logo.startPos_y - (Sint16)MOVE_FAST_THEN_DECELERATE(logo.startPos_y - logo.endPos_y, 1, time_anim1);
    menuMoveTextLeft(&text_PressStart, time_anim1);
    menuMoveTextLeft(&text_Version_Number, time_anim1);
    /* Check For Finished Animation */
    if (time_anim1 >= 1) {
        logo.rect.y = logo.startPos_y;
        text_PressStart.rect.y = text_PressStart.startPos_y;
    }
    /* Draw Logo and Text */
    SDL_RenderCopy(renderer, logo.texture, NULL, &logo.rect);
    renderText(&text_PressStart);
    renderText(&text_Version_Number);
}

void transitionGraphicsFromMainMenu() {
    /* Animate and Draw Text */
    menuMoveTextDown(&text_Play, time_anim1);
    menuMoveTextDown(&text_Controls, time_anim1);
    menuMoveTextDown(&text_Options, time_anim1);
    menuMoveTextDown(&text_Credits, time_anim1);
    renderText(&text_Play);
    renderText(&text_Controls);
    renderText(&text_Options);
    renderText(&text_Credits);
#if !defined(ANDROID)
    menuMoveTextDown(&text_Quit, time_anim1);
    renderText(&text_Quit);
#endif
}

void transitionGraphicsToMainMenu(Sint8 choice) {
    /* Animate Text */
    switch (choice) {
        case 0:
            menuMoveTextLeft(&text_Play, time_anim1);
            break;
        case 1:
            menuMoveTextLeft(&text_Controls, time_anim1);
            break;
        case 2:
            menuMoveTextLeft(&text_Options, time_anim1);
            break;
        case 3:
            menuMoveTextLeft(&text_Credits, time_anim1);
            break;
#if !defined(ANDROID)
        case 4:
            menuMoveTextLeft(&text_Quit, time_anim1);
            break;
#endif
        default:
            menuMoveTextUp(&text_Play, time_anim1);
            menuMoveTextUp(&text_Controls, time_anim1);
            menuMoveTextUp(&text_Options, time_anim1);
            menuMoveTextUp(&text_Credits, time_anim1);
#if !defined(ANDROID)
            menuMoveTextUp(&text_Quit, time_anim1);
#endif
            break;
    }
    /* Check For Finished Animation */
    if (time_anim1 >= 1) {
        text_Play.rect.y = text_Play.endPos_y;
        text_Controls.rect.y = text_Controls.endPos_y;
        text_Options.rect.y = text_Options.endPos_y;
        text_Credits.rect.y = text_Credits.endPos_y;
#if !defined(ANDROID)
        text_Quit.rect.y = text_Quit.endPos_y;
#endif
        updateMainMenuCursorPositionX();
        updateMenuCursorPositionY(menuCursorIndex_main);
    }
    /* Draw Text */
    renderText(&text_Play);
    renderText(&text_Controls);
    renderText(&text_Options);
    renderText(&text_Credits);
#if !defined(ANDROID)
    renderText(&text_Quit);
#endif
}

void transitionToStateWithTimer(double timer, Sint8 time, Uint8 state) {
    if (timer >= time) {
        timer = 0;
        programState = state;
    }
}