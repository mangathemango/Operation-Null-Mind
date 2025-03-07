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

    // Create dash cooldown timer
    static Timer* dashCooldownTimer = NULL;
    if(dashCooldownTimer != NULL) 
    {
        if (!Timer_IsFinished(dashCooldownTimer)) return 0;
        else {
            Timer_Destroy(dashCooldownTimer);
            dashCooldownTimer = NULL;
        }
    }

    Sound_Play_Effect(0);
    player.state.dashing = true; 
    player.state.movementLocked = true; // Player can't control movement during dash

    // Set dash cooldown timer for next time
    dashCooldownTimer = Timer_Create(player.stats.dashCooldown);
    Timer_Start(dashCooldownTimer);
    return 0;
}

/*
*   [PostUpdate?] Handles the character dashing state.
?   This calls every frame player.state.dashing is true.
*/
int Player_HandleDash()
{
    // Update dash particles
    player.config.dashParticleEmitter->position = player.state.position;
    player.config.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);

    // Start dashDuration timer
    static Timer* dashDuration = NULL;
    if (dashDuration == NULL) {
        dashDuration = Timer_Create(player.stats.dashDuration);
        Timer_Start(dashDuration);
    }

    if (!Timer_IsFinished(dashDuration))
    {
        float timeLeft = Timer_GetTimeLeft(dashDuration);
        player.config.dashParticleEmitter->particleSpeed = 5000 * timeLeft + 200;
        ParticleEmitter_ActivateOnce(player.config.dashParticleEmitter);
        // Moves the player every frame player is still in dash state
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
