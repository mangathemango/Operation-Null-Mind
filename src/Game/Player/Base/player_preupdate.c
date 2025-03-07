#include <player.h>

int Player_Preupdate() {
    player.state.moving = false;
    if(!player.state.dashing) player.state.movementLocked = false;
    return 0;
}