#include <maps.h>
#include <random.h>

bool Chunk_IsValid(Vec2 chunkIndex) {
    return chunkIndex.x >= 0 && chunkIndex.x < MAP_SIZE_CHUNK && chunkIndex.y >= 0 && chunkIndex.y < MAP_SIZE_CHUNK;
}

EnvironmentChunk* Chunk_GetCurrentChunk(Vec2 position) {
    Vec2 chunkIndex = Vec2_Divide(position, (float) CHUNK_SIZE_PIXEL);
    if (!Chunk_IsValid(chunkIndex)) {
        return NULL;
    }
    return &testMap.chunks[(int) chunkIndex.x][(int) chunkIndex.y];
}

Vec2 Chunk_GetRandomTileInRoom(EnvironmentChunk* chunk) {
    float roomStartX = ROOM_STARTX(chunk->roomSize) + 1;
    float roomStartY = ROOM_STARTY(chunk->roomSize) + 1;
    float roomEndX = ROOM_ENDX(chunk->roomSize) - 1;
    float roomEndY = ROOM_ENDY(chunk->roomSize) - 1;

    Vec2 tileIndex = (Vec2) {
        RandInt(roomStartX, roomEndX),
        RandInt(roomStartY, roomEndY)
    };

    return Tile_TileIndexToPixel(tileIndex, chunk->position);
}