/**
 * @file pause.h
 * @brief Manages the game's pause functionality and menu display.
 * 
 * @author Mango
 * @date 2025-03-21
 */

#pragma once

/**
 * @brief Initializes the pause menu.
 * 
 * @return void
 */
void Pause_Start();

/**
 * @brief Updates the pause menu state based on user input.
 * 
 * @return void
 */
void Pause_Update();

/**
 * @brief Renders the pause menu to the screen.
 * 
 * @return void
 */
void Pause_Render();