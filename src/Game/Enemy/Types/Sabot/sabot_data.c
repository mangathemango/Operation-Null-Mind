/**
 * @file sabot_data.c
 * @brief Contains data definitions for Sabot enemy type
 *
 * Defines the default properties, stats, and visual configuration
 * for the Sabot enemy type.
 *
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>

SabotConfig SabotConfigData = {
    .directionChangeTimer = 0,
    .directionChangeTime = 1.0f,
    .shootTimer = 0,
    .gun = {
        .config = {
            .muzzlePosition = {30, 4},
            .ejectionPosition = {14, 3},
            .gripPosition = {13, 7},
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
            .spritesheetPath = "Assets/Images/Enemies/sabot_gun.png",  // Kept original path
            .frameSize = {30, 9},
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
            .spriteSize = {30, 9},   
            .defaultClip = "normal",
            .playOnStart = true
        }
    },
    .gunOffset = {0, -3},
    .explosionRadius = 20.0f,  // Added from Radius
};

/**
 * @brief [Data] Sabot enemy default data
 * 
 * This structure defines the default properties, stats and
 * settings for the Sabot enemy type.
 */
EnemyData SabotData = {
    .type = ENEMY_TYPE_SABOT,
    .name = "Sabot",
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
        .damage = 15,
        .maxHealth = 60,
        .maxSpeed = 140.0f,
        .acceleration = 600.0f,
        .drag = 3.0f,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 3.0f,  // Match Proxy's value
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/sabot.png", // Updated to match enemy name
        .frameSize = {30, 40},  // Match Proxy's frame size
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
        .spriteSize = {30, 40},  // Match Proxy's sprite size
    },
    .config = &SabotConfigData,
    .start = &Sabot_Start,
    .update = &Sabot_Update,
    .render = &Sabot_Render,
    .onDeath = &Sabot_OnDeath,
};
