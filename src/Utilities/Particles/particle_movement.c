/**
 * @file particle_movement.c
 * @brief Contains movement patterns for particles
 *
 * This file implements various movement patterns that can be applied to particles,
 * including linear, accelerated, decelerated, spiral, random, and sine movement.
 *
 * @author Mango
 * @date 2025-03-04
 */

//? Written by Mango on 04/03/2025

#include <particle_movement.h>
#include <time_system.h>
#include <math.h>
#include <random.h>

/**
 * @brief [Utility] Completely linear movement - constant speed and direction
 * 
 * Moves the particle at a constant speed and direction without acceleration or deceleration.
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
 * @brief [Utility] Accelerated movement
 * 
 * Gradually increases the particle's speed over time.
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
 * @brief [Utility] Decelerated movement (this is just drag lmfao)
 * 
 * Gradually decreases the particle's speed over time, simulating drag.
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
 * @brief [Utility] Spiral movmeent
 * 
 * Rotates the particle's direction vector to create a spiral movement pattern.
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
 * @brief [Utility] Random movement
 * 
 * Randomly changes the particle's direction over time.
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
 * @brief [Utility] Sine wave movement
 * 
 * Moves the particle in a sine wave pattern.
 * 
 * @param particle The particle to update
 */
void Particle_SineMovement(Particle* particle) {
    particle->position.x += particle->direction.x * particle->speed * Time->deltaTimeSeconds;
    particle->position.y += particle->direction.y * particle->speed * Time->deltaTimeSeconds;
    particle->position.x += sin(particle->timeAlive * RandInt(1, 5)) * Time->deltaTimeSeconds * 10;
    particle->position.y += cos(particle->timeAlive * RandInt(1, 5)) * Time->deltaTimeSeconds * 10;
}