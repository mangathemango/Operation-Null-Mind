// Written by Mango on 28/02/2025

#include <player.h>
#include <app.h>
#include <input.h>

/*
*   [Render] Renders the player sprite based on the player's and cursor's position.
*/
int Player_Render() {
    ParticleEmitter_Render(player.config.dashParticleEmitter);
    
    SDL_RendererFlip flip;
    // Flip the sprite when mouse is on the left side of the player
    if (Input->mouse.position.x < player.state.position.x) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
    Animation_Render(player.config.animation, 
                    Vec2_Subtract(
                        player.state.position,
                        Vec2_Divide(player.animData.spriteSize, 2)
                    ), 
                    player.animData.spriteSize,
                    0,
                    NULL,
                    flip);
    return 0;
}




