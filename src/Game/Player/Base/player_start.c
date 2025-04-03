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
 * Also sets up collision, particle effects, and timers.
 * 
 * @return int Status code (0 for success)
 */
int Player_Start() {
    Player_AnimationInit();
    player.resources.dashParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Dash);
    player.resources.dashParticleEmitter->selfReference = &player.resources.dashParticleEmitter;
    player.resources.crashOut = ParticleEmitter_CreateFromPreset(ParticleEmitter_Fire);

    player.resources.dashCooldownTimer = Timer_Create(player.stats.dashCooldown);
    player.resources.dashDurationTimer = Timer_Create(player.stats.dashDuration);
    player.resources.skillResources.crashOutCooldown = Timer_Create(player.stats.skillStat.crashOutCooldown);
    player.resources.skillResources.crashOutDuration = Timer_Create(player.stats.skillStat.crashOutDuration);
    Timer_Start(player.resources.dashCooldownTimer);
    player.resources.skillResources.crashOutCooldown->finished = true; // Start with crashout off cooldown
    Collider_Register(&player.state.collider, &player);
    player.state.currentGun = GunList[player.state.gunSlots[0]];
    player.resources.shootCooldownTimer = Timer_Create(60.0f/player.state.currentGun.stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);


    player.state.currentHealth = player.stats.maxHealth;

    //skill related stuff
    player.stats.enemiesKilled = 0;
    if(player.state.skillState.scavenger == true)
    {
        scavenger();
    }
    player.state.currentAmmo = player.stats.maxAmmo;
    return 0;
}