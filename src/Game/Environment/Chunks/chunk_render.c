#include <chunks.h>

void Chunk_Render(EnvironmentChunk chunk, Vec2 chunkPosition) {
    for (int x = 0; x < CHUNK_SIZE_TILE; x++) {
        for (int y = 0; y < CHUNK_SIZE_TILE; y++) {
            Tile_Render(chunk.tiles[x][y], (Vec2) {chunkPosition.x + x, chunkPosition.y + y});
        }
    }
}