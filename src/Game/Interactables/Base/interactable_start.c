#include <interactable.h>
#include <app.h>

Interactable interactables[MAX_INTERACTABLES];
SDL_Texture* interactabletextures[INTERACTABLE_COUNT];
UIElement* interactionText;
flag hasInteraction;

void Interactable_Start() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        interactables[i].active = false;
        interactables[i].index = i;
        interactables[i].spriteTexture = NULL;
        interactables[i].textTexture = NULL;
        interactables[i].renderSize = (Vec2) {0, 0};
        interactables[i].hitboxSize = (Vec2) {0, 0};
        interactables[i].srcRect =(SDL_Rect) {-1, -1, -1, -1};
    }

    for (int i = 0; i < INTERACTABLE_COUNT; i++) {
        if (interactableData[i].spritePath == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Interactable %d has no sprite path", i);
            continue;
        }
        interactabletextures[i] = IMG_LoadTexture(app.resources.renderer, interactableData[i].spritePath);
    }

    interactionText = UI_CreateText(
        "[Press E to interact]", 
        (SDL_Rect) {
            app.config.screen_width / 2, 
            app.config.screen_height - 20, 
            0, 
            0
        }, 
        (SDL_Color) {255, 255, 255, 255}, 
        1.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );
}