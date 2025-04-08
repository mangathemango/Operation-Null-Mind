/**
 * @file death_layout.c
 * @brief Implements the death screen
 *
 * Manages the death screen UI layout, button interactions,
 * and transitions between game and pause states.
 * 
 * @author Darren
 * @date 2025-03-28
 */

#include <death.h>
#include <UI_text.h>
#include <input.h>
#include <app.h>
#include <sound.h>
 
// UI elements for the death screen
static SDL_Texture* diamondPartialIcon = NULL;
static UIElement* missionTextElement = NULL;
static UIElement* failedTextElement = NULL;
static UIElement* statisticsTextElement = NULL;

// Statistics elements
static UIElement* floorReachedLabelElement = NULL;
static UIElement* runTimeLabelElement = NULL;
static UIElement* robotsDeactivatedLabelElement = NULL;
static UIElement* healingItemsLabelElement = NULL;
static UIElement* hitsTakenLabelElement = NULL;
static UIElement* ammoSpentLabelElement = NULL;

// Stat values
static UIElement* floorReachedValueElement = NULL;
static UIElement* runTimeValueElement = NULL;
static UIElement* robotsDeactivatedValueElement = NULL;
static UIElement* healingItemsValueElement = NULL;
static UIElement* hitsTakenValueElement = NULL;
static UIElement* ammoSpentValueElement = NULL;

// Return to main menu button
static UIElement* returnButtonElement = NULL;
static SDL_Rect returnButtonRect = {0, 0, 130, 40};

/**
 * @brief Updates the statistics values on the end screen
 * 
 * @param floorValue The floor/level reached by the player
 * @param timeValue The time in seconds the run lasted
 * @param robotsValue The number of robots deactivated during the run
 * @param healingValue The number of healing items used during the run
 * @param hitsValue The number of hits taken by the player
 * @param ammoValue The amount of ammunition spent during the run
 */
void EndScreen_UpdateStats(int floorValue, int timeValue, int robotsValue, int healingValue, int hitsValue, int ammoValue) {
    // Update statistic values
    char valueText[20];
    
    sprintf(valueText, "%d", floorValue);
    UI_ChangeText(floorReachedValueElement, valueText);
    
    // Format time as mm:ss
    int minutes = timeValue / 60;
    int seconds = timeValue % 60;
    sprintf(valueText, "%02d:%02d", minutes, seconds);
    UI_ChangeText(runTimeValueElement, valueText);
    
    sprintf(valueText, "%d", robotsValue);
    UI_ChangeText(robotsDeactivatedValueElement, valueText);
    
    sprintf(valueText, "%d", healingValue);
    UI_ChangeText(healingItemsValueElement, valueText);
    
    sprintf(valueText, "%d", hitsValue);
    UI_ChangeText(hitsTakenValueElement, valueText);
    
    sprintf(valueText, "%d", ammoValue);
    UI_ChangeText(ammoSpentValueElement, valueText);
}

/**
 * @brief Creates the statistics panel UI elements
 * 
 * @param titleText The text to display in the statistics header (e.g., "Statistics")
 * @param startY The Y position to start rendering the statistics panel
 * @param bodyX The X position for labels
 * @param valueX The X position for values (right-aligned)
 * @return The Y position after the last statistic row
 */
int EndScreen_CreateStatsPanel(const char* titleText, int startY, int bodyX, int valueX) {
    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color blackColor = {0, 0, 0, 255};
    int statsStartY = startY + 20;
    int statsSpacing = 15;
    
    // Create statistics header
    statisticsTextElement = UI_CreateText(
        titleText, 
        (SDL_Rect) {
            bodyX,
            startY, 
            0, 
            0
        }, 
        blackColor, 
        1.5f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    // Create statistics labels
    floorReachedLabelElement = UI_CreateText(
        "Floor Reached", 
        (SDL_Rect) {
            bodyX, 
            statsStartY, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    runTimeLabelElement = UI_CreateText(
        "Run Time", 
        (SDL_Rect) {
            bodyX, 
            statsStartY + statsSpacing, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    robotsDeactivatedLabelElement = UI_CreateText(
        "Robots Deactivated", 
        (SDL_Rect) {
            bodyX, 
            statsStartY + statsSpacing * 2, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    healingItemsLabelElement = UI_CreateText(
        "Healing Items Used", 
        (SDL_Rect) {
            bodyX, 
            statsStartY + statsSpacing * 3, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    hitsTakenLabelElement = UI_CreateText(
        "Hits Taken", 
        (SDL_Rect) {
            bodyX, 
            statsStartY + statsSpacing * 4, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    ammoSpentLabelElement = UI_CreateText(
        "Ammo Spent", 
        (SDL_Rect) {
            bodyX, 
            statsStartY + statsSpacing * 5, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.textFont
    );
    
    // Create statistics values (right side)
    floorReachedValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    runTimeValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY + statsSpacing, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    robotsDeactivatedValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY + statsSpacing * 2, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    healingItemsValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY + statsSpacing * 3, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    hitsTakenValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY + statsSpacing * 4, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    ammoSpentValueElement = UI_CreateText(
        "0", 
        (SDL_Rect) {
            valueX, 
            statsStartY + statsSpacing * 5, 
            0, 
            0
        }, 
        whiteColor, 
        1.0f, 
        UI_TEXT_ALIGN_RIGHT, 
        app.resources.textFont
    );
    
    return statsStartY + statsSpacing * 6; // Return position after last stats row
}

/**
 * @brief Renders the statistics panel
 * 
 * @param headerRect The rectangle for the statistics header background
 */
void EndScreen_RenderStatsPanel(SDL_Rect headerRect) {
    // Render statistics header with background rectangle
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &headerRect);
    UI_RenderText(statisticsTextElement);
    
    // Render statistics labels and values
    UI_RenderText(floorReachedLabelElement);
    UI_RenderText(runTimeLabelElement);
    UI_RenderText(robotsDeactivatedLabelElement);
    UI_RenderText(healingItemsLabelElement);
    UI_RenderText(hitsTakenLabelElement);
    UI_RenderText(ammoSpentLabelElement);
    
    UI_RenderText(floorReachedValueElement);
    UI_RenderText(runTimeValueElement);
    UI_RenderText(robotsDeactivatedValueElement);
    UI_RenderText(healingItemsValueElement);
    UI_RenderText(hitsTakenValueElement);
    UI_RenderText(ammoSpentValueElement);
}

/**
 * @brief [Start] Initializes the death screen UI elements
 * 
 * Creates the text elements that make up the death screen,
 * positioning them appropriately on the screen.
 */
void Death_Start() {
    diamondPartialIcon = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/diamond_partial.png");
    if (!diamondPartialIcon) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load diamond icon: %s", IMG_GetError());
    }
    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color redColor = {255, 0, 0, 255};
    
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

    failedTextElement = UI_CreateText(
        "FAILED", 
        (SDL_Rect) {
            100, 
            65,
            0, 
            0
        }, 
        whiteColor, 
        1.3f, 
        UI_TEXT_ALIGN_LEFT, 
        app.resources.title1Font
    );
    
    int bodyX = 50;
    int valueX = app.config.screen_width - 50;
    
    // Create stats panel
    int statsY = 110;
    EndScreen_CreateStatsPanel("Statistics", statsY, bodyX, valueX);
    
    // Return to main menu button at bottom right
    returnButtonRect.x = app.config.screen_width - 150;
    returnButtonRect.y = app.config.screen_height - 30;
    
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
 * @brief [PostUpdate] Processes user input for the death screen
 * 
 * Checks for the ESC key press or button clicks to return to the main menu
 */
void Death_Update() {
    static float timer = 0;
    static bool isPlayed = 0;
    timer += Time->deltaTimeSeconds;
    if(timer > 39.428569 && !isPlayed) {
        Sound_Play_Music("Assets/Audio/Music/return0 lofi death music LOOP.wav", -1);
        isPlayed = 1;
    }
    
    // Update UI elements
    UI_UpdateText(returnButtonElement);
    
    // Handle return button interaction
    SDL_Color defaultButtonColor = {255, 255, 255, 255};
    SDL_Color hoverButtonColor = {0, 0, 0, 255};
    
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
    if ((int)timer % 5 == 0 && (int)timer != 0) {
        demoFloor = player.stats.enemiesKilled / 10;
        demoRobots = player.stats.enemiesKilled;
        EndScreen_UpdateStats(
            demoFloor,            // floor reached
            (int)demoTime,        // run time in seconds
            demoRobots,           // robots deactivated
            3,                    // healing items used
            5,                    // hits taken
            250                   // ammo spent
        );
    }
}
 
/**
 * @brief [Render] Draws the death screen to the screen
 * 
 * Renders the death screen UI elements
 */
void Death_Render() {
    // Background
    SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 255);
    SDL_Rect fullScreenRect = {0, 0, app.config.screen_width, app.config.screen_height};
    SDL_RenderFillRect(app.resources.renderer, &fullScreenRect);
    
    // Check if diamond icon exists and render it
    if (diamondPartialIcon) {
        SDL_Rect iconRect = {
            45, 20, 40, 40  // Positioned near the MISSION text
        };
        SDL_RenderCopy(app.resources.renderer, diamondPartialIcon, NULL, &iconRect);
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Diamond icon not available when trying to render");
    }
    
    // Render header text
    UI_RenderText(missionTextElement);
    UI_RenderText(failedTextElement);
    
    // Render statistics panel
    SDL_Rect statsHeaderRect = {45, 108, app.config.screen_width - 90, 20};
    EndScreen_RenderStatsPanel(statsHeaderRect);
    
    // Render return button with hover effect
    if (Input_MouseIsOnRect(returnButtonRect)) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.resources.renderer, &returnButtonRect);
    } else {
        SDL_SetRenderDrawColor(app.resources.renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(app.resources.renderer, &returnButtonRect);
    }
    UI_RenderText(returnButtonElement);
}