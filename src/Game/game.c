#include <game.h>

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

void Game_TransitionNextLevel() {
    game.isTransitioning = true;
    Timer_Start(game.transitionTimer);
}