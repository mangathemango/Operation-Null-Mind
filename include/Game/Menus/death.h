/**
 * @file death.h
 * @brief Manages the game's pause screen functionality and display.
 * 
 * @author Darren
 * @date 2025-03-21
 */

#pragma once

#include <app.h>

/**
 * @brief Initializes the death screen
 * 
 * Loads textures and creates UI elements needed for the death screen
 */
void Death_Start();

/**
 * @brief Updates the death screen state
 * 
 * Handles input and interaction with the death screen
 */
void Death_Update();

/**
 * @brief Renders the death screen
 * 
 * Displays the death screen with statistics
 */
void Death_Render();

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
void EndScreen_UpdateStats(int floorValue, int timeValue, int robotsValue, int healingValue, int hitsValue, int ammoValue);

/**
 * @brief Creates the statistics panel UI elements
 * 
 * @param titleText The text to display in the statistics header (e.g., "Statistics")
 * @param startY The Y position to start rendering the statistics panel
 * @param bodyX The X position for labels
 * @param valueX The X position for values (right-aligned)
 * @return The Y position after the last statistic row
 */
int EndScreen_CreateStatsPanel(const char* titleText, int startY, int bodyX, int valueX);

/**
 * @brief Renders the statistics panel
 * 
 * @param headerRect The rectangle for the statistics header background
 */
void EndScreen_RenderStatsPanel(SDL_Rect headerRect);