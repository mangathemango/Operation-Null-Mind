/**
 * @file gun_update.c
 * @brief Handles gun positioning, animation and state updates
 *
 * Updates the position, rotation, and particle systems for weapons
 * based on player position and input direction.
 *
 * @author Mango
 * @date 2025-03-06
 */

//? Written by Mango on 06/03/2025

#include <gun.h>
#include <player.h>
#include <input.h>
#include <math.h>
#include <camera.h>

/**
 * @brief [PostUpdate] Updates the gun's state, position, and particles
 * 
 * Updates the gun's position relative to the player, calculates the angle based on
 * mouse position, and updates particle emitter positions for muzzle flash and casings.
 * Flips the gun sprite horizontally when aiming to the left.
 */
void Gun_Update(){
    GunData* gun = &player.state.currentGun;
    
    // Convert mouse position from screen to world coordinates
    Vec2 mouseWorldPosition = Camera_ScreenVecToWorld(Input->mouse.position);
    
    // Define player-specific gun offset (aesthetic adjustment)
    Vec2 playerGunOffset = {0, -5}; // -5 moves the gun down a bit for aesthetics
    
    // Use the generalized gun position update function
    Gun_UpdatePosition(gun, player.state.position, mouseWorldPosition, playerGunOffset);
    
    // Update particle emitters (player-specific behavior)
    if(gun->resources.casingParticleEmitter){
        ParticleEmitter_Update(gun->resources.casingParticleEmitter);
    }
    
    if(gun->resources.muzzleFlashEmitter){
        ParticleEmitter_Update(gun->resources.muzzleFlashEmitter);
    }

    // Update gun's animations
    Gun_AnimationUpdate();
}