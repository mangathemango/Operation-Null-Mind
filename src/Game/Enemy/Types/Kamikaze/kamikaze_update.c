/**
 * @file echo_update.c
 * @brief Implements update logic for Echo enemy type
 *
 * Contains the AI behavior and state updates for the Echo enemy,
 * which uses a teleportation-based movement pattern.
 *
 * @author Mango
 * @date 2025-03-06
 */

#include <enemy_echo.h>
#include <player.h>
#include <time_system.h>

/**
 * @brief [PostUpdate] Updates the Echo enemy's state
 * 
 * This function is called each frame to update the Echo enemy's behavior,
 * including its teleportation movement pattern and attack logic.
 * 
 * @param data Pointer to the enemy data structure
 */
void Kamikaze_Update(EnemyData* data) {
    if (data->state.isDead) return;

    if (Vec2_Distance(data->state.position, player.state.position) < 500) {
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
    } else {
        data->state.direction = Vec2_Zero;
    }
}