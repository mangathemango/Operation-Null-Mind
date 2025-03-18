#pragma once

#include <tiles.h>
#include <colliders.h>

#define HALLWAY_SIZE_TILE 4
#define CHUNK_SIZE_TILE 40
#define CHUNK_SIZE_PIXEL (CHUNK_SIZE_TILE * TILE_SIZE_PIXELS)
#define HALLWAY_START (CHUNK_SIZE_TILE - HALLWAY_SIZE_TILE) / 2
#define HALLWAY_END HALLWAY_START + HALLWAY_SIZE_TILE
#define ROOM_STARTX(roomsize) (CHUNK_SIZE_TILE - (roomsize).x) / 2
#define ROOM_STARTY(roomsize) (CHUNK_SIZE_TILE - (roomsize).y) / 2
#define ROOM_ENDX(roomsize) ROOM_STARTX(roomsize) + (roomsize).x
#define ROOM_ENDY(roomsize) ROOM_STARTY(roomsize) + (roomsize).y

typedef enum {
    HALLWAY_NONE    = 0,
    HALLWAY_UP      = 1 << 0,
    HALLWAY_DOWN    = 1 << 1,
    HALLWAY_LEFT    = 1 << 2,
    HALLWAY_RIGHT   = 1 << 3,
} RoomHallways;

typedef enum {
    ROOM_FLOOR_PATTERN_1,
    ROOM_FLOOR_PATTERN_RANDOM,
} RoomFloorPattern;

typedef enum {
    ROOM_TYPE_START,
    ROOM_TYPE_NORMAL,
    ROOM_TYPE_BOSS,
    ROOM_TYPE_END,
} RoomType;
typedef struct {
    Vec2 position;

    EnvironmentTile tiles[CHUNK_SIZE_TILE][CHUNK_SIZE_TILE];

    Vec2 roomSize;
    RoomHallways hallways;
    RoomFloorPattern floorPattern;
    RoomType roomType;
    
    bool empty;

    Collider* colliders[CHUNK_SIZE_TILE];
    int colliderCount;
} EnvironmentChunk;

EnvironmentChunk Chunk_GenerateTiles(Vec2 position, RoomType roomType, Vec2 roomSize ,RoomFloorPattern floorPattern, RoomHallways hallways);
void Chunk_GenerateFloorTiles(EnvironmentChunk* chunk);
void Chunk_GenerateWallTiles(EnvironmentChunk* chunk);
void Chunk_GenerateHallways(EnvironmentChunk* chunk);
void Chunk_GenerateHallwayWallTiles(EnvironmentChunk* chunk);
void Chunk_GenerateColliders(EnvironmentChunk* chunk);
void Chunk_AddCollider(Vec2 startTile, Vec2 endtile, EnvironmentChunk* chunk);
void Chunk_Start();
void Chunk_Render(const EnvironmentChunk *chunk);
extern EnvironmentChunk testChunk;
extern EnvironmentChunk testChunk2;