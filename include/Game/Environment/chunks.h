/**
 * @file chunks.h
 * @brief This file contains the declaration of the EnvironmentChunk struct and its functions.
 * 
 * @author Mango and Darren
 * @date 2023-03-22
 */

#pragma once

#include <tiles.h>
#include <colliders.h>

/**
 * @def HALLWAY_SIZE_TILE
 * @brief Width/height of hallway in tiles
 */
#define HALLWAY_SIZE_TILE 6

/**
 * @def CHUNK_SIZE_TILE
 * @brief Size of a chunk in tiles
 */
#define CHUNK_SIZE_TILE 60

/**
 * @def CHUNK_SIZE_PIXEL
 * @brief Size of a chunk in pixels
 */
#define CHUNK_SIZE_PIXEL (CHUNK_SIZE_TILE * TILE_SIZE_PIXELS)

/**
 * @def HALLWAY_START
 * @brief Starting position of hallway within a chunk
 */
#define HALLWAY_START (CHUNK_SIZE_TILE - HALLWAY_SIZE_TILE) / 2

/**
 * @def HALLWAY_END
 * @brief Ending position of hallway within a chunk
 */
#define HALLWAY_END HALLWAY_START + HALLWAY_SIZE_TILE

/**
 * @def ROOM_STARTX
 * @brief Starting X position of a room based on its size
 */
#define ROOM_STARTX(roomsize) (CHUNK_SIZE_TILE - (roomsize).x) / 2

/**
 * @def ROOM_STARTY
 * @brief Starting Y position of a room based on its size
 */
#define ROOM_STARTY(roomsize) (CHUNK_SIZE_TILE - (roomsize).y) / 2

/**
 * @def ROOM_ENDX
 * @brief Ending X position of a room based on its size
 */
#define ROOM_ENDX(roomsize) ROOM_STARTX(roomsize) + (roomsize).x

/**
 * @def ROOM_ENDY
 * @brief Ending Y position of a room based on its size
 */
#define ROOM_ENDY(roomsize) ROOM_STARTY(roomsize) + (roomsize).y

/**
 * @enum RoomHallways
 * @brief Possible hallways directions in a room
 */
typedef enum {
    HALLWAY_NONE    = 0,        /**< No hallway */
    HALLWAY_UP      = 1 << 0,   /**< Hallway up */
    HALLWAY_DOWN    = 1 << 1,   /**< Hallway down */
    HALLWAY_LEFT    = 1 << 2,   /**< Hallway left */
    HALLWAY_RIGHT   = 1 << 3,   /**< Hallway right */
} RoomHallways;

/**
 * @enum RoomFloorPattern
 * @brief Possible floor patterns in a room
 */
typedef enum {
    ROOM_FLOOR_PATTERN_1,       /**< Floor pattern 1 */
    ROOM_FLOOR_PATTERN_RANDOM,  /**< Random floor pattern */
} RoomFloorPattern;

/**
 * @enum RoomType
 * @brief Possible types of rooms
 */
typedef enum {
    ROOM_TYPE_START,    /**< Start room */
    ROOM_TYPE_NORMAL,   /**< Normal room */
    ROOM_TYPE_BOSS,     /**< Boss room */
    ROOM_TYPE_END,      /**< End room */
} RoomType;

/**
 * @struct EnvironmentChunk
 * @brief Represents a chunk of the environment
 */
typedef struct {
    Vec2 position;  /**< Position of the chunk */

    EnvironmentTile tiles[CHUNK_SIZE_TILE][CHUNK_SIZE_TILE]; /**< Tiles in the chunk */

    Vec2 roomSize;  /**< Size of the room in the chunk */
    RoomHallways hallways;  /**< Hallways in the room */
    RoomFloorPattern floorPattern;  /**< Floor pattern in the room */
    RoomType roomType;  /**< Type of the room */
    
    int totalEnemyCount;  /**< Total number of enemies in the room */
    int currentEnemyCount;  /**< Current number of enemies in the room */
    bool inCombat;  /**< Whether the room is in combat */
    bool empty;  /**< Whether the room is empty */
    bool discovered;  /**< Whether the room is discovered */

    Collider* colliders[CHUNK_SIZE_TILE];  /**< Colliders in the chunk */
    int colliderCount;  /**< Number of colliders in the chunk */
} EnvironmentChunk;

/**
 * @brief Generates tiles for a chunk
 * 
 * @param position Position of the chunk
 * @param roomType Type of the room
 * @param roomSize Size of the room
 * @param floorPattern Floor pattern of the room
 * @param hallways Hallways in the room
 * @return EnvironmentChunk Generated chunk
 */
EnvironmentChunk Chunk_GenerateTiles(Vec2 position, RoomType roomType, Vec2 roomSize ,RoomFloorPattern floorPattern, RoomHallways hallways);

/**
 * @brief Generates void tiles for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateTilesButVoid(EnvironmentChunk* chunk);

/**
 * @brief Generates floor tiles for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateFloorTiles(EnvironmentChunk* chunk);

/**
 * @brief Generates wall tiles for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateWallTiles(EnvironmentChunk* chunk);

/**
 * @brief Generates hallways for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateHallways(EnvironmentChunk* chunk);

/**
 * @brief Generates hallway wall tiles for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateHallwayWallTiles(EnvironmentChunk* chunk);

/**
 * @brief Generates colliders for a chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_GenerateColliders(EnvironmentChunk* chunk);

/**
 * @brief Adds a wall collider to a chunk
 * 
 * @param startTile Starting tile of the wall
 * @param endtile Ending tile of the wall
 * @param chunk Pointer to the chunk
 */
void Chunk_AddWallCollider(Vec2 startTile, Vec2 endtile, EnvironmentChunk* chunk);

/**
 * @brief Adds a room trigger to a chunk
 * 
 * @param startTile Starting tile of the room
 * @param endtile Ending tile of the room
 * @param chunk Pointer to the chunk
 */
void Chunk_AddRoomTrigger(Vec2 startTile, Vec2 endtile, EnvironmentChunk* chunk);

/**
 * @brief Adds a hallway trigger to a chunk
 * 
 * @param startTile Starting tile of the hallway
 * @param endtile Ending tile of the hallway
 * @param chunk Pointer to the chunk
 */
void Chunk_AddHallwayTrigger(Vec2 startTile, Vec2 endtile, EnvironmentChunk* chunk);

/**
 * @brief Adds an end trigger to a chunk
 * 
 * @param startTile Starting tile of the end
 * @param endtile Ending tile of the end
 * @param chunk Pointer to the chunk
 */
void Chunk_AddEndTrigger(Vec2 startTile, Vec2 endtile, EnvironmentChunk* chunk);

/**
 * @brief Handles player inside a room
 */
void Chunk_HandlePlayerInsideRoom();

/**
 * @brief Handles player inside a hallway
 */
void Chunk_HandlePlayerInsideHallway();

/**
 * @brief Handles player inside the end
 */
void Chunk_HandlePlayerInsideEnd();

/**
 * @brief Starts the chunk
 */
void Chunk_Start();

/**
 * @brief Renders the chunk
 * 
 * @param chunk Pointer to the chunk
 */
void Chunk_Render(const EnvironmentChunk *chunk);

/**
 * @brief Gets the current chunk based on position
 * 
 * @param position Position to get the chunk
 * @return EnvironmentChunk* Pointer to the current chunk
 */
EnvironmentChunk* Chunk_GetCurrentChunk(Vec2 position);

/**
 * @brief Gets a random tile in the room
 * 
 * @param chunk Pointer to the chunk
 * @return Vec2 Random tile position
 */
Vec2 Chunk_GetRandomTileInRoom(EnvironmentChunk* chunk);

/**
 * @brief Gets a random tile center in the room
 * 
 * @param chunk Pointer to the chunk
 * @return Vec2 Random tile center position
 */
Vec2 Chunk_GetRandomTileCenterInRoom(EnvironmentChunk* chunk);

/**
 * @brief Checks if a chunk index is valid
 * 
 * @param chunkIndex Chunk index to check
 * @return true If the chunk index is valid
 * @return false If the chunk index is not valid
 */
bool Chunk_IsValid(Vec2 chunkIndex);