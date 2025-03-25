/**
 * @file player_skills.c
 * @brief Implements player special abilities and skills
 *
 * Handles the activation, cooldown and effects of player skills
 * such as dashing, special attacks, and other abilities.
 *
 * @author Mango
 * @date 2025-03-05
 */

// Written by Mango and Darren on 05/03/2025

#include <player.h>
#include <time_system.h>
#include <timer.h>
#include <sound.h>
#include <camera.h>

/**
 * @brief [Utility] Initiates player dash movement if conditions are met
 * 
 * Activates the dash ability if off cooldown and player has directional input.
 * Plays dash sound effect and locks direction during dash.
 * 
 * @return int Status code (0 for success)
 * 
 * @todo [player_skills.c:24] Change dash sfx
 */
int Player_Dash() {
    // Doesn't dash when idle
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;
    if (!Timer_IsFinished(player.resources.dashCooldownTimer)) return 0;
    
    Sound_Play_Effect(0);
    player.state.dashing = true; 
    player.state.directionLocked = true; // Player can't control movement during dash

    Timer_Start(player.resources.dashCooldownTimer);
    Timer_Start(player.resources.dashDurationTimer);
    return 0;
}

/**
 * @brief [Utility] Processes player dash state and effects
 * 
 * This is called every frame player.state.dashing is true.
 * Updates dash particle effects and handles dash movement.
 * 
 * @return int Status code (0 for success)
 */
int Player_HandleDash() {
    // Ends the dash state when the timer is finished
    if (Timer_IsFinished(player.resources.dashDurationTimer))
    {
        player.state.dashing = false; //Just unchecks dashing
        player.state.directionLocked = false; //Just unchecks movementlock
        return 0;
    }

    // Update dash particles
    float timeLeft = Timer_GetTimeLeft(player.resources.dashDurationTimer) / player.stats.dashDuration;
    player.resources.dashParticleEmitter->position = player.state.position;
    player.resources.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);
    player.resources.dashParticleEmitter->particleSpeed = 200 * timeLeft + 200;
    ParticleEmitter_ActivateOnce(player.resources.dashParticleEmitter);

    player.state.currentSpeed = player.stats.dashSpeed;

    return 0;
}
