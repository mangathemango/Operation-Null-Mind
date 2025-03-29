#include <game.h>
#include <enemy.h>

bool currentStageIncreased = false;

GameData game = {
    .currentStage = 1,
    .isTransitioning = false,
    .viewingLog = -1,
    .transitionTimer = NULL,
};

void Game_Start() {
    game.transitionTimer = Timer_Create(2.5f);
}

void Game_Update() {
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
    player.state.currentHealth = player.stats.maxHealth;
    Map_Generate(); 
    player.state.position = Chunk_GetChunkCenter(&testMap.chunks[3][3]);
    camera.position = player.state.position;

    for(int i = 0;i < ENEMY_MAX;i++)
    {
        EnemyData* enemy = &enemies[i];
        Enemy_HandleDeath(enemy);
    }
}

void Game_TransitionNextLevel(void* data, int interactableIndex) {
    game.isTransitioning = true;
    Timer_Start(game.transitionTimer);
    currentStageIncreased = false;
}