/**
 * @file sabot_data.c
 * @brief Contains data definitions for Sabot enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Sabot enemy type.
 *
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>

SabotConfig SabotConfigData = {
    .chargeTime = 1.5f,
    .chargeSpeed = 2.5f,
    .piercingFactor = 0.75f,
    .isCharging = false,
    .chargeDirection = {0, 0}
};

/**
 * @brief [Data] Sabot enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Sabot enemy type.
 */
EnemyData SabotData = {
    .type = ENEMY_TYPE_SABOT,
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
        .damage = 25,
        .maxHealth = 60,
        .maxSpeed = 140.0f,
        .acceleration = 600.0f,
        .drag = 3.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/sabot.png",
        .frameSize = {28, 32},
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
                .name = "attack",
                .startFrameIndex = 2,
                .endFrameIndex = 2,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {44, 42},
    },
    .config = &SabotConfigData,
    .start = &Sabot_Start,
    .update = &Sabot_Update,
    .render = &Sabot_Render,
};
