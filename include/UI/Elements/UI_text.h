#pragma once

#include <UI.h>
#include <SDL_ttf.h>

typedef enum {
    UI_TEXT_ALIGN_LEFT,
    UI_TEXT_ALIGN_CENTER,
    UI_TEXT_ALIGN_RIGHT
} UI_TextAlignment;

typedef struct {
    char* text;
    SDL_Texture* textTexture;
    TTF_Font* font;
    UI_TextAlignment alignment; 
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