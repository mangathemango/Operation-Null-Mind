/**
 * @file particle_emitterpresets.c
 * @brief Contains preset configurations for particle emitters
 *
 * This file defines the default configurations for various types of particle emitters
 * such as muzzle flashes, bullet casings, dash effects, etc.
 *
 * @author Mango
 * @date 2025-03-08
 */

#include <particle_emitterpresets.h>

/** Color constants for brass material */
#define BRASS_COLOR {238,209,131,255}
#define BRASS_COLOR_FADE {238,209,131,100}

/** Color constants for shotgun shell material */
#define SHOTSHELL_COLOR {207,43,33,255}
#define SHOTSHELL_COLOR_FADE {207,43,33,0}

/** 
 * @brief Dash effect particle emitter preset
 * Creates trail particles behind the player when dashing
 */
ParticleEmitter ParticleEmitter_Dash = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 10,
    .maxParticles = 200,
    .angleRange = 25,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.1,
    .particleSpeed = 200,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {204, 137, 20, 255},
    .endColor = {255, 255, 255, 0},
    .startSize = {3, 3},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 4,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** 
 * @brief Muzzle flash particle emitter preset
 * Creates bright flash particles at gun muzzle when firing
 */
ParticleEmitter ParticleEmitter_MuzzleFlash = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0.1,
    .emissionNumber = 10,
    .maxParticles = 100,
    .angleRange = 30,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.1,
    .particleSpeed = 200,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 255, 0, 255},
    .endColor = {255, 0, 0, 0},
    .startSize = {1, 1},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 4,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** 
 * @brief Pistol and SMG casing ejection particle preset
 * Creates small brass casings when pistol or SMG is fired
 */
ParticleEmitter ParticleEmitter_PistolSMGCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 10,
    .angleRange = 60,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.3,
    .particleSpeed = 150,
    .custom_Movement = NULL,

    .startColor = BRASS_COLOR,
    .endColor = BRASS_COLOR_FADE,
    .startSize = {2, 1},
    .endSize = {2, 1},
    .particleTexture = NULL,

    .gravity = {0, 10},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,
    
    .useCollider = false,
};

/** 
 * @brief Assault Rifle and Battle Rifle casing ejection particle preset
 * Creates medium brass casings when rifle is fired
 */
ParticleEmitter ParticleEmitter_ARBRCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 30,
    .angleRange = 20,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.3,
    .particleSpeed = 150,
    .custom_Movement = NULL,

    .startColor = BRASS_COLOR,
    .endColor = BRASS_COLOR_FADE,
    .startSize = {3, 1},
    .endSize = {3, 1},
    .particleTexture = NULL,

    .gravity = {0, 8},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** 
 * @brief Shotgun shell ejection particle preset
 * Creates red shotgun shells when shotgun is fired
 */
ParticleEmitter ParticleEmitter_ShotgunCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 10,
    .angleRange = 20,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.3,
    .particleSpeed = 150,
    .custom_Movement = NULL,

    .startColor = SHOTSHELL_COLOR,
    .endColor = SHOTSHELL_COLOR_FADE,
    .startSize = {3, 1},
    .endSize = {3, 1},
    .particleTexture = NULL,

    .gravity = {0, 10},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** 
 * @brief Default particle emitter preset for testing
 * General purpose emitter for experimenting with effects
 */
ParticleEmitter ParticleEmitter_Default = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 3,
    .maxParticles = 100,
    .angleRange = 180,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .cameraLocked = false,
    .particleLifetime = 0.1,
    .particleSpeed = 200,
    .custom_Movement = NULL,

    .startColor = {255, 255, 0, 255},
    .endColor = {255, 255, 0, 255},
    .startSize = {1,1},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 4,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** 
 * @brief Default bullet particle emitter preset
 * Base configuration for all projectiles in the game
 */
ParticleEmitter ParticleEmitter_BulletDefault = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 50,
    .angleRange = 0,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 1,
    .particleSpeed = 500,
    .custom_Movement = NULL,

    .startColor = {255, 255, 255, 255},
    .endColor = {255, 255, 255, 255},
    .startSize = {3,3},
    .endSize = {3, 3},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = true,
    .collider = {
        .layer = COLLISION_LAYER_PLAYER_PROJECTILE,
        .collidesWith = 
            COLLISION_LAYER_ENVIRONMENT |
            COLLISION_LAYER_ENEMY |
            COLLISION_LAYER_ENEMY_PROJECTILE,
        .hitbox = {
            .x = 0,
            .y = 0,
            .w = 6,
            .h = 6
        }
    },
};

/** 
 * @brief Default bullet particle emitter preset
 * Base configuration for all projectiles in the game
 */
ParticleEmitter ParticleEmitter_BulletEnemy = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 1000,
    .angleRange = 10,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 5,
    .particleSpeed = 200,
    .custom_Movement = NULL,

    .startColor = {255, 0, 0, 255},
    .endColor = {255, 0, 0, 255},
    .startSize = {6, 6},
    .endSize = {6, 6},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = true,
    .collider = {
        .layer = COLLISION_LAYER_PLAYER_PROJECTILE,
        .collidesWith = 
            COLLISION_LAYER_ENVIRONMENT |
            COLLISION_LAYER_PLAYER ,
        .hitbox = {
            .x = 0,
            .y = 0,
            .w = 6,
            .h = 6
        }
    },
};

/** 
 * @brief Bullet impact fragment particle preset
 * Creates sparks and fragments when bullets hit surfaces
 */
ParticleEmitter ParticleEmitter_BulletFragments = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 4,
    .maxParticles = 100,
    .angleRange = 90,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.1,
    .particleSpeed = 500,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 225, 0, 255},
    .endColor = {255, 0, 0, 0},
    .startSize = {5, 5},
    .endSize = {2, 2},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

ParticleEmitter ParticleEmitter_Explosion = {
    .position = {100, 100},

    .direction = {1, 0},
    .emissionRate = 0,
    .emissionNumber = 50,
    .maxParticles = 200,
    .angleRange = 360,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.3f,
    .particleSpeed = 300,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 0, 0, 255},
    .endColor = {255, 225, 0, 0},
    .startSize = {5, 5},
    .endSize = {5, 5},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

ParticleEmitter ParticleEmitter_Gernade = {
    .position = {100, 100},

    .direction = {1, 0},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 50,
    .angleRange = 30,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,
    .particleLifetime = 2.0f,
    .particleSpeed = 500,
    .custom_Movement = NULL,

    .startColor = {255, 0, 0, 255},
    .endColor = {255, 0, 0, 255},
    .startSize = {7, 7},
    .endSize = {7, 7},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 3.0f,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = true,
    .collider = {
        .collidesWith = COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER,
        .layer = COLLISION_LAYER_ENEMY_PROJECTILE,
    }
};


ParticleEmitter ParticleEmitter_Fire = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0.1,
    .emissionNumber = 10,
    .maxParticles = 500,
    .angleRange = 150,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,
    .particleLifetime = 0.25f,
    .particleSpeed = 100,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 255, 0, 255},
    .endColor = {255, 0, 0, 0},
    .startSize = {5, 5},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 2.0f,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
    .collider = {
        .collidesWith = COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER,
        .layer = COLLISION_LAYER_ENEMY_PROJECTILE,
    }
};

ParticleEmitter ParticleEmitter_Parry = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 10,
    .maxParticles = 100,
    .angleRange = 360,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.05,
    .particleSpeed = 500,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 255, 0, 255},
    .endColor = {255, 0, 0, 0},
    .startSize = {5, 5},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 0,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,

    .useCollider = false,
};

/** @brief Test emitter for development purposes */
ParticleEmitter* test_emitter = NULL;