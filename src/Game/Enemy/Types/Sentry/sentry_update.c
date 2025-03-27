/**
 * @file sentry_update.c
 * @brief Implements update logic for Sentry enemy type
 *
 * Contains the AI behavior and state updates for the Sentry enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>
#include <player.h>
#include <time_system.h>

/**
 * @brief [PostUpdate] Updates the Sentry enemy's state
 * 
 * This function is called each frame to update the Sentry enemy's behavior.
 * The Sentry is a stationary enemy that guards a specific area.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sentry_Update(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    // Specific behaviors will be implemented later
}
