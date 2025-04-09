/**
 * @file controls.h
 * @brief Controls screen interface for displaying game controls to the player
 * 
 * @author Mango
 * @date 2025-04-05
 */

#pragma once

#include <app.h>

extern AppScene controlLastScene;

/**
 * @brief Initializes the controls screen
 * Loads textures and UI elements needed for the controls screen
 */
void Controls_Start();

/**
 * @brief Updates the controls screen state
 * Handles input and interaction with the controls screen
 */
void Controls_Update();

/**
 * @brief Renders the controls screen
 * Displays the control scheme and navigation UI
 */
void Controls_Render();