#include <settings.h>
#include <input.h>
#include <app.h>
#include <ui_text.h>
#include <sound.h>

// Enum for different settings tabs
typedef enum {
    SETTINGS_TAB_GAMEPLAY,
    SETTINGS_TAB_CONTROLS,
    SETTINGS_TAB_VIDEO,
    SETTINGS_TAB_AUDIO
} SettingsTab;

// Current active settings tab
static SettingsTab currentTab = SETTINGS_TAB_GAMEPLAY;

// UI elements
static UIElement* settingsTitle = NULL;
static UIElement* gameplayButton = NULL;
static UIElement* controlsButton = NULL;
static UIElement* videoButton = NULL;
static UIElement* audioButton = NULL;

// Gameplay settings
static UIElement* preventOverhealingLabel = NULL;
static UIElement* preventOverhealingButton = NULL;
static UIElement* damageNumbersLabel = NULL;
static UIElement* damageNumbersButton = NULL;
static UIElement* flashRedLabel = NULL;
static UIElement* flashRedButton = NULL;

// Gameplay settings state
static bool preventOverhealing = false;
static bool damageNumbers = true;
static bool flashRed = true;

// Define constants for button dimensions and spacing
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 20
#define BUTTON_SPACING 20
#define BUTTONS_TOTAL_WIDTH (BUTTON_WIDTH * 4 + BUTTON_SPACING * 3)


void Settings_Start() {
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color buttonTextColor = {0, 0, 0, 255}; // Black color for button text
    // Title
    settingsTitle = UI_CreateText(
        "SETTINGS",
        (SDL_Rect) {app.config.screen_width / 2, 20, 0, 0},
        textColor,
        1.0f,
        UI_TEXT_ALIGN_CENTER,
        app.resources.title1Font
    );

    int textSpacing = 120;
    // Tab buttons
    gameplayButton = UI_CreateText("Gameplay", (SDL_Rect) {55, 85, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    controlsButton = UI_CreateText("Controls", (SDL_Rect) {55 + textSpacing * 1, 85, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    videoButton = UI_CreateText("Video", (SDL_Rect) {55 + textSpacing * 2, 85, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    audioButton = UI_CreateText("Audio", (SDL_Rect) {55 + textSpacing * 3, 85, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);

    // Gameplay settings
    preventOverhealingLabel = UI_CreateText("Prevent Overhealing", (SDL_Rect) {50, 120, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    preventOverhealingButton = UI_CreateText("Off", (SDL_Rect) {300, 120, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);

    damageNumbersLabel = UI_CreateText("Damage Numbers", (SDL_Rect) {50, 160, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    damageNumbersButton = UI_CreateText("On", (SDL_Rect) {300, 160, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);

    flashRedLabel = UI_CreateText("Flash Red when Hurt", (SDL_Rect) {50, 200, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
    flashRedButton = UI_CreateText("On", (SDL_Rect) {300, 200, 0, 0}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont);
}

void Settings_Update() {
    // Handle tab switching
    if (Input_MouseIsOnRect((SDL_Rect) {50, 80, 100, 20}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_GAMEPLAY;
    } else if (Input_MouseIsOnRect((SDL_Rect) {150, 80, 100, 20}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_CONTROLS;
    } else if (Input_MouseIsOnRect((SDL_Rect) {250, 80, 100, 20}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_VIDEO;
    } else if (Input_MouseIsOnRect((SDL_Rect) {350, 80, 100, 20}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_AUDIO;
    }

    // Handle gameplay settings toggles
    if (currentTab == SETTINGS_TAB_GAMEPLAY) {
        if (Input_MouseIsOnRect((SDL_Rect) {300, 120, 50, 20}) && Input->mouse.leftButton.pressed) {
            preventOverhealing = !preventOverhealing;
            UI_ChangeText(preventOverhealingButton, preventOverhealing ? "On" : "Off");
        }
        if (Input_MouseIsOnRect((SDL_Rect) {300, 160, 50, 20}) && Input->mouse.leftButton.pressed) {
            damageNumbers = !damageNumbers;
            UI_ChangeText(damageNumbersButton, damageNumbers ? "On" : "Off");
        }
        if (Input_MouseIsOnRect((SDL_Rect) {300, 200, 50, 20}) && Input->mouse.leftButton.pressed) {
            flashRed = !flashRed;
            UI_ChangeText(flashRedButton, flashRed ? "On" : "Off");
        }
    }

    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_MENU; // Go back to main menu
    }
}

void Settings_Render() {
    // Render title
    UI_RenderText(settingsTitle);

    // Calculate button positions to center them around the screen
    int totalWidth = (BUTTON_WIDTH * 4) + (BUTTON_SPACING * 3);
    int startX = (app.config.screen_width - totalWidth) / 2;

    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255); // White color

    // Render Gameplay button
    SDL_Rect gameplayRect = {startX, 80, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(app.resources.renderer, &gameplayRect);
    UI_RenderText(gameplayButton);

    // Render Controls button
    SDL_Rect controlsRect = {startX + BUTTON_WIDTH + BUTTON_SPACING, 80, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(app.resources.renderer, &controlsRect);
    UI_RenderText(controlsButton);

    // Render Video button
    SDL_Rect videoRect = {startX + 2 * (BUTTON_WIDTH + BUTTON_SPACING), 80, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(app.resources.renderer, &videoRect);
    UI_RenderText(videoButton);

    // Render Audio button
    SDL_Rect audioRect = {startX + 3 * (BUTTON_WIDTH + BUTTON_SPACING), 80, BUTTON_WIDTH, BUTTON_HEIGHT};
    SDL_RenderFillRect(app.resources.renderer, &audioRect);
    UI_RenderText(audioButton);

    // Render gameplay settings if active
    if (currentTab == SETTINGS_TAB_GAMEPLAY) {
        UI_RenderText(preventOverhealingLabel);
        UI_RenderText(preventOverhealingButton);

        UI_RenderText(damageNumbersLabel);
        UI_RenderText(damageNumbersButton);

        UI_RenderText(flashRedLabel);
        UI_RenderText(flashRedButton);
    }
}