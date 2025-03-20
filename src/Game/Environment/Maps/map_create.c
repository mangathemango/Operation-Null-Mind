#include <maps.h>
#include <random.h>
#include <enemy_types.h>

void Map_Generate() {
    // 1. Initialize all chunks as empty
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            testMap.chunks[x][y].colliderCount = 0;
            testMap.chunks[x][y].enemyCount = 0;
            testMap.chunks[x][y].empty = true;
            testMap.chunks[x][y].roomType = ROOM_TYPE_NORMAL;
        }
    }
    
    // 2. Place start room (always in top-left quadrant)
    int startX = 3; //I just change to the middle
    int startY = 3; //I just change to the middle
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
                    SDL_Log("Room size at (%d, %d): %fx%f\n", x, y, testMap.chunks[x][y].roomSize.x, testMap.chunks[x][y].roomSize.y);
                }
                
                // Create the chunk with all its details
                testMap.chunks[x][y] = Chunk_GenerateTiles(
                    testMap.chunks[x][y].position,
                    testMap.chunks[x][y].roomType,
                    testMap.chunks[x][y].roomSize,
                    testMap.chunks[x][y].floorPattern,
                    testMap.chunks[x][y].hallways
                );
                if (testMap.chunks[x][y].roomType == ROOM_TYPE_NORMAL) {
                    testMap.chunks[x][y].enemyCount = RandInt(10, 20);
                }
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
    testMap.mainPath[testMap.mainPathLength] = (Vec2){currentX, currentY}; //So basically, this just allows the main path to start somewhere
    SDL_Log("Generating main path via random walk");
    SDL_Log("Current position: (%d, %d) - Target position: (%d, %d)\n", currentX, currentY, endX, endY);
    


    testMap.mainPath[testMap.mainPathLength] = (Vec2){3, 3};//Basically the start point is 3,3 chunk
    int alternatePaths = 0; //Not implemented yet, basically this is gonna be like a stopper for the path
    for(int i = 0; i < 2; i++) { //This loops controls how many nodes, like how long is the path gonna be
        testMap.mainPathLength++;

        int totalBranch;
        //This is branch randomizer, this is to determine how many branches are gonna be created
        int totalBranchRandomizer = RandInt(1,10); 
        if (totalBranchRandomizer <= 4)         totalBranch = 1;    // 40% chance of 1 branch
        else if (totalBranchRandomizer <= 8)    totalBranch = 2;    // 40% chance of 2 branches
        else if (totalBranchRandomizer <= 9)    totalBranch = 3;    // 10% chance of 3 branches
        else                                    totalBranch = 4;    // 10% chance of 4 branches
        
        SDL_Log("Generating %d branches from (%d, %d)", totalBranch, currentX, currentY);

        Vec2 placementList[4] = {
            Vec2_Up,
            Vec2_Right,
            Vec2_Down,
            Vec2_Left
        };

        for(int j = 0; j < totalBranch; j++) {   
            int placementIndex;
            Vec2 placement = Vec2_Zero;

            // This loop is to ensure a path isn't created twice.
            while (placement.x == 0 && placement.y == 0) {
                placementIndex = RandInt(0,3); //This randomize which path to take
                placement = placementList[placementIndex];
                // Will keep looping until we find a Vec2 that isn't (0,0)
            }
            // Set the chosen placement in the array to 0,0 so it can't be chosen again
            placementList[placementIndex] = Vec2_Zero;

            switch (placementIndex) {
                case 0: SDL_Log("Branching up"); break;
                case 1: SDL_Log("Branching right"); break;
                case 2: SDL_Log("Branching down"); break;
                case 3: SDL_Log("Branching left"); break;
            }
            currentX = testMap.mainPath[testMap.mainPathLength-1].x + placement.x; 
            currentY = testMap.mainPath[testMap.mainPathLength-1].y + placement.y;
            testMap.chunks[currentX][currentY].empty = false;
            testMap.mainPath[testMap.mainPathLength] = (Vec2){currentX, currentY};
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