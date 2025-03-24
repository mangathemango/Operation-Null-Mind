#include <interactable.h>
#include <SDL_ttf.h>
#include <UI_text.h>
#include <app.h>

void Interactable_Create(InteractableType type, Vec2 position) {
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
            if (!interactables[i].textTexture){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Interactable %d has no text texture", type);
            }
            interactables[i].spriteTexture = interactabletextures[type];
            break;
        }
    }
}