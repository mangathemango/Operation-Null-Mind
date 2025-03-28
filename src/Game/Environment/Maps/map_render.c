/**
 * @file map_render.c
 * @brief Handles rendering of the game map
 *
 * Manages the drawing of map chunks, with optimizations for only
 * rendering visible chunks and elements.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <maps.h>
#include <app.h>



void Map_Render() {
    // 1. Calculate visible area in world coordinates
    SDL_Rect viewRect = Camera_GetWorldViewRect();
    
    // 2. Determine which chunks are within view
    int startX = MAX(0, viewRect.x / CHUNK_SIZE_PIXEL);
    int startY = MAX(0, viewRect.y / CHUNK_SIZE_PIXEL);
    int endX = MIN(MAP_SIZE_CHUNK - 1, (viewRect.x + viewRect.w) / CHUNK_SIZE_PIXEL + 1);
    int endY = MIN(MAP_SIZE_CHUNK - 1, (viewRect.y + viewRect.h) / CHUNK_SIZE_PIXEL + 1);
    
    // 3. Only render chunks that are visible
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            // Skip empty chunks
            if (testMap.chunks[x][y].empty) continue;
            
            Chunk_Render(&testMap.chunks[x][y]);
        }
    }
    
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 20, 150);
    SDL_RenderFillRect(app.resources.renderer, &(SDL_Rect) { 
        0, 0, app.config.screen_width, app.config.screen_height
    });
}