#pragma once

#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>
#include <timer.h>

typedef struct {
    // Current fields
    Vec2 position;
    Vec2 direction;
    float speed;
    bool alive;
    float maxLifeTime;
    float timeAlive;
    
    // Visual properties
    SDL_Color color;           // Current color (interpolated between start/end)
    Vec2 size;                 // Current size (can change over lifetime)
    float rotation;            // Current rotation angle
    float rotationSpeed;       // Speed of rotation (degrees/second)
    
    // Physics properties
    Vec2 velocity;             // Current velocity vector
    Vec2 acceleration;         // Current acceleration
    float drag;           // Individual drag factor (0-1)
    
    // Behavior
    float initialSpeed;        // Starting speed (for reference/reset)
    SDL_Color initialColor;    // Starting color (for reference/reset)
    Vec2 initialSize;          // Starting size (for reference/reset)
    int bounceCount;           // Track number of bounces
} Particle;


typedef struct ParticleEmitter {
    // Emitter Properties
    Vec2 position;                          // Position of the emitter
    
    // Emission Configuration
    float emissionRate;                     // Time between emissions in seconds
    int emissionNumber;                     // Number of particles to emit per emission
    int maxParticles;                       // Maximum particles this emitter can have
    Vec2 direction;                         // Base direction of emission
    float angleRange;                       // Spread angle in degrees
    
    // Emission control
    bool active;                            // Whether the current emitter is active
    float emitterLifetime;                  // How long the emitter is active in seconds
    float emitterAge;                       // How long the emitter has been active in seconds
    int loopCount;                          // Number of times to loop. -1 for Infinite.
    bool destroyWhenDone;                   // Should emitter be freed when particles are gone?
    
    // Particle Properties
    float particleLifetime;                 // How long particles live in seconds  
    float particleSpeed;                    // Particle movement speed
    void (*custom_Movement)(Particle*);     // Movement behavior function
    
    // Visual Properties (to add)
    SDL_Color startColor;                // Initial particle color
    SDL_Color endColor;                  // Final particle color
    Vec2 startSize;
    Vec2 endSize;                   // Size of particles
    SDL_Texture* particleTexture;        // Optional texture (NULL = rectangle)
    
    // Additional Physics (to add)
    Vec2 gravity;                        // Force applied over time
    float drag;                          // Air resistance factor

    // Runtime State
    Timer* emissionTimer;                   // Timer for emission control
    Particle* particles;                    // Array of particles
    int readyIndex;      
    struct ParticleEmitter** selfReference;                   // Next available particle index
} ParticleEmitter;

void ParticleEmitter_SetMaxParticles(ParticleEmitter* emitter, int maxParticles);
void ParticleEmitter_Emit(ParticleEmitter* emitter);
int ParticleEmitter_GetNextReady(ParticleEmitter* emitter);
void ParticleEmitter_UpdateParticles(ParticleEmitter* emitter);
void ParticleEmitter_Update(ParticleEmitter* emitter);
void ParticleEmitter_ActivateOnce(ParticleEmitter* emitter);
void ParticleEmitter_Deactivate(ParticleEmitter* emitter);
void ParticleEmitter_Render(ParticleEmitter* emitter);
void ParticleEmitter_DestroyEmitter(ParticleEmitter* emitter);
bool ParticleEmitter_ParticlesAlive(ParticleEmitter* emitter);