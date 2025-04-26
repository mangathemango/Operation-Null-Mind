#include <stdio.h>
#include <settings.h>
#include <input.h>
#include <ui_text.h>
#include <sound.h>
#include <math.h>
#include <SDL_filesystem.h>
#include <app.h>


AppScene settingsLastScene = SCENE_MENU;

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

// Video settings enum
typedef enum {
    SETTING_FULLSCREEN,
    SETTING_FPS_COUNTER,
    SETTING_DEBUG_MODE,
    SETTING_SCREEN_SHAKE,
    SETTING_CAMERA_SMOOTHING,
    SETTING_HIDE_PARTICLES,
    VIDEO_SETTINGS_COUNT
} VideoSetting;

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
static SettingData videoSettings[VIDEO_SETTINGS_COUNT];

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
#define SETTING_BUTTON_HITBOX(x) BUTTONS_ENDX - 20, SETTING_TAB_STARTY + (x) * (SETTING_TAB_SPACING), 20, SETTING_TAB_SPACING
#define CREATE_SETTING_BUTTON(x, text) UI_CreateText(text, (SDL_Rect) {SETTING_BUTTON_RECT(x)}, textColor, 1.0f, UI_TEXT_ALIGN_RIGHT, app.resources.textFont)

#define SLIDER_WIDTH 200
#define SLIDER_HEIGHT 15
#define SLIDER_BORDER 2
#define PERCENTAGE_TEXT_OFFSET 0

// Add tracking for active slider
static int activeSliderIndex = -1;

// Add scroll state for controls tab
static float controlsScrollOffset = 0;
static bool isCapturingKey = false;
static int capturingBindIndex = -1;

// Add UI elements array for keybinds
static struct {
    UIElement* actionLabel;
    UIElement* primaryLabel;
} keybindLabels[ACTION_COUNT] = {0};

// Initialize the settings arrays
void InitializeSettings() {
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

    // Initialize video settings
    videoSettings[SETTING_FULLSCREEN] = (SettingData){
        .label = "Fullscreen",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = false
    };
    videoSettings[SETTING_FPS_COUNTER] = (SettingData){
        .label = "FPS Counter",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = false
    };
    videoSettings[SETTING_DEBUG_MODE] = (SettingData){
        .label = "Debug Mode",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = false
    };
    videoSettings[SETTING_SCREEN_SHAKE] = (SettingData){
        .label = "Screen Shake",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = true
    };
    videoSettings[SETTING_CAMERA_SMOOTHING] = (SettingData){
        .label = "Camera Smoothing",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = true
    };
    videoSettings[SETTING_HIDE_PARTICLES] = (SettingData){
        .label = "Hide Particles",
        .type = SETTING_TYPE_TOGGLE,
        .toggleValue = false
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

// Helper function to get key name
static const char* GetKeyName(SDL_Scancode key) {
    // For normal keyboard keys
    if (key != SDL_SCANCODE_UNKNOWN) {
        const char* keyName = SDL_GetScancodeName(key);
        return keyName && keyName[0] ? keyName : "???";
    }
    
    return "---";
}

// Helper function to cleanup keybind UI
static void CleanupKeybindUI() {
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (keybindLabels[i].actionLabel) {
            UI_DestroyText(keybindLabels[i].actionLabel);
            keybindLabels[i].actionLabel = NULL;
        }
        if (keybindLabels[i].primaryLabel) {
            UI_DestroyText(keybindLabels[i].primaryLabel);
            keybindLabels[i].primaryLabel = NULL;
        }
    }
}

// Helper function to initialize keybind UI
static void InitializeKeybindUI() {
    SDL_Color textColor = {255, 255, 255, 255};
    
    for (int i = 0; i < ACTION_COUNT; i++) {
        const char* actionName = Input_GetActionName(i);
        if (!actionName) actionName = "Unknown";
        SDL_Log("Keybind %d: %s", i, actionName);
        
        keybindLabels[i].actionLabel = UI_CreateText(
            actionName,
            (SDL_Rect){BUTTONS_STARTX, SETTING_TAB_STARTY + i * SETTING_TAB_SPACING, 0, 0},
            textColor,
            1.0f,
            UI_TEXT_ALIGN_LEFT,
            app.resources.textFont
        );

        SDL_Scancode binding = Input_GetBinding(i);
        const char* keyName = GetKeyName(binding);
        if (!keyName) keyName = "---";
        
        keybindLabels[i].primaryLabel = UI_CreateText(
            keyName,
            (SDL_Rect){BUTTONS_ENDX - 80, SETTING_TAB_STARTY + i * SETTING_TAB_SPACING + 2, 0, 0},
            textColor,
            1.0f,
            UI_TEXT_ALIGN_CENTER,
            app.resources.textFont
        );
    }
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

    // Video settings
    for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
        videoSettings[i].labelElement = CREATE_SETTING_LABEL(i, videoSettings[i].label);
        videoSettings[i].buttonElement = CREATE_SETTING_BUTTON(i, videoSettings[i].toggleValue ? "On" : "Off");
    }

    InitializeKeybindUI();
    
}

void Settings_Update() {
    if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed && !isCapturingKey) {
        app.state.currentScene = settingsLastScene;
    }

    // Handle tab switching
    if (Input->mouse.leftButton.pressed) {
        SettingsTab newTab = currentTab;
        if (Input_MouseIsOnRect((SDL_Rect) {GAMEPLAY_RECT})) {
            newTab = SETTINGS_TAB_GAMEPLAY;
        } else if (Input_MouseIsOnRect((SDL_Rect) {CONTROLS_RECT})) {
            newTab = SETTINGS_TAB_CONTROLS;
            Settings_Start(); // Initialize all UI elements when switching to Controls tab
        } else if (Input_MouseIsOnRect((SDL_Rect) {VIDEO_RECT})) {
            newTab = SETTINGS_TAB_VIDEO;
        } else if (Input_MouseIsOnRect((SDL_Rect) {AUDIO_RECT})) {
            newTab = SETTINGS_TAB_AUDIO;
        }
        
        if (newTab != currentTab) {
            currentTab = newTab;
        }
    }

    // Handle controls settings
    if (currentTab == SETTINGS_TAB_CONTROLS) {
        // Handle scrolling
        if (Input->mouse.scrollUp) {
            controlsScrollOffset = fmaxf(0, controlsScrollOffset - SETTING_TAB_SPACING);
        }
        if (Input->mouse.scrollDown) {
            float maxScroll = ACTION_COUNT * SETTING_TAB_SPACING - (app.config.screen_height - SETTING_TAB_STARTY - 40);
            controlsScrollOffset = fminf(maxScroll, controlsScrollOffset + SETTING_TAB_SPACING);
        }

        // Update UI positions based on scroll
        for (int i = 0; i < ACTION_COUNT; i++) {
            float y = SETTING_TAB_STARTY + i * SETTING_TAB_SPACING - controlsScrollOffset;
            if (keybindLabels[i].actionLabel) {
                keybindLabels[i].actionLabel->rect.y = y;
            }
            if (keybindLabels[i].primaryLabel) {
                keybindLabels[i].primaryLabel->rect.y = y + 2;
            }
        }

        if (isCapturingKey) {
            // Capture any key press for rebinding
            for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
                if (Input->keyboard.keys[i].pressed && i != SDL_SCANCODE_ESCAPE) {
                    Input_SetBinding(capturingBindIndex, i);
                    isCapturingKey = false;
                    break;
                }
            }
            // Cancel with escape
            if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].pressed) {
                isCapturingKey = false;
            }
        } else {
            // Check for clicking on keybind buttons
            for (int i = 0; i < ACTION_COUNT; i++) {
                if (
                    i == ACTION_PAUSE ||
                    i == ACTION_SHOOT ||
                    i == ACTION_PARRY
                ) {
                    continue;
                }
                float y = SETTING_TAB_STARTY + i * SETTING_TAB_SPACING - controlsScrollOffset;
                if (y < SETTING_TAB_STARTY - SETTING_TAB_SPACING || y > app.config.screen_height - 40) continue;

                SDL_Rect primaryRect = {BUTTONS_ENDX - 140, y, 120, SETTING_TAB_SPACING};

                if (Input_MouseIsOnRect(primaryRect) && Input->mouse.leftButton.pressed) {
                    isCapturingKey = true;
                    capturingBindIndex = i;
                }
            }
        }
    } else {
        // Reset scroll when leaving controls tab
        controlsScrollOffset = 0;
    }

    // Handle gameplay settings toggles
    if (currentTab == SETTINGS_TAB_GAMEPLAY) {
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            if (Input_MouseIsOnRect((SDL_Rect) {SETTING_BUTTON_HITBOX(i)}) && Input->mouse.leftButton.pressed) {
                gameplaySettings[i].toggleValue = !gameplaySettings[i].toggleValue;
                UI_ChangeText(gameplaySettings[i].buttonElement, gameplaySettings[i].toggleValue ? "On" : "Off");
                UI_UpdateText(gameplaySettings[i].buttonElement);
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
                // Make sure to update the percentage text UI
                UI_UpdateText(audioSettings[activeSliderIndex].percentageText);
            } else {
                // Release the active slider when mouse button is released
                activeSliderIndex = -1;
            }
        }
    } else {
        // Reset active slider when leaving audio tab
        activeSliderIndex = -1;
    }

    // Handle video settings toggles
    if (currentTab == SETTINGS_TAB_VIDEO) {
        for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
            if (Input_MouseIsOnRect((SDL_Rect) {SETTING_BUTTON_HITBOX(i)}) && Input->mouse.leftButton.pressed) {
                videoSettings[i].toggleValue = !videoSettings[i].toggleValue;
                UI_ChangeText(videoSettings[i].buttonElement, videoSettings[i].toggleValue ? "On" : "Off");
                UI_UpdateText(videoSettings[i].buttonElement);
                
                // Handle fullscreen toggle immediately
                if (i == SETTING_FULLSCREEN) {
                    app.config.window_fullscreen = videoSettings[i].toggleValue;
                    SDL_SetWindowFullscreen(app.resources.window, 
                        app.config.window_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
                    SDL_SetWindowSize(app.resources.window, app.config.window_width, app.config.window_height);
                    SDL_SetWindowPosition(app.resources.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }
            }
        }
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

    // Render video settings if active
    if (currentTab == SETTINGS_TAB_VIDEO) {
        for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
            UI_RenderText(videoSettings[i].labelElement);
            UI_RenderText(videoSettings[i].buttonElement);
        }
    }

    // Render controls settings if active
    if (currentTab == SETTINGS_TAB_CONTROLS) {
        SDL_SetRenderDrawColor(app.resources.renderer, 100, 100, 100, 255);
        
        for (int i = 0; i < ACTION_COUNT; i++) {
            float y = SETTING_TAB_STARTY + i * SETTING_TAB_SPACING - controlsScrollOffset;
            if (y < SETTING_TAB_STARTY - SETTING_TAB_SPACING || y > app.config.screen_height - 40) continue;

            // Draw action name
            if (keybindLabels[i].actionLabel) {
                UI_UpdateText(keybindLabels[i].actionLabel);
                UI_RenderText(keybindLabels[i].actionLabel);
            }

            // Draw key binding box (now wider since we only have one)
            SDL_Rect primaryRect = {BUTTONS_ENDX - 140, y, 120, SETTING_TAB_SPACING - 4};
            
            SDL_SetRenderDrawColor(app.resources.renderer, 50, 50, 50, 255);
            // If the keybind is mouse or esc, draw black
            if (
                i == ACTION_PAUSE ||
                i == ACTION_SHOOT ||
                i == ACTION_PARRY
            ) {
                SDL_SetRenderDrawColor(app.resources.renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(app.resources.renderer, &primaryRect);
            
            SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(app.resources.renderer, &primaryRect);

            // Draw key name
            if (keybindLabels[i].primaryLabel) {
                UI_ChangeText(keybindLabels[i].primaryLabel, GetKeyName(Input_GetBinding(i)));
                if (i == ACTION_SHOOT) {
                    UI_ChangeText(keybindLabels[i].primaryLabel, "Left Click");
                } else if (i == ACTION_PARRY) {
                    UI_ChangeText(keybindLabels[i].primaryLabel, "Right Click");
                }
                UI_UpdateText(keybindLabels[i].primaryLabel);
                UI_RenderText(keybindLabels[i].primaryLabel);
            }

            // Highlight active capture box
            if (isCapturingKey && capturingBindIndex == i) {
                SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 0, 255);
                SDL_RenderDrawRect(app.resources.renderer, &primaryRect);
            }
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

// Add video settings getters
bool Settings_GetFullscreen() {
    return videoSettings[SETTING_FULLSCREEN].toggleValue;
}

bool Settings_GetFPSCounter() {
    return videoSettings[SETTING_FPS_COUNTER].toggleValue;
}

bool Settings_GetDebugMode() {
    return videoSettings[SETTING_DEBUG_MODE].toggleValue;
}

bool Settings_GetScreenShake() {
    return videoSettings[SETTING_SCREEN_SHAKE].toggleValue;
}

bool Settings_GetCameraSmoothing() {
    return videoSettings[SETTING_CAMERA_SMOOTHING].toggleValue;
}

bool Settings_GetHideParticles() {
    return videoSettings[SETTING_HIDE_PARTICLES].toggleValue;
}

void Settings_Migrate(int oldVersion) {
    // When adding new settings, add migration code here
    switch(oldVersion) {
        case 0:
            // Example: If migrating from version 0, no settings file existed
            InitializeSettings();
            break;
            
        // Add more cases as you add new settings versions
        // case 1:
        //     // Migrate from version 1 to 2
        //     break;
    }
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
        // Write version number first
        int version = SETTINGS_VERSION;
        fwrite(&version, sizeof(int), 1, file);
        
        // Save all settings
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            fwrite(&gameplaySettings[i].toggleValue, sizeof(bool), 1, file);
        }
        for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
            fwrite(&audioSettings[i].sliderValue, sizeof(float), 1, file);
        }
        for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
            fwrite(&videoSettings[i].toggleValue, sizeof(bool), 1, file);
        }
        // Save key bindings using the helper
        Input_SaveBindings(file);
        fclose(file);
    }
    free(settingsPath);
}

void Settings_Load() {
    // Initialize with defaults first
    InitializeSettings();
    
    char* settingsPath = GetSettingsPath();
    if (settingsPath == NULL) {
        SDL_Log("Failed to get settings path");
        return;
    }

    FILE* file = fopen(settingsPath, "rb");
    if (file) {
        // Read version number
        int version;
        if (fread(&version, sizeof(int), 1, file) != 1) {
            SDL_Log("Failed to read settings version");
            fclose(file);
            free(settingsPath);
            return;
        }

        if (version != SETTINGS_VERSION) {
            // Version mismatch - close file and migrate
            fclose(file);
            Settings_Migrate(version);
            free(settingsPath);
            return;
        }

        // Load all settings values
        for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
            fread(&gameplaySettings[i].toggleValue, sizeof(bool), 1, file);
        }
        for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
            fread(&audioSettings[i].sliderValue, sizeof(float), 1, file);
        }
        for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
            fread(&videoSettings[i].toggleValue, sizeof(bool), 1, file);
        }
        // Load key bindings using the helper
        Input_LoadBindings(file);
        fclose(file);
    } else {
        // No settings file exists - treat as version 0
        Settings_Migrate(0);
    }
    free(settingsPath);
}

void Settings_End() {
    // Clean up title and tab buttons
    UI_DestroyText(settingsTitle);
    UI_DestroyText(gameplayButton);
    UI_DestroyText(controlsButton);
    UI_DestroyText(videoButton);
    UI_DestroyText(audioButton);

    // Clean up gameplay settings
    for (int i = 0; i < GAMEPLAY_SETTINGS_COUNT; i++) {
        UI_DestroyText(gameplaySettings[i].labelElement);
        UI_DestroyText(gameplaySettings[i].buttonElement);
    }

    // Clean up audio settings
    for (int i = 0; i < AUDIO_SETTINGS_COUNT; i++) {
        UI_DestroyText(audioSettings[i].labelElement);
        UI_DestroyText(audioSettings[i].percentageText);
    }

    // Clean up video settings
    for (int i = 0; i < VIDEO_SETTINGS_COUNT; i++) {
        UI_DestroyText(videoSettings[i].labelElement);
        UI_DestroyText(videoSettings[i].buttonElement);
    }

    // Clean up keybind UI if it exists
    CleanupKeybindUI();

    // Reset states
    controlsScrollOffset = 0;
    isCapturingKey = false;
    capturingBindIndex = -1;
    activeSliderIndex = -1;
}