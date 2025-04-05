#include <mission_briefing.h>
#include <input.h>
#include <sound.h>
#include <app.h>

SDL_Texture* Mission_Background = NULL;

void Mission_Start()
{
    Mission_Background = IMG_LoadTexture(app.resources.renderer, "Assets/Images/UI/mission_briefing.png");
    if (!Mission_Background) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load mission briefing background: %s", IMG_GetError());
    }
}

void Mission_Update()
{
    if (Input->mouse.leftButton.pressed) {
        app.state.currentScene = SCENE_GAME;
        if (game.currentStage < 3) Sound_Play_Music("Assets/Audio/Music/return0 early level music.wav", -1);
        else if (game.currentStage >= 3 && game.currentStage < 7) Sound_Play_Music("Assets/Audio/Music/return0 mid level music.wav", -1);
        else if (game.currentStage >= 7) Sound_Play_Music("Assets/Audio/Music/return0 late level music.wav", -1);
        else if (game.currentStage >= 10) Sound_Play_Music("Assets/Audio/Music/return0 boss music.wav", -1);
    }
}

void Mission_Render()
{
    SDL_RenderCopy(app.resources.renderer, Mission_Background, NULL, NULL);
    SDL_RenderPresent(app.resources.renderer);
}