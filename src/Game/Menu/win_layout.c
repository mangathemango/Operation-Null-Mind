/**
 * @file win_layout.c
 * @brief Implements the win screen
 *
 * Manages the win screen UI layout, button interactions,
 * and transitions between game and menu states.
 *
 * @author GitHub Copilot
 * @date 2025-04-08
 */

#include <win.h>
#include <UI_text.h>
#include <input.h>
#include <app.h>
#include <sound.h>
#include <game.h>  // Added for game stats
#include <stdio.h> // Added for sprintf function
 
// UI elements for the win screen
static SDL_Texture* diamondFullIcon = NULL;
static UIElement* missionTextElement = NULL;
static UIElement* accomplishedTextElement = NULL;
static UIElement* statisticsTextElement = NULL;

// Statistics elements - reusing the same variables from death_layout.c through EndScreen functions
extern UIElement* floorReachedLabelElement;
extern UIElement* runTimeLabelElement;
extern UIElement* robotsDeactivatedLabelElement;
extern UIElement* healingItemsLabelElement;
extern UIElement* hitsTakenLabelElement;
extern UIElement* ammoSpentLabelElement;

extern UIElement* floorReachedValueElement;
extern UIElement* runTimeValueElement;
extern UIElement* robotsDeactivatedValueElement;
extern UIElement* healingItemsValueElement;
extern UIElement* hitsTakenValueElement;
extern UIElement* ammoSpentValueElement;

// Return to main menu button
static UIElement* returnButtonElement = NULL;
static SDL_Rect returnButtonRect = {0, 0, 130, 30};

/**
 * @brief [Start] Initializes the win screen UI elements
 * 
 * Creates the text elements that make up the win screen,
 * positioning them appropriately on the screen.
 */
void Win_Start() {
    diamondFullIcon = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/diamond_full.png");
    if (!diamondFullIcon) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load diamond full icon: %s", IMG_GetError());
    }
    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color greenColor = {100, 255, 100, 255}; // Green for success!
    
    // Top header text elements
    missionTextElement = UI_CreateText(
        "MISSION", 
        (SDL_Rect) {
            100, 
            30,
            0, 
            0
        }, 
        whiteColor, 
        1.3f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.title1Font
    );

    accomplishedTextElement = UI_CreateText(
        "ACCOMPLISHED", 
        (SDL_Rect) {
            100, 
            65,
            0, 
            0
        }, 
        greenColor, 
        1.3f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.title1Font
    );
    
    int bodyX = 50;
    int valueX = app.config.screen_width - 50;
    
    // Create stats panel
    int statsY = 110;
    EndScreen_CreateStatsPanel("Mission Summary", statsY, bodyX, valueX);
    
    // Return to main menu button at bottom right
    returnButtonRect.x = app.config.screen_width - 150;
    returnButtonRect.y = app.config.screen_height - 40;
    
    returnButtonElement = UI_CreateText(
        "Return to main menu", 
        (SDL_Rect) {
            returnButtonRect.x + returnButtonRect.w/2, 
            returnButtonRect.y + 8, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_CENTER, 
        app.resources.textFont
    );
}
 
/**
 * @brief [PostUpdate] Processes user input for the win screen
 * 
 * Checks for the ESC key press or button clicks to return to the main menu
 */
void Win_Update() {
    static float timer = 0;
    static bool isPlayed = 0;
    timer += Time->deltaTimeSeconds;
    if(timer > 2 && !isPlayed) {
        Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
        isPlayed = 1;
    }

    UI_UpdateText(returnButtonElement);

    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {0, 0, 0, 255};

    if (Input_MouseIsOnRect(returnButtonRect)) {
        UI_ChangeTextColor(returnButtonElement, hoverButtonColor);
        if (!UI_IsHovered(returnButtonElement)) {
            Sound_Play_Effect(SOUND_HOVER);
            UI_SetHovered(returnButtonElement, true);
        }
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MENU;
            Game_Restart();
            Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
            isPlayed = 0;
            timer = 0;
        }
    } else {
        UI_ChangeTextColor(returnButtonElement, defaultButtonColor);
        UI_SetHovered(returnButtonElement, false);
    }

    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_MENU;
        Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
        isPlayed = 0;
        timer = 0;
    }
    
    // Update the statistics with real game stats
    // This only needs to be done once when the win screen is first displayed
    static bool statsUpdated = false;
    if (!statsUpdated) {
        EndScreen_UpdateStats(
            game.currentStage,                 // floor/stage reached
            (int)game.runTime,                 // run time in seconds
            player.stats.enemiesKilled,        // robots deactivated
            game.healingItemsUsed,             // healing items used
            game.hitsTaken,                    // hits taken
            game.ammoSpent                     // ammo spent
        );
        statsUpdated = true;
    }
    
    // Reset the statsUpdated flag when returning to the main menu
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed || 
        (Input_MouseIsOnRect(returnButtonRect) && Input->mouse.leftButton.pressed)) {
        statsUpdated = false;
    }
}
 
/**
 * @brief [Render] Draws the win screen to the screen
 * 
 * Renders the win screen UI elements
 */
void Win_Render() {
    // Background - darker green tint for victory ambiance
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 20, 0, 255);
    SDL_Rect fullScreenRect = {0, 0, app.config.screen_width, app.config.screen_height};
    SDL_RenderFillRect(app.resources.renderer, &fullScreenRect);

    // Check if diamond icon exists and render it
    if (diamondFullIcon) {
        SDL_Rect iconRect = {
            50, 45, 40, 40  // Positioned near the MISSION text
        };
        SDL_RenderCopy(app.resources.renderer, diamondFullIcon, NULL, &iconRect);
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Diamond full icon not available when trying to render");
    }

    // Render header text
    UI_RenderText(missionTextElement);
    UI_RenderText(accomplishedTextElement);

    // Render statistics panel
    SDL_Rect statsHeaderRect = {45, 108, app.config.screen_width - 90, 20};
    EndScreen_RenderStatsPanel(statsHeaderRect);

    // Render return button with hover effect
    if (Input_MouseIsOnRect(returnButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 100, 255, 100, 255);
        SDL_RenderFillRect(app.resources.renderer, &returnButtonRect);
    } else {
        SDL_SetRenderDrawColor(app.resources.renderer, 50, 100, 50, 255);
        SDL_RenderFillRect(app.resources.renderer, &returnButtonRect);
    }
    UI_RenderText(returnButtonElement);
}