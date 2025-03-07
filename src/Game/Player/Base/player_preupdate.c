#include <player.h>

int Player_Preupdate() {
    player.state.moving = false;
    if(!player.state.dashing) player.state.movementLocked = false;
    player.state.direction = Vec2_Zero;
    return 0;
}