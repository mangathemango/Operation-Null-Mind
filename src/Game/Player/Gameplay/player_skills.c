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
#include <gun.h>

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
    
    Sound_Play_Effect(SOUND_DASH); // Play dash sound effect
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

/**
 * @brief [Utility] Activates the Crashout skill, sacrificing health for damage
 * 
 * Takes 25% of the player's current health and gives a 2x damage multiplier
 * for 15 seconds. Has a cooldown before it can be used again.
 * 
 * @return int Status code (0 for success, 1 for on cooldown)
 */
int Player_CrashOut() {
    // Don't activate if already active or on cooldown
    if (player.state.crashOut) return 1;
    if (!Timer_IsFinished(player.resources.crashOutCooldown)) return 1;
    SDL_Log("Player_Crashout Activated");
    
    // Calculate health cost (25% of current health)
    int healthCost = player.state.currentHealth * 0.25f;
    
    // Ensure player has enough health to use this ability (at least 5 HP left)
    if (player.state.currentHealth - healthCost < 10) {
        player.state.currentHealth = 10;
    }
    else {
        player.state.currentHealth -= healthCost;
    }
    
    player.state.crashOut = true; // Activate crashout state
    
    // Activate skill effects
    // player.state.crashoutActive = true;
    // player.state.crashoutMultiplier = 2.0f;  // 2x damage multiplier
    
    // Start timers
    Timer_Start(player.resources.crashOutDuration);
    
    // Play effect
    Sound_Play_Effect(SOUND_VINE_BOOM);  // Use an appropriate sound

    
    // Create visual effect (red glow around player)

    
    return 0;
}

/**
 * @brief [Update] Handles the Crashout skill state and effects
 * 
 * Updates visual effects, checks duration, and resets state when completed.
 * 
 * @return int Status code (0 for success)
 */
int Player_HandleCrashOut() {
    if (!player.state.crashOut) return 0;
    

    // Check if duration has expired
    if (Timer_IsFinished(player.resources.crashOutDuration)) {
        // Reset state
        player.state.crashOut = false;
        // player.state.crashoutMultiplier = 1.0f;
        
        // Start cooldown
        Timer_Start(player.resources.crashOutCooldown);
        
        player.stats.crashOutCurrentMultipler = 1.0f; // Reset damage multiplier
        
        return 0;
    }
    
    player.stats.crashOutCurrentMultipler = player.state.crashOutMultiplier; // Maintain damage multiplier while active
    player.resources.crashOut->position = player.state.position;
    ParticleEmitter_ActivateOnce(player.resources.crashOut);
    ParticleEmitter_Update(player.resources.crashOut);
    SDL_Log("Player_Crashout Active");
    
    // Update visual effects while active
    // float timeLeft = Timer_GetTimeLeft(player.resources.crashoutDurationTimer) / 15.0f;
    
    // Pulsing red effect increases as time runs out
    // float pulseIntensity = 0.5f + 0.5f * (1.0f - timeLeft);
    
    // Update particle effect
    // player.resources.crashoutParticleEmitter->position = player.state.position;
    // player.resources.crashoutParticleEmitter->startColor.r = 255;
    // player.resources.crashoutParticleEmitter->startColor.a = 100 + 155 * pulseIntensity;
    
    return 0;
}