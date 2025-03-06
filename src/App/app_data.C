#include <app.h>

/*
*   @file app_data.c
*   This file contains the app's data initialization.
*/

AppData app = {
    .setup = {
        .window = NULL,
        .renderer = NULL,
        .screenTexture = NULL,
    },
    .state = {
        .running = true,
    },
    .config = {
        .window_title = "Operation Ruinam Dei" ,
        .window_width = 1024 ,
        .window_height = 768 ,
        .window_fullscreen = false ,
        .screen_width = 480 ,
        .screen_height = 288 
    },

    .time = {
        .deltaTime = 0
    }
};