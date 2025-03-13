#include <maps.h>

void Map_Start() {
    Tile_Start();
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            testMap.chunks[x][y] = (EnvironmentChunk) {
                .position = (Vec2) {x, y},
                .roomSize = (Vec2) {10, 10},
                .floorPattern = ROOM_FLOOR_PATTERN_1,
                .hallways = HALLWAY_NONE,
                .empty = false,
                .colliderCount = 0
            };
        }
    }
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            testMap.chunks[x][y].hallways = Map_GetChunkHallways(testMap.chunks[x][y], testMap);
            testMap.chunks[x][y] = Chunk_Create(
                testMap.chunks[x][y].position, 
                testMap.chunks[x][y].roomSize, 
                testMap.chunks[x][y].floorPattern, 
                testMap.chunks[x][y].hallways
            );
        }
    }
}

RoomHallways Map_GetChunkHallways(EnvironmentChunk chunk, EnvironmentMap map) {
    RoomHallways hallways = HALLWAY_NONE;
    if (chunk.position.x > 0) {
        if (!map.chunks[(int) chunk.position.x - 1][(int) chunk.position.y].empty) {
            hallways |= HALLWAY_LEFT;
        }
    }
    if (chunk.position.x < MAP_SIZE_CHUNK - 2) {
        if (!map.chunks[(int) chunk.position.x + 1][(int) chunk.position.y].empty) {
            hallways |= HALLWAY_RIGHT;
        }
    }
    if (chunk.position.y > 0) {
        if (!map.chunks[(int) chunk.position.x][(int) chunk.position.y - 1].empty) {
            hallways |= HALLWAY_UP;
        }
    }
    if (chunk.position.y < MAP_SIZE_CHUNK - 2) {
        if (!map.chunks[(int) chunk.position.x][(int) chunk.position.y + 1].empty) {
            hallways |= HALLWAY_DOWN;
        }
    }
    return hallways;
}