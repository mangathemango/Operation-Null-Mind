// Written by Mango on 03/02/2025

#include <player.h>
#include <app.h>
#include <camera.h>

/**
 * @brief [PostUpdate] Main player update routine
 * 
 * This function is called inside App_PostUpdate().
 * It updates the player's input, position, and rendering.
 * 
 * @return int Status code (0 for success)
 */
int Player_PostUpdate() {
    // Handle player input, i.e movement and dashing
    Player_Input_Handler();

    // Handles when the player is in dashing state
    if(player.state.dashing) Player_HandleDash();

    // Handles player movement (will be optimized later)
    Player_Move();
    Player_UpdateHitbox();
    Player_DetectCollision();
    // Update player collider
    ParticleEmitter_Update(player.resources.dashParticleEmitter);

    // Update player animation
    Player_AnimationUpdate();
    return 0;
}