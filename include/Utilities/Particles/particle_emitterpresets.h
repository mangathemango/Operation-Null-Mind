/*
    @file particle_emitterpresets.h
*   This file contains the particle emitter presets.
?   These presets are used to create particle emitters with specific properties.
?   The emitters can then be modified as needed.
?
?   To create a preset, add another extern ParticleEmitter in this file.
?   Then, create the emitter in particle_emitterpresets.c.
?   You can copy paste the properties inside ParticleEmitter_Default and modify them as needed.
?
?   Example for gun sparks particles:
?
?       extern ParticleEmitter ParticleEmitter_GunSparks;       // in particle_emitterpresets.h
?       ParticleEmitter ParticleEmitter_GunSparks = { ... };    // in particle_emitterpresets.c
?   
?   Written by Mango on 06/03/2025
*/

#pragma once

#include <particle_movement.h>

extern ParticleEmitter ParticleEmitter_Default;

extern ParticleEmitter ParticleEmitter_Dash;

extern ParticleEmitter ParticleEmitter_MuzzleFlash;
extern ParticleEmitter ParticleEmitter_PistolSMGCasing;
extern ParticleEmitter ParticleEmitter_ShotgunCasing;
extern ParticleEmitter ParticleEmitter_ARBRCasing;

extern ParticleEmitter bullet_Default;

extern ParticleEmitter* test_emitter; //! This is just for debugging purposes.

ParticleEmitter* ParticleEmitter_CreateFromPreset(ParticleEmitter preset);