#include <tiles.h>
#include <camera.h>
#include <app.h>

void Tile_Render(EnvironmentTile tile, Vec2 tilePosition) {
    if (!tile.texture) return;
    Vec2 screenPos = Camera_WorldToScreen(
        (Vec2){
            tilePosition.x * TILE_SIZE_PIXELS, 
            tilePosition.y * TILE_SIZE_PIXELS
        }
    );

    SDL_Rect dest = {
        .x = screenPos.x,
        .y = screenPos.y,
        .w = TILE_SIZE_PIXELS,
        .h = TILE_SIZE_PIXELS
    };
    if (dest.x > app.config.screen_width || dest.y > app.config.screen_height) return;
    if (dest.x + dest.w < 0 || dest.y + dest.h < 0) return;
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