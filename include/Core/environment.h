#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SDL.h>

typedef struct {
    SDL_Rect wallSize;
    SDL_Rect hitbox;
    SDL_Texture* texture;
} Wall;

typedef struct {
    Wall* walls;
    int wallCount;
} Environment;

extern Environment environment;
void Environment_AddWall(Wall wall);
void Environment_Render();
void Environment_Destroy();

void Environment_Start();
void Environment_Update();
void Position_Update();
void HitBox_Update();
#endif //ENVIRONMENT_H