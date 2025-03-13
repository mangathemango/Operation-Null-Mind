#include <tiles.h>

EnvironmentTileData tiles = {
    .resources = {
        .textures = {
            [TILE_FLOOR_1] = NULL,
            [TILE_FLOOR_2] = NULL,
            [TILE_FLOOR_3] = NULL,
            [TILE_FLOOR_VENT_1] = NULL,
            [TILE_FLOOR_VENT_2] = NULL,
            [TILE_FLOOR_VENT_3] = NULL,
            [TILE_FLOOR_SCRATCHED_1] = NULL,
            [TILE_FLOOR_SCRATCHED_2] = NULL,
            [TILE_FLOOR_SCRATCHED_3] = NULL,
            [TILE_WALL_TOP] = NULL,
            [TILE_WALL_BOTTOM] = NULL,
            [TILE_WALL_CORNER_BORDER] = NULL,
            [TILE_WALL_SIDE_BORDER] = NULL,
        }
    },
    .config = {
        .texturePaths = {
            [TILE_FLOOR_1] = "Assets/Images/Tiles/Floor/floor_1.png",
            [TILE_FLOOR_2] = "Assets/Images/Tiles/Floor/floor_2.png",
            [TILE_FLOOR_3] = "Assets/Images/Tiles/Floor/floor_3.png",
            [TILE_FLOOR_VENT_1] = "Assets/Images/Tiles/Floor/floor_vent_1.png",
            [TILE_FLOOR_VENT_2] = "Assets/Images/Tiles/Floor/floor_vent_2.png",
            [TILE_FLOOR_VENT_3] = "Assets/Images/Tiles/Floor/floor_vent_3.png",
            [TILE_FLOOR_SCRATCHED_1] = "Assets/Images/Tiles/Floor/floor_scratched_1.png",
            [TILE_FLOOR_SCRATCHED_2] = "Assets/Images/Tiles/Floor/floor_scratched_2.png",
            [TILE_FLOOR_SCRATCHED_3] = "Assets/Images/Tiles/Floor/floor_scratched_3.png",
            [TILE_WALL_TOP] = "Assets/Images/Tiles/Wall/wall_top.png",
            [TILE_WALL_BOTTOM] = "Assets/Images/Tiles/Wall/wall_bottom.png",
            [TILE_WALL_CORNER_BORDER] = "Assets/Images/Tiles/Wall/wall_corner_border.png",
            [TILE_WALL_SIDE_BORDER] = "Assets/Images/Tiles/Wall/wall_side_border.png"
        }
    }
};