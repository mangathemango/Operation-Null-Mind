#include <mission_briefing.h>
#include <input.h>
#include <sound.h>
#include <app.h>
#include <ui_text.h>

SDL_Texture* Mission_Background = NULL;
UIElement* MissionText = NULL;
SDL_Rect MissionTextRectBox;
bool continueHovered = false;

void Mission_Start()
{
    Mission_Background = IMG_LoadTexture(app.resources.renderer, "Assets/Images/UI/mission_briefing.png");
    if (!Mission_Background) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load mission briefing background: %s", IMG_GetError());
    }
    MissionTextRectBox = (SDL_Rect) {
        app.config.screen_width - 120,
        app.config.screen_height - 44,
        100,
        30
    };
    SDL_Rect textRect = (SDL_Rect) {
        app.config.screen_width - 70,
        app.config.screen_height - 35,
        0,
        0
    };
    MissionText = UI_CreateText(
        "Continue", 
        textRect, 
        (SDL_Color) {255, 255, 255, 255}, 
        1.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );

}

void Mission_Update()
{
    if (Input_MouseIsOnRect(MissionTextRectBox)) {
        UI_ChangeTextColor(MissionText, (SDL_Color) {0, 0, 0, 255});
        if (!UI_IsHovered(MissionText)) {
            Sound_Play_Effect(SOUND_HOVER);
            UI_SetHovered(MissionText, true);
        }
        if (Input->mouse.leftButton.pressed) {
            Game_TransitionNextLevel(NULL, 0); // The parameters do nothing dw
            
            if (game.currentStage < 3) Sound_Play_Music("Assets/Audio/Music/return0 early level music.wav", 0);
            else if (game.currentStage >= 3 && game.currentStage < 7) Sound_Play_Music("Assets/Audio/Music/return0 mid level music.wav", 0);
            else if (game.currentStage >= 7 && game.currentStage < 10) Sound_Play_Music("Assets/Audio/Music/return0 late level music.wav", 0);
            else Sound_Stop_Music();
        }
    } else {
        UI_ChangeTextColor(MissionText, (SDL_Color) {255, 255, 255, 255});
        UI_SetHovered(MissionText, false);
    }
    UI_UpdateText(MissionText);
}

void Mission_Render()
{
    SDL_Rect dest = (SDL_Rect) {
        0,
        0,
        app.config.screen_width,
        app.config.screen_height
    };
    SDL_RenderCopy(app.resources.renderer, Mission_Background, NULL, &dest);

    if (UI_IsHovered(MissionText)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &MissionTextRectBox);
    } else {
        SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(app.resources.renderer, &MissionTextRectBox);
    }
    UI_RenderText(MissionText);
}