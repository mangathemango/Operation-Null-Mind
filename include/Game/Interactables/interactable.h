#pragma once

#include <colliders.h>
#include <vec2.h>
#include <SDL_ttf.h>
#include <gun.h>
#include <UI_text.h>
#include <app.h>

#define MAX_INTERACTABLES 100

extern flag hasInteraction;
extern UIElement* interactionText;
typedef enum {
    INTERACTABLE_WEAPONCRATEOPEN,
    INTERACTABLE_WEAPONCRATECLOSED,
    INTERACTABLE_LOG,
    INTERACTABLE_EXIT,
    INTERACTABLE_WEAPON,
    INTERACTABLE_HEALTH,
    INTERACTABLE_HEALTH_MEDIUM,
    INTERACTABLE_HEALTH_LARGE,
    INTERACTABLE_ABILITIES,
    INTERACTABLE_COUNT
} InteractableType;


typedef struct {
    InteractableType type;

    int index; 
    bool active;
    bool enabled;
    bool interactable;

    Vec2 position;
    Vec2 renderSize;
    Vec2 hitboxSize;
    SDL_Rect srcRect;

    SDL_Texture* spriteTexture;
    SDL_Texture* textTexture;

    char* spritePath;
    char* interactionText;
    void (*callback)(void* data, int interactableIndex);
    void* data;
} Interactable;

typedef struct {
    int healthAmount;
    char* name;
} HealthData;

typedef struct
{
    int type;
    char* name;
    char* descriptionPro;
    char* descriptionCon;
    char* path;
} AbilityData;

extern HealthData healthData[3];
extern AbilityData abilityData[8];
extern Interactable interactables[MAX_INTERACTABLES];
extern Interactable interactableData[INTERACTABLE_COUNT];
extern SDL_Texture* interactabletextures[INTERACTABLE_COUNT];

int Interactable_Create(InteractableType type, Vec2 position);
void Interactable_CreateWeapon(Gun gun, Vec2 position);
void Interactable_CreateWeaponCrate(bool opened, Gun gun, Vec2 position);
void Interactable_CreateLog(int logIndex, Vec2 position);
void Interactable_Start();
void Interactable_Update();
void Interactable_Render();
void Interactable_RenderEndRoom();
void Interactable_RenderInteractionText();
void Interactable_Reset();
void Interactable_Deactivate(int index);
void Interactable_CreateHealth(Vec2 position);
void Interactable_CreateAbilties(Vec2 position);
