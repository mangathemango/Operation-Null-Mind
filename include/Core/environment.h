#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SDL.h>

typedef struct {
    SDL_Rect wallSize; //For rendering
    SDL_Rect hitbox; //For collision detection
    SDL_Texture* texture;
} Wall;

typedef struct {
    Wall* walls;
    int wallCount;
    const char *background;
} Environment;

extern Environment environment;
void Environment_AddWall(Wall wall);
void Environment_Render();
void Environment_Destroy();
int Environment_Start();
void Environment_Update();
int Environment_AnimationInit();
//For rendering hitboxes
void Render_WallHitboxes(SDL_Renderer* renderer);
#endif //ENVIRONMENT_H