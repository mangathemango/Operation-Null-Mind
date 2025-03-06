#include <app.h>
#include <input.h>
#include <time_system.h>
#include <player.h>

/* 
*   [PreUpdate] This function is called every frame of the program BEFORE App_Event_Handler().
?   This routine serves as a system setup for the main frame.
*/
int App_PreUpdate() {
    Input_PreUpdate();
    Time_PreUpdate();
    Player_Preupdate();
    return 0;
}