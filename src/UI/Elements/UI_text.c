#include <UI_text.h>
#include <string.h>
#include <input.h>
#include <app.h>

UIElement* UI_CreateText(SDL_Rect rect, const char* text, SDL_Color color) {
    UIElement* element = malloc(sizeof(UIElement));
    if (!element) return NULL;
    
    UI_TextData* data = malloc(sizeof(UI_TextData));
    if (!data) {
        free(element);
        return NULL;
    }
    
    data->text = strdup(text);
    data->textTexture = UI_CreateTextTexture(text, color);
    data->alignment = UI_TEXT_ALIGN_LEFT;
    
    element->type = UI_ELEMENT_TEXT;
    element->rect = rect;
    element->visible = true;
    element->enabled = true;
    element->hovered = false;
    element->pressed = false;
    element->srcRect = (SDL_Rect) {0,0,0,0};
    element->color = color;
    element->scale = 1.0f;
    element->parent = NULL;
    element->children = NULL;
    element->childCount = 0;
    element->data = data;
    element->render = NULL;
    element->update = UI_UpdateText;
    element->cleanup = NULL;
    
    return element;
}

SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(app.resources.textFont, text, color);
    if (!surface) return NULL;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.resources.renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;  // Caller is responsible for freeing
}

void UI_UpdateText(UIElement* element) {
    UI_TextData* data = element->data;
    if (!data->textTexture) {
        data->textTexture = UI_CreateTextTexture(data->text, element->color);
    }
}