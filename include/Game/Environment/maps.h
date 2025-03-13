#include <SDL.h>
#include <chunks.h>

// Maps are 5 chunks wide and 5 chunks tall
#define MAP_SIZE_CHUNK 5
#define MAP_SIZE_TILE (MAP_SIZE_CHUNK * CHUNK_SIZE_TILE)

typedef struct {
    EnvironmentChunk chunks[MAP_SIZE_CHUNK][MAP_SIZE_CHUNK];
} EnvironmentMap;

extern EnvironmentMap testMap;

void Map_Start();
void Map_Render();
RoomHallways Map_GetChunkHallways(EnvironmentChunk chunk, EnvironmentMap map);