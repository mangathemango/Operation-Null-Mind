//? Written by Mango on 07/03/2025

#include <player.h>
#include <app.h>

/*
*   [Start] Initializes the player's animations
*/
int Player_AnimationInit() {
    player.resources.animation = Animation_Create(&player.animData);
    if (!player.resources.animation) {
        SDL_Log("Failed to create player animation");
        return 1;
    }
    return 0;
}

/*
*   [PostUpdate] Update's the player's animations
*/
int Player_AnimationUpdate() {
    if (player.state.moving) {
        Animation_Play(player.resources.animation, "walk");
    } else {
        Animation_Play(player.resources.animation, "idle");
    }
    Animation_Update(player.resources.animation);
    return 0;
}