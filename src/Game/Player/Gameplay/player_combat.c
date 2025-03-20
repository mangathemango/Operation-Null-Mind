// Written by Mango on 05/03/2025

#include <player.h>
#include <sound.h>
#include <random.h>

/*
    @file player_combat.c
*   This file contains the player's combat stuffs.
?   This includes attacking, taking damage, dying, etc.
*/

void Player_Shoot() {
    if (!Timer_IsFinished(player.resources.shootCooldownTimer)) return;
    Sound_Play_Effect(1);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.muzzleFlashEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun->resources.bulletPreset);
    Timer_Start(player.resources.shootCooldownTimer);
    
}

void Player_SwitchGun(GunData* gun) {
    player.state.currentGun = gun;
    player.resources.shootCooldownTimer = Timer_Create(60.0f/gun->stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}