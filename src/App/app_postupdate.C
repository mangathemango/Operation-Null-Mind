#include <app.h>
#include <player.h>
#include <particle_emitterpresets.h>
#include <input.h>
#include <sound.h>

/* 
*   This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.
*/
int App_PostUpdate() {
    Player_PostUpdate();
    if (test_emitter != NULL) {
        if (player.state.dashing) {
            ParticleEmitter_ActivateOnce(test_emitter);
            Sound_Play_Effect(0); //Testing for dashing
        }
        test_emitter->position = player.state.position;
        ParticleEmitter_Update(test_emitter);
    }
    return 0;
}