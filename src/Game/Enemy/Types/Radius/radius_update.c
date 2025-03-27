/**
 * @file radius_update.c
 * @brief Implements update logic for Radius enemy type
 *
 * Contains the AI behavior and state updates for the Radius enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>
#include <player.h>
#include <time_system.h>

/**
 * @brief [PostUpdate] Updates the Radius enemy's state
 * 
 * This function is called each frame to update the Radius enemy's behavior.
 * The Radius enemy has powerful area-of-effect attacks.
 * 
 * @param data Pointer to the enemy data structure
 */
void Radius_Update(EnemyData* data) {
    RadiusConfig* config = (RadiusConfig*)data->config;
    // Specific behaviors will be implemented later
}
