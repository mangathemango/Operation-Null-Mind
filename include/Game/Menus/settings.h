#pragma once

#include <app.h>

// Current settings version - increment this when adding new settings
#define SETTINGS_VERSION 1

extern AppScene settingsLastScene;

// Settings functions
void Settings_Start();
void Settings_Update();
void Settings_Render();

// Migration function
void Settings_Migrate(int oldVersion);

// Functions to access settings values
bool Settings_GetPreventOverhealing();
bool Settings_GetDamageNumbers();
bool Settings_GetFlashRed();

// Audio settings getters
float Settings_GetMasterVolume();
float Settings_GetMusicVolume();
float Settings_GetSoundVolume();

// Video settings getters
bool Settings_GetFullscreen();
bool Settings_GetFPSCounter();
bool Settings_GetDebugMode();
bool Settings_GetScreenShake();
bool Settings_GetCameraSmoothing();
bool Settings_GetHideParticles();

// Function to save settings
void Settings_Save();

// Function to load settings
void Settings_Load();
void InitializeSettings();