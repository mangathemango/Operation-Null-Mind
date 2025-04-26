/**
 * @file input.h
 * @brief Handles mouse and keyboard input processing for the game.
 * 
 * This struct is used to keep track of the mouse and keyboard input.
 * This is so that every other file can access the input data without using the SDL_Event parameter.
 * @section usage Usage Examples
 * ```c
 * Input->mouse.position // Returns screen position of the mouse
 * Input->keyboard.keys[SDL_SCANCODE_A].pressed // Returns true on the first frame A key is pressed
 * Input->keyboard.keys[SDL_SCANCODE_ESC].held // Returns true on every frame esc key is held
 * Input->mouse.leftButton.released // Returns true on the first frame the left mouse button is released.
 * ```
 * @author Mango
 * @date 2025-02-28
 */

#ifndef INPUT_H
#define INPUT_H    
#include <SDL.h>
#include <vec2.h>
#include <stdbool.h>
#include <stdio.h>

// Game actions that can be bound to keys
typedef enum {
    ACTION_MOVE_UP,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_RIGHT,
    ACTION_DASH,
    ACTION_SWITCH_GUN,
    ACTION_SHOOT,        // Mouse left button
    ACTION_PARRY,        // Mouse right button
    ACTION_INTERACT,     // E key
    ACTION_TOGGLE_HUD,   // Tab key
    ACTION_TOGGLE_FULLSCREEN, // F11
    ACTION_PAUSE,        // Escape key
    ACTION_COUNT
} GameAction;

typedef struct ButtonState {
    bool pressed;   // Value is True on the FIRST frame the button is pressed
    bool released;  // Value is True on the FIRST frame the button is released
    bool held;      // Value is True on EVERY frame the button is pressed
} ButtonState;

typedef struct MouseState {
    Vec2 position;          // Position of the mouse
    Vec2 motion;            // Motion of the mouse
    ButtonState leftButton;     // State of the left mouse button - either pressed, released, or held
    ButtonState rightButton;    // State of the right mouse button - either pressed, released, or held
    ButtonState middleButton;   // State of the middle mouse button - either pressed, released, or held
    bool scrollUp;              // Value is True when the scroll wheel is scrolled up
    bool scrollDown;            // Value is True when the scroll wheel is scrolled down
} MouseState;

typedef struct KeyboardState {
    ButtonState keys[SDL_NUM_SCANCODES];
} KeyboardState;

typedef struct ActionBinding {
    const char* label;        // Display name of the action
    SDL_Scancode primary;     // Key binding
    bool isMouse;            // Whether this is a mouse button binding
    int mouseButton;         // SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT etc if isMouse is true
} ActionBinding;

typedef struct InputEvent {
    MouseState mouse;       // State of the mouse
    KeyboardState keyboard; // State of the keyboard
    ButtonState anyKey;     // State of any key - pressed, released, or held
    const ButtonState* actions[ACTION_COUNT];  // Pointers to button states for each action
    ActionBinding bindings[ACTION_COUNT]; // Key bindings for each action
} InputEvent;

extern const InputEvent * const Input;

void Input_Init();
void Input_PreUpdate();
void Input_Event_Handler(SDL_Event *event);
bool Input_MouseIsOnRect(SDL_Rect rect);

// Action state getters
bool Input_IsActionPressed(GameAction action);
bool Input_IsActionHeld(GameAction action);
bool Input_IsActionReleased(GameAction action);

// Binding management
void Input_SetBinding(GameAction action, SDL_Scancode key);
SDL_Scancode Input_GetBinding(GameAction action);
const char* Input_GetActionName(GameAction action);
void Input_SaveBindings(FILE* file);
void Input_LoadBindings(FILE* file);

#endif