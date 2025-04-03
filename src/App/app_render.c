/**
 * @file app_render.c
 * @brief Main rendering pipeline
 *
 * Manages the overall rendering process for the game,
 * coordinating which elements are drawn based on the current
 * game state and scene.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <app.h>
#include <particle_emitterpresets.h>
#include <player.h>

#include <debug.h>
#include <bullet.h>
#include <input.h>

/**
 * @brief [Render] Handles the main rendering of the game, like players, game environments, etc.
 * 
 * This function is called inside App_Render().
 * 
 * @return int Status code (0 for success)
 */
int App_RenderMain() {
    switch (app.state.currentScene)
    {
        case SCENE_MENU:
            Menu_Render();
            break;

        case SCENE_DEATH:
            Death_Render();
            break;
        
        case SCENE_PAUSE:
            Map_Render();
            Interactable_Render();
            Enemy_Render();
            Player_Render();
            Interactable_RenderEndRoom();
            Gun_Render();
            Bullet_Render();
            Debug_RenderHitboxes();
            Interactable_RenderInteractionText();
            HUD_Render();
            Log_Render();
            LevelTransition_Render();
            Pause_Render();
            break;

        case SCENE_GAME:
            Map_Render();
            Interactable_Render();
            Enemy_Render();
            Player_Render();
            Interactable_RenderEndRoom();
            Gun_Render();
            Bullet_Render();
            Debug_RenderHitboxes();
            Interactable_RenderInteractionText();
            HUD_Render();
            Log_Render();
            LevelTransition_Render();
            break;
    }
    Debug_RenderFPSCount();
    Debug_RenderSpikeCount();
    Debug_RenderCurrentChunk();

    SDL_Rect cursorRect = Vec2_ToCenteredRect(
        Input->mouse.position,
        (Vec2) {7, 7} // Size of the cursor texture
    );
    
    SDL_RenderCopy(app.resources.renderer, app.resources.cursorTexture, NULL, &cursorRect);
    return 0;
}

/**
 * @brief [Render] Renders the current frame of the game.
 * 
 * Includes the main rendering function and the final rendering to the window.
 * This function is called every frame after all the updating is complete.
 * 
 * @return int Status code (0 for success)
 */
int App_Render() {
    // Set render target to screen texture
    SDL_SetRenderTarget(app.resources.renderer, app.resources.screenTexture);

    // Clear the screen texture (This is also the background color btw)
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 50);
    SDL_RenderClear(app.resources.renderer);
    
    App_RenderMain();

    // Reset render target to window
    SDL_SetRenderTarget(app.resources.renderer, NULL);
    
    // Draw screen texture to window (possibly scaled)
    SDL_RenderCopy(app.resources.renderer, app.resources.screenTexture, NULL, NULL);
    
    // Present final result
    SDL_RenderPresent(app.resources.renderer);
    return 0;
}