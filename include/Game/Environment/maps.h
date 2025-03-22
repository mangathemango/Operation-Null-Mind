/**
 * @file maps.h
 * @brief Manages game world maps composed of environment chunks.
 * 
 * @author Mango and Darren
 * @date 2025-03-22
 */

#pragma once

#include <SDL.h>
#include <chunks.h>

// Maps are 5 chunks wide and 5 chunks tall
#define MAP_SIZE_CHUNK 8 //im changing this mango
#define MAP_SIZE_TILE (MAP_SIZE_CHUNK * CHUNK_SIZE_TILE)
#define MAP_LENGTH 7

/**
 * @struct EnvironmentMap
 * @brief Represents a game environment map composed of chunks
 * 
 * The map is organized as a grid of environment chunks with defined start and end points,
 * and contains a main path through the map.
 */
typedef struct {
    EnvironmentChunk chunks[MAP_SIZE_CHUNK][MAP_SIZE_CHUNK]; /**< 2D array of environment chunks that make up the map */
    EnvironmentChunk* startChunk; /**< Pointer to the starting chunk of the map */
    EnvironmentChunk* endChunk; /**< Pointer to the ending chunk of the map */
    Vec2 mainPath[MAP_SIZE_CHUNK * MAP_SIZE_CHUNK]; /**< Array of positions representing the main path through the map */
    int mainPathLength; /**< The number of positions in the main path */
} EnvironmentMap;

/**
 * @brief Global test map instance
 */
extern EnvironmentMap testMap;

/**
 * @brief Initialize the map system
 */
void Map_Start();

/**
 * @brief Render the current map
 */
void Map_Render();

/**
 * @brief Generate a new map
 */
void Map_Generate();

/**
 * @brief Set the starting chunk of the map
 * 
 * @param x The x coordinate of the chunk
 * @param y The y coordinate of the chunk
 */
void Map_SetStartChunk(int x, int y);

/**
 * @brief Set the ending chunk of the map
 * 
 * @param x The x coordinate of the chunk
 * @param y The y coordinate of the chunk
 */
void Map_SetEndChunk(int x, int y);

/**
 * @brief Create the main path through the map
 */
void Map_CreateMainPath();

/**
 * @brief Get the hallways configuration for a specific chunk
 * 
 * @param chunk The chunk to get hallways for
 * @param map The map containing the chunk
 * @return RoomHallways The hallways configuration for the chunk
 */
RoomHallways Map_GetChunkHallways(EnvironmentChunk chunk, EnvironmentMap map);