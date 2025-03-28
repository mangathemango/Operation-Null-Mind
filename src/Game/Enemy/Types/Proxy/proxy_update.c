/**
 * @file proxy_update.c
 * @brief Implements update logic for Proxy enemy type
 *
 * Contains the AI behavior and state updates for the Proxy enemy.
 *
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>

/**
 * @brief [PostUpdate] Updates the Proxy enemy's state
 * 
 * This function is called each frame to update the Proxy enemy's behavior.
 * The Proxy enemy deploys at a position and can act as a decoy or amplifier
 * for other enemies.
 * 
 * @param data Pointer to the enemy data structure
 */
void Proxy_Update(EnemyData* data) {
    ProxyConfig* config = (ProxyConfig*)data->config;
    // Specific behaviors will be implemented later
    data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
}
