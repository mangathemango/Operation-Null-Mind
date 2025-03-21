#include <app.h>
#include <player.h>
#include <particle_emitterpresets.h>
#include <input.h>
#include <sound.h>
#include <bullet.h>
#include <enemy_types.h>

/**
 * @brief [PostUpdate] Main game update routine
 * 
 * This function is called every frame of the program AFTER App_Event_Handler().
 * This is suitable for rendering and updating the game.
 * 
 * @return int Status code (0 for success)
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
            EnemyManager_Update();
            Enemy_Update();
            Camera_UpdatePosition();
            break;
    }
    return 0;
}