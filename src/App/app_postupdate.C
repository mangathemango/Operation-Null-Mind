#include <app.h>
#include <player.h>
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
            // Updates the menu logic
            Menu_Update();
            break;
            
        case SCENE_GAME:
            Player_PostUpdate();
            Gun_Update();

            // Linearly interpolate the position of the camera towards the player
            // This basically means the camera moves smoothly towards the position of the player
            camera.position = Vec2_Lerp(
                camera.position, 
                player.state.position, 
                // Smooth time
                3 * Time->deltaTimeSeconds
            );
            break;
    }
    return 0;
}