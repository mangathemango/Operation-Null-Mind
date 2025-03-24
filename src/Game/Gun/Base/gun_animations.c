/**
 * @file gun_animations.c
 * @brief Handles weapon animation states and transitions
 *
 * Manages animations for different gun states including
 * idle, firing, and reloading with proper sprite flipping.
 * 
 * Note that the reloading animations aren't implemented yet.
 * 
 * Selects the appropriate animation clip based on gun orientation
 * and advances the animation frame.
 * 
 * @author Mango
 * @date 2025-03-05
 */

//? Written by Mango on 05/03/2025

#include <gun.h>
#include <player.h>

/**
 * @brief [PostUpdate] Updates the gun's animation state
 * 
 * Selects the appropriate animation clip based on gun orientation
 * and advances the animation frame.
 */
void Gun_AnimationUpdate() {
    GunData* gun = &player.state.currentGun;
    if (gun->state.flip == SDL_FLIP_NONE)       
        Animation_Play(gun->resources.animation, "left side idle");
    else                                       
        Animation_Play(gun->resources.animation, "right side idle");

    Animation_Update(gun->resources.animation);
}