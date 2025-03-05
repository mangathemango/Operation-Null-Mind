#include <app.h>
#include <player.h>
#include <particle_emitterpresets.h>
#include <input.h>

/* 
*   This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.
*/
int App_PostUpdate() {
    // Set render target to screen texture
    SDL_SetRenderTarget(app.setup.renderer, app.setup.screenTexture);
    
    // Clear the screen texture
    SDL_SetRenderDrawColor(app.setup.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.setup.renderer);
    
    Player_PostUpdate();
    if (test_emitter != NULL) {
        if (Input->mouse.leftButton.held) {
            ParticleEmitter_ActivateOnce(test_emitter);
        }
        test_emitter->position = Input->mouse.position;
        ParticleEmitter_Update(test_emitter);
        ParticleEmitter_Render(test_emitter);
    }
    // Reset render target to window
    SDL_SetRenderTarget(app.setup.renderer, NULL);
    
    // Draw screen texture to window (possibly scaled)
    SDL_RenderCopy(app.setup.renderer, app.setup.screenTexture, NULL, NULL);
    
    // Present final result
    SDL_RenderPresent(app.setup.renderer);
    return 0;
}