/*
    @file particle_emitterpresets.h
*   This file contains the particle emitter presets.
?   These presets are used to create particle emitters with specific properties.
?   The emitters can then be modified as needed.
?
?   To create a preset, add another exterrn ParticleEmitter in this file.
?   Then, create the emitter in particle_emitterpresets.c.
?   You can copy paste the properties inside ParticleEmitter_Default and modify them as needed.
?   Finally, create the emitter in the game loop.
?   Example:
?   Step 1: Add the preset in this file and create it in particle_emitterpresets.c
?       extern ParticleEmitter ParticleEmitter_Default; // particle_emitterpresets.h
?       ParticleEmitter ParticleEmitter_Default = { ... }; // particle_emitterpresets.c
?
?   Step 2: Create the emitter in the game loop
?   // Called inside App_Start()
?       ParticleEmitter *emitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Default);
?       emitter->selfReference = &emitter;
?   // Called inside App_PostUpdate()
?       // You can modify the emitter's properties as needed.
?       emitter->position = Input->mouse.position; 
?       ParticleEmitter_Update(emitter);            
?       ParticleEmitter_Render(emitter);
*/

#pragma once

#include <particle_movement.h>

extern ParticleEmitter ParticleEmitter_Default;
extern ParticleEmitter* test_emitter; //! This is just for debugging purposes.

ParticleEmitter* ParticleEmitter_CreateFromPreset(ParticleEmitter preset);