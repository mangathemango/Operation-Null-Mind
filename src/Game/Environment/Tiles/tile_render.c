#include <tiles.h>
#include <camera.h>
#include <app.h>

void Tile_Render(EnvironmentTile tile, Vec2 tilePosition) {
    if (!tile.texture) return;
    Vec2 tileWorldPos = Vec2_Multiply(tilePosition, TILE_SIZE_PIXELS);
    Vec2 tileSize = (Vec2) {TILE_SIZE_PIXELS, TILE_SIZE_PIXELS}; 
    
    SDL_Rect worldDest = Vec2_ToRect(tileWorldPos, tileSize);

    if (!Camera_RectIsOnScreen(worldDest)) return;

    Vec2 tileScreenPos = Camera_WorldVecToScreen(tileWorldPos);
    SDL_Rect screenDest = Vec2_ToRect(tileScreenPos, tileSize);

    float angle;
    switch (tile.rotation) {
        case TILE_ROTATE_CLOCKWISE:         angle = 90;     break;
        case TILE_ROTATE_COUNTERCLOCKWISE:  angle = -90;    break;
        case TILE_ROTATE_180:               angle = 180;    break;
        case TILE_ROTATE_NONE:  default:    angle = 0;      break; 
    }

    SDL_RenderCopyEx(
        app.resources.renderer, 
        tile.texture, 
        NULL, 
        &screenDest, 
        angle, 
        NULL, 
        SDL_FLIP_NONE
    );
}