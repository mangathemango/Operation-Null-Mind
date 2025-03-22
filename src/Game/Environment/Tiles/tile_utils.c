#include <maps.h>
#include <math.h>
#include <random.h>

/**
 * [Utility] Converts a pixel position to tile and chunk indices.
 * 
 * Takes a world-space pixel coordinate and determines which tile and chunk it belongs to.
 * 
 * @param pixelPoint The world position in pixels
 * @param chunkIndex Output parameter for the chunk index
 * @param tileIndex Output parameter for the tile index within the chunk
 */
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

/**
 * [Utility] Checks if a tile index is valid within a chunk.
 * 
 * @param tileIndex The tile index to check
 * @return bool True if the tile index is valid, false otherwise
 */
bool Tile_IsValid(Vec2 tileIndex) {
    return tileIndex.x >= 0 && tileIndex.x < CHUNK_SIZE_TILE && tileIndex.y >= 0 && tileIndex.y < CHUNK_SIZE_TILE;
}

/**
 * [Utility] Converts a pixel point to a tile position.
 * 
 * @param pixelPoint The pixel coordinates to convert
 * @return Vec2 The position of the tile that contains the pixel
 */
Vec2 Tile_GetPositionFromPixel(Vec2 pixelPoint) {
    return (Vec2) {
        (int) fmod(pixelPoint.x, CHUNK_SIZE_PIXEL),
        (int) fmod(pixelPoint.y, CHUNK_SIZE_PIXEL)
    };
}

/**
 * [Utility] Gets the rectangle for a tile from a pixel point.
 * 
 * @param pixelPoint The pixel coordinates within the tile
 * @return SDL_Rect The rectangle representing the tile
 */
SDL_Rect Tile_GetRectFromPixel(Vec2 pixelPoint) {
    return (SDL_Rect) {
        pixelPoint.x,
        pixelPoint.y,
        TILE_SIZE_PIXELS,
        TILE_SIZE_PIXELS
    };
}

/**
 * [Utility] Gets a random pixel coordinate within a rectangle.
 * 
 * @param rect The rectangle to get a random point within
 * @return Vec2 A random pixel position inside the rectangle
 */
Vec2 Tile_GetRandomPixelInRect(SDL_Rect rect) {
    return (Vec2) {
        RandFloat(rect.x, rect.x + rect.w),
        RandFloat(rect.y, rect.y + rect.h)
    };
}

/**
 * [Utility] Converts tile and chunk indices to a world pixel position.
 * 
 * @param tileIndex The tile index within the chunk
 * @param chunkIndex The chunk index
 * @return Vec2 The world pixel position
 */
Vec2 Tile_TileIndexToPixel(Vec2 tileIndex, Vec2 chunkIndex) {
    if (!Chunk_IsValid(chunkIndex) || !Tile_IsValid(tileIndex)) {
        return Vec2_Zero;
    }
    return Vec2_Add(
        Vec2_Multiply(chunkIndex, CHUNK_SIZE_PIXEL), 
        Vec2_Multiply(tileIndex, TILE_SIZE_PIXELS)
    );
}