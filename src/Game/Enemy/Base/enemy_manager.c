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
    if (player.state.insideRoom && !player.state.insideHallway) {
        EnvironmentChunk* chunk = Chunk_GetCurrentChunk(player.state.position);
        chunk->currentEnemyCount = EnemyManage_CountEnemyInChunk(chunk);
        if (chunk->currentEnemyCount <= 0 && chunk->totalEnemyCount <= 0) {
            if (!chunk->inCombat) return;
            chunk->inCombat = false;
            chunk->hallways = Map_GetChunkHallways(*chunk, testMap);
            Chunk_GenerateTilesButVoid(chunk);
            return;
        }
        if (chunk->inCombat) {
            if (chunk->currentEnemyCount > 0) return;
            int spawnCount = RandInt(chunk->totalEnemyCount / 2, chunk->totalEnemyCount);
            for (int i = 0; i < spawnCount; i++) {
                Enemy_Spawn(EchoData, Chunk_GetRandomTileCenterInRoom(chunk));
            }
            return;
        }
        chunk->inCombat = true;
        chunk->hallways = HALLWAY_NONE;
        Chunk_GenerateTilesButVoid(chunk);
    }
}