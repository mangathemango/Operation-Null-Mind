/*
    @file UI_text.h
*   This file contains the declarations for the text UI element.
?   Text UI elements are used to display text on the screen.

?   There are three steps to making an UI text element: Create, Update, and Render.

?   To create: use the UI_CreateText() function. 
?       This will create a UIElement pointer, which should be stored in a static variable for reuse.

?   To update (optional): use the UI_UpdateText() function.
?       This can be skipped if the text is static, i.e the text doesnt change/move/resize.
?       Note: when the text element changes in text, size, or color, the texture for it will have to change.
?       Therefore, you have to use functions like UI_ChangeText or UI_ChangeTextColor to update the texture.
*   This sparks joy:        UI_ChangeTextColor(element, (SDL_Color) {255, 0, 0, 255});
!   This doesnt spark joy:  element->color = {255, 0, 0, 255};

?   And finally, to render: use the UI_RenderText() function.

?   Example on how this is done can be found in src/Utilities/debug.c, in the fps render function.
*/

#pragma once

#include <UI.h>
#include <SDL_ttf.h>

// This should be self-explanatory
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