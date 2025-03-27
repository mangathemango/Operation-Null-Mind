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
    .guardRadius = 180.0f,
    .alertLevel = 0.0f,
    .alertThreshold = 0.7f,
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
            .hitbox = {0, 0, 28, 28},
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
        .maxSpeed = 50.0f,
        .acceleration = 200.0f,
        .drag = 6.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/sentry.png",
        .frameSize = {32, 32},
        .frameCount = 2,
        .clips = {
            {
                .name = "patrol",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "alerted",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "patrol",
        .spriteSize = {48, 48},
    },
    .config = &SentryConfigData,
    .start = &Sentry_Start,
    .update = &Sentry_Update,
    .render = &Sentry_Render,
};
