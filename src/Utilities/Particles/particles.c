//? Written by Mango on 07/03/2025

#include <particles.h>
#include <app.h>
#include <time_system.h>
#include <timer.h>
#include <random.h>

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
    }
    return emitter;
}

/*
*   [PostUpdate] Controls the particle emitter's particle emission, age, and rendering.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_Update(ParticleEmitter* emitter) {
    // Loop through all particles and update them
    ParticleEmitter_UpdateParticles(emitter);

    // Destroy emitter when all of its particles are gone
    if (!emitter->active) {
        if (ParticleEmitter_ParticlesAlive(emitter)) return;
        if (emitter->destroyWhenDone) {
            // Destroys particle emitter if set so.
            SDL_Log("Emitter Destroyed");
            ParticleEmitter_DestroyEmitter(emitter);
            return;
        }
        return;
    }

    // Update emitter age
    emitter->emitterAge += Time->deltaTimeSeconds;
    if (emitter->emitterLifetime >= 0 && emitter->emitterAge >= emitter->emitterLifetime) {
        emitter->emitterAge = 0;
        if (emitter->loopCount == 0) {
            emitter->active = false;
            return;
        }
        emitter->loopCount--;
    }

    // Emit particles based on timer
    if (Timer_IsFinished(emitter->emissionTimer)) {
        for (int i = 0; i < emitter->emissionNumber; i++) {
            ParticleEmitter_Emit(emitter);
        }
        Timer_Start(emitter->emissionTimer);
    }
}

/*
*   [Render] Renders every particle of a particle emitter.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_Render(ParticleEmitter* emitter) {
    for (int i = 0; i < emitter->maxParticles; i++) {
        Particle* particle = &emitter->particles[i];
        if (!emitter->particles[i].alive || particle->color.a <= 0) continue;
        
        SDL_Rect rect = {
            particle->position.x,
            particle->position.y,
            particle->size.x,
            particle->size.y
        };
        if (!particle->cameraLock) {
            rect.x = Camera_WorldToScreen((Vec2) {rect.x, rect.y}).x;
            rect.y = Camera_WorldToScreen((Vec2) {rect.x, rect.y}).y;
        }
        SDL_SetRenderDrawColor(app.resources.renderer, 
                                particle->color.r, 
                                particle->color.g, 
                                particle->color.b, 
                                particle->color.a);
        SDL_RenderFillRect(app.resources.renderer, &rect);
    }
}




/*
*   [Utility] Emits a single particle and set its properties based on the emitter.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_Emit(ParticleEmitter* emitter) {
    if (emitter->readyIndex == emitter->maxParticles) return;
    Particle* particle = &emitter->particles[emitter->readyIndex];
    particle->position = emitter->position;
    particle->direction = Vec2_RotateDegrees(emitter->direction, RandFloat(-emitter->angleRange / 2, emitter->angleRange / 2));
    particle->speed = emitter->particleSpeed;
    particle->alive = true;
    particle->maxLifeTime = emitter->particleLifetime;
    particle->timeAlive = 0;

    particle->color = emitter->startColor;
    particle->size = emitter->startSize;
    particle->rotation = 0;
    particle->rotationSpeed = 0;

    particle->velocity = Vec2_Zero;
    particle->acceleration = emitter->gravity;
    particle->drag = emitter->drag; 

    particle->initialSpeed = emitter->particleSpeed;
    particle->initialColor = emitter->startColor;
    particle->initialSize = emitter->startSize;
    particle->cameraLock = emitter->cameraLocked;
    emitter->readyIndex = ParticleEmitter_GetNextReady(emitter);

    if (!emitter->useCollider) return;
    memcpy(particle->collider, &emitter->collider, sizeof(Collider));
    Collider_Register(particle->collider, emitter);
    particle->collider->hitbox.x = particle->position.x;
    particle->collider->hitbox.y = particle->position.y;
}

/*
*   [Utility] Update the state, movement, color and size of every particles of a particle emitter.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_UpdateParticles(ParticleEmitter* emitter) {
    for (int i = 0; i < emitter->maxParticles; i++) {
        Particle* particle = &emitter->particles[i];
        if (!particle->alive) continue;
        
        particle->timeAlive += Time->deltaTimeSeconds;
        if (particle->timeAlive >= particle->maxLifeTime) {
            particle->alive = false;
            emitter->readyIndex = i;
            if (emitter->useCollider && particle->collider != NULL)
            {
                Collider_Reset(particle->collider);
            }
        }
        // Movement
        if (emitter->custom_Movement) {
            emitter->custom_Movement(&emitter->particles[i]);
        } else {
            particle->speed -= Time->deltaTimeSeconds * particle->speed * particle->drag;
            particle->velocity = Vec2_Multiply(particle->direction, particle->speed);
            particle->velocity = Vec2_Add(particle->velocity, particle->acceleration);
            particle->velocity = Vec2_Add(particle->velocity, Vec2_Multiply(emitter->gravity, Time->deltaTimeSeconds));
            particle->speed = Vec2_Magnitude(particle->velocity);
            particle->direction = Vec2_Normalize(particle->velocity);
            particle->position.x += particle->velocity.x * Time->deltaTimeSeconds;
            particle->position.y += particle->velocity.y * Time->deltaTimeSeconds;
        }

        // Color
        float t = particle->timeAlive / particle->maxLifeTime;
        particle->color.r = particle->initialColor.r + (emitter->endColor.r - emitter->startColor.r) * t;
        particle->color.g = particle->initialColor.g + (emitter->endColor.g - emitter->startColor.g) * t;   
        particle->color.b = particle->initialColor.b + (emitter->endColor.b - emitter->startColor.b) * t;
        particle->color.a = particle->initialColor.a + (emitter->endColor.a - emitter->startColor.a) * t;

        // Size
        particle->size.x = particle->initialSize.x + (emitter->endSize.x - emitter->startSize.x) * t;
        particle->size.y = particle->initialSize.y + (emitter->endSize.y - emitter->startSize.y) * t;

        // Rotation
        particle->rotation += particle->rotationSpeed * Time->deltaTimeSeconds;

        // Collider
        if (!emitter->useCollider) continue;
        if (!particle->collider || !particle->collider->active) continue;
        particle->collider->hitbox.x = particle->position.x;
        particle->collider->hitbox.y = particle->position.y;
        particle->collider->hitbox.w = particle->size.x;
        particle->collider->hitbox.h = particle->size.y;
    }
}

/*
*   [Utility] Set the max particles property of an emitter.
?   This is probably never going to be used, since this is already set inside particle_emitterpreset.
?   Only use this if (for some reason) you want to change a particle emitter's max particles in the middle of a game
    @param emitter A pointer to the particle emitter
    @param maxParticles The target max particle number
*/
void ParticleEmitter_SetMaxParticles(ParticleEmitter* emitter, int maxParticles) {
    emitter->maxParticles = maxParticles;
    emitter->particles = realloc(emitter->particles, sizeof(Particle) * emitter->maxParticles);
}

/*
*   [Utility] Gets the index of the next available particle inside an emitter's particle array.
?   Particle is available of it's dead, basically
    @param emitter A pointer to the particle emitter
*/
int ParticleEmitter_GetNextReady(ParticleEmitter* emitter) {
    for (int i = 0; i < emitter->maxParticles; i++) {
        if (!emitter->particles[i].alive) return i;
    }
    return emitter->maxParticles;
}

/*
*   [Utility/Quit] Destroys a particle emitter.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_DestroyEmitter(ParticleEmitter* emitter) {
    if (!emitter) return;
    free(emitter->particles);
    Timer_Destroy(emitter->emissionTimer);
    *(emitter->selfReference) = NULL;
    free(emitter);
}

/*
*   [Utility] Check if there are any alive particles inside an emitter's particle array.
    @param emitter A pointer to the particle emitter
*/
bool ParticleEmitter_ParticlesAlive(ParticleEmitter* emitter) {
    for (int i = 0; i < emitter->maxParticles; i++) {
        if (emitter->particles[i].alive) return true;
    }
    return false;
}

/*
*   [Utility] Allows a particle emitter to go through another loop.
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_ActivateOnce(ParticleEmitter* emitter) {
    emitter->active = true;
    emitter->emitterAge = 0;
    if (emitter->loopCount == 0) emitter->loopCount = 1;
}

/*
*   [Utility] Deactivates a particle emitter
    @param emitter A pointer to the particle emitter
*/
void ParticleEmitter_Deactivate(ParticleEmitter* emitter) {
    emitter->active = false;
    emitter->emitterAge = 0;
}