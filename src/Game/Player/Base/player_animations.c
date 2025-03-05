#include <player.h>
#include <app.h>

int Player_AnimationInit() {
    player.config.animation = Animation_Create(&player.anim);
    if (!player.config.animation) {
        SDL_Log("Failed to create player animation");
        return 1;
    }
    return 0;
}

int Player_AnimationUpdate() {
    Animation_Update(player.config.animation);
    return 0;
}