#include <chunks.h>
#include <random.h>

void Chunk_Start() {
    testChunk = Chunk_Create((Vec2) {20, 20}, ROOM_FLOOR_PATTERN_1, HALLWAY_NONE);
}

EnvironmentChunk Chunk_Create(Vec2 roomSize, RoomFloorPattern floorPattern, RoomHallways hallways) {
    EnvironmentChunk chunk = {
        .roomSize = roomSize,
        .hallways = hallways,
        .floorPattern = floorPattern,
        .empty = false
    };

    int roomStartX = (CHUNK_SIZE_TILE - roomSize.x) / 2;
    int roomStartY = (CHUNK_SIZE_TILE - roomSize.y) / 2;
    int roomEndX = roomStartX + roomSize.x;
    int roomEndY = roomStartY + roomSize.y;

    // Generate floor tiles
    for (int x = 0; x < CHUNK_SIZE_TILE; x++) {
        for (int y = 0; y < CHUNK_SIZE_TILE; y++) {
            TileType type = TILE_VOID;
            TileRotation rotation = TILE_ROTATE_NONE;
            if (x >= roomStartX && x < roomEndX && y >= roomStartY && y < roomEndY) {
                switch (floorPattern) {
                    case ROOM_FLOOR_PATTERN_RANDOM:
                        type = RandInt(TILE_FLOOR_1, TILE_FLOOR_VENT_3);
                        break;
                    case ROOM_FLOOR_PATTERN_1:
                        type = TILE_FLOOR_1;
                        break;
                }
            }
            if (x == roomStartX - 1 && (y >= (roomStartY - 2) && y < roomEndY)) {
                type = TILE_WALL_SIDE_BORDER;
                rotation = TILE_ROTATE_COUNTERCLOCKWISE;
            }
            if (x >= roomStartX && x < roomEndX) {
                if (y == roomStartY - 1) type = TILE_WALL_BOTTOM;
                if (y == roomStartY - 2) type = TILE_WALL_TOP;
            }
            chunk.tiles[x][y] = Tile_Create(type, rotation);
        }
    }

    // // Generate colliders
    // for (int x = 0; x < CHUNK_SIZE_TILE; x++) {
    //     for (int y = 0; y < CHUNK_SIZE_TILE; y++) {
    //         Collider* collider = (Collider*) malloc(sizeof(Collider));
    //         collider->hitbox = (SDL_Rect) {
    //             .x = x * TILE_SIZE_PIXELS,
    //             .y = y * TILE_SIZE_PIXELS,
    //             .w = TILE_SIZE_PIXELS,
    //             .h = TILE_SIZE_PIXELS
    //         };
    //         collider->layer = COLLISION_LAYER_ENVIRONMENT;
    //         collider->collidesWith = 0;
    //         collider->active = true;
    //         collider->owner = &chunk;
    //         chunk.colliders[x + y * CHUNK_SIZE_TILE] = collider;
    //         Collider_Register(collider, &chunk);
    //     }

    return chunk;
}