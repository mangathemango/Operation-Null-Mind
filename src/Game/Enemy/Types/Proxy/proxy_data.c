/**
 * @file proxy_data.c
 * @brief Contains data definitions for Proxy enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Proxy enemy type.
 *
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>

ProxyConfig ProxyConfigData = {
    .deployTime = 2.0f,
    .proximityRadius = 150.0f,
    .damageMultiplier = 1.5f,
    .isDeployed = false,
    .deployPosition = {0, 0}
};

/**
 * @brief [Data] Proxy enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Proxy enemy type.
 */
EnemyData ProxyData = {
    .type = ENEMY_TYPE_PROXY,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 25, 25},
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
        .maxHealth = 80,
        .maxSpeed = 120.0f,
        .acceleration = 450.0f,
        .drag = 4.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/proxy.png",
        .frameSize = {24, 30},
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
                .name = "deployed",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {42, 38},
    },
    .config = &ProxyConfigData,
    .start = &Proxy_Start,
    .update = &Proxy_Update,
    .render = &Proxy_Render,
};
