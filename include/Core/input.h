/*
    @file input.h
*   This file contains the input struct and its functions.
?   This struct is used to keep track of the mouse and keyboard input.
?   This is so that every other file can access the input data without using the SDL_Event parameter.
*/

#ifndef INPUT_H
#define INPUT_H    
#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>

typedef struct {
    /* Value is True on the FIRST frame the button is pressed */
    bool pressed;   
    /* Value is True on the FIRST frame the button is released */
    bool released;  
    /* Value is True on EVERY frame the button is pressed */
    bool held;      
} ButtonState;

typedef struct {
    /* Position of the mouse */
    Vec2 position;
    /* Motion of the mouse */          
    Vec2 motion;
    /* State of the left mouse button - either pressed, released, or held */
    ButtonState leftButton;     
    /* State of the right mouse button - either pressed, released, or held */
    ButtonState rightButton;    
    /* State of the middle mouse button - either pressed, released, or held */
    ButtonState middleButton;   
    /* Value is True when the scroll wheel is scrolled up */
    bool scrollUp;           
    /* Value is True when the scroll wheel is scrolled down */   
    bool scrollDown;           
} MouseState;

typedef struct {
    ButtonState keys[SDL_NUM_SCANCODES];
} KeyboardState;

    
typedef struct {
    /* State of the mouse */
    MouseState mouse;
    /* State of the keyboard */
    KeyboardState keyboard;
} InputEvent;

extern const InputEvent * const Input;

void Input_PreUpdate();
void Input_Event_Handler(SDL_Event *event);

#endif