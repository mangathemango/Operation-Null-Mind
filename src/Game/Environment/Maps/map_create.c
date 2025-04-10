/**
 * @file map_create.c
 * @brief Implements procedural map generation
 *
 * Handles the creation of procedurally generated maps,
 * including room placement, hallway connections, and
 * special room distribution.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <maps.h>
#include <random.h>
#include <enemy_types.h>
#include <interactable.h>
#include <random.h>
#include <game.h>

/**
 * @brief Generates a complete game map
 * 
 * Creates a procedurally generated map with rooms, hallways and paths.
 */
void Map_Generate() {
    // 1. Initialize all chunks as empty
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            testMap.chunks[x][y].totalEnemyCount = 0;
            testMap.chunks[x][y].empty = true;
            testMap.chunks[x][y].discovered = false;
            testMap.chunks[x][y].inCombat = false;
            testMap.chunks[x][y].roomType = ROOM_TYPE_NORMAL;
            testMap.chunks[x][y].position = (Vec2){x, y};
            EnvironmentChunk* chunk = &testMap.chunks[x][y];
            for (int i = 0; i < chunk->colliderCount; i++) {
                Collider_Reset(chunk->colliders[i]);
                free(chunk->colliders[i]);
            }
            chunk->colliderCount = 0;
        }
    }
    for (int i = 0; i < testMap.mainPathLength; i++) {
        testMap.mainPath[i] = Vec2_Zero;
    }
    for (int i = 0; i < testMap.alternatePathLength; i++) {
        testMap.alternatePath[i] = Vec2_Zero;
    }
    testMap.mainPathLength = 0;
    testMap.alternatePathLength = 0;
    Interactable_Reset();

    int startX = 3; 
    int startY = 3; 
    Map_SetStartChunk(startX, startY);

    if (game.currentStage != 10) {
        Map_CreateMainPath();
        Map_SetEndChunk(testMap.mainPath[testMap.mainPathLength].x, testMap.mainPath[testMap.mainPathLength].y);
        SDL_Log("Current position: (%d, %d) - Target position: (%d, %d)\n", startX, startY,(int) testMap.mainPath[testMap.mainPathLength].x, (int) testMap.mainPath[testMap.mainPathLength].y);
        for(int k = 0; k < testMap.mainPathLength;k++)
        {
            SDL_Log("Main Path: (%d, %d)", (int) testMap.mainPath[k].x, (int) testMap.mainPath[k].y);
        }
        SDL_Log("Main path generation complete");

        for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
            for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
                if (testMap.chunks[x][y].empty) {
                    continue;
                }

                if (Vec2_AreEqual((Vec2) {x, y}, testMap.startChunk->position) || Vec2_AreEqual((Vec2) {x, y}, testMap.endChunk->position)) {
                    continue;
                }
                if (!Chunk_IsOnMainPath(&testMap.chunks[x][y])) {
                    SDL_Log("Alternate path at (%d, %d)", x, y);
                    testMap.alternatePath[testMap.alternatePathLength++] = (Vec2){x, y};
                } else {
                    SDL_Log("Chunk at (%d, %d) is on main path", x, y);
                }
            }
        }
        int maxChestRoom = 2;
        for (int i = 0; i < maxChestRoom; i++) {
            if (testMap.alternatePathLength == 0) {
                break;
            }
            int randomIndex = RandInt(0, testMap.alternatePathLength - 1);
            Vec2 chunkPosition = testMap.alternatePath[randomIndex];
            testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y].roomType = ROOM_TYPE_CRATE;
            SDL_Log("Crate room at (%d, %d)", (int) chunkPosition.x, (int) chunkPosition.y);
        }
    } else {
        testMap.chunks[3][2].empty = false;
        testMap.chunks[3][2].roomType = ROOM_TYPE_BOSS;
        testMap.chunks[3][2].roomSize = (Vec2) {30, 16};
        testMap.chunks[3][2].totalEnemyCount = 1;
        Map_SetEndChunk(3, 1);
    }
    
    
    


    
    // 5. Initialize all non-empty chunks
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            if (testMap.chunks[x][y].empty) {
                continue;
            }
            SDL_Log ("Generating chunk at (%d, %d)\n", x, y);
            // Set hallways based on adjacent non-empty chunks
            testMap.chunks[x][y].floorPattern = ROOM_FLOOR_PATTERN_1;
            testMap.chunks[x][y].position = (Vec2){x, y};
            testMap.chunks[x][y].hallways = Map_GetChunkHallways(testMap.chunks[x][y], testMap);

            // Generate room details
            if ((testMap.chunks[x][y].roomType == ROOM_TYPE_NORMAL)) {
                int totalEnemyCount = 10 + game.currentStage * 2;
                testMap.chunks[x][y].totalEnemyCount = RandInt(totalEnemyCount / 2, totalEnemyCount * 3 / 2);
                testMap.chunks[x][y].roomSize = (Vec2){RandInt(10,15)*2, RandInt(10,15)*2};
            }
            if (testMap.chunks[x][y].roomType == ROOM_TYPE_CRATE) {
                testMap.chunks[x][y].roomSize = (Vec2){12, 12}; // Slightly larger start room
                Interactable_CreateWeaponCrate(
                    false, 
                    RandInt(0, GUN_COUNT - 1), 
                    Vec2_Add(
                        Chunk_GetChunkCenter(&testMap.chunks[x][y]),
                        (Vec2){0, TILE_SIZE_PIXELS / 2}
                    )
                );
                if (RandInt(0,10) <= 3) {
                    Interactable_CreateLog(
                        RandInt(0, 5), 
                        Vec2_Add(
                            Chunk_GetChunkCenter(&testMap.chunks[x][y]),
                            (Vec2){0, - 3 * TILE_SIZE_PIXELS / 2}
                        )
                    );
                }
            }
            // Create the chunk with all its details
            Chunk_GenerateTilesButVoid(&testMap.chunks[x][y]);
        }
    }
}

/**
 * @brief Sets the starting chunk of the map
 * 
 * @param x X-coordinate of the start chunk
 * @param y Y-coordinate of the start chunk
 */
void Map_SetStartChunk(int x, int y) {
    testMap.startChunk = &testMap.chunks[x][y];
    testMap.startChunk->empty = false;
    testMap.startChunk->roomSize = (Vec2){12, 12}; // Slightly larger start room
    testMap.startChunk->roomType = ROOM_TYPE_START;
    testMap.startChunk->position = (Vec2){x, y};
}

/**
 * @brief Sets the ending chunk of the map
 * 
 * @param x X-coordinate of the end chunk
 * @param y Y-coordinate of the end chunk
 */
void Map_SetEndChunk(int x, int y) {
    testMap.endChunk = &testMap.chunks[x][y];
    testMap.endChunk->empty = false;
    testMap.endChunk->roomSize = (Vec2){12, 12}; // Slightly larger end room
    testMap.endChunk->roomType = ROOM_TYPE_END;
    testMap.endChunk->position = (Vec2){x, y};
}

/**
 * @brief Creates the main path through the map
 * 
 * Generates a random path from the start to end chunk
 */
void Map_CreateMainPath() {
    if (testMap.startChunk == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot create main path without start and end chunks");
        return; // Cannot create main path without start and end chunks
    }
    int currentX = testMap.startChunk->position.x;
    int currentY = testMap.startChunk->position.y;

    // Reset path tracking
    testMap.mainPathLength = 0;
    testMap.mainPath[testMap.mainPathLength] = (Vec2){3, 3}; //So basically, this just allows the main path to start somewhere
    SDL_Log("Generating main path via random walk");
    


    int totalAlternateBranch = 0; //Not implemented yet, basically this is gonna be like a stopper for the path
    for(int i = 0; i < MAP_LENGTH; i++) { //This loops controls how many nodes, like how long is the path gonna be
        testMap.mainPathLength++;

        int totalBranch;
        //This is branch randomizer, this is to determine how many branches are gonna be created
        int totalBranchRandomizer = RandInt(1,10); 
        if (totalBranchRandomizer <= 6)         totalBranch = 1;    // 60% chance of 1 branch
        else if (totalBranchRandomizer <= 8)    totalBranch = 2;    // 20% chance of 2 branches
        else if (totalBranchRandomizer <= 9)    totalBranch = 3;    // 10% chance of 3 branches
        else                                    totalBranch = 1;    // 10% chance of 4 branches
        
        SDL_Log("Generating %d branches from (%d, %d)", totalBranch, currentX, currentY);

        Vec2 placementList[4] = {
            Vec2_Up,
            Vec2_Right,
            Vec2_Down,
            Vec2_Left
        };

        for (int j = 0; j < 4; j++) {
            if (currentX + placementList[j].x < 0 || currentX + placementList[j].x >= MAP_SIZE_CHUNK) {
                placementList[j] = Vec2_Zero;
                continue;
            }
            if (currentY + placementList[j].y < 0 || currentY + placementList[j].y >= MAP_SIZE_CHUNK) {
                placementList[j] = Vec2_Zero;
                continue;
            }
            Vec2 nextPosition = (Vec2) {
                currentX + placementList[j].x,
                currentY + placementList[j].y
            };
            if(Vec2_AreEqual(nextPosition, (Vec2) {3,3})) {
                SDL_Log("Tile is near spawn, skipping");
                placementList[j] = Vec2_Zero;
                continue;
            }
            if (testMap.mainPathLength > 1) {
                Vec2 nextPosition = (Vec2) {
                    currentX + placementList[j].x,
                    currentY + placementList[j].y
                };
                if (Vec2_AreEqual(nextPosition, (Vec2) {2, 3}) || 
                    Vec2_AreEqual(nextPosition, (Vec2) {4, 3}) || 
                    Vec2_AreEqual(nextPosition, (Vec2) {3, 2}) || 
                    Vec2_AreEqual(nextPosition, (Vec2) {3, 4}) ||
                    Vec2_AreEqual(nextPosition, (Vec2) {2, 2}) ||
                    Vec2_AreEqual(nextPosition, (Vec2) {2, 4}) ||
                    Vec2_AreEqual(nextPosition, (Vec2) {4, 4}) ||
                    Vec2_AreEqual(nextPosition, (Vec2) {4, 2})) {
                        SDL_Log("Tile is near spawn, skipping");
                        placementList[j] = Vec2_Zero;
                        continue;
                }
            }
            if (
                testMap.chunks
                [(int) (currentX + placementList[j].x)]
                [(int) (currentY + placementList[j].y)]
                .empty == false
            ) {
                placementList[j] = Vec2_Zero;
                continue;
            }
        }
        
        totalAlternateBranch += totalBranch - 1;
        if(totalAlternateBranch > 7) {
            SDL_Log("Too many alternate paths, no more branches will be created");
            totalBranch = 1;
        }
        for(int j = 0; j < totalBranch; j++) {   
            int placementIndex;
            Vec2 placement = Vec2_Zero;

            bool allZero = true;
            for (int k = 0; k < 4; k++) {
                if (placementList[k].x != 0 || placementList[k].y != 0) {
                    allZero = false;
                    break;
                }
            }
            if (allZero) {
                SDL_Log("No valid branches found, stopping path generation");
                testMap.mainPathLength--;
                break;
            }

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

/**
 * @brief Determines which hallways a chunk should have
 * 
 * @param chunk The chunk to analyze
 * @param map The complete map
 * @return RoomHallways Bitmask of hallway directions to create
 */
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