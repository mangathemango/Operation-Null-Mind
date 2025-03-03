#ifndef PLAYER_H
#define PLAYER_H
#include <vec2.h>
#include <SDL.h>
typedef struct {
    Vec2 position;
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

// Actions
int Player_Move(Vec2 direction);
void Update_Position();
void Handle_Collision();

void Init_player(Player* player);
void Handle_input(Player* player, const Uint8* keystate);
void Update_player(Player* player);
void Render_player(Player* player, SDL_Renderer* renderer);

#endif