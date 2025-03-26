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
    player.state.currentGunIndex = (player.state.currentGunIndex + 1) % 2;
    Player_ResetGun();
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
    GunSlot* gun = data;
    int freeGunSlot = 0;
    // Look for free slot
    for (int i = 0; i < 2; i++) {
        if (player.state.gunSlots[i].gun == -1) {
            freeGunSlot = i;
        }
    };
    if (freeGunSlot == 0) {
        Interactable_CreateWeapon(
            player.state.gunSlots[player.state.currentGunIndex], 
            player.state.position
        );
        player.state.gunSlots[player.state.currentGunIndex] = *gun;
    } else {
        player.state.currentGunIndex = freeGunSlot;
        player.state.gunSlots[freeGunSlot] = *gun;
        
    }
    Interactable_Deactivate(interactableIndex);

    player.resources.shootCooldownTimer = Timer_Create(60.0f/ (float) Player_GetCurrentGunData()->stats.fireRate);
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
    Gun_Type* crateGun = data;
    Interactable_CreateWeaponCrate(true, *crateGun, interactables[interactableIndex].position);
    Interactable_CreateWeapon(*crateGun, interactables[interactableIndex].position);
    Interactable_Deactivate(interactableIndex);
}

void Player_ReadLog(void* data, int interactableIndex) {
    int* index = data;
    player.state.viewingLog = *index;
}

void Player_ResetGun() {
    player.state.currentGun = Player_GetCurrentGunData();
    player.resources.shootCooldownTimer = Timer_Create(60.0f/player.state.currentGun.stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}

GunData* Player_GetCurrentGunData() {
    return &GunList[player.state.gunSlots[player.state.currentGunIndex].gun];
}
