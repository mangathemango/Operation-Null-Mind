/**
 * @file particle_movement.h
 * @brief Provides custom movement behaviors for particles.
 *
 * These functions can be used to create custom particle movement behaviors.
 * @warning Custom movement will override default movement behaviors, like speed, gravity, drag, etc.
 * 
 * @section movement_usage Usage
 * To use a custom movement function, set the custom_Movement field in the emitter to the desired function.
 * @subsection movement_example Example
 * ```c
 * emitter->custom_Movement = Particle_LinearMovement;
 * ```
 * This will make the particles move in a linear direction.
 *
 * @author Mango
 * @date 2025-03-04
 */

#pragma once

#include <particles.h>

/**
 * @brief Moves a particle in a linear direction.
 * @param particle The particle to move.
 */
void Particle_LinearMovement(Particle* particle);

/**
 * @brief Moves a particle with acceleration.
 * @param particle The particle to move.
 */
void Particle_AcceleratedMovement(Particle* particle);

/**
 * @brief Moves a particle with deceleration.
 * @param particle The particle to move.
 */
void Particle_DeceleratedMovement(Particle* particle);

/**
 * @brief Moves a particle in a spiral pattern.
 * @param particle The particle to move.
 */
void Particle_SpiralMovement(Particle* particle);

/**
 * @brief Moves a particle in a random direction.
 * @param particle The particle to move.
 */
void Particle_RandomMovement(Particle* particle);

/**
 * @brief Moves a particle in a sine wave pattern.
 * @param particle The particle to move.
 */
void Particle_SineMovement(Particle* particle);