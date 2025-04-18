/**
 * @file player_preupdate.c
 * @brief Pre-update logic for the player character
 *
 * Handles preliminary player state updates that need to occur
 * before main game systems are updated.
 *
 * Clears movement and location flags to ensure they're recalculated each frame,
 * and resets direction vector if not locked.
 * 
 * @author Mango
 * @date 2025-03-03
 */

#include <player.h>

/**
 * @brief [PreUpdate] Resets player state at the beginning of each frame
 * 
 * Clears movement and location flags to ensure they're recalculated each frame,
 * and resets direction vector if not locked.
 * 
 * @return int Status code (0 for success)
 */
int Player_Preupdate() {
    player.state.moving = false;
    player.state.insideHallway = false;
    player.state.insideRoom = false;
    player.state.insideEnd = false;
    player.state.currentGun = GunList[player.state.gunSlots[0]];
    player.state.previousGun = GunList[player.state.gunSlots[1]];
    if (!player.state.directionLocked)   player.state.direction = Vec2_Zero;
    if (!player.state.dashing) player.state.currentSpeed = 0;
    player.state.movementLocked = game.viewingLog != -1 || game.isTransitioning;
    return 0;
}