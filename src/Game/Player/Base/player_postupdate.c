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
#include <input.h>

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

    // Flip the sprite when mouse is on the left side of the player
    if (Camera_ScreenVecToWorld(Input->mouse.position).x < player.state.position.x) {
        player.state.flip = SDL_FLIP_HORIZONTAL;
    } else {
        player.state.flip = SDL_FLIP_NONE;
    }

    // Handle player input, i.e movement and dashing
    Player_Input_Handler();

    // Handles when the player is in dashing state
    if(player.state.dashing) Player_HandleDash();

    //Handle when the player is in crashout state
    if(player.state.skillState.crashOut) Player_HandleCrashOut();

    if(player.state.skillState.parryActive) {
        Handle_Parry();
    }

    // Handles player movement (will be optimized later)
    Player_Move();
    Player_UpdateHitbox();
    // Update player collider
    ParticleEmitter_Update(player.resources.dashParticleEmitter);
    ParticleEmitter_Update(player.resources.crashOut);

    // Update player animation
    Player_AnimationUpdate();

    static float parryHitTimer = 0.0f;
    if (player.state.skillState.parryHit) {
        parryHitTimer += Time->rawDeltaTimeSeconds;
        Time_SetTimeScale(0.2f);
        if (parryHitTimer >= 0.1f) {
            player.state.skillState.parryHit = false;
            parryHitTimer = 0.0f;
            Time_SetTimeScale(1);
        }
    }
    ParticleEmitter_Update(player.resources.skillResources.parryParticleEmitter);
    return 0;
}