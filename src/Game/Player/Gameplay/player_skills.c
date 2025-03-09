// Written by Mango and Darren on 05/03/2025

#include <player.h>
#include <time_system.h>
#include <timer.h>
#include <sound.h>

/*
*   [PostUpdate?] Dash the player in a direction.
*/
int Player_Dash() {
    // Doesn't dash when idle
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;
    if (!Timer_IsFinished(player.config.dashCooldownTimer)) return 0;
    
    Sound_Play_Effect(0);
    player.state.dashing = true; 
    player.state.directionLocked = true; // Player can't control movement during dash

    Timer_Start(player.config.dashCooldownTimer);
    Timer_Start(player.config.dashDurationTimer);
    return 0;
}

/*
*   [PostUpdate?] Handles the character dashing state.
?   This calls every frame player.state.dashing is true.
*/
int Player_HandleDash()
{
    // Ends the dash state when the timer is finished
    if (Timer_IsFinished(player.config.dashDurationTimer))
    {
        player.state.dashing = false; //Just unchecks dashing
        player.state.directionLocked = false; //Just unchecks movementlock
        return 0;
    }

    // Update dash particles
    float timeLeft = Timer_GetTimeLeft(player.config.dashDurationTimer) / player.stats.dashDuration;
    player.config.dashParticleEmitter->position = player.state.position;
    player.config.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);
    player.config.dashParticleEmitter->particleSpeed = 200 * timeLeft + 200;
    ParticleEmitter_ActivateOnce(player.config.dashParticleEmitter);

    player.state.currentSpeed = player.stats.dashSpeed;

    return 0;
}
