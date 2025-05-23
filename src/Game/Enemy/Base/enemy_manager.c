/**
 * @file enemy_manager.c
 * @brief Manages enemy spawning and room encounters
 *
 * Handles room-based enemy spawning, wave generation,
 * and combat state transitions for the player.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <enemy.h>
#include <maps.h>
#include <enemy_types.h>
#include <player.h>
#include <time_system.h>
#include <random.h>

/**
 * @brief [Utility] Counts the number of active enemies in a specific chunk
 *
 * @param chunk Pointer to the chunk to check
 * @return int Number of active enemies in the chunk
 */
int EnemyManage_CountEnemyInChunk(EnvironmentChunk* chunk) {
    int count = 0;
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!enemies[i].state.isDead && Chunk_GetCurrentChunk(enemies[i].state.position) == chunk) {
            count++;
        }
    }
    return count;
}

float currentClearTextAlpha = 0;

/**
 * @brief [PostUpdate] Updates the enemy management system
 * 
 * Handles enemy spawning, despawning, and room transitions.
 * Manages which enemies are active based on player position.
 */
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
            if (chunk->roomType == ROOM_TYPE_BOSS) {
                Sound_Play_Music("Assets/Audio/Music/return0 boss music.wav", 0);
            }

            chunk->totalEnemyCount = RandInt(
                EnemyComps[game.currentStage - 1].enemyMinSpawnCount,
                EnemyComps[game.currentStage - 1].enemyMaxSpawnCount
            );
            Enemy_ResetComp(&EnemyComps[game.currentStage - 1]);
        }
    }

    if (chunk->inCombat && chunk->currentEnemyCount <= 0) {
        if (chunk->totalEnemyCount > 0) {
            Enemy_SpawnWave(chunk);  
        } else {
            // Ends the combat if player has killed enough enemies
            chunk->inCombat = false;
            chunk->hallways = Map_GetChunkHallways(*chunk, testMap);
            Chunk_GenerateTilesButVoid(chunk);
            currentClearTextAlpha = 255;
            Enemy_ResetComp(&EnemyComps[game.currentStage - 1]);
            if (chunk->roomType == ROOM_TYPE_BOSS) {
                Sound_Clear_Queue();
                Sound_Stop_Music();
                Sound_Clear_Queue();
            }
        }
    }
    
    

    static float funnyTimer = 0;
    if (chunk->inCombat && player.state.currentAmmo <= player.state.currentGun.stats.ammoConsumption) {
        funnyTimer += Time->deltaTimeSeconds;
        if (funnyTimer >= 0.5f) {
            Vec2 spawnPosition = Chunk_GetRandomTileCenterInRoom(chunk);
            Enemy_Spawn(*enemyList[ENEMY_TYPE_KAMIKAZE], spawnPosition);
            funnyTimer = 0;
        }
    }

    if (chunk->currentEnemyCount <= 0 && chunk->totalEnemyCount <= 0 && !chunk->inCombat) {
        chunk->discovered = true;
    }
}

void EnemyManager_RenderClearText() {
    static UIElement* clearText = NULL;
    if (clearText == NULL) {
        clearText = UI_CreateText(
            "CLEAR",
            (SDL_Rect) {
                app.config.screen_width / 2,
                50
            },
            (SDL_Color){255, 255, 255, 0},
            1.0f,
            UI_TEXT_ALIGN_CENTER,
            app.resources.title1Font
        );
    }
    
    if (currentClearTextAlpha > 0) {
        // Ensure alpha decreases consistently and reaches 0
        currentClearTextAlpha -= 255 * Time->deltaTimeSeconds; // Adjusted to scale with time
        if (currentClearTextAlpha < 0) currentClearTextAlpha = 0; // Clamp to 0
    }

    UI_UpdateText(clearText);
    SDL_SetTextureAlphaMod(((UI_TextData*) (clearText->data))->textTexture, (int) currentClearTextAlpha);
    UI_RenderText(clearText);
}