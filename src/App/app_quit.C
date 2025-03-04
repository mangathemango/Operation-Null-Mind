#include <app.h>
#include <particles.h>
#include <particle_emitterpresets.h>
/* 
*   This function is called when the program is about to quit.
*/
int App_Quit() {
    ParticleEmitter_DestroyEmitter(test_emitter);
    SDL_DestroyTexture(app.setup.screenTexture);
    SDL_DestroyRenderer(app.setup.renderer);
    SDL_DestroyWindow(app.setup.window);
    SDL_Quit();
    return 0;
}