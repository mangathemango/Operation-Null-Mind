/**
 * @file colliders.h
 * This file contains the declarations for the collision manager.
 * The collision manager is responsible for detecting collisions between entities in the game.
 * @author Mango, Tony and Darren
 * @date 2025-03-09
 * @section usage How to use the collider system:
 * TLDR: Create Collider struct somewhere, register it, check for collisions, and handle the collisions.
 * 
 * @subsection usage_step1 Step 1: Create a collider struct for your entity.  
 * Note: the collider needs to be stored in a memory that's reusable. (i.e static/global variables)
 * 
 * @subsubsection usage_step1_example Example:
 * ```c
 *     // Static variables
 *     static Collider playerCollider = {
 *         // (If you're making the hitbox follow something, only the last two values (width and height) matter)
 *         .hitbox = {0, 0, 20, 20}, 
 *         .layer = COLLISION_LAYER_PLAYER,
 *         .collidesWith = COLLISION_LAYER_ENVIRONMENT 
 *                       | COLLISION_LAYER_ENEMY,
 *     };
 * 
 *     // Global variables (View PlayerData struct and player variable)
 *     player.state.collider = {
 *         .hitbox = {0, 0, 20, 20}, 
 *         .layer = COLLISION_LAYER_PLAYER,
 *         .collidesWith = COLLISION_LAYER_ENVIRONMENT 
 *                       | COLLISION_LAYER_ENEMY,
 *     };
 * ```
 * This collider will check for collision with environment and enemies.
 *
 * @subsection usage_step2 Step 2: Register the collider
 * Register the collider with the collision manager:
 * @subsubsection usage_step2_example Example:
 * ```c
 * Collider_Register(&playerCollider, &player);
 * ```
 * This will add the collider to the list of colliders that the collision manager checks.
 *
 * @subsection usage_step3 Step 3: Check for collisions
 * Check for collisions with the collider:
 * @subsubsection usage_step3_example Example:
 * ```c
 * ColliderCheckResult result;
 * Collider_Check(&playerCollider, &result);
 * ```
 *
 * This will check for collisions with the collider and store the results in the result struct.
 * After that, you can do something with the detected collisions:
 *
 * ```c
 * for (int i = 0; i < result.count; i++) {
 *     Collider* collisionObject = result.objects[i];
 *     // Do something with the collision object
 *     switch(collisionObject->layer) {
 *         case COLLISION_LAYER_ENVIRONMENT:
 *             // Handle collision with environment, for example stopping movement
 *             break;
 *         case COLLISION_LAYER_ENEMY:
 *             // Handle collision with enemy, for example taking damage
 *             break;
 *     }
 * }
 * ```
 */

#pragma once

#include <SDL.h>
#include <stdbool.h>

#define MAX_COLLISIONS_PER_CHECK 20
#define MAX_COLLIDABLES 1024

// Collision layers as bitmasks for efficient checking
typedef enum {
    COLLISION_LAYER_NONE                = 0,        // 00000000
    COLLISION_LAYER_PLAYER              = 1 << 0,   // 00000001
    COLLISION_LAYER_ENVIRONMENT         = 1 << 1,   // 00000010
    COLLISION_LAYER_ENEMY               = 1 << 2,   // 00000100
    COLLISION_LAYER_TRIGGER             = 1 << 3,   // 00001000
    COLLISION_LAYER_ENEMY_PROJECTILE    = 1 << 4,   // 00010000
    COLLISION_LAYER_PLAYER_PROJECTILE   = 1 << 5,   // 00100000
} CollisionLayer;

/**
 * This struct represents a collider.
 * A collider is a hitbox that can be used to detect collisions between objects.
 * It is used to detect collisions between entities in the game.
 *
 * @todo Add a system to follow/attach colliders to entities.
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

/**
 * This struct is used to store the results of a Collider_Check call.
 *
 * @var objects An array of detected colliders.
 * @var count Number of collisions detected
 */
typedef struct {
    Collider* objects[MAX_COLLISIONS_PER_CHECK]; // An array of detected colliders
    int count;                                  // Number of collisions detected
} ColliderCheckResult;


/** Initialize the collision manager */
void Collider_Start();

/** 
 * Register a collider with the collision manager
 * @param collidable The collider to register
 * @param owner The entity that owns this collider
 */
void Collider_Register(Collider* collidable, void* owner);

/**
 * Check for collisions with a collider
 * @param collidableObject The collider to check
 * @param result Where to store the collision results
 * @return true if any collisions were detected
 */
bool Collider_Check(Collider* collidableObject, ColliderCheckResult* result);

/** 
 * Deactivates a collider
 * @param collider The collider to deactivate
 */
void Collider_Reset(Collider* collider);