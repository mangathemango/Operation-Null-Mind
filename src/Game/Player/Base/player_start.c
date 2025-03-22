/**
 * @file player_start.c
 * @brief Initializes the player character
 *
 * Sets up the player's initial state, loads resources,
 * and prepares the player character for gameplay.
 * 
 * @author Mango
 * @date 2025-03-02
 */

#include <player.h>
#include <app.h>

/**
 * @brief [Start] Initializes the player's systems
 * 
 * This function is called in App_Start().
 * It initializes the player's animations and sets the player's current gun to the pistol.
 * 
 * @return int Status code (0 for success)
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