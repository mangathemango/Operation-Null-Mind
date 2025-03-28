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
        },
        .playOnStart = true,
        .defaultClip = "idle", // Sentries are mostly stationary
        .spriteSize = {30, 40},
    },
    .config = &SentryConfigData,
    .start = &Sentry_Start,
    .update = &Sentry_Update,
    .render = &Sentry_Render,
};
