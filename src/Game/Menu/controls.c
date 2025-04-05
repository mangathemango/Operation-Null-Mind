/**
 * @file controls.c
 * @brief Implements the controls screen for Operation Null Mind
 * 
 * Displays the game control scheme and allows the player to return to the menu
 * 
 * @author Mango
 * @date 2025-04-05
 */

#include <controls.h>
#include <input.h>
#include <sound.h>
#include <app.h>
#include <ui_text.h>

// Global variables for the controls screen
SDL_Texture* Controls_Background = NULL;
UIElement* ControlsText = NULL;
SDL_Rect ControlsTextRectBox;
bool backHovered = false;

/**
 * @brief Initializes the controls screen
 * Loads textures and UI elements needed for the controls screen
 */
void Controls_Start()
{
    // Load background texture
    Controls_Background = IMG_LoadTexture(app.resources.renderer, "Assets/Images/UI/controls.png");
    if (!Controls_Background) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load controls background: %s", IMG_GetError());
    }
    
    // Create back button
    ControlsTextRectBox = (SDL_Rect) {
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
    
    ControlsText = UI_CreateText(
        "Back", 
        textRect, 
        (SDL_Color) {255, 255, 255, 255}, 
        1.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );
}

/**
 * @brief Updates the controls screen state
 * Handles input and interaction with the controls screen
 */
void Controls_Update()
{
    // Handle back button interaction
    if (Input_MouseIsOnRect(ControlsTextRectBox)) {
        backHovered = true;
        UI_ChangeTextColor(ControlsText, (SDL_Color) {0, 0, 0, 255});
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MENU;
        }
    } else {
        backHovered = false;
        UI_ChangeTextColor(ControlsText, (SDL_Color) {255, 255, 255, 255});
    }
    
    // Update UI elements
    UI_UpdateText(ControlsText);
}

/**
 * @brief Renders the controls screen
 * Displays the control scheme and navigation UI
 */
void Controls_Render()
{
    // Draw background
    SDL_Rect dest = (SDL_Rect) {
        0,
        0,
        app.config.screen_width,
        app.config.screen_height
    };
    SDL_RenderCopy(app.resources.renderer, Controls_Background, NULL, &dest);
    
    // Draw back button with hover effect
    if (backHovered) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &ControlsTextRectBox);
    } else {
        SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(app.resources.renderer, &ControlsTextRectBox);
    }
    
    // Render UI text elements
    UI_RenderText(ControlsText);
}