#include <colliders.h>
#include <vec2.h>

#define MAX_INTERACTABLES 100

typedef enum {
    INTERACTABLE_WEAPONCRATE,
    INTERACTABLE_WEAPON,
    INTERACTABLE_LOG,
    INTERACTABLE_EXIT
} InteractableType;


typedef struct {
    InteractableType type;

    int index; 
    bool active;
    Collider trigger;
    SDL_Texture* texture;
    SDL_Rect size;
} Interactable;

extern Interactable interactables[MAX_INTERACTABLES];

void Interactable_Create(InteractableType type, Vec2 position);
void Interactable_Start();
void Interactable_Update();
void Interactable_Render();
void Interactable_Reset();
void Interactable_Deactivate(int index);
