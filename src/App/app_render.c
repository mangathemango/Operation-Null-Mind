#include <app.h>
#include <particle_emitterpresets.h>
#include <player.h>

/*
*   Handles the main rendering of the game, like players, game environments, etc.
?   This function is called inside App_Render().
*/
int App_RenderMain() {
    ParticleEmitter_Render(test_emitter);
    Player_Render();
    return 0;
}

/*
*   Renders the current frame of the game.
?   Includes the main rendering function and the final rendering to the window.
?   This function is called every frame after all the updating is complete
*/
int App_Render() {
    // Set render target to screen texture
    SDL_SetRenderTarget(app.setup.renderer, app.setup.screenTexture);

    // Clear the screen texture
    SDL_SetRenderDrawColor(app.setup.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.setup.renderer);
    
    App_RenderMain();

    // Reset render target to window
    SDL_SetRenderTarget(app.setup.renderer, NULL);
    
    // Draw screen texture to window (possibly scaled)
    SDL_RenderCopy(app.setup.renderer, app.setup.screenTexture, NULL, NULL);
    
    // Present final result
    SDL_RenderPresent(app.setup.renderer);
    return 0;
}