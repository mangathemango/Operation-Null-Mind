#include <app.h>
#include <player.h>
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

    if (Input->keyboard.keys[SDL_SCANCODE_F5].pressed) {
        app.config.debug = !app.config.debug;
    }

    switch (app.state.currentScene) 
    {
        case SCENE_MENU:
            // Updates the menu logic
            Menu_Update();
            break;
        case SCENE_GAME:
            Player_PostUpdate();
            Gun_Update();
            Bullet_Update();
            Enemy_Update();
            Camera_UpdatePosition();
            if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
                app.state.currentScene = SCENE_PAUSE;
            }
            break;
        case SCENE_PAUSE:
            Pause_Update();
            break;
    }
    return 0;
}