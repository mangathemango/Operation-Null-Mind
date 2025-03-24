/**
 * @file chunk_utils.c
 * @brief Utility functions for environment chunks
 *
 * Provides helper functions for chunk manipulation, validation,
 * and coordinate conversions between world space and chunks.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <maps.h>
#include <random.h>

/**
 * [Utility] Checks if a chunk index is valid within the map bounds
 * 
 * @param chunkIndex Index of the chunk to check
 * @return bool True if the chunk is valid, false otherwise
 */
bool Chunk_IsValid(Vec2 chunkIndex) {
    return chunkIndex.x >= 0 && chunkIndex.x < MAP_SIZE_CHUNK && chunkIndex.y >= 0 && chunkIndex.y < MAP_SIZE_CHUNK;
}

/**
 * [Utility] Gets the chunk at a specific world position
 * 
 * @param position World position to check
 * @return EnvironmentChunk* Pointer to the chunk at that position
 */
EnvironmentChunk* Chunk_GetCurrentChunk(Vec2 position) {
    Vec2 chunkIndex = Vec2_Divide(position, (float) CHUNK_SIZE_PIXEL);
    if (!Chunk_IsValid(chunkIndex)) {
        return NULL;
    }
    return &testMap.chunks[(int) chunkIndex.x][(int) chunkIndex.y];
}

/**
 * [Utility] Gets a random tile position within a room's boundaries
 *
 * @param chunk Pointer to the chunk containing the room
 * @return Vec2 Random tile position in world coordinates
 */
Vec2 Chunk_GetRandomTileInRoom(EnvironmentChunk* chunk) {
    float roomStartX = ROOM_STARTX(chunk->roomSize) + 1;
    float roomStartY = ROOM_STARTY(chunk->roomSize) + 1;
    float roomEndX = ROOM_ENDX(chunk->roomSize) - 1;
    float roomEndY = ROOM_ENDY(chunk->roomSize) - 2;

    Vec2 tileIndex = (Vec2) {
        RandInt(roomStartX, roomEndX),
        RandInt(roomStartY, roomEndY)
    };

    return Tile_TileIndexToPixel(tileIndex, chunk->position);
}

/**
 * [Utility] Gets a random position at the center of a tile within a room
 *
 * @param chunk Pointer to the chunk containing the room
 * @return Vec2 Random centered tile position in world coordinates
 */
Vec2 Chunk_GetRandomTileCenterInRoom(EnvironmentChunk* chunk) {
    return Vec2_Add(
        Chunk_GetRandomTileInRoom(chunk),
        (Vec2) {TILE_SIZE_PIXELS / 2, TILE_SIZE_PIXELS / 2}
    );
}