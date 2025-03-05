/*
    @file initialize_SDL.h
*   This file contains the function that initializes SDL renderer, windows, and so on.
?   This thing is called only once inside App_Start(), so it's not a big deal.
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <app.h>

int Initialize_SDL();