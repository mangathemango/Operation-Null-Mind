/**
 * @file radius_data.c
 * @brief Contains data definitions for Radius enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Radius enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>

RadiusConfig RadiusConfigData = {
    .aoeRadius = 120.0f,
    .explosionDamage = 35.0f,
    .chargeupTime = 2.0f,
    .isCharging = false,
    .currentCharge = 0.0f
};

/**
 * @brief [Data] Radius enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Radius enemy type.
 */
EnemyData RadiusData = {
    .type = ENEMY_TYPE_RADIUS,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 30, 30},
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
        .damage = 20,
        .maxHealth = 85,
        .maxSpeed = 85.0f,
        .acceleration = 420.0f,
        .drag = 4.5f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/radius.png",
        .frameSize = {32, 32},
        .frameCount = 3,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "charging",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "explosion",
                .startFrameIndex = 2,
                .endFrameIndex = 2,
                .frameDuration = 0.0f,
                .looping = false,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {48, 48},
    },
    .config = &RadiusConfigData,
    .start = &Radius_Start,
    .update = &Radius_Update,
    .render = &Radius_Render,
};
