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

#include <enemy_kamikaze.h>

KamikazeConfig KamikazeConfigData = {
    .exploding = false,
    .explosionRadius = 50,
    .directionChangeTime = 0,
    .explosionTimer = 0,
};

/**
 * @brief [Data] Echo enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Echo enemy type.
 */
EnemyData KamikazeData = {
    .type = ENEMY_TYPE_KAMIKAZE,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 15, 15},
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
        .spritesheetPath = "Assets/Images/Enemies/kamikaze.png",
        .frameSize = {46, 40},
        .frameCount = 28,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "move",
                .startFrameIndex = 0,
                .endFrameIndex = 7,
                .frameDuration = 0.1f,
                .looping = true,
            },
            {
                .name = "explode",
                .startFrameIndex = 8,
                .endFrameIndex = 27,
                .frameDuration = 0.05f,
                .looping = false,
            }
        },
        .playOnStart = true,
        .defaultClip = "move",
        .spriteSize = {23, 20},
    },
    .config = NULL,
    .start = &Kamikaze_Start,
    .update = &Kamikaze_Update,
    .render = &Kamikaze_Render,
};