#include <player.h>

/*
    @file player_data.c
*   [Data] This file contains the player's data initialization.
*/

PlayerData player = {
    .state = {
        .position = {120,72},
        .direction = {0, 0},
        .dashing = false,   
        .movementLocked = false,
        .moving = false,
    },
    .config = {
        .animation = NULL,
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
        .frameCount = 1,
        .clips = {
            {
                .name = "idle", 
                .startFrameIndex = 0, 
                .endFrameIndex = 0, 
                .frameDuration = 0.4f,
                .looping = false
            }
        },
        .spriteSize = {30,40},
        .defaultClip = "idle",
        .playOnStart = true,
    }
};