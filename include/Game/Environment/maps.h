#pragma once

#include <SDL.h>
#include <chunks.h>

// Maps are 5 chunks wide and 5 chunks tall
#define MAP_SIZE_CHUNK 7
#define MAP_SIZE_TILE (MAP_SIZE_CHUNK * CHUNK_SIZE_TILE)

// Add this to your EnvironmentMap struct
typedef struct {
    // Existing map fields
    EnvironmentChunk chunks[MAP_SIZE_CHUNK][MAP_SIZE_CHUNK];
    EnvironmentChunk* startChunk;
    EnvironmentChunk* endChunk;
    
    // Main path tracking
    Vec2 mainPath[MAP_SIZE_CHUNK * MAP_SIZE_CHUNK];
    int mainPathLength;
} EnvironmentMap;

extern EnvironmentMap testMap;

void Map_Start();
void Map_Render();
void Map_Generate();
void Map_SetStartChunk(int x, int y);
void Map_SetEndChunk(int x, int y);
void Map_CreateMainPath();
RoomHallways Map_GetChunkHallways(EnvironmentChunk chunk, EnvironmentMap map);