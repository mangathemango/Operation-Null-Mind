/**
 * @file input.c
 * @brief Input handling system
 *
 * Manages keyboard, mouse and controller input,
 * providing a consistent interface for detecting
 * button presses, releases, and held states.
 *
 * @author Mango
 * @date 2025-03-06
 */

//? Updated by Mango on 06/03/2025

#include <input.h>
#include <app.h>
#include <stdio.h>
#include <SDL_filesystem.h>
#include <settings.h>

static InputEvent _input;
const InputEvent * const Input = &_input; // This ensures that the Input variable is read-only to other files.

// Add previous frame state tracking
static bool wasHeld[SDL_NUM_SCANCODES];
static bool mouseWasHeld[3];  // For left, right, middle buttons

/**
 * @brief Presses a button
 *
 * @param button The button to press. Can either be a key button or a mouse button
 */
void Press_Button(ButtonState *button) {
    button->pressed = !button->held;  // Only true if wasn't held last frame
    button->held = true;
    button->released = false;
}

/**
 * @brief Releases a button
 *
 * @param button The button to release. Can either be a key button or a mouse button
 */
void Release_Button(ButtonState *button) {
    button->released = button->held;  // Only true if was held last frame
    button->held = false;
    button->pressed = false;
}

/**
 * @brief Resets a button's pressed and released states
 *
 * This function is called every frame to ensure that the button's pressed and released 
 * states are only true for one frame.
 *
 * @param button The button to release. Can either be a key button or a mouse button
 */
void Reset_Button(ButtonState *button) {
    button->pressed = false;
    button->released = false;
}

// Helper function to update action states based on bindings
static void UpdateActionState(GameAction action) {
    ActionBinding* binding = &_input.bindings[action];
    
    if (binding->isMouse) {
        // For mouse bindings, point to mouse button state
        switch (binding->mouseButton) {
            case SDL_BUTTON_LEFT:
                _input.actions[action] = &_input.mouse.leftButton;
                break;
            case SDL_BUTTON_RIGHT:
                _input.actions[action] = &_input.mouse.rightButton;
                break;
            case SDL_BUTTON_MIDDLE:
                _input.actions[action] = &_input.mouse.middleButton;
                break;
            default:
                _input.actions[action] = NULL;
                break;
        }
    } else {
        // For keyboard bindings, point to keyboard key state
        if (binding->primary != SDL_SCANCODE_UNKNOWN) {
            _input.actions[action] = &_input.keyboard.keys[binding->primary];
        } else {
            _input.actions[action] = NULL;
        }
    }
}

/**
 * @brief This function is called inside App_PreUpdate()
 *
 * It retrieves the mouse's state and resets all the mouse/keyboard buttons.
 */
void Input_PreUpdate() {
    // Store previous frame's held states
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        wasHeld[i] = _input.keyboard.keys[i].held;
    }
    mouseWasHeld[0] = _input.mouse.leftButton.held;
    mouseWasHeld[1] = _input.mouse.rightButton.held;
    mouseWasHeld[2] = _input.mouse.middleButton.held;

    // Reset pressed/released states (they only last one frame)
    Reset_Button(&_input.mouse.leftButton);
    Reset_Button(&_input.mouse.rightButton);
    Reset_Button(&_input.mouse.middleButton);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        Reset_Button(&_input.keyboard.keys[i]);
    }

    // Preserve held states from last frame
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        _input.keyboard.keys[i].held = wasHeld[i];
    }
    _input.mouse.leftButton.held = mouseWasHeld[0];
    _input.mouse.rightButton.held = mouseWasHeld[1];
    _input.mouse.middleButton.held = mouseWasHeld[2];

    // Reset and update anyKey state
    Reset_Button(&_input.anyKey);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        if (_input.keyboard.keys[i].pressed) _input.anyKey.pressed = true;
        if (_input.keyboard.keys[i].released) _input.anyKey.released = true;
        if (_input.keyboard.keys[i].held) _input.anyKey.held = true;
    }

    // Reset other input states
    _input.mouse.scrollUp = false;
    _input.mouse.scrollDown = false;
    _input.mouse.motion = (Vec2) {0, 0};
    
    // Update mouse position
    int windowMouseX, windowMouseY;
    SDL_GetMouseState(&windowMouseX, &windowMouseY);
    float screenMouseX, screenMouseY;
    SDL_RenderWindowToLogical(app.resources.renderer, windowMouseX, windowMouseY, &screenMouseX, &screenMouseY);
    _input.mouse.position = (Vec2){screenMouseX, screenMouseY};

    // Update game action states
    for (int i = 0; i < ACTION_COUNT; i++) {
        UpdateActionState(i);
    }
}


/**
 * @brief This function is called inside App_Event_Handler()
 *
 * It updates the InputEvent struct based on the SDL_Event.
 *
 * @param event The SDL_Event to update the InputEvent struct with
 */
void Input_Event_Handler(SDL_Event *event) {
    switch (event->type) {
    case SDL_MOUSEMOTION:
        _input.mouse.position.x = event->motion.x;
        _input.mouse.position.y = event->motion.y;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button == SDL_BUTTON_LEFT)   Press_Button(&_input.mouse.leftButton);
        if (event->button.button == SDL_BUTTON_RIGHT)  Press_Button(&_input.mouse.rightButton);
        if (event->button.button == SDL_BUTTON_MIDDLE) Press_Button(&_input.mouse.middleButton);
        break;
    case SDL_MOUSEBUTTONUP:
        if (event->button.button == SDL_BUTTON_LEFT)   Release_Button(&_input.mouse.leftButton);
        if (event->button.button == SDL_BUTTON_RIGHT)  Release_Button(&_input.mouse.rightButton);
        if (event->button.button == SDL_BUTTON_MIDDLE) Release_Button(&_input.mouse.middleButton);
        break;
    case SDL_MOUSEWHEEL:
        if (event->wheel.y > 0) _input.mouse.scrollUp = true;
        if (event->wheel.y < 0) _input.mouse.scrollDown = true;
        break;
    case SDL_KEYDOWN:
        // Handle modifier keys specially
        if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT || 
            event->key.keysym.scancode == SDL_SCANCODE_RSHIFT) {
            if (!event->key.repeat) {
                Press_Button(&_input.keyboard.keys[event->key.keysym.scancode]);
            }
        } else {
            Press_Button(&_input.keyboard.keys[event->key.keysym.scancode]);
        }
        break;
    case SDL_KEYUP:
        Release_Button(&_input.keyboard.keys[event->key.keysym.scancode]);
        break;
    }
}

/**
 * @brief Checks if the mouse is positioned over a rectangle
 *
 * @param rect The rectangle to check
 * @return true if mouse is over the rectangle, false otherwise
 */
bool Input_MouseIsOnRect(SDL_Rect rect) {
    return (_input.mouse.position.x >= rect.x && _input.mouse.position.x <= rect.x + rect.w &&
            _input.mouse.position.y >= rect.y && _input.mouse.position.y <= rect.y + rect.h);
}

// Initialize default bindings
void Input_Init() {
    // Initialize default bindings
    _input.bindings[ACTION_MOVE_UP] = (ActionBinding){
        .label = "Move Up",
        .primary = SDL_SCANCODE_W,
        .isMouse = false
    };
    _input.bindings[ACTION_MOVE_LEFT] = (ActionBinding){
        .label = "Move Left",
        .primary = SDL_SCANCODE_A,
        .isMouse = false
    };
    _input.bindings[ACTION_MOVE_DOWN] = (ActionBinding){
        .label = "Move Down",
        .primary = SDL_SCANCODE_S,
        .isMouse = false
    };
    _input.bindings[ACTION_MOVE_RIGHT] = (ActionBinding){
        .label = "Move Right",
        .primary = SDL_SCANCODE_D,
        .isMouse = false
    };

    // Actions
    _input.bindings[ACTION_DASH] = (ActionBinding){
        .label = "Dash",
        .primary = SDL_SCANCODE_LSHIFT,
        .isMouse = false
    };
    _input.bindings[ACTION_CRASH_OUT] = (ActionBinding){
        .label = "Crash Out",
        .primary = SDL_SCANCODE_LCTRL,
        .isMouse = false
    };
    _input.bindings[ACTION_SWITCH_GUN] = (ActionBinding){
        .label = "Switch Gun",
        .primary = SDL_SCANCODE_Q,
        .isMouse = false
    };
    _input.bindings[ACTION_SHOOT] = (ActionBinding){
        .label = "Shoot",
        .primary = SDL_SCANCODE_UNKNOWN,
        .isMouse = true,
        .mouseButton = SDL_BUTTON_LEFT
    };
    _input.bindings[ACTION_PARRY] = (ActionBinding){
        .label = "Parry",
        .primary = SDL_SCANCODE_UNKNOWN,
        .isMouse = true,
        .mouseButton = SDL_BUTTON_RIGHT
    };

    // UI Controls
    _input.bindings[ACTION_INTERACT] = (ActionBinding){
        .label = "Interact",
        .primary = SDL_SCANCODE_E,
        .isMouse = false
    };
    _input.bindings[ACTION_TOGGLE_HUD] = (ActionBinding){
        .label = "Toggle HUD",
        .primary = SDL_SCANCODE_TAB,
        .isMouse = false
    };
    _input.bindings[ACTION_TOGGLE_FULLSCREEN] = (ActionBinding){
        .label = "Toggle Fullscreen",
        .primary = SDL_SCANCODE_F11,
        .isMouse = false
    };
    _input.bindings[ACTION_PAUSE] = (ActionBinding){
        .label = "Pause",
        .primary = SDL_SCANCODE_ESCAPE,
        .isMouse = false
    };

    // Initialize previous state arrays
    memset(wasHeld, 0, sizeof(wasHeld));
    memset(mouseWasHeld, 0, sizeof(mouseWasHeld));
    
    // Note: Settings_Load() will load the bindings, no need to load here
}


// Helper function to save bindings data
void Input_SaveBindings(FILE* file) {
    if (file) {
        fwrite(_input.bindings, sizeof(ActionBinding), ACTION_COUNT, file);
    }
}

// Helper function to load bindings data  
void Input_LoadBindings(FILE* file) {
    return;
    if (file) {
        if (fread(_input.bindings, sizeof(ActionBinding), ACTION_COUNT, file) != ACTION_COUNT) {
            SDL_Log("Failed to read key bindings");
        }
    }
}

bool Input_IsActionPressed(GameAction action) {
    const ButtonState* state = _input.actions[action];
    if (state && state->pressed) {
        SDL_Log("Action %s pressed", _input.bindings[action].label);
        return true;
    }
    return false;
}

bool Input_IsActionHeld(GameAction action) {
    const ButtonState* state = _input.actions[action];
    if (state && state->held) {
        return true;
    }
    return false;
}

bool Input_IsActionReleased(GameAction action) {
    const ButtonState* state = _input.actions[action];
    return state ? state->released : false;
}

void Input_SetBinding(GameAction action, SDL_Scancode key) {
    _input.bindings[action].primary = key;
}

SDL_Scancode Input_GetBinding(GameAction action) {
    return _input.bindings[action].primary;
}

const char* Input_GetActionName(GameAction action) {
    return _input.bindings[action].label;
}