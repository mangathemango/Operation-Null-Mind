/**
 * @file juggernaut_data.c
 * @brief Contains data definitions for Juggernaut enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Juggernaut enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>

JuggernautConfig JuggernautConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {8, 3},
            .ejectionPosition = {5, 2},
            .gripPosition = {2, 4},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 300,
            .spread_angle = 8,
            .damage = 20,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoCapacity = 40,
            .ammoConsumption = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/proxy_gun.png",
            .frameSize = {8, 6},
            .frameCount = 1,
            .clips = {
                {
                    .name = "normal",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {8, 6},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},
    .armorValue = 0.25f,         // Reduces damage taken by 25%
    .chargeDistance = 200.0f,    // Distance at which to consider charging
    .rageThreshold = 0.4f,       // Enrages at 40% health
    .isEnraged = false,
    .stampedeDuration = 1.5f,
    .stampedeTimer = 0
};

/**
 * @brief [Data] Juggernaut enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Juggernaut enemy type.
 */
EnemyData JuggernautData = {
    .type = ENEMY_TYPE_JUGGERNAUT,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 38, 38},
            .layer = COLLISION_LAYER_ENEMY,
            .collidesWith = COLLISION_LAYER_PLAYER_PROJECTILE
                            | COLLISION_LAYER_PLAYER
                            | COLLISION_LAYER_ENVIRONMENT
                            | COLLISION_LAYER_ENEMY,
        },
        .currentHealth = 0,
        .isDead = true,
    },
    .stats = {
        .damage = 30,
        .maxHealth = 200,
        .maxSpeed = 80.0f,      // Slow but powerful
        .acceleration = 250.0f,
        .drag = 2.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 5.0f,  // Long base cooldown
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/proxy.png",
        .frameSize = {30, 40},
        .frameCount = 7,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "walkin",
                .startFrameIndex = 1,
                .endFrameIndex = 6,
                .frameDuration = 0.1f,
                .looping = true,
            },
            {
                .name = "attack",
                .startFrameIndex = 2,
                .endFrameIndex = 2,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {30, 40},
    },
    .config = &JuggernautConfigData,
    .start = &Juggernaut_Start,
    .update = &Juggernaut_Update,
    .render = &Juggernaut_Render,
};
