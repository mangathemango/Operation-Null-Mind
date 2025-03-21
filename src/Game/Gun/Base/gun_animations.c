//? Written by Mango on 05/03/2025

#include <gun.h>
#include <player.h>

/**
 * @brief [PostUpdate] Updates the gun's animation state
 * 
 * Note that the reloading animations aren't implemented yet.
 */
void Gun_AnimationUpdate() {
    GunData* gun = player.state.currentGun;
    if (gun->state.flip == SDL_FLIP_NONE)       
        Animation_Play(gun->resources.animation, "left side idle");
    else                                       
        Animation_Play(gun->resources.animation, "right side idle");

    Animation_Update(gun->resources.animation);
}