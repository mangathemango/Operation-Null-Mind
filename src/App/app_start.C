#include <app.h>
#include <player.h>
#include <initialize_SDL.h>
#include <random.h>
#include <particle_emitterpresets.h>
/*
*   This function is called at the start of the program.
?   It initializes everything needed for the program to run. Like the window, renderer, and later, the game.
*/
int App_Start() {
    RandomInit();
    if (Initialize_SDL()) return 1;
    if (Player_Start()) return 1;
    Gun_Start();
    test_emitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Default);
    test_emitter->selfReference = &test_emitter;
    return 0;
}