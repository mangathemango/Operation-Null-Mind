#include <maps.h>

void Map_Render() {
    for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
        for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
            Chunk_Render(testMap.chunks[x][y]);
        }
    }
}