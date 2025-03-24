/**
 * @file minimap.c
 * @brief Implements the minimap display system
 *
 * Provides a visual representation of the map layout,
 * player position, and discovered areas during gameplay.
 *
 * @author Mango
 * @date 2025-03-06
 */

#include <maps.h>
#include <app.h>
#include <minimap.h>

SDL_Rect minimapPosition = {0, 0, 0, 0};
SDL_Texture* playerIndicator = NULL;

/**
 * @brief [Start] Initializes the minimap system
 * 
 * Sets up the minimap's position on screen and loads
 * the player indicator texture.
 */
void Minimap_Start() {
    minimapPosition = (SDL_Rect) {
        app.config.screen_width - MINIMAP_SIZE - 10,
        10,
        MINIMAP_SIZE,
        MINIMAP_SIZE
    };
    playerIndicator = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Tiles/player-minimap.png");
}

/**
 * @brief [Render] Renders the minimap to the screen
 * 
 * Draws the background and all visible chunks on the minimap,
 * representing the explored and visible parts of the game world.
 */
void Minimap_Render() {
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 100);
    SDL_RenderFillRect(app.resources.renderer, &minimapPosition);
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            EnvironmentChunk* chunk = &testMap.chunks[x][y];
            if (!Minimap_ChunkIsVisible(chunk) || chunk->empty) continue;
            Minimap_RenderChunk(chunk);
        }
    }
}

/**
 * @brief [Render] Renders a specific chunk on the minimap
 * 
 * Renders both the room and hallways of a chunk
 * on the minimap if they're visible.
 * 
 * @param chunk Pointer to the chunk to render
 */
void Minimap_RenderChunk(EnvironmentChunk *chunk) {
    Minimap_RenderChunkRoom(chunk);
    Minimap_RenderChunkHallways(chunk);
}

/**
 * @brief [Render] Renders a room on the minimap
 * 
 * Draws a room with appropriate colors based on its type
 * and adds a player indicator if the player is in this room.
 * 
 * @param chunk Pointer to the chunk containing the room
 */
void Minimap_RenderChunkRoom(EnvironmentChunk *chunk) {
    Vec2 roomPosition = Minimap_GetMinimapChunkPosition(chunk);
    SDL_Rect roomRect = Vec2_ToCenteredRect(
        roomPosition, 
        (Vec2) {
            MINIMAP_CHUNK_ROOM_SIZE, 
            MINIMAP_CHUNK_ROOM_SIZE
        }   
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &roomRect);
    SDL_Color innerColor = Minimap_GetRoomColor(chunk);
    SDL_Rect innerRect = Vec2_ToCenteredRect(
        roomPosition, 
        (Vec2) {
            MINIMAP_CHUNK_ROOM_SIZE - 2, 
            MINIMAP_CHUNK_ROOM_SIZE - 2
        }   
    );
    SDL_SetRenderDrawColor(app.resources.renderer, innerColor.r, innerColor.g, innerColor.b, innerColor.a);
    SDL_RenderFillRect(app.resources.renderer, &innerRect);

    if (Chunk_GetCurrentChunk(player.state.position) == chunk) {
        SDL_Rect playerRect = Vec2_ToCenteredRect(
            roomPosition, 
            (Vec2) {
                MINIMAP_CHUNK_SIZE, 
                MINIMAP_CHUNK_SIZE
            }   
        );
        SDL_RenderCopy(
            app.resources.renderer,
            playerIndicator,
            NULL,
            &playerRect
        );
    }
}

/**
 * @brief [Render] Renders hallways for a chunk on the minimap
 * 
 * Draws the hallway connections from a room to adjacent rooms
 * in each valid direction.
 * 
 * @param chunk Pointer to the chunk containing the hallways
 */
void Minimap_RenderChunkHallways(EnvironmentChunk* chunk) {
    RoomHallways hallways = Minimap_GetHallways(chunk);
    Vec2 chunkPosition = Minimap_GetMinimapChunkPosition(chunk);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);

    SDL_Rect hallwayRect;
    if (hallways & HALLWAY_UP) {
        hallwayRect = Vec2_ToCenteredRect(
            (Vec2) {
                chunkPosition.x, 
                chunkPosition.y - MINIMAP_CHUNK_ROOM_SIZE/ 2 - MINIMAP_CHUNK_HALLWAY_SIZE / 2
            },
            (Vec2) {
                MINIMAP_CHUNK_HALLWAY_SIZE, 
                MINIMAP_CHUNK_HALLWAY_SIZE
            }
        );
        SDL_RenderFillRect(app.resources.renderer, &hallwayRect);
    }
    if (hallways & HALLWAY_DOWN) {
        hallwayRect = Vec2_ToCenteredRect(
            (Vec2) {
                chunkPosition.x, 
                chunkPosition.y + MINIMAP_CHUNK_ROOM_SIZE/ 2 + MINIMAP_CHUNK_HALLWAY_SIZE / 2
            },
            (Vec2) {
                MINIMAP_CHUNK_HALLWAY_SIZE, 
                MINIMAP_CHUNK_HALLWAY_SIZE
            }
        );
        SDL_RenderFillRect(app.resources.renderer, &hallwayRect);
    }
    if (hallways & HALLWAY_LEFT) {
        hallwayRect = Vec2_ToCenteredRect(
            (Vec2) {
                chunkPosition.x - MINIMAP_CHUNK_ROOM_SIZE / 2 -  MINIMAP_CHUNK_HALLWAY_SIZE / 2, 
                chunkPosition.y
            },
            (Vec2) {
                MINIMAP_CHUNK_HALLWAY_SIZE, 
                MINIMAP_CHUNK_HALLWAY_SIZE
            }
        );
        SDL_RenderFillRect(app.resources.renderer, &hallwayRect);
    }
    if (hallways & HALLWAY_RIGHT) {
        hallwayRect = Vec2_ToCenteredRect(
            (Vec2) {
                chunkPosition.x + MINIMAP_CHUNK_HALLWAY_SIZE / 2 + MINIMAP_CHUNK_ROOM_SIZE / 2, 
                chunkPosition.y
            },
            (Vec2) {
                MINIMAP_CHUNK_HALLWAY_SIZE, 
                MINIMAP_CHUNK_HALLWAY_SIZE
            }
        );
        SDL_RenderFillRect(app.resources.renderer, &hallwayRect);
    }
}

/**
 * @brief [Utility] Determines the color of a room on the minimap
 * 
 * Returns a color based on the room type and state, such as
 * whether it contains enemies or is a special room type.
 * 
 * @param chunk Pointer to the chunk containing the room
 * @return SDL_Color The color to use for the room
 */
SDL_Color Minimap_GetRoomColor(EnvironmentChunk *chunk) {
    switch (chunk->roomType) {
        case ROOM_TYPE_NORMAL:
            if (chunk->totalEnemyCount > 0 || chunk->currentEnemyCount > 0) 
                return (SDL_Color) {MINIMAP_ENEMY_ROOM_COLOR};
            else 
                return (SDL_Color) {MINIMAP_ROOM_COLOR};
        case ROOM_TYPE_BOSS:
            return (SDL_Color) {MINIMAP_SPECIAL_ROOM_COLOR};
        case ROOM_TYPE_START:
            return (SDL_Color) {MINIMAP_START_ROOM_COLOR};
        case ROOM_TYPE_END:
            return (SDL_Color) {MINIMAP_END_ROOM_COLOR};
        default:
            return (SDL_Color) {0, 0, 0, 0};
    }
}

/**
 * @brief [Utility] Converts chunk position to minimap screen position
 * 
 * Calculates the screen coordinates for a chunk on the minimap.
 * 
 * @param chunk Pointer to the chunk
 * @return Vec2 Position of the chunk on the minimap
 */
Vec2 Minimap_GetMinimapChunkPosition(EnvironmentChunk *chunk) {
    Vec2 chunkPosition = chunk->position;
    Vec2 roomPosition = (Vec2) {
        minimapPosition.x + MINIMAP_MARGIN + chunkPosition.x * MINIMAP_CHUNK_SIZE,
        minimapPosition.y + MINIMAP_MARGIN + chunkPosition.y * MINIMAP_CHUNK_SIZE
    };
    return Vec2_ToCenteredPosition(
        roomPosition, 
        (Vec2) {MINIMAP_CHUNK_ROOM_SIZE, MINIMAP_CHUNK_ROOM_SIZE}
    );
}

/**
 * @brief [Utility] Gets the visible hallway connections for a chunk
 * 
 * Determines which hallways should be drawn on the minimap based on
 * the visibility of adjacent chunks.
 * 
 * @param chunk Pointer to the chunk
 * @return RoomHallways Bitmask of visible hallway directions
 */
RoomHallways Minimap_GetHallways(EnvironmentChunk *chunk) {
    Vec2 chunkPosition = chunk->position;
    RoomHallways hallways = HALLWAY_NONE;
    if (chunkPosition.y > 0) {
        EnvironmentChunk* topChunk = &testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y - 1];
        if (topChunk && !topChunk->empty && Minimap_ChunkIsVisible(topChunk)) {
            hallways |= HALLWAY_UP;
        }
    }
    if (chunkPosition.y < MAP_SIZE_CHUNK - 1) {
        EnvironmentChunk* bottomChunk = &testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y + 1];
        if (bottomChunk && !bottomChunk->empty && Minimap_ChunkIsVisible(bottomChunk)) {
            hallways |= HALLWAY_DOWN;
        }
    }
    if (chunkPosition.x > 0) {
        EnvironmentChunk* leftChunk = &testMap.chunks[(int) chunkPosition.x - 1][(int) chunkPosition.y];
        if (leftChunk && !leftChunk->empty && Minimap_ChunkIsVisible(leftChunk)) {
            hallways |= HALLWAY_LEFT;
        }
    }
    if (chunkPosition.x < MAP_SIZE_CHUNK - 1) {
        EnvironmentChunk* rightChunk = &testMap.chunks[(int) chunkPosition.x + 1][(int) chunkPosition.y];
        if (rightChunk && !rightChunk->empty && Minimap_ChunkIsVisible(rightChunk)) {
            hallways |= HALLWAY_RIGHT;
        }
    }
    return hallways;
}

/**
 * @brief [Utility] Determines if a chunk should be visible on the minimap
 * 
 * A chunk is visible if it's discovered or adjacent to a discovered chunk.
 * 
 * @param chunk Pointer to the chunk to check
 * @return bool True if the chunk should be visible on the minimap
 */
bool Minimap_ChunkIsVisible(EnvironmentChunk *chunk) {
    if (chunk->discovered) return true;
    Vec2 chunkPosition = chunk->position;
    if (chunkPosition.y > 0) {
        EnvironmentChunk* topChunk = &testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y - 1];
        if (topChunk && topChunk->discovered) return true;
    }
    if (chunkPosition.y < MAP_SIZE_CHUNK - 1) {
        EnvironmentChunk* bottomChunk = &testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y + 1];
        if (bottomChunk && bottomChunk->discovered) return true;
    }
    if (chunkPosition.x > 0) {
        EnvironmentChunk* leftChunk = &testMap.chunks[(int) chunkPosition.x - 1][(int) chunkPosition.y];
        if (leftChunk && leftChunk->discovered) return true;
    }
    if (chunkPosition.x < MAP_SIZE_CHUNK - 1) {
        EnvironmentChunk* rightChunk = &testMap.chunks[(int) chunkPosition.x + 1][(int) chunkPosition.y];
        if (rightChunk && rightChunk->discovered) return true;
    }
    return false;
}