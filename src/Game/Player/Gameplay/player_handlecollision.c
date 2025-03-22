/**
 * @file player_handlecollision.c
 * @brief Handles player collisions with the environment and entities
 *
 * Contains functions for detecting and responding to player collisions
 * with walls, enemies, projectiles, and interactive objects.
 *
 * @date 2025-03-04
 */

#include <player.h>
#include <colliders.h>
#include <chunks.h>

/**
 * [Utility] Checks for and handles player collisions.
 * 
 * Detects if the player is colliding with any objects in the game world
 * and triggers the appropriate response based on collision type.
 * 
 * @return bool True if collision detected, false otherwise
 */
bool Player_DetectCollision() {
    ColliderCheckResult collisions;

    // This Collider_Check call will fill the collisions variable with all the colliders that the player is colliding with.
    // For more information, hover over Collider_Check in VSCode to view the function definition.
    if (!Collider_Check(&player.state.collider, &collisions)) return false;

    // The collisions array can then be looped through to check for specific layers.
    for (int i = 0; i < collisions.count; i ++) {
        if (collisions.objects[i]->layer == COLLISION_LAYER_ENVIRONMENT) {
            return true;
        }
        if (collisions.objects[i]->layer == COLLISION_LAYER_ENEMY && !player.state.dashing) {
            return true;
        }
        if (collisions.objects[i]->layer == COLLISION_LAYER_TRIGGER) {
            if (collisions.objects[i]->owner == &Chunk_HandlePlayerInsideRoom) {
                Chunk_HandlePlayerInsideRoom();
            }
            if (collisions.objects[i]->owner == &Chunk_HandlePlayerInsideHallway) {
                Chunk_HandlePlayerInsideHallway();
            }
            if(collisions.objects[i]->owner == &Chunk_HandlePlayerInsideEnd)
            {
                Chunk_HandlePlayerInsideEnd();
            }
        }
    }
    return false;
}