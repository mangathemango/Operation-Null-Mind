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
        .fps = 0,
        .currentScene = SCENE_MENU,
    },
    .config = {
        .window_title = "Operation Null Mind" ,
        .window_width = 1024 ,
        .window_height = 768 ,
        .window_fullscreen = false ,
        .screen_width = 480 ,
        .screen_height = 288 ,
        
        .title1FontPath = "Assets/Fonts/Bore Blasters 16.ttf",
        .title2FontPath = "Assets/Fonts/Bore Blasters 16.ttf",
        .textFontPath = "Assets/Fonts/monogram.ttf",
    },
};