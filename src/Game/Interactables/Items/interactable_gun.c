#include <interactable.h>
#include <app.h>
#include <string.h>
#include <stdio.h>
#include <gun.h>

void Interactable_CreateWeapon(GunSlot gunData, Vec2 position) {
    int index = Interactable_Create(INTERACTABLE_WEAPON, position);
    GunSlot* data = malloc(sizeof(GunSlot));
    memcpy(data, &gunData, sizeof(GunSlot));
    interactables[index].data = data;
    interactables[index].interactionText = GunList[gunData.gun].name;
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