/**
 * @file app.h
 * @brief This file contains the definition of the AppData struct, and the 6 main routine functions inside main.c
 * 
 * @author Mango (杜明日) 
 * @date 2025-03-22
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <debug.h>

#include <gun.h>
#include <player.h>
#include <time_system.h>
#include <particle_emitterpresets.h>
#include <UI.h>
#include <menu.h>
#include <chunks.h>
#include <camera.h>
#include <maps.h>
#include <enemy.h>
#include <pause.h>
#include <minimap.h>
#include <interactable.h>
#include <logs.h>
#include <hud.h>
#include <game.h>
#include <death.h>

/**
 * @brief An enum containing the app's scenes, like the menu, game, and pause scene.
 * 
 * Example for how to handle app scenes in src/App/app_postupdate.c
 * ```
 * switch (app.state.currentScene)
 * {
 *    case SCENE_MENU:  // Updates the menu logic
 *    case SCENE_GAME:  // Updates the game logic
 *    case SCENE_PAUSE: // Updates the pause logic
 * }
 * ```
 */
typedef enum {
    SCENE_MENU,    /**< Menu scene of the application */
    SCENE_GAME,    /**< Main gameplay scene */
    SCENE_PAUSE,    /**< Pause menu scene */
    SCENE_DEATH /**Death scene */
} AppScene;

/**
 * @brief A struct containing the app's resources like the window, renderer, and fonts.
 */
typedef struct {
    SDL_Window* window; /**< The SDL window */
    SDL_Renderer* renderer; /**< The SDL renderer */
    SDL_Texture* screenTexture; /**< The screen texture */
    TTF_Font* textFont; /**< The font for text */
    TTF_Font* title1Font; /**< The font for title 1 */
    TTF_Font* title2Font; /**< The font for title 2 */
} AppResources;

/**
 * @brief A struct containing the app's states like fps, current scene, and a flag for running.
 */
typedef struct {
    bool running; /**< Flag indicating if the app is running */
    int fps; /**< The current frames per second */
    int averageFps; /**< The average frames per second */
    AppScene currentScene; /**< The current scene */
} AppState;

/**
 * @brief A struct containing the app's configurations like window size, title, and fullscreen mode.
 */
typedef struct {
    char* window_title; /**< The window title */
    int window_width; /**< The window width */
    int window_height; /**< The window height */
    bool window_fullscreen; /**< Flag indicating if the window is fullscreen */
    int screen_width; /**< The screen width */
    int screen_height; /**< The screen height */

    bool debug; /**< Flag indicating if debug mode is enabled */
    
    char* title1FontPath; /**< The file path for title 1 font */
    char* title2FontPath; /**< The file path for title 2 font */
    char* textFontPath; /**< The file path for text font */
} AppConfig;

/**
 * @brief A struct containing the app's resources, state, and configurations. Used by the app variable.
 */
typedef struct {
    AppResources resources; /**< The app's resources */
    AppState state; /**< The app's state */
    AppConfig config; /**< The app's configurations */
} AppData;

/**
 * @brief A global variable containing the app's resources, state, and configurations.
 * @details Used throughout the application to access central app data.
 * 
 * ```c
 * // Example usages:
 * if (event == SDL_QUIT) app.state.running = false;
 * SDL_SetWindowTitle(app.resources.window, app.config.window_title);
 * SDL_RenderPresent(app.resources.renderer);
 * ```
 */
extern AppData app;

/**
 * @brief Initializes the app and starts the game loop
 * 
 * @return int Status code (0 for success, non-zero for error)
 */
int App_Start();

/**
 * @brief Performs operations before updating the current scene
 * 
 * @return int Status code (0 for success, non-zero for error)
 */
int App_PreUpdate();

/**
 * @brief Performs operations after updating the current scene
 * 
 * @return int Status code (0 for success, non-zero for error)
 */
int App_PostUpdate();

/**
 * @brief Renders the current scene to the screen
 * 
 * @return int Status code (0 for success, non-zero for error)
 */
int App_Render();

/**
 * @brief Handles SDL events
 * 
 * @param[in] event Pointer to the SDL event to handle
 * @return int Status code (0 for success, non-zero for error)
 */
int App_Event_Handler(SDL_Event *event);

/**
 * @brief Cleans up resources and quits the application
 * 
 * @return int Status code (0 for success, non-zero for error)
 */
int App_Quit();