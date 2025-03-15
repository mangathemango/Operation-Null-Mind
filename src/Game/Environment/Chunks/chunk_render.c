#include <chunks.h>

void Chunk_Render(EnvironmentChunk chunk) {
    for (int x = 0; x < CHUNK_SIZE_TILE; x++) {
        for (int y = 0; y < CHUNK_SIZE_TILE; y++) {
            Tile_Render(
                chunk.tiles[x][y], 
                (Vec2) {
                    chunk.position.x * CHUNK_SIZE_TILE + x, 
                    chunk.position.y * CHUNK_SIZE_TILE + y
                }
            );
        }
    }
}