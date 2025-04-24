#include <stdio.h>
#include <settings.h>
#include <input.h>
#include <ui_text.h>
#include <app.h>
#include <sound.h>
#include <math.h>
#include <SDL_filesystem.h>

// Enum for different settings tabs
typedef enum {
    SETTINGS_TAB_GAMEPLAY,
    SETTINGS_TAB_CONTROLS,
    SETTINGS_TAB_VIDEO,
    SETTINGS_TAB_AUDIO,
    SETTINGS_TAB_COUNT
} SettingsTab;

// Gameplay settings enum
typedef enum {
    SETTING_PREVENT_OVERHEALING,
    SETTING_DAMAGE_NUMBERS,
    SETTING_FLASH_RED,
    GAMEPLAY_SETTINGS_COUNT
} GameplaySetting;

// Audio settings enum
typedef enum {
    SETTING_MASTER_VOLUME,
    SETTING_MUSIC_VOLUME,
    SETTING_SOUND_VOLUME,
    AUDIO_SETTINGS_COUNT
} AudioSetting;

typedef enum {
    SETTING_TYPE_TOGGLE,
    SETTING_TYPE_SLIDER
} SettingType;

// Structure to hold setting data
typedef struct {
    const char* label;
    SettingType type;
    union {
        bool toggleValue;
        float sliderValue;
    };
    UIElement* labelElement;
    union {
        UIElement* buttonElement;
        struct {
            SDL_Rect sliderBar;
            UIElement* percentageText;
        };
    };
} SettingData;

// Current active settings tab
static SettingsTab currentTab = SETTINGS_TAB_GAMEPLAY;

// Settings arrays for each tab
static SettingData gameplaySettings[GAMEPLAY_SETTINGS_COUNT];
static SettingData audioSettings[AUDIO_SETTINGS_COUNT];

// UI elements for tabs
static UIElement* settingsTitle = NULL;
static UIElement* gameplayButton = NULL;
static UIElement* controlsButton = NULL;
static UIElement* videoButton = NULL;
static UIElement* audioButton = NULL;

// Define constants for button dimensions and spacing
#define BUTTON_WIDTH 70
#define BUTTON_HEIGHT 20
#define BUTTON_SPACING 20
#define BUTTONS_TOTAL_WIDTH (BUTTON_WIDTH * 4 + BUTTON_SPACING * 3)
#define BUTTONS_STARTX ((app.config.screen_width - BUTTONS_TOTAL_WIDTH) / 2)
#define BUTTONS_ENDX (BUTTONS_STARTX + BUTTONS_TOTAL_WIDTH)
#define BUTTONS_STARTY 80
#define BUTTON_TEXT_STARTY (BUTTONS_STARTY + 3)
#define BUTTON_TEXT_STARTX (BUTTONS_STARTX + BUTTON_WIDTH / 2)
#define BUTTON_TEXT_SPACING (BUTTON_WIDTH + BUTTON_SPACING)

#define BUTTON_RECT(x) BUTTONS_STARTX + (x) * (BUTTON_WIDTH + BUTTON_SPACING), BUTTONS_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT
#define GAMEPLAY_RECT BUTTON_RECT(0)
#define CONTROLS_RECT BUTTON_RECT(1)
#define VIDEO_RECT BUTTON_RECT(2)
#define AUDIO_RECT BUTTON_RECT(3)

#define SETTING_TAB_STARTY 120
#define SETTING_TAB_SPACING 20
#define SETTING_LABEL_RECT(x) BUTTONS_STARTX, SETTING_TAB_STARTY + (x) * (SETTING_TAB_SPACING), 0, 0
#define CREATE_SETTING_LABEL(x, text) UI_CreateText(text, (SDL_Rect) {SETTING_LABEL_RECT(x)}, textColor, 1.0f, UI_TEXT_ALIGN_LEFT, app.resources.textFont)

#define SETTING_BUTTON_RECT(x) BUTTONS_ENDX, SETTING_TAB_STARTY + (x) * (SETTING_TAB_SPACING), 0, 0
#define CREATE_SETTING_BUTTON(x, text) UI_CreateText(text, (SDL_Rect) {SETTING_BUTTON_RECT(x)}, textColor, 1.0f, UI_TEXT_ALIGN_RIGHT, app.resources.textFont)

#define SLIDER_WIDTH 200
#define SLIDER_HEIGHT 15
#define SLIDER_BORDER 2
#define PERCENTAGE_TEXT_OFFSET 0

// Add tracking for active slider
static int activeSliderIndex = -1;

// Initialize the settings arrays
static void InitializeSettings() {
    // Initialize gameplay settings
    gameplaySettings[SETTING_PREVENT_OVERHEALING] = (SettingData){
        .label = "Prevent Overhealing",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = false
    };
    gameplaySettings[SETTING_DAMAGE_NUMBERS] = (SettingData){
        .label = "Damage Numbers",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = true
    };
    gameplaySettings[SETTING_FLASH_RED] = (SettingData){
        .label = "Flash red when hurt",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = true
    };

    // Initialize audio settings
    audioSettings[SETTING_MASTER_VOLUME] = (SettingData){
        .label = "Master Volume",
        .type = SETTING_TYPE_SLIDER,
        .sliderValue = 1.0f
    };
    audioSettings[SETTING_MUSIC_VOLUME] = (SettingData){
        .label = "Music Volume",
        .type = SETTING_TYPE_SLIDER,
        .sliderValue = 1.0f
    };
    audioSettings[SETTING_SOUND_VOLUME] = (SettingData){
        .label = "Sound Volume",
        .type = SETTING_TYPE_SLIDER,
        .sliderValue = 1.0f
    };
}

// Helper function to update slider value based on mouse position
static void UpdateSliderValue(SettingData* setting, int mouseX) {
    float percentage = (float)(mouseX - setting->sliderBar.x) / setting->sliderBar.w;
    setting->sliderValue = fmaxf(0.0f, fminf(1.0f, percentage));
    char percentText[8];
    snprintf(percentText, sizeof(percentText), "%d%%", (int)(setting->sliderValue * 100));
    UI_ChangeText(setting->percentageText, percentText);
}

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
    gameplayButton = UI_CreateText("Gameplay", (SDL_Rect) {BUTTON_TEXT_STARTX, BUTTON_TEXT_STARTY, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    controlsButton = UI_CreateText("Controls", (SDL_Rect) {BUTTON_TEXT_STARTX + BUTTON_TEXT_SPACING * 1, BUTTON_TEXT_STARTY, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    videoButton = UI_CreateText("Video", (SDL_Rect) {BUTTON_TEXT_STARTX + BUTTON_TEXT_SPACING * 2, BUTTON_TEXT_STARTY, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);
    audioButton = UI_CreateText("Audio", (SDL_Rect) {BUTTON_TEXT_STARTX + BUTTON_TEXT_SPACING * 3, BUTTON_TEXT_STARTY, 0, 0}, buttonTextColor, 1.0f, UI_TEXT_ALIGN_CENTER, app.resources.textFont);

    // Initialize settings
    InitializeSettings();

    // Gameplay settings
    for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
        gameplaySettings[i].labelElement = CREATE_SETTING_LABEL(i, gameplaySettings[i].label);
        gameplaySettings[i].buttonElement = CREATE_SETTING_BUTTON(i, gameplaySettings[i].toggleValue ? "On" : "Off");
    }

    // Audio settings
    for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
        audioSettings[i].labelElement = CREATE_SETTING_LABEL(i, audioSettings[i].label);
        audioSettings[i].sliderBar = (SDL_Rect) {
            BUTTONS_ENDX - SLIDER_WIDTH - PERCENTAGE_TEXT_OFFSET - 30,  // Extra space for percentage text
            SETTING_TAB_STARTY + i * SETTING_TAB_SPACING - 1,
            SLIDER_WIDTH,
            SLIDER_HEIGHT
        };
        
        char percentText[8];
        snprintf(percentText, sizeof(percentText), "%d%%", (int)(audioSettings[i].sliderValue * 100));
        audioSettings[i].percentageText = UI_CreateText(
            percentText,
            (SDL_Rect) {
                BUTTONS_ENDX - PERCENTAGE_TEXT_OFFSET,
                SETTING_TAB_STARTY + i * SETTING_TAB_SPACING,
                0,
                0
            },
            textColor,
            1.0f,
            UI_TEXT_ALIGN_RIGHT,
            app.resources.textFont
        );
    }
    Settings_Load();
}

void Settings_Update() {
    // Handle tab switching
    if (Input_MouseIsOnRect((SDL_Rect) {GAMEPLAY_RECT}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_GAMEPLAY;
    } else if (Input_MouseIsOnRect((SDL_Rect) {CONTROLS_RECT}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_CONTROLS;
    } else if (Input_MouseIsOnRect((SDL_Rect) {VIDEO_RECT}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_VIDEO;
    } else if (Input_MouseIsOnRect((SDL_Rect) {AUDIO_RECT}) && Input->mouse.leftButton.pressed) {
        currentTab = SETTINGS_TAB_AUDIO;
    }

    // Handle gameplay settings toggles
    if (currentTab == SETTINGS_TAB_GAMEPLAY) {
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            if (Input_MouseIsOnRect((SDL_Rect) {300, 120 + i * 40, 50, 20}) && Input->mouse.leftButton.pressed) {
                gameplaySettings[i].toggleValue = !gameplaySettings[i].toggleValue;
                UI_ChangeText(gameplaySettings[i].buttonElement, gameplaySettings[i].toggleValue ? "On" : "Off");
            }
        }
    }

    // Handle audio settings sliders
    if (currentTab == SETTINGS_TAB_AUDIO) {
        // If no slider is active, check for new slider activation
        if (activeSliderIndex == -1) {
            for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
                SDL_Rect sliderClickArea = audioSettings[i].sliderBar;
                if (Input_MouseIsOnRect(sliderClickArea) && Input->mouse.leftButton.pressed) {
                    activeSliderIndex = i;
                    break;
                }
            }
        }
        
        // If a slider is active, update it regardless of mouse position
        if (activeSliderIndex != -1) {
            if (Input->mouse.leftButton.held) {
                UpdateSliderValue(&audioSettings[activeSliderIndex], Input->mouse.position.x);
            } else {
                // Release the active slider when mouse button is released
                activeSliderIndex = -1;
            }
        }
    } else {
        // Reset active slider when leaving audio tab
        activeSliderIndex = -1;
    }

    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
        app.state.currentScene = SCENE_MENU; // Go back to main menu
    }
}

void Settings_Render() {
    // Render title
    UI_RenderText(settingsTitle);

    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255); // White color

    // Render Gameplay button
    SDL_Rect gameplayRect = {GAMEPLAY_RECT};
    SDL_RenderFillRect(app.resources.renderer, &gameplayRect);
    UI_RenderText(gameplayButton);

    // Render Controls button
    SDL_Rect controlsRect = {CONTROLS_RECT};
    SDL_RenderFillRect(app.resources.renderer, &controlsRect);
    UI_RenderText(controlsButton);

    // Render Video button
    SDL_Rect videoRect = {VIDEO_RECT};
    SDL_RenderFillRect(app.resources.renderer, &videoRect);
    UI_RenderText(videoButton);

    // Render Audio button
    SDL_Rect audioRect = {AUDIO_RECT};
    SDL_RenderFillRect(app.resources.renderer, &audioRect);
    UI_RenderText(audioButton);

    // Render gameplay settings if active
    if (currentTab == SETTINGS_TAB_GAMEPLAY) {
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            UI_RenderText(gameplaySettings[i].labelElement);
            UI_RenderText(gameplaySettings[i].buttonElement);
        }
    }

    // Render audio settings if active
    if (currentTab == SETTINGS_TAB_AUDIO) {
        for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
            UI_RenderText(audioSettings[i].labelElement);
            UI_RenderText(audioSettings[i].percentageText);
            
            SDL_Rect sliderBar = audioSettings[i].sliderBar;
            
            // Draw white border
            SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(app.resources.renderer, &sliderBar);
            
            // Draw filled portion
            SDL_Rect fillRect = sliderBar;
            fillRect.x += SLIDER_BORDER;
            fillRect.y += SLIDER_BORDER;
            fillRect.w = (sliderBar.w - 2 * SLIDER_BORDER) * audioSettings[i].sliderValue;
            fillRect.h -= 2 * SLIDER_BORDER;
            SDL_RenderFillRect(app.resources.renderer, &fillRect);
        }
    }
}

bool Settings_GetPreventOverhealing() {
    return gameplaySettings[SETTING_PREVENT_OVERHEALING].toggleValue;
}

bool Settings_GetDamageNumbers() {
    return gameplaySettings[SETTING_DAMAGE_NUMBERS].toggleValue;
}

bool Settings_GetFlashRed() {
    return gameplaySettings[SETTING_FLASH_RED].toggleValue;
}

float Settings_GetMasterVolume() {
    return audioSettings[SETTING_MASTER_VOLUME].sliderValue;
}

float Settings_GetMusicVolume() {
    return audioSettings[SETTING_MUSIC_VOLUME].sliderValue;
}

float Settings_GetSoundVolume() {
    return audioSettings[SETTING_SOUND_VOLUME].sliderValue;
}

static char* GetSettingsPath() {
    char* prefPath = SDL_GetPrefPath("Operation-Null-Mind", "Settings");
    if (prefPath == NULL) {
        SDL_Log("Error getting settings path: %s", SDL_GetError());
        return NULL;
    }
    
    // Allocate space for the path + filename
    size_t pathLen = strlen(prefPath) + strlen("settings.dat") + 1;
    char* fullPath = (char*)malloc(pathLen);
    if (fullPath == NULL) {
        SDL_free(prefPath);
        return NULL;
    }
    
    snprintf(fullPath, pathLen, "%ssettings.dat", prefPath);
    SDL_free(prefPath);
    return fullPath;
}

void Settings_Save() {
    char* settingsPath = GetSettingsPath();
    if (settingsPath == NULL) {
        SDL_Log("Failed to get settings path");
        return;
    }

    FILE* file = fopen(settingsPath, "wb");
    if (file) {
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            fwrite(&gameplaySettings[i].toggleValue, sizeof(bool), 1, file);
        }
        for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
            fwrite(&audioSettings[i].sliderValue, sizeof(float), 1, file);
        }
        fclose(file);
    }
    free(settingsPath);
}

void Settings_Load() {
    char* settingsPath = GetSettingsPath();
    if (settingsPath == NULL) {
        SDL_Log("Failed to get settings path");
        return;
    }

    FILE* file = fopen(settingsPath, "rb");
    if (file) {
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            if (fread(&gameplaySettings[i].toggleValue, sizeof(bool), 1, file) == 1) {
                if (gameplaySettings[i].buttonElement) {
                    UI_ChangeText(gameplaySettings[i].buttonElement, 
                                gameplaySettings[i].toggleValue ? "On" : "Off");
                }
            }
        }
        for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
            if (fread(&audioSettings[i].sliderValue, sizeof(float), 1, file) == 1) {
                char percentText[8];
                snprintf(percentText, sizeof(percentText), "%d%%", (int)(audioSettings[i].sliderValue * 100));
                if (audioSettings[i].percentageText) {
                    UI_ChangeText(audioSettings[i].percentageText, percentText);
                }
            }
        }
        fclose(file);
    }
    free(settingsPath);
}