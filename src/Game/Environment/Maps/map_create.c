#include <maps.h>
#include <random.h>
#include <enemy_types.h>

void Map_Generate() {
    // 1. Initialize all chunks as empty
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            testMap.chunks[x][y].empty = true;
            testMap.chunks[x][y].roomType = ROOM_TYPE_NORMAL;
        }
    }
    
    // 2. Place start room (always in top-left quadrant)
    int startX = 0;
    int startY = 0;
    Map_SetStartChunk(startX, startY);

    // 3. Place end room (always in bottom-right quadrant)
    int endX = RandInt(MAP_SIZE_CHUNK/2 + 1, MAP_SIZE_CHUNK-1);
    int endY = RandInt(MAP_SIZE_CHUNK/2 + 1, MAP_SIZE_CHUNK-1);
    Map_SetEndChunk(endX, endY);
    
    // 4. Create main path using A* or random walk
    Map_CreateMainPath();

    
    // 5. Initialize all non-empty chunks
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            if (!testMap.chunks[x][y].empty) {
                SDL_Log ("Generating chunk at (%d, %d)\n", x, y);
                // Set hallways based on adjacent non-empty chunks
                testMap.chunks[x][y].floorPattern = ROOM_FLOOR_PATTERN_1;
                testMap.chunks[x][y].position = (Vec2){x, y};
                testMap.chunks[x][y].hallways = Map_GetChunkHallways(testMap.chunks[x][y], testMap);

                // Generate room details
                if ((testMap.chunks[x][y].roomType == ROOM_TYPE_NORMAL)) {
                    testMap.chunks[x][y].roomSize = (Vec2){RandInt(10,15)*2, RandInt(10,15)*2};
                    SDL_Log("Room size at (%d, %d): %dx%d\n", x, y, testMap.chunks[x][y].roomSize.x, testMap.chunks[x][y].roomSize.y);
                }
                
                // Create the chunk with all its details
                testMap.chunks[x][y] = Chunk_GenerateTiles(
                    testMap.chunks[x][y].position,
                    testMap.chunks[x][y].roomType,
                    testMap.chunks[x][y].roomSize,
                    testMap.chunks[x][y].floorPattern,
                    testMap.chunks[x][y].hallways
                );

                Enemy_Spawn(ZFNData, (Vec2){x * CHUNK_SIZE_PIXEL + CHUNK_SIZE_PIXEL/2, y * CHUNK_SIZE_PIXEL + CHUNK_SIZE_PIXEL/2});
            }
        }
    }
}


void Map_SetStartChunk(int x, int y) {
    testMap.startChunk = &testMap.chunks[x][y];
    testMap.startChunk->empty = false;
    testMap.startChunk->roomSize = (Vec2){12, 12}; // Slightly larger start room
    testMap.startChunk->roomType = ROOM_TYPE_START;
    testMap.startChunk->position = (Vec2){x, y};
}

void Map_SetEndChunk(int x, int y) {
    testMap.endChunk = &testMap.chunks[x][y];
    testMap.endChunk->empty = false;
    testMap.endChunk->roomSize = (Vec2){12, 12}; // Slightly larger end room
    testMap.endChunk->roomType = ROOM_TYPE_END;
    testMap.endChunk->position = (Vec2){x, y};
}
void Map_CreateMainPath() {
    if (testMap.startChunk == NULL || testMap.endChunk == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot create main path without start and end chunks");
        return; // Cannot create main path without start and end chunks
    }
    int currentX = testMap.startChunk->position.x;
    int currentY = testMap.startChunk->position.y;
    int endX = testMap.endChunk->position.x;
    int endY = testMap.endChunk->position.y;

    // Reset path tracking
    testMap.mainPathLength = 0;
    testMap.mainPath[testMap.mainPathLength++] = (Vec2){currentX, currentY};
    SDL_Log("Generating main path via random walk");
    SDL_Log("Current position: (%d, %d) - Target position: (%d, %d)\n", currentX, currentY, endX, endY);
    
    while (currentX != endX || currentY != endY) {
        // Determine if we move horizontally or vertically
        bool moveHorizontal = RandBool();

        // Force movement direction if we're aligned on one axis
        if (currentY == endY) moveHorizontal = true;
        if (currentX == endX) moveHorizontal = false;

        // Make movement
        if (moveHorizontal) {
            currentX += (currentX < endX) ? 1 : -1;
        } else {
            currentY += (currentY < endY) ? 1 : -1;
        }
        SDL_Log("Moved to (%d, %d)\n", currentX, currentY);
        // Mark chunk as part of path
        testMap.chunks[currentX][currentY].empty = false;
        testMap.mainPath[testMap.mainPathLength++] = (Vec2){currentX, currentY};
    }
}

RoomHallways Map_GetChunkHallways(EnvironmentChunk chunk, EnvironmentMap map) {
    RoomHallways hallways = HALLWAY_NONE;
    if (chunk.position.x > 0) {
        if (!map.chunks[(int) chunk.position.x - 1][(int) chunk.position.y].empty) {
            hallways |= HALLWAY_LEFT;
        }
    }
    if (chunk.position.x < MAP_SIZE_CHUNK - 1) {
        if (!map.chunks[(int) chunk.position.x + 1][(int) chunk.position.y].empty) {
            hallways |= HALLWAY_RIGHT;
        }
    }
    if (chunk.position.y > 0) {
        if (!map.chunks[(int) chunk.position.x][(int) chunk.position.y - 1].empty) {
            hallways |= HALLWAY_UP;
        }
    }
    if (chunk.position.y < MAP_SIZE_CHUNK - 1) {
        if (!map.chunks[(int) chunk.position.x][(int) chunk.position.y + 1].empty) {
            hallways |= HALLWAY_DOWN;
        }
    }
    return hallways;
}