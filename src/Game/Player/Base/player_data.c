#include <player.h>

/*
    @file player_data.c
*   This file contains the player's data initialization.
*/

PlayerData player = {
    .state = {
        .position = {120,72},
    },
    .config = {
        .speed = 100,
        .dashSpeed = 1000,
        .sprite = "Assets/Images/idle.png",
        .spriteSize = {32,32},
        .animation = NULL,
    }
};