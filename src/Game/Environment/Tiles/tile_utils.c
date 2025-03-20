#include <maps.h>
#include <math.h>
#include <random.h>

void Tile_FromPixelPoint(Vec2 pixelPoint, Vec2* chunkIndex, Vec2* tileIndex) {
    if (pixelPoint.x < 0 || pixelPoint.y < 0) {
        *chunkIndex = Vec2_Zero;
        *tileIndex = Vec2_Zero;
        return;
    }
    *chunkIndex = Vec2_Divide(pixelPoint, (float) CHUNK_SIZE_PIXEL);
    Vec2 relativePixelPosition = (Vec2) {
        (int) fmod(pixelPoint.x, CHUNK_SIZE_PIXEL),
        (int) fmod(pixelPoint.y, CHUNK_SIZE_PIXEL)
    };
    *tileIndex = Vec2_Divide(relativePixelPosition, (float) TILE_SIZE_PIXELS);
}

bool Tile_IsValid(Vec2 tileIndex) {
    return tileIndex.x >= 0 && tileIndex.x < CHUNK_SIZE_TILE && tileIndex.y >= 0 && tileIndex.y < CHUNK_SIZE_TILE;
}

Vec2 Tile_GetPositionFromPixel(Vec2 pixelPoint) {
    return (Vec2) {
        (int) fmod(pixelPoint.x, CHUNK_SIZE_PIXEL),
        (int) fmod(pixelPoint.y, CHUNK_SIZE_PIXEL)
    };
}

SDL_Rect Tile_GetRectFromPixel(Vec2 pixelPoint) {
    return (SDL_Rect) {
        pixelPoint.x,
        pixelPoint.y,
        TILE_SIZE_PIXELS,
        TILE_SIZE_PIXELS
    };
}

Vec2 Tile_GetRandomPixelInRect(SDL_Rect rect) {
    return (Vec2) {
        RandFloat(rect.x, rect.x + rect.w),
        RandFloat(rect.y, rect.y + rect.h)
    };
}

Vec2 Tile_TileIndexToPixel(Vec2 tileIndex, Vec2 chunkIndex) {
    if (!Chunk_IsValid(chunkIndex) || !Tile_IsValid(tileIndex)) {
        return Vec2_Zero;
    }
    return Vec2_Add(
        Vec2_Multiply(chunkIndex, CHUNK_SIZE_PIXEL), 
        Vec2_Multiply(tileIndex, TILE_SIZE_PIXELS)
    );
}