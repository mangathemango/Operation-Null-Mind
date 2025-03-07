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
#include <environment.h>

typedef struct {
    Vec2 position;
    Vec2 direction; //This is added to know the players last direction
    bool dashing; //This is added to know if the player is dashing
    bool movementLocked; //to know if the movement is locked
    bool moving;
    SDL_Rect hitbox;
} PlayerState;

typedef struct {
    float speed;
    float dashSpeed;
    char* sprite;
    Vec2 spriteSize;
    Animation* animation;
} PlayerConfig;

typedef struct {
    PlayerState state;
    PlayerConfig config;
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

void Player_WrapAroundScreen(); //! This is temporary and will be removed later.

// Skills
int Player_Dash();
int Player_HandleDash();

// Animations
int Player_AnimationInit();
int Player_AnimationUpdate();

#endif