#include <tiles.h>
#include <camera.h>
#include <app.h>

void Tile_Render(EnvironmentTile tile, Vec2 tilePosition) {
    if (!tile.texture) return;
    SDL_Rect dest = {
        .x = tilePosition.x * TILE_SIZE_PIXELS,
        .y = tilePosition.y * TILE_SIZE_PIXELS,
        .w = TILE_SIZE_PIXELS,
        .h = TILE_SIZE_PIXELS
    };
    dest.x = Camera_WorldToScreen((Vec2) {dest.x, dest.y}).x;
    dest.y = Camera_WorldToScreen((Vec2) {dest.x, dest.y}).y;

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