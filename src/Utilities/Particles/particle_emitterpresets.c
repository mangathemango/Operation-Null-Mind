/*
    @file particle_emitterpresets.c
*   [Data] This file contains all the data about particle emitter presets. Read particle_emitterpresets.h for more

?   Updated by Mango on 08/03/2025
*/

#include <particle_emitterpresets.h>
#define BRASS_COLOR {238,209,131,255}
#define BRASS_COLOR_FADE {238,209,131,0}
#define SHOTSHELL_COLOR {207,43,33,255}
#define SHOTSHELL_COLOR_FADE {207,43,33,0}

/*
*   [Start] Creates a particle emitter from a preset.
    @param preset The preset to create the emitter from. This is found inside particle_emitterpresets.h
    @returns A pointer to the created emitter
*/
ParticleEmitter* ParticleEmitter_CreateFromPreset(ParticleEmitter preset) {
    // Create emitter
    ParticleEmitter* emitter = malloc(sizeof(ParticleEmitter));
    if (!emitter) return NULL;
    memcpy(emitter, &preset, sizeof(ParticleEmitter));

    // Set up emitter Timer
    emitter->emissionTimer = Timer_Create(emitter->emissionRate);
    Timer_Start(emitter->emissionTimer);

    // Create particle array
    emitter->particles = malloc(sizeof(Particle) * emitter->maxParticles);
    if (!emitter->particles) {
        free(emitter);
        return NULL;
    }
    // Set all particles to dead by default
    for (int i = 0; i < emitter->maxParticles; i++) {
        emitter->particles[i].alive = false; 
        if (!emitter->useCollider) continue;
        emitter->particles[i].collider = malloc(sizeof(Collider));
        memcpy(&emitter->collider, &emitter->particles[i].collider, sizeof(Collider));
    }
    return emitter;
}

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

    .particleLifetime = 0.1,
    .particleSpeed = 200,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {61, 135, 255, 255},
    .endColor = {255, 255, 255, 100},
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

// Particle emitter for muzzle flashes
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

// Particle emitter for Pistol and SMG bullet casings
ParticleEmitter ParticleEmitter_PistolSMGCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0.1,
    .emissionNumber = 1,
    .maxParticles = 10,
    .angleRange = 20,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

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

// Particle emitter for Assault Rifle and Battle Rifle bullet casings
ParticleEmitter ParticleEmitter_ARBRCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0.1,
    .emissionNumber = 1,
    .maxParticles = 30,
    .angleRange = 20,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.3,
    .particleSpeed = 150,
    .custom_Movement = NULL,

    .startColor = BRASS_COLOR,
    .endColor = BRASS_COLOR_FADE,
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

// Particle emitter for Shotgun shell casings
ParticleEmitter ParticleEmitter_ShotgunCasing = {
    .position = {100, 100},

    .direction = {-1, -1},
    .emissionRate = 0.3,
    .emissionNumber = 1,
    .maxParticles = 10,
    .angleRange = 20,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

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

// Default particle emitter, mainly used for testing what looks good / messing around
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


ParticleEmitter bullet_Default = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0,
    .emissionNumber = 1,
    .maxParticles = 1,
    .angleRange = 0,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.5,
    .particleSpeed = 200,
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
        .hitbox = {
            .x = 0,
            .y = 0,
            .w = 6,
            .h = 6
        }
    },
};

ParticleEmitter* test_emitter = NULL;