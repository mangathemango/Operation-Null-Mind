/**
 * @file menu_layout.c
 * @brief Implements the main menu interface
 *
 * Handles layout, rendering, and interactions for the main menu
 * screen, including buttons for starting the game, options, and exit.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <UI_text.h>
#include <app.h>
#include <stdbool.h>
#include <input.h>
#include <sound.h>
#include <controls.h>

static UIElement* startButtonElement = NULL;
SDL_Rect startButtonRect = {27, 140, 200, 15};
static UIElement* controlsButtonElement = NULL;
SDL_Rect controlsButtonRect = {27, 160, 200, 15};
static UIElement* exitButtonElement = NULL;
SDL_Rect exitButtonRect = {27, 180, 200, 15};
static SDL_Texture* title = NULL;
static SDL_Texture* background = NULL;

/**
 * @brief [Start] Loads textures and creates UI elements for the menu
 * 
 * Initializes all resources needed for the main menu, including
 * the background, title, and button elements.
 */
void Menu_PrepareTextures() {
    SDL_Color textColor = {255, 255, 255, 255};

    background = IMG_LoadTexture(app.resources.renderer, "Assets/Images/night_pixel (2).png");
    title = IMG_LoadTexture(app.resources.renderer, "Assets/Images/title.png");
    startButtonElement = UI_CreateText("start",(SDL_Rect) {30, 140, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    controlsButtonElement = UI_CreateText("controls", (SDL_Rect) {30, 160, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    exitButtonElement = UI_CreateText("exit",  (SDL_Rect) {30, 180, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
}

/**
 * @brief [PostUpdate] Processes user input for menu buttons
 * 
 * Handles mouse hover and click events for the menu buttons,
 * changing their appearance and triggering appropriate actions.
 */
void Menu_Update() {
    UI_UpdateText(startButtonElement);
    UI_UpdateText(exitButtonElement);

    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {0, 0, 0, 255};
    
    if (Input_MouseIsOnRect(startButtonRect)) {
        UI_ChangeTextColor(startButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MISSION_BRIEFING;
        }
    } else {
        UI_ChangeTextColor(startButtonElement, defaultButtonColor);
    }


    if (Input_MouseIsOnRect(startButtonRect) && Input->mouse.leftButton.pressed) {
        app.state.currentScene = SCENE_GAME;
        if (game.currentStage < 3) Sound_Play_Music("Assets/Audio/Music/return0 early level music.wav", -1);
        else if (game.currentStage >= 3 && game.currentStage < 7) Sound_Play_Music("Assets/Audio/Music/return0 mid level music.wav", -1);
        else if (game.currentStage >= 7 && game.currentStage < 10) Sound_Play_Music("Assets/Audio/Music/return0 late level music.wav", -1);
        else if (game.currentStage >= 10) Sound_Stop_Music();
      
    if (Input_MouseIsOnRect(controlsButtonRect)) {
        UI_ChangeTextColor(controlsButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_CONTROLS;
            controlLastScene = SCENE_MENU;
        }
    } else {
        UI_ChangeTextColor(controlsButtonElement, defaultButtonColor);
    }

    if (Input_MouseIsOnRect(exitButtonRect)) {
        UI_ChangeTextColor(exitButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.running = false;
        }
    } else {
        UI_ChangeTextColor(exitButtonElement, defaultButtonColor);
    }

}

/**
 * @brief [Render] Draws the main menu to the screen
 * 
 * Renders the background, title, and interactive button elements
 * with appropriate hover effects.
 */
void Menu_Render() {
    SDL_RenderCopy(app.resources.renderer, background, NULL, NULL);
    SDL_Rect dest = {
        30, 50, 175, 70
    };
    SDL_RenderCopy(app.resources.renderer, title, NULL, &dest);
    if (Input_MouseIsOnRect(startButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_Rect rect = {
            27, 140, 200, 15
        };
        SDL_RenderFillRect(app.resources.renderer, &rect);
    }
    UI_RenderText(startButtonElement);

    if (Input_MouseIsOnRect(controlsButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_Rect rect = {
            27, 160, 200, 15
        };
        SDL_RenderFillRect(app.resources.renderer, &rect);
    }
    UI_RenderText(controlsButtonElement);

    if (Input_MouseIsOnRect(exitButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_Rect rect = {
            27, 180, 200, 15
        };
        SDL_RenderFillRect(app.resources.renderer, &rect);
    }
    UI_RenderText(exitButtonElement);
}