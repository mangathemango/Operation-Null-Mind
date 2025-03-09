//? Written by Mango on 09/02/2025

#include <player.h>

/*
    @file player_data.c
*   [Data] This file contains the player's data initialization.
*/

PlayerData player = {
    .state = {
        .position = {120,72},
        .direction = {0,0},
        .currentSpeed = 0,
        .moving = false,
        .dashing = false,
        .directionLocked = false,
        .collider = {
            .active = true,
            .collidesWith = COLLISION_LAYER_ENEMY | 
                            COLLISION_LAYER_ENVIRONMENT |
                            COLLISION_LAYER_ITEM,
            .layer = COLLISION_LAYER_PLAYER,
            .hitbox = {
                .x = 0,
                .y = 0,
                .w = 20,
                .h = 25
            }
        }
    },
    .config = {
        .animation = NULL,
        .dashParticleEmitter = NULL,
        .dashCooldownTimer = NULL,
        .dashDurationTimer = NULL,
    },
    .stats = {
        .walkSpeed = 100,
        .dashSpeed = 1000,
        .dashCooldown = 1,
        .dashDuration = 0.1,
    },
    .animData = {
        .spritesheetPath = "Assets/Images/robert.png",
        .frameSize = {30,40},
        .frameCount = 9,
        .clips = {
            {
                .name = "idle", 
                .startFrameIndex = 0, 
                .endFrameIndex = 0, 
                .frameDuration = 0.4f,
                .looping = false
            },
            {
                .name = "walk", 
                .startFrameIndex = 1, 
                .endFrameIndex = 8, 
                .frameDuration = 0.1f,
                .looping = true
            }
            
        },
        .spriteSize = {30,40},
        .defaultClip = "idle",
        .playOnStart = true,
    }
};