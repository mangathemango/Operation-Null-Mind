#include <particle_emitterpresets.h>

ParticleEmitter ParticleEmitter_Default = {
    .position = {100, 100},

    .direction = {0, -1},
    .emissionRate = 0.01,
    .emissionNumber = 10,
    .maxParticles = 10000,
    .angleRange = 360,

    .active = true,
    .emitterLifetime = 0,
    .emitterAge = 0,
    .loopCount = 0,
    .destroyWhenDone = false,

    .particleLifetime = 0.5,
    .particleSpeed = 20,
    .custom_Movement = Particle_RandomMovement,

    .startColor = {255, 0, 0, 50},
    .endColor = {255, 255, 0, 0},
    .startSize = {3, 3},
    .endSize = {2, 2},
    .particleTexture = NULL,

    .gravity = {0, 0},
    .drag = 4,

    .particles = NULL,
    .readyIndex = 0,
    .selfReference = NULL,
};

ParticleEmitter* test_emitter = NULL;

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
    }
    return emitter;
}