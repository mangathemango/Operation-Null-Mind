#include <app.h>

/*
*   @file app_data.c
*   [Data] This file contains the app's data initialization.

?   Written by Mango on 28/02/2025
*/

AppData app = {
    .resources = {
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
        .screen_height = 288 ,
        
        .textFontPath = "Assets/Fonts/Micro5-Regular.ttf",
    },
};