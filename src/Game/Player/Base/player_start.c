// Updated by Mango on 08/03/2025

#include <player.h>
#include <app.h>
/*
*   [Start] This function is called in App_Start().
?   It initializes the player's animations and sets the player's current gun to the pistol.
*/
int Player_Start() {
    Player_AnimationInit();
    Player_SwitchGun(&Gun_Pistol);
    player.resources.dashParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Dash);
    player.resources.dashParticleEmitter->selfReference = &player.resources.dashParticleEmitter;

    player.resources.dashCooldownTimer = Timer_Create(player.stats.dashCooldown);
    player.resources.dashDurationTimer = Timer_Create(player.stats.dashDuration);
    Timer_Start(player.resources.dashCooldownTimer);
    
    Collider_Register(&player.state.collider, &player);
    return 0;
}