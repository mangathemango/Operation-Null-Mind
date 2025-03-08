/*
    @file particle_movement.h
*   This file contains the custom particle movement functions.
?   These functions can be used to create custom particle movement behaviors.
!   Custom movement will override default movement behaviors, like speed, gravity, drag, etc.
?   To use a custom movement function, set the custom_Movement field in the emitter to the desired function.
?   Example:
?       emitter->custom_Movement = Particle_LinearMovement;
?   This will make the particles move in a linear direction.

?   Written by Mango on 04/03/2025
*/

#pragma once

#include <particles.h>

void Particle_LinearMovement(Particle* particle);
void Particle_AcceleratedMovement(Particle* particle);
void Particle_DeceleratedMovement(Particle* particle);
void Particle_SpiralMovement(Particle* particle);
void Particle_RandomMovement(Particle* particle);
void Particle_SineMovement(Particle* particle);