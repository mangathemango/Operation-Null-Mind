/**
 * @file gun.h
 * @brief Implements weapon systems including animations, shooting mechanics, and particle effects.
 * @details This includes the gun's animations, rendering, and updating.
 * @author Mango
 * @date 2025-03-06
 */

#pragma once

#include <animation.h>
#include <vec2.h>
#include <particle_emitterpresets.h>

/**
 * @brief Gun name definitions
 */
#define GUN_SHOTGUN_NAME "Beretta 1301 Tactical"
#define GUN_BATTLE_RIFLE_NAME "FN SCAR-H"
#define GUN_SMG_NAME "HK UMP45"
#define GUN_ASSAULT_RIFLE_NAME "M4A1 URG-I"
#define GUN_PISTOL_NAME "Glock 17"
#define GUN_REVOLVER_NAME "Chiappa Rhino 200DS"
#define GUN_ARMOR_PISTOL_NAME "FN Five-seveN Mk3 MRD"
#define GUN_RAPID_SMG_NAME "KRISS Vector"
#define GUN_PDW_NAME "FN P90"
#define GUN_BURST_RIFLE_NAME "M16A4"
#define GUN_BULLPUP_RIFLE_NAME "Kel-Tec RFB"
#define GUN_AUTO_SHOTGUN_NAME "Atchisson AA-12"

typedef enum {
    GUN_PISTOL,
    GUN_SMG,
    GUN_SHOTGUN,
    GUN_ASSAULT_RIFLE,
    GUN_BATTLE_RIFLE,
    GUN_REVOLVER,
    GUN_ARMOR_PISTOL,
    GUN_RAPID_SMG,
    GUN_PDW,
    GUN_BURST_RIFLE,
    GUN_BULLPUP_RIFLE,
    GUN_AUTO_SHOTGUN,
    GUN_COUNT
} Gun;

/**
 * @brief Resources used by a gun
 */
typedef struct {
    ParticleEmitter* casingParticleEmitter;    /**< Emitter for ejected shell casings */
    ParticleEmitter* muzzleFlashEmitter;       /**< Emitter for muzzle flash effects */
    ParticleEmitter* bulletPreset;             /**< Preset for bullet particles */
    ParticleEmitter* bulletFragmentEmitter;    /**< Emitter for bullet fragment particles */
    Animation* animation;                       /**< Gun animation */
} GunResources;

/**
 * @brief Gun state structure
 * @details Contains the runtime state information for a gun
 */
typedef struct {
    Vec2 position;                  /**< Current position of the gun */
    float angle;                    /**< Current rotation angle of the gun */
    SDL_RendererFlip flip;          /**< Flip state for rendering */
    SDL_Point rotationCenter;       /**< Point around which the gun rotates */
} GunState;

/**
 * @brief Gun configuration structure
 * @details Contains positioning data and particle effect configurations for a gun
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
 * @details Defines the different firing modes available for guns
 */
typedef enum {
    FIREMODE_SEMI,                  /**< Semi-automatic (one shot per trigger pull) */
    FIREMODE_AUTO,
    FIREMODE_BURST                   /**< Fully automatic (continuous fire while trigger held) */
} GunFireMode;

/**
 * @brief Bullet velocity constants
 */
#define BULLET_VELOCITY_SLOW 400
#define BULLET_VELOCITY_MID 600
#define BULLET_VELOCITY_FAST 800
#define BULLET_VELOCITY_REAL_FAST 1000

/**
 * @brief Gun statistics structure
 * @details Contains the configuration values that define a gun's capabilities
 */
typedef struct {
    float fireRate;                 /**< Shots per minute */
    float spread_angle;             /**< Bullet spread in degrees */
    int damage;                     /**< Damage per bullet */     
    float bulletLifetime;           /**< How long bullets exist before despawning */
    int bulletsPerShot;             /**< Number of bullets fired per shot (>1 only for shotguns) */
    GunFireMode fireMode;           /**< Firing mode (auto or semi) */
    int bulletVelocity;             /**< Velocity of the bullet */
    int ammoConsumption;            /**< Ammo consumed per shot */
} GunStats;

/**
 * @brief Gun data structure
 * @details Complete definition of a gun, including name, resources, state, config, stats,
 * and animation data
 */
typedef struct {
    Gun type;                    /**< Type of the gun */
    char* name;                     /**< Name of the gun */
    GunResources resources;         /**< Pointers to runtime resources */
    GunState state;                 /**< Current state information */
    GunConfig config;               /**< Configuration data */
    GunStats stats;                 /**< Stats and capabilities */
    AnimationData animData;         /**< Animation configuration */
} GunData;

/**
 * @brief Pistol weapon data
 * @details Global definition for the pistol gun type
 */
extern GunData Gun_Pistol;

/**
 * @brief SMG weapon data
 * @details Global definition for the submachine gun type
 */
extern GunData Gun_SMG;

/**
 * @brief Shotgun weapon data
 * @details Global definition for the shotgun gun type
 */
extern GunData Gun_Shotgun;

/**
 * @brief Assault rifle weapon data
 * @details Global definition for the assault rifle gun type
 */
extern GunData Gun_AssaultRifle;

/**
 * @brief Battle rifle weapon data
 * @details Global definition for the battle rifle gun type
 */
extern GunData Gun_BattleRifle;

/**
 * @brief Array of all available guns
 */
extern GunData GunList[GUN_COUNT];

/**
 * @brief Updates gun position, orientation and associated particle emitters
 * 
 * @param gun Pointer to the gun data structure
 * @param ownerPosition Position of the entity that owns the gun
 * @param targetPosition Position to aim at (usually player position)
 * @param gunOffset Additional offset from owner position
 */
void Gun_UpdatePosition(GunData* gun, Vec2 ownerPosition, Vec2 targetPosition, Vec2 gunOffset);

/**
 * @brief Updates gun animations
 */
void Gun_AnimationUpdate();

/**
 * @brief Renders all guns
 */
void Gun_Render();

/**
 * @brief Initializes gun systems
 */
void Gun_Start();

/**
 * @brief Updates gun state
 */
void Gun_Update();