/*
    @file gun.h
*   This file contains the gun data and its functions.
?   This includes the gun's animations, rendering, and updating.

?   Written by Mango on 06/03/2025
*/

#pragma once

#include <animation.h>
#include <vec2.h>
#include <particle_emitterpresets.h>

#define GUN_COUNT 5

// The gun names (I'm not a gun guy so this will be easier to work with)
#define GUN_SHOTGUN "Beretta 1301 Tactical"
#define GUN_BATTLE_RIFLE "FN SCAR-H"
#define GUN_SMG "KRISS Vector"
#define GUN_ASSAULT_RIFLE "M4A1 URG-I"
#define GUN_PISTOL "Glock 17"

typedef struct {
    ParticleEmitter* casingParticleEmitter;
    ParticleEmitter* muzzleFlashEmitter;
    ParticleEmitter* bulletPreset;
    ParticleEmitter* bulletFragmentEmitter;
    Animation* animation;
} GunResources;

/**
 * @brief Gun state structure
 * 
 * Contains the runtime state information for a gun
 */
typedef struct {
    Vec2 position;
    float angle;
    SDL_RendererFlip flip;
    SDL_Point rotationCenter;       /**< Point around which the gun rotates */
} GunState;

/**
 * @brief Gun configuration structure
 *
 * Contains positioning data and particle effect configurations for a gun
 */
typedef struct {
    Vec2 muzzlePosition;            /**< Position where bullets/muzzle flash appears */
    Vec2 ejectionPosition;          /**< Position where casings are ejected */
    Vec2 gripPosition;              /**< Position where the player holds the gun */
    ParticleEmitter muzzleFlashPreset; /**< Particle effect for muzzle flash */
    ParticleEmitter casingPreset;      /**< Particle effect for ejected casings */
} GunConfig;

/**
 * @brief Gun fire mode enumeration
 *
 * Defines the different firing modes available for guns
 */
typedef enum {
    FIREMODE_SEMI,                  /**< Semi-automatic (one shot per trigger pull) */
    FIREMODE_AUTO                   /**< Fully automatic (continuous fire while trigger held) */
} GunFireMode;

/**
 * @brief Gun statistics structure
 *
 * Contains the configuration values that define a gun's capabilities
 */
typedef struct {
    float fireRate;                 /**< Shots per minute */
    int ammoCapacity;               /**< Maximum ammunition count */
    float spread_angle;             /**< Bullet spread in degrees */
    int damage;                     /**< Damage per bullet */
    
    float bulletLifetime;           /**< How long bullets exist before despawning ()*/
    int bulletsPerShot;             /**< Number of bullets fired per shot (>1 only for shotguns) */
    GunFireMode fireMode;           /**< Firing mode (auto or semi) */
} GunStats;

/**
 * @brief Gun data structure
 *
 * Complete definition of a gun, including name, resources, state, config, stats,
 * and animation data
 */
typedef struct {
    char* name;                     /**< Name of the gun */
    GunResources resources;         /**< Pointers to runtime resources */
    GunState state;                 /**< Current state information */
    GunConfig config;               /**< Configuration data */
    GunStats stats;                 /**< Stats and capabilities */
    AnimationData animData;         /**< Animation configuration */
} GunData;

/**
 * @brief Pistol weapon data
 *
 * Global definition for the pistol gun type
 */
extern GunData Gun_Pistol;

/**
 * @brief SMG weapon data
 *
 * Global definition for the submachine gun type
 */
extern GunData Gun_SMG;

/**
 * @brief Shotgun weapon data
 *
 * Global definition for the shotgun gun type
 */
extern GunData Gun_Shotgun;

/**
 * @brief Assault rifle weapon data
 *
 * Global definition for the assault rifle gun type
 */
extern GunData Gun_AssaultRifle;

/**
 * @brief Battle rifle weapon data
 *
 * Global definition for the battle rifle gun type
 */
extern GunData Gun_BattleRifle;

extern GunData* GunList[GUN_COUNT];

void Gun_AnimationUpdate();
void Gun_Render();
void Gun_Start();
void Gun_Update();