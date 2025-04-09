#include <enemy_libet.h>
#include <stdlib.h>



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
            .layer = COLLISION_LAYER_ENEMY,
            .collidesWith = COLLISION_LAYER_PLAYER_PROJECTILE
                            | COLLISION_LAYER_PLAYER
                            | COLLISION_LAYER_ENVIRONMENT,
        },
        .currentHealth = 0,
        .isDead = true,
    },
    .stats = {
        .damage = 20,
        .maxHealth = 10000,
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
                .name = "floating",
                .startFrameIndex = 16,
                .endFrameIndex = 31,
                .frameDuration = 0.05f,
                .looping = true,
            }
        },
        .playOnStart = true,
        .defaultClip = "floating",
        .spriteSize = {120, 120},
    },
    .config = NULL,
    .start = &Libet_Start,
    .update = &Libet_Update,
    .render = &Libet_Render,
};