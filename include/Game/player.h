/**
 * @file player.h
 * @brief This file contains the player's data, actions, and functions.
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

/**
 * @brief Contains the player's current state information
 */
typedef struct {
    Vec2 position;      ///< Current player position
    Vec2 direction;     ///< Last direction the player was facing
    float currentSpeed; ///< Current movement speed
    bool dashing;       ///< Whether the player is currently dashing
    bool directionLocked; ///< Whether movement direction is locked
    bool moving;        ///< Whether the player is moving
    GunData* currentGun; ///< Currently equipped weapon
    Collider collider;   ///< Player collision data
    bool insideRoom;     ///< Whether player is in a room
    bool insideHallway;  ///< Whether player is in a hallway
    bool insideEnd;      ///< Whether player is at an endpoint
} PlayerState;

/**
 * @brief Contains the player's resources and timers
 */
typedef struct {
    ParticleEmitter* dashParticleEmitter; ///< Particle effect for dashing
    Animation* animation;                 ///< Player animation data
    Timer* dashDurationTimer;             ///< Timer for dash duration
    Timer* dashCooldownTimer;             ///< Timer for dash cooldown
    Timer* shootCooldownTimer;            ///< Timer for shoot cooldown
} PlayerResources;

/**
 * @brief Contains the player's stats and attributes
 */
typedef struct {
    float walkSpeed;    ///< Normal walking speed
    float dashSpeed;    ///< Speed during dash
    float dashDuration; ///< How long dash lasts
    float dashCooldown; ///< Time between dashes
} PlayerStat;

/**
 * @brief Main player data structure
 */
typedef struct {
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
 * @brief Makes player shoot current weapon
 */
void Player_Shoot();

/**
 * @brief Changes player's current weapon
 * @param gun Pointer to gun data
 */
void Player_SwitchGun(GunData* gun);

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
#endif