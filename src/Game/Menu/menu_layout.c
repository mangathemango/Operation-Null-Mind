#include <UI_text.h>
#include <app.h>

static UIElement* startButtonElement = NULL;
static UIElement* exitButtonElement = NULL;
static UIElement* title1Element = NULL;
static UIElement* title2Element = NULL;

void Menu_PrepareTextures() {
    SDL_Color textColor = {255, 255, 255, 255};

    title1Element = UI_CreateText("OPERATION", (SDL_Rect) {125, 75 , 0, 0}, textColor, 2.0f, UI_TEXT_ALIGN_CENTER, app.resources.title1Font);
    title2Element = UI_CreateText("NULL MIND", (SDL_Rect) {125, 110, 0, 0}, textColor, 1.5f, UI_TEXT_ALIGN_CENTER, app.resources.title2Font);
    startButtonElement = UI_CreateText("Start",(SDL_Rect) {125, 180, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    exitButtonElement = UI_CreateText("Exit",  (SDL_Rect) {125, 200, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
}

void Menu_Update() {
    UI_UpdateText(startButtonElement);
    UI_UpdateText(exitButtonElement);

    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {255, 0, 0, 255};
    
    if (startButtonElement->hovered) {
        UI_ChangeTextColor(startButtonElement, hoverButtonColor);
    } else {
        UI_ChangeTextColor(startButtonElement, defaultButtonColor);
    }

    if (startButtonElement->pressed) {
        app.state.currentScene = SCENE_GAME;
    }

    if (exitButtonElement->hovered) {
        UI_ChangeTextColor(exitButtonElement, hoverButtonColor);
    } else {
        UI_ChangeTextColor(exitButtonElement, defaultButtonColor);
    }

    if (exitButtonElement->pressed) {
        app.state.running = false;
    }
}

void Menu_Render() {
    UI_RenderText(title1Element);
    UI_RenderText(title2Element);
    UI_RenderText(startButtonElement);
    UI_RenderText(exitButtonElement);
}