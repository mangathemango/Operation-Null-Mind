#include <maps.h>
#include <random.h>

bool Chunk_IsValid(Vec2 chunkIndex) {
    return chunkIndex.x >= 0 && chunkIndex.x < MAP_SIZE_CHUNK && chunkIndex.y >= 0 && chunkIndex.y < MAP_SIZE_CHUNK;
}

Vec2 Chunk_GetRandomTileInRoom(EnvironmentChunk* chunk) {
    float roomStartX = ROOM_STARTX(chunk->roomSize);
    float roomStartY = ROOM_STARTY(chunk->roomSize);
    float roomEndX = ROOM_ENDX(chunk->roomSize);
    float roomEndY = ROOM_ENDY(chunk->roomSize);

    Vec2 tileIndex = (Vec2) {
        RandInt(roomStartX, roomEndX),
        RandInt(roomStartY, roomEndY)
    };

    return Tile_TileIndexToPixel(tileIndex, chunk->position);
}