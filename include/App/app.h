/*
    @file app.h
*   This file contains the app struct and its functions.
?   The app struct is used to keep track of the app's setup, state, and configuration.
?   For example, the window, renderer, screen size, and a running state.
*/

#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#include <gun.h>
#include <player.h>
#include <time_system.h>
#include <particle_emitterpresets.h>
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screenTexture;
} AppSetup;

typedef struct {
    bool running;
} AppState;

typedef struct {
    char* window_title;
    int window_width;
    int window_height;
    bool window_fullscreen;
    int screen_width;
    int screen_height;
} AppConfig;

typedef struct {
    AppSetup setup;
    AppState state;
    AppConfig config;
} AppData;

extern AppData app;

int App_Start();
int App_PreUpdate();
int App_PostUpdate();
int App_Render();
int App_Event_Handler(SDL_Event *event);
int App_Quit();

#endif