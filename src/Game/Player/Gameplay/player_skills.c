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
    if (player.state.movementLocked) return 0;
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
    ColliderCheckResult result;
    Collider_Check(&player.state.collider, &result);
    bool insideEnemy = false;
    for (int i = 0; i < result.count; i++){
        if (result.objects[i]->layer & COLLISION_LAYER_ENEMY){
            insideEnemy = true;
            break;
        }
    }
    if (Timer_IsFinished(player.resources.dashDurationTimer) && !insideEnemy)
    {
        player.state.dashing = false; //Just unchecks dashing
        player.state.directionLocked = false; //Just unchecks movementlock
        return 0;
    }
    if (Timer_IsFinished(player.resources.dashDurationTimer) && insideEnemy) player.state.directionLocked = false;
    // Update dash particles
    float timeLeft = Timer_GetTimeLeft(player.resources.dashDurationTimer) / player.stats.dashDuration;
    player.resources.dashParticleEmitter->position = player.state.position;
    player.resources.dashParticleEmitter->direction = Vec2_RotateDegrees(player.state.direction, 180);
    player.resources.dashParticleEmitter->particleSpeed = 200 * timeLeft + 200;
    ParticleEmitter_ActivateOnce(player.resources.dashParticleEmitter);

    player.state.currentSpeed = player.stats.dashSpeed;
    return 0;
}

bool LastStand()
{
    if(player.state.skills.lastStand == true)
    {
        static bool lastStandActive = false;
        if(player.state.currentHealth <= 0 && !lastStandActive)
        {
            player.state.currentHealth = player.stats.maxHealth;
            lastStandActive = true;
            player.state.skills.lastStand = false;
            Timer_Start(player.resources.INVINCIBLE_Timer);
            Sound_Play_Effect(1);
            return true;
        }
    }

    return false;
}