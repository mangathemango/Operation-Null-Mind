#include <player.h>
#include <app.h>
#include <environment.h>
/*
*   This function is called inside App_PostUpdate().
?   It updates the player's input, position, and rendering.
*/
int Player_PostUpdate() {
    // Handle player input, i.e movement and dashing
    Update_Player(&player); 
    Player_Input_Handler();
    //Basically, if the movement is locked, it dash,if not, its handles normally
    if(player.state.dashing) Player_HandleDash();
    else player.state.direction = Vec2_Zero;
    Player_WrapAroundScreen();

    // Update player animation
    Player_AnimationUpdate();
    return 0;
}