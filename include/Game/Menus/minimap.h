/**
 * @file minimap.h
 * @brief Minimap functionality for the game's navigation system
 * 
 * @author Mango
 * @date 2025-03-22
 */

#pragma once

#include <maps.h>

/** @brief Size of the minimap in pixels */
#define MINIMAP_SIZE 100

/** @brief Size of a chunk on the minimap in pixels */
#define MINIMAP_CHUNK_SIZE 10

/** @brief Size of a room within a chunk on the minimap in pixels */
#define MINIMAP_CHUNK_ROOM_SIZE 6

/** @brief Size of hallways on the minimap in pixels */
#define MINIMAP_CHUNK_HALLWAY_SIZE 2

/** @brief Margin around the minimap */
#define MINIMAP_MARGIN ((MINIMAP_SIZE - (MINIMAP_CHUNK_SIZE * MAP_SIZE_CHUNK)))

/** @brief Color for regular rooms (R,G,B,A) */
#define MINIMAP_ROOM_COLOR 255, 255, 255, 255

/** @brief Color for enemy rooms (R,G,B,A) */
#define MINIMAP_ENEMY_ROOM_COLOR 255, 0, 0, 255

/** @brief Color for special rooms (R,G,B,A) */
#define MINIMAP_SPECIAL_ROOM_COLOR 252, 130, 0, 255

/** @brief Color for the starting room (R,G,B,A) */
#define MINIMAP_START_ROOM_COLOR 0, 255, 0, 255

/** @brief Color for the ending room (R,G,B,A) */
#define MINIMAP_END_ROOM_COLOR 0, 0, 255, 255

/** @brief Color for player indicator on minimap (R,G,B,A) */
#define MINIMAP_PLAYER_COLOR 158, 158, 158, 255

/** @brief Position and size of the minimap on screen */
extern SDL_Rect minimapPosition;

/**
 * @brief Initialize the minimap system
 * 
 * Sets up the initial state of the minimap
 */
void Minimap_Start();

/**
 * @brief Render the complete minimap to the screen
 */
void Minimap_Render();

/**
 * @brief Render a specific chunk on the minimap
 * @param chunk Pointer to the environment chunk to render
 */
void Minimap_RenderChunk(EnvironmentChunk *chunk);

/**
 * @brief Get the hallways connected to a specific chunk
 * @param chunk Pointer to the chunk to analyze
 * @return RoomHallways Structure containing hallway information
 */
RoomHallways Minimap_GetHallways(EnvironmentChunk *chunk);

/**
 * @brief Render a room within a chunk on the minimap
 * @param chunk Pointer to the chunk containing the room
 */
void Minimap_RenderChunkRoom(EnvironmentChunk *chunk);

/**
 * @brief Render hallways for a chunk on the minimap
 * @param chunk Pointer to the chunk whose hallways should be rendered
 */
void Minimap_RenderChunkHallways(EnvironmentChunk* chunk);

/**
 * @brief Determine the appropriate color for a room based on its type
 * @param chunk Pointer to the chunk containing the room
 * @return SDL_Color Color to use for rendering the room
 */
SDL_Color Minimap_GetRoomColor(EnvironmentChunk *chunk);

/**
 * @brief Calculate the position of a chunk on the minimap
 * @param chunk Pointer to the chunk
 * @return Vec2 Position coordinates on the minimap
 */
Vec2 Minimap_GetMinimapChunkPosition(EnvironmentChunk *chunk);

/**
 * @brief Check if a chunk should be visible on the minimap
 * @param chunk Pointer to the chunk to check
 * @return bool true if the chunk should be visible, false otherwise
 */
bool Minimap_ChunkIsVisible(EnvironmentChunk *chunk);