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

static InputEvent _input;
const InputEvent * const Input = &_input; // This ensures that the Input variable is read-only to other files.

/**
 * @brief Presses a button
 *
 * @param button The button to press. Can either be a key button or a mouse button
 */
void Press_Button(ButtonState *button) {
    // Pressed is only true if the button was not held on the previous frame.
    if (!button->held) button->pressed = true;
    button->held = true; 
}

/**
 * @brief Releases a button
 *
 * @param button The button to release. Can either be a key button or a mouse button
 */
void Release_Button(ButtonState *button) {
    button->released = true;
    button->held = false; 
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


/**
 * @brief This function is called inside App_PreUpdate()
 *
 * It retrieves the mouse's state and resets all the mouse/keyboard buttons.
 */
void Input_PreUpdate() {
    // Reset all the buttons
    Reset_Button(&_input.mouse.leftButton);
    Reset_Button(&_input.mouse.rightButton);
    Reset_Button(&_input.mouse.middleButton);
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
        Reset_Button(&_input.keyboard.keys[i]);
    }

    // Reset the mouse scroll
    _input.mouse.scrollUp = false;
    _input.mouse.scrollDown = false;

    // Reset the mouse motion
    _input.mouse.motion = (Vec2) {0, 0};
    
    // Get mouse position
    int windowMouseX, windowMouseY;
    SDL_GetMouseState(&windowMouseX, &windowMouseY);
    float screenMouseX, screenMouseY;
    SDL_RenderWindowToLogical(app.resources.renderer, windowMouseX, windowMouseY, &screenMouseX, &screenMouseY);
    _input.mouse.position = (Vec2){screenMouseX, screenMouseY};
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
        Press_Button(&_input.keyboard.keys[event->key.keysym.scancode]);
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