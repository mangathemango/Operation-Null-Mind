#include <enemy.h>
#include <maps.h>
#include <enemy_types.h>
#include <player.h>
#include <time_system.h>
#include <random.h>

int EnemyManage_CountEnemyInChunk(EnvironmentChunk* chunk) {
    int count = 0;
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!enemies[i].state.isDead && Chunk_GetCurrentChunk(enemies[i].state.position) == chunk) {
            count++;
        }
    }
    return count;
}

void EnemyManager_Update() {
    // Only calls if the player is completely inside a room
    if (!player.state.insideRoom || player.state.insideHallway) return;

    EnvironmentChunk* chunk = Chunk_GetCurrentChunk(player.state.position);
    chunk->currentEnemyCount = EnemyManage_CountEnemyInChunk(chunk);

    /*
    *   There are two enemy counts in this system: currentEnemyCount and totalEnemyCount
    *    - currentEnemyCount: The number of enemies currently in the chunk
    *    - totalEnemyCount: The total number of enemies that will be spawned in the chunk
    *   For example, if a chunk has a totalEnemyCount of 20. 
    *   That means that the player has to defeat a total of 20 enemies to proceed.
    * 
    *   Whenever the player enters a room, enemies will begin to spawn in waves.
    *   Each enemies spawned will increment the currentEnemyCount, and decrement the totalEnemyCount.
    *   And of course, if the enemy dies, currentEnemyCount will decrement.
    * 
    *   An enemy wave will spawn whenever there's no enemy left on the field (aka currentEnemyCount = 0) 
    */

    if (!chunk->inCombat) {
        // Start combat only if there are enemies left in the totalEnemyCount
        if (chunk->totalEnemyCount > 0) {
            chunk->inCombat = true;
            chunk->hallways = HALLWAY_NONE;
            Chunk_GenerateTilesButVoid(chunk);
        }
    }

    if (chunk->inCombat && chunk->currentEnemyCount <= 0) {
        if (chunk->totalEnemyCount > 0) {
            // Spawns in another wave of enemy if there are still enemies left
            int spawnCount = RandInt(chunk->totalEnemyCount / 2, chunk->totalEnemyCount);
            
            for (int i = 0; i < spawnCount; i++) {
                // Each enemy spawn decrements totalEnemyCount btw
                if (chunk->totalEnemyCount <= 0) break;
                chunk->totalEnemyCount--;

                Vec2 spawnPosition = Chunk_GetRandomTileCenterInRoom(chunk);
                Enemy_Spawn(EchoData,spawnPosition);
            }
        } else {
            // Ends the combat if player has killed enough enemies
            chunk->inCombat = false;
            chunk->hallways = Map_GetChunkHallways(*chunk, testMap);
            Chunk_GenerateTilesButVoid(chunk);
        }
    }
}