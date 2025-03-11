#pragma once

#include <UI.h>

typedef enum {
    UI_TEXT_ALIGN_LEFT,
    UI_TEXT_ALIGN_CENTER,
    UI_TEXT_ALIGN_RIGHT
} UI_TextAlignment;

typedef struct {
    char* text;
    SDL_Texture* textTexture;
    UI_TextAlignment alignment; 
} UI_TextData;

UIElement* UI_CreateText(SDL_Rect rect, const char* text, SDL_Color color);
SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color);
void UI_UpdateText(UIElement* element);
void UI_RenderText(UIElement* element);
void UI_DestroyText(UIElement* element);