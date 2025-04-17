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
    .shootTime = 0.1f,
    .gun = {
        .config = {
            .muzzlePosition = {27, 5},
            .ejectionPosition = {9, 3},
            .gripPosition = {9, 8},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 300,
            .spread_angle = 8,
            .damage = 10,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/juggernaut_gun.png",
            .frameSize = {27, 11},
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
            .spriteSize = {27, 11},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},
    .timer = 0,
    .walkDuration = 3,
    .chargeDuration = 0.5,
    .enragedDuration = 5,
    .spinSpeedDegrees = 360,
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
        .damage = 10,
        .maxHealth = 600,
        .maxSpeed = 200.0f,      // Slow but powerful
        .acceleration = 250.0f,
        .drag = 2.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0.20f,  // Long base cooldown
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/juggernaut.png", 
        .frameSize = {40, 50},
        .frameCount = 6,  // Changed from 7 to 1
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "walking",
                .startFrameIndex = 0,
                .endFrameIndex = 5,
                .frameDuration = 0.1f,
                .looping = true
            }
        },
        .playOnStart = true,
        .defaultClip = "walking",
        .spriteSize = {40, 50},
    },
    .config = &JuggernautConfigData,
    .start = &Juggernaut_Start,
    .update = &Juggernaut_Update,
    .render = &Juggernaut_Render,
    .name = "Juggernaut",
};
