#pragma once

#include <stdbool.h>
#include <SDL.h>

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

// Function to save settings
void Settings_Save();

// Function to load settings
void Settings_Load();