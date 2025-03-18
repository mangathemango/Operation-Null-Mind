#include <enemy_zfn.h>

EnemyData ZFNData = {
    .type = ENEMY_TYPE_ZFN,
    .state = {
        .position = {0, 0},
        .velocity = {0, 0},
        .acceleration = {0, 0},
        .collider = {
            .hitbox = {0, 0, 20, 32},
            .layer = COLLISION_LAYER_ENEMY,
            .collidesWith = COLLISION_LAYER_PLAYER_PROJECTILE,
        },
        .currentHealth = 0,
        .isDead = true,
    },
    .stats = {
        .damage = 0,
        .maxHealth = 100,
        .speed = 0,
        .attackSpeed = 0,
        .attackRange = 0,
        .attackDamage = 0,
        .attackCooldown = 0,
    },
    .resources = {
        .animation = NULL,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/Enemies/zfn.png",
        .frameSize = {292, 438},
        .frameCount = 1,
        .clips = {
            {
                .name = "idle",
                .startFrameIndex = 0,
                .endFrameIndex = 0,
                .frameDuration = 0.0f,
                .looping = true,
            },
        },
        .playOnStart = true,
        .defaultClip = "idle",
        .spriteSize = {20, 32},
    },
    .config = NULL,
    .start = &ZFN_Start,
    .update = &ZFN_Update,
    .render = &ZFN_Render,
};