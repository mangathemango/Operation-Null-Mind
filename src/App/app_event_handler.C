#include <app.h>
#include <input.h>

/**
 * @brief [Event Handler] Processes SDL events 
 * 
 * This function is called whenever an event (mouse click, key press, ...) is detected.
 * Calls before App_PostUpdate() and after App_PreUpdate().
 * 
 * Note: Every child function of this function should also pass in (SDL_Event *event) as a parameter.
 * 
 * @param event The SDL event to process
 * @return int Status code (0 for success)
 */
int App_Event_Handler(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        app.state.running = 0;
    }
    Input_Event_Handler(event);
    return 0;
}


