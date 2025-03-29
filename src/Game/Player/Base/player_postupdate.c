/**
 * @file player_postupdate.c
 * @brief Post-update logic for the player character
 *
 * Handles final player state updates after all other game
 * systems have been updated. Includes collision detection,
 * movement finalization, and animation updates.
 *
 * @author Mango
 * @date 2025-03-02
 */

// Written by Mango on 03/02/2025

#include <player.h>
#include <app.h>
#include <camera.h>

/**
 * @brief [PostUpdate] Main player update routine
 * 
 * This function is called inside App_PostUpdate().
 * It updates the player's input, position, and animations in sequence.
 * 
 * @return int Status code (0 for success)
 */
int Player_PostUpdate() {
    Player_DetectCollision();

    // Handle player input, i.e movement and dashing
    Player_Input_Handler();

    // Handles when the player is in dashing state
    if(player.state.dashing) Player_HandleDash();

    // Handles player movement (will be optimized later)
    Player_Move();
    Player_UpdateHitbox();
    // Update player collider
    ParticleEmitter_Update(player.resources.dashParticleEmitter);

    // Update player animation
    Player_AnimationUpdate();

    return 0;
}