// Written by Mango on 03/02/2025

#include <player.h>
#include <app.h>

/*
*   [PostUpdate] This function is called inside App_PostUpdate().
?   It updates the player's input, position, and rendering.
*/
int Player_PostUpdate() {
    // Handle player input, i.e movement and dashing
    Player_Input_Handler();

    if(player.state.dashing) Player_HandleDash();
    else player.state.direction = Vec2_Zero;

    ParticleEmitter_Update(player.config.dashParticleEmitter);

    Player_WrapAroundScreen();

    // Update player animation
    Player_AnimationUpdate();
    return 0;
}