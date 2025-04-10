#include <interactable.h>
#include <app.h>
#include <random.h>


void Interactable_CreateHealth(Vec2 position) {

    int random = RandInt(INTERACTABLE_HEALTH, INTERACTABLE_HEALTH_LARGE);
    random = INTERACTABLE_HEALTH_LARGE;
    int index = Interactable_Create(random, position);

    interactables[index].textTexture = UI_CreateTextTexture(
        healthData[random - INTERACTABLE_HEALTH].name, 
        (SDL_Color){255, 255, 255, 255}, 
        app.resources.textFont
    );
    
    int* healthAmount = malloc(sizeof(int));
    *healthAmount = healthData[random - INTERACTABLE_HEALTH].healthAmount;
    interactables[index].data = healthAmount;
}