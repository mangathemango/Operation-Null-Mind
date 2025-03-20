/*
    @file player.h
*   This file contains the player's data, actions, and functions.
    TODO: Add player stats and abilities struct as well.

?   Written by Mango on 28/02/2025
*/

#ifndef PLAYER_H
#define PLAYER_H
#include <vec2.h>
#include <animation.h>
#include <stdbool.h>
#include <gun.h>
#include <particle_emitterpresets.h>
#include <colliders.h>

typedef struct {
    Vec2 position;
    Vec2 direction; //This is added to know the players last direction
    float currentSpeed;
    bool dashing; //This is added to know if the player is dashing
    bool directionLocked; //to know if the movement is locked
    bool moving;    
    GunData* currentGun;
    Collider collider;
    bool insideRoom;
    bool insideHallway;
} PlayerState;

typedef struct {
    ParticleEmitter* dashParticleEmitter;
    Animation* animation;
    Timer* dashDurationTimer;
    Timer* dashCooldownTimer;
    Timer* shootCooldownTimer;
} PlayerResources;

typedef struct {
    float walkSpeed;
    float dashSpeed;
    float dashDuration;
    float dashCooldown;
} PlayerStat;

typedef struct {
    PlayerState state;
    PlayerStat stats;
    PlayerResources resources;
    AnimationData animData;
} PlayerData;

extern PlayerData player;


void Player_Input_Handler();
int Player_Render();

int Player_Start();
int Player_PostUpdate();
int Player_Preupdate();
bool Player_DetectCollision();
// void Update_Player(PlayerState *player, Wall *wall);


// Movement
int Player_Move();
int Player_Look(Vec2 direction);
void Player_UpdateHitbox();

// Skills
int Player_Dash();
int Player_HandleDash();

// Combat
void Player_Shoot();
void Player_SwitchGun(GunData* gun);

// Animations
int Player_AnimationInit();
int Player_AnimationUpdate();

#endif