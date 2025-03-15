#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL.h>
#include <stdbool.h>

#define MAX_COLLISIONS_PER_CHECK 10
#define MAX_COLLIDABLES 1024

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

/*
*   This struct represents a collider.
?   A collider is a hitbox that can be used to detect collisions between objects.
?   It is used to detect collisions between entities in the game.

    TODO: Add a system to follow/attach colliders to entities.
*/
typedef struct {
    SDL_Rect hitbox;            // The hitbox of the collider
    CollisionLayer layer;      // What layer this object belongs to
    CollisionLayer collidesWith; // Bitmask of layers this can collide with

    // These two fields are automatically set when you register them.
    void* owner;               // Pointer back to the entity
    bool active;               // Is this collidable active?
} Collider;

extern Collider* ColliderList[MAX_COLLIDABLES];
extern int ColliderCount;

/*
*   This struct is used to store the results of a Collider_Check call.
*
*    Members:
*    -   objects: An array of detected colliders.
*    -   count: Number of collisions detected
*/
typedef struct {
    Collider* objects[MAX_COLLISIONS_PER_CHECK]; // An array of detected colliders
    int count;                                  // Number of collisions detected
} ColliderCheckResult;


// Initialize the collision manager
void Collider_Start();

void Collider_Register(Collider* collidable, void* owner);

bool Collider_Check(Collider* collidableObject, ColliderCheckResult* result);

// Deactivates a collider
void Collider_Reset(Collider* collider);

#endif