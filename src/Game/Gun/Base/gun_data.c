/**
 * @file gun_data.c
 * @brief Contains definitions for all weapon types
 *
 * Defines the properties, statistics, and visual configurations
 * for all gun types available in the game.
 *
 * @author Mango
 * @date 2025-03-07
 */

//? Written by Mango on 07/03/2025

#include <gun.h>

/*
    @file gun.h
*   [Data] This file contains the data configurations for guns in general 
*/

// Array of all gun data indexed by Gun enum
GunData GunList[GUN_COUNT] = {
    [GUN_PISTOL] = {
        .name = GUN_PISTOL_NAME,
        .config = {
            .muzzlePosition = {9, 2},
            .ejectionPosition = {5, 2},
            .gripPosition = {4, 4},
        },
        .state = {
            .position = {0, 0},
            .angle = 0
        },
        .stats = {
            .fireRate = 300,
            .ammoCapacity = 0,
            .spread_angle = 2,
            .damage = 10,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Pistol.png",
            .frameSize = {8, 10},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 10,
                    .endFrameIndex = 10,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 10,
                    .endFrameIndex = 19,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {9, 11},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_SMG] = {
        .name = GUN_SMG_NAME,
        .config = {
            .muzzlePosition = {23, 4},
            .ejectionPosition = {17, 3},
            .gripPosition = {12, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0
        },
        .stats = {
            .fireRate = 1000,
            .ammoCapacity = 0,
            .spread_angle = 60,
            .damage = 10,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/SMG.png",
            .frameSize = {23, 15},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 10,
                    .endFrameIndex = 10,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 10,
                    .endFrameIndex = 19,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {23, 15},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_SHOTGUN] = {
        .name = GUN_SHOTGUN_NAME,
        .config = {
            .muzzlePosition = {34, 3},
            .ejectionPosition = {15, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0
        },
        .stats = {
            .fireRate = 600,
            .ammoCapacity = 0,
            .spread_angle = 60,
            .damage = 10,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 0.1f,
            .bulletsPerShot = 5
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Shotgun.png",
            .frameSize = {35, 9},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 5,
                    .endFrameIndex = 5,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 4,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 5,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {35, 9},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_ASSAULT_RIFLE] = {
        .name = GUN_ASSAULT_RIFLE_NAME,
        .config = {
            .muzzlePosition = {31, 4},
            .ejectionPosition = {12, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0
        },
        .stats = {
            .fireRate = 400,
            .ammoCapacity = 0,
            .spread_angle = 20,
            .damage = 10,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Assault Rifle.png",
            .frameSize = {31, 19},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 10,
                    .endFrameIndex = 10,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 10,
                    .endFrameIndex = 19,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {31, 19},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_BATTLE_RIFLE] = {
        .name = GUN_BATTLE_RIFLE_NAME,
        .config = {
            .muzzlePosition = {34, 4},
            .ejectionPosition = {13, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0
        },
        .stats = {
            .fireRate = 300,
            .ammoCapacity = 0,
            .spread_angle = 10,
            .damage = 10,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Battle Rifle.png",
            .frameSize = {35, 19},
            .frameCount = 20,
            .clips = {
                {
                    .name = "left side idle",
                    .startFrameIndex = 0,
                    .endFrameIndex = 0,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "right side idle",
                    .startFrameIndex = 10,
                    .endFrameIndex = 10,
                    .frameDuration = 0.4f,
                    .looping = false
                },
                {
                    .name = "left side reload",
                    .startFrameIndex = 0,
                    .endFrameIndex = 9,
                    .frameDuration = 0.1f,
                    .looping = true
                },
                {
                    .name = "right side reload",
                    .startFrameIndex = 10,
                    .endFrameIndex = 19,
                    .frameDuration = 0.1f,
                    .looping = true
                },
            },
            .spriteSize = {35, 19},   
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    }
};