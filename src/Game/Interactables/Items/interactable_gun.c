#include <interactable.h>
#include <app.h>

void Interactable_CreateWeapon(Gun gun, Vec2 position) {
    SDL_Log("Creating interactable %s", GunList[gun].name);
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