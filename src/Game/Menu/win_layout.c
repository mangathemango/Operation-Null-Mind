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
        // Play victory music instead of death music
        Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1); // Replace with victory music when available
        isPlayed = 1;
    }
    
    // Update UI elements
    UI_UpdateText(returnButtonElement);
    
    // Handle return button interaction
    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {0, 0, 0, 255}; // Green for win
    
    if (Input_MouseIsOnRect(returnButtonRect)) {
        UI_ChangeTextColor(returnButtonElement, hoverButtonColor);
        if (Input->mouse.leftButton.pressed) {
            app.state.currentScene = SCENE_MENU;
            Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
            isPlayed = 0;
            timer = 0;
        }
    } else {
        UI_ChangeTextColor(returnButtonElement, defaultButtonColor);
    }

    // Also allow ESC key to return to menu
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_MENU;
        Sound_Play_Music("Assets/Audio/Music/mainMenu.wav", -1);
        isPlayed = 0;
        timer = 0;
    }
    
    // For demonstration, update stats with some dynamic values
    // In a real implementation, these would come from game state
    static int demoFloor = 0;
    static int demoTime = 0;
    static int demoRobots = 0;
    
    demoTime += Time->deltaTimeSeconds;
    if ((int)timer % 3 == 0 && (int)timer != 0) {
        demoFloor = player.stats.enemiesKilled / 10 + 1; // +1 because we completed this floor
        demoRobots = player.stats.enemiesKilled;
        EndScreen_UpdateStats(
            demoFloor,            // floor reached
            (int)demoTime,        // run time in seconds
            demoRobots,           // robots deactivated
            2,                    // healing items used (fewer than death screen)
            3,                    // hits taken (fewer than death screen)
            200                   // ammo spent
        );
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