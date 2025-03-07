#define SDL_MAIN_HANDLED 1
#include <windows.h>
#include <SDL.h>
#include <app.h>
#include <player.h>
#include <environment.h>

/* 
*    This is the entry point of the program. It's similar to the main() function in standard C.
?    Each program will call the following functions in this order:
?       App_Start() -> loop [ App_PreUpdate() -> App_Event_Handler() -> App_PostUpdate() -> App_Render] -> App_Quit()
?    Each of these functions can be found inside src/App/
!   This is a windows specific function. Also ignore all the WINAPI and HINSTANCE stuff it prolly does nothing.
    TODO: Replace return values with an App_Result enum.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (App_Start()) return 1;

    SDL_Event event;
    while (app.state.running) {
        if(App_PreUpdate()) return 1;
        while (SDL_PollEvent(&event)) {
            if(App_Event_Handler(&event)) return 1;
        }
        if(App_PostUpdate()) return 1; // Ensure this line is present to call App_PostUpdate
        if(App_Render()) return 1;
    }

    App_Quit();
    return 0;
}