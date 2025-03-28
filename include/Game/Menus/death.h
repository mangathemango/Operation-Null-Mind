/**
 * @file death.h
 * @brief Manages the game's pause screen functionality and display.
 * 
 * @author Darren
 * @date 2025-03-21
 */

#pragma once

/**
 * @brief Initializes the death menu.
 * 
 * @return void
 */
void Death_Start();

/**
 * @brief Updates the death scene based on user input.
 * 
 * @return void
 */
void Death_Update();

/**
 * @brief Renders the death scene to the screen.
 * 
 * @return void
 */
void Death_Render();