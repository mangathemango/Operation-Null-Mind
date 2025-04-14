/**
 * @file particles.h
 * @brief A particle system for visual effects and environmental elements.
 *
 * Particles are emitted from structs called ParticleEmitters.   
 * Therefore, to generate particles, you have to, of course, create a Particle Emitter first.
 * Emitters can be created based on a preset in particle_emitterpresets.c
 * (Information on how to create a preset can be found inside particle_emitterpresets.h)
 * After that, you can update and render the particles inside the game loop.
 *
 * @section particle_usage Usage
 * This is how it's done:
 *
 * @subsection preset_step1 Step 1: Choose a preset
 * Look for a preset in particle_emitterpresets.c, for example ParticleEmitter_Default
 *
 * @subsection preset_step2 Step 2: Create the emitter
 * These lines are called somewhere inside App_Start()
 * ```c
 * ParticleEmitter *emitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Default);
 * emitter->selfReference = &emitter;    // YOU HAVE TO DO THIS OR YOU DIE
 * ```
 *
 * @subsection preset_step3 Step 3: Update and render in the game loop
 * These lines are called somewhere inside App_PostUpdate()
 * ```c
 * // You can modify the emitter's properties as needed.   
 * emitter->position = ....; 
 * emitter->direction = ....;
 *
 * // Update and render the emitter
 * ParticleEmitter_Update(emitter);            
 * ParticleEmitter_Render(emitter);
 * ```
 * 
 * @subsection preset_step4 Step 4: One-time activation (optional)
 * For emitters that don't loop infinitely, add conditionals to activate the emitter
 * ```c
 * if (...) {
 *     ParticleEmitter_ActivateOnce(gunSparksEmitter);  // Activate the emitter once
 * }
 * ```
 *
 * @author Mango
 * @date 2025-03-05
 */

#pragma once

#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>
#include <timer.h>
#include <camera.h>
#include <colliders.h>

/**
 * @brief A struct that represents a particle.
 *
 * Particles are created and managed by a ParticleEmitter.
 */
typedef struct Particle {
    Vec2 position;              /**< Current position */
    Vec2 direction;             /**< Direction of movement */
    float speed;                /**< Current speed */
    bool alive;                 /**< Whether the particle is alive */
    float maxLifeTime;          /**< Time particle can live in seconds */
    float timeAlive;            /**< Time particle has been alive in seconds */
    
    // Visual properties
    SDL_Color color;            /**< Current color (interpolated between start/end) */
    Vec2 size;                  /**< Current size (can change over lifetime) */
    float rotation;             /**< Current rotation angle (Not implemented) */
    float rotationSpeed;        /**< Speed of rotation (degrees/second) (Not implemented) */
    
    // Physics properties
    Vec2 velocity;              /**< Current velocity vector. Is calculated every frame via direction and speed */
    Vec2 acceleration;          /**< Current acceleration (affected by gravity) */
    float drag;                 /**< Individual drag factor */
    
    // Behavior
    float initialSpeed;         /**< Starting speed (for reference/reset) */
    SDL_Color initialColor;     /**< Starting color (for reference/reset) */
    Vec2 initialSize;           /**< Starting size (for reference/reset) */
    bool cameraLock;            /**< Whether the particle is locked to the camera */
    int bounceCount;            /**< Track number of bounces (Not implemented) */

    Collider* collider;         /**< Collider for the particle (Not implemented) */
} Particle;

/**
 * @brief A struct that represents the configurations of a particle emitter.
 *
 * Emitter is responsible for creating and managing particles.
 * Emitter presets (such as fire, smoke, gunshots, etc.) can be created and reused inside particle_emitterpresets.h and .c 
 * Emitters themselves can be created with ParticleEmitter_CreateDefault() and then modified as needed.
 * 
 * @warning Make sure to set the selfReference field to the address of the emitter pointer.
 * @code
 *     ParticleEmitter *emitter = ParticleEmitter_CreateDefault(); 
 *     emitter->selfReference = &emitter;
 * @endcode
 * Call ParticleEmitter_Update() and ParticleEmitter_Render() every frame to update and render the particles.
 */
typedef struct ParticleEmitter {
    // Emitter Properties
    Vec2 position;                          /**< Position of the emitter */
    
    // Emission Configuration
    float emissionRate;                     /**< Time between emissions in seconds */
    int emissionNumber;                     /**< Number of particles to emit per emission */
    int maxParticles;                       /**< Maximum particles this emitter can have */
    Vec2 direction;                         /**< Base direction of emission. Direction is randomized by angleRange */
    float angleRange;                       /**< Spread angle in degrees (0 - 360). Spread is applied to direction. */
    
    // Emission control
    bool active;                            /**< Whether the current emitter is active */
    float emitterLifetime;                  /**< How long the emitter is active in seconds */
    float emitterAge;                       /**< How long the emitter has been active in seconds */
    int loopCount;                          /**< Number of times to loop. -1 for Infinite. 1 for once. 0 for none */
    bool destroyWhenDone;                   /**< Destroys emitter when all particles are gone. Suitable for one-time effects. */
    
    // Particle Properties
    bool cameraLocked;                      /**< If true, particles will appear static on the screen. */
    float particleLifetime;                 /**< How long particles live in seconds */
    float particleSpeed;                    /**< Particle movement speed */
    void (*custom_Movement)(Particle*);     /**< Movement behavior function (Will override default movement) */
    
    // Visual Properties
    SDL_Color startColor;                   /**< Initial particle color */
    SDL_Color endColor;                     /**< Final particle color */
    Vec2 startSize;                         /**< Initial size of particles in pixels */
    Vec2 endSize;                           /**< Final size of particles in pixels */
    SDL_Texture* particleTexture;           /**< Optional texture (NULL = rectangle) */
    
    // Physics
    Vec2 gravity;                           /**< Force applied over time */
    float drag;                             /**< Air resistance factor */

    // Runtime State
    Timer* emissionTimer;                   /**< Timer for emission control */
    Particle* particles;                    /**< Array of particles */
    int readyIndex;                         /**< Next available particle index */
    struct ParticleEmitter** selfReference; /**< A double pointer to this emitter. Used to set the reference to NULL when destroyed. */

    //Collider properties
    bool useCollider;                       /**< Whether to use a collider for the emitter */
    Collider collider;                      /**< Collider for the emitter (Not implemented) */
} ParticleEmitter;

/**
 * @brief Sets the maximum number of particles for an emitter.
 * @param emitter The emitter to set the maximum particles for.
 * @param maxParticles The maximum number of particles.
 */
void ParticleEmitter_SetMaxParticles(ParticleEmitter* emitter, int maxParticles);

/**
 * @brief Emits particles from the emitter.
 * @param emitter The emitter to emit particles from.
 */
void ParticleEmitter_Emit(ParticleEmitter* emitter);

/**
 * @brief Gets the next available particle index.
 * @param emitter The emitter to get the next available particle index from.
 * @return The next available particle index.
 */
int ParticleEmitter_GetNextReady(ParticleEmitter* emitter);

/**
 * @brief Updates the particles of an emitter.
 * @param emitter The emitter to update the particles of.
 */
void ParticleEmitter_UpdateParticles(ParticleEmitter* emitter);

/**
 * @brief Updates the emitter.
 * @param emitter The emitter to update.
 */
void ParticleEmitter_Update(ParticleEmitter* emitter);

/**
 * @brief Activates the emitter once.
 * @param emitter The emitter to activate.
 */
void ParticleEmitter_ActivateOnce(ParticleEmitter* emitter);

/**
 * @brief Deactivates the emitter.
 * @param emitter The emitter to deactivate.
 */
void ParticleEmitter_Deactivate(ParticleEmitter* emitter);

/**
 * @brief Renders the particles of an emitter.
 * @param emitter The emitter to render the particles of.
 */
void ParticleEmitter_Render(ParticleEmitter* emitter);

/**
 * @brief Destroys the emitter and frees its memory.
 * @param emitter The emitter to destroy.
 */
void ParticleEmitter_DestroyEmitter(ParticleEmitter* emitter);

/**
 * @brief Checks if the emitter has any particles alive.
 * @param emitter The emitter to check.
 * @return true if the emitter has particles alive, false otherwise.
 */
bool ParticleEmitter_ParticlesAlive(ParticleEmitter* emitter);