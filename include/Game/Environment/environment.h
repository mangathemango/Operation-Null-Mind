#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <SDL.h>
#include <stdlib.h>
#include <colliders.h>
#include <stdbool.h>

#define MAP_CHUNK_SIZE_TILE 40









typedef struct {

} EnvironmentData;

extern EnvironmentData environment;
void Environment_Destroy();
int Environment_Start();
void Environment_Update();
void Environment_Render();
#endif //ENVIRONMENT_H