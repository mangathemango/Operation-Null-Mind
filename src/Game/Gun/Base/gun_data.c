//? Written by Mango on 07/03/2025

#include <gun.h>

/*
    @file gun.h
*   [Data] This file contains the data configurations for guns in general 
*/

GunData Gun_Pistol = {
    .name = GUN_PISTOL,
    .config = {
        .muzzlePosition = {5, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {

    }
};

GunData Gun_SMG = {
    .name = GUN_SMG,
    .config = {
        .muzzlePosition = {8, 1},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {

    }
};

GunData Gun_Shotgun = {
    .name = GUN_SHOTGUN,
    .config = {
        .muzzlePosition = {24, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {

    }
};

GunData Gun_AssaultRifle = {
    .name = GUN_ASSAULT_RIFLE,
    .config = {
        .muzzlePosition = {22, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {

    }
};

GunData Gun_BattleRifle = {
    .name = GUN_BATTLE_RIFLE,
    .config = {
        .muzzlePosition = {19, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {

    }
};

// Gun animations details

Animation* gunAnimation = NULL;
AnimationData gunAnimData = {
    .spritesheetPath = "Assets/Images/guns.png",
    .frameSize = {49, 25},
    .frameCount = 5,
    .clips = {
        {
            .name = GUN_SMG,
            .startFrameIndex = 0,
            .endFrameIndex = 0,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_ASSAULT_RIFLE,
            .startFrameIndex = 1,
            .endFrameIndex = 1,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_BATTLE_RIFLE,
            .startFrameIndex = 2,
            .endFrameIndex = 2,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_SHOTGUN,
            .startFrameIndex = 3,
            .endFrameIndex = 3,
            .frameDuration = 0.4f,
            .looping = false
        },
        {
            .name = GUN_PISTOL,
            .startFrameIndex = 4,
            .endFrameIndex = 4,
            .frameDuration = 0.4f,
            .looping = false
        },
    },
    .spriteSize = {49, 25},
    .defaultClip = GUN_PISTOL,
    .playOnStart = true,
};