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
    int ammoComsumption = player.state.currentGun.stats.ammoConsumption;
    if (player.state.currentAmmo < ammoComsumption) return;
    Sound_Play_Effect(1);
    player.state.currentAmmo -= player.state.currentGun.stats.ammoConsumption * player.resources.skillResources.overPressuredBulletConsumptionMultipler;
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.muzzleFlashEmitter);
    player.state.currentGun.resources.bulletPreset->particleSpeed = player.state.currentGun.resources.bulletPreset->particleSpeed * player.resources.skillResources.overPressuredProjectileSpeed;
    ParticleEmitter_ActivateOnce(player.state.currentGun.resources.bulletPreset);
    SDL_Log("Bullet speed: %f", player.state.currentGun.resources.bulletPreset->particleSpeed);
    player.state.currentGun.resources.bulletPreset->particleSpeed = player.state.currentGun.resources.bulletPreset->particleSpeed / player.resources.skillResources.overPressuredProjectileSpeed;
    SDL_Log("Bullet speed: %f", player.state.currentGun.resources.bulletPreset->particleSpeed);

    player.resources.skillResources.ammoShoot++;
    SDL_Log("ammo shot %d",player.resources.skillResources.ammoShoot);
    if(ghostLoad() == true)
    {
        player.state.currentAmmo++;
        SDL_Log("Ghost Load");
    }
    player.resources.shootCooldownTimer = Timer_Create((60.0f + player.resources.skillResources.ghostLoadRandomizer)/(player.state.currentGun.stats.fireRate * player.resources.skillResources.overPressuredFireRate));
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

void Player_PickUpHealth(void* data, int interactableIndex)
{
    int* healAmount = data;
    player.state.currentHealth += *healAmount;
    if (player.state.currentHealth > player.stats.maxHealth) {
        player.state.currentHealth = player.stats.maxHealth;
    }
    Interactable_Deactivate(interactableIndex);
}

void Player_PickUpSkill(void* data, int interactableIndex)
{
    int* abilitesType = data;
    bool* skillValues[TOTAL_SKILLS] = {
        &player.state.skillState.armoredUp,
        &player.state.skillState.ghostLoad,
        &player.state.skillState.hemoCycle,
        &player.state.skillState.kineticArmor,
        &player.state.skillState.lastStand,
        &player.state.skillState.oneMore,
        &player.state.skillState.overPressured,
        &player.state.skillState.scavenger

    };

    *skillValues[*abilitesType] = true;
    Interactable_Deactivate(interactableIndex);
    
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
    Interactable_CreateWeapon(*crateGun, Vec2_Add(interactables[interactableIndex].position, Vec2_Multiply(Vec2_Down, 20)));
    Interactable_CreateHealth(Vec2_Add(interactables[interactableIndex].position, Vec2_Add(Vec2_Multiply(Vec2_Up, 25), Vec2_Multiply(Vec2_Right, 20))));
    Interactable_CreateAbilties(Vec2_Add(interactables[interactableIndex].position, Vec2_Add(Vec2_Multiply(Vec2_Up, 25), Vec2_Multiply(Vec2_Left, 20))));
    Interactable_Deactivate(interactableIndex);
}
void Player_ReadLog(void* data, int interactableIndex) {
    int* index = data;
    game.viewingLog = *index;
}


float damageEffectOpacity = 0;

void Player_TakeDamage(int damage) {
    if (!player.resources.INVINCIBLE_Timer) {
        player.resources.INVINCIBLE_Timer = Timer_Create(player.stats.INVINCIBLE_Time);
        Timer_Start(player.resources.INVINCIBLE_Timer);
        player.state.currentHealth -= (int) (damage * (100 + player.resources.skillResources.hemocycleMultipler - player.resources.skillResources.armoredUpIncomingDamageReduction) / 100);
        return;
    }
    if (!Timer_IsFinished(player.resources.INVINCIBLE_Timer)) return;
    
    SDL_Log("%d armoredUp", player.resources.skillResources.armoredUpIncomingDamageReduction);
    SDL_Log("%d hemocycle", player.resources.skillResources.hemocycleMultipler);
    player.state.currentHealth -= (int) ((damage * (100 + player.resources.skillResources.hemocycleMultipler - player.resources.skillResources.armoredUpIncomingDamageReduction) / 100)) * kineticArmor();
    if (player.state.currentHealth <= 0) {
        player.state.currentHealth = 0;
    }
    damageEffectOpacity = 100;
    Timer_Start(player.resources.INVINCIBLE_Timer);
}

void Player_RenderDamageEffect() {
    SDL_Rect dest = {
        0,
        0,
        app.config.window_width,
        app.config.window_height
    };
    SDL_SetRenderDrawColor(
        app.resources.renderer,
        255,
        0,
        0,
        damageEffectOpacity
    );
    SDL_RenderFillRect(app.resources.renderer, &dest);
    damageEffectOpacity -= damageEffectOpacity * Time->deltaTimeSeconds * 5;
}