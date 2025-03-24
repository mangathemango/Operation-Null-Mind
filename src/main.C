
/**
 * @file main.c
 * @brief Main entry point for the Operation Null Mind game
 *
 * @author Mango
 * @date 2025-03-01
 */

#define SDL_MAIN_HANDLED 1

#include <windows.h>
#include <SDL_main.h>
#include <app.h>
#include <player.h>

/**
 * @brief Entry point of the program
 * 
 * Each program will call the following functions in this order:
 * App_Start() -> loop [ App_PreUpdate() -> App_Event_Handler() -> App_PostUpdate() -> App_Render] -> App_Quit()
 * Each of these functions can be found inside src/App/
 * 
 * This is a windows specific function. Also ignore all the WINAPI and HINSTANCE stuff it probably does nothing.
 * 
 * @param hInstance Handle to the current instance of the application
 * @param hPrevInstance Unused parameter maintained for compatibility
 * @param lpCmdLine Command line arguments
 * @param nCmdShow Controls how the window is shown
 * @return int Status code (0 for success)
 * 
 * @todo Replace return values with an App_Result enum.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (App_Start()) return 1;

    SDL_Event event;
    while (app.state.running) {
        if(App_PreUpdate()) return 1;
        while (SDL_PollEvent(&event)) if(App_Event_Handler(&event)) return 1;
        if(App_PostUpdate()) return 1; // Ensure this line is present to call App_PostUpdate
        if(App_Render()) return 1;
    }
    App_Quit();
    return 0;
}