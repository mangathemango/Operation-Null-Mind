#pragma once

#include <tiles.h>
#include <colliders.h>

#define HALLWAY_SIZE_TILE 6
#define CHUNK_SIZE_TILE 30
#define CHUNK_SIZE_PIXEL (CHUNK_SIZE_TILE * TILE_SIZE_PIXELS)


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
typedef struct {
    EnvironmentTile tiles[CHUNK_SIZE_TILE][CHUNK_SIZE_TILE];
    Collider* colliders[CHUNK_SIZE_TILE];
    Vec2 roomSize;
    RoomHallways hallways;
    RoomFloorPattern floorPattern;
    bool empty;
} EnvironmentChunk;

EnvironmentChunk Chunk_Create(Vec2 roomSize ,RoomFloorPattern floorPattern, RoomHallways hallways);
void Chunk_Start();
void Chunk_Render(EnvironmentChunk chunk, Vec2 chunkPosition);
extern EnvironmentChunk testChunk;