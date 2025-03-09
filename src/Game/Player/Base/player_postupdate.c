// Written by Mango on 03/02/2025

#include <player.h>
#include <app.h>
#include <environment.h>
/*
*   [PostUpdate] This function is called inside App_PostUpdate().
?   It updates the player's input, position, and rendering.
*/
int Player_PostUpdate() {
    // Handle player input, i.e movement and dashing
    Player_Input_Handler();
    //Basically, if the movement is locked, it dash,if not, its handles normally
    if(player.state.dashing) Player_HandleDash();
    SDL_Log("%d", player.state.dashing);
    player.state.hitbox = (SDL_Rect) {
        player.state.position.x - player.animData.spriteSize.x / 2,
        player.state.position.y - player.animData.spriteSize.y / 2,
        player.animData.spriteSize.x,
        player.animData.spriteSize.y
    };
    Player_Move();

    ParticleEmitter_Update(player.config.dashParticleEmitter);

    // Update player animation
    Player_AnimationUpdate();
    return 0;
}