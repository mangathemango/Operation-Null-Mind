#include <interactable_crate.h>
#include <app.h>

void Interactable_CreateWeaponCrate(bool opened, GunSlot gun, Vec2 position) {
    GunSlot* crateGun = malloc(sizeof(Gun_Type));
    *crateGun = gun;
    int index;
    if (!opened) index = Interactable_Create(INTERACTABLE_WEAPONCRATECLOSED, position);
    else index = Interactable_Create(INTERACTABLE_WEAPONCRATEOPEN, position);
    interactables[index].data = crateGun;
    interactables[index].textTexture = UI_CreateTextTexture(
        interactables[index].interactionText, 
        (SDL_Color){255, 255, 255, 255}, 
        app.resources.textFont
    );
} 