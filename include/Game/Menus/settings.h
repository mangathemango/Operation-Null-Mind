#pragma once

#include <app.h>

extern AppScene settingsLastScene;

// Settings functions
void Settings_Start();
void Settings_Update();
void Settings_Render();

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

// Function to save settings
void Settings_Save();

// Function to load settings
void Settings_Load();
void InitializeSettings();