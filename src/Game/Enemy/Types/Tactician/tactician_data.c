/**
 * @file tactician_data.c
 * @brief Contains data definitions for Tactician enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Tactician enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_tactician.h>

TacticianConfig TacticianConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {17, 4},
            .ejectionPosition = {10, 2},
            .gripPosition = {7, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 450,
            .spread_angle = 3,
            .damage = 10,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoCapacity = 30,
            .ammoConsumption = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/tactician_gun.png",
            .frameSize = {17, 10},
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
            .spriteSize = {17, 10},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},

    .state = TACTICIAN_STATE_WALKING,
    .commandRadius = 200.0f,
    .buffStrength = 1.25f,

    .burstTimer = 0.0f,
    .burstTime = 0.1f,
    .currentBurstCount = 0,
    .maxBurstCount = 5,
    .shootTime = 2.0f,
    .lastPosition = {0, 0},
};

/**
 * @brief [Data] Tactician enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Tactician enemy type.
 */
EnemyData TacticianData = {
    .type = ENEMY_TYPE_TACTICIAN,
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
        .damage = 8,
        .maxHealth = 90,
        .maxSpeed = 90.0f,
        .acceleration = 350.0f,
        .drag = 4.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 4.0f,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/tactician.png", // Updated to match enemy name
        .frameSize = {30, 40},
        .frameCount = 1,  // Changed from 7 to 1
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            }
            // Removed walkin clip
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {30, 40},
    },
    .config = &TacticianConfigData,
    .start = &Tactician_Start,
    .update = &Tactician_Update,
    .render = &Tactician_Render,
    .name = "Tactician",
};
