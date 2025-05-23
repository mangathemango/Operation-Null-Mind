/**
 * @file colliders.c
 * @brief Collision detection system
 *
 * Provides functionality for hitbox-based collision detection
 * between game objects with layer-based filtering.
 *
 * @author Mango
 * @date 2025-03-02
 */

#include <colliders.h>
#include <stdio.h>

// Global collision registry
Collider* ColliderList[MAX_COLLIDABLES];
int ColliderCount = 0;

/**
 * [Start] Initializes the Colliders array.
 */
void Collider_Start() {
    for (int i = 0; i < MAX_COLLIDABLES; i++) {
        ColliderList[i] = NULL;
    }
    ColliderCount = 0;
}

/**
 * [Start] Registers a collider to the Colliders array.
 * This is so that every colliders can be checked by each other.
 * 
 * @param collider A pointer to the collider struct. For example: &player.state.collider
 * @param owner A pointer to the owner of the collider. For example: &player
 */
void Collider_Register(Collider* collider, void* owner) {
    if (ColliderCount >= MAX_COLLIDABLES) {
        printf("Error: Maximum collidables reached\n");
        return;
    }
    // Find first available slot
    int id = 0;
    while (id < MAX_COLLIDABLES) {
        if (ColliderList[id] == NULL) break;
        if (!ColliderList[id]->active) break;
        id++;
    }
    collider->active = true;
    collider->owner = owner;
    ColliderList[id] = collider;
    if (id >= ColliderCount) ColliderCount = id + 1;
}

/**
 * [PostUpdate] Checks if a collider is intersecting with any of its collider layers.
 * This function checks for collision between a collider and everything else in the
 * ColliderList array. Any colliders whose layer is not in the input collider's 
 * collidesWith section will be ignored.
 * 
 * @param collider The input collider
 * @param checkResult The checkResult of the collider, which includes 2 members:
 *   checkResult.objects: an array of detected colliders
 *   checkResult.count: number of collisions detected
 * @return true if collision detected, false otherwise
 */
bool Collider_Check(Collider* collider, ColliderCheckResult* checkResult) {
    if (!collider) return false; // Check if collider is NULL
    if (!collider->active) return false;
    
    bool selfFound = false;
    if (checkResult != NULL) {
        checkResult->count = 0;
    }

    // Check against all other collidables
    for (int i = 0; i < ColliderCount; i++) {
        if (ColliderList[i] == NULL) continue; // Skip empty slots
        if (ColliderList[i] == collider) {
            selfFound = true;
            continue;
        } // Skip input collider
        if (checkResult) if (checkResult->count >= MAX_COLLISIONS_PER_CHECK) continue;
        if (!ColliderList[i]->active) continue; // Skip inactive colliders
        if ((collider->collidesWith & ColliderList[i]->layer) == 0) continue; // Skip non intersecting layers
        
        if (SDL_HasIntersection(&collider->hitbox, &ColliderList[i]->hitbox)) {
            if (checkResult == NULL) return true;
            checkResult->objects[checkResult->count++] = ColliderList[i];
        }
    }
    
    if (!selfFound) {
        SDL_Log("Warning: Collider object not found in registry\n Please register the object with Collider_Register() before checking collisions\n"); 
        return false;
    }
    if (checkResult != NULL) {
        return checkResult->count > 0;
    }

    return false;
}

/**
 * @brief Deactivates a collider and resets its properties
 * 
 * @param collider The collider to reset
 */
void Collider_Reset(Collider* collider) {
    collider->active = false;
    collider->owner = NULL;
    collider->layer = COLLISION_LAYER_NONE;
    collider->collidesWith = COLLISION_LAYER_NONE;
    for (int i = 0; i < ColliderCount; i++) {
        if (ColliderList[i] == collider) {
            ColliderList[i] = NULL;
            break;
        }
    }
}