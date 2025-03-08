//? Written by Mango on 05/03/2025

#include <gun.h>
#include <player.h>

/*
*   [Start] Initializes the gun's animations
*/
void Gun_AnimationInit() {
    gunAnimation = Animation_Create(&gunAnimData);
    if (!gunAnimation) {
        SDL_Log("Failed to create gun animation");
    }

}

/*
*   [PostUpdate] Manages the gun's animation clips 
?   The gun is actually an animation with 5 different clips, each clip represeting a gun
?   This function will play the animation clip based on what gun the player is holding
*/
void Gun_AnimationUpdate() {
    Animation_Play(gunAnimation, player.state.currentGun->stats.name);
    Animation_Update(gunAnimation);
}