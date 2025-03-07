#include <player.h>

/*
*   [PreUpdate] Reset player's moving state
*/
int Player_Preupdate() {
    player.state.moving = false;
    return 0;
}