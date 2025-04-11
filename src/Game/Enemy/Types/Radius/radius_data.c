/**
 * @file radius_data.c
 * @brief Contains data definitions for Radius enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Radius enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>

RadiusConfig RadiusConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {21, 3},
            .ejectionPosition = {7, 2},
            .gripPosition = {8, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 500,
            .spread_angle = 5,
            .damage = 8,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoCapacity = 30,
            .ammoConsumption = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/radius_gun.png",
            .frameSize = {21, 8},
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
            .spriteSize = {21, 8},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},
    .explosionRadius = 50.0f,
};

EnemyData RadiusData = {
    .type = ENEMY_TYPE_RADIUS,
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
        .damage = 12,
        .maxHealth = 70,
        .maxSpeed = 160.0f, // Faster than average for orbiting
        .acceleration = 400.0f,
        .drag = 3.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 2.5f,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/radius.png", // Updated to match enemy name
        .frameSize = {30, 40},
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
        .spriteSize = {30, 40},
    },
    .name = "Radius",
    .config = &RadiusConfigData,
    .start = &Radius_Start,
    .update = &Radius_Update,
    .render = &Radius_Render,
};
