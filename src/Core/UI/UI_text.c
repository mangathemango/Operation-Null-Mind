/**
 * @file UI_text.c
 * @brief Text rendering and management for UI elements
 *
 * Provides functionality for creating, updating, and rendering
 * text elements in the user interface.
 *
 * @author Mango
 * @date 2025-03-02
 */

#include <UI_text.h>
#include <string.h>
#include <input.h>
#include <app.h>

/*
*   [Start] Creates a text UIElement based on some parameters.
    @param text The text content
    @param rect The position and size of the text (x, y, w, h). (Actually right now the w and h doesnt matter lmao)
    @param color The color of the text

*/
UIElement* UI_CreateText(const char* text, SDL_Rect rect, 
                SDL_Color color, float scale, UI_TextAlignment alignment,
                TTF_Font* font) {
    UIElement* element = malloc(sizeof(UIElement));
    if (!element) return NULL;
    
    UI_TextData* data = malloc(sizeof(UI_TextData));
    if (!data) {
        free(element);
        return NULL;
    }
    
    data->text = strdup(text);
    data->textTexture = UI_CreateTextTexture(text, color, font);
    data->alignment = alignment;
    data->font = font;
    
    element->type = UI_ELEMENT_TEXT;
    element->rect = rect;
    element->visible = true;
    element->enabled = true;
    element->hovered = false;
    element->pressed = false;
    element->srcRect = (SDL_Rect) {0,0,0,0};
    element->dstRect = (SDL_Rect) {0,0,0,0};
    element->textureSize = (SDL_Rect) {0,0,0,0};
    SDL_QueryTexture(data->textTexture, NULL, NULL, &element->textureSize.w, &element->textureSize.h);
    element->color = color;
    element->scale = scale;
    element->data = data;
    element->render = NULL;
    element->update = UI_UpdateText;
    element->cleanup = NULL;
    
    UI_UpdateText(element);
    return element;
}


SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) return NULL;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.resources.renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;  // Caller is responsible for freeing
}

void UI_UpdateText(UIElement* element) {
    UI_TextData* data = element->data;
    SDL_QueryTexture(data->textTexture, NULL, NULL, &element->textureSize.w, &element->textureSize.h);
    element->dstRect = (SDL_Rect) {
        element->rect.x,
        element->rect.y,
        element->textureSize.w * element->scale,
        element->textureSize.h * element->scale
    };
    switch (data->alignment)
    {
    case UI_TEXT_ALIGN_CENTER:
        element->dstRect.x -= element->dstRect.w / 2;
        break;
    case UI_TEXT_ALIGN_RIGHT:
        element->dstRect.x -= element->dstRect.w;
        break;
    case UI_TEXT_ALIGN_LEFT:
        break;
    }
    if (Input_MouseIsOnRect(element->dstRect)) {
        element->hovered = true;
        element->pressed = Input->mouse.leftButton.pressed;
    } else {
        element->hovered = false;
        element->pressed = false;
    }
}

void UI_RenderText(UIElement* element) {
    UI_TextData* data = element->data;
    SDL_RenderCopy(app.resources.renderer, data->textTexture, NULL, &element->dstRect);
}

void UI_DestroyText(UIElement* element) {
    UI_TextData* data = element->data;
    if (data) {
        free(data->text);
        SDL_DestroyTexture(data->textTexture);
        free(data);
    }
    free(element);
}

void UI_ChangeText(UIElement* element, const char* text) {
    UI_TextData* data = element->data;
    if (strcmp(text, data->text) == 0) return;
    free(data->text);
    data->text = strdup(text);
    SDL_DestroyTexture(data->textTexture);
    data->textTexture = UI_CreateTextTexture(text, element->color, data->font);
}

void UI_ChangeTextColor(UIElement* element, SDL_Color color) {
    if (element->color.r == color.r && 
        element->color.g == color.g && 
        element->color.b == color.b && 
        element->color.a == color.a) return;
    UI_TextData* data = element->data;
    element->color = color;
    SDL_DestroyTexture(data->textTexture);
    data->textTexture = UI_CreateTextTexture(data->text, color, data->font);
}