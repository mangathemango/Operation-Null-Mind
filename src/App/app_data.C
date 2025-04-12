/**
 * @file app_data.c
 * @brief Application data structures and default values
 *
 * Contains the initialization of core application data structures
 * including window settings, game state, and configuration.
 *
 * @author Mango
 * @date 2025-02-28
 */

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
        .averageFps = 0,
        .currentScene = SCENE_MENU,
    },
    .config = {
        .window_title = "Operation Null Mind" ,
        .window_width = 1024 ,
        .window_height = 768 ,
        .window_fullscreen = true ,
        .screen_width = 480 ,
        .screen_height = 288 ,
        
        .debug = false,
        
        .title1FontPath = "Assets/Fonts/FFF Forward.ttf",
        .title2FontPath = "Assets/Fonts/FFF Forward.ttf",
        .textFontPath = "Assets/Fonts/monogram.ttf",
    },
};