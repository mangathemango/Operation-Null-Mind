#include <maps.h>
#include <app.h>

void Map_Render() {
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            Chunk_Render(testMap.chunks[x][y]);
        }
    }
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(app.resources.renderer, &(SDL_Rect) { 
        0, 0, app.config.screen_width, app.config.screen_height
    });
}