#include <app.h>
#include <player.h>
#include <environment.h>
#include <particle_emitterpresets.h>
#include <input.h>
#include <sound.h>
#include <bullet.h>

/* 
*   [PostUpdate] This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.

?   Updated by Mango on 03/03/2025
*/
int App_PostUpdate() {
    Player_PostUpdate();
    Environment_Update(); // Add this line to update the environment
    Gun_Update();
    Bullet_Update();
    return 0;
}