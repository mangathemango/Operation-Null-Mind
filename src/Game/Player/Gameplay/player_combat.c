/**
 * @file player_combat.c
 * @brief Implements player combat functionality
 *
 * Handles player attacks, weapon use, and combat interactions
 * with enemies and the environment.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <player.h>
#include <sound.h>
#include <random.h>
#include <interactable.h>
#include <interactable_crate.h>

/**
 * @brief [Utility] Makes the player shoot their current weapon
 * 
 * Activates the shooting sequence, including sound effects, particle
 * effects for muzzle flash and casings, and creating bullet projectiles.
 */
void Player_Shoot() {
    if (!Timer_IsFinished(player.resources.shootCooldownTimer)) return;
    Sound_Play_Effect(1);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.muzzleFlashEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.bulletPreset);
    Timer_Start(player.resources.shootCooldownTimer);
    
}

/**
 * @brief [Utility] Changes the player's active weapon
 * 
 * Sets the currently active gun and resets the cooldown timer
 * based on the new weapon's fire rate.
 * 
 * @param gun Pointer to the gun data to switch to
 */
void Player_SwitchGun(Gun guntype) {
    player.state.currentGun = GunList[guntype];
    player.resources.shootCooldownTimer = Timer_Create(60.0f/GunList[guntype].stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}

void Player_PickUpGun(void* data, int interactableIndex) {
    GunData* gun = data;
    Interactable_CreateWeapon(player.state.currentGun.type, player.state.position);
    Interactable_Deactivate(interactableIndex);
    Player_SwitchGun(gun->type);
}


void Player_OpenCrate(void* data, int interactableIndex) {
    Gun* crateGun = data;
    Interactable_CreateWeapon(*crateGun, interactables[interactableIndex].position);
    Interactable_Deactivate(interactableIndex);
}