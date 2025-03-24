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
            if (!interactables[i].textTexture){
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Interactable %d has no text texture", type);
            }
            interactables[i].spriteTexture = interactabletextures[type];
            return i;
        }
    }
    return -1;
}

void Interactable_CreateWeapon(Gun gun, Vec2 position) {
    int index = Interactable_Create(INTERACTABLE_WEAPON, position);
    interactables[index].data = &GunList[gun];
    interactables[index].interactionText = GunList[gun].name;
    interactables[index].textTexture = UI_CreateTextTexture(
        interactables[index].interactionText, 
        (SDL_Color){255, 255, 255, 255}, 
        app.resources.textFont
    );
    interactables[index].spriteTexture = GunList[gun].resources.animation->spritesheet;
    interactables[index].srcRect = Vec2_ToRect(
        Vec2_Zero,
        GunList[gun].animData.frameSize
    );
    interactables[index].renderSize = GunList[gun].animData.spriteSize;
}