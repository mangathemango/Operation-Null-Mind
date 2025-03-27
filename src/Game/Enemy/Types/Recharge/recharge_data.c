/**
 * @file recharge_data.c
 * @brief Contains data definitions for Recharge enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Recharge enemy type.
 *
 * @date 2025-03-04
 */

#include <enemy_recharge.h>

RechargeConfig RechargeConfigData = {
    .rechargeRadius = 120.0f,
    .isRecharging = false,

    .healAmount = 20,
    .rechargeCooldown = 2.0f,
    .rechargeDuration = 1.0f,
    .timer = 0.0f,

    .rechargePosition = {0, 0}, 
    .rechargeTexture = NULL,
};

/**
 * @brief [Data] Recharge enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Recharge enemy type.
 */
EnemyData RechargeData = {
    .type = ENEMY_TYPE_RECHARGE,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 20, 20},
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
        .damage = 10,
        .maxHealth = 100,
        .maxSpeed = 100.0f,
        .acceleration = 500.0f,
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
        .spritesheetPath = "Assets/Images/Enemies/recharge.png",
        .frameSize = {26, 32},
        .frameCount = 1,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {26, 32},
    },
    .config = &RechargeConfigData,
    .start = &Recharge_Start,
    .update = &Recharge_Update,
    .render = &Recharge_Render,
};