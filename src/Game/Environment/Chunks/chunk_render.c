/**
 * @file chunk_render.c
 * @brief Renders environment chunks
 *
 * Handles the drawing of chunk tiles, walls, and special
 * elements with frustum culling for performance.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <chunks.h>

void Chunk_Render(const EnvironmentChunk* chunk) {
    // 2. Skip empty chunks entirely
    if (chunk->empty) return;
    
    // 3. Pre-compute world position to avoid redundant calculations
    int chunkWorldX = chunk->position.x * CHUNK_SIZE_TILE;
    int chunkWorldY = chunk->position.y * CHUNK_SIZE_TILE;
    
    // 4. Get camera view for tile-level culling
    SDL_Rect viewRect = Camera_GetWorldViewRect();
    
    // 5. Check if chunk is completely outside view (early exit)
    SDL_Rect chunkRect = {
        chunkWorldX * TILE_SIZE_PIXELS,
        chunkWorldY * TILE_SIZE_PIXELS,
        CHUNK_SIZE_PIXEL,
        CHUNK_SIZE_PIXEL
    };
    
    if (!SDL_HasIntersection(&viewRect, &chunkRect)) return;
    
    // 6. Calculate which tiles are actually visible
    int startX = MAX(0, (viewRect.x / TILE_SIZE_PIXELS) - chunkWorldX);
    int startY = MAX(0, (viewRect.y / TILE_SIZE_PIXELS) - chunkWorldY);
    int endX = MIN(CHUNK_SIZE_TILE - 1, ((viewRect.x + viewRect.w) / TILE_SIZE_PIXELS) - chunkWorldX + 1);
    int endY = MIN(CHUNK_SIZE_TILE - 1, ((viewRect.y + viewRect.h) / TILE_SIZE_PIXELS) - chunkWorldY + 1);
    
    // 7. Only render tiles in visible range
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            Tile_Render(
                chunk->tiles[x][y], 
                (Vec2) { chunkWorldX + x, chunkWorldY + y }
            );
        }
    }
}