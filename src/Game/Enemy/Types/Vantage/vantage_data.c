/**
 * @file vantage_data.c
 * @brief Contains data definitions for Vantage enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Vantage enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>

VantageConfig VantageConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {25, 5},
            .ejectionPosition = {9, 4},
            .gripPosition = {9, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
            .currentAmmo = 0,
        },
        .stats = {
            .fireRate = 200,         // Slower fire rate than standard
            .spread_angle = 0.5f,    // Very accurate
            .damage = 35,            // Higher damage per shot
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.5f,  // Longer range
            .bulletsPerShot = 1,
            .ammoCapacity = 8,
            .ammoConsumption = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Enemies/vantage_gun.png",
            .frameSize = {25, 9},
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
            .spriteSize = {25, 9},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},
    .aiming = false,
    .aimTime = 0.8f,         // Time to aim before shooting
    .aimTimer = 0,
    .shooting = false,
    .lazerStart = {0, 0},
    .lazerEnd = {0, 0},

};

/**
 * @brief [Data] Vantage enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Vantage enemy type.
 */
EnemyData VantageData = {
    .type = ENEMY_TYPE_VANTAGE,
    .name = "Vantage",
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
        .maxHealth = 75,          // Lower health than average
        .maxSpeed = 100.0f,       // Average speed
        .acceleration = 350.0f,
        .drag = 4.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 5.0f,   // Long cooldown between shots
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/vantage.png", // Updated to match enemy name
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
    .config = &VantageConfigData,
    .start = &Vantage_Start,
    .update = &Vantage_Update,
    .render = &Vantage_Render,
};
