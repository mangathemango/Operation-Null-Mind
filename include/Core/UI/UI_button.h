/**
 * @file UI_button.h
 * @brief Defines button components for the user interface system. (Not implemented)
 * @warning This file is not implemented
 * @author Mango
 * @date 2025-03-12
 */


#include <UI.h>

typedef struct {
    char* text;                      /// Button text
    SDL_Texture* textTexture;        /// Pre-rendered text
    SDL_Texture* normalTexture;      /// Default state
    SDL_Texture* hoverTexture;       /// Mouse-over state
    SDL_Texture* pressedTexture;     /// Pressed state
    SDL_Texture* disabledTexture;    /// Disabled state
    void (*onClick)(void);           /// Click callback function
} UI_ButtonData;
