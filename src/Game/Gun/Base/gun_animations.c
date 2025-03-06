#include <gun.h>
#include <player.h>

void Gun_AnimationInit() {
    gunAnimation = Animation_Create(&gunAnimData);
    if (!gunAnimation) {
        SDL_Log("Failed to create gun animation");
    }

}

void Gun_AnimationUpdate() {
    Animation_Play(gunAnimation, player.state.currentGun->stats.name);
    Animation_Update(gunAnimation);
}