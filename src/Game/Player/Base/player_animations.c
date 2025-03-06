#include <player.h>
#include <app.h>

/*
*   [Start] Initializes the player's animations
*/
int Player_AnimationInit() {
    player.config.animation = Animation_Create(&player.animData);
    if (!player.config.animation) {
        SDL_Log("Failed to create player animation");
        return 1;
    }
    return 0;
}

/*
*   [PostUpdate] Update's the player's animations
*/
int Player_AnimationUpdate() {
    Animation_Update(player.config.animation);
    return 0;
}