#pragma once

#include <SDL.h>
#include <vec2.h>

#pragma once

#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>

/*
*   UI Element Types
?   Used to determine what kind of UI element we're dealing with
?   Each type has specific behaviors and rendering methods
*/
typedef enum {
    UI_ELEMENT_NONE,
    UI_ELEMENT_PANEL,
    UI_ELEMENT_BUTTON,
    UI_ELEMENT_LABEL,
    UI_ELEMENT_CHECKBOX,
    UI_ELEMENT_SLIDER,
    UI_ELEMENT_TEXT,
    UI_ELEMENT_IMAGE
} UIElementType;

// Forward declaration to avoid circular dependency
typedef struct UIElement UIElement;

/*
*   UI Element
?   Base structure for all UI elements
?   Contains common properties and callbacks for different element types
*/
struct UIElement {
    UIElementType type;        // Type of UI element
    SDL_Rect rect;             // Position and size
    bool visible;              // Is this element visible?
    bool enabled;              // Is this element interactive?
    bool hovered;              // Is mouse over this element?
    bool pressed;              // Is mouse button pressed on this element?
    
    // Rendering properties
    SDL_Rect srcRect;          // Source rectangle for texture (NULL for entire texture)
    SDL_Rect dstRect;          // Destination rectangle for rendering
    SDL_Rect textureSize;      // Texture size
    SDL_Color color;           // Color tint/modulation
    float scale;               // Scale factor for the texture

    // Parent-child relationship (for layout)
    UIElement* parent;         // Parent element (NULL for root elements)
    UIElement** children;      // Array of child elements
    int childCount;            // Number of children
    
    // Element-specific data (depends on type)
    void* data;                
    
    // Callbacks 
    void (*render)(UIElement* self);                      // Render function
    void (*update)(UIElement* self);                      // Update logic
    void (*cleanup)(UIElement* self);                     // Free resources
};

// Core UI element functions
UIElement* UI_CreateElement(UIElementType type, SDL_Rect rect);
void UI_DestroyElement(UIElement* element);
void UI_RenderElement(UIElement* element);
bool UI_HandleElementEvent(UIElement* element, SDL_Event* event);
void UI_UpdateElement(UIElement* element);

// Element creation helpers
UIElement* UI_CreateButton(SDL_Rect rect, const char* text, void (*onClick)(void));

// Existing text rendering functions
SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color);
void UI_RenderTextureText(SDL_Texture* texture, Vec2 destPosition, float scale);
void UI_InefficientlyRenderText(const char* text, SDL_Rect rect, SDL_Color color);