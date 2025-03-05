#include <particle_emitterpresets.h>

ParticleEmitter Default_ParticleEmitter = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0.01,
    .emissionNumber = 10,
    .maxParticles = 10000,
    .angleRange = 360,

    .active = false,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 1,
    .destroyWhenDone = false,

    .particleLifetime = 30,
    .particleSpeed = 20,
    .custom_Movement = NULL,

    .startColor = {255, 0, 0, 100},
    .endColor = {255, 255, 0, 0},
    .startSize = {3, 3},
    .endSize = {1, 1},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 4,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,
};

ParticleEmitter* test_emitter = NULL;

ParticleEmitter* ParticleEmitter_CreateDefault() {
    ParticleEmitter* emitter = malloc(sizeof(ParticleEmitter));
    if (!emitter) return NULL;
    memcpy(emitter, &Default_ParticleEmitter, sizeof(ParticleEmitter));
    emitter->emissionTimer = Timer_Create(emitter->emissionRate);
    Timer_Start(emitter->emissionTimer);
    emitter->particles = malloc(sizeof(Particle) * emitter->maxParticles);
    if (!emitter->particles) {
        free(emitter);
        return NULL;
    }
    for (int i = 0; i < emitter->maxParticles; i++) {
        emitter->particles[i].alive = false;
    }
    return emitter;
}