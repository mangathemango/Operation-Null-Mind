#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL.h>
#include <stdbool.h>

#define MAX_COLLISIONS_PER_CHECK 10
#define MAX_COLLIDABLES 256
extern Collider* Collidables[MAX_COLLIDABLES];

// Collision layers as bitmasks for efficient checking
typedef enum {
    COLLISION_LAYER_NONE                = 0,
    COLLISION_LAYER_PLAYER              = 1 << 0,
    COLLISION_LAYER_ENVIRONMENT         = 1 << 1,
    COLLISION_LAYER_ENEMY               = 1 << 2,
    COLLISION_LAYER_ITEM                = 1 << 3,
    COLLISION_LAYER_ENEMY_PROJECTILE    = 1 << 4,
    COLLISION_LAYER_PLAYER_PROJECTILE   = 1 << 5,
} CollisionLayer;

// Each collidable object
typedef struct {
    SDL_Rect hitbox;
    CollisionLayer layer;      // What layer this object belongs to
    CollisionLayer collidesWith; // Bitmask of layers this can collide with
    void* owner;               // Pointer back to the entity
    bool active;               // Is this collidable active?
} Collider;


typedef struct {
    Collider* objects[MAX_COLLISIONS_PER_CHECK];
    int count;
} ColliderCheckResult;


// Initialize the collision manager
bool Collider_Start();

// Register a new collidable and return its ID for later reference
int Collider_Register(Collider* collidable, void* owner);

bool Collider_Check(Collider* collidableObject, ColliderCheckResult* result);

// Deactivates a collider
void Collider_Reset(Collider* collider);

#endif