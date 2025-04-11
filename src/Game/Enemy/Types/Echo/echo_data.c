/**
 * @file echo_data.c
 * @brief Contains data definitions for Echo enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Echo enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_echo.h>

EchoConfig EchoConfigData = {
    .state = ECHO_STATE_WALKING,
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {21, 4},
            .ejectionPosition = {9, 2},
            .gripPosition = {8, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 600,
            .spread_angle = 3,
            .damage = 12,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/echo_gun.png",
            .frameSize = {21, 9},
            .frameCount = 1,
            .clips = {
                {
                    .name = "idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "walking",
                    .startFrameIndex = 0,
                    .endFrameIndex = 6,
                    .frameDuration = 0.1f,
                    .looping = true
                }
            },
            .spriteSize = {21, 9},   
            .defaultClip = "idle",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},

    .burstCount = 0,
    .burstMaxCount = 3,
    .burstTimer = 0.0f,
    .burstTime = 0.1f,
    
};

/**
 * @brief [Data] Echo enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Echo enemy type.
 */
EnemyData EchoData = {
    .type = ENEMY_TYPE_ECHO,
    .name = "Echo",
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
        .maxHealth = 85,
        .maxSpeed = 110.0f,
        .acceleration = 450.0f,
        .drag = 4.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 3.5f,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/echo.png",
        .frameSize = {30, 40},
        .frameCount = 7,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            }
            ,
            {
                .name = "walking",
                .startFrameIndex = 0,
                .endFrameIndex = 6,
                .frameDuration = 0.1f,
                .looping = true
            }
        },
        .playOnStart = true,
        .defaultClip = "walking",
        .spriteSize = {30, 40},
    },
    .config = &EchoConfigData,
    .start = &Echo_Start,
    .update = &Echo_Update,
    .render = &Echo_Render,
};