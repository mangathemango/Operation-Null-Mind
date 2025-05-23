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
#include <controls.h>
#include <win.h> // Added for Win_Update function
#include <settings.h>

/**
 * @brief [PostUpdate] Main game update routine
 * 
 * This function is called every frame of the program AFTER App_Event_Handler(). 
 * This is suitable for rendering and updating the game.
 * 
 * @return int Status code (0 for success)
 */
int App_PostUpdate() {
    switch (app.state.currentScene) 
    {
        case SCENE_MENU:
            // Updates the menu logic
            Menu_Update();
            break;
        case SCENE_MISSION_BRIEFING:
            Mission_Update();
            LevelTransition_Update();
            Game_Update();
            break;
        case SCENE_CONTROLS:
            Controls_Update();
            break;
        case SCENE_GAME:
            Player_PostUpdate();
            Player_UpdateSkill();
            Gun_Update();
            Bullet_Update();
            EnemyManager_Update();
            Enemy_Update();
            Interactable_Update();
            Camera_UpdatePosition();
            Game_Update();
            Game_QueueNextMusic();
            LevelTransition_Update();
            if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
                app.state.currentScene = SCENE_PAUSE;
            }
            if(player.state.currentHealth <= 0) {
                if(player.state.skillState.lastStand == false)
                {
                    // For debugging win screen, going to SCENE_WIN instead of SCENE_DEATH
                    app.state.currentScene = SCENE_DEATH; // Temporarily show win screen for debugging
                    Sound_Play_Music("Assets/Audio/Music/return0 lofi death music BEGINNING.wav", -1);
                }
            }
            break;
        case SCENE_PAUSE:
            if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
                app.state.currentScene = SCENE_PAUSE;
            }
            Game_QueueNextMusic();
            Pause_Update();
            break;

        case SCENE_DEATH:
            Death_Update();
            break;
            
        case SCENE_WIN:
            Win_Update();
            break;
            
        case SCENE_SETTINGS:
            Settings_Update();
            break;

        default:
            break;
    }
    if (Input_IsActionPressed(ACTION_TOGGLE_FULLSCREEN)) {
        // Store current render target
        SDL_Texture* currentTarget = SDL_GetRenderTarget(app.resources.renderer);
        
        app.config.window_fullscreen = !app.config.window_fullscreen;
        SDL_SetWindowFullscreen(app.resources.window, 
            app.config.window_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
        
        // Get the new window size after fullscreen change
        int windowWidth, windowHeight;
        SDL_GetWindowSize(app.resources.window, &windowWidth, &windowHeight);
        
        // Update viewport to match new window size
        SDL_Rect viewport = {0, 0, windowWidth, windowHeight};
        SDL_RenderSetViewport(app.resources.renderer, &viewport);
        
        // Update logical size to maintain proper scaling
        SDL_RenderSetLogicalSize(app.resources.renderer, app.config.screen_width, app.config.screen_height);
        
        
        // Restore the render target
        SDL_SetRenderTarget(app.resources.renderer, currentTarget);
        
        // Center the window if going back to windowed mode
        if (!app.config.window_fullscreen) {
            SDL_SetWindowSize(app.resources.window, app.config.window_width, app.config.window_height);
            SDL_SetWindowPosition(app.resources.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        }
        RadiusExplosionIndicator = CreateCircleTexture(
            RadiusConfigData.explosionRadius,
            (SDL_Color){255, 0, 0, 255}
        );
    }
    return 0;
}