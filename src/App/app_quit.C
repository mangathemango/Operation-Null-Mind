#include <app.h>
#include <particles.h>
#include <particle_emitterpresets.h>
#include <sound.h>

/* 
*   [Quit] This function is called when the program is about to quit.

?   Updated by Darren on 07/03/2025
*/
int App_Quit() {
    Sound_System_Cleanup();
    SDL_DestroyTexture(app.setup.screenTexture);
    SDL_DestroyRenderer(app.setup.renderer);
    SDL_DestroyWindow(app.setup.window);
    SDL_Quit();
    return 0;
}