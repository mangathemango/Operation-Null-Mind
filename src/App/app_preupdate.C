/**
 * @file app_preupdate.c
 * @brief Pre-update logic for the game loop
 *
 * Handles preliminary updates at the beginning of each frame
 * before main game systems are updated.
 *
 * @author Mango
 * @date 2025-03-01
 */

#include <app.h>
#include <input.h>
#include <time_system.h>
#include <player.h>

/**
 * @brief [PreUpdate] Early frame setup routine 
 * 
 * This function is called every frame of the program BEFORE App_Event_Handler().
 * This routine serves as a system setup for the main frame.
 * 
 * @return int Status code (0 for success)
 */
int App_PreUpdate() {
    Input_PreUpdate();
    Time_PreUpdate();

    switch (app.state.currentScene){
        case SCENE_MENU:
            break;
        case SCENE_GAME:
            Player_Preupdate();
            if(game.currentStage < 3) Sound_Queue_Next_Song("Assets/Audio/Music/return0 early level music.wav");
            else if (game.currentStage >= 3 && game.currentStage < 7)Sound_Queue_Next_Song("Assets/Audio/Music/return0 mid level music.wav");
            else if (game.currentStage >= 7) Sound_Queue_Next_Song("Assets/Audio/Music/return0 late level music.wav");
            break;
        case SCENE_PAUSE:
            break;
        case SCENE_DEATH:
            break;
    }
    return 0;
}