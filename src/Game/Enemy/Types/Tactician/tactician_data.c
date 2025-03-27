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
    .commandRadius = 200.0f,
    .buffStrength = 1.25f,
    .maxControlledUnits = 5,
    .isCommanding = false,
    .controlledUnitCount = 0
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
            .hitbox = {0, 0, 24, 24},
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
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/tactician.png",
        .frameSize = {30, 34},
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
                .name = "commanding",
                .startFrameIndex = 1,
                .endFrameIndex = 1,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {40, 44},
    },
    .config = &TacticianConfigData,
    .start = &Tactician_Start,
    .update = &Tactician_Update,
    .render = &Tactician_Render,
};
