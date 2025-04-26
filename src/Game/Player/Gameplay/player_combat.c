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
#include <input.h>
#include <math.h>
#include <settings.h>

/**
 * @brief [Utility] Makes the player shoot their current weapon
 * 
 * Activates the shooting sequence, including sound effects, particle
 * effects for muzzle flash and casings, and creating bullet projectiles.
 */
void Player_Shoot() {
    if (!Timer_IsFinished(player.resources.shootCooldownTimer)) return;
    GunData* gun = &player.state.currentGun;
    int ammoComsumption = gun->stats.ammoConsumption;
    if (player.state.skillState.overPressured) ammoComsumption++;
    if (player.state.currentAmmo < ammoComsumption) return;

    // Map gun types to their corresponding sound effects
    SoundEffect gunSoundEffects[] = {
        SOUND_PISTOL,
        SOUND_SMG,
        SOUND_SHOTGUN,
        SOUND_ASSAULT_RIFLE,
        SOUND_BATTLE_RIFLE,
        SOUND_REVOLVER,
        SOUND_ARMOR_PISTOL,
        SOUND_RAPID_SMG,
        SOUND_PDW,
        SOUND_BURST_RIFLE,
        SOUND_BULLPUP_RIFLE,
        SOUND_AUTO_SHOTGUN,
    };

    // Play the corresponding sound effect for the current gun
    if (gun->type >= 0 && gun->type < sizeof(gunSoundEffects) / sizeof(gunSoundEffects[0])) {
        Sound_Play_Effect(gunSoundEffects[gun->type]);
    }

    player.state.currentAmmo -= ammoComsumption;
    Game_AddAmmoSpent(ammoComsumption);

    Vec2 mouseWorldPosition = Camera_ScreenVecToWorld(Input->mouse.position);

    gun->state.angle = atan2(
        mouseWorldPosition.y - player.state.position.y,
        mouseWorldPosition.x - player.state.position.x
    ) * 180 / M_PI;
    
    if (player.state.position.x > mouseWorldPosition.x) {
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(
            Vec2_Right, 
            gun->state.angle + gun->config.casingEjectionAngle
        );
    } else {
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(
            Vec2_Right, 
            gun->state.angle - gun->config.casingEjectionAngle
        );
    }
    ParticleEmitter_ActivateOnce(gun->resources.casingParticleEmitter);
    ParticleEmitter_ActivateOnce(gun->resources.muzzleFlashEmitter);

    gun->resources.bulletPreset->particleSpeed = gun->stats.bulletVelocity * player.resources.skillResources.overPressuredProjectileSpeed;
    ParticleEmitter_ActivateOnce(gun->resources.bulletPreset);

    player.resources.skillResources.ammoShoot++;

    Vec2_Increment(
        &camera.position, 
        Vec2_Multiply(
            gun->resources.muzzleFlashEmitter->direction,
            -2
        )
    );

    if(Player_GhostLoadGunJammed()) {
        Sound_Play_Effect(SOUND_GUN_JAM);
        player.state.currentAmmo += ammoComsumption;
    }

    player.resources.shootCooldownTimer = Timer_Create((60.0f /(gun->stats.fireRate * player.resources.skillResources.overPressuredFireRate)) + player.resources.skillResources.ghostLoadRandomizer);
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

    Sound_Play_Effect(SOUND_GUN_PICKUP);
    Interactable_Deactivate(interactableIndex);
    player.resources.shootCooldownTimer = Timer_Create(60.0f/GunList[gun->type].stats.fireRate);
    Timer_Start(player.resources.shootCooldownTimer);
}

void Player_PickUpHealth(void* data, int interactableIndex)
{
    if (Settings_GetPreventOverhealing() && player.state.currentHealth == player.stats.maxHealth) return;
    int* healAmount = data;
    Player_TakeDamage(-*healAmount);
    Interactable_Deactivate(interactableIndex);
    Game_AddHealingItemUsed();
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
        &player.state.skillState.overPressured,
        &player.state.skillState.scavenger

    };

    *skillValues[*abilitesType] = true;
    Sound_Play_Effect(SOUND_PASSIVE_OBTAINED);
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
    Sound_Play_Effect(SOUND_CRATE_OPENING);
}

void Player_ReadLog(void* data, int interactableIndex) {
    int* index = data;
    if (game.viewingLog > 0) {
        game.viewingLog = -1;
        return;
    }
    game.viewingLog = *index;
}


float damageEffectOpacity = 0;

void Player_TakeDamage(int damage) {
    if (damage < 0) {
        player.state.currentHealth -= damage;
        if (player.state.currentHealth > player.stats.maxHealth) {
            player.state.currentHealth = player.stats.maxHealth;
        }
        Sound_Play_Effect(SOUND_PLAYER_HEALING);
        Enemy_CreateHealthText(
            (Vec2) {
                player.state.position.x, 
                player.state.position.y - player.animData.spriteSize.y / 2
            }, 
            damage
        );
        return;
    }
    if (!Timer_IsFinished(player.resources.INVINCIBLE_Timer)) return;
    
    Game_AddHitsTaken();
    int effectiveDamage = damage * (100 + player.resources.skillResources.hemocycleMultipler - player.resources.skillResources.armoredUpIncomingDamageReduction) / 100;
    if (!Player_KineticArmorIsEffective()) effectiveDamage = 0;
    player.state.currentHealth -= effectiveDamage;
    if (player.state.currentHealth <= 0) {
        player.state.currentHealth = 0;
    } else {
        damageEffectOpacity = 100;
    }
    Enemy_CreateHealthText(
        (Vec2) {
            player.state.position.x, 
            player.state.position.y - player.animData.spriteSize.y / 2
        }, 
        effectiveDamage
    );
    Sound_Play_Effect(SOUND_PLAYER_HURT);
    Timer_Start(player.resources.INVINCIBLE_Timer);
}

void Player_RenderDamageEffect() {
    if (!Settings_GetFlashRed()) return;
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