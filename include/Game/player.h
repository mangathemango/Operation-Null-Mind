/**
 * @file player.h
 * @brief Manages player character state, movement, animations, and interactions.
 * @todo Add player stats and abilities struct as well.
 * 
 * @author Mango
 * @date 2025-02-28
 */

#pragma once
#include <vec2.h>
#include <animation.h>
#include <stdbool.h>
#include <gun.h>
#include <particle_emitterpresets.h>
#include <colliders.h>
#include <game.h>
#include <sound.h>

typedef enum PlayerPassive {
    ARMORED_UP,
    GHOST_LOAD,
    HEMO_CYCLE,
    KINETIC_ARMOR,
    LAST_STAND,
    OVER_PRESSURED,
    SCAVENGER,
    TOTAL_SKILLS,
} PlayerPassive;

typedef struct SkillState {
    bool overPressured;
    bool lastStand;
    bool kineticArmor;
    bool ghostLoad;
    bool oneMore;
    bool armoredUp;
    bool scavenger;
    bool hemoCycle;
    int crashOutMultiplier;
    bool crashOut;
    bool parryActive;         ///< Whether Parry ability is active
    bool parryHit;
} SkillState;

typedef struct SkillResources {
    float overPressuredBulletConsumptionMultipler; ///< Amount of ammo consumed when overpressured
    float overPressuredFireRate; ///< Fire rate when overpressured
    float overPressuredProjectileSpeed; ///< Speed of overpressured bullets
    int scavengerAmmoBonus; ///< Amount of ammo gained from scavenger skill
    int scavengerAmmoCapacity; ///< Amount of capacity reduced percentage from scavenger skill
    int hemocycleMultipler; ///< Amount of health gained from hemocycle skill
    int armoredUpIncomingDamageReduction; /// Amount of damage reduction from armored up skill
    int armoredUpDamageOutputDamageReduction; ///< Amount of damage reduction from armored up skill
    int ammoShoot; ///< Amount of ammo shot from the gun
    float ghostLoadRandomizer; ///< Randomizer for ghost load jamming
    Timer* crashOutCooldown; ///< Timer for crashout cooldown
    Timer* crashOutDuration; ///< Timer for crashout duration
    Timer* parryTimer;             ///< Timer for Parry ability cooldown
    Timer* parryDurationTimer;     ///< Timer for Parry ability duration
    ParticleEmitter* parryParticleEmitter;  ///< Visual effect for Parry
    SDL_Texture* parryTexture; ///< Texture for Parry effect
    float parryRadius; ///< Radius of the parry effect
    Vec2 parryDirection;
} SkillResources;

typedef struct SkillStat {
    float overPressuredOriginalMultipler; ///< Amount of ammo consumed when overpressured
    float overPressuredOriginalFireRate; ///< Fire rate when overpressured
    float overPressuredOriginalProjectileSpeed; ///< Speed of overpressured bullets
    int scavengerAmmoBonus; ///< Amount of ammo gained from scavenger skill
    int scavengerAmmoCapacity; ///< Amount of capacity reduced percentage from scavenger skill
    int hemocycleMultipler; ///< Amount of health gained from hemocycle skill
    int hemocycleHealthGained; ///< Amount of health gained from hemocycle skill
    int armoredUpIncomingDamageReduction; /// Amount of damage reduction from armored up skill
    int armoredUpDamageOutputDamageReduction; ///< Amount of damage reduction from armored up skill
    float ghostLoadRandomizer; ///< Randomizer for ghost load jamming
    int crashOutCurrentMultipler;
    int crashOutCooldown;
    int crashOutDuration;
    float parryCooldown;      ///< Cooldown time for parry ability
    float parryDuration;      ///< How long parry lasts when activated
    float maxParryAngle; ///< Maximum angle for parry
} SkillStat;

/**
 * @brief Contains the player's current state information
 */
typedef struct PlayerState {
    Vec2 position;      ///< Current player position
    Vec2 direction;     ///< Last direction the player was facing
    float currentSpeed; ///< Current movement speed
    int currentHealth;
    int currentAmmo;

    bool dashing;       ///< Whether the player is currently dashing
    bool directionLocked; ///< Whether movement direction is locked
    bool moving;        ///< Whether the player is moving
    bool movementLocked; ///< Whether movement is locked
    float crashOutMultiplier; ///< Multipler that will be used fro crashout
    GunData currentGun; ///< Currently equipped weapon
    GunData previousGun; ///< Previously equipped weapon
    Gun gunSlots[2]; ///< Guns held by the player
    SkillState skillState; ///< Player skills and abilities

    Collider collider;   ///< Player collision data
    bool insideRoom;     ///< Whether player is in a room
    bool insideHallway;  ///< Whether player is in a hallway
    bool insideEnd;      ///< Whether player is at an endpoint
    SDL_RendererFlip flip; ///< Flip state for rendering
} PlayerState;

/**
 * @brief Contains the player's resources and timers
 */
typedef struct PlayerResources {
    ParticleEmitter* dashParticleEmitter; ///< Particle effect for dashing
    ParticleEmitter* crashOut;  ///< Particle effect for crashout
    Animation* animation;                 ///< Player animation data
    Timer* dashDurationTimer;             ///< Timer for dash duration
    Timer* dashCooldownTimer;             ///< Timer for dash cooldown
    Timer* shootCooldownTimer;            ///< Timer for shoot cooldown
    Timer* INVINCIBLE_Timer;               ///< [Title card] timer
    SkillResources skillResources;        ///< Resources for player skills
} PlayerResources;

/**
 * @brief Contains the player's stats and attributes
 */
typedef struct PlayerStat {
    int maxHealth;
    int maxAmmo;
    float INVINCIBLE_Time; ///< Time the player is [Title card] before taking damage again
    float walkSpeed;    ///< Normal walking speed
    float dashSpeed;    ///< Speed during dash
    float dashDuration; ///< How long dash lasts
    float dashCooldown; ///< Time between dashes
    int enemiesKilled; ///< Number of enemies killed
    SkillStat skillStat;   ///< Player skills and abilities  
} PlayerStat;

/**
 * @brief Main player data structure
 */
typedef struct PlayerData {
    PlayerState state;      ///< Current player state
    PlayerStat stats;       ///< Player statistics
    PlayerResources resources; ///< Player resources
    AnimationData animData; ///< Animation data
} PlayerData;

/** @brief Global player instance */
extern PlayerData player;

/**
 * @brief Handles player input
 */
void Player_Input_Handler();

/**
 * @brief Renders the player
 * @return Status code
 */
int Player_Render();

/**
 * @brief Initializes the player
 * @return Status code
 */
int Player_Start();

/**
 * @brief Post-update operations for player
 * @return Status code
 */
int Player_PostUpdate();

/**
 * @brief Pre-update operations for player
 * @return Status code
 */
int Player_Preupdate();

/**
 * @brief Detects collisions for player
 * @return True if collision detected
 */
bool Player_DetectCollision();

/**
 * @brief Moves the player
 * @return Status code
 */
int Player_Move();

/**
 * @brief Makes player look in specified direction
 * @param direction Direction vector
 * @return Status code
 */
int Player_Look(Vec2 direction);

/**
 * @brief Updates player hitbox
 */
void Player_UpdateHitbox();

/**
 * @brief Initiates player dash
 * @return Status code
 */
int Player_Dash();

/**
 * @brief Handles ongoing dash state
 * @return Status code
 */
int Player_HandleDash();

/**
 * @brief Activates crashout ability
 * @return Status code
 */
int Player_CrashOut();

/**
 * @brief Handles ongoing crashout state
 * @return Status code
 */
int Player_HandleCrashOut();


/**
 * @brief Makes player shoot current weapon
 */
void Player_Shoot();

/**
 * @brief Changes player's current weapon
 */
void Player_SwitchGun();

/**
 * @brief Initializes player animations
 * @return Status code
 */
int Player_AnimationInit();

/**
 * @brief Updates player animations
 * @return Status code
 */
int Player_AnimationUpdate();


//Player skills
void Skill_Update();

void scavenger();

void Player_TakeDamage(int damage);
void Player_RenderDamageEffect();

bool kineticArmor();

bool ghostLoad();

int Parry();

int Handle_ParryRender();

int Handle_Parry();


void Player_PickUpGun(void* data, int interactableIndex);
void Player_OpenCrate(void* data, int interactableIndex);
void Player_ReadLog(void* data, int interactableIndex);