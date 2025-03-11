#include <UI.h>
#include <UI_text.h>
#include <app.h>

static UIElement* startButtonElement = NULL;
static UIElement* exitButtonElement = NULL;
static UIElement* title1Element = NULL;
static UIElement* title2Element = NULL;

void Menu_PrepareTextures() {
    SDL_Color textColor = {255, 255, 255, 255};

    title1Element = UI_CreateText("OPERATION", (SDL_Rect) {125, 75 , 0, 0}, textColor, 3.0f, UI_TEXT_ALIGN_CENTER);
    title2Element = UI_CreateText("NULL MIND", (SDL_Rect) {125, 110, 0, 0}, textColor, 1.5f, UI_TEXT_ALIGN_CENTER);
    startButtonElement = UI_CreateText("Start",(SDL_Rect) {125, 180, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_CENTER);
    exitButtonElement = UI_CreateText("Exit",  (SDL_Rect) {125, 200, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_CENTER);
}

void Menu_Update() {
    UI_UpdateText(startButtonElement);
    UI_UpdateText(exitButtonElement);
    UI_UpdateText(title1Element);
    UI_UpdateText(title2Element);

    float targetY;
    if (startButtonElement->hovered) {
        UI_ChangeTextColor(startButtonElement, (SDL_Color) {255, 0, 0, 255});
    } else {
        UI_ChangeTextColor(startButtonElement, (SDL_Color) {255, 255, 255, 255});
    }
    if (startButtonElement->pressed) {
        app.state.currentScene = SCENE_GAME;
    }
}

void Menu_Render() {
    UI_RenderText(title1Element);
    UI_RenderText(title2Element);
    UI_RenderText(startButtonElement);
    UI_RenderText(exitButtonElement);
}