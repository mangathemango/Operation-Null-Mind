#include <player.h>
#include <app.h>
/*
*   [Start] This function is called in App_Start().
?   It initializes the player's animations and sets the player's current gun to the pistol.
*/
int Player_Start() {
    Player_AnimationInit();
    player.state.currentGun = &Gun_Pistol;
    player.config.dashParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Dash);
    player.config.dashParticleEmitter->selfReference = &player.config.dashParticleEmitter;
    return 0;
}