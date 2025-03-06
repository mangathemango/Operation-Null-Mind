#include <gun.h>


GunData Gun_Pistol = {
    .config = {
        .muzzlePosition = {4, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {
        .name = GUN_PISTOL
    }
};

GunData Gun_SMG = {
    .config = {
        .muzzlePosition = {7, 1},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {
        .name = GUN_SMG
    }
};

GunData Gun_Shotgun = {
    .config = {
        .muzzlePosition = {20, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {
        .name = GUN_SHOTGUN
    }
};

GunData Gun_AssaultRifle = {
    .config = {
        .muzzlePosition = {22, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {
        .name = GUN_ASSAULT_RIFLE
    }
};

GunData Gun_BattleRifle = {
    .config = {
        .muzzlePosition = {18, 0},
    },
    .state = {
        .position = {0, 0},
        .angle = 0
    },
    .stats = {
        .name = GUN_BATTLE_RIFLE
    }
};

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