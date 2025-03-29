/**
 * @file sentry_data.c
 * @brief Contains data definitions for Sentry enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Sentry enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>

SentryConfig SentryConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {30, 8},
            .ejectionPosition = {11, 8},
            .gripPosition = {11, 8},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 550,
            .spread_angle = 1, // More accurate than proxy
            .damage = 15,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoCapacity = 30,
            .ammoConsumption = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/sentry_gun.png",
            .frameSize = {30, 16},
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
            .spriteSize = {30, 16},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, 10},
    .guardRadius = 250.0f,
    .alertLevel = 0.0f,
    .alertThreshold = 1.0f,
    .isAlerted = false,
    .guardPosition = {0, 0}
};

/**
 * @brief [Data] Sentry enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Sentry enemy type.
 */
EnemyData SentryData = {
    .type = ENEMY_TYPE_SENTRY,
    .name = "Sentry",
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 26, 26},
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
        .damage = 15,
        .maxHealth = 120,
        .maxSpeed = 50.0f, // Slower than other enemies
        .acceleration = 300.0f,
        .drag = 5.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 3.0f,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/sentry.png", // Updated to match enemy name
        .frameSize = {38, 26},
        .frameCount = 1,  // Changed from 7 to 1
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            }
            // Removed walkin clip
        },
        .playOnStart = true,
        .defaultClip = "idle", // Sentries are mostly stationary
        .spriteSize = {38, 26},
    },
    .config = &SentryConfigData,
    .start = &Sentry_Start,
    .update = &Sentry_Update,
    .render = &Sentry_Render,
};
