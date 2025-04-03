/**
 * @file player_data.c
 * @brief Contains player data definitions and default values
 *
 * Initializes and defines the core data structures for the player
 * character, including stats, state, resources, and animation data.
 *
 * @author Mango
 * @date 2025-02-09
 */

//? Written by Mango on 09/02/2025

#include <player.h>

/**
 * @brief [Data] The player's initial data and configuration
 * 
 * Contains all default values for the player including position, collision properties,
 * movement speeds, sprite data, and animation definitions.
 */
PlayerData player = {
    .state = {
        .position = {4200,4200},
        .direction = {0,0},
        .currentSpeed = 0,
        .gunSlots = {GUN_PISTOL, GUN_SHOTGUN},
        .moving = false,
        .dashing = false,
        .directionLocked = false,
        .skillState = {
            .armoredUp = true,
            .ghostLoad = true,
            .hemoCycle = true,
            .kineticArmor = true,
            .lastStand = true,
            .oneMore = false,
            .overPressured = true,
            .scavenger = true,
            .crashOut = false,
            .crashOutMultiplier = 2,
        },
        .collider = {
            .active = true,
            .collidesWith = 
                COLLISION_LAYER_ENEMY | 
                COLLISION_LAYER_ENVIRONMENT |
                COLLISION_LAYER_TRIGGER, // 00001110
            .layer = COLLISION_LAYER_PLAYER,
            .hitbox = {
                .x = 0,
                .y = 0,
                .w = 20,
                .h = 25
            }
        },
    },
    .resources = {
        .animation = NULL,
        .dashParticleEmitter = NULL,
        .dashCooldownTimer = NULL,
        .dashDurationTimer = NULL,
        .skillResources = {
            .overPressuredBulletConsumptionMultipler = 1,
            .overPressuredFireRate = 1.0f,
            .overPressuredProjectileSpeed = 1.0f,
            .scavengerAmmoBonus = 0,
            .scavengerAmmoCapacity = 0,
            .ammoShoot = 0,
            .ghostLoadRandomizer = 0,
            .crashOutCooldown = NULL,
            .crashOutDuration = NULL,
        },
    },
    .stats = {
        .walkSpeed = 150,
        .dashSpeed = 1000,
        .dashCooldown = 1,
        .dashDuration = 0.1,
        .maxHealth = 200,
        .maxAmmo = 200,
        .INVINCIBLE_Time = 0.25,
        .enemiesKilled = 0,
        .skillStat = {
            .overPressuredOriginalFireRate = 1.5f,
            .overPressuredOriginalProjectileSpeed = 1.5f,
            .overPressuredOriginalMultipler = 2,
            .scavengerAmmoBonus = 3,
            .scavengerAmmoCapacity = 20,
            .hemocycleMultipler = 20,
            .hemocycleHealthGained = 100,
            .armoredUpIncomingDamageReduction = 25,
            .armoredUpDamageOutputDamageReduction = 15,
            .ghostLoadRandomizer = 1000.0f,
            .crashOutCooldown = 15,
            .crashOutDuration = 15,
            .crashOutCurrentMultipler = 1,
        },
        .INVINCIBLE_Time = 0.25,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/robert.png",
        .frameSize = {30,40},
        .frameCount = 9,
        .clips = {
            {
                .name = "idle", 
                .startFrameIndex = 0, 
                .endFrameIndex = 0, 
                .frameDuration = 0.4f,
                .looping = false
            },
            {
                .name = "walk", 
                .startFrameIndex = 1, 
                .endFrameIndex = 8, 
                .frameDuration = 0.1f,
                .looping = true
            }
            
        },
        .spriteSize = {30,40},
        .defaultClip = "idle",
        .playOnStart = true,
    }
};