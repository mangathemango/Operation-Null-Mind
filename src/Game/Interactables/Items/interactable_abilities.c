#include <interactable.h>
#include <app.h>
#include <random.h>

void Interactable_CreateAbilties(Vec2 position) {
    int index = Interactable_Create(INTERACTABLE_ABILITIES, position);
    
    int random = RandInt(ARMORED_UP, SCAVENGER);
    interactables[index].textTexture = UI_CreateTextTexture(
        abilityData[random].name, 
        (SDL_Color){255, 255, 255, 255}, 
        app.resources.textFont
    );

    SDL_Texture * abilityTexture = IMG_LoadTexture(app.resources.renderer, abilityData[random].path);
    interactables[index].spriteTexture = abilityTexture;

    int* abilitesType = malloc(sizeof(int));
    *abilitesType = abilityData[random].type;
    interactables[index].data = abilitesType;
}