// Written by Mango on 28/02/2025

#include <player.h>
#include <app.h>
#include <input.h>

/*
*   [Render] Renders the player sprite based on the player's and cursor's position.
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




