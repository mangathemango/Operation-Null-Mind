#include <settings.h>
#include <input.h>
#include <app.h>

UIElement* settingsTextElement = NULL;
UIElement* backButtonElement = NULL;
SDL_Rect backButtonRect = {27, 140, 200, 15};

UIElement* volumeTextElement = NULL;

UIElement* masterVolumeText;
SDL_Rect masterVolumeSliderRect = {27, 160, 200, 15};

UIElement* sfxVolumeText;
SDL_Rect sfxVolumeSliderRect = {27, 180, 200, 15};

UIElement* musicVolumeText;
SDL_Rect musicVolumeSliderRect = {27, 200, 200, 15};


void Settings_Start() {

}

void Settings_Update() {
    if (Input->mouse.leftButton.pressed) {
        app.state.currentScene = SCENE_MENU;
    }
}

void Settings_Render() {
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &masterVolumeSliderRect);
    SDL_RenderFillRect(app.resources.renderer, &sfxVolumeSliderRect);
    SDL_RenderFillRect(app.resources.renderer, &musicVolumeSliderRect);
}