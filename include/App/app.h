/**
 * @file app.h
 * @brief This file contains the definition of the app's resources, state, and configuration structs.
 * 
 * @author Mango (杜明日) 
 * @date 2025-03-22
 */

#ifndef APP_H
#define APP_H

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

/**
 * @brief An enum containing the app's scenes, like the menu, game, and pause scene.
 * 
 * @example src/App/app_postupdate.c
 * ```c
 * switch (app.state.currentScene)
 * {
 *    case SCENE_MENU:  // Updates the menu logic
 *    case SCENE_GAME:  // Updates the game logic
 *    case SCENE_PAUSE: // Updates the pause logic
 * }
 * ```
 */
typedef enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_PAUSE
} AppScene;

/**
 * @brief A struct containing the app's resources like the window, renderer, and fonts.
 */
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screenTexture;
    TTF_Font* textFont;
    TTF_Font* title1Font;
    TTF_Font* title2Font;
} AppResources;

/**
 * @brief A struct containing the app's states like fps, current scene, and a flag for running.
 */
typedef struct {
    bool running;
    int fps;
    int averageFps;
    AppScene currentScene;
} AppState;

/**
 * @brief A struct containing the app's configurations like window size, title, and fullscreen mode.
 */
typedef struct {
    char* window_title;
    int window_width;
    int window_height;
    bool window_fullscreen;
    int screen_width;
    int screen_height;

    bool debug;
    
    char* title1FontPath;
    char* title2FontPath;
    char* textFontPath;     
} AppConfig;

/**
 * @brief A struct containing the app's resources, state, and configurations. Used by the app variable.
 */
typedef struct {
    AppResources resources;
    AppState state;
    AppConfig config;
} AppData;

/**
 * @brief A global variable containing the app's resources, state, and configurations.
 * ```c
 * // Example usages:
 * if (event == SDL_QUIT) app.state.running = false;
 * SDL_SetWindowTitle(app.resources.window, app.config.window_title);
 * SDL_RenderPresent(app.resources.renderer);
 * ```
 */
extern AppData app;

int App_Start();
int App_PreUpdate();
int App_PostUpdate();
int App_Render();
int App_Event_Handler(SDL_Event *event);
int App_Quit();


#endif //APP_H