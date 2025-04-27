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
#include <math.h>
#include <settings.h>

static UIElement* startButtonElement = NULL;
SDL_Rect startButtonRect = {27, 140, 200, 15};
static UIElement* settingsButtonElement = NULL;
SDL_Rect settingsButtonRect = {27, 160, 200, 15};
static UIElement* exitButtonElement = NULL;
SDL_Rect exitButtonRect = {27, 180, 200, 15};
static SDL_Texture* title = NULL;
static SDL_Texture* background = NULL;
Vec2 backgroundSize = {0, 0};

/**
 * @brief [Start] Loads textures and creates UI elements for the menu
 * 
 * Initializes all resources needed for the main menu, including
 * the background, title, and button elements.
 */
void Menu_PrepareTextures() {
    SDL_Color textColor = {255, 255, 255, 255};

    background = IMG_LoadTexture(app.resources.renderer, "Assets/Images/phagen.png");
    if (!background) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load background texture: %s", SDL_GetError());
    }
    int backgroundWidth, backgroundHeight;
    SDL_QueryTexture(background, NULL, NULL, &backgroundWidth, &backgroundHeight);
    backgroundSize.x = backgroundWidth;
    backgroundSize.y = backgroundHeight;
    title = IMG_LoadTexture(app.resources.renderer, "Assets/Images/title.png");
    startButtonElement = UI_CreateText("Start",(SDL_Rect) {35, 140, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    settingsButtonElement = UI_CreateText("Settings", (SDL_Rect) {35, 160, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    exitButtonElement = UI_CreateText("Exit",  (SDL_Rect) {35, 180, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
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

    static bool startButtonHovered = false;
    static bool controlsButtonHovered = false;
    static bool exitButtonHovered = false;
    static bool settingsButtonHovered = false;

    if (Input_MouseIsOnRect(startButtonRect)) {
        UI_ChangeTextColor(startButtonElement, hoverButtonColor);
        if (!startButtonHovered) {
            Sound_Play_Effect(SOUND_HOVER);
            startButtonHovered = true;
        }
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MISSION_BRIEFING;
            Sound_Play_Effect(SOUND_SELECT);
        }
    } else {
        UI_ChangeTextColor(startButtonElement, defaultButtonColor);
        startButtonHovered = false;
    }

    if (Input_MouseIsOnRect(settingsButtonRect)) {
        UI_ChangeTextColor(settingsButtonElement, hoverButtonColor);
        if (!settingsButtonHovered) {
            Sound_Play_Effect(SOUND_HOVER);
            settingsButtonHovered = true;
        }
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_SETTINGS;
            settingsLastScene = SCENE_MENU;
            Sound_Play_Effect(SOUND_SELECT);
        }
    } else {
        UI_ChangeTextColor(settingsButtonElement, defaultButtonColor);
        settingsButtonHovered = false;
    }


    if (Input_MouseIsOnRect(exitButtonRect)) {
        UI_ChangeTextColor(exitButtonElement, hoverButtonColor);
        if (!exitButtonHovered) {
            Sound_Play_Effect(SOUND_HOVER);
            exitButtonHovered = true;
        }
        if (Input->mouse.leftButton.pressed) {
            app.state.running = false;
            Sound_Play_Effect(SOUND_SELECT);
        }
    } else {
        UI_ChangeTextColor(exitButtonElement, defaultButtonColor);
        exitButtonHovered = false;
    }

}

/**
 * @brief [Render] Draws the main menu to the screen
 * 
 * Renders the background, title, and interactive button elements
 * with appropriate hover effects.
 */
void Menu_Render() {
    SDL_Rect backgroundDest = {
        300, 0, backgroundSize.x, backgroundSize.y
    };
    SDL_RenderCopyEx(
        app.resources.renderer, 
        background, 
        NULL, 
        &backgroundDest,
        sin(Time->programElapsedTimeSeconds) * 5,
        &(SDL_Point) {40, -40},
        SDL_FLIP_NONE
    );
    SDL_Rect dest = {
        30, 50, 175, 70
    };
    SDL_RenderCopy(app.resources.renderer, title, NULL, &dest);
    if (Input_MouseIsOnRect(startButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &startButtonRect);
    }
    UI_RenderText(startButtonElement);


    if (Input_MouseIsOnRect(settingsButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &settingsButtonRect);
    }
    UI_RenderText(settingsButtonElement);

    if (Input_MouseIsOnRect(exitButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &exitButtonRect);
    }
    UI_RenderText(exitButtonElement);
}