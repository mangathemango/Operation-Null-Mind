/**
 * @file initialize_SDL.h
 * @brief This file contains the function that initializes SDL renderer, windows, and so on.
 *
 * This function is called only once inside App_Start(), so it's not a big deal.
 *
 * @author Mango
 * @date 2025-02-28
 */

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <app.h>
#include <SDL_mixer.h>

/**
 * @brief Initializes SDL and its subsystems.
 * @return 0 on success, -1 on failure.
 */
int Initialize_SDL();