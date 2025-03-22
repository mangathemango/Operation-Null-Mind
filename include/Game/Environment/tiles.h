/**
 * @file tiles.h
 * @brief Defines and manages environment tiles for game world construction.
 * 
 * @author Mango
 * @date 2025-03-13
 */

#pragma once

#include <vec2.h>
#include <SDL.h>
#include <camera.h>

/**
 * @def TILE_SIZE_PIXELS
 * @brief Defines the size of a tile in pixels
 */
#define TILE_SIZE_PIXELS 20

/**
 * @def MAX(a, b)
 * @brief Safely calculates maximum of two values
 * @param a First value to compare
 * @param b Second value to compare
 * @return The greater of a and b
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @def MIN(a, b)
 * @brief Safely calculates minimum of two values
 * @param a First value to compare
 * @param b Second value to compare
 * @return The lesser of a and b
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * @enum TileType
 * @brief Defines various types of environment tiles
 */
typedef enum {
    TILE_VOID,                  /**< Empty/void tile */
    TILE_FLOOR_1,               /**< Standard floor type 1 */
    TILE_FLOOR_2,               /**< Standard floor type 2 */
    TILE_FLOOR_3,               /**< Standard floor type 3 */
    TILE_FLOOR_VENT_1,          /**< Floor with vent, variation 1 */
    TILE_FLOOR_VENT_2,          /**< Floor with vent, variation 2 */
    TILE_FLOOR_VENT_3,          /**< Floor with vent, variation 3 */
    TILE_FLOOR_SCRATCHED_1,     /**< Scratched floor, variation 1 */
    TILE_FLOOR_SCRATCHED_2,     /**< Scratched floor, variation 2 */
    TILE_FLOOR_SCRATCHED_3,     /**< Scratched floor, variation 3 */
    
    /* Wall tiles */
    TILE_WALL_TOP,              /**< Wall top section */
    TILE_WALL_BOTTOM,           /**< Wall bottom section */
    TILE_WALL_CORNER_BORDER_SMALL, /**< Small corner wall border */
    TILE_WALL_CORNER_BORDER,    /**< Corner wall border */
    TILE_WALL_SIDE_BORDER,      /**< Side wall border */
    
    TILE_TYPE_COUNT             /**< Total count of tile types */
} TileType;

/**
 * @enum TileRotation
 * @brief Defines rotation options for tiles
 */
typedef enum{
    TILE_ROTATE_NONE,           /**< No rotation */
    TILE_ROTATE_CLOCKWISE,      /**< 90 degrees clockwise rotation */
    TILE_ROTATE_COUNTERCLOCKWISE, /**< 90 degrees counterclockwise rotation */
    TILE_ROTATE_180,            /**< 180 degrees rotation */
} TileRotation;

/**
 * @struct EnvironmentTile
 * @brief Represents a single environment tile
 */
typedef struct {
    SDL_Texture* texture;       /**< Texture for this tile */
    TileRotation rotation;      /**< Rotation applied to this tile */
} EnvironmentTile;

/**
 * @struct EnvironmentTileResources
 * @brief Contains loaded textures for all tile types
 */
typedef struct {
    SDL_Texture* textures[TILE_TYPE_COUNT]; /**< Array of textures for each tile type */
} EnvironmentTileResources;

/**
 * @struct EnvironmentTileConfig
 * @brief Configuration for tile resources
 */
typedef struct {
    char* texturePaths[TILE_TYPE_COUNT]; /**< Paths to texture files for each tile type */
} EnvironmentTileConfig;

/**
 * @struct EnvironmentTileData
 * @brief Global tile data container
 */
typedef struct {
    EnvironmentTileResources resources; /**< Loaded tile resources */
    EnvironmentTileConfig config;       /**< Tile configuration */
} EnvironmentTileData;

/** Global tile data instance */
extern EnvironmentTileData tiles;

/**
 * @brief Initialize tile system
 */
void Tile_Start();

/**
 * @brief Create a new environment tile
 * @param type The type of tile to create
 * @param rotation The rotation to apply to the tile
 * @return A new EnvironmentTile instance
 */
EnvironmentTile Tile_Create(TileType type, TileRotation rotation);

/**
 * @brief Destroy a tile and free resources
 * @param tile Pointer to the tile to destroy
 */
void Tile_Destroy(EnvironmentTile* tile);

/**
 * @brief Render a tile at the specified position
 * @param tile The tile to render
 * @param tilePosition Position where the tile should be rendered
 */
void Tile_Render(EnvironmentTile tile, Vec2 tilePosition);

/* Utilities */

/**
 * @brief Convert a pixel coordinate to tile and chunk indices
 * @param pixelPoint The pixel coordinate to convert
 * @param chunkIndex Output parameter for the chunk index
 * @param tileIndex Output parameter for the tile index
 */
void Tile_FromPixelPoint(Vec2 pixelPoint, Vec2* chunkIndex, Vec2* tileIndex);

/**
 * @brief Check if a tile index is valid
 * @param tileIndex The tile index to check
 * @return true if the tile index is valid, false otherwise
 */
bool Tile_IsValid(Vec2 tileIndex);

/**
 * @brief Convert a pixel coordinate to a tile position
 * @param pixelPoint The pixel coordinate to convert
 * @return The tile position
 */
Vec2 Tile_GetPositionFromPixel(Vec2 pixelPoint);

/**
 * @brief Get the rectangle of a tile from a pixel coordinate
 * @param pixelPoint The pixel coordinate
 * @return An SDL_Rect representing the tile's bounds
 */
SDL_Rect Tile_GetRectFromPixel(Vec2 pixelPoint);

/**
 * @brief Get a random pixel coordinate within a rectangle
 * @param rect The rectangle to get a random pixel from
 * @return A random pixel coordinate within the rectangle
 */
Vec2 Tile_GetRandomPixelInRect(SDL_Rect rect);

/**
 * @brief Convert tile and chunk indices to a pixel coordinate
 * @param tileIndex The tile index
 * @param chunkIndex The chunk index
 * @return The corresponding pixel coordinate
 */
Vec2 Tile_TileIndexToPixel(Vec2 tileIndex, Vec2 chunkIndex);

