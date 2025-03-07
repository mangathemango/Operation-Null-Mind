#include <app.h>
#include <player.h>
#include <particle_emitterpresets.h>
#include <input.h>
#include <sound.h>

/* 
*   [PostUpdate] This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.
*/
int App_PostUpdate() {
    Player_PostUpdate();
    Gun_Update();
    return 0;
}