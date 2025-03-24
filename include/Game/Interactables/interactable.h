#pragma once

#include <colliders.h>
#include <vec2.h>
#include <SDL_ttf.h>

#define MAX_INTERACTABLES 100

typedef enum {
    INTERACTABLE_WEAPONCRATEOPEN,
    INTERACTABLE_WEAPONCRATECLOSED,
    // INTERACTABLE_LOG,
    // INTERACTABLE_EXIT,
    INTERACTABLE_WEAPON,
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

    SDL_Texture* spriteTexture;
    SDL_Texture* textTexture;

    char* spritePath;
    char* interactionText;
    void* data;
} Interactable;

extern Interactable interactables[MAX_INTERACTABLES];
extern Interactable interactableData[INTERACTABLE_COUNT];
extern SDL_Texture* interactabletextures[INTERACTABLE_COUNT];

void Interactable_Create(InteractableType type, Vec2 position);
void Interactable_Start();
void Interactable_Update();
void Interactable_Render();
void Interactable_Reset();
void Interactable_Deactivate(int index);
