// Written by Mango on 03/03/2025

#include <player.h>

/*
*   [PreUpdate] Reset player's moving state
*/
int Player_Preupdate() {
    player.state.moving = false;
    if (!player.state.directionLocked)   player.state.direction = Vec2_Zero;
    if (!player.state.dashing) player.state.currentSpeed = 0;
    return 0;
}