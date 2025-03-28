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
    .gun = {
        .name = GUN_BATTLE_RIFLE_NAME,
        .config = {
            .muzzlePosition = {34, 4},
            .ejectionPosition = {13, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 650,
            .spread_angle = 2,
            .damage = 120,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoCapacity = 20,
            .ammoConsumption = 2
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Battle Rifle.png",
            .frameSize = {35, 19},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 10,
                    .endFrameIndex = 10,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 10,
                    .endFrameIndex = 19,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {35, 19},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    .gunOffset = {5, 5}
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
