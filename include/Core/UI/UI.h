/*
    @file UI.h
*   This file contains the declarations for the UI system.
?   TLDR, it just provdes the UIElement struct for creating UI elements inside UI_Text and stuff.
*/

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
    
    // Element-specific data (depends on type)
    void* data;                
    
    // Callbacks 
    void (*render)(UIElement* self);                      // Render function
    void (*update)(UIElement* self);                      // Update logic
    void (*cleanup)(UIElement* self);                     // Free resources
};