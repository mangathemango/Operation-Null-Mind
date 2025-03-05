#include <player.h>

int Player_Preupdate() {
    player.state.moving = false;
    return 0;
}