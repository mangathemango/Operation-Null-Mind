// Written by Mango on 05/03/2025

#include <player.h>
#include <sound.h>
/*
    @file player_combat.c
*   This file contains the player's combat stuffs.
?   This includes attacking, taking damage, dying, etc.
*/

void Player_Shoot() {
    static Timer* shootTimer = NULL;
    if (shootTimer == NULL) {
        shootTimer = Timer_Create(0.1); // This is a temporary firerate placeholder
        Timer_Start(shootTimer);
    }
    if (Timer_IsFinished(shootTimer)) {
        Sound_Play_Effect(1);
        ParticleEmitter_ActivateOnce(player.state.currentGun->config.casingParticleEmitter);
        ParticleEmitter_ActivateOnce(player.state.currentGun->config.muzzleFlashEmitter);
        Timer_Start(shootTimer);
    }
}