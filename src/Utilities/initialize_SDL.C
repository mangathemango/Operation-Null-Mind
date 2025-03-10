// Written by Mango on 28/02/2025

#include <initialize_SDL.h>

/*
*   [Start] Initializes everything related to SDL: window, renderer, image loading, and so on.
*/
int Initialize_SDL() {
    // Initialize SDL and SDL_image
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // Set up window
    app.resources.window = SDL_CreateWindow(
        app.config.window_title,                                                // Set window title
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,                         // Centers the window
        app.config.window_width, app.config.window_height,                      // Set window size
        app.config.window_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);      // Set fullscreen
    
    if (!app.resources.window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_RaiseWindow(app.resources.window);                                          


    // Set up renderer
    app.resources.renderer = SDL_CreateRenderer(app.resources.window, -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    
    if (!app.resources.renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 1;
    }

    SDL_RenderSetLogicalSize(app.resources.renderer, app.config.screen_width, app.config.screen_height);
    SDL_SetRenderDrawBlendMode(app.resources.renderer, SDL_BLENDMODE_BLEND);

    // Load font
    app.resources.textFont = TTF_OpenFont(app.config.textFontPath, 20);
    if (app.resources.textFont == NULL) {
        SDL_Log("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }
    return 0;
}