//? Written by Mango on 04/03/2025

#include <particle_movement.h>
#include <time_system.h>
#include <math.h>
#include <random.h>

/**
 * [Utility] Completely linear movement - constant speed and direction
 * 
 * @param particle The particle to update
 */
void Particle_LinearMovement(Particle* particle) {
    Vec2 velocity = {
        particle->direction.x * particle->speed,
        particle->direction.y * particle->speed
    };
    particle->position.x += velocity.x * Time->deltaTimeSeconds;
    particle->position.y += velocity.y * Time->deltaTimeSeconds;
}

/**
 * [Utility] Accelerated movement
 * 
 * @param particle The particle to update
 */
void Particle_AcceleratedMovement(Particle* particle) {
    particle->speed += 100 * Time->deltaTimeSeconds;
    Vec2 velocity = {
        particle->direction.x * particle->speed,
        particle->direction.y * particle->speed
    };
    particle->position.x += velocity.x * Time->deltaTimeSeconds;
    particle->position.y += velocity.y * Time->deltaTimeSeconds;
}

/**
 * [Utility] Decelerated movement (this is just drag lmfao)
 * 
 * @param particle The particle to update
 */
void Particle_DeceleratedMovement(Particle* particle) {
    particle->speed -= Time->deltaTimeSeconds * particle->speed * 2.7;
    Vec2 velocity = {
        particle->direction.x * particle->speed,
        particle->direction.y * particle->speed
    };
    particle->position.x += velocity.x * Time->deltaTimeSeconds;
    particle->position.y += velocity.y * Time->deltaTimeSeconds;
}

/**
 * [Utility] Spiral movmeent
 * 
 * @param particle The particle to update
 */
void Particle_SpiralMovement(Particle* particle) {
    float rotation = 180; // Amount to rotate in degrees/second
    particle->direction = Vec2_RotateDegrees(particle->direction, rotation * Time->deltaTimeSeconds);
    Vec2 velocity = {
        particle->direction.x * particle->speed,
        particle->direction.y * particle->speed
    };
    particle->position.x += velocity.x * Time->deltaTimeSeconds;
    particle->position.y += velocity.y * Time->deltaTimeSeconds;
}

/**
 * [Utility] Random movement
 * 
 * @param particle The particle to update
 */
void Particle_RandomMovement(Particle* particle) {
    Vec2 velocity = {
        particle->direction.x * particle->speed,
        particle->direction.y * particle->speed
    };
    particle->position.x += velocity.x * Time->deltaTimeSeconds;
    particle->position.y += velocity.y * Time->deltaTimeSeconds;
    particle->position.x += (rand() % 3 - 1);
    particle->position.y += (rand() % 3 - 1);
}

/**
 * [Utility] Sine movement
 * 
 * @param particle The particle to update
 */
void Particle_SineMovement(Particle* particle) {
    particle->position.x += particle->direction.x * particle->speed * Time->deltaTimeSeconds;
    particle->position.y += particle->direction.y * particle->speed * Time->deltaTimeSeconds;
    particle->position.x += sin(particle->timeAlive * RandInt(1, 5)) * Time->deltaTimeSeconds * 10;
    particle->position.y += cos(particle->timeAlive * RandInt(1, 5)) * Time->deltaTimeSeconds * 10;
}