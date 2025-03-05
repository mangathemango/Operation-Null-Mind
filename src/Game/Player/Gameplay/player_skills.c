#include <player.h>
#include <time_system.h>
#include <timer.h>

/*
*   Dash the player in a direction.
*/
int Player_Dash() {
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;
    static Timer* dashCooldownTimer = NULL;
    
    if(dashCooldownTimer != NULL) //Just dash cooldown timer
    {
        if (!Timer_IsFinished(dashCooldownTimer)) return 0;
        else {
            Timer_Destroy(dashCooldownTimer);
            dashCooldownTimer = NULL;
        }
    }

    player.state.dashing = true; 
    player.state.movementLocked = true;

    dashCooldownTimer = Timer_Create(player.stats.dashCooldown);
    Timer_Start(dashCooldownTimer);
    return 0;
}

int Player_HandleDash()
{
    static Timer* dashDuration = NULL;
    if (dashDuration == NULL) {
        dashDuration = Timer_Create(player.stats.dashDuration);
        Timer_Start(dashDuration);
    }
    if (!Timer_IsFinished(dashDuration))
    {
        Vec2_Normalize(player.state.direction); //Normalize the direction
        player.state.position.x += (player.state.direction.x) * (player.stats.dashSpeed * Time->deltaTimeSeconds);
        player.state.position.y += (player.state.direction.y) * (player.stats.dashSpeed * Time->deltaTimeSeconds);
    }
    else {
        Timer_Destroy(dashDuration);
        dashDuration = NULL;
        player.state.dashing = false; //Just unchecks dashing
        player.state.movementLocked = false; //Just unchecks movementlock
    }
    
    return 0;
}
