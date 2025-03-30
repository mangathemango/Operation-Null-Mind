/**
 * @file app_postupdate.c
 * @brief Post-update logic for the game loop
 *
 * Handles final updates at the end of each frame after
 * all other game systems have been updated.
 *
 * @author Mango
 * @date 2025-03-02
 */

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
            Interactable_Update();
            Camera_UpdatePosition();
            Game_Update();
            LevelTransition_Update();
            if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
                app.state.currentScene = SCENE_PAUSE;
            }
            if(player.state.currentHealth <= 0) {
                app.state.currentScene = SCENE_DEATH;
                Game_Restart();
            }
            break;
        case SCENE_PAUSE:
            Pause_Update();
            break;

        case SCENE_DEATH:
            Death_Update();
            break;
    }
    return 0;
}