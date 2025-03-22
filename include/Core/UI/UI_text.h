/**
 * @file UI_button.h
 * @brief This file contains the definition of the UI_TextData struct. 
 * @author Mango (杜明日) 
 * @date 2025-03-12
 * 
 * @section usage Usage Examples
 * @example src/Utilities/debug.c:124-164 How the spike count text was created and rendered.
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

typedef struct {
    char* text;                 // Text to display
    SDL_Texture* textTexture;   // Pre-rendered text
    TTF_Font* font;             // Font used for rendering
    UI_TextAlignment alignment; // Either UI_Text_Align_Left, UI_Text_Align_Center, or UI_Text_Align_Right
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