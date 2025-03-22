/**
 * @file pause_layout.c
 * @brief Implements the pause menu screen
 *
 * Manages the pause screen UI layout, button interactions,
 * and transitions between game and pause states.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <pause.h>
#include <UI_text.h>
#include <input.h>
#include <app.h>

static UIElement* pauseTextElement = NULL;
static UIElement* resumeTextElement = NULL;

/**
 * @brief [Start] Initializes the pause menu UI elements
 * 
 * Creates the text elements that make up the pause menu screen,
 * positioning them appropriately on the screen.
 */
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

/**
 * @brief [PostUpdate] Processes user input for the pause menu
 * 
 * Checks for the ESC key press to return to the game
 * from the pause menu.
 */
void Pause_Update() {
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_GAME;
    }
}

/**
 * @brief [Render] Draws the pause menu to the screen
 * 
 * Renders the "Paused" header and instructions for resuming
 * the game.
 */
void Pause_Render() {
    UI_RenderText(pauseTextElement);
    UI_RenderText(resumeTextElement);
}