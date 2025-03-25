#include <interactable.h>
#include <SDL_ttf.h>
#include <UI_text.h>
#include <app.h>

int Interactable_Create(InteractableType type, Vec2 position) {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (!interactables[i].active) {
            interactables[i] = interactableData[type];
            interactables[i].position = position;
            interactables[i].active = true;
            interactables[i].textTexture = UI_CreateTextTexture(
                interactables[i].interactionText, 
                (SDL_Color){255, 255, 255, 255}, 
                app.resources.textFont
            );
            interactables[i].spriteTexture = interactabletextures[type];
            return i;
        }
    }
    return -1;
}

void Interactable_Reset() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        interactables[i].active = false;
        interactables[i].interactable = false;
        interactables[i].position = Vec2_Zero;
        interactables[i].data = NULL;
        interactables[i].interactionText = NULL;
        interactables[i].spriteTexture = NULL;
        interactables[i].textTexture = NULL;
        interactables[i].renderSize = Vec2_Zero;
        interactables[i].hitboxSize = Vec2_Zero;
        interactables[i].srcRect = (SDL_Rect) {-1, -1, -1, -1};
    }
}

void Interactable_Deactivate(int index) {
    interactables[index].active = false;
    interactables[index].interactable = false;
    interactables[index].position = Vec2_Zero;
    interactables[index].data = NULL;
    interactables[index].interactionText = NULL;
    interactables[index].spriteTexture = NULL;
    interactables[index].textTexture = NULL;
    interactables[index].renderSize = Vec2_Zero;
    interactables[index].hitboxSize = Vec2_Zero;
    interactables[index].srcRect = (SDL_Rect) {-1, -1, -1, -1};
}