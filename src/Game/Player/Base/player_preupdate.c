/**
 * @file player_preupdate.c
 * @brief Pre-update logic for the player character
 *
 * Handles preliminary player state updates that need to occur
 * before main game systems are updated.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <player.h>

/**
 * @brief [PreUpdate] Resets player state at the beginning of each frame
 * 
 * @return int Status code (0 for success)
 */
int Player_Preupdate() {
    player.state.moving = false;
    player.state.insideHallway = false;
    player.state.insideRoom = false;
    player.state.insideEnd = false;
    if (!player.state.directionLocked)   player.state.direction = Vec2_Zero;
    if (!player.state.dashing) player.state.currentSpeed = 0;
    return 0;
}