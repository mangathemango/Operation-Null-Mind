/**
 * @file menu.h
 * @brief Manages game main menu system, including rendering and user interactions.
 * 
 * @author Mango
 * @date 2025-03-12
 */

#pragma once

/**
 * @brief Prepares and loads all menu textures.
 * 
 * @return void
 */
void Menu_PrepareTextures();

/**
 * @brief Updates the menu state based on user input.
 * 
 * @return void
 */
void Menu_Update();

/**
 * @brief Renders the menu to the screen.
 * 
 * @return void
 */
void Menu_Render();