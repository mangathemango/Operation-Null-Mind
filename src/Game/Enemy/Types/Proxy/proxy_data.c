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
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {8, 3},
            .ejectionPosition = {5, 2},
            .gripPosition = {2, 4},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 650,
            .spread_angle = 2,
            .damage = 120,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/proxy_gun.png",
            .frameSize = {8, 6},
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
            .spriteSize = {8, 6},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3}
};

/**
 * @brief [Data] Proxy enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Proxy enemy type.
 */
EnemyData ProxyData = {
    .type = ENEMY_TYPE_PROXY,
    .name = "Proxy",
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
        .maxHealth = 80,
        .maxSpeed = 120.0f,
        .acceleration = 450.0f,
        .drag = 4.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 3.0f,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/proxy.png",
        .frameSize = {30, 40},
        .frameCount = 7,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
            {
                .name = "walkin",
                .startFrameIndex = 1,
                .endFrameIndex = 6,
                .frameDuration = 0.1f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "walkin",
        .spriteSize = {30, 40},
    },
    .config = &ProxyConfigData,
    .start = &Proxy_Start,
    .update = &Proxy_Update,
    .render = &Proxy_Render,
};
