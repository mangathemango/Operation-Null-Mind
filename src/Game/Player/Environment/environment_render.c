#include <environment.h>
#include <app.h>
#include <stdlib.h>

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

void Environment_Render() {
     if (environment.walls == NULL) return;
     for (int i = 0; i < environment.wallCount; i++) {
         Wall wall = environment.walls[i];
     if (wall.texture) SDL_RenderCopy(app.setup.renderer, wall.texture, NULL, &wall.wallSize);
         else {
         SDL_SetRenderDrawColor(app.setup.renderer, 255, 255, 255, 255);
         SDL_RenderFillRect(app.setup.renderer, &wall.wallSize);
     }
     }
}

void Environment_Destroy() {
    if (!environment.walls) return;
    free(environment.walls);
    environment.walls = NULL;
}