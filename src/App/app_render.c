#include <app.h>
#include <particle_emitterpresets.h>
#include <player.h>
#include <environment.h>
#include <debug.h>
/*
*   [Render] Handles the main rendering of the game, like players, game environments, etc.
?   This function is called inside App_Render().

?   Updated by Mango on 05/03/2025
*/
int App_RenderMain() {
    switch (app.state.currentScene)
    {
        case SCENE_MENU:
            Menu_Render();
            break;
        
        case SCENE_GAME:
            Chunk_Render(testChunk, (Vec2) {0, 0});
            Player_Render();
            Gun_Render();
            Debug_RenderHitboxes();
            break;
    }
    Debug_RenderFPSCount();
    return 0;
}

/*
*   [Render] Renders the current frame of the game.
?   Includes the main rendering function and the final rendering to the window.
?   This function is called every frame after all the updating is complete
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