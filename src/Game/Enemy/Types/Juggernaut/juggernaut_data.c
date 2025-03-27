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
    .armorValue = 0.5f,
    .slowFactor = 0.7f,
    .rageMeter = 0.0f,
    .isEnraged = false,
    .enrageThreshold = 75.0f
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
            .hitbox = {0, 0, 40, 40},
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
        .damage = 35,
        .maxHealth = 200,
        .maxSpeed = 60.0f,
        .acceleration = 250.0f,
        .drag = 8.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/juggernaut.png",
        .frameSize = {48, 48},
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
                .name = "enraged",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {64, 64},
    },
    .config = &JuggernautConfigData,
    .start = &Juggernaut_Start,
    .update = &Juggernaut_Update,
    .render = &Juggernaut_Render,
};
