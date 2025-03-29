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
            .muzzlePosition = {8, 3},
            .ejectionPosition = {5, 2},
            .gripPosition = {2, 4},
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
            .spritesheetPath = "Assets/Images/Enemies/proxy_gun.png",  // Kept original path
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
            .hitbox = {0, 0, 28, 28},
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
        .damage = 25,
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
        .spriteSize = {30, 40},  // Match Proxy's sprite size
    },
    .config = &SabotConfigData,
    .start = &Sabot_Start,
    .update = &Sabot_Update,
    .render = &Sabot_Render,
};
