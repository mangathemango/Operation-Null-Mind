#pragma once

#include <maps.h>
#define MINIMAP_SIZE 100
#define MINIMAP_CHUNK_SIZE 10
#define MINIMAP_CHUNK_ROOM_SIZE 6
#define MINIMAP_CHUNK_HALLWAY_SIZE 2
#define MINIMAP_MARGIN ((MINIMAP_SIZE - (MINIMAP_CHUNK_SIZE * MAP_SIZE_CHUNK)))

#define MINIMAP_ROOM_COLOR 255, 255, 255, 255
#define MINIMAP_ENEMY_ROOM_COLOR 255, 0, 0, 255
#define MINIMAP_SPECIAL_ROOM_COLOR 255, 255, 0, 255
#define MINIMAP_START_ROOM_COLOR 0, 255, 0, 255
#define MINIMAP_END_ROOM_COLOR 0, 0, 255, 255
#define MINIMAP_PLAYER_COLOR 158, 158, 158, 255

extern SDL_Rect minimapPosition;
void Minimap_Start();
void Minimap_Render();
void Minimap_RenderChunk(EnvironmentChunk *chunk);
RoomHallways Minimap_GetHallways(EnvironmentChunk *chunk);
void Minimap_RenderChunkRoom(EnvironmentChunk *chunk);
void Minimap_RenderChunkHallways(EnvironmentChunk* chunk);
SDL_Color Minimap_GetRoomColor(EnvironmentChunk *chunk);
Vec2 Minimap_GetMinimapChunkPosition(EnvironmentChunk *chunk);
bool Minimap_ChunkIsVisible(EnvironmentChunk *chunk);