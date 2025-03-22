/**
 * @file tile_start.c
 * @brief Initializes the tile system
 *
 * Loads tile textures and sets up the tile creation system
 * for the game environment.
 *
 * @author Mango
 * @date 2025-03-02
 */

#include <tiles.h>
#include <camera.h>
#include <app.h>

void Tile_Start() {
    // Load textures
    for (int i = 1; i < TILE_TYPE_COUNT; i++) {
        SDL_Surface* surface = IMG_Load(tiles.config.texturePaths[i]);
        if (!surface) {
            SDL_Log("Failed to load image: %s", IMG_GetError());
        }

        tiles.resources.textures[i] = SDL_CreateTextureFromSurface(app.resources.renderer, surface);
        SDL_FreeSurface(surface);
    }
}

EnvironmentTile Tile_Create(TileType type, TileRotation rotation) {
    return (EnvironmentTile) {
        .texture = tiles.resources.textures[type],
        .rotation = rotation
    };
}

