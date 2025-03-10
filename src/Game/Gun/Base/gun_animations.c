//? Written by Mango on 05/03/2025

#include <gun.h>
#include <player.h>

/*
*   [Start] Initializes the gun's animations
*/
void Gun_AnimationInit() {
    for (int i = 0; i < GUN_COUNT; i++) {
        GunData* gun = &GunList[i];
        gun->resources.animation = Animation_Create(&gun->animData);
    }
}

/*
*   [PostUpdate] Manages the gun's animation clips 
?   The gun is actually an animation with 5 different clips, each clip represeting a gun
?   This function will play the animation clip based on what gun the player is holding
*/
void Gun_AnimationUpdate() {
    GunData* gun = player.state.currentGun;
    Animation_Play(gunAnimation, player.state.currentGun->name);
    Animation_Update(gunAnimation);
}