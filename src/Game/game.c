#include <game.h>
#include <enemy.h>
#include <sound.h>

bool currentStageIncreased = false;

GameData game = {
    .currentStage = 1,
    .isTransitioning = false,
    .viewingLog = -1,
    .transitionTimer = NULL,
    .hudToggled = false,
    .runTime = 0.0f,
    .ammoSpent = 0,
    .hitsTaken = 0,
    .healingItemsUsed = 0
};

void Game_Start() {
    game.transitionTimer = Timer_Create(2.5f);
    // Initialize game stats
    game.runTime = 0.0f;
    game.ammoSpent = 0;
    game.hitsTaken = 0;
    game.healingItemsUsed = 0;
}

void Game_Update() {
    // Update runtime counter
    game.runTime += Time->deltaTimeSeconds;
    
    if (game.isTransitioning) {
        if (Timer_GetTimeLeft(game.transitionTimer) < 1.0f && !currentStageIncreased) {
            SDL_Log("Time Left: %f", Timer_GetTimeLeft(game.transitionTimer));
            game.currentStage++;
            currentStageIncreased = true;
        }
        if (!Timer_IsFinished(game.transitionTimer)) return;
        game.isTransitioning = false;
        Map_Generate(); 
        player.state.position = Chunk_GetChunkCenter(&testMap.chunks[3][3]);
        camera.position = player.state.position;
    }
}

void Game_Restart()
{
    game.isTransitioning = false;
    game.currentStage = 1;
    
    // Reset game stats
    game.runTime = 0.0f;
    game.ammoSpent = 0;
    game.hitsTaken = 0;
    game.healingItemsUsed = 0;
    player.state.currentHealth = player.stats.maxHealth;
    player.state.gunSlots[0] = GUN_PISTOL;
    player.state.gunSlots[1] = -1;
    Map_Generate(); 
    player.state.position = Chunk_GetChunkCenter(&testMap.chunks[3][3]);
    camera.position = player.state.position;
    Sound_Play_Music("Assets/Audio/Music/return0 lofi death music BEGINNING.wav", 1);

    for(int i = 0;i < ENEMY_MAX;i++)
    {
        EnemyData* enemy = &enemies[i];
        Enemy_HandleDeath(enemy);
    }
    player.stats.enemiesKilled = 0;
}

// Game stat helper functions

/**
 * Increments the ammoSpent counter
 * Call this when a bullet is fired
 */
void Game_AddAmmoSpent(int ammoCount) {
    game.ammoSpent+=ammoCount;
}

/**
 * Increments the hitsTaken counter
 * Call this when player takes damage
 */
void Game_AddHitsTaken() {
    game.hitsTaken++;
}

/**
 * Increments the healingItemsUsed counter
 * Call this when player uses a healing item
 */
void Game_AddHealingItemUsed() {
    game.healingItemsUsed++;
}

void Game_TransitionNextLevel(void* data, int interactableIndex) {
    if (game.currentStage == 10) {
        app.state.currentScene = SCENE_WIN;
        return;
    }
    game.isTransitioning = true;
    Timer_Start(game.transitionTimer);
    currentStageIncreased = false;
}