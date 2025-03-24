/**
 * @file player_render.c
 * @brief Handles rendering of the player character
 *
 * Contains functions for drawing the player's sprite,
 * animations, effects, and UI elements tied to the player.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <player.h>
#include <app.h>
#include <input.h>

/**
 * @brief [Render] Renders the player sprite based on the player's and cursor's position
 * 
 * Draws the player's character sprite and dash particle effects at the appropriate
 * screen position. Flips the sprite based on mouse cursor position.
 * 
 * @return int Status code (0 for success)
 */
int Player_Render() {
    ParticleEmitter_Render(player.resources.dashParticleEmitter);
    
    SDL_RendererFlip flip;
    // Flip the sprite when mouse is on the left side of the player
    if (Camera_ScreenVecToWorld(Input->mouse.position).x < player.state.position.x) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    Animation_Render(
        player.resources.animation,            
        Camera_WorldVecToScreen(
            Vec2_ToCenteredPosition(
                player.state.position,
                player.animData.spriteSize
            )
        ), 
        player.animData.spriteSize,
        0,
        NULL,
        flip
    );
    return 0;
}




