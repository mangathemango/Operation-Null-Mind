#include <app.h>
#include <player.h>
#include <environment.h>
#include <particle_emitterpresets.h>
#include <input.h>
#include <sound.h>

/* 
*   [PostUpdate] This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.

?   Updated by Mango on 03/03/2025
*/
int App_PostUpdate() {
    switch (app.state.currentScene) 
    {
        case SCENE_MENU:
            Menu_Update();
            break;
            
        case SCENE_GAME:
            Player_PostUpdate();
            Environment_Update();
            Gun_Update();
            break;
    }
    return 0;
}