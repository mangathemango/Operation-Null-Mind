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
#include <controls.h>

static UIElement* pauseTextElement = NULL;
static UIElement* continueButtonElement = NULL;
static UIElement* controlsButtonElement = NULL;
static UIElement* exitButtonElement = NULL;

// Define button rectangles for collision detection
static SDL_Rect continueButtonRect = {27, 140, 200, 15}; 
static SDL_Rect controlsButtonRect = {27, 160, 200, 15};
static SDL_Rect exitButtonRect = {27, 180, 200, 15};

/**
 * @brief [Start] Initializes the pause menu UI elements
 * 
 * Creates the text elements that make up the pause menu screen,
 * positioning them appropriately on the screen.
 */
void Pause_Start() {
    SDL_Color textColor = {255, 255, 255, 255};
    
    pauseTextElement = UI_CreateText(
        "Paused", 
        (SDL_Rect) {
            40, 
            app.config.screen_height / 2 - 80, 
            0, 
            0
        }, 
        textColor, 
        4.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );

    // Create button text elements aligned to the left
    continueButtonElement = UI_CreateText(
        "continue", 
        (SDL_Rect) {
            40, 
            140, 
            0, 
            0
        }, 
        textColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    controlsButtonElement = UI_CreateText(
        "controls", 
        (SDL_Rect) {
            40, 
            160, 
            0, 
            0
        }, 
        textColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    exitButtonElement = UI_CreateText(
        "exit to main menu", 
        (SDL_Rect) {
            40, 
            180, 
            0, 
            0
        }, 
        textColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
}

/**
 * @brief [PostUpdate] Processes user input for the pause menu
 * 
 * Checks for button interactions and keyboard input to handle
 * actions like resuming the game, viewing controls, or returning 
 * to the main menu.
 */
void Pause_Update() {
    // Default and hover colors for buttons
    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {0, 0, 0, 255};
    
    // Update text elements
    UI_UpdateText(continueButtonElement);
    UI_UpdateText(controlsButtonElement);
    UI_UpdateText(exitButtonElement);
    
    // Continue button hover and click
    if (Input_MouseIsOnRect(continueButtonRect)) {
        UI_ChangeTextColor(continueButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_GAME;
        }
    } else {
        UI_ChangeTextColor(continueButtonElement, defaultButtonColor);
    }
    
    // Controls button hover and click
    if (Input_MouseIsOnRect(controlsButtonRect)) {
        UI_ChangeTextColor(controlsButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_CONTROLS;
            controlLastScene = SCENE_PAUSE;
        }
    } else {
        UI_ChangeTextColor(controlsButtonElement, defaultButtonColor);
    }
    
    // Exit button hover and click
    if (Input_MouseIsOnRect(exitButtonRect)) {
        UI_ChangeTextColor(exitButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MENU;
            Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
        }
    } else {
        UI_ChangeTextColor(exitButtonElement, defaultButtonColor);
    }
    
    // Keyboard shortcut for continue
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_GAME;
    }
}

/**
 * @brief [Render] Draws the pause menu to the screen
 * 
 * Renders the "Paused" header and buttons with appropriate hover effects.
 */
void Pause_Render() {
    // Semi-transparent overlay
    SDL_Rect dest = {
        0,
        0,
        app.config.screen_width, 
        app.config.screen_height
    };
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 150);
    SDL_RenderFillRect(app.resources.renderer, &dest);
    
    // Render pause title
    UI_RenderText(pauseTextElement);
    
    // Render buttons with hover effects
    if (Input_MouseIsOnRect(continueButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_Rect rect = {
            27, 140, 200, 15
        };
        SDL_RenderFillRect(app.resources.renderer, &rect);
    }
    UI_RenderText(continueButtonElement);
    
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

    SDL_Rect destRect = {
        297, 80, 40, 120
    };
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &destRect);

    SDL_Rect destRect2 = {
        357, 80, 40, 120
    };
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &destRect2);
}