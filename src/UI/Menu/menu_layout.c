#include <UI.h>

static SDL_Texture* startButtonTexture = NULL;
static SDL_Texture* exitButtonTexture = NULL;
static SDL_Texture* titleTexture1 = NULL;
static SDL_Texture* titleTexture2 = NULL;

void Menu_PrepareTextures() {
    SDL_Color textColor = {255, 255, 255, 255};
    startButtonTexture = UI_CreateTextTexture("Start", textColor);
    exitButtonTexture = UI_CreateTextTexture("Exit", textColor);
    titleTexture1 = UI_CreateTextTexture("Operation", textColor);
    titleTexture2 = UI_CreateTextTexture("Null Mind", textColor);
}

void Menu_Render() {
    // Render titleArbata Compact
    UI_RenderTextureText(titleTexture1, (Vec2){50, 50}, 3.0f);
    UI_RenderTextureText(titleTexture2, (Vec2){90, 100}, 1.5f);

    // Render buttons
    UI_RenderTextureText(startButtonTexture, (Vec2){105, 180}, 1.0f);
    UI_RenderTextureText(exitButtonTexture, (Vec2){110, 200}, 1.0f);
}