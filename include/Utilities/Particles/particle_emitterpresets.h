/**
 * @file particle_emitterpresets.h
 * @brief Defines preset particle emitter configurations for common visual effects.
 *
 * These presets are used to create particle emitters with specific properties.
 * The emitters can then be modified as needed.
 *
 * To create a preset, add another extern ParticleEmitter in this file.
 * Then, create the emitter in particle_emitterpresets.c.
 * You can copy paste the properties inside ParticleEmitter_Default and modify them as needed.
 *
 * Example for gun sparks particles:
 * ```
 * extern ParticleEmitter ParticleEmitter_GunSparks;       // in particle_emitterpresets.h
 * ParticleEmitter ParticleEmitter_GunSparks = { ... };    // in particle_emitterpresets.c
 * ```
 *
 * @author Mango
 * @date 2025-06-03
 */

#pragma once

#include <particle_movement.h>

/** @brief Default particle emitter preset */
extern ParticleEmitter ParticleEmitter_Default;

/** @brief Dash effect particle emitter preset */
extern ParticleEmitter ParticleEmitter_Dash;

/** @brief Muzzle flash effect particle emitter preset */
extern ParticleEmitter ParticleEmitter_MuzzleFlash;
/** @brief Pistol and SMG shell casing particle emitter preset */
extern ParticleEmitter ParticleEmitter_PistolSMGCasing;
/** @brief Shotgun shell casing particle emitter preset */
extern ParticleEmitter ParticleEmitter_ShotgunCasing;
/** @brief Assault rifle and battle rifle casing particle emitter preset */
extern ParticleEmitter ParticleEmitter_ARBRCasing;

/** @brief Default bullet impact particle preset */
extern ParticleEmitter ParticleEmitter_BulletDefault;
extern ParticleEmitter ParticleEmitter_BulletEnemy;
/** @brief Bullet fragment particles preset */
extern ParticleEmitter ParticleEmitter_BulletFragments;
extern ParticleEmitter ParticleEmitter_Explosion;
extern ParticleEmitter ParticleEmitter_Gernade;
extern ParticleEmitter ParticleEmitter_CrashOut;

extern ParticleEmitter* test_emitter; //!< This is just for debugging purposes.

/**
 * @brief Creates a new particle emitter from a preset
 * @param preset The preset to use as a template
 * @return Pointer to the newly created particle emitter
 */
ParticleEmitter* ParticleEmitter_CreateFromPreset(ParticleEmitter preset);