// Written by Mango on 03/03/2025

#include <player.h>

/*
*   [PreUpdate] Reset player's moving state
*/
int Player_Preupdate() {
    player.state.moving = false;
    return 0;
}