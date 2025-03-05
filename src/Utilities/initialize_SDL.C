#include <initialize_SDL.h>

/*
*   Initializes everything related to SDL: window, renderer, image loading, and so on.
*/
int Initialize_SDL() {
    // Initialize SDL and SDL_image
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    // Set up window
    app.setup.window = SDL_CreateWindow(
        app.config.window_title,                                                // Set window title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                         // Centers the window
        app.config.window_width, app.config.window_height,                      // Set window size
        app.config.window_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);      // Set fullscreen
    
    if (!app.setup.window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_RaiseWindow(app.setup.window);                                          


    // Set up renderer
    app.setup.renderer = SDL_CreateRenderer(app.setup.window, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    
    if (!app.setup.renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 1;
    }


    SDL_RenderSetLogicalSize(app.setup.renderer, app.config.screen_width, app.config.screen_height);

    SDL_SetRenderDrawBlendMode(app.setup.renderer, SDL_BLENDMODE_BLEND);

    return 0;
}