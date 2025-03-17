/*
    @file input.h
*   This file contains the input struct and its functions.
?   This struct is used to keep track of the mouse and keyboard input.
?   This is so that every other file can access the input data without using the SDL_Event parameter.

?   Written by Mango on 28/02/2025
*/

#ifndef INPUT_H
#define INPUT_H    
#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>

typedef struct {
    bool pressed;   // Value is True on the FIRST frame the button is pressed
    bool released;  // Value is True on the FIRST frame the button is released
    bool held;      // Value is True on EVERY frame the button is pressed
} ButtonState;

typedef struct {
    Vec2 position;          // Position of the mouse
    Vec2 motion;            // Motion of the mouse
    ButtonState leftButton;     // State of the left mouse button - either pressed, released, or held
    ButtonState rightButton;    // State of the right mouse button - either pressed, released, or held
    ButtonState middleButton;   // State of the middle mouse button - either pressed, released, or held
    bool scrollUp;              // Value is True when the scroll wheel is scrolled up
    bool scrollDown;            // Value is True when the scroll wheel is scrolled down
} MouseState;

typedef struct {
    ButtonState keys[SDL_NUM_SCANCODES];
} KeyboardState;

    
typedef struct {
    MouseState mouse;       // State of the mouse
    KeyboardState keyboard; // State of the keyboard
} InputEvent;

extern const InputEvent * const Input;

void Input_PreUpdate();
void Input_Event_Handler(SDL_Event *event);

bool Input_MouseIsOnRect(SDL_Rect rect);
#endif