/**
 * @file map_start.c
 * @brief Initializes the map generation system
 *
 * Sets up the initial map state, generates the first level,
 * and prepares all map-related resources.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <maps.h>
#include <random.h>

void Map_Start() {
    Tile_Start();
    Map_Generate();
}