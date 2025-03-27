/**
 * @file vantage_data.c
 * @brief Contains data definitions for Vantage enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Vantage enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>

VantageConfig VantageConfigData = {
    .detectionRange = 500.0f,
    .sniperRange = 350.0f,
    .aimTime = 1.2f,
    .isAiming = false,
    .targetPosition = {0, 0}
};

/**
 * @brief [Data] Vantage enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Vantage enemy type.
 */
EnemyData VantageData = {
    .type = ENEMY_TYPE_VANTAGE,
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
        .damage = 30,
        .maxHealth = 45,
        .maxSpeed = 80.0f,
        .acceleration = 300.0f,
        .drag = 5.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/vantage.png",
        .frameSize = {32, 36},
        .frameCount = 2,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "aiming",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {42, 45},
    },
    .config = &VantageConfigData,
    .start = &Vantage_Start,
    .update = &Vantage_Update,
    .render = &Vantage_Render,
};
