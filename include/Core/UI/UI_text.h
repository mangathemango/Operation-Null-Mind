/**
 * @file UI_text.h
 * @brief This file contains the definition of the UI_TextData struct. 
 * @author Mango (杜明日) 
 * @date 2025-03-12
 * 
 * @section usage Usage Examples
 * 
 * Creating and managing text elements:
 * 
 * ```c
 * // Create a simple text element
 * UIElement* titleText = UI_CreateText(
 *     "Operation Null Mind", 
 *     (SDL_Rect){400, 100, 400, 50},
 *     (SDL_Color){255, 255, 255, 255},
 *     1.5f,
 *     UI_TEXT_ALIGN_CENTER,
 *     app.resources.fonts.titleFont
 * );
 * 
 * // Changing text content dynamically
 * UI_ChangeText(scoreText, "Score: 1500");
 * 
 * // Changing text color
 * UI_ChangeTextColor(warningText, (SDL_Color){255, 0, 0, 255});
 * ```
 */

#pragma once

#include <UI.h>
#include <SDL_ttf.h>

/**
 * @brief An enum for text alignment
 */
typedef enum {
    UI_TEXT_ALIGN_LEFT,
    UI_TEXT_ALIGN_CENTER,
    UI_TEXT_ALIGN_RIGHT
} UI_TextAlignment;

/**
 * @brief Data structure for UI text elements
 * 
 * This structure holds all necessary data for rendering and managing text UI elements,
 * including the text content, texture, font and alignment properties.
 */
typedef struct {
    char* text;                 /**< Text content to display */
    SDL_Texture* textTexture;   /**< Pre-rendered text texture */
    TTF_Font* font;             /**< Font used for text rendering */
    UI_TextAlignment alignment; /**< Text alignment (left, center, or right) */
} UI_TextData;

UIElement* UI_CreateText(const char* text, SDL_Rect rect, 
                        SDL_Color color, float scale, UI_TextAlignment alignment,
                        TTF_Font* font);
SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color, TTF_Font* font);

void UI_UpdateText(UIElement* element);
void UI_RenderText(UIElement* element);
void UI_DestroyText(UIElement* element);

void UI_ChangeText(UIElement* element, const char* text);
void UI_ChangeTextColor(UIElement* element, SDL_Color color);