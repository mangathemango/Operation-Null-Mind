// Written by Mango on 03/03/2025

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
    if (!player.state.directionLocked)   player.state.direction = Vec2_Zero;
    if (!player.state.dashing) player.state.currentSpeed = 0;
    return 0;
}