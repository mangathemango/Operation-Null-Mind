/**
 * @file echo_data.c
 * @brief Contains data definitions for Echo enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Echo enemy type.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <enemy_echo.h>

/**
 * @brief [Data] Echo enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Echo enemy type.
 */
EnemyData EchoData = {
    .type = ENEMY_TYPE_ECHO,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 20, 32},
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
        .damage = 0,
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
        .spritesheetPath = "Assets/Images/Enemies/echo.png",
        .frameSize = {40, 40},
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
        .spriteSize = {40, 40},
    },
    .config = NULL,
    .start = &Echo_Start,
    .update = &Echo_Update,
    .render = &Echo_Render,
};