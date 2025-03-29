#include <game.h>
#include <enemy.h>

GameData game = {
    .currentStage = 1,
    .isTransitioning = false,
    .viewingLog = -1,
    .transitionTimer = NULL,
};

void Game_Start() {
    game.transitionTimer = Timer_Create(2.0f);
}

void Game_Update() {
    if (game.isTransitioning) {
        if (!Timer_IsFinished(game.transitionTimer)) return;
        game.isTransitioning = false;
        game.currentStage++;
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
}