#include <interactable.h>
#include <app.h>

Interactable interactables[MAX_INTERACTABLES];
SDL_Texture* interactabletextures[INTERACTABLE_COUNT];
UIElement* interactionText;
flag hasInteraction;
HealthData healthData[3] = {
    [0] = {20, "Medi-Stim"},
    [1] = {30, "Biofoam Spray"},
    [2] = {50, "Nano-Gel"}
};

AbilityData abilityData[8] =
{
    [ARMORED_UP] = 
    {
        .type = ARMORED_UP,
        .name = "Shield Up",
        .descriptionPro = "Take less damage from enemies",
        .descriptionCon = "Do less damage to enemies",
        .path = "Assets/Images/Icons/abilities/shieldUp.png",
    },
    [GHOST_LOAD] =
    {
        .type = GHOST_LOAD,
        .name = "Ghost Load",
        .descriptionPro = "Every 8th shot doesn't use ammo",
        .descriptionCon = "Chance to jam your gun",
        .path = "Assets/Images/Icons/abilities/ghostLoad.png",
    },
    [HEMO_CYCLE] =
    {
        .type = HEMO_CYCLE,
        .name = "Hemocycle",
        .descriptionPro = "Every 4th shot heals you",
        .descriptionCon = "Takes more damage from enemies",
        .path = "Assets/Images/Icons/abilities/hemocycle.png",
    },
    [KINETIC_ARMOR] =
    {
        .type = KINETIC_ARMOR,
        .name = "Kinetic Armor",
        .descriptionPro = "Chance to not take damage",
        .descriptionCon = "Loses 20 ammo everytime it activates",
        .path = "Assets/Images/Icons/abilities/kineticArmor.png",
    },
    [LAST_STAND] =
    {
        .type = LAST_STAND,
        .name = "Last Stand",
        .descriptionPro = "Gives a second life",
        .descriptionCon = "All abilites have a longer cooldown",
        .path = "Assets/Images/Icons/abilities/lastStand.png",
    },
    [ONE_MORE] = 
    {
        .type = ONE_MORE,
        .name = "One More",
        .descriptionPro = "Add a 3rd gun slot",
        .descriptionCon = "Reduce melee damage",
        .path = "Assets/Images/Icons/abilities/oneMore.png",
    },
    [OVER_PRESSURED] =
    {
        .type = OVER_PRESSURED,
        .name = "Overpressured",
        .descriptionPro = "Increase fire rate and projectile speed",
        .descriptionCon = "Every shot drains extra ammo",
        .path = "Assets/Images/Icons/abilities/overPressured.png",
    },
    [SCAVENGER] =
    {
        .type = SCAVENGER,
        .name = "Scavenger",
        .descriptionPro = "Ammo drops increased",
        .descriptionCon = "Reduce max ammo capacity",
        .path = "Assets/Images/Icons/abilities/scavenger.png",
    }
};

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