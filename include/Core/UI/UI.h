/**
 * @file UI.h
 * @brief Defines the base UI element structure for the user interface system.
 * @author Mango
 * @date 2025-03-12
 * 
 * @section usage Usage Examples
 * 
 * The UIElement struct being used as a base to render UI texts:
 * ```c
 * // Create a simple text element
 * static UIElement* titleText = UI_CreateText(
 *    "Operation Null Mind",
 *     (SDL_Rect){400, 100, 400, 50},   // Position and size
 *     (SDL_Color){255, 255, 255, 255}, // Color
 *     1.5f,                            // Scale
 *     UI_TEXT_ALIGN_CENTER,            // Alignment (Look at UI_TextAlignment enum)
 *     app.resources.fonts.titleFont    // Font
 * );
 * ```
 */

#pragma once

#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>

/**
 * @brief UI Element Types enumeration
 *
 * Used to determine what kind of UI element we're dealing with.
 * Each type has specific behaviors and rendering methods.
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

/**
 * @brief UI Element structure
 *
 * Base structure for all UI elements.
 * Contains common properties and callbacks for different element types.
 */
struct UIElement {
    /// Element-specific data (depends on type)
    UIElementType type;        /**< Type of UI element */
    void* data;                /**< Pointer to element-specific data. e.g, UI texts use a UI_TextData variable here */
    
    /// Common properties
    SDL_Rect rect;             /**< Position and size */
    bool visible;              /**< Is this element visible? */
    bool enabled;              /**< Is this element interactive? */
    bool hovered;              /**< Is mouse over this element? */
    bool pressed;              /**< Is mouse button pressed on this element? */
    
    /// Rendering properties
    SDL_Rect srcRect;          /**< Source rectangle for texture (NULL for entire texture) */
    SDL_Rect dstRect;          /**< Destination rectangle for rendering */
    SDL_Rect textureSize;      /**< Texture size */
    SDL_Color color;           /**< Color tint/modulation */
    float scale;               /**< Scale factor for the texture */
    
    // Callbacks 
    void (*render)(UIElement* self);      /**< Render function */
    void (*update)(UIElement* self);      /**< Update logic */
    void (*cleanup)(UIElement* self);     /**< Free resources */
};