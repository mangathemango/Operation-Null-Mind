/*
    @file colliders.h
*   This file contains the declarations for the collision manager.
*   The collision manager is responsible for detecting collisions between entities in the game.

?   How to use the collider system:
?   TLDR: Create Collider struct somewhere, register it, check for collisions, and handle the collisions.
? 
?   Step 1: Create a collider struct for your entity.
?       This doesn't have to be inside an entity struct. (Though, this would be good for organization)
?       But yeah, it just needs to exist in a memory that's reusable. (i.e static/global variables)
?   Example:
?       static Collider playerCollider = {
?           // (If you're making the hitbox follow something, only the last two values (width and height) matter)
?           .hitbox = {0, 0, 20, 20}, 
?           .layer = COLLISION_LAYER_PLAYER,
?           .collidesWith = COLLISION_LAYER_ENVIRONMENT 
?                         | COLLISION_LAYER_ENEMY,
?       };
?   This collider will check for collision with environment and enemies.
?
?   Step 2: Register the collider with the collision manager.
?       Collider_Register(&playerCollider, playerEntity);
?   This will add the collider to the list of colliders that the collision manager checks.
?
?   Step 3: Check for collisions with the collider.
?       ColliderCheckResult result;
?       Collider_Check(&playerCollider, &result); 
?
?   This will check for collisions with the collider and store the results in the result struct.
?   After that, you can do something with the detected collisions.
?
?       for (int i = 0; i < result.count; i++) {
?           Collider* collisionObject = result.objects[i];
?           // Do something with the collision object
?           switch(collisionObject->layer) {
?               case COLLISION_LAYER_ENVIRONMENT:
?                   // Handle collision with environment, for example stopping movement
?                   break;
?               case COLLISION_LAYER_ENEMY:
?                   // Handle collision with enemy, for example taking damage
?                   break;
?           }
?       }
?       
?   This will check for collisions with the collider and store the results in the result struct.
*/

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