#include <pause.h>
#include <UI_text.h>
#include <input.h>
#include <app.h>

static UIElement* pauseTextElement = NULL;
static UIElement* resumeTextElement = NULL;

void Pause_Start() {

    pauseTextElement = UI_CreateText(
        "Paused", 
        (SDL_Rect) {
            app.config.screen_width / 2, 
            app.config.screen_height / 2 - 50, 
            0, 
            0
        }, 
        (SDL_Color){255, 255, 255, 255}, 
        4.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );

    resumeTextElement = UI_CreateText(
        "Press ESC to resume", 
        (SDL_Rect) {
            app.config.screen_width / 2, 
            app.config.screen_height / 2 + 50, 
            0, 
            0
        }, 
        (SDL_Color){255, 255, 255, 255}, 
        1.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );
}

void Pause_Update() {
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_GAME;
    }
}

void Pause_Render() {
    UI_RenderText(pauseTextElement);
    UI_RenderText(resumeTextElement);
}