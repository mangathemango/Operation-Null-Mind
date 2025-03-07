#include <environment.h>

void Environment_Destroy() {
    if (!environment.walls) return;
    free(environment.walls);
    environment.walls = NULL;
}

void Environment_AddWall(Wall wall) {
    if (!environment.walls) {
        environment.walls = malloc(sizeof(Wall));
        if (!environment.walls) return;
    } else {
        environment.walls = realloc(environment.walls, sizeof(Wall) * (environment.wallCount + 1));
        if (!environment.walls) return;
    }
    memcpy(&environment.walls[environment.wallCount++], &wall, sizeof(Wall));
}