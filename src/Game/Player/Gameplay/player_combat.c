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
    player.state.currentAmmo--;
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.muzzleFlashEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.bulletPreset);
    Timer_Start(player.resources.shootCooldownTimer);
    
}

/**
 * @brief [Utility] Changes the player's active weapon
 */
void Player_SwitchGun() {
    Gun temp = player.state.gunSlots[0];
    int i = 0;
    for (i = 0; i < 2 - 1; i++) {
        if (player.state.gunSlots[i + 1] == -1) break;
        player.state.gunSlots[i] = player.state.gunSlots[i + 1];
    }
    player.state.gunSlots[i] = temp;
    player.state.currentGun = GunList[player.state.gunSlots[0]];
    player.resources.shootCooldownTimer = Timer_Create(60.0f/player.state.currentGun.stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}

/**
 * @brief Picks up a gun.
 * This function is a callback when the player interacts with a gun on the ground.
 * 
 * @param data  The gun data
 * @param interactableIndex  The index of the interactable gun on the ground.
 * 
 * @todo [player_combat.c:77] Add gun pickup sfx
 */
void Player_PickUpGun(void* data, int interactableIndex) {
    GunData* gun = data;
    int freeGunSlot = 0;
    // Look for free slot
    for (int i = 0; i < 2; i++) {
        if (player.state.gunSlots[i] == -1) {
            freeGunSlot = i;
        }
    };
    if (freeGunSlot == 0) {
        // Drop current gun if no free slot
        player.state.gunSlots[0] = gun->type;
        Interactable_CreateWeapon(player.state.currentGun.type, player.state.position);
    } else {
        // Swap guns
        player.state.gunSlots[freeGunSlot] = player.state.gunSlots[0];
        player.state.gunSlots[0] = gun->type;
    }
    Interactable_Deactivate(interactableIndex);
    player.resources.shootCooldownTimer = Timer_Create(60.0f/GunList[gun->type].stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}

/**
 * @brief Opens a crate
 * This function is a callback when the player interacts with a closed crate.
 * 
 * @param data  The gun data
 * @param interactableIndex  The index of the interactable crate.
 */
void Player_OpenCrate(void* data, int interactableIndex) {
    Gun* crateGun = data;
    Interactable_CreateWeaponCrate(true, *crateGun, interactables[interactableIndex].position);
    Interactable_CreateWeapon(*crateGun, interactables[interactableIndex].position);
    Interactable_Deactivate(interactableIndex);
}

void Player_ReadLog(void* data, int interactableIndex) {
    int* index = data;
    player.state.viewingLog = *index;
}