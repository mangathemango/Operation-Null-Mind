#include <gun.h>

void Gun_AnimationInit() {
    gunAnimation = Animation_Create(&gunAnimData);
    if (!gunAnimation) {
        SDL_Log("Failed to create gun animation");
    }
}

void Gun_AnimationUpdate() {
    Animation_Update(gunAnimation);
}