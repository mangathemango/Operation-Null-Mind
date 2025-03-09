#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SDL.h>
#include <stdlib.h>
#include <colliders.h>

typedef struct {
    SDL_Rect wallSize; //For rendering
    Collider collider;
    SDL_Texture* texture;
} Wall;

typedef struct {
    Wall* walls;
    int wallCount;
    const char *background;
} Environment;

extern Environment environment;
void Environment_AddWall(Wall wall);
void Environment_Destroy();
int Environment_Start();
void Environment_Update();
void Environment_Render();
#endif //ENVIRONMENT_H