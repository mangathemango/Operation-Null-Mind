#include <player.h>
#include <time_system.h>
#include <timer.h>
#include <sound.h>

/*
*   Dash the player in a direction.
*/
int Player_Dash() {
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;
    static Timer* dashCooldown = NULL;
    
    if(dashCooldown != NULL) //Just dash cooldown timer
    {
        if (!Timer_IsFinished(dashCooldown)) return 0;
        else {
            Timer_Destroy(dashCooldown);
            dashCooldown = NULL;
        }
    }

    Sound_Play_Effect(0);
    player.state.dashing = true; 
    player.state.movementLocked = true;

    dashCooldown = Timer_Create(1);
    Timer_Start(dashCooldown);
    return 0;
}

int Player_HandleDash()
{
    static Timer* dashDuration = NULL;
    if (dashDuration == NULL) {
        dashDuration = Timer_Create(0.1);
        Timer_Start(dashDuration);
    }
    if (!Timer_IsFinished(dashDuration))
    {
        Vec2_Normalize(player.state.direction); //Normalize the direction
        player.state.position.x += (player.state.direction.x) * (player.config.dashSpeed * Time->deltaTimeSeconds);
        player.state.position.y += (player.state.direction.y) * (player.config.dashSpeed * Time->deltaTimeSeconds);
    }
    else {
        Timer_Destroy(dashDuration);
        dashDuration = NULL;
        player.state.dashing = false; //Just unchecks dashing
        player.state.movementLocked = false; //Just unchecks movementlock
    }
    
    return 0;
}
