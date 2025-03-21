// Written by Mango on 05/03/2025

#include <player.h>
#include <sound.h>
#include <random.h>

/**
 * @file player_combat.c
 * @brief Handles player combat functionality
 * 
 * This file contains the player's combat stuffs.
 * This includes attacking, taking damage, dying, etc.
 */

/**
 * @brief Makes the player shoot their current weapon
 */
void Player_Shoot() {
    if (!Timer_IsFinished(player.resources.shootCooldownTimer)) return;
    Sound_Play_Effect(1);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.muzzleFlashEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.bulletPreset);
    Timer_Start(player.resources.shootCooldownTimer);
    
}

/**
 * @brief Changes the player's active weapon
 * 
 * @param gun Pointer to the gun data to switch to
 */
void Player_SwitchGun(GunData* gun) {
    player.state.currentGun = gun;
    player.resources.shootCooldownTimer = Timer_Create(60.0f/gun->stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}