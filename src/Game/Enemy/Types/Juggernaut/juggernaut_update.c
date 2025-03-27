/**
 * @file juggernaut_update.c
 * @brief Implements update logic for Juggernaut enemy type
 *
 * Contains the AI behavior and state updates for the Juggernaut enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>
#include <player.h>
#include <time_system.h>

/**
 * @brief [PostUpdate] Updates the Juggernaut enemy's state
 * 
 * This function is called each frame to update the Juggernaut enemy's behavior.
 * The Juggernaut is a heavily armored, slow, but powerful enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Juggernaut_Update(EnemyData* data) {
    JuggernautConfig* config = (JuggernautConfig*)data->config;
    // Specific behaviors will be implemented later
}
