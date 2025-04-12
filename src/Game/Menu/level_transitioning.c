#include <game.h>
#include <stdio.h>

SDL_Texture* LevelTransition_background = NULL;
UIElement* LevelNumberText = NULL;
static float currentOffset = 0;
static float targetOffset = 0;
void LevelTransition_Start() {
    targetOffset = app.config.screen_height;
    LevelNumberText = UI_CreateText(
        "1",
        (SDL_Rect) {
            app.config.screen_width / 2, 
            app.config.screen_height / 2 - 30, 
            app.config.screen_width, 
            app.config.screen_height
        },
        (SDL_Color) {255, 255, 255, 255}, 
        2.0f,
        UI_TEXT_ALIGN_CENTER,
        app.resources.title1Font
    );
    currentOffset = -app.config.screen_height;
}

void LevelTransition_Update() {
    if (game.isTransitioning) {
        targetOffset = 0;
    } else {
        targetOffset = -app.config.screen_height;
    }
    currentOffset += (targetOffset - currentOffset) * 5 * Time->deltaTimeSeconds;

    char levelText[10] = "0";
    snprintf(levelText, sizeof(levelText), "%d", game.currentStage);

    LevelNumberText->rect.y = currentOffset + app.config.screen_height / 2 - LevelNumberText->textureSize.h / 2; 
    UI_ChangeText(LevelNumberText, levelText);
    UI_UpdateText(LevelNumberText);
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

    UI_RenderText(LevelNumberText);
}