#ifndef PLAYER_H
#define PLAYER_H
#include <vec2.h>
#include <stdbool.h>
#include <SDL.h>
#include <environment.h>
typedef struct {
    Vec2 position;
    bool moving;
    SDL_Rect hitbox;
} PlayerState;

typedef struct {
    float speed;
    char* sprite;
    Vec2 spriteSize;
} PlayerConfig;

typedef struct {
    PlayerState state;
    PlayerConfig config;
} PlayerData;

typedef struct {
    SDL_FRect position;
    SDL_Rect hitbox;
    float move_speed;
} Player;

extern PlayerData player;


void Player_Input_Handler();
int Player_Render();

int Player_Start();
int Player_PostUpdate();
void Player_Post_Position();
// void Update_Player(PlayerState *player, Wall *wall);

// Actions
int Player_Move(Vec2 direction);
//Collision
void Check_Collision(SDL_Rect a, SDL_Rect b,int *collisionFlag);

#endif