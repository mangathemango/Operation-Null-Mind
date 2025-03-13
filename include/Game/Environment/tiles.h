#pragma once

#include <vec2.h>
#include <SDL.h>

#define TILE_SIZE_PIXELS 20


// Define tile types with enum
typedef enum {
    // Floor tiles
    TILE_VOID,
    TILE_FLOOR_1,
    TILE_FLOOR_2,
    TILE_FLOOR_3,
    TILE_FLOOR_VENT_1,
    TILE_FLOOR_VENT_2,
    TILE_FLOOR_VENT_3,
    TILE_FLOOR_SCRATCHED_1,
    TILE_FLOOR_SCRATCHED_2,
    TILE_FLOOR_SCRATCHED_3,
    
    // Wall tiles
    TILE_WALL_TOP,
    TILE_WALL_BOTTOM,
    TILE_WALL_CORNER_BORDER,
    TILE_WALL_SIDE_BORDER,
    
    // Keep track of count
    TILE_TYPE_COUNT
} TileType;

typedef enum{
    TILE_ROTATE_NONE,
    TILE_ROTATE_CLOCKWISE,
    TILE_ROTATE_COUNTERCLOCKWISE,
    TILE_ROTATE_180,
} TileRotation;
typedef struct {
    SDL_Texture* texture;
    TileRotation rotation;
} EnvironmentTile;

typedef struct {
    SDL_Texture* textures[TILE_TYPE_COUNT];
} EnvironmentTileResources;

typedef struct {
    char* texturePaths[TILE_TYPE_COUNT];
} EnvironmentTileConfig;

typedef struct {
    EnvironmentTileResources resources;
    EnvironmentTileConfig config;
} EnvironmentTileData;

extern EnvironmentTileData tiles;

void Tile_Start();
EnvironmentTile Tile_Create(TileType type, TileRotation rotation);
void Tile_Destroy(EnvironmentTile* tile);
void Tile_Render(EnvironmentTile tile, Vec2 tilePosition);
