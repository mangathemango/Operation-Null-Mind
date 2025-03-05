#include <gun.h>

void Gun_Update() {
    Gun_AnimationUpdate();
    Animation_Play(gunAnimation, player.state.currentGun);
}