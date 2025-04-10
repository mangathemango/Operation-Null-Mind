#include <enemy_libet.h>
#include <stdlib.h>


LibetConfig LibetConfigData = {
    .state = LIBET_FLOATING,
    .timer = 0.0f,
    .floatTime = 1.0f,
    .lazerChargeTime = 1.0f,
    .lazerFireTime = 0.3f,
};

/**
 * @brief [Data] Libet boss enemy default data
 *
 * This structure defines the default properties, stats, and settings for the Libet boss enemy.
 */
EnemyData LibetData = {
    .type = ENEMY_TYPE_LIBET,
    .name = "Libet",
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .direction = {0, 0},
        .collider = {
            .hitbox = {0, 0, 40, 40},
            .layer = COLLISION_LAYER_NONE,
        },
        .currentHealth = 0,
        .isDead = true,
    },
    .stats = {
        .damage = 20,
        .maxHealth = 5000,
        .maxSpeed = 80.0f,
        .acceleration = 300.0f,
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
        .spritesheetPath = "Assets/Images/Enemies/libet.png",
        .frameSize = {120, 120},
        .frameCount = 32,
        .clips = {
            {
                .name = "[VINCIBLE]",
                .startFrameIndex = 0,
                .endFrameIndex = 15,
                .frameDuration = 0.05f,
                .looping = true,
            },
            {
                .name = "[INVINCIBLE]",
                .startFrameIndex = 16,
                .endFrameIndex = 31,
                .frameDuration = 0.05f,
                .looping = true,
            }
        },
        .playOnStart = true,
        .defaultClip = "[INVINCIBLE]",
        .spriteSize = {120, 120},
    },
    .config = NULL,
    .start = &Libet_Start,
    .update = &Libet_Update,
    .render = &Libet_Render,
};