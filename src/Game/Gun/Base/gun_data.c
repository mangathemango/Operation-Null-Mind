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
            .angle = 0,
        },
        .stats = {
            .fireRate = 500,
            .spread_angle = 6,
            .damage = 35,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 1,
            .bulletVelocity = BULLET_VELOCITY_MID
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Pistol.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
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
            .angle = 0,
        },
        .stats = {
            .fireRate = 1200,
            .spread_angle = 11,
            .damage = 50,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 1,
            .bulletVelocity = BULLET_VELOCITY_MID
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/SMG.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
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
            .fireRate = 120,
            .spread_angle = 25,
            .damage = 25,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 0.6f,
            .bulletsPerShot = 8,
            .ammoConsumption = 8,
            .bulletVelocity = BULLET_VELOCITY_SLOW
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Shotgun.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
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
            .fireRate = 800,
            .spread_angle = 4,
            .damage = 80,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 2,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Assault Rifle.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
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
            .angle = 0,
        },
        .stats = {
            .fireRate = 650,
            .spread_angle = 2,
            .damage = 120,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 2,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Battle Rifle.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_REVOLVER] = {
        .name = GUN_REVOLVER_NAME,
        .config = {
            .muzzlePosition = {12, 3},
            .ejectionPosition = {6, 3},
            .gripPosition = {5, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 450,
            .spread_angle = 9,
            .damage = 55,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 1,
            .bulletVelocity = BULLET_VELOCITY_SLOW
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Revolver.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_ARMOR_PISTOL] = {
        .name = GUN_ARMOR_PISTOL_NAME,
        .config = {
            .muzzlePosition = {10, 2},
            .ejectionPosition = {5, 2},
            .gripPosition = {4, 4},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 600,
            .spread_angle = 7,
            .damage = 40,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 1,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Armor Pistol.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_RAPID_SMG] = {
        .name = GUN_RAPID_SMG_NAME,
        .config = {
            .muzzlePosition = {23, 4},
            .ejectionPosition = {17, 3},
            .gripPosition = {12, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 1200,
            .spread_angle = 11,
            .damage = 30,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 1,
            .bulletVelocity = BULLET_VELOCITY_MID
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Rapid SMG.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_PDW] = {
        .name = GUN_PDW_NAME,
        .config = {
            .muzzlePosition = {20, 3},
            .ejectionPosition = {15, 3},
            .gripPosition = {10, 5},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 900,
            .spread_angle = 4,
            .damage = 40,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 2,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/PDW.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_BURST_RIFLE] = {
        .name = GUN_BURST_RIFLE_NAME,
        .config = {
            .muzzlePosition = {30, 4},
            .ejectionPosition = {12, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 950,
            .spread_angle = 4,
            .damage = 45,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 3,
            .ammoConsumption = 3,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Burst Rifle.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_BULLPUP_RIFLE] = {
        .name = GUN_BULLPUP_RIFLE_NAME,
        .config = {
            .muzzlePosition = {28, 4},
            .ejectionPosition = {10, 3},
            .gripPosition = {9, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 600,
            .spread_angle = 1,
            .damage = 60,
            .fireMode = FIREMODE_SEMI,
            .bulletLifetime = 1.0f,
            .bulletsPerShot = 1,
            .ammoConsumption = 2,
            .bulletVelocity = BULLET_VELOCITY_FAST
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Bullpup Rifle.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    },
    [GUN_AUTO_SHOTGUN] = {
        .name = GUN_AUTO_SHOTGUN_NAME,
        .config = {
            .muzzlePosition = {35, 4},
            .ejectionPosition = {15, 3},
            .gripPosition = {11, 6},
        },
        .state = {
            .position = {0, 0},
            .angle = 0,
        },
        .stats = {
            .fireRate = 250,
            .spread_angle = 40,
            .damage = 20,
            .fireMode = FIREMODE_AUTO,
            .bulletLifetime = 0.6f,
            .bulletsPerShot = 8,
            .ammoConsumption = 8,
            .bulletVelocity = BULLET_VELOCITY_SLOW
        },
        .animData = {
            .spritesheetPath = "Assets/Images/Guns/Auto Shotgun.png",
            .frameSize = {37, 12},
            .frameCount = 2,
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
                    .startFrameIndex = 1,
                    .endFrameIndex = 1,
                    .frameDuration = 0.4f,
                    .looping = false
                }
            },
            .spriteSize = {37, 12},
            .defaultClip = "left side idle",
            .playOnStart = true
        }
    }
};