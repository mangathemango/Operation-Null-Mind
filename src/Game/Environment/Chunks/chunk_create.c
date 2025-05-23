/**
 * @file chunk_create.c
 * @brief Creates and initializes environment chunks
 *
 * Handles the procedural generation of chunk tiles, walls,
 * and collision boundaries based on chunk parameters.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <chunks.h>
#include <enemy.h>
#include <enemy_types.h>
#include <random.h>

/**
 * [Utility] Generates a complete chunk with tiles, hallways, and colliders
 * 
 * Creates a fully-formed environment chunk with all necessary components
 * including floor tiles, walls, hallways, and collision boxes.
 * 
 * @param position World position of the chunk
 * @param roomType Type of room to generate (start, normal, boss, end)
 * @param roomSize Size of the room in tiles
 * @param floorPattern Pattern to use for floor tiles
 * @param hallways Configuration of hallways connected to this room
 * @return EnvironmentChunk The fully generated chunk
 */
EnvironmentChunk Chunk_GenerateTiles(Vec2 position, RoomType roomType, Vec2 roomSize, RoomFloorPattern floorPattern, RoomHallways hallways) {
    EnvironmentChunk chunk = {
        .position = position,
        .roomSize = roomSize,
        .hallways = hallways,
        .floorPattern = floorPattern,
        .roomType = roomType,
    };


    Chunk_GenerateFloorTiles(&chunk);
    Chunk_GenerateWallTiles(&chunk);
    Chunk_GenerateHallways(&chunk);
    Chunk_GenerateHallwayWallTiles(&chunk);
    Chunk_GenerateColliders(&chunk);
    return chunk;
}

/**
 * [Utility] Regenerates all tiles for an existing chunk
 * 
 * Clears all existing tiles and colliders from a chunk and regenerates them,
 * useful when hallway configurations change or room state changes.
 * 
 * @param chunk Pointer to the chunk to regenerate
 */
void Chunk_GenerateTilesButVoid(EnvironmentChunk* chunk) {
    for (int i = 0; i < chunk->colliderCount; i++) {
        Collider_Reset(chunk->colliders[i]);
        free(chunk->colliders[i]);
    }
    chunk->colliderCount = 0;
    Chunk_GenerateFloorTiles(chunk);
    Chunk_GenerateWallTiles(chunk);
    Chunk_GenerateHallways(chunk);
    Chunk_GenerateHallwayWallTiles(chunk);
    Chunk_GenerateColliders(chunk);
}

/**
 * [Utility] Generates floor tiles for a chunk
 * 
 * Creates the base floor tiles for a room based on its size and floor pattern.
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateFloorTiles(EnvironmentChunk* chunk) {
    
    int roomStartX = (CHUNK_SIZE_TILE - chunk->roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - chunk->roomSize.y) / 2;
    int roomEndX = roomStartX + chunk->roomSize.x;
    int roomEndY = roomStartY + chunk->roomSize.y;

    // Generate floor tiles
    for (int x = 0; x < CHUNK_SIZE_TILE; x++) {
        for (int y = 0; y < CHUNK_SIZE_TILE; y++) {
            TileType type = TILE_VOID;
            TileRotation rotation = TILE_ROTATE_NONE;
            if (x >= roomStartX && x < roomEndX && y >= roomStartY && y < roomEndY) {
                switch (chunk->floorPattern) {
                    case ROOM_FLOOR_PATTERN_RANDOM:
                        type = RandInt(TILE_FLOOR_1, TILE_FLOOR_VENT_3);
                        break;
                    case ROOM_FLOOR_PATTERN_1:
                        type = TILE_FLOOR_1;
                        break;
                }
            }
            chunk->tiles[x][y] = Tile_Create(type, rotation);
        }
    }
}

/**
 * [Utility] Generates hallway tiles for a chunk
 * 
 * Creates floor tiles for hallways based on the room's hallway configuration.
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateHallways(EnvironmentChunk* chunk) {
    int roomStartX = ROOM_STARTX(chunk->roomSize);
    int roomStartY = ROOM_STARTY(chunk->roomSize);
    int roomEndX = ROOM_ENDX(chunk->roomSize);
    int roomEndY = ROOM_ENDY(chunk->roomSize);

    for (int x = HALLWAY_START; x < HALLWAY_END; x++) {
        if (chunk->hallways & HALLWAY_UP) {
            for (int y = 0; y < roomStartY; y++) {
                chunk->tiles[x][y] = Tile_Create(TILE_FLOOR_1, TILE_ROTATE_NONE);
            }
        }
        if (chunk->hallways & HALLWAY_DOWN) {
            for (int y = roomEndY; y < CHUNK_SIZE_TILE; y++) {
                chunk->tiles[x][y] = Tile_Create(TILE_FLOOR_1, TILE_ROTATE_NONE);
            }
        }
    }

    for (int y = HALLWAY_START; y < HALLWAY_END; y++) {
        if (chunk->hallways & HALLWAY_LEFT) {
            for (int x = 0; x < roomStartX; x++) {
                chunk->tiles[x][y] = Tile_Create(TILE_FLOOR_1, TILE_ROTATE_NONE);
            }
        }
        if (chunk->hallways & HALLWAY_RIGHT) {
            for (int x = roomEndX; x < CHUNK_SIZE_TILE; x++) {
                chunk->tiles[x][y] = Tile_Create(TILE_FLOOR_1, TILE_ROTATE_NONE);
            }
        }
    }
}

/**
 * [Utility] Generates wall tiles for a chunk
 * 
 * Creates wall tiles around the room perimeter using appropriate wall sprites
 * with correct rotations.
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateWallTiles(EnvironmentChunk* chunk) {

    int roomStartX = (CHUNK_SIZE_TILE - chunk->roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - chunk->roomSize.y) / 2;
    int roomEndX = roomStartX + chunk->roomSize.x;
    int roomEndY = roomStartY + chunk->roomSize.y;

    for (int x = roomStartX; x < roomEndX; x++) {
        chunk->tiles[x][roomStartY - 1] = Tile_Create(TILE_WALL_BOTTOM, TILE_ROTATE_NONE);
        chunk->tiles[x][roomStartY - 2] = Tile_Create(TILE_WALL_TOP, TILE_ROTATE_NONE);
        chunk->tiles[x][roomStartY - 3] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_NONE);
    }

    for (int y = roomStartY - 2; y < roomEndY; y++) {
        chunk->tiles[roomStartX - 1][y] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_COUNTERCLOCKWISE);
        chunk->tiles[roomEndX][y]   = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_CLOCKWISE);
    }
    chunk->tiles[roomStartX - 1][roomStartY - 3] = Tile_Create(TILE_WALL_CORNER_BORDER_SMALL, TILE_ROTATE_COUNTERCLOCKWISE);
    chunk->tiles[roomEndX][roomStartY - 3] = Tile_Create(TILE_WALL_CORNER_BORDER_SMALL, TILE_ROTATE_NONE);
}

/**
 * [Utility] Generates wall tiles for hallways
 * 
 * Creates wall tiles along the sides of hallways with appropriate
 * corner pieces at junctions.
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateHallwayWallTiles(EnvironmentChunk* chunk) {
    int roomStartX = (CHUNK_SIZE_TILE - chunk->roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - chunk->roomSize.y) / 2;
    int roomEndX = roomStartX + chunk->roomSize.x;
    int roomEndY = roomStartY + chunk->roomSize.y;

    if (chunk->hallways & HALLWAY_UP) {
        for (int y = 0; y < roomStartY - 2; y++) {
            chunk->tiles[HALLWAY_START - 1][y] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_COUNTERCLOCKWISE);
            chunk->tiles[HALLWAY_END][y] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_CLOCKWISE);
        } 
        chunk->tiles[HALLWAY_START - 1][roomStartY - 3] = Tile_Create(TILE_WALL_CORNER_BORDER, TILE_ROTATE_COUNTERCLOCKWISE);
        chunk->tiles[HALLWAY_END][roomStartY - 3] = Tile_Create(TILE_WALL_CORNER_BORDER, TILE_ROTATE_NONE);
    }

    if (chunk->hallways & HALLWAY_LEFT) {
        for (int x = 0; x < roomStartX; x ++) {
            chunk->tiles[x][HALLWAY_START - 1] = Tile_Create(TILE_WALL_BOTTOM, TILE_ROTATE_NONE);
            chunk->tiles[x][HALLWAY_START - 2] = Tile_Create(TILE_WALL_TOP, TILE_ROTATE_NONE);
            chunk->tiles[x][HALLWAY_START - 3] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_NONE);
        }
        chunk->tiles[roomStartX - 1][HALLWAY_START - 3] = Tile_Create(TILE_WALL_CORNER_BORDER, TILE_ROTATE_COUNTERCLOCKWISE);
    }

    if (chunk->hallways & HALLWAY_RIGHT) {
        for (int x = roomEndX; x < CHUNK_SIZE_TILE; x ++) {
            chunk->tiles[x][HALLWAY_START - 1] = Tile_Create(TILE_WALL_BOTTOM, TILE_ROTATE_NONE);
            chunk->tiles[x][HALLWAY_START - 2] = Tile_Create(TILE_WALL_TOP, TILE_ROTATE_NONE);
            chunk->tiles[x][HALLWAY_START - 3] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_NONE);
        }
        chunk->tiles[roomEndX][HALLWAY_START - 3] = Tile_Create(TILE_WALL_CORNER_BORDER, TILE_ROTATE_NONE);
    }
    
    if (chunk->hallways & HALLWAY_DOWN) {
        for (int y = roomEndY; y < CHUNK_SIZE_TILE; y++) {
            chunk->tiles[HALLWAY_START - 1][y] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_COUNTERCLOCKWISE);
            chunk->tiles[HALLWAY_END][y] = Tile_Create(TILE_WALL_SIDE_BORDER, TILE_ROTATE_CLOCKWISE);
        } 
    }
}

/**
 * [Utility] Generates collision boxes for a chunk
 * 
 * Creates colliders for walls and hallways, as well as trigger
 * zones for room and hallway detection.
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateColliders(EnvironmentChunk* chunk) {
    int roomStartX = (CHUNK_SIZE_TILE - chunk->roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - chunk->roomSize.y) / 2;
    int roomEndX = roomStartX + chunk->roomSize.x;
    int roomEndY = roomStartY + chunk->roomSize.y;

    Chunk_AddRoomTrigger(
        (Vec2) {roomStartX, roomStartY}, 
        (Vec2) {roomEndX - 1, roomEndY - 1}, 
        chunk
    );
    if(chunk->roomType == ROOM_TYPE_END || chunk->roomType == ROOM_TYPE_START)
    {
        Chunk_AddEndTrigger(
            (Vec2) {roomStartX, roomStartY}, 
            (Vec2) {roomEndX - 1, roomEndY - 1}, 
            chunk
        );
    }
    if (chunk->hallways & HALLWAY_UP) {
        Chunk_AddHallwayTrigger(
            (Vec2) {HALLWAY_START, 0}, 
            (Vec2) {HALLWAY_END - 1, roomStartY - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_START - 1, 0}, 
            (Vec2) {HALLWAY_START - 1, roomStartY - 3}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_END, 0}, 
            (Vec2) {HALLWAY_END, roomStartY - 3}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomStartX, roomStartY - 2}, 
            (Vec2) {HALLWAY_START - 1, roomStartY - 2}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_END, roomStartY - 2}, 
            (Vec2) {roomEndX - 1, roomStartY - 2}, 
            chunk
        );
    } else {
        Chunk_AddWallCollider(
            (Vec2) {roomStartX, roomStartY - 2},
            (Vec2) {roomEndX - 1, roomStartY - 2},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_LEFT) {
        Chunk_AddHallwayTrigger(
            (Vec2) {0, HALLWAY_START}, 
            (Vec2) {roomStartX - 1, HALLWAY_END - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {0 , HALLWAY_START - 2}, 
            (Vec2) {roomStartX - 1, HALLWAY_START - 2}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {0 , HALLWAY_END}, 
            (Vec2) {roomStartX - 1, HALLWAY_END}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomStartX - 1, roomStartY - 1}, 
            (Vec2) {roomStartX - 1, HALLWAY_START - 3}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomStartX - 1, HALLWAY_END + 1}, 
            (Vec2) {roomStartX - 1, roomEndY - 1}, 
            chunk
        );
    } else {
        Chunk_AddWallCollider(
            (Vec2) {roomStartX - 1, roomStartY - 1},
            (Vec2) {roomStartX - 1, roomEndY - 1},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_DOWN) {
        Chunk_AddHallwayTrigger(
            (Vec2) {HALLWAY_START, roomEndY}, 
            (Vec2) {HALLWAY_END - 1, CHUNK_SIZE_TILE - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomStartX, roomEndY}, 
            (Vec2) {HALLWAY_START - 2, roomEndY}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_START - 1, roomEndY}, 
            (Vec2) {HALLWAY_START - 1, CHUNK_SIZE_TILE - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_END, roomEndY}, 
            (Vec2) {HALLWAY_END, CHUNK_SIZE_TILE - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {HALLWAY_END + 1, roomEndY}, 
            (Vec2) {roomEndX - 1, roomEndY}, 
            chunk
        );
    } else {
        Chunk_AddWallCollider(
            (Vec2) {roomStartX, roomEndY},
            (Vec2) {roomEndX - 1, roomEndY},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_RIGHT) {
        Chunk_AddHallwayTrigger(
            (Vec2) {roomEndX, HALLWAY_START}, 
            (Vec2) {CHUNK_SIZE_TILE - 1, HALLWAY_END - 1}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomEndX, roomStartY - 1}, 
            (Vec2) {roomEndX, HALLWAY_START - 3}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomEndX, HALLWAY_START - 2}, 
            (Vec2) {CHUNK_SIZE_TILE - 1, HALLWAY_START - 2}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomEndX, HALLWAY_END}, 
            (Vec2) {CHUNK_SIZE_TILE - 1, HALLWAY_END}, 
            chunk
        );
        Chunk_AddWallCollider(
            (Vec2) {roomEndX, HALLWAY_END + 1}, 
            (Vec2) {roomEndX, roomEndY - 1}, 
            chunk
        );
    } else {
        Chunk_AddWallCollider(
            (Vec2) {roomEndX, roomStartY - 1},
            (Vec2) {roomEndX, roomEndY - 1},
            chunk
        );
    }
}

/**
 * [Utility] Adds a wall collider to a chunk
 * 
 * Creates a physical collision box for walls at the specified location.
 * 
 * @param startTile Starting tile position of the wall
 * @param endTile Ending tile position of the wall
 * @param chunk Pointer to the chunk
 */
void Chunk_AddWallCollider(Vec2 startTile, Vec2 endTile, EnvironmentChunk* chunk) {
    Vec2 startPixel = Vec2_Multiply(startTile, TILE_SIZE_PIXELS);
    Vec2 colliderSizeTiles = Vec2_Subtract(endTile, startTile);
    Vec2_Increment(&colliderSizeTiles, (Vec2) {1, 1});
    Vec2 colliderSizePixels = Vec2_Multiply(colliderSizeTiles, TILE_SIZE_PIXELS);
    
    Collider* collider = malloc(sizeof(Collider));
    collider->hitbox = (SDL_Rect) {
        startPixel.x + chunk->position.x * CHUNK_SIZE_PIXEL,
        startPixel.y + chunk->position.y * CHUNK_SIZE_PIXEL,
        colliderSizePixels.x,
        colliderSizePixels.y,
    };
    collider->collidesWith = COLLISION_LAYER_NONE;
    collider->layer = COLLISION_LAYER_ENVIRONMENT;
    Collider_Register(collider, NULL);
    chunk->colliders[chunk->colliderCount++] = collider;
}

#include <player.h>

/**
 * [Event Handler] Event handler for when player enters a room
 * 
 * Updates player state to indicate they are inside a room,
 * which affects combat and other game systems.
 */
void Chunk_HandlePlayerInsideRoom() {
    player.state.insideRoom = true;
}

/**
 * [Event Handler] Event handler for when player enters a hallway
 * 
 * Updates player state to indicate they are inside a hallway,
 * which affects combat and movement.
 */
void Chunk_HandlePlayerInsideHallway() {
    player.state.insideHallway = true;
}

/**
 * [Event Handler] Event handler for when player enters an end room
 * 
 * Updates player state to indicate they have reached the end of the level,
 * enabling level completion functionality.
 */
void Chunk_HandlePlayerInsideEnd() {
    player.state.insideEnd = true;
}

/**
 * [Utility] Adds a room trigger collider to a chunk
 * 
 * Creates a trigger zone that detects when the player is inside a room.
 * 
 * @param startTile Starting tile position
 * @param endTile Ending tile position
 * @param chunk Pointer to the chunk
 */
void Chunk_AddRoomTrigger(Vec2 startTile, Vec2 endTile, EnvironmentChunk* chunk) {
    Vec2 startPixel = Vec2_Multiply(startTile, TILE_SIZE_PIXELS);
    Vec2 colliderSizeTiles = Vec2_Subtract(endTile, startTile);
    Vec2_Increment(&colliderSizeTiles, (Vec2) {1, 1});
    Vec2 colliderSizePixels = Vec2_Multiply(colliderSizeTiles, TILE_SIZE_PIXELS);
    
    Collider* collider = malloc(sizeof(Collider));
    collider->hitbox = (SDL_Rect) {
        startPixel.x + chunk->position.x * CHUNK_SIZE_PIXEL,
        startPixel.y + chunk->position.y * CHUNK_SIZE_PIXEL,
        colliderSizePixels.x,
        colliderSizePixels.y,
    };
    collider->collidesWith = COLLISION_LAYER_NONE;
    collider->layer = COLLISION_LAYER_TRIGGER;
    Collider_Register(collider, &Chunk_HandlePlayerInsideRoom);
    chunk->colliders[chunk->colliderCount++] = collider;
}

/**
 * [Utility] Adds a hallway trigger collider to a chunk
 * 
 * Creates a trigger zone that detects when the player is inside a hallway.
 * 
 * @param startTile Starting tile position
 * @param endTile Ending tile position
 * @param chunk Pointer to the chunk
 */
void Chunk_AddHallwayTrigger(Vec2 startTile, Vec2 endTile, EnvironmentChunk* chunk) {
    Vec2 startPixel = Vec2_Multiply(startTile, TILE_SIZE_PIXELS);
    Vec2 colliderSizeTiles = Vec2_Subtract(endTile, startTile);
    Vec2_Increment(&colliderSizeTiles, (Vec2) {1, 1});
    Vec2 colliderSizePixels = Vec2_Multiply(colliderSizeTiles, TILE_SIZE_PIXELS);
    
    Collider* collider = malloc(sizeof(Collider));
    collider->hitbox = (SDL_Rect) {
        startPixel.x + chunk->position.x * CHUNK_SIZE_PIXEL,
        startPixel.y + chunk->position.y * CHUNK_SIZE_PIXEL,
        colliderSizePixels.x,
        colliderSizePixels.y,
    };
    collider->collidesWith = COLLISION_LAYER_NONE;
    collider->layer = COLLISION_LAYER_TRIGGER;
    Collider_Register(collider, &Chunk_HandlePlayerInsideHallway);
    chunk->colliders[chunk->colliderCount++] = collider;
}

/**
 * [Utility] Adds an end room trigger collider to a chunk
 * 
 * Creates a trigger zone in the center of the end room that detects
 * when the player has reached the level exit.
 * 
 * @param startTile Starting tile position
 * @param endTile Ending tile position
 * @param chunk Pointer to the chunk
 */
void Chunk_AddEndTrigger(Vec2 startTile, Vec2 endTile, EnvironmentChunk* chunk) {
    Vec2 colliderSizeTiles = Vec2_Subtract(endTile, startTile);
    Vec2_Increment(&colliderSizeTiles, (Vec2) {1, 1});
    
    int index = Interactable_Create(
        INTERACTABLE_EXIT, 
        Vec2_Add(Chunk_GetChunkCenter(chunk), (Vec2) {0, -20})
    );
    
    if (chunk->roomType == ROOM_TYPE_END) {
        interactables[index].enabled = true;
    } else {
        interactables[index].enabled = false;
    }

    Vec2 chunkPosition, tilePosition;
    Tile_FromPixelPoint(
        Chunk_GetChunkCenter(chunk), 
        &chunkPosition, 
        &tilePosition
    );
    Vec2 pixelPoint = Tile_TileIndexToPixel(
        tilePosition, 
        chunkPosition
    );
    Chunk_AddWallCollider(
        Vec2_Subtract(tilePosition, (Vec2) {3, 3}),
        Vec2_Add(tilePosition, (Vec2) {2, -1}),
        chunk
    );
}