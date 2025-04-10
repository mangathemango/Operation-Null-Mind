#pragma once

#include <app.h>
#include <death.h>  // For access to EndScreen functions

/**
 * @brief Initializes the win screen
 * 
 * Loads textures and creates UI elements needed for the win screen
 */
void Win_Start();

/**
 * @brief Updates the win screen state
 * 
 * Handles input and interaction with the win screen
 */
void Win_Update();

/**
 * @brief Renders the win screen
 * 
 * Displays the mission accomplished screen with stats
 */
void Win_Render();