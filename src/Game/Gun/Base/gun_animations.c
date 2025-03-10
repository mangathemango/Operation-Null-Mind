//? Written by Mango on 05/03/2025

#include <gun.h>
#include <player.h>

/*
*   [PostUpdate] Manages the gun's animation clips 
?   The gun is actually an animation with 5 different clips, each clip represeting a gun
?   This function will play the animation clip based on what gun the player is holding
*/
void Gun_AnimationUpdate() {
    GunData* gun = player.state.currentGun;
    if (gun->state.flip == SDL_FLIP_NONE)       
        Animation_Play(gun->resources.animation, "left side idle");
    else                                       
        Animation_Play(gun->resources.animation, "right side idle");

    Animation_Update(gun->resources.animation);
}