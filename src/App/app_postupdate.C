#include <app.h>
#include <player.h>
#include <particle_emitterpresets.h>
#include <input.h>

/* 
*   This function is called every frame of the program AFTER App_Event_Handler().
?   This is suitable for rendering and updating the game.
*/
int App_PostUpdate() {
    Player_PostUpdate();
    if (test_emitter != NULL) {
        if (Input->mouse.leftButton.held) {
            ParticleEmitter_ActivateOnce(test_emitter);
        }
        test_emitter->position = Input->mouse.position;
        ParticleEmitter_Update(test_emitter);
    }
    Gun_Update();
    return 0;
}