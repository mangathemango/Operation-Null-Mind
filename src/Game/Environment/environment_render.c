#include <environment.h>
#include <app.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

void Environment_Render() {
    if (environment.walls == NULL) return;
    for (int i = 0; i < environment.wallCount; i++) {
        Wall wall = environment.walls[i];
        if (wall.texture) {
            SDL_RenderCopy(app.setup.renderer, wall.texture, NULL, &wall.wallSize);
        } else {
            SDL_SetRenderDrawColor(app.setup.renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(app.setup.renderer, &wall.wallSize);
        }
    }
}

