#include <game.h>

SDL_Texture* LevelTransition_background = NULL;
static float currentOffset = 0;
static float targetOffset = 0;
void LevelTransition_Start() {
    targetOffset = app.config.screen_height;
}

void LevelTransition_Update() {
    if (game.isTransitioning) {
        targetOffset = 0;
    } else {
        targetOffset = -app.config.screen_height;
    }
    currentOffset += (targetOffset - currentOffset) * 0.1f;
}

void LevelTransition_Render() {
    if (currentOffset <= -app.config.screen_height + 2) {
        return;
    }
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 255);
    SDL_Rect dest = {
        0, 
        currentOffset, 
        app.config.screen_width, 
        app.config.screen_height
    };
    SDL_RenderFillRect(app.resources.renderer, &dest);
}