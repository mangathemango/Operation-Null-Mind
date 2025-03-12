#include <tiles.h>
#include <colliders.h>

#define HALLWAY_SIZE_TILE 6
#define CHUNK_SIZE_TILE 6
#define CHUNK_SIZE_PIXEL (CHUNK_SIZE_TILE * TILE_SIZE_PIXELS)

typedef struct {
    EnvironmentTile tiles[CHUNK_SIZE_TILE][CHUNK_SIZE_TILE];
    Collider* colliders[CHUNK_SIZE_TILE];
} EnvironmentChunk;