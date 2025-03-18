#include <chunks.h>
#include <enemy.h>
#include <enemy_types.h>
#include <random.h>

/*
*   This file handles the creation of a chunk.
?   The code for this part is really painful and uninteresting to read.
?   It's just trying to draw stuff on the screen. With code.
?   It's like trying to paint a picture with a toothbrush.

?   Anyways, just use Chunk_GenerateTiles() to create a chunk.
*/


EnvironmentChunk Chunk_GenerateTiles(Vec2 position, RoomType roomType, Vec2 roomSize, RoomFloorPattern floorPattern, RoomHallways hallways) {
    EnvironmentChunk chunk = {
        .position = position,
        .roomSize = roomSize,
        .hallways = hallways,
        .floorPattern = floorPattern,
        .roomType = roomType,
        .empty = false
    };

    Chunk_GenerateFloorTiles(&chunk);
    Chunk_GenerateWallTiles(&chunk);
    Chunk_GenerateHallways(&chunk);
    Chunk_GenerateHallwayWallTiles(&chunk);
    Chunk_GenerateColliders(&chunk);
    return chunk;
}

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

void Chunk_GenerateColliders(EnvironmentChunk* chunk) {
    int roomStartX = (CHUNK_SIZE_TILE - chunk->roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - chunk->roomSize.y) / 2;
    int roomEndX = roomStartX + chunk->roomSize.x;
    int roomEndY = roomStartY + chunk->roomSize.y;

    if (chunk->hallways & HALLWAY_UP) {
        Chunk_AddCollider(
            (Vec2) {HALLWAY_START - 1, 0}, 
            (Vec2) {HALLWAY_START - 1, roomStartY - 3}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {HALLWAY_END, 0}, 
            (Vec2) {HALLWAY_END, roomStartY - 3}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomStartX, roomStartY - 2}, 
            (Vec2) {HALLWAY_START - 1, roomStartY - 2}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {HALLWAY_END, roomStartY - 2}, 
            (Vec2) {roomEndX - 1, roomStartY - 2}, 
            chunk
        );
    } else {
        Chunk_AddCollider(
            (Vec2) {roomStartX, roomStartY - 2},
            (Vec2) {roomEndX - 1, roomStartY - 2},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_LEFT) {
        Chunk_AddCollider(
            (Vec2) {0 , HALLWAY_START - 2}, 
            (Vec2) {roomStartX - 1, HALLWAY_START - 2}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {0 , HALLWAY_END}, 
            (Vec2) {roomStartX - 1, HALLWAY_END}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomStartX - 1, roomStartY - 1}, 
            (Vec2) {roomStartX - 1, HALLWAY_START - 3}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomStartX - 1, HALLWAY_END + 1}, 
            (Vec2) {roomStartX - 1, roomEndY - 1}, 
            chunk
        );
    } else {
        Chunk_AddCollider(
            (Vec2) {roomStartX - 1, roomStartY - 1},
            (Vec2) {roomStartX - 1, roomEndY - 1},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_DOWN) {
        Chunk_AddCollider(
            (Vec2) {roomStartX, roomEndY}, 
            (Vec2) {HALLWAY_START - 2, roomEndY}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {HALLWAY_START - 1, roomEndY}, 
            (Vec2) {HALLWAY_START - 1, CHUNK_SIZE_TILE - 1}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {HALLWAY_END, roomEndY}, 
            (Vec2) {HALLWAY_END, CHUNK_SIZE_TILE - 1}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {HALLWAY_END + 1, roomEndY}, 
            (Vec2) {roomEndX - 1, roomEndY}, 
            chunk
        );
    } else {
        Chunk_AddCollider(
            (Vec2) {roomStartX, roomEndY},
            (Vec2) {roomEndX - 1, roomEndY},
            chunk
        );
    }

    if (chunk->hallways & HALLWAY_RIGHT) {
        Chunk_AddCollider(
            (Vec2) {roomEndX, roomStartY - 1}, 
            (Vec2) {roomEndX, HALLWAY_START - 3}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomEndX, HALLWAY_START - 2}, 
            (Vec2) {CHUNK_SIZE_TILE - 1, HALLWAY_START - 2}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomEndX, HALLWAY_END}, 
            (Vec2) {CHUNK_SIZE_TILE - 1, HALLWAY_END}, 
            chunk
        );
        Chunk_AddCollider(
            (Vec2) {roomEndX, HALLWAY_END + 1}, 
            (Vec2) {roomEndX, roomEndY - 1}, 
            chunk
        );
    } else {
        Chunk_AddCollider(
            (Vec2) {roomEndX, roomStartY - 1},
            (Vec2) {roomEndX, roomEndY - 1},
            chunk
        );
    }
}

void Chunk_AddCollider(Vec2 startTile, Vec2 endTile, EnvironmentChunk* chunk) {
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
