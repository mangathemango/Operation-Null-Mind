#include <app.h>
#include <input.h>
#include <time_system.h>
#include <player.h>

/* 
*   [PreUpdate] This function is called every frame of the program BEFORE App_Event_Handler().
?   This routine serves as a system setup for the main frame.

?   Written by Mango on 28/02/2025
*/
int App_PreUpdate() {
    Input_PreUpdate();
    Time_PreUpdate();

    switch (app.state.currentScene){
        case SCENE_MENU:
            break;
            
        case SCENE_GAME:
            Player_Preupdate();
            break;
    }
    return 0;
}