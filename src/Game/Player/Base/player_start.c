#include <player.h>
#include <app.h>
/*
*   [Start] This function is called in App_Start().
?   It initializes the player's sprite texture. That's about it.
*/
int Player_Start() {
    Player_AnimationInit();
    player.state.currentGun = &Gun_Pistol;
    return 0;
}