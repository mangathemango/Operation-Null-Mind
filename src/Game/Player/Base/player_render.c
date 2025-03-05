#include <player.h>
#include <app.h>
#include <input.h>

/*
*   Renders the player sprite based on the player's position.
*/
int Player_Render() {
    SDL_RendererFlip flip;
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




