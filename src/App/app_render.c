#include <app.h>
#include <particle_emitterpresets.h>
#include <player.h>


int App_RenderMain() {
    Player_Render();
    ParticleEmitter_Render(test_emitter);
    return 0;
}


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