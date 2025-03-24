#include <interactable_crate.h>
#include <app.h>

void Interactable_CreateWeaponCrate(Gun gun, Vec2 position) {
    Gun* crateGun = malloc(sizeof(Gun));
    *crateGun = gun;
    int index = Interactable_Create(INTERACTABLE_WEAPONCRATECLOSED, position);
    interactables[index].data = crateGun;
    interactables[index].textTexture = UI_CreateTextTexture(
        interactables[index].interactionText, 
        (SDL_Color){255, 255, 255, 255}, 
        app.resources.textFont
    );
} 