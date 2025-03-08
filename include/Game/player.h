/*
    @file player.h
*   This file contains the player's data, actions, and functions.
    TODO: Add player stats and abilities struct as well.
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <vec2.h>
#include <animation.h>
#include <stdbool.h>
#include <gun.h>
#include <particle_emitterpresets.h>

typedef struct {
    Vec2 position;
    Vec2 direction; //This is added to know the players last direction
    bool dashing; //This is added to know if the player is dashing
    bool movementLocked; //to know if the movement is locked
    bool moving;    
    GunData* currentGun;
} PlayerState;

typedef struct {
    ParticleEmitter* dashParticleEmitter;
    Animation* animation;
    Timer* dashDurationTimer;
    Timer* dashCooldownTimer;
} PlayerConfig;

typedef struct {
    float walkSpeed;
    float dashSpeed;
    float dashDuration;
    float dashCooldown;
} PlayerStat;

typedef struct {
    PlayerState state;
    PlayerStat stats;
    PlayerConfig config;
    AnimationData animData;
} PlayerData;

extern PlayerData player;


void Player_Input_Handler();
int Player_Render();

int Player_Start();
int Player_PostUpdate();
int Player_Preupdate();

// Movement
int Player_Move(Vec2 direction);
void Player_WrapAroundScreen(); //! This is temporary and will be removed later.

// Skills
int Player_Dash();
int Player_HandleDash();

// Combat
void Player_Shoot();

// Animations
int Player_AnimationInit();
int Player_AnimationUpdate();

#endif