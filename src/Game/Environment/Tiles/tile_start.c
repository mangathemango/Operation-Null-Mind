#include <tiles.h>
#include <app.h>

void Tile_Start() {
    // Load textures
    for (int i = 0; i < TILE_TYPE_COUNT; i++) {
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

void Tile_Render(EnvironmentTile tile, Vec2 tilePosition) {
    SDL_Rect dest = {
        .x = tilePosition.x * TILE_SIZE_PIXELS,
        .y = tilePosition.y * TILE_SIZE_PIXELS,
        .w = TILE_SIZE_PIXELS,
        .h = TILE_SIZE_PIXELS
    };

    float angle;
    switch (tile.rotation) {
        case TILE_ROTATE_CLOCKWISE:
            angle = 90;
            break;
        case TILE_ROTATE_COUNTERCLOCKWISE:
            angle = -90;
            break;
        case TILE_ROTATE_180:
            angle = 180;
            break;
        case TILE_ROTATE_NONE:
        default:
            angle = 0;
            break;
    }

    SDL_RenderCopyEx(
        app.resources.renderer, 
        tile.texture, 
        NULL, 
        &dest, 
        angle, 
        NULL, 
        SDL_FLIP_NONE
    );
}